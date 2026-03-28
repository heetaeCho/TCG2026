#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "HtmlFonts.h"



using ::testing::Eq;



class HtmlFontTest : public ::testing::Test {

protected:

    HtmlFont font;

    GfxFont gfxFont; // Assuming GfxFont is default constructible for this test

    int size = 12;

    GfxRGB rgb = {0, 0, 0};

    double opacity = 1.0;



    void SetUp() override {

        font = HtmlFont(gfxFont, size, rgb, opacity);

    }

};



TEST_F(HtmlFontTest_2627, GetFullName_ReturnsValidString_2627) {

    EXPECT_EQ(font.getFullName().empty(), false);

}



TEST_F(HtmlFontTest_2627, GetFontName_ReturnsValidString_2627) {

    EXPECT_EQ(font.getFontName().empty(), false);

}



TEST_F(HtmlFontTest_2627, IsEqual_ReturnsTrueForSameFont_2627) {

    HtmlFont sameFont(gfxFont, size, rgb, opacity);

    EXPECT_TRUE(font.isEqual(sameFont));

}



TEST_F(HtmlFontTest_2627, IsEqualIgnoreBold_ReturnsTrueForSameFontIgnoringBold_2627) {

    HtmlFont sameFont(gfxFont, size, rgb, opacity);

    font.setLineSize(15); // Change a non-bold property

    EXPECT_TRUE(font.isEqualIgnoreBold(sameFont));

}



TEST_F(HtmlFontTest_2627, GetColor_ReturnsValidColor_2627) {

    HtmlFontColor color = font.getColor();

    EXPECT_EQ(color.r, 0);

    EXPECT_EQ(color.g, 0);

    EXPECT_EQ(color.b, 0);

}



TEST_F(HtmlFontTest_2627, IsItalic_ReturnsFalseByDefault_2627) {

    EXPECT_FALSE(font.isItalic());

}



TEST_F(HtmlFontTest_2627, IsBold_ReturnsFalseByDefault_2627) {

    EXPECT_FALSE(font.isBold());

}



TEST_F(HtmlFontTest_2627, IsRotOrSkewed_ReturnsFalseByDefault_2627) {

    EXPECT_FALSE(font.isRotOrSkewed());

}



TEST_F(HtmlFontTest_2627, GetSize_ReturnsCorrectSize_2627) {

    EXPECT_EQ(font.getSize(), size);

}



TEST_F(HtmlFontTest_2627, SetLineSize_ChangesLineSize_2627) {

    int newLineSize = 15;

    font.setLineSize(newLineSize);

    EXPECT_EQ(font.getLineSize(), newLineSize);

}



TEST_F(HtmlFontTest_2627, GetRotMat_ReturnsDefaultMatrix_2627) {

    std::array<double, 4> defaultMatrix = {0.0, 0.0, 0.0, 0.0};

    EXPECT_EQ(font.getRotMat(), defaultMatrix);

}



TEST_F(HtmlFontTest_2627, SetRotMat_ChangesRotationMatrix_2627) {

    std::array<double, 4> newMatrix = {1.0, 2.0, 3.0, 4.0};

    font.setRotMat(newMatrix);

    EXPECT_EQ(font.getRotMat(), newMatrix);

}



TEST_F(HtmlFontTest_2627, Print_DoesNotThrowException_2627) {

    EXPECT_NO_THROW(font.print());

}
