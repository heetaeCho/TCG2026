#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLDocumentTest : public ::testing::Test {

protected:

    XMLDocument doc;

    

    XMLDocumentTest() : doc(false, Whitespace::COLLAPSE_WHITESPACE) {}

};



TEST_F(XMLDocumentTest_274, NewText_ReturnsValidPointer_274) {

    const char* text = "Sample Text";

    XMLText* xmlText = doc.NewText(text);

    EXPECT_NE(xmlText, nullptr);

}



TEST_F(XMLDocumentTest_274, NewText_SetsCorrectValue_274) {

    const char* text = "Sample Text";

    XMLText* xmlText = doc.NewText(text);

    EXPECT_STREQ(xmlText->Value(), text);

}



TEST_F(XMLDocumentTest_274, NewText_EmptyString_ReturnsValidPointer_274) {

    const char* emptyText = "";

    XMLText* xmlText = doc.NewText(emptyText);

    EXPECT_NE(xmlText, nullptr);

}



TEST_F(XMLDocumentTest_274, NewText_NullString_ReturnsNullPointer_274) {

    const char* nullText = nullptr;

    XMLText* xmlText = doc.NewText(nullText);

    EXPECT_EQ(xmlText, nullptr);

}
