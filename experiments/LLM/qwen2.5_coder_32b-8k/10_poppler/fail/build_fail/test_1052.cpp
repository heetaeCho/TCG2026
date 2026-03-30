#include <gtest/gtest.h>

#include "TestProjects/poppler/splash/SplashPattern.h"



class SplashSolidColorTest : public ::testing::Test {

protected:

    SplashColor sampleColor = {0xff, 0x00, 0x00}; // Example color value for testing

    std::unique_ptr<SplashSolidColor> solidColor;



    void SetUp() override {

        solidColor = std::make_unique<SplashSolidColor>(&sampleColor);

    }

};



TEST_F(SplashSolidColorTest_1052, IsCMYK_ReturnsFalse_1052) {

    EXPECT_FALSE(solidColor->isCMYK());

}



TEST_F(SplashSolidColorTest_1052, GetColor_CopiesColorValue_1052) {

    SplashColor color;

    int x = 0, y = 0;

    solidColor->getColor(x, y, &color);

    EXPECT_EQ(color[0], sampleColor[0]);

    EXPECT_EQ(color[1], sampleColor[1]);

    EXPECT_EQ(color[2], sampleColor[2]);

}



TEST_F(SplashSolidColorTest_1052, Copy_ReturnsNewInstanceWithSameColor_1052) {

    auto copiedPattern = solidColor->copy();

    SplashColor color;

    int x = 0, y = 0;

    copiedPattern->getColor(x, y, &color);

    EXPECT_EQ(color[0], sampleColor[0]);

    EXPECT_EQ(color[1], sampleColor[1]);

    EXPECT_EQ(color[2], sampleColor[2]);

}



TEST_F(SplashSolidColorTest_1052, TestPosition_AlwaysReturnsTrueForAnyPosition_1052) {

    int x = 0, y = 0;

    EXPECT_TRUE(solidColor->testPosition(x, y));

    x = -1, y = -1;

    EXPECT_TRUE(solidColor->testPosition(x, y));

    x = 1000, y = 1000;

    EXPECT_TRUE(solidColor->testPosition(x, y));

}



TEST_F(SplashSolidColorTest_1052, IsStatic_ReturnsTrue_1052) {

    EXPECT_TRUE(solidColor->isStatic());

}
