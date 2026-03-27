#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLHandleTest_122 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLNode* rootNode = nullptr;

    void SetUp() override {
        rootNode = doc.NewElement("Root");
        doc.InsertEndChild(rootNode);
    }
};

// Test that LastChild() returns a handle to the last child when children exist
TEST_F(XMLHandleTest_122, LastChildReturnsCorrectNode_122) {
    XMLNode* child1 = doc.NewElement("Child1");
    XMLNode* child2 = doc.NewElement("Child2");

    rootNode->InsertEndChild(child1);
    rootNode->InsertEndChild(child2);

    XMLHandle handle(rootNode);
    XMLHandle lastChildHandle = handle.LastChild();

    EXPECT_EQ(lastChildHandle.ToNode(), child2);
}

// Test LastChild() on a node with no children returns null node
TEST_F(XMLHandleTest_122, LastChildOnEmptyNodeReturnsNull_122) {
    XMLHandle handle(rootNode);
    XMLHandle lastChildHandle = handle.LastChild();

    EXPECT_EQ(lastChildHandle.ToNode(), nullptr);
}

// Test LastChild() on a null handle returns a null handle
TEST_F(XMLHandleTest_122, LastChildOnNullHandleReturnsNull_122) {
    XMLHandle nullHandle(static_cast<XMLNode*>(nullptr));
    XMLHandle lastChildHandle = nullHandle.LastChild();

    EXPECT_EQ(lastChildHandle.ToNode(), nullptr);
}

// Test chaining LastChild() after FirstChild() returns the last child correctly
TEST_F(XMLHandleTest_122, LastChildChainedAfterFirstChild_122) {
    XMLNode* child1 = doc.NewElement("Child1");
    XMLNode* child2 = doc.NewElement("Child2");

    rootNode->InsertEndChild(child1);
    rootNode->InsertEndChild(child2);

    XMLHandle handle(rootNode);
    XMLHandle lastChildHandle = handle.FirstChild().LastChild();

    // Since FirstChild() returns handle to first child (child1), and it has no children, LastChild() should return nullptr
    EXPECT_EQ(lastChildHandle.ToNode(), nullptr);
}

// Test that LastChild() on XMLHandle copied from another handle behaves the same
TEST_F(XMLHandleTest_122, LastChildOnCopiedHandle_122) {
    XMLNode* child1 = doc.NewElement("Child1");
    XMLNode* child2 = doc.NewElement("Child2");

    rootNode->InsertEndChild(child1);
    rootNode->InsertEndChild(child2);

    XMLHandle originalHandle(rootNode);
    XMLHandle copiedHandle(originalHandle);

    XMLHandle lastChildOriginal = originalHandle.LastChild();
    XMLHandle lastChildCopied = copiedHandle.LastChild();

    EXPECT_EQ(lastChildOriginal.ToNode(), child2);
    EXPECT_EQ(lastChildCopied.ToNode(), child2);
}
