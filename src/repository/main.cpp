#include <grpcpp/server_builder.h>
#include <repository-envoy.h>
#include <jacaranda.h>

int main() {
    RepositoryEnvoy repository_envoy;

    // Define ourselves as a server so that the compiler can request code from us
    grpc::ServerBuilder builder;
    // No authentication credentials
    builder.AddListeningPort(repository_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&repository_envoy);
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());

    // This call will not return unless some other thread shuts the server down
    server->Wait();
}