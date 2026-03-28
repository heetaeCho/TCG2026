#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node_data.h"
#include "yaml-cpp/node/detail/memory.h"
#include "yaml-cpp/node/detail/node.h"

namespace YAML {
namespace detail {

class NodeDataTest_648 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = std::make_shared<memory_holder>();
  }

  shared_memory_holder pMemory;
};

// Test default construction - node should be undefined and Null type
TEST_F(NodeDataTest_648, DefaultConstruction_IsUndefined_648) {
  node_data nd;
  EXPECT_FALSE(nd.is_defined());
  EXPECT_EQ(nd.type(), NodeType::Null);
}

// Test mark_defined makes node defined
TEST_F(NodeDataTest_648, MarkDefined_MakesNodeDefined_648) {
  node_data nd;
  nd.mark_defined();
  EXPECT_TRUE(nd.is_defined());
}

// Test set_type to Sequence
TEST_F(NodeDataTest_648, SetType_Sequence_648) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  EXPECT_EQ(nd.type(), NodeType::Sequence);
}

// Test set_type to Map
TEST_F(NodeDataTest_648, SetType_Map_648) {
  node_data nd;
  nd.set_type(NodeType::Map);
  EXPECT_EQ(nd.type(), NodeType::Map);
}

// Test set_type to Scalar
TEST_F(NodeDataTest_648, SetType_Scalar_648) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  EXPECT_EQ(nd.type(), NodeType::Scalar);
}

// Test set_type to Null
TEST_F(NodeDataTest_648, SetType_Null_648) {
  node_data nd;
  nd.set_type(NodeType::Null);
  EXPECT_EQ(nd.type(), NodeType::Null);
}

// Test set_null
TEST_F(NodeDataTest_648, SetNull_648) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("hello");
  nd.set_null();
  EXPECT_EQ(nd.type(), NodeType::Null);
}

// Test set_scalar and scalar getter
TEST_F(NodeDataTest_648, SetScalar_ReturnsCorrectValue_648) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("test_value");
  EXPECT_EQ(nd.scalar(), "test_value");
}

// Test set_tag and tag getter
TEST_F(NodeDataTest_648, SetTag_ReturnsCorrectValue_648) {
  node_data nd;
  nd.set_tag("!!str");
  EXPECT_EQ(nd.tag(), "!!str");
}

// Test set_style and style getter
TEST_F(NodeDataTest_648, SetStyle_ReturnsCorrectValue_648) {
  node_data nd;
  nd.set_style(EmitterStyle::Flow);
  EXPECT_EQ(nd.style(), EmitterStyle::Flow);
}

// Test set_style with Block style
TEST_F(NodeDataTest_648, SetStyle_Block_648) {
  node_data nd;
  nd.set_style(EmitterStyle::Block);
  EXPECT_EQ(nd.style(), EmitterStyle::Block);
}

// Test set_mark
TEST_F(NodeDataTest_648, SetMark_648) {
  node_data nd;
  Mark m;
  m.line = 5;
  m.column = 10;
  nd.set_mark(m);
  EXPECT_EQ(nd.mark().line, 5);
  EXPECT_EQ(nd.mark().column, 10);
}

// Test empty_scalar returns empty string
TEST_F(NodeDataTest_648, EmptyScalar_ReturnsEmptyString_648) {
  const std::string& empty = node_data::empty_scalar();
  EXPECT_TRUE(empty.empty());
}

// Test begin/end on undefined node returns default iterators
TEST_F(NodeDataTest_648, BeginEnd_UndefinedNode_ReturnsDefaultIterators_648) {
  node_data nd;
  // Not defined, not a sequence or map
  auto it_begin = nd.begin();
  auto it_end = nd.end();
  EXPECT_EQ(it_begin, it_end);
}

// Test begin/end on Null type returns default iterators
TEST_F(NodeDataTest_648, BeginEnd_NullType_ReturnsDefaultIterators_648) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Null);
  auto it_begin = nd.begin();
  auto it_end = nd.end();
  EXPECT_EQ(it_begin, it_end);
}

// Test begin/end on Scalar type returns default iterators
TEST_F(NodeDataTest_648, BeginEnd_ScalarType_ReturnsDefaultIterators_648) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("hello");
  auto it_begin = nd.begin();
  auto it_end = nd.end();
  EXPECT_EQ(it_begin, it_end);
}

// Test size on empty sequence
TEST_F(NodeDataTest_648, Size_EmptySequence_648) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Sequence);
  EXPECT_EQ(nd.size(), 0u);
}

// Test size on empty map
TEST_F(NodeDataTest_648, Size_EmptyMap_648) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);
  EXPECT_EQ(nd.size(), 0u);
}

// Test begin/end on empty sequence
TEST_F(NodeDataTest_648, BeginEnd_EmptySequence_AreEqual_648) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Sequence);
  auto it_begin = nd.begin();
  auto it_end = nd.end();
  EXPECT_EQ(it_begin, it_end);
}

// Test begin/end on empty map
TEST_F(NodeDataTest_648, BeginEnd_EmptyMap_AreEqual_648) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);
  auto it_begin = nd.begin();
  auto it_end = nd.end();
  EXPECT_EQ(it_begin, it_end);
}

// Test push_back to sequence increases size
TEST_F(NodeDataTest_648, PushBack_IncreasesSequenceSize_648) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Sequence);

  node& n = pMemory->create_node();
  n.set_scalar("item1");
  nd.push_back(n, pMemory);

  EXPECT_EQ(nd.size(), 1u);
}

// Test push_back multiple items
TEST_F(NodeDataTest_648, PushBack_MultipleItems_648) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Sequence);

  node& n1 = pMemory->create_node();
  n1.set_scalar("item1");
  nd.push_back(n1, pMemory);

  node& n2 = pMemory->create_node();
  n2.set_scalar("item2");
  nd.push_back(n2, pMemory);

  node& n3 = pMemory->create_node();
  n3.set_scalar("item3");
  nd.push_back(n3, pMemory);

  EXPECT_EQ(nd.size(), 3u);
}

// Test begin/end iteration on non-empty sequence
TEST_F(NodeDataTest_648, BeginEnd_NonEmptySequence_CanIterate_648) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Sequence);

  node& n1 = pMemory->create_node();
  n1.set_scalar("item1");
  nd.push_back(n1, pMemory);

  auto it = nd.begin();
  auto end = nd.end();
  EXPECT_NE(it, end);

  // Advance to end
  ++it;
  EXPECT_EQ(it, end);
}

// Test insert adds key-value pair to map
TEST_F(NodeDataTest_648, Insert_AddsToMap_648) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("key1");
  node& value = pMemory->create_node();
  value.set_scalar("value1");

  nd.insert(key, value, pMemory);
  EXPECT_EQ(nd.size(), 1u);
}

// Test insert multiple key-value pairs
TEST_F(NodeDataTest_648, Insert_MultipleKeyValuePairs_648) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);

  node& key1 = pMemory->create_node();
  key1.set_scalar("key1");
  node& value1 = pMemory->create_node();
  value1.set_scalar("value1");
  nd.insert(key1, value1, pMemory);

  node& key2 = pMemory->create_node();
  key2.set_scalar("key2");
  node& value2 = pMemory->create_node();
  value2.set_scalar("value2");
  nd.insert(key2, value2, pMemory);

  EXPECT_EQ(nd.size(), 2u);
}

// Test begin/end iteration on non-empty map
TEST_F(NodeDataTest_648, BeginEnd_NonEmptyMap_CanIterate_648) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("key1");
  node& value = pMemory->create_node();
  value.set_scalar("value1");
  nd.insert(key, value, pMemory);

  auto it = nd.begin();
  auto end = nd.end();
  EXPECT_NE(it, end);

  ++it;
  EXPECT_EQ(it, end);
}

// Test get on map with existing key
TEST_F(NodeDataTest_648, Get_ExistingKey_ReturnsNode_648) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("key1");
  node& value = pMemory->create_node();
  value.set_scalar("value1");
  nd.insert(key, value, pMemory);

  const node* result = nd.get(std::string("key1"), pMemory);
  EXPECT_NE(result, nullptr);
}

// Test get on map with non-existing key
TEST_F(NodeDataTest_648, Get_NonExistingKey_ReturnsNull_648) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("key1");
  node& value = pMemory->create_node();
  value.set_scalar("value1");
  nd.insert(key, value, pMemory);

  const node* result = nd.get(std::string("nonexistent"), pMemory);
  EXPECT_EQ(result, nullptr);
}

// Test remove on map with existing key
TEST_F(NodeDataTest_648, Remove_ExistingKey_ReturnsTrue_648) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("key1");
  node& value = pMemory->create_node();
  value.set_scalar("value1");
  nd.insert(key, value, pMemory);

  bool removed = nd.remove(std::string("key1"), pMemory);
  EXPECT_TRUE(removed);
}

// Test remove on map with non-existing key
TEST_F(NodeDataTest_648, Remove_NonExistingKey_ReturnsFalse_648) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("key1");
  node& value = pMemory->create_node();
  value.set_scalar("value1");
  nd.insert(key, value, pMemory);

  bool removed = nd.remove(std::string("nonexistent"), pMemory);
  EXPECT_FALSE(removed);
}

// Test set_type transition from Sequence to Map
TEST_F(NodeDataTest_648, SetType_SequenceToMap_648) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Sequence);

  node& n1 = pMemory->create_node();
  n1.set_scalar("item1");
  nd.push_back(n1, pMemory);

  nd.set_type(NodeType::Map);
  EXPECT_EQ(nd.type(), NodeType::Map);
}

// Test set_type transition from Map to Sequence
TEST_F(NodeDataTest_648, SetType_MapToSequence_648) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);
  nd.set_type(NodeType::Sequence);
  EXPECT_EQ(nd.type(), NodeType::Sequence);
}

// Test set_scalar with empty string
TEST_F(NodeDataTest_648, SetScalar_EmptyString_648) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("");
  EXPECT_EQ(nd.scalar(), "");
}

// Test set_tag with empty string
TEST_F(NodeDataTest_648, SetTag_EmptyString_648) {
  node_data nd;
  nd.set_tag("");
  EXPECT_EQ(nd.tag(), "");
}

// Test size on undefined node
TEST_F(NodeDataTest_648, Size_UndefinedNode_648) {
  node_data nd;
  EXPECT_EQ(nd.size(), 0u);
}

// Test size on Null type
TEST_F(NodeDataTest_648, Size_NullType_648) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Null);
  EXPECT_EQ(nd.size(), 0u);
}

// Test size on Scalar type
TEST_F(NodeDataTest_648, Size_ScalarType_648) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("hello");
  EXPECT_EQ(nd.size(), 0u);
}

// Test force_insert on map
TEST_F(NodeDataTest_648, ForceInsert_AddsToMap_648) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);

  nd.force_insert(std::string("key1"), std::string("value1"), pMemory);
  EXPECT_EQ(nd.size(), 1u);
}

// Test force_insert allows duplicate keys
TEST_F(NodeDataTest_648, ForceInsert_AllowsDuplicateKeys_648) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);

  nd.force_insert(std::string("key1"), std::string("value1"), pMemory);
  nd.force_insert(std::string("key1"), std::string("value2"), pMemory);
  EXPECT_EQ(nd.size(), 2u);
}

// Test default mark is null
TEST_F(NodeDataTest_648, DefaultMark_IsNull_648) {
  node_data nd;
  Mark m = nd.mark();
  EXPECT_EQ(m.line, 0);
  EXPECT_EQ(m.column, 0);
}

// Test set_type to same type doesn't change state
TEST_F(NodeDataTest_648, SetType_SameType_NoChange_648) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Sequence);
  nd.set_type(NodeType::Sequence);
  EXPECT_EQ(nd.type(), NodeType::Sequence);
  EXPECT_EQ(nd.size(), 0u);
}

// Test default style
TEST_F(NodeDataTest_648, DefaultStyle_648) {
  node_data nd;
  EXPECT_EQ(nd.style(), EmitterStyle::Default);
}

// Test get with node& on map
TEST_F(NodeDataTest_648, Get_WithNodeRef_ExistingKey_648) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("key1");
  node& value = pMemory->create_node();
  value.set_scalar("value1");
  nd.insert(key, value, pMemory);

  const node* result = nd.get(key, pMemory);
  EXPECT_NE(result, nullptr);
}

// Test remove with node& on map
TEST_F(NodeDataTest_648, Remove_WithNodeRef_ExistingKey_648) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("key1");
  node& value = pMemory->create_node();
  value.set_scalar("value1");
  nd.insert(key, value, pMemory);

  bool removed = nd.remove(key, pMemory);
  EXPECT_TRUE(removed);
}

// Test remove with node& on map with non-existing key
TEST_F(NodeDataTest_648, Remove_WithNodeRef_NonExistingKey_648) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("key1");
  node& value = pMemory->create_node();
  value.set_scalar("value1");
  nd.insert(key, value, pMemory);

  node& otherKey = pMemory->create_node();
  otherKey.set_scalar("nonexistent");
  bool removed = nd.remove(otherKey, pMemory);
  EXPECT_FALSE(removed);
}

// Test that after removing all entries, size is 0
TEST_F(NodeDataTest_648, Remove_AllEntries_SizeZero_648) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("key1");
  node& value = pMemory->create_node();
  value.set_scalar("value1");
  nd.insert(key, value, pMemory);

  nd.remove(std::string("key1"), pMemory);
  EXPECT_EQ(nd.size(), 0u);
}

// Test that push_back on null type converts to sequence
TEST_F(NodeDataTest_648, PushBack_OnNullType_ConvertsToSequence_648) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Null);

  node& n = pMemory->create_node();
  n.set_scalar("item");
  nd.push_back(n, pMemory);

  EXPECT_EQ(nd.type(), NodeType::Sequence);
  EXPECT_EQ(nd.size(), 1u);
}

}  // namespace detail
}  // namespace YAML
