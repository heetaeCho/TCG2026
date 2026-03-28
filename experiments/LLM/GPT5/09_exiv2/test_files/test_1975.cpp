#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include "XMLParserAdapter.hpp"
#include "XML_Node.hpp"

using namespace std;

// Test fixture for XML_Node tests
class XMLNodeTest : public ::testing::Test {
protected:
    // Setup function to initialize any required data
    void SetUp() override {
        // Test setup logic if required
    }

    // Teardown function to clean up after tests
    void TearDown() override {
        // Test teardown logic if required
    }
};

// Test case for normal operation: Serialize an element node
TEST_F(XMLNodeTest, SerializeElementNode_1975) {
    // Setup
    XML_Node node(nullptr, "exampleNode", kElemNode);
    string buffer;

    // Act
    node.Serialize(&buffer);

    // Verify that the buffer contains the expected serialized result
    EXPECT_THAT(buffer, testing::HasSubstr("<exampleNode"));
    EXPECT_THAT(buffer, testing::HasSubstr("</exampleNode>"));
}

// Test case for normal operation: Serialize an attribute node
TEST_F(XMLNodeTest, SerializeAttributeNode_1976) {
    // Setup
    XML_Node node(nullptr, "exampleAttr", kAttrNode);
    node.value = "value";
    string buffer;

    // Act
    node.Serialize(&buffer);

    // Verify that the buffer contains the expected serialized result
    EXPECT_THAT(buffer, testing::HasSubstr(" exampleAttr=\"value\""));
}

// Test case for normal operation: Serialize a CDATA node
TEST_F(XMLNodeTest, SerializeCDataNode_1977) {
    // Setup
    XML_Node node(nullptr, "exampleCData", kCDataNode);
    node.value = "CDATA content";
    string buffer;

    // Act
    node.Serialize(&buffer);

    // Verify that the buffer contains the expected serialized result
    EXPECT_THAT(buffer, testing::HasSubstr("CDATA content"));
}

// Test case for normal operation: Serialize a PI node
TEST_F(XMLNodeTest, SerializePINode_1978) {
    // Setup
    XML_Node node(nullptr, "examplePI", kPINode);
    node.value = "PI content";
    string buffer;

    // Act
    node.Serialize(&buffer);

    // Verify that the buffer contains the expected serialized result
    EXPECT_THAT(buffer, testing::HasSubstr("PI content"));
}

// Test case for boundary condition: Serialize empty element node (empty content)
TEST_F(XMLNodeTest, SerializeEmptyElementNode_1979) {
    // Setup
    XML_Node node(nullptr, "emptyNode", kElemNode);
    node.content.clear();
    string buffer;

    // Act
    node.Serialize(&buffer);

    // Verify that the buffer contains the expected serialized result for empty element
    EXPECT_THAT(buffer, testing::HasSubstr("<emptyNode/>"));
}

// Test case for boundary condition: Serialize element node with multiple content
TEST_F(XMLNodeTest, SerializeElementNodeWithMultipleContent_1980) {
    // Setup
    XML_Node node(nullptr, "parentNode", kElemNode);
    XML_Node childNode(nullptr, "childNode", kElemNode);
    node.content.push_back(childNode);
    string buffer;

    // Act
    node.Serialize(&buffer);

    // Verify that the buffer contains the expected serialized result for element with content
    EXPECT_THAT(buffer, testing::HasSubstr("<parentNode><childNode</childNode></parentNode>"));
}

// Test case for exceptional case: Serialize node with invalid type
TEST_F(XMLNodeTest, SerializeInvalidNode_1981) {
    // Setup
    XML_Node node(nullptr, "invalidNode", static_cast<XMP_Uns8>(-1));  // Invalid node type
    string buffer;

    // Act
    node.Serialize(&buffer);

    // Verify that the buffer remains empty as there is no valid serialization
    EXPECT_TRUE(buffer.empty());
}

// Test case for verification of external interactions: Serialize the node and check if the buffer gets modified
TEST_F(XMLNodeTest, VerifyBufferModified_1982) {
    // Setup
    XML_Node node(nullptr, "testNode", kElemNode);
    string buffer;

    // Act
    node.Serialize(&buffer);

    // Verify that the buffer is not empty after serialization
    EXPECT_FALSE(buffer.empty());
}

// Test case for verifying the handling of empty buffer (boundary condition)
TEST_F(XMLNodeTest, SerializeWithEmptyBuffer_1983) {
    // Setup
    XML_Node node(nullptr, "emptyBufferTest", kElemNode);
    string buffer = "";

    // Act
    node.Serialize(&buffer);

    // Verify that the buffer now contains data after serialization
    EXPECT_FALSE(buffer.empty());
}