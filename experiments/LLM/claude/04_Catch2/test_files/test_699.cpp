#include <gtest/gtest.h>
#include "catch2/catch_approx.hpp"
#include <limits>
#include <cmath>

using Catch::Approx;

// ============================================================
// Tests for operator>=(T const& lhs, Approx const& rhs)
// ============================================================

// Test: lhs is clearly greater than rhs value → should return true
TEST(ApproxGreaterEqual_699, LhsClearlyGreaterThanRhs_699) {
    Approx approx(1.0);
    EXPECT_TRUE(2.0 >= approx);
}

// Test: lhs equals rhs value exactly → should return true
TEST(ApproxGreaterEqual_699, LhsExactlyEqualsRhs_699) {
    Approx approx(1.0);
    EXPECT_TRUE(1.0 >= approx);
}

// Test: lhs is clearly less than rhs value → should return false
TEST(ApproxGreaterEqual_699, LhsClearlyLessThanRhs_699) {
    Approx approx(2.0);
    EXPECT_FALSE(1.0 >= approx);
}

// Test: lhs is within epsilon of rhs (approximately equal) → should return true
TEST(ApproxGreaterEqual_699, LhsWithinEpsilonOfRhs_699) {
    Approx approx(1.0);
    // Default epsilon is ~0.01192 (float epsilon * 100)
    // So 1.0 - 0.005 should still be approximately equal to 1.0
    EXPECT_TRUE(0.995 >= approx);
}

// Test: lhs is slightly below rhs but within default margin/epsilon
TEST(ApproxGreaterEqual_699, LhsSlightlyBelowButWithinApprox_699) {
    Approx approx(1.0);
    double lhs = 1.0 - 1e-4;
    EXPECT_TRUE(lhs >= approx);
}

// Test: lhs is well below rhs and outside epsilon range → should return false
TEST(ApproxGreaterEqual_699, LhsWellBelowRhsOutsideEpsilon_699) {
    Approx approx(1.0);
    double lhs = 0.9;
    EXPECT_FALSE(lhs >= approx);
}

// Test: Using custom epsilon with tight tolerance
TEST(ApproxGreaterEqual_699, CustomEpsilonTight_699) {
    Approx approx = Approx(1.0).epsilon(0.001);
    // 0.999 is within 0.1% of 1.0
    EXPECT_TRUE(0.999 >= approx);
    // 0.99 is NOT within 0.1% of 1.0
    EXPECT_FALSE(0.99 >= approx);
}

// Test: Using custom margin
TEST(ApproxGreaterEqual_699, CustomMargin_699) {
    Approx approx = Approx(1.0).margin(0.5);
    // 0.6 is within margin of 0.5 from 1.0
    EXPECT_TRUE(0.6 >= approx);
    // 0.4 is outside margin of 0.5 from 1.0 and also < 1.0
    EXPECT_FALSE(0.4 >= approx);
}

// Test: With zero values
TEST(ApproxGreaterEqual_699, ZeroValues_699) {
    Approx approx(0.0);
    EXPECT_TRUE(0.0 >= approx);
    EXPECT_TRUE(1.0 >= approx);
}

// Test: Negative values where lhs > rhs
TEST(ApproxGreaterEqual_699, NegativeValuesLhsGreater_699) {
    Approx approx(-2.0);
    EXPECT_TRUE(-1.0 >= approx);
}

// Test: Negative values where lhs < rhs
TEST(ApproxGreaterEqual_699, NegativeValuesLhsLess_699) {
    Approx approx(-1.0);
    EXPECT_FALSE(-2.0 >= approx);
}

// Test: Negative values where lhs equals rhs
TEST(ApproxGreaterEqual_699, NegativeValuesEqual_699) {
    Approx approx(-1.0);
    EXPECT_TRUE(-1.0 >= approx);
}

// Test: Integer types with implicit conversion to double
TEST(ApproxGreaterEqual_699, IntegerType_699) {
    Approx approx(5.0);
    EXPECT_TRUE(5 >= approx);
    EXPECT_TRUE(6 >= approx);
    EXPECT_FALSE(4 >= approx);
}

// Test: Float types
TEST(ApproxGreaterEqual_699, FloatType_699) {
    Approx approx(1.0);
    float lhs = 1.0f;
    EXPECT_TRUE(lhs >= approx);
}

// Test: Very large values
TEST(ApproxGreaterEqual_699, VeryLargeValues_699) {
    Approx approx(1e10);
    EXPECT_TRUE(1e10 >= approx);
    EXPECT_TRUE(2e10 >= approx);
    EXPECT_FALSE(1e9 >= approx);
}

// Test: Very small values
TEST(ApproxGreaterEqual_699, VerySmallValues_699) {
    Approx approx(1e-10);
    EXPECT_TRUE(1e-10 >= approx);
    EXPECT_TRUE(1e-9 >= approx);
}

// Test: Using negated Approx
TEST(ApproxGreaterEqual_699, NegatedApprox_699) {
    Approx approx = -Approx(1.0);
    // -Approx(1.0) should have m_value = -1.0
    EXPECT_TRUE(0.0 >= approx);
    EXPECT_TRUE(-1.0 >= approx);
    EXPECT_FALSE(-2.0 >= approx);
}

// Test: Scale factor
TEST(ApproxGreaterEqual_699, WithScale_699) {
    Approx approx = Approx(0.0).scale(1.0).margin(0.0).epsilon(0.01);
    // When value is 0, scale may influence the epsilon calculation
    // 0.0 >= Approx(0.0) should be true
    EXPECT_TRUE(0.0 >= approx);
}

// Test: Boundary just outside epsilon
TEST(ApproxGreaterEqual_699, BoundaryJustOutsideEpsilon_699) {
    double epsilon_val = 0.01;
    Approx approx = Approx(1.0).epsilon(epsilon_val).margin(0.0);
    // Just outside epsilon: 1.0 - 0.02 = 0.98
    // 0.98 is 2% away from 1.0, epsilon is 1%
    EXPECT_FALSE(0.98 >= approx);
}

// Test: Boundary at epsilon edge
TEST(ApproxGreaterEqual_699, BoundaryAtEpsilonEdge_699) {
    double epsilon_val = 0.01;
    Approx approx = Approx(100.0).epsilon(epsilon_val).margin(0.0);
    // epsilon * value = 0.01 * 100 = 1.0
    // 99.0 is exactly 1.0 away → should be at the edge
    EXPECT_TRUE(99.0 >= approx);
    // 98.0 is 2.0 away → outside
    EXPECT_FALSE(98.0 >= approx);
}

// Test: lhs much greater than rhs
TEST(ApproxGreaterEqual_699, LhsMuchGreater_699) {
    Approx approx(1.0);
    EXPECT_TRUE(1000000.0 >= approx);
}

// Test: Using operator() to create new Approx and comparing
TEST(ApproxGreaterEqual_699, OperatorCallCreatesNewApprox_699) {
    Approx base = Approx(0.0).epsilon(0.01).margin(0.5);
    Approx derived = base(2.0);
    // derived should have m_value = 2.0 with same epsilon/margin
    EXPECT_TRUE(2.0 >= derived);
    EXPECT_TRUE(1.6 >= derived);  // within margin 0.5
    EXPECT_FALSE(1.0 >= derived); // outside margin and epsilon
}
