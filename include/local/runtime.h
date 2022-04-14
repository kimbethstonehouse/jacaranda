#pragma once

#include <string>
#include <map>
#include <static-module.h>
#include <runtime-module.h>
#include <function.h>
#include <memory>

class Runtime {
public:
    Runtime();
    ~Runtime();
    void load_module(const std::string &filename);
    void run(const std::string &filename);
    void invoke_function(std::shared_ptr<RuntimeModule>, int function_index, bool startFunction = false);
    void remote_compile(Function &func);
private:
    std::map<std::string, std::shared_ptr<StaticModule>> static_modules_;
    // TODO: what is the key here, what if we instantiate the same static module twice?
    std::map<std::string, std::shared_ptr<RuntimeModule>> runtime_modules_;
    char *code_section_;
    char *next_function_;
};