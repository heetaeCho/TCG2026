#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest_261 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* element;



    void SetUp() override {

        element = doc.NewElement("testElement");

        ASSERT_NE(element, nullptr);

    }



    void TearDown() override {

        delete element;

    }

};



TEST_F(XMLElementTest_261, InsertNewText_ReturnsValidPointer_261) {

    XMLText* textNode = element->InsertNewText("Sample text");

    EXPECT_NE(textNode, nullptr);

}



TEST_F(XMLElementTest_261, InsertNewText_TextValueIsSet_261) {

    const char* sampleText = "Sample text";

    XMLText* textNode = element->InsertNewText(sampleText);

    ASSERT_NE(textNode, nullptr);

    EXPECT_STREQ(textNode->Value(), sampleText);

}



TEST_F(XMLElementTest_261, InsertNewText_MultipleCallsReturnDifferentPointers_261) {

    XMLText* firstTextNode = element->InsertNewText("First text");

    XMLText* secondTextNode = element->InsertNewText("Second text");

    EXPECT_NE(firstTextNode, nullptr);

    EXPECT_NE(secondTextNode, nullptr);

    EXPECT_NE(firstTextNode, secondTextNode);

}



TEST_F(XMLElementTest_261, InsertNewText_NullText_ReturnsNullPointer_261) {

    XMLText* textNode = element->InsertNewText(nullptr);

    EXPECT_EQ(textNode, nullptr);

}



TEST_F(XMLElementTest_261, InsertNewText_EmptyText_ReturnsValidPointer_261) {

    XMLText* textNode = element->InsertNewText("");

    EXPECT_NE(textNode, nullptr);

}
