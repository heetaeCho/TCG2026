#include <gtest/gtest.h>
#include <cmath>
#include "splash/SplashMath.h"

class SplashDistTest_1563 : public ::testing::Test {
protected:
};

// Test distance between identical points (should be 0)
TEST_F(SplashDistTest_1563, ZeroDistance_1563) {
    SplashCoord result = splashDist(0.0, 0.0, 0.0, 0.0);
    EXPECT_NEAR(result, 0.0, 1e-6);
}

// Test distance between identical non-origin points
TEST_F(SplashDistTest_1563, ZeroDistanceNonOrigin_1563) {
    SplashCoord result = splashDist(3.0, 4.0, 3.0, 4.0);
    EXPECT_NEAR(result, 0.0, 1e-6);
}

// Test well-known 3-4-5 right triangle
TEST_F(SplashDistTest_1563, ThreeFourFiveTriangle_1563) {
    SplashCoord result = splashDist(0.0, 0.0, 3.0, 4.0);
    EXPECT_NEAR(result, 5.0, 1e-6);
}

// Test horizontal distance only
TEST_F(SplashDistTest_1563, HorizontalDistance_1563) {
    SplashCoord result = splashDist(1.0, 0.0, 5.0, 0.0);
    EXPECT_NEAR(result, 4.0, 1e-6);
}

// Test vertical distance only
TEST_F(SplashDistTest_1563, VerticalDistance_1563) {
    SplashCoord result = splashDist(0.0, 2.0, 0.0, 7.0);
    EXPECT_NEAR(result, 5.0, 1e-6);
}

// Test distance is symmetric (dist(A,B) == dist(B,A))
TEST_F(SplashDistTest_1563, SymmetricDistance_1563) {
    SplashCoord result1 = splashDist(1.0, 2.0, 4.0, 6.0);
    SplashCoord result2 = splashDist(4.0, 6.0, 1.0, 2.0);
    EXPECT_NEAR(result1, result2, 1e-6);
}

// Test with negative coordinates
TEST_F(SplashDistTest_1563, NegativeCoordinates_1563) {
    SplashCoord result = splashDist(-3.0, -4.0, 0.0, 0.0);
    EXPECT_NEAR(result, 5.0, 1e-6);
}

// Test with both points in negative quadrant
TEST_F(SplashDistTest_1563, BothPointsNegative_1563) {
    SplashCoord result = splashDist(-5.0, -5.0, -2.0, -1.0);
    EXPECT_NEAR(result, 5.0, 1e-6);
}

// Test with fractional coordinates
TEST_F(SplashDistTest_1563, FractionalCoordinates_1563) {
    SplashCoord result = splashDist(0.0, 0.0, 1.0, 1.0);
    EXPECT_NEAR(result, std::sqrt(2.0), 1e-6);
}

// Test unit distance along x-axis
TEST_F(SplashDistTest_1563, UnitDistanceX_1563) {
    SplashCoord result = splashDist(0.0, 0.0, 1.0, 0.0);
    EXPECT_NEAR(result, 1.0, 1e-6);
}

// Test unit distance along y-axis
TEST_F(SplashDistTest_1563, UnitDistanceY_1563) {
    SplashCoord result = splashDist(0.0, 0.0, 0.0, 1.0);
    EXPECT_NEAR(result, 1.0, 1e-6);
}

// Test distance is always non-negative
TEST_F(SplashDistTest_1563, DistanceAlwaysNonNegative_1563) {
    SplashCoord result = splashDist(10.0, 10.0, -10.0, -10.0);
    EXPECT_GE(result, 0.0);
}

// Test large coordinates
TEST_F(SplashDistTest_1563, LargeCoordinates_1563) {
    SplashCoord result = splashDist(0.0, 0.0, 3000.0, 4000.0);
    EXPECT_NEAR(result, 5000.0, 1e-3);
}

// Test very small distances
TEST_F(SplashDistTest_1563, VerySmallDistance_1563) {
    SplashCoord result = splashDist(0.0, 0.0, 0.0001, 0.0);
    EXPECT_NEAR(result, 0.0001, 1e-8);
}

// Test 5-12-13 triangle
TEST_F(SplashDistTest_1563, FiveTwelveThirteenTriangle_1563) {
    SplashCoord result = splashDist(0.0, 0.0, 5.0, 12.0);
    EXPECT_NEAR(result, 13.0, 1e-6);
}

// Test with offset origin (non-zero starting point)
TEST_F(SplashDistTest_1563, OffsetOrigin_1563) {
    SplashCoord result = splashDist(10.0, 10.0, 13.0, 14.0);
    EXPECT_NEAR(result, 5.0, 1e-6);
}

// Test diagonal distance in a unit square
TEST_F(SplashDistTest_1563, DiagonalUnitSquare_1563) {
    SplashCoord result = splashDist(0.0, 0.0, 1.0, 1.0);
    EXPECT_NEAR(result, std::sqrt(2.0), 1e-6);
}

// Test negative to positive crossing
TEST_F(SplashDistTest_1563, NegativeToPositive_1563) {
    SplashCoord result = splashDist(-1.0, -1.0, 1.0, 1.0);
    EXPECT_NEAR(result, std::sqrt(8.0), 1e-6);
}
