#pragma once
#include <cstdint>
#include <map>
#include <string>

#include "image.hpp"

namespace filters {
using FilterFn = void (*)(Image&);
const std::map<std::string, FilterFn>& filter_table();

void negative(std::uint8_t* data, int width, int height);
void flip_vertical(std::uint8_t* data, int width, int height);
void grayscale(std::uint8_t* data, int width, int height);
void blur(std::uint8_t* data, int width, int height);
void edge_detect(std::uint8_t* data, int width, int height);

// image adapters
inline void negative(Image& image) {
    negative(image.data(), image.width(), image.height());
}

inline void flip_vertical(Image& image) {
    flip_vertical(image.data(), image.width(), image.height());
}

inline void grayscale(Image& image) {
    grayscale(image.data(), image.width(), image.height());
}

inline void blur(Image& image) {
    blur(image.data(), image.width(), image.height());
}

inline void edge_detect(Image& image) {
    edge_detect(image.data(), image.width(), image.height());
}

}  // namespace filters