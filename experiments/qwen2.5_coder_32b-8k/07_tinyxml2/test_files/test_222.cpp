#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLAttributeTest : public ::testing::Test {

protected:

    XMLAttribute xmlAttribute;

};



TEST_F(XMLAttributeTest_222, SetAttribute_Uint64_NormalOperation_222) {

    uint64_t testValue = 123456789012345;

    xmlAttribute.SetAttribute(testValue);

    

    const char* valueStr = xmlAttribute.Value();

    EXPECT_STREQ(valueStr, "123456789012345");

}



TEST_F(XMLAttributeTest_222, SetAttribute_Uint64_BoundaryCondition_MaxUint64_222) {

    uint64_t testValue = UINT64_MAX;

    xmlAttribute.SetAttribute(testValue);

    

    const char* valueStr = xmlAttribute.Value();

    EXPECT_STREQ(valueStr, "18446744073709551615");

}



TEST_F(XMLAttributeTest_222, SetAttribute_Uint64_BoundaryCondition_Zero_222) {

    uint64_t testValue = 0;

    xmlAttribute.SetAttribute(testValue);

    

    const char* valueStr = xmlAttribute.Value();

    EXPECT_STREQ(valueStr, "0");

}



TEST_F(XMLAttributeTest_222, SetAttribute_Uint64_BoundaryCondition_One_222) {

    uint64_t testValue = 1;

    xmlAttribute.SetAttribute(testValue);

    

    const char* valueStr = xmlAttribute.Value();

    EXPECT_STREQ(valueStr, "1");

}
