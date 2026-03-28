#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/node_data.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeDataInsertTest_650 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = shared_memory_holder(new Memory);
  }

  shared_memory_holder pMemory;
};

// Test: Insert into a Map type should succeed without changing type
TEST_F(NodeDataInsertTest_650, InsertIntoMapType_650) {
  node_data data;
  data.set_type(NodeType::Map);
  data.mark_defined();

  node& key = pMemory->create_node();
  key.set_scalar("key1");
  key.set_type(NodeType::Scalar);

  node& value = pMemory->create_node();
  value.set_scalar("value1");
  value.set_type(NodeType::Scalar);

  EXPECT_NO_THROW(data.insert(key, value, pMemory));
  EXPECT_EQ(NodeType::Map, data.type());
}

// Test: Insert into Undefined type should convert to Map
TEST_F(NodeDataInsertTest_650, InsertIntoUndefinedTypeConvertsToMap_650) {
  node_data data;
  // Default type is Null, set to Undefined explicitly if possible
  // node_data default is Null type

  node& key = pMemory->create_node();
  key.set_scalar("key1");
  key.set_type(NodeType::Scalar);

  node& value = pMemory->create_node();
  value.set_scalar("value1");
  value.set_type(NodeType::Scalar);

  // Default is Null which should convert to map
  EXPECT_NO_THROW(data.insert(key, value, pMemory));
  EXPECT_EQ(NodeType::Map, data.type());
}

// Test: Insert into Null type should convert to Map
TEST_F(NodeDataInsertTest_650, InsertIntoNullTypeConvertsToMap_650) {
  node_data data;
  data.set_type(NodeType::Null);

  node& key = pMemory->create_node();
  key.set_scalar("key1");
  key.set_type(NodeType::Scalar);

  node& value = pMemory->create_node();
  value.set_scalar("value1");
  value.set_type(NodeType::Scalar);

  EXPECT_NO_THROW(data.insert(key, value, pMemory));
  EXPECT_EQ(NodeType::Map, data.type());
}

// Test: Insert into Sequence type should convert to Map
TEST_F(NodeDataInsertTest_650, InsertIntoSequenceTypeConvertsToMap_650) {
  node_data data;
  data.set_type(NodeType::Sequence);

  node& key = pMemory->create_node();
  key.set_scalar("key1");
  key.set_type(NodeType::Scalar);

  node& value = pMemory->create_node();
  value.set_scalar("value1");
  value.set_type(NodeType::Scalar);

  EXPECT_NO_THROW(data.insert(key, value, pMemory));
  EXPECT_EQ(NodeType::Map, data.type());
}

// Test: Insert into Scalar type should throw BadSubscript
TEST_F(NodeDataInsertTest_650, InsertIntoScalarTypeThrows_650) {
  node_data data;
  data.set_type(NodeType::Scalar);
  data.set_scalar("some_scalar");

  node& key = pMemory->create_node();
  key.set_scalar("key1");
  key.set_type(NodeType::Scalar);

  node& value = pMemory->create_node();
  value.set_scalar("value1");
  value.set_type(NodeType::Scalar);

  EXPECT_THROW(data.insert(key, value, pMemory), BadSubscript);
}

// Test: Insert multiple key-value pairs into a map
TEST_F(NodeDataInsertTest_650, InsertMultiplePairsIntoMap_650) {
  node_data data;
  data.set_type(NodeType::Map);
  data.mark_defined();

  node& key1 = pMemory->create_node();
  key1.set_scalar("key1");
  key1.set_type(NodeType::Scalar);

  node& value1 = pMemory->create_node();
  value1.set_scalar("value1");
  value1.set_type(NodeType::Scalar);

  node& key2 = pMemory->create_node();
  key2.set_scalar("key2");
  key2.set_type(NodeType::Scalar);

  node& value2 = pMemory->create_node();
  value2.set_scalar("value2");
  value2.set_type(NodeType::Scalar);

  EXPECT_NO_THROW(data.insert(key1, value1, pMemory));
  EXPECT_NO_THROW(data.insert(key2, value2, pMemory));
  EXPECT_EQ(NodeType::Map, data.type());
}

// Test: Insert into sequence with existing elements converts to map
TEST_F(NodeDataInsertTest_650, InsertIntoSequenceWithElementsConvertsToMap_650) {
  node_data data;
  data.set_type(NodeType::Sequence);

  node& seqItem = pMemory->create_node();
  seqItem.set_scalar("item1");
  seqItem.set_type(NodeType::Scalar);
  data.push_back(seqItem, pMemory);

  node& key = pMemory->create_node();
  key.set_scalar("key1");
  key.set_type(NodeType::Scalar);

  node& value = pMemory->create_node();
  value.set_scalar("value1");
  value.set_type(NodeType::Scalar);

  EXPECT_NO_THROW(data.insert(key, value, pMemory));
  EXPECT_EQ(NodeType::Map, data.type());
}

// Test: Verify size increases after insert into map
TEST_F(NodeDataInsertTest_650, InsertIncreasesMapSize_650) {
  node_data data;
  data.set_type(NodeType::Map);
  data.mark_defined();

  std::size_t initialSize = data.size();

  node& key = pMemory->create_node();
  key.set_scalar("key1");
  key.set_type(NodeType::Scalar);

  node& value = pMemory->create_node();
  value.set_scalar("value1");
  value.set_type(NodeType::Scalar);

  data.insert(key, value, pMemory);

  EXPECT_GE(data.size(), initialSize);
}

// Test: Insert after converting from Null should allow retrieval
TEST_F(NodeDataInsertTest_650, InsertAfterNullConversionAllowsGet_650) {
  node_data data;
  data.set_type(NodeType::Null);

  node& key = pMemory->create_node();
  key.set_scalar("mykey");
  key.set_type(NodeType::Scalar);

  node& value = pMemory->create_node();
  value.set_scalar("myvalue");
  value.set_type(NodeType::Scalar);

  data.insert(key, value, pMemory);

  // Try to get the value using the key
  const node* result = data.get(key, pMemory);
  EXPECT_NE(nullptr, result);
}

// Test: Insert with same key twice
TEST_F(NodeDataInsertTest_650, InsertSameKeyTwice_650) {
  node_data data;
  data.set_type(NodeType::Map);
  data.mark_defined();

  node& key = pMemory->create_node();
  key.set_scalar("duplicate_key");
  key.set_type(NodeType::Scalar);

  node& value1 = pMemory->create_node();
  value1.set_scalar("value1");
  value1.set_type(NodeType::Scalar);

  node& value2 = pMemory->create_node();
  value2.set_scalar("value2");
  value2.set_type(NodeType::Scalar);

  EXPECT_NO_THROW(data.insert(key, value1, pMemory));
  EXPECT_NO_THROW(data.insert(key, value2, pMemory));
}

// Test: High-level Node API insert test
TEST_F(NodeDataInsertTest_650, HighLevelNodeInsert_650) {
  YAML::Node map;
  map["key1"] = "value1";
  map["key2"] = "value2";

  EXPECT_TRUE(map.IsMap());
  EXPECT_EQ("value1", map["key1"].as<std::string>());
  EXPECT_EQ("value2", map["key2"].as<std::string>());
}

// Test: High-level Node force_insert
TEST_F(NodeDataInsertTest_650, HighLevelNodeForceInsert_650) {
  YAML::Node map;
  map.force_insert("key1", "value1");

  EXPECT_TRUE(map.IsMap());
  EXPECT_EQ(1u, map.size());
}

// Test: High-level inserting into scalar throws
TEST_F(NodeDataInsertTest_650, HighLevelScalarInsertThrows_650) {
  YAML::Node scalar("hello");
  EXPECT_TRUE(scalar.IsScalar());
  EXPECT_THROW(scalar.force_insert("key", "value"), BadSubscript);
}

// Test: set_type and basic accessors
TEST_F(NodeDataInsertTest_650, SetTypeAndAccessors_650) {
  node_data data;
  EXPECT_EQ(NodeType::Null, data.type());

  data.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, data.type());

  data.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, data.type());

  data.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, data.type());
}

// Test: mark_defined
TEST_F(NodeDataInsertTest_650, MarkDefined_650) {
  node_data data;
  EXPECT_FALSE(data.is_defined());
  data.mark_defined();
  EXPECT_TRUE(data.is_defined());
}

// Test: set_scalar and scalar()
TEST_F(NodeDataInsertTest_650, SetScalarAndRetrieve_650) {
  node_data data;
  data.set_type(NodeType::Scalar);
  data.set_scalar("test_value");
  EXPECT_EQ("test_value", data.scalar());
}

// Test: set_tag and tag()
TEST_F(NodeDataInsertTest_650, SetTagAndRetrieve_650) {
  node_data data;
  data.set_tag("!custom_tag");
  EXPECT_EQ("!custom_tag", data.tag());
}

// Test: empty_scalar returns empty string
TEST_F(NodeDataInsertTest_650, EmptyScalarReturnsEmpty_650) {
  const std::string& empty = node_data::empty_scalar();
  EXPECT_TRUE(empty.empty());
}

// Test: set_null resets type to Null
TEST_F(NodeDataInsertTest_650, SetNull_650) {
  node_data data;
  data.set_type(NodeType::Scalar);
  data.set_scalar("something");
  data.set_null();
  EXPECT_EQ(NodeType::Null, data.type());
}

// Test: push_back into sequence
TEST_F(NodeDataInsertTest_650, PushBackIntoSequence_650) {
  node_data data;
  data.set_type(NodeType::Sequence);
  data.mark_defined();

  node& item = pMemory->create_node();
  item.set_scalar("item1");
  item.set_type(NodeType::Scalar);

  EXPECT_NO_THROW(data.push_back(item, pMemory));
  EXPECT_GE(data.size(), 1u);
}

// Test: size of empty map
TEST_F(NodeDataInsertTest_650, SizeOfEmptyMap_650) {
  node_data data;
  data.set_type(NodeType::Map);
  EXPECT_EQ(0u, data.size());
}

// Test: size of empty sequence
TEST_F(NodeDataInsertTest_650, SizeOfEmptySequence_650) {
  node_data data;
  data.set_type(NodeType::Sequence);
  EXPECT_EQ(0u, data.size());
}

// Test: set_style and style
TEST_F(NodeDataInsertTest_650, SetStyleAndRetrieve_650) {
  node_data data;
  data.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, data.style());

  data.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, data.style());
}

// Test: set_mark and mark
TEST_F(NodeDataInsertTest_650, SetMarkAndRetrieve_650) {
  node_data data;
  Mark m;
  m.line = 10;
  m.column = 20;
  m.pos = 30;
  data.set_mark(m);
  EXPECT_EQ(10, data.mark().line);
  EXPECT_EQ(20, data.mark().column);
  EXPECT_EQ(30u, data.mark().pos);
}

// Test: remove from map
TEST_F(NodeDataInsertTest_650, RemoveFromMap_650) {
  node_data data;
  data.set_type(NodeType::Map);
  data.mark_defined();

  node& key = pMemory->create_node();
  key.set_scalar("key_to_remove");
  key.set_type(NodeType::Scalar);

  node& value = pMemory->create_node();
  value.set_scalar("value");
  value.set_type(NodeType::Scalar);

  data.insert(key, value, pMemory);
  bool removed = data.remove(key, pMemory);
  EXPECT_TRUE(removed);
}

// Test: remove non-existent key from map
TEST_F(NodeDataInsertTest_650, RemoveNonExistentKeyFromMap_650) {
  node_data data;
  data.set_type(NodeType::Map);
  data.mark_defined();

  node& key = pMemory->create_node();
  key.set_scalar("non_existent_key");
  key.set_type(NodeType::Scalar);

  bool removed = data.remove(key, pMemory);
  EXPECT_FALSE(removed);
}

// Test: begin and end iterators for empty map
TEST_F(NodeDataInsertTest_650, BeginEndForEmptyMap_650) {
  node_data data;
  data.set_type(NodeType::Map);
  EXPECT_EQ(data.begin(), data.end());
}

// Test: begin and end iterators for empty sequence
TEST_F(NodeDataInsertTest_650, BeginEndForEmptySequence_650) {
  node_data data;
  data.set_type(NodeType::Sequence);
  EXPECT_EQ(data.begin(), data.end());
}

}  // namespace detail
}  // namespace YAML
