#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest_80 : public ::testing::Test {

protected:

    XMLDocument* doc;

    XMLElement* element;



    void SetUp() override {

        doc = new XMLDocument();

        element = doc->NewElement("testElement");

        doc->LinkEndChild(element);

    }



    void TearDown() override {

        delete doc;

    }

};



TEST_F(XMLElementTest_80, ToElementReturnsSelf_80) {

    EXPECT_EQ(element->ToElement(), element);

}



TEST_F(XMLElementTest_80, SetAndGetIntAttribute_80) {

    int value = 42;

    element->SetAttribute("test", value);

    EXPECT_EQ(element->IntAttribute("test"), value);

}



TEST_F(XMLElementTest_80, GetNonexistentIntAttributeReturnsDefault_80) {

    int defaultValue = 99;

    EXPECT_EQ(element->IntAttribute("nonexistent", defaultValue), defaultValue);

}



TEST_F(XMLElementTest_80, SetAndGetStringAttribute_80) {

    const char* value = "testValue";

    element->SetAttribute("test", value);

    EXPECT_STREQ(element->Attribute("test"), value);

}



TEST_F(XMLElementTest_80, GetNonexistentStringAttributeReturnsDefault_80) {

    const char* defaultValue = "default";

    element->SetAttribute("test", defaultValue); // Setting to ensure we check the default correctly

    EXPECT_STREQ(element->Attribute("nonexistent", "default"), defaultValue);

}



TEST_F(XMLElementTest_80, SetAndDeleteAttribute_80) {

    element->SetAttribute("test", 123);

    element->DeleteAttribute("test");

    EXPECT_EQ(element->FindAttribute("test"), nullptr);

}



TEST_F(XMLElementTest_80, InsertNewChildElement_80) {

    XMLElement* child = element->InsertNewChildElement("child");

    EXPECT_STREQ(child->Name(), "child");

    EXPECT_TRUE(element->FirstChildElement() == child);

}



TEST_F(XMLElementTest_80, SetAndGetIntText_80) {

    int value = 42;

    element->SetText(value);

    int result;

    XMLError error = element->QueryIntText(&result);

    EXPECT_EQ(error, XML_NO_ERROR);

    EXPECT_EQ(result, value);

}



TEST_F(XMLElementTest_80, SetAndGetFloatText_80) {

    float value = 3.14f;

    element->SetText(value);

    float result;

    XMLError error = element->QueryFloatText(&result);

    EXPECT_EQ(error, XML_NO_ERROR);

    EXPECT_FLOAT_EQ(result, value);

}



TEST_F(XMLElementTest_80, SetAndGetDefaultTextIfInvalid_80) {

    const char* invalidText = "not a number";

    element->SetText(invalidText);

    int defaultValue = 123;

    EXPECT_EQ(element->IntText(defaultValue), defaultValue);

}
