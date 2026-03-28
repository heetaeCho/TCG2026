#include <gtest/gtest.h>
#include <string>
#include "catch2/internal/catch_textflow.hpp"

using Catch::TextFlow::AnsiSkippingString;

// Test normal construction with a regular string
TEST(AnsiSkippingStringTest_611, ConstructFromConstRef_611) {
    std::string text = "Hello, World!";
    AnsiSkippingString ansiStr(text);
    EXPECT_EQ(ansiStr.size(), 13u);
}

// Test construction with move semantics
TEST(AnsiSkippingStringTest_611, ConstructFromRvalue_611) {
    AnsiSkippingString ansiStr(std::string("Hello"));
    EXPECT_EQ(ansiStr.size(), 5u);
}

// Test empty string
TEST(AnsiSkippingStringTest_611, EmptyString_611) {
    AnsiSkippingString ansiStr(std::string(""));
    EXPECT_EQ(ansiStr.size(), 0u);
}

// Test that begin and end iterators are equal for empty string
TEST(AnsiSkippingStringTest_611, EmptyStringBeginEqualsEnd_611) {
    AnsiSkippingString ansiStr(std::string(""));
    auto it_begin = ansiStr.begin();
    auto it_end = ansiStr.end();
    EXPECT_TRUE(it_begin == it_end);
}

// Test that begin and end iterators are not equal for non-empty string
TEST(AnsiSkippingStringTest_611, NonEmptyStringBeginNotEqualsEnd_611) {
    AnsiSkippingString ansiStr(std::string("abc"));
    auto it_begin = ansiStr.begin();
    auto it_end = ansiStr.end();
    EXPECT_FALSE(it_begin == it_end);
}

// Test size with plain text (no ANSI codes)
TEST(AnsiSkippingStringTest_611, SizePlainText_611) {
    AnsiSkippingString ansiStr(std::string("Test string"));
    EXPECT_EQ(ansiStr.size(), 11u);
}

// Test size with ANSI escape codes - they should be skipped
TEST(AnsiSkippingStringTest_611, SizeWithAnsiCodes_611) {
    // ANSI escape: \033[31m (red color) and \033[0m (reset)
    std::string text = "\033[31mHello\033[0m";
    AnsiSkippingString ansiStr(text);
    // The visible text is "Hello" which is 5 characters
    EXPECT_EQ(ansiStr.size(), 5u);
}

// Test size with multiple ANSI codes
TEST(AnsiSkippingStringTest_611, SizeWithMultipleAnsiCodes_611) {
    std::string text = "\033[1m\033[31mBold Red\033[0m";
    AnsiSkippingString ansiStr(text);
    // Visible text: "Bold Red" = 8 characters
    EXPECT_EQ(ansiStr.size(), 8u);
}

// Test substring extraction on plain text
TEST(AnsiSkippingStringTest_611, SubstringPlainText_611) {
    AnsiSkippingString ansiStr(std::string("Hello, World!"));
    auto it_begin = ansiStr.begin();
    auto it_end = ansiStr.end();
    std::string result = ansiStr.substring(it_begin, it_end);
    EXPECT_EQ(result, "Hello, World!");
}

// Test substring with begin == end returns empty
TEST(AnsiSkippingStringTest_611, SubstringEmptyRange_611) {
    AnsiSkippingString ansiStr(std::string("Hello"));
    auto it_begin = ansiStr.begin();
    std::string result = ansiStr.substring(it_begin, it_begin);
    EXPECT_EQ(result, "");
}

// Test iteration through plain text characters
TEST(AnsiSkippingStringTest_611, IteratePlainText_611) {
    AnsiSkippingString ansiStr(std::string("abc"));
    auto it = ansiStr.begin();
    auto end = ansiStr.end();
    
    std::string collected;
    while (it != end) {
        collected += *it;
        ++it;
    }
    EXPECT_EQ(collected, "abc");
}

// Test iteration skips ANSI escape sequences
TEST(AnsiSkippingStringTest_611, IterateSkipsAnsiCodes_611) {
    std::string text = "\033[31mabc\033[0m";
    AnsiSkippingString ansiStr(text);
    
    std::string collected;
    auto it = ansiStr.begin();
    auto end = ansiStr.end();
    while (it != end) {
        collected += *it;
        ++it;
    }
    EXPECT_EQ(collected, "abc");
}

// Test with only ANSI codes (no visible text)
TEST(AnsiSkippingStringTest_611, OnlyAnsiCodes_611) {
    std::string text = "\033[31m\033[0m";
    AnsiSkippingString ansiStr(text);
    EXPECT_EQ(ansiStr.size(), 0u);
}

// Test single character string
TEST(AnsiSkippingStringTest_611, SingleCharacter_611) {
    AnsiSkippingString ansiStr(std::string("X"));
    EXPECT_EQ(ansiStr.size(), 1u);
    
    auto it = ansiStr.begin();
    EXPECT_EQ(*it, 'X');
    ++it;
    EXPECT_TRUE(it == ansiStr.end());
}

// Test with ANSI code at beginning
TEST(AnsiSkippingStringTest_611, AnsiAtBeginning_611) {
    std::string text = "\033[32mGreen";
    AnsiSkippingString ansiStr(text);
    EXPECT_EQ(ansiStr.size(), 5u);
}

// Test with ANSI code at end
TEST(AnsiSkippingStringTest_611, AnsiAtEnd_611) {
    std::string text = "Text\033[0m";
    AnsiSkippingString ansiStr(text);
    EXPECT_EQ(ansiStr.size(), 4u);
}

// Test with spaces and special characters
TEST(AnsiSkippingStringTest_611, SpecialCharacters_611) {
    AnsiSkippingString ansiStr(std::string("a b\tc\nd"));
    // All these are non-ANSI characters, so size should count them all
    EXPECT_EQ(ansiStr.size(), 7u);
}

// Test substring preserves ANSI codes in output
TEST(AnsiSkippingStringTest_611, SubstringWithAnsiCodes_611) {
    std::string text = "\033[31mHello\033[0m World";
    AnsiSkippingString ansiStr(text);
    auto it_begin = ansiStr.begin();
    auto it_end = ansiStr.end();
    std::string result = ansiStr.substring(it_begin, it_end);
    // The substring should include the original text with ANSI codes
    EXPECT_EQ(result, text);
}

// Test long string
TEST(AnsiSkippingStringTest_611, LongString_611) {
    std::string longText(1000, 'a');
    AnsiSkippingString ansiStr(longText);
    EXPECT_EQ(ansiStr.size(), 1000u);
}

// Test partial iteration and substring
TEST(AnsiSkippingStringTest_611, PartialSubstring_611) {
    AnsiSkippingString ansiStr(std::string("Hello World"));
    auto it_begin = ansiStr.begin();
    auto it = it_begin;
    // Advance 5 characters
    for (int i = 0; i < 5; ++i) {
        ++it;
    }
    std::string result = ansiStr.substring(it_begin, it);
    EXPECT_EQ(result, "Hello");
}

// Test string with embedded escape that's not a complete ANSI sequence
TEST(AnsiSkippingStringTest_611, IncompleteEscapeSequence_611) {
    // Just an ESC character followed by a regular character (not '[')
    std::string text = "ab\033cd";
    AnsiSkippingString ansiStr(text);
    // Behavior depends on implementation but we can at least verify it doesn't crash
    EXPECT_GE(ansiStr.size(), 0u);
}

// Test construction preserves original for plain text substring
TEST(AnsiSkippingStringTest_611, FullSubstringEqualsOriginal_611) {
    std::string original = "Simple text without ANSI";
    AnsiSkippingString ansiStr(original);
    std::string result = ansiStr.substring(ansiStr.begin(), ansiStr.end());
    EXPECT_EQ(result, original);
}
