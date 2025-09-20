#include <stb/stb_image.h>
#include <stb/stb_image_write.h>

#include <iostream>

#include "parser.hpp"
#include "exceptions.hpp"

int main(int argc, char** argv) {
    try {
        auto cmd = parse_command(argc, argv);
        cmd->run();
    } catch (const UserException& e) {
        std::cerr << e.what() << '\n';
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "We're sorry. An unexpected error occured.\n";
        return 1;
    }

    return 0;
}
