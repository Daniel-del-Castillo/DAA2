#pragma once

#include <fstream>
#include <unordered_map>
#include "headers/dynamic_vec.hpp"


struct MemoryState {
    unsigned instruction_counter;
    DynamicVec<int> registers;
    std::fstream output;
    std::fstream input;
};