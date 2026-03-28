#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* element;



    void SetUp() override {

        element = doc.NewElement("TestElement");

        if (element) {

            doc.InsertFirstChild(element);

        }

    }



    void TearDown() override {

        doc.Clear();

    }

};



TEST_F(XMLElementTest_255, BoolText_DefaultValue_Returned_When_Attribute_Not_Present_255) {

    bool defaultValue = true;

    bool result = element->BoolText(defaultValue);

    EXPECT_EQ(result, defaultValue);

}



TEST_F(XMLElementTest_255, BoolText_Returns_True_When_Attribute_Is_True_255) {

    element->SetAttribute("boolAttr", "true");

    bool result = element->BoolText(false);

    EXPECT_EQ(result, true);

}



TEST_F(XMLElementTest_255, BoolText_Returns_False_When_Attribute_Is_False_255) {

    element->SetAttribute("boolAttr", "false");

    bool result = element->BoolText(true);

    EXPECT_EQ(result, false);

}



TEST_F(XMLElementTest_255, BoolText_Ignores_NonBoolean_Text_And_Returns_DefaultValue_255) {

    element->SetAttribute("boolAttr", "notABoolean");

    bool defaultValue = true;

    bool result = element->BoolText(defaultValue);

    EXPECT_EQ(result, defaultValue);

}



TEST_F(XMLElementTest_255, BoolText_CaseInsensitive_True_Value_255) {

    element->SetAttribute("boolAttr", "TRUE");

    bool result = element->BoolText(false);

    EXPECT_EQ(result, true);



    element->SetAttribute("boolAttr", "true");

    result = element->BoolText(false);

    EXPECT_EQ(result, true);

}



TEST_F(XMLElementTest_255, BoolText_CaseInsensitive_False_Value_255) {

    element->SetAttribute("boolAttr", "FALSE");

    bool result = element->BoolText(true);

    EXPECT_EQ(result, false);



    element->SetAttribute("boolAttr", "false");

    result = element->BoolText(true);

    EXPECT_EQ(result, false);

}
