#pragma once

#include <string>
#include <static-module.h>
#include <runtime-module.h>

class Runtime {
public:
    Runtime() {}
    ~Runtime() {}

    void load_module(const std::string &filename);
    void run(const std::string &filename);
    void invoke_function(RuntimeModule &runtime_module, const int &function_index, bool startFunction = false);
    void remote_compile(Function &func);
private:
    std::map<std::string, StaticModule> static_modules_;
    // TODO: what is the key here, what if we instantiate the same static module twice?
    std::map<std::string, RuntimeModule> runtime_modules_;
};