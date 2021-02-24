#pragma once

#include <fstream>
#include <unordered_map>

using Registers = std::unordered_map<int, int>;

struct MemoryState {
    unsigned instruction_counter;
    Registers registers;
    std::fstream output;
    std::fstream input;
};