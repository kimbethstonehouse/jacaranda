#include <jacaranda.grpc.pb.h>
#include <compiler.h>
#include <section.h>
#include <ast.h>
#include <function.h>

extern "C" const char __stub_main;
extern "C" const char __stub_atoi;

extern "C" unsigned long __stub_main_size;
extern "C" unsigned long __stub_atoi_size;

void Compiler::compile(const CompilationRequest *request, NativeBinary *native) {
    // todo: check cache
    WasmFunction function = envoy_->request_code(request->module_name(), request->func_idx());
    Wasm::FunctionBody body(request->func_idx(), Payload(function.func_body().data(), function.func_body().size()), function.func_type());
    std::shared_ptr<llvm::Module> module = body.parse_body();
//    module->dump();

    BaseCompiler cc;
    Visitor V(cc);
    V.accept(*module.get());

    if (request->func_idx() == 1) {
        native->set_data_bytes(&__stub_main, __stub_main_size);
        native->set_data_length(__stub_main_size);
    } else {
        native->set_data_bytes(&__stub_atoi, __stub_atoi_size);
        native->set_data_length(__stub_atoi_size);
    }
}