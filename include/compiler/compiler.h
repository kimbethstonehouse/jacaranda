#pragma once

#include <llvm/IR/Module.h>
#include <decoder.h>
#include <compiler-envoy-client.h>

class Compiler {
public:
    Compiler(CompilerEnvoyClient *envoy) : envoy_(envoy) {}
    ~Compiler() {
        delete envoy_;
        for (auto entry : module_architecture_pairs_) delete entry.second;
    }
    void compile(const CompilationRequest *request, NativeBinary *native);
private:
    Decoder decoder_;
    CompilerEnvoyClient *envoy_;
    std::map<std::string, llvm::Module *> module_architecture_pairs_;
};