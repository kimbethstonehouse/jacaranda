#include <section.h>

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

        types_.insert({i, std::unique_ptr<FunctionType>(new FunctionType(param_count, param_types, return_count, return_type))});
    }
}

void Wasm::ImportSection::parse_section() {
    Payload payload = get_data();
    count_ = payload.read_uleb128(VARUINT32);

    for (int i = 0; i < count_; i++) {
        std::string module_name = payload.read_name(VARUINT32);
        std::string import_name = payload.read_name(VARUINT32);
        unsigned char type = payload.read_uleb128(VARUINT7);

        if (type != ExternalKind::FUNCTION) {
            throw parse_exception("invalid external kind " + std::to_string(type) +
                                  ", currently only functions are supported");
        }

        unsigned int type_index = payload.read_uleb128(VARUINT32);

        imports_.insert({i, ImportEntry(module_name, import_name, type, type_index)});
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
        bodies_.insert({i, Payload(payload.at(), body_size)});
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

void Wasm::FunctionBody::parse_body() {
    body_size_ = payload_.read_uleb128(VARUINT32);
    local_count_ = payload_.read_uleb128(VARUINT32);

    for (int i = 0; i < local_count_; i++) {
        local_variables_.push_back(LocalEntry(payload_.read_uleb128(VARUINT32),
                                              ValueType(payload_.read_uleb128(VARUINT7))));
    }

    int bytecode_length = payload_.data_end()-payload_.at();
    code_ = Payload(payload_.at(), payload_.data_end()-payload_.at());

    // Sanity check
    if (*code_.data_end() != 0x0b) {
        throw compile_exception("error during function body decoding, end byte does not equal 0x0b");
    }
}
