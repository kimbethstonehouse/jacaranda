#pragma once

#include <string>
#include <module.h>

class Runtime {
public:
    Runtime() {}
    ~Runtime() {}

    Module load_module(const std::string &filename);
    void run();
private:
    std::vector<Module> modules_;
    // todo: list of instantiated modules too, with start function
};