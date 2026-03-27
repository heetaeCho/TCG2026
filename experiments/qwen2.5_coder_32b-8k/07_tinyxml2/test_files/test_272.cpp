#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLDocumentTest_272 : public ::testing::Test {

protected:

    void SetUp() override {

        doc = new XMLDocument();

    }



    void TearDown() override {

        delete doc;

    }



    XMLDocument* doc;

};



TEST_F(XMLDocumentTest_272, NewElement_ReturnsNonNullPointer_272) {

    XMLElement* element = doc->NewElement("test");

    EXPECT_NE(element, nullptr);

}



TEST_F(XMLDocumentTest_272, NewElement_SetsCorrectName_272) {

    const char* name = "test";

    XMLElement* element = doc->NewElement(name);

    EXPECT_STREQ(element->Name(), name);

}



TEST_F(XMLDocumentTest_272, NewElement_WithEmptyString_ReturnsNonNullPointer_272) {

    XMLElement* element = doc->NewElement("");

    EXPECT_NE(element, nullptr);

}



TEST_F(XMLDocumentTest_272, NewElement_WithNullPtr_ReturnsNonNullPointer_272) {

    XMLElement* element = doc->NewElement(nullptr);

    EXPECT_NE(element, nullptr);

}
