#include <gtest/gtest.h>

#include "GfxFont.h"

#include <memory>

#include <string>

#include <optional>



class GfxFontTest_1138 : public ::testing::Test {

protected:

    // Helper function to create a GfxFont instance for testing

    std::unique_ptr<GfxFont> createGfxFont() {

        return GfxFont::makeFont(nullptr, "testTag", Ref{}, nullptr, gfxFontType1);

    }

};



TEST_F(GfxFontTest_1138, GetTag_ReturnsCorrectValue_1138) {

    auto font = createGfxFont();

    EXPECT_EQ(font->getTag(), "testTag");

}



TEST_F(GfxFontTest_1138, IsSubset_DefaultBehavior_1138) {

    auto font = createGfxFont();

    EXPECT_FALSE(font->isSubset());

}



TEST_F(GfxFontTest_1138, GetNameWithoutSubsetTag_DefaultBehavior_1138) {

    auto font = createGfxFont();

    EXPECT_EQ(font->getNameWithoutSubsetTag(), "");

}



TEST_F(GfxFontTest_1138, GetToUnicode_DefaultBehavior_1138) {

    auto font = createGfxFont();

    EXPECT_EQ(font->getToUnicode(), nullptr);

}



TEST_F(GfxFontTest_1138, LocateFont_DefaultBehavior_1138) {

    auto font = createGfxFont();

    XRef xref;

    PSOutputDev ps;

    GooString substituteFontName;

    auto result = font->locateFont(&xref, &ps, &substituteFontName);

    EXPECT_FALSE(result.has_value());

}



TEST_F(GfxFontTest_1138, ReadEmbFontFile_DefaultBehavior_1138) {

    auto font = createGfxFont();

    XRef xref;

    auto result = font->readEmbFontFile(&xref);

    EXPECT_FALSE(result.has_value());

}



TEST_F(GfxFontTest_1138, GetNextChar_DefaultBehavior_1138) {

    auto font = createGfxFont();

    const char* s = "";

    int len = 0;

    CharCode code;

    const Unicode* u;

    int uLen;

    double dx, dy, ox, oy;

    EXPECT_EQ(font->getNextChar(s, len, &code, &u, &uLen, &dx, &dy, &ox, &oy), -1);

}



TEST_F(GfxFontTest_1138, GetAlternateName_DefaultBehavior_1138) {

    const char* name = "Arial";

    EXPECT_STREQ(GfxFont::getAlternateName(name), name);

}



TEST_F(GfxFontTest_1138, IsBase14Font_StringView_DefaultBehavior_1138) {

    std::string_view family = "Helvetica";

    std::string_view style = "Normal";

    EXPECT_TRUE(GfxFont::isBase14Font(family, style));

}



TEST_F(GfxFontTest_1138, IsBase14Font_Int_DefaultBehavior_1138) {

    int family = 0; // Assuming 0 corresponds to a base 14 font

    int style = 0; // Assuming 0 corresponds to a normal style

    EXPECT_TRUE(GfxFont::isBase14Font(family, style));

}



TEST_F(GfxFontTest_1138, IsCIDFont_DefaultBehavior_1138) {

    auto font = createGfxFont();

    EXPECT_FALSE(font->isCIDFont());

}



TEST_F(GfxFontTest_1138, GetEmbeddedFontID_DefaultBehavior_1138) {

    auto font = createGfxFont();

    Ref embID;

    EXPECT_FALSE(font->getEmbeddedFontID(&embID));

}



TEST_F(GfxFontTest_1138, InvalidateEmbeddedFont_DefaultBehavior_1138) {

    auto font = createGfxFont();

    EXPECT_FALSE(font->invalidateEmbeddedFont());

}



TEST_F(GfxFontTest_1138, GetEmbeddedFontName_DefaultBehavior_1138) {

    auto font = createGfxFont();

    EXPECT_EQ(font->getEmbeddedFontName(), nullptr);

}



TEST_F(GfxFontTest_1138, GetFlags_DefaultBehavior_1138) {

    auto font = createGfxFont();

    EXPECT_EQ(font->getFlags(), 0);

}



TEST_F(GfxFontTest_1138, IsFixedWidth_DefaultBehavior_1138) {

    auto font = createGfxFont();

    EXPECT_FALSE(font->isFixedWidth());

}



TEST_F(GfxFontTest_1138, IsSerif_DefaultBehavior_1138) {

    auto font = createGfxFont();

    EXPECT_FALSE(font->isSerif());

}



TEST_F(GfxFontTest_1138, IsSymbolic_DefaultBehavior_1138) {

    auto font = createGfxFont();

    EXPECT_FALSE(font->isSymbolic());

}



TEST_F(GfxFontTest_1138, IsItalic_DefaultBehavior_1138) {

    auto font = createGfxFont();

    EXPECT_FALSE(font->isItalic());

}



TEST_F(GfxFontTest_1138, IsBold_DefaultBehavior_1138) {

    auto font = createGfxFont();

    EXPECT_FALSE(font->isBold());

}



TEST_F(GfxFontTest_1138, GetFontMatrix_DefaultBehavior_1138) {

    auto font = createGfxFont();

    std::array<double, 6> expected = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

    EXPECT_EQ(font->getFontMatrix(), expected);

}



TEST_F(GfxFontTest_1138, GetFontBBox_DefaultBehavior_1138) {

    auto font = createGfxFont();

    std::array<double, 4> expected = {0.0, 0.0, 0.0, 0.0};

    EXPECT_EQ(font->getFontBBox(), expected);

}



TEST_F(GfxFontTest_1138, GetAscent_DefaultBehavior_1138) {

    auto font = createGfxFont();

    EXPECT_EQ(font->getAscent(), 0.0);

}



TEST_F(GfxFontTest_1138, GetDescent_DefaultBehavior_1138) {

    auto font = createGfxFont();

    EXPECT_EQ(font->getDescent(), 0.0);

}



TEST_F(GfxFontTest_1138, HasToUnicodeCMap_DefaultBehavior_1138) {

    auto font = createGfxFont();

    EXPECT_FALSE(font->hasToUnicodeCMap());

}



TEST_F(GfxFontTest_1138, GetEncodingName_DefaultBehavior_1138) {

    auto font = createGfxFont();

    EXPECT_EQ(font->getEncodingName(), "");

}
