#include <gtest/gtest.h>
#include "catch2/catch_approx.hpp"
#include <limits>
#include <cmath>

using Catch::Approx;

// ============================================================
// Test fixture
// ============================================================
class ApproxTest_694 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Basic equality tests
// ============================================================

TEST_F(ApproxTest_694, ExactEqualityWithDouble_694) {
    Approx approx(1.0);
    EXPECT_TRUE(approx == 1.0);
    EXPECT_TRUE(1.0 == approx);
}

TEST_F(ApproxTest_694, ExactEqualityWithInt_694) {
    Approx approx(5);
    EXPECT_TRUE(approx == 5);
    EXPECT_TRUE(5 == approx);
}

TEST_F(ApproxTest_694, SymmetricEquality_694) {
    // operator==(Approx, T) should delegate to operator==(T, Approx)
    Approx approx(3.14);
    bool lhsResult = (approx == 3.14);
    bool rhsResult = (3.14 == approx);
    EXPECT_EQ(lhsResult, rhsResult);
}

TEST_F(ApproxTest_694, NotEqualWhenFarApart_694) {
    Approx approx(1.0);
    EXPECT_FALSE(approx == 2.0);
    EXPECT_FALSE(2.0 == approx);
}

// ============================================================
// Default epsilon tests
// ============================================================

TEST_F(ApproxTest_694, DefaultEpsilonAllowsSmallDifference_694) {
    // Default epsilon is ~float epsilon * 100 ≈ 1.19209e-05 * 100 ≈ 0.00119209
    // For value 100.0, tolerance is about 100 * 0.00119209 = 0.119209
    Approx approx(100.0);
    EXPECT_TRUE(approx == 100.1);
    EXPECT_TRUE(100.1 == approx);
}

TEST_F(ApproxTest_694, DefaultEpsilonRejectsTooLargeDifference_694) {
    Approx approx(100.0);
    EXPECT_FALSE(approx == 102.0);
    EXPECT_FALSE(102.0 == approx);
}

// ============================================================
// Custom epsilon tests
// ============================================================

TEST_F(ApproxTest_694, CustomEpsilonWidensRange_694) {
    Approx approx = Approx(100.0).epsilon(0.1); // 10% tolerance
    EXPECT_TRUE(approx == 109.0);
    EXPECT_TRUE(approx == 91.0);
    EXPECT_TRUE(109.0 == approx);
    EXPECT_TRUE(91.0 == approx);
}

TEST_F(ApproxTest_694, CustomEpsilonNarrowsRange_694) {
    Approx approx = Approx(100.0).epsilon(0.001); // 0.1% tolerance
    EXPECT_FALSE(approx == 101.0);
    EXPECT_FALSE(101.0 == approx);
    EXPECT_TRUE(approx == 100.05);
}

// ============================================================
// Margin tests
// ============================================================

TEST_F(ApproxTest_694, MarginAllowsAbsoluteDifference_694) {
    Approx approx = Approx(0.0).margin(0.5);
    EXPECT_TRUE(approx == 0.3);
    EXPECT_TRUE(0.3 == approx);
    EXPECT_TRUE(approx == -0.3);
    EXPECT_FALSE(approx == 1.0);
    EXPECT_FALSE(1.0 == approx);
}

TEST_F(ApproxTest_694, MarginWithZeroValue_694) {
    // With value 0, epsilon-based comparison won't help; margin is needed
    Approx approx = Approx(0.0).margin(0.01);
    EXPECT_TRUE(approx == 0.005);
    EXPECT_TRUE(0.005 == approx);
    EXPECT_FALSE(approx == 0.02);
}

// ============================================================
// Scale tests
// ============================================================

TEST_F(ApproxTest_694, ScaleAffectsComparison_694) {
    Approx approx = Approx(0.0).scale(100.0).epsilon(0.01);
    // With scale=100 and epsilon=0.01, the tolerance should be around 1.0
    EXPECT_TRUE(approx == 0.5);
    EXPECT_TRUE(0.5 == approx);
}

// ============================================================
// Negation operator tests
// ============================================================

TEST_F(ApproxTest_694, NegationOperator_694) {
    Approx approx = Approx(5.0);
    Approx negApprox = -approx;
    EXPECT_TRUE(negApprox == -5.0);
    EXPECT_TRUE(-5.0 == negApprox);
}

TEST_F(ApproxTest_694, NegationOfZero_694) {
    Approx approx = Approx(0.0);
    Approx negApprox = -approx;
    EXPECT_TRUE(negApprox == 0.0);
}

TEST_F(ApproxTest_694, NegationOfNegativeValue_694) {
    Approx approx = Approx(-3.0);
    Approx negApprox = -approx;
    EXPECT_TRUE(negApprox == 3.0);
    EXPECT_TRUE(3.0 == negApprox);
}

// ============================================================
// Call operator tests
// ============================================================

TEST_F(ApproxTest_694, CallOperatorCreatesNewApproxWithSameSettings_694) {
    Approx base = Approx(0.0).epsilon(0.1).margin(0.5);
    Approx derived = base(10.0);
    // derived should have value 10.0 with same epsilon/margin
    EXPECT_TRUE(derived == 10.0);
    EXPECT_TRUE(derived == 10.5); // within margin of 0.5 or 10% of 10 = 1.0
}

TEST_F(ApproxTest_694, CallOperatorWithIntValue_694) {
    Approx base = Approx(0.0).epsilon(0.01);
    Approx derived = base(100);
    EXPECT_TRUE(derived == 100);
    EXPECT_TRUE(100 == derived);
}

// ============================================================
// Custom factory method tests
// ============================================================

TEST_F(ApproxTest_694, CustomFactoryCreatesApproxWithZeroValue_694) {
    Approx approx = Approx::custom();
    EXPECT_TRUE(approx == 0.0);
    EXPECT_TRUE(0.0 == approx);
}

// ============================================================
// toString tests
// ============================================================

TEST_F(ApproxTest_694, ToStringReturnsNonEmpty_694) {
    Approx approx(1.5);
    std::string str = approx.toString();
    EXPECT_FALSE(str.empty());
}

TEST_F(ApproxTest_694, ToStringContainsApproxIndicator_694) {
    Approx approx(3.14);
    std::string str = approx.toString();
    // The string should contain some representation of the value
    EXPECT_NE(str.find("Approx"), std::string::npos);
}

// ============================================================
// Boundary condition tests
// ============================================================

TEST_F(ApproxTest_694, ZeroValueWithDefaultSettings_694) {
    Approx approx(0.0);
    EXPECT_TRUE(approx == 0.0);
    // Without margin, even tiny differences around 0 should fail
    // because epsilon * 0 = 0
    EXPECT_FALSE(approx == 0.001);
}

TEST_F(ApproxTest_694, VeryLargeValue_694) {
    double large = 1e15;
    Approx approx(large);
    EXPECT_TRUE(approx == large);
    EXPECT_TRUE(large == approx);
}

TEST_F(ApproxTest_694, VerySmallValue_694) {
    double small = 1e-15;
    Approx approx = Approx(small).margin(1e-16);
    EXPECT_TRUE(approx == small);
}

TEST_F(ApproxTest_694, NegativeValue_694) {
    Approx approx(-42.0);
    EXPECT_TRUE(approx == -42.0);
    EXPECT_TRUE(-42.0 == approx);
    EXPECT_FALSE(approx == 42.0);
}

// ============================================================
// Chaining tests
// ============================================================

TEST_F(ApproxTest_694, ChainingEpsilonAndMargin_694) {
    Approx approx = Approx(10.0).epsilon(0.01).margin(0.5);
    // Tolerance should be max of epsilon-based (0.01*10 = 0.1) and margin (0.5)
    EXPECT_TRUE(approx == 10.4);
    EXPECT_TRUE(10.4 == approx);
}

TEST_F(ApproxTest_694, ChainingEpsilonMarginScale_694) {
    Approx approx = Approx(10.0).epsilon(0.01).margin(0.0).scale(100.0);
    // epsilon-based tolerance considers scale
    EXPECT_TRUE(approx == 10.0);
}

// ============================================================
// Integer type tests
// ============================================================

TEST_F(ApproxTest_694, IntConstructor_694) {
    Approx approx(42);
    EXPECT_TRUE(approx == 42);
    EXPECT_TRUE(42 == approx);
    EXPECT_TRUE(approx == 42.0);
}

TEST_F(ApproxTest_694, FloatComparison_694) {
    Approx approx(1.0f);
    EXPECT_TRUE(approx == 1.0f);
    EXPECT_TRUE(1.0f == approx);
}

TEST_F(ApproxTest_694, LongComparison_694) {
    Approx approx(100L);
    EXPECT_TRUE(approx == 100L);
    EXPECT_TRUE(100L == approx);
}

// ============================================================
// Edge: exact boundary of tolerance
// ============================================================

TEST_F(ApproxTest_694, ExactlyAtMarginBoundary_694) {
    Approx approx = Approx(10.0).margin(1.0).epsilon(0.0);
    EXPECT_TRUE(approx == 11.0);  // exactly at boundary
    EXPECT_TRUE(approx == 9.0);   // exactly at boundary
    EXPECT_FALSE(approx == 11.1); // just beyond
    EXPECT_FALSE(approx == 8.9);  // just beyond
}

// ============================================================
// Multiple comparisons with same Approx
// ============================================================

TEST_F(ApproxTest_694, ReusableApprox_694) {
    Approx approx = Approx(5.0).epsilon(0.1);
    EXPECT_TRUE(approx == 5.0);
    EXPECT_TRUE(approx == 5.4);
    EXPECT_TRUE(approx == 4.6);
    EXPECT_FALSE(approx == 6.0);
    EXPECT_FALSE(approx == 4.0);
}
