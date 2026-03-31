#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include <string>
#include <vector>

// Test fixture
class NodeForceInsertTest_576 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Normal operation: force_insert with string key and string value into a map node
TEST_F(NodeForceInsertTest_576, ForceInsertStringKeyStringValue_576) {
    YAML::Node node(YAML::NodeType::Map);
    node.force_insert("key1", "value1");
    
    // Verify the inserted key-value pair exists
    ASSERT_TRUE(node["key1"].IsDefined());
    EXPECT_EQ(node["key1"].as<std::string>(), "value1");
}

// Normal operation: force_insert with integer key and integer value
TEST_F(NodeForceInsertTest_576, ForceInsertIntKeyIntValue_576) {
    YAML::Node node(YAML::NodeType::Map);
    node.force_insert(1, 100);
    
    ASSERT_TRUE(node[1].IsDefined());
    EXPECT_EQ(node[1].as<int>(), 100);
}

// Normal operation: force_insert multiple key-value pairs
TEST_F(NodeForceInsertTest_576, ForceInsertMultiplePairs_576) {
    YAML::Node node(YAML::NodeType::Map);
    node.force_insert("a", 1);
    node.force_insert("b", 2);
    node.force_insert("c", 3);
    
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node["a"].as<int>(), 1);
    EXPECT_EQ(node["b"].as<int>(), 2);
    EXPECT_EQ(node["c"].as<int>(), 3);
}

// force_insert allows duplicate keys (unlike operator[]=)
TEST_F(NodeForceInsertTest_576, ForceInsertDuplicateKeys_576) {
    YAML::Node node(YAML::NodeType::Map);
    node.force_insert("key", "value1");
    node.force_insert("key", "value2");
    
    // force_insert should allow duplicate keys, so size should be 2
    EXPECT_EQ(node.size(), 2u);
}

// force_insert on a default-constructed node (should create the node)
TEST_F(NodeForceInsertTest_576, ForceInsertOnDefaultConstructedNode_576) {
    YAML::Node node;
    node.force_insert("key", "value");
    
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 1u);
}

// force_insert with mixed types for key and value
TEST_F(NodeForceInsertTest_576, ForceInsertMixedTypes_576) {
    YAML::Node node(YAML::NodeType::Map);
    node.force_insert("string_key", 42);
    node.force_insert(99, "string_value");
    
    EXPECT_EQ(node["string_key"].as<int>(), 42);
    EXPECT_EQ(node[99].as<std::string>(), "string_value");
}

// force_insert with Node as key and value
TEST_F(NodeForceInsertTest_576, ForceInsertNodeKeyNodeValue_576) {
    YAML::Node node(YAML::NodeType::Map);
    YAML::Node key("mykey");
    YAML::Node value("myvalue");
    
    node.force_insert(key, value);
    
    EXPECT_EQ(node["mykey"].as<std::string>(), "myvalue");
}

// force_insert with double/float values
TEST_F(NodeForceInsertTest_576, ForceInsertDoubleValue_576) {
    YAML::Node node(YAML::NodeType::Map);
    node.force_insert("pi", 3.14159);
    
    ASSERT_TRUE(node["pi"].IsDefined());
    EXPECT_NEAR(node["pi"].as<double>(), 3.14159, 0.001);
}

// force_insert with boolean values
TEST_F(NodeForceInsertTest_576, ForceInsertBoolValue_576) {
    YAML::Node node(YAML::NodeType::Map);
    node.force_insert("flag", true);
    
    ASSERT_TRUE(node["flag"].IsDefined());
    EXPECT_EQ(node["flag"].as<bool>(), true);
}

// force_insert with empty string key and value
TEST_F(NodeForceInsertTest_576, ForceInsertEmptyStrings_576) {
    YAML::Node node(YAML::NodeType::Map);
    node.force_insert("", "");
    
    EXPECT_EQ(node.size(), 1u);
    EXPECT_EQ(node[""].as<std::string>(), "");
}

// force_insert preserves existing non-duplicate entries
TEST_F(NodeForceInsertTest_576, ForceInsertPreservesExistingEntries_576) {
    YAML::Node node(YAML::NodeType::Map);
    node["existing"] = "original";
    node.force_insert("new_key", "new_value");
    
    EXPECT_EQ(node["existing"].as<std::string>(), "original");
    EXPECT_EQ(node["new_key"].as<std::string>(), "new_value");
}

// Verify the node becomes a Map type after force_insert on Null node
TEST_F(NodeForceInsertTest_576, ForceInsertConvertsNullToMap_576) {
    YAML::Node node(YAML::NodeType::Null);
    node.force_insert("key", "value");
    
    EXPECT_TRUE(node.IsMap());
}

// force_insert with complex Node values (sequence as value)
TEST_F(NodeForceInsertTest_576, ForceInsertSequenceAsValue_576) {
    YAML::Node node(YAML::NodeType::Map);
    YAML::Node seq(YAML::NodeType::Sequence);
    seq.push_back(1);
    seq.push_back(2);
    seq.push_back(3);
    
    node.force_insert("list", seq);
    
    ASSERT_TRUE(node["list"].IsSequence());
    EXPECT_EQ(node["list"].size(), 3u);
    EXPECT_EQ(node["list"][0].as<int>(), 1);
    EXPECT_EQ(node["list"][1].as<int>(), 2);
    EXPECT_EQ(node["list"][2].as<int>(), 3);
}

// force_insert with map as value (nested map)
TEST_F(NodeForceInsertTest_576, ForceInsertNestedMap_576) {
    YAML::Node node(YAML::NodeType::Map);
    YAML::Node inner(YAML::NodeType::Map);
    inner["inner_key"] = "inner_value";
    
    node.force_insert("outer_key", inner);
    
    ASSERT_TRUE(node["outer_key"].IsMap());
    EXPECT_EQ(node["outer_key"]["inner_key"].as<std::string>(), "inner_value");
}

// force_insert with const char* key and value
TEST_F(NodeForceInsertTest_576, ForceInsertConstCharPtr_576) {
    YAML::Node node(YAML::NodeType::Map);
    const char* key = "ckey";
    const char* val = "cval";
    node.force_insert(key, val);
    
    EXPECT_EQ(node["ckey"].as<std::string>(), "cval");
}

// Verify size increases with each force_insert (including duplicates)
TEST_F(NodeForceInsertTest_576, ForceInsertSizeIncreasesWithDuplicates_576) {
    YAML::Node node(YAML::NodeType::Map);
    
    node.force_insert("same", "v1");
    EXPECT_EQ(node.size(), 1u);
    
    node.force_insert("same", "v2");
    EXPECT_EQ(node.size(), 2u);
    
    node.force_insert("same", "v3");
    EXPECT_EQ(node.size(), 3u);
}

// force_insert with large number of entries
TEST_F(NodeForceInsertTest_576, ForceInsertManyEntries_576) {
    YAML::Node node(YAML::NodeType::Map);
    const int count = 100;
    
    for (int i = 0; i < count; i++) {
        node.force_insert(std::to_string(i), i);
    }
    
    EXPECT_EQ(node.size(), static_cast<std::size_t>(count));
    
    // Spot check a few entries
    EXPECT_EQ(node["0"].as<int>(), 0);
    EXPECT_EQ(node["50"].as<int>(), 50);
    EXPECT_EQ(node["99"].as<int>(), 99);
}

// Verify iteration works after force_insert
TEST_F(NodeForceInsertTest_576, ForceInsertIterableAfterInsert_576) {
    YAML::Node node(YAML::NodeType::Map);
    node.force_insert("a", 1);
    node.force_insert("b", 2);
    
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 2);
}

// force_insert with negative integer keys
TEST_F(NodeForceInsertTest_576, ForceInsertNegativeIntKey_576) {
    YAML::Node node(YAML::NodeType::Map);
    node.force_insert(-1, "negative");
    
    EXPECT_EQ(node[-1].as<std::string>(), "negative");
}
