#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLUtilTest_169 : public ::testing::Test {

protected:

    char buffer[50];

};



TEST_F(XMLUtilTest_169, ToStr_DoubleNormalOperation_169) {

    double value = 3.14159;

    XMLUtil::ToStr(value, buffer, sizeof(buffer));

    EXPECT_STREQ("3.14159", buffer);

}



TEST_F(XMLUtilTest_169, ToStr_DoubleBoundaryCondition_Zero_169) {

    double value = 0.0;

    XMLUtil::ToStr(value, buffer, sizeof(buffer));

    EXPECT_STREQ("0", buffer);

}



TEST_F(XMLUtilTest_169, ToStr_DoubleBoundaryCondition_MaxPositive_169) {

    double value = DBL_MAX;

    XMLUtil::ToStr(value, buffer, sizeof(buffer));

    // The exact string representation of DBL_MAX can vary, but it should be a valid number

    EXPECT_TRUE(std::stod(buffer) == DBL_MAX);

}



TEST_F(XMLUtilTest_169, ToStr_DoubleBoundaryCondition_MaxNegative_169) {

    double value = -DBL_MAX;

    XMLUtil::ToStr(value, buffer, sizeof(buffer));

    // The exact string representation of -DBL_MAX can vary, but it should be a valid number

    EXPECT_TRUE(std::stod(buffer) == -DBL_MAX);

}



TEST_F(XMLUtilTest_169, ToStr_DoubleBoundaryCondition_Epsilon_169) {

    double value = DBL_EPSILON;

    XMLUtil::ToStr(value, buffer, sizeof(buffer));

    // The exact string representation of DBL_EPSILON can vary, but it should be a valid number

    EXPECT_TRUE(std::stod(buffer) == DBL_EPSILON);

}



TEST_F(XMLUtilTest_169, ToStr_DoubleErrorCase_BufferTooSmall_169) {

    double value = 3.14159;

    XMLUtil::ToStr(value, buffer, 2); // Buffer size too small to hold the result

    EXPECT_STRNE("3.14159", buffer);

}
