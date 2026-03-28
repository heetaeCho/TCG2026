#include <gtest/gtest.h>

#include "GfxFont.h"



class GfxFontTest_1160 : public ::testing::Test {

protected:

    std::unique_ptr<GfxFont> font;



    void SetUp() override {

        // Assuming a factory method or some way to create an instance of GfxFont

        // Since we cannot infer the implementation, we will mock or use a stub if necessary.

        // For this example, let's assume makeFont can be used to create an instance.

        font = GfxFont::makeFont(nullptr, "testTag", Ref(), nullptr);

    }

};



TEST_F(GfxFontTest_1160, GetWMode_Default_ReturnsHorizontal_1160) {

    EXPECT_EQ(font->getWMode(), WritingMode::Horizontal);

}



TEST_F(GfxFontTest_1160, IsSubset_Default_ReturnsFalse_1160) {

    EXPECT_FALSE(font->isSubset());

}



TEST_F(GfxFontTest_1160, GetNameWithoutSubsetTag_Default_ReturnsEmptyString_1160) {

    EXPECT_EQ(font->getNameWithoutSubsetTag(), "");

}



TEST_F(GfxFontTest_1160, GetToUnicode_Default_ReturnsNullptr_1160) {

    EXPECT_EQ(font->getToUnicode(), nullptr);

}



TEST_F(GfxFontTest_1160, LocateFont_NullXRef_ReturnsEmptyOptional_1160) {

    std::optional<GfxFontLoc> result = font->locateFont(nullptr, nullptr, nullptr);

    EXPECT_FALSE(result.has_value());

}



TEST_F(GfxFontTest_1160, ReadEmbFontFile_NullXRef_ReturnsEmptyOptional_1160) {

    std::optional<std::vector<unsigned char>> result = font->readEmbFontFile(nullptr);

    EXPECT_FALSE(result.has_value());

}



TEST_F(GfxFontTest_1160, GetNextChar_Default_ReturnsZero_1160) {

    CharCode code;

    const Unicode* u;

    int uLen;

    double dx, dy, ox, oy;

    int result = font->getNextChar("", 0, &code, &u, &uLen, &dx, &dy, &ox, &oy);

    EXPECT_EQ(result, 0);

}



TEST_F(GfxFontTest_1160, GetAlternateName_NullName_ReturnsNullptr_1160) {

    const char* result = GfxFont::getAlternateName(nullptr);

    EXPECT_EQ(result, nullptr);

}



TEST_F(GfxFontTest_1160, IsBase14Font_StringParams_Default_ReturnsFalse_1160) {

    EXPECT_FALSE(GfxFont::isBase14Font("Arial", "Regular"));

}



TEST_F(GfxFontTest_1160, IsCIDFont_Default_ReturnsFalse_1160) {

    EXPECT_FALSE(font->isCIDFont());

}



TEST_F(GfxFontTest_1160, GetEmbeddedFontID_NullEmbID_ReturnsFalse_1160) {

    Ref embID;

    EXPECT_FALSE(font->getEmbeddedFontID(&embID));

}



TEST_F(GfxFontTest_1160, InvalidateEmbeddedFont_Default_ReturnsFalse_1160) {

    EXPECT_FALSE(font->invalidateEmbeddedFont());

}



TEST_F(GfxFontTest_1160, GetEmbeddedFontName_Default_ReturnsNullptr_1160) {

    EXPECT_EQ(font->getEmbeddedFontName(), nullptr);

}



TEST_F(GfxFontTest_1160, GetFlags_Default_ReturnsZero_1160) {

    EXPECT_EQ(font->getFlags(), 0);

}



TEST_F(GfxFontTest_1160, IsFixedWidth_Default_ReturnsFalse_1160) {

    EXPECT_FALSE(font->isFixedWidth());

}



TEST_F(GfxFontTest_1160, IsSerif_Default_ReturnsFalse_1160) {

    EXPECT_FALSE(font->isSerif());

}



TEST_F(GfxFontTest_1160, IsSymbolic_Default_ReturnsFalse_1160) {

    EXPECT_FALSE(font->isSymbolic());

}



TEST_F(GfxFontTest_1160, IsItalic_Default_ReturnsFalse_1160) {

    EXPECT_FALSE(font->isItalic());

}



TEST_F(GfxFontTest_1160, IsBold_Default_ReturnsFalse_1160) {

    EXPECT_FALSE(font->isBold());

}



TEST_F(GfxFontTest_1160, GetFontMatrix_Default_ReturnsIdentityMatrix_1160) {

    std::array<double, 6> identityMatrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};

    EXPECT_EQ(font->getFontMatrix(), identityMatrix);

}



TEST_F(GfxFontTest_1160, GetFontBBox_Default_ReturnsZeroArray_1160) {

    std::array<double, 4> zeroArray = {0.0, 0.0, 0.0, 0.0};

    EXPECT_EQ(font->getFontBBox(), zeroArray);

}



TEST_F(GfxFontTest_1160, GetAscent_Default_ReturnsZero_1160) {

    EXPECT_EQ(font->getAscent(), 0.0);

}



TEST_F(GfxFontTest_1160, GetDescent_Default_ReturnsZero_1160) {

    EXPECT_EQ(font->getDescent(), 0.0);

}



TEST_F(GfxFontTest_1160, HasToUnicodeCMap_Default_ReturnsFalse_1160) {

    EXPECT_FALSE(font->hasToUnicodeCMap());

}



TEST_F(GfxFontTest_1160, GetEncodingName_Default_ReturnsEmptyString_1160) {

    EXPECT_EQ(font->getEncodingName(), "");

}
