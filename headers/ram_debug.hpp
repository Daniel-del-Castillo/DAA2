#pragma once

#include "headers/ram.hpp"
#include <iostream>

class RAMDebug : public RAM {
    using RAM::RAM;
    void execute();
    void show_registers();
    void show_instructions() const;
    void ask_user_for_action();
};