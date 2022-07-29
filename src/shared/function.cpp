#include <function.h>
#include <llvm/IR/IRBuilder.h>
#include <ast.h>

void Wasm::FunctionBody::get_local() {
    // todo
}

void Wasm::FunctionBody::set_local() {
    // todo
}

void Wasm::FunctionBody::emit_i32_const() {
    allocas_.push_back(llvm_ir_builder_->CreateAlloca(get_llvm_type(LanguageTypes::I32)));
    llvm_ir_builder_->CreateStore(
            get_llvm_int_value(LanguageTypes::I32, payload_.read_leb128(VARINT32)), allocas_.back());
}

void Wasm::FunctionBody::emit_i32_eqz() {
    llvm::Value *value = llvm_ir_builder_->CreateLoad(allocas_.back());
    llvm::Value *result = llvm_ir_builder_->CreateICmpEQ(value,get_llvm_int_value(LanguageTypes::I32, 0));
    llvm_ir_builder_->CreateStore(result, allocas_.back());
}

void Wasm::FunctionBody::emit_i32_add() {
    llvm::Value *right = llvm_ir_builder_->CreateLoad(allocas_.back());
    allocas_.pop_back();
    llvm::Value *left = llvm_ir_builder_->CreateLoad(allocas_.back());
    llvm::Value *result = llvm_ir_builder_->CreateAdd(left, right);
    llvm_ir_builder_->CreateStore(result, allocas_.back());
}

void Wasm::FunctionBody::emit_i32_sub() {
    llvm::Value *right = llvm_ir_builder_->CreateLoad(allocas_.back());
    allocas_.pop_back();
    llvm::Value *left = llvm_ir_builder_->CreateLoad(allocas_.back());
    llvm::Value *result = llvm_ir_builder_->CreateSub(left, right);
    llvm_ir_builder_->CreateStore(result, allocas_.back());
}

llvm::Value *Wasm::FunctionBody::get_llvm_int_value(unsigned char type, int value) {
    return llvm::ConstantInt::get(*llvm_context_, llvm::APInt(
            type == LanguageTypes::I32 ? 32 : 64, value));
}

llvm::Value *Wasm::FunctionBody::get_llvm_fp_value(unsigned char type, double value) {
    return llvm::ConstantFP::get(*llvm_context_, llvm::APFloat(
            type == LanguageTypes::F32 ? (float) value : value));
}

llvm::Type *Wasm::FunctionBody::get_llvm_type(unsigned char type) {
    switch (type) {
        case LanguageTypes::I32:
            return llvm::Type::getInt32Ty(*llvm_context_);
        case LanguageTypes::I64:
            return llvm::Type::getInt64Ty(*llvm_context_);
        case LanguageTypes::F32:
            return llvm::Type::getFloatTy(*llvm_context_);
        case LanguageTypes::F64:
            return llvm::Type::getDoubleTy(*llvm_context_);
    }
}

std::shared_ptr<llvm::Module> Wasm::FunctionBody::parse_body() {
    llvm_context_ = std::make_shared<llvm::LLVMContext>();
    llvm_ir_builder_ = std::make_shared<llvm::IRBuilder<>>(*llvm_context_);
    llvm_module_ = std::make_shared<llvm::Module>("", *llvm_context_);
    local_count_ = payload_.read_uleb128(VARUINT32);

    std::vector<llvm::Type *> llvm_param_types;
    for (auto param : function_type_.param_types()) {
        llvm_param_types.push_back(get_llvm_type(param.type()));
    }

    llvm::FunctionType *llvm_function_type = llvm::FunctionType::get(
            get_llvm_type(function_type_.return_type()->type()), llvm_param_types, false);

    // At this point we have a function prototype (declaration) with no body
    llvm::Function *llvm_function = llvm::Function::Create(
            llvm_function_type, llvm::Function::ExternalLinkage, std::to_string(index_), llvm_module_.get());

    llvm::BasicBlock *start_basic_block = llvm::BasicBlock::Create(*llvm_context_, "entry", llvm_function);
    llvm_ir_builder_->SetInsertPoint(start_basic_block);

    for (int i = 0; i < local_count_; i++) {
        local_variables_.push_back(LocalEntry(payload_.read_uleb128(VARUINT32),
                                              ValueType(payload_.read_uleb128(VARUINT7))));
    }

    int block_idx = 0;
//    std::vector<std::shared_ptr<BlockInstruction>> block_stack;

    while(payload_.at() != payload_.data_end()) {
        // TODO: account for the prefix bytes
        char opcode = payload_.read_u8();

        switch(opcode) {
            case CALL_OPCODE:
//                instructions_list->push_back(std::make_shared<CallInstruction>(CallInstruction(
//                        payload_.read_uleb128(VARUINT32))));
                break;
            case BLOCK_OPCODE:
                // uint7 is not a mistake as we look for 0x40 rather than -0x40
//                block_stack.push_back(std::make_shared<BlockInstruction>(block_idx,payload_.read_uleb128(VARUINT7)));
//                instructions_list->push_back(block_stack.back());
//                instructions_list = block_stack.back()->instructions();
//                block_idx++;
                break;
            case END_OPCODE:
//                instructions_list->push_back(std::make_shared<EndInstruction>(EndInstruction()));
//                if (block_stack.size() > 1) {
//                    block_stack.pop_back();
//                    instructions_list = block_stack.back()->instructions();
//                } else if (block_stack.size() == 1) {
//                    block_stack.pop_back();
//                    instructions_list = &instructions_;
//                }
                break;
            case BR_IF_OPCODE:
                // todo
//                int relative_depth = payload_.read_uleb128(VARUINT32);
//                instructions_list->push_back(std::make_shared<BrIfInstruction>(BrIfInstruction(
//                        payload_.read_uleb128(VARUINT32))));
                break;
            case RETURN_OPCODE:
//                llvm::Value *return_value = pop.
//                return llvm_module_;
                // todo:
//                instructions_list->push_back(std::make_shared<ReturnInstruction>(ReturnInstruction()));
                break;
            case GET_LOCAL_OPCODE:
                get_local();
                break;
            case SET_LOCAL_OPCODE:
                set_local();
                break;
            case I32_CONST_OPCODE:
                emit_i32_const();
                break;
            case I32_EQZ_OPCODE:
                emit_i32_eqz();
                break;
            case I32_ADD_OPCODE:
                emit_i32_add();
                break;
            case I32_SUB_OPCODE:
                emit_i32_sub();
                break;
            default:
                throw new decode_exception("unsupported instruction with opcode " + std::to_string(opcode) + " encountered");
        }
    }

    // Sanity check
    if (*(payload_.at()-1) != END_OPCODE) {
        throw decode_exception("error during function body decoding, expected end byte to be 0x0b, but was " + std::to_string(*payload_.at()));
    }
}