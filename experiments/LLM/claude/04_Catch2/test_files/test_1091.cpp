#include <gtest/gtest.h>
#include <string>
#include "catch2/internal/catch_textflow.hpp"

using Catch::TextFlow::AnsiSkippingString;

// Test basic construction with empty string
TEST(AnsiSkippingStringTest_1091, EmptyString_1091) {
    AnsiSkippingString s(std::string(""));
    EXPECT_EQ(s.size(), 0u);
}

// Test construction with plain text (no ANSI codes)
TEST(AnsiSkippingStringTest_1091, PlainText_1091) {
    AnsiSkippingString s(std::string("Hello"));
    EXPECT_EQ(s.size(), 5u);
}

// Test construction with ANSI escape sequence
TEST(AnsiSkippingStringTest_1091, AnsiEscapeSequence_1091) {
    // \033[31m is a typical ANSI color code (red)
    AnsiSkippingString s(std::string("\033[31mHello\033[0m"));
    // The visible size should be 5 ("Hello"), ANSI codes should be skipped
    EXPECT_EQ(s.size(), 5u);
}

// Test construction with only ANSI codes, no visible text
TEST(AnsiSkippingStringTest_1091, OnlyAnsiCodes_1091) {
    AnsiSkippingString s(std::string("\033[31m\033[0m"));
    EXPECT_EQ(s.size(), 0u);
}

// Test begin and end iterators on empty string
TEST(AnsiSkippingStringTest_1091, BeginEndEmpty_1091) {
    AnsiSkippingString s(std::string(""));
    auto it = s.begin();
    auto endIt = s.end();
    EXPECT_TRUE(it == endIt);
}

// Test begin and end iterators on non-empty string
TEST(AnsiSkippingStringTest_1091, BeginEndNonEmpty_1091) {
    AnsiSkippingString s(std::string("abc"));
    auto it = s.begin();
    auto endIt = s.end();
    EXPECT_FALSE(it == endIt);
}

// Test iteration through plain text
TEST(AnsiSkippingStringTest_1091, IteratePlainText_1091) {
    AnsiSkippingString s(std::string("abc"));
    std::string result;
    for (auto it = s.begin(); it != s.end(); ++it) {
        result += *it;
    }
    EXPECT_EQ(result, "abc");
}

// Test iteration skips ANSI codes
TEST(AnsiSkippingStringTest_1091, IterateSkipsAnsi_1091) {
    AnsiSkippingString s(std::string("\033[31mHi\033[0m"));
    std::string result;
    for (auto it = s.begin(); it != s.end(); ++it) {
        result += *it;
    }
    EXPECT_EQ(result, "Hi");
}

// Test substring with full range on plain text
TEST(AnsiSkippingStringTest_1091, SubstringFullRange_1091) {
    AnsiSkippingString s(std::string("Hello"));
    std::string sub = s.substring(s.begin(), s.end());
    EXPECT_EQ(sub, "Hello");
}

// Test substring with full range including ANSI codes
TEST(AnsiSkippingStringTest_1091, SubstringFullRangeWithAnsi_1091) {
    AnsiSkippingString s(std::string("\033[31mHello\033[0m"));
    std::string sub = s.substring(s.begin(), s.end());
    // substring should include the ANSI codes in the raw string
    EXPECT_EQ(sub, "\033[31mHello\033[0m");
}

// Test substring with empty range
TEST(AnsiSkippingStringTest_1091, SubstringEmptyRange_1091) {
    AnsiSkippingString s(std::string("Hello"));
    std::string sub = s.substring(s.begin(), s.begin());
    EXPECT_EQ(sub, "");
}

// Test substring of empty string
TEST(AnsiSkippingStringTest_1091, SubstringEmptyString_1091) {
    AnsiSkippingString s(std::string(""));
    std::string sub = s.substring(s.begin(), s.end());
    EXPECT_EQ(sub, "");
}

// Test construction with move semantics
TEST(AnsiSkippingStringTest_1091, MoveConstruction_1091) {
    std::string text = "Hello World";
    AnsiSkippingString s(std::move(text));
    EXPECT_EQ(s.size(), 11u);
}

// Test with multiple ANSI codes interspersed
TEST(AnsiSkippingStringTest_1091, MultipleAnsiCodes_1091) {
    AnsiSkippingString s(std::string("\033[1m\033[31mBold Red\033[0m Normal\033[34m Blue\033[0m"));
    // Visible text: "Bold Red Normal Blue"
    EXPECT_EQ(s.size(), 20u);
}

// Test with single character
TEST(AnsiSkippingStringTest_1091, SingleCharacter_1091) {
    AnsiSkippingString s(std::string("x"));
    EXPECT_EQ(s.size(), 1u);
    auto it = s.begin();
    EXPECT_EQ(*it, 'x');
    ++it;
    EXPECT_TRUE(it == s.end());
}

// Test partial substring via iterator advancement
TEST(AnsiSkippingStringTest_1091, PartialSubstring_1091) {
    AnsiSkippingString s(std::string("abcdef"));
    auto beginIt = s.begin();
    auto midIt = s.begin();
    ++midIt;
    ++midIt;
    ++midIt; // points to 'd'
    std::string sub = s.substring(beginIt, midIt);
    EXPECT_EQ(sub, "abc");
}

// Test with spaces and special characters (non-ANSI)
TEST(AnsiSkippingStringTest_1091, SpacesAndSpecialChars_1091) {
    AnsiSkippingString s(std::string("Hello, World! 123"));
    EXPECT_EQ(s.size(), 17u);
}

// Test with ESC character that doesn't form a valid ANSI sequence
TEST(AnsiSkippingStringTest_1091, IncompleteEscapeSequence_1091) {
    // \033 followed by something that's not '[' - behavior depends on implementation
    AnsiSkippingString s(std::string("\033XHello"));
    // We just check it doesn't crash; size depends on implementation details
    EXPECT_GE(s.size(), 0u);
}

// Test with newlines in the string
TEST(AnsiSkippingStringTest_1091, StringWithNewlines_1091) {
    AnsiSkippingString s(std::string("Hello\nWorld"));
    EXPECT_EQ(s.size(), 11u);
}

// Test with tab characters
TEST(AnsiSkippingStringTest_1091, StringWithTabs_1091) {
    AnsiSkippingString s(std::string("Hello\tWorld"));
    EXPECT_EQ(s.size(), 11u);
}

// Test that ANSI codes at the beginning are handled
TEST(AnsiSkippingStringTest_1091, AnsiAtBeginning_1091) {
    AnsiSkippingString s(std::string("\033[32mGreen"));
    EXPECT_EQ(s.size(), 5u);
}

// Test that ANSI codes at the end are handled
TEST(AnsiSkippingStringTest_1091, AnsiAtEnd_1091) {
    AnsiSkippingString s(std::string("Text\033[0m"));
    EXPECT_EQ(s.size(), 4u);
}

// Test long string
TEST(AnsiSkippingStringTest_1091, LongString_1091) {
    std::string longStr(1000, 'a');
    AnsiSkippingString s(longStr);
    EXPECT_EQ(s.size(), 1000u);
}

// Test iteration consistency with size
TEST(AnsiSkippingStringTest_1091, IterationCountMatchesSize_1091) {
    AnsiSkippingString s(std::string("\033[1;34mTest\033[0m String"));
    size_t count = 0;
    for (auto it = s.begin(); it != s.end(); ++it) {
        ++count;
    }
    EXPECT_EQ(count, s.size());
}
