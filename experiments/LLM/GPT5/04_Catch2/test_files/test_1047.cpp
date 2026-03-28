// File: tests/AnsiSkippingStringIterator_1047.tests.cpp

#include <gtest/gtest.h>
#include <string>

// Include the interface under test.
// Adjust the include path if your project layout differs.
#include "Catch2/src/catch2/internal/catch_textflow.hpp"

using Catch::TextFlow::AnsiSkippingString;

class AnsiSkippingStringIteratorTest_1047 : public ::testing::Test {
protected:
    using Iter = AnsiSkippingString::const_iterator;

    // Common ANSI sequences used in console output
    static std::string Red(const std::string& s)   { return "\x1b[31m" + s + "\x1b[0m"; }
    static std::string Bold(const std::string& s)  { return "\x1b[1m"  + s + "\x1b[0m"; }
};

// --- Normal operation -------------------------------------------------------

// Ensures basic construction on a plain string and correct first character.
TEST_F(AnsiSkippingStringIteratorTest_1047, PlainString_FirstChar_1047) {
    const std::string s = "Hello";
    Iter it{s};

    // Observable: dereferencing yields the first character.
    EXPECT_EQ(*it, 'H');
}

// If the string starts with ANSI escapes, the iterator’s constructor invokes
// its internal parsing (per interface snippet), so the first observable char
// should be the first visible, not an escape prefix.
TEST_F(AnsiSkippingStringIteratorTest_1047, LeadingAnsi_FirstVisibleChar_1047) {
    const std::string s = "\x1b[31mRed\x1b[0m";
    Iter it{s};

    EXPECT_EQ(*it, 'R');
    ++it;
    EXPECT_EQ(*it, 'e');
    ++it;
    EXPECT_EQ(*it, 'd');
}

// Verify pre- and post-increment semantics produce expected characters in order.
TEST_F(AnsiSkippingStringIteratorTest_1047, PrePostIncrement_1047) {
    const std::string s = Red("ABC"); // "\x1b[31mABC\x1b[0m"
    Iter it{s};

    // Start: 'A'
    EXPECT_EQ(*it, 'A');

    // post-increment yields old value, then moves
    Iter old = it++;
    EXPECT_EQ(*old, 'A');
    EXPECT_EQ(*it,  'B');

    // pre-increment moves first, then yields new
    Iter& ref = ++it;
    EXPECT_EQ(&ref, &it); // pre-increment returns reference to self
    EXPECT_EQ(*it,  'C');
}

// --- Boundary-ish (still observable) ----------------------------------------

// Mixed ANSI sequences should not disturb visible traversal order.
TEST_F(AnsiSkippingStringIteratorTest_1047, MixedAnsiSequences_TraversalOrder_1047) {
    const std::string s = Bold("He") + "\x1b[0m" + Red("llo");
    Iter it{s};

    ASSERT_EQ(*it, 'H'); ++it;
    ASSERT_EQ(*it, 'e'); ++it;
    ASSERT_EQ(*it, 'l'); ++it;
    ASSERT_EQ(*it, 'l'); ++it;
    ASSERT_EQ(*it, 'o');
}

// Decrement support: after moving forward, -- should step back to previous
// visible character (observable through dereference).
TEST_F(AnsiSkippingStringIteratorTest_1047, Decrement_RoundTrip_1047) {
    const std::string s = "\x1b[1mXY\x1b[0m";
    Iter it{s};
    ASSERT_EQ(*it, 'X');
    ++it;
    ASSERT_EQ(*it, 'Y');

    --it; // go back to 'X'
    EXPECT_EQ(*it, 'X');
}

// `oneBefore()` should provide an iterator positioned at the previous
// visible character (when one exists).
TEST_F(AnsiSkippingStringIteratorTest_1047, OneBefore_ReturnsPrevious_1047) {
    const std::string s = "\x1b[1mR\x1b[0mG";
    Iter it{s};            // at 'R'
    ++it;                  // now at 'G'

    Iter before = it.oneBefore();
    EXPECT_EQ(*before, 'R');
}

// --- Comparisons & copy semantics -------------------------------------------

// Basic equality/inequality behavior: copies compare equal, advancing breaks equality.
TEST_F(AnsiSkippingStringIteratorTest_1047, EqualityAndInequality_1047) {
    const std::string s = Red("Cat");
    Iter it{s};
    Iter it_copy = it;

    EXPECT_TRUE(it == it_copy);
    EXPECT_FALSE(it != it_copy);

    ++it;
    EXPECT_FALSE(it == it_copy);
    EXPECT_TRUE(it != it_copy);
}

// Ordering-like comparison (`<=`) should be consistent as we advance.
TEST_F(AnsiSkippingStringIteratorTest_1047, LessEqual_MonotonicProgress_1047) {
    const std::string s = "\x1b[31mA\x1b[0mB";
    Iter a{s};
    Iter b = a;

    EXPECT_TRUE(a <= b); // same position
    ++b;
    EXPECT_TRUE(a <= b); // a before b
    ++a;
    EXPECT_TRUE(a <= b); // equal again
}

// --- Edge-adjacent scenario (still black-box safe) --------------------------

// If the visible portion is a single character wrapped in ANSI codes,
// iterator should still dereference to that character after construction.
TEST_F(AnsiSkippingStringIteratorTest_1047, SingleVisibleCharWrappedInAnsi_1047) {
    const std::string s = "\x1b[31mZ\x1b[0m";
    Iter it{s};
    EXPECT_EQ(*it, 'Z');
}
