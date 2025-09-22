#include <stb/stb_image.h>
#include <stb/stb_image_write.h>

#include <fstream>
#include <iostream>
#include <stdexcept>

#include "exceptions.hpp"
#include "parser.hpp"

int main(int argc, char** argv) {
    try {
        auto cmd = parse_command(argc, argv);
        cmd->run();
    } catch (const UserException& e) {
        std::cerr << e.what() << '\n';
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "We're sorry. An unexpected error occured.\n";
        std::ofstream out("imageproc.log", std::ios::app);
        if (out.is_open()) {
            out << e.what() << std::endl;
        }
        return 1;
    }

    return 0;
}
