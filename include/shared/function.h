#pragma once

#include <section.h>
#include <llvm/IR/Module.h>
#include <ast.h>
#include <llvm/IR/IRBuilder.h>

namespace Wasm {
    class Function {
    public:
        Function(bool internal_function, unsigned int function_index, std::shared_ptr<Wasm::FunctionType> function_type, std::shared_ptr<Payload> function_body) :
                internal_function_(internal_function), function_index_(function_index), function_type_(function_type),
                function_body_(function_body) {}

        bool internal_function() const { return internal_function_; }
        std::shared_ptr<Wasm::FunctionType> function_type() const { return function_type_; }
        std::shared_ptr<Payload> function_body() const { return function_body_; }

    private:
        bool internal_function_;
        unsigned int function_index_;
        std::shared_ptr<Wasm::FunctionType> function_type_;
        std::shared_ptr<Payload> function_body_;
    };

/* A sequence of local variable declarations followed by bytecode
 * instructions. Instructions are encoded as an opcode followed by
 * zero or mode immediates. Each function body must end with the end opcode.
 * body_size varuint32: indicating the size in bytes of the function body to follow
 * local_count varuint32: indicating the number of local entries
 * locals local_entry*: repeated LocalEntries
 * code byte*: bytecode of the function
 * end byte: 0x0b to indicate the end of the body */
    class FunctionBody {
    public:
        FunctionBody(unsigned int index, Payload payload, Wasm::FunctionType function_type) : index_(index), payload_(payload), function_type_(function_type) {}

        llvm::Value *get_llvm_int_value(unsigned char type, int value);
        llvm::Value *get_llvm_fp_value(unsigned char type, double value);
        llvm::Type *get_llvm_type(unsigned char type);

        void get_local();
        void set_local();

        void emit_i32_const();
        void emit_i32_eqz();
        void emit_i32_add();
        void emit_i32_sub();

        LocalEntry local(int idx) { return local_variables_.at(idx); }
        unsigned int local_count() { return local_count_; }
        std::shared_ptr<llvm::Module> parse_body();
    private:
        Payload payload_;
        unsigned int index_;
        unsigned int body_size_;
        unsigned int local_count_;
        Wasm::FunctionType function_type_;
        std::shared_ptr<llvm::LLVMContext> llvm_context_;
        std::shared_ptr<llvm::IRBuilder<>> llvm_ir_builder_;
        std::shared_ptr<llvm::Module> llvm_module_;
        std::vector<llvm::Value *> allocas_;
        std::vector<Wasm::LocalEntry> local_variables_;
    };
}
