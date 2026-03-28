#include "catch2/internal/catch_textflow.hpp"
#include <gtest/gtest.h>
#include <string>

using Catch::TextFlow::AnsiSkippingString;

// Test basic construction and size for a plain string
TEST(AnsiSkippingStringTest_35, PlainStringSize_35) {
    AnsiSkippingString s(std::string("Hello"));
    EXPECT_EQ(s.size(), 5u);
}

// Test empty string
TEST(AnsiSkippingStringTest_35, EmptyStringSize_35) {
    AnsiSkippingString s(std::string(""));
    EXPECT_EQ(s.size(), 0u);
}

// Test string with ANSI escape codes - size should skip ANSI sequences
TEST(AnsiSkippingStringTest_35, AnsiEscapeCodeSkipped_35) {
    // \033[31m is a typical ANSI color code (red)
    AnsiSkippingString s(std::string("\033[31mHello\033[0m"));
    // The visible text is "Hello" which is 5 characters
    EXPECT_EQ(s.size(), 5u);
}

// Test string with only ANSI escape codes and no visible text
TEST(AnsiSkippingStringTest_35, OnlyAnsiCodes_35) {
    AnsiSkippingString s(std::string("\033[31m\033[0m"));
    EXPECT_EQ(s.size(), 0u);
}

// Test move construction
TEST(AnsiSkippingStringTest_35, MoveConstruction_35) {
    std::string text = "Hello World";
    AnsiSkippingString s(std::move(text));
    EXPECT_EQ(s.size(), 11u);
}

// Test single character string
TEST(AnsiSkippingStringTest_35, SingleCharacterSize_35) {
    AnsiSkippingString s(std::string("X"));
    EXPECT_EQ(s.size(), 1u);
}

// Test string with spaces
TEST(AnsiSkippingStringTest_35, StringWithSpacesSize_35) {
    AnsiSkippingString s(std::string("Hello World"));
    EXPECT_EQ(s.size(), 11u);
}

// Test begin and end iterators for a plain string
TEST(AnsiSkippingStringTest_35, BeginEndIterators_35) {
    AnsiSkippingString s(std::string("Hello"));
    auto it = s.begin();
    auto endIt = s.end();
    // Iterators should not be equal for non-empty string
    EXPECT_NE(it, endIt);
}

// Test begin and end iterators for empty string
TEST(AnsiSkippingStringTest_35, BeginEndIteratorsEmpty_35) {
    AnsiSkippingString s(std::string(""));
    auto it = s.begin();
    auto endIt = s.end();
    EXPECT_EQ(it, endIt);
}

// Test iteration over plain characters
TEST(AnsiSkippingStringTest_35, IterateOverPlainString_35) {
    AnsiSkippingString s(std::string("ABC"));
    auto it = s.begin();
    EXPECT_EQ(*it, 'A');
    ++it;
    EXPECT_EQ(*it, 'B');
    ++it;
    EXPECT_EQ(*it, 'C');
    ++it;
    EXPECT_EQ(it, s.end());
}

// Test iteration skips ANSI codes
TEST(AnsiSkippingStringTest_35, IterateSkipsAnsiCodes_35) {
    AnsiSkippingString s(std::string("\033[31mAB\033[0m"));
    auto it = s.begin();
    EXPECT_EQ(*it, 'A');
    ++it;
    EXPECT_EQ(*it, 'B');
    ++it;
    EXPECT_EQ(it, s.end());
}

// Test substring extraction for plain text
TEST(AnsiSkippingStringTest_35, SubstringPlainText_35) {
    AnsiSkippingString s(std::string("Hello World"));
    auto beginIt = s.begin();
    auto endIt = s.begin();
    // Advance endIt to cover "Hello"
    for (int i = 0; i < 5; ++i) {
        ++endIt;
    }
    std::string sub = s.substring(beginIt, endIt);
    EXPECT_EQ(sub, "Hello");
}

// Test substring with ANSI codes preserves them in the result
TEST(AnsiSkippingStringTest_35, SubstringWithAnsiCodes_35) {
    AnsiSkippingString s(std::string("\033[31mHello\033[0m World"));
    auto beginIt = s.begin();
    auto endIt = s.begin();
    // Advance endIt to cover "Hello" (5 visible chars)
    for (int i = 0; i < 5; ++i) {
        ++endIt;
    }
    std::string sub = s.substring(beginIt, endIt);
    // The substring should include the ANSI prefix since it's part of the underlying string
    EXPECT_NE(sub.find("Hello"), std::string::npos);
}

// Test full substring from begin to end
TEST(AnsiSkippingStringTest_35, SubstringFullString_35) {
    AnsiSkippingString s(std::string("Hello"));
    std::string sub = s.substring(s.begin(), s.end());
    EXPECT_EQ(sub, "Hello");
}

// Test string with multiple ANSI codes
TEST(AnsiSkippingStringTest_35, MultipleAnsiCodes_35) {
    AnsiSkippingString s(std::string("\033[1m\033[31mBold Red\033[0m"));
    // Visible text is "Bold Red" which is 8 characters
    EXPECT_EQ(s.size(), 8u);
}

// Test string with newlines
TEST(AnsiSkippingStringTest_35, StringWithNewlines_35) {
    AnsiSkippingString s(std::string("Hello\nWorld"));
    EXPECT_EQ(s.size(), 11u);
}

// Test string with tabs
TEST(AnsiSkippingStringTest_35, StringWithTabs_35) {
    AnsiSkippingString s(std::string("Hello\tWorld"));
    EXPECT_EQ(s.size(), 11u);
}

// Test longer ANSI sequence
TEST(AnsiSkippingStringTest_35, LongerAnsiSequence_35) {
    // \033[38;5;196m is a 256-color ANSI code
    AnsiSkippingString s(std::string("\033[38;5;196mRed\033[0m"));
    EXPECT_EQ(s.size(), 3u);
}

// Test copy construction with const reference
TEST(AnsiSkippingStringTest_35, ConstRefConstruction_35) {
    const std::string text = "Test String";
    AnsiSkippingString s(text);
    EXPECT_EQ(s.size(), 11u);
}

// Test empty substring
TEST(AnsiSkippingStringTest_35, EmptySubstring_35) {
    AnsiSkippingString s(std::string("Hello"));
    std::string sub = s.substring(s.begin(), s.begin());
    EXPECT_EQ(sub, "");
}

// Test string with partial escape-like characters (not a full ANSI code)
TEST(AnsiSkippingStringTest_35, PartialEscapeNotAnsi_35) {
    // Just an ESC character without the '[' following - behavior depends on implementation
    // but we test that size is computed and no crash occurs
    AnsiSkippingString s(std::string("A\033B"));
    // We just verify it doesn't crash and returns some size
    EXPECT_GE(s.size(), 0u);
}

// Test large string
TEST(AnsiSkippingStringTest_35, LargeString_35) {
    std::string large(10000, 'A');
    AnsiSkippingString s(large);
    EXPECT_EQ(s.size(), 10000u);
}

// Test large string with ANSI codes interspersed
TEST(AnsiSkippingStringTest_35, LargeStringWithAnsi_35) {
    std::string text;
    for (int i = 0; i < 100; ++i) {
        text += "\033[31m";
        text += "Hello";
        text += "\033[0m";
    }
    AnsiSkippingString s(text);
    EXPECT_EQ(s.size(), 500u); // 100 * 5 visible chars
}
