#pragma once

#include <llvm/IR/Type.h>

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

// CALL
#define CALL_OPCODE 0x10

// CONTROL FLOW
#define BLOCK_OPCODE 0x02
#define END_OPCODE 0x0b
#define BR_IF_OPCODE 0x0d
#define RETURN_OPCODE 0x0f

// VARIABLE ACCESS
#define GET_LOCAL_OPCODE 0x20
#define SET_LOCAL_OPCODE 0x21

// MEMORY ACCESS
#define I32_LOAD8_S_OPCODE 0x2c

// CONSTANTS
#define I32_CONST_OPCODE 0x41

// COMPARISON OPERATORS
#define I32_EQZ_OPCODE 0x45

// NUMERIC OPERATORS
#define I32_ADD_OPCODE 0x6a
#define I32_SUB_OPCODE 0x6b

// Technically negative, but we use the
// positive representation for simplicity
namespace LanguageTypes {
    // The value types I32 and I64 are not inherently signed or unsigned
    // They can be interpreted either way by an operator
    unsigned char const I32 = 0x7f;
    unsigned char const I64 = 0x7e;
    unsigned char const F32 = 0x7d;
    unsigned char const F64 = 0x7c;
    // Indicates that a block leaves no results on the stack
    unsigned char const NO_RET = 0x40;
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

// Supported varintN sizes
enum VarintN {
    VARINT7 = 7,
    VARINT32 = 32,
    VARINT64 = 64,
};

static const char wasm_magic_reference[4] = {0x00, 0x61, 0x73, 0x6d};   // {NULL} asm
static const char wasm_version_reference[4] = {0x01, 0x00, 0x00, 0x00}; // Version 1

class parse_exception : public std::runtime_error {
public:
    parse_exception(const std::string &message) : runtime_error("parse: " + message) {}
};

class execute_exception : public std::runtime_error {
public:
    execute_exception(const std::string &message) : runtime_error("execute: " + message) {}
};

class repository_exception : public std::runtime_error {
public:
    repository_exception(const std::string &message) : runtime_error("repository: " + message) {}
};

class compile_exception : public std::runtime_error {
public:
    compile_exception(const std::string &message) : runtime_error("compile: " + message) {}
};

class decode_exception : public std::runtime_error {
public:
    decode_exception(const std::string &message) : runtime_error("decode: " + message) {}
};