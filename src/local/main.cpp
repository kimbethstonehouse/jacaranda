#include <iostream>
#include <runtime.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "usage: " << argv[0] << " file.shared [args]" << std::endl;
        return -1;
    }

    // TODO: ideally we wouldn't create a new runtime everytime,
    // but have the runtime persist between executions...
    // Assumes the remote compiler is up and running
    Runtime runtime;

    runtime.load_module(argv[1]);
    runtime.run(argv[1]);
}