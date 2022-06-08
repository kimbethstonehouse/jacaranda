#include <client.h>

Binary JacarandaClient::compile(int function_index, const std::basic_string<char>& target_data_layout) {
    RequestCompilationMessage wasm;
    Binary native;
    grpc::ClientContext context;

    wasm.set_function_index(function_index);
    wasm.set_target_data_layout(target_data_layout);

    stub_->compile(&context, wasm, &native);
    return native;
}