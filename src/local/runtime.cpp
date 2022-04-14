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
    auto runtime_module_it = runtime_modules_.find(filename);

    if (static_module_it == static_modules_.end()) {
        throw run_exception("local: run: static module was not loaded correctly");
    }

    // Only instantiate if not already instantiated (todo: for this specific architecture)
    if (runtime_module_it == runtime_modules_.end()) {
        runtime_modules_.insert({filename, std::make_shared<RuntimeModule>(static_module_it->second)});
        runtime_module_it = runtime_modules_.find(filename);
    }

    auto start_section = runtime_module_it->second->static_module()->get_section<StartSection>();
    if (start_section != nullptr) { // TODO: will this return nullptr if not present?
        invoke_function(runtime_module_it->second, start_section->get_idx(), true);
    }

    // StaticModule must export a start function
    auto exports = runtime_module_it->second->static_module()->get_section<ExportSection>()->exports();
    bool found_main = false;
    for (const auto &exp : exports) {
        if (exp.second.export_name() == "_start" && exp.second.export_type() == ExternalKind::FUNCTION) {
            found_main = true;
            auto runtime = runtime_module_it->second;
            invoke_function(runtime_module_it->second, exp.second.index());
            break;
        }
    }

    if (!found_main) {
        throw run_exception("local: run: module did not export _start function");
    }
}

void Runtime::invoke_function(std::shared_ptr<RuntimeModule> runtime_module, int function_index, bool startFunction) {
    auto &functions = runtime_module->functions();
    auto func = functions.find(function_index);

    if (func == functions.end()) {
        throw run_exception("local: run: tried to invoke nonexistent function with id " + std::to_string(function_index));
    }

    // TODO: Imported functions are ignored for now
    if (!func->second.internal_function()) return;

    // Have we seen this function before?
    if (!func->second.is_compiled()) {
        if (startFunction) return; // TODO: Compiler::compile()
        else remote_compile(func->second);
    }

    func->second.invoke();
}