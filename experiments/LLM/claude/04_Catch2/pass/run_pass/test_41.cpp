#include "catch2/internal/catch_textflow.hpp"
#include <gtest/gtest.h>
#include <string>

using namespace Catch::TextFlow;

class AnsiSkippingStringIteratorTest_41 : public ::testing::Test {
protected:
};

TEST_F(AnsiSkippingStringIteratorTest_41, DefaultConstructFromString_41) {
    std::string s = "hello";
    AnsiSkippingString::const_iterator it(s);
    // Iterator should be valid and dereferenceable
    EXPECT_EQ(*it, 'h');
}

TEST_F(AnsiSkippingStringIteratorTest_41, DereferenceFirstChar_41) {
    std::string s = "abcdef";
    AnsiSkippingString::const_iterator it(s);
    EXPECT_EQ(*it, 'a');
}

TEST_F(AnsiSkippingStringIteratorTest_41, PreIncrementAdvances_41) {
    std::string s = "abc";
    AnsiSkippingString::const_iterator it(s);
    ++it;
    EXPECT_EQ(*it, 'b');
}

TEST_F(AnsiSkippingStringIteratorTest_41, PostIncrementAdvances_41) {
    std::string s = "abc";
    AnsiSkippingString::const_iterator it(s);
    AnsiSkippingString::const_iterator prev = it++;
    EXPECT_EQ(*prev, 'a');
    EXPECT_EQ(*it, 'b');
}

TEST_F(AnsiSkippingStringIteratorTest_41, PreDecrementGoesBack_41) {
    std::string s = "abc";
    AnsiSkippingString::const_iterator it(s);
    ++it;
    ++it;
    --it;
    EXPECT_EQ(*it, 'b');
}

TEST_F(AnsiSkippingStringIteratorTest_41, PostDecrementGoesBack_41) {
    std::string s = "abc";
    AnsiSkippingString::const_iterator it(s);
    ++it;
    ++it;
    AnsiSkippingString::const_iterator prev = it--;
    EXPECT_EQ(*prev, 'c');
    EXPECT_EQ(*it, 'b');
}

TEST_F(AnsiSkippingStringIteratorTest_41, EqualityOperator_41) {
    std::string s = "abc";
    AnsiSkippingString::const_iterator it1(s);
    AnsiSkippingString::const_iterator it2(s);
    EXPECT_TRUE(it1 == it2);
}

TEST_F(AnsiSkippingStringIteratorTest_41, InequalityOperator_41) {
    std::string s = "abc";
    AnsiSkippingString::const_iterator it1(s);
    AnsiSkippingString::const_iterator it2(s);
    ++it2;
    EXPECT_TRUE(it1 != it2);
}

TEST_F(AnsiSkippingStringIteratorTest_41, LessThanOrEqualOperator_41) {
    std::string s = "abc";
    AnsiSkippingString::const_iterator it1(s);
    AnsiSkippingString::const_iterator it2(s);
    ++it2;
    EXPECT_TRUE(it1 <= it2);
    EXPECT_TRUE(it1 <= it1);
    EXPECT_FALSE(it2 <= it1);
}

TEST_F(AnsiSkippingStringIteratorTest_41, IterateThroughEntireString_41) {
    std::string s = "hello";
    AnsiSkippingString::const_iterator it(s);
    std::string result;
    for (size_t i = 0; i < s.size(); ++i) {
        result += *it;
        ++it;
    }
    EXPECT_EQ(result, "hello");
}

TEST_F(AnsiSkippingStringIteratorTest_41, SkipsAnsiEscapeSequences_41) {
    // ANSI escape: ESC[31m (red color)
    std::string s = "\033[31mhello\033[0m";
    AnsiSkippingString::const_iterator it(s);
    // The iterator should skip ANSI sequences and give us 'h' first
    EXPECT_EQ(*it, 'h');
}

TEST_F(AnsiSkippingStringIteratorTest_41, SkipsAnsiAndIteratesContent_41) {
    std::string s = "\033[31mab\033[0m";
    AnsiSkippingString::const_iterator it(s);
    std::string result;
    // Collect visible characters
    EXPECT_EQ(*it, 'a');
    ++it;
    EXPECT_EQ(*it, 'b');
}

TEST_F(AnsiSkippingStringIteratorTest_41, OneBeforeReturnsCorrectIterator_41) {
    std::string s = "abc";
    AnsiSkippingString::const_iterator it(s);
    ++it;
    ++it;
    AnsiSkippingString::const_iterator before = it.oneBefore();
    EXPECT_EQ(*before, 'b');
}

TEST_F(AnsiSkippingStringIteratorTest_41, EmptyString_41) {
    std::string s = "";
    AnsiSkippingString::const_iterator it1(s);
    AnsiSkippingString::const_iterator it2(s);
    EXPECT_TRUE(it1 == it2);
}

TEST_F(AnsiSkippingStringIteratorTest_41, SingleCharacterString_41) {
    std::string s = "x";
    AnsiSkippingString::const_iterator it(s);
    EXPECT_EQ(*it, 'x');
}

TEST_F(AnsiSkippingStringIteratorTest_41, OnlyAnsiSequence_41) {
    std::string s = "\033[31m\033[0m";
    AnsiSkippingString::const_iterator it1(s);
    AnsiSkippingString::const_iterator it2(s);
    // Both should effectively be at the same position since there's no visible content
    // After skipping ANSI, iterators from begin should be equal
}

TEST_F(AnsiSkippingStringIteratorTest_41, MultipleAnsiSequencesBetweenChars_41) {
    std::string s = "\033[1m\033[31ma\033[0m";
    AnsiSkippingString::const_iterator it(s);
    EXPECT_EQ(*it, 'a');
}

TEST_F(AnsiSkippingStringIteratorTest_41, EqualIteratorsAfterSameAdvancement_41) {
    std::string s = "abcdef";
    AnsiSkippingString::const_iterator it1(s);
    AnsiSkippingString::const_iterator it2(s);
    ++it1;
    ++it1;
    ++it2;
    ++it2;
    EXPECT_TRUE(it1 == it2);
}

TEST_F(AnsiSkippingStringIteratorTest_41, DecrementAfterIncrementReturnsToOriginal_41) {
    std::string s = "abc";
    AnsiSkippingString::const_iterator it(s);
    AnsiSkippingString::const_iterator original(s);
    ++it;
    --it;
    EXPECT_TRUE(it == original);
    EXPECT_EQ(*it, 'a');
}

TEST_F(AnsiSkippingStringIteratorTest_41, SelfEqualityAlwaysTrue_41) {
    std::string s = "test";
    AnsiSkippingString::const_iterator it(s);
    EXPECT_TRUE(it == it);
    EXPECT_FALSE(it != it);
    EXPECT_TRUE(it <= it);
}
