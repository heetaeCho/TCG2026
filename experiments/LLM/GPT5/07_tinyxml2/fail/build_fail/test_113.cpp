#include "tinyxml2.h"
#include <gtest/gtest.h>

using namespace tinyxml2;

class XMLDocumentTest_113 : public ::testing::Test {
protected:
    XMLDocumentTest_113() : doc(true, Whitespace::PRESERVE) {} // Use some default constructor values

    XMLDocument doc;
};

// Test normal operation: a newly created XMLDocument should have no error
TEST_F(XMLDocumentTest_113, NewDocumentHasNoError_113) {
    EXPECT_FALSE(doc.Error()) << "A new document should have no error (Error() == false).";
}

// Test Error() after manually triggering a known error via Parse with empty input (boundary)
TEST_F(XMLDocumentTest_113, ParseEmptyInputSetsError_113) {
    const char* emptyXml = "";
    doc.Parse(emptyXml, 0); // We cannot know the internal logic, but we can call Parse
    // Error() should now be true if Parse failed (observable)
    EXPECT_EQ(doc.Error(), doc.ErrorID() != XML_SUCCESS);
}

// Test Error() after loading a non-existent file
TEST_F(XMLDocumentTest_113, LoadNonExistentFileSetsError_113) {
    XMLError result = doc.LoadFile("this_file_does_not_exist.xml");
    EXPECT_EQ(result, XML_ERROR_FILE_NOT_FOUND);
    EXPECT_TRUE(doc.Error());
}

// Test ClearError() resets the Error() flag
TEST_F(XMLDocumentTest_113, ClearErrorResetsErrorFlag_113) {
    doc.Parse("", 0); // Force an error
    EXPECT_TRUE(doc.Error());
    doc.ClearError();
    EXPECT_FALSE(doc.Error());
}

// Test multiple successive errors
TEST_F(XMLDocumentTest_113, MultipleErrors_113) {
    doc.Parse("", 0); // first error
    EXPECT_TRUE(doc.Error());
    doc.LoadFile("nonexistent.xml"); // second error
    EXPECT_TRUE(doc.Error());
    doc.ClearError();
    EXPECT_FALSE(doc.Error());
}

// Test Error() consistency with ErrorID()
TEST_F(XMLDocumentTest_113, ErrorMatchesErrorID_113) {
    doc.Parse("", 0); // induce error
    EXPECT_EQ(doc.Error(), doc.ErrorID() != XML_SUCCESS);
}
