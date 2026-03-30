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



TEST_F(XMLElementTest_235, GetText_ReturnsNull_WhenNoChildren_235) {

    EXPECT_EQ(element->GetText(), nullptr);

}



TEST_F(XMLElementTest_235, GetText_SkipsCommentNodes_235) {

    XMLNode* comment = element->InsertNewChildElement("comment")->ToComment();

    XMLNode* textNode = element->InsertEndChild(new XMLText(&doc));

    textNode->SetValue("Sample Text");



    EXPECT_STREQ(element->GetText(), "Sample Text");

}



TEST_F(XMLElementTest_235, GetText_ReturnsTextContent_WhenTextIsFirstNonCommentChild_235) {

    XMLNode* textNode = element->InsertEndChild(new XMLText(&doc));

    textNode->SetValue("Sample Text");



    EXPECT_STREQ(element->GetText(), "Sample Text");

}



TEST_F(XMLElementTest_235, GetText_ReturnsNull_WhenFirstNonCommentChildIsNotText_235) {

    element->InsertEndChild(new XMLElement(&doc));

    

    EXPECT_EQ(element->GetText(), nullptr);

}
