#include <gtest/gtest.h>
#include "catch2/catch_approx.hpp"
#include <limits>
#include <cmath>

using Catch::Approx;

// ============================================================
// Construction Tests
// ============================================================

TEST(ApproxTest_701, ConstructFromDouble_701) {
    Approx a(1.0);
    // Should not throw; basic construction
    EXPECT_EQ(a.toString().empty(), false);
}

TEST(ApproxTest_701, ConstructFromInt_701) {
    Approx a(42);
    // Template constructor should accept int (convertible to double)
    EXPECT_EQ(a.toString().empty(), false);
}

TEST(ApproxTest_701, ConstructFromFloat_701) {
    Approx a(3.14f);
    EXPECT_EQ(a.toString().empty(), false);
}

TEST(ApproxTest_701, ConstructFromZero_701) {
    Approx a(0.0);
    EXPECT_EQ(a.toString().empty(), false);
}

TEST(ApproxTest_701, ConstructFromNegative_701) {
    Approx a(-5.5);
    EXPECT_EQ(a.toString().empty(), false);
}

// ============================================================
// Equality Comparison Tests (operator== and operator!=)
// ============================================================

TEST(ApproxTest_701, ExactEqualityMatch_701) {
    EXPECT_TRUE(1.0 == Approx(1.0));
}

TEST(ApproxTest_701, CloseValuesWithinDefaultEpsilon_701) {
    double val = 1.0;
    double close = 1.0 + std::numeric_limits<float>::epsilon();
    EXPECT_TRUE(close == Approx(val));
}

TEST(ApproxTest_701, ValuesNotEqual_701) {
    EXPECT_FALSE(1.0 == Approx(2.0));
}

TEST(ApproxTest_701, NotEqualOperator_701) {
    EXPECT_TRUE(1.0 != Approx(2.0));
}

TEST(ApproxTest_701, NotEqualOperatorFalseForSameValue_701) {
    EXPECT_FALSE(1.0 != Approx(1.0));
}

TEST(ApproxTest_701, ZeroEqualsZero_701) {
    EXPECT_TRUE(0.0 == Approx(0.0));
}

// ============================================================
// Epsilon Tests
// ============================================================

TEST(ApproxTest_701, EpsilonChangesComparison_701) {
    // With a large epsilon, values far apart should be considered equal
    EXPECT_TRUE(1.0 == Approx(1.1).epsilon(0.2));
}

TEST(ApproxTest_701, EpsilonTooSmallForDifference_701) {
    EXPECT_FALSE(1.0 == Approx(1.1).epsilon(0.01));
}

TEST(ApproxTest_701, EpsilonReturnsSelf_701) {
    Approx a(1.0);
    Approx& ref = a.epsilon(0.1);
    EXPECT_EQ(&ref, &a);
}

TEST(ApproxTest_701, EpsilonWithIntValue_701) {
    // epsilon(0) should be valid - very tight epsilon
    Approx a(1.0);
    a.epsilon(0);
    EXPECT_TRUE(1.0 == a);
}

// ============================================================
// Margin Tests
// ============================================================

TEST(ApproxTest_701, MarginAllowsAbsoluteDifference_701) {
    EXPECT_TRUE(1.0 == Approx(1.5).margin(0.5));
}

TEST(ApproxTest_701, MarginTooSmall_701) {
    EXPECT_FALSE(1.0 == Approx(2.0).margin(0.5));
}

TEST(ApproxTest_701, MarginReturnsSelf_701) {
    Approx a(1.0);
    Approx& ref = a.margin(0.5);
    EXPECT_EQ(&ref, &a);
}

TEST(ApproxTest_701, ZeroWithMargin_701) {
    // Zero compared with margin should work for absolute comparison
    EXPECT_TRUE(0.05 == Approx(0.0).margin(0.1));
}

TEST(ApproxTest_701, ZeroWithMarginTooSmall_701) {
    EXPECT_FALSE(0.5 == Approx(0.0).margin(0.1));
}

// ============================================================
// Scale Tests
// ============================================================

TEST(ApproxTest_701, ScaleReturnsSelf_701) {
    Approx a(1.0);
    Approx& ref = a.scale(2.0);
    EXPECT_EQ(&ref, &a);
}

TEST(ApproxTest_701, ScaleAffectsComparison_701) {
    // With a large scale, the epsilon-based tolerance should increase
    Approx a(1.0);
    a.scale(100.0).epsilon(0.1);
    // The tolerance should be roughly scale * epsilon = 10
    EXPECT_TRUE(5.0 == a);
}

// ============================================================
// Negation Tests
// ============================================================

TEST(ApproxTest_701, NegationOperator_701) {
    Approx a(5.0);
    Approx neg = -a;
    EXPECT_TRUE(-5.0 == neg);
}

TEST(ApproxTest_701, NegationOfZero_701) {
    Approx a(0.0);
    Approx neg = -a;
    EXPECT_TRUE(0.0 == neg);
}

TEST(ApproxTest_701, NegationOfNegative_701) {
    Approx a(-3.0);
    Approx neg = -a;
    EXPECT_TRUE(3.0 == neg);
}

// ============================================================
// Call Operator Tests
// ============================================================

TEST(ApproxTest_701, CallOperatorCreatesNewApprox_701) {
    Approx base = Approx(0.0).epsilon(0.01).margin(0.5);
    Approx derived = base(5.0);
    EXPECT_TRUE(5.0 == derived);
}

TEST(ApproxTest_701, CallOperatorWithInt_701) {
    Approx base = Approx(0.0).epsilon(0.1);
    Approx derived = base(42);
    EXPECT_TRUE(42.0 == derived);
}

// ============================================================
// Custom Factory Tests
// ============================================================

TEST(ApproxTest_701, CustomFactory_701) {
    Approx a = Approx::custom();
    // custom() should return an Approx with value 0
    EXPECT_TRUE(0.0 == a);
}

// ============================================================
// toString Tests
// ============================================================

TEST(ApproxTest_701, ToStringNotEmpty_701) {
    Approx a(3.14);
    std::string str = a.toString();
    EXPECT_FALSE(str.empty());
}

TEST(ApproxTest_701, ToStringContainsApprox_701) {
    Approx a(1.0);
    std::string str = a.toString();
    // The string representation should contain "Approx" or the value
    // We just check it's not empty and has some content
    EXPECT_GT(str.size(), 0u);
}

// ============================================================
// Relational Operator Tests (<=, >=, <, >)
// ============================================================

TEST(ApproxTest_701, LessThanOrEqualWhenEqual_701) {
    EXPECT_TRUE(1.0 <= Approx(1.0));
}

TEST(ApproxTest_701, LessThanOrEqualWhenLess_701) {
    EXPECT_TRUE(0.5 <= Approx(1.0));
}

TEST(ApproxTest_701, LessThanOrEqualWhenGreaterButWithinTolerance_701) {
    // If value is slightly greater but within epsilon, <= should still hold
    double val = 1.0 + std::numeric_limits<float>::epsilon() * 50;
    EXPECT_TRUE(val <= Approx(1.0));
}

TEST(ApproxTest_701, GreaterThanOrEqualWhenEqual_701) {
    EXPECT_TRUE(1.0 >= Approx(1.0));
}

TEST(ApproxTest_701, GreaterThanOrEqualWhenGreater_701) {
    EXPECT_TRUE(2.0 >= Approx(1.0));
}

TEST(ApproxTest_701, LessThanWhenClearlyLess_701) {
    EXPECT_TRUE(0.5 < Approx(2.0));
}

TEST(ApproxTest_701, GreaterThanWhenClearlyGreater_701) {
    EXPECT_TRUE(3.0 > Approx(1.0));
}

// ============================================================
// Boundary / Edge Cases
// ============================================================

TEST(ApproxTest_701, VeryLargeValues_701) {
    double large = 1e15;
    EXPECT_TRUE(large == Approx(large));
}

TEST(ApproxTest_701, VerySmallValues_701) {
    double small = 1e-15;
    EXPECT_TRUE(small == Approx(small));
}

TEST(ApproxTest_701, NegativeValuesEquality_701) {
    EXPECT_TRUE(-42.5 == Approx(-42.5));
}

TEST(ApproxTest_701, NegativeValuesInequality_701) {
    EXPECT_FALSE(-1.0 == Approx(-2.0));
}

TEST(ApproxTest_701, ChainingEpsilonAndMargin_701) {
    Approx a = Approx(1.0).epsilon(0.01).margin(0.5);
    EXPECT_TRUE(1.4 == a);
}

TEST(ApproxTest_701, ChainingAllSetters_701) {
    Approx a = Approx(10.0).epsilon(0.1).margin(1.0).scale(1.0);
    EXPECT_TRUE(10.5 == a);
}

// ============================================================
// Symmetric Comparison Tests
// ============================================================

TEST(ApproxTest_701, SymmetricEqualityLHS_701) {
    EXPECT_TRUE(Approx(1.0) == 1.0);
}

TEST(ApproxTest_701, SymmetricEqualityRHS_701) {
    EXPECT_TRUE(1.0 == Approx(1.0));
}

TEST(ApproxTest_701, SymmetricInequalityLHS_701) {
    EXPECT_TRUE(Approx(1.0) != 2.0);
}

TEST(ApproxTest_701, SymmetricInequalityRHS_701) {
    EXPECT_TRUE(2.0 != Approx(1.0));
}
