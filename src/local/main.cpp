#include <iostream>
#include <runtime.h>
#include <grpcpp/create_channel.h>
#include <client.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "usage: " << argv[0] << " file.shared [args]" << std::endl;
        return -1;
    }

    // Assumes the jacaranda server is up and running
    JacarandaClient jacaranda_client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
    // TODO: ideally we wouldn't create a new runtime everytime, but have the runtime persist between executions...
    Runtime runtime(&jacaranda_client);
    runtime.load_module(argv[1]);
    runtime.run(argv[1], argc-2, argv+2);
}