#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tinyxml2.h"



using namespace tinyxml2;

using ::testing::Eq;



class XMLDocumentTest_115 : public ::testing::Test {

protected:

    XMLDocument doc{false, Whitespace::preserve};

};



TEST_F(XMLDocumentTest_115, ErrorLineNumInitiallyZero_115) {

    EXPECT_EQ(doc.ErrorLineNum(), 0);

}



TEST_F(XMLDocumentTest_115, ParseValidXMLNoError_115) {

    const char* xml = R"(<root></root>)";

    XMLError result = doc.Parse(xml, strlen(xml));

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_EQ(doc.ErrorLineNum(), 0);

}



TEST_F(XMLDocumentTest_115, ParseInvalidXMLWithErrorLine_115) {

    const char* xml = R"(<root>)";

    XMLError result = doc.Parse(xml, strlen(xml));

    EXPECT_NE(result, XML_SUCCESS);

    EXPECT_EQ(doc.ErrorLineNum(), 1); // Assuming error occurs at line 1

}



TEST_F(XMLDocumentTest_115, LoadNonExistentFileSetsErrorLine_115) {

    XMLError result = doc.LoadFile("non_existent_file.xml");

    EXPECT_NE(result, XML_SUCCESS);

    EXPECT_EQ(doc.ErrorLineNum(), 0); // File reading error typically doesn't have a line number

}



TEST_F(XMLDocumentTest_115, ClearErrorResetsErrorLine_115) {

    const char* xml = R"(<root>)";

    XMLError result = doc.Parse(xml, strlen(xml));

    EXPECT_NE(result, XML_SUCCESS);

    EXPECT_EQ(doc.ErrorLineNum(), 1); // Assuming error occurs at line 1

    doc.ClearError();

    EXPECT_EQ(doc.ErrorID(), XML_NO_ERROR);

    EXPECT_EQ(doc.ErrorLineNum(), 0);

}



TEST_F(XMLDocumentTest_115, ProcessEntitiesFalseByDefault_115) {

    EXPECT_FALSE(doc.ProcessEntities());

}



TEST_F(XMLDocumentTest_115, WhitespaceModePreserveByConstructor_115) {

    EXPECT_EQ(doc.WhitespaceMode(), Whitespace::preserve);

}
