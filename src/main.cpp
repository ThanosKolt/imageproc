#include <stb/stb_image.h>
#include <stb/stb_image_write.h>

#include <iostream>
#include <vector>

#include "io.hpp"

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "usage: " << argv[0] << " <in> <out>\n";
        return 1;
    }

    Image original_img = load_image(argv[1]);
    Image inverted_img(original_img.width(), original_img.height());

    for (int i = 0; i < original_img.width() * original_img.height() * (int)ChannelType::RGB; i++) {
        inverted_img.data()[i] = 255 - original_img.data()[i];  // invert colors
    }

    save_png(argv[2], inverted_img);

    return 0;
}