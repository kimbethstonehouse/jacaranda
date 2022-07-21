#include <jitaas.grpc.pb.h>
#include <grpcpp/channel.h>
#include "repository.h"

#pragma once

class RepositoryEnvoy final : public Jacaranda::Service {
public:
    grpc::Status request_code(grpc::ServerContext *context, const CodeRequest *request, WasmFunction *function) override {
        repository_.code(request, function);
        return grpc::Status::OK;
    }

    grpc::Status request_function_indices(grpc::ServerContext *context, const IndicesRequest *request, FunctionIndices *indices) override {
        repository_.function_indices(request, indices);
        return grpc::Status::OK;
    }

private:
    Repository repository_;
};