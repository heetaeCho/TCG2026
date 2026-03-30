#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest_232 : public ::testing::Test {

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



TEST_F(XMLElementTest_232, BoolAttribute_DefaultValueReturned_232) {

    bool result = element->BoolAttribute("nonExistent", true);

    EXPECT_TRUE(result);

}



TEST_F(XMLElementTest_232, BoolAttribute_AttributeExists_ReturnsCorrectValue_232) {

    element->SetAttribute("boolAttr", "true");

    bool result = element->BoolAttribute("boolAttr", false);

    EXPECT_TRUE(result);



    element->SetAttribute("boolAttr", "false");

    result = element->BoolAttribute("boolAttr", true);

    EXPECT_FALSE(result);

}



TEST_F(XMLElementTest_232, BoolAttribute_CaseInsensitive_ReturnsCorrectValue_232) {

    element->SetAttribute("BoolAttr", "TRUE");

    bool result = element->BoolAttribute("boolattr", false);

    EXPECT_TRUE(result);



    element->SetAttribute("BOOLATTR", "FALSE");

    result = element->BoolAttribute("boolAttr", true);

    EXPECT_FALSE(result);

}



TEST_F(XMLElementTest_232, BoolAttribute_InvalidValue_ReturnsDefaultValue_232) {

    element->SetAttribute("boolAttr", "invalid");

    bool result = element->BoolAttribute("boolAttr", true);

    EXPECT_TRUE(result);



    result = element->BoolAttribute("boolAttr", false);

    EXPECT_FALSE(result);

}



TEST_F(XMLElementTest_232, BoolAttribute_EmptyValue_ReturnsDefaultValue_232) {

    element->SetAttribute("boolAttr", "");

    bool result = element->BoolAttribute("boolAttr", true);

    EXPECT_TRUE(result);



    result = element->BoolAttribute("boolAttr", false);

    EXPECT_FALSE(result);

}
