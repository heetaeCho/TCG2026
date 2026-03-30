#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest_98 : public ::testing::Test {

protected:

    XMLElement element;

};



TEST_F(XMLElementTest_98, SetAttributeInt_NormalOperation_98) {

    element.SetAttribute("test", 42);

    EXPECT_EQ(element.IntAttribute("test"), 42);

}



TEST_F(XMLElementTest_98, SetAttributeInt_BoundaryCondition_Zero_98) {

    element.SetAttribute("test", 0);

    EXPECT_EQ(element.IntAttribute("test"), 0);

}



TEST_F(XMLElementTest_98, SetAttributeInt_BoundaryCondition_MaxInt_98) {

    element.SetAttribute("test", INT_MAX);

    EXPECT_EQ(element.IntAttribute("test"), INT_MAX);

}



TEST_F(XMLElementTest_98, SetAttributeInt_BoundaryCondition_MinInt_98) {

    element.SetAttribute("test", INT_MIN);

    EXPECT_EQ(element.IntAttribute("test"), INT_MIN);

}



TEST_F(XMLElementTest_98, SetAttributeInt_AttributeNotPresent_ReturnsDefaultValue_98) {

    int defaultValue = 10;

    EXPECT_EQ(element.IntAttribute("nonexistent", defaultValue), defaultValue);

}



TEST_F(XMLElementTest_98, SetAttributeInt_QueryIntAttribute_Success_98) {

    element.SetAttribute("test", 42);

    int value;

    XMLError result = element.QueryIntAttribute("test", &value);

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_EQ(value, 42);

}



TEST_F(XMLElementTest_98, SetAttributeInt_QueryIntAttribute_AttributeNotPresent_ReturnsError_98) {

    int value;

    XMLError result = element.QueryIntAttribute("nonexistent", &value);

    EXPECT_EQ(result, XML_NO_ATTRIBUTE);

}
