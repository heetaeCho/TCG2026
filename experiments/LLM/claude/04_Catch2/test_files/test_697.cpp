#include <gtest/gtest.h>
#include "catch2/catch_approx.hpp"
#include <limits>
#include <cmath>

using Catch::Approx;

// ============================================================
// Tests for operator<=( T const& lhs, Approx const& rhs )
// The semantics: lhs <= rhs iff (lhs < rhs.value) OR (lhs == rhs)
// where "lhs == rhs" uses approximate equality with epsilon/margin.
// ============================================================

class ApproxLessEqualTest_697 : public ::testing::Test {
protected:
    // default epsilon is ~100 * float epsilon ≈ 0.0000119209...
    // default margin is 0.0
};

// --- Normal operation ---

TEST_F(ApproxLessEqualTest_697, LhsStrictlyLessThanRhsValue_ReturnsTrue_697) {
    Approx approx(10.0);
    EXPECT_TRUE(9.0 <= approx);
}

TEST_F(ApproxLessEqualTest_697, LhsEqualToRhsValue_ReturnsTrue_697) {
    Approx approx(10.0);
    EXPECT_TRUE(10.0 <= approx);
}

TEST_F(ApproxLessEqualTest_697, LhsSlightlyGreaterThanRhsValue_WithinEpsilon_ReturnsTrue_697) {
    // Default epsilon ~ 100 * FLT_EPSILON. For value 10.0, tolerance ~ 10.0 * 100 * FLT_EPSILON
    double value = 10.0;
    double defaultEpsilon = static_cast<double>(std::numeric_limits<float>::epsilon()) * 100.0;
    double tolerance = value * defaultEpsilon;
    double lhs = value + tolerance * 0.5; // within approximate equality
    Approx approx(value);
    EXPECT_TRUE(lhs <= approx);
}

TEST_F(ApproxLessEqualTest_697, LhsGreaterThanRhsValue_OutsideEpsilon_ReturnsFalse_697) {
    Approx approx(10.0);
    EXPECT_FALSE(11.0 <= approx);
}

TEST_F(ApproxLessEqualTest_697, LhsMuchLessThanRhsValue_ReturnsTrue_697) {
    Approx approx(100.0);
    EXPECT_TRUE(-50.0 <= approx);
}

// --- With custom epsilon ---

TEST_F(ApproxLessEqualTest_697, CustomEpsilon_LhsWithinTolerance_ReturnsTrue_697) {
    Approx approx = Approx(10.0).epsilon(0.1); // 10% tolerance => ±1.0
    // lhs = 10.9, within tolerance
    EXPECT_TRUE(10.9 <= approx);
}

TEST_F(ApproxLessEqualTest_697, CustomEpsilon_LhsOutsideTolerance_ReturnsFalse_697) {
    Approx approx = Approx(10.0).epsilon(0.01); // 1% tolerance => ±0.1
    // lhs = 10.5 is outside
    EXPECT_FALSE(10.5 <= approx);
}

// --- With custom margin ---

TEST_F(ApproxLessEqualTest_697, CustomMargin_LhsWithinMargin_ReturnsTrue_697) {
    Approx approx = Approx(10.0).margin(1.0);
    // lhs = 10.5 is within margin of 1.0
    EXPECT_TRUE(10.5 <= approx);
}

TEST_F(ApproxLessEqualTest_697, CustomMargin_LhsOutsideMargin_ReturnsFalse_697) {
    Approx approx = Approx(10.0).margin(0.5);
    // lhs = 11.0 is outside margin of 0.5
    EXPECT_FALSE(11.0 <= approx);
}

TEST_F(ApproxLessEqualTest_697, CustomMargin_LhsExactlyAtMarginBoundary_ReturnsTrue_697) {
    Approx approx = Approx(10.0).margin(1.0);
    EXPECT_TRUE(11.0 <= approx);
}

// --- Boundary conditions ---

TEST_F(ApproxLessEqualTest_697, ZeroValue_LhsZero_ReturnsTrue_697) {
    Approx approx(0.0);
    EXPECT_TRUE(0.0 <= approx);
}

TEST_F(ApproxLessEqualTest_697, ZeroValue_LhsSlightlyPositive_WithDefaultEpsilon_697) {
    // For value 0.0, the epsilon-based tolerance is 0 (since it's relative).
    // margin is 0 by default. So only exact 0 or less should pass.
    Approx approx(0.0);
    double smallPositive = 0.001;
    EXPECT_FALSE(smallPositive <= approx);
}

TEST_F(ApproxLessEqualTest_697, ZeroValue_LhsNegative_ReturnsTrue_697) {
    Approx approx(0.0);
    EXPECT_TRUE(-1.0 <= approx);
}

TEST_F(ApproxLessEqualTest_697, NegativeValues_LhsLessThanNegativeRhs_ReturnsTrue_697) {
    Approx approx(-5.0);
    EXPECT_TRUE(-10.0 <= approx);
}

TEST_F(ApproxLessEqualTest_697, NegativeValues_LhsGreaterThanNegativeRhs_ReturnsFalse_697) {
    Approx approx(-10.0);
    EXPECT_FALSE(-5.0 <= approx);
}

TEST_F(ApproxLessEqualTest_697, NegativeValues_LhsApproxEqualToNegativeRhs_ReturnsTrue_697) {
    Approx approx = Approx(-10.0).margin(0.5);
    EXPECT_TRUE(-9.7 <= approx);
}

// --- Integer types (template with int) ---

TEST_F(ApproxLessEqualTest_697, IntegerLhs_LessThan_ReturnsTrue_697) {
    Approx approx(10.0);
    EXPECT_TRUE(9 <= approx);
}

TEST_F(ApproxLessEqualTest_697, IntegerLhs_Equal_ReturnsTrue_697) {
    Approx approx(10.0);
    EXPECT_TRUE(10 <= approx);
}

TEST_F(ApproxLessEqualTest_697, IntegerLhs_Greater_ReturnsFalse_697) {
    Approx approx(10.0);
    EXPECT_FALSE(11 <= approx);
}

// --- Float type lhs ---

TEST_F(ApproxLessEqualTest_697, FloatLhs_LessThan_ReturnsTrue_697) {
    Approx approx(10.0);
    float lhs = 9.5f;
    EXPECT_TRUE(lhs <= approx);
}

TEST_F(ApproxLessEqualTest_697, FloatLhs_Greater_ReturnsFalse_697) {
    Approx approx(10.0);
    float lhs = 10.5f;
    EXPECT_FALSE(lhs <= approx);
}

// --- Large values ---

TEST_F(ApproxLessEqualTest_697, LargeValues_LhsLess_ReturnsTrue_697) {
    Approx approx(1e15);
    EXPECT_TRUE(9e14 <= approx);
}

TEST_F(ApproxLessEqualTest_697, LargeValues_LhsSlightlyGreater_WithEpsilon_ReturnsTrue_697) {
    double value = 1e10;
    double defaultEpsilon = static_cast<double>(std::numeric_limits<float>::epsilon()) * 100.0;
    double tolerance = value * defaultEpsilon;
    double lhs = value + tolerance * 0.5;
    Approx approx(value);
    EXPECT_TRUE(lhs <= approx);
}

// --- Very small values ---

TEST_F(ApproxLessEqualTest_697, VerySmallValues_WithMargin_697) {
    Approx approx = Approx(1e-10).margin(1e-9);
    EXPECT_TRUE(5e-10 <= approx);
}

// --- Combined epsilon and margin ---

TEST_F(ApproxLessEqualTest_697, CombinedEpsilonAndMargin_LhsWithinMarginButNotEpsilon_ReturnsTrue_697) {
    // value = 0.0, epsilon-based tolerance = 0, but margin = 0.5
    Approx approx = Approx(0.0).epsilon(0.01).margin(0.5);
    EXPECT_TRUE(0.3 <= approx);
}

// --- Negative Approx (operator-) ---

TEST_F(ApproxLessEqualTest_697, NegatedApprox_LhsLessThanNegatedValue_ReturnsTrue_697) {
    Approx approx = -Approx(10.0);
    // approx represents -10.0
    EXPECT_TRUE(-15.0 <= approx);
}

TEST_F(ApproxLessEqualTest_697, NegatedApprox_LhsEqualToNegatedValue_ReturnsTrue_697) {
    Approx approx = -Approx(10.0);
    EXPECT_TRUE(-10.0 <= approx);
}

TEST_F(ApproxLessEqualTest_697, NegatedApprox_LhsGreaterThanNegatedValue_ReturnsFalse_697) {
    Approx approx = -Approx(10.0);
    EXPECT_FALSE(5.0 <= approx);
}

// --- scale() ---

TEST_F(ApproxLessEqualTest_697, WithScale_AffectsTolerance_697) {
    // scale affects the epsilon-based tolerance calculation
    Approx approx = Approx(0.0).scale(100.0).epsilon(0.1);
    // tolerance should be based on max(scale, value) * epsilon = 100 * 0.1 = 10
    EXPECT_TRUE(5.0 <= approx);
}

// --- Approx constructed from integer ---

TEST_F(ApproxLessEqualTest_697, ApproxFromInteger_LhsLess_ReturnsTrue_697) {
    Approx approx(5);
    EXPECT_TRUE(3 <= approx);
}

TEST_F(ApproxLessEqualTest_697, ApproxFromInteger_LhsEqual_ReturnsTrue_697) {
    Approx approx(5);
    EXPECT_TRUE(5 <= approx);
}

TEST_F(ApproxLessEqualTest_697, ApproxFromInteger_LhsGreater_ReturnsFalse_697) {
    Approx approx(5);
    EXPECT_FALSE(6 <= approx);
}
