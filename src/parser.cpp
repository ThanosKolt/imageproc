#include "parser.hpp"
#include "exceptions.hpp"
#include <string_view>

std::unique_ptr<Command> parse_command(int argc, char** argv) {
    if (argc == 2 && std::string_view(argv[1]) == "--help") {
        return std::make_unique<HelpCommand>();
    }

    if (argc == 5 && std::string_view(argv[3]) == "--filter") {
        return std::make_unique<FilterCommand>(argv[1], argv[2], argv[4]);
    }

    throw UserException(
        "Invalid arguments. Usage: " + std::string(argv[0]) +
        " <input> <output> --filter <name of filter>\n See "
        "--help for all available filter options.");
}
