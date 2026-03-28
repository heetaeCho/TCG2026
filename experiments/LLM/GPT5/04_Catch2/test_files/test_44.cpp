// File: ansi_skipping_string_onebefore_tests_44.cpp
#include <gtest/gtest.h>
#include "catch2/internal/catch_textflow.hpp"

using Catch::TextFlow::AnsiSkippingString;

class AnsiSkippingStringIteratorTest_44 : public ::testing::Test {
protected:
    using It = AnsiSkippingString::const_iterator;

    // Helper: construct iterator over `s` and advance `n` steps.
    static It MakeAndAdvance(const std::string& s, size_t n) {
        It it(s);
        for (size_t i = 0; i < n; ++i) { ++it; }
        return it;
    }
};

// [Normal] oneBefore from a middle position returns an iterator to the previous element
TEST_F(AnsiSkippingStringIteratorTest_44, OneBefore_MiddlePosition_44) {
    const std::string s = "ABC";
    It it = MakeAndAdvance(s, 1);          // points to 'B'
    It prev = it.oneBefore();              // should point to 'A'

    // oneBefore should be equivalent to --(copy)
    It expected = it;
    --expected;
    EXPECT_EQ(prev, expected);

    // And prev + 1 should return to original `it`
    It tmp = prev;
    ++tmp;
    EXPECT_EQ(tmp, it);

    // Optional observable char check via const-deref
    const It cprev = prev;
    EXPECT_EQ(*cprev, 'A');
}

// [Safety] Calling oneBefore does not modify the original iterator
TEST_F(AnsiSkippingStringIteratorTest_44, OneBefore_DoesNotModifyOriginal_44) {
    const std::string s = "ABC";
    It it = MakeAndAdvance(s, 2);          // points to 'C'
    It it_copy = it;
    It prev = it.oneBefore();              // prev should point to 'B'

    // Original iterator remains unchanged
    EXPECT_EQ(it, it_copy);

    // prev + 1 should equal original
    It forward = prev;
    ++forward;
    EXPECT_EQ(forward, it);
}

// [Equivalence] Chaining oneBefore twice equals double pre-decrement on a copy
TEST_F(AnsiSkippingStringIteratorTest_44, OneBefore_ChainedTwice_EqualsDoubleDecrement_44) {
    const std::string s = "Hello";
    It it = MakeAndAdvance(s, 3);          // H(0) e(1) l(2) l(3) o(4) -> points to 'l' at index 3
    It two_back = it.oneBefore().oneBefore();

    It expected = it;
    --expected;
    --expected;

    EXPECT_EQ(two_back, expected);

    // Optional observable deref
    const It c_two_back = two_back;
    EXPECT_EQ(*c_two_back, 'e');           // index 1 in "Hello"
}

// [Boundary near begin] From the 2nd character, oneBefore should land on the 1st
TEST_F(AnsiSkippingStringIteratorTest_44, OneBefore_FromSecondCharacter_GoesToFirst_44) {
    const std::string s = "XY";
    It it = MakeAndAdvance(s, 1);          // points to 'Y'
    It prev = it.oneBefore();              // should point to 'X'

    // Compare with an explicitly constructed begin iterator
    It begin_it(s);
    EXPECT_EQ(prev, begin_it);

    // Char check
    const It cprev = prev;
    EXPECT_EQ(*cprev, 'X');
}

// [Boundary at end] From end(), oneBefore should point to the last character
TEST_F(AnsiSkippingStringIteratorTest_44, OneBefore_FromEnd_YieldsLastCharacter_44) {
    const std::string s = "Z";
    It end_it(s);
    ++end_it;                              // advance past the only character -> end

    It last = end_it.oneBefore();          // should point to 'Z'
    It begin_it(s);
    EXPECT_EQ(last, begin_it);             // for 1-char string, last == begin

    // Char check
    const It clast = last;
    EXPECT_EQ(*clast, 'Z');
}
