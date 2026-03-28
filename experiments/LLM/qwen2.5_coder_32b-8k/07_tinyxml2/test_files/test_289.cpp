#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLDocumentTest_289 : public ::testing::Test {

protected:

    void SetUp() override {

        doc = new XMLDocument(false, Whitespace::preserve);

    }



    void TearDown() override {

        delete doc;

    }



    XMLDocument* doc;

};



TEST_F(XMLDocumentTest_289, Constructor_DefaultValues_289) {

    EXPECT_FALSE(doc->ProcessEntities());

    EXPECT_EQ(doc->WhitespaceMode(), Whitespace::preserve);

}



TEST_F(XMLDocumentTest_289, ErrorName_DefaultErrorID_289) {

    EXPECT_STREQ(doc->ErrorName(), "XML_SUCCESS");

}



TEST_F(XMLDocumentTest_289, Parse_EmptyString_NoError_289) {

    XMLError result = doc->Parse("", 0);

    EXPECT_EQ(result, XML_SUCCESS);

}



TEST_F(XMLDocumentTest_289, Parse_InvalidXML_ErrorSet_289) {

    XMLError result = doc->Parse("<invalid>", strlen("<invalid>"));

    EXPECT_NE(result, XML_SUCCESS);

    EXPECT_STRNE(doc->ErrorName(), "XML_SUCCESS");

}



TEST_F(XMLDocumentTest_289, LoadFile_NonExistentFile_ErrorSet_289) {

    XMLError result = doc->LoadFile("non_existent_file.xml");

    EXPECT_NE(result, XML_SUCCESS);

    EXPECT_STRNE(doc->ErrorName(), "XML_SUCCESS");

}



TEST_F(XMLDocumentTest_289, SaveFile_NullPointer_ReturnsError_289) {

    XMLError result = doc->SaveFile(nullptr, false);

    EXPECT_NE(result, XML_SUCCESS);

    EXPECT_STRNE(doc->ErrorName(), "XML_SUCCESS");

}



TEST_F(XMLDocumentTest_289, ClearError_ResetsErrorID_289) {

    doc->Parse("<invalid>", strlen("<invalid>"));

    doc->ClearError();

    EXPECT_EQ(doc->ErrorID(), XML_SUCCESS);

}



TEST_F(XMLDocumentTest_289, NewElement_ReturnsNonNull_289) {

    XMLElement* element = doc->NewElement("test");

    EXPECT_NE(element, nullptr);

}



TEST_F(XMLDocumentTest_289, NewComment_ReturnsNonNull_289) {

    XMLComment* comment = doc->NewComment("test");

    EXPECT_NE(comment, nullptr);

}



TEST_F(XMLDocumentTest_289, NewText_ReturnsNonNull_289) {

    XMLText* text = doc->NewText("test");

    EXPECT_NE(text, nullptr);

}



TEST_F(XMLDocumentTest_289, NewDeclaration_ReturnsNonNull_289) {

    XMLDeclaration* declaration = doc->NewDeclaration("test");

    EXPECT_NE(declaration, nullptr);

}



TEST_F(XMLDocumentTest_289, NewUnknown_ReturnsNonNull_289) {

    XMLUnknown* unknown = doc->NewUnknown("test");

    EXPECT_NE(unknown, nullptr);

}



TEST_F(XMLDocumentTest_289, DeleteNode_NoCrash_289) {

    XMLElement* element = doc->NewElement("test");

    doc->DeleteNode(element);

    // No crash expected

}



TEST_F(XMLDocumentTest_289, HasBOM_DefaultValue_False_289) {

    EXPECT_FALSE(doc->HasBOM());

}



TEST_F(XMLDocumentTest_289, SetBOM_ChangesValue_289) {

    doc->SetBOM(true);

    EXPECT_TRUE(doc->HasBOM());

}
