#include <gtest/gtest.h>
#include <cmath>  // for powf and pow

// Define the SplashCoord type, assuming it is a float for the float version.
typedef float SplashCoord;

// The splashPow function from the partial code
static inline SplashCoord splashPow(SplashCoord x, SplashCoord y) {
#if USE_FLOAT
    return powf(x, y);  // float version
#else
    return pow(x, y);  // double version
#endif
}

// Test suite for the splashPow function
class SplashMathTest_1562 : public ::testing::Test {};

// Test case: Normal operation (float version)
TEST_F(SplashMathTest_1562, splashPow_FloatVersion_1562) {
    // Test splashPow with a few known values for the float version (powf)
    EXPECT_FLOAT_EQ(splashPow(2.0f, 3.0f), 8.0f);  // 2^3 = 8
    EXPECT_FLOAT_EQ(splashPow(5.0f, 0.0f), 1.0f);  // 5^0 = 1
    EXPECT_FLOAT_EQ(splashPow(0.0f, 5.0f), 0.0f);  // 0^5 = 0
    EXPECT_FLOAT_EQ(splashPow(2.0f, -1.0f), 0.5f);  // 2^-1 = 0.5
}

// Test case: Normal operation (double version)
TEST_F(SplashMathTest_1562, splashPow_DoubleVersion_1562) {
    // Assuming the non-float version uses double, test known values for pow
    EXPECT_DOUBLE_EQ(splashPow(2.0, 3.0), 8.0);  // 2^3 = 8
    EXPECT_DOUBLE_EQ(splashPow(5.0, 0.0), 1.0);  // 5^0 = 1
    EXPECT_DOUBLE_EQ(splashPow(0.0, 5.0), 0.0);  // 0^5 = 0
    EXPECT_DOUBLE_EQ(splashPow(2.0, -1.0), 0.5);  // 2^-1 = 0.5
}

// Test case: Boundary condition (testing 0^0)
TEST_F(SplashMathTest_1562, splashPow_ZeroToZero_1562) {
    // Test for 0^0, which can be undefined or treated as 1 in many contexts
    EXPECT_FLOAT_EQ(splashPow(0.0f, 0.0f), 1.0f);
    EXPECT_DOUBLE_EQ(splashPow(0.0, 0.0), 1.0);
}

// Test case: Exceptional case (negative base, non-integer exponent)
TEST_F(SplashMathTest_1562, splashPow_NegativeBase_1562) {
    // Testing negative base with non-integer exponents is undefined for real numbers
    // Ensure it's handled correctly (this test may depend on specific behavior or error handling in the actual implementation)
    EXPECT_TRUE(std::isnan(splashPow(-2.0f, 0.5f)));  // -2^(1/2) is NaN
    EXPECT_TRUE(std::isnan(splashPow(-2.0, 0.5)));  // -2^(1/2) is NaN
}

// Test case: Boundary condition (very large exponent)
TEST_F(SplashMathTest_1562, splashPow_LargeExponent_1562) {
    // Test with large exponents
    EXPECT_FLOAT_EQ(splashPow(2.0f, 1000.0f), std::pow(2.0f, 1000.0f));
    EXPECT_DOUBLE_EQ(splashPow(2.0, 1000.0), std::pow(2.0, 1000.0));
}

// Test case: Boundary condition (very small exponent)
TEST_F(SplashMathTest_1562, splashPow_SmallExponent_1562) {
    // Test with very small exponents (close to zero)
    EXPECT_FLOAT_EQ(splashPow(2.0f, -1000.0f), std::pow(2.0f, -1000.0f));
    EXPECT_DOUBLE_EQ(splashPow(2.0, -1000.0), std::pow(2.0, -1000.0));
}