#include <runtime.h>

class Function {
    typedef void (*FunctionPointer)(void);
public:
    Function(bool internal_function, unsigned int function_index, unsigned int type_index, Payload &function_body) :
            internal_function_(internal_function), function_index_(function_index), type_index_(type_index),
            function_body_(function_body), compiled_code_(nullptr) {}

    void invoke() { compiled_code_(); }
    bool is_compiled() const { return compiled_code_ != nullptr; }
    bool internal_function() const { return internal_function_; }
    Payload &function_body() const { return function_body_; }

private:
    bool internal_function_;
    unsigned int function_index_;
    unsigned int type_index_;
    FunctionPointer compiled_code_;
    Payload &function_body_;
};