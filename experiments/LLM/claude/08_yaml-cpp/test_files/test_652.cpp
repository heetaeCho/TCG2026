#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node_data.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeDataTest_652 : public ::testing::Test {
 protected:
  void SetUp() override {
    memory_holder_.reset(new memory_holder);
    pMemory_ = memory_holder_->m_pMemory;
  }

  // We'll use the public YAML::Node API since node_data is internal
  // and difficult to instantiate directly. We test through the Node interface.
  std::shared_ptr<memory_holder> memory_holder_;
  shared_memory_holder pMemory_;
};

// Since node_data is an internal class that's hard to test directly,
// we test through the YAML::Node public API which exercises node_data internally.

class NodeDataViaNodeTest_652 : public ::testing::Test {
 protected:
  void SetUp() override {}
};

// Test: Default node is Null type
TEST_F(NodeDataViaNodeTest_652, DefaultNodeIsNull_652) {
  YAML::Node node;
  EXPECT_TRUE(node.IsNull());
}

// Test: Setting a node to a map and accessing by key
TEST_F(NodeDataViaNodeTest_652, MapSubscriptCreatesEntry_652) {
  YAML::Node node;
  node["key"] = "value";
  EXPECT_TRUE(node.IsMap());
  EXPECT_EQ(node["key"].as<std::string>(), "value");
}

// Test: Accessing a key on a Null node converts it to a map
TEST_F(NodeDataViaNodeTest_652, NullNodeConvertsToMapOnSubscript_652) {
  YAML::Node node;
  EXPECT_TRUE(node.IsNull());
  node["key"] = "value";
  EXPECT_TRUE(node.IsMap());
}

// Test: Accessing a key on an Undefined node converts it to map
TEST_F(NodeDataViaNodeTest_652, UndefinedNodeConvertsToMapOnSubscript_652) {
  YAML::Node node;
  YAML::Node child = node["nonexistent"];
  // Accessing a child that doesn't exist creates it
  child["subkey"] = "subvalue";
  EXPECT_EQ(child["subkey"].as<std::string>(), "subvalue");
}

// Test: Subscript on a Scalar node throws BadSubscript
TEST_F(NodeDataViaNodeTest_652, ScalarNodeThrowsOnSubscript_652) {
  YAML::Node node = YAML::Node("scalar_value");
  EXPECT_TRUE(node.IsScalar());
  EXPECT_THROW(node["key"], YAML::BadSubscript);
}

// Test: Sequence node converts to map on subscript access
TEST_F(NodeDataViaNodeTest_652, SequenceConvertsToMapOnSubscript_652) {
  YAML::Node node;
  node.push_back("item1");
  node.push_back("item2");
  EXPECT_TRUE(node.IsSequence());
  
  // Accessing by string key should convert sequence to map
  node["key"] = "value";
  EXPECT_TRUE(node.IsMap());
}

// Test: Map get returns same node for existing key
TEST_F(NodeDataViaNodeTest_652, MapGetReturnsSameNodeForExistingKey_652) {
  YAML::Node node;
  node["key"] = "value1";
  node["key"] = "value2";
  EXPECT_EQ(node["key"].as<std::string>(), "value2");
  EXPECT_EQ(node.size(), 1u);
}

// Test: Map get creates new entry for new key
TEST_F(NodeDataViaNodeTest_652, MapGetCreatesNewEntryForNewKey_652) {
  YAML::Node node;
  node["key1"] = "value1";
  node["key2"] = "value2";
  EXPECT_EQ(node.size(), 2u);
  EXPECT_EQ(node["key1"].as<std::string>(), "value1");
  EXPECT_EQ(node["key2"].as<std::string>(), "value2");
}

// Test: Multiple keys in map
TEST_F(NodeDataViaNodeTest_652, MultipleKeysInMap_652) {
  YAML::Node node;
  node["a"] = 1;
  node["b"] = 2;
  node["c"] = 3;
  EXPECT_EQ(node.size(), 3u);
  EXPECT_EQ(node["a"].as<int>(), 1);
  EXPECT_EQ(node["b"].as<int>(), 2);
  EXPECT_EQ(node["c"].as<int>(), 3);
}

// Test: set_type to Map then subscript works
TEST_F(NodeDataViaNodeTest_652, ExplicitMapTypeSubscriptWorks_652) {
  YAML::Node node(YAML::NodeType::Map);
  EXPECT_TRUE(node.IsMap());
  node["key"] = "value";
  EXPECT_EQ(node["key"].as<std::string>(), "value");
}

// Test: Empty map has size 0
TEST_F(NodeDataViaNodeTest_652, EmptyMapSizeIsZero_652) {
  YAML::Node node(YAML::NodeType::Map);
  EXPECT_EQ(node.size(), 0u);
}

// Test: Const subscript on scalar throws
TEST_F(NodeDataViaNodeTest_652, ConstScalarSubscriptThrows_652) {
  const YAML::Node node = YAML::Node("scalar");
  EXPECT_THROW(node["key"], YAML::BadSubscript);
}

// Test: node_data set_type and type
TEST_F(NodeDataViaNodeTest_652, SetTypeAndGetType_652) {
  YAML::Node node;
  node = YAML::Node(YAML::NodeType::Sequence);
  EXPECT_TRUE(node.IsSequence());
}

// Test: node_data set_scalar and scalar
TEST_F(NodeDataViaNodeTest_652, SetScalarAndGetScalar_652) {
  YAML::Node node = YAML::Node("hello");
  EXPECT_EQ(node.Scalar(), "hello");
}

// Test: node_data set_tag and tag
TEST_F(NodeDataViaNodeTest_652, SetTagAndGetTag_652) {
  YAML::Node node;
  node.SetTag("!custom");
  EXPECT_EQ(node.Tag(), "!custom");
}

// Test: node_data set_style and style
TEST_F(NodeDataViaNodeTest_652, SetStyleAndGetStyle_652) {
  YAML::Node node;
  node.SetStyle(YAML::EmitterStyle::Flow);
  EXPECT_EQ(node.Style(), YAML::EmitterStyle::Flow);
}

// Test: push_back to create sequence
TEST_F(NodeDataViaNodeTest_652, PushBackCreatesSequence_652) {
  YAML::Node node;
  node.push_back(1);
  node.push_back(2);
  node.push_back(3);
  EXPECT_TRUE(node.IsSequence());
  EXPECT_EQ(node.size(), 3u);
  EXPECT_EQ(node[0].as<int>(), 1);
  EXPECT_EQ(node[1].as<int>(), 2);
  EXPECT_EQ(node[2].as<int>(), 3);
}

// Test: remove key from map
TEST_F(NodeDataViaNodeTest_652, RemoveKeyFromMap_652) {
  YAML::Node node;
  node["key1"] = "value1";
  node["key2"] = "value2";
  EXPECT_EQ(node.size(), 2u);
  
  bool removed = node.remove("key1");
  EXPECT_TRUE(removed);
  EXPECT_EQ(node.size(), 1u);
}

// Test: remove non-existent key returns false
TEST_F(NodeDataViaNodeTest_652, RemoveNonExistentKeyReturnsFalse_652) {
  YAML::Node node;
  node["key1"] = "value1";
  
  bool removed = node.remove("nonexistent");
  EXPECT_FALSE(removed);
  EXPECT_EQ(node.size(), 1u);
}

// Test: Map iteration
TEST_F(NodeDataViaNodeTest_652, MapIteration_652) {
  YAML::Node node;
  node["a"] = 1;
  node["b"] = 2;
  
  int count = 0;
  for (auto it = node.begin(); it != node.end(); ++it) {
    count++;
  }
  EXPECT_EQ(count, 2);
}

// Test: Sequence iteration
TEST_F(NodeDataViaNodeTest_652, SequenceIteration_652) {
  YAML::Node node;
  node.push_back(10);
  node.push_back(20);
  node.push_back(30);
  
  int count = 0;
  for (auto it = node.begin(); it != node.end(); ++it) {
    count++;
  }
  EXPECT_EQ(count, 3);
}

// Test: is_defined
TEST_F(NodeDataViaNodeTest_652, IsDefinedAfterAssignment_652) {
  YAML::Node node;
  node = "hello";
  EXPECT_TRUE(node.IsDefined());
}

// Test: set_null
TEST_F(NodeDataViaNodeTest_652, SetNull_652) {
  YAML::Node node = YAML::Node("value");
  EXPECT_TRUE(node.IsScalar());
  node = YAML::Node();
  EXPECT_TRUE(node.IsNull());
}

// Test: empty_scalar
TEST_F(NodeDataViaNodeTest_652, EmptyScalarNode_652) {
  YAML::Node node = YAML::Node("");
  EXPECT_TRUE(node.IsScalar());
  EXPECT_EQ(node.Scalar(), "");
}

// Test: force_insert on map
TEST_F(NodeDataViaNodeTest_652, ForceInsertOnMap_652) {
  YAML::Node node;
  node.force_insert("key1", "value1");
  node.force_insert("key2", "value2");
  EXPECT_TRUE(node.IsMap());
  EXPECT_EQ(node.size(), 2u);
}

// Test: Sequence to map conversion preserves indices as keys
TEST_F(NodeDataViaNodeTest_652, SequenceToMapConversion_652) {
  YAML::Node node;
  node.push_back("first");
  node.push_back("second");
  EXPECT_TRUE(node.IsSequence());
  EXPECT_EQ(node.size(), 2u);
  
  // Subscript with string key converts to map
  node["string_key"] = "string_value";
  EXPECT_TRUE(node.IsMap());
}

// Test: Integer key subscript on map
TEST_F(NodeDataViaNodeTest_652, IntegerKeySubscript_652) {
  YAML::Node node;
  node[1] = "one";
  node[2] = "two";
  EXPECT_TRUE(node.IsMap());
  EXPECT_EQ(node[1].as<std::string>(), "one");
  EXPECT_EQ(node[2].as<std::string>(), "two");
}

// Test: Nested map access
TEST_F(NodeDataViaNodeTest_652, NestedMapAccess_652) {
  YAML::Node node;
  node["level1"]["level2"] = "deep_value";
  EXPECT_TRUE(node.IsMap());
  EXPECT_TRUE(node["level1"].IsMap());
  EXPECT_EQ(node["level1"]["level2"].as<std::string>(), "deep_value");
}

// Test: Mark
TEST_F(NodeDataViaNodeTest_652, MarkIsNullByDefault_652) {
  YAML::Node node;
  EXPECT_EQ(node.Mark().line, -1);
  EXPECT_EQ(node.Mark().column, -1);
}

}  // namespace detail
}  // namespace YAML
