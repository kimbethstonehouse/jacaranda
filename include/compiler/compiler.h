#pragma once

#include <llvm/IR/Module.h>
#include <decoder.h>
#include <compiler-envoy-client.h>
#include <llvm/IR/InstVisitor.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;

class Compiler {
public:
    Compiler(std::shared_ptr<CompilerEnvoyClient> envoy) : envoy_(envoy) {}
//    ~Compiler() { for (auto entry : module_architecture_pairs_) delete entry.second; }
    void compile(const CompilationRequest *request, NativeBinary *native);

private:
    Decoder decoder_;
    std::shared_ptr<CompilerEnvoyClient> envoy_;
//    std::map<std::string, llvm::Module *> module_architecture_pairs_;
};

struct Visitor : public InstVisitor<Visitor, Value *> {
    Visitor() {}

    // Generic visit method - Allow visitation to all instructions in a range
    template<class Iterator>
    Value *visit(Iterator Start, Iterator End) {
        while (Start != End)
            this->accept(*Start++);
        return nullptr;
    }

    // Define visitors for functions and basic blocks...
    Value *visit(Module &M) {
        this->visitModule(M);
        visit(M.begin(), M.end());
        return nullptr;
    }
    Value *visit(Function &F) {
        this->visitFunction(F);
        visit(F.begin(), F.end());
        return nullptr;
    }
    Value *visit(BasicBlock &BB) {
        this->visitBasicBlock(BB);
        visit(BB.begin(), BB.end());
        return nullptr;
    }

    Value *visitInstruction(Instruction &I) {
        return nullptr;
    }

    Value *visitValue(Value &V) {
        return nullptr;
    }

    Value *accept(Value &V) {
        if (auto I = dyn_cast<Instruction>(&V)) return this->visit(I);
        // todo: if argument, if global variable, etc
        return this->visitValue(V);
    }

    Value *visitModule(Module &M) {
        llvm::errs() << "Visiting module!" << "\n";
        return nullptr;
    }

    Value *visitFunction(Function &F) {
        llvm::errs() << "\t.type\t" << F.getName() << ",@function" << "\n";
        llvm::errs() << F.getName() << ":" << "\n";
        llvm::errs() << "pushq\t%rbp" << "\n";
        llvm::errs() << "movq\t%rsp, %rbp" << "\n";
        return nullptr;
        //        llvm::errs() << "Function: " << F.getName() << "\n";
    }

    Value *visitBasicBlock(BasicBlock &B) {
//        llvm::errs() << "BasicBlock: " << B.getName() << "\n";
        return nullptr;

    }

    Value *visitBranchInst(BranchInst &I) {
//        I.getCondition();
        llvm::errs() << "BranchInst: " << I << "\n";
        return nullptr;
    }

    Value *visitAllocaInst(AllocaInst &I) {
        llvm::errs() << "AllocaInst: " << I << "\n";
        return nullptr;
    }

    Value *visitLoadInst(LoadInst &I) {
        llvm::errs() << "LoadInst: " << I << "\n";
        return nullptr;
    }

    Value *visitStoreInst(StoreInst &I) {
        llvm::errs() << "StoreInst: " << I << "\n";
        return nullptr;
    }

    Value *visitICmpInst(ICmpInst &I) {
        llvm::errs() << "ICmpInst: " << I << "\n";
        return nullptr;
    }

    Value *visitBinaryOperator(BinaryOperator &I) {
        llvm::errs() << "BinaryOperator: " << I << "\n";
        return nullptr;
    }

    Value *visitReturnInst(ReturnInst &I) {
        llvm::errs() << "ReturnInst: " << I << "\n";
        return nullptr;
    }
private:

};