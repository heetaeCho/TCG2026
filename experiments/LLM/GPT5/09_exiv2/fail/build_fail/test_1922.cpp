#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "XMPUtils-FileInfo.cpp"  // Adjust the include path accordingly
#include "XMPCore_Impl.hpp"  // Adjust the include path accordingly
#include "XMP_Const.h"  // Adjust the include path accordingly

// Mock class for XMP_Node if needed
class MockXMP_Node : public XMP_Node {
public:
    MOCK_METHOD(void, RemoveChildren, (), (override));
    MOCK_METHOD(void, RemoveQualifiers, (), (override));
    MOCK_METHOD(void, ClearNode, (), (override));
};

// Test suite for ItemValuesMatch function
TEST_F(ItemValuesMatchTest_1922, TestMatch_IdenticalNodes) {
    // Prepare mock nodes with identical values
    MockXMP_Node leftNode(nullptr, "name", "value", 0);
    MockXMP_Node rightNode(nullptr, "name", "value", 0);
    
    // Assuming ItemValuesMatch function is available and can be invoked.
    EXPECT_TRUE(ItemValuesMatch(&leftNode, &rightNode));
}

TEST_F(ItemValuesMatchTest_1922, TestNoMatch_DifferentValues) {
    // Prepare mock nodes with different values
    MockXMP_Node leftNode(nullptr, "name", "left_value", 0);
    MockXMP_Node rightNode(nullptr, "name", "right_value", 0);
    
    EXPECT_FALSE(ItemValuesMatch(&leftNode, &rightNode));
}

TEST_F(ItemValuesMatchTest_1922, TestMatch_StructNodesWithSameChildren) {
    // Mock structs with children having the same values
    MockXMP_Node leftNode(nullptr, "struct", "", kXMP_PropValueIsStruct);
    MockXMP_Node rightNode(nullptr, "struct", "", kXMP_PropValueIsStruct);
    
    // Set up children for both nodes
    MockXMP_Node leftChild(nullptr, "child", "left_value", 0);
    MockXMP_Node rightChild(nullptr, "child", "left_value", 0);
    leftNode.children.push_back(&leftChild);
    rightNode.children.push_back(&rightChild);
    
    EXPECT_TRUE(ItemValuesMatch(&leftNode, &rightNode));
}

TEST_F(ItemValuesMatchTest_1922, TestNoMatch_StructNodesWithDifferentChildren) {
    // Mock structs with different children
    MockXMP_Node leftNode(nullptr, "struct", "", kXMP_PropValueIsStruct);
    MockXMP_Node rightNode(nullptr, "struct", "", kXMP_PropValueIsStruct);
    
    // Set up different children for each node
    MockXMP_Node leftChild(nullptr, "child", "left_value", 0);
    MockXMP_Node rightChild(nullptr, "child", "right_value", 0);
    leftNode.children.push_back(&leftChild);
    rightNode.children.push_back(&rightChild);
    
    EXPECT_FALSE(ItemValuesMatch(&leftNode, &rightNode));
}

TEST_F(ItemValuesMatchTest_1922, TestMatch_ArrayNodes) {
    // Prepare nodes as arrays
    MockXMP_Node leftNode(nullptr, "array", "", kXMP_PropValueIsArray);
    MockXMP_Node rightNode(nullptr, "array", "", kXMP_PropValueIsArray);
    
    // Set up array items
    MockXMP_Node leftItem(nullptr, "item", "left_value", 0);
    MockXMP_Node rightItem(nullptr, "item", "left_value", 0);
    leftNode.children.push_back(&leftItem);
    rightNode.children.push_back(&rightItem);
    
    EXPECT_TRUE(ItemValuesMatch(&leftNode, &rightNode));
}

TEST_F(ItemValuesMatchTest_1922, TestNoMatch_ArrayNodes) {
    // Prepare nodes as arrays
    MockXMP_Node leftNode(nullptr, "array", "", kXMP_PropValueIsArray);
    MockXMP_Node rightNode(nullptr, "array", "", kXMP_PropValueIsArray);
    
    // Set up different array items
    MockXMP_Node leftItem(nullptr, "item", "left_value", 0);
    MockXMP_Node rightItem(nullptr, "item", "right_value", 0);
    leftNode.children.push_back(&leftItem);
    rightNode.children.push_back(&rightItem);
    
    EXPECT_FALSE(ItemValuesMatch(&leftNode, &rightNode));
}

// Additional exceptional cases
TEST_F(ItemValuesMatchTest_1922, TestNullNodes) {
    // Test case with null nodes
    EXPECT_FALSE(ItemValuesMatch(nullptr, nullptr));
}

TEST_F(ItemValuesMatchTest_1922, TestNullLeftNode) {
    // Test case with a null left node
    MockXMP_Node rightNode(nullptr, "name", "value", 0);
    EXPECT_FALSE(ItemValuesMatch(nullptr, &rightNode));
}

TEST_F(ItemValuesMatchTest_1922, TestNullRightNode) {
    // Test case with a null right node
    MockXMP_Node leftNode(nullptr, "name", "value", 0);
    EXPECT_FALSE(ItemValuesMatch(&leftNode, nullptr));
}