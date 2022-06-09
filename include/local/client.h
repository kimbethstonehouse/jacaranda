#include <jitaas.grpc.pb.h>
#include <grpcpp/channel.h>
#include <payload.h>
#include <section.h>

#pragma once

class JacarandaClient {
public:
    JacarandaClient(std::shared_ptr<grpc::Channel> channel) : stub_(Jacaranda::NewStub(channel)) {}
    NativeBinary compile(std::unique_ptr<Wasm::FunctionType> &function_type, Payload &function_body, const std::basic_string<char>& target_data_layout);
private:
    std::unique_ptr<Jacaranda::Stub> stub_;
};