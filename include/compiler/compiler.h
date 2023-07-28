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

struct Visitor : public InstVisitor<Visitor> {
    Visitor() {
        registers_.push_back("r8");
        registers_.push_back("r9");
        registers_.push_back("r10");
        registers_.push_back("r11");
        registers_.push_back("r12");
        registers_.push_back("r13");
        registers_.push_back("r14");
        registers_.push_back("r15");
    }

    void visitFunction(Function &F) {
        llvm::errs() << "\t.type\t" << F.getName() << ",@function" << "\n";
        llvm::errs() << F.getName() << ":" << "\n";
        llvm::errs() << "pushq\t%rbp" << "\n";
        llvm::errs() << "movq\t%rsp, %rbp" << "\n";
        //        llvm::errs() << "Function: " << F.getName() << "\n";
    }

    void visitBasicBlock(BasicBlock &B) {
//        llvm::errs() << "BasicBlock: " << B.getName() << "\n";
    }

    void visitBranchInst(BranchInst &I) {
//        I.getCondition();
        llvm::errs() << "BranchInst: " << I << "\n";
    }

    void visitAllocaInst(AllocaInst &I) {
        llvm::errs() << "AllocaInst: " << I << "\n";
    }

    void visitLoadInst(LoadInst &I) {
        llvm::errs() << "LoadInst: " << I << "\n";
    }

    void visitStoreInst(StoreInst &I) {
        llvm::errs() << "StoreInst: " << I << "\n";
    }

    void visitICmpInst(ICmpInst &I) {
        llvm::errs() << "ICmpInst: " << I << "\n";
    }

    void visitBinaryOperator(BinaryOperator &I) {
        llvm::errs() << "BinaryOperator: " << I << "\n";
    }

    void visitReturnInst(ReturnInst &I) {
        llvm::errs() << "ReturnInst: " << I << "\n";
    }
private:
    std::vector<std::string> registers_;
    std::string getRegister() {
        std::string temp = registers_.front();
        registers_.pop_back();
        return temp;
    }

    void freeRegister(std::string reg) {
        registers_.push_back(reg);
    }
};