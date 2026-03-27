#include <gtest/gtest.h>
#include <cmath>

// Include the header file where splashFloor is defined
#include "./TestProjects/poppler/splash/SplashMath.h"

// Mock class to handle dependencies if needed (none in this case)
class SplashMathTest_1557 : public ::testing::Test {
};

// Test case for normal operation with a positive floating-point number
TEST_F(SplashMathTest_1557, splashFloor_PositiveFloat_1557) {
    SplashCoord x = 3.7f;
    int result = splashFloor(x);
    EXPECT_EQ(result, 3);
}

// Test case for normal operation with a negative floating-point number
TEST_F(SplashMathTest_1557, splashFloor_NegativeFloat_1557) {
    SplashCoord x = -3.7f;
    int result = splashFloor(x);
    EXPECT_EQ(result, -4);
}

// Test case for normal operation with a zero value
TEST_F(SplashMathTest_1557, splashFloor_Zero_1557) {
    SplashCoord x = 0.0f;
    int result = splashFloor(x);
    EXPECT_EQ(result, 0);
}

// Test case for normal operation with a positive integer
TEST_F(SplashMathTest_1557, splashFloor_PositiveInt_1557) {
    SplashCoord x = 4.0f;
    int result = splashFloor(x);
    EXPECT_EQ(result, 4);
}

// Test case for normal operation with a negative integer
TEST_F(SplashMathTest_1557, splashFloor_NegativeInt_1557) {
    SplashCoord x = -5.0f;
    int result = splashFloor(x);
    EXPECT_EQ(result, -5);
}

// Test case for boundary condition, when the input is just below a whole number
TEST_F(SplashMathTest_1557, splashFloor_BoundaryBelow_1557) {
    SplashCoord x = 5.999f;
    int result = splashFloor(x);
    EXPECT_EQ(result, 5);
}

// Test case for boundary condition, when the input is just above a whole number
TEST_F(SplashMathTest_1557, splashFloor_BoundaryAbove_1557) {
    SplashCoord x = 6.001f;
    int result = splashFloor(x);
    EXPECT_EQ(result, 6);
}

// Exceptional case with a very large number
TEST_F(SplashMathTest_1557, splashFloor_LargeNumber_1557) {
    SplashCoord x = 1e6f;
    int result = splashFloor(x);
    EXPECT_EQ(result, 1000000);
}

// Exceptional case with a very small number (close to zero)
TEST_F(SplashMathTest_1557, splashFloor_SmallNumber_1557) {
    SplashCoord x = 0.0001f;
    int result = splashFloor(x);
    EXPECT_EQ(result, 0);
}

// Exceptional case with NaN (not a number) input
TEST_F(SplashMathTest_1557, splashFloor_NaN_1557) {
    SplashCoord x = std::nanf("");
    int result = splashFloor(x);
    // Expecting NaN to return 0 as a fallback (you may adapt this as per actual behavior)
    EXPECT_EQ(result, 0);
}