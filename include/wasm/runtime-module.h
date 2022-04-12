#pragma once

#include <function.h>
#include <static-module.h>

// The instantiation of a static module, with runtime state.
class RuntimeModule {
public:
    RuntimeModule(StaticModule &static_module) : static_module_(static_module) { load_functions(); }

    StaticModule &static_module() const { return static_module_; }
    std::map<int, Function> &functions() { return functions_; }
private:
    StaticModule &static_module_;
    std::map<int, Function> functions_;

    void load_functions();
};
