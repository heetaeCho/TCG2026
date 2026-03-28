#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"

// Test default-constructed Node returns Default style
TEST(NodeStyleTest_560, DefaultConstructedNodeReturnsDefaultStyle_560) {
    YAML::Node node;
    EXPECT_EQ(YAML::EmitterStyle::Default, node.Style());
}

// Test that setting style to Block is retrievable
TEST(NodeStyleTest_560, SetStyleBlockReturnsBlock_560) {
    YAML::Node node;
    node.SetStyle(YAML::EmitterStyle::Block);
    EXPECT_EQ(YAML::EmitterStyle::Block, node.Style());
}

// Test that setting style to Flow is retrievable
TEST(NodeStyleTest_560, SetStyleFlowReturnsFlow_560) {
    YAML::Node node;
    node.SetStyle(YAML::EmitterStyle::Flow);
    EXPECT_EQ(YAML::EmitterStyle::Flow, node.Style());
}

// Test that setting style to Default is retrievable
TEST(NodeStyleTest_560, SetStyleDefaultReturnsDefault_560) {
    YAML::Node node;
    node.SetStyle(YAML::EmitterStyle::Default);
    EXPECT_EQ(YAML::EmitterStyle::Default, node.Style());
}

// Test Style on a scalar node
TEST(NodeStyleTest_560, ScalarNodeStyleDefault_560) {
    YAML::Node node("hello");
    EXPECT_EQ(YAML::EmitterStyle::Default, node.Style());
}

// Test Style on a scalar node after setting it
TEST(NodeStyleTest_560, ScalarNodeSetStyleFlow_560) {
    YAML::Node node("hello");
    node.SetStyle(YAML::EmitterStyle::Flow);
    EXPECT_EQ(YAML::EmitterStyle::Flow, node.Style());
}

// Test Style on a sequence node
TEST(NodeStyleTest_560, SequenceNodeStyleDefault_560) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_EQ(YAML::EmitterStyle::Default, node.Style());
}

// Test Style on a sequence node after setting Block
TEST(NodeStyleTest_560, SequenceNodeSetStyleBlock_560) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.SetStyle(YAML::EmitterStyle::Block);
    EXPECT_EQ(YAML::EmitterStyle::Block, node.Style());
}

// Test Style on a map node
TEST(NodeStyleTest_560, MapNodeStyleDefault_560) {
    YAML::Node node(YAML::NodeType::Map);
    EXPECT_EQ(YAML::EmitterStyle::Default, node.Style());
}

// Test Style on a map node after setting Flow
TEST(NodeStyleTest_560, MapNodeSetStyleFlow_560) {
    YAML::Node node(YAML::NodeType::Map);
    node.SetStyle(YAML::EmitterStyle::Flow);
    EXPECT_EQ(YAML::EmitterStyle::Flow, node.Style());
}

// Test that an invalid node throws InvalidNode when Style() is called
TEST(NodeStyleTest_560, InvalidNodeThrowsOnStyle_560) {
    YAML::Node node;
    // Accessing a non-existent key on a map returns an undefined/invalid node
    // which should throw when accessing Style()
    YAML::Node mapNode(YAML::NodeType::Map);
    mapNode["existingKey"] = "value";
    
    // Access a key that doesn't exist on a const-like context
    // The operator[] on a const node for a missing key returns an invalid zombie node
    const YAML::Node constMap = mapNode;
    YAML::Node missing = constMap["nonExistentKey"];
    
    // The missing node should throw InvalidNode
    EXPECT_THROW(missing.Style(), YAML::InvalidNode);
}

// Test Style on a Null node type
TEST(NodeStyleTest_560, NullNodeTypeStyleDefault_560) {
    YAML::Node node(YAML::NodeType::Null);
    EXPECT_EQ(YAML::EmitterStyle::Default, node.Style());
}

// Test overwriting style multiple times
TEST(NodeStyleTest_560, OverwriteStyleMultipleTimes_560) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.SetStyle(YAML::EmitterStyle::Flow);
    EXPECT_EQ(YAML::EmitterStyle::Flow, node.Style());
    node.SetStyle(YAML::EmitterStyle::Block);
    EXPECT_EQ(YAML::EmitterStyle::Block, node.Style());
    node.SetStyle(YAML::EmitterStyle::Default);
    EXPECT_EQ(YAML::EmitterStyle::Default, node.Style());
}

// Test Style on a node created by parsing YAML with flow style
TEST(NodeStyleTest_560, ParsedFlowSequenceStyle_560) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    // Parsed flow sequence should have Flow style
    EXPECT_EQ(YAML::EmitterStyle::Flow, node.Style());
}

// Test Style on a node created by parsing YAML with block style
TEST(NodeStyleTest_560, ParsedBlockSequenceStyle_560) {
    YAML::Node node = YAML::Load("- 1\n- 2\n- 3");
    EXPECT_EQ(YAML::EmitterStyle::Block, node.Style());
}

// Test Style on a node created by parsing flow map
TEST(NodeStyleTest_560, ParsedFlowMapStyle_560) {
    YAML::Node node = YAML::Load("{a: 1, b: 2}");
    EXPECT_EQ(YAML::EmitterStyle::Flow, node.Style());
}

// Test Style on a node created by parsing block map
TEST(NodeStyleTest_560, ParsedBlockMapStyle_560) {
    YAML::Node node = YAML::Load("a: 1\nb: 2");
    EXPECT_EQ(YAML::EmitterStyle::Block, node.Style());
}

// Test that a copied node shares the same style
TEST(NodeStyleTest_560, CopiedNodeSharesStyle_560) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.SetStyle(YAML::EmitterStyle::Flow);
    YAML::Node copy = node;
    EXPECT_EQ(YAML::EmitterStyle::Flow, copy.Style());
}

// Test that modifying style on a copy affects original (shared reference)
TEST(NodeStyleTest_560, CopiedNodeStyleSharedReference_560) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.SetStyle(YAML::EmitterStyle::Flow);
    YAML::Node copy = node;
    copy.SetStyle(YAML::EmitterStyle::Block);
    EXPECT_EQ(YAML::EmitterStyle::Block, node.Style());
}

// Test Undefined node type style
TEST(NodeStyleTest_560, UndefinedNodeTypeStyleDefault_560) {
    YAML::Node node(YAML::NodeType::Undefined);
    EXPECT_EQ(YAML::EmitterStyle::Default, node.Style());
}

// Test Style on a node built via push_back (sequence)
TEST(NodeStyleTest_560, SequenceBuiltViaPushBackDefaultStyle_560) {
    YAML::Node node;
    node.push_back(1);
    node.push_back(2);
    EXPECT_EQ(YAML::EmitterStyle::Default, node.Style());
}

// Test SetStyle then push_back preserves style
TEST(NodeStyleTest_560, SetStyleThenPushBackPreservesStyle_560) {
    YAML::Node node;
    node.push_back(1);
    node.SetStyle(YAML::EmitterStyle::Flow);
    node.push_back(2);
    EXPECT_EQ(YAML::EmitterStyle::Flow, node.Style());
}
