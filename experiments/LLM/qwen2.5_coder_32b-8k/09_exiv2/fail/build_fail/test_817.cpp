#include <gtest/gtest.h>

#include "exiv2/value.hpp"



namespace Exiv2 {

class CommentValueTest : public ::testing::Test {

protected:

    CommentValue::CharsetInfo charsetInfo;

};



TEST_F(CommentValueTest_817, KnownCharsetByName_817) {

    EXPECT_EQ(charsetInfo.charsetIdByName("ascii"),   CommentValue::ascii);

    EXPECT_EQ(charsetInfo.charsetIdByName("jis"),     CommentValue::jis);

    EXPECT_EQ(charsetInfo.charsetIdByName("unicode"), CommentValue::unicode);

}



TEST_F(CommentValueTest_817, UnknownCharsetByNameReturnsInvalid_817) {

    EXPECT_EQ(charsetInfo.charsetIdByName("unknown"), CommentValue::invalidCharsetId);

}



TEST_F(CommentValueTest_817, BoundaryConditionEmptyString_817) {

    EXPECT_EQ(charsetInfo.charsetIdByName(""), CommentValue::invalidCharsetId);

}



TEST_F(CommentValueTest_817, BoundaryConditionLastCharset_817) {

    EXPECT_EQ(charsetInfo.charsetIdByName("last"), CommentValue::invalidCharsetId);

}



} // namespace Exiv2
