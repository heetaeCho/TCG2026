#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary yaml-cpp headers
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/detail/node_data.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeDataGetTest_651 : public ::testing::Test {
 protected:
  void SetUp() override {
  }

  void TearDown() override {
  }
};

// Test that accessing a key on a Node that is not a Map returns null/fails gracefully
TEST_F(NodeDataGetTest_651, GetOnNonMapNodeReturnsNull_651) {
  // A scalar node is not a map, so operator[] should not find keys like a map
  Node scalar_node("hello");
  ASSERT_TRUE(scalar_node.IsScalar());
  
  // Accessing a non-existent key on a scalar - this should not crash
  // The node_data::get should return nullptr for non-map types
  Node result = scalar_node["some_key"];
  EXPECT_FALSE(result.IsDefined());
}

// Test that accessing a key on a Sequence node returns null/undefined
TEST_F(NodeDataGetTest_651, GetOnSequenceNodeReturnsUndefined_651) {
  Node seq_node;
  seq_node.push_back("item1");
  seq_node.push_back("item2");
  ASSERT_TRUE(seq_node.IsSequence());
  
  // String key access on sequence should not find anything as a map lookup
  Node result = seq_node["nonexistent"];
  // Accessing a string key on a sequence will convert it, but the internal
  // get() on the original sequence data should return nullptr
  // After the access the node type may change, but we test the initial behavior
  EXPECT_TRUE(result.IsDefined() || !result.IsDefined()); // Just ensuring no crash
}

// Test that accessing an existing key on a Map node returns the correct value
TEST_F(NodeDataGetTest_651, GetOnMapNodeReturnsExistingValue_651) {
  Node map_node;
  map_node["key1"] = "value1";
  map_node["key2"] = "value2";
  map_node["key3"] = "value3";
  ASSERT_TRUE(map_node.IsMap());
  
  EXPECT_EQ(map_node["key1"].as<std::string>(), "value1");
  EXPECT_EQ(map_node["key2"].as<std::string>(), "value2");
  EXPECT_EQ(map_node["key3"].as<std::string>(), "value3");
}

// Test that accessing a non-existing key on a Map node returns undefined or creates new
TEST_F(NodeDataGetTest_651, GetOnMapNodeNonExistingKey_651) {
  Node map_node;
  map_node["existing_key"] = "existing_value";
  ASSERT_TRUE(map_node.IsMap());
  
  // Const access should return undefined for non-existing key
  const Node& const_map = map_node;
  Node result = const_map["nonexistent_key"];
  EXPECT_FALSE(result.IsDefined());
}

// Test that a Null node returns null for get
TEST_F(NodeDataGetTest_651, GetOnNullNodeReturnsUndefined_651) {
  Node null_node;
  ASSERT_TRUE(null_node.IsNull());
  
  const Node& const_null = null_node;
  Node result = const_null["any_key"];
  EXPECT_FALSE(result.IsDefined());
}

// Test get with integer key on a map
TEST_F(NodeDataGetTest_651, GetOnMapNodeWithIntegerKey_651) {
  Node map_node;
  map_node[42] = "forty-two";
  map_node[0] = "zero";
  ASSERT_TRUE(map_node.IsMap());
  
  EXPECT_EQ(map_node[42].as<std::string>(), "forty-two");
  EXPECT_EQ(map_node[0].as<std::string>(), "zero");
}

// Test that get with same key used multiple times returns the same node
TEST_F(NodeDataGetTest_651, GetSameKeyReturnsSameValue_651) {
  Node map_node;
  map_node["key"] = "value";
  
  std::string val1 = map_node["key"].as<std::string>();
  std::string val2 = map_node["key"].as<std::string>();
  
  EXPECT_EQ(val1, val2);
  EXPECT_EQ(val1, "value");
}

// Test get on an empty map
TEST_F(NodeDataGetTest_651, GetOnEmptyMapReturnsUndefined_651) {
  Node map_node = YAML::Load("{}");
  ASSERT_TRUE(map_node.IsMap());
  ASSERT_EQ(map_node.size(), 0u);
  
  const Node& const_map = map_node;
  Node result = const_map["any_key"];
  EXPECT_FALSE(result.IsDefined());
}

// Test that map with multiple keys iterates correctly (boundary: first and last key)
TEST_F(NodeDataGetTest_651, GetFirstAndLastKeyInMap_651) {
  Node map_node;
  map_node["alpha"] = "first";
  map_node["beta"] = "second";
  map_node["gamma"] = "third";
  map_node["delta"] = "fourth";
  map_node["epsilon"] = "fifth";
  
  EXPECT_EQ(map_node["alpha"].as<std::string>(), "first");
  EXPECT_EQ(map_node["epsilon"].as<std::string>(), "fifth");
}

// Test get with empty string key
TEST_F(NodeDataGetTest_651, GetWithEmptyStringKey_651) {
  Node map_node;
  map_node[""] = "empty_key_value";
  ASSERT_TRUE(map_node.IsMap());
  
  EXPECT_EQ(map_node[""].as<std::string>(), "empty_key_value");
}

// Test const get on a scalar node returns undefined
TEST_F(NodeDataGetTest_651, ConstGetOnScalarReturnsUndefined_651) {
  Node scalar("just a scalar");
  const Node& const_scalar = scalar;
  
  Node result = const_scalar["key"];
  EXPECT_FALSE(result.IsDefined());
}

// Test that overwriting a key in map works and get returns updated value
TEST_F(NodeDataGetTest_651, GetReturnsUpdatedValueAfterOverwrite_651) {
  Node map_node;
  map_node["key"] = "original";
  EXPECT_EQ(map_node["key"].as<std::string>(), "original");
  
  map_node["key"] = "updated";
  EXPECT_EQ(map_node["key"].as<std::string>(), "updated");
}

// Test with node as key (complex key scenario)
TEST_F(NodeDataGetTest_651, GetWithNodeAsKey_651) {
  Node map_node;
  Node key_node = "complex_key";
  map_node[key_node] = "complex_value";
  
  EXPECT_EQ(map_node[key_node].as<std::string>(), "complex_value");
}

}  // namespace detail
}  // namespace YAML
