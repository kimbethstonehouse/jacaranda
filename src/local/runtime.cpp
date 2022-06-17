#include <runtime.h>
#include <section.h>
#include <sys/un.h>

#include <grpcpp/create_channel.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/DynamicLibrary.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>

// Opens a connection to the compiler
Runtime::Runtime(JacarandaClient *client) : client_(client) {
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
    munmap(jump_table_, runtime_module_->function_count() * PTR_SIZE);
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

extern "C" void *do_request_compilation(int function_index, Runtime *runtime) {
    return runtime->request_compilation(function_index);
}


void *Runtime::request_compilation(int function_index) {
    // Check if the specified function exists in this module
    auto &functions = runtime_module_->functions();
    auto func = functions.find(function_index);

    if (func == functions.end()) {
        throw execute_exception("tried to invoke nonexistent function with id " + std::to_string(function_index));
    }

    // Imported functions are ignored for now
//    if (!func->second.internal_function()) return nullptr;

    // Write to the remote compiler asking for the compiled code
    NativeBinary native = client_->compile("add-x86",function_index,
                                           func->second.internal_function(),
                                           func->second.function_type(),
                                           func->second.function_body(),
                                           target_machine_->createDataLayout().getStringRepresentation(),
                                           target_machine_->getProgramPointerSize());


    memcpy(next_function_, native.data_bytes().data(), native.data_length());
    jump_table_[function_index] = next_function_;

    // Pad to 16 bytes
    next_function_ += align(native.data_length(), 16);
    return jump_table_[function_index];
}

void Runtime::load_module(const std::string &filename) {
    // Only load if not already loaded
    if (static_modules_.find(filename) == static_modules_.end()) {
        static_modules_.insert({filename, std::make_shared<StaticModule>(filename)});
    }
}

void Runtime::run(const std::string &filename, int argc, char **argv) {
    auto static_module_it = static_modules_.find(filename);

    if (static_module_it == static_modules_.end()) {
        throw execute_exception("static module was not loaded correctly");
    }

    // Instantiate the runtime module and runtime environment
    runtime_module_ = new RuntimeModule(static_module_it->second);
    init_execution_state(runtime_module_->function_count());

    auto start_section = runtime_module_->static_module()->get_section<Wasm::StartSection>();
    if (start_section != nullptr) {
        if (jump_table_[start_section->get_idx()] == &trampoline_to_compile) request_compilation(start_section->get_idx());
        trampoline_to_execute(start_section->get_idx(), jump_table_, argc, argv, this);
    }

    // StaticModule must export a start function
    auto exports = runtime_module_->static_module()->get_section<Wasm::ExportSection>()->exports();
    bool found_main = false;
    for (const auto &exp : exports) {
        // The main function may be called something else, but let's ignore that for now
        if (exp.second.export_name() == "__main_argc_argv" && exp.second.export_type() == ExternalKind::FUNCTION) {
            found_main = true;
            if (jump_table_[exp.second.index()] == &trampoline_to_compile) request_compilation(exp.second.index());
            int res = trampoline_to_execute(exp.second.index(), jump_table_, argc, argv, this);
            std::cout << "Result: " << res << std::endl;
            break;
        }
    }

    if (!found_main) {
        throw execute_exception("module did not export _start function");
    }
}

void Runtime::init_execution_state(int function_count) {
    jump_table_ = (void **) mmap(nullptr, function_count * PTR_SIZE,
                                PROT_EXEC | PROT_READ | PROT_WRITE,MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    for (int i = 0; i < function_count; i++) {
        jump_table_[i] = (void *) &trampoline_to_compile;
    }
}