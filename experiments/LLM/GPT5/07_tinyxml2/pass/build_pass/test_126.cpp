#include "tinyxml2.h"
#include <gtest/gtest.h>

using namespace tinyxml2;

// Helper fixture for XMLHandle tests
class XMLHandleTest_126 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLNode* parent = nullptr;
    XMLNode* child1 = nullptr;
    XMLNode* child2 = nullptr;

    void SetUp() override {
        parent = doc.NewElement("parent");
        doc.InsertEndChild(parent);

        child1 = doc.NewElement("child1");
        child2 = doc.NewElement("child2");

        parent->InsertEndChild(child1);
        parent->InsertEndChild(child2);
    }
};

// Test normal operation: NextSibling returns the next sibling node
TEST_F(XMLHandleTest_126, NextSiblingReturnsCorrectNode_126) {
    XMLHandle handle(child1);

    XMLHandle next = handle.NextSibling();

    // Expect the next sibling to be child2
    EXPECT_EQ(next.ToNode(), child2);
}

// Test boundary: NextSibling returns nullptr when there is no next sibling
TEST_F(XMLHandleTest_126, NextSiblingReturnsNullForLastChild_126) {
    XMLHandle handle(child2);

    XMLHandle next = handle.NextSibling();

    // Last child has no next sibling
    EXPECT_EQ(next.ToNode(), nullptr);
}

// Test boundary: NextSibling returns nullptr when handle wraps nullptr
TEST_F(XMLHandleTest_126, NextSiblingOnNullHandleReturnsNull_126) {
    XMLHandle handle(static_cast<XMLNode*>(nullptr));

    XMLHandle next = handle.NextSibling();

    EXPECT_EQ(next.ToNode(), nullptr);
}

// Test chaining NextSibling calls
TEST_F(XMLHandleTest_126, NextSiblingChaining_126) {
    XMLHandle handle(child1);

    XMLHandle next = handle.NextSibling().NextSibling();

    // child1 -> child2 -> nullptr
    EXPECT_EQ(next.ToNode(), nullptr);
}

// Test observable behavior: NextSibling does not alter original handle
TEST_F(XMLHandleTest_126, NextSiblingDoesNotModifyOriginalHandle_126) {
    XMLHandle handle(child1);

    XMLHandle next = handle.NextSibling();

    // Original handle should still point to child1
    EXPECT_EQ(handle.ToNode(), child1);
    EXPECT_EQ(next.ToNode(), child2);
}
