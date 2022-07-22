#include <runtime-envoy.h>

FunctionIndices RuntimeEnvoy::request_function_indices(std::string module_name) {
    IndicesRequest request;
    FunctionIndices indices;
    grpc::ClientContext context;

    request.set_module_name(module_name);
    repository_stub_->request_function_indices(&context, request, &indices);
    return indices;
}

NativeBinary RuntimeEnvoy::request_compile(std::string module_name, std::string architecture, unsigned int function_idx,
                                     const std::basic_string<char>& target_data_layout, unsigned int program_pointer_size) {
    CompilationRequest request;
    NativeBinary native;
    grpc::ClientContext context;

    request.set_module_name(module_name);
    request.set_architecture(architecture);
    request.set_func_idx(function_idx);
    request.set_target_data_layout(target_data_layout);
    request.set_program_pointer_size(program_pointer_size);

    compiler_stub_->request_compile(&context, request, &native);
    return native;
}