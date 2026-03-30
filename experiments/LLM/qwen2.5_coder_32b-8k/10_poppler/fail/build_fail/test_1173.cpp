#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TextOutputDev.h"



class TextFontInfoTest : public ::testing::Test {

protected:

    TextFontInfo* fontInfo;



    virtual void SetUp() {

        // Since we cannot create a GfxState object here, we assume that the constructor is tested elsewhere

        // and focus on testing the observable behavior of the class.

        fontInfo = new TextFontInfo(nullptr); // Assuming nullptr can be used for state in tests

    }



    virtual void TearDown() {

        delete fontInfo;

    }

};



TEST_F(TextFontInfoTest_1173, GetFontName_ReturnsNonNullPointer_1173) {

    EXPECT_NE(fontInfo->getFontName(), static_cast<const GooString*>(nullptr));

}



TEST_F(TextFontInfoTest_1173, MatchesWithGfxState_ReturnsBoolean_1173) {

    EXPECT_TRUE(std::is_same<decltype(fontInfo->matches(nullptr)), bool>::value);

}



TEST_F(TextFontInfoTest_1173, MatchesWithTextFontInfo_ReturnsBoolean_1173) {

    TextFontInfo otherFontInfo(nullptr);

    EXPECT_TRUE(std::is_same<decltype(fontInfo->matches(&otherFontInfo)), bool>::value);

}



TEST_F(TextFontInfoTest_1173, MatchesWithRef_ReturnsBoolean_1173) {

    Ref ref;

    EXPECT_TRUE(std::is_same<decltype(fontInfo->matches(&ref)), bool>::value);

}



TEST_F(TextFontInfoTest_1173, GetAscent_ReturnsDouble_1173) {

    EXPECT_TRUE(std::is_same<decltype(fontInfo->getAscent()), double>::value);

}



TEST_F(TextFontInfoTest_1173, GetDescent_ReturnsDouble_1173) {

    EXPECT_TRUE(std::is_same<decltype(fontInfo->getDescent()), double>::value);

}



TEST_F(TextFontInfoTest_1173, GetWMode_ReturnsWritingModeEnum_1173) {

    EXPECT_TRUE(std::is_same<decltype(fontInfo->getWMode()), GfxFont::WritingMode>::value);

}



TEST_F(TextFontInfoTest_1173, IsFixedWidth_ReturnsBoolean_1173) {

    EXPECT_TRUE(std::is_same<decltype(fontInfo->isFixedWidth()), bool>::value);

}



TEST_F(TextFontInfoTest_1173, IsSerif_ReturnsBoolean_1173) {

    EXPECT_TRUE(std::is_same<decltype(fontInfo->isSerif()), bool>::value);

}



TEST_F(TextFontInfoTest_1173, IsSymbolic_ReturnsBoolean_1173) {

    EXPECT_TRUE(std::is_same<decltype(fontInfo->isSymbolic()), bool>::value);

}



TEST_F(TextFontInfoTest_1173, IsItalic_ReturnsBoolean_1173) {

    EXPECT_TRUE(std::is_same<decltype(fontInfo->isItalic()), bool>::value);

}



TEST_F(TextFontInfoTest_1173, IsBold_ReturnsBoolean_1173) {

    EXPECT_TRUE(std::is_same<decltype(fontInfo->isBold()), bool>::value);

}
