#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "HtmlFonts.h"



using namespace testing;



class HtmlFontTest : public ::testing::Test {

protected:

    std::unique_ptr<HtmlFont> font;

    GfxFont gfxFont; // Assuming GfxFont is default constructible for this test

    int size = 12;

    GfxRGB rgb{0, 0, 0};

    double opacity = 1.0;



    void SetUp() override {

        font = std::make_unique<HtmlFont>(gfxFont, size, rgb, opacity);

    }

};



TEST_F(HtmlFontTest_2625, SetRotMatUpdatesRotSkewMat_2625) {

    std::array<double, 4> mat = {1.0, 0.0, 0.0, 1.0};

    font->setRotMat(mat);

    EXPECT_EQ(font->getRotMat(), mat);

}



TEST_F(HtmlFontTest_2625, SetRotMatMarksRotOrSkewedTrue_2625) {

    std::array<double, 4> mat = {1.0, 0.0, 0.0, 1.0};

    font->setRotMat(mat);

    EXPECT_TRUE(font->isRotOrSkewed());

}



TEST_F(HtmlFontTest_2625, InitialStateIsNotRotOrSkewed_2625) {

    EXPECT_FALSE(font->isRotOrSkewed());

}



TEST_F(HtmlFontTest_2625, SetLineSizeUpdatesLineSize_2625) {

    int newLineSize = 18;

    font->setLineSize(newLineSize);

    EXPECT_EQ(font->getLineSize(), newLineSize);

}
