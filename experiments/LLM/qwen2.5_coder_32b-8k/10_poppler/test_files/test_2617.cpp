#include <gtest/gtest.h>

#include "HtmlFonts.h"

#include <gmock/gmock.h>



using namespace testing;



class HtmlFontColorTest : public ::testing::Test {

protected:

    HtmlFontColor defaultColor;

    HtmlFontColor customColor;



    HtmlFontColorTest() 

        : defaultColor(),

          customColor(GfxRGB{100, 200, 50}, 128.0) {}

};



TEST_F(HtmlFontColorTest_2617, DefaultConstructorInitializesToBlackOpaque_2617) {

    EXPECT_EQ(defaultColor.getOpacity(), 255);

}



TEST_F(HtmlFontColorTest_2617, CustomConstructorSetsCorrectValues_2617) {

    EXPECT_DOUBLE_EQ(customColor.getOpacity(), 128.0);

    // Assuming isEqual can be used to verify internal state

    HtmlFontColor expectedColor(GfxRGB{100, 200, 50}, 128.0);

    EXPECT_TRUE(customColor.isEqual(expectedColor));

}



TEST_F(HtmlFontColorTest_2617, IsEqualReturnsTrueForIdenticalColors_2617) {

    HtmlFontColor color1(GfxRGB{255, 0, 0}, 255.0);

    HtmlFontColor color2(GfxRGB{255, 0, 0}, 255.0);

    EXPECT_TRUE(color1.isEqual(color2));

}



TEST_F(HtmlFontColorTest_2617, IsEqualReturnsFalseForDifferentColors_2617) {

    HtmlFontColor color1(GfxRGB{255, 0, 0}, 255.0);

    HtmlFontColor color2(GfxRGB{0, 255, 0}, 255.0);

    EXPECT_FALSE(color1.isEqual(color2));

}



TEST_F(HtmlFontColorTest_2617, IsEqualReturnsFalseForDifferentOpacity_2617) {

    HtmlFontColor color1(GfxRGB{255, 0, 0}, 128.0);

    HtmlFontColor color2(GfxRGB{255, 0, 0}, 255.0);

    EXPECT_FALSE(color1.isEqual(color2));

}



TEST_F(HtmlFontColorTest_2617, GetOpacityReturnsCorrectValue_2617) {

    EXPECT_DOUBLE_EQ(customColor.getOpacity(), 128.0);

}
