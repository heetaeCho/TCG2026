#include <gtest/gtest.h>

#include "HtmlFonts.h"

#include <string>



class HtmlFontColorTest_2616 : public ::testing::Test {

protected:

    HtmlFontColor defaultColor;

    HtmlFontColor customColor;



    HtmlFontColorTest_2616() : 

        defaultColor(),

        customColor(GfxRGB(0.5, 0.5, 0.5), 128) {}

};



TEST_F(HtmlFontColorTest_2616, DefaultConstructorInitializesFullOpacity_2616) {

    EXPECT_DOUBLE_EQ(defaultColor.getOpacity(), 1.0);

}



TEST_F(HtmlFontColorTest_2616, CustomConstructorSetsCorrectOpacity_2616) {

    EXPECT_DOUBLE_EQ(customColor.getOpacity(), 0.5);

}



TEST_F(HtmlFontColorTest_2616, BoundaryConditionZeroOpacity_2616) {

    HtmlFontColor zeroOpacityColor(GfxRGB(0.5, 0.5, 0.5), 0);

    EXPECT_DOUBLE_EQ(zeroOpacityColor.getOpacity(), 0.0);

}



TEST_F(HtmlFontColorTest_2616, BoundaryConditionMaxOpacity_2616) {

    HtmlFontColor maxOpacityColor(GfxRGB(0.5, 0.5, 0.5), 255);

    EXPECT_DOUBLE_EQ(maxOpacityColor.getOpacity(), 1.0);

}



TEST_F(HtmlFontColorTest_2616, IsEqualReturnsTrueForSameColor_2616) {

    HtmlFontColor anotherDefaultColor;

    EXPECT_TRUE(defaultColor.isEqual(anotherDefaultColor));

}



TEST_F(HtmlFontColorTest_2616, IsEqualReturnsFalseForDifferentColors_2616) {

    EXPECT_FALSE(defaultColor.isEqual(customColor));

}
