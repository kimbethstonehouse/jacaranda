#pragma once

#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>
#include <jitaas.h>
#include <section.h>

class Compiler {
public:
    Compiler() {}
    ~Compiler() {}

    std::vector<unsigned char> compile(Payload source);
private:
};

// TODO: Not currently parsed.
/* A sequence of local variable declarations followed by bytecode
 * instructions. Instructions are encoded as an opcode followed by
 * zero or mode immediates. Each function body must end with the end opcode. */
class FunctionBody {
public:
    FunctionBody() {}
private:
    unsigned int body_size_;
    unsigned int local_count_;
    std::map<int, LocalEntry> local_variables_;
    Payload code_;
};