#pragma once

#include <vector>
#include "headers/instructions.hpp"
#include "headers/memory_state.hpp"

class RAMMachine {
    std::vector<Instruction*> instructions;
    MemoryState mem;
};