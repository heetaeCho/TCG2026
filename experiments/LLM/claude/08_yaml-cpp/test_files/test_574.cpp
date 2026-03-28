#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"

// Test basic construction and type checking
TEST(NodeOperatorBracketTest_574, DefaultNodeIsNull_574) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
}

TEST(NodeOperatorBracketTest_574, AccessNonExistentKeyOnMapReturnsUndefined_574) {
    YAML::Node node(YAML::NodeType::Map);
    const YAML::Node result = node["nonexistent"];
    EXPECT_FALSE(result.IsDefined());
}

TEST(NodeOperatorBracketTest_574, AccessExistingKeyOnMapReturnsDefined_574) {
    YAML::Node node;
    node["key"] = "value";
    const YAML::Node result = node["key"];
    EXPECT_TRUE(result.IsDefined());
    EXPECT_EQ(result.as<std::string>(), "value");
}

TEST(NodeOperatorBracketTest_574, AccessKeyWithNodeTypeKey_574) {
    YAML::Node node;
    node["hello"] = "world";
    YAML::Node key;
    key = std::string("hello");
    const YAML::Node result = node[key];
    EXPECT_TRUE(result.IsDefined());
    EXPECT_EQ(result.as<std::string>(), "world");
}

TEST(NodeOperatorBracketTest_574, AccessNonExistentNodeKeyReturnsUndefined_574) {
    YAML::Node node;
    node["a"] = "b";
    YAML::Node key;
    key = std::string("missing");
    const YAML::Node result = node[key];
    EXPECT_FALSE(result.IsDefined());
}

TEST(NodeOperatorBracketTest_574, AccessSequenceByIndex_574) {
    YAML::Node node;
    node.push_back("first");
    node.push_back("second");
    node.push_back("third");
    const YAML::Node result = node[1];
    EXPECT_TRUE(result.IsDefined());
    EXPECT_EQ(result.as<std::string>(), "second");
}

TEST(NodeOperatorBracketTest_574, AccessSequenceByOutOfRangeIndex_574) {
    YAML::Node node;
    node.push_back("first");
    const YAML::Node result = node[10];
    EXPECT_FALSE(result.IsDefined());
}

TEST(NodeOperatorBracketTest_574, AccessSequenceByIndexZero_574) {
    YAML::Node node;
    node.push_back("only");
    const YAML::Node result = node[0];
    EXPECT_TRUE(result.IsDefined());
    EXPECT_EQ(result.as<std::string>(), "only");
}

TEST(NodeOperatorBracketTest_574, ConstAccessOnMap_574) {
    YAML::Node node;
    node["x"] = 42;
    const YAML::Node& constNode = node;
    const YAML::Node result = constNode["x"];
    EXPECT_TRUE(result.IsDefined());
    EXPECT_EQ(result.as<int>(), 42);
}

TEST(NodeOperatorBracketTest_574, ConstAccessNonExistentKeyDoesNotModify_574) {
    YAML::Node node;
    node["a"] = 1;
    const YAML::Node& constNode = node;
    const YAML::Node result = constNode["b"];
    EXPECT_FALSE(result.IsDefined());
    EXPECT_EQ(node.size(), 1u);
}

TEST(NodeOperatorBracketTest_574, NestedMapAccess_574) {
    YAML::Node node;
    node["outer"]["inner"] = "deep";
    const YAML::Node result = node["outer"]["inner"];
    EXPECT_TRUE(result.IsDefined());
    EXPECT_EQ(result.as<std::string>(), "deep");
}

TEST(NodeOperatorBracketTest_574, AccessWithIntegerKey_574) {
    YAML::Node node;
    node[42] = "answer";
    const YAML::Node result = node[42];
    EXPECT_TRUE(result.IsDefined());
    EXPECT_EQ(result.as<std::string>(), "answer");
}

TEST(NodeOperatorBracketTest_574, AccessWithStringKey_574) {
    YAML::Node node;
    node["str_key"] = "str_value";
    const YAML::Node result = node[std::string("str_key")];
    EXPECT_TRUE(result.IsDefined());
    EXPECT_EQ(result.as<std::string>(), "str_value");
}

TEST(NodeOperatorBracketTest_574, AccessWithCharPtrKey_574) {
    YAML::Node node;
    node["ckey"] = "cval";
    const char* key = "ckey";
    const YAML::Node result = node[key];
    EXPECT_TRUE(result.IsDefined());
    EXPECT_EQ(result.as<std::string>(), "cval");
}

TEST(NodeOperatorBracketTest_574, MultipleKeysInMap_574) {
    YAML::Node node;
    node["a"] = 1;
    node["b"] = 2;
    node["c"] = 3;
    EXPECT_EQ(node["a"].as<int>(), 1);
    EXPECT_EQ(node["b"].as<int>(), 2);
    EXPECT_EQ(node["c"].as<int>(), 3);
    EXPECT_EQ(node.size(), 3u);
}

TEST(NodeOperatorBracketTest_574, AccessAfterRemove_574) {
    YAML::Node node;
    node["keep"] = "yes";
    node["remove"] = "no";
    node.remove("remove");
    const YAML::Node result = node["remove"];
    EXPECT_FALSE(result.IsDefined());
}

TEST(NodeOperatorBracketTest_574, NodeKeyAccessOnEmptyMap_574) {
    YAML::Node node(YAML::NodeType::Map);
    YAML::Node key("missing");
    const YAML::Node result = node[key];
    EXPECT_FALSE(result.IsDefined());
}

TEST(NodeOperatorBracketTest_574, ParsedYamlMapAccess_574) {
    YAML::Node node = YAML::Load("{name: John, age: 30}");
    EXPECT_EQ(node["name"].as<std::string>(), "John");
    EXPECT_EQ(node["age"].as<int>(), 30);
}

TEST(NodeOperatorBracketTest_574, ParsedYamlSequenceAccess_574) {
    YAML::Node node = YAML::Load("[10, 20, 30]");
    EXPECT_EQ(node[0].as<int>(), 10);
    EXPECT_EQ(node[1].as<int>(), 20);
    EXPECT_EQ(node[2].as<int>(), 30);
}

TEST(NodeOperatorBracketTest_574, ParsedNestedYaml_574) {
    YAML::Node node = YAML::Load("{outer: {inner: value}}");
    const YAML::Node result = node["outer"]["inner"];
    EXPECT_TRUE(result.IsDefined());
    EXPECT_EQ(result.as<std::string>(), "value");
}

TEST(NodeOperatorBracketTest_574, AccessReturnsCorrectType_574) {
    YAML::Node node;
    node["scalar"] = "hello";
    node["seq"].push_back(1);
    node["map"]["k"] = "v";
    EXPECT_TRUE(node["scalar"].IsScalar());
    EXPECT_TRUE(node["seq"].IsSequence());
    EXPECT_TRUE(node["map"].IsMap());
}

TEST(NodeOperatorBracketTest_574, ZombieNodeBoolConversion_574) {
    YAML::Node node(YAML::NodeType::Map);
    const YAML::Node result = node["nonexistent_key"];
    // A zombie/undefined node should still be convertible to bool
    // but IsDefined should be false
    EXPECT_FALSE(result.IsDefined());
}

TEST(NodeOperatorBracketTest_574, AccessWithNodeKeyThatExists_574) {
    YAML::Node node;
    node["found"] = "yes";
    YAML::Node keyNode("found");
    const YAML::Node result = node[keyNode];
    EXPECT_TRUE(result.IsDefined());
    EXPECT_EQ(result.as<std::string>(), "yes");
}

TEST(NodeOperatorBracketTest_574, EmptyStringKey_574) {
    YAML::Node node;
    node[""] = "empty_key_value";
    const YAML::Node result = node[""];
    EXPECT_TRUE(result.IsDefined());
    EXPECT_EQ(result.as<std::string>(), "empty_key_value");
}

TEST(NodeOperatorBracketTest_574, OverwriteValueAndAccess_574) {
    YAML::Node node;
    node["key"] = "first";
    node["key"] = "second";
    const YAML::Node result = node["key"];
    EXPECT_EQ(result.as<std::string>(), "second");
}

TEST(NodeOperatorBracketTest_574, AccessOnScalarNodeThrows_574) {
    YAML::Node node("scalar_value");
    EXPECT_TRUE(node.IsScalar());
    // Accessing a key on a scalar should throw or produce an error
    EXPECT_THROW(node["key"], YAML::BadSubscript);
}

TEST(NodeOperatorBracketTest_574, SequenceWithMixedTypes_574) {
    YAML::Node node = YAML::Load("[1, hello, 3.14, true]");
    EXPECT_EQ(node[0].as<int>(), 1);
    EXPECT_EQ(node[1].as<std::string>(), "hello");
    EXPECT_NEAR(node[2].as<double>(), 3.14, 0.001);
    EXPECT_EQ(node[3].as<bool>(), true);
}

TEST(NodeOperatorBracketTest_574, MapSizeConsistentWithAccess_574) {
    YAML::Node node;
    node["a"] = 1;
    node["b"] = 2;
    EXPECT_EQ(node.size(), 2u);
    // Const access should not increase size
    const YAML::Node& cnode = node;
    cnode["c"];
    EXPECT_EQ(node.size(), 2u);
}

TEST(NodeOperatorBracketTest_574, AccessWithFallbackOnUndefined_574) {
    YAML::Node node(YAML::NodeType::Map);
    const YAML::Node result = node["missing"];
    // Using as<> with fallback on undefined node
    EXPECT_EQ(result.as<std::string>("default_val"), "default_val");
}

TEST(NodeOperatorBracketTest_574, LargeMapAccess_574) {
    YAML::Node node;
    for (int i = 0; i < 1000; ++i) {
        node[std::to_string(i)] = i;
    }
    EXPECT_EQ(node.size(), 1000u);
    EXPECT_EQ(node["500"].as<int>(), 500);
    EXPECT_EQ(node["999"].as<int>(), 999);
    EXPECT_EQ(node["0"].as<int>(), 0);
}
