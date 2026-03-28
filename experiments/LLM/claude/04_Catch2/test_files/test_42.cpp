#include <gtest/gtest.h>
#include "catch2/internal/catch_textflow.hpp"
#include <string>

using namespace Catch::TextFlow;

// ============================================================
// Tests for AnsiSkippingString
// ============================================================

class AnsiSkippingStringTest_42 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Default construction from empty string
TEST_F(AnsiSkippingStringTest_42, EmptyStringBeginEqualsEnd_42) {
    std::string empty = "";
    AnsiSkippingString ass(empty);
    EXPECT_TRUE(ass.begin() == ass.end());
}

// Test: Non-empty string begin != end
TEST_F(AnsiSkippingStringTest_42, NonEmptyStringBeginNotEqualsEnd_42) {
    std::string s = "Hello";
    AnsiSkippingString ass(s);
    EXPECT_TRUE(ass.begin() != ass.end());
}

// Test: Iterating through a simple string gives correct characters
TEST_F(AnsiSkippingStringTest_42, IterateThroughSimpleString_42) {
    std::string s = "abc";
    AnsiSkippingString ass(s);
    std::string result;
    for (auto it = ass.begin(); it != ass.end(); ++it) {
        result += *it;
    }
    EXPECT_EQ(result, "abc");
}

// Test: Dereference operator returns correct character
TEST_F(AnsiSkippingStringTest_42, DereferenceOperator_42) {
    std::string s = "X";
    AnsiSkippingString ass(s);
    auto it = ass.begin();
    EXPECT_EQ(*it, 'X');
}

// Test: Pre-increment advances iterator
TEST_F(AnsiSkippingStringTest_42, PreIncrementAdvances_42) {
    std::string s = "AB";
    AnsiSkippingString ass(s);
    auto it = ass.begin();
    EXPECT_EQ(*it, 'A');
    ++it;
    EXPECT_EQ(*it, 'B');
}

// Test: Post-increment advances but returns old position
TEST_F(AnsiSkippingStringTest_42, PostIncrementReturnsPrevious_42) {
    std::string s = "CD";
    AnsiSkippingString ass(s);
    auto it = ass.begin();
    auto old = it++;
    EXPECT_EQ(*old, 'C');
    EXPECT_EQ(*it, 'D');
}

// Test: Pre-decrement goes back
TEST_F(AnsiSkippingStringTest_42, PreDecrementGoesBack_42) {
    std::string s = "EF";
    AnsiSkippingString ass(s);
    auto it = ass.begin();
    ++it; // now at 'F'
    EXPECT_EQ(*it, 'F');
    --it;
    EXPECT_EQ(*it, 'E');
}

// Test: Post-decrement goes back but returns old position
TEST_F(AnsiSkippingStringTest_42, PostDecrementReturnsCurrent_42) {
    std::string s = "GH";
    AnsiSkippingString ass(s);
    auto it = ass.begin();
    ++it; // now at 'H'
    auto old = it--;
    EXPECT_EQ(*old, 'H');
    EXPECT_EQ(*it, 'G');
}

// Test: Equality operator for same position
TEST_F(AnsiSkippingStringTest_42, EqualityOperator_42) {
    std::string s = "test";
    AnsiSkippingString ass(s);
    auto it1 = ass.begin();
    auto it2 = ass.begin();
    EXPECT_TRUE(it1 == it2);
}

// Test: Inequality operator for different positions
TEST_F(AnsiSkippingStringTest_42, InequalityOperator_42) {
    std::string s = "test";
    AnsiSkippingString ass(s);
    auto it1 = ass.begin();
    auto it2 = ass.begin();
    ++it2;
    EXPECT_TRUE(it1 != it2);
}

// Test: operator!= is negation of operator==
TEST_F(AnsiSkippingStringTest_42, InequalityIsNegationOfEquality_42) {
    std::string s = "ab";
    AnsiSkippingString ass(s);
    auto it1 = ass.begin();
    auto it2 = ass.begin();
    // Same position: == true, != false
    EXPECT_TRUE(it1 == it2);
    EXPECT_FALSE(it1 != it2);
    ++it2;
    // Different position: == false, != true
    EXPECT_FALSE(it1 == it2);
    EXPECT_TRUE(it1 != it2);
}

// Test: operator<= for same position
TEST_F(AnsiSkippingStringTest_42, LessEqualSamePosition_42) {
    std::string s = "xyz";
    AnsiSkippingString ass(s);
    auto it1 = ass.begin();
    auto it2 = ass.begin();
    EXPECT_TRUE(it1 <= it2);
}

// Test: operator<= for earlier position
TEST_F(AnsiSkippingStringTest_42, LessEqualEarlierPosition_42) {
    std::string s = "xyz";
    AnsiSkippingString ass(s);
    auto it1 = ass.begin();
    auto it2 = ass.begin();
    ++it2;
    EXPECT_TRUE(it1 <= it2);
}

// Test: operator<= for later position
TEST_F(AnsiSkippingStringTest_42, LessEqualLaterPositionIsFalse_42) {
    std::string s = "xyz";
    AnsiSkippingString ass(s);
    auto it1 = ass.begin();
    auto it2 = ass.begin();
    ++it1;
    EXPECT_FALSE(it1 <= it2);
}

// Test: oneBefore returns iterator one position before
TEST_F(AnsiSkippingStringTest_42, OneBeforeReturnsCorrectPosition_42) {
    std::string s = "abc";
    AnsiSkippingString ass(s);
    auto it = ass.begin();
    ++it; // now at 'b'
    auto before = it.oneBefore();
    EXPECT_EQ(*before, 'a');
}

// Test: ANSI escape sequences are skipped
TEST_F(AnsiSkippingStringTest_42, AnsiEscapeSequencesAreSkipped_42) {
    // ANSI escape: ESC[31m (red color)
    std::string s = "\033[31mHello\033[0m";
    AnsiSkippingString ass(s);
    std::string result;
    for (auto it = ass.begin(); it != ass.end(); ++it) {
        result += *it;
    }
    EXPECT_EQ(result, "Hello");
}

// Test: String with only ANSI escape - should produce empty iteration
TEST_F(AnsiSkippingStringTest_42, OnlyAnsiEscapeProducesEmpty_42) {
    std::string s = "\033[31m\033[0m";
    AnsiSkippingString ass(s);
    std::string result;
    for (auto it = ass.begin(); it != ass.end(); ++it) {
        result += *it;
    }
    EXPECT_EQ(result, "");
}

// Test: Single character string
TEST_F(AnsiSkippingStringTest_42, SingleCharacterString_42) {
    std::string s = "Z";
    AnsiSkippingString ass(s);
    auto it = ass.begin();
    EXPECT_NE(it, ass.end());
    EXPECT_EQ(*it, 'Z');
    ++it;
    EXPECT_EQ(it, ass.end());
}

// Test: Iterate full string and count characters
TEST_F(AnsiSkippingStringTest_42, CountCharactersInIteration_42) {
    std::string s = "Hello, World!";
    AnsiSkippingString ass(s);
    int count = 0;
    for (auto it = ass.begin(); it != ass.end(); ++it) {
        ++count;
    }
    EXPECT_EQ(count, 13);
}

// Test: String with mixed ANSI and text
TEST_F(AnsiSkippingStringTest_42, MixedAnsiAndText_42) {
    std::string s = "A\033[1mB\033[0mC";
    AnsiSkippingString ass(s);
    std::string result;
    for (auto it = ass.begin(); it != ass.end(); ++it) {
        result += *it;
    }
    EXPECT_EQ(result, "ABC");
}

// Test: Increment then decrement returns to original
TEST_F(AnsiSkippingStringTest_42, IncrementThenDecrementReturnsToOriginal_42) {
    std::string s = "abcdef";
    AnsiSkippingString ass(s);
    auto it = ass.begin();
    auto original = it;
    ++it;
    --it;
    EXPECT_EQ(it, original);
    EXPECT_EQ(*it, 'a');
}

// Test: Multiple increments iterate correctly
TEST_F(AnsiSkippingStringTest_42, MultipleIncrements_42) {
    std::string s = "12345";
    AnsiSkippingString ass(s);
    auto it = ass.begin();
    EXPECT_EQ(*it, '1');
    ++it;
    EXPECT_EQ(*it, '2');
    ++it;
    EXPECT_EQ(*it, '3');
    ++it;
    EXPECT_EQ(*it, '4');
    ++it;
    EXPECT_EQ(*it, '5');
    ++it;
    EXPECT_EQ(it, ass.end());
}

// Test: End iterator equality
TEST_F(AnsiSkippingStringTest_42, EndIteratorEquality_42) {
    std::string s = "ab";
    AnsiSkippingString ass(s);
    auto end1 = ass.end();
    auto end2 = ass.end();
    EXPECT_TRUE(end1 == end2);
}

// Test: begin <= end for non-empty string
TEST_F(AnsiSkippingStringTest_42, BeginLessEqualEnd_42) {
    std::string s = "test";
    AnsiSkippingString ass(s);
    EXPECT_TRUE(ass.begin() <= ass.end());
}

// Test: String with spaces
TEST_F(AnsiSkippingStringTest_42, StringWithSpaces_42) {
    std::string s = "a b c";
    AnsiSkippingString ass(s);
    std::string result;
    for (auto it = ass.begin(); it != ass.end(); ++it) {
        result += *it;
    }
    EXPECT_EQ(result, "a b c");
}

// Test: String with newlines
TEST_F(AnsiSkippingStringTest_42, StringWithNewlines_42) {
    std::string s = "a\nb\nc";
    AnsiSkippingString ass(s);
    std::string result;
    for (auto it = ass.begin(); it != ass.end(); ++it) {
        result += *it;
    }
    EXPECT_EQ(result, "a\nb\nc");
}
