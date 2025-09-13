#pragma once
#include <cstdint>
#include <vector>

enum class ChannelType { Grayscale = 1, RGB = 3, RGBA = 4 };

class Image {
  private:
    int m_width;
    int m_height;
    std::vector<std::uint8_t> m_pixels;

  public:
    Image(int width, int height)
        : m_width(width), m_height(height), m_pixels(width * height * (int)ChannelType::RGB) {}

    int width() const noexcept {
        return m_width;
    }

    int height() const noexcept {
        return m_height;
    }

    std::uint8_t* data() {
        return m_pixels.data();
    }

    const std::uint8_t* data() const {
        return m_pixels.data();
    }
};