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

struct Visitor : public InstVisitor<Visitor, Value *> {
    Visitor() {
        code.init(rt.environment(), rt.cpuFeatures());
    }

    template<class Iterator>
    Value *accept(Iterator Start, Iterator End) {
        while (Start != End)
            this->accept(*Start++);
        return nullptr;
    }

    Value *accept(Module &M, x86::Compiler cc) {
        this->visitModule(M);
        accept(M.begin(), M.end());
        return nullptr;
    }

    Value *accept(Function &F) {
        this->visitFunction(F);
        accept(F.begin(), F.end());
        return nullptr;
    }
    Value *accept(BasicBlock &BB) {
        this->visitBasicBlock(BB);
        accept(BB.begin(), BB.end());
        return nullptr;
    }

    // visit - Finally, code to visit an instruction...
    //
    Value *visit(Instruction &I) {
//        static_assert(std::is_base_of<InstVisitor, SubClass>::value,
//                      "Must pass the derived type to this template!");

        switch (I.getOpcode()) {
            default: llvm_unreachable("Unknown instruction type encountered!");
                // Build the switch statement using the Instruction.def file...
#define HANDLE_INST(NUM, OPCODE, CLASS) \
    case Instruction::OPCODE: return \
                      visit##OPCODE(static_cast<CLASS&>(I));
#include "llvm/IR/Instruction.def"
        }
    }

    Value *accept(Value &V) {
        if (auto I = dyn_cast<Instruction>(&V)) return this->visit(*I);
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

    Value *visitInstruction(Instruction &I) {
        return nullptr;
    }

    Value *visitValue(Value &V) {
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
        x86::Gp vReg = cc.newGpd();
        accept(*I.getPointerOperand());
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
    JitRuntime rt;
    CodeHolder code;
    x86::Compiler *cc;
};