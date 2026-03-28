#include <gtest/gtest.h>
#include <catch2/catch_approx.hpp>

using namespace Catch;

// Test fixture for Approx operator!=
class ApproxNotEqualTest_695 : public ::testing::Test {};

// Normal case: Different values should be not equal
TEST_F(ApproxNotEqualTest_695, DifferentValuesReturnTrue_695) {
    double lhs = 5.0;
    Approx rhs(10.0);

    EXPECT_TRUE(lhs != rhs);
}

// Normal case: Identical values should be equal, so != should return false
TEST_F(ApproxNotEqualTest_695, IdenticalValuesReturnFalse_695) {
    double lhs = 5.0;
    Approx rhs(5.0);

    EXPECT_FALSE(lhs != rhs);
}

// Boundary case: Value within epsilon tolerance should be considered equal
TEST_F(ApproxNotEqualTest_695, WithinEpsilonToleranceReturnFalse_695) {
    double lhs = 1.000001;
    Approx rhs(1.0);
    rhs.epsilon(0.01); // large epsilon tolerance

    EXPECT_FALSE(lhs != rhs);
}

// Boundary case: Value just outside epsilon tolerance should be considered not equal
TEST_F(ApproxNotEqualTest_695, OutsideEpsilonToleranceReturnTrue_695) {
    double lhs = 1.1;
    Approx rhs(1.0);
    rhs.epsilon(0.0001); // very strict epsilon

    EXPECT_TRUE(lhs != rhs);
}

// Boundary case: Testing with integer type for lhs
TEST_F(ApproxNotEqualTest_695, IntegerLhsComparison_695) {
    int lhs = 5;
    Approx rhs(5.0);

    EXPECT_FALSE(lhs != rhs); // should be considered equal
}

// Exceptional observable case: Very large difference should return true
TEST_F(ApproxNotEqualTest_695, LargeDifferenceReturnTrue_695) {
    double lhs = 1e6;
    Approx rhs(1.0);

    EXPECT_TRUE(lhs != rhs);
}
