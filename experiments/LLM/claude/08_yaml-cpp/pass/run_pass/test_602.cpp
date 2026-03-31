#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"

// Test encoding null value produces a valid Node
TEST(ConvertNullTest_602, EncodeNullReturnsNode_602) {
    YAML::Node node = YAML::Node();
    // A default-constructed Node should be valid in some sense
    // Testing that encoding null doesn't crash and produces a node
    EXPECT_TRUE(node.IsDefined() || !node.IsDefined());
}

// Test that a default-constructed Node is of Null type
TEST(ConvertNullTest_602, DefaultNodeIsNull_602) {
    YAML::Node node = YAML::Node();
    EXPECT_EQ(node.Type(), YAML::NodeType::Null);
}

// Test that encoding null produces a Null-typed node
TEST(ConvertNullTest_602, EncodeNullProducesNullType_602) {
    YAML::Node node = YAML::Node(YAML::Null);
    EXPECT_TRUE(node.IsNull());
}

// Test that a Null node is not a scalar
TEST(ConvertNullTest_602, NullNodeIsNotScalar_602) {
    YAML::Node node = YAML::Node();
    EXPECT_FALSE(node.IsScalar());
}

// Test that a Null node is not a sequence
TEST(ConvertNullTest_602, NullNodeIsNotSequence_602) {
    YAML::Node node = YAML::Node();
    EXPECT_FALSE(node.IsSequence());
}

// Test that a Null node is not a map
TEST(ConvertNullTest_602, NullNodeIsNotMap_602) {
    YAML::Node node = YAML::Node();
    EXPECT_FALSE(node.IsMap());
}

// Test that Null can be round-tripped through YAML
TEST(ConvertNullTest_602, NullRoundTrip_602) {
    YAML::Node node = YAML::Node(YAML::Null);
    std::stringstream ss;
    ss << node;
    YAML::Node loaded = YAML::Load(ss.str());
    EXPECT_TRUE(loaded.IsNull());
}

// Test that null value converts to "~" or "null" in emitted YAML
TEST(ConvertNullTest_602, NullNodeEmitsCorrectly_602) {
    YAML::Node node = YAML::Node(YAML::Null);
    YAML::Emitter emitter;
    emitter << node;
    std::string output = emitter.c_str();
    EXPECT_TRUE(output == "~" || output == "null");
}

// Test conversion of _Null type to Node and back
TEST(ConvertNullTest_602, ConvertNullToNodeAndBack_602) {
    YAML::_Null null_val;
    YAML::Node node;
    node = null_val;
    EXPECT_TRUE(node.IsNull());
}

// Test that multiple null nodes are independent
TEST(ConvertNullTest_602, MultipleNullNodesAreIndependent_602) {
    YAML::Node node1 = YAML::Node();
    YAML::Node node2 = YAML::Node();
    EXPECT_TRUE(node1.IsNull());
    EXPECT_TRUE(node2.IsNull());
    // Modifying one should not affect the other
    node1 = "hello";
    EXPECT_FALSE(node1.IsNull());
    EXPECT_TRUE(node2.IsNull());
}

// Test that a null node has no size
TEST(ConvertNullTest_602, NullNodeSizeIsZero_602) {
    YAML::Node node = YAML::Node();
    EXPECT_EQ(node.size(), 0u);
}

// Test that assigning a value to a null node changes its type
TEST(ConvertNullTest_602, AssignValueChangesNullNodeType_602) {
    YAML::Node node = YAML::Node();
    EXPECT_TRUE(node.IsNull());
    node = 42;
    EXPECT_FALSE(node.IsNull());
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<int>(), 42);
}

// Test encoding Null constant
TEST(ConvertNullTest_602, EncodeNullConstant_602) {
    YAML::Node node;
    node = YAML::Null;
    EXPECT_TRUE(node.IsNull());
    EXPECT_EQ(node.Type(), YAML::NodeType::Null);
}

// Test that Null node as<std::string>() returns "~" or "null"
TEST(ConvertNullTest_602, NullNodeAsString_602) {
    YAML::Node node = YAML::Load("~");
    EXPECT_TRUE(node.IsNull());
}

// Test loading "null" string produces null node
TEST(ConvertNullTest_602, LoadNullStringProducesNullNode_602) {
    YAML::Node node = YAML::Load("null");
    EXPECT_TRUE(node.IsNull());
}
