#include <jacaranda.grpc.pb.h>
#include <compiler.h>
#include <section.h>

extern "C" const char __stub_main;
extern "C" const char __stub_atoi;

extern "C" unsigned long __stub_main_size;
extern "C" unsigned long __stub_atoi_size;

void Compiler::compile(const CompilationRequest *request, NativeBinary *native) {
    // todo: check cache
//    WasmFunction function = envoy_->request_code(request->module_name(), request->func_idx());
//    Wasm::FunctionBody body(Payload(function.func_body().data(), function.func_body().size()));

    if (request->func_idx() == 1) {
        native->set_data_bytes(&__stub_main, __stub_main_size);
        native->set_data_length(__stub_main_size);
    } else {
        native->set_data_bytes(&__stub_atoi, __stub_atoi_size);
        native->set_data_length(__stub_atoi_size);
    }
}

//    auto entry = module_architecture_pairs_.find(wasm->hash());
//
//    if (entry == module_architecture_pairs_.end()) {
//        llvm_module = new llvm::Module("", llvm_context);
//        module_architecture_pairs_.insert({wasm->hash(), llvm_module});
//    } else {
//        // We have seen this module before and have already created the IR
//        llvm_module = entry->second;
//        return;
//    }
//    decoder_.createLLVMIR(wasm);