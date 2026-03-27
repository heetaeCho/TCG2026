#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxFont.h"



using namespace testing;



class MockXRef : public XRef {

public:

    MOCK_METHOD(Dict*, getDict, (const Ref&), (override));

    MOCK_METHOD(bool, ok, (), (const, override));

};



class MockPSOutputDev : public PSOutputDev {

public:

    MOCK_METHOD(void, updateFont, (GfxState* state), (override));

};



class GfxFontTest_1146 : public ::testing::Test {

protected:

    Ref ref{1, 0};

    std::string tag = "TestTag";

    MockXRef mockXRef;

    MockPSOutputDev mockPSOutputDev;



    void SetUp() override {

        // Setup can be done here if needed

    }



    GfxFont* createGfxFont() {

        return new GfxFont(tag.c_str(), ref, std::optional<std::string>("FontName"), gfxFontType1, ref);

    }

};



TEST_F(GfxFontTest_1146, IsCIDFont_Default_1146) {

    auto font = createGfxFont();

    EXPECT_FALSE(font->isCIDFont());

}



TEST_F(GfxFontTest_1146, GetTag_ReturnsCorrectValue_1146) {

    auto font = createGfxFont();

    EXPECT_EQ(tag, font->getTag());

}



TEST_F(GfxFontTest_1146, GetID_ReturnsCorrectReference_1146) {

    auto font = createGfxFont();

    EXPECT_EQ(&ref, font->getID());

}



TEST_F(GfxFontTest_1146, Matches_Tag_ReturnsTrue_1146) {

    auto font = createGfxFont();

    EXPECT_TRUE(font->matches(tag.c_str()));

}



TEST_F(GfxFontTest_1146, Matches_DifferentTag_ReturnsFalse_1146) {

    auto font = createGfxFont();

    EXPECT_FALSE(font->matches("DifferentTag"));

}



TEST_F(GfxFontTest_1146, IsSubset_Default_ReturnsFalse_1146) {

    auto font = createGfxFont();

    EXPECT_FALSE(font->isSubset());

}



TEST_F(GfxFontTest_1146, GetNameWithoutSubsetTag_ReturnsName_1146) {

    auto font = createGfxFont();

    EXPECT_EQ("FontName", font->getNameWithoutSubsetTag());

}



TEST_F(GfxFontTest_1146, GetToUnicode_Default_ReturnsNullptr_1146) {

    auto font = createGfxFont();

    EXPECT_EQ(nullptr, font->getToUnicode());

}



TEST_F(GfxFontTest_1146, LocateFont_NoExternalFont_ReturnsEmptyOptional_1146) {

    auto font = createGfxFont();

    GooString substituteFontName("Substitute");

    EXPECT_CALL(mockXRef, ok()).WillOnce(Return(true));

    EXPECT_EQ(std::nullopt, font->locateFont(&mockXRef, &mockPSOutputDev, &substituteFontName));

}



TEST_F(GfxFontTest_1146, ReadEmbFontFile_Default_ReturnsEmptyOptional_1146) {

    auto font = createGfxFont();

    EXPECT_EQ(std::nullopt, font->readEmbFontFile(&mockXRef));

}



TEST_F(GfxFontTest_1146, GetNextChar_Default_ReturnsMinusOne_1146) {

    auto font = createGfxFont();

    CharCode code;

    const Unicode* u;

    int uLen;

    double dx, dy, ox, oy;

    EXPECT_EQ(-1, font->getNextChar("test", 4, &code, &u, &uLen, &dx, &dy, &ox, &oy));

}



TEST_F(GfxFontTest_1146, GetAlternateName_Default_ReturnsSameName_1146) {

    const char* name = "TestName";

    EXPECT_STREQ(name, GfxFont::getAlternateName(name));

}



TEST_F(GfxFontTest_1146, IsBase14Font_StringView_ReturnsFalseForUnknownFont_1146) {

    EXPECT_FALSE(GfxFont::isBase14Font("UnknownFont", "Regular"));

}



TEST_F(GfxFontTest_1146, IsBase14Font_StringView_ReturnsTrueForKnownFont_1146) {

    EXPECT_TRUE(GfxFont::isBase14Font("Helvetica", "Bold"));

}



TEST_F(GfxFontTest_1146, GetFontType_Default_ReturnsGfxFontType1_1146) {

    auto font = createGfxFont();

    Ref embID;

    Dict mockDict; // Assuming an empty dict for this test

    EXPECT_EQ(gfxFontType1, GfxFont::getFontType(&mockXRef, &mockDict, &embID));

}



TEST_F(GfxFontTest_1146, IsOk_Default_ReturnsTrue_1146) {

    auto font = createGfxFont();

    EXPECT_TRUE(font->isOk());

}



TEST_F(GfxFontTest_1146, GetFamily_Default_ReturnsNullptr_1146) {

    auto font = createGfxFont();

    EXPECT_EQ(nullptr, font->getFamily());

}



TEST_F(GfxFontTest_1146, GetStretch_Default_ReturnsNormal_1146) {

    auto font = createGfxFont();

    EXPECT_EQ(stretchNormal, font->getStretch());

}



TEST_F(GfxFontTest_1146, GetWeight_Default_ReturnsNormal_1146) {

    auto font = createGfxFont();

    EXPECT_EQ(weightNormal, font->getWeight());

}



TEST_F(GfxFontTest_1146, GetName_Default_ReturnsEmptyOptional_1146) {

    auto font = createGfxFont();

    EXPECT_EQ(std::nullopt, font->getName());

}



TEST_F(GfxFontTest_1146, GetType_Default_ReturnsType1_1146) {

    auto font = createGfxFont();

    EXPECT_EQ(gfxFontType1, font->getType());

}



TEST_F(GfxFontTest_1146, GetEmbeddedFontID_Default_ReturnsFalse_1146) {

    auto font = createGfxFont();

    Ref embID;

    EXPECT_FALSE(font->getEmbeddedFontID(&embID));

}



TEST_F(GfxFontTest_1146, InvalidateEmbeddedFont_Default_ReturnsFalse_1146) {

    auto font = createGfxFont();

    EXPECT_FALSE(font->invalidateEmbeddedFont());

}



TEST_F(GfxFontTest_1146, GetEmbeddedFontName_Default_ReturnsNullptr_1146) {

    auto font = createGfxFont();

    EXPECT_EQ(nullptr, font->getEmbeddedFontName());

}



TEST_F(GfxFontTest_1146, GetFlags_Default_ReturnsZero_1146) {

    auto font = createGfxFont();

    EXPECT_EQ(0, font->getFlags());

}



TEST_F(GfxFontTest_1146, IsFixedWidth_Default_ReturnsFalse_1146) {

    auto font = createGfxFont();

    EXPECT_FALSE(font->isFixedWidth());

}



TEST_F(GfxFontTest_1146, IsSerif_Default_ReturnsFalse_1146) {

    auto font = createGfxFont();

    EXPECT_FALSE(font->isSerif());

}



TEST_F(GfxFontTest_1146, IsSymbolic_Default_ReturnsFalse_1146) {

    auto font = createGfxFont();

    EXPECT_FALSE(font->isSymbolic());

}



TEST_F(GfxFontTest_1146, IsItalic_Default_ReturnsFalse_1146) {

    auto font = createGfxFont();

    EXPECT_FALSE(font->isItalic());

}



TEST_F(GfxFontTest_1146, IsBold_Default_ReturnsFalse_1146) {

    auto font = createGfxFont();

    EXPECT_FALSE(font->isBold());

}



TEST_F(GfxFontTest_1146, GetFontMatrix_Default_ReturnsIdentityMatrix_1146) {

    auto font = createGfxFont();

    std::array<double, 6> identity = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};

    EXPECT_EQ(identity, font->getFontMatrix());

}



TEST_F(GfxFontTest_1146, GetFontBBox_Default_ReturnsZeroBBox_1146) {

    auto font = createGfxFont();

    std::array<double, 4> zeroBBox = {0.0, 0.0, 0.0, 0.0};

    EXPECT_EQ(zeroBBox, font->getFontBBox());

}



TEST_F(GfxFontTest_1146, GetAscent_Default_ReturnsZero_1146) {

    auto font = createGfxFont();

    EXPECT_DOUBLE_EQ(0.0, font->getAscent());

}



TEST_F(GfxFontTest_1146, GetDescent_Default_ReturnsZero_1146) {

    auto font = createGfxFont();

    EXPECT_DOUBLE_EQ(0.0, font->getDescent());

}



TEST_F(GfxFontTest_1146, HasToUnicodeCMap_Default_ReturnsFalse_1146) {

    auto font = createGfxFont();

    EXPECT_FALSE(font->hasToUnicodeCMap());

}



TEST_F(GfxFontTest_1146, GetEncodingName_Default_ReturnsEmptyString_1146) {

    auto font = createGfxFont();

    EXPECT_EQ("", font->getEncodingName());

}
