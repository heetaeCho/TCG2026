// File: tests/AnsiSkippingString_substring_612.tests.cpp
#include <gtest/gtest.h>
#include <string>

// Headers under test
#include "catch2/internal/catch_textflow.hpp"

using Catch::TextFlow::AnsiSkippingString;

class AnsiSkippingStringTest_612 : public ::testing::Test {};

// [Normal] Full range returns the original text
TEST_F(AnsiSkippingStringTest_612, SubstringFullRange_ReturnsOriginal_612) {
    const std::string text = "Hello, world!";
    AnsiSkippingString s(text);

    auto sub = s.substring(s.begin(), s.end());
    EXPECT_EQ(sub, text);
}

// [Boundary] Empty range (begin == end) yields empty string at start
TEST_F(AnsiSkippingStringTest_612, SubstringEmptyAtStart_612) {
    const std::string text = "abcdef";
    AnsiSkippingString s(text);

    auto b = s.begin();
    auto e = b; // same position
    auto sub = s.substring(b, e);
    EXPECT_TRUE(sub.empty());
}

// [Boundary] Empty range (begin == end) yields empty string in the middle
TEST_F(AnsiSkippingStringTest_612, SubstringEmptyInMiddle_612) {
    const std::string text = "abcdef";
    AnsiSkippingString s(text);

    auto it = s.begin();
    ++it; ++it; ++it; // position after 'c'
    auto sub = s.substring(it, it);
    EXPECT_TRUE(sub.empty());
}

// [Normal] Substring from the beginning to one past the first character
TEST_F(AnsiSkippingStringTest_612, SubstringFirstChar_612) {
    const std::string text = "xyz";
    AnsiSkippingString s(text);

    auto b = s.begin();
    auto e = b; ++e; // advance by one
    auto sub = s.substring(b, e);
    EXPECT_EQ(sub, std::string("x"));
}

// [Normal] Substring from a middle iterator to end
TEST_F(AnsiSkippingStringTest_612, SubstringFromMiddleToEnd_612) {
    const std::string text = "substring-test";
    AnsiSkippingString s(text);

    auto mid = s.begin();
    // Advance to position 3 (after 's','u','b'), expecting "string-test"
    ++mid; ++mid; ++mid;
    auto sub = s.substring(mid, s.end());
    EXPECT_EQ(sub, std::string("string-test"));
}

// [Boundary] Last character using end().oneBefore() to end()
TEST_F(AnsiSkippingStringTest_612, SubstringLastChar_UsingOneBefore_612) {
    const std::string text = "edge";
    AnsiSkippingString s(text);

    auto last = s.end().oneBefore();
    auto sub = s.substring(last, s.end());
    EXPECT_EQ(sub, std::string("e"));
}

// [Construction] Works with rvalue constructor for full-range substring
TEST_F(AnsiSkippingStringTest_612, RvalueConstructionFullSubstring_612) {
    AnsiSkippingString s(std::string("move-ok"));
    auto sub = s.substring(s.begin(), s.end());
    EXPECT_EQ(sub, std::string("move-ok"));
}
