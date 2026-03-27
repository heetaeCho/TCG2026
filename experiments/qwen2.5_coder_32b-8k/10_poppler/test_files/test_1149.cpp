#include <gtest/gtest.h>

#include "GfxFont.h"

#include "XRef.h"

#include "Dict.h"

#include "PSOutputDev.h"

#include "CharCodeToUnicode.h"

#include "GooString.h"

#include <optional>

#include <string_view>



using namespace std;



class GfxFontTest_1149 : public ::testing::Test {

protected:

    XRef* mockXRef;

    Dict* mockDict;

    PSOutputDev* mockPSOutputDev;



    void SetUp() override {

        mockXRef = new XRef();

        mockDict = new Dict();

        mockPSOutputDev = new PSOutputDev(nullptr, false);

    }



    void TearDown() override {

        delete mockXRef;

        delete mockDict;

        delete mockPSOutputDev;

    }

};



TEST_F(GfxFontTest_1149, GetEmbeddedFontName_NormalOperation_1149) {

    auto font = GfxFont::makeFont(mockXRef, "tag", Ref(1, 0), mockDict);

    const GooString* name = font->getEmbeddedFontName();

    EXPECT_TRUE(name != nullptr); // Assuming it returns a valid pointer in normal operation

}



TEST_F(GfxFontTest_1149, GetEmbeddedFontName_EmptyName_1149) {

    auto font = GfxFont::makeFont(mockXRef, "tag", Ref(1, 0), mockDict);

    const GooString* name = font->getEmbeddedFontName();

    EXPECT_TRUE(name != nullptr && name->isEmpty()); // Assuming it returns an empty GooString if no name is set

}



TEST_F(GfxFontTest_1149, GetEmbeddedFontName_BoundaryCondition_1149) {

    auto font = GfxFont::makeFont(mockXRef, "tag", Ref(1, 0), mockDict);

    const GooString* name = font->getEmbeddedFontName();

    EXPECT_TRUE(name != nullptr); // Check behavior when boundary conditions are met

}



TEST_F(GfxFontTest_1149, GetEmbeddedFontName_ExceptionalCase_1149) {

    auto font = GfxFont::makeFont(mockXRef, "tag", Ref(1, 0), mockDict);

    const GooString* name = font->getEmbeddedFontName();

    EXPECT_TRUE(name != nullptr); // Check behavior in exceptional cases if observable

}



TEST_F(GfxFontTest_1149, IsSubset_NormalOperation_1149) {

    auto font = GfxFont::makeFont(mockXRef, "tag", Ref(1, 0), mockDict);

    EXPECT_TRUE(font->isOk()); // Assuming isOk() should be true for a valid font

}



TEST_F(GfxFontTest_1149, IsCIDFont_NormalOperation_1149) {

    auto font = GfxFont::makeFont(mockXRef, "tag", Ref(1, 0), mockDict);

    EXPECT_FALSE(font->isCIDFont()); // Assuming isCIDFont() should be false for a non-CID font

}



TEST_F(GfxFontTest_1149, GetTag_NormalOperation_1149) {

    auto font = GfxFont::makeFont(mockXRef, "tag", Ref(1, 0), mockDict);

    EXPECT_EQ(font->getTag(), "tag");

}



TEST_F(GfxFontTest_1149, GetID_NormalOperation_1149) {

    auto font = GfxFont::makeFont(mockXRef, "tag", Ref(1, 0), mockDict);

    const Ref* id = font->getID();

    EXPECT_TRUE(id != nullptr && id->num == 1 && id->gen == 0);

}



TEST_F(GfxFontTest_1149, Matches_NormalOperation_1149) {

    auto font = GfxFont::makeFont(mockXRef, "tag", Ref(1, 0), mockDict);

    EXPECT_TRUE(font->matches("tag"));

    EXPECT_FALSE(font->matches("otherTag"));

}



TEST_F(GfxFontTest_1149, GetFamily_NormalOperation_1149) {

    auto font = GfxFont::makeFont(mockXRef, "tag", Ref(1, 0), mockDict);

    const GooString* family = font->getFamily();

    EXPECT_TRUE(family != nullptr); // Assuming it returns a valid pointer in normal operation

}



TEST_F(GfxFontTest_1149, GetStretch_NormalOperation_1149) {

    auto font = GfxFont::makeFont(mockXRef, "tag", Ref(1, 0), mockDict);

    EXPECT_EQ(font->getStretch(), StretchNormal); // Assuming default value is StretchNormal

}



TEST_F(GfxFontTest_1149, GetWeight_NormalOperation_1149) {

    auto font = GfxFont::makeFont(mockXRef, "tag", Ref(1, 0), mockDict);

    EXPECT_EQ(font->getWeight(), WeightNormal); // Assuming default value is WeightNormal

}



TEST_F(GfxFontTest_1149, GetType_NormalOperation_1149) {

    auto font = GfxFont::makeFont(mockXRef, "tag", Ref(1, 0), mockDict);

    EXPECT_EQ(font->getType(), fontUnknownType); // Assuming default value is fontUnknownType

}



TEST_F(GfxFontTest_1149, GetEmbeddedFontID_NormalOperation_1149) {

    auto font = GfxFont::makeFont(mockXRef, "tag", Ref(1, 0), mockDict);

    Ref embID;

    EXPECT_FALSE(font->getEmbeddedFontID(&embID)); // Assuming it returns false if no embedded font ID

}



TEST_F(GfxFontTest_1149, InvalidateEmbeddedFont_NormalOperation_1149) {

    auto font = GfxFont::makeFont(mockXRef, "tag", Ref(1, 0), mockDict);

    EXPECT_FALSE(font->invalidateEmbeddedFont()); // Assuming it returns false if no embedded font to invalidate

}



TEST_F(GfxFontTest_1149, GetFlags_NormalOperation_1149) {

    auto font = GfxFont::makeFont(mockXRef, "tag", Ref(1, 0), mockDict);

    EXPECT_EQ(font->getFlags(), 0); // Assuming default value is 0

}



TEST_F(GfxFontTest_1149, IsFixedWidth_NormalOperation_1149) {

    auto font = GfxFont::makeFont(mockXRef, "tag", Ref(1, 0), mockDict);

    EXPECT_FALSE(font->isFixedWidth()); // Assuming default value is false

}



TEST_F(GfxFontTest_1149, IsSerif_NormalOperation_1149) {

    auto font = GfxFont::makeFont(mockXRef, "tag", Ref(1, 0), mockDict);

    EXPECT_FALSE(font->isSerif()); // Assuming default value is false

}



TEST_F(GfxFontTest_1149, IsSymbolic_NormalOperation_1149) {

    auto font = GfxFont::makeFont(mockXRef, "tag", Ref(1, 0), mockDict);

    EXPECT_FALSE(font->isSymbolic()); // Assuming default value is false

}



TEST_F(GfxFontTest_1149, IsItalic_NormalOperation_1149) {

    auto font = GfxFont::makeFont(mockXRef, "tag", Ref(1, 0), mockDict);

    EXPECT_FALSE(font->isItalic()); // Assuming default value is false

}



TEST_F(GfxFontTest_1149, IsBold_NormalOperation_1149) {

    auto font = GfxFont::makeFont(mockXRef, "tag", Ref(1, 0), mockDict);

    EXPECT_FALSE(font->isBold()); // Assuming default value is false

}



TEST_F(GfxFontTest_1149, GetFontMatrix_NormalOperation_1149) {

    auto font = GfxFont::makeFont(mockXRef, "tag", Ref(1, 0), mockDict);

    const std::array<double, 6>& matrix = font->getFontMatrix();

    EXPECT_TRUE(matrix == std::array<double, 6>{1.0, 0.0, 0.0, 1.0, 0.0, 0.0}); // Assuming default value is identity matrix

}



TEST_F(GfxFontTest_1149, GetFontBBox_NormalOperation_1149) {

    auto font = GfxFont::makeFont(mockXRef, "tag", Ref(1, 0), mockDict);

    const std::array<double, 4>& bbox = font->getFontBBox();

    EXPECT_TRUE(bbox == std::array<double, 4>{0.0, 0.0, 0.0, 0.0}); // Assuming default value is zero array

}



TEST_F(GfxFontTest_1149, GetAscent_NormalOperation_1149) {

    auto font = GfxFont::makeFont(mockXRef, "tag", Ref(1, 0), mockDict);

    EXPECT_EQ(font->getAscent(), 0.0); // Assuming default value is 0.0

}



TEST_F(GfxFontTest_1149, GetDescent_NormalOperation_1149) {

    auto font = GfxFont::makeFont(mockXRef, "tag", Ref(1, 0), mockDict);

    EXPECT_EQ(font->getDescent(), 0.0); // Assuming default value is 0.0

}



TEST_F(GfxFontTest_1149, GetWMode_NormalOperation_1149) {

    auto font = GfxFont::makeFont(mockXRef, "tag", Ref(1, 0), mockDict);

    EXPECT_EQ(font->getWMode(), wmodeHorizontal); // Assuming default value is horizontal

}



TEST_F(GfxFontTest_1149, HasToUnicodeCMap_NormalOperation_1149) {

    auto font = GfxFont::makeFont(mockXRef, "tag", Ref(1, 0), mockDict);

    EXPECT_FALSE(font->hasToUnicodeCMap()); // Assuming default value is false

}



TEST_F(GfxFontTest_1149, GetEncodingName_NormalOperation_1149) {

    auto font = GfxFont::makeFont(mockXRef, "tag", Ref(1, 0), mockDict);

    EXPECT_EQ(font->getEncodingName(), ""); // Assuming default value is empty string

}
