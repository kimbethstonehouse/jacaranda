#include <grpcpp/channel.h>
#include <jacaranda.grpc.pb.h>
#include <payload.h>
#include <section.h>

#pragma once

class RuntimeEnvoy {
public:
    RuntimeEnvoy(std::shared_ptr<grpc::Channel> compiler_channel, std::shared_ptr<grpc::Channel> repository_channel)
    : compiler_stub_(CompilerService::NewStub(compiler_channel)), repository_stub_(RepositoryService::NewStub(repository_channel)) {}
    NativeBinary request_compile(std::string module_name, std::string architecture, unsigned int function_idx,
                         const std::basic_string<char>& target_data_layout, unsigned int program_pointer_size);
    FunctionIndices request_function_indices(std::string module_name);
private:
    std::unique_ptr<CompilerService::Stub> compiler_stub_;
    std::unique_ptr<RepositoryService::Stub> repository_stub_;
};