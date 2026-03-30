#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLDocumentTest_110 : public ::testing::Test {

protected:

    XMLDocument* doc;

    

    void SetUp() override {

        doc = new XMLDocument();

    }

    

    void TearDown() override {

        delete doc;

    }

};



TEST_F(XMLDocumentTest_110, HasBOM_DefaultValue_110) {

    EXPECT_FALSE(doc->HasBOM());

}



TEST_F(XMLDocumentTest_110, SetBOM_ToggleValue_110) {

    doc->SetBOM(true);

    EXPECT_TRUE(doc->HasBOM());



    doc->SetBOM(false);

    EXPECT_FALSE(doc->HasBOM());

}



TEST_F(XMLDocumentTest_110, ProcessEntities_DefaultValue_110) {

    XMLDocument defaultDoc;

    EXPECT_EQ(defaultDoc.ProcessEntities(), false);



    XMLDocument entitiesDoc(true, COLLAPSE_WHITESPACE);

    EXPECT_EQ(entitiesDoc.ProcessEntities(), true);

}



TEST_F(XMLDocumentTest_110, WhitespaceMode_DefaultValue_110) {

    XMLDocument defaultDoc;

    EXPECT_EQ(defaultDoc.WhitespaceMode(), PRESERVE_WHITESPACE);



    XMLDocument collapseDoc(false, COLLAPSE_WHITESPACE);

    EXPECT_EQ(collapseDoc.WhitespaceMode(), COLLAPSE_WHITESPACE);

}



TEST_F(XMLDocumentTest_110, Error_DefaultValue_110) {

    EXPECT_FALSE(doc->Error());

}



TEST_F(XMLDocumentTest_110, ErrorID_DefaultValue_110) {

    EXPECT_EQ(doc->ErrorID(), XML_SUCCESS);

}



TEST_F(XMLDocumentTest_110, ErrorStr_DefaultValue_110) {

    EXPECT_STREQ(doc->ErrorStr(), "");

}



TEST_F(XMLDocumentTest_110, ErrorLineNum_DefaultValue_110) {

    EXPECT_EQ(doc->ErrorLineNum(), 0);

}
