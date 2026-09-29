#include "parser/parser.hpp"
#include <sstream>

Command parseCommand(const std::string& input)
{
    std::stringstream ss(input);

    Command command;
    ss >> command.name;

    std::string argument;

    while (ss >> argument) {
        command.arguments.push_back(argument);
    }

    return command;
}