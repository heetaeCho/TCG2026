#include "tinyxml2.h"
#include <gtest/gtest.h>

using namespace tinyxml2;

// Fixture for XMLHandle tests
class XMLHandleTest_124 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLNode* parent = nullptr;
    XMLNode* firstChild = nullptr;
    XMLNode* secondChild = nullptr;
    XMLNode* thirdChild = nullptr;

    void SetUp() override {
        parent = doc.NewElement("Parent");
        doc.InsertEndChild(parent);

        firstChild = doc.NewElement("Child1");
        secondChild = doc.NewElement("Child2");
        thirdChild = doc.NewElement("Child3");

        parent->InsertEndChild(firstChild);
        parent->InsertEndChild(secondChild);
        parent->InsertEndChild(thirdChild);
    }
};

// Test: PreviousSibling of middle node returns correct sibling
TEST_F(XMLHandleTest_124, PreviousSibling_MiddleNode_ReturnsFirstChild_124) {
    XMLHandle handle(secondChild);
    XMLHandle prev = handle.PreviousSibling();
    EXPECT_EQ(prev.ToNode(), firstChild);
}

// Test: PreviousSibling of first node returns null
TEST_F(XMLHandleTest_124, PreviousSibling_FirstNode_ReturnsNull_124) {
    XMLHandle handle(firstChild);
    XMLHandle prev = handle.PreviousSibling();
    EXPECT_EQ(prev.ToNode(), nullptr);
}

// Test: PreviousSibling of last node returns middle node
TEST_F(XMLHandleTest_124, PreviousSibling_LastNode_ReturnsMiddleChild_124) {
    XMLHandle handle(thirdChild);
    XMLHandle prev = handle.PreviousSibling();
    EXPECT_EQ(prev.ToNode(), secondChild);
}

// Test: PreviousSibling of handle wrapping nullptr returns handle wrapping nullptr
TEST_F(XMLHandleTest_124, PreviousSibling_NullHandle_ReturnsNullHandle_124) {
    XMLHandle handle(nullptr);
    XMLHandle prev = handle.PreviousSibling();
    EXPECT_EQ(prev.ToNode(), nullptr);
}

// Test: Chain of PreviousSibling calls returns nodes in reverse order
TEST_F(XMLHandleTest_124, PreviousSibling_Chain_ReturnsNodesInReverse_124) {
    XMLHandle handle(thirdChild);

    XMLHandle second = handle.PreviousSibling();
    EXPECT_EQ(second.ToNode(), secondChild);

    XMLHandle first = second.PreviousSibling();
    EXPECT_EQ(first.ToNode(), firstChild);

    XMLHandle none = first.PreviousSibling();
    EXPECT_EQ(none.ToNode(), nullptr);
}
