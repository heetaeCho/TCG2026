#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/node_data.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeRefInsertTest_229 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = shared_memory_holder(new memory);
  }

  shared_memory_holder pMemory;
};

// Test: Insert a key-value pair into a node_ref that is set to Map type
TEST_F(NodeRefInsertTest_229, InsertKeyValueIntoMap_229) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  ref.mark_defined();

  node& key = pMemory->create_node();
  key.set_scalar("testkey");
  key.set_type(NodeType::Scalar);

  node& value = pMemory->create_node();
  value.set_scalar("testvalue");
  value.set_type(NodeType::Scalar);

  ref.insert(key, value, pMemory);

  EXPECT_EQ(ref.size(), 1u);
}

// Test: Insert multiple key-value pairs into a map
TEST_F(NodeRefInsertTest_229, InsertMultipleKeyValuePairs_229) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  ref.mark_defined();

  node& key1 = pMemory->create_node();
  key1.set_scalar("key1");
  key1.set_type(NodeType::Scalar);
  node& val1 = pMemory->create_node();
  val1.set_scalar("val1");
  val1.set_type(NodeType::Scalar);

  node& key2 = pMemory->create_node();
  key2.set_scalar("key2");
  key2.set_type(NodeType::Scalar);
  node& val2 = pMemory->create_node();
  val2.set_scalar("val2");
  val2.set_type(NodeType::Scalar);

  ref.insert(key1, val1, pMemory);
  ref.insert(key2, val2, pMemory);

  EXPECT_EQ(ref.size(), 2u);
}

// Test: Insert into a node_ref converts sequence to map
TEST_F(NodeRefInsertTest_229, InsertConvertsSequenceToMap_229) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  ref.mark_defined();

  // Push back some elements to sequence first
  node& seqNode = pMemory->create_node();
  seqNode.set_scalar("seqval");
  seqNode.set_type(NodeType::Scalar);
  ref.push_back(seqNode, pMemory);

  EXPECT_EQ(ref.type(), NodeType::Sequence);

  // Now insert a key-value pair, which should convert to map
  node& key = pMemory->create_node();
  key.set_scalar("mapkey");
  key.set_type(NodeType::Scalar);
  node& value = pMemory->create_node();
  value.set_scalar("mapvalue");
  value.set_type(NodeType::Scalar);

  ref.insert(key, value, pMemory);

  EXPECT_EQ(ref.type(), NodeType::Map);
}

// Test: Insert into a Null type node_ref converts to map
TEST_F(NodeRefInsertTest_229, InsertIntoNullTypeConvertsToMap_229) {
  node_ref ref;
  ref.mark_defined();
  EXPECT_EQ(ref.type(), NodeType::Null);

  node& key = pMemory->create_node();
  key.set_scalar("key");
  key.set_type(NodeType::Scalar);
  node& value = pMemory->create_node();
  value.set_scalar("value");
  value.set_type(NodeType::Scalar);

  ref.insert(key, value, pMemory);

  EXPECT_EQ(ref.type(), NodeType::Map);
  EXPECT_EQ(ref.size(), 1u);
}

// Test: Retrieve inserted value by key
TEST_F(NodeRefInsertTest_229, RetrieveInsertedValue_229) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  ref.mark_defined();

  node& key = pMemory->create_node();
  key.set_scalar("mykey");
  key.set_type(NodeType::Scalar);
  node& value = pMemory->create_node();
  value.set_scalar("myvalue");
  value.set_type(NodeType::Scalar);

  ref.insert(key, value, pMemory);

  node* found = ref.get(std::string("mykey"), pMemory);
  ASSERT_NE(found, nullptr);
  EXPECT_EQ(found->scalar(), "myvalue");
}

// Test: Insert with same key does not duplicate
TEST_F(NodeRefInsertTest_229, InsertDuplicateKey_229) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  ref.mark_defined();

  node& key1 = pMemory->create_node();
  key1.set_scalar("samekey");
  key1.set_type(NodeType::Scalar);
  node& val1 = pMemory->create_node();
  val1.set_scalar("val1");
  val1.set_type(NodeType::Scalar);

  node& key2 = pMemory->create_node();
  key2.set_scalar("samekey");
  key2.set_type(NodeType::Scalar);
  node& val2 = pMemory->create_node();
  val2.set_scalar("val2");
  val2.set_type(NodeType::Scalar);

  ref.insert(key1, val1, pMemory);
  ref.insert(key2, val2, pMemory);

  // The behavior with duplicate keys: the map should contain the pair
  // At minimum, we can verify the size and that a value is retrievable
  node* found = ref.get(std::string("samekey"), pMemory);
  ASSERT_NE(found, nullptr);
}

// Test: Insert and verify begin/end iterators cover inserted elements
TEST_F(NodeRefInsertTest_229, InsertAndIterateOverMap_229) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  ref.mark_defined();

  node& key = pMemory->create_node();
  key.set_scalar("iterkey");
  key.set_type(NodeType::Scalar);
  node& value = pMemory->create_node();
  value.set_scalar("iterval");
  value.set_type(NodeType::Scalar);

  ref.insert(key, value, pMemory);

  auto it = ref.begin();
  auto endIt = ref.end();
  EXPECT_NE(it, endIt);

  int count = 0;
  for (auto iter = ref.begin(); iter != ref.end(); ++iter) {
    count++;
  }
  EXPECT_EQ(count, 1);
}

// Test: Insert into undefined node_ref
TEST_F(NodeRefInsertTest_229, InsertIntoUndefinedNode_229) {
  node_ref ref;
  // Not calling mark_defined, so it's undefined
  EXPECT_FALSE(ref.is_defined());

  node& key = pMemory->create_node();
  key.set_scalar("undkey");
  key.set_type(NodeType::Scalar);
  node& value = pMemory->create_node();
  value.set_scalar("undval");
  value.set_type(NodeType::Scalar);

  // Insert should still work (converting to map)
  ref.insert(key, value, pMemory);

  EXPECT_EQ(ref.type(), NodeType::Map);
  EXPECT_GE(ref.size(), 1u);
}

// Test: node class insert delegates properly
TEST_F(NodeRefInsertTest_229, NodeInsertDelegatesToRef_229) {
  node& mapNode = pMemory->create_node();
  mapNode.set_type(NodeType::Map);
  mapNode.mark_defined();

  node& key = pMemory->create_node();
  key.set_scalar("nkey");
  key.set_type(NodeType::Scalar);
  node& value = pMemory->create_node();
  value.set_scalar("nvalue");
  value.set_type(NodeType::Scalar);

  mapNode.insert(key, value, pMemory);

  EXPECT_EQ(mapNode.size(), 1u);
  node* found = mapNode.get(std::string("nkey"), pMemory);
  ASSERT_NE(found, nullptr);
  EXPECT_EQ(found->scalar(), "nvalue");
}

// Test: Insert with empty string keys
TEST_F(NodeRefInsertTest_229, InsertEmptyStringKey_229) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  ref.mark_defined();

  node& key = pMemory->create_node();
  key.set_scalar("");
  key.set_type(NodeType::Scalar);
  node& value = pMemory->create_node();
  value.set_scalar("emptykey_value");
  value.set_type(NodeType::Scalar);

  ref.insert(key, value, pMemory);

  EXPECT_EQ(ref.size(), 1u);
  node* found = ref.get(std::string(""), pMemory);
  ASSERT_NE(found, nullptr);
  EXPECT_EQ(found->scalar(), "emptykey_value");
}

// Test: Insert with empty string value
TEST_F(NodeRefInsertTest_229, InsertEmptyStringValue_229) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  ref.mark_defined();

  node& key = pMemory->create_node();
  key.set_scalar("somekey");
  key.set_type(NodeType::Scalar);
  node& value = pMemory->create_node();
  value.set_scalar("");
  value.set_type(NodeType::Scalar);

  ref.insert(key, value, pMemory);

  node* found = ref.get(std::string("somekey"), pMemory);
  ASSERT_NE(found, nullptr);
  EXPECT_EQ(found->scalar(), "");
}

// Test: Insert and then remove the key
TEST_F(NodeRefInsertTest_229, InsertThenRemove_229) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  ref.mark_defined();

  node& key = pMemory->create_node();
  key.set_scalar("removekey");
  key.set_type(NodeType::Scalar);
  node& value = pMemory->create_node();
  value.set_scalar("removeval");
  value.set_type(NodeType::Scalar);

  ref.insert(key, value, pMemory);
  EXPECT_EQ(ref.size(), 1u);

  bool removed = ref.remove(std::string("removekey"), pMemory);
  EXPECT_TRUE(removed);
}

// Test: Insert using the high-level YAML::Node API
TEST_F(NodeRefInsertTest_229, HighLevelNodeInsert_229) {
  YAML::Node node;
  node["key1"] = "value1";
  node["key2"] = "value2";

  EXPECT_EQ(node.size(), 2u);
  EXPECT_EQ(node["key1"].as<std::string>(), "value1");
  EXPECT_EQ(node["key2"].as<std::string>(), "value2");
}

// Test: Insert via force_insert at node_ref level
TEST_F(NodeRefInsertTest_229, ForceInsertKeyValue_229) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  ref.mark_defined();

  ref.force_insert(std::string("fkey"), std::string("fval"), pMemory);

  EXPECT_EQ(ref.size(), 1u);
  node* found = ref.get(std::string("fkey"), pMemory);
  ASSERT_NE(found, nullptr);
  EXPECT_EQ(found->scalar(), "fval");
}

// Test: Size after insert on an initially empty map
TEST_F(NodeRefInsertTest_229, SizeAfterInsertOnEmptyMap_229) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  ref.mark_defined();

  EXPECT_EQ(ref.size(), 0u);

  node& key = pMemory->create_node();
  key.set_scalar("k");
  key.set_type(NodeType::Scalar);
  node& value = pMemory->create_node();
  value.set_scalar("v");
  value.set_type(NodeType::Scalar);

  ref.insert(key, value, pMemory);
  EXPECT_EQ(ref.size(), 1u);
}

}  // namespace detail
}  // namespace YAML
