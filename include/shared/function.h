#pragma once

#include <section.h>
#include <llvm/IR/Module.h>
#include <ast.h>
#include <llvm/IR/IRBuilder.h>
#include "jacaranda.pb.h"

namespace Wasm {
//    class Function {
//    public:
//        Function(bool internal_function, unsigned int function_index, std::shared_ptr<::WasmFunctionType> function_type, std::shared_ptr<Payload> function_body) :
//                internal_function_(internal_function), function_index_(function_index), function_type_(function_type),
//                function_body_(function_body) {}
//
//        bool internal_function() const { return internal_function_; }
//        std::shared_ptr<::WasmFunctionType> function_type() const { return function_type_; }
//        std::shared_ptr<Payload> function_body() const { return function_body_; }
//
//    private:
//        bool internal_function_;
//        unsigned int function_index_;
//        std::shared_ptr<::WasmFunctionType> function_type_;
//        std::shared_ptr<Payload> function_body_;
//    };

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
        FunctionBody(unsigned int index, Payload payload, ::WasmFunctionType function_type) : index_(index), payload_(payload), function_type_(function_type) {}

        llvm::Value *get_llvm_int_value(unsigned char type, int value);
        llvm::Value *get_llvm_fp_value(unsigned char type, double value);
        llvm::Type *get_llvm_type(unsigned char type);
        llvm::Type *get_llvm_block_type();
        llvm::Type *get_llvm_void_type();
        llvm::Type *get_llvm_bool_type();
        llvm::Type *get_llvm_ptr_type();

        void emit_call();
        void emit_block();
        void emit_br_if();
        void emit_end();
        void emit_return();

        void emit_get_local();
        void emit_set_local();

        void emit_i32_load();
        void emit_i32_load_8_s();

        void emit_i32_const();
        void emit_i32_eqz();
        void emit_i32_add();
        void emit_i32_sub();

        llvm::Value *peek_alloca() { return allocas_.back(); }

        llvm::Value *pop_alloca() {
            llvm::Value *alloca = allocas_.back();
            allocas_.pop_back();
            return alloca;
        }
        void push_alloca(llvm::Value *alloca) { allocas_.push_back(alloca); }

        void push_block(llvm::BasicBlock *block) { block_stack_.push_back(block); }
        llvm::BasicBlock *pop_block() {
            llvm::BasicBlock *block = block_stack_.back();
            block_stack_.pop_back();
            return block;
        }

        llvm::BasicBlock *get_block_at_depth(int relative_depth) {
            return block_stack_.at(block_stack_.size()-relative_depth-1); }

        LocalEntry local(int idx) { return local_variables_.at(idx); }
        unsigned int local_count() { return local_count_; }
        std::shared_ptr<llvm::Module> parse_body();
    private:
        Payload payload_;
        unsigned int index_;
        unsigned int body_size_;
        unsigned int local_count_;
        ::WasmFunctionType function_type_;

        // Variables used during the LLVM IR generation
        llvm::BasicBlock *current_basic_block_;
        // The index of the current block
        int block_idx_;
        // Holds the end of each block, for jumping out to by index
        std::vector<llvm::BasicBlock *> block_stack_;
        std::map<int, int> block_types_;
        // Holds the size of the stack when each block was entered, for easy unwinding
        std::map<int, int> stack_frames_;
        std::shared_ptr<llvm::LLVMContext> llvm_context_;
        std::shared_ptr<llvm::IRBuilder<>> llvm_ir_builder_;
        std::shared_ptr<llvm::Module> llvm_module_;
        llvm::Function *llvm_function_;
        std::vector<llvm::Value *> allocas_;
        std::vector<Wasm::LocalEntry> local_variables_;
    };
}
