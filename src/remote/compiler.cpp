#include <iostream>

#include "compiler.h"

void Compiler::open_socket() {
    if ((sfd_ = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        throw socket_exception("remote: socket creation failed");
    }

    // Make sure the socket filepath isn't too long
    if (strlen(SOCKET_FILE) > sizeof(addr_.sun_path) - 1) {
        throw socket_exception("remote: socket path too long");
    }

    // Delete any socket file that already exists
    if (remove(SOCKET_FILE) == -1 && errno != ENOENT) {
        throw socket_exception("remote: could not remove previous socket");
    }

    // Zero out the address and set family and path
    memset(&addr_, 0, sizeof(struct sockaddr_un));
    addr_.sun_family = AF_UNIX;
    strncpy(addr_.sun_path, SOCKET_FILE, sizeof(addr_.sun_path) - 1);

    // Bind the socket to the address
    if (bind(sfd_, (struct sockaddr *) &addr_, sizeof(struct sockaddr_un)) == -1) {
        throw socket_exception("remote: socket bind failed");
    }

    // Mark the socket as passive to accept incoming connections
    if (listen(sfd_, BACKLOG) == -1) {
        throw socket_exception("remote: socket listen failed");
    }
}

// Handles client connections iteratively, passing each accepted connection to be serviced
[[ noreturn ]] void Compiler::handle_connections() {
    for (;;) {
        // Connection is returned on a new socket
        // The listening socket remains open for further connections
        int cfd = accept(sfd_, NULL, NULL);

        // TODO: accepted a connection, ideally the below becomes a separate thread and we keep spinning
//        read(cfd, &src_size, 4);
//        char src_code[src_size];
//        num_read = read(cfd, src_code, src_size);
//        // Then, write those bytes from buf into STDOUT.
//        write(STDOUT_FILENO, src_code, num_read);
//
//        // TODO: invoke compiler
//
//        char bin_code[MAX_FILE_SIZE];
//        int bin_len = read(BIN_FILE_NAME, bin_code);
//
//        // Protocol: first four bytes specify length of data
//        write(cfd, &bin_len, 4);
//        if (write(cfd, bin_code, bin_len) != bin_len) {
//            std::cerr << "server socket write failed" << std::endl;
//            return 1;
//        }
//
//        if (close(cfd) == -1) {
//            std::cerr << "server socket close failed" << std::endl;
//            return 1;
//        }
    }
}