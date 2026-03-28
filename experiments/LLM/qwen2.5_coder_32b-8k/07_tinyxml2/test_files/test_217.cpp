#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLAttributeTest_217 : public ::testing::Test {

protected:

    XMLAttribute xmlAttr;

};



TEST_F(XMLAttributeTest_217, QueryDoubleValue_ValidDoubleString_217) {

    double value = 0.0;

    const char* validDoubleStr = "3.14";

    xmlAttr.SetAttribute(validDoubleStr);

    EXPECT_EQ(xmlAttr.QueryDoubleValue(&value), XML_SUCCESS);

    EXPECT_DOUBLE_EQ(value, 3.14);

}



TEST_F(XMLAttributeTest_217, QueryDoubleValue_EmptyString_217) {

    double value = 0.0;

    const char* emptyStr = "";

    xmlAttr.SetAttribute(emptyStr);

    EXPECT_EQ(xmlAttr.QueryDoubleValue(&value), XML_WRONG_ATTRIBUTE_TYPE);

}



TEST_F(XMLAttributeTest_217, QueryDoubleValue_NonNumericString_217) {

    double value = 0.0;

    const char* nonNumericStr = "abc";

    xmlAttr.SetAttribute(nonNumericStr);

    EXPECT_EQ(xmlAttr.QueryDoubleValue(&value), XML_WRONG_ATTRIBUTE_TYPE);

}



TEST_F(XMLAttributeTest_217, QueryDoubleValue_LargeNumberString_217) {

    double value = 0.0;

    const char* largeNumberStr = "1.7976931348623157e+308"; // max double

    xmlAttr.SetAttribute(largeNumberStr);

    EXPECT_EQ(xmlAttr.QueryDoubleValue(&value), XML_SUCCESS);

    EXPECT_DOUBLE_EQ(value, 1.7976931348623157e+308);

}



TEST_F(XMLAttributeTest_217, QueryDoubleValue_NegativeNumberString_217) {

    double value = 0.0;

    const char* negativeNumberStr = "-3.14";

    xmlAttr.SetAttribute(negativeNumberStr);

    EXPECT_EQ(xmlAttr.QueryDoubleValue(&value), XML_SUCCESS);

    EXPECT_DOUBLE_EQ(value, -3.14);

}
