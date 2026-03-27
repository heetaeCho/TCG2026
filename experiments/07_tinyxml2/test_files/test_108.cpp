#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLDocumentTest_108 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize with default values for processEntities and whitespaceMode

        xmlDoc = new XMLDocument(false, Whitespace::preserve);

    }



    void TearDown() override {

        delete xmlDoc;

    }



    XMLDocument* xmlDoc;

};



TEST_F(XMLDocumentTest_108, ProcessEntitiesDefault_108) {

    EXPECT_FALSE(xmlDoc->ProcessEntities());

}



TEST_F(XMLDocumentTest_108, ProcessEntitiesTrue_108) {

    XMLDocument doc(true, Whitespace::preserve);

    EXPECT_TRUE(doc.ProcessEntities());

}



TEST_F(XMLDocumentTest_108, ProcessEntitiesFalse_108) {

    XMLDocument doc(false, Whitespace::preserve);

    EXPECT_FALSE(doc.ProcessEntities());

}



TEST_F(XMLDocumentTest_108, WhitespaceModeDefault_108) {

    EXPECT_EQ(xmlDoc->WhitespaceMode(), Whitespace::preserve);

}



TEST_F(XMLDocumentTest_108, WhitespaceModeCollapse_108) {

    XMLDocument doc(false, Whitespace::collapse);

    EXPECT_EQ(doc.WhitespaceMode(), Whitespace::collapse);

}



TEST_F(XMLDocumentTest_108, ErrorInitialValue_108) {

    EXPECT_FALSE(xmlDoc->Error());

}



TEST_F(XMLDocumentTest_108, ErrorIDInitialValue_108) {

    EXPECT_EQ(xmlDoc->ErrorID(), XML_SUCCESS);

}



TEST_F(XMLDocumentTest_108, RootElementInitiallyNull_108) {

    EXPECT_EQ(xmlDoc->RootElement(), nullptr);

}



// Assuming LoadFile and SaveFile would set an error if the file operations fail

// These tests are based on observable behavior of setting errors.

TEST_F(XMLDocumentTest_108, LoadNonExistentFileSetsError_108) {

    XMLError result = xmlDoc->LoadFile("non_existent_file.xml");

    EXPECT_NE(result, XML_SUCCESS);

    EXPECT_TRUE(xmlDoc->Error());

}



// Assuming SaveFile to a non-writable location would set an error

TEST_F(XMLDocumentTest_108, SaveToNonWritableLocationSetsError_108) {

    XMLError result = xmlDoc->SaveFile("/non_writable_location/output.xml", false);

    EXPECT_NE(result, XML_SUCCESS);

    EXPECT_TRUE(xmlDoc->Error());

}



// Assuming Parse with invalid XML would set an error

TEST_F(XMLDocumentTest_108, ParseInvalidXMLSetsError_108) {

    const char* invalidXml = "<invalid><tag></invalid>";

    XMLError result = xmlDoc->Parse(invalidXml, strlen(invalidXml));

    EXPECT_NE(result, XML_SUCCESS);

    EXPECT_TRUE(xmlDoc->Error());

}



// Assuming Parse with valid XML would not set an error

TEST_F(XMLDocumentTest_108, ParseValidXMLNoError_108) {

    const char* validXml = "<root><tag></tag></root>";

    XMLError result = xmlDoc->Parse(validXml, strlen(validXml));

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_FALSE(xmlDoc->Error());

}



TEST_F(XMLDocumentTest_108, NewElementReturnsNonNull_108) {

    XMLElement* element = xmlDoc->NewElement("test");

    EXPECT_NE(element, nullptr);

}



TEST_F(XMLDocumentTest_108, NewCommentReturnsNonNull_108) {

    XMLComment* comment = xmlDoc->NewComment("test comment");

    EXPECT_NE(comment, nullptr);

}



TEST_F(XMLDocumentTest_108, NewTextReturnsNonNull_108) {

    XMLText* text = xmlDoc->NewText("test text");

    EXPECT_NE(text, nullptr);

}



TEST_F(XMLDocumentTest_108, NewDeclarationReturnsNonNull_108) {

    XMLDeclaration* declaration = xmlDoc->NewDeclaration("version=\"1.0\"");

    EXPECT_NE(declaration, nullptr);

}



TEST_F(XMLDocumentTest_108, NewUnknownReturnsNonNull_108) {

    XMLUnknown* unknown = xmlDoc->NewUnknown("<unknown></unknown>");

    EXPECT_NE(unknown, nullptr);

}
