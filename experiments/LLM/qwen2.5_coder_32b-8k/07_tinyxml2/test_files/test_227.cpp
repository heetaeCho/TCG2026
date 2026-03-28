#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* element;



    void SetUp() override {

        element = doc.NewElement("TestElement");

        doc.InsertFirstChild(element);

    }



    void TearDown() override {

        delete element;

    }

};



TEST_F(XMLElementTest_227, Attribute_ReturnsNullForNonExistentAttribute_227) {

    EXPECT_EQ(nullptr, element->Attribute("nonexistent"));

}



TEST_F(XMLElementTest_227, Attribute_ReturnsCorrectValueForExistingAttribute_227) {

    element->SetAttribute("test", "value");

    EXPECT_STREQ("value", element->Attribute("test"));

}



TEST_F(XMLElementTest_227, Attribute_ReturnsNullWhenValueDoesNotMatch_227) {

    element->SetAttribute("test", "value");

    EXPECT_EQ(nullptr, element->Attribute("test", "wrong_value"));

}



TEST_F(XMLElementTest_227, Attribute_MatchesValueExactly_227) {

    element->SetAttribute("test", "value");

    EXPECT_STREQ("value", element->Attribute("test", "value"));

}



TEST_F(XMLElementTest_227, Attribute_HandlesNullDefaultValueGracefully_227) {

    EXPECT_EQ(nullptr, element->Attribute("nonexistent", nullptr));

}
