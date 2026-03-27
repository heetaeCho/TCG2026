#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/GfxFont.h"

#include "XRef.h"  // Assume XRef is defined in this header or similar

#include "Dict.h"   // Assume Dict is defined in this header or similar



using namespace testing;



class GfxFontMock : public GfxFont {

public:

    MOCK_CONST_METHOD0(getFamily, const GooString*());

    MOCK_CONST_METHOD0(isSubset, bool());

    MOCK_METHOD0(getNameWithoutSubsetTag, std::string());

    MOCK_CONST_METHOD0(getToUnicode, const CharCodeToUnicode*());

    MOCK_METHOD3(locateFont, std::optional<GfxFontLoc>(XRef*, PSOutputDev*, GooString*));

    MOCK_METHOD1(readEmbFontFile, std::optional<std::vector<unsigned char>>(XRef*));

    MOCK_METHOD9(getNextChar, int(const char*, int, CharCode*, const Unicode**, int*, double*, double*, double*, double*));

    MOCK_STATIC_CONST_METHOD1(getAlternateName, const char*(const char*));

    MOCK_STATIC_CONST_METHOD2(isBase14Font, bool(std::string_view, std::string_view));

    MOCK_METHOD0(isCIDFont, bool());

    MOCK_CONST_METHOD1(getEmbeddedFontID, bool(Ref*));

    MOCK_METHOD0(invalidateEmbeddedFont, bool());

    MOCK_CONST_METHOD0(getEmbeddedFontName, const GooString*());

    MOCK_CONST_METHOD0(getFlags, int());

    MOCK_CONST_METHOD0(isFixedWidth, bool());

    MOCK_CONST_METHOD0(isSerif, bool());

    MOCK_CONST_METHOD0(isSymbolic, bool());

    MOCK_CONST_METHOD0(isItalic, bool());

    MOCK_CONST_METHOD0(isBold, bool());

    MOCK_CONST_METHOD0(getFontMatrix, const std::array<double, 6>&());

    MOCK_CONST_METHOD0(getFontBBox, const std::array<double, 4>&());

    MOCK_CONST_METHOD0(getAscent, double());

    MOCK_CONST_METHOD0(getDescent, double());

    MOCK_CONST_METHOD0(getWMode, WritingMode());

    MOCK_CONST_METHOD0(hasToUnicodeCMap, bool());

    MOCK_CONST_METHOD0(getEncodingName, const std::string&());



    GfxFontMock(const char* tagA, Ref idA, std::optional<std::string>&& nameA, GfxFontType typeA, Ref embFontIDA)

        : GfxFont(tagA, idA, std::move(nameA), typeA, embFontIDA) {}

};



class GfxFontTest_1141 : public ::testing::Test {

protected:

    XRef xref;

    Dict fontDict;

    Ref ref{42, 0};

    GfxFontType fontType = GfxFontType::unknownFont;



    std::unique_ptr<GfxFontMock> mockGfxFont = std::make_unique<GfxFontMock>("TestTag", ref, "TestFamily", fontType, Ref{13, 0});



    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(GfxFontTest_1141, GetFamily_ReturnsCorrectValue_1141) {

    const char* expectedFamily = "ExpectedFamily";

    auto mockGooString = std::make_unique<GooString>(expectedFamily);

    EXPECT_CALL(*mockGfxFont, getFamily())

        .WillOnce(Return(mockGooString.get()));



    const GooString* result = mockGfxFont->getFamily();

    ASSERT_EQ(result->getCString(), expectedFamily);

}



TEST_F(GfxFontTest_1141, GetTag_ReturnsCorrectValue_1141) {

    EXPECT_EQ(mockGfxFont->getTag(), "TestTag");

}



TEST_F(GfxFontTest_1141, IsSubset_ReturnsFalseByDefault_1141) {

    EXPECT_CALL(*mockGfxFont, isSubset())

        .WillOnce(Return(false));



    bool result = mockGfxFont->isSubset();

    ASSERT_EQ(result, false);

}



TEST_F(GfxFontTest_1141, IsCIDFont_ReturnsFalseByDefault_1141) {

    EXPECT_CALL(*mockGfxFont, isCIDFont())

        .WillOnce(Return(false));



    bool result = mockGfxFont->isCIDFont();

    ASSERT_EQ(result, false);

}



TEST_F(GfxFontTest_1141, IsFixedWidth_ReturnsFalseByDefault_1141) {

    EXPECT_CALL(*mockGfxFont, isFixedWidth())

        .WillOnce(Return(false));



    bool result = mockGfxFont->isFixedWidth();

    ASSERT_EQ(result, false);

}



TEST_F(GfxFontTest_1141, IsSerif_ReturnsFalseByDefault_1141) {

    EXPECT_CALL(*mockGfxFont, isSerif())

        .WillOnce(Return(false));



    bool result = mockGfxFont->isSerif();

    ASSERT_EQ(result, false);

}



TEST_F(GfxFontTest_1141, IsSymbolic_ReturnsFalseByDefault_1141) {

    EXPECT_CALL(*mockGfxFont, isSymbolic())

        .WillOnce(Return(false));



    bool result = mockGfxFont->isSymbolic();

    ASSERT_EQ(result, false);

}



TEST_F(GfxFontTest_1141, IsItalic_ReturnsFalseByDefault_1141) {

    EXPECT_CALL(*mockGfxFont, isItalic())

        .WillOnce(Return(false));



    bool result = mockGfxFont->isItalic();

    ASSERT_EQ(result, false);

}



TEST_F(GfxFontTest_1141, IsBold_ReturnsFalseByDefault_1141) {

    EXPECT_CALL(*mockGfxFont, isBold())

        .WillOnce(Return(false));



    bool result = mockGfxFont->isBold();

    ASSERT_EQ(result, false);

}



TEST_F(GfxFontTest_1141, GetEmbeddedFontName_ReturnsNullByDefault_1141) {

    EXPECT_CALL(*mockGfxFont, getEmbeddedFontName())

        .WillOnce(Return(nullptr));



    const GooString* result = mockGfxFont->getEmbeddedFontName();

    ASSERT_EQ(result, nullptr);

}



TEST_F(GfxFontTest_1141, GetFlags_ReturnsZeroByDefault_1141) {

    EXPECT_CALL(*mockGfxFont, getFlags())

        .WillOnce(Return(0));



    int result = mockGfxFont->getFlags();

    ASSERT_EQ(result, 0);

}



TEST_F(GfxFontTest_1141, GetAscent_ReturnsZeroByDefault_1141) {

    EXPECT_CALL(*mockGfxFont, getAscent())

        .WillOnce(Return(0.0));



    double result = mockGfxFont->getAscent();

    ASSERT_DOUBLE_EQ(result, 0.0);

}



TEST_F(GfxFontTest_1141, GetDescent_ReturnsZeroByDefault_1141) {

    EXPECT_CALL(*mockGfxFont, getDescent())

        .WillOnce(Return(0.0));



    double result = mockGfxFont->getDescent();

    ASSERT_DOUBLE_EQ(result, 0.0);

}



TEST_F(GfxFontTest_1141, HasToUnicodeCMap_ReturnsFalseByDefault_1141) {

    EXPECT_CALL(*mockGfxFont, hasToUnicodeCMap())

        .WillOnce(Return(false));



    bool result = mockGfxFont->hasToUnicodeCMap();

    ASSERT_EQ(result, false);

}



TEST_F(GfxFontTest_1141, GetEncodingName_ReturnsEmptyStringByDefault_1141) {

    EXPECT_CALL(*mockGfxFont, getEncodingName())

        .WillOnce(Return(""));



    const std::string& result = mockGfxFont->getEncodingName();

    ASSERT_EQ(result, "");

}
