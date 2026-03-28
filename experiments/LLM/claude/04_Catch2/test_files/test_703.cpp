#include <gtest/gtest.h>
#include "catch2/catch_approx.hpp"
#include <limits>
#include <string>

using Catch::Approx;

// ============================================================
// Construction Tests
// ============================================================

TEST(ApproxTest_703, ConstructFromDouble_703) {
    Approx a(1.0);
    // Should not throw; basic construction from double
    SUCCEED();
}

TEST(ApproxTest_703, ConstructFromInt_703) {
    Approx a(42);
    // Template constructor converts int to double
    SUCCEED();
}

TEST(ApproxTest_703, ConstructFromFloat_703) {
    Approx a(3.14f);
    SUCCEED();
}

TEST(ApproxTest_703, ConstructFromZero_703) {
    Approx a(0.0);
    SUCCEED();
}

TEST(ApproxTest_703, ConstructFromNegative_703) {
    Approx a(-5.5);
    SUCCEED();
}

// ============================================================
// Custom factory
// ============================================================

TEST(ApproxTest_703, CustomFactory_703) {
    Approx a = Approx::custom();
    // custom() should return a valid Approx object
    SUCCEED();
}

// ============================================================
// Negation operator
// ============================================================

TEST(ApproxTest_703, NegationOperator_703) {
    Approx a(5.0);
    Approx neg = -a;
    // -Approx(5.0) should compare equal to -5.0
    EXPECT_TRUE(-5.0 == neg);
}

TEST(ApproxTest_703, NegationOfZero_703) {
    Approx a(0.0);
    Approx neg = -a;
    EXPECT_TRUE(0.0 == neg);
}

TEST(ApproxTest_703, NegationOfNegative_703) {
    Approx a(-3.0);
    Approx neg = -a;
    EXPECT_TRUE(3.0 == neg);
}

// ============================================================
// Equality comparison (operator==)
// ============================================================

TEST(ApproxTest_703, ExactEquality_703) {
    EXPECT_TRUE(1.0 == Approx(1.0));
}

TEST(ApproxTest_703, EqualityWithinDefaultEpsilon_703) {
    double val = 1.0;
    double eps = static_cast<double>(std::numeric_limits<float>::epsilon()) * 100.0;
    // A value within default epsilon * scale should be equal
    EXPECT_TRUE(val == Approx(val));
}

TEST(ApproxTest_703, EqualitySymmetric_703) {
    EXPECT_TRUE(Approx(1.0) == 1.0);
    EXPECT_TRUE(1.0 == Approx(1.0));
}

TEST(ApproxTest_703, InequalityFarValues_703) {
    EXPECT_FALSE(1.0 == Approx(2.0));
}

TEST(ApproxTest_703, NotEqualOperator_703) {
    EXPECT_TRUE(1.0 != Approx(2.0));
    EXPECT_FALSE(1.0 != Approx(1.0));
}

// ============================================================
// Less than / greater than
// ============================================================

TEST(ApproxTest_703, LessThanOrEqual_703) {
    EXPECT_TRUE(1.0 <= Approx(1.0));
    EXPECT_TRUE(0.5 <= Approx(1.0));
}

TEST(ApproxTest_703, GreaterThanOrEqual_703) {
    EXPECT_TRUE(1.0 >= Approx(1.0));
    EXPECT_TRUE(1.5 >= Approx(1.0));
}

TEST(ApproxTest_703, LessThan_703) {
    // 0.5 is clearly less than Approx(1.0)
    EXPECT_TRUE(0.5 < Approx(1.0));
    // 1.0 is not less than Approx(1.0) because they are equal
    EXPECT_FALSE(1.0 < Approx(1.0));
}

TEST(ApproxTest_703, GreaterThan_703) {
    EXPECT_TRUE(1.5 > Approx(1.0));
    EXPECT_FALSE(1.0 > Approx(1.0));
}

// ============================================================
// Epsilon modifier
// ============================================================

TEST(ApproxTest_703, EpsilonMakesComparisonWider_703) {
    // With a large epsilon, values that differ by a lot should still match
    EXPECT_TRUE(1.0 == Approx(1.1).epsilon(0.2));
}

TEST(ApproxTest_703, EpsilonMakesComparisonTighter_703) {
    // With a very small epsilon, even close values should not match
    double a = 1.0;
    double b = 1.0 + 1e-5;
    EXPECT_FALSE(a == Approx(b).epsilon(1e-10).margin(0.0));
}

TEST(ApproxTest_703, EpsilonReturnsSelf_703) {
    Approx a(1.0);
    Approx& ref = a.epsilon(0.01);
    EXPECT_EQ(&a, &ref);
}

TEST(ApproxTest_703, EpsilonFromInt_703) {
    // epsilon can take an int (converted to double)
    Approx a(100.0);
    a.epsilon(1); // Should not throw
    SUCCEED();
}

// ============================================================
// Margin modifier
// ============================================================

TEST(ApproxTest_703, MarginAllowsAbsoluteDifference_703) {
    // Default epsilon is relative; margin provides an absolute tolerance
    EXPECT_TRUE(0.0 == Approx(0.0).margin(0.001));
    EXPECT_TRUE(0.0005 == Approx(0.0).margin(0.001));
}

TEST(ApproxTest_703, MarginNotEnough_703) {
    EXPECT_FALSE(0.1 == Approx(0.0).margin(0.01));
}

TEST(ApproxTest_703, MarginReturnsSelf_703) {
    Approx a(1.0);
    Approx& ref = a.margin(0.5);
    EXPECT_EQ(&a, &ref);
}

TEST(ApproxTest_703, MarginZero_703) {
    // With zero margin and comparing near zero, only exact match works
    EXPECT_TRUE(0.0 == Approx(0.0).margin(0.0));
    EXPECT_FALSE(1e-10 == Approx(0.0).margin(0.0).epsilon(0.0));
}

// ============================================================
// Scale modifier
// ============================================================

TEST(ApproxTest_703, ScaleReturnsSelf_703) {
    Approx a(1.0);
    Approx& ref = a.scale(2.0);
    EXPECT_EQ(&a, &ref);
}

TEST(ApproxTest_703, ScaleFromInt_703) {
    Approx a(1.0);
    Approx& ref = a.scale(10);
    EXPECT_EQ(&a, &ref);
}

TEST(ApproxTest_703, ScaleFromFloat_703) {
    Approx a(1.0);
    Approx& ref = a.scale(1.5f);
    EXPECT_EQ(&a, &ref);
}

TEST(ApproxTest_703, ScaleAffectsComparison_703) {
    // Scaling up should widen the tolerance since epsilon is relative to max(scale, value)
    double val = 1.0;
    double other = 1.0 + 0.05;
    // Without scale this might not match under tight epsilon
    // With a big scale, the tolerance window grows
    EXPECT_TRUE(other == Approx(val).epsilon(0.01).scale(100.0));
}

// ============================================================
// operator() — creates new Approx with same settings
// ============================================================

TEST(ApproxTest_703, CallOperatorCreatesNewApprox_703) {
    Approx base = Approx::custom().epsilon(0.1).margin(0.5);
    Approx derived = base(3.0);
    // The derived Approx should compare to 3.0
    EXPECT_TRUE(3.0 == derived);
}

TEST(ApproxTest_703, CallOperatorPreservesEpsilon_703) {
    Approx base = Approx::custom().epsilon(0.5);
    Approx derived = base(10.0);
    // 10.0 * 0.5 = 5.0 tolerance, so 14.0 should match
    EXPECT_TRUE(14.0 == derived);
}

TEST(ApproxTest_703, CallOperatorPreservesMargin_703) {
    Approx base = Approx::custom().margin(2.0).epsilon(0.0);
    Approx derived = base(5.0);
    EXPECT_TRUE(6.5 == derived);
    EXPECT_FALSE(8.0 == derived);
}

// ============================================================
// toString
// ============================================================

TEST(ApproxTest_703, ToStringContainsApprox_703) {
    Approx a(1.5);
    std::string s = a.toString();
    EXPECT_FALSE(s.empty());
    // The string representation should contain "Approx" or the value
    EXPECT_NE(s.find("Approx"), std::string::npos);
}

TEST(ApproxTest_703, ToStringForZero_703) {
    Approx a(0.0);
    std::string s = a.toString();
    EXPECT_FALSE(s.empty());
}

TEST(ApproxTest_703, ToStringForNegative_703) {
    Approx a(-3.14);
    std::string s = a.toString();
    EXPECT_FALSE(s.empty());
}

// ============================================================
// Boundary / special values
// ============================================================

TEST(ApproxTest_703, VeryLargeValue_703) {
    double big = 1e300;
    EXPECT_TRUE(big == Approx(big));
}

TEST(ApproxTest_703, VerySmallValue_703) {
    double tiny = 1e-300;
    EXPECT_TRUE(tiny == Approx(tiny));
}

TEST(ApproxTest_703, NegativeZero_703) {
    EXPECT_TRUE(-0.0 == Approx(0.0));
    EXPECT_TRUE(0.0 == Approx(-0.0));
}

TEST(ApproxTest_703, ComparisonNearZeroWithMargin_703) {
    // Near zero, relative epsilon is useless; margin is needed
    EXPECT_FALSE(0.001 == Approx(0.0));
    EXPECT_TRUE(0.001 == Approx(0.0).margin(0.01));
}

// ============================================================
// Chaining modifiers
// ============================================================

TEST(ApproxTest_703, ChainingAllModifiers_703) {
    Approx a = Approx(5.0).epsilon(0.1).margin(0.5).scale(2.0);
    EXPECT_TRUE(5.0 == a);
}

TEST(ApproxTest_703, ChainingReturnsSameObject_703) {
    Approx a(1.0);
    Approx* p1 = &a;
    Approx* p2 = &(a.epsilon(0.1));
    Approx* p3 = &(a.margin(0.5));
    Approx* p4 = &(a.scale(2.0));
    EXPECT_EQ(p1, p2);
    EXPECT_EQ(p1, p3);
    EXPECT_EQ(p1, p4);
}
