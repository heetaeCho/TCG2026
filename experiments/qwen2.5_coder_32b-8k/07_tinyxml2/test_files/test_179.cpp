#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tinyxml2.h"



using namespace tinyxml2;

using ::testing::_;

using ::testing::IsNull;

using ::testing::NotNull;



class XMLDocumentTest : public ::testing::Test {

protected:

    XMLDocument doc;

    char buffer[1024];

    XMLNode* node;



    XMLDocumentTest() : doc(false, PRESERVE_WHITESPACE), node(nullptr) {}

};



TEST_F(XMLDocumentTest_179, Identify_EmptyString_ReturnsNullPointer_179) {

    strcpy(buffer, "");

    char* result = doc.Identify(buffer, &node, true);

    EXPECT_EQ(result, buffer);

    EXPECT_THAT(node, IsNull());

}



TEST_F(XMLDocumentTest_179, Identify_WhitespaceOnly_ReturnsEndOfBuffer_179) {

    strcpy(buffer, "   ");

    char* result = doc.Identify(buffer, &node, true);

    EXPECT_EQ(result, buffer + 3);

    EXPECT_THAT(node, IsNull());

}



TEST_F(XMLDocumentTest_179, Identify_XMLDeclaration_ReturnsEndOfHeader_179) {

    strcpy(buffer, "<?xml version=\"1.0\"?>");

    char* result = doc.Identify(buffer, &node, true);

    EXPECT_EQ(result, buffer + 20);

    EXPECT_THAT(node, NotNull());

}



TEST_F(XMLDocumentTest_179, Identify_Comment_ReturnsEndOfHeader_179) {

    strcpy(buffer, "<!-- This is a comment -->");

    char* result = doc.Identify(buffer, &node, true);

    EXPECT_EQ(result, buffer + 24);

    EXPECT_THAT(node, NotNull());

}



TEST_F(XMLDocumentTest_179, Identify_CDATA_ReturnsEndOfHeader_179) {

    strcpy(buffer, "<![CDATA[Some text]]>");

    char* result = doc.Identify(buffer, &node, true);

    EXPECT_EQ(result, buffer + 16);

    EXPECT_THAT(node, NotNull());

}



TEST_F(XMLDocumentTest_179, Identify_DTD_ReturnsEndOfHeader_179) {

    strcpy(buffer, "<!DOCTYPE root>");

    char* result = doc.Identify(buffer, &node, true);

    EXPECT_EQ(result, buffer + 15);

    EXPECT_THAT(node, NotNull());

}



TEST_F(XMLDocumentTest_179, Identify_Element_ReturnsEndOfHeader_179) {

    strcpy(buffer, "<element>");

    char* result = doc.Identify(buffer, &node, true);

    EXPECT_EQ(result, buffer + 9);

    EXPECT_THAT(node, NotNull());

}



TEST_F(XMLDocumentTest_179, Identify_Text_ReturnsSamePointer_179) {

    strcpy(buffer, "Some text");

    char* result = doc.Identify(buffer, &node, true);

    EXPECT_EQ(result, buffer);

    EXPECT_THAT(node, NotNull());

}
