#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLAttributeTest_220 : public ::testing::Test {

protected:

    XMLAttribute xmlAttr;

};



TEST_F(XMLAttributeTest_220, SetAttribute_NormalOperation_220) {

    unsigned value = 12345;

    xmlAttr.SetAttribute(value);

    EXPECT_STREQ(xmlAttr.Value(), "12345");

}



TEST_F(XMLAttributeTest_220, SetAttribute_BoundaryCondition_Zero_220) {

    unsigned value = 0;

    xmlAttr.SetAttribute(value);

    EXPECT_STREQ(xmlAttr.Value(), "0");

}



TEST_F(XMLAttributeTest_220, SetAttribute_BoundaryCondition_MaxUnsigned_220) {

    unsigned value = UINT_MAX;

    xmlAttr.SetAttribute(value);

    char expectedStr[11]; // Max value of uint in decimal is 4294967295 which has 10 digits + null terminator

    snprintf(expectedStr, sizeof(expectedStr), "%u", value);

    EXPECT_STREQ(xmlAttr.Value(), expectedStr);

}



TEST_F(XMLAttributeTest_220, SetAttribute_ExceptionalCase_NoChangeAfterSet_220) {

    unsigned initialValue = 54321;

    xmlAttr.SetAttribute(initialValue);

    EXPECT_STREQ(xmlAttr.Value(), "54321");



    unsigned newValue = 67890;

    xmlAttr.SetAttribute(newValue);

    EXPECT_STREQ(xmlAttr.Value(), "67890");

}
