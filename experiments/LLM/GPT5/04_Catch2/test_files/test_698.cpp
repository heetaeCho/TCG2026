// File: tests/approx_less_equal_698_tests.cpp

#include <gtest/gtest.h>
#include "catch2/catch_approx.hpp"

using Catch::Approx;

namespace {

// Normal: strictly less-than on RHS -> true via (m_value < rhs)
TEST(ApproxLessEqual_698, LessThanRhsReturnsTrue_698) {
    EXPECT_TRUE(Approx(1.0) <= 2.0);
    EXPECT_TRUE(Approx(0.0) <= 0.1);
}

// Equality: rhs == value -> true via (lhs == rhs)
TEST(ApproxLessEqual_698, EqualValuesReturnTrue_698) {
    EXPECT_TRUE(Approx(1.0) <= 1.0);
    EXPECT_TRUE(Approx(123.456) <= 123.456);
}

// Outside default tolerance: rhs well below value -> false
// (first part false; equality part also expected false given default tiny eps/margin)
TEST(ApproxLessEqual_698, RhsMuchSmallerThanValueReturnsFalse_698) {
    EXPECT_FALSE(Approx(2.0) <= 1.0);
    EXPECT_FALSE(Approx(10.0) <= 0.0);
}

// Boundary via margin: rhs < value but within margin -> true via (lhs == rhs)
TEST(ApproxLessEqual_698, RhsWithinMarginReturnsTrue_698) {
    // value = 100, margin = 0.5
    // |100 - 99.6| = 0.4 <= 0.5 -> treated as equal
    EXPECT_TRUE(Approx(100.0).margin(0.5) <= 99.6);
}

// Exactly at margin boundary should still be considered equal -> true
TEST(ApproxLessEqual_698, RhsExactlyAtMarginReturnsTrue_698) {
    // |100 - 99.5| = 0.5 == margin
    EXPECT_TRUE(Approx(100.0).margin(0.5) <= 99.5);
}

// Just outside margin: not equal and lhs.m_value < rhs is false -> false
TEST(ApproxLessEqual_698, RhsOutsideMarginReturnsFalse_698) {
    // |100 - 99.49| = 0.51 > 0.5
    EXPECT_FALSE(Approx(100.0).margin(0.5) <= 99.49);
}

// Type coverage: integral RHS accepted by the templated operator
TEST(ApproxLessEqual_698, WorksWithIntegralRhs_698) {
    EXPECT_TRUE(Approx(3.0) <= 3);   // equal
    EXPECT_FALSE(Approx(3.0) <= 2);  // below value, default tolerance too small
}

// Type coverage: float RHS also accepted
TEST(ApproxLessEqual_698, WorksWithFloatRhs_698) {
    float rhs = 3.0f;
    EXPECT_TRUE(Approx(3.0) <= rhs);
    EXPECT_TRUE(Approx(2.9999).margin(0.01) <= rhs); // within margin -> equal
    EXPECT_FALSE(Approx(3.0) <= 2.9f);               // outside margin/epsilon
}

} // namespace
