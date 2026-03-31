#include "catch2/internal/catch_textflow.hpp"
#include <gtest/gtest.h>
#include <string>

using namespace Catch::TextFlow;

class AnsiSkippingStringTest_39 : public ::testing::Test {
protected:
    void SetUp() override {}
};

// Test basic construction and dereferencing
TEST_F(AnsiSkippingStringTest_39, DefaultConstructFromString_39) {
    std::string s = "hello";
    AnsiSkippingString str(s);
    auto it = str.begin();
    EXPECT_EQ(*it, 'h');
}

// Test iterating through a simple string
TEST_F(AnsiSkippingStringTest_39, IterateThroughSimpleString_39) {
    std::string s = "abc";
    AnsiSkippingString str(s);
    auto it = str.begin();
    EXPECT_EQ(*it, 'a');
    ++it;
    EXPECT_EQ(*it, 'b');
    ++it;
    EXPECT_EQ(*it, 'c');
}

// Test pre-increment returns reference
TEST_F(AnsiSkippingStringTest_39, PreIncrementReturnsReference_39) {
    std::string s = "ab";
    AnsiSkippingString str(s);
    auto it = str.begin();
    auto& ref = ++it;
    EXPECT_EQ(*ref, 'b');
    EXPECT_EQ(*it, 'b');
}

// Test post-increment returns previous value
TEST_F(AnsiSkippingStringTest_39, PostIncrementReturnsPrevious_39) {
    std::string s = "ab";
    AnsiSkippingString str(s);
    auto it = str.begin();
    auto prev = it++;
    EXPECT_EQ(*prev, 'a');
    EXPECT_EQ(*it, 'b');
}

// Test pre-decrement
TEST_F(AnsiSkippingStringTest_39, PreDecrementGoesBack_39) {
    std::string s = "ab";
    AnsiSkippingString str(s);
    auto it = str.begin();
    ++it;
    EXPECT_EQ(*it, 'b');
    --it;
    EXPECT_EQ(*it, 'a');
}

// Test post-decrement returns current before decrementing
TEST_F(AnsiSkippingStringTest_39, PostDecrementReturnsCurrent_39) {
    std::string s = "ab";
    AnsiSkippingString str(s);
    auto it = str.begin();
    ++it;
    auto prev = it--;
    EXPECT_EQ(*prev, 'b');
    EXPECT_EQ(*it, 'a');
}

// Test equality operator
TEST_F(AnsiSkippingStringTest_39, EqualityOperator_39) {
    std::string s = "abc";
    AnsiSkippingString str(s);
    auto it1 = str.begin();
    auto it2 = str.begin();
    EXPECT_TRUE(it1 == it2);
}

// Test inequality operator
TEST_F(AnsiSkippingStringTest_39, InequalityOperator_39) {
    std::string s = "abc";
    AnsiSkippingString str(s);
    auto it1 = str.begin();
    auto it2 = str.begin();
    ++it2;
    EXPECT_TRUE(it1 != it2);
}

// Test less-than-or-equal operator
TEST_F(AnsiSkippingStringTest_39, LessThanOrEqualOperator_39) {
    std::string s = "abc";
    AnsiSkippingString str(s);
    auto it1 = str.begin();
    auto it2 = str.begin();
    EXPECT_TRUE(it1 <= it2);
    ++it2;
    EXPECT_TRUE(it1 <= it2);
    EXPECT_FALSE(it2 <= it1);
}

// Test begin equals begin
TEST_F(AnsiSkippingStringTest_39, BeginEqualsBegin_39) {
    std::string s = "test";
    AnsiSkippingString str(s);
    EXPECT_TRUE(str.begin() == str.begin());
}

// Test end equals end
TEST_F(AnsiSkippingStringTest_39, EndEqualsEnd_39) {
    std::string s = "test";
    AnsiSkippingString str(s);
    EXPECT_TRUE(str.end() == str.end());
}

// Test begin != end for non-empty string
TEST_F(AnsiSkippingStringTest_39, BeginNotEqualsEndForNonEmpty_39) {
    std::string s = "x";
    AnsiSkippingString str(s);
    EXPECT_TRUE(str.begin() != str.end());
}

// Test begin == end for empty string
TEST_F(AnsiSkippingStringTest_39, BeginEqualsEndForEmptyString_39) {
    std::string s = "";
    AnsiSkippingString str(s);
    EXPECT_TRUE(str.begin() == str.end());
}

// Test ANSI escape sequences are skipped
TEST_F(AnsiSkippingStringTest_39, SkipsAnsiEscapeSequences_39) {
    // ANSI escape: ESC[31m (red color)
    std::string s = "\033[31mA";
    AnsiSkippingString str(s);
    auto it = str.begin();
    // The iterator should skip the ANSI escape and give us 'A'
    EXPECT_EQ(*it, 'A');
}

// Test ANSI escape in the middle of string
TEST_F(AnsiSkippingStringTest_39, SkipsAnsiEscapeInMiddle_39) {
    std::string s = "A\033[0mB";
    AnsiSkippingString str(s);
    auto it = str.begin();
    EXPECT_EQ(*it, 'A');
    ++it;
    EXPECT_EQ(*it, 'B');
}

// Test multiple ANSI escapes
TEST_F(AnsiSkippingStringTest_39, SkipsMultipleAnsiEscapes_39) {
    std::string s = "\033[1m\033[31mHi\033[0m";
    AnsiSkippingString str(s);
    auto it = str.begin();
    EXPECT_EQ(*it, 'H');
    ++it;
    EXPECT_EQ(*it, 'i');
}

// Test oneBefore
TEST_F(AnsiSkippingStringTest_39, OneBeforeReturnsIteratorBefore_39) {
    std::string s = "abc";
    AnsiSkippingString str(s);
    auto it = str.begin();
    ++it; // points to 'b'
    auto before = it.oneBefore();
    EXPECT_EQ(*before, 'a');
}

// Test iterating to end and back
TEST_F(AnsiSkippingStringTest_39, IterateToEndAndBack_39) {
    std::string s = "ab";
    AnsiSkippingString str(s);
    auto it = str.begin();
    ++it;
    ++it;
    EXPECT_TRUE(it == str.end());
    --it;
    EXPECT_EQ(*it, 'b');
    --it;
    EXPECT_EQ(*it, 'a');
    EXPECT_TRUE(it == str.begin());
}

// Test single character string
TEST_F(AnsiSkippingStringTest_39, SingleCharacterString_39) {
    std::string s = "X";
    AnsiSkippingString str(s);
    auto it = str.begin();
    EXPECT_EQ(*it, 'X');
    ++it;
    EXPECT_TRUE(it == str.end());
}

// Test string with spaces
TEST_F(AnsiSkippingStringTest_39, StringWithSpaces_39) {
    std::string s = "a b";
    AnsiSkippingString str(s);
    auto it = str.begin();
    EXPECT_EQ(*it, 'a');
    ++it;
    EXPECT_EQ(*it, ' ');
    ++it;
    EXPECT_EQ(*it, 'b');
}

// Test <= with equal iterators
TEST_F(AnsiSkippingStringTest_39, LessEqualWithEqualIterators_39) {
    std::string s = "abc";
    AnsiSkippingString str(s);
    auto it = str.begin();
    auto it2 = str.begin();
    EXPECT_TRUE(it <= it2);
    EXPECT_TRUE(it2 <= it);
}

// Test string with only ANSI codes
TEST_F(AnsiSkippingStringTest_39, StringWithOnlyAnsiCodes_39) {
    std::string s = "\033[31m\033[0m";
    AnsiSkippingString str(s);
    EXPECT_TRUE(str.begin() == str.end());
}
