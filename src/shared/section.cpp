#include <section.h>
#include <ast.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>

void Wasm::CustomSection::parse_section() {
    name_ = get_data().read_name(VARUINT32);
}

void Wasm::TypeSection::parse_section() {
    Payload payload = get_data();
    count_ = payload.read_uleb128(VARUINT32);

    for (int i = 0; i < count_; i++) {
        unsigned char form = payload.read_uleb128(VARUINT7);
        if (form != LanguageTypes::FUNC) {
            throw parse_exception("invalid function type value " + std::to_string(form) +
                                  ", should be " + std::to_string(LanguageTypes::FUNC));
        }

        // Parse the function type
        unsigned int param_count = payload.read_uleb128(VARUINT32);
        std::vector<ValueType> param_types;

        for (int j = 0; j < param_count; j++) {
            param_types.push_back(ValueType(payload.read_uleb128(VARUINT7)));
        }

        unsigned char return_count = payload.read_uleb128(VARUINT1);
        std::optional<ValueType> return_type;

        if (return_count == 1) {
            return_type = ValueType(payload.read_uleb128(VARUINT7));
        }

        types_.insert({i, std::make_shared<FunctionType>(FunctionType(param_count, param_types, return_count, return_type))});
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
        functions_.insert({i, FunctionEntry(type_index)});
    }
}

void Wasm::GlobalSection::parse_section() {
    Payload payload = get_data();
    count_ = payload.read_uleb128(VARUINT32);
    // TODO: Parse global entries.
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

    for (int i = 0; i < count_; i++) {
        std::string name = payload.read_name(VARUINT32);
        unsigned char type = payload.read_uleb128(VARUINT7);
        unsigned int index = payload.read_uleb128(VARUINT32);

        exports_.insert({i, ExportEntry(name, type, index)});
    }
}
