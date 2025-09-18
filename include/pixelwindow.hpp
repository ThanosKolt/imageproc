#pragma once
#include <optional>

#include "image.hpp"

struct Pixel {
    std::uint8_t r, g, b;
};

struct PixelWindow {
    const Image& img;
    int x, y;
    int size;

    // returns nullopt when out of bounds
    std::optional<Pixel> at(int dx, int dy) const;
};