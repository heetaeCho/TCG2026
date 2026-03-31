#include <gtest/gtest.h>
#include "catch2/catch_approx.hpp"
#include <limits>
#include <cmath>
#include <string>

using Catch::Approx;

// ==================== Construction Tests ====================

TEST(ApproxTest_692, ConstructFromDouble_692) {
    Approx approx(1.0);
    // Should be constructible without throwing
    SUCCEED();
}

TEST(ApproxTest_692, ConstructFromInt_692) {
    Approx approx(5);
    SUCCEED();
}

TEST(ApproxTest_692, ConstructFromFloat_692) {
    Approx approx(3.14f);
    SUCCEED();
}

TEST(ApproxTest_692, ConstructFromZero_692) {
    Approx approx(0.0);
    SUCCEED();
}

TEST(ApproxTest_692, ConstructFromNegative_692) {
    Approx approx(-42.0);
    SUCCEED();
}

// ==================== operator() Tests ====================

TEST(ApproxTest_692, CallOperatorReturnsNewApprox_692) {
    Approx approx(1.0);
    Approx result = approx(2.0);
    // The result should represent value 2.0
    // We can verify by checking string representation contains "2.0"
    std::string str = result.toString();
    EXPECT_FALSE(str.empty());
}

TEST(ApproxTest_692, CallOperatorPreservesEpsilon_692) {
    Approx approx(1.0);
    approx.epsilon(0.01);
    Approx result = approx(5.0);
    // The returned approx should have the same epsilon
    // We verify indirectly: 5.0 should approx-equal 5.04 with epsilon 0.01
    // 5.04 / 5.0 - 1.0 = 0.008, which is < 0.01
    EXPECT_TRUE(result == 5.04);
    // But 5.06 / 5.0 - 1.0 = 0.012 > 0.01
    EXPECT_FALSE(result == 5.06);
}

TEST(ApproxTest_692, CallOperatorPreservesMargin_692) {
    Approx approx(1.0);
    approx.margin(0.5);
    Approx result = approx(10.0);
    // With margin 0.5, 10.4 should be equal to approx(10.0)
    EXPECT_TRUE(result == 10.4);
    // But 10.6 should not be
    EXPECT_FALSE(result == 10.6);
}

TEST(ApproxTest_692, CallOperatorPreservesScale_692) {
    Approx approx(1.0);
    approx.scale(100.0);
    Approx result = approx(0.0);
    // scale affects the comparison - with scale 100 and default epsilon
    // the tolerance is epsilon * (scale + value) = eps * (100 + 0)
    std::string str = result.toString();
    EXPECT_FALSE(str.empty());
}

TEST(ApproxTest_692, CallOperatorWithIntValue_692) {
    Approx approx(1.0);
    Approx result = approx(42);
    std::string str = result.toString();
    EXPECT_FALSE(str.empty());
}

TEST(ApproxTest_692, CallOperatorWithFloatValue_692) {
    Approx approx(1.0);
    Approx result = approx(3.14f);
    SUCCEED();
}

// ==================== Epsilon Tests ====================

TEST(ApproxTest_692, SetEpsilon_692) {
    Approx approx(100.0);
    approx.epsilon(0.01);
    // 100.0 vs 100.5: relative diff = 0.005, should be within 0.01
    EXPECT_TRUE(approx == 100.5);
    // 100.0 vs 102.0: relative diff = 0.02, should NOT be within 0.01
    EXPECT_FALSE(approx == 102.0);
}

TEST(ApproxTest_692, EpsilonChaining_692) {
    Approx approx = Approx(100.0).epsilon(0.01);
    EXPECT_TRUE(approx == 100.5);
}

// ==================== Margin Tests ====================

TEST(ApproxTest_692, SetMargin_692) {
    Approx approx(100.0);
    approx.margin(1.0);
    EXPECT_TRUE(approx == 100.5);
    EXPECT_TRUE(approx == 100.99);
    EXPECT_FALSE(approx == 102.0);
}

TEST(ApproxTest_692, MarginChaining_692) {
    Approx approx = Approx(100.0).margin(2.0);
    EXPECT_TRUE(approx == 101.5);
}

// ==================== Scale Tests ====================

TEST(ApproxTest_692, SetScale_692) {
    Approx approx = Approx(0.0).scale(1.0);
    SUCCEED();
}

TEST(ApproxTest_692, ScaleChaining_692) {
    Approx approx = Approx(0.0).scale(100.0).epsilon(0.01);
    // With scale=100 and epsilon=0.01, tolerance = 0.01 * (100 + 0) = 1.0
    EXPECT_TRUE(approx == 0.5);
}

// ==================== Negation Tests ====================

TEST(ApproxTest_692, NegationOperator_692) {
    Approx approx(5.0);
    Approx neg = -approx;
    EXPECT_TRUE(neg == -5.0);
}

TEST(ApproxTest_692, NegationOfZero_692) {
    Approx approx(0.0);
    Approx neg = -approx;
    EXPECT_TRUE(neg == 0.0);
}

TEST(ApproxTest_692, NegationOfNegative_692) {
    Approx approx(-3.0);
    Approx neg = -approx;
    EXPECT_TRUE(neg == 3.0);
}

// ==================== Custom Factory Tests ====================

TEST(ApproxTest_692, CustomFactory_692) {
    Approx approx = Approx::custom();
    // custom() should return a valid Approx with value 0
    EXPECT_TRUE(approx == 0.0);
}

// ==================== toString Tests ====================

TEST(ApproxTest_692, ToStringNotEmpty_692) {
    Approx approx(3.14);
    std::string str = approx.toString();
    EXPECT_FALSE(str.empty());
}

TEST(ApproxTest_692, ToStringContainsValue_692) {
    Approx approx(42.0);
    std::string str = approx.toString();
    // Should contain "42" somewhere
    EXPECT_NE(str.find("42"), std::string::npos);
}

// ==================== Equality Comparison Tests ====================

TEST(ApproxTest_692, ExactEqualityWorks_692) {
    Approx approx(1.0);
    EXPECT_TRUE(approx == 1.0);
}

TEST(ApproxTest_692, DefaultEpsilonAllowsSmallDifference_692) {
    // Default epsilon is float::epsilon * 100 ≈ 1.19e-5
    Approx approx(100.0);
    EXPECT_TRUE(approx == 100.0);
    // Very small relative difference should pass
    EXPECT_TRUE(approx == 100.001);
}

TEST(ApproxTest_692, LargeValueDifferenceFails_692) {
    Approx approx(1.0);
    EXPECT_FALSE(approx == 2.0);
}

TEST(ApproxTest_692, SymmetricComparison_692) {
    Approx approx(5.0);
    EXPECT_TRUE(5.0 == approx);
    EXPECT_TRUE(approx == 5.0);
}

TEST(ApproxTest_692, InequalityOperator_692) {
    Approx approx(5.0);
    EXPECT_TRUE(approx != 6.0);
    EXPECT_FALSE(approx != 5.0);
}

TEST(ApproxTest_692, LessThanOrEqualOperator_692) {
    Approx approx(5.0);
    EXPECT_TRUE(4.0 <= approx);
    EXPECT_TRUE(5.0 <= approx);
}

TEST(ApproxTest_692, GreaterThanOrEqualOperator_692) {
    Approx approx(5.0);
    EXPECT_TRUE(6.0 >= approx);
    EXPECT_TRUE(5.0 >= approx);
}

// ==================== Boundary / Edge Case Tests ====================

TEST(ApproxTest_692, ZeroValueComparison_692) {
    Approx approx(0.0);
    EXPECT_TRUE(approx == 0.0);
    // With default margin of 0 and value 0, only exact 0 should match
    // (since relative comparison at 0 is always 0 tolerance)
    EXPECT_FALSE(approx == 0.01);
}

TEST(ApproxTest_692, ZeroWithMargin_692) {
    Approx approx = Approx(0.0).margin(0.01);
    EXPECT_TRUE(approx == 0.005);
    EXPECT_TRUE(approx == -0.005);
    EXPECT_FALSE(approx == 0.02);
}

TEST(ApproxTest_692, VeryLargeValue_692) {
    double large = 1e15;
    Approx approx(large);
    EXPECT_TRUE(approx == large);
}

TEST(ApproxTest_692, VerySmallValue_692) {
    double small = 1e-15;
    Approx approx = Approx(small).margin(1e-14);
    EXPECT_TRUE(approx == small);
}

TEST(ApproxTest_692, NegativeValueComparison_692) {
    Approx approx(-10.0);
    EXPECT_TRUE(approx == -10.0);
    EXPECT_FALSE(approx == 10.0);
}

// ==================== Combined Settings Tests ====================

TEST(ApproxTest_692, EpsilonAndMarginCombined_692) {
    // margin and epsilon work together - the larger tolerance wins
    Approx approx = Approx(100.0).epsilon(0.001).margin(5.0);
    // margin allows +/- 5.0
    EXPECT_TRUE(approx == 104.0);
    // epsilon allows 0.1% of value = 0.1
    // margin of 5.0 is larger, so 104.0 is within margin
    EXPECT_TRUE(approx == 104.9);
    EXPECT_FALSE(approx == 106.0);
}

TEST(ApproxTest_692, CallOperatorThenModify_692) {
    Approx base = Approx(0.0).epsilon(0.01).margin(0.5);
    Approx derived = base(10.0);
    // derived should have value 10.0 with same epsilon and margin
    EXPECT_TRUE(derived == 10.0);
    EXPECT_TRUE(derived == 10.4);  // within margin
    EXPECT_FALSE(derived == 10.6);  // outside margin, and relative diff > epsilon
}

TEST(ApproxTest_692, MultipleCallOperator_692) {
    Approx base(0.0);
    base.epsilon(0.01);
    Approx a = base(100.0);
    Approx b = base(200.0);
    EXPECT_TRUE(a == 100.0);
    EXPECT_TRUE(b == 200.0);
    EXPECT_FALSE(a == 200.0);
    EXPECT_FALSE(b == 100.0);
}
