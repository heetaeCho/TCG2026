#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "XMPCore_Impl.hpp"

using namespace testing;

// Mock for XMP_Node, since we are testing interactions with it
class MockXMPNode : public XMP_Node {
public:
    MockXMPNode(XMP_Node* _parent, const XMP_VarString& _name, XMP_OptionBits _options)
        : XMP_Node(_parent, _name, _options) {}
    
    MOCK_METHOD(void, RemoveChildren, (), (override));
    MOCK_METHOD(void, RemoveQualifiers, (), (override));
    MOCK_METHOD(void, ClearNode, (), (override));
    MOCK_METHOD(~XMP_Node, ~XMP_Node, (), (override));
};

// Test suite for the LookupQualSelector function
class LookupQualSelectorTest : public ::testing::Test {
protected:
    // Test Setup: Prepare XMP_Node for testing
    XMP_Node* rootNode;
    XMP_VarString qualName;
    XMP_VarString qualValue;

    void SetUp() override {
        rootNode = new MockXMPNode(nullptr, "root", 0);
        qualName = "xml:lang";
        qualValue = "en";
    }

    void TearDown() override {
        delete rootNode;
    }
};

// Normal Operation Test
TEST_F(LookupQualSelectorTest, LookupQualSelector_NormalOperation_1887) {
    // Arrange
    MockXMPNode* childNode = new MockXMPNode(rootNode, "child", 0);
    rootNode->children.push_back(childNode);
    XMP_VarString testQualName = "xml:lang";
    XMP_VarString testQualValue = "en";
    
    // Act
    XMP_Index result = LookupQualSelector(rootNode, testQualName, testQualValue);
    
    // Assert
    EXPECT_GE(result, 0) << "Expected a valid index to be returned.";
    delete childNode;
}

// Boundary Condition Test: Case where no match is found for xml:lang
TEST_F(LookupQualSelectorTest, LookupQualSelector_NoMatch_1888) {
    // Arrange
    MockXMPNode* childNode = new MockXMPNode(rootNode, "child", 0);
    rootNode->children.push_back(childNode);
    XMP_VarString testQualName = "nonexistent:lang";
    XMP_VarString testQualValue = "en";

    // Act
    XMP_Index result = LookupQualSelector(rootNode, testQualName, testQualValue);

    // Assert
    EXPECT_EQ(result, -1) << "Expected index to be -1 when no match is found.";
    delete childNode;
}

// Boundary Condition Test: Case where the XML Lang is provided and should match
TEST_F(LookupQualSelectorTest, LookupQualSelector_XmlLangMatch_1889) {
    // Arrange
    MockXMPNode* childNode = new MockXMPNode(rootNode, "child", 0);
    rootNode->children.push_back(childNode);
    XMP_VarString testQualName = "xml:lang";
    XMP_VarString testQualValue = "en";

    // Simulate a scenario where we would have a valid match for "xml:lang"
    XMP_Index expectedIndex = 0; // assuming it should return the first index

    // Act
    XMP_Index result = LookupQualSelector(rootNode, testQualName, testQualValue);

    // Assert
    EXPECT_EQ(result, expectedIndex) << "Expected to find a matching item for xml:lang.";
    delete childNode;
}

// Exceptional Case Test: Empty root node
TEST_F(LookupQualSelectorTest, LookupQualSelector_EmptyRootNode_1890) {
    // Arrange
    XMP_Node* emptyRootNode = new MockXMPNode(nullptr, "root", 0);
    XMP_VarString testQualName = "xml:lang";
    XMP_VarString testQualValue = "en";

    // Act
    XMP_Index result = LookupQualSelector(emptyRootNode, testQualName, testQualValue);

    // Assert
    EXPECT_EQ(result, -1) << "Expected index to be -1 when root node has no children.";
    delete emptyRootNode;
}

// Exceptional Case Test: Null pointer for arrayNode
TEST_F(LookupQualSelectorTest, LookupQualSelector_NullArrayNode_1891) {
    // Act & Assert
    EXPECT_DEATH(LookupQualSelector(nullptr, "xml:lang", "en"), ".*");
}

// Exceptional Case Test: Invalid qualifier name
TEST_F(LookupQualSelectorTest, LookupQualSelector_InvalidQualifier_1892) {
    // Arrange
    MockXMPNode* childNode = new MockXMPNode(rootNode, "child", 0);
    rootNode->children.push_back(childNode);
    XMP_VarString testQualName = "invalid:qual";
    XMP_VarString testQualValue = "someValue";

    // Act
    XMP_Index result = LookupQualSelector(rootNode, testQualName, testQualValue);

    // Assert
    EXPECT_EQ(result, -1) << "Expected index to be -1 when an invalid qualifier is passed.";
    delete childNode;
}