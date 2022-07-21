#pragma once

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Intrinsics.h>

#include <jitaas.pb.h>
#include <wasm.h>

class Decoder {
    typedef llvm::SmallVector<llvm::PHINode *, 1> PhiVector;
    static std::map<unsigned char, llvm::Type *> llvm_types;

public:
    void createLLVMIR(const CompilationRequest *request, const WasmFunction *function);

    PhiVector createPhis(llvm::BasicBlock *basic_block, llvm::IRBuilder<> &ir_builder, llvm::Type *type);

    // This is called after unconditional control flow to indicate that operators following it
    // are unreachable until the control stack is popped.
    void enterUnreachable();

private:
    // Compiles a literal value to an LLVM constant of the correct type
//    inline llvm::ConstantInt *emitLiteral(llvm::LLVMContext &llvm_context, unsigned int value) {
//        return llvm::ConstantInt::get(llvm_context, llvm::APInt(32, (WAVM::U64) value, false));
//    }

    // Functions that map between the symbols used for externally visible functions and the function
    inline std::string getExternalName(const char *baseName, uintptr_t index) {
        return std::string(baseName) + std::to_string(index);
    }

    // Converts a WebAssembly variable type to an LLVM type.
    inline llvm::Type *asLLVMType(llvm::LLVMContext &llvm_context, unsigned int value_type) {
        switch (value_type) {
            case LanguageTypes::I32:
                return llvm::Type::getInt32Ty(llvm_context);
            case LanguageTypes::I64:
                return llvm::Type::getInt64Ty(llvm_context);
            case LanguageTypes::F32:
                return llvm::Type::getFloatTy(llvm_context);
//            case LanguageTypes::F64:
            default:
                return llvm::Type::getDoubleTy(llvm_context);
        }

        throw decode_exception(
                "encountered unsupported variable type during conversion to llvm ir: " + std::to_string(value_type));
    }

    // Converts a WebAssembly function type to an LLVM type.
    inline llvm::FunctionType *asLLVMType(llvm::LLVMContext &llvm_context, const FunctionType &function_type) {
        llvm::Type **llvm_param_types = (llvm::Type **) alloca(sizeof(llvm::Type *) * function_type.param_count());

        for (uintptr_t param_idx = 0; param_idx < function_type.param_count(); ++param_idx) {
            llvm_param_types[param_idx] = asLLVMType(llvm_context, function_type.param_types(param_idx));
        }

        llvm::Type *llvm_return_type = asLLVMType(llvm_context, function_type.return_type());

        return llvm::FunctionType::get(llvm_return_type,
                                       llvm::ArrayRef<llvm::Type *>(llvm_param_types, function_type.param_count()),
                                       false);
    }
};