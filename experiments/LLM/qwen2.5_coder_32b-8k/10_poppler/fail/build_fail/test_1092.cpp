#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/SplashOutputDev.h"



using namespace testing;



class SplashUnivariatePatternTest : public ::testing::Test {

protected:

    GfxState mockState;

    GfxUnivariateShading mockShading;

    SplashColorMode colorMode = splashModeRGB8; // Example mode

    SplashUnivariatePattern pattern{colorMode, &mockState, &mockShading};

};



TEST_F(SplashUnivariatePatternTest_1092, IsStaticReturnsFalse_1092) {

    EXPECT_FALSE(pattern.isStatic());

}



TEST_F(SplashUnivariatePatternTest_1092, GetColorWithValidCoordinates_1092) {

    SplashColor color;

    int x = 0;

    int y = 0;

    bool result = pattern.getColor(x, y, &color);

    // Assuming getColor returns true if coordinates are valid and sets the color

    EXPECT_TRUE(result); 

}



TEST_F(SplashUnivariatePatternTest_1092, TestPositionWithValidCoordinates_1092) {

    int x = 0;

    int y = 0;

    bool result = pattern.testPosition(x, y);

    // Assuming testPosition returns true if coordinates are valid

    EXPECT_TRUE(result); 

}



TEST_F(SplashUnivariatePatternTest_1092, GetParameterWithValidCoordinates_1092) {

    double xs = 0.5;

    double ys = 0.5;

    double t;

    bool result = pattern.getParameter(xs, ys, &t);

    // Assuming getParameter returns true if coordinates are valid and sets the parameter

    EXPECT_TRUE(result); 

}



TEST_F(SplashUnivariatePatternTest_1092, GetShadingReturnsNonNullPointer_1092) {

    GfxUnivariateShading* shading = pattern.getShading();

    EXPECT_NE(shading, nullptr);

}



TEST_F(SplashUnivariatePatternTest_1092, IsCMYKReturnsFalseForRGBMode_1092) {

    bool isCMYK = pattern.isCMYK();

    // Assuming splashModeRGB8 does not correspond to CMYK

    EXPECT_FALSE(isCMYK);

}
