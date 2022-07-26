#pragma once

#include <wasm.h>
#include <section.h>

namespace Wasm {
    class BlockType {
    public:
        BlockType(unsigned char type) : type_(type) { validate(); }
        unsigned char type() const { return type_; }

    private:
        unsigned char type_;
        void validate() {
            if (type_ != LanguageTypes::I32 && type_ != LanguageTypes::I64 &&
                type_ != LanguageTypes::F32 && type_ != LanguageTypes::F64 && type_ != LanguageTypes::NO_RET) {
                throw parse_exception("invalid block type form");
            }
        }
    };

    class Instruction {
    public:
        Instruction(char opcode) :opcode_(opcode) {}

    private:
        // todo: do we actually need this?
        char opcode_;
    };

    // function_index varuint32
    // call a function by its index
    class CallInstruction : public Instruction {
    public:
        CallInstruction(int function_index) : Instruction(CALL_OPCODE), function_index_(function_index) {}
    private:
        int function_index_;
    };

    // signature block_type (varint7)
    // begin a sequence of expressions, yielding 0 or 1 values
    class BlockInstruction : public Instruction {
    public:
        BlockInstruction(char signature) : Instruction(BLOCK_OPCODE), signature_(BlockType(signature)) {}
    private:
        BlockType signature_;
    };

    // end a block, loop, or if
    class EndInstruction : public Instruction {
    public:
        EndInstruction() : Instruction(END_OPCODE) {}
    };

    // relative_depth varuint32
    // conditional break that targets an outer nested block
    class BrIfInstruction : public Instruction {
    public:
        BrIfInstruction(int relative_depth) : Instruction(BR_IF_OPCODE), relative_depth_(relative_depth) {}
    private:
        int relative_depth_;
    };

    // return zero or one value from this function
    class ReturnInstruction : public Instruction {
    public:
        ReturnInstruction() : Instruction(RETURN_OPCODE) {}
    };

    // local_index varuint32
    // read a local variable or parameter
    class GetLocalInstruction : public Instruction {
    public:
        GetLocalInstruction(int local_index) : Instruction(GET_LOCAL_OPCODE), local_index_(local_index) {}
    private:
        int local_index_;
    };

    // local_index varuint32
    // write a local variable or parameter
    class SetLocalInstruction : public Instruction {
    public:
        SetLocalInstruction(int local_index) : Instruction(SET_LOCAL_OPCODE), local_index_(local_index) {}
    private:
        int local_index_;
    };

    // memory_immediate type encoded as:
    // flags varuint32 containing the alignment in the least significant bits encoded as log2(alignment)
    // offset varuint32 containing the value of the offset
    // Load one byte and sign extend i8 to i32
    class I32Load8_sInstruction : public Instruction {
    public:
        I32Load8_sInstruction(int flags, int offset) : Instruction(I32_LOAD8_S_OPCODE), flags_(flags), offset_(offset) {}
    private:
        int flags_;
        int offset_;
    };

    // value varuint32
    // a constant value interpreted as i32
    class I32ConstInstruction : public Instruction {
    public:
        I32ConstInstruction(int value) : Instruction(I32_CONST_OPCODE), value_(value) {}
    private:
        int value_;
    };

    class I32EqzInstruction : public Instruction {
    public:
        I32EqzInstruction() : Instruction(I32_EQZ_OPCODE) {}
    };
}