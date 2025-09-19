#include "io.hpp"

#include <stb/stb_image.h>
#include <stb/stb_image_write.h>

#include <stdexcept>

Image load_image(const std::string& path) {
    int width, height, channels;
    std::uint8_t* data = stbi_load(path.c_str(), &width, &height, &channels, (int)ChannelType::RGB);
    if (!data) {
        throw std::runtime_error("failed to load image: " + path);
    }
    Image img(width, height);
    std::copy(data, data + width * height * 3, img.data());
    stbi_image_free(data);
    return img;
}

void save_png(const std::string& path, const Image& img) {
    const int stride = img.width() * 3;
    if (!stbi_write_png(path.c_str(), img.width(), img.height(), (int)ChannelType::RGB, img.data(),
                        stride))
        throw std::runtime_error("failed to save image: " + path);
}
