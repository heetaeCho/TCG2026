#include <gtest/gtest.h>

#include "exiv2/value.hpp"



namespace Exiv2 {

    class CommentValueTest : public ::testing::Test {

    protected:

        CommentValue::CharsetInfo charsetInfo;

    };

}



TEST_F(CommentValueTest_816, CodeForAscii_816) {

    EXPECT_STREQ("ASCII", charsetInfo.code(Exiv2::CommentValue::ascii));

}



TEST_F(CommentValueTest_816, CodeForJis_816) {

    EXPECT_STREQ("JIS", charsetInfo.code(Exiv2::CommentValue::jis));

}



TEST_F(CommentValueTest_816, CodeForUnicode_816) {

    EXPECT_STREQ("UNICODE", charsetInfo.code(Exiv2::CommentValue::unicode));

}



TEST_F(CommentValueTest_816, CodeForUndefined_816) {

    EXPECT_STREQ("", charsetInfo.code(Exiv2::CommentValue::undefined));

}



TEST_F(CommentValueTest_816, CodeForInvalidCharsetId_816) {

    EXPECT_STREQ("", charsetInfo.code(Exiv2::CommentValue::invalidCharsetId));

}



TEST_F(CommentValueTest_816, CodeForLastCharsetId_816) {

    EXPECT_STREQ("", charsetInfo.code(Exiv2::CommentValue::lastCharsetId));

}



TEST_F(CommentValueTest_816, CodeForOutofBoundsId_816) {

    EXPECT_STREQ("", charsetInfo.code(static_cast<Exiv2::CommentValue::CharsetId>(Exiv2::CommentValue::lastCharsetId + 1)));

}
