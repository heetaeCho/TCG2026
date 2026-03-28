#include <gtest/gtest.h>
#include <string>

#include "catch2/internal/catch_textflow.hpp"

using namespace Catch::TextFlow;

class AnsiSkippingStringIteratorTest_44 : public ::testing::Test {
protected:
};

// Test basic construction and dereferencing at the beginning of a simple string
TEST_F(AnsiSkippingStringIteratorTest_44, DereferenceAtBegin_44) {
    std::string str = "Hello";
    AnsiSkippingString::const_iterator it(str);
    EXPECT_EQ(*it, 'H');
}

// Test prefix increment moves to next character
TEST_F(AnsiSkippingStringIteratorTest_44, PrefixIncrement_44) {
    std::string str = "Hello";
    AnsiSkippingString::const_iterator it(str);
    ++it;
    EXPECT_EQ(*it, 'e');
}

// Test postfix increment returns old value and advances
TEST_F(AnsiSkippingStringIteratorTest_44, PostfixIncrement_44) {
    std::string str = "Hello";
    AnsiSkippingString::const_iterator it(str);
    auto old = it++;
    EXPECT_EQ(*old, 'H');
    EXPECT_EQ(*it, 'e');
}

// Test prefix decrement moves back one character
TEST_F(AnsiSkippingStringIteratorTest_44, PrefixDecrement_44) {
    std::string str = "Hello";
    AnsiSkippingString::const_iterator it(str);
    ++it;
    ++it;
    --it;
    EXPECT_EQ(*it, 'e');
}

// Test postfix decrement returns current and moves back
TEST_F(AnsiSkippingStringIteratorTest_44, PostfixDecrement_44) {
    std::string str = "Hello";
    AnsiSkippingString::const_iterator it(str);
    ++it;
    ++it;
    auto old = it--;
    EXPECT_EQ(*old, 'l');
    EXPECT_EQ(*it, 'e');
}

// Test equality of two iterators at same position
TEST_F(AnsiSkippingStringIteratorTest_44, EqualityOperator_44) {
    std::string str = "Hello";
    AnsiSkippingString::const_iterator it1(str);
    AnsiSkippingString::const_iterator it2(str);
    EXPECT_TRUE(it1 == it2);
}

// Test inequality of two iterators at different positions
TEST_F(AnsiSkippingStringIteratorTest_44, InequalityOperator_44) {
    std::string str = "Hello";
    AnsiSkippingString::const_iterator it1(str);
    AnsiSkippingString::const_iterator it2(str);
    ++it2;
    EXPECT_TRUE(it1 != it2);
}

// Test less-than-or-equal operator
TEST_F(AnsiSkippingStringIteratorTest_44, LessThanOrEqualSamePosition_44) {
    std::string str = "Hello";
    AnsiSkippingString::const_iterator it1(str);
    AnsiSkippingString::const_iterator it2(str);
    EXPECT_TRUE(it1 <= it2);
}

// Test less-than-or-equal with first before second
TEST_F(AnsiSkippingStringIteratorTest_44, LessThanOrEqualBeforePosition_44) {
    std::string str = "Hello";
    AnsiSkippingString::const_iterator it1(str);
    AnsiSkippingString::const_iterator it2(str);
    ++it2;
    EXPECT_TRUE(it1 <= it2);
}

// Test oneBefore returns an iterator one position before current
TEST_F(AnsiSkippingStringIteratorTest_44, OneBeforeReturnsCorrectIterator_44) {
    std::string str = "Hello";
    AnsiSkippingString::const_iterator it(str);
    ++it;
    ++it;
    auto before = it.oneBefore();
    EXPECT_EQ(*before, 'e');
}

// Test iterating through the entire string
TEST_F(AnsiSkippingStringIteratorTest_44, FullIteration_44) {
    std::string str = "abc";
    AnsiSkippingString::const_iterator it(str);
    EXPECT_EQ(*it, 'a');
    ++it;
    EXPECT_EQ(*it, 'b');
    ++it;
    EXPECT_EQ(*it, 'c');
}

// Test that ANSI escape sequences are skipped
TEST_F(AnsiSkippingStringIteratorTest_44, SkipsAnsiEscapeSequences_44) {
    // ANSI escape: ESC [ 31 m (red color)
    std::string str = "\033[31mHello";
    AnsiSkippingString::const_iterator it(str);
    EXPECT_EQ(*it, 'H');
}

// Test string with ANSI escape in the middle
TEST_F(AnsiSkippingStringIteratorTest_44, SkipsAnsiEscapeInMiddle_44) {
    std::string str = "A\033[0mB";
    AnsiSkippingString::const_iterator it(str);
    EXPECT_EQ(*it, 'A');
    ++it;
    EXPECT_EQ(*it, 'B');
}

// Test string with multiple ANSI escape sequences
TEST_F(AnsiSkippingStringIteratorTest_44, SkipsMultipleAnsiEscapes_44) {
    std::string str = "\033[1m\033[31mHi\033[0m";
    AnsiSkippingString::const_iterator it(str);
    EXPECT_EQ(*it, 'H');
    ++it;
    EXPECT_EQ(*it, 'i');
}

// Test empty string - begin equals end
TEST_F(AnsiSkippingStringIteratorTest_44, EmptyStringIterator_44) {
    std::string str = "";
    AnsiSkippingString::const_iterator it1(str);
    AnsiSkippingString::const_iterator it2(str);
    EXPECT_TRUE(it1 == it2);
}

// Test single character string
TEST_F(AnsiSkippingStringIteratorTest_44, SingleCharacterString_44) {
    std::string str = "X";
    AnsiSkippingString::const_iterator it(str);
    EXPECT_EQ(*it, 'X');
}

// Test oneBefore does not modify original iterator
TEST_F(AnsiSkippingStringIteratorTest_44, OneBeforeDoesNotModifyOriginal_44) {
    std::string str = "Hello";
    AnsiSkippingString::const_iterator it(str);
    ++it;
    ++it;
    auto before = it.oneBefore();
    EXPECT_EQ(*it, 'l');
    EXPECT_EQ(*before, 'e');
}

// Test decrement after increment returns to original position
TEST_F(AnsiSkippingStringIteratorTest_44, IncrementThenDecrementReturnsToOriginal_44) {
    std::string str = "Hello";
    AnsiSkippingString::const_iterator it(str);
    AnsiSkippingString::const_iterator original(str);
    ++it;
    --it;
    EXPECT_TRUE(it == original);
}

// Test inequality is correct negation of equality
TEST_F(AnsiSkippingStringIteratorTest_44, InequalityIsNegationOfEquality_44) {
    std::string str = "Hello";
    AnsiSkippingString::const_iterator it1(str);
    AnsiSkippingString::const_iterator it2(str);
    EXPECT_FALSE(it1 != it2);
    ++it2;
    EXPECT_TRUE(it1 != it2);
}

// Test string with only ANSI escape (no visible characters)
TEST_F(AnsiSkippingStringIteratorTest_44, StringWithOnlyAnsiEscape_44) {
    std::string str = "\033[31m\033[0m";
    AnsiSkippingString::const_iterator it1(str);
    AnsiSkippingString::const_iterator it2(str);
    // Both should effectively be at "end" since no visible characters
    EXPECT_TRUE(it1 == it2);
}

// Test string with spaces
TEST_F(AnsiSkippingStringIteratorTest_44, StringWithSpaces_44) {
    std::string str = "A B";
    AnsiSkippingString::const_iterator it(str);
    EXPECT_EQ(*it, 'A');
    ++it;
    EXPECT_EQ(*it, ' ');
    ++it;
    EXPECT_EQ(*it, 'B');
}

// Test less-than-or-equal when second is before first
TEST_F(AnsiSkippingStringIteratorTest_44, LessThanOrEqualWhenAfter_44) {
    std::string str = "Hello";
    AnsiSkippingString::const_iterator it1(str);
    AnsiSkippingString::const_iterator it2(str);
    ++it1;
    // it1 is after it2, so it1 <= it2 should be false
    EXPECT_FALSE(it1 <= it2);
}
