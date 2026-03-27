#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "XMPMeta-GetSet.cpp"  // Include the header that contains the SetNode function

// Mock classes if needed (e.g., XMP_Node mock for dependency verification)
class MockXMPNode : public XMP_Node {
public:
    MOCK_METHOD(void, RemoveChildren, (), (override));
    MOCK_METHOD(void, RemoveQualifiers, (), (override));
    MOCK_METHOD(void, ClearNode, (), (override));
    MOCK_METHOD(void, SetNodeValue, (XMP_Node* node, const XMP_StringPtr value), (override));
};

// Unit Test for SetNode function
TEST_F(SetNodeTest_1925, SetNode_SuccessNormalOperation) {
    XMP_Node* node = new XMP_Node(nullptr, "testNode", "testValue", 0);
    const XMP_StringPtr value = "newTestValue";
    XMP_OptionBits options = 0;  // No delete flag

    SetNode(node, value, options);

    EXPECT_EQ(node->value, value);  // Check if the value was updated
    delete node;
}

TEST_F(SetNodeTest_1925, SetNode_DeleteExistingFlag) {
    XMP_Node* node = new XMP_Node(nullptr, "testNode", "testValue", kXMP_DeleteExisting);
    const XMP_StringPtr value = "newTestValue";
    XMP_OptionBits options = kXMP_DeleteExisting;

    // Ensure that RemoveChildren and RemoveQualifiers are called
    MockXMPNode mockNode;
    EXPECT_CALL(mockNode, RemoveChildren()).Times(1);
    EXPECT_CALL(mockNode, RemoveQualifiers()).Times(1);

    SetNode(node, value, options);

    // Check that the node's value was erased
    EXPECT_EQ(node->value, "");  // Value should be erased
    delete node;
}

TEST_F(SetNodeTest_1925, SetNode_CompositeNodeWithValue) {
    XMP_Node* node = new XMP_Node(nullptr, "testNode", "testValue", kXMP_PropCompositeMask);
    const XMP_StringPtr value = "compositeValue";
    XMP_OptionBits options = kXMP_PropCompositeMask;

    // Trying to set a value on a composite node should throw an error
    EXPECT_THROW(SetNode(node, value, options), std::runtime_error);
    delete node;
}

TEST_F(SetNodeTest_1925, SetNode_MismatchedCompositeType) {
    XMP_Node* node = new XMP_Node(nullptr, "testNode", "testValue", kXMP_PropCompositeMask);
    const XMP_StringPtr value = nullptr;
    XMP_OptionBits options = 0;  // Different composite type requested

    // Trying to set a mismatched composite type should throw an error
    EXPECT_THROW(SetNode(node, value, options), std::runtime_error);
    delete node;
}

TEST_F(SetNodeTest_1925, SetNode_NullValueWithCompositeMask) {
    XMP_Node* node = new XMP_Node(nullptr, "testNode", "testValue", kXMP_PropCompositeMask);
    const XMP_StringPtr value = nullptr;  // Null value to clear
    XMP_OptionBits options = kXMP_PropCompositeMask;

    SetNode(node, value, options);

    // Ensure node value is cleared
    EXPECT_TRUE(node->value.empty());
    delete node;
}

TEST_F(SetNodeTest_1925, SetNode_NoValueSetOnCompositeNode) {
    XMP_Node* node = new XMP_Node(nullptr, "testNode", "", kXMP_PropCompositeMask);
    const XMP_StringPtr value = nullptr;  // Empty string
    XMP_OptionBits options = kXMP_PropCompositeMask;

    SetNode(node, value, options);

    // No value should be set as the node was composite and value is null
    EXPECT_TRUE(node->value.empty());
    delete node;
}

// Test for boundary conditions
TEST_F(SetNodeTest_1925, SetNode_WithEdgeCases) {
    XMP_Node* node = new XMP_Node(nullptr, "testNode", "", kXMP_PropCompositeMask);
    const XMP_StringPtr value = "boundaryTestValue";
    XMP_OptionBits options = 0;

    SetNode(node, value, options);

    // Ensure boundary value is correctly set
    EXPECT_EQ(node->value, value);
    delete node;
}

// Error Handling Tests
TEST_F(SetNodeTest_1925, SetNode_ThrowsOnInvalidXPath) {
    XMP_Node* node = new XMP_Node(nullptr, "testNode", "testValue", 0);
    const XMP_StringPtr value = "invalidXPath";
    XMP_OptionBits options = 0;

    // Simulate invalid XPath scenario
    EXPECT_THROW(SetNode(node, value, options), std::runtime_error);
    delete node;
}