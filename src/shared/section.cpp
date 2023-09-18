#include <section.h>
#include <llvm/IR/Module.h>

void Wasm::CustomSection::parse_section() {
    name_ = get_data().read_name(VARUINT32);
}

/* The func_type is the description of a function signature.
 * form varint7: the value for the func type constructor (-0x20, i.e. 0x60)
 * param_count varuint32: the number of parameters to the function
 * param_types value_type*: the parameter types of the function
 * return_count varuint1: the number of results from the function
 * return_type value_type?: the result type of the function (if return_count is 1) */
void Wasm::TypeSection::parse_section() {
    Payload payload = get_data();
    count_ = payload.read_uleb128(VARUINT32);

    for (int i = 0; i < count_; i++) {
        unsigned char form = payload.read_uleb128(VARUINT7);
        if (form != LanguageTypes::FUNC) {
            throw parse_exception("invalid function type value " + std::to_string(form) +
                                  ", should be " + std::to_string(LanguageTypes::FUNC));
        }

        std::shared_ptr<WasmFunctionType> function_type = std::make_shared<WasmFunctionType>();

        // Parse the function type
        function_type->set_param_count(payload.read_uleb128(VARUINT32));
        for (int j = 0; j < function_type->param_count(); j++) {
            unsigned char param_type = payload.read_uleb128(VARUINT7);
            Wasm::validate_type(param_type);
            function_type->add_param_types(param_type);
        }

        function_type->set_return_count(payload.read_uleb128(VARUINT1));
        if (function_type->return_count() == 1) {
            function_type->set_return_type(payload.read_uleb128(VARUINT7));
        }

        types_.insert({i, function_type});
    }
}

void Wasm::ImportSection::parse_section() {
    Payload payload = get_data();
    count_ = payload.read_uleb128(VARUINT32);

    for (int i = 0; i < count_; i++) {
        std::string module_name = payload.read_name(VARUINT32);
        std::string import_name = payload.read_name(VARUINT32);
        unsigned char type = payload.read_uleb128(VARUINT7);

        if (type == ExternalKind::FUNCTION) {
            unsigned int type_index = payload.read_uleb128(VARUINT32);
            imports_.insert({i, ImportEntry(module_name, import_name, type, type_index)});
        } else if (type == ExternalKind::TABLE) {
            // todo: actually store this information
            int element_type = payload.read_leb128(VARINT7);
            bool flags = payload.read_uleb128(VARUINT1);
            int initial = payload.read_uleb128(VARUINT32);
            if (flags) int maximum = payload.read_uleb128(VARUINT32);
        } else if (type == ExternalKind::MEMORY) {
            // todo: actually store this information
            bool flags = payload.read_uleb128(VARUINT1);
            int initial = payload.read_uleb128(VARUINT32);
            if (flags) int maximum = payload.read_uleb128(VARUINT32);
        } else {
            // todo: parse global types
            throw parse_exception("invalid external kind " + std::to_string(type) +
                      ", currently only functions, tables and memories are supported");
        }
    }
}

void Wasm::FunctionSection::parse_section() {
    Payload payload = get_data();
    count_ = payload.read_uleb128(VARUINT32);

    for (int i = 0; i < count_; i++) {
        unsigned int type_index = payload.read_uleb128(VARUINT32);
        functions_.insert({i, type_index});
    }
}

void Wasm::GlobalSection::parse_section() {
    Payload payload = get_data();
    count_ = payload.read_uleb128(VARUINT32);
    // TODO: Parse global entries. May be mutable or immutable, and must contain constant initialiser expression.
}

void Wasm::CodeSection::parse_section() {
    Payload payload = get_data();
    count_ = payload.read_uleb128(VARUINT32);

    for (int i = 0; i < count_; i++) {
        unsigned int body_size = payload.read_uleb128(VARUINT32);
        bodies_.insert({i, std::make_shared<Payload>(payload.at(), body_size)});
        payload.skip(body_size);
    }
}

void Wasm::ExportSection::parse_section() {
    Payload payload = get_data();
    count_ = payload.read_uleb128(VARUINT32);

    bool found_main = false;
    for (int i = 0; i < count_; i++) {
        std::string name = payload.read_name(VARUINT32);
        unsigned char type = payload.read_uleb128(VARUINT7);
        unsigned int index = payload.read_uleb128(VARUINT32);

        // The main function may be called something else, but let's ignore that for now
        // Either way, the first function to be executed MUST be imported as per the specification
        if (name == "__main_argc_argv" && type == ExternalKind::FUNCTION) {
            found_main = true;
            main_idx_ = index;
        }
        exports_.insert({i, ExportEntry(name, type, index)});
    }

    // A WebAssembly module must export a start function
    if (!found_main) {
        throw repository_exception("module did not export _start function");
    }
}
