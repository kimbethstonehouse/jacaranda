#include <compiler-envoy-client.h>

WasmFunction CompilerEnvoyClient::request_code(std::string module_name, unsigned int function_idx) {
    CodeRequest request;
    WasmFunction function;
    grpc::ClientContext context;

    request.set_module_name(module_name);
    request.set_func_idx(function_idx);

    stub_->request_code(&context, request, &function);
    return function;
}