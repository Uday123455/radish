#pragma once

#include <string>
#include <vector>

struct Command {
    std::string name;
    std::vector<std::string> arguments;
};

Command parseCommand(const std::string& input);