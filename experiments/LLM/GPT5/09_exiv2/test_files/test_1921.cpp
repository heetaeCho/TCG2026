#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "XMPUtils-FileInfo.cpp"  // Assuming the code is directly included

// Mock classes for external dependencies if necessary
class MockXMP_Node : public XMP_Node {
public:
    MockXMP_Node(XMP_Node* _parent, XMP_StringPtr _name, XMP_OptionBits _options)
        : XMP_Node(_parent, _name, _options) {}
    MOCK_METHOD(void, erase, (XMP_NodePtrPos), (override));
};

// Test Fixture for RemoveSchemaChildren
class RemoveSchemaChildrenTest : public ::testing::Test {
protected:
    XMP_Node* schemaNode;
    XMP_NodePtrPos schemaPos;

    void SetUp() override {
        // Mock schemaNode initialization or set it up as needed
        schemaNode = new XMP_Node(nullptr, "schema", 0);
        schemaPos = &schemaNode;  // Simulate the schemaPos for test cases
    }

    void TearDown() override {
        delete schemaNode;
    }
};

// Normal operation test
TEST_F(RemoveSchemaChildrenTest, RemoveSchemaChildren_NormalOperation_1921) {
    // Test the normal case where children are removed
    schemaNode->children.push_back(new XMP_Node(schemaNode, "property1", 0));
    schemaNode->children.push_back(new XMP_Node(schemaNode, "property2", 0));
    size_t initialSize = schemaNode->children.size();

    RemoveSchemaChildren(schemaPos, true);

    EXPECT_EQ(schemaNode->children.size(), initialSize - 2);
}

// Boundary test: Empty schema node
TEST_F(RemoveSchemaChildrenTest, RemoveSchemaChildren_EmptySchema_1922) {
    // Case where schema node has no children
    schemaNode->children.clear();

    RemoveSchemaChildren(schemaPos, true);

    EXPECT_TRUE(schemaNode->children.empty());
}

// Boundary test: Schema node with one child
TEST_F(RemoveSchemaChildrenTest, RemoveSchemaChildren_OneChild_1923) {
    // Case where schema node has exactly one child
    schemaNode->children.push_back(new XMP_Node(schemaNode, "property1", 0));

    RemoveSchemaChildren(schemaPos, true);

    EXPECT_TRUE(schemaNode->children.empty());
}

// Exceptional case: Attempt to remove when schema node is null
TEST_F(RemoveSchemaChildrenTest, RemoveSchemaChildren_NullSchemaNode_1924) {
    // Null schemaPos edge case
    schemaPos = nullptr;

    EXPECT_THROW(RemoveSchemaChildren(schemaPos, true), std::invalid_argument);
}

// Test verifying external interactions: Deleting and erasing children
TEST_F(RemoveSchemaChildrenTest, RemoveSchemaChildren_VerifyDeleteAndErase_1925) {
    // Create mock child nodes
    MockXMP_Node* childNode = new MockXMP_Node(schemaNode, "property1", 0);
    schemaNode->children.push_back(childNode);

    EXPECT_CALL(*childNode, erase(::testing::_)).Times(1);  // Expecting erase to be called on the child node

    RemoveSchemaChildren(schemaPos, true);

    // Ensure the child node was deleted and erased
    EXPECT_TRUE(schemaNode->children.empty());
}

// Test verifying edge case: Do not delete properties
TEST_F(RemoveSchemaChildrenTest, RemoveSchemaChildren_DoNotDeleteProperties_1926) {
    // Case where doAll is false and no children should be removed
    schemaNode->children.push_back(new XMP_Node(schemaNode, "property1", 0));

    RemoveSchemaChildren(schemaPos, false);

    EXPECT_EQ(schemaNode->children.size(), 1);
}