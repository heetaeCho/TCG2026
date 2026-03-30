#include <gtest/gtest.h>
#include <cmath>  // For fabs and fabsf

// Include the SplashMath.h file for the splashAbs function
#include "./TestProjects/poppler/splash/SplashMath.h"

// Test Fixture
class SplashMathTest_1556 : public ::testing::Test {
};

// Normal operation test for splashAbs with positive float
TEST_F(SplashMathTest_1556, splashAbs_PositiveFloat_1556) {
    SplashCoord x = 5.0f;
    SplashCoord result = splashAbs(x);
    EXPECT_EQ(result, 5.0f);
}

// Normal operation test for splashAbs with negative float
TEST_F(SplashMathTest_1556, splashAbs_NegativeFloat_1556) {
    SplashCoord x = -5.0f;
    SplashCoord result = splashAbs(x);
    EXPECT_EQ(result, 5.0f);
}

// Normal operation test for splashAbs with positive integer
TEST_F(SplashMathTest_1556, splashAbs_PositiveInt_1556) {
    SplashCoord x = 10;
    SplashCoord result = splashAbs(x);
    EXPECT_EQ(result, 10);
}

// Normal operation test for splashAbs with negative integer
TEST_F(SplashMathTest_1556, splashAbs_NegativeInt_1556) {
    SplashCoord x = -10;
    SplashCoord result = splashAbs(x);
    EXPECT_EQ(result, 10);
}

// Boundary test for splashAbs with zero
TEST_F(SplashMathTest_1556, splashAbs_Zero_1556) {
    SplashCoord x = 0;
    SplashCoord result = splashAbs(x);
    EXPECT_EQ(result, 0);
}

// Exceptional case test for splashAbs with a very large float value
TEST_F(SplashMathTest_1556, splashAbs_LargeFloat_1556) {
    SplashCoord x = 1e6f;
    SplashCoord result = splashAbs(x);
    EXPECT_EQ(result, 1e6f);
}

// Exceptional case test for splashAbs with a very small float value
TEST_F(SplashMathTest_1556, splashAbs_SmallFloat_1556) {
    SplashCoord x = 1e-6f;
    SplashCoord result = splashAbs(x);
    EXPECT_EQ(result, 1e-6f);
}