#include <client.h>

Binary JacarandaClient::compile(int function_index) {
    RequestCompilationMessage wasm;
    Binary native;
    grpc::ClientContext context;

    wasm.set_function_index(function_index);

    stub_->compile(&context, wasm, &native);
    return native;
}