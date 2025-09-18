#include "pixelwindow.hpp"

#include <cmath>

std::optional<Pixel> PixelWindow::at(int dx, int dy) const {
    if (std::abs(dx) > size || std::abs(dy) > size || x + dx <= 0 || x + dx > img.width() ||
        y + dy <= 0 || y + dy > img.height()) {
        return std::nullopt;
    }

    // don't store in struct, recompute for safety in case of img vector reallocating
    const std::uint8_t* center = img.data() + (x + y * img.width()) * 3;
    const std::uint8_t* neighbor = center + (dx + dy * img.width()) * 3;

    return Pixel{neighbor[0], neighbor[1], neighbor[2]};
}