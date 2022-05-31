#pragma once

#include <jitaas.pb.h>

class Compiler {
public:
    Compiler() {}
    ~Compiler() {}
    void compile(const Binary *wasm, Binary *native);
};

// TODO: Not currently parsed.
/* A sequence of local variable declarations followed by bytecode
 * instructions. Instructions are encoded as an opcode followed by
 * zero or mode immediates. Each function body must end with the end opcode. */
//class FunctionBody {
//public:
//    FunctionBody() {}
//private:
//    unsigned int body_size_;
//    unsigned int local_count_;
//    std::map<int, LocalEntry> local_variables_;
//    Payload code_;
//};