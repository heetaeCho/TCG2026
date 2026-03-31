#include <gtest/gtest.h>
#include "catch2/catch_approx.hpp"
#include <limits>
#include <cmath>

using Catch::Approx;

// ============================================================
// Tests for operator<=(Approx const& lhs, T const& rhs)
// ============================================================

TEST(ApproxLessThanOrEqual_698, ExactEquality_698) {
    // When lhs.m_value == rhs, operator<= should return true (via equality)
    Approx approx(5.0);
    EXPECT_TRUE(approx <= 5.0);
}

TEST(ApproxLessThanOrEqual_698, ApproxValueLessThanRhs_698) {
    // When lhs.m_value < rhs, operator<= should return true
    Approx approx(3.0);
    EXPECT_TRUE(approx <= 5.0);
}

TEST(ApproxLessThanOrEqual_698, ApproxValueGreaterThanRhs_698) {
    // When lhs.m_value > rhs and not approximately equal, should return false
    Approx approx(10.0);
    EXPECT_FALSE(approx <= 5.0);
}

TEST(ApproxLessThanOrEqual_698, ApproxValueSlightlyGreaterWithinDefaultEpsilon_698) {
    // When lhs.m_value is slightly greater than rhs but within default epsilon, should return true
    double val = 1.0;
    double rhs = val - 1e-7; // very slightly less than val
    Approx approx(val);
    // Default epsilon is ~0.0119209... (float epsilon * 100)
    // So |1.0 - (1.0-1e-7)| = 1e-7 which is within epsilon*scale(max(1.0, 1.0)) = ~0.0119
    EXPECT_TRUE(approx <= rhs);
}

TEST(ApproxLessThanOrEqual_698, ApproxValueSignificantlyGreaterThanRhs_698) {
    // When lhs.m_value is much greater than rhs, should return false
    Approx approx(100.0);
    EXPECT_FALSE(approx <= 5.0);
}

TEST(ApproxLessThanOrEqual_698, WithCustomEpsilon_698) {
    // With a large epsilon, values that are somewhat different can be approximately equal
    Approx approx = Approx(5.5).epsilon(0.2);
    // 5.5 > 5.0, but with epsilon=0.2, |5.5-5.0|=0.5 vs epsilon*max(5.5,5.0)=0.2*5.5=1.1
    // So 0.5 < 1.1, meaning they're approximately equal
    EXPECT_TRUE(approx <= 5.0);
}

TEST(ApproxLessThanOrEqual_698, WithCustomEpsilonNotEqual_698) {
    // With a tiny epsilon, values that differ should not be approximately equal
    Approx approx = Approx(5.1).epsilon(0.001);
    // 5.1 > 5.0, |5.1-5.0|=0.1 vs epsilon*max(5.1,5.0)=0.001*5.1=0.0051
    // 0.1 > 0.0051, so not approximately equal, and 5.1 > 5.0
    EXPECT_FALSE(approx <= 5.0);
}

TEST(ApproxLessThanOrEqual_698, WithCustomMargin_698) {
    // With a custom margin, values within the margin are approximately equal
    Approx approx = Approx(5.05).margin(0.1);
    // 5.05 > 5.0, but margin is 0.1, |5.05-5.0|=0.05 < 0.1, so approximately equal
    EXPECT_TRUE(approx <= 5.0);
}

TEST(ApproxLessThanOrEqual_698, WithCustomMarginNotEqual_698) {
    // With a small margin, values outside the margin are not approximately equal
    Approx approx = Approx(5.5).margin(0.1).epsilon(0.0);
    // 5.5 > 5.0, |5.5-5.0|=0.5 > 0.1, and epsilon=0, so not approximately equal
    EXPECT_FALSE(approx <= 5.0);
}

TEST(ApproxLessThanOrEqual_698, ZeroValues_698) {
    Approx approx(0.0);
    EXPECT_TRUE(approx <= 0.0);
}

TEST(ApproxLessThanOrEqual_698, NegativeValues_698) {
    Approx approx(-5.0);
    EXPECT_TRUE(approx <= -3.0);
}

TEST(ApproxLessThanOrEqual_698, NegativeApproxGreaterThanNegativeRhs_698) {
    Approx approx(-3.0);
    EXPECT_FALSE(approx <= -5.0);
}

TEST(ApproxLessThanOrEqual_698, IntegerType_698) {
    Approx approx(3.0);
    EXPECT_TRUE(approx <= 5);
}

TEST(ApproxLessThanOrEqual_698, IntegerTypeEqual_698) {
    Approx approx(5.0);
    EXPECT_TRUE(approx <= 5);
}

TEST(ApproxLessThanOrEqual_698, IntegerTypeGreater_698) {
    Approx approx(10.0);
    EXPECT_FALSE(approx <= 5);
}

TEST(ApproxLessThanOrEqual_698, FloatType_698) {
    Approx approx(3.0);
    EXPECT_TRUE(approx <= 5.0f);
}

TEST(ApproxLessThanOrEqual_698, LargeValues_698) {
    Approx approx(1e15);
    EXPECT_TRUE(approx <= 1e16);
}

TEST(ApproxLessThanOrEqual_698, LargeValueGreater_698) {
    Approx approx(1e16);
    EXPECT_FALSE(approx <= 1e15);
}

TEST(ApproxLessThanOrEqual_698, VerySmallDifference_698) {
    // Values extremely close together should be approximately equal
    double val = 1.0;
    double rhs = val + std::numeric_limits<double>::epsilon();
    Approx approx(val);
    EXPECT_TRUE(approx <= rhs);
}

TEST(ApproxLessThanOrEqual_698, NegatedApprox_698) {
    // Test with negated Approx
    Approx approx = -Approx(5.0);
    // approx.m_value = -5.0
    EXPECT_TRUE(approx <= -3.0);   // -5 < -3
    EXPECT_TRUE(approx <= -5.0);   // -5 == -5 (approx equal)
    EXPECT_FALSE(approx <= -10.0); // -5 > -10 and not approx equal
}

TEST(ApproxLessThanOrEqual_698, WithScale_698) {
    // Scale affects the equality comparison
    Approx approx = Approx(5.1).scale(100.0).epsilon(0.01);
    // equalityComparison: |5.1 - 5.0| = 0.1 vs epsilon * max(scale, max(|5.1|, |5.0|)) = 0.01 * max(100, 5.1) = 1.0
    // 0.1 < 1.0, so approximately equal
    EXPECT_TRUE(approx <= 5.0);
}

TEST(ApproxLessThanOrEqual_698, CustomApprox_698) {
    Approx approx = Approx::custom().epsilon(0.01).margin(0.0);
    // custom() creates Approx(0), then we use operator() to set value
    Approx approxVal = approx(3.0);
    EXPECT_TRUE(approxVal <= 5.0);
}

TEST(ApproxLessThanOrEqual_698, BoundaryEpsilonExact_698) {
    // Test at the boundary of epsilon tolerance
    double epsilon = 0.1;
    double base = 10.0;
    // Tolerance = epsilon * max(scale=0, max(|approxVal|, |rhs|))
    // If approxVal = 11.0, rhs = 10.0: tolerance = 0.1 * 11.0 = 1.1, diff = 1.0 < 1.1 => equal => true
    Approx approx = Approx(11.0).epsilon(epsilon);
    EXPECT_TRUE(approx <= base);

    // If approxVal = 12.0, rhs = 10.0: tolerance = 0.1 * 12.0 = 1.2, diff = 2.0 > 1.2 => not equal, and 12 > 10 => false
    Approx approx2 = Approx(12.0).epsilon(epsilon);
    EXPECT_FALSE(approx2 <= base);
}
