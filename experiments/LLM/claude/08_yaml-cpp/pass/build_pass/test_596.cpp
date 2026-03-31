#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"

// Test: decode returns false when node is not a scalar
TEST(YAMLConvertStringTest_596, DecodeNonScalarReturnsFalse_596) {
    YAML::Node node(YAML::NodeType::Sequence);
    std::string result;
    bool success = YAML::convert<std::string>::decode(node, result);
    EXPECT_FALSE(success);
}

// Test: decode returns true when node is a scalar
TEST(YAMLConvertStringTest_596, DecodeScalarReturnsTrue_596) {
    YAML::Node node("hello");
    std::string result;
    bool success = YAML::convert<std::string>::decode(node, result);
    EXPECT_TRUE(success);
}

// Test: decode sets rhs to the scalar value
TEST(YAMLConvertStringTest_596, DecodeScalarSetsValue_596) {
    YAML::Node node("hello world");
    std::string result;
    YAML::convert<std::string>::decode(node, result);
    EXPECT_EQ("hello world", result);
}

// Test: decode with empty scalar string
TEST(YAMLConvertStringTest_596, DecodeEmptyScalar_596) {
    YAML::Node node("");
    std::string result = "non-empty";
    bool success = YAML::convert<std::string>::decode(node, result);
    EXPECT_TRUE(success);
    EXPECT_EQ("", result);
}

// Test: decode returns false for map node
TEST(YAMLConvertStringTest_596, DecodeMapReturnsFalse_596) {
    YAML::Node node(YAML::NodeType::Map);
    node["key"] = "value";
    std::string result;
    bool success = YAML::convert<std::string>::decode(node, result);
    EXPECT_FALSE(success);
}

// Test: decode returns false for null node
TEST(YAMLConvertStringTest_596, DecodeNullNodeReturnsFalse_596) {
    YAML::Node node(YAML::NodeType::Null);
    std::string result;
    bool success = YAML::convert<std::string>::decode(node, result);
    EXPECT_FALSE(success);
}

// Test: decode returns false for undefined node
TEST(YAMLConvertStringTest_596, DecodeUndefinedNodeReturnsFalse_596) {
    YAML::Node node(YAML::NodeType::Undefined);
    std::string result;
    bool success = YAML::convert<std::string>::decode(node, result);
    EXPECT_FALSE(success);
}

// Test: decode with numeric scalar
TEST(YAMLConvertStringTest_596, DecodeNumericScalar_596) {
    YAML::Node node("12345");
    std::string result;
    bool success = YAML::convert<std::string>::decode(node, result);
    EXPECT_TRUE(success);
    EXPECT_EQ("12345", result);
}

// Test: decode with special characters in scalar
TEST(YAMLConvertStringTest_596, DecodeSpecialCharScalar_596) {
    YAML::Node node("hello\nworld\ttab");
    std::string result;
    bool success = YAML::convert<std::string>::decode(node, result);
    EXPECT_TRUE(success);
    EXPECT_EQ("hello\nworld\ttab", result);
}

// Test: decode with unicode-like content
TEST(YAMLConvertStringTest_596, DecodeUnicodeScalar_596) {
    YAML::Node node("héllo wörld");
    std::string result;
    bool success = YAML::convert<std::string>::decode(node, result);
    EXPECT_TRUE(success);
    EXPECT_EQ("héllo wörld", result);
}

// Test: decode with sequence node containing elements
TEST(YAMLConvertStringTest_596, DecodeSequenceWithElementsReturnsFalse_596) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back("item1");
    node.push_back("item2");
    std::string result;
    bool success = YAML::convert<std::string>::decode(node, result);
    EXPECT_FALSE(success);
}

// Test: decode preserves previous value on failure
TEST(YAMLConvertStringTest_596, DecodeFailureDoesNotModifyRhs_596) {
    YAML::Node node(YAML::NodeType::Sequence);
    std::string result = "original";
    bool success = YAML::convert<std::string>::decode(node, result);
    EXPECT_FALSE(success);
    EXPECT_EQ("original", result);
}

// Test: decode with a very long string
TEST(YAMLConvertStringTest_596, DecodeLongScalar_596) {
    std::string longStr(10000, 'x');
    YAML::Node node(longStr);
    std::string result;
    bool success = YAML::convert<std::string>::decode(node, result);
    EXPECT_TRUE(success);
    EXPECT_EQ(longStr, result);
}

// Test: Using Node::as<std::string>() which internally uses convert::decode
TEST(YAMLConvertStringTest_596, NodeAsStringUsesConvert_596) {
    YAML::Node node("test_value");
    std::string val = node.as<std::string>();
    EXPECT_EQ("test_value", val);
}

// Test: Node::as<std::string>() with fallback on non-scalar
TEST(YAMLConvertStringTest_596, NodeAsStringFallback_596) {
    YAML::Node node(YAML::NodeType::Sequence);
    std::string val = node.as<std::string>("fallback_value");
    EXPECT_EQ("fallback_value", val);
}

// Test: Node::IsScalar() check for scalar node
TEST(YAMLConvertStringTest_596, NodeIsScalarTrue_596) {
    YAML::Node node("scalar");
    EXPECT_TRUE(node.IsScalar());
}

// Test: Node::IsScalar() check for sequence node
TEST(YAMLConvertStringTest_596, NodeIsScalarFalseForSequence_596) {
    YAML::Node node(YAML::NodeType::Sequence);
    EXPECT_FALSE(node.IsScalar());
}

// Test: decode with whitespace-only scalar
TEST(YAMLConvertStringTest_596, DecodeWhitespaceScalar_596) {
    YAML::Node node("   ");
    std::string result;
    bool success = YAML::convert<std::string>::decode(node, result);
    EXPECT_TRUE(success);
    EXPECT_EQ("   ", result);
}
