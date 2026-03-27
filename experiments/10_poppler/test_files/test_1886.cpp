#include <gtest/gtest.h>

#include <cmath>



// Assuming srgb_gamma_function is part of a class or namespace that we need to mock or access.

// For this example, let's assume it's a standalone function in a namespace or header file.



namespace {

    double srgb_gamma_function(double x);

}



class SrgbGammaFunctionTest_1886 : public ::testing::Test {

protected:

    // No setup needed for this simple function

};



TEST_F(SrgbGammaFunctionTest_1886, LinearSegmentBelowThreshold_1886) {

    double input = 0.03928 / 12.92321;

    double expected_output = input * 12.92321;

    EXPECT_DOUBLE_EQ(srgb_gamma_function(input), expected_output);

}



TEST_F(SrgbGammaFunctionTest_1886, NonLinearSegmentAboveThreshold_1886) {

    double input = 0.5; // Example value above the threshold

    double expected_output = 1.055 * std::pow(input, 1.0 / 2.4) - 0.055;

    EXPECT_DOUBLE_EQ(srgb_gamma_function(input), expected_output);

}



TEST_F(SrgbGammaFunctionTest_1886, ZeroInput_1886) {

    double input = 0.0;

    double expected_output = 0.0; // Since 0 is below the threshold, it should be multiplied by 12.92321

    EXPECT_DOUBLE_EQ(srgb_gamma_function(input), expected_output);

}



TEST_F(SrgbGammaFunctionTest_1886, MaxDoubleInput_1886) {

    double input = std::numeric_limits<double>::max();

    double expected_output = 1.055 * std::pow(input, 1.0 / 2.4) - 0.055;

    EXPECT_DOUBLE_EQ(srgb_gamma_function(input), expected_output);

}



TEST_F(SrgbGammaFunctionTest_1886, MinDoubleInput_1886) {

    double input = std::numeric_limits<double>::min();

    double expected_output = input * 12.92321; // Since min is below the threshold

    EXPECT_DOUBLE_EQ(srgb_gamma_function(input), expected_output);

}



TEST_F(SrgbGammaFunctionTest_1886, NegativeInput_1886) {

    double input = -0.5; // Example negative value

    double expected_output = input * 12.92321; // Since negative is below the threshold

    EXPECT_DOUBLE_EQ(srgb_gamma_function(input), expected_output);

}
