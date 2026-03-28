#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

// Test that ShallowClone returns null (0) when called with nullptr
TEST(XMLDocumentTest_116, ShallowCloneReturnsNullWithNullptr_116) {
    XMLDocument doc;
    XMLNode* result = doc.ShallowClone(nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test that ShallowClone returns null (0) when called with a valid document pointer
TEST(XMLDocumentTest_116, ShallowCloneReturnsNullWithValidDocument_116) {
    XMLDocument doc;
    XMLDocument otherDoc;
    XMLNode* result = doc.ShallowClone(&otherDoc);
    EXPECT_EQ(result, nullptr);
}

// Test that ShallowClone returns null (0) when called with self
TEST(XMLDocumentTest_116, ShallowCloneReturnsNullWithSelf_116) {
    XMLDocument doc;
    XMLNode* result = doc.ShallowClone(&doc);
    EXPECT_EQ(result, nullptr);
}

// Test that ShallowClone consistently returns null on multiple calls
TEST(XMLDocumentTest_116, ShallowCloneConsistentlyReturnsNull_116) {
    XMLDocument doc;
    XMLDocument otherDoc;
    
    XMLNode* result1 = doc.ShallowClone(&otherDoc);
    XMLNode* result2 = doc.ShallowClone(&otherDoc);
    XMLNode* result3 = doc.ShallowClone(nullptr);
    
    EXPECT_EQ(result1, nullptr);
    EXPECT_EQ(result2, nullptr);
    EXPECT_EQ(result3, nullptr);
}

// Test multiple XMLDocument instances all return null from ShallowClone
TEST(XMLDocumentTest_116, MultipleDocumentsShallowCloneReturnsNull_116) {
    XMLDocument doc1;
    XMLDocument doc2;
    XMLDocument doc3;
    
    EXPECT_EQ(doc1.ShallowClone(&doc2), nullptr);
    EXPECT_EQ(doc2.ShallowClone(&doc3), nullptr);
    EXPECT_EQ(doc3.ShallowClone(&doc1), nullptr);
}
