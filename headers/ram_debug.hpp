#pragma once

#include "headers/ram.hpp"
#include <iostream>

class RAMDebug : public RAM {
    using RAM::RAM;
    void execute();
    void ask_user_for_action();
};