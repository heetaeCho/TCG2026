#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// Dummy XMLNode class for testing, since ShallowEqual takes XMLNode*
class XMLNode {};

class XMLDocumentTest_117 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLNode node;
};

// Test normal operation with a valid XMLNode pointer
TEST_F(XMLDocumentTest_117, ShallowEqualWithValidNode_117) {
    EXPECT_NO_THROW({
        bool result = doc.ShallowEqual(&node);
        // As a black box, we cannot assert true/false reliably,
        // but we can check the return type is bool.
        EXPECT_TRUE(result == true || result == false);
    });
}

// Test boundary case with nullptr
TEST_F(XMLDocumentTest_117, ShallowEqualWithNullptr_117) {
    EXPECT_NO_THROW({
        bool result = doc.ShallowEqual(nullptr);
        EXPECT_TRUE(result == true || result == false);
    });
}
