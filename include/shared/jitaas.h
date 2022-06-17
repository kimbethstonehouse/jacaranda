#pragma once
#include <fstream>
#include <llvm/IR/Constant.h>
#include <llvm/ADT/Twine.h>
#include <llvm/IR/DerivedTypes.h>
#include <wasm.h>
#include <jitaas.pb.h>

#define MAX_FILE_SIZE 102400 // 100KB max
#define PTR_SIZE 8

inline size_t align(size_t a, size_t b) { return (1 + (a - 1) / b) * b; }

// Compiles a literal value to an LLVM constant of the correct type
inline llvm::ConstantInt* emitLiteral(llvm::LLVMContext& llvm_context, unsigned int literal_type) {

    return llvm::ConstantInt::get(llvm_context, llvm::APInt(32, (U64)value, false));
}

// Functions that map between the symbols used for externally visible functions and the function
inline std::string getExternalName(const char* baseName, uintptr_t index){
    return std::string(baseName) + std::to_string(index);
}

// Converts a WebAssembly variable type to an LLVM type.
inline llvm::Type* asLLVMType(llvm::LLVMContext& llvm_context, unsigned int value_type) {
    switch (value_type) {
        case LanguageTypes::I32:
            return llvm::Type::getInt32Ty(llvm_context);
        case LanguageTypes::I64:
            return llvm::Type::getInt64Ty(llvm_context);
        case LanguageTypes::F32:
            return llvm::Type::getFloatTy(llvm_context);
        case LanguageTypes::F64:
            return llvm::Type::getDoubleTy(llvm_context);
    }

    throw compile_exception("encountered unsupported variable type during conversion to llvm ir: " + value_type);
}

// Converts a WebAssembly function type to an LLVM type.
inline llvm::FunctionType* asLLVMType(llvm::LLVMContext& llvm_context, const FunctionType &function_type) {
    llvm::Type** llvm_param_types = (llvm::Type**) alloca(sizeof(llvm::Type*) * function_type.param_count());

    for(uintptr_t param_idx = 0; param_idx < function_type.param_count(); ++param_idx) {
        llvm_param_types[param_idx] = asLLVMType(llvm_context, function_type.param_types().at(param_idx));
    }

    llvm::Type* llvm_return_type = asLLVMType(llvm_context, function_type.return_type());

    return llvm::FunctionType::get(llvm_return_type, llvm::ArrayRef<llvm::Type*>(llvm_param_types,
                                                                                 function_type.param_count()), false);
}

///** Read file into buffer. */
inline int read(const char *path, char *buffer) {
    std::ifstream file(path);
    file.open(path, std::ifstream ::binary);
    int i = -1;
    if (file.is_open()) {
        i = 0;
        while(!file.eof() && i < MAX_FILE_SIZE) {
            char c;
            file.get(c);
            i++;
        }
    }
    file.close();
    return i;
}