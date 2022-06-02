#include <jitaas.grpc.pb.h>
#include <compiler.h>

class JacarandaServer final : public Jacaranda::Service {
public:
    grpc::Status compile(grpc::ServerContext *context, const RequestCompilationMessage *wasm, Binary *native) override {
        compiler_.compile(wasm, native);
        return grpc::Status::OK;
    }
private:
    Compiler compiler_;
};