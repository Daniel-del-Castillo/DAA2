#include "headers/ram.hpp"

RAM::RAM(instructions_vec& instructions, std::fstream& input, std::fstream& output) {
    this->instructions = instructions;
    mem.input.swap(input);
    mem.output.swap(output);
    mem.instruction_counter = 0;
}

RAM::~RAM() {
    for(Instruction* instruction : instructions) {
        delete instruction;
    }
    mem.input.close();
    mem.output.close();
}

instructions_vec& RAM::get_instructions() {
    return instructions;
}