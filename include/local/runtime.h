#pragma once

#include <string>
#include <map>
#include <static-module.h>
#include <runtime-module.h>
#include <function.h>
#include <memory>

// TODO: fix args
extern "C" void trampoline_to_execute(int, void *, void *);
extern "C" void trampoline_to_compile(int, void *, void *);

class Runtime {
public:
    Runtime();
    ~Runtime();
    void load_module(const std::string &filename);
    void run(const std::string &filename, int argc, char **argv);
    void request_compilation(int function_index);
private:
    void init_jump_table(int function_count);

    std::map<std::string, std::shared_ptr<StaticModule>> static_modules_;
    RuntimeModule *runtime_module_;
    char *code_section_;
    char *next_function_;
    void **jump_table_;
};