#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tinyxml2.h"



using namespace tinyxml2;

using ::testing::Return;



class XMLElementTest_105 : public testing::Test {

protected:

    XMLDocument* doc;

    XMLElement* element;



    void SetUp() override {

        doc = new XMLDocument();

        element = doc->NewElement("testElement");

    }



    void TearDown() override {

        delete doc;

    }

};



TEST_F(XMLElementTest_105, FirstAttribute_ReturnsNullWhenNoAttributes_105) {

    EXPECT_EQ(element->FirstAttribute(), nullptr);

}



TEST_F(XMLElementTest_105, SetAndGetText_WithValidString_105) {

    const char* text = "Sample Text";

    element->SetText(text);

    EXPECT_STREQ(element->GetText(), text);

}



TEST_F(XMLElementTest_105, SetAttribute_And_QueryAttribute_ReturnCorrectValue_105) {

    int expectedValue = 42;

    element->SetAttribute("testAttribute", expectedValue);



    int value;

    XMLError result = element->QueryIntAttribute("testAttribute", &value);

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_EQ(value, expectedValue);

}



TEST_F(XMLElementTest_105, QueryAttribute_ReturnsDefaultValueWhenNotFound_105) {

    int defaultValue = 42;

    int value;

    XMLError result = element->QueryIntAttribute("nonExistentAttribute", &value);

    EXPECT_EQ(result, XML_NO_ATTRIBUTE);

    EXPECT_EQ(value, defaultValue); // Assuming default value is not set by QueryIntAttribute

}



TEST_F(XMLElementTest_105, FindAttribute_ReturnsNullWhenNotFound_105) {

    EXPECT_EQ(element->FindAttribute("nonExistentAttribute"), nullptr);

}



TEST_F(XMLElementTest_105, InsertNewChildElement_AddsChildCorrectly_105) {

    XMLElement* child = element->InsertNewChildElement("child");

    EXPECT_STREQ(child->Name(), "child");

}



TEST_F(XMLElementTest_105, DeleteAttribute_RemovesAttribute_105) {

    element->SetAttribute("testAttribute", 42);

    element->DeleteAttribute("testAttribute");

    EXPECT_EQ(element->FindAttribute("testAttribute"), nullptr);

}
