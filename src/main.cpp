#include <iostream>
#include "headers/ram.hpp"
#include "headers/ram_builder.hpp"

#define DEBUG_OPTION "debug"

void show_usage() {
    std::cout << "Usage:\n";
    std::cout << "./ram_sim ram_program.ram input_tape.in output_tape.out [debug]\n";
    std::cout << "Debug is optional and activates debug mode\n";
}

int main(int argc, char** argv) {
    if (std::string(argv[1]) == "-h") {
        show_usage();
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
        std::cout << "An error ocurred while reading the instructions: " << e.what() << "\n";
        return 2;
    }
    builder.set_input_stream(input_file);
    builder.set_output_stream(output_file);
    RAM* ram;
    if (argc > 4 && std::string(argv[4]) == DEBUG_OPTION) {
        ram = builder.build_debug();
    } else {
        ram = builder.build();
    }
    try {
        int instructions_executed = ram->execute();
        std::cout << "Execution finished succesfully after " << instructions_executed <<  " instructions\n";
    } catch(std::exception& e) {
        std::cout << "An error ocurred during the execution: " << e.what() << "\n";
    }

    delete ram;
    return 0;
}