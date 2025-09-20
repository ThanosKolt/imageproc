#include "command.hpp"

#include <iostream>

#include "filters.hpp"
#include "exceptions.hpp"
#include "io.hpp"

void FilterCommand::run() const {
    auto it = filters::filter_table().find(filter);
    if (it == filters::filter_table().end()) {
        throw UserException("Unknown filter: " + filter + "\nSee --help\n");
    }

    auto img = load_image(input);

    auto filterFn = it->second;
    filterFn(img);

    save_png(output, img);
    std::cout << output << " saved!\n";
}

void HelpCommand::run() const {
    std::cout << 
    "Usage: ./imageproc <input> <output> --filter <name of filter>\n"
    "Filter options:\n";
    for (const auto& [name, _] : filters::filter_table()) {
        std::cout << "- " << name << "\n";
    }
}
