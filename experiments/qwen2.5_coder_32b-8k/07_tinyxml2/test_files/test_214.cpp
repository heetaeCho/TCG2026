#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLAttributeTest_214 : public ::testing::Test {

protected:

    XMLAttribute* attr;

    

    virtual void SetUp() {

        attr = new XMLAttribute();

    }



    virtual void TearDown() {

        delete attr;

    }

};



TEST_F(XMLAttributeTest_214, QueryUnsigned64Value_Success_214) {

    const char* valueStr = "123456789012345";

    uint64_t expectedValue = 123456789012345;

    attr->SetAttribute(valueStr);

    

    uint64_t outValue;

    XMLError result = attr->QueryUnsigned64Value(&outValue);

    

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_EQ(outValue, expectedValue);

}



TEST_F(XMLAttributeTest_214, QueryUnsigned64Value_Zero_214) {

    const char* valueStr = "0";

    uint64_t expectedValue = 0;

    attr->SetAttribute(valueStr);

    

    uint64_t outValue;

    XMLError result = attr->QueryUnsigned64Value(&outValue);

    

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_EQ(outValue, expectedValue);

}



TEST_F(XMLAttributeTest_214, QueryUnsigned64Value_MaxUint64_214) {

    const char* valueStr = "18446744073709551615"; // Maximum uint64_t value

    uint64_t expectedValue = 18446744073709551615;

    attr->SetAttribute(valueStr);

    

    uint64_t outValue;

    XMLError result = attr->QueryUnsigned64Value(&outValue);

    

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_EQ(outValue, expectedValue);

}



TEST_F(XMLAttributeTest_214, QueryUnsigned64Value_NegativeNumber_Error_214) {

    const char* valueStr = "-1";

    attr->SetAttribute(valueStr);

    

    uint64_t outValue;

    XMLError result = attr->QueryUnsigned64Value(&outValue);

    

    EXPECT_EQ(result, XML_WRONG_ATTRIBUTE_TYPE);

}



TEST_F(XMLAttributeTest_214, QueryUnsigned64Value_NonNumericString_Error_214) {

    const char* valueStr = "abc";

    attr->SetAttribute(valueStr);

    

    uint64_t outValue;

    XMLError result = attr->QueryUnsigned64Value(&outValue);

    

    EXPECT_EQ(result, XML_WRONG_ATTRIBUTE_TYPE);

}



TEST_F(XMLAttributeTest_214, QueryUnsigned64Value_EmptyString_Error_214) {

    const char* valueStr = "";

    attr->SetAttribute(valueStr);

    

    uint64_t outValue;

    XMLError result = attr->QueryUnsigned64Value(&outValue);

    

    EXPECT_EQ(result, XML_WRONG_ATTRIBUTE_TYPE);

}
