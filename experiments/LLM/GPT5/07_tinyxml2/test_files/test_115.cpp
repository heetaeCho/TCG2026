#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

// Test fixture for XMLDocument tests
class XMLDocumentTest_115 : public ::testing::Test {
protected:
    XMLDocument doc{true, Whitespace::PRESERVE}; // using processEntities = true, arbitrary whitespace mode
};

// Normal operation: newly constructed document should have error line number 0
TEST_F(XMLDocumentTest_115, ErrorLineNum_InitiallyZero_115) {
    EXPECT_EQ(doc.ErrorLineNum(), 0);
}

// Observable behavior: after a parsing error, ErrorLineNum should be > 0
TEST_F(XMLDocumentTest_115, ErrorLineNum_AfterParseError_115) {
    const char* invalidXml = "<root><unclosed></root>";
    XMLError err = doc.Parse(invalidXml, strlen(invalidXml));
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_GT(doc.ErrorLineNum(), 0);
}

// Boundary case: empty string should not produce an error line number
TEST_F(XMLDocumentTest_115, ErrorLineNum_EmptyString_115) {
    XMLError err = doc.Parse("", 0);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(doc.ErrorLineNum(), 0);
}

// Error handling: load from non-existent file should set error line number to 0 (observable behavior)
TEST_F(XMLDocumentTest_115, ErrorLineNum_NonExistentFile_115) {
    XMLError err = doc.LoadFile("nonexistent_file.xml");
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_EQ(doc.ErrorLineNum(), 0);
}

// Multiple operations: ErrorLineNum resets after ClearError
TEST_F(XMLDocumentTest_115, ErrorLineNum_ResetAfterClearError_115) {
    const char* invalidXml = "<root><unclosed></root>";
    XMLError err = doc.Parse(invalidXml, strlen(invalidXml));
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_GT(doc.ErrorLineNum(), 0);

    doc.ClearError();
    EXPECT_EQ(doc.ErrorLineNum(), 0);
}

// Root element: parsing a valid XML should keep error line number at 0
TEST_F(XMLDocumentTest_115, ErrorLineNum_AfterValidParse_115) {
    const char* validXml = "<root><child/></root>";
    XMLError err = doc.Parse(validXml, strlen(validXml));
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(doc.ErrorLineNum(), 0);
}
