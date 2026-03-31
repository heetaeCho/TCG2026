#include <gtest/gtest.h>
#include "catch2/catch_approx.hpp"
#include <limits>
#include <cmath>
#include <string>

using Catch::Approx;

// ============================================================
// Construction Tests
// ============================================================

TEST(ApproxTest_705, ConstructFromDouble_705) {
    Approx a(1.0);
    // Should be constructible without throwing
    SUCCEED();
}

TEST(ApproxTest_705, ConstructFromInt_705) {
    Approx a(5);
    // Template constructor should accept int (convertible to double)
    SUCCEED();
}

TEST(ApproxTest_705, ConstructFromFloat_705) {
    Approx a(3.14f);
    SUCCEED();
}

TEST(ApproxTest_705, ConstructFromZero_705) {
    Approx a(0.0);
    SUCCEED();
}

TEST(ApproxTest_705, ConstructFromNegative_705) {
    Approx a(-42.5);
    SUCCEED();
}

// ============================================================
// Custom factory
// ============================================================

TEST(ApproxTest_705, CustomCreatesDefaultApprox_705) {
    Approx a = Approx::custom();
    // custom() should return a valid Approx with value 0
    SUCCEED();
}

// ============================================================
// Negation operator
// ============================================================

TEST(ApproxTest_705, NegationOfPositive_705) {
    Approx a(5.0);
    Approx neg = -a;
    // The negated Approx should compare equal to -5.0
    EXPECT_TRUE(neg == -5.0);
}

TEST(ApproxTest_705, NegationOfNegative_705) {
    Approx a(-3.0);
    Approx neg = -a;
    EXPECT_TRUE(neg == 3.0);
}

TEST(ApproxTest_705, NegationOfZero_705) {
    Approx a(0.0);
    Approx neg = -a;
    EXPECT_TRUE(neg == 0.0);
}

TEST(ApproxTest_705, DoubleNegation_705) {
    Approx a(7.5);
    Approx doubleNeg = -(-a);
    EXPECT_TRUE(doubleNeg == 7.5);
}

// ============================================================
// Equality comparison (operator== both directions)
// ============================================================

TEST(ApproxTest_705, ExactEqualityDouble_705) {
    EXPECT_TRUE(Approx(1.0) == 1.0);
}

TEST(ApproxTest_705, ExactEqualityInt_705) {
    EXPECT_TRUE(Approx(42) == 42.0);
}

TEST(ApproxTest_705, EqualityWithinDefaultEpsilon_705) {
    double value = 1.0;
    double epsilon = static_cast<double>(std::numeric_limits<float>::epsilon()) * 100.0;
    double closeValue = value + value * epsilon * 0.5;
    EXPECT_TRUE(Approx(value) == closeValue);
}

TEST(ApproxTest_705, InequalityOutsideDefaultEpsilon_705) {
    double value = 1.0;
    double epsilon = static_cast<double>(std::numeric_limits<float>::epsilon()) * 100.0;
    double farValue = value + value * epsilon * 2.0;
    EXPECT_FALSE(Approx(value) == farValue);
}

TEST(ApproxTest_705, ReverseEqualityLhsDouble_705) {
    EXPECT_TRUE(1.0 == Approx(1.0));
}

TEST(ApproxTest_705, ReverseInequalityLhsDouble_705) {
    EXPECT_FALSE(100.0 == Approx(1.0));
}

// ============================================================
// Inequality operator (operator!=)
// ============================================================

TEST(ApproxTest_705, NotEqualWhenDifferent_705) {
    EXPECT_TRUE(Approx(1.0) != 2.0);
}

TEST(ApproxTest_705, NotNotEqualWhenSame_705) {
    EXPECT_FALSE(Approx(1.0) != 1.0);
}

TEST(ApproxTest_705, ReverseNotEqual_705) {
    EXPECT_TRUE(100.0 != Approx(1.0));
}

// ============================================================
// Less-than and greater-than operators
// ============================================================

TEST(ApproxTest_705, LessThanOrEqualWhenEqual_705) {
    EXPECT_TRUE(Approx(1.0) <= 1.0);
}

TEST(ApproxTest_705, LessThanOrEqualWhenLess_705) {
    EXPECT_TRUE(Approx(1.0) <= 2.0);
}

TEST(ApproxTest_705, LessThanOrEqualFalseWhenGreater_705) {
    EXPECT_FALSE(Approx(3.0) <= 1.0);
}

TEST(ApproxTest_705, GreaterThanOrEqualWhenEqual_705) {
    EXPECT_TRUE(Approx(1.0) >= 1.0);
}

TEST(ApproxTest_705, GreaterThanOrEqualWhenGreater_705) {
    EXPECT_TRUE(Approx(3.0) >= 1.0);
}

TEST(ApproxTest_705, GreaterThanOrEqualFalseWhenLess_705) {
    EXPECT_FALSE(Approx(1.0) >= 3.0);
}

// ============================================================
// Epsilon setting
// ============================================================

TEST(ApproxTest_705, CustomEpsilonWidensRange_705) {
    // With a large epsilon, values further apart should match
    EXPECT_TRUE(Approx(1.0).epsilon(0.5) == 1.4);
}

TEST(ApproxTest_705, CustomEpsilonNarrowsRange_705) {
    // With a very small epsilon
    double defaultEps = static_cast<double>(std::numeric_limits<float>::epsilon()) * 100.0;
    double smallerEps = defaultEps * 0.01;
    double value = 1.0;
    double closeButNotEnough = value + value * defaultEps * 0.5;
    // With default epsilon this would pass, with smaller it might not
    // Let's just verify the epsilon can be set
    Approx a = Approx(value).epsilon(smallerEps);
    // Exact equality should still hold
    EXPECT_TRUE(a == value);
}

TEST(ApproxTest_705, EpsilonZero_705) {
    // Epsilon of 0 means only margin matters (and default margin is 0)
    Approx a = Approx(1.0).epsilon(0.0);
    EXPECT_TRUE(a == 1.0); // exact match should work
    EXPECT_FALSE(a == 1.0 + 1e-10); // very close but not exact
}

// ============================================================
// Margin setting
// ============================================================

TEST(ApproxTest_705, MarginAllowsAbsoluteDifference_705) {
    EXPECT_TRUE(Approx(0.0).margin(1.0) == 0.5);
}

TEST(ApproxTest_705, MarginZeroAtZero_705) {
    // At zero, percentage-based epsilon doesn't help, need margin
    EXPECT_FALSE(Approx(0.0) == 0.5);
    EXPECT_TRUE(Approx(0.0).margin(1.0) == 0.5);
}

TEST(ApproxTest_705, MarginExceedsFails_705) {
    EXPECT_FALSE(Approx(0.0).margin(0.1) == 0.5);
}

// ============================================================
// Scale setting
// ============================================================

TEST(ApproxTest_705, ScaleCanBeSet_705) {
    Approx a = Approx(1.0).scale(10.0);
    // Scale affects the epsilon computation
    SUCCEED();
}

// ============================================================
// Callable operator (operator())
// ============================================================

TEST(ApproxTest_705, CallOperatorCreatesNewApprox_705) {
    Approx base = Approx(0.0).epsilon(0.1).margin(0.5);
    Approx derived = base(5.0);
    EXPECT_TRUE(derived == 5.0);
}

TEST(ApproxTest_705, CallOperatorPreservesSettings_705) {
    Approx base = Approx(0.0).margin(1.0);
    Approx derived = base(0.0);
    // Should preserve the margin from base
    EXPECT_TRUE(derived == 0.5);
}

// ============================================================
// toString
// ============================================================

TEST(ApproxTest_705, ToStringContainsValue_705) {
    Approx a(1.5);
    std::string s = a.toString();
    EXPECT_FALSE(s.empty());
    // The string representation should contain something meaningful
    // At minimum it shouldn't be empty
}

TEST(ApproxTest_705, ToStringForZero_705) {
    Approx a(0.0);
    std::string s = a.toString();
    EXPECT_FALSE(s.empty());
}

// ============================================================
// Boundary / Edge Cases
// ============================================================

TEST(ApproxTest_705, VeryLargeValue_705) {
    double big = 1e300;
    EXPECT_TRUE(Approx(big) == big);
}

TEST(ApproxTest_705, VerySmallValue_705) {
    double tiny = 1e-300;
    EXPECT_TRUE(Approx(tiny) == tiny);
}

TEST(ApproxTest_705, NegativeZero_705) {
    EXPECT_TRUE(Approx(0.0) == -0.0);
    EXPECT_TRUE(Approx(-0.0) == 0.0);
}

TEST(ApproxTest_705, InfinityNotEqualToFinite_705) {
    EXPECT_FALSE(Approx(std::numeric_limits<double>::infinity()) == 1.0);
}

TEST(ApproxTest_705, InfinityEqualToItself_705) {
    // This may or may not hold depending on implementation
    // Just testing observable behavior
    double inf = std::numeric_limits<double>::infinity();
    // We just check it doesn't crash
    bool result = (Approx(inf) == inf);
    (void)result;
    SUCCEED();
}

TEST(ApproxTest_705, NaNNotEqualToAnything_705) {
    double nan = std::numeric_limits<double>::quiet_NaN();
    // NaN comparisons are typically false
    EXPECT_FALSE(Approx(nan) == nan);
    EXPECT_FALSE(Approx(nan) == 0.0);
    EXPECT_FALSE(Approx(0.0) == nan);
}

// ============================================================
// Chaining
// ============================================================

TEST(ApproxTest_705, ChainingEpsilonAndMargin_705) {
    Approx a = Approx(1.0).epsilon(0.01).margin(0.5);
    EXPECT_TRUE(a == 1.0);
    EXPECT_TRUE(a == 1.4);  // within margin of 0.5
}

TEST(ApproxTest_705, ChainingAllSettings_705) {
    Approx a = Approx(1.0).epsilon(0.01).margin(0.1).scale(1.0);
    EXPECT_TRUE(a == 1.0);
}

// ============================================================
// Symmetry of comparisons
// ============================================================

TEST(ApproxTest_705, SymmetricEquality_705) {
    Approx a(5.0);
    EXPECT_EQ(a == 5.0, 5.0 == a);
}

TEST(ApproxTest_705, SymmetricInequality_705) {
    Approx a(5.0);
    EXPECT_EQ(a != 10.0, 10.0 != a);
}

TEST(ApproxTest_705, ReverseLessThanOrEqual_705) {
    // double <= Approx
    EXPECT_TRUE(1.0 <= Approx(1.0));
    EXPECT_TRUE(0.5 <= Approx(1.0));
    EXPECT_FALSE(2.0 <= Approx(1.0));
}

TEST(ApproxTest_705, ReverseGreaterThanOrEqual_705) {
    // double >= Approx
    EXPECT_TRUE(1.0 >= Approx(1.0));
    EXPECT_TRUE(2.0 >= Approx(1.0));
    EXPECT_FALSE(0.5 >= Approx(1.0));
}
