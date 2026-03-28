#include <gtest/gtest.h>
#include <string>
#include "catch2/internal/catch_textflow.hpp"

using Catch::TextFlow::AnsiSkippingString;

// Test normal construction with a simple string (no ANSI codes)
TEST(AnsiSkippingStringTest_1092, ConstructFromConstRef_1092) {
    std::string text = "Hello, World!";
    AnsiSkippingString s(text);
    EXPECT_EQ(s.size(), 13u);
}

TEST(AnsiSkippingStringTest_1092, ConstructFromRvalue_1092) {
    AnsiSkippingString s(std::string("Hello"));
    EXPECT_EQ(s.size(), 5u);
}

// Test empty string
TEST(AnsiSkippingStringTest_1092, EmptyString_1092) {
    AnsiSkippingString s(std::string(""));
    EXPECT_EQ(s.size(), 0u);
}

// Test that begin() == end() for empty string
TEST(AnsiSkippingStringTest_1092, EmptyStringBeginEqualsEnd_1092) {
    AnsiSkippingString s(std::string(""));
    auto it_begin = s.begin();
    auto it_end = s.end();
    EXPECT_TRUE(it_begin == it_end);
}

// Test size of plain text
TEST(AnsiSkippingStringTest_1092, PlainTextSize_1092) {
    AnsiSkippingString s(std::string("abcdef"));
    EXPECT_EQ(s.size(), 6u);
}

// Test string with ANSI escape codes - size should skip ANSI sequences
TEST(AnsiSkippingStringTest_1092, AnsiCodesSkippedInSize_1092) {
    // \033[31m is a typical ANSI color code (red)
    // "Hello" is 5 visible characters
    AnsiSkippingString s(std::string("\033[31mHello\033[0m"));
    EXPECT_EQ(s.size(), 5u);
}

// Test string with multiple ANSI escape codes
TEST(AnsiSkippingStringTest_1092, MultipleAnsiCodes_1092) {
    // \033[1m\033[32m is bold + green, \033[0m is reset
    AnsiSkippingString s(std::string("\033[1m\033[32mHi\033[0m"));
    EXPECT_EQ(s.size(), 2u);
}

// Test iteration over plain text
TEST(AnsiSkippingStringTest_1092, IteratePlainText_1092) {
    AnsiSkippingString s(std::string("abc"));
    size_t count = 0;
    for (auto it = s.begin(); it != s.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 3u);
}

// Test iteration over text with ANSI codes
TEST(AnsiSkippingStringTest_1092, IterateAnsiText_1092) {
    AnsiSkippingString s(std::string("\033[31mab\033[0m"));
    size_t count = 0;
    for (auto it = s.begin(); it != s.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 2u);
}

// Test substring on plain text
TEST(AnsiSkippingStringTest_1092, SubstringPlainText_1092) {
    AnsiSkippingString s(std::string("Hello, World!"));
    auto it_begin = s.begin();
    auto it_end = s.end();
    std::string result = s.substring(it_begin, it_end);
    EXPECT_EQ(result, "Hello, World!");
}

// Test substring on empty string
TEST(AnsiSkippingStringTest_1092, SubstringEmptyString_1092) {
    AnsiSkippingString s(std::string(""));
    std::string result = s.substring(s.begin(), s.end());
    EXPECT_EQ(result, "");
}

// Test substring preserves ANSI codes in output
TEST(AnsiSkippingStringTest_1092, SubstringWithAnsi_1092) {
    AnsiSkippingString s(std::string("\033[31mHello\033[0m"));
    std::string result = s.substring(s.begin(), s.end());
    // The substring should include the ANSI codes since it extracts from the underlying string
    EXPECT_EQ(result, "\033[31mHello\033[0m");
}

// Test single character string
TEST(AnsiSkippingStringTest_1092, SingleCharacter_1092) {
    AnsiSkippingString s(std::string("X"));
    EXPECT_EQ(s.size(), 1u);
    auto it = s.begin();
    EXPECT_FALSE(it == s.end());
}

// Test string with only ANSI codes (no visible text)
TEST(AnsiSkippingStringTest_1092, OnlyAnsiCodes_1092) {
    AnsiSkippingString s(std::string("\033[31m\033[0m"));
    EXPECT_EQ(s.size(), 0u);
}

// Test string with spaces
TEST(AnsiSkippingStringTest_1092, StringWithSpaces_1092) {
    AnsiSkippingString s(std::string("a b c"));
    EXPECT_EQ(s.size(), 5u);
}

// Test long string
TEST(AnsiSkippingStringTest_1092, LongString_1092) {
    std::string longText(1000, 'a');
    AnsiSkippingString s(std::string(longText));
    EXPECT_EQ(s.size(), 1000u);
}

// Test string with embedded escape that isn't a complete ANSI sequence
TEST(AnsiSkippingStringTest_1092, PartialEscapeSequence_1092) {
    // Just ESC without [ - behavior depends on implementation
    AnsiSkippingString s(std::string("\033Hello"));
    // We just verify it doesn't crash and has some size
    EXPECT_GE(s.size(), 0u);
}

// Test string with newlines
TEST(AnsiSkippingStringTest_1092, StringWithNewlines_1092) {
    AnsiSkippingString s(std::string("Hello\nWorld"));
    EXPECT_EQ(s.size(), 11u);
}

// Test string with tabs
TEST(AnsiSkippingStringTest_1092, StringWithTabs_1092) {
    AnsiSkippingString s(std::string("Hello\tWorld"));
    EXPECT_EQ(s.size(), 11u);
}

// Test ANSI codes interspersed with text
TEST(AnsiSkippingStringTest_1092, InterspersedAnsiCodes_1092) {
    // Each letter colored differently
    AnsiSkippingString s(std::string("\033[31mA\033[32mB\033[33mC\033[0m"));
    EXPECT_EQ(s.size(), 3u);
}

// Test substring with partial iteration
TEST(AnsiSkippingStringTest_1092, SubstringPartial_1092) {
    AnsiSkippingString s(std::string("Hello World"));
    auto it_begin = s.begin();
    auto it_mid = s.begin();
    // Advance to some point
    for (int i = 0; i < 5; i++) {
        ++it_mid;
    }
    std::string result = s.substring(it_begin, it_mid);
    EXPECT_EQ(result, "Hello");
}

// Test begin/end consistency - multiple calls return equivalent iterators
TEST(AnsiSkippingStringTest_1092, BeginEndConsistency_1092) {
    AnsiSkippingString s(std::string("Test"));
    auto b1 = s.begin();
    auto b2 = s.begin();
    EXPECT_TRUE(b1 == b2);
    
    auto e1 = s.end();
    auto e2 = s.end();
    EXPECT_TRUE(e1 == e2);
}

// Test ANSI code with complex parameters (e.g., 256-color)
TEST(AnsiSkippingStringTest_1092, ComplexAnsiCode_1092) {
    // 256-color ANSI: \033[38;5;196m
    AnsiSkippingString s(std::string("\033[38;5;196mRed\033[0m"));
    EXPECT_EQ(s.size(), 3u);
}
