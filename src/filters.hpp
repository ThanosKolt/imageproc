#pragma once
#include <cstdint>

namespace filters {
void negative(std::uint8_t* data, int width, int height);
void flip_vertical(std::uint8_t* data, int width, int height);
}