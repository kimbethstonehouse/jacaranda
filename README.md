# Jacaranda

The infrastructure is currently split into three main sections.

## JacarandaRepository

*See src/repository/repository.cpp*

A stub for the central code repository. At the moment, the compiler requests code for a particular WebAssembly module and function, and the respository reads the code from a local file, parses it, and sends it via gRPC. In the future, this will likely be more sophisticated.

## JacarandaRuntime

*See src/runtime/runtime.cpp*

Responsible for allocating memory, initialising jump tables and handling the execution of the native code provided by the compiler, function-by-function.

## JacarandaCompiler

*See src/compiler/compiler.cpp*

Handles the actual compilation of the WebAssembly binary code. Currently responds with precompiled code until LLVM is integrated.

## JacarandaEnvoys

*See src/*/*-envoy.cpp*

Handle the communication between services. Responsible for serialising and deserialising information into protocol buffers and making remote procedure calls via stubs. Communication is done via gRPC as it allows bidirectional communication, rather than unidirectional procedure calls from client to server only.

## Building

git clone
cd jitaas
mkdir build && cd build
cmake ..
make

## Executing

Open three separate terminals. Follow this order, since each component depends on the previous service being up and running.

./exe/repository
./exe/compiler

You can then execute wasm programs using the runtime executable.

./exe/runtime [file.wasm] [program arguments]
