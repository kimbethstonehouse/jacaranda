#include <grpcpp/server_builder.h>
#include "server.cpp"
#include "compiler.h"
#include <string>

int main() {
    std::string server_address("0.0.0.0:50051");
    JacarandaServer jacaranda_server;

    grpc::ServerBuilder builder;
    // No authentication credentials
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&jacaranda_server);
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());

    // This call will not return unless some other thread shuts the server down
    server->Wait();
}