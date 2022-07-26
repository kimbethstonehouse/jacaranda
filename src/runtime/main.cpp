#include <grpcpp/create_channel.h>
#include <iostream>
#include <runtime.h>
#include <runtime-envoy.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "usage: " << argv[0] << " file.shared [args]" << std::endl;
        return -1;
    }

    // Define ourselves as a client so that we can request code from the compiler (assumes the compiler is up and running)
    std::shared_ptr<RuntimeEnvoy> envoy = std::make_shared<RuntimeEnvoy>(RuntimeEnvoy(
            grpc::CreateChannel(compiler_address, grpc::InsecureChannelCredentials()),
                                           grpc::CreateChannel(repository_address, grpc::InsecureChannelCredentials())));
    // todo: ideally we wouldn't create a new runtime everytime, but have the runtime persist between executions...
    Runtime runtime(envoy);
    runtime.run(argv[1], argc-2, argv+2);
}