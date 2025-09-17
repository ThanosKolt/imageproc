#pragma once
#include <optional>
#include <string>

struct Command {
    std::string input;
    std::string output;
    std::string filter;
};

std::optional<Command> parse_command(int argc, char** argv);
void run_command(const Command& cmd);