#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include <string>
#include <string_view>

// Test: decode returns false for non-scalar nodes (Null node)
TEST(YamlConvertStringView_601, DecodeFailsForNullNode_601) {
    YAML::Node node;
    std::string_view sv;
    bool result = YAML::convert<std::string_view>::decode(node, sv);
    EXPECT_FALSE(result);
}

// Test: decode returns true for scalar node and sets string_view correctly
TEST(YamlConvertStringView_601, DecodeSucceedsForScalarNode_601) {
    YAML::Node node = YAML::Node("hello");
    std::string_view sv;
    bool result = YAML::convert<std::string_view>::decode(node, sv);
    EXPECT_TRUE(result);
    EXPECT_EQ(sv, "hello");
}

// Test: decode returns false for sequence node
TEST(YamlConvertStringView_601, DecodeFailsForSequenceNode_601) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back("item1");
    node.push_back("item2");
    std::string_view sv;
    bool result = YAML::convert<std::string_view>::decode(node, sv);
    EXPECT_FALSE(result);
}

// Test: decode returns false for map node
TEST(YamlConvertStringView_601, DecodeFailsForMapNode_601) {
    YAML::Node node(YAML::NodeType::Map);
    node["key"] = "value";
    std::string_view sv;
    bool result = YAML::convert<std::string_view>::decode(node, sv);
    EXPECT_FALSE(result);
}

// Test: decode works with empty scalar string
TEST(YamlConvertStringView_601, DecodeSucceedsForEmptyScalar_601) {
    YAML::Node node = YAML::Node(std::string(""));
    std::string_view sv = "initial";
    bool result = YAML::convert<std::string_view>::decode(node, sv);
    EXPECT_TRUE(result);
    EXPECT_EQ(sv, "");
}

// Test: decode correctly handles scalar with special characters
TEST(YamlConvertStringView_601, DecodeSucceedsForScalarWithSpecialChars_601) {
    YAML::Node node = YAML::Node("hello\nworld\ttab");
    std::string_view sv;
    bool result = YAML::convert<std::string_view>::decode(node, sv);
    EXPECT_TRUE(result);
    EXPECT_EQ(sv, "hello\nworld\ttab");
}

// Test: decode correctly handles scalar with spaces
TEST(YamlConvertStringView_601, DecodeSucceedsForScalarWithSpaces_601) {
    YAML::Node node = YAML::Node("  spaces around  ");
    std::string_view sv;
    bool result = YAML::convert<std::string_view>::decode(node, sv);
    EXPECT_TRUE(result);
    EXPECT_EQ(sv, "  spaces around  ");
}

// Test: decode from parsed YAML scalar
TEST(YamlConvertStringView_601, DecodeFromParsedYamlScalar_601) {
    YAML::Node node = YAML::Load("test_value");
    std::string_view sv;
    bool result = YAML::convert<std::string_view>::decode(node, sv);
    EXPECT_TRUE(result);
    EXPECT_EQ(sv, "test_value");
}

// Test: decode from parsed YAML map value (accessing scalar inside map)
TEST(YamlConvertStringView_601, DecodeFromParsedYamlMapValue_601) {
    YAML::Node root = YAML::Load("key: value");
    YAML::Node valueNode = root["key"];
    std::string_view sv;
    bool result = YAML::convert<std::string_view>::decode(valueNode, sv);
    EXPECT_TRUE(result);
    EXPECT_EQ(sv, "value");
}

// Test: decode fails for entire map node parsed from YAML
TEST(YamlConvertStringView_601, DecodeFailsForParsedMapNode_601) {
    YAML::Node root = YAML::Load("{a: 1, b: 2}");
    std::string_view sv;
    bool result = YAML::convert<std::string_view>::decode(root, sv);
    EXPECT_FALSE(result);
}

// Test: decode fails for entire sequence node parsed from YAML
TEST(YamlConvertStringView_601, DecodeFailsForParsedSequenceNode_601) {
    YAML::Node root = YAML::Load("[1, 2, 3]");
    std::string_view sv;
    bool result = YAML::convert<std::string_view>::decode(root, sv);
    EXPECT_FALSE(result);
}

// Test: decode with numeric scalar
TEST(YamlConvertStringView_601, DecodeSucceedsForNumericScalar_601) {
    YAML::Node node = YAML::Node("12345");
    std::string_view sv;
    bool result = YAML::convert<std::string_view>::decode(node, sv);
    EXPECT_TRUE(result);
    EXPECT_EQ(sv, "12345");
}

// Test: decode with long string scalar
TEST(YamlConvertStringView_601, DecodeSucceedsForLongScalar_601) {
    std::string longStr(10000, 'x');
    YAML::Node node = YAML::Node(longStr);
    std::string_view sv;
    bool result = YAML::convert<std::string_view>::decode(node, sv);
    EXPECT_TRUE(result);
    EXPECT_EQ(sv.size(), 10000u);
    EXPECT_EQ(sv, longStr);
}

// Test: string_view points to the same data as Node::Scalar()
TEST(YamlConvertStringView_601, StringViewPointsToNodeScalarData_601) {
    YAML::Node node = YAML::Node("test_data");
    std::string_view sv;
    YAML::convert<std::string_view>::decode(node, sv);
    // The string_view should reference the same underlying data as node.Scalar()
    EXPECT_EQ(sv.data(), node.Scalar().data());
}

// Test: Using Node::as<std::string_view> for scalar
TEST(YamlConvertStringView_601, NodeAsStringView_601) {
    YAML::Node node = YAML::Node("as_test");
    std::string_view sv = node.as<std::string_view>();
    EXPECT_EQ(sv, "as_test");
}

// Test: Explicitly created Null node type
TEST(YamlConvertStringView_601, DecodeFailsForExplicitNullType_601) {
    YAML::Node node(YAML::NodeType::Null);
    std::string_view sv;
    bool result = YAML::convert<std::string_view>::decode(node, sv);
    EXPECT_FALSE(result);
}

// Test: Node::as with fallback for non-scalar
TEST(YamlConvertStringView_601, NodeAsStringViewWithFallback_601) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back("item");
    std::string_view fallback = "default";
    std::string_view result = node.as<std::string_view>(fallback);
    EXPECT_EQ(result, "default");
}
