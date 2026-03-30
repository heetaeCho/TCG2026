#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest_90 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* element;



    void SetUp() override {

        element = doc.NewElement("testElement");

        ASSERT_NE(element, nullptr);

    }



    void TearDown() override {

        if (element) {

            element->DeleteChildren();

            delete element;

            element = nullptr;

        }

    }

};



TEST_F(XMLElementTest_90, QueryUnsignedAttribute_NormalOperation_90) {

    unsigned int value = 42;

    element->SetAttribute("test", value);



    unsigned int result = 0;

    XMLError error = element->QueryUnsignedAttribute("test", &result);

    EXPECT_EQ(error, XML_SUCCESS);

    EXPECT_EQ(result, value);

}



TEST_F(XMLElementTest_90, QueryUnsignedAttribute_AttributeNotFound_90) {

    unsigned int result = 42;

    XMLError error = element->QueryUnsignedAttribute("nonexistent", &result);

    EXPECT_EQ(error, XML_NO_ATTRIBUTE);

    EXPECT_EQ(result, 42); // result should not be modified

}



TEST_F(XMLElementTest_90, QueryUnsignedAttribute_BoundaryCondition_Zero_90) {

    unsigned int value = 0;

    element->SetAttribute("test", value);



    unsigned int result = 1;

    XMLError error = element->QueryUnsignedAttribute("test", &result);

    EXPECT_EQ(error, XML_SUCCESS);

    EXPECT_EQ(result, value);

}



TEST_F(XMLElementTest_90, QueryUnsignedAttribute_BoundaryCondition_MaxUint_90) {

    unsigned int value = UINT_MAX;

    element->SetAttribute("test", value);



    unsigned int result = 0;

    XMLError error = element->QueryUnsignedAttribute("test", &result);

    EXPECT_EQ(error, XML_SUCCESS);

    EXPECT_EQ(result, value);

}



TEST_F(XMLElementTest_90, QueryUnsignedAttribute_InvalidInput_90) {

    element->SetAttribute("test", "invalid");



    unsigned int result = 42;

    XMLError error = element->QueryUnsignedAttribute("test", &result);

    EXPECT_EQ(error, XML_WRONG_ATTRIBUTE_TYPE);

    EXPECT_EQ(result, 42); // result should not be modified

}
