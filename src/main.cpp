#include <stb/stb_image.h>
#include <stb/stb_image_write.h>

#include <iostream>
#include <vector>

#include "filters.hpp"
#include "io.hpp"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "usage: " << argv[0] << " <in> <out>\n";
        return 1;
    }

    Image img = load_image(argv[1]);

    filters::flip_vertical(img);
    save_png("result1.png", img);

    filters::negative(img);
    save_png("result2.png", img);

    filters::grayscale(img);
    save_png("result0.png", img);

    return 0;
}
