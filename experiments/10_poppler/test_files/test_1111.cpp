#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/SplashOutputDev.h"

#include "TestProjects/poppler/poppler/Splash.h"



class SplashOutputDevTest : public ::testing::Test {

protected:

    SplashColorMode colorMode = splashModeRGB8;

    int bitmapRowPad = 1;

    SplashColor paperColor = {255, 255, 255};

    bool bitmapTopDown = false;

    SplashThinLineMode thinLineMode = splashThinLineDefault;

    bool overprintPreview = false;



    std::unique_ptr<SplashOutputDev> outputDev;



    void SetUp() override {

        outputDev.reset(new SplashOutputDev(colorMode, bitmapRowPad, paperColor, bitmapTopDown, thinLineMode, overprintPreview));

    }

};



TEST_F(SplashOutputDevTest_1111, GetSplash_ReturnsNonNullPointer_1111) {

    EXPECT_NE(outputDev->getSplash(), nullptr);

}



TEST_F(SplashOutputDevTest_1111, GetBitmapWidth_ReturnsPositiveInteger_1111) {

    EXPECT_GT(outputDev->getBitmapWidth(), 0);

}



TEST_F(SplashOutputDevTest_1111, GetBitmapHeight_ReturnsPositiveInteger_1111) {

    EXPECT_GT(outputDev->getBitmapHeight(), 0);

}



TEST_F(SplashOutputDevTest_1111, TakeBitmap_ReturnsNonNullPointer_1111) {

    EXPECT_NE(outputDev->takeBitmap(), nullptr);

}



TEST_F(SplashOutputDevTest_1111, GetVectorAntialias_DefaultValueIsFalse_1111) {

    EXPECT_FALSE(outputDev->getVectorAntialias());

}



TEST_F(SplashOutputDevTest_1111, SetVectorAntialias_ChangesValueCorrectly_1111) {

    outputDev->setVectorAntialias(true);

    EXPECT_TRUE(outputDev->getVectorAntialias());

}



TEST_F(SplashOutputDevTest_1111, GetFontAntialias_DefaultValueIsFalse_1111) {

    EXPECT_FALSE(outputDev->getFontAntialias());

}



TEST_F(SplashOutputDevTest_1111, SetFontAntialias_ChangesValueCorrectly_1111) {

    outputDev->setFontAntialias(true);

    EXPECT_TRUE(outputDev->getFontAntialias());

}



TEST_F(SplashOutputDevTest_1111, UseTilingPatternFill_ReturnsFalseByDefault_1111) {

    EXPECT_FALSE(outputDev->useTilingPatternFill());

}



TEST_F(SplashOutputDevTest_1111, UseShadedFills_DefaultValueIsTrue_1111) {

    EXPECT_TRUE(outputDev->useShadedFills(0));

    EXPECT_TRUE(outputDev->useShadedFills(1));

    EXPECT_TRUE(outputDev->useShadedFills(2));

}



TEST_F(SplashOutputDevTest_1111, UpsideDown_DefaultValueIsFalse_1111) {

    EXPECT_FALSE(outputDev->upsideDown());

}



TEST_F(SplashOutputDevTest_1111, UseDrawChar_DefaultValueIsTrue_1111) {

    EXPECT_TRUE(outputDev->useDrawChar());

}



TEST_F(SplashOutputDevTest_1111, InterpretType3Chars_DefaultValueIsFalse_1111) {

    EXPECT_FALSE(outputDev->interpretType3Chars());

}
