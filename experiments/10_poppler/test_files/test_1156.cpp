#include <gtest/gtest.h>

#include "GfxFont.h"

#include <array>



class GfxFontTest : public ::testing::Test {

protected:

    class MockXRef : public XRef {

        // Add necessary mock methods if needed

    };



    std::unique_ptr<GfxFont> createGfxFont() {

        Ref id(1, 0);

        auto xref = std::make_unique<MockXRef>();

        return GfxFont::makeFont(xref.get(), "testTag", id, nullptr, id);

    }

};



TEST_F(GfxFontTest_1156, GetFontMatrix_ReturnsValidArray_1156) {

    auto font = createGfxFont();

    const std::array<double, 6>& matrix = font->getFontMatrix();

    EXPECT_EQ(matrix.size(), 6);

}



TEST_F(GfxFontTest_1156, IsSubset_DefaultBehavior_1156) {

    auto font = createGfxFont();

    EXPECT_FALSE(font->isSubset());

}



TEST_F(GfxFontTest_1156, GetTag_ReturnsValidString_1156) {

    auto font = createGfxFont();

    EXPECT_EQ(font->getTag(), "testTag");

}



TEST_F(GfxFontTest_1156, GetID_ReturnsValidRef_1156) {

    auto font = createGfxFont();

    const Ref* id = font->getID();

    EXPECT_NE(id, nullptr);

    EXPECT_EQ(*id, Ref(1, 0));

}



TEST_F(GfxFontTest_1156, Matches_CorrectTag_ReturnsTrue_1156) {

    auto font = createGfxFont();

    EXPECT_TRUE(font->matches("testTag"));

}



TEST_F(GfxFontTest_1156, Matches_IncorrectTag_ReturnsFalse_1156) {

    auto font = createGfxFont();

    EXPECT_FALSE(font->matches("wrongTag"));

}



TEST_F(GfxFontTest_1156, GetFamily_DefaultBehavior_1156) {

    auto font = createGfxFont();

    const GooString* family = font->getFamily();

    EXPECT_EQ(family, nullptr);

}



TEST_F(GfxFontTest_1156, GetStretch_DefaultBehavior_1156) {

    auto font = createGfxFont();

    Stretch stretch = font->getStretch();

    EXPECT_EQ(stretch, NormalWidth);

}



TEST_F(GfxFontTest_1156, GetWeight_DefaultBehavior_1156) {

    auto font = createGfxFont();

    Weight weight = font->getWeight();

    EXPECT_EQ(weight, NormalWeight);

}



TEST_F(GfxFontTest_1156, GetType_DefaultBehavior_1156) {

    auto font = createGfxFont();

    GfxFontType type = font->getType();

    EXPECT_EQ(type, unknownFont); // Assuming default type is unknownFont

}



TEST_F(GfxFontTest_1156, IsCIDFont_DefaultBehavior_1156) {

    auto font = createGfxFont();

    EXPECT_FALSE(font->isCIDFont());

}



TEST_F(GfxFontTest_1156, GetEmbeddedFontID_DefaultBehavior_1156) {

    auto font = createGfxFont();

    Ref embID;

    EXPECT_FALSE(font->getEmbeddedFontID(&embID));

}



TEST_F(GfxFontTest_1156, InvalidateEmbeddedFont_DefaultBehavior_1156) {

    auto font = createGfxFont();

    EXPECT_FALSE(font->invalidateEmbeddedFont());

}



TEST_F(GfxFontTest_1156, GetEmbeddedFontName_DefaultBehavior_1156) {

    auto font = createGfxFont();

    const GooString* embFontName = font->getEmbeddedFontName();

    EXPECT_EQ(embFontName, nullptr);

}



TEST_F(GfxFontTest_1156, GetFlags_DefaultBehavior_1156) {

    auto font = createGfxFont();

    int flags = font->getFlags();

    EXPECT_EQ(flags, 0); // Assuming default flags are 0

}



TEST_F(GfxFontTest_1156, IsFixedWidth_DefaultBehavior_1156) {

    auto font = createGfxFont();

    EXPECT_FALSE(font->isFixedWidth());

}



TEST_F(GfxFontTest_1156, IsSerif_DefaultBehavior_1156) {

    auto font = createGfxFont();

    EXPECT_FALSE(font->isSerif());

}



TEST_F(GfxFontTest_1156, IsSymbolic_DefaultBehavior_1156) {

    auto font = createGfxFont();

    EXPECT_FALSE(font->isSymbolic());

}



TEST_F(GfxFontTest_1156, IsItalic_DefaultBehavior_1156) {

    auto font = createGfxFont();

    EXPECT_FALSE(font->isItalic());

}



TEST_F(GfxFontTest_1156, IsBold_DefaultBehavior_1156) {

    auto font = createGfxFont();

    EXPECT_FALSE(font->isBold());

}



TEST_F(GfxFontTest_1156, GetFontBBox_ReturnsValidArray_1156) {

    auto font = createGfxFont();

    const std::array<double, 4>& bbox = font->getFontBBox();

    EXPECT_EQ(bbox.size(), 4);

}



TEST_F(GfxFontTest_1156, GetAscent_DefaultBehavior_1156) {

    auto font = createGfxFont();

    double ascent = font->getAscent();

    EXPECT_DOUBLE_EQ(ascent, 0.0); // Assuming default ascent is 0.0

}



TEST_F(GfxFontTest_1156, GetDescent_DefaultBehavior_1156) {

    auto font = createGfxFont();

    double descent = font->getDescent();

    EXPECT_DOUBLE_EQ(descent, 0.0); // Assuming default descent is 0.0

}



TEST_F(GfxFontTest_1156, GetWMode_DefaultBehavior_1156) {

    auto font = createGfxFont();

    WritingMode wmode = font->getWMode();

    EXPECT_EQ(wmode, Horizontal);

}



TEST_F(GfxFontTest_1156, HasToUnicodeCMap_DefaultBehavior_1156) {

    auto font = createGfxFont();

    EXPECT_FALSE(font->hasToUnicodeCMap());

}



TEST_F(GfxFontTest_1156, GetEncodingName_DefaultBehavior_1156) {

    auto font = createGfxFont();

    const std::string& encodingName = font->getEncodingName();

    EXPECT_EQ(encodingName, ""); // Assuming default encoding name is empty string

}
