#include <runtime-module.h>
#include <section.h>
#include <stdexcept>
#include <iostream>

// Function index space indexes all imported and internally-defined function definitions,
// assigning monotonically-increasing indices based on the order of definition in the module
void RuntimeModule::load_functions()
{
    auto imports = static_module_->get_section<Wasm::ImportSection>()->imports();
    auto type_section = static_module_->get_section<Wasm::TypeSection>();

    Payload blank = Payload();
    for (const auto &import : imports) {
        if (import.second.import_type() == ExternalKind::FUNCTION) {
            functions_.insert({import.first, Function(false, import.first, type_section->get_type(import.second.type_index()), blank)});
        }
    }

    auto functions = static_module_->get_section<Wasm::FunctionSection>()->functions();
    auto code = static_module_->get_section<Wasm::CodeSection>()->bodies();

    if (functions.size() != code.size()) {
        throw run_exception("local: run: number of function declarations in function section "
                            "does not match number of function definitions in code section");
    }

    int index;
    int index_offset = imports.size();

    for (const auto &function : functions) {
        index = function.first + index_offset;
        functions_.insert({index, Function(true, index, type_section->get_type(function.second.type_index()), code.find(function.first)->second)});
    }

    function_count_ = index + 1; // The count is the last zero-based index plus one
}