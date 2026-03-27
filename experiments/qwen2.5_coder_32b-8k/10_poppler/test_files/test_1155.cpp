#include <gtest/gtest.h>

#include "GfxFont.h"



class GfxFontTest_1155 : public ::testing::Test {

protected:

    class MockXRef : public XRef {

        // Mock implementation if needed for tests

    };



    class MockDict : public Dict {

        // Mock implementation if needed for tests

    };



    class MockPSOutputDev : public PSOutputDev {

        // Mock implementation if needed for tests

    };



    std::unique_ptr<MockXRef> mockXRef;

    std::unique_ptr<MockDict> mockFontDict;

    std::unique_ptr<GfxFont> gfxFont;



    void SetUp() override {

        mockXRef = std::make_unique<MockXRef>();

        mockFontDict = std::make_unique<MockDict>();

        gfxFont = GfxFont::makeFont(mockXRef.get(), "tag", Ref(1, 0), mockFontDict.get());

    }

};



TEST_F(GfxFontTest_1155, IsBold_ReturnsTrueWhenFlagSet_1155) {

    // Assuming we can set the flags for testing purposes

    gfxFont->flags |= fontBold;

    EXPECT_TRUE(gfxFont->isBold());

}



TEST_F(GfxFontTest_1155, IsBold_ReturnsFalseWhenFlagNotSet_1155) {

    gfxFont->flags &= ~fontBold;

    EXPECT_FALSE(gfxFont->isBold());

}



TEST_F(GfxFontTest_1155, IsOk_NormalOperation_1155) {

    // Assuming isOk() returns true for a valid GfxFont object

    EXPECT_TRUE(gfxFont->isOk());

}



TEST_F(GfxFontTest_1155, GetTag_ReturnsCorrectTag_1155) {

    EXPECT_EQ(gfxFont->getTag(), "tag");

}



TEST_F(GfxFontTest_1155, Matches_ReturnsTrueForMatchingTag_1155) {

    EXPECT_TRUE(gfxFont->matches("tag"));

}



TEST_F(GfxFontTest_1155, Matches_ReturnsFalseForNonMatchingTag_1155) {

    EXPECT_FALSE(gfxFont->matches("non_matching_tag"));

}



TEST_F(GfxFontTest_1155, IsCIDFont_NormalOperation_1155) {

    // Assuming isCIDFont() returns false for a non-CID font by default

    EXPECT_FALSE(gfxFont->isCIDFont());

}



TEST_F(GfxFontTest_1155, GetEmbeddedFontName_ReturnsValidString_1155) {

    EXPECT_NE(gfxFont->getEmbeddedFontName(), nullptr);

}



TEST_F(GfxFontTest_1155, GetFontMatrix_ReturnsValidArray_1155) {

    const auto& fontMatrix = gfxFont->getFontMatrix();

    EXPECT_EQ(fontMatrix.size(), 6);

}



TEST_F(GfxFontTest_1155, GetFontBBox_ReturnsValidArray_1155) {

    const auto& fontBBox = gfxFont->getFontBBox();

    EXPECT_EQ(fontBBox.size(), 4);

}



TEST_F(GfxFontTest_1155, GetAscent_ReturnsNonNegativeValue_1155) {

    EXPECT_GE(gfxFont->getAscent(), 0.0);

}



TEST_F(GfxFontTest_1155, GetDescent_ReturnsNonPositiveValue_1155) {

    EXPECT_LE(gfxFont->getDescent(), 0.0);

}



TEST_F(GfxFontTest_1155, HasToUnicodeCMap_ReturnsFalseForDefaultObject_1155) {

    EXPECT_FALSE(gfxFont->hasToUnicodeCMap());

}
