#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "SplashOutputDev.h"



using ::testing::Return;

using ::testing::Eq;



class SplashGouraudPatternTest : public ::testing::Test {

protected:

    GfxGouraudTriangleShading* shading;

    bool bDirectColorTranslation = false;

    SplashGouraudPattern* pattern;



    void SetUp() override {

        shading = new GfxGouraudTriangleShading();

        pattern = new SplashGouraudPattern(bDirectColorTranslation, shading);

    }



    void TearDown() override {

        delete pattern;

        delete shading;

    }

};



TEST_F(SplashGouraudPatternTest_1096, CopyCreatesNewInstance_1096) {

    SplashPattern* copiedPattern = pattern->copy();

    EXPECT_NE(copiedPattern, pattern);

    EXPECT_EQ(typeid(*copiedPattern), typeid(SplashGouraudPattern));

    delete copiedPattern;

}



TEST_F(SplashGouraudPatternTest_1096, IsStaticReturnsFalse_1096) {

    EXPECT_FALSE(pattern->isStatic());

}



TEST_F(SplashGouraudPatternTest_1096, IsCMYKBehaviorUnknown_1096) {

    bool isCMYK = pattern->isCMYK();

    // Since the behavior of this method is unknown, we just test it runs

}



TEST_F(SplashGouraudPatternTest_1096, IsParameterizedReturnsTrue_1096) {

    EXPECT_TRUE(pattern->isParameterized());

}



TEST_F(SplashGouraudPatternTest_1096, GetNTrianglesBehaviorUnknown_1096) {

    int nTriangles = pattern->getNTriangles();

    // Since the behavior of this method is unknown, we just test it runs

}



TEST_F(SplashGouraudPatternTest_1096, TestPositionAlwaysFalse_1096) {

    EXPECT_FALSE(pattern->testPosition(0, 0));

}



TEST_F(SplashGouraudPatternTest_1096, GetColorBehaviorUnknown_1096) {

    SplashColorPtr color = new SplashColor[4];

    bool result = pattern->getColor(0, 0, color);

    // Since the behavior of this method is unknown, we just test it runs

    delete[] color;

}



TEST_F(SplashGouraudPatternTest_1096, GetNonParametrizedTriangleBehaviorUnknown_1096) {

    double x0 = 0, y0 = 0, x1 = 0, y1 = 0, x2 = 0, y2 = 0;

    SplashColorPtr color0 = new SplashColor[4];

    SplashColorPtr color1 = new SplashColor[4];

    SplashColorPtr color2 = new SplashColor[4];

    pattern->getNonParametrizedTriangle(0, splashModeRGB8, &x0, &y0, color0, &x1, &y1, color1, &x2, &y2, color2);

    // Since the behavior of this method is unknown, we just test it runs

    delete[] color0;

    delete[] color1;

    delete[] color2;

}



TEST_F(SplashGouraudPatternTest_1096, GetParameterizedColorBehaviorUnknown_1096) {

    double colorinterp = 0.5;

    SplashColorPtr dest = new SplashColor[4];

    pattern->getParameterizedColor(colorinterp, splashModeRGB8, dest);

    // Since the behavior of this method is unknown, we just test it runs

    delete[] dest;

}



TEST_F(SplashGouraudPatternTest_1096, GetParametrizedTriangleBehaviorUnknown_1096) {

    double x0 = 0, y0 = 0, x1 = 0, y1 = 0, x2 = 0, y2 = 0;

    SplashColorPtr color0 = new SplashColor[4];

    SplashColorPtr color1 = new SplashColor[4];

    SplashColorPtr color2 = new SplashColor[4];

    pattern->getParametrizedTriangle(0, &x0, &y0, color0, &x1, &y1, color1, &x2, &y2, color2);

    // Since the behavior of this method is unknown, we just test it runs

    delete[] color0;

    delete[] color1;

    delete[] color2;

}
