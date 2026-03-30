#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLUtilTest_166 : public ::testing::Test {

protected:

    XMLUtil xmlUtil;

};



TEST_F(XMLUtilTest_166, ToStr_Unsigned_Normal_166) {

    char buffer[10];

    unsigned v = 12345;

    xmlUtil.ToStr(v, buffer, sizeof(buffer));

    EXPECT_STREQ("12345", buffer);

}



TEST_F(XMLUtilTest_166, ToStr_Unsigned_Zero_166) {

    char buffer[10];

    unsigned v = 0;

    xmlUtil.ToStr(v, buffer, sizeof(buffer));

    EXPECT_STREQ("0", buffer);

}



TEST_F(XMLUtilTest_166, ToStr_Unsigned_Boundary_MaxValue_166) {

    char buffer[20];

    unsigned v = UINT_MAX;

    xmlUtil.ToStr(v, buffer, sizeof(buffer));

    EXPECT_STREQ("4294967295", buffer);

}



TEST_F(XMLUtilTest_166, ToStr_Unsigned_BufferTooSmall_166) {

    char buffer[2];

    unsigned v = 123;

    xmlUtil.ToStr(v, buffer, sizeof(buffer));

    EXPECT_STRNE("123", buffer); // The buffer is too small to hold the result

}



TEST_F(XMLUtilTest_166, ToStr_Unsigned_BufferSizeOne_166) {

    char buffer[1];

    unsigned v = 0;

    xmlUtil.ToStr(v, buffer, sizeof(buffer));

    EXPECT_STREQ("", buffer); // The buffer is too small to hold even the null terminator

}



TEST_F(XMLUtilTest_166, ToStr_Unsigned_BufferJustRight_166) {

    char buffer[12]; // "4294967295" has 10 characters + 1 for null terminator = 11

    unsigned v = UINT_MAX;

    xmlUtil.ToStr(v, buffer, sizeof(buffer));

    EXPECT_STREQ("4294967295", buffer);

}



TEST_F(XMLUtilTest_166, ToStr_Unsigned_BufferSizeZero_166) {

    char buffer[1];

    unsigned v = 0;

    xmlUtil.ToStr(v, buffer, 0);

    EXPECT_STREQ("", buffer); // No space to write anything

}
