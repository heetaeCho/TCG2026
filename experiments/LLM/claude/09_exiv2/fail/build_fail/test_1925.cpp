#include <gtest/gtest.h>
#include <string>
#include <vector>

// Include the necessary headers from the project
#include "XMPCore_Impl.hpp"
#include "XMP_Const.h"

// Forward declaration - SetNode is static, so we need to include the source
// or make it accessible. For testing purposes, we include the implementation.
// In practice, this would be tested through the public XMPMeta API.
#include "XMPMeta-GetSet.cpp"

class SetNodeTest_1925 : public ::testing::Test {
protected:
    void SetUp() override {
        parent = new XMP_Node(nullptr, "parent", 0);
    }

    void TearDown() override {
        delete parent;
    }

    XMP_Node* parent;
};

// Test: Setting a simple value on a node with no options
TEST_F(SetNodeTest_1925, SetSimpleValue_1925) {
    XMP_Node node(parent, "testNode", 0);
    SetNode(&node, "hello", 0);
    EXPECT_EQ(node.value, "hello");
}

// Test: Setting a value with kXMP_DeleteExisting clears existing data
TEST_F(SetNodeTest_1925, DeleteExistingClearsNode_1925) {
    XMP_Node node(parent, "testNode", "oldValue", 0);
    
    // Add a child and qualifier to verify they get removed
    XMP_Node* child = new XMP_Node(&node, "child", 0);
    node.children.push_back(child);
    XMP_Node* qual = new XMP_Node(&node, "qual", kXMP_PropIsQualifier);
    node.qualifiers.push_back(qual);
    
    SetNode(&node, "newValue", kXMP_DeleteExisting);
    
    EXPECT_EQ(node.value, "newValue");
    EXPECT_TRUE(node.children.empty());
    EXPECT_TRUE(node.qualifiers.empty());
    // kXMP_DeleteExisting should be cleared from options
    EXPECT_EQ(node.options & kXMP_DeleteExisting, 0u);
}

// Test: Setting value on a composite node throws
TEST_F(SetNodeTest_1925, CompositeNodeWithValueThrows_1925) {
    XMP_Node node(parent, "testNode", kXMP_PropValueIsStruct);
    EXPECT_THROW(SetNode(&node, "value", 0), XMP_Error);
}

// Test: Setting value on an array node throws
TEST_F(SetNodeTest_1925, ArrayNodeWithValueThrows_1925) {
    XMP_Node node(parent, "testNode", kXMP_PropValueIsArray);
    EXPECT_THROW(SetNode(&node, "value", 0), XMP_Error);
}

// Test: Null value on a node with no existing value and struct options
TEST_F(SetNodeTest_1925, NullValueStructNode_1925) {
    XMP_Node node(parent, "testNode", kXMP_PropValueIsStruct);
    SetNode(&node, nullptr, kXMP_PropValueIsStruct);
    EXPECT_TRUE(node.children.empty());
    EXPECT_TRUE((node.options & kXMP_PropValueIsStruct) != 0);
}

// Test: Null value on node with existing non-empty value throws
TEST_F(SetNodeTest_1925, NullValueWithExistingValueThrows_1925) {
    XMP_Node node(parent, "testNode", "existingValue", 0);
    EXPECT_THROW(SetNode(&node, nullptr, 0), XMP_Error);
}

// Test: Changing array to struct with null value throws (composite form mismatch)
TEST_F(SetNodeTest_1925, CompositeFormMismatchThrows_1925) {
    XMP_Node node(parent, "testNode", kXMP_PropValueIsArray);
    EXPECT_THROW(SetNode(&node, nullptr, kXMP_PropValueIsStruct), XMP_Error);
}

// Test: Changing struct to array with null value throws (composite form mismatch)
TEST_F(SetNodeTest_1925, StructToArrayMismatchThrows_1925) {
    XMP_Node node(parent, "testNode", kXMP_PropValueIsStruct);
    EXPECT_THROW(SetNode(&node, nullptr, kXMP_PropValueIsArray), XMP_Error);
}

// Test: Same composite form with null value succeeds and removes children
TEST_F(SetNodeTest_1925, SameCompositeFormRemovesChildren_1925) {
    XMP_Node node(parent, "testNode", kXMP_PropValueIsArray);
    XMP_Node* child = new XMP_Node(&node, "item", 0);
    node.children.push_back(child);
    
    SetNode(&node, nullptr, kXMP_PropValueIsArray);
    EXPECT_TRUE(node.children.empty());
}

// Test: DeleteExisting with null value clears everything
TEST_F(SetNodeTest_1925, DeleteExistingWithNullValue_1925) {
    XMP_Node node(parent, "testNode", "oldValue", kXMP_PropValueIsStruct);
    
    SetNode(&node, nullptr, kXMP_DeleteExisting | kXMP_PropValueIsStruct);
    
    EXPECT_TRUE(node.value.empty());
    EXPECT_TRUE(node.children.empty());
    EXPECT_TRUE(node.qualifiers.empty());
}

// Test: Options are OR-ed into existing node options
TEST_F(SetNodeTest_1925, OptionsAreMerged_1925) {
    XMP_Node node(parent, "testNode", kXMP_PropHasQualifiers);
    SetNode(&node, "value", kXMP_PropValueIsURI);
    EXPECT_TRUE((node.options & kXMP_PropHasQualifiers) != 0);
    EXPECT_TRUE((node.options & kXMP_PropValueIsURI) != 0);
}

// Test: Setting empty string value on simple node
TEST_F(SetNodeTest_1925, SetEmptyStringValue_1925) {
    XMP_Node node(parent, "testNode", 0);
    SetNode(&node, "", 0);
    EXPECT_EQ(node.value, "");
}

// Test: DeleteExisting resets options then applies new ones
TEST_F(SetNodeTest_1925, DeleteExistingResetsOptions_1925) {
    XMP_Node node(parent, "testNode", "old", kXMP_PropValueIsURI | kXMP_PropHasQualifiers);
    SetNode(&node, "new", kXMP_DeleteExisting | kXMP_PropValueIsURI);
    
    // After delete existing, options should be set to the new options (without kXMP_DeleteExisting)
    EXPECT_TRUE((node.options & kXMP_PropValueIsURI) != 0);
    EXPECT_EQ(node.value, "new");
}

// Test: Null value on empty-value non-composite node with children removal
TEST_F(SetNodeTest_1925, NullValueEmptyNodeRemovesChildren_1925) {
    XMP_Node node(parent, "testNode", 0);
    // Node has empty value, no composite flag
    XMP_Node* child = new XMP_Node(&node, "child", 0);
    node.children.push_back(child);
    
    SetNode(&node, nullptr, 0);
    EXPECT_TRUE(node.children.empty());
}
