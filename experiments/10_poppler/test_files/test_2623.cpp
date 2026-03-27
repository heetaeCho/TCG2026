#include <gtest/gtest.h>

#include "TestProjects/poppler/utils/HtmlFonts.h"



using namespace testing;



class HtmlFontTest : public ::testing::Test {

protected:

    GfxFont mockGfxFont; // Assuming GfxFont is a simple class for mocking

    std::array<double, 4> rotSkewMat = {0.0, 0.0, 0.0, 1.0};

    HtmlFont* font;



    void SetUp() override {

        GfxRGB rgb = {0, 0, 0}; // Default color black

        double opacity = 1.0; // Full opacity

        font = new HtmlFont(mockGfxFont, 12, rgb, opacity);

    }



    void TearDown() override {

        delete font;

    }

};



TEST_F(HtmlFontTest_2623, GetFullName_ReturnsNonEmptyString_2623) {

    EXPECT_FALSE(font->getFullName().empty());

}



TEST_F(HtmlFontTest_2623, GetFontName_ReturnsNonEmptyString_2623) {

    EXPECT_FALSE(font->getFontName().empty());

}



TEST_F(HtmlFontTest_2623, HtmlFilter_ReturnsNonNullPtr_2623) {

    Unicode mockUnicode = 0x0041; // 'A'

    int uLen = 1;

    auto result = HtmlFont::HtmlFilter(&mockUnicode, uLen);

    EXPECT_NE(result.get(), nullptr);

}



TEST_F(HtmlFontTest_2623, IsEqual_ReturnsFalseForDifferentFonts_2623) {

    GfxRGB rgb = {0, 0, 1}; // Different color blue

    HtmlFont differentFont(mockGfxFont, 12, rgb, 1.0);

    EXPECT_FALSE(font->isEqual(differentFont));

}



TEST_F(HtmlFontTest_2623, IsEqualIgnoreBold_ReturnsTrueForSameFontsExceptBold_2623) {

    GfxRGB rgb = {0, 0, 0}; // Same color black

    HtmlFont sameFont(mockGfxFont, 12, rgb, 1.0);

    EXPECT_TRUE(font->isEqualIgnoreBold(sameFont));

}



TEST_F(HtmlFontTest_2623, GetColor_ReturnsConstructedColor_2623) {

    HtmlFontColor color = font->getColor();

    EXPECT_EQ(color.r, 0);

    EXPECT_EQ(color.g, 0);

    EXPECT_EQ(color.b, 0);

}



TEST_F(HtmlFontTest_2623, IsItalic_ReturnsFalseByDefault_2623) {

    EXPECT_FALSE(font->isItalic());

}



TEST_F(HtmlFontTest_2623, IsBold_ReturnsFalseByDefault_2623) {

    EXPECT_FALSE(font->isBold());

}



TEST_F(HtmlFontTest_2623, IsRotOrSkewed_ReturnsFalseByDefault_2623) {

    EXPECT_FALSE(font->isRotOrSkewed());

}



TEST_F(HtmlFontTest_2623, GetSize_ReturnsConstructedSize_2623) {

    EXPECT_EQ(font->getSize(), 12);

}



TEST_F(HtmlFontTest_2623, GetLineSize_ReturnsZeroByDefault_2623) {

    EXPECT_EQ(font->getLineSize(), 0);

}



TEST_F(HtmlFontTest_2623, SetAndGetLineSize_WorkAsExpected_2623) {

    int newLineSize = 14;

    font->setLineSize(newLineSize);

    EXPECT_EQ(font->getLineSize(), newLineSize);

}



TEST_F(HtmlFontTest_2623, SetAndGetRotMat_WorkAsExpected_2623) {

    std::array<double, 4> newRotSkewMat = {1.0, 0.0, 0.0, 0.5};

    font->setRotMat(newRotSkewMat);

    EXPECT_EQ(font->getRotMat(), newRotSkewMat);

}
