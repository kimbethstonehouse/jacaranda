class Function {
    typedef void (*FunctionPointer)(void);
public:
    Function(bool internal_function, unsigned int type_index) :
            internal_function_(internal_function), type_index_(type_index), compiled_code_(nullptr) {}

    void invoke() { compiled_code_(); }

    bool is_compiled() const { return compiled_code_ != nullptr; }
    bool internal_function() const { return internal_function_; }
//    FunctionPointer compiled_code() const { return compiled_code_; }
private:
    bool internal_function_;
    unsigned int type_index_;
    FunctionPointer compiled_code_;
};