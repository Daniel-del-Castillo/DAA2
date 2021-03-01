#include "headers/instructions.hpp"

Instruction::Instruction(int operand, Mode mode) {
    this->operand = operand;
    this->mode = mode;
}

std::string mode_to_string(Mode mode) {
    switch (mode) {
    case Mode::INMEDIATE:
        return "=";
        break;
    case Mode::INDIRECT:
        return "*";
        break;
    } 
    return "";
}

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

std::string LoadInstruction::to_string() {
    return std::string("LOAD ") + mode_to_string(mode) + std::to_string(operand); 
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

std::string StoreInstruction::to_string() {
    return std::string("STORE ") + mode_to_string(mode) + std::to_string(operand); 
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

std::string AddInstruction::to_string() {
    return std::string("ADD ") + mode_to_string(mode) + std::to_string(operand); 
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

std::string SubInstruction::to_string() {
    return std::string("SUB ") + mode_to_string(mode) + std::to_string(operand); 
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

std::string MultInstruction::to_string() {
    return std::string("MULT ") + mode_to_string(mode) + std::to_string(operand); 
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

std::string DivInstruction::to_string() {
    return std::string("DIV ") + mode_to_string(mode) + std::to_string(operand); 
}

int read_number(std::fstream& input) {
    std::string number_str;
    std::getline(input, number_str);
    int number;
    try {
        number = std::stoi(number_str);
    } catch(std::exception& e) {
        throw INVALID_INPUT + number_str; 
    }
    return number;
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

std::string ReadInstruction::to_string() {
    return std::string("READ ") + mode_to_string(mode) + std::to_string(operand); 
}

void WriteInstruction::execute(MemoryState& mem) {
    switch (mode) {
    case Mode::INMEDIATE:
        mem.output << operand << "\n";
        break;
    case Mode::DIRECT:
        if (operand == ACCUMULATOR_REG) {
            throw INVALID_WRITE;
        }
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

std::string WriteInstruction::to_string() {
    return std::string("WRITE ") + mode_to_string(mode) + std::to_string(operand); 
}

void JumpInstruction::execute(MemoryState& mem) {
    if (mode == Mode::LABEL) {
        mem.instruction_counter = operand;
    } else {
        throw INVALID_MODE;
    }
    mem.instruction_counter += 1;
}

std::string JumpInstruction::to_string() {
    return std::string("JUMP ") + std::to_string(operand); 
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

std::string JGTZInstruction::to_string() {
    return std::string("JGTZ ") + std::to_string(operand); 
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

std::string JZeroInstruction::to_string() {
    return std::string("JZERO ") + std::to_string(operand); 
}

void HaltInstruction::execute(MemoryState& mem) {
    throw EXECUTION_END;
}

std::string HaltInstruction::to_string() {
    return std::string("HALT");
}