#pragma once

#include <fstream>
#include <string>
#include <unordered_map>
#include <cctype>
#include <algorithm>
#include <utility>
#include "headers/ram.hpp"
#include "headers/ram_debug.hpp"

class InputAlreadySet: public std::exception {
   public: 
    const char* what() const noexcept;
};

class OutputAlreadySet: public std::exception {
   public: 
    const char* what() const noexcept;
};

class InstructionsAlreadySet: public std::exception {
   public: 
    const char* what() const noexcept;
};

class InputNotSet: public std::exception {
   public: 
    const char* what() const noexcept;
};

class OutputNotSet: public std::exception {
   public: 
    const char* what() const noexcept;
};

class InstructionsNotSet: public std::exception {
   public: 
    const char* what() const noexcept;
};

class InvalidInstructionPart: public std::exception {
   protected: 
    mutable std::string message;
   public: 
    InvalidInstructionPart(const std::string& s);
};

class InvalidOperation: public InvalidInstructionPart {
    using InvalidInstructionPart::InvalidInstructionPart;
   public: 
    const char* what() const noexcept;
};

class InvalidLabel: public InvalidInstructionPart {
    using InvalidInstructionPart::InvalidInstructionPart;
   public: 
    const char* what() const noexcept;
};

class InvalidOperand: public InvalidInstructionPart {
    using InvalidInstructionPart::InvalidInstructionPart;
   public: 
    const char* what() const noexcept;
};

#define LABEL_SYMBOL ":"
#define COMMENT_SYMBOL ";"

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
    RAMDebug* build_debug();
    void read_instructions_from(std::fstream& input); 
    void set_input_stream(std::fstream& input);
    void set_output_stream(std::fstream& input);
};
