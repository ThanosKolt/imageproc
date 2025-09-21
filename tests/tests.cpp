#include <gtest/gtest.h>

#include "filters.hpp"
#include "parser.hpp"
#include "exceptions.hpp"

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
    auto filterCmd = dynamic_cast<FilterCommand*>(cmd.get());
    ASSERT_NE(filterCmd, nullptr);
    ASSERT_EQ(filterCmd->input, "in.png");
    ASSERT_EQ(filterCmd->output, "out.png");
    ASSERT_EQ(filterCmd->filter, "negative");
}

TEST(CliTest, ParseCommandFiltersOption) {
    const char* argv[] = {"imageproc", "--help"};
    auto cmd = parse_command(2, const_cast<char**>(argv));
    auto listCmd = dynamic_cast<HelpCommand*>(cmd.get());
    ASSERT_NE(listCmd, nullptr);
}

TEST(CliTest, ParseCommandInvalidThrows) {
    const char* argv[] = {"imageproc", "in.png"};
    ASSERT_THROW(parse_command(2, const_cast<char**>(argv)), UserException);
}

TEST(CommandTest, FilterCommandInvalidFilterThrows) {
    auto cmd = FilterCommand("in", "out", "uknownFilter");
    ASSERT_THROW(cmd.run(), UserException);
}
