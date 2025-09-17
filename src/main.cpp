#include <stb/stb_image.h>
#include <stb/stb_image_write.h>

#include <iostream>
#include <vector>

#include "cli.hpp"
#include "filters.hpp"
#include "io.hpp"

int main(int argc, char** argv) {
    try {
        auto cmd = parse_command(argc, argv);
        if (cmd.has_value())
            run_command(cmd.value());
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}
