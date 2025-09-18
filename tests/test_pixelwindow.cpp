#include <gtest/gtest.h>

#include "pixelwindow.hpp"

Image image_init(int width, int height) {
    Image img{width, height};
    for (int y = 0; y < img.height(); y++) {
        for (int x = 0; x < img.width(); x++) {
            int index = (y * img.width() + x) * 3;
            img.data()[index + 0] = static_cast<uint8_t>(x);      // R = x
            img.data()[index + 1] = static_cast<uint8_t>(y);      // G = y
            img.data()[index + 2] = static_cast<uint8_t>(x + y);  // B = x + y
        }
    }
    return img;
}

TEST(PixelWindowTest, AtReturnsNulloptWhenOutOfBounds) {
    Image img = image_init(6, 6);
    PixelWindow win{img, 0, 0, 2};
    auto result = win.at(-1, -1);

    ASSERT_FALSE(result.has_value());
}

TEST(PixelWindowTest, AtReturnsNulloptWhenLargerThanSize) {
    Image img = image_init(6, 6);
    PixelWindow win{img, 4, 4, 2};
    auto result = win.at(-3, -3);

    ASSERT_FALSE(result.has_value());
}

TEST(PixelWindowTest, AtReturnsNeighborLeftUp) {
    Image img = image_init(6, 6);
    PixelWindow win{img, 4, 4, 2};
    auto result = win.at(-1, -1);

    Pixel expected = {3, 3, 6};
    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(expected.r, result->r);
    ASSERT_EQ(expected.g, result->g);
    ASSERT_EQ(expected.b, result->b);
}

TEST(PixelWindowTest, AtReturnsNeighborLeftDown) {
    Image img = image_init(6, 6);
    PixelWindow win{img, 4, 4, 2};
    auto result = win.at(-1, 1);

    Pixel expected = {3, 5, 8};

    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(expected.r, result->r);
    ASSERT_EQ(expected.g, result->g);
    ASSERT_EQ(expected.b, result->b);
}

TEST(PixelWindowTest, AtReturnsNeighborRightUp) {
    Image img = image_init(6, 6);
    PixelWindow win{img, 4, 4, 2};
    auto result = win.at(1, -1);

    Pixel expected = {5, 3, 8};

    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(expected.r, result->r);
    ASSERT_EQ(expected.g, result->g);
    ASSERT_EQ(expected.b, result->b);
}

TEST(PixelWindowTest, AtReturnsNeighborRightDown) {
    Image img = image_init(6, 6);
    PixelWindow win{img, 4, 4, 2};
    auto result = win.at(1, 1);

    Pixel expected = {5, 5, 10};

    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(expected.r, result->r);
    ASSERT_EQ(expected.g, result->g);
    ASSERT_EQ(expected.b, result->b);
}

TEST(PixelWindowTest, AtReturnsCenterPixel) {
    Image img = image_init(6, 6);
    PixelWindow win{img, 4, 4, 2};
    auto result = win.at(0, 0);

    Pixel expected = {4, 4, 8};

    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(expected.r, result->r);
    ASSERT_EQ(expected.g, result->g);
    ASSERT_EQ(expected.b, result->b);
}