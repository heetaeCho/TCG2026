#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLDocumentTest_268 : public ::testing::Test {

protected:

    void SetUp() override {

        doc = new XMLDocument(true, Whitespace::COLLAPSE_WHITESPACE);

    }



    void TearDown() override {

        delete doc;

    }



    XMLDocument* doc;

};



TEST_F(XMLDocumentTest_268, Constructor_DefaultValues_268) {

    EXPECT_EQ(doc->ProcessEntities(), true);

    EXPECT_EQ(doc->WhitespaceMode(), Whitespace::COLLAPSE_WHITESPACE);

    EXPECT_EQ(doc->HasBOM(), false);

}



TEST_F(XMLDocumentTest_268, NewElement_SuccessfulCreation_268) {

    XMLElement* element = doc->NewElement("test");

    EXPECT_NE(element, nullptr);

    EXPECT_STREQ(element->Value(), "test");

}



TEST_F(XMLDocumentTest_268, NewComment_SuccessfulCreation_268) {

    XMLComment* comment = doc->NewComment("This is a comment");

    EXPECT_NE(comment, nullptr);

    EXPECT_STREQ(comment->Value(), "This is a comment");

}



TEST_F(XMLDocumentTest_268, NewText_SuccessfulCreation_268) {

    XMLText* text = doc->NewText("Sample text");

    EXPECT_NE(text, nullptr);

    EXPECT_STREQ(text->Value(), "Sample text");

}



TEST_F(XMLDocumentTest_268, DeleteNode_NoCrashOnNull_268) {

    EXPECT_NO_THROW(doc->DeleteNode(nullptr));

}



TEST_F(XMLDocumentTest_268, Clear_ErrorCleared_268) {

    doc->SetError(XML_ERROR_FILE_READ_ERROR, 10, "File read error");

    EXPECT_EQ(doc->ErrorID(), XML_ERROR_FILE_READ_ERROR);

    doc->Clear();

    EXPECT_EQ(doc->ErrorID(), XML_SUCCESS);

}



TEST_F(XMLDocumentTest_268, Parse_InvalidXML_ReturnsError_268) {

    XMLError result = doc->Parse("<invalid_xml>", 14);

    EXPECT_NE(result, XML_SUCCESS);

}



TEST_F(XMLDocumentTest_268, ErrorStr_AfterParseError_IsNotEmpty_268) {

    doc->Parse("<invalid_xml>", 14);

    EXPECT_STRNE(doc->ErrorStr(), "");

}



TEST_F(XMLDocumentTest_268, SetBOM_GetBOM_Consistency_268) {

    doc->SetBOM(true);

    EXPECT_EQ(doc->HasBOM(), true);



    doc->SetBOM(false);

    EXPECT_EQ(doc->HasBOM(), false);

}



TEST_F(XMLDocumentTest_268, RootElement_AfterNewElement_ReturnsElement_268) {

    XMLElement* root = doc->NewElement("root");

    doc->InsertFirstChild(root);



    XMLElement* retrievedRoot = doc->RootElement();

    EXPECT_EQ(retrievedRoot, root);

}



TEST_F(XMLDocumentTest_268, RootElement_NoElements_ReturnsNull_268) {

    EXPECT_EQ(doc->RootElement(), nullptr);

}
