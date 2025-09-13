#include <gtest/gtest.h>

#include "filters.hpp"

TEST(FilterTest, NegativeTest) {
    int width = 2, height = 2;
    std::uint8_t data[]{255, 0, 155, 255, 255, 255, 255, 255, 255, 255, 255, 255};
    std::uint8_t expected[]{0, 255, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    filters::negative(data, width, height);

    for (int i = 0; i < width * height * 3; i++) {
        ASSERT_EQ(data[i], expected[i]);
    }
}

TEST(FilterTest, FlipVerticalTest) {
    int width = 3, height = 3;

    std::uint8_t data[]{1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
                        15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27};

    std::uint8_t expected[]{19, 20, 21, 22, 23, 24, 25, 26, 27, 10, 11, 12, 13, 14,
                            15, 16, 17, 18, 1,  2,  3,  4,  5,  6,  7,  8,  9};

    filters::flip_vertical(data, width, height);

    for (int i = 0; i < width * height * 3; i++) {
        ASSERT_EQ(data[i], expected[i]);
    }
}