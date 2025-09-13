#pragma once
#include <string>

#include "image.hpp"

Image load_image(const std::string& path);
void save_png(const std::string& path, const Image& img);