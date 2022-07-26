#pragma once

#include <section.h>

class Function {
public:
    Function(bool internal_function, unsigned int function_index, std::shared_ptr<Wasm::FunctionType> function_type, std::shared_ptr<Payload> function_body) :
            internal_function_(internal_function), function_index_(function_index), function_type_(function_type),
            function_body_(function_body) {}
    
    bool internal_function() const { return internal_function_; }
    std::shared_ptr<Wasm::FunctionType> function_type() const { return function_type_; }
    std::shared_ptr<Payload> function_body() const { return function_body_; }

private:
    bool internal_function_;
    unsigned int function_index_;
    std::shared_ptr<Wasm::FunctionType> function_type_;
    std::shared_ptr<Payload> function_body_;
};