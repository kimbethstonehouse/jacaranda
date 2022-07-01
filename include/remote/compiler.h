#pragma once

#include <decoder.h>
#include <jitaas.pb.h>
#include <llvm/IR/Module.h>

class Compiler {
public:
    Compiler() {}
    ~Compiler() { for (auto entry : module_architecture_pairs_) delete entry.second; }
    void compile(const WasmFunction *wasm, NativeBinary *native);
private:
    Decoder decoder_;
    std::map<std::string, llvm::Module *> module_architecture_pairs_;
};