#include <string>
#include "catch2/internal/catch_textflow.hpp"

#include <gtest/gtest.h>

using Catch::TextFlow::AnsiSkippingString;

class AnsiSkippingStringTest_612 : public ::testing::Test {
protected:
};

// --- Size Tests ---

TEST_F(AnsiSkippingStringTest_612, EmptyStringHasSizeZero_612) {
    AnsiSkippingString s(std::string(""));
    EXPECT_EQ(s.size(), 0u);
}

TEST_F(AnsiSkippingStringTest_612, PlainStringSize_612) {
    AnsiSkippingString s(std::string("hello"));
    EXPECT_EQ(s.size(), 5u);
}

TEST_F(AnsiSkippingStringTest_612, StringWithAnsiEscapeHasSmallerSize_612) {
    // ANSI escape: ESC[31m (red color) = 5 chars but should be skipped
    std::string text = "\033[31mhello";
    AnsiSkippingString s(text);
    // The ANSI escape sequence should be skipped in size calculation
    EXPECT_EQ(s.size(), 5u);
}

TEST_F(AnsiSkippingStringTest_612, MoveConstructor_612) {
    std::string text = "hello world";
    AnsiSkippingString s(std::move(text));
    EXPECT_EQ(s.size(), 11u);
}

// --- Iterator Tests ---

TEST_F(AnsiSkippingStringTest_612, BeginEndEqualForEmptyString_612) {
    AnsiSkippingString s(std::string(""));
    EXPECT_TRUE(s.begin() == s.end());
}

TEST_F(AnsiSkippingStringTest_612, BeginNotEqualEndForNonEmpty_612) {
    AnsiSkippingString s(std::string("a"));
    EXPECT_TRUE(s.begin() != s.end());
}

TEST_F(AnsiSkippingStringTest_612, DereferenceBeginReturnsFirstChar_612) {
    AnsiSkippingString s(std::string("hello"));
    auto it = s.begin();
    EXPECT_EQ(*it, 'h');
}

TEST_F(AnsiSkippingStringTest_612, PreIncrementIterator_612) {
    AnsiSkippingString s(std::string("ab"));
    auto it = s.begin();
    EXPECT_EQ(*it, 'a');
    ++it;
    EXPECT_EQ(*it, 'b');
}

TEST_F(AnsiSkippingStringTest_612, PostIncrementIterator_612) {
    AnsiSkippingString s(std::string("ab"));
    auto it = s.begin();
    auto prev = it++;
    EXPECT_EQ(*prev, 'a');
    EXPECT_EQ(*it, 'b');
}

TEST_F(AnsiSkippingStringTest_612, IterateEntirePlainString_612) {
    std::string text = "hello";
    AnsiSkippingString s(text);
    std::string result;
    for (auto it = s.begin(); it != s.end(); ++it) {
        result += *it;
    }
    EXPECT_EQ(result, "hello");
}

TEST_F(AnsiSkippingStringTest_612, DecrementIterator_612) {
    AnsiSkippingString s(std::string("abc"));
    auto it = s.begin();
    ++it;
    ++it;
    EXPECT_EQ(*it, 'c');
    --it;
    EXPECT_EQ(*it, 'b');
}

TEST_F(AnsiSkippingStringTest_612, PostDecrementIterator_612) {
    AnsiSkippingString s(std::string("abc"));
    auto it = s.begin();
    ++it;
    ++it;
    auto prev = it--;
    EXPECT_EQ(*prev, 'c');
    EXPECT_EQ(*it, 'b');
}

TEST_F(AnsiSkippingStringTest_612, IteratorLessThanOrEqual_612) {
    AnsiSkippingString s(std::string("abc"));
    auto it1 = s.begin();
    auto it2 = s.begin();
    EXPECT_TRUE(it1 <= it2);
    ++it2;
    EXPECT_TRUE(it1 <= it2);
}

TEST_F(AnsiSkippingStringTest_612, OneBeforeReturnsCorrectIterator_612) {
    AnsiSkippingString s(std::string("abc"));
    auto it = s.begin();
    ++it;
    ++it; // points to 'c'
    auto before = it.oneBefore();
    EXPECT_EQ(*before, 'b');
}

// --- Substring Tests ---

TEST_F(AnsiSkippingStringTest_612, SubstringFullString_612) {
    AnsiSkippingString s(std::string("hello"));
    std::string result = s.substring(s.begin(), s.end());
    EXPECT_EQ(result, "hello");
}

TEST_F(AnsiSkippingStringTest_612, SubstringPartialString_612) {
    AnsiSkippingString s(std::string("hello world"));
    auto it_begin = s.begin();
    auto it_end = s.begin();
    // Advance end to point past "hello"
    for (int i = 0; i < 5; ++i) {
        ++it_end;
    }
    std::string result = s.substring(it_begin, it_end);
    EXPECT_EQ(result, "hello");
}

TEST_F(AnsiSkippingStringTest_612, SubstringFromMiddle_612) {
    AnsiSkippingString s(std::string("hello world"));
    auto it_begin = s.begin();
    // Advance begin to 'w'
    for (int i = 0; i < 6; ++i) {
        ++it_begin;
    }
    std::string result = s.substring(it_begin, s.end());
    EXPECT_EQ(result, "world");
}

TEST_F(AnsiSkippingStringTest_612, SubstringEmptyRange_612) {
    AnsiSkippingString s(std::string("hello"));
    auto it = s.begin();
    std::string result = s.substring(it, it);
    EXPECT_EQ(result, "");
}

// --- ANSI Escape Skipping Tests ---

TEST_F(AnsiSkippingStringTest_612, AnsiEscapeSkippedDuringIteration_612) {
    // ESC[31m is a typical ANSI color code
    std::string text = "\033[31mhi";
    AnsiSkippingString s(text);
    std::string result;
    for (auto it = s.begin(); it != s.end(); ++it) {
        result += *it;
    }
    EXPECT_EQ(result, "hi");
}

TEST_F(AnsiSkippingStringTest_612, MultipleAnsiEscapesSkipped_612) {
    std::string text = "\033[31mhello\033[0m";
    AnsiSkippingString s(text);
    EXPECT_EQ(s.size(), 5u);
}

TEST_F(AnsiSkippingStringTest_612, SubstringRestoresAnsiTerminator_612) {
    // The sentinel 'm' replacement in substring should restore 'm' chars
    std::string text = "\033[31mhello\033[0m";
    AnsiSkippingString s(text);
    std::string result = s.substring(s.begin(), s.end());
    // The substring should contain the visible text
    EXPECT_NE(result.find("hello"), std::string::npos);
}

TEST_F(AnsiSkippingStringTest_612, PlainStringSubstringUnchanged_612) {
    AnsiSkippingString s(std::string("no ansi here"));
    std::string result = s.substring(s.begin(), s.end());
    EXPECT_EQ(result, "no ansi here");
}

// --- Boundary Tests ---

TEST_F(AnsiSkippingStringTest_612, SingleCharacterString_612) {
    AnsiSkippingString s(std::string("x"));
    EXPECT_EQ(s.size(), 1u);
    auto it = s.begin();
    EXPECT_EQ(*it, 'x');
    ++it;
    EXPECT_TRUE(it == s.end());
}

TEST_F(AnsiSkippingStringTest_612, OnlyAnsiEscapeString_612) {
    std::string text = "\033[31m";
    AnsiSkippingString s(text);
    EXPECT_EQ(s.size(), 0u);
    EXPECT_TRUE(s.begin() == s.end());
}

TEST_F(AnsiSkippingStringTest_612, LongPlainString_612) {
    std::string text(1000, 'a');
    AnsiSkippingString s(text);
    EXPECT_EQ(s.size(), 1000u);
}

TEST_F(AnsiSkippingStringTest_612, IteratorEqualitySelf_612) {
    AnsiSkippingString s(std::string("abc"));
    auto it = s.begin();
    EXPECT_TRUE(it == it);
    EXPECT_FALSE(it != it);
}

TEST_F(AnsiSkippingStringTest_612, IterateForwardAndBackward_612) {
    AnsiSkippingString s(std::string("abcde"));
    auto it = s.begin();
    ++it; ++it; ++it; // at 'd'
    EXPECT_EQ(*it, 'd');
    --it; --it; // at 'b'
    EXPECT_EQ(*it, 'b');
}

TEST_F(AnsiSkippingStringTest_612, SubstringFromBeginMatchesFullBegin_612) {
    AnsiSkippingString s(std::string("test string"));
    auto b = s.begin();
    auto e = s.begin();
    for (int i = 0; i < 4; ++i) ++e;
    std::string result = s.substring(b, e);
    EXPECT_EQ(result, "test");
}

TEST_F(AnsiSkippingStringTest_612, AnsiInMiddleOfString_612) {
    std::string text = "he\033[32mllo";
    AnsiSkippingString s(text);
    EXPECT_EQ(s.size(), 5u);
    std::string result;
    for (auto it = s.begin(); it != s.end(); ++it) {
        result += *it;
    }
    EXPECT_EQ(result, "hello");
}

TEST_F(AnsiSkippingStringTest_612, ConstructFromRvalue_612) {
    AnsiSkippingString s(std::string("rvalue test"));
    EXPECT_EQ(s.size(), 11u);
}
