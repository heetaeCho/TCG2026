#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest_87 : public ::testing::Test {

protected:

    XMLElement* element;



    void SetUp() override {

        XMLDocument doc;

        element = new XMLElement(&doc);

    }



    void TearDown() override {

        delete element;

    }

};



TEST_F(XMLElementTest_87, QueryFloatAttribute_WithExistingAttribute_87) {

    float value = 0.0f;

    element->SetAttribute("test", "3.14");

    EXPECT_EQ(XML_SUCCESS, element->QueryFloatAttribute("test", &value));

    EXPECT_FLOAT_EQ(3.14f, value);

}



TEST_F(XMLElementTest_87, QueryFloatAttribute_WithNonExistentAttribute_87) {

    float value = 0.0f;

    EXPECT_EQ(XML_NO_ATTRIBUTE, element->QueryFloatAttribute("nonexistent", &value));

    EXPECT_FLOAT_EQ(0.0f, value);

}



TEST_F(XMLElementTest_87, QueryFloatAttribute_WithInvalidAttributeValue_87) {

    float value = 0.0f;

    element->SetAttribute("test", "not_a_float");

    EXPECT_EQ(XML_WRONG_ATTRIBUTE_TYPE, element->QueryFloatAttribute("test", &value));

    EXPECT_FLOAT_EQ(0.0f, value);

}



TEST_F(XMLElementTest_87, QueryFloatAttribute_AttributeValueIsZero_87) {

    float value = 1.0f;

    element->SetAttribute("test", "0");

    EXPECT_EQ(XML_SUCCESS, element->QueryFloatAttribute("test", &value));

    EXPECT_FLOAT_EQ(0.0f, value);

}



TEST_F(XMLElementTest_87, QueryFloatAttribute_AttributeValueIsPositiveMax_87) {

    float value = 0.0f;

    element->SetAttribute("test", "3.402823466e+38");

    EXPECT_EQ(XML_SUCCESS, element->QueryFloatAttribute("test", &value));

    EXPECT_FLOAT_EQ(3.402823466e+38f, value);

}



TEST_F(XMLElementTest_87, QueryFloatAttribute_AttributeValueIsNegativeMax_87) {

    float value = 0.0f;

    element->SetAttribute("test", "-3.402823466e+38");

    EXPECT_EQ(XML_SUCCESS, element->QueryFloatAttribute("test", &value));

    EXPECT_FLOAT_EQ(-3.402823466e+38f, value);

}
