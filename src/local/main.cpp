#include <iostream>

#include "runtime.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "usage: " << argv[0] << " file.wasm [args]" << std::endl;
        return -1;
    }

    // Assumes the remote compiler is up and running
    Runtime runtime;
    runtime.load_module(argv[1]);
    runtime.run();
}