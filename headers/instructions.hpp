#pragma once

#include <string>
#include <fstream>
#include "headers/memory_state.hpp"

class InvalidInstruction: public std::exception {
   protected: 
    mutable std::string message;
   public: 
    InvalidInstruction(const std::string& s);
};

class InvalidMode: public InvalidInstruction {
    using InvalidInstruction::InvalidInstruction;
    const char* what() const noexcept;
};

class InvalidStore: public InvalidInstruction {
    using InvalidInstruction::InvalidInstruction;
    const char* what() const noexcept;
};

class InvalidRead: public InvalidInstruction {
    using InvalidInstruction::InvalidInstruction;
    const char* what() const noexcept;
};

class InvalidInput: public InvalidInstruction {
    using InvalidInstruction::InvalidInstruction;
    const char* what() const noexcept;
};

class InvalidWrite: public InvalidInstruction {
    using InvalidInstruction::InvalidInstruction;
    const char* what() const noexcept;
};

class DivisionByZero: public InvalidInstruction {
    using InvalidInstruction::InvalidInstruction;
    const char* what() const noexcept;
};

class ExecutionEnd: public std::exception {
    const char* what() const noexcept;
};

#define LOAD_INSTRUCTION_ID std::string("load")
#define STORE_INSTRUCTION_ID std::string("store")
#define ADD_INSTRUCTION_ID std::string("add")
#define SUB_INSTRUCTION_ID std::string("sub")
#define MULT_INSTRUCTION_ID std::string("mult")
#define DIV_INSTRUCTION_ID std::string("div")
#define READ_INSTRUCTION_ID std::string("read")
#define WRITE_INSTRUCTION_ID std::string("write")
#define JUMP_INSTRUCTION_ID std::string("jump")
#define JGTZ_INSTRUCTION_ID std::string("jgtz")
#define JZERO_INSTRUCTION_ID std::string("jzero")
#define HALT_INSTRUCTION_ID std::string("halt")
#define INMEDIATE_MODE_SYMBOL "="
#define INDIRECT_MODE_SYMBOL "*"
#define ACCUMULATOR_REG 0

enum Mode {
    INMEDIATE,
    DIRECT,
    INDIRECT,
    LABEL,
    HALT,
};

std::string mode_to_string();

class Instruction {
   protected: 
    int operand;
    Mode mode;
   public:
    Instruction(int operand, Mode mode);
    virtual ~Instruction() = default;
    virtual void execute(MemoryState& mem) const = 0;
    virtual std::string to_string() const = 0;
};

class LoadInstruction : public Instruction {
   public: 
    using Instruction::Instruction;
    void execute(MemoryState& mem) const;
    std::string to_string() const;
};

class StoreInstruction : public Instruction {
   public: 
    using Instruction::Instruction;
    void execute(MemoryState& mem) const;
    std::string to_string() const;
};

class AddInstruction : public Instruction {
   public: 
    using Instruction::Instruction;
    void execute(MemoryState& mem) const;
    std::string to_string() const;
};

class SubInstruction : public Instruction {
   public: 
    using Instruction::Instruction;
    void execute(MemoryState& mem) const;
    std::string to_string() const;
};

class MultInstruction : public Instruction {
   public: 
    using Instruction::Instruction;
    void execute(MemoryState& mem) const;
    std::string to_string() const;
};

class DivInstruction : public Instruction {
   public: 
    using Instruction::Instruction;
    void execute(MemoryState& mem) const;
    std::string to_string() const;
};

class ReadInstruction : public Instruction {
   public: 
    using Instruction::Instruction;
    void execute(MemoryState& mem) const;
    std::string to_string() const;
};

class WriteInstruction : public Instruction {
   public: 
    using Instruction::Instruction;
    void execute(MemoryState& mem) const;
    std::string to_string() const;
};

class JumpInstruction : public Instruction {
   public: 
    using Instruction::Instruction;
    void execute(MemoryState& mem) const;
    std::string to_string() const;
};

class JGTZInstruction : public Instruction {
   public: 
    using Instruction::Instruction;
    void execute(MemoryState& mem) const;
    std::string to_string() const;
};

class JZeroInstruction : public Instruction {
   public: 
    using Instruction::Instruction;
    void execute(MemoryState& mem) const;
    std::string to_string() const;
};

class HaltInstruction : public Instruction {
   public: 
    using Instruction::Instruction;
    void execute(MemoryState& mem) const;
    std::string to_string() const;
};