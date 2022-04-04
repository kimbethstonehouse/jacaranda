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

namespace LanguageTypes {
    // Technically negative, but we use the
    // positive representation for simplicity
    unsigned char const I32 = 0x7f;
    unsigned char const I64 = 0x7e;
    unsigned char const F32 = 0x7d;
    unsigned char const F64 = 0x7c;
    unsigned char const ANYFUNC = 0x70;
    unsigned char const FUNC = 0x60;
}

namespace ExternalKind {
    unsigned char const FUNCTION = 0;
    unsigned char const TABLE = 1;
    unsigned char const MEMORY = 2;
    unsigned char const GLOBAL = 3;
}

// Supported varuintN sizes
enum VaruintN {
    VARUINT1 = 1,
    VARUINT7 = 7,
    VARUINT32 = 32,
};

static const char wasm_magic_reference[4] = {0x00, 0x61, 0x73, 0x6d};   // {NULL} asm
static const char wasm_version_reference[4] = {0x01, 0x00, 0x00, 0x00}; // Version 1

class load_exception : public std::runtime_error
{
public:
    load_exception(const std::string &message) : runtime_error(message) {}
};