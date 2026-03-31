#include <gtest/gtest.h>
#include "catch2/catch_approx.hpp"
#include "catch2/catch_tostring.hpp"
#include <limits>
#include <string>
#include <cmath>

using Catch::Approx;

// ============================================================
// Construction Tests
// ============================================================

TEST(ApproxTest_709, ConstructFromDouble_709) {
    Approx a(1.0);
    // Should be constructible without throwing
    EXPECT_FALSE(a.toString().empty());
}

TEST(ApproxTest_709, ConstructFromInt_709) {
    Approx a(5);
    EXPECT_FALSE(a.toString().empty());
}

TEST(ApproxTest_709, ConstructFromFloat_709) {
    Approx a(3.14f);
    EXPECT_FALSE(a.toString().empty());
}

TEST(ApproxTest_709, ConstructZero_709) {
    Approx a(0.0);
    EXPECT_FALSE(a.toString().empty());
}

TEST(ApproxTest_709, ConstructNegative_709) {
    Approx a(-42.5);
    EXPECT_FALSE(a.toString().empty());
}

// ============================================================
// Custom factory
// ============================================================

TEST(ApproxTest_709, CustomFactory_709) {
    Approx a = Approx::custom();
    // custom() should return a valid Approx with value 0
    EXPECT_FALSE(a.toString().empty());
}

// ============================================================
// Negation operator
// ============================================================

TEST(ApproxTest_709, NegationOperator_709) {
    Approx a(5.0);
    Approx neg = -a;
    // The negated Approx should have a different toString
    std::string posStr = a.toString();
    std::string negStr = neg.toString();
    EXPECT_NE(posStr, negStr);
}

TEST(ApproxTest_709, NegationOfZero_709) {
    Approx a(0.0);
    Approx neg = -a;
    // Negation of zero; both should represent approximately 0
    // toString should still work
    EXPECT_FALSE(neg.toString().empty());
}

TEST(ApproxTest_709, NegationOfNegative_709) {
    Approx a(-3.0);
    Approx neg = -a;
    // Double negation should give back something representing +3.0
    EXPECT_FALSE(neg.toString().empty());
}

// ============================================================
// toString / StringMaker
// ============================================================

TEST(ApproxTest_709, ToStringContainsApprox_709) {
    Approx a(1.5);
    std::string s = a.toString();
    // The string representation should contain "Approx" somewhere
    EXPECT_NE(s.find("Approx"), std::string::npos);
}

TEST(ApproxTest_709, StringMakerConvert_709) {
    Approx a(2.5);
    std::string s = Catch::StringMaker<Catch::Approx>::convert(a);
    EXPECT_EQ(s, a.toString());
}

TEST(ApproxTest_709, ToStringLargeValue_709) {
    Approx a(1e15);
    std::string s = a.toString();
    EXPECT_FALSE(s.empty());
}

TEST(ApproxTest_709, ToStringSmallValue_709) {
    Approx a(1e-15);
    std::string s = a.toString();
    EXPECT_FALSE(s.empty());
}

// ============================================================
// Equality comparison (using operator== which relies on equalityComparisonImpl)
// ============================================================

TEST(ApproxTest_709, DefaultEqualityExactMatch_709) {
    Approx a(1.0);
    EXPECT_TRUE(a == 1.0);
}

TEST(ApproxTest_709, DefaultEqualityCloseValue_709) {
    Approx a(1.0);
    // Default epsilon is float::epsilon * 100, so small perturbations should match
    double close = 1.0 + 1e-8;
    EXPECT_TRUE(a == close);
}

TEST(ApproxTest_709, DefaultEqualityDistantValue_709) {
    Approx a(1.0);
    EXPECT_FALSE(a == 2.0);
}

TEST(ApproxTest_709, EqualitySymmetric_709) {
    Approx a(5.0);
    EXPECT_TRUE(5.0 == a);
    EXPECT_TRUE(a == 5.0);
}

TEST(ApproxTest_709, InequalityOperator_709) {
    Approx a(1.0);
    EXPECT_TRUE(a != 2.0);
    EXPECT_TRUE(2.0 != a);
    EXPECT_FALSE(a != 1.0);
}

TEST(ApproxTest_709, LessThanOrEqualOperator_709) {
    Approx a(1.0);
    EXPECT_TRUE(0.5 <= a);
    EXPECT_TRUE(1.0 <= a); // equal counts as <=
}

TEST(ApproxTest_709, GreaterThanOrEqualOperator_709) {
    Approx a(1.0);
    EXPECT_TRUE(1.5 >= a);
    EXPECT_TRUE(1.0 >= a); // equal counts as >=
}

// ============================================================
// Epsilon setting
// ============================================================

TEST(ApproxTest_709, CustomEpsilon_709) {
    Approx a = Approx(100.0).epsilon(0.01); // 1% tolerance
    EXPECT_TRUE(a == 100.5);  // within 1%
    EXPECT_TRUE(a == 99.5);   // within 1%
    EXPECT_FALSE(a == 110.0); // outside 1%
}

TEST(ApproxTest_709, TightEpsilon_709) {
    Approx a = Approx(1.0).epsilon(0.0001); // 0.01% tolerance
    EXPECT_TRUE(a == 1.0);
    EXPECT_TRUE(a == 1.00005);
    EXPECT_FALSE(a == 1.01);
}

TEST(ApproxTest_709, EpsilonZero_709) {
    // Epsilon of 0 means only margin matters (default margin is 0)
    Approx a = Approx(1.0).epsilon(0.0);
    EXPECT_TRUE(a == 1.0);   // exact match
    EXPECT_FALSE(a == 1.001); // no tolerance
}

// ============================================================
// Margin setting
// ============================================================

TEST(ApproxTest_709, CustomMargin_709) {
    Approx a = Approx(0.0).margin(0.5);
    EXPECT_TRUE(a == 0.3);
    EXPECT_TRUE(a == -0.3);
    EXPECT_FALSE(a == 1.0);
}

TEST(ApproxTest_709, MarginOverridesEpsilonForZero_709) {
    // For value 0, epsilon-based tolerance is 0, so margin is needed
    Approx a = Approx(0.0).margin(0.001);
    EXPECT_TRUE(a == 0.0005);
    EXPECT_FALSE(a == 0.01);
}

TEST(ApproxTest_709, MarginZero_709) {
    Approx a = Approx(1.0).margin(0.0).epsilon(0.0);
    EXPECT_TRUE(a == 1.0);
    EXPECT_FALSE(a == 1.0001);
}

// ============================================================
// Scale setting
// ============================================================

TEST(ApproxTest_709, CustomScale_709) {
    // Scale affects the epsilon-based tolerance: tolerance = epsilon * (scale + value)
    Approx a = Approx(0.0).scale(100.0);
    // Now tolerance based on epsilon * (100 + 0) rather than epsilon * 0
    // With default epsilon ~= float_eps * 100 ≈ 0.0119...
    // tolerance ≈ 0.0119 * 100 ≈ 1.19
    EXPECT_TRUE(a == 0.5);
}

// ============================================================
// operator() - creating a new Approx with different value but same settings
// ============================================================

TEST(ApproxTest_709, CallOperatorCreatesNewApprox_709) {
    Approx a = Approx(1.0).epsilon(0.01).margin(0.5);
    Approx b = a(5.0);
    // b should approximate 5.0 with same epsilon/margin
    EXPECT_TRUE(b == 5.0);
    EXPECT_TRUE(b == 5.04); // within 1% of 5 = 0.05
    // Original should still approximate 1.0
    EXPECT_TRUE(a == 1.0);
}

TEST(ApproxTest_709, CallOperatorWithZero_709) {
    Approx a = Approx(1.0).margin(0.1);
    Approx b = a(0.0);
    EXPECT_TRUE(b == 0.05);
    EXPECT_FALSE(b == 0.5);
}

// ============================================================
// Chaining
// ============================================================

TEST(ApproxTest_709, ChainingEpsilonMarginScale_709) {
    Approx a = Approx(10.0).epsilon(0.01).margin(0.5).scale(1.0);
    EXPECT_TRUE(a == 10.0);
    EXPECT_TRUE(a == 10.05);
}

// ============================================================
// Edge cases with special floating-point values
// ============================================================

TEST(ApproxTest_709, LargeValue_709) {
    double large = 1e18;
    Approx a(large);
    EXPECT_TRUE(a == large);
}

TEST(ApproxTest_709, VerySmallValue_709) {
    double small = 1e-18;
    Approx a = Approx(small).margin(1e-17);
    EXPECT_TRUE(a == small);
}

TEST(ApproxTest_709, NegativeValueEquality_709) {
    Approx a(-5.0);
    EXPECT_TRUE(a == -5.0);
    EXPECT_FALSE(a == 5.0);
}

TEST(ApproxTest_709, NegationPreservesEpsilonMargin_709) {
    Approx a = Approx(5.0).epsilon(0.01).margin(0.1);
    Approx neg = -a;
    EXPECT_TRUE(neg == -5.0);
    EXPECT_TRUE(neg == -5.04); // within 1% of 5
}

// ============================================================
// Boundary: epsilon at boundaries
// ============================================================

TEST(ApproxTest_709, EpsilonBoundaryJustInside_709) {
    // epsilon = 0.1 means 10% tolerance relative to max(scale, abs(value))
    Approx a = Approx(100.0).epsilon(0.1);
    // tolerance = 0.1 * 100 = 10
    EXPECT_TRUE(a == 109.9);
}

TEST(ApproxTest_709, EpsilonBoundaryJustOutside_709) {
    Approx a = Approx(100.0).epsilon(0.1).margin(0.0);
    // tolerance = 0.1 * 100 = 10
    EXPECT_FALSE(a == 111.0);
}

// ============================================================
// Margin boundary
// ============================================================

TEST(ApproxTest_709, MarginBoundaryJustInside_709) {
    Approx a = Approx(0.0).epsilon(0.0).margin(1.0);
    EXPECT_TRUE(a == 0.99);
}

TEST(ApproxTest_709, MarginBoundaryJustOutside_709) {
    Approx a = Approx(0.0).epsilon(0.0).margin(1.0);
    EXPECT_FALSE(a == 1.5);
}

// ============================================================
// Integer comparison
// ============================================================

TEST(ApproxTest_709, IntegerComparison_709) {
    Approx a(10);
    EXPECT_TRUE(a == 10);
    EXPECT_TRUE(10 == a);
}
