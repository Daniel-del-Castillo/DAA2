#include <iostream>
#include "headers/ram.hpp"
#include "headers/ram_builder.hpp"

int main(int argc, char** argv) {
    if (std::string(argv[1]) == "-h") {
        std::cout << "Usage:\n";
        std::cout << "./ram_sim ram_program.ram input_tape.in output_tape.out [debug]\n";
        std::cout << "Debug is optional and activates debug mode\n";
        return 0;
    }
    if (argc < 4) {
        std::cout << "Invalid number of arguments. Use -h to see the help";
        return 1;
    }
    std::fstream instructions_file(argv[1], std::ios::in);
    std::fstream input_file(argv[2], std::ios::in);
    std::fstream output_file(argv[3], std::ios::out | std::ios::trunc | std::ios::in);
    RAMBuilder builder;
    try {
        builder.read_instructions_from(instructions_file);
    } catch(std::exception& e) {
        std::cout << "An error ocurred while reading the instructions: " << e.what() << std::endl;
    }
    builder.set_input_stream(input_file);
    builder.set_output_stream(output_file);
    RAM* ram;
    if (argc > 4 && std::string(argv[4]) == "debug") {
        ram = builder.build_debug();
    } else {
        ram = builder.build();
    }
    try {
        ram->execute();
        std::cout << "Execution finished succesfully" << std::endl;
    } catch(std::exception& e) {
        std::cout << "An error ocurred during the execution: " << e.what() << std::endl;
    }

    delete ram;
    return 0;
}