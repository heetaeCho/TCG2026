#include <gtest/gtest.h>
#include "catch2/catch_approx.hpp"
#include <limits>
#include <cmath>

using Catch::Approx;

// ============================================================
// Tests for operator>=(Approx const& lhs, T const& rhs)
// ============================================================

TEST(ApproxGreaterEqual_700, ExactEquality_700) {
    // When lhs.m_value == rhs, operator>= should return true (via equality)
    Approx approx(5.0);
    EXPECT_TRUE(approx >= 5.0);
}

TEST(ApproxGreaterEqual_700, ApproxValueGreaterThanRhs_700) {
    // When lhs.m_value > rhs clearly, operator>= should return true
    Approx approx(10.0);
    EXPECT_TRUE(approx >= 5.0);
}

TEST(ApproxGreaterEqual_700, ApproxValueLessThanRhs_700) {
    // When lhs.m_value < rhs and not within epsilon, operator>= should return false
    Approx approx(3.0);
    EXPECT_FALSE(approx >= 5.0);
}

TEST(ApproxGreaterEqual_700, ApproxValueSlightlyLessThanRhsWithinDefaultEpsilon_700) {
    // When lhs.m_value is slightly less than rhs but within default epsilon tolerance,
    // the equality check should make operator>= return true
    double value = 1.0;
    double rhs = 1.0 + std::numeric_limits<float>::epsilon() * 50.0; // within default epsilon * 100
    Approx approx(value);
    EXPECT_TRUE(approx >= rhs);
}

TEST(ApproxGreaterEqual_700, ApproxValueSlightlyLessThanRhsOutsideDefaultEpsilon_700) {
    // When lhs.m_value is less than rhs and outside default epsilon tolerance
    double value = 1.0;
    double rhs = 1.5; // clearly outside default epsilon
    Approx approx(value);
    EXPECT_FALSE(approx >= rhs);
}

TEST(ApproxGreaterEqual_700, WithCustomEpsilon_700) {
    // With a large custom epsilon, values further apart should still be "equal"
    Approx approx = Approx(1.0).epsilon(0.5); // 50% tolerance
    // rhs = 1.4, difference = 0.4, which is within 50% of 1.4 (0.7)
    EXPECT_TRUE(approx >= 1.4);
}

TEST(ApproxGreaterEqual_700, WithCustomEpsilonFails_700) {
    // With a small custom epsilon, close values might not be "equal"
    Approx approx = Approx(1.0).epsilon(0.001);
    // rhs = 1.1, difference = 0.1, which is > 0.1% of 1.1
    EXPECT_FALSE(approx >= 1.1);
}

TEST(ApproxGreaterEqual_700, WithCustomMargin_700) {
    // margin defines an absolute tolerance
    Approx approx = Approx(1.0).margin(0.5);
    // rhs = 1.3, difference = 0.3 < margin 0.5, so considered equal
    EXPECT_TRUE(approx >= 1.3);
}

TEST(ApproxGreaterEqual_700, WithCustomMarginFails_700) {
    Approx approx = Approx(1.0).margin(0.1);
    // rhs = 1.5, difference = 0.5 > margin 0.1 and also > default epsilon
    EXPECT_FALSE(approx >= 1.5);
}

TEST(ApproxGreaterEqual_700, ZeroValues_700) {
    Approx approx(0.0);
    EXPECT_TRUE(approx >= 0.0);
}

TEST(ApproxGreaterEqual_700, NegativeValues_700) {
    Approx approx(-3.0);
    EXPECT_TRUE(approx >= -5.0);  // -3 > -5
}

TEST(ApproxGreaterEqual_700, NegativeValuesFail_700) {
    Approx approx(-5.0);
    EXPECT_FALSE(approx >= -3.0);  // -5 < -3
}

TEST(ApproxGreaterEqual_700, NegativeValuesEqual_700) {
    Approx approx(-5.0);
    EXPECT_TRUE(approx >= -5.0);
}

TEST(ApproxGreaterEqual_700, IntegerRhs_700) {
    Approx approx(5.0);
    EXPECT_TRUE(approx >= 5);
    EXPECT_TRUE(approx >= 4);
    EXPECT_FALSE(approx >= 6);
}

TEST(ApproxGreaterEqual_700, FloatRhs_700) {
    Approx approx(5.0);
    EXPECT_TRUE(approx >= 5.0f);
    EXPECT_TRUE(approx >= 4.0f);
    EXPECT_FALSE(approx >= 6.0f);
}

TEST(ApproxGreaterEqual_700, LargeValues_700) {
    Approx approx(1e10);
    EXPECT_TRUE(approx >= 1e10);
    EXPECT_TRUE(approx >= 1e9);
    EXPECT_FALSE(approx >= 1e11);
}

TEST(ApproxGreaterEqual_700, SmallValues_700) {
    Approx approx(1e-10);
    EXPECT_TRUE(approx >= 1e-10);
    EXPECT_TRUE(approx >= 1e-11);
}

TEST(ApproxGreaterEqual_700, ApproxValueSlightlyGreater_700) {
    // When lhs.m_value is just barely greater than rhs, should return true
    Approx approx(5.0 + 1e-15);
    EXPECT_TRUE(approx >= 5.0);
}

TEST(ApproxGreaterEqual_700, NegatedApprox_700) {
    // Negating the approx flips m_value, so -(Approx(5.0)) has m_value = -5.0
    Approx approx = -Approx(5.0);
    EXPECT_TRUE(approx >= -5.0);
    EXPECT_TRUE(approx >= -10.0);
    EXPECT_FALSE(approx >= 0.0);
}

TEST(ApproxGreaterEqual_700, WithScaleParameter_700) {
    // Scale affects the epsilon calculation: epsilon * (scale + value)
    Approx approx = Approx(1.0).scale(100.0).epsilon(0.01);
    // With scale=100, epsilon=0.01: tolerance ~ 0.01 * (100 + |rhs|)
    // For rhs ~= 2.0: tolerance ~ 0.01 * 102 = 1.02
    // So difference of 1.0 should be within tolerance
    EXPECT_TRUE(approx >= 2.0);
}

TEST(ApproxGreaterEqual_700, WithMarginZeroAndSmallEpsilon_700) {
    Approx approx = Approx(1.0).margin(0.0).epsilon(1e-10);
    // Very tight tolerance: only essentially equal values pass
    EXPECT_TRUE(approx >= 1.0);  // exact equality
    EXPECT_FALSE(approx >= 1.001);  // slightly greater rhs
}

TEST(ApproxGreaterEqual_700, ConstructedFromInt_700) {
    Approx approx(5);
    EXPECT_TRUE(approx >= 5);
    EXPECT_TRUE(approx >= 4);
    EXPECT_FALSE(approx >= 6);
}

TEST(ApproxGreaterEqual_700, CustomApprox_700) {
    Approx approx = Approx::custom();
    // custom() creates an Approx with value 0.0
    EXPECT_TRUE(approx >= 0.0);
    EXPECT_TRUE(approx >= -1.0);
    EXPECT_FALSE(approx >= 1.0);
}

TEST(ApproxGreaterEqual_700, CallOperatorThenGreaterEqual_700) {
    Approx base(0.0);
    Approx approx = base(5.0);
    EXPECT_TRUE(approx >= 5.0);
    EXPECT_TRUE(approx >= 4.0);
    EXPECT_FALSE(approx >= 6.0);
}
