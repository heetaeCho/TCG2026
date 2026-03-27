#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest_85 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* element;



    void SetUp() override {

        element = doc.NewElement("testElement");

        doc.InsertFirstChild(element);

    }



    void TearDown() override {

        doc.Clear();

    }

};



TEST_F(XMLElementTest_85, QueryBoolAttribute_NormalOperation_True_85) {

    element->SetAttribute("active", true);

    bool value;

    XMLError result = element->QueryBoolAttribute("active", &value);

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_TRUE(value);

}



TEST_F(XMLElementTest_85, QueryBoolAttribute_NormalOperation_False_85) {

    element->SetAttribute("active", false);

    bool value;

    XMLError result = element->QueryBoolAttribute("active", &value);

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_FALSE(value);

}



TEST_F(XMLElementTest_85, QueryBoolAttribute_AttributeNotFound_85) {

    bool value;

    XMLError result = element->QueryBoolAttribute("nonExistent", &value);

    EXPECT_EQ(result, XML_NO_ATTRIBUTE);

}



TEST_F(XMLElementTest_85, QueryBoolAttribute_WrongType_85) {

    element->SetAttribute("active", "notABool");

    bool value;

    XMLError result = element->QueryBoolAttribute("active", &value);

    EXPECT_EQ(result, XML_WRONG_ATTRIBUTE_TYPE);

}
