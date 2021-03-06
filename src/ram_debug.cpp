#include "headers/ram_debug.hpp"

void show_help() {
    std::cout << "r: see the registries\n";
    std::cout << "t: trace\n";
    std::cout << "e: execute\n";
    std::cout << "s: disassembly\n";
    std::cout << "i: see input tape\n";
    std::cout << "o: see output tape\n";
    std::cout << "h: help\n";
    std::cout << "x: exit\n";
}

void RAMDebug::ask_user_for_action() {
    std::string input;
    std::cout << "Instruction counter: " << mem.instruction_counter << "\n";
    std::cout << ">";
    std::getline(std::cin, input);
    switch (input[0]) {
    case 't':
        instructions[mem.instruction_counter]->execute(mem);
        break;
    case 'e':
        RAM::execute();
        break;
    case 's':
        std::cout << instructions[mem.instruction_counter]->to_string() << "\n";
        break;
    case 'h':
        show_help();
        break;
    case 'x':
        throw EXECUTION_END;
    default:
        std::cout << "Invalid option. Use h to see the help\n";
        break;
    }
}

void RAMDebug::execute() {
    show_help();
    while(true) {
        ask_user_for_action();
    }
}