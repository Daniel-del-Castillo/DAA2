#include <iostream>
#include "headers/ram.hpp"
#include "headers/ram_builder.hpp"

int main() {
    std::fstream instructions_file("ejemplosRAM/test1.ram", std::fstream::in);
    std::fstream input_file("input", std::fstream::in);
    std::fstream output_file("output", std::fstream::out);
    RAMBuilder builder;
    try {
        builder.read_instructions_from(instructions_file);
        builder.set_input_stream(input_file);
        builder.set_output_stream(output_file);
        RAM* ram = builder.build();
        instructions_vec instructions = ram->get_instructions();
        for(Instruction* instruction : instructions) {
            std::cout << instruction->to_string() << "\n";
        }

        delete ram;
    } catch(std::string e) {
        std::cout << "An error ocurred while reading the instructions: " << e << std::endl;
    }
    return 0;
}