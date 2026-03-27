#include <gtest/gtest.h>

#include "GfxFont.h"

#include <memory>

#include <string>



class GfxFontTest : public ::testing::Test {

protected:

    std::unique_ptr<GfxFont> font;



    void SetUp() override {

        // Assuming a mock or test implementation of GfxFont is available

        font = GfxFont::makeFont(nullptr, "TestTag", {1, 0}, nullptr, {2, 0});

    }

};



TEST_F(GfxFontTest_1140, MatchesReturnsTrueForMatchingTag_1140) {

    EXPECT_TRUE(font->matches("TestTag"));

}



TEST_F(GfxFontTest_1140, MatchesReturnsFalseForNonMatchingTag_1140) {

    EXPECT_FALSE(font->matches("AnotherTag"));

}



TEST_F(GfxFontTest_1140, IsOkReturnsTrue_1140) {

    // Assuming isOk() returns true for a valid font

    EXPECT_TRUE(font->isOk());

}



TEST_F(GfxFontTest_1140, GetTagReturnsCorrectValue_1140) {

    EXPECT_EQ(font->getTag(), "TestTag");

}



TEST_F(GfxFontTest_1140, IsSubsetReturnsFalseByDefault_1140) {

    // Assuming isSubset() returns false by default if not explicitly set

    EXPECT_FALSE(font->isSubset());

}



TEST_F(GfxFontTest_1140, GetEmbeddedFontIDReturnsFalseIfNotSet_1140) {

    Ref embID;

    EXPECT_FALSE(font->getEmbeddedFontID(&embID));

}



TEST_F(GfxFontTest_1140, InvalidateEmbeddedFontReturnsFalseIfNotSet_1140) {

    // Assuming invalidateEmbeddedFont() returns false if no embedded font is set

    EXPECT_FALSE(font->invalidateEmbeddedFont());

}



TEST_F(GfxFontTest_1140, GetEmbeddedFontNameReturnsNullptrByDefault_1140) {

    EXPECT_EQ(font->getEmbeddedFontName(), nullptr);

}



TEST_F(GfxFontTest_1140, IsCIDFontReturnsFalseByDefault_1140) {

    // Assuming isCIDFont() returns false for non-CID fonts

    EXPECT_FALSE(font->isCIDFont());

}
