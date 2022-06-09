#include <client.h>

// todo: handle request for func type

NativeBinary JacarandaClient::compile(std::unique_ptr<Wasm::FunctionType> &function_type, Payload &function_body, const std::basic_string<char>& target_data_layout) {
    WasmFunction wasm;
    NativeBinary native;
    grpc::ClientContext context;

    FunctionType rpc_function_type;
    rpc_function_type.set_param_count(function_type.get()->param_count());

    // Protocol buffers guarantee to retain parameter order
    for (Wasm::ValueType value_type : function_type.get()->param_types()) {
        rpc_function_type.add_param_types(value_type.type());
    }

    rpc_function_type.set_return_count(function_type.get()->return_count());
    // Optional type is only present if the function has a return value
    if (function_type.get()->return_count() > 0) {
        rpc_function_type.set_return_type(function_type.get()->return_type().value().type());
    }

    wasm.set_allocated_func_type(&rpc_function_type);
    wasm.set_target_data_layout(target_data_layout);

    stub_->compile(&context, wasm, &native);
    return native;
}