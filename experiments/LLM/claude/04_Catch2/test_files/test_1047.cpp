#include <gtest/gtest.h>
#include <string>
#include "catch2/internal/catch_textflow.hpp"

using namespace Catch::TextFlow;

class AnsiSkippingStringIteratorTest_1047 : public ::testing::Test {
protected:
};

// Test basic construction and dereferencing a simple string
TEST_F(AnsiSkippingStringIteratorTest_1047, ConstructFromSimpleString_1047) {
    std::string s = "Hello";
    AnsiSkippingString::const_iterator it(s);
    EXPECT_EQ(*it, 'H');
}

// Test prefix increment on simple string
TEST_F(AnsiSkippingStringIteratorTest_1047, PrefixIncrement_1047) {
    std::string s = "AB";
    AnsiSkippingString::const_iterator it(s);
    EXPECT_EQ(*it, 'A');
    ++it;
    EXPECT_EQ(*it, 'B');
}

// Test postfix increment on simple string
TEST_F(AnsiSkippingStringIteratorTest_1047, PostfixIncrement_1047) {
    std::string s = "CD";
    AnsiSkippingString::const_iterator it(s);
    AnsiSkippingString::const_iterator prev = it++;
    EXPECT_EQ(*prev, 'C');
    EXPECT_EQ(*it, 'D');
}

// Test prefix decrement
TEST_F(AnsiSkippingStringIteratorTest_1047, PrefixDecrement_1047) {
    std::string s = "XY";
    AnsiSkippingString::const_iterator it(s);
    ++it;
    EXPECT_EQ(*it, 'Y');
    --it;
    EXPECT_EQ(*it, 'X');
}

// Test postfix decrement
TEST_F(AnsiSkippingStringIteratorTest_1047, PostfixDecrement_1047) {
    std::string s = "PQ";
    AnsiSkippingString::const_iterator it(s);
    ++it;
    AnsiSkippingString::const_iterator prev = it--;
    EXPECT_EQ(*prev, 'Q');
    EXPECT_EQ(*it, 'P');
}

// Test equality operator
TEST_F(AnsiSkippingStringIteratorTest_1047, EqualityOperator_1047) {
    std::string s = "Test";
    AnsiSkippingString::const_iterator it1(s);
    AnsiSkippingString::const_iterator it2(s);
    EXPECT_TRUE(it1 == it2);
}

// Test inequality operator
TEST_F(AnsiSkippingStringIteratorTest_1047, InequalityOperator_1047) {
    std::string s = "Test";
    AnsiSkippingString::const_iterator it1(s);
    AnsiSkippingString::const_iterator it2(s);
    ++it2;
    EXPECT_TRUE(it1 != it2);
}

// Test less-than-or-equal operator
TEST_F(AnsiSkippingStringIteratorTest_1047, LessEqualOperator_1047) {
    std::string s = "AB";
    AnsiSkippingString::const_iterator it1(s);
    AnsiSkippingString::const_iterator it2(s);
    EXPECT_TRUE(it1 <= it2);
    ++it2;
    EXPECT_TRUE(it1 <= it2);
    EXPECT_FALSE(it2 <= it1);
}

// Test oneBefore returns iterator one position before current
TEST_F(AnsiSkippingStringIteratorTest_1047, OneBefore_1047) {
    std::string s = "ABC";
    AnsiSkippingString::const_iterator it(s);
    ++it;
    ++it;
    AnsiSkippingString::const_iterator prev = it.oneBefore();
    EXPECT_EQ(*prev, 'B');
    EXPECT_EQ(*it, 'C');
}

// Test ANSI escape sequence skipping - iterator should skip ESC[...m sequences
TEST_F(AnsiSkippingStringIteratorTest_1047, SkipsAnsiEscapeAtStart_1047) {
    std::string s = "\033[31mHello";
    AnsiSkippingString::const_iterator it(s);
    EXPECT_EQ(*it, 'H');
}

// Test ANSI escape in middle of string
TEST_F(AnsiSkippingStringIteratorTest_1047, SkipsAnsiEscapeInMiddle_1047) {
    std::string s = "A\033[0mB";
    AnsiSkippingString::const_iterator it(s);
    EXPECT_EQ(*it, 'A');
    ++it;
    EXPECT_EQ(*it, 'B');
}

// Test multiple ANSI escapes
TEST_F(AnsiSkippingStringIteratorTest_1047, SkipsMultipleAnsiEscapes_1047) {
    std::string s = "\033[1m\033[31mX\033[0m";
    AnsiSkippingString::const_iterator it(s);
    EXPECT_EQ(*it, 'X');
}

// Test empty string
TEST_F(AnsiSkippingStringIteratorTest_1047, EmptyString_1047) {
    std::string s = "";
    AnsiSkippingString::const_iterator it1(s);
    AnsiSkippingString::const_iterator it2(s);
    EXPECT_TRUE(it1 == it2);
}

// Test iterating through entire simple string
TEST_F(AnsiSkippingStringIteratorTest_1047, FullIteration_1047) {
    std::string s = "ABCDE";
    AnsiSkippingString::const_iterator it(s);
    std::string result;
    AnsiSkippingString::const_iterator end(s);
    // Advance end to end position manually
    for (int i = 0; i < 5; ++i) {
        result += *it;
        ++it;
    }
    EXPECT_EQ(result, "ABCDE");
}

// Test single character string
TEST_F(AnsiSkippingStringIteratorTest_1047, SingleCharString_1047) {
    std::string s = "Z";
    AnsiSkippingString::const_iterator it(s);
    EXPECT_EQ(*it, 'Z');
}

// Test string that is only ANSI escape
TEST_F(AnsiSkippingStringIteratorTest_1047, OnlyAnsiEscape_1047) {
    std::string s = "\033[31m";
    AnsiSkippingString::const_iterator it1(s);
    AnsiSkippingString::const_iterator it2(s);
    // Both should effectively be at the end since there's no visible content
    EXPECT_TRUE(it1 == it2);
}

// Test equality after same number of increments
TEST_F(AnsiSkippingStringIteratorTest_1047, EqualityAfterSameIncrements_1047) {
    std::string s = "Hello";
    AnsiSkippingString::const_iterator it1(s);
    AnsiSkippingString::const_iterator it2(s);
    ++it1;
    ++it1;
    ++it2;
    ++it2;
    EXPECT_TRUE(it1 == it2);
}

// Test decrement after increment returns to same position
TEST_F(AnsiSkippingStringIteratorTest_1047, DecrementAfterIncrementReturnsSamePosition_1047) {
    std::string s = "World";
    AnsiSkippingString::const_iterator it(s);
    AnsiSkippingString::const_iterator original(s);
    ++it;
    --it;
    EXPECT_TRUE(it == original);
    EXPECT_EQ(*it, 'W');
}
