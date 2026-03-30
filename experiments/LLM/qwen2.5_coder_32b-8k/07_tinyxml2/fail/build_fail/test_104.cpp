#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest_104 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* element;



    void SetUp() override {

        element = doc.NewElement("testElement");

        ASSERT_NE(element, nullptr);

        doc.InsertFirstChild(element);

    }



    void TearDown() override {

        doc.Clear();

    }

};



TEST_F(XMLElementTest_104, SetAttribute_Float_NormalOperation_104) {

    element->SetAttribute("testFloat", 3.14f);



    float value;

    XMLError result = element->QueryFloatAttribute("testFloat", &value);

    EXPECT_EQ(result, XML_NO_ERROR);

    EXPECT_FLOAT_EQ(value, 3.14f);

}



TEST_F(XMLElementTest_104, SetAttribute_Float_BoundaryCondition_MaxValue_104) {

    element->SetAttribute("testFloat", std::numeric_limits<float>::max());



    float value;

    XMLError result = element->QueryFloatAttribute("testFloat", &value);

    EXPECT_EQ(result, XML_NO_ERROR);

    EXPECT_FLOAT_EQ(value, std::numeric_limits<float>::max());

}



TEST_F(XMLElementTest_104, SetAttribute_Float_BoundaryCondition_MinValue_104) {

    element->SetAttribute("testFloat", std::numeric_limits<float>::lowest());



    float value;

    XMLError result = element->QueryFloatAttribute("testFloat", &value);

    EXPECT_EQ(result, XML_NO_ERROR);

    EXPECT_FLOAT_EQ(value, std::numeric_limits<float>::lowest());

}



TEST_F(XMLElementTest_104, SetAttribute_Float_BoundaryCondition_Zero_104) {

    element->SetAttribute("testFloat", 0.0f);



    float value;

    XMLError result = element->QueryFloatAttribute("testFloat", &value);

    EXPECT_EQ(result, XML_NO_ERROR);

    EXPECT_FLOAT_EQ(value, 0.0f);

}



TEST_F(XMLElementTest_104, SetAttribute_Float_ErrorCase_AttributeNotFound_104) {

    float value;

    XMLError result = element->QueryFloatAttribute("nonExistent", &value);

    EXPECT_EQ(result, XML_WRONG_ATTRIBUTE_TYPE);

}
