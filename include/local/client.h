#include <jitaas.grpc.pb.h>
#include <grpcpp/channel.h>
#include <payload.h>

#pragma once

class JacarandaClient {
public:
    JacarandaClient(std::shared_ptr<grpc::Channel> channel) : stub_(Jacaranda::NewStub(channel)) {}
    Binary compile(int function_index);
private:
    std::unique_ptr<Jacaranda::Stub> stub_;
};