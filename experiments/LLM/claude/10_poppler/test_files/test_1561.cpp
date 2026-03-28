#include <gtest/gtest.h>
#include <cmath>
#include <limits>

// Include the header under test
#include "splash/SplashMath.h"

class SplashSqrtTest_1561 : public ::testing::Test {
protected:
    // Helper to compare floating point values with tolerance
    void expectNear(SplashCoord actual, SplashCoord expected, SplashCoord tolerance = 1e-6) {
        EXPECT_NEAR(actual, expected, tolerance);
    }
};

// Normal operation: square root of a perfect square
TEST_F(SplashSqrtTest_1561, SqrtOfPerfectSquare_1561) {
    SplashCoord result = splashSqrt(4.0);
    expectNear(result, 2.0);
}

// Normal operation: square root of 1
TEST_F(SplashSqrtTest_1561, SqrtOfOne_1561) {
    SplashCoord result = splashSqrt(1.0);
    expectNear(result, 1.0);
}

// Normal operation: square root of 9
TEST_F(SplashSqrtTest_1561, SqrtOfNine_1561) {
    SplashCoord result = splashSqrt(9.0);
    expectNear(result, 3.0);
}

// Normal operation: square root of 16
TEST_F(SplashSqrtTest_1561, SqrtOfSixteen_1561) {
    SplashCoord result = splashSqrt(16.0);
    expectNear(result, 4.0);
}

// Normal operation: square root of 25
TEST_F(SplashSqrtTest_1561, SqrtOfTwentyFive_1561) {
    SplashCoord result = splashSqrt(25.0);
    expectNear(result, 5.0);
}

// Normal operation: square root of non-perfect square
TEST_F(SplashSqrtTest_1561, SqrtOfTwo_1561) {
    SplashCoord result = splashSqrt(2.0);
    expectNear(result, (SplashCoord)1.41421356237, 1e-5);
}

// Normal operation: square root of 3
TEST_F(SplashSqrtTest_1561, SqrtOfThree_1561) {
    SplashCoord result = splashSqrt(3.0);
    expectNear(result, (SplashCoord)1.73205080757, 1e-5);
}

// Normal operation: square root of a fractional number
TEST_F(SplashSqrtTest_1561, SqrtOfFraction_1561) {
    SplashCoord result = splashSqrt(0.25);
    expectNear(result, 0.5);
}

// Normal operation: square root of 0.01
TEST_F(SplashSqrtTest_1561, SqrtOfSmallFraction_1561) {
    SplashCoord result = splashSqrt(0.01);
    expectNear(result, 0.1, 1e-5);
}

// Boundary condition: square root of zero
TEST_F(SplashSqrtTest_1561, SqrtOfZero_1561) {
    SplashCoord result = splashSqrt(0.0);
    EXPECT_EQ(result, 0.0);
}

// Boundary condition: square root of a very small positive number
TEST_F(SplashSqrtTest_1561, SqrtOfVerySmallPositive_1561) {
    SplashCoord input = 1e-10;
    SplashCoord result = splashSqrt(input);
    expectNear(result, (SplashCoord)1e-5, 1e-8);
}

// Boundary condition: square root of a very large number
TEST_F(SplashSqrtTest_1561, SqrtOfLargeNumber_1561) {
    SplashCoord result = splashSqrt(1e10);
    expectNear(result, (SplashCoord)1e5, 1.0);
}

// Normal operation: square root of 100
TEST_F(SplashSqrtTest_1561, SqrtOfHundred_1561) {
    SplashCoord result = splashSqrt(100.0);
    expectNear(result, 10.0);
}

// Normal operation: square root of 10000
TEST_F(SplashSqrtTest_1561, SqrtOfTenThousand_1561) {
    SplashCoord result = splashSqrt(10000.0);
    expectNear(result, 100.0);
}

// Verify that sqrt(x)^2 ≈ x for various values
TEST_F(SplashSqrtTest_1561, SqrtSquaredEqualsOriginal_1561) {
    SplashCoord values[] = {0.5, 1.0, 2.0, 3.0, 7.0, 10.0, 50.0, 123.456};
    for (SplashCoord val : values) {
        SplashCoord root = splashSqrt(val);
        expectNear(root * root, val, 1e-4);
    }
}

// Boundary condition: square root of infinity should be infinity
TEST_F(SplashSqrtTest_1561, SqrtOfInfinity_1561) {
    SplashCoord inf = std::numeric_limits<SplashCoord>::infinity();
    SplashCoord result = splashSqrt(inf);
    EXPECT_TRUE(std::isinf(result));
    EXPECT_GT(result, 0);
}

// Exceptional case: square root of NaN should be NaN
TEST_F(SplashSqrtTest_1561, SqrtOfNaN_1561) {
    SplashCoord nan_val = std::numeric_limits<SplashCoord>::quiet_NaN();
    SplashCoord result = splashSqrt(nan_val);
    EXPECT_TRUE(std::isnan(result));
}

// Exceptional case: square root of negative number should produce NaN
TEST_F(SplashSqrtTest_1561, SqrtOfNegativeNumber_1561) {
    SplashCoord result = splashSqrt(-1.0);
    EXPECT_TRUE(std::isnan(result));
}

// Exceptional case: square root of negative large number should produce NaN
TEST_F(SplashSqrtTest_1561, SqrtOfLargeNegativeNumber_1561) {
    SplashCoord result = splashSqrt(-1000.0);
    EXPECT_TRUE(std::isnan(result));
}

// Normal operation: result is non-negative for non-negative input
TEST_F(SplashSqrtTest_1561, ResultIsNonNegative_1561) {
    SplashCoord values[] = {0.0, 0.001, 0.5, 1.0, 10.0, 1000.0};
    for (SplashCoord val : values) {
        SplashCoord result = splashSqrt(val);
        EXPECT_GE(result, 0.0);
    }
}

// Boundary condition: square root of the smallest positive denormalized number
TEST_F(SplashSqrtTest_1561, SqrtOfDenormMin_1561) {
    SplashCoord denorm_min = std::numeric_limits<SplashCoord>::denorm_min();
    SplashCoord result = splashSqrt(denorm_min);
    EXPECT_GT(result, 0.0);
    EXPECT_FALSE(std::isnan(result));
    EXPECT_FALSE(std::isinf(result));
}

// Boundary condition: square root of max finite value
TEST_F(SplashSqrtTest_1561, SqrtOfMaxFinite_1561) {
    SplashCoord max_val = std::numeric_limits<SplashCoord>::max();
    SplashCoord result = splashSqrt(max_val);
    EXPECT_FALSE(std::isnan(result));
    EXPECT_FALSE(std::isinf(result));
    EXPECT_GT(result, 0.0);
}

// Normal operation: monotonicity - sqrt(a) < sqrt(b) when a < b
TEST_F(SplashSqrtTest_1561, Monotonicity_1561) {
    SplashCoord a = 2.0;
    SplashCoord b = 8.0;
    EXPECT_LT(splashSqrt(a), splashSqrt(b));
}
