#pragma once

#include <string>
#include "headers/memory_state.hpp"

#define INVALID_MODE "This instruction has an invalid mode"
#define INVALID_STORE "The STORE instruction can't be used with an inmediate operand"
#define INVALID_READ "The READ instruction can't be used with an inmediate operand"
#define EXECUTION_END "The execution finished succesfully"
#define ACCUMULATOR_REG 0

enum Mode {
    INMEDIATE,
    DIRECT,
    INDIRECT,
    LABEL,
};

class Instruction {
   protected: 
    int operand;
    Mode mode;
   public:
    virtual void execute(MemoryState& mem);
};

class LoadInstruction : public Instruction {
    void execute(MemoryState& mem);
};

class StoreInstruction : public Instruction {
    void execute(MemoryState& mem);
};

class AddInstruction : public Instruction {
    void execute(MemoryState& mem);
};

class SubInstruction : public Instruction {
    void execute(MemoryState& mem);
};

class MultInstruction : public Instruction {
    void execute(MemoryState& mem);
};

class DivInstruction : public Instruction {
    void execute(MemoryState& mem);
};

class ReadInstruction : public Instruction {
    void execute(MemoryState& mem);
};

class WriteInstruction : public Instruction {
    void execute(MemoryState& mem);
};

class JumpInstruction : public Instruction {
    void execute(MemoryState& mem);
};

class JGTZInstruction : public Instruction {
    void execute(MemoryState& mem);
};

class JZeroInstruction : public Instruction {
    void execute(MemoryState& mem);
};

class HaltInstruction : public Instruction {
    void execute(MemoryState& mem);
};