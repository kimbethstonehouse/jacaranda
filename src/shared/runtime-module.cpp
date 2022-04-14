#include <runtime-module.h>
#include <section.h>

// Function index space indexes all imported and internally-defined function definitions,
// assigning monotonically-increasing indices based on the order of definition in the module
void RuntimeModule::load_functions() {
    auto imports = static_module_->get_section<ImportSection>()->imports();
    auto types = static_module_->get_section<TypeSection>()->types();

    Payload blank = Payload();
    for (const auto &import : imports) {
        if (import.second.import_type() == ExternalKind::FUNCTION) {
            functions_.insert({import.first, Function(false, import.first,types.find(import.second.type_index())->second, blank)});
        }
    }

    auto functions = static_module_->get_section<FunctionSection>()->functions();
    auto code = static_module_->get_section<CodeSection>()->bodies();

    if (functions.size() != code.size()) {
        throw run_exception("local: run: number of function declarations in function section "
                            "does not match number of function definitions in code section");
    }

    int index;
    int index_offset = imports.size();

    for (const auto &function : functions) {
        index = function.first+index_offset;
        functions_.insert({index, Function(true, index, types.find(function.second.type_index())->second, code.find(function.first)->second)});
    }
}