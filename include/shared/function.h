#pragma once

#include <section.h>

extern "C" int do_invoke_function(void*, void*);

class Function {
public:
    typedef void (*FunctionPointer)(void);
    Function(bool internal_function, unsigned int function_index, FuncType &type, Payload &function_body) :
            internal_function_(internal_function), function_index_(function_index), type_(type),
            function_body_(function_body), compiled_code_(nullptr) {}

    /*void invoke() {
        compiled_code_();
//        do_invoke_function(nullptr, (void *) compiled_code_);
    }*/
    
    void update_pointer(char *pointer) { compiled_code_ = (FunctionPointer) pointer; }
    bool is_compiled() const { return compiled_code_ != nullptr; }
    bool internal_function() const { return internal_function_; }
    Payload &function_body() const { return function_body_; }

private:
    bool internal_function_;
    unsigned int function_index_;
    FuncType &type_;
    FunctionPointer compiled_code_;
    Payload &function_body_;
};