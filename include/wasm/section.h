#pragma once

#include <cstdlib>
#include <iostream>
#include <map>
#include <payload.h>
#include <vector>
#include <optional>
#include <wasm.h>

class ValueType {
public:
    ValueType(unsigned char type) : type_(type) { validate(); }
private:
    unsigned char type_;
    void validate() {
        if (type_ != LanguageTypes::I32 && type_ != LanguageTypes::I64 &&
                type_ != LanguageTypes::F32 && type_ != LanguageTypes::F64) {
            throw load_exception("local: parse: invalid value type form");
        }
    }
};

class GlobalType {
public:
    GlobalType(ValueType content_type, unsigned char mutability) : content_type_(content_type), mutability_(mutability) {}
private:
    ValueType content_type_;
    unsigned char mutability_; // 0 if immutable, 1 if mutable
};

/* The func_type is the description of a function signature.
 * form varint7: the value for the func type constructor (-0x20, i.e. 0x60)
 * param_count varuint32: the number of parameters to the function
 * param_types value_type*: the parameter types of the function
 * return_count varuint1: the number of results from the function
 * return_type value_type?: the result type of the function (if return_count is 1) */
class FuncType {
public:
    FuncType(unsigned int param_count, std::vector<ValueType> param_types,
             unsigned char return_count, std::optional<ValueType> return_type) :
             param_count_(param_count), param_types_(param_types),
             return_count_(return_count), return_type_(return_type) {}
private:
    unsigned int param_count_;
    std::vector<ValueType> param_types_;
    unsigned char return_count_;
    std::optional<ValueType> return_type_;
};

class ImportEntry {
public:
    ImportEntry(std::string module_name, std::string import_name, unsigned char import_type, unsigned int type_index) :
        module_name_(module_name), import_name_(import_name), import_type_(import_type), type_index_(type_index) {}
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

class FunctionEntry {
public:
    FunctionEntry(unsigned int type_index) : type_index_(type_index) {}
    int type_index() const { return type_index_; }
private:
    unsigned int type_index_;
};

class GlobalEntry {
public:
    GlobalEntry(ValueType content_type, unsigned char mutability) : type_(content_type, mutability) {}

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
    std::string export_name() const { return export_name_; }
    unsigned char export_type() const { return export_type_; }
    unsigned int index() const { return index_; }
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
    LocalEntry(unsigned int count, ValueType type) : count_(count), type_(type) {}
private:
    unsigned int count_;
    ValueType type_;
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
 * entries func_type*: repeated FuncType entries */
class TypeSection : public Section {
public:
    static constexpr int id = TYPE_SECTION_ID;
    TypeSection(Payload payload) : Section(payload) { parse_section(); }
private:
    unsigned int count_;
    // Map from function index to signature
    std::map<int, FuncType> types_;
    void parse_section() override;
    FuncType get_type(const int &idx) { return types_.at(idx); }
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

    const std::map<int, FunctionEntry> &functions() const { return functions_; }
    const FunctionEntry &get_function(int index) const { return functions_.at(index); }
private:
    unsigned int count_;
    // Map from function index to type index
    std::map<int, FunctionEntry> functions_;
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
 * count varuint32: indicating the number of memories defined by the module
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

    const std::map<int, ExportEntry> &exports() const { return exports_; }
    const ExportEntry &get_export(int index) const { return exports_.at(index); }

private:
    unsigned int count_;
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

    Payload get_body(int index) const { return bodies_.at(index); }
    std::map<int, Payload> bodies() const { return bodies_; }
private:
    unsigned int count_;
    // We parse the bodies themselves lazily. Leave as buffers in the meantime.
    std::map<int, Payload> bodies_;
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