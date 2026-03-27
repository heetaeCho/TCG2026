#include <gtest/gtest.h>

#include <exiv2/value.hpp>



using namespace Exiv2::CommentValue;



class CharsetInfoTest : public ::testing::Test {

protected:

    CharsetInfo charsetInfo;

};



TEST_F(CharsetInfoTest_ValidCharsetId_815, NameReturnsCorrectStringForAscii_815) {

    EXPECT_STREQ(charsetInfo.name(ascii), "ASCII");

}



TEST_F(CharsetInfoTest_ValidCharsetId_815, NameReturnsCorrectStringForJis_815) {

    EXPECT_STREQ(charsetInfo.name(jis), "JIS");

}



TEST_F(CharsetInfoTest_ValidCharsetId_815, NameReturnsCorrectStringForUnicode_815) {

    EXPECT_STREQ(charsetInfo.name(unicode), "UNICODE");

}



TEST_F(CharsetInfoTest_UndefinedCharsetId_815, NameReturnsUndefinedForUndefinedId_815) {

    EXPECT_STREQ(charsetInfo.name(undefined), "undefined");

}



TEST_F(CharsetInfoTest_OutOfBoundsCharsetId_815, NameReturnsUndefinedForInvalidId_815) {

    EXPECT_STREQ(charsetInfo.name(invalidCharsetId), "undefined");

}



TEST_F(CharsetInfoTest_OutOfBoundsCharsetId_815, NameReturnsUndefinedForLastIdPlusOne_815) {

    EXPECT_STREQ(charsetInfo.name(static_cast<CharsetId>(lastCharsetId + 1)), "undefined");

}
