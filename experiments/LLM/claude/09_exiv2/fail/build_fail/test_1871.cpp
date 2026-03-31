#include <gtest/gtest.h>
#include <string>
#include <vector>

// Include necessary headers from the project
#include "XMPCore_Impl.hpp"

class XMPNodeTest_1871 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Construction with parent=nullptr, C-string name, and options
TEST_F(XMPNodeTest_1871, ConstructWithCStringNameAndOptions_1871) {
    XMP_Node node(nullptr, "testName", 0);
    EXPECT_EQ(node.name, "testName");
    EXPECT_EQ(node.value, "");
    EXPECT_EQ(node.parent, nullptr);
    EXPECT_EQ(node.options, 0u);
    EXPECT_TRUE(node.children.empty());
    EXPECT_TRUE(node.qualifiers.empty());
}

// Test: Construction with parent=nullptr, std::string name, and options
TEST_F(XMPNodeTest_1871, ConstructWithVarStringNameAndOptions_1871) {
    XMP_VarString nameStr("testVarName");
    XMP_Node node(nullptr, nameStr, 0);
    EXPECT_EQ(node.name, "testVarName");
    EXPECT_EQ(node.value, "");
    EXPECT_EQ(node.parent, nullptr);
    EXPECT_EQ(node.options, 0u);
}

// Test: Construction with C-string name and C-string value
TEST_F(XMPNodeTest_1871, ConstructWithCStringNameAndValue_1871) {
    XMP_Node node(nullptr, "nodeName", "nodeValue", 0);
    EXPECT_EQ(node.name, "nodeName");
    EXPECT_EQ(node.value, "nodeValue");
    EXPECT_EQ(node.parent, nullptr);
    EXPECT_EQ(node.options, 0u);
}

// Test: Construction with VarString name and VarString value
TEST_F(XMPNodeTest_1871, ConstructWithVarStringNameAndValue_1871) {
    XMP_VarString nameStr("varName");
    XMP_VarString valueStr("varValue");
    XMP_Node node(nullptr, nameStr, valueStr, 0);
    EXPECT_EQ(node.name, "varName");
    EXPECT_EQ(node.value, "varValue");
    EXPECT_EQ(node.parent, nullptr);
}

// Test: Parent pointer is correctly set
TEST_F(XMPNodeTest_1871, ParentPointerIsSet_1871) {
    XMP_Node parentNode(nullptr, "parent", 0);
    XMP_Node childNode(&parentNode, "child", 0);
    EXPECT_EQ(childNode.parent, &parentNode);
}

// Test: Options are correctly stored
TEST_F(XMPNodeTest_1871, OptionsAreStoredCorrectly_1871) {
    XMP_Node node(nullptr, "test", 0x1234);
    EXPECT_EQ(node.options, 0x1234u);
}

// Test: Empty name construction
TEST_F(XMPNodeTest_1871, EmptyNameConstruction_1871) {
    XMP_Node node(nullptr, "", 0);
    EXPECT_EQ(node.name, "");
    EXPECT_TRUE(node.name.empty());
}

// Test: Empty value construction
TEST_F(XMPNodeTest_1871, EmptyValueConstruction_1871) {
    XMP_Node node(nullptr, "name", "", 0);
    EXPECT_EQ(node.value, "");
    EXPECT_TRUE(node.value.empty());
}

// Test: RemoveChildren on node with no children
TEST_F(XMPNodeTest_1871, RemoveChildrenOnEmptyNode_1871) {
    XMP_Node node(nullptr, "test", 0);
    EXPECT_TRUE(node.children.empty());
    node.RemoveChildren();
    EXPECT_TRUE(node.children.empty());
}

// Test: RemoveQualifiers on node with no qualifiers
TEST_F(XMPNodeTest_1871, RemoveQualifiersOnEmptyNode_1871) {
    XMP_Node node(nullptr, "test", 0);
    EXPECT_TRUE(node.qualifiers.empty());
    node.RemoveQualifiers();
    EXPECT_TRUE(node.qualifiers.empty());
}

// Test: ClearNode clears name, value, children, and qualifiers
TEST_F(XMPNodeTest_1871, ClearNodeClearsData_1871) {
    XMP_Node node(nullptr, "clearMe", "clearValue", 0x0F);
    node.ClearNode();
    EXPECT_TRUE(node.children.empty());
    EXPECT_TRUE(node.qualifiers.empty());
}

// Test: Adding children and then removing them
TEST_F(XMPNodeTest_1871, AddAndRemoveChildren_1871) {
    XMP_Node parentNode(nullptr, "parent", 0);
    XMP_Node* child1 = new XMP_Node(&parentNode, "child1", 0);
    XMP_Node* child2 = new XMP_Node(&parentNode, "child2", 0);
    parentNode.children.push_back(child1);
    parentNode.children.push_back(child2);
    EXPECT_EQ(parentNode.children.size(), 2u);
    parentNode.RemoveChildren();
    EXPECT_TRUE(parentNode.children.empty());
}

// Test: Adding qualifiers and then removing them
TEST_F(XMPNodeTest_1871, AddAndRemoveQualifiers_1871) {
    XMP_Node node(nullptr, "node", 0);
    XMP_Node* qual1 = new XMP_Node(&node, "qual1", "qval1", 0);
    XMP_Node* qual2 = new XMP_Node(&node, "qual2", "qval2", 0);
    node.qualifiers.push_back(qual1);
    node.qualifiers.push_back(qual2);
    EXPECT_EQ(node.qualifiers.size(), 2u);
    node.RemoveQualifiers();
    EXPECT_TRUE(node.qualifiers.empty());
}

// Test: Destructor cleans up children (no crash/leak)
TEST_F(XMPNodeTest_1871, DestructorCleansUpChildren_1871) {
    XMP_Node* parentNode = new XMP_Node(nullptr, "parent", 0);
    XMP_Node* child = new XMP_Node(parentNode, "child", 0);
    parentNode->children.push_back(child);
    // Should not crash or leak
    delete parentNode;
}

// Test: Destructor cleans up qualifiers (no crash/leak)
TEST_F(XMPNodeTest_1871, DestructorCleansUpQualifiers_1871) {
    XMP_Node* node = new XMP_Node(nullptr, "node", 0);
    XMP_Node* qual = new XMP_Node(node, "qual", "qualVal", 0);
    node->qualifiers.push_back(qual);
    // Should not crash or leak
    delete node;
}

// Test: Nested children cleanup via destructor
TEST_F(XMPNodeTest_1871, NestedChildrenCleanup_1871) {
    XMP_Node* root = new XMP_Node(nullptr, "root", 0);
    XMP_Node* child = new XMP_Node(root, "child", 0);
    XMP_Node* grandchild = new XMP_Node(child, "grandchild", 0);
    child->children.push_back(grandchild);
    root->children.push_back(child);
    // Should recursively clean up without crash
    delete root;
}

// Test: Large name string
TEST_F(XMPNodeTest_1871, LargeNameString_1871) {
    std::string largeName(10000, 'A');
    XMP_Node node(nullptr, largeName.c_str(), 0);
    EXPECT_EQ(node.name, largeName);
}

// Test: Large value string
TEST_F(XMPNodeTest_1871, LargeValueString_1871) {
    std::string largeValue(10000, 'B');
    XMP_Node node(nullptr, "name", largeValue.c_str(), 0);
    EXPECT_EQ(node.value, largeValue);
}

// Test: Multiple calls to RemoveChildren
TEST_F(XMPNodeTest_1871, MultipleRemoveChildrenCalls_1871) {
    XMP_Node node(nullptr, "test", 0);
    XMP_Node* child = new XMP_Node(&node, "child", 0);
    node.children.push_back(child);
    node.RemoveChildren();
    EXPECT_TRUE(node.children.empty());
    // Second call should be safe
    node.RemoveChildren();
    EXPECT_TRUE(node.children.empty());
}

// Test: Multiple calls to RemoveQualifiers
TEST_F(XMPNodeTest_1871, MultipleRemoveQualifiersCalls_1871) {
    XMP_Node node(nullptr, "test", 0);
    XMP_Node* qual = new XMP_Node(&node, "qual", 0);
    node.qualifiers.push_back(qual);
    node.RemoveQualifiers();
    EXPECT_TRUE(node.qualifiers.empty());
    // Second call should be safe
    node.RemoveQualifiers();
    EXPECT_TRUE(node.qualifiers.empty());
}

// Test: ClearNode on a node with children and qualifiers
TEST_F(XMPNodeTest_1871, ClearNodeWithChildrenAndQualifiers_1871) {
    XMP_Node node(nullptr, "clearNode", "clearValue", 0xFF);
    XMP_Node* child = new XMP_Node(&node, "child", 0);
    XMP_Node* qual = new XMP_Node(&node, "qual", 0);
    node.children.push_back(child);
    node.qualifiers.push_back(qual);
    EXPECT_EQ(node.children.size(), 1u);
    EXPECT_EQ(node.qualifiers.size(), 1u);
    node.ClearNode();
    EXPECT_TRUE(node.children.empty());
    EXPECT_TRUE(node.qualifiers.empty());
}

// Test: Special characters in name and value
TEST_F(XMPNodeTest_1871, SpecialCharactersInNameAndValue_1871) {
    XMP_Node node(nullptr, "name with spaces & <special> \"chars\"", "value\nwith\ttabs\0", 0);
    EXPECT_EQ(node.name, "name with spaces & <special> \"chars\"");
}

// Test: Unicode-like characters in name
TEST_F(XMPNodeTest_1871, UnicodeInName_1871) {
    XMP_Node node(nullptr, "日本語テスト", 0);
    EXPECT_EQ(node.name, "日本語テスト");
}

// Test: Many children
TEST_F(XMPNodeTest_1871, ManyChildren_1871) {
    XMP_Node parentNode(nullptr, "parent", 0);
    const int numChildren = 100;
    for (int i = 0; i < numChildren; ++i) {
        XMP_Node* child = new XMP_Node(&parentNode, ("child" + std::to_string(i)).c_str(), 0);
        parentNode.children.push_back(child);
    }
    EXPECT_EQ(parentNode.children.size(), static_cast<size_t>(numChildren));
    parentNode.RemoveChildren();
    EXPECT_TRUE(parentNode.children.empty());
}

// Test: Node with both children and qualifiers, destroy via destructor
TEST_F(XMPNodeTest_1871, DestructorWithBothChildrenAndQualifiers_1871) {
    XMP_Node* node = new XMP_Node(nullptr, "mixed", "mixedValue", 0x10);
    for (int i = 0; i < 5; ++i) {
        node->children.push_back(new XMP_Node(node, ("child" + std::to_string(i)).c_str(), 0));
        node->qualifiers.push_back(new XMP_Node(node, ("qual" + std::to_string(i)).c_str(), 0));
    }
    // Should not crash
    delete node;
}
