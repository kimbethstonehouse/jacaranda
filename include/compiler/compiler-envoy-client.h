#pragma once

#include <grpcpp/channel.h>
#include <jacaranda.grpc.pb.h>
#include <jacaranda.pb.h>

class CompilerEnvoyClient {
public:
    CompilerEnvoyClient(std::shared_ptr<grpc::Channel> channel) : stub_(Jacaranda::NewStub(channel)) {}

    WasmFunction request_code(std::string module_name, unsigned int function_idx);

private:
    std::unique_ptr<Jacaranda::Stub> stub_;
};