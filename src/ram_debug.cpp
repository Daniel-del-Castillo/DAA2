#include "headers/ram_debug.hpp"

void RAMDebug::execute() {
    for(Instruction* instruction: instructions) {
        instruction->execute(mem);
        std::cout << instruction->to_string() << "\n";
    }
    
}