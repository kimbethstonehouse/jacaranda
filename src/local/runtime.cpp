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

Runtime::~Runtime() {
    munmap(code_section_, pow(2, 30));
    munmap(jump_table_, runtime_module_->function_count() * PTR_SIZE);
}

void Runtime::request_compilation(int function_index) {
    // Check if the specified function exists in this module
    auto &functions = runtime_module_->functions();
    auto func = functions.find(function_index);

    if (func == functions.end()) {
        throw run_exception("local: run: tried to invoke nonexistent function with id " + std::to_string(function_index));
    }

    // Imported functions are ignored for now
    if (!func->second.internal_function()) return;

    // Write to the remote compiler asking for the compiled code
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

    Payload &func_body = func->second.function_body();
    int body_size = (int) func_body.size();

    // Protocol: first four bytes specify length of data
    write(cfd, &body_size, 4);
    // TODO: write signature too
    if (write(cfd, func_body.data_start(), body_size) != body_size) {
        throw run_exception("local: run: client socket write failed");
    }

    // Read the size of the compiled code
    read(cfd, &body_size, 4);
    // TODO: patch any function calls in the binary with the function's jump table entry
    // TODO: also push the function index onto the stack if it has not yet been compiled
    if (read(cfd, (void *) next_function_, body_size) != body_size) {
        throw run_exception("local: run: client socket read failed");
    }

    jump_table_[function_index] = next_function_;

    // Pad to 16 bytes
    next_function_ += align(body_size, 16);

    if (close(cfd) == -1) {
        throw run_exception("local: run: client socket close failed");
    }

    // TODO: return function pointer
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
        trampoline_to_execute(argc, argv, jump_table_[start_section->get_idx()]);
    }

    // StaticModule must export a start function
    auto exports = runtime_module_->static_module()->get_section<ExportSection>()->exports();
    bool found_main = false;
    for (const auto &exp : exports) {
        // The main function may be called something else, but let's ignore that for now
        if (exp.second.export_name() == "__main_argc_argv" && exp.second.export_type() == ExternalKind::FUNCTION) {
            found_main = true;
            if (jump_table_[exp.second.index()] == &trampoline_to_compile) request_compilation(exp.second.index());
            trampoline_to_execute(argc, argv, jump_table_[exp.second.index()]);
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