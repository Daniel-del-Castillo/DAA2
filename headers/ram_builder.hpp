#pragma once

#include <fstream>
#include <string>
#include <unordered_map>
#include <cctype>
#include <algorithm>
#include <utility>
#include "headers/ram.hpp"

#define INPUT_ALREADY_SET std::string("Input stream was already set")
#define OUTPUT_ALREADY_SET std::string("Output stream was already set")
#define INSTRUCTIONS_ALREADY_SET std::string("Instructions were already set")
#define INPUT_NOT_SET std::string("Input stream wasn't set")
#define OUTPUT_NOT_SET std::string("Output stream wasn't set")
#define INSTRUCTIONS_NOT_SET std::string("Instructions weren't set")
#define INVALID_INSTRUCTION std::string("INVALID INSTRUCTION: ")
#define INVALID_LABEL std::string("INVALID LABEL: ")
#define INVALID_OPERAND std::string("INVALID OPERAND: ")
#define LOAD_INSTRUCTION_ID std::string("load")
#define STORE_INSTRUCTION_ID std::string("store")
#define ADD_INSTRUCTION_ID std::string("add")
#define SUB_INSTRUCTION_ID std::string("sub")
#define MULT_INSTRUCTION_ID std::string("mult")
#define DIV_INSTRUCTION_ID std::string("div")
#define READ_INSTRUCTION_ID std::string("read")
#define WRITE_INSTRUCTION_ID std::string("write")
#define JUMP_INSTRUCTION_ID std::string("jump")
#define JGTZ_INSTRUCTION_ID std::string("jgtz")
#define JZERO_INSTRUCTION_ID std::string("jzero")
#define HALT_INSTRUCTION_ID std::string("halt")

using lines_vec = std::vector<std::string>;
using labels = std::unordered_map<std::string, int>;

class RAMBuilder {
    bool input_set;
    bool output_set;
    bool instructions_set;
    instructions_vec instructions;
    std::fstream input;
    std::fstream output;

   public:
    RAMBuilder();
    RAM* build();
    void read_instructions_from(std::fstream& input); 
    void set_input_stream(std::fstream& input);
    void set_output_stream(std::fstream& input);
};