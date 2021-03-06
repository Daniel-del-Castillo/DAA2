#include "headers/instructions.hpp"

InvalidInstruction::InvalidInstruction(const std::string& s) {
    message = s;
}

const char* InvalidMode::what() const noexcept {
    message = std::string("This instruction has an invalid mode: ") + message;
    return message.c_str();
}

const char* InvalidStore::what() const noexcept {
    message =  std::string("The STORE instruction can't be used with an inmediate operand")
        + message;
    return message.c_str();
}

const char* InvalidRead::what() const noexcept {
    message = std::string("The READ instruction can't be used with an inmediate operand")
        + message;
    return message.c_str();
}

const char* InvalidInput::what() const noexcept {
    message = std::string("The READ instruction read something invalid: ")
        + message;
    return message.c_str();
}

const char* InvalidWrite::what() const noexcept {
    message = std::string("The WRITE instruction can't be used to write the content of the accumulator: ") 
        + message;
    return message.c_str();
}

const char* DivisionByZero::what() const noexcept {
    message = std::string("Can't divide by zero! Happened in instruction: ")
        + message;
    return message.c_str();
}

const char* ExecutionEnd::what() const noexcept {
    return "The execution finished succesfully";
}

Instruction::Instruction(int operand, Mode mode) {
    this->operand = operand;
    this->mode = mode;
}

std::string mode_to_string(Mode mode) {
    switch (mode) {
    case Mode::INMEDIATE:
        return INMEDIATE_MODE_SYMBOL;
        break;
    case Mode::INDIRECT:
        return INDIRECT_MODE_SYMBOL;
        break;
    } 
    return "";
}

void LoadInstruction::execute(MemoryState& mem) {
    int value;
    switch (mode) {
    case Mode::INMEDIATE:
        mem.registers[ACCUMULATOR_REG] = operand;
        break;
    case Mode::DIRECT:
        value = mem.registers[operand];
        mem.registers[ACCUMULATOR_REG] = value;
        break;
    case Mode::INDIRECT:
        value = mem.registers[mem.registers[operand]];
        mem.registers[ACCUMULATOR_REG] = value;
        break;
    default:
        throw InvalidMode(to_string());
    }
    mem.instruction_counter += 1;
}

std::string LoadInstruction::to_string() {
    return LOAD_INSTRUCTION_ID + std::string(" ") + mode_to_string(mode) + std::to_string(operand); 
}

void StoreInstruction::execute(MemoryState& mem) {
    int value;
    switch (mode) {
    case Mode::INMEDIATE:
        throw InvalidStore(to_string());
        break;
    case Mode::DIRECT:
        value = mem.registers[ACCUMULATOR_REG];
        mem.registers[operand] = value;
        break;
    case Mode::INDIRECT:
        value = mem.registers[ACCUMULATOR_REG];
        mem.registers[mem.registers[operand]] = value;
        break;
    default:
        throw InvalidMode(to_string());
    }
    mem.instruction_counter += 1;
}

std::string StoreInstruction::to_string() {
    return STORE_INSTRUCTION_ID + std::string(" ") + mode_to_string(mode) + std::to_string(operand); 
}

void AddInstruction::execute(MemoryState& mem) {
    int value;
    switch (mode) {
    case Mode::INMEDIATE:
        mem.registers[ACCUMULATOR_REG] += operand;
        break;
    case Mode::DIRECT:
        value = mem.registers[operand];
        mem.registers[ACCUMULATOR_REG] += value;
        break;
    case Mode::INDIRECT:
        value = mem.registers[mem.registers[operand]];
        mem.registers[ACCUMULATOR_REG] += value;
        break;
    default:
        throw InvalidMode(to_string());
    }
    mem.instruction_counter += 1;
}

std::string AddInstruction::to_string() {
    return ADD_INSTRUCTION_ID + std::string(" ") + mode_to_string(mode) + std::to_string(operand); 
}

void SubInstruction::execute(MemoryState& mem) {
    int value;
    switch (mode) {
    case Mode::INMEDIATE:
        mem.registers[ACCUMULATOR_REG] -= operand;
        break;
    case Mode::DIRECT:
        value = mem.registers[operand];
        mem.registers[ACCUMULATOR_REG] -= value;
        break;
    case Mode::INDIRECT:
        value = mem.registers[mem.registers[operand]];
        mem.registers[ACCUMULATOR_REG] -= value;
        break;
    default:
        throw InvalidMode(to_string());
    }
    mem.instruction_counter += 1;
}

std::string SubInstruction::to_string() {
    return SUB_INSTRUCTION_ID + std::string(" ") + mode_to_string(mode) + std::to_string(operand); 
}

void MultInstruction::execute(MemoryState& mem) {
    int value;
    switch (mode) {
    case Mode::INMEDIATE:
        mem.registers[ACCUMULATOR_REG] *= operand;
        break;
    case Mode::DIRECT:
        value = mem.registers[operand];
        mem.registers[ACCUMULATOR_REG] *= value;
        break;
    case Mode::INDIRECT:
        value = mem.registers[mem.registers[operand]];
        mem.registers[ACCUMULATOR_REG] *= value;
        break;
    default:
        throw InvalidMode(to_string());
    }
    mem.instruction_counter += 1;
}

std::string MultInstruction::to_string() {
    return MULT_INSTRUCTION_ID + std::string(" ") + mode_to_string(mode) + std::to_string(operand); 
}

void DivInstruction::execute(MemoryState& mem) {
    int value;
    switch (mode) {
    case Mode::INMEDIATE:
        if (operand == 0) {
            throw DivisionByZero(to_string());
        }
        mem.registers[ACCUMULATOR_REG] /= operand;
        break;
    case Mode::DIRECT:
        if (mem.registers[operand] == 0) {
            throw DivisionByZero(to_string());
        }
        value = mem.registers[operand];
        mem.registers[ACCUMULATOR_REG] /= value;
        break;
    case Mode::INDIRECT:
        if (mem.registers[mem.registers[operand]] == 0) {
            throw DivisionByZero(to_string());
        }
        value = mem.registers[mem.registers[operand]];
        mem.registers[ACCUMULATOR_REG] /= value;
        break;
    default:
        throw InvalidMode(to_string());
    }
    mem.instruction_counter += 1;
}

std::string DivInstruction::to_string() {
    return DIV_INSTRUCTION_ID + std::string(" ") + mode_to_string(mode) + std::to_string(operand); 
}

int read_number(std::fstream& input) {
    std::string number_str;
    std::getline(input, number_str);
    int number;
    try {
        number = std::stoi(number_str);
    } catch(std::exception& e) {
        throw InvalidInput(number_str); 
    }
    return number;
}

void ReadInstruction::execute(MemoryState& mem) {
    switch (mode) {
    case Mode::INMEDIATE:
        throw InvalidRead(to_string());
        break;
    case Mode::DIRECT:
        mem.registers[operand] = read_number(mem.input);
        break;
    case Mode::INDIRECT:
        mem.registers[mem.registers[operand]] = read_number(mem.input);
        break;
    default:
        throw InvalidMode(to_string());
    }
    mem.instruction_counter += 1;
}

std::string ReadInstruction::to_string() {
    return READ_INSTRUCTION_ID + std::string(" ") + mode_to_string(mode) + std::to_string(operand); 
}

void WriteInstruction::execute(MemoryState& mem) {
    switch (mode) {
    case Mode::INMEDIATE:
        mem.output << operand << "\n";
        break;
    case Mode::DIRECT:
        if (operand == ACCUMULATOR_REG) {
            throw InvalidWrite(to_string());
        }
        mem.output << mem.registers[operand] << "\n";
        break;
    case Mode::INDIRECT:
        mem.output << mem.registers[mem.registers[operand]] << "\n";
        break;
    default:
        throw InvalidMode(to_string());
    }
    mem.instruction_counter += 1;
}

std::string WriteInstruction::to_string() {
    return WRITE_INSTRUCTION_ID + std::string(" ") + mode_to_string(mode) + std::to_string(operand); 
}

void JumpInstruction::execute(MemoryState& mem) {
    if (mode == Mode::LABEL) {
        mem.instruction_counter = operand;
    } else {
        throw InvalidMode(to_string());
    }
}

std::string JumpInstruction::to_string() {
    return JUMP_INSTRUCTION_ID + std::string(" ") + std::to_string(operand); 
}

void JGTZInstruction::execute(MemoryState& mem) {
    if (mode == Mode::LABEL) {
        if (mem.registers[ACCUMULATOR_REG] >= 0) {
            mem.instruction_counter = operand;
        } else {
            mem.instruction_counter += 1;
        }
    } else {
        throw InvalidMode(to_string());
    }
}

std::string JGTZInstruction::to_string() {
    return JGTZ_INSTRUCTION_ID + std::string(" ") + std::to_string(operand); 
}

void JZeroInstruction::execute(MemoryState& mem) {
    if (mode == Mode::LABEL) {
        if (mem.registers[ACCUMULATOR_REG] == 0) {
            mem.instruction_counter = operand;
        } else {
            mem.instruction_counter += 1;
        }
    } else {
        throw InvalidMode(to_string());
    }
}

std::string JZeroInstruction::to_string() {
    return JZERO_INSTRUCTION_ID + std::string(" ") + std::to_string(operand); 
}

void HaltInstruction::execute(MemoryState& mem) {
    throw ExecutionEnd();
}

std::string HaltInstruction::to_string() {
    return HALT_INSTRUCTION_ID;
}