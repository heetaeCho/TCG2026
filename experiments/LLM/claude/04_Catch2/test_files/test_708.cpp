#include <gtest/gtest.h>

// Include the Catch2 Approx header
#include "catch2/catch_approx.hpp"

using Catch::Approx;

// Test basic construction and comparison
TEST(ApproxTest_708, DefaultConstructionFromDouble_708) {
    Approx a(1.0);
    EXPECT_TRUE(a == 1.0);
    EXPECT_FALSE(a == 2.0);
}

TEST(ApproxTest_708, DefaultConstructionFromInt_708) {
    Approx a(42);
    EXPECT_TRUE(a == 42.0);
    EXPECT_FALSE(a == 43.0);
}

TEST(ApproxTest_708, EqualityWithinDefaultEpsilon_708) {
    // Default epsilon is typically std::numeric_limits<float>::epsilon()*100
    Approx a(1.0);
    // Values very close to 1.0 should be approximately equal
    EXPECT_TRUE(a == 1.0);
    EXPECT_TRUE(1.0 == a);
}

TEST(ApproxTest_708, InequalityOutsideEpsilon_708) {
    Approx a(1.0);
    EXPECT_TRUE(a != 2.0);
    EXPECT_TRUE(2.0 != a);
}

TEST(ApproxTest_708, CustomEpsilon_708) {
    Approx a = Approx(1.0).epsilon(0.1);
    // 1.05 is within 10% of 1.0
    EXPECT_TRUE(a == 1.05);
    // 1.2 is outside 10% of 1.0
    EXPECT_FALSE(a == 1.2);
}

TEST(ApproxTest_708, CustomMargin_708) {
    Approx a = Approx(1.0).margin(0.5);
    // 1.3 is within margin of 0.5
    EXPECT_TRUE(a == 1.3);
    // 2.0 is outside margin of 0.5
    EXPECT_FALSE(a == 2.0);
}

TEST(ApproxTest_708, CustomScale_708) {
    Approx a = Approx(1.0).scale(10.0);
    // Scale affects the comparison
    EXPECT_TRUE(a == 1.0);
}

TEST(ApproxTest_708, LessThanOperator_708) {
    Approx a(1.0);
    // 0.5 should be less than approx(1.0)
    EXPECT_TRUE(0.5 < a);
    EXPECT_FALSE(1.0 < a);
    EXPECT_FALSE(2.0 < a);
}

TEST(ApproxTest_708, LessThanOrEqualOperator_708) {
    Approx a(1.0);
    EXPECT_TRUE(0.5 <= a);
    EXPECT_TRUE(1.0 <= a);
    EXPECT_FALSE(2.0 <= a);
}

TEST(ApproxTest_708, GreaterThanOperator_708) {
    Approx a(1.0);
    EXPECT_TRUE(2.0 > a);
    EXPECT_FALSE(1.0 > a);
    EXPECT_FALSE(0.5 > a);
}

TEST(ApproxTest_708, GreaterThanOrEqualOperator_708) {
    Approx a(1.0);
    EXPECT_TRUE(2.0 >= a);
    EXPECT_TRUE(1.0 >= a);
    EXPECT_FALSE(0.5 >= a);
}

TEST(ApproxTest_708, ApproxLessThanValue_708) {
    Approx a(1.0);
    EXPECT_TRUE(a < 2.0);
    EXPECT_FALSE(a < 1.0);
    EXPECT_FALSE(a < 0.5);
}

TEST(ApproxTest_708, ApproxLessThanOrEqualValue_708) {
    Approx a(1.0);
    EXPECT_TRUE(a <= 2.0);
    EXPECT_TRUE(a <= 1.0);
    EXPECT_FALSE(a <= 0.5);
}

TEST(ApproxTest_708, ApproxGreaterThanValue_708) {
    Approx a(1.0);
    EXPECT_TRUE(a > 0.5);
    EXPECT_FALSE(a > 1.0);
    EXPECT_FALSE(a > 2.0);
}

TEST(ApproxTest_708, ApproxGreaterThanOrEqualValue_708) {
    Approx a(1.0);
    EXPECT_TRUE(a >= 0.5);
    EXPECT_TRUE(a >= 1.0);
    EXPECT_FALSE(a >= 2.0);
}

TEST(ApproxTest_708, ZeroValue_708) {
    Approx a(0.0);
    EXPECT_TRUE(a == 0.0);
    EXPECT_FALSE(a == 1.0);
}

TEST(ApproxTest_708, ZeroWithMargin_708) {
    // For zero values, epsilon-based comparison doesn't work well,
    // margin is needed
    Approx a = Approx(0.0).margin(0.001);
    EXPECT_TRUE(a == 0.0005);
    EXPECT_FALSE(a == 0.01);
}

TEST(ApproxTest_708, NegativeValues_708) {
    Approx a(-1.0);
    EXPECT_TRUE(a == -1.0);
    EXPECT_FALSE(a == 1.0);
}

TEST(ApproxTest_708, NegativeWithEpsilon_708) {
    Approx a = Approx(-1.0).epsilon(0.1);
    EXPECT_TRUE(a == -1.05);
    EXPECT_FALSE(a == -1.5);
}

TEST(ApproxTest_708, LargeValues_708) {
    Approx a(1e10);
    EXPECT_TRUE(a == 1e10);
    EXPECT_FALSE(a == 2e10);
}

TEST(ApproxTest_708, SmallValues_708) {
    Approx a = Approx(1e-10).margin(1e-12);
    EXPECT_TRUE(a == 1e-10);
}

TEST(ApproxTest_708, UserDefinedLiteral_708) {
    using namespace Catch::literals;
    auto a = 1_a;
    EXPECT_TRUE(a == 1.0);
    EXPECT_FALSE(a == 2.0);
}

TEST(ApproxTest_708, UserDefinedLiteralZero_708) {
    using namespace Catch::literals;
    auto a = 0_a;
    EXPECT_TRUE(a == 0.0);
}

TEST(ApproxTest_708, UserDefinedLiteralLargeValue_708) {
    using namespace Catch::literals;
    auto a = 1000_a;
    EXPECT_TRUE(a == 1000.0);
    EXPECT_FALSE(a == 2000.0);
}

TEST(ApproxTest_708, ChainedEpsilonAndMargin_708) {
    Approx a = Approx(1.0).epsilon(0.01).margin(0.5);
    EXPECT_TRUE(a == 1.0);
    EXPECT_TRUE(a == 1.4);  // within margin
}

TEST(ApproxTest_708, CopyConstruction_708) {
    Approx a = Approx(1.0).epsilon(0.1);
    Approx b(a);
    EXPECT_TRUE(b == 1.0);
    EXPECT_TRUE(b == 1.05);
}

TEST(ApproxTest_708, SymmetricEquality_708) {
    Approx a(5.0);
    double val = 5.0;
    EXPECT_TRUE(a == val);
    EXPECT_TRUE(val == a);
    EXPECT_FALSE(a != val);
    EXPECT_FALSE(val != a);
}

TEST(ApproxTest_708, EpsilonBoundary_708) {
    // Test right at the boundary of epsilon
    Approx a = Approx(100.0).epsilon(0.01);
    // 1% of 100 = 1.0, so 101.0 should be at the boundary
    EXPECT_TRUE(a == 101.0);
    // Just outside
    EXPECT_FALSE(a == 102.0);
}

TEST(ApproxTest_708, MarginBoundary_708) {
    Approx a = Approx(10.0).margin(1.0);
    EXPECT_TRUE(a == 11.0);  // exactly at margin
    EXPECT_FALSE(a == 11.5); // outside margin (assuming epsilon doesn't cover it)
}

TEST(ApproxTest_708, ToString_708) {
    Approx a(1.0);
    std::string str = a.toString();
    // The string should contain the value
    EXPECT_FALSE(str.empty());
}
