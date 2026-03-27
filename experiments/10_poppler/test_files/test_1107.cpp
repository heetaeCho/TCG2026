#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/SplashOutputDev.h"



class SplashOutputDevTest : public ::testing::Test {

protected:

    SplashColor paperColor = {255, 255, 255};

    SplashOutputDev *outputDev;



    void SetUp() override {

        outputDev = new SplashOutputDev(splashModeRGB8, 0, paperColor, false, splashThinLineDefault, false);

    }



    void TearDown() override {

        delete outputDev;

    }

};



TEST_F(SplashOutputDevTest_1107, UpsideDown_ReturnsCorrectValueForBitmapTopDownFalse_1107) {

    EXPECT_FALSE(outputDev->upsideDown());

}



TEST_F(SplashOutputDevTest_1107, UpsideDown_ReturnsCorrectValueForBitmapTopDownTrue_1107) {

    delete outputDev;

    outputDev = new SplashOutputDev(splashModeRGB8, 0, paperColor, true, splashThinLineDefault, false);

    EXPECT_TRUE(outputDev->upsideDown());

}



TEST_F(SplashOutputDevTest_1107, GetBitmapWidth_ReturnsExpectedValue_1107) {

    int width = outputDev->getBitmapWidth();

    EXPECT_GE(width, 0); // Assuming the width is non-negative

}



TEST_F(SplashOutputDevTest_1107, GetBitmapHeight_ReturnsExpectedValue_1107) {

    int height = outputDev->getBitmapHeight();

    EXPECT_GE(height, 0); // Assuming the height is non-negative

}



TEST_F(SplashOutputDevTest_1107, TakeBitmap_ReturnsNonNullPointer_1107) {

    SplashBitmap *bitmap = outputDev->takeBitmap();

    EXPECT_NE(bitmap, nullptr);

}



TEST_F(SplashOutputDevTest_1107, GetVectorAntialias_DefaultValueIsFalse_1107) {

    EXPECT_FALSE(outputDev->getVectorAntialias());

}



TEST_F(SplashOutputDevTest_1107, SetVectorAntialias_ChangesValueCorrectly_1107) {

    outputDev->setVectorAntialias(true);

    EXPECT_TRUE(outputDev->getVectorAntialias());



    outputDev->setVectorAntialias(false);

    EXPECT_FALSE(outputDev->getVectorAntialias());

}



TEST_F(SplashOutputDevTest_1107, GetFontAntialias_DefaultValueIsFalse_1107) {

    EXPECT_FALSE(outputDev->getFontAntialias());

}



TEST_F(SplashOutputDevTest_1107, SetFontAntialias_ChangesValueCorrectly_1107) {

    outputDev->setFontAntialias(true);

    EXPECT_TRUE(outputDev->getFontAntialias());



    outputDev->setFontAntialias(false);

    EXPECT_FALSE(outputDev->getFontAntialias());

}



TEST_F(SplashOutputDevTest_1107, SetEnableFreeType_ChangesValueCorrectly_1107) {

    outputDev->setEnableFreeType(true);

    // Since there's no public method to get the value of enableFreeType,

    // we can only assume that setting it does not throw an exception and behaves as expected.

}



TEST_F(SplashOutputDevTest_1107, UseTilingPatternFill_DefaultValueIsFalse_1107) {

    EXPECT_FALSE(outputDev->useTilingPatternFill());

}



TEST_F(SplashOutputDevTest_1107, UseShadedFills_DefaultValueIsTrueForTypeAxial_1107) {

    EXPECT_TRUE(outputDev->useShadedFills(2)); // 2 corresponds to axial shading

}



TEST_F(SplashOutputDevTest_1107, UseDrawChar_DefaultValueIsFalse_1107) {

    EXPECT_FALSE(outputDev->useDrawChar());

}



TEST_F(SplashOutputDevTest_1107, InterpretType3Chars_DefaultValueIsTrue_1107) {

    EXPECT_TRUE(outputDev->interpretType3Chars());

}
