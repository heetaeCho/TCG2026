#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLDocumentTest_327 : public ::testing::Test {

protected:

    void SetUp() override {

        doc = new XMLDocument(false, Whitespace::COLLAPSE_WHITESPACE);

    }



    void TearDown() override {

        delete doc;

    }



    XMLDocument* doc;

};



TEST_F(XMLDocumentTest_327, Constructor_DefaultValues_327) {

    EXPECT_FALSE(doc->HasBOM());

    EXPECT_EQ(Whitespace::COLLAPSE_WHITESPACE, doc->WhitespaceMode());

}



TEST_F(XMLDocumentTest_327, NewElement_ReturnsValidPointer_327) {

    XMLElement* element = doc->NewElement("test");

    ASSERT_NE(nullptr, element);

    EXPECT_STREQ("test", element->Value());

    doc->DeleteNode(element);

}



TEST_F(XMLDocumentTest_327, NewComment_ReturnsValidPointer_327) {

    XMLComment* comment = doc->NewComment("test comment");

    ASSERT_NE(nullptr, comment);

    EXPECT_STREQ("test comment", comment->Value());

    doc->DeleteNode(comment);

}



TEST_F(XMLDocumentTest_327, NewText_ReturnsValidPointer_327) {

    XMLText* text = doc->NewText("test text");

    ASSERT_NE(nullptr, text);

    EXPECT_STREQ("test text", text->Value());

    doc->DeleteNode(text);

}



TEST_F(XMLDocumentTest_327, NewDeclaration_ReturnsValidPointer_327) {

    XMLDeclaration* declaration = doc->NewDeclaration("version=\"1.0\"");

    ASSERT_NE(nullptr, declaration);

    EXPECT_STREQ("version=\"1.0\"", declaration->Value());

    doc->DeleteNode(declaration);

}



TEST_F(XMLDocumentTest_327, NewUnknown_ReturnsValidPointer_327) {

    XMLUnknown* unknown = doc->NewUnknown("test unknown");

    ASSERT_NE(nullptr, unknown);

    EXPECT_STREQ("test unknown", unknown->Value());

    doc->DeleteNode(unknown);

}



TEST_F(XMLDocumentTest_327, RootElement_DefaultIsNull_327) {

    EXPECT_EQ(nullptr, doc->RootElement());

}



TEST_F(XMLDocumentTest_327, Error_DefaultIsNoError_327) {

    EXPECT_FALSE(doc->Error());

    EXPECT_EQ(XML_SUCCESS, doc->ErrorID());

    EXPECT_EQ(0, doc->ErrorLineNum());

    EXPECT_STREQ("XML_SUCCESS", doc->ErrorName());

    EXPECT_STREQ("", doc->ErrorStr());

}



TEST_F(XMLDocumentTest_327, SetBOM_ChecksValue_327) {

    doc->SetBOM(true);

    EXPECT_TRUE(doc->HasBOM());



    doc->SetBOM(false);

    EXPECT_FALSE(doc->HasBOM());

}
