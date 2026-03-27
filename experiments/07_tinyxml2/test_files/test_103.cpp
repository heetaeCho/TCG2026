#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest : public ::testing::Test {

protected:

    XMLElement element;

};



TEST_F(XMLElementTest_103, SetAttributeDouble_NormalOperation_103) {

    const char* attributeName = "testAttribute";

    double attributeValue = 3.14159;



    element.SetAttribute(attributeName, attributeValue);

    

    const XMLAttribute* attr = element.FindAttribute(attributeName);

    ASSERT_NE(attr, nullptr);

    EXPECT_DOUBLE_EQ(attr->DoubleValue(), attributeValue);

}



TEST_F(XMLElementTest_103, SetAttributeDouble_BoundaryCondition_Zero_103) {

    const char* attributeName = "testAttribute";

    double attributeValue = 0.0;



    element.SetAttribute(attributeName, attributeValue);

    

    const XMLAttribute* attr = element.FindAttribute(attributeName);

    ASSERT_NE(attr, nullptr);

    EXPECT_DOUBLE_EQ(attr->DoubleValue(), attributeValue);

}



TEST_F(XMLElementTest_103, SetAttributeDouble_BoundaryCondition_Max_103) {

    const char* attributeName = "testAttribute";

    double attributeValue = std::numeric_limits<double>::max();



    element.SetAttribute(attributeName, attributeValue);

    

    const XMLAttribute* attr = element.FindAttribute(attributeName);

    ASSERT_NE(attr, nullptr);

    EXPECT_DOUBLE_EQ(attr->DoubleValue(), attributeValue);

}



TEST_F(XMLElementTest_103, SetAttributeDouble_BoundaryCondition_Min_103) {

    const char* attributeName = "testAttribute";

    double attributeValue = std::numeric_limits<double>::lowest();



    element.SetAttribute(attributeName, attributeValue);

    

    const XMLAttribute* attr = element.FindAttribute(attributeName);

    ASSERT_NE(attr, nullptr);

    EXPECT_DOUBLE_EQ(attr->DoubleValue(), attributeValue);

}



TEST_F(XMLElementTest_103, SetAttributeDouble_OverwriteExisting_103) {

    const char* attributeName = "testAttribute";

    double firstAttributeValue = 3.14159;

    double secondAttributeValue = 2.71828;



    element.SetAttribute(attributeName, firstAttributeValue);

    element.SetAttribute(attributeName, secondAttributeValue);

    

    const XMLAttribute* attr = element.FindAttribute(attributeName);

    ASSERT_NE(attr, nullptr);

    EXPECT_DOUBLE_EQ(attr->DoubleValue(), secondAttributeValue);

}



TEST_F(XMLElementTest_103, SetAttributeDouble_QueryDoubleAttribute_103) {

    const char* attributeName = "testAttribute";

    double attributeValue = 3.14159;



    element.SetAttribute(attributeName, attributeValue);

    

    double queriedValue;

    XMLError result = element.QueryDoubleAttribute(attributeName, &queriedValue);

    

    EXPECT_EQ(result, XML_NO_ERROR);

    EXPECT_DOUBLE_EQ(queriedValue, attributeValue);

}



TEST_F(XMLElementTest_103, SetAttributeDouble_QueryDoubleAttribute_NotFound_103) {

    const char* attributeName = "nonExistentAttribute";

    double defaultValue = 9.87654;

    

    double queriedValue;

    XMLError result = element.QueryDoubleAttribute(attributeName, &queriedValue);

    

    EXPECT_EQ(result, XML_NO_ATTRIBUTE);

    EXPECT_DOUBLE_EQ(queriedValue, defaultValue); // Default value is not set by QueryDoubleAttribute

}
