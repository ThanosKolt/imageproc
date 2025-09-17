#include <gtest/gtest.h>

#include "cli.hpp"
#include "filters.hpp"

TEST(FilterTest, NegativeTest) {
    int width = 1, height = 1;
    std::uint8_t data[]{255, 0, 155};
    std::uint8_t expected[]{0, 255, 100};

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

TEST(FilterTest, GrayscaleTest) {
    int width = 1, height = 1;

    std::uint8_t data[]{10, 10, 10};

    // multipliers: 0.299, 0.587, 0.114;
    std::uint8_t expected = 3 + 6 + 1;

    filters::grayscale(data, width, height);

    for (int i = 0; i < width * height * 3; i++) {
        ASSERT_EQ(data[i], expected);
    }
}

TEST(CliTest, ParseCommandValid) {
    const char* argv[] = {"imageproc", "in.png", "out.png", "--filter", "negative"};
    auto cmd = parse_command(5, const_cast<char**>(argv));
    ASSERT_TRUE(cmd.has_value());
    ASSERT_EQ(cmd->input, "in.png");
    ASSERT_EQ(cmd->output, "out.png");
    ASSERT_EQ(cmd->filter, "negative");
}

TEST(CliTest, ParseCommandFiltersOption) {
    const char* argv[] = {"imageproc", "--filters"};
    auto cmd = parse_command(2, const_cast<char**>(argv));
    ASSERT_FALSE(cmd.has_value());
}

TEST(CliTest, ParseCommandInvalidThrows) {
    const char* argv[] = {"imageproc", "in.png"};
    ASSERT_THROW(parse_command(2, const_cast<char**>(argv)), std::invalid_argument);
}

// run_command test for unknown filter
TEST(CliTest, RunCommandUnknownFilter) {
    Command cmd{"in.png", "out.png", "asdfasdfa"};
    ASSERT_THROW(run_command(cmd), std::invalid_argument);
}