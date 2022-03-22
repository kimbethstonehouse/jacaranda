#pragma once

#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>
#include <jitaas.h>

class Compiler {
public:
    Compiler() {}
    ~Compiler() { close_socket(); }

    void open_socket();
    [[ noreturn ]] void handle_connections();
private:
    void close_socket() { close(sfd_); }

    int sfd_;
    struct sockaddr_un addr_;
};

class socket_exception : public std::runtime_error
{
public:
    socket_exception(const std::string &message) : runtime_error(message) {}
};