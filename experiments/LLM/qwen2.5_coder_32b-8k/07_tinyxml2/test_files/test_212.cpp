#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLAttributeTest : public ::testing::Test {

protected:

    XMLAttribute xmlAttr;

    unsigned int value;



    void SetValue(const char* val) {

        const_cast<char*>(xmlAttr.Value()) = val;

    }

};



TEST_F(XMLAttributeTest_212, QueryUnsignedValue_Success_212) {

    SetValue("42");

    EXPECT_EQ(xmlAttr.QueryUnsignedValue(&value), XML_SUCCESS);

    EXPECT_EQ(value, 42U);

}



TEST_F(XMLAttributeTest_212, QueryUnsignedValue_Zero_212) {

    SetValue("0");

    EXPECT_EQ(xmlAttr.QueryUnsignedValue(&value), XML_SUCCESS);

    EXPECT_EQ(value, 0U);

}



TEST_F(XMLAttributeTest_212, QueryUnsignedValue_MaxUint_212) {

    SetValue(std::to_string(UINT_MAX).c_str());

    EXPECT_EQ(xmlAttr.QueryUnsignedValue(&value), XML_SUCCESS);

    EXPECT_EQ(value, UINT_MAX);

}



TEST_F(XMLAttributeTest_212, QueryUnsignedValue_NegativeNumber_212) {

    SetValue("-42");

    EXPECT_EQ(xmlAttr.QueryUnsignedValue(&value), XML_WRONG_ATTRIBUTE_TYPE);

}



TEST_F(XMLAttributeTest_212, QueryUnsignedValue_InvalidString_212) {

    SetValue("abc");

    EXPECT_EQ(xmlAttr.QueryUnsignedValue(&value), XML_WRONG_ATTRIBUTE_TYPE);

}



TEST_F(XMLAttributeTest_212, QueryUnsignedValue_EmptyString_212) {

    SetValue("");

    EXPECT_EQ(xmlAttr.QueryUnsignedValue(&value), XML_WRONG_ATTRIBUTE_TYPE);

}
