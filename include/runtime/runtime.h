#pragma once

#include <string>
#include <map>
#include <wasm-module.h>
#include <function.h>
#include <memory.h>
#include <jitaas.h>
#include <jitaas.grpc.pb.h>
#include <runtime-envoy.h>
#include <sys/mman.h>
#include <llvm/Target/TargetMachine.h>

// TODO: fix args and ret types
extern "C" int trampoline_to_execute(int function_index, void **jump_table_, int argc, char **argv, void *runtime_);
extern "C" void trampoline_to_compile(int, void *, void *);

class Runtime {
public:
    Runtime(RuntimeEnvoy *client);
    ~Runtime();
    void load_module(const std::string &filename);
    void run(const std::string &filename, int argc, char **argv);
    void *request_compilation(int function_index);
    void create_target_machine();
private:
    void init_execution_state();
    void request_function_indices(const std::string &filename);
    NativeBinary compilation_rpc(NativeBinary bin);

    RuntimeEnvoy *envoy_;
    std::unique_ptr<llvm::TargetMachine> target_machine_;

    std::optional<int> start_idx_; // An index for the optional start section
    int main_idx_;
    int function_count_; // todo: populate
    char *code_section_;
    char *next_function_;
    void **jump_table_;
};