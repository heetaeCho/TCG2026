#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLDocumentTest_108 : public ::testing::Test {
protected:
    // Helper to create documents with processEntities = true or false
    XMLDocument* CreateDocument(bool processEntities) {
        return new XMLDocument(processEntities, XMLDocument::Whitespace::PRESERVE);
    }
};

// Test normal behavior: ProcessEntities returns true when constructed with true
TEST_F(XMLDocumentTest_108, ProcessEntitiesReturnsTrueWhenConstructedTrue_108) {
    XMLDocument* doc = CreateDocument(true);
    EXPECT_TRUE(doc->ProcessEntities());
    delete doc;
}

// Test normal behavior: ProcessEntities returns false when constructed with false
TEST_F(XMLDocumentTest_108, ProcessEntitiesReturnsFalseWhenConstructedFalse_108) {
    XMLDocument* doc = CreateDocument(false);
    EXPECT_FALSE(doc->ProcessEntities());
    delete doc;
}

// Boundary / consistency check: multiple calls return the same value
TEST_F(XMLDocumentTest_108, ProcessEntitiesConsistentAcrossCalls_108) {
    XMLDocument* doc = CreateDocument(true);
    bool firstCall = doc->ProcessEntities();
    bool secondCall = doc->ProcessEntities();
    EXPECT_EQ(firstCall, secondCall);
    delete doc;
}

// Test interaction: verify that calling ProcessEntities does not modify the document (observable const behavior)
TEST_F(XMLDocumentTest_108, ProcessEntitiesDoesNotModifyDocument_108) {
    XMLDocument* doc = CreateDocument(true);
    // Call ProcessEntities multiple times, expect the same observable behavior
    EXPECT_TRUE(doc->ProcessEntities());
    EXPECT_TRUE(doc->ProcessEntities());
    delete doc;
}
