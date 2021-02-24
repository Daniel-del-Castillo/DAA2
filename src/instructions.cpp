#include "headers/instructions.hpp"

void LoadInstruction::execute(MemoryState& mem) {
    switch (mode) {
    case Mode::INMEDIATE:
        mem.registers[ACCUMULATOR_REG] = operand;
        break;
    case Mode::DIRECT:
        mem.registers[ACCUMULATOR_REG] = mem.registers[operand];
        break;
    case Mode::INDIRECT:
        mem.registers[ACCUMULATOR_REG] = mem.registers[mem.registers[operand]];
        break;
    default:
        throw INVALID_MODE;
    }
    mem.instruction_counter += 1;
}

void StoreInstruction::execute(MemoryState& mem) {
    switch (mode) {
    case Mode::INMEDIATE:
        throw INVALID_STORE;
        break;
    case Mode::DIRECT:
        mem.registers[operand] = mem.registers[ACCUMULATOR_REG];
        break;
    case Mode::INDIRECT:
        mem.registers[mem.registers[operand]] = mem.registers[ACCUMULATOR_REG];
        break;
    default:
        throw INVALID_MODE;
    }
    mem.instruction_counter += 1;
}

void AddInstruction::execute(MemoryState& mem) {
    switch (mode) {
    case Mode::INMEDIATE:
        mem.registers[ACCUMULATOR_REG] += operand;
        break;
    case Mode::DIRECT:
        mem.registers[ACCUMULATOR_REG] += mem.registers[operand];
        break;
    case Mode::INDIRECT:
        mem.registers[ACCUMULATOR_REG] += mem.registers[mem.registers[operand]];
        break;
    default:
        throw INVALID_MODE;
    }
    mem.instruction_counter += 1;
}

void SubInstruction::execute(MemoryState& mem) {
    switch (mode) {
    case Mode::INMEDIATE:
        mem.registers[ACCUMULATOR_REG] -= operand;
        break;
    case Mode::DIRECT:
        mem.registers[ACCUMULATOR_REG] -= mem.registers[operand];
        break;
    case Mode::INDIRECT:
        mem.registers[ACCUMULATOR_REG] -= mem.registers[mem.registers[operand]];
        break;
    default:
        throw INVALID_MODE;
    }
    mem.instruction_counter += 1;
}

void MultInstruction::execute(MemoryState& mem) {
    switch (mode) {
    case Mode::INMEDIATE:
        mem.registers[ACCUMULATOR_REG] *= operand;
        break;
    case Mode::DIRECT:
        mem.registers[ACCUMULATOR_REG] *= mem.registers[operand];
        break;
    case Mode::INDIRECT:
        mem.registers[ACCUMULATOR_REG] *= mem.registers[mem.registers[operand]];
        break;
    default:
        throw INVALID_MODE;
    }
    mem.instruction_counter += 1;
}

void DivInstruction::execute(MemoryState& mem) {
    switch (mode) {
    case Mode::INMEDIATE:
        mem.registers[ACCUMULATOR_REG] /= operand;
        break;
    case Mode::DIRECT:
        mem.registers[ACCUMULATOR_REG] /= mem.registers[operand];
        break;
    case Mode::INDIRECT:
        mem.registers[ACCUMULATOR_REG] /= mem.registers[mem.registers[operand]];
        break;
    default:
        throw INVALID_MODE;
    }
    mem.instruction_counter += 1;
}

int read_number(std::fstream& input) {
    std::string number_str;
    std::getline(input, number_str);
    return std::stoi(number_str);
}

void ReadInstruction::execute(MemoryState& mem) {
    switch (mode) {
    case Mode::INMEDIATE:
        throw INVALID_READ;
        break;
    case Mode::DIRECT:
        mem.registers[operand] = read_number(mem.input);
        break;
    case Mode::INDIRECT:
        mem.registers[mem.registers[operand]] = read_number(mem.input);
        break;
    default:
        throw INVALID_MODE;
    }
    mem.instruction_counter += 1;
}

void WriteInstruction::execute(MemoryState& mem) {
    switch (mode) {
    case Mode::INMEDIATE:
        mem.output << operand << "\n";
        break;
    case Mode::DIRECT:
        mem.output << mem.registers[operand] << "\n";
        break;
    case Mode::INDIRECT:
        mem.output << mem.registers[mem.registers[operand]] << "\n";
        break;
    default:
        throw INVALID_MODE;
    }
    mem.instruction_counter += 1;
}

void JumpInstruction::execute(MemoryState& mem) {
    if (mode == Mode::LABEL) {
        mem.instruction_counter = operand;
    } else {
        throw INVALID_MODE;
    }
    mem.instruction_counter += 1;
}

void JGTZInstruction::execute(MemoryState& mem) {
    if (mode == Mode::LABEL) {
        if (mem.registers[ACCUMULATOR_REG] >= 0) {
            mem.instruction_counter = operand;
        } else {
            mem.instruction_counter += 1;
        }
    } else {
        throw INVALID_MODE;
    }
    mem.instruction_counter += 1;
}

void JZeroInstruction::execute(MemoryState& mem) {
    if (mode == Mode::LABEL) {
        if (mem.registers[ACCUMULATOR_REG] == 0) {
            mem.instruction_counter = operand;
        } else {
            mem.instruction_counter += 1;
        }
    } else {
        throw INVALID_MODE;
    }
    mem.instruction_counter += 1;
}

void HaltInstruction::execute(MemoryState& mem) {
    throw EXECUTION_END;
}