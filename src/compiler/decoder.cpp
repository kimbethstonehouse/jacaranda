#include <decoder.h>
#include <payload.h>
#include <section.h>

#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/Support/DynamicLibrary.h>

// Creates a phi node for the argument of branches to a basic block.
Decoder::PhiVector Decoder::createPhis(llvm::BasicBlock* basic_block, llvm::IRBuilder<> &ir_builder, llvm::Type *type) {
    auto original_block = ir_builder.GetInsertBlock();
    ir_builder.SetInsertPoint(basic_block);

    PhiVector result;
    result.push_back(ir_builder.CreatePHI(type, 2)); // why 2?

    // Restore state
    if(original_block) ir_builder.SetInsertPoint(original_block);
    return result;
}

void Decoder::createLLVMIR(const CompilationRequest *request, WasmFunction function) {
    // Emit LLVM IR for the module.
    llvm::LLVMContext llvm_context;
    llvm::Module llvm_module("", llvm_context);

    llvm_module.setDataLayout(request->target_data_layout());

    llvm::Type *i32 = llvm::Type::getInt32Ty(llvm_context);
    llvm::Type *i64 = llvm::Type::getInt64Ty(llvm_context);

    // Create an external reference to the appropriate exception personality function.
    // todo: think this should be one per module
    llvm::Function *personality_function = llvm::Function::Create(
            llvm::FunctionType::get(i32, {}, false),
            llvm::GlobalValue::LinkageTypes::ExternalLinkage,
            "__gxx_personality_v0",
            llvm_module);



    // Create LLVM external globals corresponding to the encoded function types for the module's
    // indexed function types.
    // todo: is this even necessary? also memory leak
    llvm::GlobalVariable *llvm_global_variable = new llvm::GlobalVariable(llvm_module,
                                                                          llvm::Type::getInt8Ty(llvm_context),
                                                                          false,
                                                                          llvm::GlobalVariable::ExternalLinkage,
                                                                          nullptr,
                                                                          getExternalName("typeId", request->func_idx()));

    // Create the function declaration
    llvm::Function* llvm_function = llvm::Function::Create(asLLVMType(llvm_context, function.func_type()),
                                                      llvm::Function::ExternalLinkage, getExternalName("function", request->func_idx()), llvm_module);
    llvm_function->setCallingConv(llvm::CallingConv::C); // todo: change!
    llvm_function->setPersonalityFn(personality_function);

    // Add the function definition
    llvm::IRBuilder<> ir_builder(llvm_context);

    // Create an initial basic block for the function
    auto entry_basic_block = llvm::BasicBlock::Create(llvm_context, "entry", llvm_function);

    // Create the return basic block, and push the root control context for the function.
    auto return_basic_block = llvm::BasicBlock::Create(llvm_context, "return", llvm_function);
    auto return_phis = createPhis(return_basic_block, ir_builder,
                                  asLLVMType(llvm_context, function.func_type().return_type()));
    ir_builder.SetInsertPoint(entry_basic_block);

    // Create and initialize allocas for all the parameters.
    auto llvm_arg_iterator = llvm_function->arg_begin();
    for(uintptr_t param_idx = 0; param_idx < function.func_type().param_count(); ++param_idx) {
        auto param_type = function.func_type().param_types(param_idx);
        auto param_pointer = ir_builder.CreateAlloca(asLLVMType(llvm_context, param_type), nullptr, "");

        // Copy the parameter value into the local that stores it.
        ir_builder.CreateStore(&*llvm_arg_iterator, param_pointer);
        ++llvm_arg_iterator;
    }

    // Parsing is done lazily, so the WebAssembly function body will need to be parsed now.
    Payload payload(function.func_body().data(), function.func_body().length());
//    Wasm::FunctionBody function_body(payload);
    // todo: for each instruction in vector, convert to llvm ir

    // Create and initialize allocas for all the local variables.
//    for(uintptr_t local_idx = 0; local_idx < function_body.local_count(); ++local_idx) {
//        auto local_type = function_body.local(local_idx).type();
//        auto local_pointer = ir_builder.CreateAlloca(asLLVMType(llvm_context, local_type), nullptr, "");
//
//        // Initialise the local variable to zero.
//        llvm::Value *value;
//        if (local_type == LanguageTypes::I32) {
//            value = llvm::ConstantInt::get(llvm_context,llvm::APInt(32, 0, false));
//        } else if (local_type == LanguageTypes::I64) {
//            value = llvm::ConstantInt::get(llvm_context, llvm::APInt(64, 0, false));
//        } else if (local_type == LanguageTypes::F32) {
//            value = llvm::ConstantFP::get(llvm_context, llvm::APFloat(0.0f));
//        } else if (local_type == LanguageTypes::F64) {
//            value = llvm::ConstantFP::get(llvm_context, llvm::APFloat(0.0));
//        } else {
//            throw compile_exception("type of local variable is invalid: " + std::to_string(local_type));
//        }
//
//        ir_builder.CreateStore(value, local_pointer);
//        ++llvm_arg_iterator;
//    }

    // todo: parse the bytecode and create an llvm module from that information
    // todo: if encounter a call, ask for function type info and add that to the globals list
}