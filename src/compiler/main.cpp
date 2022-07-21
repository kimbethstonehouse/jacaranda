#include <grpcpp/server_builder.h>
#include <compiler-envoy.h>
#include <jitaas.h>
#include <grpcpp/create_channel.h>

int main() {
    // Define ourselves as a client so that we can request code from the code repository (assumes the repository is up and running)
    CompilerEnvoy compiler_envoy(grpc::CreateChannel(repository_address, grpc::InsecureChannelCredentials()));

    // Define ourselves as a server so that the local runtimes can request code from us
    grpc::ServerBuilder builder;
    // No authentication credentials
    builder.AddListeningPort(compiler_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&compiler_envoy);
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());

    // This call will not return unless some other thread shuts the server down
    server->Wait();
}