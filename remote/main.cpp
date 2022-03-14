#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>
#include <jitaas.h>

int open_socket() {
    int sfd;
    struct sockaddr_un addr;

    if ((sfd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        std::cerr << "remote socket creation failed" << std::endl;
        return -1;
    }

    // Make sure the address we're planning to use isn't too long.
    if (strlen(SV_SOCK_PATH) > sizeof(addr.sun_path) - 1) {
        std::cerr << "remote socket path too long" << std::endl;
        return -1;
    }

    // Delete any file that already exists at the address. Make sure the deletion
    // succeeds. If the error is just that the file/directory doesn't exist, it's fine.
    if (remove(SV_SOCK_PATH) == -1 && errno != ENOENT) {
        std::cerr << "could not remove previous remote socket" << std::endl;
        return -1;
    }

    // Zero out the address, and set family and path.
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) - 1);

    // Bind the socket to the address. Note that we're binding the server socket
    // to a well-known address so that clients know where to connect.
    if (bind(sfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1) {
        std::cerr << "remote socket bind failed" << std::endl;
        return -1;
    }

    // The listen call marks the socket as *passive*. The socket will subsequently
    // be used to accept connections from *active* sockets.
    // listen cannot be called on a connected socket (a socket on which a connect()
    // has been succesfully performed or a socket returned by a call to accept()).
    if (listen(sfd, BACKLOG) == -1) {
        std::cerr << "remote socket listen failed" << std::endl;
        return -1;
    }

    return sfd;
}

/** Read file into buffer. */
inline int read(const char *path, char *buffer) {
    std::ifstream file(path);
    int i = -1;
    if (file.is_open()) {
        i = 0;
        while(!file.eof() && i < MAX_FILE_SIZE) {
            file.get(buffer[i]);
            i++;
        }
    }
    file.close();
    return i;
}

int main(int argc, char **argv) {
    int sfd;

    if ((sfd = open_socket()) == -1) {
        return 1;
    }

    int src_size, num_read;
    for (;;) {          /* Handle client connections iteratively */

        // Accept a connection. The connection is returned on a NEW
        // socket, 'cfd'; the listening socket ('sfd') remains open
        // and can be used to accept further connections. */
        std::cout << "Waiting to accept a connection..." << std::endl;

        // NOTE: blocks until a connection request arrives.
        int cfd = accept(sfd, NULL, NULL);
        std::cout << "Accepted socket " << cfd << std::endl;

        //         Read at most BUF_SIZE bytes from the socket into buf.
        // unless signalled by EOF, read or recv will block until BUF_SIZE chars are read;

        read(cfd, &src_size, 4);
        char src_code[src_size];
        num_read = read(cfd, src_code, src_size);
        // Then, write those bytes from buf into STDOUT.
        write(STDOUT_FILENO, src_code, num_read);

        // TODO: invoke compiler

        char bin_code[MAX_FILE_SIZE];
        int bin_len = read(BIN_FILE_NAME, bin_code);

        // Protocol: first four bytes specify length of data
        write(cfd, &bin_len, 4);
        if (write(cfd, bin_code, bin_len) != bin_len) {
            std::cerr << "server socket write failed" << std::endl;
            return 1;
        }

        if (close(cfd) == -1) {
            std::cerr << "server socket close failed" << std::endl;
            return 1;
        }
    }
}