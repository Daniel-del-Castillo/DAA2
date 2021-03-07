#pragma once

#include <vector>
#include "headers/instructions.hpp"
#include "headers/memory_state.hpp"

using instructions_vec = std::vector<Instruction*>;

class RAM {
   protected:
    instructions_vec instructions;
    MemoryState mem;
    
   public:
    RAM(const instructions_vec& instructions, std::fstream& input, std::fstream& output); 
    virtual ~RAM();
    
    virtual int execute();
    const instructions_vec& get_instructions() const;
};