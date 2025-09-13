#include <stb/stb_image.h>
#include <stb/stb_image_write.h>

#include <iostream>
#include <vector>

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "usage: " << argv[0] << " <in> <out>\n";
        return 1;
    }

    int width, height, channels;
    std::uint8_t* in = stbi_load(argv[1], &width, &height, &channels, RGB);
    if (!in) {
        std::cerr << "failed to load\n";
        return 1;
    }

    std::vector<std::uint8_t> out(width * height * RGB);
    for (int i = 0; i < width * height * RGB; i++)
        out[i] = 255 - in[i];  // invert colors

    const int stride = width * 3;
    if (!stbi_write_png(argv[2], width, height, 3, out.data(), stride))
        std::cerr << "failed to write\n";

    stbi_image_free(in);
    return 0;
}