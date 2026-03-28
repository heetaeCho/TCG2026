#include <gtest/gtest.h>
#include <cmath>

// Mocking the SplashCoord type to assume it's a float or double, depending on the compile-time flag.
#ifdef USE_FLOAT
using SplashCoord = float;
#else
using SplashCoord = double;
#endif

// Include the partial code here to make it available for the tests
static inline SplashCoord splashSqrt(SplashCoord x) { 
    #if USE_FLOAT 
        return sqrtf(x); 
    #else 
        return sqrt(x); 
    #endif 
}

// Test case for normal operation
TEST_F(SplashMathTest_1561, SqrtPositiveNumber_1561) {
    SplashCoord input = 4.0;
    SplashCoord expected = 2.0;
    SplashCoord result = splashSqrt(input);
    EXPECT_EQ(result, expected) << "Expected sqrt(4.0) to be 2.0.";
}

TEST_F(SplashMathTest_1561, SqrtDecimalNumber_1561) {
    SplashCoord input = 2.25;
    SplashCoord expected = 1.5;
    SplashCoord result = splashSqrt(input);
    EXPECT_EQ(result, expected) << "Expected sqrt(2.25) to be 1.5.";
}

// Test case for boundary conditions
TEST_F(SplashMathTest_1561, SqrtZero_1561) {
    SplashCoord input = 0.0;
    SplashCoord expected = 0.0;
    SplashCoord result = splashSqrt(input);
    EXPECT_EQ(result, expected) << "Expected sqrt(0.0) to be 0.0.";
}

TEST_F(SplashMathTest_1561, SqrtLargeNumber_1561) {
    SplashCoord input = 1e6;  // A large number
    SplashCoord expected = 1000.0;
    SplashCoord result = splashSqrt(input);
    EXPECT_EQ(result, expected) << "Expected sqrt(1e6) to be 1000.0.";
}

// Test case for exceptional or error cases
TEST_F(SplashMathTest_1561, SqrtNegativeNumber_1561) {
    SplashCoord input = -4.0;
    // The behavior of sqrt on negative numbers depends on the implementation
    // Since this is supposed to be a black-box test, we won't check the exact error handling
    // instead we will assert that the result is NaN or some error value.
    SplashCoord result = splashSqrt(input);
    EXPECT_TRUE(std::isnan(result)) << "Expected sqrt(-4.0) to return NaN.";
}

// Test case for verification of external interactions
// Not applicable in this case since splashSqrt doesn't interact with external objects.