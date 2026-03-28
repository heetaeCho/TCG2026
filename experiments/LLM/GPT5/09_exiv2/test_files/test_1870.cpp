#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "XMPCore_Impl.hpp"

// Mock class for verifying interactions if needed
class MockXMP_Node : public XMP_Node {
public:
    MockXMP_Node(XMP_Node* parent, const XMP_VarString& name, XMP_OptionBits options)
        : XMP_Node(parent, name, options) {}

    MOCK_METHOD(void, RemoveChildren, (), (override));
    MOCK_METHOD(void, RemoveQualifiers, (), (override));
};

// Test suite for XMP_Node
class XMPNodeTest_1870 : public ::testing::Test {
protected:
    XMP_Node* node;

    void SetUp() override {
        node = new XMP_Node(nullptr, "TestNode", 0);
    }

    void TearDown() override {
        delete node;
    }
};

// Test for ClearNode() function
TEST_F(XMPNodeTest_1870, ClearNode_1870) {
    node->name = "TestName";
    node->value = "TestValue";
    node->ClearNode();

    // Verify that the name and value are erased
    EXPECT_EQ(node->name, "");
    EXPECT_EQ(node->value, "");

    // If RemoveChildren and RemoveQualifiers are called, the function should invoke those methods
    // In this case, we mock those methods and verify they were called
    MockXMP_Node mockNode(nullptr, "MockNode", 0);
    EXPECT_CALL(mockNode, RemoveChildren()).Times(1);
    EXPECT_CALL(mockNode, RemoveQualifiers()).Times(1);
    mockNode.ClearNode();
}

// Boundary test for ClearNode() when the node is empty
TEST_F(XMPNodeTest_1870, ClearNode_EmptyNode_1871) {
    // Node is already in a default, empty state
    node->ClearNode();

    // Verify the node remains in a cleared state
    EXPECT_EQ(node->name, "");
    EXPECT_EQ(node->value, "");
}

// Test for constructor initializing the XMP_Node correctly
TEST_F(XMPNodeTest_1870, Constructor_InitializesCorrectly_1872) {
    EXPECT_EQ(node->name, "TestNode");
    EXPECT_EQ(node->value, "");
    EXPECT_EQ(node->parent, nullptr);
    EXPECT_EQ(node->options, 0);
}

// Test boundary case for XMP_Node constructor with a value
TEST_F(XMPNodeTest_1870, Constructor_WithValue_1873) {
    XMP_Node* nodeWithValue = new XMP_Node(nullptr, "TestNodeWithValue", "TestValue", 0);

    EXPECT_EQ(nodeWithValue->name, "TestNodeWithValue");
    EXPECT_EQ(nodeWithValue->value, "TestValue");
    EXPECT_EQ(nodeWithValue->parent, nullptr);

    delete nodeWithValue;
}

// Test for the destructor
TEST_F(XMPNodeTest_1870, Destructor_CleansUpMemory_1874) {
    // Simply test that the node gets cleaned up without any issues
    ASSERT_NO_THROW({
        delete node;
    });
}