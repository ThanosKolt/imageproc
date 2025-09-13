#include <gtest/gtest.h>

TEST(BasicTest, TruthTest) {
    EXPECT_TRUE(true);
    EXPECT_EQ(2 + 2, 4);
}

TEST(BasicTest, StringTest) {
    std::string hello = "Hello";
    EXPECT_EQ(hello + " World", "Hello World");
}
