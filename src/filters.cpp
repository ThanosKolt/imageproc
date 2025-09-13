#include "filters.hpp"

#include <iostream>

#include "image.hpp"

void filters::negative(std::uint8_t* data, int width, int height) {
    for (int i = 0; i < width * height * (int)ChannelType::RGB; i++) {
        data[i] = 255 - data[i];
    }
}

void filters::flip_vertical(std::uint8_t* data, int width, int height) {
    const int step = width * 3;
    for (int row = 0; row < height / 2; ++row) {
        for (int col = 0; col < step; ++col) {
            auto& top = data[row * step + col];
            auto& bot = data[(height - 1 - row) * step + col];
            std::swap(top, bot);
        }
    }
}