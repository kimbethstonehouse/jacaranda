#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>
#include <iostream>

#define SV_SOCK_PATH "/tmp/us_xfr"
#define BUF_SIZE 100
#define BACKLOG 5

int connect() {
    int cfd;
    struct sockaddr_un addr;

    // Create a new client socket with domain: AF_UNIX, type: SOCK_STREAM, protocol: 0
    if ((cfd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        std::cerr << "client socket creation failed" << std::endl;
        return -1;
    }

    // Construct server address, and make the connection.
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) - 1);

    // Connects the active socket referred to be cfd to the listening socket
    // whose address is specified by addr.
    if (connect(cfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1) {
        std::cerr << "client socket connection failed" << std::endl;
        return -1;
    }

    return cfd;
}

int main(int argc, char **argv)
{
    int cfd;
    // Create a new client socket with domain: AF_UNIX, type: SOCK_STREAM, protocol: 0
    if ((cfd = connect()) == -1) {
        return -1;
    }
//    if (argc < 2) {
//        std::cerr << "usage: " << argv[0] << " file.wasm [args]" << std::endl;
//        return 1;
//    }
//
//    const char* wasm_file = argv[1];

    char *cbuf = "Hello from client socket!\n";
    int num_read;
    char sbuf[BUF_SIZE];
    ssize_t buf_len = strlen(cbuf);

    if (write(cfd, cbuf, buf_len) != buf_len) {
        std::cerr << "client socket write failed" << std::endl;
        return 1;
    }

    // Read at most BUF_SIZE bytes from the socket into buf.
    while ((num_read = read(cfd, sbuf, BUF_SIZE)) > 0) {
        // Then, write those bytes from buf into STDOUT.
        write(STDOUT_FILENO, sbuf, num_read);
    }

    if (num_read == -1) {
        std::cerr << "client socket read failed" << std::endl;
        return 1;
    }

    // Closes our socket; server sees EOF.
    exit(EXIT_SUCCESS);
}