#include <gtest/gtest.h>
#include <cmath>

// Assuming SplashCoord is a typedef for a numeric type (like float or double)
typedef float SplashCoord;

// Function to be tested (from the given partial code)
static inline SplashCoord splashDist(SplashCoord x0, SplashCoord y0, SplashCoord x1, SplashCoord y1) {
    SplashCoord dx, dy;
    dx = x1 - x0;
    dy = y1 - y0;
    return splashSqrt(dx * dx + dy * dy);
}

// Mock for splashSqrt function (assuming it exists and works similarly to std::sqrt)
static inline SplashCoord splashSqrt(SplashCoord value) {
    return std::sqrt(value);
}

// Unit Test Case
TEST_F(SplashMathTest_1563, splashDist_NormalOperation_1563) {
    SplashCoord x0 = 0.0f;
    SplashCoord y0 = 0.0f;
    SplashCoord x1 = 3.0f;
    SplashCoord y1 = 4.0f;

    // The expected distance is 5 (Pythagorean theorem: sqrt(3^2 + 4^2) = 5)
    SplashCoord result = splashDist(x0, y0, x1, y1);
    
    EXPECT_FLOAT_EQ(result, 5.0f);
}

TEST_F(SplashMathTest_1563, splashDist_ZeroDistance_1563) {
    SplashCoord x0 = 2.0f;
    SplashCoord y0 = 3.0f;
    SplashCoord x1 = 2.0f;
    SplashCoord y1 = 3.0f;

    // The distance between the same point is 0
    SplashCoord result = splashDist(x0, y0, x1, y1);
    
    EXPECT_FLOAT_EQ(result, 0.0f);
}

TEST_F(SplashMathTest_1563, splashDist_NegativeCoordinates_1563) {
    SplashCoord x0 = -1.0f;
    SplashCoord y0 = -1.0f;
    SplashCoord x1 = 1.0f;
    SplashCoord y1 = 1.0f;

    // The expected distance is sqrt((1 - (-1))^2 + (1 - (-1))^2) = sqrt(8) ≈ 2.8284
    SplashCoord result = splashDist(x0, y0, x1, y1);
    
    EXPECT_FLOAT_EQ(result, std::sqrt(8.0f));
}

TEST_F(SplashMathTest_1563, splashDist_LargeCoordinates_1563) {
    SplashCoord x0 = 1000000.0f;
    SplashCoord y0 = 1000000.0f;
    SplashCoord x1 = 1000001.0f;
    SplashCoord y1 = 1000001.0f;

    // The expected distance is sqrt((1000001 - 1000000)^2 + (1000001 - 1000000)^2) = sqrt(2)
    SplashCoord result = splashDist(x0, y0, x1, y1);
    
    EXPECT_FLOAT_EQ(result, std::sqrt(2.0f));
}

TEST_F(SplashMathTest_1563, splashDist_HandlingOverflow_1563) {
    SplashCoord x0 = FLT_MAX;
    SplashCoord y0 = FLT_MAX;
    SplashCoord x1 = FLT_MAX;
    SplashCoord y1 = FLT_MAX;

    // The expected distance is 0, as the points are identical
    SplashCoord result = splashDist(x0, y0, x1, y1);
    
    EXPECT_FLOAT_EQ(result, 0.0f);
}