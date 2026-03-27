#include <gtest/gtest.h>

#include "TestProjects/poppler/utils/HtmlFonts.h"

#include <memory>



// Mock GfxFont for testing purposes

class MockGfxFont : public GfxFont {

public:

    MOCK_METHOD(void, someMethod, (), (const));

};



TEST_F(HtmlFontTest_2618, GetColor_ReturnsCorrectColor_2618) {

    GfxRGB rgb = {0.5, 0.5, 0.5};

    MockGfxFont mockFont;

    HtmlFont font(mockFont, 12, rgb, 1.0);

    EXPECT_EQ(font.getColor().red, static_cast<int>(rgb.r * 255));

    EXPECT_EQ(font.getColor().green, static_cast<int>(rgb.g * 255));

    EXPECT_EQ(font.getColor().blue, static_cast<int>(rgb.b * 255));

}



TEST_F(HtmlFontTest_2618, GetFullName_ReturnsValidString_2618) {

    GfxRGB rgb = {0.5, 0.5, 0.5};

    MockGfxFont mockFont;

    HtmlFont font(mockFont, 12, rgb, 1.0);

    EXPECT_FALSE(font.getFullName().empty());

}



TEST_F(HtmlFontTest_2618, GetFontName_ReturnsValidString_2618) {

    GfxRGB rgb = {0.5, 0.5, 0.5};

    MockGfxFont mockFont;

    HtmlFont font(mockFont, 12, rgb, 1.0);

    EXPECT_FALSE(font.getFontName().empty());

}



TEST_F(HtmlFontTest_2618, IsEqual_ReturnsTrueForSameFonts_2618) {

    GfxRGB rgb = {0.5, 0.5, 0.5};

    MockGfxFont mockFont;

    HtmlFont font1(mockFont, 12, rgb, 1.0);

    HtmlFont font2(mockFont, 12, rgb, 1.0);

    EXPECT_TRUE(font1.isEqual(font2));

}



TEST_F(HtmlFontTest_2618, IsEqual_ReturnsFalseForDifferentFonts_2618) {

    GfxRGB rgb1 = {0.5, 0.5, 0.5};

    GfxRGB rgb2 = {1.0, 1.0, 1.0};

    MockGfxFont mockFont;

    HtmlFont font1(mockFont, 12, rgb1, 1.0);

    HtmlFont font2(mockFont, 14, rgb2, 1.0);

    EXPECT_FALSE(font1.isEqual(font2));

}



TEST_F(HtmlFontTest_2618, IsEqualIgnoreBold_ReturnsTrueForSameFontsIgnoringBold_2618) {

    GfxRGB rgb = {0.5, 0.5, 0.5};

    MockGfxFont mockFont;

    HtmlFont font1(mockFont, 12, rgb, 1.0);

    HtmlFont font2(mockFont, 14, rgb, 1.0);

    EXPECT_TRUE(font1.isEqualIgnoreBold(font2));

}



TEST_F(HtmlFontTest_2618, IsItalic_ReturnsFalseByDefault_2618) {

    GfxRGB rgb = {0.5, 0.5, 0.5};

    MockGfxFont mockFont;

    HtmlFont font(mockFont, 12, rgb, 1.0);

    EXPECT_FALSE(font.isItalic());

}



TEST_F(HtmlFontTest_2618, IsBold_ReturnsFalseByDefault_2618) {

    GfxRGB rgb = {0.5, 0.5, 0.5};

    MockGfxFont mockFont;

    HtmlFont font(mockFont, 12, rgb, 1.0);

    EXPECT_FALSE(font.isBold());

}



TEST_F(HtmlFontTest_2618, IsRotOrSkewed_ReturnsFalseByDefault_2618) {

    GfxRGB rgb = {0.5, 0.5, 0.5};

    MockGfxFont mockFont;

    HtmlFont font(mockFont, 12, rgb, 1.0);

    EXPECT_FALSE(font.isRotOrSkewed());

}



TEST_F(HtmlFontTest_2618, GetSize_ReturnsCorrectSize_2618) {

    GfxRGB rgb = {0.5, 0.5, 0.5};

    MockGfxFont mockFont;

    HtmlFont font(mockFont, 12, rgb, 1.0);

    EXPECT_EQ(font.getSize(), 12);

}



TEST_F(HtmlFontTest_2618, GetLineSize_ReturnsCorrectLineSize_2618) {

    GfxRGB rgb = {0.5, 0.5, 0.5};

    MockGfxFont mockFont;

    HtmlFont font(mockFont, 12, rgb, 1.0);

    font.setLineSize(14);

    EXPECT_EQ(font.getLineSize(), 14);

}



TEST_F(HtmlFontTest_2618, SetRotMat_SetsCorrectRotationMatrix_2618) {

    GfxRGB rgb = {0.5, 0.5, 0.5};

    MockGfxFont mockFont;

    HtmlFont font(mockFont, 12, rgb, 1.0);

    std::array<double, 4> rotMat = {1.0, 0.0, 0.0, 1.0};

    font.setRotMat(rotMat);

    EXPECT_EQ(font.getRotMat(), rotMat);

}
