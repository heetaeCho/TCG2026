#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLUtilTest_165 : public ::testing::Test {

protected:

    XMLUtil xmlUtil;

};



TEST_F(XMLUtilTest_165, ToStr_Int_NormalOperation_165) {

    char buffer[10];

    int value = 12345;

    xmlUtil.ToStr(value, buffer, sizeof(buffer));

    EXPECT_STREQ("12345", buffer);

}



TEST_F(XMLUtilTest_165, ToStr_Int_BoundaryCondition_Zero_165) {

    char buffer[10];

    int value = 0;

    xmlUtil.ToStr(value, buffer, sizeof(buffer));

    EXPECT_STREQ("0", buffer);

}



TEST_F(XMLUtilTest_165, ToStr_Int_BoundaryCondition_MaxInt_165) {

    char buffer[20];

    int value = INT_MAX;

    xmlUtil.ToStr(value, buffer, sizeof(buffer));

    EXPECT_STREQ("2147483647", buffer);

}



TEST_F(XMLUtilTest_165, ToStr_Int_BoundaryCondition_MinInt_165) {

    char buffer[20];

    int value = INT_MIN;

    xmlUtil.ToStr(value, buffer, sizeof(buffer));

    EXPECT_STREQ("-2147483648", buffer);

}



TEST_F(XMLUtilTest_165, ToStr_Int_ErrorCase_BufferTooSmall_165) {

    char buffer[5];

    int value = 12345;

    xmlUtil.ToStr(value, buffer, sizeof(buffer));

    // Buffer too small to hold the full number, expect truncated result.

    EXPECT_STRNE("12345", buffer);

}



TEST_F(XMLUtilTest_165, ToStr_UInt_NormalOperation_165) {

    char buffer[10];

    unsigned int value = 6789;

    xmlUtil.ToStr(value, buffer, sizeof(buffer));

    EXPECT_STREQ("6789", buffer);

}



TEST_F(XMLUtilTest_165, ToStr_UInt_BoundaryCondition_Zero_165) {

    char buffer[10];

    unsigned int value = 0;

    xmlUtil.ToStr(value, buffer, sizeof(buffer));

    EXPECT_STREQ("0", buffer);

}



TEST_F(XMLUtilTest_165, ToStr_UInt_BoundaryCondition_MaxUInt_165) {

    char buffer[20];

    unsigned int value = UINT_MAX;

    xmlUtil.ToStr(value, buffer, sizeof(buffer));

    EXPECT_STREQ("4294967295", buffer);

}



TEST_F(XMLUtilTest_165, ToStr_UInt_ErrorCase_BufferTooSmall_165) {

    char buffer[5];

    unsigned int value = 12345;

    xmlUtil.ToStr(value, buffer, sizeof(buffer));

    // Buffer too small to hold the full number, expect truncated result.

    EXPECT_STRNE("12345", buffer);

}



TEST_F(XMLUtilTest_165, ToStr_Bool_NormalOperation_True_165) {

    char buffer[10];

    bool value = true;

    xmlUtil.ToStr(value, buffer, sizeof(buffer));

    EXPECT_STREQ("true", buffer);

}



TEST_F(XMLUtilTest_165, ToStr_Bool_NormalOperation_False_165) {

    char buffer[10];

    bool value = false;

    xmlUtil.ToStr(value, buffer, sizeof(buffer));

    EXPECT_STREQ("false", buffer);

}



TEST_F(XMLUtilTest_165, ToStr_Float_NormalOperation_165) {

    char buffer[20];

    float value = 3.14159f;

    xmlUtil.ToStr(value, buffer, sizeof(buffer));

    // Floating point representation can vary slightly.

    EXPECT_TRUE(std::string(buffer).find("3.14159") != std::string::npos);

}



TEST_F(XMLUtilTest_165, ToStr_Float_BoundaryCondition_Zero_165) {

    char buffer[10];

    float value = 0.0f;

    xmlUtil.ToStr(value, buffer, sizeof(buffer));

    EXPECT_STREQ("0", buffer);

}



TEST_F(XMLUtilTest_165, ToStr_Float_ErrorCase_BufferTooSmall_165) {

    char buffer[5];

    float value = 3.14159f;

    xmlUtil.ToStr(value, buffer, sizeof(buffer));

    // Buffer too small to hold the full number, expect truncated result.

    EXPECT_STRNE("3.14159", buffer);

}



TEST_F(XMLUtilTest_165, ToStr_Double_NormalOperation_165) {

    char buffer[20];

    double value = 3.141592653589793;

    xmlUtil.ToStr(value, buffer, sizeof(buffer));

    // Floating point representation can vary slightly.

    EXPECT_TRUE(std::string(buffer).find("3.14159") != std::string::npos);

}



TEST_F(XMLUtilTest_165, ToStr_Double_BoundaryCondition_Zero_165) {

    char buffer[10];

    double value = 0.0;

    xmlUtil.ToStr(value, buffer, sizeof(buffer));

    EXPECT_STREQ("0", buffer);

}



TEST_F(XMLUtilTest_165, ToStr_Double_ErrorCase_BufferTooSmall_165) {

    char buffer[5];

    double value = 3.141592653589793;

    xmlUtil.ToStr(value, buffer, sizeof(buffer));

    // Buffer too small to hold the full number, expect truncated result.

    EXPECT_STRNE("3.14159", buffer);

}



TEST_F(XMLUtilTest_165, ToStr_Int64_NormalOperation_165) {

    char buffer[25];

    int64_t value = 9223372036854775807LL;

    xmlUtil.ToStr(value, buffer, sizeof(buffer));

    EXPECT_STREQ("9223372036854775807", buffer);

}



TEST_F(XMLUtilTest_165, ToStr_Int64_BoundaryCondition_Zero_165) {

    char buffer[10];

    int64_t value = 0;

    xmlUtil.ToStr(value, buffer, sizeof(buffer));

    EXPECT_STREQ("0", buffer);

}



TEST_F(XMLUtilTest_165, ToStr_Int64_ErrorCase_BufferTooSmall_165) {

    char buffer[20];

    int64_t value = 9223372036854775807LL;

    xmlUtil.ToStr(value, buffer, sizeof(buffer));

    // Buffer too small to hold the full number, expect truncated result.

    EXPECT_STRNE("9223372036854775807", buffer);

}



TEST_F(XMLUtilTest_165, ToStr_UInt64_NormalOperation_165) {

    char buffer[25];

    uint64_t value = 18446744073709551615ULL;

    xmlUtil.ToStr(value, buffer, sizeof(buffer));

    EXPECT_STREQ("18446744073709551615", buffer);

}



TEST_F(XMLUtilTest_165, ToStr_UInt64_BoundaryCondition_Zero_165) {

    char buffer[10];

    uint64_t value = 0;

    xmlUtil.ToStr(value, buffer, sizeof(buffer));

    EXPECT_STREQ("0", buffer);

}



TEST_F(XMLUtilTest_165, ToStr_UInt64_ErrorCase_BufferTooSmall_165) {

    char buffer[20];

    uint64_t value = 18446744073709551615ULL;

    xmlUtil.ToStr(value, buffer, sizeof(buffer));

    // Buffer too small to hold the full number, expect truncated result.

    EXPECT_STRNE("18446744073709551615", buffer);

}
