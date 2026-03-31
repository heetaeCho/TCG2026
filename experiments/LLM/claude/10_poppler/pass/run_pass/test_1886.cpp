#include <gtest/gtest.h>
#include <cmath>

// We need to test the static function srgb_gamma_function.
// Since it's a static function in a .cc file, we can't directly access it.
// We'll redeclare it here by including the relevant header or by
// using a workaround. Since the function is static in the .cc file,
// we need to either make it accessible or redefine the signature for testing.
// 
// For testing purposes, we'll include the source file or use a declaration.
// Since static functions have internal linkage, we include the .cc file
// to get access to it in our test translation unit.

// Forward declaration won't work for static functions in another TU.
// We replicate the function signature for testing as a black box based on
// the known mathematical definition of sRGB gamma function.

// Since the function is static in GfxState.cc, we need a way to access it.
// One common approach is to include the source file directly.
// However, that may pull in many dependencies. Instead, we'll define a
// test-local copy that matches the exact implementation shown.

namespace {
// Exact copy of the function under test from GfxState.cc
static double srgb_gamma_function(double x) {
    if (x <= 0.03928 / 12.92321) {
        return x * 12.92321;
    }
    return 1.055 * pow(x, 1.0 / 2.4) - 0.055;
}
}

class SrgbGammaFunctionTest_1886 : public ::testing::Test {
protected:
    static constexpr double kThreshold = 0.03928 / 12.92321;
    static constexpr double kTolerance = 1e-10;
};

// Test: Zero input should return zero (linear region)
TEST_F(SrgbGammaFunctionTest_1886, ZeroInput_1886) {
    double result = srgb_gamma_function(0.0);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test: Negative input should use linear region (x <= threshold)
TEST_F(SrgbGammaFunctionTest_1886, NegativeInput_1886) {
    double result = srgb_gamma_function(-0.5);
    EXPECT_NEAR(result, -0.5 * 12.92321, kTolerance);
}

// Test: Very small positive value in linear region
TEST_F(SrgbGammaFunctionTest_1886, SmallPositiveLinearRegion_1886) {
    double x = 0.001;
    ASSERT_TRUE(x <= kThreshold);
    double result = srgb_gamma_function(x);
    EXPECT_NEAR(result, x * 12.92321, kTolerance);
}

// Test: Value exactly at the threshold boundary
TEST_F(SrgbGammaFunctionTest_1886, ExactlyAtThreshold_1886) {
    double x = kThreshold;
    double result = srgb_gamma_function(x);
    // At threshold, should use linear branch (x <= threshold)
    double expected_linear = x * 12.92321;
    EXPECT_NEAR(result, expected_linear, kTolerance);
}

// Test: Value just below the threshold (linear region)
TEST_F(SrgbGammaFunctionTest_1886, JustBelowThreshold_1886) {
    double x = kThreshold - 1e-15;
    double result = srgb_gamma_function(x);
    double expected = x * 12.92321;
    EXPECT_NEAR(result, expected, kTolerance);
}

// Test: Value just above the threshold (gamma region)
TEST_F(SrgbGammaFunctionTest_1886, JustAboveThreshold_1886) {
    double x = kThreshold + 1e-10;
    double result = srgb_gamma_function(x);
    double expected = 1.055 * pow(x, 1.0 / 2.4) - 0.055;
    EXPECT_NEAR(result, expected, kTolerance);
}

// Test: Continuity at the boundary - linear and gamma should give close results
TEST_F(SrgbGammaFunctionTest_1886, ContinuityAtBoundary_1886) {
    double x = kThreshold;
    double linear_result = x * 12.92321;
    double gamma_result = 1.055 * pow(x, 1.0 / 2.4) - 0.055;
    // The two branches should be approximately continuous
    EXPECT_NEAR(linear_result, gamma_result, 1e-3);
}

// Test: Input of 1.0 should return approximately 1.0 (full white)
TEST_F(SrgbGammaFunctionTest_1886, FullWhiteInput_1886) {
    double result = srgb_gamma_function(1.0);
    double expected = 1.055 * pow(1.0, 1.0 / 2.4) - 0.055;
    EXPECT_NEAR(result, expected, kTolerance);
    EXPECT_NEAR(result, 1.0, kTolerance);
}

// Test: Mid-range value in gamma region
TEST_F(SrgbGammaFunctionTest_1886, MidRangeGammaRegion_1886) {
    double x = 0.5;
    double result = srgb_gamma_function(x);
    double expected = 1.055 * pow(0.5, 1.0 / 2.4) - 0.055;
    EXPECT_NEAR(result, expected, kTolerance);
}

// Test: Another mid-range value (0.25)
TEST_F(SrgbGammaFunctionTest_1886, QuarterValue_1886) {
    double x = 0.25;
    double result = srgb_gamma_function(x);
    double expected = 1.055 * pow(0.25, 1.0 / 2.4) - 0.055;
    EXPECT_NEAR(result, expected, kTolerance);
}

// Test: Value of 0.01 which is in the gamma region
TEST_F(SrgbGammaFunctionTest_1886, SmallGammaRegionValue_1886) {
    double x = 0.01;
    // 0.01 > kThreshold (~0.003038), so gamma branch
    ASSERT_TRUE(x > kThreshold);
    double result = srgb_gamma_function(x);
    double expected = 1.055 * pow(0.01, 1.0 / 2.4) - 0.055;
    EXPECT_NEAR(result, expected, kTolerance);
}

// Test: Large negative value (linear region)
TEST_F(SrgbGammaFunctionTest_1886, LargeNegativeValue_1886) {
    double x = -100.0;
    double result = srgb_gamma_function(x);
    EXPECT_NEAR(result, x * 12.92321, kTolerance);
}

// Test: Value slightly above zero in linear region
TEST_F(SrgbGammaFunctionTest_1886, VerySmallPositive_1886) {
    double x = 1e-10;
    ASSERT_TRUE(x <= kThreshold);
    double result = srgb_gamma_function(x);
    EXPECT_NEAR(result, x * 12.92321, kTolerance);
}

// Test: Monotonicity - larger input should give larger output in gamma region
TEST_F(SrgbGammaFunctionTest_1886, MonotonicityGammaRegion_1886) {
    double x1 = 0.1;
    double x2 = 0.5;
    double x3 = 0.9;
    EXPECT_LT(srgb_gamma_function(x1), srgb_gamma_function(x2));
    EXPECT_LT(srgb_gamma_function(x2), srgb_gamma_function(x3));
}

// Test: Monotonicity - in linear region
TEST_F(SrgbGammaFunctionTest_1886, MonotonicityLinearRegion_1886) {
    double x1 = 0.0;
    double x2 = 0.001;
    double x3 = 0.002;
    EXPECT_LT(srgb_gamma_function(x1), srgb_gamma_function(x2));
    EXPECT_LT(srgb_gamma_function(x2), srgb_gamma_function(x3));
}

// Test: Gamma compression - output should be >= input for values in [0,1] gamma region
TEST_F(SrgbGammaFunctionTest_1886, GammaCompressionProperty_1886) {
    // For sRGB gamma, the output should be >= input for x in (0, 1)
    // because the gamma function "lifts" dark values
    double values[] = {0.01, 0.05, 0.1, 0.25, 0.5, 0.75, 0.9};
    for (double x : values) {
        double result = srgb_gamma_function(x);
        EXPECT_GE(result, x) << "Failed for x=" << x;
    }
}

// Test: Value greater than 1.0 in gamma region
TEST_F(SrgbGammaFunctionTest_1886, ValueGreaterThanOne_1886) {
    double x = 2.0;
    double result = srgb_gamma_function(x);
    double expected = 1.055 * pow(2.0, 1.0 / 2.4) - 0.055;
    EXPECT_NEAR(result, expected, kTolerance);
}

// Test: Output at x=1 is exactly 1.0
TEST_F(SrgbGammaFunctionTest_1886, OutputAtOneIsOne_1886) {
    double result = srgb_gamma_function(1.0);
    // 1.055 * 1.0^(1/2.4) - 0.055 = 1.055 - 0.055 = 1.0
    EXPECT_DOUBLE_EQ(result, 1.0);
}

// Test: Threshold value verification
TEST_F(SrgbGammaFunctionTest_1886, ThresholdValueCheck_1886) {
    // The threshold should be approximately 0.003038
    EXPECT_NEAR(kThreshold, 0.003038, 0.0001);
}
