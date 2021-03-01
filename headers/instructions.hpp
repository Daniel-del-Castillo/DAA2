#pragma once

#include <string>
#include <fstream>
#include "headers/memory_state.hpp"

#define INVALID_MODE std::string("This instruction has an invalid mode")
#define INVALID_STORE std::string("The STORE instruction can't be used with an inmediate operand")
#define INVALID_READ std::string("The READ instruction can't be used with an inmediate operand")
#define INVALID_INPUT std::string("The READ instruction read something invalid: ")
#define INVALID_WRITE std::string("The WRITE instruction can't be used to write the content of the accumulator")
#define EXECUTION_END std::string("The execution finished succesfully")
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
    virtual void execute(MemoryState& mem) = 0;
    virtual std::string to_string() = 0;
};

class LoadInstruction : public Instruction {
   public: 
    using Instruction::Instruction;
    void execute(MemoryState& mem);
    std::string to_string();
};

class StoreInstruction : public Instruction {
   public: 
    using Instruction::Instruction;
    void execute(MemoryState& mem);
    std::string to_string();
};

class AddInstruction : public Instruction {
   public: 
    using Instruction::Instruction;
    void execute(MemoryState& mem);
    std::string to_string();
};

class SubInstruction : public Instruction {
   public: 
    using Instruction::Instruction;
    void execute(MemoryState& mem);
    std::string to_string();
};

class MultInstruction : public Instruction {
   public: 
    using Instruction::Instruction;
    void execute(MemoryState& mem);
    std::string to_string();
};

class DivInstruction : public Instruction {
   public: 
    using Instruction::Instruction;
    void execute(MemoryState& mem);
    std::string to_string();
};

class ReadInstruction : public Instruction {
   public: 
    using Instruction::Instruction;
    void execute(MemoryState& mem);
    std::string to_string();
};

class WriteInstruction : public Instruction {
   public: 
    using Instruction::Instruction;
    void execute(MemoryState& mem);
    std::string to_string();
};

class JumpInstruction : public Instruction {
   public: 
    using Instruction::Instruction;
    void execute(MemoryState& mem);
    std::string to_string();
};

class JGTZInstruction : public Instruction {
   public: 
    using Instruction::Instruction;
    void execute(MemoryState& mem);
    std::string to_string();
};

class JZeroInstruction : public Instruction {
   public: 
    using Instruction::Instruction;
    void execute(MemoryState& mem);
    std::string to_string();
};

class HaltInstruction : public Instruction {
   public: 
    using Instruction::Instruction;
    void execute(MemoryState& mem);
    std::string to_string();
};