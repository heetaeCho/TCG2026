#include <gtest/gtest.h>
#include "catch2/catch_approx.hpp"
#include <limits>
#include <cmath>
#include <string>

using Catch::Approx;

// ============================================================
// Construction Tests
// ============================================================

TEST(ApproxConstructionTest_702, ConstructFromDouble_702) {
    Approx a(1.0);
    // Should be constructible without throwing
    SUCCEED();
}

TEST(ApproxConstructionTest_702, ConstructFromInt_702) {
    Approx a(5);
    SUCCEED();
}

TEST(ApproxConstructionTest_702, ConstructFromFloat_702) {
    Approx a(3.14f);
    SUCCEED();
}

TEST(ApproxConstructionTest_702, ConstructFromZero_702) {
    Approx a(0.0);
    SUCCEED();
}

TEST(ApproxConstructionTest_702, ConstructFromNegative_702) {
    Approx a(-42.0);
    SUCCEED();
}

// ============================================================
// Custom Factory Tests
// ============================================================

TEST(ApproxCustomTest_702, CustomCreatesInstance_702) {
    Approx a = Approx::custom();
    SUCCEED();
}

// ============================================================
// Equality Comparison Tests (operator== via friend)
// ============================================================

TEST(ApproxEqualityTest_702, ExactMatch_702) {
    EXPECT_TRUE(Approx(1.0) == 1.0);
}

TEST(ApproxEqualityTest_702, ExactMatchZero_702) {
    EXPECT_TRUE(Approx(0.0) == 0.0);
}

TEST(ApproxEqualityTest_702, CloseValuesWithinDefaultEpsilon_702) {
    double val = 1.0;
    double eps = static_cast<double>(std::numeric_limits<float>::epsilon()) * 100.0;
    double closeVal = val + val * eps * 0.5;
    EXPECT_TRUE(Approx(val) == closeVal);
}

TEST(ApproxEqualityTest_702, FarValuesOutsideDefaultEpsilon_702) {
    double val = 1.0;
    EXPECT_FALSE(Approx(val) == 2.0);
}

TEST(ApproxEqualityTest_702, SymmetricEquality_702) {
    EXPECT_TRUE(1.0 == Approx(1.0));
    EXPECT_TRUE(Approx(1.0) == 1.0);
}

TEST(ApproxEqualityTest_702, InequalityOperator_702) {
    EXPECT_TRUE(Approx(1.0) != 2.0);
    EXPECT_TRUE(2.0 != Approx(1.0));
}

TEST(ApproxEqualityTest_702, InequalitySymmetric_702) {
    EXPECT_FALSE(Approx(1.0) != 1.0);
    EXPECT_FALSE(1.0 != Approx(1.0));
}

// ============================================================
// Comparison Operators Tests
// ============================================================

TEST(ApproxComparisonTest_702, LessThanOrEqual_702) {
    EXPECT_TRUE(1.0 <= Approx(1.0));
    EXPECT_TRUE(0.5 <= Approx(1.0));
}

TEST(ApproxComparisonTest_702, GreaterThanOrEqual_702) {
    EXPECT_TRUE(1.0 >= Approx(1.0));
    EXPECT_TRUE(2.0 >= Approx(1.0));
}

TEST(ApproxComparisonTest_702, LessThan_702) {
    EXPECT_TRUE(0.5 < Approx(1.0));
    EXPECT_FALSE(1.0 < Approx(1.0));
}

TEST(ApproxComparisonTest_702, GreaterThan_702) {
    EXPECT_TRUE(2.0 > Approx(1.0));
    EXPECT_FALSE(1.0 > Approx(1.0));
}

// ============================================================
// Margin Tests
// ============================================================

TEST(ApproxMarginTest_702, MarginWithDouble_702) {
    Approx a(1.0);
    a.margin(0.5);
    EXPECT_TRUE(a == 1.3);
    EXPECT_TRUE(a == 0.7);
}

TEST(ApproxMarginTest_702, MarginWithInt_702) {
    Approx a(10.0);
    a.margin(2);
    EXPECT_TRUE(a == 11);
    EXPECT_TRUE(a == 9);
}

TEST(ApproxMarginTest_702, MarginZero_702) {
    Approx a(1.0);
    a.margin(0.0);
    // With zero margin, only epsilon-based comparison should work
    EXPECT_TRUE(a == 1.0);
}

TEST(ApproxMarginTest_702, MarginChainingReturnsRef_702) {
    Approx a(1.0);
    Approx& ref = a.margin(0.1);
    EXPECT_EQ(&ref, &a);
}

TEST(ApproxMarginTest_702, NegativeMarginThrows_702) {
    Approx a(1.0);
    EXPECT_THROW(a.margin(-1.0), std::domain_error);
}

TEST(ApproxMarginTest_702, LargeMarginAcceptsWideRange_702) {
    Approx a(0.0);
    a.margin(100.0);
    EXPECT_TRUE(a == 99.0);
    EXPECT_TRUE(a == -99.0);
    EXPECT_FALSE(a == 101.0);
}

// ============================================================
// Epsilon Tests
// ============================================================

TEST(ApproxEpsilonTest_702, EpsilonWithDouble_702) {
    Approx a(100.0);
    a.epsilon(0.1); // 10% tolerance
    EXPECT_TRUE(a == 109.0);
    EXPECT_TRUE(a == 91.0);
}

TEST(ApproxEpsilonTest_702, EpsilonChainingReturnsRef_702) {
    Approx a(1.0);
    Approx& ref = a.epsilon(0.01);
    EXPECT_EQ(&ref, &a);
}

TEST(ApproxEpsilonTest_702, NegativeEpsilonThrows_702) {
    Approx a(1.0);
    EXPECT_THROW(a.epsilon(-0.1), std::domain_error);
}

TEST(ApproxEpsilonTest_702, EpsilonGreaterThanOneThrows_702) {
    Approx a(1.0);
    EXPECT_THROW(a.epsilon(1.5), std::domain_error);
}

TEST(ApproxEpsilonTest_702, EpsilonZero_702) {
    Approx a(1.0);
    a.epsilon(0.0);
    // With zero epsilon and zero margin, only exact match should work
    a.margin(0.0);
    EXPECT_TRUE(a == 1.0);
    EXPECT_FALSE(a == 1.0 + 1e-15);
}

// ============================================================
// Scale Tests
// ============================================================

TEST(ApproxScaleTest_702, ScaleChainingReturnsRef_702) {
    Approx a(1.0);
    Approx& ref = a.scale(2.0);
    EXPECT_EQ(&ref, &a);
}

TEST(ApproxScaleTest_702, ScaleWithInt_702) {
    Approx a(0.0);
    a.scale(100);
    SUCCEED();
}

// ============================================================
// Negation Operator Tests
// ============================================================

TEST(ApproxNegationTest_702, NegationOfPositive_702) {
    Approx a(5.0);
    Approx neg = -a;
    EXPECT_TRUE(neg == -5.0);
}

TEST(ApproxNegationTest_702, NegationOfNegative_702) {
    Approx a(-3.0);
    Approx neg = -a;
    EXPECT_TRUE(neg == 3.0);
}

TEST(ApproxNegationTest_702, NegationOfZero_702) {
    Approx a(0.0);
    Approx neg = -a;
    EXPECT_TRUE(neg == 0.0);
}

TEST(ApproxNegationTest_702, NegationPreservesMargin_702) {
    Approx a(5.0);
    a.margin(1.0);
    Approx neg = -a;
    EXPECT_TRUE(neg == -5.5);
    EXPECT_TRUE(neg == -4.5);
}

// ============================================================
// Function Call Operator Tests
// ============================================================

TEST(ApproxCallOperatorTest_702, CallOperatorCreatesNewApprox_702) {
    Approx a(1.0);
    a.margin(0.5).epsilon(0.01);
    Approx b = a(2.0);
    // The new Approx should be centered on 2.0 but retain settings
    EXPECT_TRUE(b == 2.0);
}

TEST(ApproxCallOperatorTest_702, CallOperatorWithInt_702) {
    Approx a(1.0);
    Approx b = a(42);
    EXPECT_TRUE(b == 42.0);
}

// ============================================================
// toString Tests
// ============================================================

TEST(ApproxToStringTest_702, ToStringReturnsNonEmpty_702) {
    Approx a(1.0);
    std::string s = a.toString();
    EXPECT_FALSE(s.empty());
}

TEST(ApproxToStringTest_702, ToStringContainsApprox_702) {
    Approx a(1.0);
    std::string s = a.toString();
    EXPECT_NE(s.find("Approx"), std::string::npos);
}

TEST(ApproxToStringTest_702, ToStringContainsValue_702) {
    Approx a(3.14);
    std::string s = a.toString();
    // Should contain some representation of the value
    EXPECT_NE(s.find("3.14"), std::string::npos);
}

// ============================================================
// Chaining Tests
// ============================================================

TEST(ApproxChainingTest_702, MarginEpsilonScaleChaining_702) {
    Approx a(10.0);
    Approx& ref = a.margin(1.0).epsilon(0.05).scale(2.0);
    EXPECT_EQ(&ref, &a);
    EXPECT_TRUE(a == 10.0);
}

// ============================================================
// Boundary / Special Value Tests
// ============================================================

TEST(ApproxBoundaryTest_702, VerySmallValues_702) {
    double tiny = 1e-300;
    Approx a(tiny);
    a.margin(1e-300);
    EXPECT_TRUE(a == tiny);
}

TEST(ApproxBoundaryTest_702, VeryLargeValues_702) {
    double large = 1e300;
    Approx a(large);
    EXPECT_TRUE(a == large);
}

TEST(ApproxBoundaryTest_702, InfinityValue_702) {
    double inf = std::numeric_limits<double>::infinity();
    Approx a(inf);
    EXPECT_TRUE(a == inf);
}

TEST(ApproxBoundaryTest_702, NegativeInfinityValue_702) {
    double neginf = -std::numeric_limits<double>::infinity();
    Approx a(neginf);
    EXPECT_TRUE(a == neginf);
}

TEST(ApproxBoundaryTest_702, NaNNotEqualToAnything_702) {
    double nan_val = std::numeric_limits<double>::quiet_NaN();
    Approx a(nan_val);
    EXPECT_FALSE(a == nan_val);
    EXPECT_FALSE(a == 0.0);
}

// ============================================================
// Integration-like: margin + epsilon combined
// ============================================================

TEST(ApproxIntegrationTest_702, MarginAndEpsilonCombined_702) {
    // Margin provides absolute tolerance, epsilon provides relative
    // The comparison should pass if within either
    Approx a(100.0);
    a.epsilon(0.01).margin(5.0); // 1% relative or 5.0 absolute
    EXPECT_TRUE(a == 104.0);  // within margin
    EXPECT_TRUE(a == 100.5);  // within epsilon
    EXPECT_TRUE(a == 96.0);   // within margin
}

TEST(ApproxIntegrationTest_702, SmallValueWithMargin_702) {
    // For values near zero, epsilon-based comparison breaks down
    // margin provides a floor
    Approx a(0.0);
    a.margin(0.001);
    EXPECT_TRUE(a == 0.0005);
    EXPECT_FALSE(a == 0.002);
}
