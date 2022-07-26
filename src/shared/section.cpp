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

void Wasm::FunctionBody::parse_body() {
    local_count_ = payload_.read_uleb128(VARUINT32);

    for (int i = 0; i < local_count_; i++) {
        local_variables_.push_back(LocalEntry(payload_.read_uleb128(VARUINT32),
                                              ValueType(payload_.read_uleb128(VARUINT7))));
    }

    while(payload_.at() != payload_.data_end()) {
        // TODO: account for the prefix bytes
        char opcode = payload_.read_u8();

        switch(opcode) {
            case CALL_OPCODE:
                instructions_.push_back(std::make_shared<Instruction>(CallInstruction(
                        payload_.read_uleb128(VARUINT32))));
                break;
            case BLOCK_OPCODE:
                instructions_.push_back(std::make_shared<Instruction>(BlockInstruction(
                        // uint7 is not a mistake as we look for 0x40 rather than -0x40
                        payload_.read_uleb128(VARUINT7))));
                break;
            case END_OPCODE:
                instructions_.push_back(std::make_shared<Instruction>(EndInstruction()));
                break;
            case BR_IF_OPCODE:
                instructions_.push_back(std::make_shared<Instruction>(BrIfInstruction(
                        payload_.read_uleb128(VARUINT32))));
                break;
            case RETURN_OPCODE:
                instructions_.push_back(std::make_shared<Instruction>(ReturnInstruction()));
                break;
            case GET_LOCAL_OPCODE:
                instructions_.push_back(std::make_shared<Instruction>(GetLocalInstruction(
                        payload_.read_uleb128(VARUINT32))));
                break;
            case SET_LOCAL_OPCODE:
                instructions_.push_back(std::make_shared<Instruction>(SetLocalInstruction(
                        payload_.read_uleb128(VARUINT32))));
                break;
            case (0x28): //todo: what?
                instructions_.push_back(std::make_shared<Instruction>(I32Load8_sInstruction(
                        payload_.read_uleb128(VARUINT32), payload_.read_uleb128(VARUINT32))));
                break;
            case (I32_LOAD8_S_OPCODE):
                instructions_.push_back(std::make_shared<Instruction>(I32Load8_sInstruction(
                        payload_.read_uleb128(VARUINT32), payload_.read_uleb128(VARUINT32))));
                break;
            case I32_CONST_OPCODE:
                instructions_.push_back(std::make_shared<Instruction>(I32ConstInstruction(
                        payload_.read_leb128(VARINT32))));
                break;
            case I32_EQZ_OPCODE:
                instructions_.push_back(std::make_shared<Instruction>(I32EqzInstruction()));
                break;
                // todo: go back through binary and add more
            default:
                throw new decode_exception("unsupported instruction with opcode " + std::to_string(opcode) + " encountered");
        }
    }

    // Sanity check
    if (*payload_.at() != END_OPCODE) {
        throw decode_exception("error during function body decoding, expected end byte to be 0x0b, but was " + std::to_string(*payload_.at()));
    }
}
