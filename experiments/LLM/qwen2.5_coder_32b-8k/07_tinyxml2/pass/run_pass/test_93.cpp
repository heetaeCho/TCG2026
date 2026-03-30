#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest_93 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* element;



    void SetUp() override {

        element = doc.NewElement("TestElement");

        ASSERT_NE(element, nullptr);

    }



    void TearDown() override {

        doc.DeleteNode(element);

    }

};



TEST_F(XMLElementTest_93, QueryBoolAttribute_NormalOperation_93) {

    bool value;

    element->SetAttribute("boolAttr", true);

    XMLError result = element->QueryAttribute("boolAttr", &value);

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_TRUE(value);



    element->SetAttribute("boolAttr", false);

    result = element->QueryAttribute("boolAttr", &value);

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_FALSE(value);

}



TEST_F(XMLElementTest_93, QueryBoolAttribute_AttributeNotFound_93) {

    bool value;

    XMLError result = element->QueryAttribute("nonExistentAttr", &value);

    EXPECT_EQ(result, XML_NO_ATTRIBUTE);

}



TEST_F(XMLElementTest_93, QueryBoolAttribute_WrongType_93) {

    bool value;

    element->SetAttribute("boolAttr", "notABool");

    XMLError result = element->QueryAttribute("boolAttr", &value);

    EXPECT_EQ(result, XML_WRONG_ATTRIBUTE_TYPE);

}



TEST_F(XMLElementTest_93, QueryBoolAttribute_BoundaryCondition_EmptyString_93) {

    bool value;

    element->SetAttribute("", true);

    XMLError result = element->QueryAttribute("", &value);

    EXPECT_EQ(result, XML_NO_ATTRIBUTE);

}
