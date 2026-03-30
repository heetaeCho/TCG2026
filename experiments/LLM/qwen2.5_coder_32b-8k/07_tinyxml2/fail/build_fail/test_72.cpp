#include <gtest/gtest.h>

#include "tinyxml2/tinyxml2.h"



using namespace tinyxml2;



class XMLAttributeTest_72 : public ::testing::Test {

protected:

    XMLAttribute attr;

};



TEST_F(XMLAttributeTest_72, Int64Value_ReturnsDefault_72) {

    int64_t value = attr.Int64Value();

    EXPECT_EQ(value, 0);

}



TEST_F(XMLAttributeTest_72, QueryInt64Value_Success_72) {

    int64_t expectedValue = 12345;

    XMLError result = attr.QueryInt64Value(&expectedValue);

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_EQ(attr.Int64Value(), expectedValue);

}



TEST_F(XMLAttributeTest_72, QueryInt64Value_Failure_72) {

    int64_t value = 0;

    XMLError result = attr.QueryInt64Value(&value);

    EXPECT_EQ(result, XML_WRONG_ATTRIBUTE_TYPE);

}



TEST_F(XMLAttributeTest_72, SetAttribute_Int64_Success_72) {

    int64_t expectedValue = 98765;

    attr.SetAttribute(expectedValue);

    EXPECT_EQ(attr.Int64Value(), expectedValue);

}



TEST_F(XMLAttributeTest_72, GetLineNum_Default_72) {

    int lineNum = attr.GetLineNum();

    EXPECT_EQ(lineNum, 0);

}



TEST_F(XMLAttributeTest_72, Next_ReturnsNullptr_72) {

    const XMLAttribute* nextAttr = attr.Next();

    EXPECT_EQ(nextAttr, nullptr);

}



TEST_F(XMLAttributeTest_72, Name_Default_72) {

    const char* name = attr.Name();

    EXPECT_STREQ(name, "");

}



TEST_F(XMLAttributeTest_72, Value_Default_72) {

    const char* value = attr.Value();

    EXPECT_STREQ(value, "");

}
