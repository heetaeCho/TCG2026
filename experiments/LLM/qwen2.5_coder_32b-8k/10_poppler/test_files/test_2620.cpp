#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "HtmlFonts.h"



class HtmlFontTest_2620 : public ::testing::Test {

protected:

    GfxFont gfxFont;

    GfxRGB rgb = {0, 0, 0};

    double opacity = 1.0;

    std::unique_ptr<HtmlFont> htmlFont;



    void SetUp() override {

        htmlFont = std::make_unique<HtmlFont>(gfxFont, 12, rgb, opacity);

    }

};



TEST_F(HtmlFontTest_2620, GetFullName_ReturnsString_2620) {

    EXPECT_EQ(htmlFont->getFullName().empty(), false);

}



TEST_F(HtmlFontTest_2620, GetFontName_ReturnsString_2620) {

    EXPECT_EQ(htmlFont->getFontName().empty(), false);

}



TEST_F(HtmlFontTest_2620, HtmlFilter_ReturnsUniquePtrGooString_2620) {

    Unicode u[] = {'t', 'e', 's', 't'};

    int uLen = 4;

    auto result = HtmlFont::HtmlFilter(u, uLen);

    EXPECT_NE(result.get(), nullptr);

}



TEST_F(HtmlFontTest_2620, IsEqual_ReturnsTrueForSameObject_2620) {

    HtmlFont anotherFont(gfxFont, 12, rgb, opacity);

    EXPECT_TRUE(htmlFont->isEqual(anotherFont));

}



TEST_F(HtmlFontTest_2620, IsEqualIgnoreBold_ReturnsTrueForSameObjectIgnoringBold_2620) {

    HtmlFont anotherFont(gfxFont, 12, rgb, opacity);

    EXPECT_TRUE(htmlFont->isEqualIgnoreBold(anotherFont));

}



TEST_F(HtmlFontTest_2620, GetColor_ReturnsHtmlFontColor_2620) {

    HtmlFontColor color = htmlFont->getColor();

    EXPECT_EQ(color.red, 0);

    EXPECT_EQ(color.green, 0);

    EXPECT_EQ(color.blue, 0);

}



TEST_F(HtmlFontTest_2620, IsItalic_ReturnsFalseByDefault_2620) {

    EXPECT_FALSE(htmlFont->isItalic());

}



TEST_F(HtmlFontTest_2620, IsBold_ReturnsFalseByDefault_2620) {

    EXPECT_FALSE(htmlFont->isBold());

}



TEST_F(HtmlFontTest_2620, IsRotOrSkewed_ReturnsFalseByDefault_2620) {

    EXPECT_FALSE(htmlFont->isRotOrSkewed());

}



TEST_F(HtmlFontTest_2620, GetSize_ReturnsCorrectValue_2620) {

    EXPECT_EQ(htmlFont->getSize(), 12);

}



TEST_F(HtmlFontTest_2620, SetLineSize_ChangesLineSize_2620) {

    htmlFont->setLineSize(14);

    EXPECT_EQ(htmlFont->getLineSize(), 14);

}



TEST_F(HtmlFontTest_2620, GetRotMat_ReturnsDefaultMatrix_2620) {

    std::array<double, 4> defaultMat = {1.0, 0.0, 0.0, 1.0};

    EXPECT_EQ(htmlFont->getRotMat(), defaultMat);

}



TEST_F(HtmlFontTest_2620, SetRotMat_ChangesRotationMatrix_2620) {

    std::array<double, 4> newMat = {0.707, -0.707, 0.707, 0.707};

    htmlFont->setRotMat(newMat);

    EXPECT_EQ(htmlFont->getRotMat(), newMat);

}



TEST_F(HtmlFontTest_2620, Print_DoesNotThrowException_2620) {

    EXPECT_NO_THROW(htmlFont->print());

}
