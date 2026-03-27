#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



class CharsetInfoTest : public ::testing::Test {

protected:

    CommentValue::CharsetInfo charsetInfo;

};



TEST_F(CharsetInfoTest_818, charsetIdByCode_Ascii_818) {

    EXPECT_EQ(charsetIdByName("ASCII"), charsetInfo.charsetIdByCode("ASCII     "));

}



TEST_F(CharsetInfoTest_818, charsetIdByCode_Jis_818) {

    EXPECT_EQ(charsetIdByName("JIS"), charsetInfo.charsetIdByCode("JIS       "));

}



TEST_F(CharsetInfoTest_818, charsetIdByCode_Unicode_818) {

    EXPECT_EQ(charsetIdByName("UNICODE"), charsetInfo.charsetIdByCode("UNICODE   "));

}



TEST_F(CharsetInfoTest_818, charsetIdByCode_Undefined_818) {

    EXPECT_EQ(charsetIdByName("UNDEFINED"), charsetInfo.charsetIdByCode("UNDEFINED "));

}



TEST_F(CharsetInfoTest_818, charsetIdByCode_InvalidCharsetId_818) {

    EXPECT_EQ(CommentValue::invalidCharsetId, charsetInfo.charsetIdByCode("INVALID   "));

}



TEST_F(CharsetInfoTest_818, charsetIdByCode_EmptyString_818) {

    EXPECT_EQ(CommentValue::invalidCharsetId, charsetInfo.charsetIdByCode(""));

}



TEST_F(CharsetInfoTest_818, charsetIdByCode_ShortString_818) {

    EXPECT_EQ(CommentValue::invalidCharsetId, charsetInfo.charsetIdByCode("ASCII"));

}



TEST_F(CharsetInfoTest_818, charsetIdByCode_LongString_818) {

    EXPECT_EQ(CommentValue::invalidCharsetId, charsetInfo.charsetIdByCode("TOOLONGCODE "));

}
