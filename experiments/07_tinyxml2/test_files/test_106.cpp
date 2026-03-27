#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest_106 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* element;



    void SetUp() override {

        element = doc.NewElement("testElement");

    }



    void TearDown() override {

        delete element;

    }

};



TEST_F(XMLElementTest_106, ClosingType_ReturnsDefault_106) {

    EXPECT_EQ(element->ClosingType(), ElementClosingType::OPEN);

}



TEST_F(XMLElementTest_106, SetNameAndGetText_NormalOperation_106) {

    element->SetText("sample text");

    EXPECT_STREQ(element->GetText(), "sample text");

}



TEST_F(XMLElementTest_106, QueryIntAttribute_ReturnsDefaultWhenNotFound_106) {

    int value = 42;

    XMLError result = element->QueryIntAttribute("nonexistent", &value);

    EXPECT_EQ(result, XML_NO_ATTRIBUTE);

    EXPECT_EQ(value, 42); // should remain unchanged

}



TEST_F(XMLElementTest_106, SetAndGetIntAttribute_NormalOperation_106) {

    element->SetAttribute("testInt", 10);

    int value = 0;

    XMLError result = element->QueryIntAttribute("testInt", &value);

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_EQ(value, 10);

}



TEST_F(XMLElementTest_106, SetAndGetStringAttribute_NormalOperation_106) {

    element->SetAttribute("testString", "example");

    const char* value = nullptr;

    XMLError result = element->QueryStringAttribute("testString", &value);

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_STREQ(value, "example");

}



TEST_F(XMLElementTest_106, DeleteNonExistentAttribute_NoError_106) {

    element->DeleteAttribute("nonexistent"); // No error expected

}



TEST_F(XMLElementTest_106, InsertNewChildElement_NormalOperation_106) {

    XMLElement* child = element->InsertNewChildElement("child");

    EXPECT_NE(child, nullptr);

    EXPECT_STREQ(child->Name(), "child");

}



TEST_F(XMLElementTest_106, SetTextWithDifferentTypes_NormalOperation_106) {

    element->SetText(42);

    EXPECT_STREQ(element->GetText(), "42");



    element->SetText(true);

    EXPECT_STREQ(element->GetText(), "true");



    element->SetText(3.14f);

    EXPECT_STREQ(element->GetText(), "3.14");

}
