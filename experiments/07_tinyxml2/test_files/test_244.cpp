#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest_244 : public ::testing::Test {

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



TEST_F(XMLElementTest_244, QueryIntText_SuccessfulConversion_244) {

    int value;

    XMLText* textNode = doc.NewText("123");

    element->InsertEndChild(textNode);



    XMLError result = element->QueryIntText(&value);

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_EQ(value, 123);

}



TEST_F(XMLElementTest_244, QueryIntText_NonIntegerText_244) {

    int value;

    XMLText* textNode = doc.NewText("abc");

    element->InsertEndChild(textNode);



    XMLError result = element->QueryIntText(&value);

    EXPECT_EQ(result, XML_CAN_NOT_CONVERT_TEXT);

}



TEST_F(XMLElementTest_244, QueryIntText_NoTextNode_244) {

    int value;

    XMLError result = element->QueryIntText(&value);

    EXPECT_EQ(result, XML_NO_TEXT_NODE);

}



TEST_F(XMLElementTest_244, QueryIntText_LargeIntegerValue_244) {

    int value;

    XMLText* textNode = doc.NewText("2147483647");

    element->InsertEndChild(textNode);



    XMLError result = element->QueryIntText(&value);

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_EQ(value, 2147483647);

}



TEST_F(XMLElementTest_244, QueryIntText_ZeroValue_244) {

    int value;

    XMLText* textNode = doc.NewText("0");

    element->InsertEndChild(textNode);



    XMLError result = element->QueryIntText(&value);

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_EQ(value, 0);

}



TEST_F(XMLElementTest_244, QueryIntText_NegativeValue_244) {

    int value;

    XMLText* textNode = doc.NewText("-1");

    element->InsertEndChild(textNode);



    XMLError result = element->QueryIntText(&value);

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_EQ(value, -1);

}



TEST_F(XMLElementTest_244, QueryIntText_EmptyString_244) {

    int value;

    XMLText* textNode = doc.NewText("");

    element->InsertEndChild(textNode);



    XMLError result = element->QueryIntText(&value);

    EXPECT_EQ(result, XML_CAN_NOT_CONVERT_TEXT);

}
