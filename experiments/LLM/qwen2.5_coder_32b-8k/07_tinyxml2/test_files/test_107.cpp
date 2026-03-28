#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLDocumentTest_107 : public ::testing::Test {

protected:

    void SetUp() override {

        doc = new XMLDocument();

    }



    void TearDown() override {

        delete doc;

    }



    XMLDocument* doc;

};



TEST_F(XMLDocumentTest_107, ToDocumentReturnsSelf_107) {

    EXPECT_EQ(doc->ToDocument(), doc);

}



TEST_F(XMLDocumentTest_107, ProcessEntitiesDefaultIsFalse_107) {

    EXPECT_FALSE(doc->ProcessEntities());

}



TEST_F(XMLDocumentTest_107, WhitespaceModeDefaultIsPreserve_107) {

    EXPECT_EQ(doc->WhitespaceMode(), WHITESPACE_PRESERVE);

}



TEST_F(XMLDocumentTest_107, HasBOMDefaultIsFalse_107) {

    EXPECT_FALSE(doc->HasBOM());

}



TEST_F(XMLDocumentTest_107, SetBOMChangesValue_107) {

    doc->SetBOM(true);

    EXPECT_TRUE(doc->HasBOM());



    doc->SetBOM(false);

    EXPECT_FALSE(doc->HasBOM());

}



TEST_F(XMLDocumentTest_107, RootElementInitiallyNull_107) {

    EXPECT_EQ(doc->RootElement(), nullptr);

}



TEST_F(XMLDocumentTest_107, ErrorInitiallyFalse_107) {

    EXPECT_FALSE(doc->Error());

}



TEST_F(XMLDocumentTest_107, ErrorIDInitiallySuccess_107) {

    EXPECT_EQ(doc->ErrorID(), XML_SUCCESS);

}



TEST_F(XMLDocumentTest_107, ErrorLineNumInitiallyZero_107) {

    EXPECT_EQ(doc->ErrorLineNum(), 0);

}



TEST_F(XMLDocumentTest_107, ClearResetsErrorState_107) {

    doc->SetError(XML_ERROR_FILE_NOT_FOUND, 5, "File not found");

    EXPECT_TRUE(doc->Error());

    EXPECT_EQ(doc->ErrorID(), XML_ERROR_FILE_NOT_FOUND);



    doc->Clear();

    EXPECT_FALSE(doc->Error());

    EXPECT_EQ(doc->ErrorID(), XML_SUCCESS);

}



TEST_F(XMLDocumentTest_107, NewElementCreatesValidElement_107) {

    XMLElement* element = doc->NewElement("Test");

    EXPECT_NE(element, nullptr);

    EXPECT_STREQ(element->Value(), "Test");



    doc->DeleteNode(element);

}



TEST_F(XMLDocumentTest_107, DeleteNodeRemovesElement_107) {

    XMLElement* element = doc->NewElement("Test");

    doc->DeleteNode(element);



    EXPECT_EQ(doc->RootElement(), nullptr);

}



TEST_F(XMLDocumentTest_107, ErrorNameForSuccessIsCorrect_107) {

    EXPECT_STREQ(doc->ErrorName(), XML_NO_ERROR_ID);

}



TEST_F(XMLDocumentTest_107, ErrorStrInitiallyEmpty_107) {

    EXPECT_STREQ(doc->ErrorStr(), "");

}
