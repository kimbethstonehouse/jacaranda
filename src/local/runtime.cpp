#include <runtime.h>
#include <section.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <jitaas.h>
#include <unistd.h>

// TODO: communicate with compiler
// TODO: open connection, write into socket, read from socket
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
    if (write(cfd, func_body.data_start(), body_size) != body_size) {
        throw run_exception("local: run: client socket write failed");
    }

    // TODO: read compiled code into function ptr
//    char bin_code[MAX_FILE_SIZE];
//    int bin_len, num_read;
//
//    // Read the size of the compiled code
//    read(cfd, &body_size, 4);
//    if ((num_read = read(cfd, bin_code, bin_len)) != bin_len) {
//        std::cerr << "client socket read failed" << std::endl;
//    }
//
//    // Then, write those bytes from buf into STDOUT.
//    write(STDOUT_FILENO, bin_code, bin_len);
//
//    // TODO: execute a.out
//
//    if (close(cfd) == -1) {
//        std::cerr << "client socket close failed" << std::endl;
//        return 1;
//    }
}

void Runtime::load_module(const std::string &filename) {
    if (static_modules_.find(filename) == static_modules_.end()) {
        static_modules_.insert({filename, StaticModule(filename)});
    }
}

void Runtime::run(const std::string &filename) {
    auto static_module_it = static_modules_.find(filename);
    auto runtime_module_it = runtime_modules_.find(filename);

    if (static_module_it == static_modules_.end()) {
        throw run_exception("local: run: static module was not loaded correctly");
    }

    // Only load if not previously been loaded
    if (runtime_module_it == runtime_modules_.end()) {
        runtime_modules_.insert({filename, RuntimeModule(static_module_it->second)});
        runtime_module_it = runtime_modules_.find(filename);
    }

    auto start_section = runtime_module_it->second.static_module().get_section<StartSection>();
    if (start_section != nullptr) { // TODO: will this return nullptr if not present?
        invoke_function(runtime_module_it->second, start_section->get_idx(), true);
    }

    // StaticModule must export a start function
    auto exports = runtime_module_it->second.static_module().get_section<ExportSection>()->exports();
    bool found_main = false;
    for (const auto &exp : exports) {
        if (exp.second.export_name() == "_start" && exp.second.export_type() == ExternalKind::FUNCTION) {
            found_main = true;
            invoke_function(runtime_module_it->second, exp.second.index());
            break;
        }
    }

    if (!found_main) {
        throw run_exception("local: run: module did not export _start function");
    }
}

void Runtime::invoke_function(RuntimeModule &runtime_module, const int& function_index, bool startFunction) {
    auto functions = runtime_module.functions();
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