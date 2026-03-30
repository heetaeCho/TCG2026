// File: test_ansi_skipping_string_size_35.cpp

#include <gtest/gtest.h>
#include <string>

// Include the header under test
#include "catch2/internal/catch_textflow.hpp"

using Catch::TextFlow::AnsiSkippingString;

// Test fixture kept minimal for clarity and consistency
class AnsiSkippingStringTest_35 : public ::testing::Test {};

// ---- Normal operation -------------------------------------------------------

TEST_F(AnsiSkippingStringTest_35, EmptyString_SizeZero_35) {
    AnsiSkippingString s{std::string{}};
    EXPECT_EQ(s.size(), 0u);
}

TEST_F(AnsiSkippingStringTest_35, PlainText_CountsAllChars_35) {
    AnsiSkippingString s{std::string{"hello"}};
    EXPECT_EQ(s.size(), 5u);
}

// A couple of representative ANSI SGR sequences (e.g., "\x1b[31m" for red, "\x1b[0m" reset)
// are included in the string. We assert that only visible characters are counted.
TEST_F(AnsiSkippingStringTest_35, MixedAnsiAndText_CountsOnlyVisible_35) {
    const std::string withAnsi = "a\x1b[31mb\x1b[0mc";
    AnsiSkippingString s{withAnsi};
    // Expecting only 'a', 'b', 'c' to be counted
    EXPECT_EQ(s.size(), 3u);
}

TEST_F(AnsiSkippingStringTest_35, OnlyAnsiCodes_CountsZeroVisible_35) {
    const std::string onlyAnsi = "\x1b[1m\x1b[31m\x1b[0m";
    AnsiSkippingString s{onlyAnsi};
    EXPECT_EQ(s.size(), 0u);
}

// Start/end with ANSI codes around visible text
TEST_F(AnsiSkippingStringTest_35, SurroundingAnsiCodes_VisibleTextCount_35) {
    const std::string text = "\x1b[1m\x1b[32mXYZ\x1b[0m";
    AnsiSkippingString s{text};
    EXPECT_EQ(s.size(), 3u); // X, Y, Z
}

// Multiple adjacent SGR sequences between characters
TEST_F(AnsiSkippingStringTest_35, RepeatedAnsiBetweenChars_35) {
    const std::string text = "A\x1b[1m\x1b[31m\x1b[4mB\x1b[0mC";
    AnsiSkippingString s{text};
    EXPECT_EQ(s.size(), 3u); // A, B, C
}

// ---- Boundary-ish cases you can observe via the interface -------------------

// Long string with regular interleaved ANSI sequences; verifies correctness at scale
TEST_F(AnsiSkippingStringTest_35, LongStringWithAnsi_MeasuresVisibleOnly_35) {
    std::string txt;
    // Build "A<ansi>B<ansi>C..." 100 times -> 300 visible chars total
    for (int i = 0; i < 100; ++i) {
        txt += "A";
        txt += "\x1b[33m"; // set yellow
        txt += "B";
        txt += "\x1b[0m";  // reset
        txt += "C";
    }
    AnsiSkippingString s{txt};
    EXPECT_EQ(s.size(), 300u);
}

// Move-constructed from rvalue should preserve observable size behavior
TEST_F(AnsiSkippingStringTest_35, MoveConstructed_PreservesVisibleCount_35) {
    std::string src = "\x1b[31mred\x1b[0m+plain";
    // Visible: "red+plain" => 9 characters
    AnsiSkippingString s{std::move(src)};
    EXPECT_EQ(s.size(), 9u);
}
