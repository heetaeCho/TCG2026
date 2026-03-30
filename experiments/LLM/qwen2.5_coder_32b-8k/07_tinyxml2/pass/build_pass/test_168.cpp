#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLUtilTest_168 : public ::testing::Test {

protected:

    XMLUtil util;

};



TEST_F(XMLUtilTest_168, ToStr_Float_NormalOperation_168) {

    char buffer[50];

    util.ToStr(3.1415926f, buffer, sizeof(buffer));

    EXPECT_STREQ("3.14159", buffer);

}



TEST_F(XMLUtilTest_168, ToStr_Float_BoundaryCondition_Zero_168) {

    char buffer[50];

    util.ToStr(0.0f, buffer, sizeof(buffer));

    EXPECT_STREQ("0", buffer);

}



TEST_F(XMLUtilTest_168, ToStr_Float_BoundaryCondition_MaxValue_168) {

    char buffer[50];

    util.ToStr(std::numeric_limits<float>::max(), buffer, sizeof(buffer));

    // The exact string representation can vary, but it should be something like "3.4e+38"

    EXPECT_TRUE(strstr(buffer, "e+38") != nullptr);

}



TEST_F(XMLUtilTest_168, ToStr_Float_BoundaryCondition_MinValue_168) {

    char buffer[50];

    util.ToStr(std::numeric_limits<float>::lowest(), buffer, sizeof(buffer));

    // The exact string representation can vary, but it should be something like "-3.4e+38"

    EXPECT_TRUE(strstr(buffer, "e+38") != nullptr || strstr(buffer, "-3.4e+38") != nullptr);

}



TEST_F(XMLUtilTest_168, ToStr_Float_ErrorCase_BufferTooSmall_168) {

    char buffer[2];

    util.ToStr(3.1415926f, buffer, sizeof(buffer));

    EXPECT_STREQ("", buffer);  // Buffer too small to hold any meaningful output

}



TEST_F(XMLUtilTest_168, ToStr_Float_ErrorCase_NegativeBuffer_168) {

    char buffer[50];

    util.ToStr(-3.1415926f, buffer, sizeof(buffer));

    EXPECT_STREQ("-3.14159", buffer);

}



TEST_F(XMLUtilTest_168, ToStr_Float_ErrorCase_LargeNegativeValue_168) {

    char buffer[50];

    util.ToStr(-std::numeric_limits<float>::max(), buffer, sizeof(buffer));

    // The exact string representation can vary, but it should be something like "-3.4e+38"

    EXPECT_TRUE(strstr(buffer, "-3.4e+38") != nullptr);

}
