#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/SplashOutputDev.h"



class SplashOutputDevTest : public ::testing::Test {

protected:

    SplashColorMode colorMode = splashModeRGB8;

    int bitmapRowPad = 1;

    SplashColor paperColor = {0, 0, 0};

    bool bitmapTopDown = false;

    SplashThinLineMode thinLineMode = splashThinLineDefault;

    bool overprintPreview = false;



    std::unique_ptr<SplashOutputDev> splashOutputDev;



    void SetUp() override {

        splashOutputDev = std::make_unique<SplashOutputDev>(colorMode, bitmapRowPad, paperColor, bitmapTopDown, thinLineMode, overprintPreview);

    }

};



TEST_F(SplashOutputDevTest_1105, UseTilingPatternFill_ReturnsTrue_1105) {

    EXPECT_TRUE(splashOutputDev->useTilingPatternFill());

}



TEST_F(SplashOutputDevTest_1105, UseShadedFills_Type0_ReturnsFalse_1105) {

    EXPECT_FALSE(splashOutputDev->useShadedFills(0));

}



TEST_F(SplashOutputDevTest_1105, UseShadedFills_Type1_ReturnsFalse_1105) {

    EXPECT_FALSE(splashOutputDev->useShadedFills(1));

}



TEST_F(SplashOutputDevTest_1105, UpsideDown_ReturnsFalse_1105) {

    EXPECT_FALSE(splashOutputDev->upsideDown());

}



TEST_F(SplashOutputDevTest_1105, UseDrawChar_ReturnsTrue_1105) {

    EXPECT_TRUE(splashOutputDev->useDrawChar());

}



TEST_F(SplashOutputDevTest_1105, InterpretType3Chars_ReturnsTrue_1105) {

    EXPECT_TRUE(splashOutputDev->interpretType3Chars());

}



TEST_F(SplashOutputDevTest_1105, GetBitmap_ReturnsNonNullPtr_1105) {

    EXPECT_NE(splashOutputDev->getBitmap(), nullptr);

}



TEST_F(SplashOutputDevTest_1105, GetSplash_ReturnsNonNullPtr_1105) {

    EXPECT_NE(splashOutputDev->getSplash(), nullptr);

}



TEST_F(SplashOutputDevTest_1105, GetCurrentFont_Default_ReturnsNullPtr_1105) {

    EXPECT_EQ(splashOutputDev->getCurrentFont(), nullptr);

}



TEST_F(SplashOutputDevTest_1105, SetSkipText_SkipHorizTextTrue_RotatedTextFalse_1105) {

    splashOutputDev->setSkipText(true, false);

    // No observable behavior to test directly, but can be verified if needed

}



TEST_F(SplashOutputDevTest_1105, GetFontAntialias_Default_ReturnsTrue_1105) {

    EXPECT_TRUE(splashOutputDev->getFontAntialias());

}



TEST_F(SplashOutputDevTest_1105, SetFontAntialias_True_1105) {

    splashOutputDev->setFontAntialias(true);

    // No observable behavior to test directly, but can be verified if needed

}



TEST_F(SplashOutputDevTest_1105, SetEnableFreeType_EnableTrue_1105) {

    splashOutputDev->setEnableFreeType(true);

    // No observable behavior to test directly, but can be verified if needed

}
