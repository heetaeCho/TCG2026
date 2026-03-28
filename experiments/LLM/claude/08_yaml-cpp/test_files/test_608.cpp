#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include <map>
#include <string>
#include <vector>

// Test fixture for convert.h map decode tests
class MapConvertTest_608 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Decoding a valid map node with string keys and string values
TEST_F(MapConvertTest_608, DecodeStringStringMap_608) {
    YAML::Node node;
    node["key1"] = "value1";
    node["key2"] = "value2";
    node["key3"] = "value3";

    std::map<std::string, std::string> result;
    ASSERT_TRUE(YAML::convert<std::map<std::string, std::string>>::decode(node, result));
    EXPECT_EQ(result.size(), 3u);
    EXPECT_EQ(result["key1"], "value1");
    EXPECT_EQ(result["key2"], "value2");
    EXPECT_EQ(result["key3"], "value3");
}

// Test: Decoding a valid map node with string keys and int values
TEST_F(MapConvertTest_608, DecodeStringIntMap_608) {
    YAML::Node node;
    node["a"] = "1";
    node["b"] = "2";
    node["c"] = "3";

    std::map<std::string, int> result;
    ASSERT_TRUE(YAML::convert<std::map<std::string, int>>::decode(node, result));
    EXPECT_EQ(result.size(), 3u);
    EXPECT_EQ(result["a"], 1);
    EXPECT_EQ(result["b"], 2);
    EXPECT_EQ(result["c"], 3);
}

// Test: Decoding a valid map node with int keys and int values
TEST_F(MapConvertTest_608, DecodeIntIntMap_608) {
    YAML::Node node;
    node[1] = 10;
    node[2] = 20;
    node[3] = 30;

    std::map<int, int> result;
    ASSERT_TRUE(YAML::convert<std::map<int, int>>::decode(node, result));
    EXPECT_EQ(result.size(), 3u);
    EXPECT_EQ(result[1], 10);
    EXPECT_EQ(result[2], 20);
    EXPECT_EQ(result[3], 30);
}

// Test: Decoding a non-map node (sequence) should return false
TEST_F(MapConvertTest_608, DecodeSequenceNodeReturnsFalse_608) {
    YAML::Node node;
    node.push_back("item1");
    node.push_back("item2");

    std::map<std::string, std::string> result;
    ASSERT_FALSE(YAML::convert<std::map<std::string, std::string>>::decode(node, result));
}

// Test: Decoding a scalar node should return false
TEST_F(MapConvertTest_608, DecodeScalarNodeReturnsFalse_608) {
    YAML::Node node("just a scalar");

    std::map<std::string, std::string> result;
    ASSERT_FALSE(YAML::convert<std::map<std::string, std::string>>::decode(node, result));
}

// Test: Decoding a null node should return false
TEST_F(MapConvertTest_608, DecodeNullNodeReturnsFalse_608) {
    YAML::Node node(YAML::NodeType::Null);

    std::map<std::string, std::string> result;
    ASSERT_FALSE(YAML::convert<std::map<std::string, std::string>>::decode(node, result));
}

// Test: Decoding an empty map node should succeed and result in empty map
TEST_F(MapConvertTest_608, DecodeEmptyMapNode_608) {
    YAML::Node node(YAML::NodeType::Map);

    std::map<std::string, std::string> result;
    result["pre-existing"] = "data";
    ASSERT_TRUE(YAML::convert<std::map<std::string, std::string>>::decode(node, result));
    EXPECT_TRUE(result.empty());
}

// Test: Decoding clears existing data in the map
TEST_F(MapConvertTest_608, DecodeClearsExistingData_608) {
    YAML::Node node;
    node["new_key"] = "new_value";

    std::map<std::string, std::string> result;
    result["old_key"] = "old_value";
    result["another_old"] = "another_old_value";

    ASSERT_TRUE(YAML::convert<std::map<std::string, std::string>>::decode(node, result));
    EXPECT_EQ(result.size(), 1u);
    EXPECT_EQ(result.count("old_key"), 0u);
    EXPECT_EQ(result.count("another_old"), 0u);
    EXPECT_EQ(result["new_key"], "new_value");
}

// Test: Decoding a map with a single element
TEST_F(MapConvertTest_608, DecodeSingleElementMap_608) {
    YAML::Node node;
    node["only"] = "one";

    std::map<std::string, std::string> result;
    ASSERT_TRUE(YAML::convert<std::map<std::string, std::string>>::decode(node, result));
    EXPECT_EQ(result.size(), 1u);
    EXPECT_EQ(result["only"], "one");
}

// Test: Decoding from YAML string
TEST_F(MapConvertTest_608, DecodeFromYAMLString_608) {
    std::string yaml_str = "alpha: 100\nbeta: 200\ngamma: 300";
    YAML::Node node = YAML::Load(yaml_str);

    std::map<std::string, int> result;
    ASSERT_TRUE(YAML::convert<std::map<std::string, int>>::decode(node, result));
    EXPECT_EQ(result.size(), 3u);
    EXPECT_EQ(result["alpha"], 100);
    EXPECT_EQ(result["beta"], 200);
    EXPECT_EQ(result["gamma"], 300);
}

// Test: Using Node::as<> to convert directly
TEST_F(MapConvertTest_608, NodeAsMap_608) {
    YAML::Node node;
    node["x"] = "10";
    node["y"] = "20";

    auto result = node.as<std::map<std::string, std::string>>();
    EXPECT_EQ(result.size(), 2u);
    EXPECT_EQ(result["x"], "10");
    EXPECT_EQ(result["y"], "20");
}

// Test: Decoding a map with duplicate keys (last value should win in YAML node)
TEST_F(MapConvertTest_608, DecodeMapWithDuplicateKeys_608) {
    std::string yaml_str = "key: first\nkey: second";
    YAML::Node node = YAML::Load(yaml_str);

    std::map<std::string, std::string> result;
    ASSERT_TRUE(YAML::convert<std::map<std::string, std::string>>::decode(node, result));
    // The YAML spec says duplicate keys are an error, but yaml-cpp may handle it;
    // at minimum, we should get a valid map with the key present
    EXPECT_EQ(result.count("key"), 1u);
}

// Test: Decoding int keys and string values
TEST_F(MapConvertTest_608, DecodeIntKeyStringValueMap_608) {
    YAML::Node node;
    node[42] = "answer";
    node[0] = "zero";

    std::map<int, std::string> result;
    ASSERT_TRUE(YAML::convert<std::map<int, std::string>>::decode(node, result));
    EXPECT_EQ(result.size(), 2u);
    EXPECT_EQ(result[42], "answer");
    EXPECT_EQ(result[0], "zero");
}

// Test: Node::as with fallback when node is not a map
TEST_F(MapConvertTest_608, NodeAsMapWithFallback_608) {
    YAML::Node node("not a map");
    std::map<std::string, std::string> fallback;
    fallback["default"] = "value";

    auto result = node.as<std::map<std::string, std::string>>(fallback);
    EXPECT_EQ(result.size(), 1u);
    EXPECT_EQ(result["default"], "value");
}

// Test: Large map decode
TEST_F(MapConvertTest_608, DecodeLargeMap_608) {
    YAML::Node node;
    const int count = 1000;
    for (int i = 0; i < count; ++i) {
        node[std::to_string(i)] = std::to_string(i * 10);
    }

    std::map<std::string, std::string> result;
    ASSERT_TRUE(YAML::convert<std::map<std::string, std::string>>::decode(node, result));
    EXPECT_EQ(result.size(), static_cast<std::size_t>(count));
    EXPECT_EQ(result["0"], "0");
    EXPECT_EQ(result["999"], "9990");
}

// Test: Decoding map with bool values
TEST_F(MapConvertTest_608, DecodeStringBoolMap_608) {
    YAML::Node node;
    node["enabled"] = "true";
    node["disabled"] = "false";

    std::map<std::string, bool> result;
    ASSERT_TRUE(YAML::convert<std::map<std::string, bool>>::decode(node, result));
    EXPECT_EQ(result.size(), 2u);
    EXPECT_TRUE(result["enabled"]);
    EXPECT_FALSE(result["disabled"]);
}

// Test: Decoding map with double values
TEST_F(MapConvertTest_608, DecodeStringDoubleMap_608) {
    YAML::Node node;
    node["pi"] = "3.14159";
    node["e"] = "2.71828";

    std::map<std::string, double> result;
    ASSERT_TRUE(YAML::convert<std::map<std::string, double>>::decode(node, result));
    EXPECT_EQ(result.size(), 2u);
    EXPECT_NEAR(result["pi"], 3.14159, 0.0001);
    EXPECT_NEAR(result["e"], 2.71828, 0.0001);
}

// Test: Undefined node should return false
TEST_F(MapConvertTest_608, DecodeUndefinedNodeReturnsFalse_608) {
    YAML::Node parent;
    YAML::Node undefined = parent["nonexistent"];

    std::map<std::string, std::string> result;
    ASSERT_FALSE(YAML::convert<std::map<std::string, std::string>>::decode(undefined, result));
}
