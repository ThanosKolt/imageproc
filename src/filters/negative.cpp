#include "negative.hpp"

#include "image.hpp"

void filters::negative(std::uint8_t* data, int width, int height) {
    for (int i = 0; i < width * height * (int)ChannelType::RGB; i++) {
        data[i] = 255 - data[i];
    }
}