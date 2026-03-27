#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest_82 : public ::testing::Test {

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



TEST_F(XMLElementTest_82, QueryUnsignedAttribute_NormalOperation_82) {

    unsigned int value;

    element->SetAttribute("test", 42u);

    EXPECT_EQ(element->QueryUnsignedAttribute("test", &value), XML_SUCCESS);

    EXPECT_EQ(value, 42u);

}



TEST_F(XMLElementTest_82, QueryUnsignedAttribute_AttributeNotFound_82) {

    unsigned int value;

    EXPECT_EQ(element->QueryUnsignedAttribute("nonexistent", &value), XML_NO_ATTRIBUTE);

}



TEST_F(XMLElementTest_82, QueryUnsignedAttribute_WrongAttributeType_82) {

    element->SetAttribute("test", "not_a_number");

    unsigned int value;

    EXPECT_EQ(element->QueryUnsignedAttribute("test", &value), XML_WRONG_ATTRIBUTE_TYPE);

}
