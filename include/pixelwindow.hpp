#pragma once
#include <optional>

#include "image.hpp"

struct Pixel {
    std::uint8_t r, g, b;
};

struct PixelWindow {
    const std::uint8_t* data;
    int width, height;
    int x, y;
    int size;

    PixelWindow(const std::uint8_t* data, int width, int height, int x, int y, int size)
        : data(data), width(width), height(height), x(x), y(y), size(size) {}

    PixelWindow(const Image& img, int x, int y, int size)
        : data(img.data()), width(img.width()), height(img.height()), x(x), y(y), size(size) {}

    // returns nullopt when out of bounds
    std::optional<Pixel> at(int dx, int dy) const;
};