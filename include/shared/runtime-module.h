#pragma once

#include <function.h>
#include <static-module.h>
#include <math.h>
#include <sys/mman.h>
#include <memory>

// The instantiation of a static module, with runtime state.
class RuntimeModule {
public:
    RuntimeModule(std::shared_ptr<StaticModule> static_module) : static_module_(static_module) { load_functions(); }

    std::shared_ptr<StaticModule> static_module() const { return static_module_; }
    std::map<int, Function> &functions() { return functions_; }
    int function_count() { return function_count_; }

private:
    std::shared_ptr<StaticModule> static_module_;
    std::map<int, Function> functions_;
    int function_count_;

    void load_functions();
};
