#include <runtime.h>
#include <section.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <jitaas.h>
#include <unistd.h>

Runtime::Runtime() {
    code_section_ = (char *) mmap(nullptr, pow(2, 30),
                                  PROT_EXEC | PROT_READ | PROT_WRITE,MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    next_function_ = code_section_;
}

Runtime::~Runtime() { munmap(code_section_, pow(2, 30)); }

void Runtime::remote_compile(Function &func) {
    int cfd;
    struct sockaddr_un addr;
    if ((cfd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        throw run_exception("local: run: creating new client socket failed");
    }

    // Construct server address, and make the connection
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_FILE, sizeof(addr.sun_path) - 1);

    // Connects the active socket referred to by cfd to the listening socket specified by addr
    if (connect(cfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1) {
        throw run_exception("local: run: creating new client socket failed");
    }

    Payload &func_body = func.function_body();
    int body_size = (int) func_body.size();

    // Protocol: first four bytes specify length of data
    write(cfd, &body_size, 4);
    // TODO: write signature too
    if (write(cfd, func_body.data_start(), body_size) != body_size) {
        throw run_exception("local: run: client socket write failed");
    }

    // Read the size of the compiled code
    read(cfd, &body_size, 4);
    if (read(cfd, (void *) next_function_, body_size) != body_size) {
        throw run_exception("local: run: client socket read failed");
    }

    func.update_pointer(next_function_);

    // Pad to 16 bytes
    next_function_ += align(body_size, 16);

    if (close(cfd) == -1) {
        throw run_exception("local: run: client socket close failed");
    }
}

void Runtime::load_module(const std::string &filename) {
    // Only load if not already loaded
    if (static_modules_.find(filename) == static_modules_.end()) {
        static_modules_.insert({filename, std::make_shared<StaticModule>(filename)});
    }
}

void Runtime::run(const std::string &filename) {
    auto static_module_it = static_modules_.find(filename);

    if (static_module_it == static_modules_.end()) {
        throw run_exception("local: run: static module was not loaded correctly");
    }

    // Instantiate the runtime module
    runtime_module_ = RuntimeModule(static_module_it->second);

    auto start_section = runtime_module_.static_module()->get_section<StartSection>();
    if (start_section != nullptr) {
        invoke_function(start_section->get_idx(), true);
    }

    // StaticModule must export a start function
    auto exports = runtime_module_.static_module()->get_section<ExportSection>()->exports();
    bool found_main = false;
    for (const auto &exp : exports) {
        // TODO: the main function may be called something else
        if (exp.second.export_name() == "__main_argc_argv" && exp.second.export_type() == ExternalKind::FUNCTION) {
            found_main = true;
            // TODO: straight to jump table here
            invoke_function(exp.second.index());
            break;
        }
    }

    if (!found_main) {
        throw run_exception("local: run: module did not export _start function");
    }
}

void invoke_function(RuntimeModule *runtime_module, int function_index, bool start_function) {
    // TODO put arguments into registers
    // then find the jump table entry and just invoke that
    // this will either invoke the compiled code or will call compile_reinvoke_function

    ExecutionState state;
    state.FunctionIndex = function_index;
    state.Mod = runtime_module;

    runtime_module->invoke_function(&state);
}

void Runtime::compile_reinvoke_function(int function_index, bool start_function) {
    auto &functions = runtime_module_.functions();
    auto func = functions.find(function_index);

    if (func == functions.end()) {
        throw run_exception("local: run: tried to invoke nonexistent function with id " + std::to_string(function_index));
    }

    // TODO: Imported functions are ignored for now
    if (!func->second.internal_function()) return;

    // Have we seen this function before?
    if (!func->second.is_compiled()) {
        if (start_function) return; // TODO: Compiler::compile()
        else remote_compile(func->second);
    }

    func->second.invoke();
}