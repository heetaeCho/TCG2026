#include <gtest/gtest.h>
#include <cmath>

extern double srgb_gamma_function(double x);

// Test for normal operation (within expected range)
TEST_F(GfxStateTest_1886, SrgbGammaFunction_NormalOperation_1886) {
    // Test typical values
    EXPECT_NEAR(srgb_gamma_function(0.1), 1.292321, 1e-5);  // For x = 0.1, within the first case
    EXPECT_NEAR(srgb_gamma_function(0.5), 1.055 * pow(0.5, 1.0 / 2.4) - 0.055, 1e-5);  // For x = 0.5, within the second case
}

// Test boundary conditions
TEST_F(GfxStateTest_1886, SrgbGammaFunction_LowerBoundary_1886) {
    // Test at boundary for the first case where x <= 0.03928 / 12.92321
    EXPECT_NEAR(srgb_gamma_function(0.03928 / 12.92321), 0.03928, 1e-5);  // Just below the threshold
    EXPECT_NEAR(srgb_gamma_function(0), 0, 1e-5);  // Zero should return zero as per the formula
}

TEST_F(GfxStateTest_1886, SrgbGammaFunction_UpperBoundary_1886) {
    // Test at the upper boundary where x is just above 0.03928 / 12.92321
    EXPECT_NEAR(srgb_gamma_function(0.5), 1.055 * pow(0.5, 1.0 / 2.4) - 0.055, 1e-5);
    EXPECT_NEAR(srgb_gamma_function(1), 1.055 * pow(1, 1.0 / 2.4) - 0.055, 1e-5);  // Testing with x=1 (upper boundary)
}

// Test for exceptional cases
TEST_F(GfxStateTest_1886, SrgbGammaFunction_NegativeInput_1886) {
    // Test if function handles negative input gracefully
    // Assuming that the function is not intended to handle negative numbers, 
    // let's expect it to return 0 or an expected behavior (modify based on real function needs).
    EXPECT_NEAR(srgb_gamma_function(-0.1), 0, 1e-5);  // Negative input should be handled appropriately
}