#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// Test fixture for XMLDocument
class XMLDocumentTest_116 : public ::testing::Test {
protected:
    XMLDocument doc;
};

// Test normal operation: calling ShallowClone with nullptr
TEST_F(XMLDocumentTest_116, ShallowCloneWithNullDocumentReturnsNull_116) {
    XMLNode* result = doc.ShallowClone(nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test normal operation: calling ShallowClone with a valid document pointer
TEST_F(XMLDocumentTest_116, ShallowCloneWithValidDocumentReturnsNull_116) {
    XMLDocument otherDoc;
    XMLNode* result = doc.ShallowClone(&otherDoc);
    EXPECT_EQ(result, nullptr);
}

// Test boundary case: multiple calls
TEST_F(XMLDocumentTest_116, MultipleShallowCloneCallsReturnNull_116) {
    XMLDocument otherDoc;
    EXPECT_EQ(doc.ShallowClone(&otherDoc), nullptr);
    EXPECT_EQ(doc.ShallowClone(nullptr), nullptr);
}
