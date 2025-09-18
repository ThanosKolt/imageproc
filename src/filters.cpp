#include "filters.hpp"

#include "image.hpp"

namespace filters {
const std::map<std::string, FilterFn>& filter_table() {
    static const std::map<std::string, FilterFn> table = {
        {"negative", negative}, {"flipv", flip_vertical}, {"grayscale", grayscale}};
    return table;
}

void negative(std::uint8_t* data, int width, int height) {
    const int channels = static_cast<int>(ChannelType::RGB);
    for (int i = 0; i < width * height * channels; i++) {
        data[i] = 255 - data[i];
    }
}

void flip_vertical(std::uint8_t* data, int width, int height) {
    const int step = width * 3;
    for (int row = 0; row < height / 2; ++row) {
        for (int col = 0; col < step; ++col) {
            auto& top = data[row * step + col];
            auto& bot = data[(height - 1 - row) * step + col];
            std::swap(top, bot);
        }
    }
}

void grayscale(std::uint8_t* data, int width, int height) {
    for (int i = 0; i < width * height * 3; i += 3) {
        // Grayscale Value = (0.299 * Red) + (0.587 * Green) + (0.114 * Blue
        auto gray = 0.299 * data[i] + 0.587 * data[i + 1] + 0.114 * data[i + 2];
        data[i] = gray;
        data[i + 1] = gray;
        data[i + 2] = gray;
    }
}
}
