#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest_94 : public ::testing::Test {

protected:

    XMLElement element;

};



TEST_F(XMLElementTest_94, QueryAttribute_Double_NormalOperation_94) {

    double value = 0.0;

    const char* attrName = "testAttr";

    element.SetAttribute(attrName, 123.456);



    XMLError result = element.QueryAttribute(attrName, &value);

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_DOUBLE_EQ(value, 123.456);

}



TEST_F(XMLElementTest_94, QueryAttribute_Double_AttributeNotFound_94) {

    double value = 0.0;

    const char* attrName = "nonExistentAttr";



    XMLError result = element.QueryAttribute(attrName, &value);

    EXPECT_EQ(result, XML_NO_ATTRIBUTE);

}



TEST_F(XMLElementTest_94, QueryAttribute_Double_DefaultValue_94) {

    double value = 0.0;

    const char* attrName = "nonExistentAttr";

    double defaultValue = -1.23;



    XMLError result = element.QueryDoubleAttribute(attrName, &value);

    EXPECT_EQ(result, XML_NO_ATTRIBUTE);

    EXPECT_DOUBLE_EQ(value, defaultValue); // Note: value is not set by QueryAttribute in this case

}



TEST_F(XMLElementTest_94, QueryAttribute_Double_InvalidConversion_94) {

    double value = 0.0;

    const char* attrName = "testAttr";

    element.SetAttribute(attrName, "invalidValue");



    XMLError result = element.QueryDoubleAttribute(attrName, &value);

    EXPECT_EQ(result, XML_WRONG_ATTRIBUTE_TYPE);

}
