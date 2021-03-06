#include "headers/ram_builder.hpp"

RAMBuilder::RAMBuilder() {
    input_set = false;
    output_set = false;
    instructions_set = false;
}

labels get_labels(lines_vec& lines) {
    std::unordered_map<std::string, int> labels;
    for(int i = 0; i < lines.size(); i++) {
        int index = lines[i].find(LABEL_SYMBOL);
        if (index == std::string::npos) {
            continue;
        }
        labels.insert({lines[i].substr(0, index), i});
        lines[i] = lines[i].substr(index + 1);
    }
    return labels;
}

void remove_spaces(std::string& string) {
    string.erase(std::remove_if(
        string.begin(), 
        string.end(), 
        [](unsigned char x){return std::isspace(x);}
    ), string.end());
}

void remove_comments(std::string& string) {
    int index = string.find(COMMENT_SYMBOL);
    if (index != std::string::npos) {
        string.erase(index);
    }
}

void to_lowercase(std::string& string) {
    std::transform(
        string.begin(), 
        string.end(), 
        string.begin(), 
       [](unsigned char c){ return std::tolower(c); } 
    );
}

lines_vec get_unparsed_instructions(std::fstream& input) {
    std::vector<std::string> unparsed_instructions;
    std::string line;
    while (!input.eof()) {
        std::getline(input, line);
        remove_spaces(line);
        remove_comments(line);
        to_lowercase(line);
        if (!line.empty()) {
            unparsed_instructions.push_back(line);
        }
    }
    return unparsed_instructions;
}

std::pair<Mode, int> parse_operand(std::string line) {
    Mode mode;
    if (line.find(INMEDIATE_MODE_SYMBOL) == 0) {
        mode = Mode::INMEDIATE;
    } else if (line.find(INDIRECT_MODE_SYMBOL) == 0) {
        mode = Mode::INDIRECT;
    } else {
        mode = Mode::DIRECT;
    }
    int operand;
    try {
        if (mode == Mode::DIRECT) {
            operand = std::stoi(line);
        } else {
            operand = std::stoi(line.substr(1));
        }
    } catch (std::exception& e) {
        throw INVALID_OPERAND + line;
    }
    return {mode, operand};
}

int parse_label(std::string label, labels& labels) {
    auto key_value_iter = labels.find(label);
    if (key_value_iter == labels.end()) {
        throw INVALID_LABEL + label;
    }
    return std::get<int>(*key_value_iter);
}

Instruction* parse_instruction(std::string line, labels& labels) {
    Mode mode;
    int operand;
    if (line.find(LOAD_INSTRUCTION_ID) == 0) {
        std::tie(mode, operand) = parse_operand(line.substr(LOAD_INSTRUCTION_ID.size()));
        return new LoadInstruction(operand, mode);
    } else if (line.find(STORE_INSTRUCTION_ID) == 0) {
        std::tie(mode, operand) = parse_operand(line.substr(STORE_INSTRUCTION_ID.size()));
        return new StoreInstruction(operand, mode);
    } else if (line.find(ADD_INSTRUCTION_ID) == 0) {
        std::tie(mode, operand) = parse_operand(line.substr(ADD_INSTRUCTION_ID.size()));
        return new AddInstruction(operand, mode);
    } else if (line.find(SUB_INSTRUCTION_ID) == 0) {
        std::tie(mode, operand) = parse_operand(line.substr(SUB_INSTRUCTION_ID.size()));
        return new SubInstruction(operand, mode);
    } else if (line.find(MULT_INSTRUCTION_ID) == 0) {
        std::tie(mode, operand) = parse_operand(line.substr(MULT_INSTRUCTION_ID.size()));
        return new MultInstruction(operand, mode);
    } else if (line.find(DIV_INSTRUCTION_ID) == 0) {
        std::tie(mode, operand) = parse_operand(line.substr(DIV_INSTRUCTION_ID.size()));
        return new DivInstruction(operand, mode);
    } else if (line.find(READ_INSTRUCTION_ID) == 0) {
        std::tie(mode, operand) = parse_operand(line.substr(READ_INSTRUCTION_ID.size()));
        return new ReadInstruction(operand, mode);
    } else if (line.find(WRITE_INSTRUCTION_ID) == 0) {
        std::tie(mode, operand) = parse_operand(line.substr(WRITE_INSTRUCTION_ID.size()));
        return new WriteInstruction(operand, mode);
    } else if (line.find(JUMP_INSTRUCTION_ID) == 0) {
        operand = parse_label(line.substr(JUMP_INSTRUCTION_ID.size()), labels);
        return new JumpInstruction(operand, Mode::LABEL);
    } else if (line.find(JGTZ_INSTRUCTION_ID) == 0) {
        operand = parse_label(line.substr(JGTZ_INSTRUCTION_ID.size()), labels);
        return new JGTZInstruction(operand, Mode::LABEL);
    } else if (line.find(JZERO_INSTRUCTION_ID) == 0) {
        operand = parse_label(line.substr(JZERO_INSTRUCTION_ID.size()), labels);
        return new JZeroInstruction(operand, Mode::LABEL);
    } else if (line.find(HALT_INSTRUCTION_ID) == 0) {
        return new HaltInstruction(0, Mode::HALT);
    } else {
        throw INVALID_INSTRUCTION + line;
    }
}

instructions_vec parse_instructions(lines_vec& lines, labels& labels) {
    instructions_vec instructions;
    for(const std::string& s : lines) {
        instructions.push_back(parse_instruction(s, labels));
    }
    return instructions;
}

instructions_vec get_instructions_from_file(std::fstream& input) {
    instructions_vec instructions;
    lines_vec lines = get_unparsed_instructions(input);
    input.close();
    labels labels = get_labels(lines);
    return parse_instructions(lines, labels);
}

RAM* RAMBuilder::build() {
    if (!input_set) {
        throw INPUT_NOT_SET;
    } else if (!output_set) {
        throw OUTPUT_NOT_SET;
    } else if (!instructions_set) {
        throw INSTRUCTIONS_NOT_SET;
    }
    input_set = false;
    output_set = false;
    RAM* ram = new RAM(instructions, input, output);
    instructions_set = false;
    instructions = instructions_vec();
    return ram;
}

void RAMBuilder::read_instructions_from(std::fstream& input) {
    if (instructions_set) {
        throw INSTRUCTIONS_ALREADY_SET;
    }
    instructions = get_instructions_from_file(input);
    instructions_set = true;
}

void RAMBuilder::set_input_stream(std::fstream& input) {
    if (input_set) {
        throw INPUT_ALREADY_SET;
    } else {
        this->input.swap(input); 
        input_set = true;
    }
}

void RAMBuilder::set_output_stream(std::fstream& output) {
    if (output_set) {
        throw OUTPUT_ALREADY_SET;
    } else {
        this->output.swap(output); 
        output_set = true;
    }
}