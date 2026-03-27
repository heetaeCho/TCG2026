#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLUtilTest_170 : public ::testing::Test {

protected:

    XMLUtil xmlUtil;

};



TEST_F(XMLUtilTest_170, ToStr_Int64_NormalOperation_170) {

    char buffer[20];

    int bufferSize = sizeof(buffer);

    int64_t value = 123456789012345LL;

    xmlUtil.ToStr(value, buffer, bufferSize);

    EXPECT_STREQ("123456789012345", buffer);

}



TEST_F(XMLUtilTest_170, ToStr_Int64_ZeroValue_170) {

    char buffer[20];

    int bufferSize = sizeof(buffer);

    int64_t value = 0LL;

    xmlUtil.ToStr(value, buffer, bufferSize);

    EXPECT_STREQ("0", buffer);

}



TEST_F(XMLUtilTest_170, ToStr_Int64_NegativeValue_170) {

    char buffer[20];

    int bufferSize = sizeof(buffer);

    int64_t value = -987654321LL;

    xmlUtil.ToStr(value, buffer, bufferSize);

    EXPECT_STREQ("-987654321", buffer);

}



TEST_F(XMLUtilTest_170, ToStr_Int64_BufferSizeTooSmall_170) {

    char buffer[5];

    int bufferSize = sizeof(buffer);

    int64_t value = 1234567890LL;

    xmlUtil.ToStr(value, buffer, bufferSize);

    EXPECT_STREQ("1234", buffer); // Buffer is too small to hold the full number

}



TEST_F(XMLUtilTest_170, ToStr_Int64_MaxValue_170) {

    char buffer[25];

    int bufferSize = sizeof(buffer);

    int64_t value = INT64_MAX;

    xmlUtil.ToStr(value, buffer, bufferSize);

    EXPECT_STREQ("9223372036854775807", buffer);

}



TEST_F(XMLUtilTest_170, ToStr_Int64_MinValue_170) {

    char buffer[25];

    int bufferSize = sizeof(buffer);

    int64_t value = INT64_MIN;

    xmlUtil.ToStr(value, buffer, bufferSize);

    EXPECT_STREQ("-9223372036854775808", buffer);

}
