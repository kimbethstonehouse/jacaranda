#include <grpcpp/create_channel.h>
#include <grpcpp/server_builder.h>
#include <compiler-envoy-client.h>
#include <compiler-envoy-server.h>
#include <jacaranda.h>

int main() {
    // Define ourselves as a client so that we can request code from the code repository (assumes the repository is up and running)
    std::shared_ptr<CompilerEnvoyClient> compiler_envoy_client = std::make_shared<CompilerEnvoyClient>
            (CompilerEnvoyClient(grpc::CreateChannel(repository_address, grpc::InsecureChannelCredentials())));
    std::shared_ptr<Compiler> compiler = std::make_shared<Compiler>(compiler_envoy_client);
    // Define ourselves as a server so that the local runtimes can request code from us
    CompilerEnvoyServer compiler_envoy_server(compiler);

    grpc::ServerBuilder builder;
    // No authentication credentials
    builder.AddListeningPort(compiler_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&compiler_envoy_server);
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());

    // This call will not return unless some other thread shuts the server down
    server->Wait();
}