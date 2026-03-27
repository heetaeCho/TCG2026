#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLAttributeTest_221 : public ::testing::Test {

protected:

    XMLAttribute attr;

};



TEST_F(XMLAttributeTest_221, SetAttribute_NormalOperation_221) {

    int64_t testValue = 123456789012345;

    attr.SetAttribute(testValue);

    EXPECT_STREQ(attr.Value(), "123456789012345");

}



TEST_F(XMLAttributeTest_221, SetAttribute_BoundaryCondition_Zero_221) {

    int64_t testValue = 0;

    attr.SetAttribute(testValue);

    EXPECT_STREQ(attr.Value(), "0");

}



TEST_F(XMLAttributeTest_221, SetAttribute_BoundaryCondition_MaxInt64_221) {

    int64_t testValue = INT64_MAX;

    attr.SetAttribute(testValue);

    EXPECT_STREQ(attr.Value(), "9223372036854775807");

}



TEST_F(XMLAttributeTest_221, SetAttribute_BoundaryCondition_MinInt64_221) {

    int64_t testValue = INT64_MIN;

    attr.SetAttribute(testValue);

    EXPECT_STREQ(attr.Value(), "-9223372036854775808");

}



TEST_F(XMLAttributeTest_221, SetAttribute_NegativeValue_221) {

    int64_t testValue = -12345;

    attr.SetAttribute(testValue);

    EXPECT_STREQ(attr.Value(), "-12345");

}
