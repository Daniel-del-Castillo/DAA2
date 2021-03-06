#pragma once

#include <vector>
#include <iostream>
#include "headers/instructions.hpp"
#include "headers/memory_state.hpp"

using instructions_vec = std::vector<Instruction*>;

class RAM {
    instructions_vec instructions;
    MemoryState mem;
    
   public:
    RAM(instructions_vec& instructions, std::fstream& input, std::fstream& output); 
    ~RAM();
    
    void execute();
    void execute_debug();
    instructions_vec& get_instructions();
};