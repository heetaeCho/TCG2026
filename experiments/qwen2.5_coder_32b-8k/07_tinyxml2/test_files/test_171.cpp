#include <gtest/gtest.h>

#include "tinyxml2.h"



namespace tinyxml2 {



class XMLUtilTest : public ::testing::Test {

protected:

    char buffer[32];

};



TEST_F(XMLUtilTest_171, ToStr_Uint64_NormalOperation_171) {

    uint64_t value = 1234567890ULL;

    XMLUtil::ToStr(value, buffer, sizeof(buffer));

    EXPECT_STREQ(buffer, "1234567890");

}



TEST_F(XMLUtilTest_171, ToStr_Uint64_ZeroValue_171) {

    uint64_t value = 0ULL;

    XMLUtil::ToStr(value, buffer, sizeof(buffer));

    EXPECT_STREQ(buffer, "0");

}



TEST_F(XMLUtilTest_171, ToStr_Uint64_MaxValue_171) {

    uint64_t value = UINT64_MAX;

    XMLUtil::ToStr(value, buffer, sizeof(buffer));

    EXPECT_STREQ(buffer, "18446744073709551615");

}



TEST_F(XMLUtilTest_171, ToStr_Uint64_BufferTooSmall_171) {

    uint64_t value = 1234567890ULL;

    XMLUtil::ToStr(value, buffer, 2); // Buffer can't hold the full number

    EXPECT_STRNE(buffer, "1234567890");

}



TEST_F(XMLUtilTest_171, ToStr_Uint64_BufferJustRight_171) {

    uint64_t value = 1234567890ULL;

    XMLUtil::ToStr(value, buffer, 11); // Buffer can hold the number and null terminator

    EXPECT_STREQ(buffer, "1234567890");

}



} // namespace tinyxml2
