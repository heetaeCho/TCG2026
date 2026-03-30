#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "HtmlFonts.h"



using namespace testing;



class HtmlFontTest_2622 : public ::testing::Test {

protected:

    GfxFont gfxFont; // Assuming GfxFont is default-constructible for this test setup

    HtmlFontColor color;

    HtmlFont font{gfxFont, 12, GfxRGB(), 1.0};



    void SetUp() override {

        color = HtmlFontColor(); // Assuming HtmlFontColor is default-constructible for this test setup

        font = HtmlFont(gfxFont, 12, GfxRGB(), 1.0);

    }

};



TEST_F(HtmlFontTest_2622, GetSize_ReturnsCorrectValue_2622) {

    EXPECT_EQ(font.getSize(), 12);

}



TEST_F(HtmlFontTest_2622, SetLineSize_ChangesLineSize_2622) {

    font.setLineSize(14);

    EXPECT_EQ(font.getLineSize(), 14);

}



TEST_F(HtmlFontTest_2622, IsRotOrSkewed_ReturnsFalseByDefault_2622) {

    EXPECT_FALSE(font.isRotOrSkewed());

}



TEST_F(HtmlFontTest_2622, SetRotMat_ChangesRotationMatrix_2622) {

    std::array<double, 4> rotationMatrix = {1.0, 0.0, 0.0, 1.0};

    font.setRotMat(rotationMatrix);

    EXPECT_EQ(font.getRotMat(), rotationMatrix);

}



TEST_F(HtmlFontTest_2622, IsEqual_ReturnsTrueForSameObject_2622) {

    HtmlFont sameFont(gfxFont, 12, GfxRGB(), 1.0);

    EXPECT_TRUE(font.isEqual(sameFont));

}



TEST_F(HtmlFontTest_2622, IsEqualIgnoreBold_ReturnsTrueForSameObjectIgnoringBold_2622) {

    HtmlFont sameFont(gfxFont, 12, GfxRGB(), 1.0);

    EXPECT_TRUE(font.isEqualIgnoreBold(sameFont));

}



// Boundary condition tests

TEST_F(HtmlFontTest_2622, GetSize_ReturnsZeroForNegativeInputInConstructor_2622) {

    HtmlFont fontWithNegativeSize(gfxFont, -5, GfxRGB(), 1.0);

    EXPECT_EQ(fontWithNegativeSize.getSize(), 0);

}



// Assuming there are no exceptional or error cases directly observable through the interface
