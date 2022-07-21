#include <jitaas.grpc.pb.h>
#include <grpcpp/channel.h>
#include <payload.h>
#include <section.h>
#include "compiler.h"

#pragma once

class CompilerEnvoy final : public Jacaranda::Service {
public:
    CompilerEnvoy(std::shared_ptr<grpc::Channel> channel) : stub_(Jacaranda::NewStub(channel)) {}

    grpc::Status request_compile(grpc::ServerContext *context, const CompilationRequest *request, NativeBinary *native) override {
        compiler_.compile(request, native);
        return grpc::Status::OK;
    }

    WasmFunction request_code(std::string module_name, unsigned int function_idx);

private:
    Compiler compiler_;
    std::unique_ptr<Jacaranda::Stub> stub_;
};