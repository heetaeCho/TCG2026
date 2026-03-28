#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "HtmlFonts.h"



using namespace testing;



class HtmlFontAccuTest : public ::testing::Test {

protected:

    HtmlFontAccu fontAccu;

};



TEST_F(HtmlFontAccuTest_2628, GetValidIndex_2628) {

    // Arrange

    HtmlFont testFont;

    int index = fontAccu.AddFont(testFont);



    // Act & Assert

    EXPECT_NE(fontAccu.Get(index), nullptr);

}



TEST_F(HtmlFontAccuTest_2628, GetInvalidIndex_OutOfBounds_2628) {

    // Arrange & Act & Assert

    EXPECT_DEATH(fontAccu.Get(-1), "");

    EXPECT_DEATH(fontAccu.Get(1000), "");  // Assuming there are less than 1000 fonts added

}



TEST_F(HtmlFontAccuTest_2628, SizeInitiallyZero_2628) {

    // Arrange & Act & Assert

    EXPECT_EQ(fontAccu.size(), 0);

}



TEST_F(HtmlFontAccuTest_2628, AddFontIncreasesSize_2628) {

    // Arrange

    HtmlFont testFont;



    // Act

    fontAccu.AddFont(testFont);



    // Assert

    EXPECT_EQ(fontAccu.size(), 1);

}



TEST_F(HtmlFontAccuTest_2628, AddMultipleFontsIncreasesSize_2628) {

    // Arrange

    HtmlFont testFont1;

    HtmlFont testFont2;



    // Act

    fontAccu.AddFont(testFont1);

    fontAccu.AddFont(testFont2);



    // Assert

    EXPECT_EQ(fontAccu.size(), 2);

}



TEST_F(HtmlFontAccuTest_2628, CSStyleReturnsNonNullPointer_2628) {

    // Arrange

    HtmlFont testFont;

    int index = fontAccu.AddFont(testFont);



    // Act & Assert

    EXPECT_NE(fontAccu.CSStyle(index, 0).get(), nullptr);

}



TEST_F(HtmlFontAccuTest_2628, CSStyleThrowsForInvalidIndex_2628) {

    // Arrange & Act & Assert

    EXPECT_DEATH(fontAccu.CSStyle(-1, 0), "");

    EXPECT_DEATH(fontAccu.CSStyle(1000, 0), "");  // Assuming there are less than 1000 fonts added

}
