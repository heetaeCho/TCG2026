#include <gtest/gtest.h>
#include "XMPCore_Impl.hpp"

class XMP_NodeTest_1870 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test ClearNode resets options to 0
TEST_F(XMP_NodeTest_1870, ClearNodeResetsOptions_1870) {
    XMP_Node parent(nullptr, "parent", 0);
    XMP_Node node(&parent, "testName", "testValue", 0x1234);
    
    EXPECT_EQ(node.options, 0x1234);
    node.ClearNode();
    EXPECT_EQ(node.options, 0);
}

// Test ClearNode clears the name
TEST_F(XMP_NodeTest_1870, ClearNodeClearsName_1870) {
    XMP_Node node(nullptr, "someName", "someValue", 0);
    
    EXPECT_EQ(node.name, "someName");
    node.ClearNode();
    EXPECT_TRUE(node.name.empty());
}

// Test ClearNode clears the value
TEST_F(XMP_NodeTest_1870, ClearNodeClearsValue_1870) {
    XMP_Node node(nullptr, "someName", "someValue", 0);
    
    EXPECT_EQ(node.value, "someValue");
    node.ClearNode();
    EXPECT_TRUE(node.value.empty());
}

// Test ClearNode removes children
TEST_F(XMP_NodeTest_1870, ClearNodeRemovesChildren_1870) {
    XMP_Node node(nullptr, "parent", 0);
    XMP_Node* child = new XMP_Node(&node, "child", 0);
    node.children.push_back(child);
    
    EXPECT_EQ(node.children.size(), 1u);
    node.ClearNode();
    EXPECT_TRUE(node.children.empty());
}

// Test ClearNode removes qualifiers
TEST_F(XMP_NodeTest_1870, ClearNodeRemovesQualifiers_1870) {
    XMP_Node node(nullptr, "parent", 0);
    XMP_Node* qualifier = new XMP_Node(&node, "qualifier", 0);
    node.qualifiers.push_back(qualifier);
    
    EXPECT_EQ(node.qualifiers.size(), 1u);
    node.ClearNode();
    EXPECT_TRUE(node.qualifiers.empty());
}

// Test ClearNode on node with empty name and value (boundary)
TEST_F(XMP_NodeTest_1870, ClearNodeOnEmptyNode_1870) {
    XMP_Node node(nullptr, "", "", 0);
    
    EXPECT_TRUE(node.name.empty());
    EXPECT_TRUE(node.value.empty());
    EXPECT_EQ(node.options, 0);
    
    node.ClearNode();
    
    EXPECT_TRUE(node.name.empty());
    EXPECT_TRUE(node.value.empty());
    EXPECT_EQ(node.options, 0);
    EXPECT_TRUE(node.children.empty());
    EXPECT_TRUE(node.qualifiers.empty());
}

// Test ClearNode does not affect parent pointer
TEST_F(XMP_NodeTest_1870, ClearNodeDoesNotAffectParent_1870) {
    XMP_Node parent(nullptr, "parent", 0);
    XMP_Node node(&parent, "child", "value", 42);
    
    EXPECT_EQ(node.parent, &parent);
    node.ClearNode();
    EXPECT_EQ(node.parent, &parent);
}

// Test ClearNode with multiple children
TEST_F(XMP_NodeTest_1870, ClearNodeRemovesMultipleChildren_1870) {
    XMP_Node node(nullptr, "parent", 0);
    
    for (int i = 0; i < 5; ++i) {
        XMP_Node* child = new XMP_Node(&node, "child", 0);
        node.children.push_back(child);
    }
    
    EXPECT_EQ(node.children.size(), 5u);
    node.ClearNode();
    EXPECT_TRUE(node.children.empty());
}

// Test ClearNode with multiple qualifiers
TEST_F(XMP_NodeTest_1870, ClearNodeRemovesMultipleQualifiers_1870) {
    XMP_Node node(nullptr, "parent", 0);
    
    for (int i = 0; i < 3; ++i) {
        XMP_Node* qual = new XMP_Node(&node, "qual", 0);
        node.qualifiers.push_back(qual);
    }
    
    EXPECT_EQ(node.qualifiers.size(), 3u);
    node.ClearNode();
    EXPECT_TRUE(node.qualifiers.empty());
}

// Test constructor with XMP_StringPtr name
TEST_F(XMP_NodeTest_1870, ConstructorWithStringPtr_1870) {
    XMP_Node node(nullptr, "testName", 0x10);
    
    EXPECT_EQ(node.name, "testName");
    EXPECT_EQ(node.options, 0x10);
    EXPECT_EQ(node.parent, nullptr);
    EXPECT_TRUE(node.value.empty());
}

// Test constructor with XMP_VarString name
TEST_F(XMP_NodeTest_1870, ConstructorWithVarString_1870) {
    XMP_VarString nameStr = "varStringName";
    XMP_Node node(nullptr, nameStr, 0x20);
    
    EXPECT_EQ(node.name, "varStringName");
    EXPECT_EQ(node.options, 0x20);
}

// Test constructor with name and value (StringPtr)
TEST_F(XMP_NodeTest_1870, ConstructorWithNameAndValue_1870) {
    XMP_Node parent(nullptr, "parent", 0);
    XMP_Node node(&parent, "name", "value", 0x30);
    
    EXPECT_EQ(node.name, "name");
    EXPECT_EQ(node.value, "value");
    EXPECT_EQ(node.options, 0x30);
    EXPECT_EQ(node.parent, &parent);
}

// Test constructor with VarString name and value
TEST_F(XMP_NodeTest_1870, ConstructorWithVarStringNameAndValue_1870) {
    XMP_VarString nameStr = "varName";
    XMP_VarString valueStr = "varValue";
    XMP_Node node(nullptr, nameStr, valueStr, 0x40);
    
    EXPECT_EQ(node.name, "varName");
    EXPECT_EQ(node.value, "varValue");
    EXPECT_EQ(node.options, 0x40);
}

// Test calling ClearNode twice
TEST_F(XMP_NodeTest_1870, ClearNodeCalledTwice_1870) {
    XMP_Node node(nullptr, "name", "value", 0xFF);
    
    node.ClearNode();
    EXPECT_TRUE(node.name.empty());
    EXPECT_TRUE(node.value.empty());
    EXPECT_EQ(node.options, 0);
    
    // Second call should be safe
    node.ClearNode();
    EXPECT_TRUE(node.name.empty());
    EXPECT_TRUE(node.value.empty());
    EXPECT_EQ(node.options, 0);
}

// Test ClearNode with large option bits
TEST_F(XMP_NodeTest_1870, ClearNodeWithLargeOptionBits_1870) {
    XMP_Node node(nullptr, "name", "value", 0xFFFFFFFF);
    
    EXPECT_EQ(node.options, 0xFFFFFFFF);
    node.ClearNode();
    EXPECT_EQ(node.options, 0);
}

// Test ClearNode with long name and value strings
TEST_F(XMP_NodeTest_1870, ClearNodeWithLongStrings_1870) {
    std::string longName(10000, 'a');
    std::string longValue(10000, 'b');
    XMP_Node node(nullptr, longName, longValue, 0);
    
    EXPECT_EQ(node.name.size(), 10000u);
    EXPECT_EQ(node.value.size(), 10000u);
    
    node.ClearNode();
    EXPECT_TRUE(node.name.empty());
    EXPECT_TRUE(node.value.empty());
}
