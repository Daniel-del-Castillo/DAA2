#pragma once

#include "headers/ram.hpp"
#include <iostream>

class RAMDebug : public RAM {
    using RAM::RAM;
    int execute();
    void show_registers();
    void execute_until_end();
    void show_instructions() const;
    bool ask_user_for_action();
    bool ask_user_for_action_after_halt();
};