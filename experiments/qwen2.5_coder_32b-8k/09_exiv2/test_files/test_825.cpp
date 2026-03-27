#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"

#include <string>



using namespace Exiv2;

using testing::Eq;



class CommentValueTest_825 : public ::testing::Test {

protected:

    CommentValue commentValue;

};



TEST_F(CommentValueTest_825, DetectCharset_UTF8_BOM_825) {

    std::string c = "\xef\xbb\xbfHello, World!";

    EXPECT_STREQ(commentValue.detectCharset(c), "UTF-8");

    EXPECT_EQ(c, "Hello, World!");

}



TEST_F(CommentValueTest_825, DetectCharset_UCS2LE_BOM_825) {

    std::string c = "\xff\xfeH\0e\0l\0l\0o\0,\0 \0W\0o\0r\0l\0d\0!";

    EXPECT_STREQ(commentValue.detectCharset(c), "UCS-2LE");

    EXPECT_EQ(c, "H\0e\0l\0l\0o\0,\0 \0W\0o\0r\0l\0d\0!");

}



TEST_F(CommentValueTest_825, DetectCharset_UCS2BE_BOM_825) {

    std::string c = "\xfe\xffH\0e\0l\0l\0o\0,\0 \0W\0o\0r\0l\0d\0!";

    EXPECT_STREQ(commentValue.detectCharset(c), "UCS-2BE");

    EXPECT_EQ(c, "H\0e\0l\0l\0o\0,\0 \0W\0o\0r\0l\0d\0!");

}



TEST_F(CommentValueTest_825, DetectCharset_Default_LittleEndian_825) {

    std::string c = "Hello, World!";

    commentValue.byteOrder_ = littleEndian;

    EXPECT_STREQ(commentValue.detectCharset(c), "UCS-2LE");

    EXPECT_EQ(c, "Hello, World!");

}



TEST_F(CommentValueTest_825, DetectCharset_Default_BigEndian_825) {

    std::string c = "Hello, World!";

    commentValue.byteOrder_ = bigEndian;

    EXPECT_STREQ(commentValue.detectCharset(c), "UCS-2BE");

    EXPECT_EQ(c, "Hello, World!");

}



TEST_F(CommentValueTest_825, DetectCharset_EmptyString_825) {

    std::string c = "";

    commentValue.byteOrder_ = littleEndian;

    EXPECT_STREQ(commentValue.detectCharset(c), "UCS-2LE");

    EXPECT_EQ(c, "");

}



TEST_F(CommentValueTest_825, DetectCharset_ShortUTF8BOM_825) {

    std::string c = "\xef\xbb";

    commentValue.byteOrder_ = littleEndian;

    EXPECT_STREQ(commentValue.detectCharset(c), "UCS-2LE");

    EXPECT_EQ(c, "\xef\xbb");

}



TEST_F(CommentValueTest_825, DetectCharset_ShortUCS2LEBOM_825) {

    std::string c = "\xff";

    commentValue.byteOrder_ = littleEndian;

    EXPECT_STREQ(commentValue.detectCharset(c), "UCS-2LE");

    EXPECT_EQ(c, "\xff");

}



TEST_F(CommentValueTest_825, DetectCharset_ShortUCS2BEBOM_825) {

    std::string c = "\xfe";

    commentValue.byteOrder_ = littleEndian;

    EXPECT_STREQ(commentValue.detectCharset(c), "UCS-2LE");

    EXPECT_EQ(c, "\xfe");

}
