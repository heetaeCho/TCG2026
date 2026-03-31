#include "catch2/internal/catch_textflow.hpp"
#include <gtest/gtest.h>
#include <string>

using namespace Catch::TextFlow;

class AnsiSkippingStringTest_37 : public ::testing::Test {
protected:
};

TEST_F(AnsiSkippingStringTest_37, DefaultConstructFromPlainString_37) {
    std::string input = "hello";
    AnsiSkippingString str(input);
    auto it = str.begin();
    auto end = str.end();
    EXPECT_NE(it, end);
}

TEST_F(AnsiSkippingStringTest_37, IterateOverPlainString_37) {
    std::string input = "abc";
    AnsiSkippingString str(input);
    std::string result;
    for (auto it = str.begin(); it != str.end(); ++it) {
        result += *it;
    }
    EXPECT_EQ(result, "abc");
}

TEST_F(AnsiSkippingStringTest_37, EmptyString_37) {
    std::string input = "";
    AnsiSkippingString str(input);
    EXPECT_EQ(str.begin(), str.end());
}

TEST_F(AnsiSkippingStringTest_37, SingleCharacter_37) {
    std::string input = "x";
    AnsiSkippingString str(input);
    auto it = str.begin();
    EXPECT_NE(it, end(str));
    EXPECT_EQ(*it, 'x');
    ++it;
    EXPECT_EQ(it, str.end());
}

TEST_F(AnsiSkippingStringTest_37, SkipsAnsiEscapeSequence_37) {
    // ANSI escape: ESC[31m (red color)
    std::string input = "\033[31mhello\033[0m";
    AnsiSkippingString str(input);
    std::string result;
    for (auto it = str.begin(); it != str.end(); ++it) {
        result += *it;
    }
    EXPECT_EQ(result, "hello");
}

TEST_F(AnsiSkippingStringTest_37, SkipsMultipleAnsiEscapes_37) {
    std::string input = "\033[1m\033[31mhi\033[0m";
    AnsiSkippingString str(input);
    std::string result;
    for (auto it = str.begin(); it != str.end(); ++it) {
        result += *it;
    }
    EXPECT_EQ(result, "hi");
}

TEST_F(AnsiSkippingStringTest_37, OnlyAnsiEscapes_37) {
    std::string input = "\033[31m\033[0m";
    AnsiSkippingString str(input);
    auto it = str.begin();
    EXPECT_EQ(it, str.end());
}

TEST_F(AnsiSkippingStringTest_37, PostIncrementReturnsOldValue_37) {
    std::string input = "ab";
    AnsiSkippingString str(input);
    auto it = str.begin();
    auto old = it++;
    EXPECT_EQ(*old, 'a');
    EXPECT_EQ(*it, 'b');
}

TEST_F(AnsiSkippingStringTest_37, PreDecrementWorks_37) {
    std::string input = "abc";
    AnsiSkippingString str(input);
    auto it = str.begin();
    ++it;
    ++it;
    EXPECT_EQ(*it, 'c');
    --it;
    EXPECT_EQ(*it, 'b');
    --it;
    EXPECT_EQ(*it, 'a');
}

TEST_F(AnsiSkippingStringTest_37, PostDecrementReturnsOldValue_37) {
    std::string input = "ab";
    AnsiSkippingString str(input);
    auto it = str.begin();
    ++it;
    EXPECT_EQ(*it, 'b');
    auto old = it--;
    EXPECT_EQ(*old, 'b');
    EXPECT_EQ(*it, 'a');
}

TEST_F(AnsiSkippingStringTest_37, EqualityOperator_37) {
    std::string input = "abc";
    AnsiSkippingString str(input);
    auto it1 = str.begin();
    auto it2 = str.begin();
    EXPECT_TRUE(it1 == it2);
    ++it1;
    EXPECT_FALSE(it1 == it2);
}

TEST_F(AnsiSkippingStringTest_37, InequalityOperator_37) {
    std::string input = "abc";
    AnsiSkippingString str(input);
    auto it1 = str.begin();
    auto it2 = str.begin();
    EXPECT_FALSE(it1 != it2);
    ++it1;
    EXPECT_TRUE(it1 != it2);
}

TEST_F(AnsiSkippingStringTest_37, LessThanOrEqualOperator_37) {
    std::string input = "abc";
    AnsiSkippingString str(input);
    auto it1 = str.begin();
    auto it2 = str.begin();
    EXPECT_TRUE(it1 <= it2);
    ++it2;
    EXPECT_TRUE(it1 <= it2);
    EXPECT_FALSE(it2 <= it1);
}

TEST_F(AnsiSkippingStringTest_37, OneBeforeReturnsCorrectIterator_37) {
    std::string input = "abc";
    AnsiSkippingString str(input);
    auto it = str.begin();
    ++it; // pointing to 'b'
    auto before = it.oneBefore();
    EXPECT_EQ(*before, 'a');
}

TEST_F(AnsiSkippingStringTest_37, AnsiEscapeAtEnd_37) {
    std::string input = "hi\033[0m";
    AnsiSkippingString str(input);
    std::string result;
    for (auto it = str.begin(); it != str.end(); ++it) {
        result += *it;
    }
    EXPECT_EQ(result, "hi");
}

TEST_F(AnsiSkippingStringTest_37, AnsiEscapeAtBeginning_37) {
    std::string input = "\033[31mhi";
    AnsiSkippingString str(input);
    std::string result;
    for (auto it = str.begin(); it != str.end(); ++it) {
        result += *it;
    }
    EXPECT_EQ(result, "hi");
}

TEST_F(AnsiSkippingStringTest_37, AnsiEscapeBetweenChars_37) {
    std::string input = "a\033[31mb";
    AnsiSkippingString str(input);
    std::string result;
    for (auto it = str.begin(); it != str.end(); ++it) {
        result += *it;
    }
    EXPECT_EQ(result, "ab");
}

TEST_F(AnsiSkippingStringTest_37, DecrementSkipsAnsiBackwards_37) {
    std::string input = "a\033[31mb";
    AnsiSkippingString str(input);
    auto it = str.begin();
    ++it; // should point to 'b' (skipping ANSI)
    EXPECT_EQ(*it, 'b');
    --it;
    EXPECT_EQ(*it, 'a');
}

TEST_F(AnsiSkippingStringTest_37, LongAnsiSequence_37) {
    std::string input = "\033[38;2;255;0;0mred\033[0m";
    AnsiSkippingString str(input);
    std::string result;
    for (auto it = str.begin(); it != str.end(); ++it) {
        result += *it;
    }
    EXPECT_EQ(result, "red");
}

TEST_F(AnsiSkippingStringTest_37, StringWithSpacesAndAnsi_37) {
    std::string input = "\033[1mhello world\033[0m";
    AnsiSkippingString str(input);
    std::string result;
    for (auto it = str.begin(); it != str.end(); ++it) {
        result += *it;
    }
    EXPECT_EQ(result, "hello world");
}

TEST_F(AnsiSkippingStringTest_37, EndIteratorsAreEqual_37) {
    std::string input = "test";
    AnsiSkippingString str(input);
    auto end1 = str.end();
    auto end2 = str.end();
    EXPECT_EQ(end1, end2);
}
