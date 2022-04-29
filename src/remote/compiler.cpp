#include <iostream>
#include <compiler.h>

int Compiler::compile(char *src_code, char *bin_code) {
    // int bin_len = read(BIN_FILE_NAME, bin_code);
    *(bin_code) = 0x48;
    *(bin_code+1) = 0x8d;
    *(bin_code+2) = 0x3e;

    *(bin_code+3) = 0xe8;
    *(bin_code+4) = 0x00;
    *(bin_code+5) = 0x00;
    *(bin_code+6) = 0x00;
    *(bin_code+7) = 0x00;

    *(bin_code+8) = 0x48;
    *(bin_code+9) = 0x89;
    *(bin_code+10) = 0xc1;

    *(bin_code+11) = 0x48;
    *(bin_code+12) = 0x8d;
    *(bin_code+13) = 0x7e;
    *(bin_code+14) = 0x08;

    *(bin_code+15) = 0xe8;
    *(bin_code+16) = 0x00;
    *(bin_code+17) = 0x00;
    *(bin_code+18) = 0x00;
    *(bin_code+19) = 0x00;

    *(bin_code+20) = 0x48;
    *(bin_code+21) = 0x01;
    *(bin_code+22) = 0xc8;

    *(bin_code+23) = 0xc3;
    return 24;
}

void Compiler::open_socket() {
    std::cout << "Opening a socket..." << std::endl;

    if ((sfd_ = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        throw socket_exception("remote: socket creation failed");
    }

    // Delete any socket file that already exists
    if (remove(SOCKET_FILE) == -1 && errno != ENOENT) {
        throw socket_exception("remote: previous socket file removal failed");
    }

    // Zero out the address and set family and path
    memset(&addr_, 0, sizeof(struct sockaddr_un));
    addr_.sun_family = AF_UNIX;
    strncpy(addr_.sun_path, SOCKET_FILE, sizeof(addr_.sun_path) - 1);

    // Bind the socket to the address
    if (bind(sfd_, (struct sockaddr *) &addr_, sizeof(struct sockaddr_un)) == -1) {
        throw socket_exception("remote: socket bind failed");
    }

    std::cout << "socket fd " << sfd_ << std::endl;


    // Mark the socket as passive to accept incoming connections
    if (listen(sfd_, BACKLOG) == -1) {
        throw socket_exception("remote: socket listen failed");
    }
}

// Handle client connections iteratively, passing each accepted connection to be serviced
[[ noreturn ]] void Compiler::handle_connections() {
    std::cout << "Waiting to accept a connection..." << std::endl;

//    char *bin_code = "lea (%rsi), %rdi\n"
//                     "call atoi\n"
//                     "mov %rax, %rcx\n"
//                     "\n"
//                     "lea 8(%rsi), %rdi\n"
//                     "call atoi\n"
//                     "\n"
//                     "add %rcx, %rax\n"
//                     "ret";
//    int bin_len = read(BIN_FILE_NAME, bin_code);

    for (;;) {
        // Connection is returned on a new socket
        // The listening socket remains open for further connections
        int cfd = accept(sfd_, NULL, NULL);

        std::cout << "Accepted a connection, fd..." << cfd << std::endl;

        int src_size, num_read;

        // TODO: ideally the below becomes a separate thread and we keep spinning
        read(cfd, &src_size, 4);
        char src_code[src_size];
        num_read = read(cfd, src_code, src_size);

        char bin_code[24];
        int bin_len = compile(src_code, bin_code);

        // Protocol: first four bytes specify length of data
        write(cfd, &bin_len, 4);
        if (write(cfd, bin_code, bin_len) != bin_len) {
            throw run_exception("run: remote: server socket write failed");
        }

        if (close(cfd) == -1) {
            throw run_exception("run: remote: server socket close failed");
        }
    }
}