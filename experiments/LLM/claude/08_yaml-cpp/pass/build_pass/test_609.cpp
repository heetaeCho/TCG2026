#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include <unordered_map>
#include <string>
#include <map>
#include <vector>

// Test encoding an empty unordered_map
TEST(UnorderedMapConvertTest_609, EncodeEmptyMap_609) {
    std::unordered_map<std::string, std::string> emptyMap;
    YAML::Node node(emptyMap);
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 0u);
}

// Test encoding a single-element unordered_map
TEST(UnorderedMapConvertTest_609, EncodeSingleElement_609) {
    std::unordered_map<std::string, int> singleMap;
    singleMap["key1"] = 42;
    YAML::Node node(singleMap);
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 1u);
    EXPECT_EQ(node["key1"].as<int>(), 42);
}

// Test encoding multiple elements
TEST(UnorderedMapConvertTest_609, EncodeMultipleElements_609) {
    std::unordered_map<std::string, int> multiMap;
    multiMap["a"] = 1;
    multiMap["b"] = 2;
    multiMap["c"] = 3;
    YAML::Node node(multiMap);
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node["a"].as<int>(), 1);
    EXPECT_EQ(node["b"].as<int>(), 2);
    EXPECT_EQ(node["c"].as<int>(), 3);
}

// Test encoding with integer keys and string values
TEST(UnorderedMapConvertTest_609, EncodeIntKeyStringValue_609) {
    std::unordered_map<int, std::string> intMap;
    intMap[1] = "one";
    intMap[2] = "two";
    intMap[3] = "three";
    YAML::Node node(intMap);
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[1].as<std::string>(), "one");
    EXPECT_EQ(node[2].as<std::string>(), "two");
    EXPECT_EQ(node[3].as<std::string>(), "three");
}

// Test encoding with double values
TEST(UnorderedMapConvertTest_609, EncodeDoubleValues_609) {
    std::unordered_map<std::string, double> doubleMap;
    doubleMap["pi"] = 3.14159;
    doubleMap["e"] = 2.71828;
    YAML::Node node(doubleMap);
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 2u);
    EXPECT_NEAR(node["pi"].as<double>(), 3.14159, 0.0001);
    EXPECT_NEAR(node["e"].as<double>(), 2.71828, 0.0001);
}

// Test encoding with bool values
TEST(UnorderedMapConvertTest_609, EncodeBoolValues_609) {
    std::unordered_map<std::string, bool> boolMap;
    boolMap["true_val"] = true;
    boolMap["false_val"] = false;
    YAML::Node node(boolMap);
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 2u);
    EXPECT_EQ(node["true_val"].as<bool>(), true);
    EXPECT_EQ(node["false_val"].as<bool>(), false);
}

// Test that encoding produces a Map type node
TEST(UnorderedMapConvertTest_609, EncodeProducesMapType_609) {
    std::unordered_map<std::string, std::string> m;
    m["x"] = "y";
    YAML::Node node(m);
    EXPECT_EQ(node.Type(), YAML::NodeType::Map);
}

// Test encoding with empty string keys
TEST(UnorderedMapConvertTest_609, EncodeEmptyStringKey_609) {
    std::unordered_map<std::string, int> m;
    m[""] = 100;
    YAML::Node node(m);
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 1u);
    EXPECT_EQ(node[""].as<int>(), 100);
}

// Test encoding with empty string values
TEST(UnorderedMapConvertTest_609, EncodeEmptyStringValue_609) {
    std::unordered_map<std::string, std::string> m;
    m["key"] = "";
    YAML::Node node(m);
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 1u);
    EXPECT_EQ(node["key"].as<std::string>(), "");
}

// Test encoding with negative integer keys
TEST(UnorderedMapConvertTest_609, EncodeNegativeIntKeys_609) {
    std::unordered_map<int, std::string> m;
    m[-1] = "neg_one";
    m[0] = "zero";
    m[1] = "one";
    YAML::Node node(m);
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[-1].as<std::string>(), "neg_one");
    EXPECT_EQ(node[0].as<std::string>(), "zero");
    EXPECT_EQ(node[1].as<std::string>(), "one");
}

// Test decoding back to unordered_map (round-trip)
TEST(UnorderedMapConvertTest_609, RoundTripEncodeDecode_609) {
    std::unordered_map<std::string, int> original;
    original["alpha"] = 10;
    original["beta"] = 20;
    original["gamma"] = 30;

    YAML::Node node(original);
    auto decoded = node.as<std::unordered_map<std::string, int>>();

    EXPECT_EQ(decoded.size(), original.size());
    for (const auto& kv : original) {
        EXPECT_EQ(decoded[kv.first], kv.second);
    }
}

// Test decoding empty map
TEST(UnorderedMapConvertTest_609, RoundTripEmptyMap_609) {
    std::unordered_map<std::string, std::string> original;
    YAML::Node node(original);
    auto decoded = node.as<std::unordered_map<std::string, std::string>>();
    EXPECT_TRUE(decoded.empty());
}

// Test encoding a large unordered_map
TEST(UnorderedMapConvertTest_609, EncodeLargeMap_609) {
    std::unordered_map<int, int> largeMap;
    for (int i = 0; i < 1000; ++i) {
        largeMap[i] = i * 2;
    }
    YAML::Node node(largeMap);
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 1000u);

    // Spot-check a few values
    EXPECT_EQ(node[0].as<int>(), 0);
    EXPECT_EQ(node[500].as<int>(), 1000);
    EXPECT_EQ(node[999].as<int>(), 1998);
}

// Test encoding int-to-int map
TEST(UnorderedMapConvertTest_609, EncodeIntToIntMap_609) {
    std::unordered_map<int, int> m;
    m[10] = 100;
    m[20] = 200;
    YAML::Node node(m);
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 2u);
    EXPECT_EQ(node[10].as<int>(), 100);
    EXPECT_EQ(node[20].as<int>(), 200);
}

// Test that the node created from unordered_map is not a sequence
TEST(UnorderedMapConvertTest_609, EncodeIsNotSequence_609) {
    std::unordered_map<std::string, std::string> m;
    m["foo"] = "bar";
    YAML::Node node(m);
    EXPECT_FALSE(node.IsSequence());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_FALSE(node.IsNull());
}

// Test encoding with special characters in keys and values
TEST(UnorderedMapConvertTest_609, EncodeSpecialCharacters_609) {
    std::unordered_map<std::string, std::string> m;
    m["key with spaces"] = "value with spaces";
    m["key:colon"] = "value:colon";
    m["key\nnewline"] = "value\nnewline";
    YAML::Node node(m);
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node["key with spaces"].as<std::string>(), "value with spaces");
    EXPECT_EQ(node["key:colon"].as<std::string>(), "value:colon");
    EXPECT_EQ(node["key\nnewline"].as<std::string>(), "value\nnewline");
}

// Test round-trip with int keys
TEST(UnorderedMapConvertTest_609, RoundTripIntKeys_609) {
    std::unordered_map<int, std::string> original;
    original[42] = "answer";
    original[0] = "zero";
    original[-5] = "negative";

    YAML::Node node(original);
    auto decoded = node.as<std::unordered_map<int, std::string>>();

    EXPECT_EQ(decoded.size(), original.size());
    for (const auto& kv : original) {
        EXPECT_EQ(decoded[kv.first], kv.second);
    }
}

// Test that the encoded node is iterable
TEST(UnorderedMapConvertTest_609, EncodeIterableNode_609) {
    std::unordered_map<std::string, int> m;
    m["x"] = 1;
    m["y"] = 2;
    YAML::Node node(m);

    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 2);
}

// Test overwriting values - since unordered_map keys are unique, each key maps to one value
TEST(UnorderedMapConvertTest_609, EncodeUniqueKeys_609) {
    std::unordered_map<std::string, int> m;
    m["dup"] = 1;
    // In unordered_map, inserting same key overwrites
    m["dup"] = 2;
    YAML::Node node(m);
    EXPECT_EQ(node.size(), 1u);
    EXPECT_EQ(node["dup"].as<int>(), 2);
}
