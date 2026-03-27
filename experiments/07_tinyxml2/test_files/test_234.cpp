#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest_234 : public ::testing::Test {

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



TEST_F(XMLElementTest_234, FloatAttribute_ReturnsDefaultValueWhenAttributeNotFound_234) {

    float result = element->FloatAttribute("nonexistent", 1.5f);

    EXPECT_FLOAT_EQ(result, 1.5f);

}



TEST_F(XMLElementTest_234, FloatAttribute_ReturnsParsedValueWhenAttributeExists_234) {

    XMLDocument doc;

    XMLElement* childElement = doc.NewElement("Child");

    childElement->SetAttribute("value", "3.14");

    element->InsertEndChild(childElement);

    float result = childElement->FloatAttribute("value", 0.0f);

    EXPECT_FLOAT_EQ(result, 3.14f);

}



TEST_F(XMLElementTest_234, FloatAttribute_HandlesBoundaryValues_234) {

    XMLDocument doc;

    XMLElement* childElement = doc.NewElement("Child");

    childElement->SetAttribute("value", "0");

    element->InsertEndChild(childElement);

    float result = childElement->FloatAttribute("value", 1.0f);

    EXPECT_FLOAT_EQ(result, 0.0f);



    childElement->SetAttribute("value", "-3.402823e+38"); // smallest float

    result = childElement->FloatAttribute("value", 1.0f);

    EXPECT_FLOAT_EQ(result, -std::numeric_limits<float>::max());



    childElement->SetAttribute("value", "3.402823e+38"); // largest float

    result = childElement->FloatAttribute("value", 1.0f);

    EXPECT_FLOAT_EQ(result, std::numeric_limits<float>::max());

}



TEST_F(XMLElementTest_234, FloatAttribute_HandlesInvalidValue_ReturnsDefaultValue_234) {

    XMLDocument doc;

    XMLElement* childElement = doc.NewElement("Child");

    childElement->SetAttribute("value", "invalid");

    element->InsertEndChild(childElement);

    float result = childElement->FloatAttribute("value", 1.0f);

    EXPECT_FLOAT_EQ(result, 1.0f); // should return default value

}
