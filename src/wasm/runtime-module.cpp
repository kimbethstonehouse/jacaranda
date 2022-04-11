#include <runtime-module.h>
#include <section.h>

// Function index space indexes all imported and internally-defined function definitions,
// assigning monotonically-increasing indices based on the order of definition in the module
void RuntimeModule::load_functions() {
    auto imports = static_module_->get_section<ImportSection>()->imports();
    for (const auto &import : imports) {
        if (import.second.import_type() == ExternalKind::FUNCTION) {
            functions_.insert({import.first, Function(false, import.second.type_index())});
        }
    }

    auto functions = static_module_->get_section<FunctionSection>()->functions();
    auto code = static_module_->get_section<CodeSection>()->bodies();

    if (functions.size() != code.size()) {
        throw run_exception("local: run: number of function declarations in function section "
                            "does not match number of function definitions in code section");
    }

    int index_offset = imports.size();

    for (const auto &function : functions) {
        functions_.insert({function.first+index_offset, Function(true, function.second.type_index())});
    }
}

void RuntimeModule::invoke_function(int idx, bool startFunction) {
    auto function = functions_.find(idx);

    if (function == functions_.end()) {
        throw run_exception("local: run: tried to invoke nonexistent function with id " + std::to_string(idx));
    }

    // TODO: Imported functions are ignored for now
    if (!function->second.internal_function()) return;

    if (startFunction) {
        // TODO: if not compiled, compile locally
    } else {
        // TODO: if not compiled, compile remotely
    }

    function->second.invoke();
}