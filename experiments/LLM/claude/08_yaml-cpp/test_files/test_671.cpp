#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/detail/node_data.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"
#include "yaml-cpp/exceptions.h"

namespace YAML {
namespace detail {

class NodeDataForceInsertTest_671 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = std::make_shared<memory_holder>();
  }

  shared_memory_holder pMemory;
};

// Test force_insert on a Map type node - should succeed without conversion
TEST_F(NodeDataForceInsertTest_671, ForceInsertOnMapType_671) {
  node_data data;
  data.set_type(NodeType::Map);
  data.mark_defined();

  EXPECT_NO_THROW(data.force_insert("key1", "value1", pMemory));
  EXPECT_EQ(data.type(), NodeType::Map);
  EXPECT_GE(data.size(), 1u);
}

// Test force_insert on Undefined type - should convert to map
TEST_F(NodeDataForceInsertTest_671, ForceInsertOnUndefinedType_671) {
  node_data data;
  // Default type is Null, set to Undefined explicitly if possible
  // node_data starts as Null by default
  // We test Null case instead since Undefined may not be easily settable
  
  // Let's test Null type
  node_data data2;
  data2.set_type(NodeType::Null);
  
  EXPECT_NO_THROW(data2.force_insert("key", "value", pMemory));
  EXPECT_EQ(data2.type(), NodeType::Map);
}

// Test force_insert on Null type - should convert to map
TEST_F(NodeDataForceInsertTest_671, ForceInsertOnNullType_671) {
  node_data data;
  data.set_type(NodeType::Null);
  
  EXPECT_NO_THROW(data.force_insert("key", "value", pMemory));
  EXPECT_EQ(data.type(), NodeType::Map);
  EXPECT_GE(data.size(), 1u);
}

// Test force_insert on Sequence type - should convert to map
TEST_F(NodeDataForceInsertTest_671, ForceInsertOnSequenceType_671) {
  node_data data;
  data.set_type(NodeType::Sequence);
  data.mark_defined();
  
  EXPECT_NO_THROW(data.force_insert("key", "value", pMemory));
  EXPECT_EQ(data.type(), NodeType::Map);
}

// Test force_insert on Scalar type - should throw BadInsert
TEST_F(NodeDataForceInsertTest_671, ForceInsertOnScalarTypeThrowsBadInsert_671) {
  node_data data;
  data.set_type(NodeType::Scalar);
  data.set_scalar("some_scalar");
  data.mark_defined();
  
  EXPECT_THROW(data.force_insert("key", "value", pMemory), BadInsert);
}

// Test force_insert with integer keys and values
TEST_F(NodeDataForceInsertTest_671, ForceInsertWithIntegerKeyValue_671) {
  node_data data;
  data.set_type(NodeType::Map);
  data.mark_defined();
  
  EXPECT_NO_THROW(data.force_insert(1, 100, pMemory));
  EXPECT_GE(data.size(), 1u);
}

// Test force_insert multiple entries
TEST_F(NodeDataForceInsertTest_671, ForceInsertMultipleEntries_671) {
  node_data data;
  data.set_type(NodeType::Map);
  data.mark_defined();
  
  EXPECT_NO_THROW(data.force_insert("key1", "value1", pMemory));
  EXPECT_NO_THROW(data.force_insert("key2", "value2", pMemory));
  EXPECT_NO_THROW(data.force_insert("key3", "value3", pMemory));
  
  EXPECT_GE(data.size(), 3u);
}

// Test force_insert with duplicate keys - force_insert should allow duplicates
TEST_F(NodeDataForceInsertTest_671, ForceInsertDuplicateKeys_671) {
  node_data data;
  data.set_type(NodeType::Map);
  data.mark_defined();
  
  EXPECT_NO_THROW(data.force_insert("key", "value1", pMemory));
  EXPECT_NO_THROW(data.force_insert("key", "value2", pMemory));
  
  // force_insert should insert both, so size should be at least 2
  EXPECT_GE(data.size(), 2u);
}

// Test force_insert with empty string key and value
TEST_F(NodeDataForceInsertTest_671, ForceInsertEmptyStringKeyValue_671) {
  node_data data;
  data.set_type(NodeType::Map);
  data.mark_defined();
  
  EXPECT_NO_THROW(data.force_insert("", "", pMemory));
  EXPECT_GE(data.size(), 1u);
}

// Test force_insert on sequence with existing elements converts to map
TEST_F(NodeDataForceInsertTest_671, ForceInsertOnSequenceWithElementsConvertsToMap_671) {
  node_data data;
  data.set_type(NodeType::Sequence);
  data.mark_defined();
  
  // Add an element to the sequence first
  node& n = pMemory->create_node();
  n.set_data(std::string("seq_elem"));
  data.push_back(n, pMemory);
  
  EXPECT_EQ(data.type(), NodeType::Sequence);
  EXPECT_EQ(data.size(), 1u);
  
  // force_insert should convert sequence to map
  EXPECT_NO_THROW(data.force_insert("new_key", "new_value", pMemory));
  EXPECT_EQ(data.type(), NodeType::Map);
}

// Test force_insert with mixed types for key and value
TEST_F(NodeDataForceInsertTest_671, ForceInsertMixedTypes_671) {
  node_data data;
  data.set_type(NodeType::Map);
  data.mark_defined();
  
  EXPECT_NO_THROW(data.force_insert(42, "string_value", pMemory));
  EXPECT_NO_THROW(data.force_insert("string_key", 123, pMemory));
  EXPECT_GE(data.size(), 2u);
}

// Test using the higher-level Node API with force_insert behavior
TEST_F(NodeDataForceInsertTest_671, HighLevelNodeForceInsert_671) {
  YAML::Node node(NodeType::Map);
  
  EXPECT_NO_THROW(node.force_insert("a", 1));
  EXPECT_NO_THROW(node.force_insert("b", 2));
  
  EXPECT_TRUE(node.IsMap());
  EXPECT_GE(node.size(), 2u);
}

// Test high-level Node force_insert on scalar throws
TEST_F(NodeDataForceInsertTest_671, HighLevelNodeForceInsertOnScalarThrows_671) {
  YAML::Node node("scalar_value");
  
  EXPECT_THROW(node.force_insert("key", "value"), BadInsert);
}

// Test high-level Node force_insert converts null to map
TEST_F(NodeDataForceInsertTest_671, HighLevelNodeForceInsertOnNullConverts_671) {
  YAML::Node node(NodeType::Null);
  
  EXPECT_NO_THROW(node.force_insert("key", "value"));
  EXPECT_TRUE(node.IsMap());
}

// Test high-level Node force_insert allows duplicate keys
TEST_F(NodeDataForceInsertTest_671, HighLevelNodeForceInsertDuplicateKeys_671) {
  YAML::Node node(NodeType::Map);
  
  node.force_insert("dup", "val1");
  node.force_insert("dup", "val2");
  
  // force_insert should add both entries
  EXPECT_GE(node.size(), 2u);
}

// Test high-level Node force_insert converts sequence to map
TEST_F(NodeDataForceInsertTest_671, HighLevelNodeForceInsertOnSequence_671) {
  YAML::Node node(NodeType::Sequence);
  node.push_back("elem1");
  
  EXPECT_TRUE(node.IsSequence());
  
  node.force_insert("key", "value");
  
  EXPECT_TRUE(node.IsMap());
}

}  // namespace detail
}  // namespace YAML
