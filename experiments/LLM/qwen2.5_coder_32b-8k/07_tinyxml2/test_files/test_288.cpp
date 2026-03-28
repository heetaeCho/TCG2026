#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLDocumentTest_288 : public ::testing::Test {

protected:

    void SetUp() override {

        doc = new XMLDocument(false, Whitespace::preserve);

    }



    void TearDown() override {

        delete doc;

    }



    XMLDocument* doc;

};



TEST_F(XMLDocumentTest_288, ParseValidXMLString_288) {

    const char* xml = "<root><child>Text</child></root>";

    XMLError result = doc->Parse(xml, strlen(xml));

    EXPECT_EQ(result, XML_SUCCESS);

}



TEST_F(XMLDocumentTest_288, ParseInvalidXMLString_288) {

    const char* invalidXml = "<root><child>Text</child>";

    XMLError result = doc->Parse(invalidXml, strlen(invalidXml));

    EXPECT_NE(result, XML_SUCCESS);

}



TEST_F(XMLDocumentTest_288, LoadFileNonExistentFile_288) {

    XMLError result = doc->LoadFile("non_existent_file.xml");

    EXPECT_EQ(result, XML_ERROR_FILE_NOT_FOUND);

}



TEST_F(XMLDocumentTest_288, CreateNewElement_288) {

    XMLElement* element = doc->NewElement("testElement");

    ASSERT_NE(element, nullptr);

    EXPECT_STREQ(element->Value(), "testElement");

}



TEST_F(XMLDocumentTest_288, CreateNewComment_288) {

    XMLComment* comment = doc->NewComment("This is a test comment");

    ASSERT_NE(comment, nullptr);

    EXPECT_STREQ(comment->Value(), "This is a test comment");

}



TEST_F(XMLDocumentTest_288, CreateNewText_288) {

    XMLText* text = doc->NewText("Sample text content");

    ASSERT_NE(text, nullptr);

    EXPECT_STREQ(text->Value(), "Sample text content");

}



TEST_F(XMLDocumentTest_288, ClearErrorAfterParseFailure_288) {

    const char* invalidXml = "<root><child>Text</child>";

    XMLError result = doc->Parse(invalidXml, strlen(invalidXml));

    EXPECT_NE(result, XML_SUCCESS);

    doc->ClearError();

    EXPECT_EQ(doc->ErrorID(), XML_SUCCESS);

}



TEST_F(XMLDocumentTest_288, ErrorNameAndStrAfterParseFailure_288) {

    const char* invalidXml = "<root><child>Text</child>";

    XMLError result = doc->Parse(invalidXml, strlen(invalidXml));

    EXPECT_NE(result, XML_SUCCESS);

    EXPECT_STREQ(doc->ErrorName(), "XML_ERROR_PARSING_ELEMENT");

    EXPECT_STRNE(doc->ErrorStr(), "");

}
