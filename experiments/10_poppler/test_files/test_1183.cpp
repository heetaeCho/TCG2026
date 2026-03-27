#include <gtest/gtest.h>

#include "TextOutputDev.h"

#include <memory>



class TextWordTest_1183 : public ::testing::Test {

protected:

    void SetUp() override {

        gfxFont = std::make_shared<GfxFont>();

        fontName = new GooString("TestFont");

        fontInfo = new TextFontInfo(nullptr);

        fontInfo->gfxFont = gfxFont;

        fontInfo->fontName = fontName;



        textWord = new TextWord(nullptr, 0, 12.0);

        charInfo.font = fontInfo;

        textWord->addChar(fontInfo, 0.0, 0.0, 5.0, 5.0, 0, 1, 65, 'A', Matrix());

    }



    void TearDown() override {

        delete textWord;

        delete fontInfo;

        delete fontName;

    }



    std::shared_ptr<GfxFont> gfxFont;

    GooString *fontName;

    TextFontInfo *fontInfo;

    TextWord *textWord;

    TextWord::CharInfo charInfo;

};



TEST_F(TextWordTest_1183, GetFontNameValidIndex_1183) {

    EXPECT_STREQ(textWord->getFontName(0)->getCString(), "TestFont");

}



TEST_F(TextWordTest_1183, GetFontNameInvalidIndex_1183) {

    EXPECT_EQ(textWord->getFontName(1), nullptr);

}



TEST_F(TextWordTest_1183, GetLengthNormal_1183) {

    EXPECT_EQ(textWord->getLength(), 1);

}



TEST_F(TextWordTest_1183, GetCharValidIndex_1183) {

    EXPECT_EQ(*textWord->getChar(0), 'A');

}



TEST_F(TextWordTest_1183, GetCharInvalidIndex_1183) {

    EXPECT_EQ(textWord->getChar(1), nullptr);

}



TEST_F(TextWordTest_1183, GetRotationNormal_1183) {

    EXPECT_EQ(textWord->getRotation(), 0);

}



TEST_F(TextWordTest_1183, HasSpaceAfterNoSpace_1183) {

    EXPECT_FALSE(textWord->hasSpaceAfter());

}



// Assuming addChar or another method sets spaceAfter

// This would require modifying the setup to test this case.

// TEST_F(TextWordTest_1183, HasSpaceAfterWithSpace_1183) {

//     // Modify textWord to have space after

//     EXPECT_TRUE(textWord->hasSpaceAfter());

// }



TEST_F(TextWordTest_1183, GetFontInfoValidIndex_1183) {

    EXPECT_EQ(textWord->getFontInfo(0), fontInfo);

}



TEST_F(TextWordTest_1183, GetFontInfoInvalidIndex_1183) {

    EXPECT_EQ(textWord->getFontInfo(1), nullptr);

}
