#include <jitaas.grpc.pb.h>
#include <grpcpp/channel.h>
#include <payload.h>
#include <section.h>

#pragma once

class RuntimeEnvoy {
public:
    RuntimeEnvoy(std::shared_ptr<grpc::Channel> channel) : stub_(Jacaranda::NewStub(channel)) {}
    NativeBinary request_compile(std::string module_name, std::string architecture, unsigned int function_idx,
                         const std::basic_string<char>& target_data_layout, unsigned int program_pointer_size);
    FunctionIndices request_function_indices(std::string module_name);
private:
    std::unique_ptr<Jacaranda::Stub> stub_;
};