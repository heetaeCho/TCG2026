#include <gtest/gtest.h>
#include "catch2/catch_approx.hpp"
#include <limits>
#include <cmath>

using Catch::Approx;

// ============================================================
// Test: Basic inequality - values that are clearly different
// ============================================================
TEST(ApproxNotEqualTest_695, ClearlyDifferentValuesAreNotEqual_695) {
    Approx approx(1.0);
    EXPECT_TRUE(2.0 != approx);
}

TEST(ApproxNotEqualTest_695, ClearlyDifferentNegativeValuesAreNotEqual_695) {
    Approx approx(1.0);
    EXPECT_TRUE(-1.0 != approx);
}

// ============================================================
// Test: Equal values should NOT be not-equal
// ============================================================
TEST(ApproxNotEqualTest_695, ExactlyEqualValuesAreNotNotEqual_695) {
    Approx approx(1.0);
    EXPECT_FALSE(1.0 != approx);
}

TEST(ApproxNotEqualTest_695, ZeroEqualsZero_695) {
    Approx approx(0.0);
    EXPECT_FALSE(0.0 != approx);
}

// ============================================================
// Test: Values within default epsilon are approximately equal (not not-equal)
// ============================================================
TEST(ApproxNotEqualTest_695, WithinDefaultEpsilonIsNotNotEqual_695) {
    double value = 100.0;
    // Default epsilon is float::epsilon * 100 ≈ 0.0000119209...
    // For value 100.0, tolerance = epsilon * 100.0 ≈ 0.00119209...
    double withinTolerance = value + 0.0001;
    Approx approx(value);
    EXPECT_FALSE(withinTolerance != approx);
}

// ============================================================
// Test: Values outside default epsilon are not equal
// ============================================================
TEST(ApproxNotEqualTest_695, OutsideDefaultEpsilonIsNotEqual_695) {
    double value = 1.0;
    // Default epsilon ≈ 0.0000119209..., tolerance ≈ 0.0000119209 * max(1.0, 1.0) ≈ 0.0000119209
    double outsideTolerance = value + 1.0;
    Approx approx(value);
    EXPECT_TRUE(outsideTolerance != approx);
}

// ============================================================
// Test: Custom epsilon - large epsilon makes more values "equal"
// ============================================================
TEST(ApproxNotEqualTest_695, CustomLargeEpsilonMakesCloseValuesEqual_695) {
    Approx approx = Approx(1.0).epsilon(0.5);  // 50% tolerance
    // 1.0 ± 0.5 should be within tolerance
    EXPECT_FALSE(1.4 != approx);
    EXPECT_TRUE(2.0 != approx);
}

// ============================================================
// Test: Custom margin
// ============================================================
TEST(ApproxNotEqualTest_695, CustomMarginAllowsAbsoluteDifference_695) {
    Approx approx = Approx(0.0).margin(0.5);
    EXPECT_FALSE(0.3 != approx);   // within margin
    EXPECT_TRUE(1.0 != approx);    // outside margin
}

// ============================================================
// Test: Integer type as lhs
// ============================================================
TEST(ApproxNotEqualTest_695, IntegerLhsComparedToApprox_695) {
    Approx approx(5.0);
    EXPECT_FALSE(5 != approx);
    EXPECT_TRUE(6 != approx);
}

// ============================================================
// Test: Float type as lhs
// ============================================================
TEST(ApproxNotEqualTest_695, FloatLhsComparedToApprox_695) {
    Approx approx(3.0);
    EXPECT_FALSE(3.0f != approx);
    EXPECT_TRUE(4.0f != approx);
}

// ============================================================
// Test: Negative values
// ============================================================
TEST(ApproxNotEqualTest_695, NegativeApproxValue_695) {
    Approx approx(-5.0);
    EXPECT_FALSE(-5.0 != approx);
    EXPECT_TRUE(5.0 != approx);
}

// ============================================================
// Test: Negated Approx using operator-
// ============================================================
TEST(ApproxNotEqualTest_695, NegatedApprox_695) {
    Approx approx = -Approx(5.0);
    EXPECT_FALSE(-5.0 != approx);
    EXPECT_TRUE(5.0 != approx);
}

// ============================================================
// Test: Very small values near zero
// ============================================================
TEST(ApproxNotEqualTest_695, VerySmallValuesNearZero_695) {
    Approx approx = Approx(0.0).margin(1e-10);
    EXPECT_FALSE(1e-11 != approx);  // within margin
    EXPECT_TRUE(1.0 != approx);     // outside margin
}

// ============================================================
// Test: Large values
// ============================================================
TEST(ApproxNotEqualTest_695, LargeValues_695) {
    double value = 1e10;
    Approx approx(value);
    EXPECT_FALSE(value != approx);
    EXPECT_TRUE((value + 1e8) != approx);  // significantly different
}

// ============================================================
// Test: operator() creates new Approx with same settings
// ============================================================
TEST(ApproxNotEqualTest_695, OperatorCallCreatesNewApproxForNotEqual_695) {
    Approx generator = Approx(0.0).epsilon(0.1);
    Approx newApprox = generator(10.0);
    EXPECT_FALSE(10.0 != newApprox);
    EXPECT_TRUE(20.0 != newApprox);
}

// ============================================================
// Test: custom() static method
// ============================================================
TEST(ApproxNotEqualTest_695, CustomStaticMethodNotEqual_695) {
    Approx approx = Approx::custom().epsilon(0.01).margin(0.01);
    // custom() creates Approx(0.0) essentially
    EXPECT_FALSE(0.0 != approx);
    EXPECT_TRUE(1.0 != approx);
}

// ============================================================
// Test: Scale setting
// ============================================================
TEST(ApproxNotEqualTest_695, ScaleAffectsComparison_695) {
    Approx approx = Approx(0.0).scale(100.0).margin(0.0);
    // With scale=100, the epsilon-based tolerance uses max(scale, value)
    // Default epsilon ≈ 0.0000119209..., tolerance ≈ 0.0000119209 * 100 ≈ 0.00119209
    EXPECT_FALSE(0.001 != approx);
    EXPECT_TRUE(1.0 != approx);
}

// ============================================================
// Test: Symmetry - not equal is symmetric via operator!=
// ============================================================
TEST(ApproxNotEqualTest_695, NotEqualIsConsistentWithEqual_695) {
    Approx approx(5.0);
    // For any value, (v != approx) should be !(v == approx)
    EXPECT_EQ((5.0 != approx), !(5.0 == approx));
    EXPECT_EQ((6.0 != approx), !(6.0 == approx));
    EXPECT_EQ((4.0 != approx), !(4.0 == approx));
}

// ============================================================
// Test: Boundary - value exactly at epsilon boundary
// ============================================================
TEST(ApproxNotEqualTest_695, BoundaryEpsilonValue_695) {
    double value = 100.0;
    double eps = 0.1;  // 10%
    Approx approx = Approx(value).epsilon(eps);
    // tolerance = eps * value = 10.0
    // Exactly at boundary: 110.0
    EXPECT_FALSE(110.0 != approx);  // at boundary, should be equal
    // Slightly beyond
    EXPECT_TRUE(111.0 != approx);   // beyond boundary
}

// ============================================================
// Test: Unsigned integer type
// ============================================================
TEST(ApproxNotEqualTest_695, UnsignedIntegerLhs_695) {
    Approx approx(10.0);
    unsigned int val = 10u;
    EXPECT_FALSE(val != approx);
    unsigned int val2 = 20u;
    EXPECT_TRUE(val2 != approx);
}

// ============================================================
// Test: Long type
// ============================================================
TEST(ApproxNotEqualTest_695, LongTypeLhs_695) {
    Approx approx(42.0);
    long val = 42L;
    EXPECT_FALSE(val != approx);
    long val2 = 100L;
    EXPECT_TRUE(val2 != approx);
}

// ============================================================
// Test: Approx constructed from integer
// ============================================================
TEST(ApproxNotEqualTest_695, ApproxConstructedFromInteger_695) {
    Approx approx(5);
    EXPECT_FALSE(5.0 != approx);
    EXPECT_TRUE(10.0 != approx);
}

// ============================================================
// Test: Zero margin and zero epsilon near zero value
// ============================================================
TEST(ApproxNotEqualTest_695, ZeroMarginZeroEpsilonNearZero_695) {
    Approx approx = Approx(0.0).margin(0.0).epsilon(0.0);
    EXPECT_FALSE(0.0 != approx);
    // Any non-zero value should be not-equal
    EXPECT_TRUE(1e-15 != approx);
}
