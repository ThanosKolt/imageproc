#include "cli.hpp"

#include <iostream>
#include <map>
#include <stdexcept>
#include <string_view>

#include "filters.hpp"
#include "image.hpp"
#include "io.hpp"

using FilterFn = void (*)(Image&);

const std::map<std::string, FilterFn> filter_table = {{"negative", filters::negative},
                                                      {"flipv", filters::flip_vertical},
                                                      {"grayscale", filters::grayscale}};

std::optional<Command> parse_command(int argc, char** argv) {
    if (argc == 2 && std::string_view(argv[1]) == "--filters") {
        std::cout << "Filter options:\n";
        for (const auto& [name, _] : filter_table) {
            std::cout << "- " << name << "\n";
        }
        return std::nullopt;
    }

    if (argc != 5 || std::string_view(argv[3]) != "--filter") {
        throw std::invalid_argument("Invalid arguments. Usage: " + std::string(argv[0]) +
                                    " <input> <output> --filter <name of filter>\n See "
                                    "--filters for all available filter options.");
    }

    return Command{argv[1], argv[2], argv[4]};
}

void run_command(const Command& cmd) {
    auto it = filter_table.find(cmd.filter);
    if (it == filter_table.end()) {
        throw std::invalid_argument("Unknown filter: " + cmd.filter + "\n");
    }

    auto img = load_image(cmd.input);

    auto filterFn = it->second;
    filterFn(img);

    save_png(cmd.output, img);
    std::cout << cmd.output << " saved!\n";
}
