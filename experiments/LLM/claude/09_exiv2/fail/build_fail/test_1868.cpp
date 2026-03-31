#include <gtest/gtest.h>
#include <string>
#include <vector>

// Include necessary headers from the project
#include "XMPCore_Impl.hpp"

class XMPNodeRemoveChildrenTest_1868 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that RemoveChildren on a node with no children does nothing and doesn't crash
TEST_F(XMPNodeRemoveChildrenTest_1868, RemoveChildrenOnEmptyNode_1868) {
    XMP_Node node(nullptr, "root", 0);
    EXPECT_TRUE(node.children.empty());
    node.RemoveChildren();
    EXPECT_TRUE(node.children.empty());
}

// Test that RemoveChildren clears a single child
TEST_F(XMPNodeRemoveChildrenTest_1868, RemoveChildrenWithSingleChild_1868) {
    XMP_Node node(nullptr, "root", 0);
    XMP_Node* child = new XMP_Node(&node, "child1", 0);
    node.children.push_back(child);
    EXPECT_EQ(node.children.size(), 1u);
    node.RemoveChildren();
    EXPECT_TRUE(node.children.empty());
}

// Test that RemoveChildren clears multiple children
TEST_F(XMPNodeRemoveChildrenTest_1868, RemoveChildrenWithMultipleChildren_1868) {
    XMP_Node node(nullptr, "root", 0);
    for (int i = 0; i < 5; ++i) {
        std::string name = "child" + std::to_string(i);
        XMP_Node* child = new XMP_Node(&node, name.c_str(), 0);
        node.children.push_back(child);
    }
    EXPECT_EQ(node.children.size(), 5u);
    node.RemoveChildren();
    EXPECT_TRUE(node.children.empty());
}

// Test that calling RemoveChildren twice is safe
TEST_F(XMPNodeRemoveChildrenTest_1868, RemoveChildrenCalledTwice_1868) {
    XMP_Node node(nullptr, "root", 0);
    XMP_Node* child = new XMP_Node(&node, "child1", 0);
    node.children.push_back(child);
    node.RemoveChildren();
    EXPECT_TRUE(node.children.empty());
    // Call again on already empty children
    node.RemoveChildren();
    EXPECT_TRUE(node.children.empty());
}

// Test that RemoveChildren does not affect qualifiers
TEST_F(XMPNodeRemoveChildrenTest_1868, RemoveChildrenDoesNotAffectQualifiers_1868) {
    XMP_Node node(nullptr, "root", 0);
    XMP_Node* child = new XMP_Node(&node, "child1", 0);
    XMP_Node* qualifier = new XMP_Node(&node, "qualifier1", 0);
    node.children.push_back(child);
    node.qualifiers.push_back(qualifier);
    EXPECT_EQ(node.children.size(), 1u);
    EXPECT_EQ(node.qualifiers.size(), 1u);
    node.RemoveChildren();
    EXPECT_TRUE(node.children.empty());
    EXPECT_EQ(node.qualifiers.size(), 1u);
    // Cleanup qualifiers manually to avoid leak
    node.RemoveQualifiers();
}

// Test that RemoveChildren does not affect the node's own name or value
TEST_F(XMPNodeRemoveChildrenTest_1868, RemoveChildrenPreservesNodeProperties_1868) {
    XMP_Node node(nullptr, "root", "rootvalue", 0);
    XMP_Node* child = new XMP_Node(&node, "child1", "childvalue", 0);
    node.children.push_back(child);
    node.RemoveChildren();
    EXPECT_EQ(node.name, "root");
    EXPECT_EQ(node.value, "rootvalue");
    EXPECT_TRUE(node.children.empty());
}

// Test RemoveChildren with children that have nested children (grandchildren)
TEST_F(XMPNodeRemoveChildrenTest_1868, RemoveChildrenWithNestedChildren_1868) {
    XMP_Node node(nullptr, "root", 0);
    XMP_Node* child = new XMP_Node(&node, "child1", 0);
    XMP_Node* grandchild = new XMP_Node(child, "grandchild1", 0);
    child->children.push_back(grandchild);
    node.children.push_back(child);
    EXPECT_EQ(node.children.size(), 1u);
    // RemoveChildren should delete the child (which should in turn handle grandchild via destructor)
    node.RemoveChildren();
    EXPECT_TRUE(node.children.empty());
}

// Test RemoveChildren with a large number of children
TEST_F(XMPNodeRemoveChildrenTest_1868, RemoveChildrenWithManyChildren_1868) {
    XMP_Node node(nullptr, "root", 0);
    const size_t numChildren = 100;
    for (size_t i = 0; i < numChildren; ++i) {
        std::string name = "child" + std::to_string(i);
        XMP_Node* child = new XMP_Node(&node, name.c_str(), 0);
        node.children.push_back(child);
    }
    EXPECT_EQ(node.children.size(), numChildren);
    node.RemoveChildren();
    EXPECT_TRUE(node.children.empty());
}

// Test that parent pointer is preserved after RemoveChildren
TEST_F(XMPNodeRemoveChildrenTest_1868, RemoveChildrenPreservesParent_1868) {
    XMP_Node parentNode(nullptr, "grandparent", 0);
    XMP_Node node(&parentNode, "parent", 0);
    XMP_Node* child = new XMP_Node(&node, "child1", 0);
    node.children.push_back(child);
    node.RemoveChildren();
    EXPECT_TRUE(node.children.empty());
    EXPECT_EQ(node.parent, &parentNode);
}

// Test RemoveChildren with children constructed using different constructors
TEST_F(XMPNodeRemoveChildrenTest_1868, RemoveChildrenWithDifferentConstructors_1868) {
    XMP_Node node(nullptr, "root", 0);
    
    // Child created with XMP_StringPtr name
    XMP_Node* child1 = new XMP_Node(&node, "child1", 0);
    
    // Child created with XMP_VarString name
    XMP_VarString name2 = "child2";
    XMP_Node* child2 = new XMP_Node(&node, name2, 0);
    
    // Child created with name and value (XMP_StringPtr)
    XMP_Node* child3 = new XMP_Node(&node, "child3", "value3", 0);
    
    // Child created with name and value (XMP_VarString)
    XMP_VarString name4 = "child4";
    XMP_VarString value4 = "value4";
    XMP_Node* child4 = new XMP_Node(&node, name4, value4, 0);
    
    node.children.push_back(child1);
    node.children.push_back(child2);
    node.children.push_back(child3);
    node.children.push_back(child4);
    
    EXPECT_EQ(node.children.size(), 4u);
    node.RemoveChildren();
    EXPECT_TRUE(node.children.empty());
}

// Test RemoveQualifiers clears qualifiers
TEST_F(XMPNodeRemoveChildrenTest_1868, RemoveQualifiersClearsQualifiers_1868) {
    XMP_Node node(nullptr, "root", 0);
    XMP_Node* qualifier = new XMP_Node(&node, "qual1", 0);
    node.qualifiers.push_back(qualifier);
    EXPECT_EQ(node.qualifiers.size(), 1u);
    node.RemoveQualifiers();
    EXPECT_TRUE(node.qualifiers.empty());
}

// Test ClearNode clears both children and qualifiers
TEST_F(XMPNodeRemoveChildrenTest_1868, ClearNodeClearsEverything_1868) {
    XMP_Node node(nullptr, "root", "somevalue", 0);
    XMP_Node* child = new XMP_Node(&node, "child1", 0);
    XMP_Node* qualifier = new XMP_Node(&node, "qual1", 0);
    node.children.push_back(child);
    node.qualifiers.push_back(qualifier);
    EXPECT_EQ(node.children.size(), 1u);
    EXPECT_EQ(node.qualifiers.size(), 1u);
    node.ClearNode();
    EXPECT_TRUE(node.children.empty());
    EXPECT_TRUE(node.qualifiers.empty());
}
