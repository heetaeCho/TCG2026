// File: tests/ansi_skipping_string_iterator_test_36.cpp

#include <gtest/gtest.h>
#include <string>

// Include the header under test
#include "Catch2/src/catch2/internal/catch_textflow.hpp"

namespace {

using Iterator = Catch::TextFlow::AnsiSkippingString::const_iterator;

class AnsiSkippingStringIteratorTest_36 : public ::testing::Test {
protected:
    static Iterator Make(const std::string& s) {
        // Uses the explicit constructor that takes a const std::string&
        return Iterator(s);
    }
};

} // namespace

// --- Normal operation ---

TEST_F(AnsiSkippingStringIteratorTest_36, DereferenceReturnsCurrentChar_36) {
    const std::string s = "abc";
    auto it = Make(s);

    // Observable behavior: operator*() const returns a char for current position.
    EXPECT_EQ(*it, 'a');
}

TEST_F(AnsiSkippingStringIteratorTest_36, PrefixIncrementAdvancesPosition_36) {
    const std::string s = "abc";
    auto it = Make(s);

    ++it;
    EXPECT_EQ(*it, 'b');

    ++it;
    EXPECT_EQ(*it, 'c');
}

TEST_F(AnsiSkippingStringIteratorTest_36, PostfixIncrementAdvancesPositionAndYieldsOld_36) {
    const std::string s = "xyz";
    auto it = Make(s);

    char first = *it++;
    EXPECT_EQ(first, 'x');   // value before increment
    EXPECT_EQ(*it, 'y');     // now advanced
}

// --- Boundary-ish (within defined observable use; no reliance on internals) ---

TEST_F(AnsiSkippingStringIteratorTest_36, DecrementAfterIncrementReturnsToPrevious_36) {
    const std::string s = "pq";
    auto it = Make(s);

    ++it;             // move to 'q'
    EXPECT_EQ(*it, 'q');

    --it;             // move back to 'p'
    EXPECT_EQ(*it, 'p');
}

TEST_F(AnsiSkippingStringIteratorTest_36, PostfixDecrementMovesBack_36) {
    const std::string s = "hi";
    auto it = Make(s);

    ++it; // now at 'i'
    char before = *it--;
    EXPECT_EQ(before, 'i');  // value before decrement
    EXPECT_EQ(*it, 'h');     // now moved back
}

// --- Relational and utility operations ---

TEST_F(AnsiSkippingStringIteratorTest_36, EqualityAndInequalityOnSameSequence_36) {
    const std::string s = "12";
    auto it1 = Make(s);
    auto it2 = Make(s);

    EXPECT_TRUE(it1 == it2);
    EXPECT_FALSE(it1 != it2);

    ++it2;
    EXPECT_FALSE(it1 == it2);
    EXPECT_TRUE(it1 != it2);
}

TEST_F(AnsiSkippingStringIteratorTest_36, LessEqualReflectsNotAfterIncrement_36) {
    const std::string s = "ab";
    auto a = Make(s);   // at 'a'
    auto b = Make(s);   // also at 'a'

    ++b;                // at 'b'
    // We only rely on the public operator<= existing and being consistent.
    EXPECT_TRUE(a <= b);
    EXPECT_TRUE(a <= a);
    EXPECT_FALSE(b <= a); // after increment, b should not be <= a
}

TEST_F(AnsiSkippingStringIteratorTest_36, OneBeforeReturnsIteratorToPreviousPosition_36) {
    const std::string s = "frog";
    auto it = Make(s);     // 'f'
    ++it;                  // 'r'
    auto prev = it.oneBefore();

    // Observable behavior: dereferencing 'prev' should yield previous element.
    EXPECT_EQ(*prev, 'f');

    // And original iterator remains unchanged at current position.
    EXPECT_EQ(*it, 'r');
}

// --- Mixed prefix/postfix sequences ---

TEST_F(AnsiSkippingStringIteratorTest_36, MixedIncrementsAndDecrementsMaintainCoherentTraversal_36) {
    const std::string s = "wxyz";
    auto it = Make(s);   // 'w'

    EXPECT_EQ(*it, 'w');
    it++;                // -> 'x'
    EXPECT_EQ(*it, 'x');
    ++it;                // -> 'y'
    EXPECT_EQ(*it, 'y');
    it--;                // -> 'x'
    EXPECT_EQ(*it, 'x');
    --it;                // -> 'w'
    EXPECT_EQ(*it, 'w');
}
