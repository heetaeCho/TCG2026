// File: ansi_skipping_string_const_iterator_eq_tests_41.cpp
#include <gtest/gtest.h>
#include <string>

// Adjust this include path if your project layout differs.
#include "catch2/internal/catch_textflow.hpp"

using Iter = Catch::TextFlow::AnsiSkippingString::const_iterator;

class AnsiSkippingStringConstIteratorTest_41 : public ::testing::Test {};

// Reflexivity: iterator equals itself.
TEST_F(AnsiSkippingStringConstIteratorTest_41, SelfEquality_41) {
    std::string s = "hi";
    Iter it(s);
    EXPECT_TRUE(it == it);
}

// Copy-constructed iterators (same position, same underlying string) compare equal.
TEST_F(AnsiSkippingStringConstIteratorTest_41, CopyConstructedIteratorsAreEqual_41) {
    std::string s = "hello";
    Iter it1(s);
    Iter it2 = it1;
    EXPECT_TRUE(it1 == it2);
}

// After advancing one iterator, they no longer compare equal.
TEST_F(AnsiSkippingStringConstIteratorTest_41, PreIncrementChangesPosition_Inequality_41) {
    std::string s = "ab";
    Iter it1(s);
    Iter it2 = it1;
    ++it2; // move forward from the initial position
    EXPECT_FALSE(it1 == it2);
}

// Advancing and then moving back restores equality.
TEST_F(AnsiSkippingStringConstIteratorTest_41, DecrementRestoresEquality_41) {
    std::string s = "ab";
    Iter it1(s);
    Iter it2 = it1;
    ++it2;     // move away from it1
    --it2;     // return to original position
    EXPECT_TRUE(it1 == it2);
}

// Post-increment returns the old position; returned value equals the pre-increment iterator.
TEST_F(AnsiSkippingStringConstIteratorTest_41, PostIncrementReturnsOldPosition_41) {
    std::string s = "abc";
    Iter it(s);
    Iter before = it;
    Iter returned = it++;   // returned should represent the old position
    EXPECT_TRUE(returned == before);
    EXPECT_FALSE(returned == it);  // after increment, current position differs from returned
}

// For an empty string, begin() == end() for the underlying string; two iterators
// constructed at the start position compare equal.
TEST_F(AnsiSkippingStringConstIteratorTest_41, EmptyString_BeginEqualsBegin_41) {
    std::string s; // empty
    Iter it1(s);
    Iter it2(s);
    EXPECT_TRUE(it1 == it2);
}

// Iterators independently advanced to the same position over the same string compare equal.
TEST_F(AnsiSkippingStringConstIteratorTest_41, SamePositionFromIndependentAdvances_41) {
    std::string s = "abcdef";
    Iter it1(s);
    Iter it2(s);

    ++it1; ++it1;   // advance twice
    ++it2; ++it2;   // advance twice in a separate iterator

    EXPECT_TRUE(it1 == it2);
}

// Equality is transitive: if a==b and b==c, then a==c.
TEST_F(AnsiSkippingStringConstIteratorTest_41, EqualityTransitivity_41) {
    std::string s = "xyz";
    Iter a(s);
    Iter b = a;
    Iter c = b;

    EXPECT_TRUE(a == b);
    EXPECT_TRUE(b == c);
    EXPECT_TRUE(a == c);
}
