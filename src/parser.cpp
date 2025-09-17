#include "parser.hpp"

#include <iostream>
#include <map>
#include <stdexcept>
#include <string_view>

#include "filters.hpp"
#include "image.hpp"
#include "io.hpp"

std::unique_ptr<Command> parse_command(int argc, char** argv) {
    if (argc == 2 && std::string_view(argv[1]) == "--filters") {
        return std::make_unique<ListCommand>();
    }

    if (argc == 5 && std::string_view(argv[3]) == "--filter") {
        return std::make_unique<FilterCommand>(argv[1], argv[2], argv[4]);
    }

    throw std::invalid_argument("Invalid arguments. Usage: " + std::string(argv[0]) +
                                " <input> <output> --filter <name of filter>\n See "
                                "--filters for all available filter options.");
}