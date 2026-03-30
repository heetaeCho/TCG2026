// File: tests/approx_operator_le_tests_697.cpp

#include <gtest/gtest.h>
#include "catch2/catch_approx.hpp"

using Catch::Approx;

// Test fixture kept minimal — no internal state assumptions.
class ApproxOperatorLessEqualTest_697 : public ::testing::Test {};

// [Normal operation] If lhs is strictly less than rhs.m_value, lhs <= Approx(rhs) must be true
TEST_F(ApproxOperatorLessEqualTest_697, LessThan_ReturnsTrue_697) {
    double lhs = 3.0;
    Approx rhs = Approx(5.0);
    EXPECT_TRUE(lhs <= rhs);
}

// [Normal operation] If lhs is exactly equal to rhs value, <= must be true
TEST_F(ApproxOperatorLessEqualTest_697, EqualExact_ReturnsTrue_697) {
    double lhs = 5.0;
    Approx rhs = Approx(5.0);
    EXPECT_TRUE(lhs <= rhs);
}

// [Boundary via margin] Slightly above target but within absolute margin should still be considered <=
TEST_F(ApproxOperatorLessEqualTest_697, SlightlyAboveWithinMargin_ReturnsTrue_697) {
    double lhs = 5.05;
    // Absolute margin large enough to consider equality true
    Approx rhs = Approx(5.0).margin(0.1);
    EXPECT_TRUE(lhs <= rhs);
}

// [Boundary via margin] Slightly above target but OUTSIDE margin should be > and not equal => <= is false
TEST_F(ApproxOperatorLessEqualTest_697, SlightlyAboveOutsideMargin_ReturnsFalse_697) {
    double lhs = 5.02;
    // Margin too small to treat as equal
    Approx rhs = Approx(5.0).margin(0.01);
    EXPECT_FALSE(lhs <= rhs);
}

// [Type coverage] Works with integral lhs (SFINAE: constructible to double)
TEST_F(ApproxOperatorLessEqualTest_697, WorksWithIntLhs_697) {
    int lhs = 4;          // 4 < 5
    Approx rhs = Approx(5.0);
    EXPECT_TRUE(lhs <= rhs);

    int lhs2 = 6;         // 6 > 5 and not equal (no margin)
    EXPECT_FALSE(lhs2 <= rhs);
}

// [Type coverage] Works with float lhs
TEST_F(ApproxOperatorLessEqualTest_697, WorksWithFloatLhs_697) {
    float lhs = 1.0f;
    Approx rhs = Approx(1.0f);
    EXPECT_TRUE(lhs <= rhs); // equal

    float lhs2 = 1.0001f;
    // With tiny margin, this should still be considered > and not equal
    EXPECT_FALSE(lhs2 <= Approx(1.0f).margin(1e-6f));
}

// [Negative numbers] Correct ordering and equality behavior around negatives
TEST_F(ApproxOperatorLessEqualTest_697, NegativeValues_697) {
    double lhs_less = -2.0;   // strictly less than -1
    double lhs_more = -0.9;   // strictly greater than -1
    Approx rhs = Approx(-1.0);

    EXPECT_TRUE(lhs_less <= rhs);   // -2 < -1
    EXPECT_FALSE(lhs_more <= rhs);  // -0.9 > -1 and not equal (no margin)
}

// [Special/edge] Infinity ordering obeyed (if supported by platform)
TEST_F(ApproxOperatorLessEqualTest_697, InfinityOrdering_697) {
    const double pos_inf = std::numeric_limits<double>::infinity();
    const double neg_inf = -std::numeric_limits<double>::infinity();
    Approx rhs = Approx(1.0);

    EXPECT_TRUE(neg_inf <= rhs);   // -inf is less than any finite value
    EXPECT_FALSE(pos_inf <= rhs);  // +inf is greater than any finite value (not equal)
}

// [Zero boundary] Around zero with margin to verify equality branch participates in <=
TEST_F(ApproxOperatorLessEqualTest_697, ZeroWithMargin_697) {
    double lhs = 0.0005;
    Approx rhs = Approx(0.0).margin(0.001); // within margin ⇒ treated as equal
    EXPECT_TRUE(lhs <= rhs);

    // Outside margin ⇒ not equal and not less
    EXPECT_FALSE(0.002 <= Approx(0.0).margin(0.001));
}
