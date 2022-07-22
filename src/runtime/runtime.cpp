#include <grpcpp/create_channel.h>
#include <sys/un.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/DynamicLibrary.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <runtime.h>

// The envoy communicates with other components (e.g. the compiler) on our behalf
Runtime::Runtime(RuntimeEnvoy *envoy) : envoy_(envoy) {
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
    delete envoy_;
    munmap(code_section_, pow(2, 30));
    munmap(jump_table_, function_count_ * PTR_SIZE);
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
    NativeBinary native = envoy_->request_compile("add", "x86", function_index,
                                          target_machine_->createDataLayout().getStringRepresentation(),
                                          target_machine_->getProgramPointerSize());

    memcpy(next_function_, native.data_bytes().data(), native.data_length());
    jump_table_[function_index] = next_function_;

    // Pad to 16 bytes
    next_function_ += align(native.data_length(), 16);
    return jump_table_[function_index];
}

void Runtime::run(const std::string &filename, int argc, char **argv) {
    request_function_indices(filename);
    init_execution_state();

    if (start_idx_.has_value()) {
        if (jump_table_[start_idx_.value()] == &trampoline_to_compile) request_compilation(start_idx_.value());
        trampoline_to_execute(start_idx_.value(), jump_table_, argc, argv, this);
    }

    if (jump_table_[main_idx_] == &trampoline_to_compile) request_compilation(main_idx_);
    int res = trampoline_to_execute(main_idx_, jump_table_, argc, argv, this);
    std::cout << "Result: " << res << std::endl;
}

// The runtime needs to know how many functions are in the WebAssembly module, and what the starting function index is
// The rest of the WebAssembly binary can perhaps be stored elsewhere, like the code repository
void Runtime::request_function_indices(const std::string &filename) {
    FunctionIndices indices = envoy_->request_function_indices(filename);
    function_count_ = indices.func_count();
    if (indices.has_start_idx()) start_idx_ = indices.start_idx();
    main_idx_ = indices.main_idx();
}

void Runtime::init_execution_state() {
    jump_table_ = (void **) mmap(nullptr, function_count_ * PTR_SIZE,
                                PROT_EXEC | PROT_READ | PROT_WRITE,MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    for (int i = 0; i < function_count_; i++) {
        jump_table_[i] = (void *) &trampoline_to_compile;
    }
}