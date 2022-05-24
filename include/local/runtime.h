#pragma once

#include <string>
#include <map>
#include <static-module.h>
#include <runtime-module.h>
#include <function.h>
#include <memory>
#include <rpc/client.h>

// TODO: fix args and ret types
extern "C" int trampoline_to_execute(int, void *, int, void **);
extern "C" void trampoline_to_compile(int, void *, void *);

class Runtime {
public:
    Runtime();
    ~Runtime();
    void load_module(const std::string &filename);
    void run(const std::string &filename, int argc, char **argv);
    void *request_compilation(int function_index);
private:
    void init_jump_table(int function_count);

    std::map<std::string, std::shared_ptr<StaticModule>> static_modules_;
    RuntimeModule *runtime_module_;
    rpc::client client_;
    char *code_section_;
    char *next_function_;
    void **jump_table_;
};