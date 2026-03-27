#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLDocumentTest_275 : public ::testing::Test {

protected:

    XMLDocument* doc;



    void SetUp() override {

        doc = new XMLDocument();

    }



    void TearDown() override {

        delete doc;

    }

};



TEST_F(XMLDocumentTest_275, NewDeclaration_DefaultValue_275) {

    XMLDeclaration* dec = doc->NewDeclaration(nullptr);

    ASSERT_STREQ(dec->Value(), "xml version=\"1.0\" encoding=\"UTF-8\"");

}



TEST_F(XMLDocumentTest_275, NewDeclaration_CustomValue_275) {

    const char* customStr = "version=\"1.1\" encoding=\"ISO-8859-1\"";

    XMLDeclaration* dec = doc->NewDeclaration(customStr);

    ASSERT_STREQ(dec->Value(), customStr);

}



TEST_F(XMLDocumentTest_275, NewDeclaration_EmptyString_275) {

    const char* emptyStr = "";

    XMLDeclaration* dec = doc->NewDeclaration(emptyStr);

    ASSERT_STREQ(dec->Value(), "");

}
