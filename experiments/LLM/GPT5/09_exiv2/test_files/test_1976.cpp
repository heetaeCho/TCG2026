#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "XMLParserAdapter.hpp"  // Assuming this includes necessary XML_Node and helpers

// Test class definition
class XMLNodeTest : public ::testing::Test {
protected:
    XML_Node *rootNode;
    XML_Node *elemNode;
    XML_Node *attrNode;

    // Setup function to initialize common nodes
    void SetUp() override {
        // Create nodes for testing
        rootNode = new XML_Node(nullptr, "root", kRootNode);
        elemNode = new XML_Node(rootNode, "element", kElemNode);
        attrNode = new XML_Node(elemNode, "attribute", kAttrNode);

        // Add some attributes and content to test the functions
        elemNode->attrs.push_back(attrNode);
        rootNode->content.push_back(elemNode);
    }

    // Tear down function to clean up after each test
    void TearDown() override {
        delete rootNode;
        delete elemNode;
        delete attrNode;
    }
};

// Test for normal operation: CollectNamespaceDecls on an element with attributes
TEST_F(XMLNodeTest, CollectNamespaceDecls_Normal_1976) {
    // Define the expected map that will hold the namespace declarations
    std::map<std::string, std::string> nsMap;

    // Set up the namespace and name for the node
    elemNode->ns = "http://example.com/ns";
    elemNode->name = "prefix:element";

    // Call CollectNamespaceDecls function
    CollectNamespaceDecls(&nsMap, *rootNode);

    // Test that the namespace map contains the correct namespace declaration
    ASSERT_EQ(nsMap.size(), 1);
    ASSERT_EQ(nsMap["prefix"], "http://example.com/ns");
}

// Test for boundary condition: An element with no namespace
TEST_F(XMLNodeTest, CollectNamespaceDecls_NoNamespace_1977) {
    // Define the expected map that will hold the namespace declarations
    std::map<std::string, std::string> nsMap;

    // Set the node name without a namespace
    elemNode->name = "element";

    // Call CollectNamespaceDecls function
    CollectNamespaceDecls(&nsMap, *rootNode);

    // Test that the namespace map is empty
    ASSERT_EQ(nsMap.size(), 0);
}

// Test for boundary condition: An element with empty node and attributes
TEST_F(XMLNodeTest, CollectNamespaceDecls_EmptyNode_1978) {
    // Define the expected map that will hold the namespace declarations
    std::map<std::string, std::string> nsMap;

    // Set empty namespace and name for the node
    elemNode->ns = "";
    elemNode->name = "";

    // Call CollectNamespaceDecls function
    CollectNamespaceDecls(&nsMap, *rootNode);

    // Test that the namespace map is empty
    ASSERT_EQ(nsMap.size(), 0);
}

// Test for exceptional case: Null node input
TEST_F(XMLNodeTest, CollectNamespaceDecls_NullNode_1979) {
    // Define the expected map that will hold the namespace declarations
    std::map<std::string, std::string> nsMap;

    // Call CollectNamespaceDecls function with null node
    EXPECT_THROW(CollectNamespaceDecls(&nsMap, *nullptr), std::exception);
}

// Test for verification of external interactions: Call to CollectNamespaceDecls with mock node
TEST_F(XMLNodeTest, CollectNamespaceDecls_VerifyMockInteraction_1980) {
    // Define the expected map that will hold the namespace declarations
    std::map<std::string, std::string> nsMap;

    // Mock XML_Node behavior (using GoogleMock)
    XML_Node mockNode(nullptr, "element", kElemNode);
    EXPECT_CALL(mockNode, IsWhitespaceNode()).WillOnce(testing::Return(false));

    // Call CollectNamespaceDecls function
    CollectNamespaceDecls(&nsMap, mockNode);

    // Verify external interactions (this is an example, modify per actual mock behavior)
    ASSERT_EQ(nsMap.size(), 0);
}

// Test for boundary condition: Multiple nodes with the same prefix
TEST_F(XMLNodeTest, CollectNamespaceDecls_MultipleNodesSamePrefix_1981) {
    // Define the expected map that will hold the namespace declarations
    std::map<std::string, std::string> nsMap;

    // Set namespace and name for two elements with the same prefix
    XML_Node *elemNode2 = new XML_Node(rootNode, "prefix:element2", kElemNode);
    elemNode2->ns = "http://example.com/ns";

    rootNode->content.push_back(elemNode2);

    // Call CollectNamespaceDecls function
    CollectNamespaceDecls(&nsMap, *rootNode);

    // Verify that only one namespace declaration is stored for the same prefix
    ASSERT_EQ(nsMap.size(), 1);
    ASSERT_EQ(nsMap["prefix"], "http://example.com/ns");

    // Clean up
    delete elemNode2;
}

// Test for exceptional case: Missing namespace prefix in name
TEST_F(XMLNodeTest, CollectNamespaceDecls_MissingPrefix_1982) {
    // Define the expected map that will hold the namespace declarations
    std::map<std::string, std::string> nsMap;

    // Set node name without a prefix (invalid format)
    elemNode->name = "element";  // Missing prefix

    // Call CollectNamespaceDecls function
    CollectNamespaceDecls(&nsMap, *rootNode);

    // Test that no namespace declaration is added
    ASSERT_EQ(nsMap.size(), 0);
}