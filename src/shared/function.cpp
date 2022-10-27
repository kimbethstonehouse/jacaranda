#include <function.h>
#include <llvm/IR/IRBuilder.h>
#include <ast.h>
#include <llvm/IR/Verifier.h>

#include <llvm/IR/Function.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/Passes/PassBuilder.h>

void Wasm::FunctionBody::emit_call() {
    int idx = payload_.read_uleb128(VARUINT32);
    // todo: get function type of call
    // todo: do properly
    llvm::Value *lhs = llvm_ir_builder_->CreateLoad(pop_alloca());
    llvm::Value *rhs = llvm_ir_builder_->CreateLoad(peek_alloca());
    llvm::Value *result = llvm_ir_builder_->CreateAdd(lhs, rhs);
    llvm_ir_builder_->CreateStore(result, peek_alloca());
}

// todo: the third type index case is ignored for now
void Wasm::FunctionBody::emit_block() {
    // It is EITHER the single byte -0x40 to represent empty, or a valtype encoded as a single byte,
    // or a type index encoded as a +ve signed 32/33 (?) bit integer
    block_types_.insert({block_idx_, payload_.read_uleb128(VARUINT7)});
    push_block(llvm::BasicBlock::Create(*llvm_context_, "block" + std::to_string(block_idx_) + "end"));
    stack_frames_.insert({block_idx_, allocas_.size()});

    block_idx_++;
    current_basic_block_ = llvm::BasicBlock::Create(*llvm_context_, "block" + std::to_string(block_idx_) + "start", llvm_function_);
    llvm_ir_builder_->CreateBr(current_basic_block_);
    llvm_ir_builder_->SetInsertPoint(current_basic_block_);

    // A label for the current block defining the current stack frame
//    push_alloca(llvm_ir_builder_->CreateAlloca(get_llvm_block_type()));
//    llvm_ir_builder_->CreateStore(current_basic_block_, allocas_.back());
}

void Wasm::FunctionBody::emit_br_if() {
    int relative_depth = payload_.read_uleb128(VARUINT32);
    // The else block, to become the insert point once the branch instruction is created
    current_basic_block_ = llvm::BasicBlock::Create(*llvm_context_, llvm_ir_builder_->GetInsertBlock()->getName() + "else", llvm_function_);
    // I don't think that the stack needs unwinding if the branch is taken, because there is no explicit stack, only
    // one that we model using a stack of allocas, which is unwound naturally as we parse the WebAssembly bytecode
    llvm_ir_builder_->CreateCondBr(llvm_ir_builder_->CreateLoad(pop_alloca()), get_block_at_depth(relative_depth), current_basic_block_);
    llvm_ir_builder_->SetInsertPoint(current_basic_block_);
}

void Wasm::FunctionBody::emit_end() {
    current_basic_block_ = pop_block();
    current_basic_block_->insertInto(llvm_function_);

    if (!llvm_ir_builder_->GetInsertBlock()->back().isTerminator()) llvm_ir_builder_->CreateBr(current_basic_block_);
    llvm_ir_builder_->SetInsertPoint(current_basic_block_);
    block_idx_--; // Block_idx_ is the next free block idx, so the current index is -1

    llvm::Value *return_value = nullptr;
    int block_type = block_types_.at(block_idx_);
    llvm::Type *llvm_type = get_llvm_type(block_type);

    // If the block has a return value, pop it
    if (llvm_type != get_llvm_void_type()) {
        return_value = llvm_ir_builder_->CreateLoad(pop_alloca());

        // Assert that the return value has the expected type according to the block signature
        if (return_value->getType() != llvm_type) {
            throw new compile_exception("expected " + std::to_string(block_type) +
                                        " return type for block " + std::to_string(block_idx_));
        }
    }

    // Unwind the stack to where it was when we entered the block
    while (allocas_.size() != stack_frames_.at(block_idx_)) pop_alloca();

    // Push the return value back onto the stack
    if (return_value) {
        allocas_.push_back(llvm_ir_builder_->CreateAlloca(return_value->getType()));
        llvm_ir_builder_->CreateStore(return_value, allocas_.back());
    }
}

void Wasm::FunctionBody::emit_return() {
    if (function_type_.has_return_type()) {
        llvm_ir_builder_->CreateRet(llvm_ir_builder_->CreateLoad(pop_alloca()));
    } else {
        llvm_ir_builder_->CreateRetVoid();
    }
}

void Wasm::FunctionBody::emit_get_local() {
    int idx = payload_.read_uleb128(VARUINT32);
    llvm::Value *value = llvm_ir_builder_->CreateLoad(allocas_.at(idx+IMPLICIT_PARAM_COUNT));
    push_alloca(llvm_ir_builder_->CreateAlloca(value->getType()));
    llvm_ir_builder_->CreateStore(value, allocas_.back());
}

void Wasm::FunctionBody::emit_set_local() {
    llvm::Value *value = llvm_ir_builder_->CreateLoad(pop_alloca());
    llvm_ir_builder_->CreateStore(value, allocas_.at(payload_.read_uleb128(VARUINT32)+IMPLICIT_PARAM_COUNT));
}

// Note: uninterpreted integers are encoded as signed integers
void Wasm::FunctionBody::emit_i32_const() {
    push_alloca(llvm_ir_builder_->CreateAlloca(get_llvm_type(LanguageTypes::I32)));
    llvm_ir_builder_->CreateStore(
            get_llvm_int_value(LanguageTypes::I32, payload_.read_leb128(VARINT32)), allocas_.back());
}

void Wasm::FunctionBody::emit_i32_eqz() {
    llvm::Value *value = llvm_ir_builder_->CreateLoad(pop_alloca());
    llvm::Value *result = llvm_ir_builder_->CreateICmpEQ(value,get_llvm_int_value(LanguageTypes::I32, 0));
    push_alloca(llvm_ir_builder_->CreateAlloca(get_llvm_bool_type()));
    llvm_ir_builder_->CreateStore(result, allocas_.back());
}

void Wasm::FunctionBody::emit_i32_add() {
    llvm::Value *right = llvm_ir_builder_->CreateLoad(pop_alloca());
    llvm::Value *left = llvm_ir_builder_->CreateLoad(allocas_.back()); // No pop as we reuse the alloca for the result
    llvm::Value *result = llvm_ir_builder_->CreateAdd(left, right);
    llvm_ir_builder_->CreateStore(result, allocas_.back());
}

void Wasm::FunctionBody::emit_i32_sub() {
    llvm::Value *right = llvm_ir_builder_->CreateLoad(pop_alloca());
    llvm::Value *left = llvm_ir_builder_->CreateLoad(allocas_.back()); // No pop as we reuse the alloca for the result
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

//llvm::Type *Wasm::FunctionBody::get_llvm_block_type() {
//    // todo: label type is unsized, loading unsized types is not allowed
//    return llvm::Type::getPtr(*llvm_context_);
//}

llvm::Type *Wasm::FunctionBody::get_llvm_void_type() {
    return llvm::Type::getVoidTy(*llvm_context_);
}

llvm::Type *Wasm::FunctionBody::get_llvm_bool_type() {
    return llvm::Type::getInt1Ty(*llvm_context_);
}

llvm::Type *Wasm::FunctionBody::get_llvm_ptr_type() {
    return llvm::Type::getInt32PtrTy(*llvm_context_);
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
        case LanguageTypes::NO_RET:
            return llvm::Type::getVoidTy(*llvm_context_);
        default:
            throw new compile_exception("unsupported language type " + std::to_string(type));
    }
}

std::shared_ptr<llvm::Module> Wasm::FunctionBody::parse_body() {
    llvm_context_ = std::make_shared<llvm::LLVMContext>();
    llvm_ir_builder_ = std::make_shared<llvm::IRBuilder<>>(*llvm_context_);
    llvm_module_ = std::make_shared<llvm::Module>("", *llvm_context_);
    local_count_ = payload_.read_uleb128(VARUINT32);

    std::vector<llvm::Type *> llvm_param_types;
    for (auto param : function_type_.param_types()) {
        llvm::Type *type = get_llvm_type(param);
        llvm_param_types.push_back(type);
    }

    llvm::FunctionType *llvm_function_type = llvm::FunctionType::get(
            get_llvm_type(function_type_.return_type()), llvm_param_types, false);

    // At this point we have a function prototype (declaration) with no body
    llvm_function_ = llvm::Function::Create(
            llvm_function_type, llvm::Function::ExternalLinkage, std::to_string(index_), llvm_module_.get());


    block_idx_ = 0;
    current_basic_block_ = llvm::BasicBlock::Create(*llvm_context_, "block" + std::to_string(block_idx_) + "start", llvm_function_);
    llvm_ir_builder_->SetInsertPoint(current_basic_block_);

    // Implicit parameters: function index, ptr to jump table base, ptr to runtime object
    allocas_.push_back(llvm_ir_builder_->CreateAlloca(get_llvm_type(LanguageTypes::I32)));
    allocas_.push_back(llvm_ir_builder_->CreateAlloca(get_llvm_ptr_type()));
    allocas_.push_back(llvm_ir_builder_->CreateAlloca(get_llvm_ptr_type()));

    for (auto type : llvm_param_types) {
        // Allocate space on the stack for parameters
        // Parameters are mutable!
        // todo: copy values
        allocas_.push_back(llvm_ir_builder_->CreateAlloca(type));
    }

    for (int i = 0; i < local_count_; i++) {
        int count = payload_.read_uleb128(VARUINT32);
        llvm::Type *type = get_llvm_type(payload_.read_uleb128(VARUINT7));

        for (int j = 0; j < count; j++) {
            // Allocate space on the stack for local variables
            allocas_.push_back(llvm_ir_builder_->CreateAlloca(type));
            // Zero initialise, as expected by WebAssembly specification
            llvm_ir_builder_->CreateStore(0, allocas_.back());
        }
    }

    // Thankfully, functions cannot be nested, so we can just expect a sequence of instructions here
    while (1) {
        // TODO: maybe account for the prefix bytes ?
        char opcode = payload_.read_u8();

        // For the final end opcode, insert a return and finish (wasm functions don't finish with a return instruction, but LLVM requires one)
        if (payload_.at() == payload_.data_end() && opcode == END_OPCODE) {
            emit_return();
            break;
        }

        switch(opcode) {
            case CALL_OPCODE:
                emit_call();
                break;
            case BLOCK_OPCODE:
                emit_block();
                break;
            case END_OPCODE:
                emit_end();
                break;
            case BR_IF_OPCODE:
                emit_br_if();
                break;
            case RETURN_OPCODE:
                emit_return();
                break;
            case GET_LOCAL_OPCODE:
                emit_get_local();
                break;
            case SET_LOCAL_OPCODE:
                emit_set_local();
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

    // Create the analysis managers.
    llvm::LoopAnalysisManager LAM;
    llvm::FunctionAnalysisManager FAM;
    llvm::CGSCCAnalysisManager CGAM;
    llvm::ModuleAnalysisManager MAM;

    // Create the new pass manager builder.
    // Take a look at the PassBuilder constructor parameters for more
    // customization, e.g. specifying a TargetMachine or various debugging
    // options.
    llvm::PassBuilder PB;

    // Register all the basic analyses with the managers.
    PB.registerModuleAnalyses(MAM);
    PB.registerCGSCCAnalyses(CGAM);
    PB.registerFunctionAnalyses(FAM);
    PB.registerLoopAnalyses(LAM);
    PB.crossRegisterProxies(LAM, FAM, CGAM, MAM);

    // Create the pass manager.
    // This one corresponds to a typical -O2 optimization pipeline.
    llvm::ModulePassManager MPM = PB.buildPerModuleDefaultPipeline(llvm::PassBuilder::OptimizationLevel::O2);

    // Optimize the IR!
//    MPM.run(*llvm_module_, MAM);

    llvm_module_->print(llvm::outs(), nullptr);

//    llvm_module_->print(llvm::errs(), nullptr);
    bool errors = llvm::verifyFunction(*llvm_function_, &llvm::errs());
    if (errors) std::cout << "errors found during parse" << std::endl;
    return llvm_module_;
}