// File: columns_iterator_not_equal_54_tests.cpp
#include <gtest/gtest.h>
#include "catch2/internal/catch_textflow.hpp"

using Catch::TextFlow::Columns;

class ColumnsIteratorNotEqualTest_54 : public ::testing::Test {};

// Verifies that comparing an iterator with itself using operator!= returns false.
TEST_F(ColumnsIteratorNotEqualTest_54, SelfComparisonIsFalse_54) {
    Columns cols;                 // treat Columns as black box; default-construct if available
    Columns::iterator it(cols);   // begin-like iterator via public ctor
    EXPECT_FALSE(it != it);
}

// Verifies that two default-constructed iterators over the SAME Columns object
// compare as not-unequal (i.e., operator!= returns false at the same position).
TEST_F(ColumnsIteratorNotEqualTest_54, SameColumnsSamePositionAreNotUnequal_54) {
    Columns cols;
    Columns::iterator it1(cols);
    Columns::iterator it2(cols);  // independent iterator at the same position
    EXPECT_FALSE(it1 != it2);
}

// Sanity check that operator!= is symmetric: (a != b) == (b != a)
TEST_F(ColumnsIteratorNotEqualTest_54, NotEqualIsSymmetric_54) {
    Columns cols;
    Columns::iterator a(cols);
    Columns::iterator b(cols);
    bool ab = (a != b);
    bool ba = (b != a);
    EXPECT_EQ(ab, ba);
}

// Verifies that creating two iterators from the same Columns and then copying one
// still results in not-unequal being false.
TEST_F(ColumnsIteratorNotEqualTest_54, CopyOfIteratorIsNotUnequal_54) {
    Columns cols;
    Columns::iterator it(cols);
    Columns::iterator copy = it;  // rely on standard copy semantics
    EXPECT_FALSE(copy != it);
}
