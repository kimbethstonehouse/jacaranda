#pragma once

#include <string>
#include <static-module.h>
#include <runtime-module.h>

class Runtime {
public:
    Runtime() {}
    ~Runtime() { delete static_module_; delete runtime_module_; }

    void load_module(const std::string &filename);
    void run();
private:
    // TODO: ideally, we want to be able to load multiple modules, then choose one to run.
//    std::vector<StaticModule> modules_;
    StaticModule *static_module_;
    RuntimeModule *runtime_module_;

    // todo: list of instantiated modules too, with start function
};