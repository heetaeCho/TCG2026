#include <gtest/gtest.h>

#include "HtmlFonts.h"

#include <GfxFont.h>



using namespace testing;



// Mock GfxFont class for dependency injection in tests

class MockGfxFont : public GfxFont {

public:

    MOCK_CONST_METHOD0(getName, const char*());

    MOCK_CONST_METHOD0(isItalic, bool());

    MOCK_CONST_METHOD0(isBold, bool());

};



class HtmlFontTest_2621 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize a GfxFont mock object

        gfxFontMock = std::make_unique<StrictMock<MockGfxFont>>();

        

        // Set up expected calls to the mock if necessary

        EXPECT_CALL(*gfxFontMock, getName()).WillOnce(Return("TestFont"));

        EXPECT_CALL(*gfxFontMock, isItalic()).WillRepeatedly(Return(false));

        EXPECT_CALL(*gfxFontMock, isBold()).WillRepeatedly(Return(false));



        // Create an HtmlFont instance using the mock GfxFont

        htmlFont = std::make_unique<HtmlFont>(*gfxFontMock, 12, GfxRGB{0.5, 0.5, 0.5}, 1.0);

    }



    void TearDown() override {

        // Clean up resources if necessary

        htmlFont.reset();

        gfxFontMock.reset();

    }



    std::unique_ptr<HtmlFont> htmlFont;

    std::unique_ptr<StrictMock<MockGfxFont>> gfxFontMock;

};



// Test normal operation of isRotOrSkewed

TEST_F(HtmlFontTest_2621, IsRotOrSkewedFalse_2621) {

    EXPECT_FALSE(htmlFont->isRotOrSkewed());

}



// Test boundary condition: setting rotation matrix to non-identity

TEST_F(HtmlFontTest_2621, SetRotMatNonIdentity_2621) {

    std::array<double, 4> rotSkewMatrix = {0.7071, -0.7071, 0.7071, 0.7071};

    htmlFont->setRotMat(rotSkewMatrix);

    EXPECT_TRUE(htmlFont->isRotOrSkewed());

}



// Test boundary condition: setting rotation matrix to identity

TEST_F(HtmlFontTest_2621, SetRotMatIdentity_2621) {

    std::array<double, 4> rotSkewMatrix = {1.0, 0.0, 0.0, 1.0};

    htmlFont->setRotMat(rotSkewMatrix);

    EXPECT_FALSE(htmlFont->isRotOrSkewed());

}



// Test getting font size

TEST_F(HtmlFontTest_2621, GetFontSize_2621) {

    EXPECT_EQ(htmlFont->getSize(), 12);

}



// Test setting and getting line size

TEST_F(HtmlFontTest_2621, SetAndGetLineSize_2621) {

    int newLineSize = 14;

    htmlFont->setLineSize(newLineSize);

    EXPECT_EQ(htmlFont->getLineSize(), newLineSize);

}



// Test isItalic and isBold (normal operation)

TEST_F(HtmlFontTest_2621, IsItalicFalse_2621) {

    EXPECT_FALSE(htmlFont->isItalic());

}



TEST_F(HtmlFontTest_2621, IsBoldFalse_2621) {

    EXPECT_FALSE(htmlFont->isBold());

}
