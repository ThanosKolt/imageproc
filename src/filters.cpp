#include "filters.hpp"

#include <cstring>
#include <pixelwindow.hpp>

#include "image.hpp"

namespace filters {
const std::map<std::string, FilterFn>& filter_table() {
    static const std::map<std::string, FilterFn> table = {
        {"negative", negative}, {"flipv", flip_vertical}, {"grayscale", grayscale}, {"blur", blur}};
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

void blur(std::uint8_t* data, int width, int height) {
    // make copy
    std::uint8_t buffer[width * height * 3];
    std::memcpy(buffer, data, width * height * 3);

    // loop?
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            PixelWindow win{data, width, height, x, y, 4};
            int r_sum = 0, g_sum = 0, b_sum = 0;
            int count = 0;
            for (int dx = -win.size; dx <= win.size; dx++) {
                for (int dy = -win.size; dy <= win.size; dy++) {
                    auto pxl = win.at(dx, dy);
                    if (pxl.has_value()) {
                        r_sum += pxl->r;
                        g_sum += pxl->g;
                        b_sum += pxl->b;
                        count++;
                    }
                }
            }
            r_sum = r_sum / count;
            g_sum = g_sum / count;
            b_sum = b_sum / count;
            int index = (y * width + x) * 3;
            buffer[index] = r_sum;
            buffer[index + 1] = g_sum;
            buffer[index + 2] = b_sum;
        }
    }
    std::memcpy(data, buffer, width * height * 3);
}
}  // namespace filters
