#include "headers/ram_debug.hpp"

void RAMDebug::execute() {
    while(true) {
        instructions[mem.instruction_counter]->execute(mem);
        std::cout << instructions[mem.instruction_counter]->to_string() << "\n";
    }
}