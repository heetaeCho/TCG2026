#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxFont.h"



class GfxFontTest : public ::testing::Test {

protected:

    class MockXRef : public XRef {

        // Add any necessary mock methods here if needed

    };



    class MockPSOutputDev : public PSOutputDev {

        // Add any necessary mock methods here if needed

    };



    std::unique_ptr<GfxFont> CreateGfxFont() {

        Ref id(1, 0);

        return GfxFont::makeFont(new MockXRef(), "tag", id, nullptr, GfxFontType::type1, id);

    }

};



TEST_F(GfxFontTest_1145, GetType_ReturnsExpectedType_1145) {

    auto font = CreateGfxFont();

    EXPECT_EQ(font->getType(), GfxFontType::type1);

}



TEST_F(GfxFontTest_1145, IsSubset_ReturnsFalseByDefault_1145) {

    auto font = CreateGfxFont();

    EXPECT_FALSE(font->isSubset());

}



TEST_F(GfxFontTest_1145, GetTag_ReturnsExpectedTag_1145) {

    auto font = CreateGfxFont();

    EXPECT_EQ(font->getTag(), "tag");

}



TEST_F(GfxFontTest_1145, IsCIDFont_ReturnsFalseByDefault_1145) {

    auto font = CreateGfxFont();

    EXPECT_FALSE(font->isCIDFont());

}



TEST_F(GfxFontTest_1145, GetEmbeddedFontID_ReturnsFalseIfNoEmbedding_1145) {

    auto font = CreateGfxFont();

    Ref embID;

    EXPECT_FALSE(font->getEmbeddedFontID(&embID));

}



TEST_F(GfxFontTest_1145, InvalidateEmbeddedFont_ReturnsFalseByDefault_1145) {

    auto font = CreateGfxFont();

    EXPECT_FALSE(font->invalidateEmbeddedFont());

}



TEST_F(GfxFontTest_1145, GetEmbeddedFontName_ReturnsNullptrByDefault_1145) {

    auto font = CreateGfxFont();

    EXPECT_EQ(font->getEmbeddedFontName(), nullptr);

}



TEST_F(GfxFontTest_1145, IsOk_ReturnsTrueByDefault_1145) {

    auto font = CreateGfxFont();

    EXPECT_TRUE(font->isOk());

}



TEST_F(GfxFontTest_1145, GetFamily_ReturnsNullptrByDefault_1145) {

    auto font = CreateGfxFont();

    EXPECT_EQ(font->getFamily(), nullptr);

}



TEST_F(GfxFontTest_1145, GetStretch_ReturnsNormalByDefault_1145) {

    auto font = CreateGfxFont();

    EXPECT_EQ(font->getStretch(), Stretch::normal);

}



TEST_F(GfxFontTest_1145, GetWeight_ReturnsNormalByDefault_1145) {

    auto font = CreateGfxFont();

    EXPECT_EQ(font->getWeight(), Weight::normal);

}



TEST_F(GfxFontTest_1145, GetName_ReturnsEmptyOptionalByDefault_1145) {

    auto font = CreateGfxFont();

    EXPECT_FALSE(font->getName().has_value());

}



TEST_F(GfxFontTest_1145, GetNextChar_DefaultBehavior_1145) {

    auto font = CreateGfxFont();

    CharCode code;

    const Unicode* u;

    int uLen;

    double dx, dy, ox, oy;

    EXPECT_EQ(font->getNextChar("", 0, &code, &u, &uLen, &dx, &dy, &ox, &oy), -1);

}



TEST_F(GfxFontTest_1145, GetAlternateName_ReturnsSameIfNoChange_1145) {

    EXPECT_EQ(GfxFont::getAlternateName("Helvetica"), "Helvetica");

}



TEST_F(GfxFontTest_1145, IsBase14Font_StringVersion_ReturnsTrueForKnownFonts_1145) {

    EXPECT_TRUE(GfxFont::isBase14Font("Helvetica", "Normal"));

}



TEST_F(GfxFontTest_1145, IsBase14Font_StringVersion_ReturnsFalseForUnknownFonts_1145) {

    EXPECT_FALSE(GfxFont::isBase14Font("UnknownFont", "Normal"));

}



TEST_F(GfxFontTest_1145, GetExternalFont_DefaultBehavior_1145) {

    EXPECT_FALSE(GfxFont::getExternalFont("unknown/path.ttf", false).has_value());

}



TEST_F(GfxFontTest_1145, IsBase14Font_IntVersion_ReturnsTrueForKnownFonts_1145) {

    EXPECT_TRUE(GfxFont::isBase14Font(0, 0)); // Assuming 0 corresponds to a known font

}



TEST_F(GfxFontTest_1145, IsBase14Font_IntVersion_ReturnsFalseForUnknownFonts_1145) {

    EXPECT_FALSE(GfxFont::isBase14Font(-1, -1)); // Assuming -1 does not correspond to any font

}



TEST_F(GfxFontTest_1145, GetFlags_ReturnsZeroByDefault_1145) {

    auto font = CreateGfxFont();

    EXPECT_EQ(font->getFlags(), 0);

}



TEST_F(GfxFontTest_1145, IsFixedWidth_ReturnsFalseByDefault_1145) {

    auto font = CreateGfxFont();

    EXPECT_FALSE(font->isFixedWidth());

}



TEST_F(GfxFontTest_1145, IsSerif_ReturnsFalseByDefault_1145) {

    auto font = CreateGfxFont();

    EXPECT_FALSE(font->isSerif());

}



TEST_F(GfxFontTest_1145, IsSymbolic_ReturnsFalseByDefault_1145) {

    auto font = CreateGfxFont();

    EXPECT_FALSE(font->isSymbolic());

}



TEST_F(GfxFontTest_1145, IsItalic_ReturnsFalseByDefault_1145) {

    auto font = CreateGfxFont();

    EXPECT_FALSE(font->isItalic());

}



TEST_F(GfxFontTest_1145, IsBold_ReturnsFalseByDefault_1145) {

    auto font = CreateGfxFont();

    EXPECT_FALSE(font->isBold());

}



TEST_F(GfxFontTest_1145, GetFontMatrix_DefaultValues_1145) {

    auto font = CreateGfxFont();

    std::array<double, 6> expectedMatrix = {0.0};

    EXPECT_EQ(font->getFontMatrix(), expectedMatrix);

}



TEST_F(GfxFontTest_1145, GetFontBBox_DefaultValues_1145) {

    auto font = CreateGfxFont();

    std::array<double, 4> expectedBBox = {0.0};

    EXPECT_EQ(font->getFontBBox(), expectedBBox);

}



TEST_F(GfxFontTest_1145, GetAscent_DefaultValue_1145) {

    auto font = CreateGfxFont();

    EXPECT_DOUBLE_EQ(font->getAscent(), 0.0);

}



TEST_F(GfxFontTest_1145, GetDescent_DefaultValue_1145) {

    auto font = CreateGfxFont();

    EXPECT_DOUBLE_EQ(font->getDescent(), 0.0);

}



TEST_F(GfxFontTest_1145, GetWMode_DefaultValue_1145) {

    auto font = CreateGfxFont();

    EXPECT_EQ(font->getWMode(), WritingMode::horizontal);

}



TEST_F(GfxFontTest_1145, HasToUnicodeCMap_DefaultFalse_1145) {

    auto font = CreateGfxFont();

    EXPECT_FALSE(font->hasToUnicodeCMap());

}



TEST_F(GfxFontTest_1145, GetEncodingName_DefaultEmpty_1145) {

    auto font = CreateGfxFont();

    EXPECT_EQ(font->getEncodingName(), "");

}
