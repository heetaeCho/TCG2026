#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* element;



    void SetUp() override {

        element = doc.NewElement("test_element");

        ASSERT_NE(element, nullptr);

    }



    void TearDown() override {

        delete element;

    }

};



TEST_F(XMLElementTest_99, SetAttribute_NormalOperation_99) {

    element->SetAttribute("test_attr", 42u);



    unsigned value = 0;

    XMLError result = element->QueryUnsignedAttribute("test_attr", &value);

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_EQ(value, 42u);

}



TEST_F(XMLElementTest_99, SetAttribute_BoundaryCondition_MaxValue_99) {

    element->SetAttribute("test_attr", UINT_MAX);



    unsigned value = 0;

    XMLError result = element->QueryUnsignedAttribute("test_attr", &value);

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_EQ(value, UINT_MAX);

}



TEST_F(XMLElementTest_99, SetAttribute_BoundaryCondition_ZeroValue_99) {

    element->SetAttribute("test_attr", 0u);



    unsigned value = 1; // Non-zero default to check if it changes

    XMLError result = element->QueryUnsignedAttribute("test_attr", &value);

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_EQ(value, 0u);

}



TEST_F(XMLElementTest_99, SetAttribute_ErrorCase_AttributeNotFoundAfterSet_99) {

    element->SetAttribute("test_attr", 42u);



    unsigned value = 0;

    XMLError result = element->QueryUnsignedAttribute("non_existent_attr", &value);

    EXPECT_EQ(result, XML_NO_ATTRIBUTE);

}



TEST_F(XMLElementTest_99, SetAttribute_ErrorCase_EmptyAttributeName_99) {

    element->SetAttribute("", 42u);



    unsigned value = 0;

    XMLError result = element->QueryUnsignedAttribute("", &value);

    EXPECT_EQ(result, XML_NO_ATTRIBUTE);

}
