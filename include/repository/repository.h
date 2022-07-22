#pragma once

#include <jacaranda.grpc.pb.h>
#include <wasm-module.h>

class Repository {
public:
    Repository() {}

    void code(const CodeRequest *request, WasmFunction *function);
    void function_indices(const IndicesRequest *request, FunctionIndices *indices);

private:
    void load_module(const std::string &filename);
    std::map<std::string, std::shared_ptr<WasmModule>> static_modules_;
};

