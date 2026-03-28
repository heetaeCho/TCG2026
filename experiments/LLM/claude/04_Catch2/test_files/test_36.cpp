#include "catch2/internal/catch_textflow.hpp"
#include <gtest/gtest.h>
#include <string>

using namespace Catch::TextFlow;

// =============================================================================
// Tests for AnsiSkippingString::const_iterator
// =============================================================================

class AnsiSkippingStringIteratorTest_36 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Default construction from a simple string, dereference first character
TEST_F(AnsiSkippingStringIteratorTest_36, DereferenceFirstChar_36) {
    std::string s = "Hello";
    AnsiSkippingString::const_iterator it(s);
    EXPECT_EQ(*it, 'H');
}

// Test: Iterate through a simple string character by character
TEST_F(AnsiSkippingStringIteratorTest_36, IterateThroughSimpleString_36) {
    std::string s = "abc";
    AnsiSkippingString::const_iterator it(s);
    EXPECT_EQ(*it, 'a');
    ++it;
    EXPECT_EQ(*it, 'b');
    ++it;
    EXPECT_EQ(*it, 'c');
}

// Test: Post-increment returns previous position
TEST_F(AnsiSkippingStringIteratorTest_36, PostIncrementReturnsPrevious_36) {
    std::string s = "xy";
    AnsiSkippingString::const_iterator it(s);
    auto prev = it++;
    EXPECT_EQ(*prev, 'x');
    EXPECT_EQ(*it, 'y');
}

// Test: Pre-decrement goes back one character
TEST_F(AnsiSkippingStringIteratorTest_36, PreDecrementGoesBack_36) {
    std::string s = "ab";
    AnsiSkippingString::const_iterator it(s);
    ++it;
    EXPECT_EQ(*it, 'b');
    --it;
    EXPECT_EQ(*it, 'a');
}

// Test: Post-decrement returns current before decrementing
TEST_F(AnsiSkippingStringIteratorTest_36, PostDecrementReturnsCurrent_36) {
    std::string s = "ab";
    AnsiSkippingString::const_iterator it(s);
    ++it;
    auto prev = it--;
    EXPECT_EQ(*prev, 'b');
    EXPECT_EQ(*it, 'a');
}

// Test: Equality of two iterators pointing to the same position
TEST_F(AnsiSkippingStringIteratorTest_36, EqualityOfSamePosition_36) {
    std::string s = "test";
    AnsiSkippingString::const_iterator it1(s);
    AnsiSkippingString::const_iterator it2(s);
    EXPECT_TRUE(it1 == it2);
    EXPECT_FALSE(it1 != it2);
}

// Test: Inequality after advancing one iterator
TEST_F(AnsiSkippingStringIteratorTest_36, InequalityAfterAdvance_36) {
    std::string s = "test";
    AnsiSkippingString::const_iterator it1(s);
    AnsiSkippingString::const_iterator it2(s);
    ++it2;
    EXPECT_TRUE(it1 != it2);
    EXPECT_FALSE(it1 == it2);
}

// Test: Less-than-or-equal comparison
TEST_F(AnsiSkippingStringIteratorTest_36, LessThanOrEqualComparison_36) {
    std::string s = "abc";
    AnsiSkippingString::const_iterator it1(s);
    AnsiSkippingString::const_iterator it2(s);
    EXPECT_TRUE(it1 <= it2);  // equal
    ++it2;
    EXPECT_TRUE(it1 <= it2);  // it1 < it2
}

// Test: oneBefore returns iterator one position before current
TEST_F(AnsiSkippingStringIteratorTest_36, OneBeforeReturnsCorrectIterator_36) {
    std::string s = "xyz";
    AnsiSkippingString::const_iterator it(s);
    ++it;
    ++it;
    auto before = it.oneBefore();
    EXPECT_EQ(*before, 'y');
}

// Test: ANSI escape sequences are skipped
TEST_F(AnsiSkippingStringIteratorTest_36, SkipsAnsiEscapeSequences_36) {
    // ESC[31m is a typical ANSI color code (red)
    std::string s = "\033[31mHello";
    AnsiSkippingString::const_iterator it(s);
    // The iterator should skip the ANSI escape and give us 'H' first
    EXPECT_EQ(*it, 'H');
}

// Test: ANSI escape in the middle of string is skipped
TEST_F(AnsiSkippingStringIteratorTest_36, SkipsAnsiEscapeInMiddle_36) {
    std::string s = "A\033[0mB";
    AnsiSkippingString::const_iterator it(s);
    EXPECT_EQ(*it, 'A');
    ++it;
    EXPECT_EQ(*it, 'B');
}

// Test: Multiple ANSI escapes are skipped
TEST_F(AnsiSkippingStringIteratorTest_36, SkipsMultipleAnsiEscapes_36) {
    std::string s = "\033[1m\033[31mX\033[0m";
    AnsiSkippingString::const_iterator it(s);
    EXPECT_EQ(*it, 'X');
}

// Test: Empty string - begin equals end (iterator constructed from empty string)
TEST_F(AnsiSkippingStringIteratorTest_36, EmptyStringBeginEqualsEnd_36) {
    std::string s = "";
    AnsiSkippingString::const_iterator begin(s);
    // For an empty string, the iterator at begin should be at end
    // We can test by checking that two iterators from the same empty string are equal
    AnsiSkippingString::const_iterator begin2(s);
    EXPECT_TRUE(begin == begin2);
}

// Test: Single character string
TEST_F(AnsiSkippingStringIteratorTest_36, SingleCharacterString_36) {
    std::string s = "Z";
    AnsiSkippingString::const_iterator it(s);
    EXPECT_EQ(*it, 'Z');
}

// Test: String with only ANSI escape (no visible characters)
TEST_F(AnsiSkippingStringIteratorTest_36, StringWithOnlyAnsiEscape_36) {
    std::string s = "\033[31m";
    AnsiSkippingString::const_iterator it1(s);
    AnsiSkippingString::const_iterator it2(s);
    // Both should be at the same position (effectively end)
    EXPECT_TRUE(it1 == it2);
}

// Test: Iterate forward and backward, ending at original position
TEST_F(AnsiSkippingStringIteratorTest_36, ForwardAndBackwardReturnsToStart_36) {
    std::string s = "Hello";
    AnsiSkippingString::const_iterator it(s);
    AnsiSkippingString::const_iterator start(s);
    ++it;
    ++it;
    --it;
    --it;
    EXPECT_TRUE(it == start);
    EXPECT_EQ(*it, 'H');
}

// Test: Special characters (non-ANSI) are not skipped
TEST_F(AnsiSkippingStringIteratorTest_36, SpecialCharsNotSkipped_36) {
    std::string s = "!@#$";
    AnsiSkippingString::const_iterator it(s);
    EXPECT_EQ(*it, '!');
    ++it;
    EXPECT_EQ(*it, '@');
    ++it;
    EXPECT_EQ(*it, '#');
    ++it;
    EXPECT_EQ(*it, '$');
}

// Test: Spaces and tabs are preserved
TEST_F(AnsiSkippingStringIteratorTest_36, SpacesAndTabsPreserved_36) {
    std::string s = " \t ";
    AnsiSkippingString::const_iterator it(s);
    EXPECT_EQ(*it, ' ');
    ++it;
    EXPECT_EQ(*it, '\t');
    ++it;
    EXPECT_EQ(*it, ' ');
}

// Test: Newline characters are preserved
TEST_F(AnsiSkippingStringIteratorTest_36, NewlinePreserved_36) {
    std::string s = "a\nb";
    AnsiSkippingString::const_iterator it(s);
    EXPECT_EQ(*it, 'a');
    ++it;
    EXPECT_EQ(*it, '\n');
    ++it;
    EXPECT_EQ(*it, 'b');
}

// Test: ANSI escape followed by more ANSI escapes and text
TEST_F(AnsiSkippingStringIteratorTest_36, ComplexAnsiSequence_36) {
    std::string s = "\033[1;31;40mRed\033[0m";
    AnsiSkippingString::const_iterator it(s);
    EXPECT_EQ(*it, 'R');
    ++it;
    EXPECT_EQ(*it, 'e');
    ++it;
    EXPECT_EQ(*it, 'd');
}

// Test: <= operator when iterators are equal
TEST_F(AnsiSkippingStringIteratorTest_36, LessOrEqualWhenEqual_36) {
    std::string s = "abc";
    AnsiSkippingString::const_iterator it1(s);
    AnsiSkippingString::const_iterator it2(s);
    ++it1;
    ++it2;
    EXPECT_TRUE(it1 <= it2);
    EXPECT_TRUE(it2 <= it1);
}
