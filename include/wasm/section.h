#pragma once

#include <cstdlib>
#include <iostream>
#include <map>
#include <payload.h>
#include <vector>

#define CUSTOM_SECTION_ID 0
#define TYPE_SECTION_ID 1
#define IMPORT_SECTION_ID 2
#define FUNCTION_SECTION_ID 3
#define TABLE_SECTION_ID 4
#define MEMORY_SECTION_ID 5
#define GLOBAL_SECTION_ID 6
#define EXPORT_SECTION_ID 7
#define START_SECTION_ID 8
#define ELEMENT_SECTION_ID 9
#define CODE_SECTION_ID 10
#define DATA_SECTION_ID 11
#define DATA_COUNT_SECTION_ID 12

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
    CustomSection(Payload payload) : Section(payload) {}
};

/* Declares all function signatures that will be used in the module.
 * count varuint32: count of type entries to follow
 * entries func_type*: repeated type entries as described above */
class TypeSection : public Section {
public:
    static constexpr int id = TYPE_SECTION_ID;
    TypeSection(Payload payload) : Section(payload) { parse_section(); }
private:
    unsigned int count_;
    void parse_section() override;
    // TODO: type entries
//    std::map<int, const char *> types_;
};

enum class ImportType { function = 0 };

class ImportEntry {
public:
    std::string module_name;
    std::string import_name;
    ImportType type;

    // Function Import
    unsigned int type_index;
};

class ImportSection : public Section {
public:
    using import_map = std::map<int, ImportEntry>;

    static constexpr int id = IMPORT_SECTION_ID;
    ImportSection(Payload payload) : Section(payload) { load_imports(); }

    const import_map &imports() const { return imports_; }

private:
    import_map imports_;
    void load_imports();
};

class FunctionEntry {
public:
    unsigned int type_index;
};

class FunctionSection : public Section {
public:
    using function_map = std::map<int, FunctionEntry>;

    static constexpr int id = FUNCTION_SECTION_ID;
    FunctionSection(Payload payload) : Section(payload) { load_functions(); }

    const function_map &functions() const { return functions_; }

    const FunctionEntry &get_function(int index) const { return functions_.at(index); }

private:
    function_map functions_;
    void load_functions();
};

class TableSection : public Section {
public:
    static constexpr int id = TABLE_SECTION_ID;
    TableSection(Payload payload) : Section(payload) {}
};

class MemorySection : public Section {
public:
    static constexpr int id = MEMORY_SECTION_ID;
    MemorySection(Payload payload) : Section(payload) {}
};

class GlobalSection : public Section {
public:
    static constexpr int id = GLOBAL_SECTION_ID;
    GlobalSection(Payload payload) : Section(payload) {}
};

enum class ExportType { func = 0, table = 1, mem = 2, global = 3 };

class ExportEntry {
public:
    std::string name;
    ExportType type;
    unsigned int index;
};

class ExportSection : public Section {
public:
    using export_map = std::map<int, ExportEntry>;

    static constexpr int id = EXPORT_SECTION_ID;
    ExportSection(Payload payload) : Section(payload) { load_exports(); }

    const export_map &exports() const { return exports_; }

    const ExportEntry &get_export(int index) const { return exports_.at(index); }

private:
    export_map exports_;
    void load_exports();
};

class StartSection : public Section {
public:
    static constexpr int id = START_SECTION_ID;
    StartSection(Payload payload) : Section(payload) {}

    unsigned int funcidx() const { return get_data().read_uleb128(); }
};

class ElementSection : public Section {
public:
    static constexpr int id = ELEMENT_SECTION_ID;
    ElementSection(Payload payload) : Section(payload) {}
};

class CodeSection : public Section {
public:
    using code_map = std::map<int, Payload>;

    static constexpr int id = CODE_SECTION_ID;
    CodeSection(Payload payload) : Section(payload) { load_code(); }

    Payload get_buffer_for_code(int index) const { return code_.at(index); }

private:
    code_map code_;
    void load_code();
};

class DataSection : public Section {
public:
    static constexpr int id = DATA_SECTION_ID;
    DataSection(Payload payload) : Section(payload) {}
};

class DataCountSection : public Section {
public:
    static constexpr int id = DATA_COUNT_SECTION_ID;
    DataCountSection(Payload payload) : Section(payload) {}
};