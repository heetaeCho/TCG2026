#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* element;



    void SetUp() override {

        element = new XMLElement(&doc);

    }



    void TearDown() override {

        delete element;

    }

};



TEST_F(XMLElementTest_79, SetNameAndGetText_NormalOperation_79) {

    const char* name = "testElement";

    element->SetName(name);

    EXPECT_STREQ(element->Value(), name);

}



TEST_F(XMLElementTest_79, SetStaticMemoryFlag_79) {

    const char* name = "staticElement";

    element->SetName(name, true);

    EXPECT_STREQ(element->Value(), name);

}



TEST_F(XMLElementTest_79, DefaultTextIsNotNull_79) {

    EXPECT_NE(element->GetText(), nullptr);

}



TEST_F(XMLElementTest_79, SetAndGetIntAttribute_79) {

    int value = 42;

    const char* attrName = "testAttr";

    element->SetAttribute(attrName, value);

    EXPECT_EQ(element->IntAttribute(attrName), value);

}



TEST_F(XMLElementTest_79, QueryNonExistentAttribute_ReturnsDefaultValue_79) {

    const char* attrName = "nonExistentAttr";

    int defaultValue = 10;

    EXPECT_EQ(element->IntAttribute(attrName, defaultValue), defaultValue);

}



TEST_F(XMLElementTest_79, SetAndGetFloatText_79) {

    float value = 3.14f;

    element->SetText(value);

    EXPECT_FLOAT_EQ(element->FloatText(0.0f), value);

}
