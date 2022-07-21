#include <repository.h>

void Repository::function_indices(const IndicesRequest *request, FunctionIndices *indices) {
    std::shared_ptr<WasmModule> wasm_module;
    auto wasm_module_it = static_modules_.find(request->module_name());

    // Check if the WebAssembly module has already been loaded
    if (wasm_module_it == static_modules_.end()) {
        wasm_module = std::make_shared<WasmModule>(request->module_name());
        static_modules_.insert({request->module_name(), wasm_module});
    } else {
        wasm_module = wasm_module_it->second;
    }

    auto start_section = wasm_module->get_section<Wasm::StartSection>();
    if (start_section != nullptr) {
        indices->set_start_idx(start_section->get_idx());
    }

    // A WebAssembly module must export a start function
    auto exports = wasm_module->get_section<Wasm::ExportSection>()->exports();
    bool found_main = false;
    for (const auto &exp : exports) {
        // The main function may be called something else, but let's ignore that for now
        if (exp.second.export_name() == "__main_argc_argv" && exp.second.export_type() == ExternalKind::FUNCTION) {
            found_main = true;
            indices->set_main_idx(exp.second.index());
            break;
        }
    }

    if (!found_main) {
        throw repository_exception("module did not export _start function");
    }
}

// todo: this is horribly inefficient
void Repository::code(const CodeRequest *request, WasmFunction *function) {
    std::shared_ptr<WasmModule> wasm_module;
    auto wasm_module_it = static_modules_.find(request->module_name());

    // Check if the WebAssembly module has already been loaded
    if (wasm_module_it == static_modules_.end()) {
        wasm_module = std::make_shared<WasmModule>(request->module_name());
        static_modules_.insert({request->module_name(), wasm_module});
    } else {
        wasm_module = wasm_module_it->second;
    }

    // Check if the specified function exists in this module
    auto &functions = wasm_module->functions();
    auto func_it = functions.find(request->func_idx());

    if (func_it == functions.end()) {
        throw repository_exception("tried to invoke nonexistent function with id " + std::to_string(request->func_idx()));
    }

    auto func = func_it->second;
    function->set_is_imported(func.internal_function());

    FunctionType rpc_function_type;
    rpc_function_type.set_param_count(func.function_type()->param_count());

    // Protocol buffers guarantee to retain parameter order
    for (Wasm::ValueType value_type : func.function_type()->param_types()) {
        rpc_function_type.add_param_types(value_type.type());
    }

    rpc_function_type.set_return_count(func.function_type()->return_count());
    // Optional type is only present if the function has a return value
    if (func.function_type()->return_count() > 0) {
        rpc_function_type.set_return_type(func.function_type()->return_type().value().type());
    }

    function->set_allocated_func_type(&rpc_function_type);
    function->set_func_body(func.function_body().data_start(), func.function_body().size());
}