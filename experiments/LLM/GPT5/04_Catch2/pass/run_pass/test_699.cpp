// File: tests/Approx_GreaterEqual_699_Test.cpp

#include <gtest/gtest.h>
#include "catch2/catch_approx.hpp"
#include <limits>

using Catch::Approx;

class ApproxGteTest_699 : public ::testing::Test {};

//
// Normal operation
//
TEST_F(ApproxGteTest_699, GreaterThanReturnsTrue_699) {
    // 3 is strictly greater than Approx(2)
    EXPECT_TRUE(3.0 >= Approx(2.0));
    EXPECT_TRUE(3   >= Approx(2.0));
}

TEST_F(ApproxGteTest_699, EqualWithinDefaultToleranceReturnsTrue_699) {
    // Exact equality with the target value should be considered >=
    EXPECT_TRUE(2.0 >= Approx(2.0));
    EXPECT_TRUE(2   >= Approx(2.0));
}

TEST_F(ApproxGteTest_699, LessThanAndOutsideDefaultToleranceReturnsFalse_699) {
    // 1.999 is not within Approx(2.0) under default tolerances
    EXPECT_FALSE(1.999 >= Approx(2.0));
    // Clear integer case
    EXPECT_FALSE(1 >= Approx(2.0));
}

//
// Boundary conditions via margin (observable through the public API)
//
TEST_F(ApproxGteTest_699, WithinAbsoluteMarginCountsAsEqualityThusGte_699) {
    // Using margin to define absolute tolerance
    // 1.6 is within margin 0.5 of 2.0 (|1.6 - 2.0| = 0.4), so equality holds and thus >= is true
    EXPECT_TRUE(1.6 >= Approx(2.0).margin(0.5));
}

TEST_F(ApproxGteTest_699, ExactlyOnMarginBoundaryIsConsideredGte_699) {
    // On-the-edge case: |1.5 - 2.0| == 0.5; treated as equal by Approx (boundary inclusion),
    // so >= should be true due to equality.
    EXPECT_TRUE(1.5 >= Approx(2.0).margin(0.5));
}

TEST_F(ApproxGteTest_699, JustOutsideMarginIsNotGte_699) {
    // Slightly outside the margin should not count as equal, and since it's also not >
    // the target value, >= should be false.
    EXPECT_FALSE(1.4999 >= Approx(2.0).margin(0.5));
}

//
// Exceptional / special numeric values (observable result only)
//
TEST_F(ApproxGteTest_699, NaNComparedWithApproxIsNotGte_699) {
    const double NaN = std::numeric_limits<double>::quiet_NaN();
    EXPECT_FALSE(NaN >= Approx(0.0));
}

//
// Cross-type usage (template T), still black-box from Approx
//
TEST_F(ApproxGteTest_699, IntegerLhsWithApproxDoubleRhs_699) {
    // Mixed types should work through the templated operator
    EXPECT_TRUE(10 >= Approx(9.999));
    EXPECT_FALSE(8 >= Approx(9.0));
}
