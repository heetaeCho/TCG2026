#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLAttributeTest_219 : public ::testing::Test {

protected:

    XMLAttribute attr;

};



TEST_F(XMLAttributeTest_219, SetAttributeInt_NormalOperation_219) {

    int value = 42;

    attr.SetAttribute(value);

    EXPECT_STREQ(attr.Value(), "42");

}



TEST_F(XMLAttributeTest_219, SetAttributeInt_ZeroValue_219) {

    int value = 0;

    attr.SetAttribute(value);

    EXPECT_STREQ(attr.Value(), "0");

}



TEST_F(XMLAttributeTest_219, SetAttributeInt_NegativeValue_219) {

    int value = -42;

    attr.SetAttribute(value);

    EXPECT_STREQ(attr.Value(), "-42");

}



TEST_F(XMLAttributeTest_219, SetAttributeInt_MaxValue_219) {

    int value = INT_MAX;

    attr.SetAttribute(value);

    char expected[20];

    snprintf(expected, sizeof(expected), "%d", INT_MAX);

    EXPECT_STREQ(attr.Value(), expected);

}



TEST_F(XMLAttributeTest_219, SetAttributeInt_MinValue_219) {

    int value = INT_MIN;

    attr.SetAttribute(value);

    char expected[20];

    snprintf(expected, sizeof(expected), "%d", INT_MIN);

    EXPECT_STREQ(attr.Value(), expected);

}
