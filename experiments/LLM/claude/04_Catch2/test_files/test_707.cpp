#include <catch2/catch_approx.hpp>
#include <gtest/gtest.h>
#include <limits>
#include <cmath>

using Catch::Approx;
using namespace Catch::literals;

// Test the user-defined literal
TEST(ApproxLiteralTest_707, UDLCreatesApprox_707) {
    auto a = 1.0_a;
    EXPECT_TRUE(a == 1.0);
}

TEST(ApproxLiteralTest_707, UDLMatchesValue_707) {
    auto a = 3.14_a;
    EXPECT_TRUE(a == 3.14);
}

// Test basic construction
TEST(ApproxTest_707, ConstructFromDouble_707) {
    Approx a(1.0);
    EXPECT_TRUE(a == 1.0);
}

TEST(ApproxTest_707, ConstructFromInt_707) {
    Approx a(5);
    EXPECT_TRUE(a == 5.0);
}

TEST(ApproxTest_707, ConstructFromFloat_707) {
    Approx a(2.5f);
    EXPECT_TRUE(a == 2.5);
}

// Test equality comparison
TEST(ApproxTest_707, EqualityWithExactValue_707) {
    Approx a(100.0);
    EXPECT_TRUE(a == 100.0);
    EXPECT_TRUE(100.0 == a);
}

TEST(ApproxTest_707, InequalityWithDifferentValue_707) {
    Approx a(100.0);
    EXPECT_TRUE(a != 200.0);
    EXPECT_TRUE(200.0 != a);
}

TEST(ApproxTest_707, EqualityWithinDefaultEpsilon_707) {
    // Default epsilon is std::numeric_limits<float>::epsilon()*100
    double val = 100.0;
    double close = val + val * std::numeric_limits<float>::epsilon() * 50;
    EXPECT_TRUE(Approx(val) == close);
}

TEST(ApproxTest_707, InequalityOutsideDefaultEpsilon_707) {
    double val = 100.0;
    double far = val + 1.0;
    EXPECT_TRUE(Approx(val) != far);
}

// Test custom epsilon
TEST(ApproxTest_707, CustomEpsilon_707) {
    Approx a = Approx(100.0).epsilon(0.01);
    EXPECT_TRUE(a == 100.5);
    EXPECT_TRUE(a != 102.0);
}

TEST(ApproxTest_707, VerySmallEpsilon_707) {
    Approx a = Approx(1.0).epsilon(1e-12);
    EXPECT_TRUE(a == 1.0);
    EXPECT_TRUE(a != 1.001);
}

TEST(ApproxTest_707, LargeEpsilon_707) {
    Approx a = Approx(100.0).epsilon(0.5);
    EXPECT_TRUE(a == 149.0);
    EXPECT_TRUE(a != 200.0);
}

// Test custom margin
TEST(ApproxTest_707, CustomMargin_707) {
    Approx a = Approx(0.0).margin(0.5);
    EXPECT_TRUE(a == 0.3);
    EXPECT_TRUE(a != 1.0);
}

TEST(ApproxTest_707, MarginWithZeroValue_707) {
    // When value is 0, epsilon-based comparison fails, margin helps
    Approx a = Approx(0.0).margin(0.001);
    EXPECT_TRUE(a == 0.0005);
    EXPECT_TRUE(a != 0.01);
}

// Test custom scale
TEST(ApproxTest_707, CustomScale_707) {
    Approx a = Approx(0.0).scale(100.0).epsilon(0.01);
    EXPECT_TRUE(a == 0.5);
}

// Test comparison operators
TEST(ApproxTest_707, LessThanOrEqual_707) {
    EXPECT_TRUE(1.0 <= Approx(1.0));
    EXPECT_TRUE(0.5 <= Approx(1.0));
}

TEST(ApproxTest_707, GreaterThanOrEqual_707) {
    EXPECT_TRUE(1.0 >= Approx(1.0));
    EXPECT_TRUE(1.5 >= Approx(1.0));
}

TEST(ApproxTest_707, LessThan_707) {
    EXPECT_FALSE(1.0 < Approx(1.0));  // equal, so not less than
    EXPECT_TRUE(0.5 < Approx(1.0));
}

TEST(ApproxTest_707, GreaterThan_707) {
    EXPECT_FALSE(1.0 > Approx(1.0));  // equal, so not greater than
    EXPECT_TRUE(1.5 > Approx(1.0));
}

// Test with negative values
TEST(ApproxTest_707, NegativeValues_707) {
    Approx a(-5.0);
    EXPECT_TRUE(a == -5.0);
    EXPECT_TRUE(a != -10.0);
}

// Test with zero
TEST(ApproxTest_707, ZeroValue_707) {
    Approx a(0.0);
    EXPECT_TRUE(a == 0.0);
}

// Test with very large values
TEST(ApproxTest_707, LargeValues_707) {
    double large = 1e10;
    Approx a(large);
    EXPECT_TRUE(a == large);
}

// Test with very small values
TEST(ApproxTest_707, SmallValues_707) {
    double small = 1e-10;
    Approx a = Approx(small).margin(1e-12);
    EXPECT_TRUE(a == small);
}

// Test chaining
TEST(ApproxTest_707, ChainingEpsilonAndMargin_707) {
    Approx a = Approx(1.0).epsilon(0.01).margin(0.001);
    EXPECT_TRUE(a == 1.0);
    EXPECT_TRUE(a == 1.005);
}

// Test symmetry of comparisons
TEST(ApproxTest_707, SymmetricEquality_707) {
    Approx a(42.0);
    EXPECT_TRUE(a == 42.0);
    EXPECT_TRUE(42.0 == a);
    EXPECT_FALSE(a != 42.0);
    EXPECT_FALSE(42.0 != a);
}

// Test Approx operator overloads on the class itself
TEST(ApproxTest_707, ApproxLessThanOrEqualOperator_707) {
    Approx a(1.0);
    EXPECT_TRUE(a <= 1.0);
    EXPECT_TRUE(a <= 2.0);
    EXPECT_FALSE(a <= 0.0);
}

TEST(ApproxTest_707, ApproxGreaterThanOrEqualOperator_707) {
    Approx a(1.0);
    EXPECT_TRUE(a >= 1.0);
    EXPECT_TRUE(a >= 0.0);
    EXPECT_FALSE(a >= 2.0);
}

// Test toString (if accessible)
TEST(ApproxTest_707, ToStringReturnsNonEmpty_707) {
    Approx a(3.14);
    std::string s = a.toString();
    EXPECT_FALSE(s.empty());
}

// Boundary: epsilon at 0
TEST(ApproxTest_707, EpsilonZeroRequiresExactMatch_707) {
    Approx a = Approx(1.0).epsilon(0.0).margin(0.0);
    EXPECT_TRUE(a == 1.0);
    EXPECT_TRUE(a != 1.0 + std::numeric_limits<double>::epsilon());
}

// Boundary: margin at 0
TEST(ApproxTest_707, MarginZero_707) {
    Approx a = Approx(0.0).margin(0.0).epsilon(0.0);
    EXPECT_TRUE(a == 0.0);
    EXPECT_TRUE(a != 1e-15);
}
