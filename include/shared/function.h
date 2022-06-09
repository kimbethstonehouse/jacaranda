#pragma once

#include <section.h>

class Function {
public:
    Function(bool internal_function, unsigned int function_index, std::unique_ptr<Wasm::FunctionType> &function_type, Payload &function_body) :
            internal_function_(internal_function), function_index_(function_index), function_type_(function_type),
            function_body_(function_body) {}
    
    bool internal_function() const { return internal_function_; }
    std::unique_ptr<Wasm::FunctionType> &function_type() const { return function_type_; }
    Payload &function_body() const { return function_body_; }

private:
    bool internal_function_;
    unsigned int function_index_;
    std::unique_ptr<Wasm::FunctionType> &function_type_;
    Payload &function_body_;
};