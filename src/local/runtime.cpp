#include <runtime.h>

// TODO: communicate with compiler
//void Runtime::ask_compiler() {
//    int cfd;
//    // Create a new client socket with domain: AF_UNIX, type: SOCK_STREAM, protocol: 0
//    int cfd;
//    struct sockaddr_un addr;
//
//    // Create a new client socket with domain: AF_UNIX, type: SOCK_STREAM, protocol: 0
//    if ((cfd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
//        std::cerr << "client socket creation failed" << std::endl;
//        return -1;
//    }
//
//    // Construct server address, and make the connection.
//    memset(&addr, 0, sizeof(struct sockaddr_un));
//    addr.sun_family = AF_UNIX;
//    strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) - 1);
//
//    // Connects the active socket referred to be cfd to the listening socket
//    // whose address is specified by addr.
//    if (connect(cfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1) {
//        std::cerr << "client socket connection failed" << std::endl;
//        return -1;
//    }f ((cfd = connect()) == -1) {
//        return -1;
//    }
//
//    // Protocol: first four bytes specify length of data
//    write(cfd, &src_len, 4);
//    if (write(cfd, src_code, src_len) != src_len) {
//        std::cerr << "client socket write failed" << std::endl;
//        return 1;
//    }
//
//    char bin_code[MAX_FILE_SIZE];
//    int bin_len, num_read;
//
//    // Read at most BUF_SIZE bytes from the socket into buf.
//    read(cfd, &bin_len, 4);
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
//}

Module Runtime::load_module(const std::string &filename) {
    Module module(filename);
    modules_.push_back(module);
    return module;
}

void Runtime::run() {
    // TODO
}
