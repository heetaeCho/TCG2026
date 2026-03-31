#include <gtest/gtest.h>
#include "catch2/catch_approx.hpp"
#include <limits>
#include <cmath>

using Catch::Approx;

// ============================================================
// Normal operation tests
// ============================================================

TEST(ApproxTest_693, ExactEqualityWithDouble_693) {
    Approx approx(1.0);
    EXPECT_TRUE(1.0 == approx);
}

TEST(ApproxTest_693, ExactEqualityWithInt_693) {
    Approx approx(5.0);
    EXPECT_TRUE(5 == approx);
}

TEST(ApproxTest_693, ApproxEqualityWithinDefaultEpsilon_693) {
    // Default epsilon is float::epsilon * 100
    double value = 1.0;
    double small_diff = value * static_cast<double>(std::numeric_limits<float>::epsilon()) * 50.0;
    Approx approx(value);
    EXPECT_TRUE((value + small_diff) == approx);
}

TEST(ApproxTest_693, NotEqualOutsideDefaultEpsilon_693) {
    double value = 1.0;
    double large_diff = value * static_cast<double>(std::numeric_limits<float>::epsilon()) * 200.0;
    Approx approx(value);
    EXPECT_FALSE((value + large_diff) == approx);
}

TEST(ApproxTest_693, CustomEpsilon_693) {
    Approx approx = Approx(100.0).epsilon(0.01);
    // Within 1%
    EXPECT_TRUE(100.5 == approx);
    // Outside 1%
    EXPECT_FALSE(102.0 == approx);
}

TEST(ApproxTest_693, CustomMargin_693) {
    Approx approx = Approx(0.0).margin(0.5);
    EXPECT_TRUE(0.3 == approx);
    EXPECT_TRUE(-0.3 == approx);
    EXPECT_FALSE(0.6 == approx);
    EXPECT_FALSE(-0.6 == approx);
}

TEST(ApproxTest_693, ScaleSetter_693) {
    Approx approx = Approx(0.0).scale(100.0).epsilon(0.01);
    // The scale should affect the tolerance calculation
    EXPECT_TRUE(0.5 == approx);
}

TEST(ApproxTest_693, NegationOperator_693) {
    Approx approx = -Approx(5.0);
    EXPECT_TRUE(-5.0 == approx);
    EXPECT_FALSE(5.0 == approx);
}

TEST(ApproxTest_693, CallOperatorCreatesNewApprox_693) {
    Approx base = Approx(0.0).epsilon(0.1);
    Approx derived = base(10.0);
    EXPECT_TRUE(10.0 == derived);
    EXPECT_TRUE(10.5 == derived);
    EXPECT_FALSE(12.0 == derived);
}

TEST(ApproxTest_693, CustomFactoryMethod_693) {
    Approx approx = Approx::custom();
    // custom() should create an Approx with value 0
    EXPECT_TRUE(0.0 == approx);
}

TEST(ApproxTest_693, ToStringProducesNonEmpty_693) {
    Approx approx(1.5);
    std::string str = approx.toString();
    EXPECT_FALSE(str.empty());
}

// ============================================================
// Boundary condition tests
// ============================================================

TEST(ApproxTest_693, ZeroValueWithDefaultSettings_693) {
    Approx approx(0.0);
    EXPECT_TRUE(0.0 == approx);
    // Without margin, comparing to non-zero near zero should fail
    // because epsilon-based tolerance scales with value (which is 0)
    EXPECT_FALSE(0.001 == approx);
}

TEST(ApproxTest_693, ZeroValueWithMargin_693) {
    Approx approx = Approx(0.0).margin(0.001);
    EXPECT_TRUE(0.0005 == approx);
    EXPECT_FALSE(0.002 == approx);
}

TEST(ApproxTest_693, VeryLargeValues_693) {
    double big = 1e15;
    Approx approx(big);
    EXPECT_TRUE(big == approx);
}

TEST(ApproxTest_693, VerySmallValues_693) {
    double tiny = 1e-15;
    Approx approx = Approx(tiny).margin(1e-16);
    EXPECT_TRUE(tiny == approx);
}

TEST(ApproxTest_693, NegativeValues_693) {
    Approx approx(-3.0);
    EXPECT_TRUE(-3.0 == approx);
    EXPECT_FALSE(3.0 == approx);
}

TEST(ApproxTest_693, EpsilonAtBoundary_693) {
    // Set epsilon to exactly 0.1 (10%)
    Approx approx = Approx(100.0).epsilon(0.1);
    // Exactly at 10% boundary
    EXPECT_TRUE(110.0 == approx);
    EXPECT_TRUE(90.0 == approx);
    // Just outside
    EXPECT_FALSE(111.0 == approx);
    EXPECT_FALSE(89.0 == approx);
}

TEST(ApproxTest_693, MarginAtBoundary_693) {
    Approx approx = Approx(50.0).margin(5.0);
    EXPECT_TRUE(55.0 == approx);
    EXPECT_TRUE(45.0 == approx);
    EXPECT_FALSE(55.1 == approx);
    EXPECT_FALSE(44.9 == approx);
}

// ============================================================
// Template / type conversion tests
// ============================================================

TEST(ApproxTest_693, ConstructFromInt_693) {
    Approx approx(3);
    EXPECT_TRUE(3.0 == approx);
}

TEST(ApproxTest_693, ConstructFromFloat_693) {
    Approx approx(2.5f);
    EXPECT_TRUE(2.5 == approx);
}

TEST(ApproxTest_693, CompareWithFloat_693) {
    Approx approx(1.0);
    float f = 1.0f;
    EXPECT_TRUE(f == approx);
}

TEST(ApproxTest_693, CompareWithInt_693) {
    Approx approx(42.0);
    EXPECT_TRUE(42 == approx);
}

TEST(ApproxTest_693, EpsilonFromInt_693) {
    // Setting epsilon with int-like value; should not throw/fail
    // epsilon of 0 means exact comparison
    Approx approx = Approx(1.0).epsilon(0.0);
    EXPECT_TRUE(1.0 == approx);
}

TEST(ApproxTest_693, MarginFromInt_693) {
    Approx approx = Approx(5.0).margin(1);
    EXPECT_TRUE(5.5 == approx);
    EXPECT_TRUE(4.5 == approx);
}

// ============================================================
// Negation and symmetry tests
// ============================================================

TEST(ApproxTest_693, NegationPreservesEpsilon_693) {
    Approx approx = -Approx(10.0).epsilon(0.1);
    // Should be approx -10.0 with 10% epsilon
    EXPECT_TRUE(-10.0 == approx);
    EXPECT_TRUE(-9.5 == approx);
    EXPECT_TRUE(-10.5 == approx);
    EXPECT_FALSE(-12.0 == approx);
}

TEST(ApproxTest_693, NegationPreservesMargin_693) {
    Approx approx = -Approx(10.0).margin(2.0);
    EXPECT_TRUE(-10.0 == approx);
    EXPECT_TRUE(-9.0 == approx);
    EXPECT_TRUE(-11.0 == approx);
    EXPECT_FALSE(-13.0 == approx);
}

TEST(ApproxTest_693, DoubleNegation_693) {
    Approx approx = -(-Approx(5.0));
    EXPECT_TRUE(5.0 == approx);
}

// ============================================================
// CallOperator preserves settings tests
// ============================================================

TEST(ApproxTest_693, CallOperatorPreservesEpsilon_693) {
    Approx base = Approx(0.0).epsilon(0.1);
    Approx newApprox = base(100.0);
    // 10% of 100 = 10, so 109 should be within range
    EXPECT_TRUE(109.0 == newApprox);
    EXPECT_FALSE(112.0 == newApprox);
}

TEST(ApproxTest_693, CallOperatorPreservesMargin_693) {
    Approx base = Approx(0.0).margin(5.0);
    Approx newApprox = base(0.0);
    EXPECT_TRUE(4.0 == newApprox);
    EXPECT_FALSE(6.0 == newApprox);
}

// ============================================================
// Special floating point values
// ============================================================

TEST(ApproxTest_693, InfinityNotEqualToFinite_693) {
    Approx approx(1.0);
    EXPECT_FALSE(std::numeric_limits<double>::infinity() == approx);
}

TEST(ApproxTest_693, NaNNotEqual_693) {
    Approx approx(1.0);
    EXPECT_FALSE(std::numeric_limits<double>::quiet_NaN() == approx);
}

TEST(ApproxTest_693, NegativeInfinityNotEqual_693) {
    Approx approx(-1.0);
    EXPECT_FALSE(-std::numeric_limits<double>::infinity() == approx);
}
