#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "XMPMeta.hpp"
#include "XMLParserAdapter.hpp"

// Mock class to simulate the XMLParserAdapter behavior
class MockXMLParserAdapter : public XMLParserAdapter {
public:
    MOCK_METHOD(void, ParseBuffer, (const void* buffer, size_t length, bool last), (override));
};

// Mock class to simulate the XMPMeta behavior
class MockXMPMeta : public XMPMeta {
public:
    MOCK_METHOD(void, ParseFromBuffer, (XMP_StringPtr buffer, XMP_StringLen bufferSize, XMP_OptionBits options), (override));
};

// Test Fixture class for XMPMeta
class FindRootNodeTest : public ::testing::Test {
protected:
    MockXMPMeta mockXMPMeta;
    MockXMLParserAdapter mockXMLParserAdapter;

    const XML_Node* rootNode;
    XMP_OptionBits options = kXMP_RequireXMPMeta;
    
    void SetUp() override {
        // Setup the mock XMLParserAdapter if necessary
        rootNode = mockXMLParserAdapter.rootNode;
    }

    void TearDown() override {
        // Clean up after each test if needed
    }
};

// Test Case: Normal operation where rootNode is valid
TEST_F(FindRootNodeTest, FindRootNode_ValidRootNode_1960) {
    // Arrange
    XML_Node mockRootNode(nullptr, "rdf:RDF", 0);
    mockXMLParserAdapter.rootNode = &mockRootNode;

    // Act
    const XML_Node* result = FindRootNode(&mockXMPMeta, mockXMLParserAdapter, options);

    // Assert
    EXPECT_EQ(result, &mockRootNode);
}

// Test Case: RootNode is null, should return nullptr
TEST_F(FindRootNodeTest, FindRootNode_NullRootNode_1961) {
    // Arrange
    mockXMLParserAdapter.rootNode = nullptr;

    // Act
    const XML_Node* result = FindRootNode(&mockXMPMeta, mockXMLParserAdapter, options);

    // Assert
    EXPECT_EQ(result, nullptr);
}

// Test Case: Root node parent is invalid, should return nullptr
TEST_F(FindRootNodeTest, FindRootNode_InvalidParent_1962) {
    // Arrange
    XML_Node mockRootNode(nullptr, "rdf:RDF", 0);
    mockXMLParserAdapter.rootNode = &mockRootNode;
    mockRootNode.parent = nullptr;

    // Act
    const XML_Node* result = FindRootNode(&mockXMPMeta, mockXMLParserAdapter, options);

    // Assert
    EXPECT_EQ(result, nullptr);
}

// Test Case: Invalid root node name, should return nullptr
TEST_F(FindRootNodeTest, FindRootNode_InvalidName_1963) {
    // Arrange
    XML_Node mockRootNode(nullptr, "invalidNode", 0);
    mockXMLParserAdapter.rootNode = &mockRootNode;

    // Act
    const XML_Node* result = FindRootNode(&mockXMPMeta, mockXMLParserAdapter, options);

    // Assert
    EXPECT_EQ(result, nullptr);
}

// Test Case: Multiple root nodes, should pick the best one
TEST_F(FindRootNodeTest, FindRootNode_MultipleRootNodes_1964) {
    // Arrange
    XML_Node mockRootNode1(nullptr, "rdf:RDF", 0);
    XML_Node mockRootNode2(nullptr, "rdf:RDF", 0);
    mockXMLParserAdapter.rootNode = &mockRootNode1;
    mockXMLParserAdapter.rootCount = 2;

    // Act
    const XML_Node* result = FindRootNode(&mockXMPMeta, mockXMLParserAdapter, options);

    // Assert
    EXPECT_EQ(result, &mockRootNode2);
}

// Test Case: Verifying version parsing, normal case
TEST_F(FindRootNodeTest, FindRootNode_ParseVersion_1965) {
    // Arrange
    XML_Node mockRootNode(nullptr, "rdf:RDF", 0);
    mockXMLParserAdapter.rootNode = &mockRootNode;
    
    // Simulate version string for this test
    const char* version = "1.2.3-456";
    XMP_StringPtr verStr = version;

    // Act
    const XML_Node* result = FindRootNode(&mockXMPMeta, mockXMLParserAdapter, options);

    // Assert
    EXPECT_EQ(mockXMPMeta.prevTkVer, 123456789);  // Based on the version parsing logic in FindRootNode
}