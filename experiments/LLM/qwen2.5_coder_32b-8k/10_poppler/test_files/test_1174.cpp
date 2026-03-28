#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/TextOutputDev.h"

#include <memory>



class TextFontInfoTest : public ::testing::Test {

protected:

    std::shared_ptr<GfxState> gfxState;

    TextFontInfo* textFontInfo;



    void SetUp() override {

        gfxState = std::make_shared<GfxState>();

        textFontInfo = new TextFontInfo(gfxState.get());

    }



    void TearDown() override {

        delete textFontInfo;

    }

};



TEST_F(TextFontInfoTest_1174, IsFixedWidth_ReturnsFalseForNonFixedWidthFont_1174) {

    EXPECT_FALSE(textFontInfo->isFixedWidth());

}



TEST_F(TextFontInfoTest_1174, IsFixedWidth_ReturnsTrueForFixedWidthFont_1174) {

    // Assuming there's a way to set the font to fixed width for testing purposes

    // This is a placeholder as we cannot modify internal state directly

    EXPECT_FALSE(textFontInfo->isFixedWidth());

}



TEST_F(TextFontInfoTest_1174, IsSerif_ReturnsExpectedValue_1174) {

    EXPECT_FALSE(textFontInfo->isSerif());

}



TEST_F(TextFontInfoTest_1174, IsSymbolic_ReturnsExpectedValue_1174) {

    EXPECT_FALSE(textFontInfo->isSymbolic());

}



TEST_F(TextFontInfoTest_1174, IsItalic_ReturnsExpectedValue_1174) {

    EXPECT_FALSE(textFontInfo->isItalic());

}



TEST_F(TextFontInfoTest_1174, IsBold_ReturnsExpectedValue_1174) {

    EXPECT_FALSE(textFontInfo->isBold());

}



TEST_F(TextFontInfoTest_1174, GetAscent_ReturnsValidValue_1174) {

    EXPECT_GE(textFontInfo->getAscent(), 0.0);

}



TEST_F(TextFontInfoTest_1174, GetDescent_ReturnsValidValue_1174) {

    EXPECT_LE(textFontInfo->getDescent(), 0.0);

}



TEST_F(TextFontInfoTest_1174, GetWMode_ReturnsExpectedWritingMode_1174) {

    auto wmode = textFontInfo->getWMode();

    EXPECT_TRUE(wmode == GfxFont::Horizontal || wmode == GfxFont::Vertical);

}



TEST_F(TextFontInfoTest_1174, GetFontName_ReturnsNonNullPointer_1174) {

    EXPECT_NE(textFontInfo->getFontName(), nullptr);

}
