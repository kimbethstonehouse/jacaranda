#pragma once

#include <function.h>
#include <static-module.h>
#include <math.h>
#include <sys/mman.h>
#include <memory>

struct JumpTableEntry
{
    void *FunctionPtr;
};

class RuntimeModule;

struct ExecutionState
{
    int FunctionIndex;
    RuntimeModule *Mod;
};

// The instantiation of a static module, with runtime state.
class RuntimeModule {
public:
    RuntimeModule(std::shared_ptr<StaticModule> static_module) : static_module_(static_module) { init_jump_table(); load_functions(); }

    std::shared_ptr<StaticModule> static_module() const { return static_module_; }
    std::map<int, Function> &functions() { return functions_; }

    void invoke_function(ExecutionState *state);
    void *compile_function(int index);

private:
    std::shared_ptr<StaticModule> static_module_;
    std::map<int, Function> functions_;

    JumpTableEntry jump_table_[256];

    void init_jump_table();
    void load_functions();
};
