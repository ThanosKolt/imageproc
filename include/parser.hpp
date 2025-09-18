#pragma once
#include <memory>

#include "command.hpp"

std::unique_ptr<Command> parse_command(int argc, char** argv);
