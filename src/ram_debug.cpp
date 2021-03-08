#include "headers/ram_debug.hpp"

void RAMDebug::show_registers() {
    for (int i = 0; i < mem.registers.size(); i++) {
       std::cout << "[" << i << "] => " << mem.registers[i] << "\n"; 
    }
}

void RAMDebug::show_instructions() const {
    for (int i = 0; i < instructions.size(); i++) {
       std::cout << i << " " << instructions[i]->to_string() << "\n"; 
    }
}

void show_help() {
    std::cout << "r: see the registers\n";
    std::cout << "t: trace\n";
    std::cout << "e: execute\n";
    std::cout << "s: disassembly\n";
    std::cout << "i: see input tape\n";
    std::cout << "o: see output tape\n";
    std::cout << "h: help\n";
    std::cout << "x: exit\n";
}

void show_file_content(std::fstream& stream) {
    stream.clear();
    unsigned start_pos = stream.tellg();
    stream.seekg(0, std::ios::beg);
    std::string line;
    while(std::getline(stream, line)) {
        std::cout << line << "\n";
    }
    stream.clear();
    stream.seekg(start_pos, std::ios::beg);
}

bool RAMDebug::ask_user_for_action() {
    std::string input;
    std::cout << "Instruction: ";
    std::cout << instructions[mem.instruction_counter]->to_string() << "\n";
    std::cout << "Instruction counter: " << mem.instruction_counter << "\n";
    std::cout << ">";
    std::getline(std::cin, input);
    switch (input[0]) {
    case 'r':
        show_registers();
        break;
    case 't':
        instructions[mem.instruction_counter]->execute(mem);
        instructions_executed++;
        break;
    case 'e':
        RAM::execute();
        throw ExecutionEnd();
        break;
    case 's':
        show_instructions();
        break;
    case 'i':
        show_file_content(mem.input);
        break;
    case 'o':
        show_file_content(mem.output);
        break;
    case 'h':
        show_help();
        break;
    case 'x':
        return false;
    default:
        std::cout << "Invalid option. Use h to see the help\n";
        break;
    }
    return true;
}

void show_help_after_halt() {
    std::cout << "r: see the registers\n";
    std::cout << "i: see input tape\n";
    std::cout << "o: see output tape\n";
    std::cout << "h: help\n";
    std::cout << "x: exit\n";
}

bool RAMDebug::ask_user_for_action_after_halt() {
    std::string input;
    std::cout << ">";
    std::getline(std::cin, input);
    switch (input[0]) {
    case 'r':
        show_registers();
        break;
    case 's':
        show_instructions();
        break;
    case 'i':
        show_file_content(mem.input);
        break;
    case 'o':
        show_file_content(mem.output);
        break;
    case 'h':
        show_help_after_halt();
        break;
    case 'x':
        return false;
    default:
        std::cout << "Invalid option. Use h to see the help\n";
        break;
    }
    return true;
}

int RAMDebug::execute() {
    show_help();
    try {
        while(ask_user_for_action()) {}
        return instructions_executed;
    } catch(ExecutionEnd& e) {
        std::cout << e.what() << "\n";
    } catch(std::exception& e) {
        std::cout << "An error ocurred during the execution: " << e.what() << "\n";
    }
    std::cout << "You can now see the state of the machine or exit\n"; 
    show_help_after_halt();
    while(ask_user_for_action_after_halt()) {}
    return instructions_executed;
}