#pragma once

#include <jitaas.pb.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>

class Compiler {
    static std::map<unsigned char, llvm::Type *> llvm_types;
    typedef llvm::SmallVector<llvm::PHINode*, 1> PhiVector;

public:
    Compiler() {}
    ~Compiler() {
        for (auto entry : module_architecture_pairs_) { delete entry.second; }
    }
    void compile(const WasmFunction *wasm, NativeBinary *native);
private:
    void createLLVMIR(const WasmFunction *wasm);
    PhiVector createPhis(llvm::BasicBlock* basic_block, llvm::IRBuilder<> &ir_builder, llvm::Type *type);
    void addGlobalData(const WasmFunction *wasm, llvm::Module *llvm_module);
    std::map<std::string, llvm::Module *> module_architecture_pairs_;
};