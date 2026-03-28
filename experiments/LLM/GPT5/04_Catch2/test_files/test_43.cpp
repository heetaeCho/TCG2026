// TEST_ID: 43
// File: tests/AnsiSkippingStringConstIterator_LeTests_43.cpp

#include <gtest/gtest.h>
#include <string>

// Include the provided header
#include "catch2/internal/catch_textflow.hpp"

using ConstIt = Catch::TextFlow::AnsiSkippingString::const_iterator;

namespace {

// --- Normal operation ---

TEST(AnsiSkippingStringConstIteratorLE_43, SelfComparisonIsTrue_43) {
    std::string s = "abc";
    ConstIt a{s};
    ConstIt b = a; // same position
    EXPECT_TRUE(a <= b);
    EXPECT_TRUE(b <= a);
    EXPECT_TRUE(a == b);
}

TEST(AnsiSkippingStringConstIteratorLE_43, BeginIsLessOrEqualThanNext_43) {
    std::string s = "hello";
    ConstIt begin{s};
    ConstIt next = begin;
    next++; // advance one step via post-increment

    EXPECT_TRUE(begin <= next);
    EXPECT_FALSE(next <= begin);
}

TEST(AnsiSkippingStringConstIteratorLE_43, TransitivityHolds_43) {
    std::string s = "abcd";
    ConstIt a{s};      // points to 'a'
    ConstIt b = a; b++; // points to 'b'
    ConstIt c = b; c++; // points to 'c'

    ASSERT_TRUE(a <= b);
    ASSERT_TRUE(b <= c);
    EXPECT_TRUE(a <= c); // transitivity of <=
}

// --- Boundary conditions ---

TEST(AnsiSkippingStringConstIteratorLE_43, EmptyStringIteratorsAreMutuallyLe_43) {
    std::string empty;
    ConstIt a{empty};
    ConstIt b{empty};

    EXPECT_TRUE(a <= b);
    EXPECT_TRUE(b <= a);
    EXPECT_TRUE(a == b);
}

TEST(AnsiSkippingStringConstIteratorLE_43, LastElementOrdering_43) {
    std::string s = "xyzq";
    ASSERT_FALSE(s.empty());

    ConstIt begin{s};
    ConstIt last = begin;

    // Move to the last valid element (avoid touching the end iterator)
    for (std::size_t i = 1; i < s.size(); ++i) {
        last++;
    }

    // Sanity: dereference is valid and equals last character
    ASSERT_EQ(*last, s.back());

    // begin should be <= last, but not vice-versa (strict ordering)
    EXPECT_TRUE(begin <= last);
    EXPECT_FALSE(last <= begin);
}

TEST(AnsiSkippingStringConstIteratorLE_43, PreAndPostIncrementYieldComparablePositions_43) {
    std::string s = "sample";
    ConstIt a{s};

    ConstIt post = a; post++;  // post-increment
    ConstIt pre  = a; ++pre;   // pre-increment

    // Both should refer to the same position, so <= must be true both ways
    EXPECT_TRUE(post <= pre);
    EXPECT_TRUE(pre  <= post);
    EXPECT_TRUE(post == pre);
}

// --- Interaction checks around movement (no private state relied upon) ---

TEST(AnsiSkippingStringConstIteratorLE_43, MovingForwardFlipsLeDirection_43) {
    std::string s = "ab";
    ConstIt it{s};           // 'a'
    ConstIt advanced = it;   // copy at same position
    advanced++;              // now 'b'

    // Before moving back, ordering is it <= advanced and not the other way
    EXPECT_TRUE(it <= advanced);
    EXPECT_FALSE(advanced <= it);

    // Move back and confirm symmetry at same position
    advanced--; // back to 'a'
    EXPECT_TRUE(it <= advanced);
    EXPECT_TRUE(advanced <= it);
    EXPECT_TRUE(it == advanced);
}

} // namespace
