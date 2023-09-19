#include <grpcpp/create_channel.h>
#include <sys/un.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/DynamicLibrary.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <runtime.h>

// The envoy communicates with other components (e.g. the compiler) on our behalf
Runtime::Runtime(std::shared_ptr<RuntimeEnvoy> envoy) : envoy_(envoy) {
    // Map regions of memory to execute native code
    code_section_ = (char *) mmap(nullptr, pow(2, 30),
                                  PROT_EXEC | PROT_READ | PROT_WRITE,MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (code_section_ == MAP_FAILED) {
        throw execute_exception("mmap failed");
    }
    next_function_ = code_section_;
    create_target_machine();
}

Runtime::~Runtime() {
    munmap(code_section_, pow(2, 30));
//    munmap(jump_table_, function_count_ * PTR_SIZE);
}

void Runtime::create_target_machine() {
    // Init LLVM
    llvm::InitializeAllTargetInfos();
    llvm::InitializeAllTargets();
    llvm::InitializeAllTargetMCs();
    llvm::InitializeAllAsmPrinters();
    llvm::InitializeAllAsmParsers();
    llvm::InitializeAllDisassemblers();
    llvm::sys::DynamicLibrary::LoadLibraryPermanently(nullptr);

    llvm::Triple triple(llvm::sys::getProcessTriple());
    llvm::SmallVector<std::string, 1> targetAttributes;

#if LLVM_VERSION_MAJOR < 10
    if(triple.getArch() == llvm::Triple::x86 || triple.getArch() == llvm::Triple::x86_64)
	{
		// Disable AVX-512 on X86 targets to workaround a LLVM backend bug:
		// https://bugs.llvm.org/show_bug.cgi?id=43750
		targetAttributes.push_back("-avx512f");
	}
#endif

    target_machine_ = std::unique_ptr<llvm::TargetMachine>(llvm::EngineBuilder().selectTarget(
            llvm::Triple(llvm::sys::getProcessTriple()), "",
            llvm::sys::getHostCPUName(), targetAttributes));
}

// A trampoline method that facilitates invoking an object member function from x86 code
extern "C" void *do_request_compilation(int function_index, Runtime *runtime) {
    return runtime->request_compilation(function_index);
}

void *Runtime::request_compilation(int function_index) {
    // Write to the remote compiler asking for the compiled code
    NativeBinary native = envoy_->request_compile(module_name_, "x86", function_index,
                                          target_machine_->createDataLayout().getStringRepresentation(),
                                          target_machine_->getProgramPointerSize());

    // Copy the result into executable memory and update the jump table pointer
    memcpy(next_function_, native.data_bytes().data(), native.data_length());
    runtime_state_.jump_table[function_index] = next_function_;

    // x86 optimisation: x86 CPUs can branch more efficiently when targets are 16-byte aligned
    next_function_ += align(native.data_length(), 16);
    return runtime_state_.jump_table[function_index];
}

// todo: fix return type
extern "C" void invoke_function(void *state, int fn_idx, void *args, int nr_args);

void Runtime::run(const std::string &filename, int argc, char **argv) {
    set_module_name(filename);
    request_function_indices();
    init_execution_state();

    // Todo: match imports to exports from another module
    // Note that imports can be reexported, so the function index may correspond to an import from another module

    // The start index refers to an optional start section in the WebAssembly module, intended for initialising the state of a module
    if (start_idx_.has_value()) {
        invoke_function(&runtime_state_, start_idx_.has_value(), nullptr, 0);
    }

    // The main index refers to the first function to be executed, and is NOT optional
    invoke_function(&runtime_state_, main_idx_, argv, argc);

//    if (jump_table_[main_idx_] == &trampoline_to_compile) request_compilation(main_idx_);
//    int res = trampoline_to_execute(main_idx_, jump_table_, argc, argv, this);
//    std::cout << "Result: " << res << std::endl;
}

// The runtime needs to know how many functions are in the WebAssembly module, and what the starting function index is
// The actual WebAssembly binary is stored in the central code repository, and the runtime does not access it
void Runtime::request_function_indices() {
    FunctionIndices indices = envoy_->request_function_indices(module_name_);
    function_count_ = indices.func_count();
    if (indices.has_start_idx()) start_idx_ = indices.start_idx();
    main_idx_ = indices.main_idx();
}

static void function_stub(runtime_state *rt, int fn_idx, void *argv, int argc) {
    std::cout << "function stub" << std::endl;
    rt->rt->request_compilation(fn_idx);
    invoke_function(rt, fn_idx, argv, argc);
}

// Initialise each function pointer to the address of the compile function
void Runtime::init_execution_state() {
    runtime_state_.rt = this;
    runtime_state_.jump_table = (void **) mmap(nullptr, function_count_ * PTR_SIZE, PROT_READ | PROT_WRITE,MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    for (int i = 0; i < function_count_; i++) {
        runtime_state_.jump_table[i] = (void *) &function_stub;
    }
}
