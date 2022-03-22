#include <section.h>

void TypeSection::parse_section() {
    Payload payload = get_data();
    count_ = payload.read_uleb128();
    // TODO: type entries
}

void ExportSection::load_exports() {
    Payload payload = get_data();

    unsigned int nr_exports = payload.read_uleb128();
    std::cerr << "nr exports=" << nr_exports << std::endl;

    int export_index = 0;
    while (!payload.eob()) {
        // read name
        std::string name = payload.read_name();

        // read type
        ExportType type = (ExportType) payload.read_u8();

        // read index
        unsigned int idx = payload.read_uleb128();

        std::cerr << "name=" << name << ", type=" << (int)type << ", index=" << idx << std::endl;

        exports_[export_index++] = ExportEntry{name, type, idx};
    }
}

void ImportSection::load_imports() {
    Payload payload = get_data();

    unsigned int nr_imports = payload.read_uleb128();
    std::cerr << "nr imports=" << nr_imports << std::endl;

    int import_index = 0;
    while (!payload.eob()) {
        std::string module_name = payload.read_name();
        std::string import_name = payload.read_name();

        int type = payload.read_u8();

        switch (type) {
            case 0: {
                unsigned int typeidx = payload.read_uleb128();
                imports_[import_index++] = ImportEntry{module_name, import_name, (ImportType) type, typeidx};
                break;
            }

            default:
                throw std::runtime_error("unsupported import type " + std::to_string(type));
        }
    }
}

void FunctionSection::load_functions()
{
    Payload payload = get_data();

    unsigned int nr_functions = payload.read_uleb128();
    std::cerr << "nr fn=" << nr_functions << std::endl;

    int function_index = 0;
    while (!payload.eob()) {
        // read type index
        unsigned int type_index = payload.read_uleb128();

        functions_[function_index++] = FunctionEntry{type_index};
    }
}

void CodeSection::load_code()
{
    Payload payload = get_data();

    unsigned int nr_blocks = payload.read_uleb128();
    std::cerr << "nr code blocks=" << nr_blocks << std::endl;

    int index = 0;
    while (!payload.eob()) {
        unsigned int size = payload.read_uleb128();
        code_[index++] = Payload{payload.at(), size};
        payload.skip(size);
    }
}

