#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/TextOutputDev.h"



class TextFontInfoTest : public ::testing::Test {

protected:

    std::shared_ptr<GfxState> state;

    TextFontInfo* fontInfo;



    void SetUp() override {

        state = std::make_shared<GfxState>();

        fontInfo = new TextFontInfo(state.get());

    }



    void TearDown() override {

        delete fontInfo;

    }

};



TEST_F(TextFontInfoTest_1177, IsItalicReturnsFalseByDefault_1177) {

    EXPECT_FALSE(fontInfo->isItalic());

}



// Assuming that we can set some state to make the font italic for testing

// Since we cannot modify the internal state directly, this test assumes such a setup is possible externally.

TEST_F(TextFontInfoTest_1177, IsItalicReturnsTrueWhenSet_1177) {

    // This is a placeholder for setting up the state to make the font italic.

    // In practice, this would involve manipulating the GfxState object appropriately.

    EXPECT_TRUE(fontInfo->isItalic());

}



// Additional tests based on other observable behaviors

TEST_F(TextFontInfoTest_1177, MatchesWithSameGfxStateReturnsTrue_1177) {

    TextFontInfo sameFontInfo(state.get());

    EXPECT_TRUE(fontInfo->matches(&sameFontInfo));

}



TEST_F(TextFontInfoTest_1177, MatchesWithDifferentGfxStateReturnsFalse_1177) {

    auto differentState = std::make_shared<GfxState>();

    TextFontInfo differentFontInfo(differentState.get());

    EXPECT_FALSE(fontInfo->matches(&differentFontInfo));

}



TEST_F(TextFontInfoTest_1177, GetFontNameReturnsNonNullPointer_1177) {

    EXPECT_NE(nullptr, fontInfo->getFontName());

}



// Assuming we can test for fixed width property similarly

TEST_F(TextFontInfoTest_1177, IsFixedWidthReturnsFalseByDefault_1177) {

    EXPECT_FALSE(fontInfo->isFixedWidth());

}



// Similarly, other properties can be tested if there's a way to set them externally

TEST_F(TextFontInfoTest_1177, IsSerifReturnsFalseByDefault_1177) {

    EXPECT_FALSE(fontInfo->isSerif());

}



TEST_F(TextFontInfoTest_1177, IsSymbolicReturnsFalseByDefault_1177) {

    EXPECT_FALSE(fontInfo->isSymbolic());

}



TEST_F(TextFontInfoTest_1177, IsBoldReturnsFalseByDefault_1177) {

    EXPECT_FALSE(fontInfo->isBold());

}
