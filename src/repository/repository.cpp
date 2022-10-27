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

    if (wasm_module->has_start_idx()) { indices->set_start_idx(wasm_module->start_idx()); }
    indices->set_main_idx(wasm_module->main_idx());
    indices->set_func_count(wasm_module->function_count());
}

void Repository::code(const CodeRequest *request, WasmFunction *function) {
    std::shared_ptr<WasmModule> wasm_module;
    auto wasm_module_it = static_modules_.find(request->module_name());

    // Check if the WebAssembly module has already been loaded
    if (wasm_module_it == static_modules_.end()) {
        // todo: make thread safe
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

    function->CopyFrom(*func_it->second);
}