#include <runtime.h>
#include <section.h>
#include <sys/un.h>
#include <jitaas.h>

char *main_str = "main";
char *atoi_str = "atoi";

Payload main_payload(main_str, 4);
Payload atoi_payload(atoi_str, 4);

// Opens a connection to the compiler
Runtime::Runtime() : client_("127.0.0.1", 8080) {
    // Map regions of memory to execute native code
    code_section_ = (char *) mmap(nullptr, pow(2, 30),
                                  PROT_EXEC | PROT_READ | PROT_WRITE,MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    next_function_ = code_section_;
}

Runtime::~Runtime() {
    munmap(code_section_, pow(2, 30));
    munmap(jump_table_, runtime_module_->function_count() * PTR_SIZE);
}

extern "C" void *Runtime::request_compilation(int function_index) {
    // Check if the specified function exists in this module
    auto &functions = runtime_module_->functions();
    auto func = functions.find(function_index);

    if (func == functions.end()) {
        throw run_exception("local: run: tried to invoke nonexistent function with id " + std::to_string(function_index));
    }

    // Imported functions are ignored for now
    if (!func->second.internal_function()) return nullptr;

    // TODO: send the actual src payload rather than function name
    // Write to the remote compiler asking for the compiled code
    std::vector<char> binary = client_.call("compile", function_index == 0 ? main_payload : atoi_payload).as<std::vector<char>>();
    std::memcpy(next_function_, binary.data(), binary.size());

    jump_table_[function_index] = next_function_;

    // Pad to 16 bytes
    next_function_ += align(binary.size(), 16);
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
        throw run_exception("local: run: static module was not loaded correctly");
    }

    // Instantiate the runtime module and runtime environment
    runtime_module_ = new RuntimeModule(static_module_it->second);
    init_jump_table(runtime_module_->function_count());

    auto start_section = runtime_module_->static_module()->get_section<StartSection>();
    if (start_section != nullptr) {
        if (jump_table_[start_section->get_idx()] == &trampoline_to_compile) request_compilation(start_section->get_idx());
        trampoline_to_execute(argc, argv, start_section->get_idx(), jump_table_);
    }

    // StaticModule must export a start function
    auto exports = runtime_module_->static_module()->get_section<ExportSection>()->exports();
    bool found_main = false;
    for (const auto &exp : exports) {
        // The main function may be called something else, but let's ignore that for now
        if (exp.second.export_name() == "__main_argc_argv" && exp.second.export_type() == ExternalKind::FUNCTION) {
            found_main = true;
            if (jump_table_[exp.second.index()] == &trampoline_to_compile) request_compilation(exp.second.index());
            int res = trampoline_to_execute(argc, argv, exp.second.index(), jump_table_);
//            std::cout << "Result: " << res << std::endl;
            break;
        }
    }

    if (!found_main) {
        throw run_exception("local: run: module did not export _start function");
    }
}

void Runtime::init_jump_table(int function_count) {
    jump_table_ = (void **) mmap(nullptr, function_count * PTR_SIZE,
                                PROT_EXEC | PROT_READ | PROT_WRITE,MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    for (int i = 0; i < function_count; i++) {
        jump_table_[i] = (void *) &trampoline_to_compile;
    }
}