#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest_245 : public ::testing::Test {

protected:

    XMLElement* element;

    XMLDocument doc;



    void SetUp() override {

        element = new XMLElement(&doc);

    }



    void TearDown() override {

        delete element;

    }

};



TEST_F(XMLElementTest_245, QueryUnsignedText_Success_245) {

    unsigned int value = 0;

    const char* text = "123";

    XMLText* xmlText = new XMLText();

    xmlText->SetValue(text);

    element->InsertEndChild(xmlText);



    XMLError result = element->QueryUnsignedText(&value);

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_EQ(value, 123u);

}



TEST_F(XMLElementTest_245, QueryUnsignedText_NoTextNode_245) {

    unsigned int value = 0;

    XMLError result = element->QueryUnsignedText(&value);

    EXPECT_EQ(result, XML_NO_TEXT_NODE);

}



TEST_F(XMLElementTest_245, QueryUnsignedText_CannotConvertText_245) {

    unsigned int value = 0;

    const char* text = "abc";

    XMLText* xmlText = new XMLText();

    xmlText->SetValue(text);

    element->InsertEndChild(xmlText);



    XMLError result = element->QueryUnsignedText(&value);

    EXPECT_EQ(result, XML_CAN_NOT_CONVERT_TEXT);

}



TEST_F(XMLElementTest_245, QueryUnsignedText_ZeroValue_245) {

    unsigned int value = 1; // Initialize to non-zero

    const char* text = "0";

    XMLText* xmlText = new XMLText();

    xmlText->SetValue(text);

    element->InsertEndChild(xmlText);



    XMLError result = element->QueryUnsignedText(&value);

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_EQ(value, 0u);

}



TEST_F(XMLElementTest_245, QueryUnsignedText_MaxValue_245) {

    unsigned int value = 0;

    const char* text = "4294967295"; // UINT_MAX

    XMLText* xmlText = new XMLText();

    xmlText->SetValue(text);

    element->InsertEndChild(xmlText);



    XMLError result = element->QueryUnsignedText(&value);

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_EQ(value, 4294967295u); // UINT_MAX

}
