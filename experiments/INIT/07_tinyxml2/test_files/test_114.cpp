#include "tinyxml2.h"
#include <gtest/gtest.h>

using namespace tinyxml2;

// Test fixture for XMLDocument tests
class XMLDocumentTest_114 : public ::testing::Test {
protected:
    // Default setup: create a document with entities processing enabled and default whitespace
    XMLDocumentTest_114() : doc(true, Whitespace::WS_PRESERVE) {}
    XMLDocument doc;
};

// Test that a newly constructed document has ErrorID == XML_SUCCESS
TEST_F(XMLDocumentTest_114, ErrorID_DefaultIsSuccess_114) {
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
}

// Test that after parsing an empty string, ErrorID remains XML_SUCCESS (normal operation)
TEST_F(XMLDocumentTest_114, ErrorID_AfterParseEmptyString_114) {
    doc.Parse("", 0);
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);
}

// Test that after parsing invalid XML, ErrorID indicates an error (observable behavior)
TEST_F(XMLDocumentTest_114, ErrorID_AfterParseInvalidXML_114) {
    const char* invalidXML = "<root><unclosed></root>";
    doc.Parse(invalidXML, strlen(invalidXML));
    EXPECT_NE(doc.ErrorID(), XML_SUCCESS);  // should return some error ID
}

// Test that ErrorID is const-correct (can be called on const XMLDocument)
TEST_F(XMLDocumentTest_114, ErrorID_ConstDocumentCallable_114) {
    const XMLDocument& constDoc = doc;
    EXPECT_EQ(constDoc.ErrorID(), XML_SUCCESS);
}

// Test that after clearing errors, ErrorID resets to XML_SUCCESS
TEST_F(XMLDocumentTest_114, ErrorID_AfterClearError_114) {
    const char* invalidXML = "<root><unclosed></root>";
    doc.Parse(invalidXML, strlen(invalidXML));
    EXPECT_NE(doc.ErrorID(), XML_SUCCESS);  // ensure error occurred

    doc.ClearError();
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);  // ErrorID should be reset
}

// Test boundary: very large input string
TEST_F(XMLDocumentTest_114, ErrorID_AfterParseLargeInput_114) {
    std::string largeXML(100000, 'a');  // not valid XML, but just large
    doc.Parse(largeXML.c_str(), largeXML.size());
    EXPECT_NE(doc.ErrorID(), XML_SUCCESS);
}
