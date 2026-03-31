#include "catch2/internal/catch_textflow.hpp"
#include <gtest/gtest.h>
#include <string>

using namespace Catch::TextFlow;

class AnsiSkippingStringConstIteratorTest_43 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default construction from a string - iterator starts at begin
TEST_F(AnsiSkippingStringConstIteratorTest_43, ConstructFromString_IteratorAtBegin_43) {
    std::string s = "hello";
    AnsiSkippingString::const_iterator it(s);
    // Dereference should give first character
    EXPECT_EQ(*it, 'h');
}

// Test dereferencing iterator at various positions
TEST_F(AnsiSkippingStringConstIteratorTest_43, DereferenceGivesCorrectChar_43) {
    std::string s = "abc";
    AnsiSkippingString::const_iterator it(s);
    EXPECT_EQ(*it, 'a');
    ++it;
    EXPECT_EQ(*it, 'b');
    ++it;
    EXPECT_EQ(*it, 'c');
}

// Test prefix increment
TEST_F(AnsiSkippingStringConstIteratorTest_43, PrefixIncrementAdvancesIterator_43) {
    std::string s = "xy";
    AnsiSkippingString::const_iterator it(s);
    EXPECT_EQ(*it, 'x');
    auto& ref = ++it;
    EXPECT_EQ(*ref, 'y');
    EXPECT_EQ(*it, 'y');
}

// Test postfix increment
TEST_F(AnsiSkippingStringConstIteratorTest_43, PostfixIncrementReturnsOldValue_43) {
    std::string s = "ab";
    AnsiSkippingString::const_iterator it(s);
    auto old = it++;
    EXPECT_EQ(*old, 'a');
    EXPECT_EQ(*it, 'b');
}

// Test prefix decrement
TEST_F(AnsiSkippingStringConstIteratorTest_43, PrefixDecrementMovesBack_43) {
    std::string s = "ab";
    AnsiSkippingString::const_iterator it(s);
    ++it;
    EXPECT_EQ(*it, 'b');
    --it;
    EXPECT_EQ(*it, 'a');
}

// Test postfix decrement
TEST_F(AnsiSkippingStringConstIteratorTest_43, PostfixDecrementReturnsOldValue_43) {
    std::string s = "ab";
    AnsiSkippingString::const_iterator it(s);
    ++it;
    auto old = it--;
    EXPECT_EQ(*old, 'b');
    EXPECT_EQ(*it, 'a');
}

// Test equality operator - same position
TEST_F(AnsiSkippingStringConstIteratorTest_43, EqualityOperatorSamePosition_43) {
    std::string s = "test";
    AnsiSkippingString::const_iterator it1(s);
    AnsiSkippingString::const_iterator it2(s);
    EXPECT_TRUE(it1 == it2);
}

// Test equality operator - different positions
TEST_F(AnsiSkippingStringConstIteratorTest_43, EqualityOperatorDifferentPosition_43) {
    std::string s = "test";
    AnsiSkippingString::const_iterator it1(s);
    AnsiSkippingString::const_iterator it2(s);
    ++it2;
    EXPECT_FALSE(it1 == it2);
}

// Test inequality operator
TEST_F(AnsiSkippingStringConstIteratorTest_43, InequalityOperator_43) {
    std::string s = "test";
    AnsiSkippingString::const_iterator it1(s);
    AnsiSkippingString::const_iterator it2(s);
    EXPECT_FALSE(it1 != it2);
    ++it2;
    EXPECT_TRUE(it1 != it2);
}

// Test less-than-or-equal operator - same position
TEST_F(AnsiSkippingStringConstIteratorTest_43, LessThanOrEqualSamePosition_43) {
    std::string s = "test";
    AnsiSkippingString::const_iterator it1(s);
    AnsiSkippingString::const_iterator it2(s);
    EXPECT_TRUE(it1 <= it2);
    EXPECT_TRUE(it2 <= it1);
}

// Test less-than-or-equal operator - different positions
TEST_F(AnsiSkippingStringConstIteratorTest_43, LessThanOrEqualDifferentPositions_43) {
    std::string s = "test";
    AnsiSkippingString::const_iterator it1(s);
    AnsiSkippingString::const_iterator it2(s);
    ++it2;
    EXPECT_TRUE(it1 <= it2);
    EXPECT_FALSE(it2 <= it1);
}

// Test with empty string
TEST_F(AnsiSkippingStringConstIteratorTest_43, EmptyStringIteratorsEqual_43) {
    std::string s = "";
    AnsiSkippingString::const_iterator it1(s);
    // Two iterators on empty string at begin should be equal
    AnsiSkippingString::const_iterator it2(s);
    EXPECT_TRUE(it1 == it2);
    EXPECT_TRUE(it1 <= it2);
}

// Test single character string
TEST_F(AnsiSkippingStringConstIteratorTest_43, SingleCharString_43) {
    std::string s = "Z";
    AnsiSkippingString::const_iterator it(s);
    EXPECT_EQ(*it, 'Z');
}

// Test oneBefore returns iterator one position before current
TEST_F(AnsiSkippingStringConstIteratorTest_43, OneBeforeReturnsCorrectIterator_43) {
    std::string s = "abc";
    AnsiSkippingString::const_iterator it(s);
    ++it;
    ++it;
    auto before = it.oneBefore();
    EXPECT_EQ(*before, 'b');
}

// Test ANSI escape sequence skipping - iterator should skip over escape sequences
TEST_F(AnsiSkippingStringConstIteratorTest_43, AnsiEscapeSequenceSkipping_43) {
    // \033[31m is a typical ANSI escape for red color
    std::string s = "\033[31mHello\033[0m";
    AnsiSkippingString::const_iterator it(s);
    // The iterator should skip the ANSI escape and give us 'H' first
    EXPECT_EQ(*it, 'H');
}

// Test iterating through string with ANSI codes gives visible characters only
TEST_F(AnsiSkippingStringConstIteratorTest_43, IterateThroughAnsiString_43) {
    std::string s = "\033[1mAB\033[0m";
    AnsiSkippingString::const_iterator it(s);
    EXPECT_EQ(*it, 'A');
    ++it;
    EXPECT_EQ(*it, 'B');
}

// Test multiple increments and decrements maintain consistency
TEST_F(AnsiSkippingStringConstIteratorTest_43, IncrementDecrementConsistency_43) {
    std::string s = "abcdef";
    AnsiSkippingString::const_iterator it(s);
    ++it;
    ++it;
    ++it;
    --it;
    --it;
    EXPECT_EQ(*it, 'b');
}

// Test <= with iterator at the end
TEST_F(AnsiSkippingStringConstIteratorTest_43, LessThanOrEqualAtEnd_43) {
    std::string s = "ab";
    AnsiSkippingString::const_iterator it1(s);
    AnsiSkippingString::const_iterator it2(s);
    ++it1;
    ++it2;
    EXPECT_TRUE(it1 <= it2);
}

// Test that iterators from same string at same position are equal after traversal
TEST_F(AnsiSkippingStringConstIteratorTest_43, IteratorsConvergeAfterSameTraversal_43) {
    std::string s = "xyz";
    AnsiSkippingString::const_iterator it1(s);
    AnsiSkippingString::const_iterator it2(s);
    ++it1;
    ++it2;
    EXPECT_TRUE(it1 == it2);
    EXPECT_EQ(*it1, *it2);
}

// Test with string containing spaces
TEST_F(AnsiSkippingStringConstIteratorTest_43, StringWithSpaces_43) {
    std::string s = "a b";
    AnsiSkippingString::const_iterator it(s);
    EXPECT_EQ(*it, 'a');
    ++it;
    EXPECT_EQ(*it, ' ');
    ++it;
    EXPECT_EQ(*it, 'b');
}

// Test with string containing newlines
TEST_F(AnsiSkippingStringConstIteratorTest_43, StringWithNewlines_43) {
    std::string s = "a\nb";
    AnsiSkippingString::const_iterator it(s);
    EXPECT_EQ(*it, 'a');
    ++it;
    EXPECT_EQ(*it, '\n');
    ++it;
    EXPECT_EQ(*it, 'b');
}

// Test complex ANSI sequence in middle of string
TEST_F(AnsiSkippingStringConstIteratorTest_43, AnsiSequenceInMiddle_43) {
    std::string s = "A\033[38;5;196mB";
    AnsiSkippingString::const_iterator it(s);
    EXPECT_EQ(*it, 'A');
    ++it;
    // Should skip the ANSI escape and land on 'B'
    EXPECT_EQ(*it, 'B');
}
