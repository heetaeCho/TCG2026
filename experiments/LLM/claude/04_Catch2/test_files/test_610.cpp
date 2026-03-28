#include "catch2/internal/catch_textflow.hpp"
#include <gtest/gtest.h>
#include <string>

using Catch::TextFlow::AnsiSkippingString;

// Test construction from const std::string&
TEST(AnsiSkippingStringTest_610, ConstructFromConstRef_610) {
    std::string text = "Hello, World!";
    AnsiSkippingString str(text);
    EXPECT_EQ(str.size(), 13u);
}

// Test construction from rvalue string
TEST(AnsiSkippingStringTest_610, ConstructFromRvalue_610) {
    AnsiSkippingString str(std::string("Hello"));
    EXPECT_EQ(str.size(), 5u);
}

// Test empty string
TEST(AnsiSkippingStringTest_610, EmptyString_610) {
    AnsiSkippingString str(std::string(""));
    EXPECT_EQ(str.size(), 0u);
}

// Test begin and end iterators on empty string
TEST(AnsiSkippingStringTest_610, BeginEqualsEndOnEmpty_610) {
    AnsiSkippingString str(std::string(""));
    auto it_begin = str.begin();
    auto it_end = str.end();
    EXPECT_EQ(it_begin, it_end);
}

// Test begin and end iterators on non-empty string
TEST(AnsiSkippingStringTest_610, BeginNotEqualsEndOnNonEmpty_610) {
    AnsiSkippingString str(std::string("abc"));
    auto it_begin = str.begin();
    auto it_end = str.end();
    EXPECT_NE(it_begin, it_end);
}

// Test size of plain text
TEST(AnsiSkippingStringTest_610, SizePlainText_610) {
    AnsiSkippingString str(std::string("abcdef"));
    EXPECT_EQ(str.size(), 6u);
}

// Test that ANSI escape codes are skipped in size calculation
TEST(AnsiSkippingStringTest_610, SizeSkipsAnsiEscapeCodes_610) {
    // ANSI escape: \033[31m (red color) = 5 bytes, should be skipped
    std::string text = "\033[31mHello\033[0m";
    AnsiSkippingString str(text);
    // "Hello" is 5 visible characters, ANSI codes should be skipped
    EXPECT_EQ(str.size(), 5u);
}

// Test substring on plain text
TEST(AnsiSkippingStringTest_610, SubstringPlainText_610) {
    AnsiSkippingString str(std::string("Hello, World!"));
    auto it_begin = str.begin();
    auto it_end = str.end();
    std::string result = str.substring(it_begin, it_end);
    EXPECT_EQ(result, "Hello, World!");
}

// Test substring on empty string
TEST(AnsiSkippingStringTest_610, SubstringEmptyString_610) {
    AnsiSkippingString str(std::string(""));
    auto it_begin = str.begin();
    auto it_end = str.end();
    std::string result = str.substring(it_begin, it_end);
    EXPECT_EQ(result, "");
}

// Test substring with begin == end gives empty string
TEST(AnsiSkippingStringTest_610, SubstringBeginEqualsEnd_610) {
    AnsiSkippingString str(std::string("Hello"));
    auto it_begin = str.begin();
    std::string result = str.substring(it_begin, it_begin);
    EXPECT_EQ(result, "");
}

// Test iteration over plain text characters
TEST(AnsiSkippingStringTest_610, IterationPlainText_610) {
    AnsiSkippingString str(std::string("abc"));
    auto it = str.begin();
    auto end = str.end();
    
    EXPECT_NE(it, end);
    EXPECT_EQ(*it, 'a');
    ++it;
    EXPECT_NE(it, end);
    EXPECT_EQ(*it, 'b');
    ++it;
    EXPECT_NE(it, end);
    EXPECT_EQ(*it, 'c');
    ++it;
    EXPECT_EQ(it, end);
}

// Test that ANSI escape sequences are skipped during iteration
TEST(AnsiSkippingStringTest_610, IterationSkipsAnsi_610) {
    // \033[31m is a color code; iterator should skip it
    std::string text = "\033[31mAB\033[0m";
    AnsiSkippingString str(text);
    
    auto it = str.begin();
    auto end = str.end();
    
    EXPECT_NE(it, end);
    EXPECT_EQ(*it, 'A');
    ++it;
    EXPECT_NE(it, end);
    EXPECT_EQ(*it, 'B');
    ++it;
    EXPECT_EQ(it, end);
}

// Test size with multiple ANSI codes
TEST(AnsiSkippingStringTest_610, SizeMultipleAnsiCodes_610) {
    std::string text = "\033[1m\033[31mHi\033[0m";
    AnsiSkippingString str(text);
    EXPECT_EQ(str.size(), 2u);
}

// Test single character string
TEST(AnsiSkippingStringTest_610, SingleCharacter_610) {
    AnsiSkippingString str(std::string("X"));
    EXPECT_EQ(str.size(), 1u);
    auto it = str.begin();
    EXPECT_EQ(*it, 'X');
    ++it;
    EXPECT_EQ(it, str.end());
}

// Test string with only ANSI codes and no visible text
TEST(AnsiSkippingStringTest_610, OnlyAnsiCodes_610) {
    std::string text = "\033[31m\033[0m";
    AnsiSkippingString str(text);
    EXPECT_EQ(str.size(), 0u);
    EXPECT_EQ(str.begin(), str.end());
}

// Test substring includes ANSI codes in output
TEST(AnsiSkippingStringTest_610, SubstringIncludesAnsiInOutput_610) {
    std::string text = "\033[31mHello\033[0m";
    AnsiSkippingString str(text);
    auto it_begin = str.begin();
    auto it_end = str.end();
    std::string result = str.substring(it_begin, it_end);
    // The substring should include the raw ANSI codes
    EXPECT_EQ(result, text);
}

// Test partial substring
TEST(AnsiSkippingStringTest_610, PartialSubstring_610) {
    AnsiSkippingString str(std::string("Hello"));
    auto it = str.begin();
    ++it; // skip 'H'
    ++it; // skip 'e'
    auto it_end = it;
    ++it_end; // include 'l'
    ++it_end; // include 'l'
    std::string result = str.substring(it, it_end);
    EXPECT_EQ(result, "ll");
}

// Test with spaces
TEST(AnsiSkippingStringTest_610, StringWithSpaces_610) {
    AnsiSkippingString str(std::string("a b c"));
    EXPECT_EQ(str.size(), 5u);
}

// Test with newline characters
TEST(AnsiSkippingStringTest_610, StringWithNewlines_610) {
    AnsiSkippingString str(std::string("line1\nline2"));
    EXPECT_EQ(str.size(), 11u);
}

// Test long string
TEST(AnsiSkippingStringTest_610, LongString_610) {
    std::string long_text(1000, 'x');
    AnsiSkippingString str(long_text);
    EXPECT_EQ(str.size(), 1000u);
}

// Test ANSI code at beginning
TEST(AnsiSkippingStringTest_610, AnsiAtBeginning_610) {
    std::string text = "\033[32mGreen";
    AnsiSkippingString str(text);
    EXPECT_EQ(str.size(), 5u);
    auto it = str.begin();
    EXPECT_EQ(*it, 'G');
}

// Test ANSI code at end
TEST(AnsiSkippingStringTest_610, AnsiAtEnd_610) {
    std::string text = "Text\033[0m";
    AnsiSkippingString str(text);
    EXPECT_EQ(str.size(), 4u);
}

// Test ANSI code in middle
TEST(AnsiSkippingStringTest_610, AnsiInMiddle_610) {
    std::string text = "He\033[31mllo";
    AnsiSkippingString str(text);
    EXPECT_EQ(str.size(), 5u);
}
