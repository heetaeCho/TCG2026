#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include <string>
#include <unordered_map>
#include <map>
#include <vector>

// Test fixture for unordered_map decode tests
class UnorderedMapDecodeTest_610 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Decoding a valid map node into unordered_map<string, string>
TEST_F(UnorderedMapDecodeTest_610, DecodeValidMapStringString_610) {
    YAML::Node node;
    node["key1"] = "value1";
    node["key2"] = "value2";
    node["key3"] = "value3";

    std::unordered_map<std::string, std::string> result;
    bool success = YAML::convert<std::unordered_map<std::string, std::string>>::decode(node, result);

    EXPECT_TRUE(success);
    EXPECT_EQ(result.size(), 3u);
    EXPECT_EQ(result["key1"], "value1");
    EXPECT_EQ(result["key2"], "value2");
    EXPECT_EQ(result["key3"], "value3");
}

// Test: Decoding a valid map node into unordered_map<string, int>
TEST_F(UnorderedMapDecodeTest_610, DecodeValidMapStringInt_610) {
    YAML::Node node;
    node["a"] = 1;
    node["b"] = 2;
    node["c"] = 3;

    std::unordered_map<std::string, int> result;
    bool success = YAML::convert<std::unordered_map<std::string, int>>::decode(node, result);

    EXPECT_TRUE(success);
    EXPECT_EQ(result.size(), 3u);
    EXPECT_EQ(result["a"], 1);
    EXPECT_EQ(result["b"], 2);
    EXPECT_EQ(result["c"], 3);
}

// Test: Decoding a valid map node into unordered_map<int, int>
TEST_F(UnorderedMapDecodeTest_610, DecodeValidMapIntInt_610) {
    YAML::Node node;
    node[1] = 10;
    node[2] = 20;
    node[3] = 30;

    std::unordered_map<int, int> result;
    bool success = YAML::convert<std::unordered_map<int, int>>::decode(node, result);

    EXPECT_TRUE(success);
    EXPECT_EQ(result.size(), 3u);
    EXPECT_EQ(result[1], 10);
    EXPECT_EQ(result[2], 20);
    EXPECT_EQ(result[3], 30);
}

// Test: Decoding a sequence node should fail
TEST_F(UnorderedMapDecodeTest_610, DecodeSequenceNodeFails_610) {
    YAML::Node node;
    node.push_back("item1");
    node.push_back("item2");

    ASSERT_TRUE(node.IsSequence());

    std::unordered_map<std::string, std::string> result;
    bool success = YAML::convert<std::unordered_map<std::string, std::string>>::decode(node, result);

    EXPECT_FALSE(success);
}

// Test: Decoding a scalar node should fail
TEST_F(UnorderedMapDecodeTest_610, DecodeScalarNodeFails_610) {
    YAML::Node node("hello");

    ASSERT_TRUE(node.IsScalar());

    std::unordered_map<std::string, std::string> result;
    bool success = YAML::convert<std::unordered_map<std::string, std::string>>::decode(node, result);

    EXPECT_FALSE(success);
}

// Test: Decoding a null node should fail
TEST_F(UnorderedMapDecodeTest_610, DecodeNullNodeFails_610) {
    YAML::Node node(YAML::NodeType::Null);

    ASSERT_TRUE(node.IsNull());

    std::unordered_map<std::string, std::string> result;
    bool success = YAML::convert<std::unordered_map<std::string, std::string>>::decode(node, result);

    EXPECT_FALSE(success);
}

// Test: Decoding an empty map node succeeds and produces empty unordered_map
TEST_F(UnorderedMapDecodeTest_610, DecodeEmptyMapNode_610) {
    YAML::Node node(YAML::NodeType::Map);

    ASSERT_TRUE(node.IsMap());

    std::unordered_map<std::string, std::string> result;
    bool success = YAML::convert<std::unordered_map<std::string, std::string>>::decode(node, result);

    EXPECT_TRUE(success);
    EXPECT_TRUE(result.empty());
}

// Test: Decoding clears the existing content of the unordered_map
TEST_F(UnorderedMapDecodeTest_610, DecodeClearsExistingContent_610) {
    YAML::Node node;
    node["x"] = "y";

    std::unordered_map<std::string, std::string> result;
    result["old_key"] = "old_value";
    result["another"] = "data";

    bool success = YAML::convert<std::unordered_map<std::string, std::string>>::decode(node, result);

    EXPECT_TRUE(success);
    EXPECT_EQ(result.size(), 1u);
    EXPECT_EQ(result["x"], "y");
    EXPECT_EQ(result.find("old_key"), result.end());
    EXPECT_EQ(result.find("another"), result.end());
}

// Test: Decoding a single-element map
TEST_F(UnorderedMapDecodeTest_610, DecodeSingleElementMap_610) {
    YAML::Node node;
    node["only"] = "one";

    std::unordered_map<std::string, std::string> result;
    bool success = YAML::convert<std::unordered_map<std::string, std::string>>::decode(node, result);

    EXPECT_TRUE(success);
    EXPECT_EQ(result.size(), 1u);
    EXPECT_EQ(result["only"], "one");
}

// Test: Decoding a map with integer keys and string values
TEST_F(UnorderedMapDecodeTest_610, DecodeIntKeyStringValue_610) {
    YAML::Node node;
    node[42] = "answer";
    node[0] = "zero";

    std::unordered_map<int, std::string> result;
    bool success = YAML::convert<std::unordered_map<int, std::string>>::decode(node, result);

    EXPECT_TRUE(success);
    EXPECT_EQ(result.size(), 2u);
    EXPECT_EQ(result[42], "answer");
    EXPECT_EQ(result[0], "zero");
}

// Test: Using Node::as<> to convert to unordered_map
TEST_F(UnorderedMapDecodeTest_610, NodeAsUnorderedMap_610) {
    YAML::Node node;
    node["foo"] = "bar";
    node["baz"] = "qux";

    auto result = node.as<std::unordered_map<std::string, std::string>>();

    EXPECT_EQ(result.size(), 2u);
    EXPECT_EQ(result["foo"], "bar");
    EXPECT_EQ(result["baz"], "qux");
}

// Test: Decoding from YAML string
TEST_F(UnorderedMapDecodeTest_610, DecodeFromYAMLString_610) {
    std::string yaml = "alpha: 1\nbeta: 2\ngamma: 3\n";
    YAML::Node node = YAML::Load(yaml);

    std::unordered_map<std::string, int> result;
    bool success = YAML::convert<std::unordered_map<std::string, int>>::decode(node, result);

    EXPECT_TRUE(success);
    EXPECT_EQ(result.size(), 3u);
    EXPECT_EQ(result["alpha"], 1);
    EXPECT_EQ(result["beta"], 2);
    EXPECT_EQ(result["gamma"], 3);
}

// Test: Decoding a map with double values
TEST_F(UnorderedMapDecodeTest_610, DecodeMapWithDoubleValues_610) {
    YAML::Node node;
    node["pi"] = 3.14;
    node["e"] = 2.718;

    std::unordered_map<std::string, double> result;
    bool success = YAML::convert<std::unordered_map<std::string, double>>::decode(node, result);

    EXPECT_TRUE(success);
    EXPECT_EQ(result.size(), 2u);
    EXPECT_NEAR(result["pi"], 3.14, 0.01);
    EXPECT_NEAR(result["e"], 2.718, 0.01);
}

// Test: Decoding a map with bool values
TEST_F(UnorderedMapDecodeTest_610, DecodeMapWithBoolValues_610) {
    YAML::Node node;
    node["flag1"] = true;
    node["flag2"] = false;

    std::unordered_map<std::string, bool> result;
    bool success = YAML::convert<std::unordered_map<std::string, bool>>::decode(node, result);

    EXPECT_TRUE(success);
    EXPECT_EQ(result.size(), 2u);
    EXPECT_TRUE(result["flag1"]);
    EXPECT_FALSE(result["flag2"]);
}

// Test: Undefined node should fail decode
TEST_F(UnorderedMapDecodeTest_610, DecodeUndefinedNodeFails_610) {
    YAML::Node node;
    // Access a non-existent key to get an undefined node
    YAML::Node undefinedNode = node["nonexistent"];

    std::unordered_map<std::string, std::string> result;
    bool success = YAML::convert<std::unordered_map<std::string, std::string>>::decode(undefinedNode, result);

    EXPECT_FALSE(success);
}

// Test: Decoding when rhs already has data, decode clears it properly
TEST_F(UnorderedMapDecodeTest_610, DecodeClearsOnEmptyMap_610) {
    YAML::Node node(YAML::NodeType::Map);

    std::unordered_map<std::string, std::string> result;
    result["pre_existing"] = "value";

    bool success = YAML::convert<std::unordered_map<std::string, std::string>>::decode(node, result);

    EXPECT_TRUE(success);
    EXPECT_TRUE(result.empty());
}

// Test: Large map decoding
TEST_F(UnorderedMapDecodeTest_610, DecodeLargeMap_610) {
    YAML::Node node;
    const int count = 100;
    for (int i = 0; i < count; ++i) {
        node[std::to_string(i)] = i;
    }

    std::unordered_map<std::string, int> result;
    bool success = YAML::convert<std::unordered_map<std::string, int>>::decode(node, result);

    EXPECT_TRUE(success);
    EXPECT_EQ(result.size(), static_cast<size_t>(count));
    for (int i = 0; i < count; ++i) {
        EXPECT_EQ(result[std::to_string(i)], i);
    }
}

// Test: Encoding and then decoding unordered_map roundtrip
TEST_F(UnorderedMapDecodeTest_610, RoundTripEncodeDecodе_610) {
    std::unordered_map<std::string, int> original;
    original["one"] = 1;
    original["two"] = 2;
    original["three"] = 3;

    YAML::Node node(original);

    std::unordered_map<std::string, int> decoded;
    bool success = YAML::convert<std::unordered_map<std::string, int>>::decode(node, decoded);

    EXPECT_TRUE(success);
    EXPECT_EQ(decoded.size(), original.size());
    for (const auto& kv : original) {
        EXPECT_EQ(decoded[kv.first], kv.second);
    }
}
