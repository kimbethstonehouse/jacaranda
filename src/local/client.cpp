#include <client.h>

Binary JacarandaClient::compile(Payload payload) {
    Binary wasm;
    Binary native;
    grpc::ClientContext context;

    wasm.set_data_bytes(payload.data_start(), payload.size());
    wasm.set_data_length(payload.size());

    stub_->compile(&context, wasm, &native);
    return native;
}