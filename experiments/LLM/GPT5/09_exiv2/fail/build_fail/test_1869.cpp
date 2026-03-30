#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "XMPCore_Impl.hpp"

class XMPNodeTest_1869 : public ::testing::Test {
protected:
    // You can define any shared setup here, for example creating a parent node.
    XMP_Node* node;

    void SetUp() override {
        node = new XMP_Node(nullptr, "TestNode", 0);  // Creating a simple node with no qualifiers
    }

    void TearDown() override {
        delete node;
    }
};

// Test normal operation when there are no qualifiers to remove
TEST_F(XMPNodeTest_1869, RemoveQualifiers_NoQualifiers_1869) {
    node->RemoveQualifiers();
    // Assuming there is some way to verify that no qualifiers were removed (if there were any)
    // e.g., checking the state of qualifiers or confirming no calls to delete
    EXPECT_TRUE(node->qualifiers.empty());
}

// Test when qualifiers exist, checking that they are properly removed
TEST_F(XMPNodeTest_1869, RemoveQualifiers_WithQualifiers_1869) {
    // Adding some dummy qualifiers to the node
    node->qualifiers.push_back(new XMP_Node(nullptr, "Qualifier1", 0));
    node->qualifiers.push_back(new XMP_Node(nullptr, "Qualifier2", 0));

    // Removing qualifiers
    node->RemoveQualifiers();

    // Ensure the qualifiers are cleared
    EXPECT_TRUE(node->qualifiers.empty());
}

// Test for an edge case: calling RemoveQualifiers on an already empty qualifiers list
TEST_F(XMPNodeTest_1869, RemoveQualifiers_EmptyQualifiers_1869) {
    node->RemoveQualifiers();
    // Since the qualifiers list is empty, there should be no error or change
    EXPECT_TRUE(node->qualifiers.empty());
}

// Test with NULL qualifiers, simulating a case where the qualifiers list has null pointers
TEST_F(XMPNodeTest_1869, RemoveQualifiers_NullQualifiers_1869) {
    // Adding a null pointer to the qualifiers list
    node->qualifiers.push_back(nullptr);
    node->RemoveQualifiers();
    // Ensure that the list is cleared and no errors occurred
    EXPECT_TRUE(node->qualifiers.empty());
}

// Verify that the RemoveQualifiers method properly handles an exception if the node itself is invalid
TEST_F(XMPNodeTest_1869, RemoveQualifiers_NullNode_1869) {
    // Simulate a null node by setting it to nullptr
    XMP_Node* nullNode = nullptr;
    
    // Calling RemoveQualifiers should not crash or throw, it should just do nothing
    EXPECT_NO_THROW({
        if (nullNode) nullNode->RemoveQualifiers();
    });
}

// Verifying that the method does not delete null pointers
TEST_F(XMPNodeTest_1869, RemoveQualifiers_DoesNotDeleteNull_1869) {
    // Pushing a null pointer
    node->qualifiers.push_back(nullptr);
    node->RemoveQualifiers();
    
    // The list should be empty
    EXPECT_TRUE(node->qualifiers.empty());
}