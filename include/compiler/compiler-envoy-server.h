#pragma once

#include <jacaranda.grpc.pb.h>
#include <compiler.h>

class CompilerEnvoyServer final : public CompilerService::Service {
public:
    CompilerEnvoyServer(std::shared_ptr<Compiler> compiler) : compiler_(compiler) {}

    grpc::Status request_compile(grpc::ServerContext *context, const CompilationRequest *request, NativeBinary *native) override {
        compiler_->compile(request, native);
        return grpc::Status::OK;
    }

private:
    std::shared_ptr<Compiler> compiler_;
};