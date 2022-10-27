#pragma once

#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>
#include <optional>
#include <memory>
#include <wasm.h>
#include <payload.h>
#include <jacaranda.pb.h>

namespace Wasm {
    static void validate_type(unsigned char type) {
        if (type != LanguageTypes::I32 && type != LanguageTypes::I64 &&
                type != LanguageTypes::F32 && type != LanguageTypes::F64) {
            throw parse_exception("invalid value type form");
        }
    }

    class GlobalType {
    public:
        GlobalType(unsigned char content_type, unsigned char mutability) : content_type_(content_type),
                                                                       mutability_(mutability) { validate_type(content_type_); }

    private:
        unsigned char content_type_;
        unsigned char mutability_; // 0 if immutable, 1 if mutable
    };

    class ImportEntry {
    public:
        ImportEntry(std::string module_name, std::string import_name, unsigned char import_type,
                    unsigned int type_index) :
                module_name_(module_name), import_name_(import_name), import_type_(import_type),
                type_index_(type_index) {}

        unsigned char import_type() const { return import_type_; }

        unsigned int type_index() const { return type_index_; }

    private:
        std::string module_name_; // aka module_str
        std::string import_name_; // aka field_str
        unsigned char import_type_; // aka kind
        /* Technically optional, but since we only support importing functions,
         * this can be considered mandatory. This is an index into TypeSection. */
        unsigned int type_index_; // aka type
    };

    class GlobalEntry {
    public:
        GlobalEntry(unsigned char content_type, unsigned char mutability) : type_(content_type, mutability) { validate_type(content_type); }

    private:
        GlobalType type_;
        // Initialiser expression to define the initial value of the variable.
        // Encoded with the same binary encoding as Wasm expressions, followed by the end opcode as a delimiter.
        // TODO: how are expressions encoded?
        unsigned int init_expr_;
    };

    class ExportEntry {
    public:
        ExportEntry(std::string export_name, unsigned char export_type, unsigned int index) :
                export_name_(export_name), export_type_(export_type), index_(index) {}

    private:
        std::string export_name_; // aka field_str
        unsigned char export_type_; // aka kind
        /* Index into the index space corresponding to the export type
         * We only support exporting functions, so this is a function index. */
        unsigned int index_;
    };

// Each local entry declares a number of local variables of a given type.
// It is legal to have several entries with the same type.
    class LocalEntry {
    public:
        LocalEntry(unsigned int count, unsigned char type) : count_(count), type_(type) { validate_type(type_); }

        unsigned char type() const { return type_; }

    private:
        unsigned int count_;
        unsigned char type_;
    };

    class Section {
    public:
        Section(Payload payload) : payload_(payload) {}

        Payload get_data() const { return payload_; }

    protected:
        virtual void parse_section() {}

    private:
        Payload payload_;
    };

    class CustomSection : public Section {
    public:
        static constexpr int id = CUSTOM_SECTION_ID;

        CustomSection(Payload payload) : Section(payload) { parse_section(); }

    private:
        std::string name_;

        void parse_section() override;
    };

/* Declares all function signatures that will be used in the module.
 * count varuint32: count of type entries to follow
 * entries func_type*: repeated FunctionType entries */
    class TypeSection : public Section {
    public:
        static constexpr int id = TYPE_SECTION_ID;

        TypeSection(Payload payload) : Section(payload) { parse_section(); }

        std::shared_ptr<WasmFunctionType> get_type(const int &idx) const { return types_.at(idx); }

    private:
        unsigned int count_;
        // Map from function index to signature
        std::map<int, std::shared_ptr<WasmFunctionType>> types_;

        void parse_section() override;
    };

/* Declares all imports that will be used in the module.
 * count varuint32: count of import entries to follow
 * entries import_entry*: repeated ImportEntries */
    class ImportSection : public Section {
    public:
        static constexpr int id = IMPORT_SECTION_ID;

        ImportSection(Payload payload) : Section(payload) { parse_section(); }

        const std::map<int, ImportEntry> &imports() const { return imports_; }

    private:
        unsigned int count_;
        std::map<int, ImportEntry> imports_;

        void parse_section() override;
    };

/* Declares a TypeSection index for all functions that will be used in the module.
 * count varuint32: count of signature indices to follow
 * types varuint32*: sequence of indices into the TypeSection */
    class FunctionSection : public Section {
    public:
        static constexpr int id = FUNCTION_SECTION_ID;

        FunctionSection(Payload payload) : Section(payload) { parse_section(); }

        const std::map<int, int> &functions() const { return functions_; }

    private:
        unsigned int count_;
        // Map from function index to type index
        std::map<int, int> functions_;

        void parse_section() override;
    };

/* The encoding of a table section. TODO: Not currently parsed. Used mainly to emulate function pointers. Will be useful in future, but I'm lazy.
 * count varuint32: indicating the number of tables defined by the module
 * types table_type*: repeated table_type entries */
    class TableSection : public Section {
    public:
        static constexpr int id = TABLE_SECTION_ID;

        TableSection(Payload payload) : Section(payload) {}
    };

/* The encoding of a memory section. TODO: Not currently parsed.
 * count varuint32: indicating the number of memories defined by the module (currently only one is allowed by the specification)
 * types memory_type*: repeated memory_type entries */
    class MemorySection : public Section {
    public:
        static constexpr int id = MEMORY_SECTION_ID;

        MemorySection(Payload payload) : Section(payload) {}
    };

/* Declares all global variables that will be used in the module.
 * count varuint32: indicating the number of global variable entries defined by the module
 * types global_variable*: repeated global_variable entries */
    class GlobalSection : public Section {
    public:
        static constexpr int id = GLOBAL_SECTION_ID;

        GlobalSection(Payload payload) : Section(payload) { parse_section(); }

    private:
        unsigned int count_;
        std::map<int, GlobalEntry> globals_;

        void parse_section() override;
    };

/* Declares all exports for the module.
 * count varuint32: count of export entries to follow
 * entries export_entry*: repeated ExportEntries */
    class ExportSection : public Section {
    public:
        static constexpr int id = EXPORT_SECTION_ID;

        ExportSection(Payload payload) : Section(payload) { parse_section(); }

        const int main_idx() { return main_idx_; }
        const std::map<int, ExportEntry> &exports() const { return exports_; }
        const ExportEntry &get_export(int index) const { return exports_.at(index); }

    private:
        unsigned int count_;
        // todo: don't think this accounts for the import function offset
        unsigned int main_idx_;
        std::map<int, ExportEntry> exports_;

        void parse_section() override;
    };

    class StartSection : public Section {
    public:
        static constexpr int id = START_SECTION_ID;

        StartSection(Payload payload) : Section(payload) { idx_ = get_data().read_uleb128(VARUINT32); }

        unsigned int get_idx() const { return idx_; }

    private:
        unsigned int idx_;
    };


// TODO: Not currently parsed.
    class ElementSection : public Section {
    public:
        static constexpr int id = ELEMENT_SECTION_ID;

        ElementSection(Payload payload) : Section(payload) {}
    };

/* Contains a body for every function in the module.
 * The count declared in the function section must match the count here.
 * count varuint32: count of function bodies to follow
 * bodies function_body*: sequence of Function Bodies */
    class CodeSection : public Section {
    public:
        static constexpr int id = CODE_SECTION_ID;

        CodeSection(Payload payload) : Section(payload) { parse_section(); }
//        ~CodeSection() { for (auto entry : bodies_) { delete entry.second; } }

        std::shared_ptr<Payload> get_body(int index) const { return bodies_.at(index); }

        std::map<int, std::shared_ptr<Payload>> bodies() const { return bodies_; }

    private:
        unsigned int count_;
        // We parse the bodies themselves lazily. Leave as buffers in the meantime.
        std::map<int, std::shared_ptr<Payload>> bodies_;

        void parse_section() override;
    };

/* Declares the initialised data that is loaded into the linear memory. // TODO: not currently parsed
 * count varuint32: count of data segments to follow
 * data data_segment*: repeated DataSegments */
    class DataSection : public Section {
    public:
        static constexpr int id = DATA_SECTION_ID;

        DataSection(Payload payload) : Section(payload) {}
    };
}