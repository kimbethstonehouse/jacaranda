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

// Language types
#define I32 0x7f
#define I64 0x7e
#define F32 0x7d
#define F64 0x7c
#define ANYFUNC 0x70
#define FUNC 0x60

static const char wasm_magic_reference[4] = {0x00, 0x61, 0x73, 0x6d};   // {NULL} asm
static const char wasm_version_reference[4] = {0x01, 0x00, 0x00, 0x00}; // Version 1