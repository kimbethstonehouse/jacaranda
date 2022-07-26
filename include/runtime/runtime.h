#pragma once

#include <llvm/Target/TargetMachine.h>
#include <string>
#include <map>
#include <sys/mman.h>
#include <memory.h>
#include <jacaranda.grpc.pb.h>
#include <jacaranda.h>
#include <runtime-envoy.h>

// TODO: fix args and ret types
extern "C" int trampoline_to_execute(int function_index, void **jump_table_, int argc, char **argv, void *runtime_);
extern "C" void trampoline_to_compile(int, void *, void *);

class Runtime {
public:
    Runtime(std::shared_ptr<RuntimeEnvoy> envoy);
    ~Runtime();
    void load_module(const std::string &filename);
    void run(const std::string &filename, int argc, char **argv);
    void *request_compilation(int function_index);
    void create_target_machine();
private:
    void init_execution_state();
    void request_function_indices();
    void set_module_name(const std::string &filename) { module_name_ = filename; }
    NativeBinary compilation_rpc(NativeBinary bin);

    std::shared_ptr<RuntimeEnvoy> envoy_;
    std::unique_ptr<llvm::TargetMachine> target_machine_;

    std::optional<int> start_idx_; // An index for the optional start section
    int main_idx_;
    int function_count_; // todo: populate
    char *code_section_;
    char *next_function_;
    void **jump_table_;
    std::string module_name_;
};