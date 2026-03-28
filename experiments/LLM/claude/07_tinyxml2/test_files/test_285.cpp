#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLDocumentClearErrorTest_285 : public ::testing::Test {
protected:
    XMLDocument doc;
};

// Test that a freshly constructed document has no error
TEST_F(XMLDocumentClearErrorTest_285, NewDocumentHasNoError_285) {
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(XML_SUCCESS, doc.ErrorID());
    EXPECT_EQ(0, doc.ErrorLineNum());
}

// Test that ClearError resets error after a parsing error
TEST_F(XMLDocumentClearErrorTest_285, ClearErrorAfterParseError_285) {
    // Parse invalid XML to induce an error
    XMLError err = doc.Parse("<unclosed");
    EXPECT_NE(XML_SUCCESS, err);
    EXPECT_TRUE(doc.Error());
    EXPECT_NE(0, doc.ErrorID());

    // Now clear the error
    doc.ClearError();

    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(XML_SUCCESS, doc.ErrorID());
    EXPECT_EQ(0, doc.ErrorLineNum());
}

// Test that ClearError resets error after loading a nonexistent file
TEST_F(XMLDocumentClearErrorTest_285, ClearErrorAfterFileNotFound_285) {
    XMLError err = doc.LoadFile("nonexistent_file_that_does_not_exist_285.xml");
    EXPECT_NE(XML_SUCCESS, err);
    EXPECT_TRUE(doc.Error());

    doc.ClearError();

    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(XML_SUCCESS, doc.ErrorID());
    EXPECT_EQ(0, doc.ErrorLineNum());
}

// Test that ClearError on a document with no error is a no-op
TEST_F(XMLDocumentClearErrorTest_285, ClearErrorOnNoErrorDocument_285) {
    EXPECT_FALSE(doc.Error());

    doc.ClearError();

    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(XML_SUCCESS, doc.ErrorID());
    EXPECT_EQ(0, doc.ErrorLineNum());
}

// Test that ClearError works after empty document parse
TEST_F(XMLDocumentClearErrorTest_285, ClearErrorAfterEmptyDocumentParse_285) {
    XMLError err = doc.Parse("");
    EXPECT_NE(XML_SUCCESS, err);
    EXPECT_TRUE(doc.Error());

    doc.ClearError();

    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(XML_SUCCESS, doc.ErrorID());
    EXPECT_EQ(0, doc.ErrorLineNum());
}

// Test that ClearError resets ErrorStr (observable via ErrorStr returning empty/null-like)
TEST_F(XMLDocumentClearErrorTest_285, ClearErrorResetsErrorStr_285) {
    doc.Parse("<mismatched></wrong>");
    EXPECT_TRUE(doc.Error());
    // ErrorStr should be non-empty when there's an error
    const char* errStr = doc.ErrorStr();
    EXPECT_NE(nullptr, errStr);
    EXPECT_GT(strlen(errStr), 0u);

    doc.ClearError();

    // After clearing, ErrorStr should reflect no error
    const char* clearedStr = doc.ErrorStr();
    // It should either be null or empty
    if (clearedStr != nullptr) {
        EXPECT_EQ(0u, strlen(clearedStr));
    }
}

// Test that ClearError resets ErrorLineNum after a multi-line parse error
TEST_F(XMLDocumentClearErrorTest_285, ClearErrorResetsLineNum_285) {
    const char* xml = "<root>\n<child>\n</wrong>\n</root>";
    doc.Parse(xml);
    EXPECT_TRUE(doc.Error());
    // Error should be on a line > 0
    EXPECT_GT(doc.ErrorLineNum(), 0);

    doc.ClearError();

    EXPECT_EQ(0, doc.ErrorLineNum());
}

// Test multiple ClearError calls are idempotent
TEST_F(XMLDocumentClearErrorTest_285, MultipleClearErrorCalls_285) {
    doc.Parse("<bad");
    EXPECT_TRUE(doc.Error());

    doc.ClearError();
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(XML_SUCCESS, doc.ErrorID());

    doc.ClearError();
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(XML_SUCCESS, doc.ErrorID());
    EXPECT_EQ(0, doc.ErrorLineNum());
}

// Test ClearError followed by successful parse
TEST_F(XMLDocumentClearErrorTest_285, ClearErrorThenSuccessfulParse_285) {
    doc.Parse("<bad");
    EXPECT_TRUE(doc.Error());

    doc.ClearError();
    EXPECT_FALSE(doc.Error());

    XMLError err = doc.Parse("<root><child/></root>");
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(0, doc.ErrorLineNum());
}

// Test ClearError after mismatched element error
TEST_F(XMLDocumentClearErrorTest_285, ClearErrorAfterMismatchedElement_285) {
    XMLError err = doc.Parse("<a></b>");
    EXPECT_TRUE(doc.Error());
    EXPECT_EQ(XML_ERROR_MISMATCHED_ELEMENT, doc.ErrorID());

    doc.ClearError();

    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(XML_SUCCESS, doc.ErrorID());
    EXPECT_EQ(0, doc.ErrorLineNum());
}

// Test ErrorName after ClearError returns the success name
TEST_F(XMLDocumentClearErrorTest_285, ErrorNameAfterClearError_285) {
    doc.Parse("<bad");
    EXPECT_TRUE(doc.Error());

    doc.ClearError();

    const char* name = doc.ErrorName();
    EXPECT_NE(nullptr, name);
    // The error name for XML_SUCCESS
    const char* successName = XMLDocument::ErrorIDToName(XML_SUCCESS);
    EXPECT_STREQ(successName, name);
}
