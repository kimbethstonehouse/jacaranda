#include <compiler.h>
#include <llvm/IR/Constants.h>
#include <jitaas.h>
#include <payload.h>
#include <section.h>

extern "C" const char __stub_main;
extern "C" const char __stub_atoi;

extern "C" unsigned long __stub_main_size;
extern "C" unsigned long __stub_atoi_size;



void Compiler::addGlobalData(const WasmFunction *wasm, llvm::Module *llvm_module) {
    // todo: this is the first time we have been called, so an rpc to ask for global, memory, table info for module
    // todo: make this target info something that you ask for via rpc too
    llvm_module->setDataLayout(wasm->target_data_layout());

}

// Creates a phi node for the argument of branches to a basic block.
Compiler::PhiVector Compiler::createPhis(llvm::BasicBlock* basic_block, llvm::IRBuilder<> &ir_builder, llvm::Type *type) {
    auto original_block = ir_builder.GetInsertBlock();
    ir_builder.SetInsertPoint(basic_block);

    PhiVector result;
    result.push_back(ir_builder.CreatePHI(type, 2)); // why 2?

    // Restore state
    if(original_block) ir_builder.SetInsertPoint(original_block);
    return result;
}

void Compiler::createLLVMIR(const WasmFunction *wasm) {
    llvm::Module *llvm_module;
    llvm::LLVMContext llvm_context;
    auto entry = module_architecture_pairs_.find(wasm->hash());

    if (entry == module_architecture_pairs_.end()) {
        llvm_module = new llvm::Module("", llvm_context);
        module_architecture_pairs_.insert({wasm->hash(), llvm_module});
    } else {
        // We have seen this module before and have already created the IR
        llvm_module = entry->second;
        return;
    }

    llvm::Type *i32 = llvm::Type::getInt32Ty(llvm_context);
    llvm::Type *i64 = llvm::Type::getInt64Ty(llvm_context);

    // Create an external reference to the appropriate exception personality function.
    // todo: think this should be one per module
    llvm::Function *personality_function = llvm::Function::Create(
            llvm::FunctionType::get(i32, {}, false),
            llvm::GlobalValue::LinkageTypes::ExternalLinkage,
            "__gxx_personality_v0",
            llvm_module);

    // todo: is this even necessary?
    llvm::GlobalVariable *llvm_global_variable = new llvm::GlobalVariable(*llvm_module,
                                                                          llvm::Type::getInt8Ty(llvm_context),
                                                                          false,
                                                                          llvm::GlobalVariable::ExternalLinkage,
                                                                          nullptr,
                                                                          getExternalName("typeId", wasm->func_idx()));

    // Create an LLVM external global corresponding to the function type.
    // todo: is this even necessary?
    llvm::Constant *function_type = llvm::ConstantExpr::getPtrToInt(
            llvm_global_variable,
            wasm->program_pointer_size() == 4 ? i32 : i64);

    // todo: think this is needed but not sure
    delete llvm_global_variable;

    // Create the function declaration
    llvm::Function* function = llvm::Function::Create(asLLVMType(llvm_context, wasm->func_type()),
                                                      llvm::Function::ExternalLinkage, getExternalName("function", wasm->func_idx()), llvm_module);
    function->setCallingConv(llvm::CallingConv::C); // todo: change!
    function->setPersonalityFn(personality_function);

    // Add the function definition
    llvm::IRBuilder<> ir_builder(llvm_context);

    // Create an initial basic block for the function
    auto entry_basic_block = llvm::BasicBlock::Create(llvm_context, "entry", function);

    // Create the return basic block, and push the root control context for the function.
    auto return_basic_block = llvm::BasicBlock::Create(llvm_context, "return", function);
    auto return_phis = createPhis(return_basic_block, ir_builder,
                                  asLLVMType(llvm_context, wasm->func_type().return_type()));
    ir_builder.SetInsertPoint(entry_basic_block);

    // Create and initialize allocas for all the parameters.
    auto llvm_arg_iterator = function->arg_begin();
    for(uintptr_t param_idx = 0; param_idx < wasm->func_type().param_count(); ++param_idx) {
        auto param_type = wasm->func_type().param_types().at(param_idx);
        auto param_pointer = ir_builder.CreateAlloca(asLLVMType(llvm_context, param_type), nullptr, "");

        // Copy the parameter value into the local that stores it.
        ir_builder.CreateStore(&*llvm_arg_iterator, param_pointer);
        ++llvm_arg_iterator;
    }

    // Parsing is done lazily, so the WebAssembly function body will need to be parsed now.
    Payload payload(wasm->func_body().data(), wasm->func_body().length());
    Wasm::FunctionBody function_body(payload);

    // Create and initialize allocas for all the local variables.
    for(uintptr_t local_idx = 0; local_idx < function_body.local_count(); ++local_idx) {
        auto local_type = function_body.local(local_idx).type();
        auto local_pointer = ir_builder.CreateAlloca(asLLVMType(llvm_context, local_type), nullptr, "");

        // Initialise the local variable to zero.
        llvm::Value *value;
        if (local_type == LanguageTypes::I32) {
            value = llvm::ConstantInt::get(llvm_context,llvm::APInt(32, 0, false));
        } else if (local_type == LanguageTypes::I64) {
            value = llvm::ConstantInt::get(llvm_context, llvm::APInt(64, 0, false));
        } else if (local_type == LanguageTypes::F32) {
            value = llvm::ConstantFP::get(llvm_context, llvm::APFloat(0.0f));
        } else if (local_type == LanguageTypes::F64) {
            value = llvm::ConstantFP::get(llvm_context, llvm::APFloat(0.0));
        } else {
            throw compile_exception("type of local variable is invalid: " + std::to_string(local_type));
        }

        ir_builder.CreateStore(value, local_pointer);
        ++llvm_arg_iterator;
    }

    // todo: parse the bytecode and create an llvm module from that information
    // todo: if encounter a call, ask for function type info and add that to the globals list
}

void Compiler::compile(const WasmFunction *wasm, NativeBinary *native) {
    createLLVMIR(wasm);
//    if (wasm->function_index() == 1) {
        native->set_data_bytes(&__stub_main, __stub_main_size);
        native->set_data_length(__stub_main_size);
//    } else {
//        native->set_data_bytes(&__stub_atoi, __stub_atoi_size);
//        native->set_data_length(__stub_atoi_size);
//    }
}