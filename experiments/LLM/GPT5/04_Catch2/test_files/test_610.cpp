// File: tests/AnsiSkippingStringTests_610.cpp
#include <gtest/gtest.h>
#include "catch2/internal/catch_textflow.hpp"

using Catch::TextFlow::AnsiSkippingString;

class AnsiSkippingStringTest_610 : public ::testing::Test {};

// [610] Construct from lvalue string: size() matches input length (no ANSI involved)
TEST_F(AnsiSkippingStringTest_610, ConstructFromLvalue_610) {
    const std::string input = "hello world";
    AnsiSkippingString s(input);

    // Observable API: size() should report the number of characters that the
    // object will expose via its iterators. With plain text (no ANSI), this
    // should match input.size().
    EXPECT_EQ(s.size(), input.size());

    // Also verify full-range substring equals input for plain text.
    EXPECT_EQ(s.substring(s.begin(), s.end()), input);
}

// [610] Construct from rvalue string: size() and substring on full range
TEST_F(AnsiSkippingStringTest_610, ConstructFromRvalue_610) {
    AnsiSkippingString s(std::string("abc"));
    EXPECT_EQ(s.size(), 3u);
    EXPECT_EQ(s.substring(s.begin(), s.end()), std::string("abc"));
}

// [610] Empty string: begin/end are a valid empty range; size() == 0; substring empty
TEST_F(AnsiSkippingStringTest_610, EmptyString_610) {
    const std::string input = "";
    AnsiSkippingString s(input);

    EXPECT_EQ(s.size(), 0u);
    EXPECT_EQ(s.substring(s.begin(), s.end()), std::string());

    // Boundary: substring of [begin, begin) and [end, end) should be empty
    EXPECT_EQ(s.substring(s.begin(), s.begin()), std::string());
    EXPECT_EQ(s.substring(s.end(), s.end()), std::string());
}

// [610] Const-correctness: methods callable on const instance and behave consistently
TEST_F(AnsiSkippingStringTest_610, ConstCorrectness_610) {
    const std::string input = "const check";
    const AnsiSkippingString s(input);

    // All used methods are declared const in the interface.
    EXPECT_EQ(s.size(), input.size());
    EXPECT_EQ(s.substring(s.begin(), s.end()), input);

    // Boundary substrings on const object
    EXPECT_EQ(s.substring(s.begin(), s.begin()), std::string());
    EXPECT_EQ(s.substring(s.end(), s.end()), std::string());
}

// [610] Full-range substring equals input when there are no ANSI sequences
TEST_F(AnsiSkippingStringTest_610, FullRangeSubstringPlainText_610) {
    const std::string input = "plain text only";
    AnsiSkippingString s(input);

    // We only assert behavior visible through the public API.
    EXPECT_EQ(s.substring(s.begin(), s.end()), input);
    EXPECT_EQ(s.size(), input.size());
}
