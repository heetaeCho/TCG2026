#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxFont.cc"

#include "Error.h"



namespace {



class GfxFontTest_1970 : public ::testing::Test {

protected:

    Unicode uBuf[2];

};



TEST_F(GfxFontTest_1970, ZeroLengthOutputBuffer_1970) {

    EXPECT_EQ(parseCharName("test", uBuf, 0, false, false, false, false, false), 0);

}



TEST_F(GfxFontTest_1970, VariantsDotNotdef_1970) {

    EXPECT_EQ(parseCharName(".notdef", uBuf, 2, false, false, false, false, true), 0);

}



TEST_F(GfxFontTest_1970, LigaturesSingleComponent_1970) {

    EXPECT_EQ(parseCharName("a", uBuf, 2, false, true, false, false, false), 0);

}



TEST_F(GfxFontTest_1970, LigaturesMultipleComponents_1970) {

    EXPECT_EQ(parseCharName("a_b_c", uBuf, 3, false, true, false, false, false), 0);

}



TEST_F(GfxFontTest_1970, NamesMappingSuccess_1970) {

    // Assuming globalParams->mapNameToUnicodeText("test") returns a valid Unicode value

    EXPECT_EQ(parseCharName("test", uBuf, 2, true, false, false, false, false), 1);

}



TEST_F(GfxFontTest_1970, NamesMappingFailure_1970) {

    // Assuming globalParams->mapNameToUnicodeText("unknown") returns 0

    EXPECT_EQ(parseCharName("unknown", uBuf, 2, true, false, false, false, false), 0);

}



TEST_F(GfxFontTest_1970, UnicodeHexStringValid_1970) {

    EXPECT_EQ(parseCharName("uni0041 uni0061", uBuf, 2, false, false, false, false, false), 2);

}



TEST_F(GfxFontTest_1970, UnicodeHexStringInvalid_1970) {

    EXPECT_EQ(parseCharName("uni004G", uBuf, 2, false, false, false, false, false), 0);

}



TEST_F(GfxFontTest_1970, UnicodeShortHexValid_1970) {

    EXPECT_EQ(parseCharName("u0041", uBuf, 2, false, false, true, false, false), 1);

}



TEST_F(GfxFontTest_1970, UnicodeShortHexInvalid_1970) {

    EXPECT_EQ(parseCharName("uG041", uBuf, 2, false, false, true, false, false), 0);

}



TEST_F(GfxFontTest_1970, NumericNameSuccess_1970) {

    // Assuming parseNumericName can parse and returns valid Unicode value

    EXPECT_EQ(parseCharName("numeric_name", uBuf, 2, false, false, true, false, false), 1);

}



TEST_F(GfxFontTest_1970, NumericNameFailure_1970) {

    // Assuming parseNumericName cannot parse and returns 0

    EXPECT_EQ(parseCharName("invalid_numeric", uBuf, 2, false, false, true, false, false), 0);

}



}  // namespace
