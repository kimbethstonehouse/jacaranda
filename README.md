# Jacaranda

The infrastructure is currently split into four main sections.

## JacarandaRepository

A stub for the central code repository. At the moment, the compiler requests code from this repository using an ordinary function call, and the respository just reads the code from a local file. However, in the future, this will ideally be decoupled from the compiler, and the two will communicate via RPC.

## Runtime

*See src/local/runtime.cpp*

Responsible for allocating memory, initialising jump tables and handling the execution of the native code provided by the compiler.

## JacarandaClient

*See src/local/client.cpp*

Handles the communication between the local runtime and the remote compiler. For example, JacarandaClient::compile creates a protocol buffer with the relevant function information and sends that information to the remote compiler via an RPC.


