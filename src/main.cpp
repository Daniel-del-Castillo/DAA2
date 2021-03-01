#include <iostream>
#include "headers/ram.hpp"
#include "headers/ram_builder.hpp"

int main() {
    std::fstream instructions_file("ejemplosRAM/test7.ram", std::ios::in);
    std::fstream input_file("input", std::ios::in);
    std::fstream output_file("output", std::ios::out | std::ios::trunc);
    RAMBuilder builder;
    try {
        builder.read_instructions_from(instructions_file);
    } catch(std::string e) {
        std::cout << "An error ocurred while reading the instructions: " << e << std::endl;
    }
    builder.set_input_stream(input_file);
    builder.set_output_stream(output_file);
    RAM* ram = builder.build();
    instructions_vec instructions = ram->get_instructions();
    for(Instruction* instruction : instructions) {
        std::cout << instruction->to_string() << "\n";
    }

    delete ram;
    return 0;
}