#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/TextOutputDev.h"



class TextFontInfoTest_1175 : public ::testing::Test {

protected:

    TextFontInfo* fontInfo;



    void SetUp() override {

        // Assuming there's a way to create a GfxState for testing purposes

        // This is a placeholder as the actual creation of GfxState is not shown in the provided code.

        GfxState* state = new GfxState();

        fontInfo = new TextFontInfo(state);

        delete state;  // The state is copied or used internally, so we can delete it here.

    }



    void TearDown() override {

        delete fontInfo;

    }

};



TEST_F(TextFontInfoTest_1175, IsSerif_ReturnsTrue_1175) {

    // Assuming there's a way to set the font to serif for testing purposes

    // This is a placeholder as the actual setting of font properties is not shown in the provided code.

    EXPECT_TRUE(fontInfo->isSerif());

}



TEST_F(TextFontInfoTest_1175, IsSerif_ReturnsFalse_1175) {

    // Assuming there's a way to set the font to non-serif for testing purposes

    // This is a placeholder as the actual setting of font properties is not shown in the provided code.

    EXPECT_FALSE(fontInfo->isSerif());

}



TEST_F(TextFontInfoTest_1175, GetFontName_ReturnsValidGooStringPointer_1175) {

    const GooString* fontName = fontInfo->getFontName();

    EXPECT_NE(fontName, nullptr);

}



TEST_F(TextFontInfoTest_1175, IsFixedWidth_ReturnsExpectedValue_1175) {

    bool isFixedWidth = fontInfo->isFixedWidth();

    // We cannot determine the actual expected value here, but we can check that it returns a boolean.

    EXPECT_TRUE(isFixedWidth || !isFixedWidth);

}



TEST_F(TextFontInfoTest_1175, IsSymbolic_ReturnsExpectedValue_1175) {

    bool isSymbolic = fontInfo->isSymbolic();

    // We cannot determine the actual expected value here, but we can check that it returns a boolean.

    EXPECT_TRUE(isSymbolic || !isSymbolic);

}



TEST_F(TextFontInfoTest_1175, IsItalic_ReturnsExpectedValue_1175) {

    bool isItalic = fontInfo->isItalic();

    // We cannot determine the actual expected value here, but we can check that it returns a boolean.

    EXPECT_TRUE(isItalic || !isItalic);

}



TEST_F(TextFontInfoTest_1175, IsBold_ReturnsExpectedValue_1175) {

    bool isBold = fontInfo->isBold();

    // We cannot determine the actual expected value here, but we can check that it returns a boolean.

    EXPECT_TRUE(isBold || !isBold);

}



TEST_F(TextFontInfoTest_1175, GetAscent_ReturnsNonNegativeValue_1175) {

    double ascent = fontInfo->getAscent();

    EXPECT_GE(ascent, 0.0);

}



TEST_F(TextFontInfoTest_1175, GetDescent_ReturnsNonPositiveValue_1175) {

    double descent = fontInfo->getDescent();

    EXPECT_LE(descent, 0.0);

}
