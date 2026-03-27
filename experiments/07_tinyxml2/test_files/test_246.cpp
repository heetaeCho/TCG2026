#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest_246 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* element;



    void SetUp() override {

        element = doc.NewElement("testElement");

        doc.InsertEndChild(element);

    }



    void TearDown() override {

        delete element;

    }

};



TEST_F(XMLElementTest_246, QueryInt64Text_ValidValue_246) {

    int64_t value;

    element->SetText("123456789012345");

    EXPECT_EQ(element->QueryInt64Text(&value), XML_SUCCESS);

    EXPECT_EQ(value, 123456789012345);

}



TEST_F(XMLElementTest_246, QueryInt64Text_EmptyText_246) {

    int64_t value;

    element->SetText("");

    EXPECT_EQ(element->QueryInt64Text(&value), XML_CAN_NOT_CONVERT_TEXT);

}



TEST_F(XMLElementTest_246, QueryInt64Text_InvalidText_246) {

    int64_t value;

    element->SetText("invalid_text");

    EXPECT_EQ(element->QueryInt64Text(&value), XML_CAN_NOT_CONVERT_TEXT);

}



TEST_F(XMLElementTest_246, QueryInt64Text_NoTextNode_246) {

    int64_t value;

    element->Clear();

    EXPECT_EQ(element->QueryInt64Text(&value), XML_NO_TEXT_NODE);

}
