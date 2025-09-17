#pragma once
#include <memory>
#include <optional>
#include <string>

#include "command.hpp"

std::unique_ptr<Command> parse_command(int argc, char** argv);