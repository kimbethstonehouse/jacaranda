#pragma once

#include <llvm/IR/Module.h>
#include <decoder.h>
#include <compiler-envoy-client.h>
#include <llvm/IR/InstVisitor.h>
#include <llvm/Support/raw_ostream.h>
#include <asmjit.h>

using namespace llvm;
using namespace asmjit;

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

struct Visitor : public InstVisitor<Visitor, BaseReg> {
    Visitor(BaseCompiler &cc) : cc(cc), reg_idx(0) { }

    template<class Iterator>
    BaseReg accept(Iterator Start, Iterator End) {
        while (Start != End)
            this->accept(*Start++);
        return none;
    }

    BaseReg accept(Module &M) {
        this->visitModule(M);
        accept(M.begin(), M.end());
        return none;
    }

    BaseReg accept(Function &F) {
        this->visitFunction(F);
        accept(F.begin(), F.end());
        return none;
    }
    BaseReg accept(BasicBlock &BB) {
        this->visitBasicBlock(BB);
        accept(BB.begin(), BB.end());
        return none;
    }

    BaseReg accept(Value &V) {
        if (auto I = dyn_cast<Instruction>(&V)) return this->visit(*I);
        // todo: if argument, if global variable, etc
        return this->visitValue(V);
    }

    BaseReg visitModule(Module &M) {
        llvm::errs() << "Visiting module!" << "\n";
        return none;
    }

    BaseReg visitFunction(Function &F) {
        llvm::errs() << "\t.type\t" << F.getName() << ",@function" << "\n";
        llvm::errs() << F.getName() << ":" << "\n";
        llvm::errs() << "pushq\t%rbp" << "\n";
        llvm::errs() << "movq\t%rsp, %rbp" << "\n";
        return none;
        //        llvm::errs() << "Function: " << F.getName() << "\n";
    }

    BaseReg visitBasicBlock(BasicBlock &B) {
//        llvm::errs() << "BasicBlock: " << B.getName() << "\n";
        return none;

    }

    BaseReg visitInstruction(Instruction &I) {
        return none;
    }

    BaseReg visitValue(Value &V) {
        return none;
    }

    BaseReg visitBranchInst(BranchInst &I) {
//        I.getCondition();
        llvm::errs() << "BranchInst: " << I << "\n";
        return none;
    }

    BaseReg visitAllocaInst(AllocaInst &I) {
        llvm::errs() << "AllocaInst: " << I << "\n";
        BaseReg *out;
        cc._newReg(out, TypeId::kUInt32); // todo: HACK, get type from Alloca
        return *out;
    }

    BaseReg visitLoadInst(LoadInst &I) {
        BaseReg reg = accept(*I.getPointerOperand());
        llvm::errs() << "LoadInst: " << I << "\n";
        return none;
    }

    BaseReg visitStoreInst(StoreInst &I) {
        llvm::errs() << "StoreInst: " << I << "\n";
        return none;
    }

    BaseReg visitICmpInst(ICmpInst &I) {
        llvm::errs() << "ICmpInst: " << I << "\n";
        return none;
    }

    BaseReg visitBinaryOperator(BinaryOperator &I) {
        llvm::errs() << "BinaryOperator: " << I << "\n";
        return none;
    }

    BaseReg visitReturnInst(ReturnInst &I) {
        llvm::errs() << "ReturnInst: " << I << "\n";
        return none;
    }

private:
    BaseCompiler &cc;
    BaseReg none;
    BaseReg **base_regs;
    int reg_idx;
};
