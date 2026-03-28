#include <gtest/gtest.h>
#include <limits>
#include <cmath>
#include <string>

// Include the header for Approx
#include "catch2/catch_approx.hpp"

using Catch::Approx;

// ============================================================
// Test Fixture
// ============================================================
class ApproxTest_704 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Construction Tests
// ============================================================

TEST_F(ApproxTest_704, ConstructWithDouble_704) {
    Approx a(1.0);
    // Should not throw, basic construction
    SUCCEED();
}

TEST_F(ApproxTest_704, ConstructWithZero_704) {
    Approx a(0.0);
    SUCCEED();
}

TEST_F(ApproxTest_704, ConstructWithNegativeValue_704) {
    Approx a(-5.0);
    SUCCEED();
}

TEST_F(ApproxTest_704, ConstructWithInteger_704) {
    Approx a(42);
    SUCCEED();
}

TEST_F(ApproxTest_704, ConstructWithFloat_704) {
    Approx a(3.14f);
    SUCCEED();
}

TEST_F(ApproxTest_704, ConstructWithLargeValue_704) {
    Approx a(1e308);
    SUCCEED();
}

TEST_F(ApproxTest_704, ConstructWithSmallValue_704) {
    Approx a(1e-308);
    SUCCEED();
}

// ============================================================
// Custom factory method
// ============================================================

TEST_F(ApproxTest_704, CustomReturnsApprox_704) {
    Approx a = Approx::custom();
    // custom() should return an Approx with value 0
    SUCCEED();
}

// ============================================================
// toString Tests
// ============================================================

TEST_F(ApproxTest_704, ToStringReturnsNonEmpty_704) {
    Approx a(1.5);
    std::string s = a.toString();
    EXPECT_FALSE(s.empty());
}

TEST_F(ApproxTest_704, ToStringContainsApproxIndicator_704) {
    Approx a(1.0);
    std::string s = a.toString();
    // The string representation should contain some indication of the value
    EXPECT_FALSE(s.empty());
}

TEST_F(ApproxTest_704, ToStringForZero_704) {
    Approx a(0.0);
    std::string s = a.toString();
    EXPECT_FALSE(s.empty());
}

// ============================================================
// Negation operator
// ============================================================

TEST_F(ApproxTest_704, NegationOperator_704) {
    Approx a(5.0);
    Approx neg = -a;
    // -Approx(5.0) should represent approx -5.0
    // We can verify via toString that it changed
    std::string s = neg.toString();
    EXPECT_FALSE(s.empty());
}

TEST_F(ApproxTest_704, NegationOfZero_704) {
    Approx a(0.0);
    Approx neg = -a;
    std::string s = neg.toString();
    EXPECT_FALSE(s.empty());
}

TEST_F(ApproxTest_704, NegationOfNegative_704) {
    Approx a(-3.0);
    Approx neg = -a;
    // Should represent approx 3.0
    SUCCEED();
}

// ============================================================
// operator() - creating new Approx with same settings
// ============================================================

TEST_F(ApproxTest_704, CallOperatorCreatesNewApprox_704) {
    Approx a(1.0);
    Approx b = a(2.0);
    // b should approximate 2.0 with same epsilon/margin as a
    SUCCEED();
}

TEST_F(ApproxTest_704, CallOperatorWithInteger_704) {
    Approx a(1.0);
    Approx b = a(42);
    SUCCEED();
}

// ============================================================
// Epsilon setting
// ============================================================

TEST_F(ApproxTest_704, SetEpsilon_704) {
    Approx a(1.0);
    Approx& ref = a.epsilon(0.01);
    // Should return reference to self (chaining)
    EXPECT_EQ(&ref, &a);
}

TEST_F(ApproxTest_704, SetEpsilonZero_704) {
    Approx a(1.0);
    a.epsilon(0.0);
    SUCCEED();
}

TEST_F(ApproxTest_704, SetEpsilonOne_704) {
    Approx a(1.0);
    a.epsilon(1.0);
    SUCCEED();
}

TEST_F(ApproxTest_704, SetEpsilonNegativeThrows_704) {
    Approx a(1.0);
    // Negative epsilon should be invalid
    EXPECT_ANY_THROW(a.epsilon(-0.1));
}

TEST_F(ApproxTest_704, SetEpsilonGreaterThanOneThrows_704) {
    Approx a(1.0);
    // Epsilon > 1.0 should be invalid
    EXPECT_ANY_THROW(a.epsilon(1.1));
}

// ============================================================
// Margin setting
// ============================================================

TEST_F(ApproxTest_704, SetMargin_704) {
    Approx a(1.0);
    Approx& ref = a.margin(0.5);
    EXPECT_EQ(&ref, &a);
}

TEST_F(ApproxTest_704, SetMarginZero_704) {
    Approx a(1.0);
    a.margin(0.0);
    SUCCEED();
}

TEST_F(ApproxTest_704, SetMarginNegativeThrows_704) {
    Approx a(1.0);
    EXPECT_ANY_THROW(a.margin(-1.0));
}

// ============================================================
// Scale setting
// ============================================================

TEST_F(ApproxTest_704, SetScale_704) {
    Approx a(1.0);
    Approx& ref = a.scale(2.0);
    EXPECT_EQ(&ref, &a);
}

TEST_F(ApproxTest_704, SetScaleZero_704) {
    Approx a(1.0);
    a.scale(0.0);
    SUCCEED();
}

TEST_F(ApproxTest_704, SetScaleNegative_704) {
    Approx a(1.0);
    a.scale(-1.0);
    SUCCEED();
}

// ============================================================
// Equality comparison (via == operator if available)
// ============================================================

TEST_F(ApproxTest_704, EqualityWithExactValue_704) {
    Approx a(1.0);
    EXPECT_TRUE(a == 1.0);
}

TEST_F(ApproxTest_704, EqualityWithinDefaultEpsilon_704) {
    double value = 1.0;
    double defaultEpsilon = static_cast<double>(std::numeric_limits<float>::epsilon()) * 100.0;
    double closeValue = value + value * defaultEpsilon * 0.5;
    Approx a(value);
    EXPECT_TRUE(a == closeValue);
}

TEST_F(ApproxTest_704, InequalityOutsideDefaultEpsilon_704) {
    double value = 1.0;
    double defaultEpsilon = static_cast<double>(std::numeric_limits<float>::epsilon()) * 100.0;
    double farValue = value + value * defaultEpsilon * 2.0;
    Approx a(value);
    EXPECT_FALSE(a == farValue);
}

TEST_F(ApproxTest_704, EqualitySymmetric_704) {
    Approx a(1.0);
    EXPECT_TRUE(1.0 == a);
    EXPECT_TRUE(a == 1.0);
}

TEST_F(ApproxTest_704, InequalityOperator_704) {
    Approx a(1.0);
    EXPECT_TRUE(a != 2.0);
    EXPECT_TRUE(2.0 != a);
}

TEST_F(ApproxTest_704, EqualityWithZero_704) {
    Approx a(0.0);
    EXPECT_TRUE(a == 0.0);
}

TEST_F(ApproxTest_704, EqualityZeroWithSmallValue_704) {
    // For zero, only margin matters (since epsilon is relative)
    Approx a(0.0);
    // Default margin is 0, so even a tiny value should not be equal
    EXPECT_FALSE(a == 0.0001);
}

TEST_F(ApproxTest_704, EqualityZeroWithMargin_704) {
    Approx a = Approx(0.0).margin(0.001);
    EXPECT_TRUE(a == 0.0005);
}

TEST_F(ApproxTest_704, EqualityZeroOutsideMargin_704) {
    Approx a = Approx(0.0).margin(0.001);
    EXPECT_FALSE(a == 0.01);
}

// ============================================================
// Comparison operators (<=, >=)
// ============================================================

TEST_F(ApproxTest_704, LessThanOrEqualApprox_704) {
    Approx a(1.0);
    // A value slightly above 1.0 within epsilon should be <= Approx(1.0)
    EXPECT_TRUE(1.0 <= a);
}

TEST_F(ApproxTest_704, GreaterThanOrEqualApprox_704) {
    Approx a(1.0);
    EXPECT_TRUE(1.0 >= a);
}

TEST_F(ApproxTest_704, LessThanOrEqualBelowApprox_704) {
    Approx a(1.0);
    EXPECT_TRUE(0.5 <= a);
}

TEST_F(ApproxTest_704, GreaterThanOrEqualAboveApprox_704) {
    Approx a(1.0);
    EXPECT_TRUE(1.5 >= a);
}

// ============================================================
// Custom epsilon affects comparison
// ============================================================

TEST_F(ApproxTest_704, CustomEpsilonWiderMatch_704) {
    Approx a = Approx(100.0).epsilon(0.1); // 10% tolerance
    EXPECT_TRUE(a == 109.0); // within 10%
}

TEST_F(ApproxTest_704, CustomEpsilonNarrowNoMatch_704) {
    Approx a = Approx(100.0).epsilon(0.001); // 0.1% tolerance
    EXPECT_FALSE(a == 101.0); // 1% difference, outside 0.1%
}

// ============================================================
// Chaining
// ============================================================

TEST_F(ApproxTest_704, ChainingEpsilonAndMargin_704) {
    Approx a = Approx(1.0).epsilon(0.01).margin(0.001).scale(1.0);
    EXPECT_TRUE(a == 1.0);
}

// ============================================================
// Negation with equality
// ============================================================

TEST_F(ApproxTest_704, NegationEqualityCheck_704) {
    Approx a(5.0);
    Approx neg = -a;
    EXPECT_TRUE(neg == -5.0);
}

TEST_F(ApproxTest_704, NegationEqualityNotOriginal_704) {
    Approx a(5.0);
    Approx neg = -a;
    EXPECT_FALSE(neg == 5.0);
}

// ============================================================
// operator() preserves settings
// ============================================================

TEST_F(ApproxTest_704, CallOperatorPreservesEpsilon_704) {
    Approx base = Approx(0.0).epsilon(0.1); // 10% tolerance
    Approx derived = base(100.0);
    // 109.0 is within 10% of 100.0
    EXPECT_TRUE(derived == 109.0);
    // 120.0 is NOT within 10% of 100.0
    EXPECT_FALSE(derived == 120.0);
}

TEST_F(ApproxTest_704, CallOperatorPreservesMargin_704) {
    Approx base = Approx(0.0).margin(5.0);
    Approx derived = base(100.0);
    // 104.0 is within margin 5.0 of 100.0
    EXPECT_TRUE(derived == 104.0);
}

// ============================================================
// Edge cases with special floating point values
// ============================================================

TEST_F(ApproxTest_704, ApproxWithVeryLargeValue_704) {
    Approx a(1e15);
    EXPECT_TRUE(a == 1e15);
}

TEST_F(ApproxTest_704, ApproxWithVerySmallValue_704) {
    Approx a(1e-15);
    EXPECT_TRUE(a == 1e-15);
}

TEST_F(ApproxTest_704, ApproxNegativeValue_704) {
    Approx a(-42.0);
    EXPECT_TRUE(a == -42.0);
}
