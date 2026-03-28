#include <gtest/gtest.h>

#include "tinyxml2.h"

#include <limits>



using namespace tinyxml2;



class XMLAttributeTest_211 : public ::testing::Test {

protected:

    void SetUp() override {

        xmlAttr = new XMLAttribute();

        xmlAttr->SetValue("123");

    }



    void TearDown() override {

        delete xmlAttr;

    }



    XMLAttribute* xmlAttr;

};



TEST_F(XMLAttributeTest_211, QueryIntValue_Success_211) {

    int value = 0;

    EXPECT_EQ(xmlAttr->QueryIntValue(&value), XML_SUCCESS);

    EXPECT_EQ(value, 123);

}



TEST_F(XMLAttributeTest_211, QueryIntValue_Zero_211) {

    xmlAttr->SetValue("0");

    int value = -1;

    EXPECT_EQ(xmlAttr->QueryIntValue(&value), XML_SUCCESS);

    EXPECT_EQ(value, 0);

}



TEST_F(XMLAttributeTest_211, QueryIntValue_Negative_211) {

    xmlAttr->SetValue("-456");

    int value = 0;

    EXPECT_EQ(xmlAttr->QueryIntValue(&value), XML_SUCCESS);

    EXPECT_EQ(value, -456);

}



TEST_F(XMLAttributeTest_211, QueryIntValue_OutOfRange_211) {

    xmlAttr->SetValue(std::to_string(std::numeric_limits<int>::max()).c_str());

    int value = 0;

    EXPECT_EQ(xmlAttr->QueryIntValue(&value), XML_SUCCESS);

    EXPECT_EQ(value, std::numeric_limits<int>::max());



    xmlAttr->SetValue("2147483648"); // Out of range for signed int

    EXPECT_EQ(xmlAttr->QueryIntValue(&value), XML_WRONG_ATTRIBUTE_TYPE);

}



TEST_F(XMLAttributeTest_211, QueryIntValue_EmptyString_211) {

    xmlAttr->SetValue("");

    int value = 0;

    EXPECT_EQ(xmlAttr->QueryIntValue(&value), XML_WRONG_ATTRIBUTE_TYPE);

}



TEST_F(XMLAttributeTest_211, QueryIntValue_NonNumericString_211) {

    xmlAttr->SetValue("abc");

    int value = 0;

    EXPECT_EQ(xmlAttr->QueryIntValue(&value), XML_WRONG_ATTRIBUTE_TYPE);

}
