#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/utils/HtmlFonts.h"



using namespace testing;



class HtmlFontTest : public ::testing::Test {

protected:

    HtmlFont* htmlFont;

    

    virtual void SetUp() {

        // Assuming GfxFont and GfxRGB are default constructible or mockable.

        // Since we don't have access to their implementation, we will just pass dummy values here.

        GfxFont gfxFont;  // Placeholder for actual construction logic

        GfxRGB rgb = {0.0, 0.0, 0.0};  // Black color

        double opacity = 1.0;

        htmlFont = new HtmlFont(gfxFont, 12, rgb, opacity);

    }

    

    virtual void TearDown() {

        delete htmlFont;

    }

};



TEST_F(HtmlFontTest_2624, GetLineSize_DefaultValue_2624) {

    EXPECT_EQ(htmlFont->getLineSize(), 0); // Assuming default value is 0 if not set

}



TEST_F(HtmlFontTest_2624, SetAndGetLineSize_NormalOperation_2624) {

    htmlFont->setLineSize(18);

    EXPECT_EQ(htmlFont->getLineSize(), 18);

}



TEST_F(HtmlFontTest_2624, SetAndGetLineSize_BoundaryCondition_2624) {

    htmlFont->setLineSize(INT_MAX);

    EXPECT_EQ(htmlFont->getLineSize(), INT_MAX);



    htmlFont->setLineSize(INT_MIN);

    EXPECT_EQ(htmlFont->getLineSize(), INT_MIN);

}



TEST_F(HtmlFontTest_2624, SetAndGetLineSize_ZeroValue_2624) {

    htmlFont->setLineSize(0);

    EXPECT_EQ(htmlFont->getLineSize(), 0);

}
