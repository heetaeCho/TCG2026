#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/utils/HtmlFonts.h"



using namespace testing;



class HtmlFontAccuTest : public ::testing::Test {

protected:

    HtmlFontAccu htmlFontAccu;

};



TEST_F(HtmlFontAccuTest_2629, InitialSizeIsZero_2629) {

    EXPECT_EQ(htmlFontAccu.size(), 0);

}



TEST_F(HtmlFontAccuTest_2629, AddFontIncreasesSize_2629) {

    HtmlFont font;

    htmlFontAccu.AddFont(font);

    EXPECT_EQ(htmlFontAccu.size(), 1);

}



TEST_F(HtmlFontAccuTest_2629, GetReturnsCorrectFont_2629) {

    HtmlFont expectedFont;

    htmlFontAccu.AddFont(expectedFont);

    const HtmlFont* retrievedFont = htmlFontAccu.Get(0);

    EXPECT_EQ(retrievedFont, &expectedFont);

}



TEST_F(HtmlFontAccuTest_2629, GetReturnsNullForInvalidIndex_2629) {

    const HtmlFont* font = htmlFontAccu.Get(0);

    EXPECT_EQ(font, nullptr);

}



TEST_F(HtmlFontAccuTest_2629, CSStyleReturnsUniquePtr_2629) {

    HtmlFont font;

    htmlFontAccu.AddFont(font);

    std::unique_ptr<GooString> style = htmlFontAccu.CSStyle(0, 0);

    EXPECT_NE(style.get(), nullptr);

}



TEST_F(HtmlFontAccuTest_2629, CSStyleReturnsNullForInvalidIndex_2629) {

    std::unique_ptr<GooString> style = htmlFontAccu.CSStyle(0, 0);

    EXPECT_EQ(style.get(), nullptr);

}
