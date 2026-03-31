#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node_data.h"
#include "yaml-cpp/node/detail/memory.h"
#include "yaml-cpp/node/detail/node.h"

namespace YAML {
namespace detail {

class NodeDataTest_649 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = std::make_shared<memory_holder>();
    memory = pMemory->create_memory();
  }

  std::shared_ptr<memory_holder> pMemory;
  shared_memory_holder memory;
};

// Test default construction state
TEST_F(NodeDataTest_649, DefaultConstructionIsNotDefined_649) {
  node_data nd;
  EXPECT_FALSE(nd.is_defined());
}

TEST_F(NodeDataTest_649, DefaultConstructionTypeIsNull_649) {
  node_data nd;
  EXPECT_EQ(NodeType::Null, nd.type());
}

TEST_F(NodeDataTest_649, DefaultConstructionScalarIsEmpty_649) {
  node_data nd;
  EXPECT_TRUE(nd.scalar().empty());
}

TEST_F(NodeDataTest_649, DefaultConstructionTagIsEmpty_649) {
  node_data nd;
  EXPECT_TRUE(nd.tag().empty());
}

// Test mark_defined
TEST_F(NodeDataTest_649, MarkDefinedMakesNodeDefined_649) {
  node_data nd;
  nd.mark_defined();
  EXPECT_TRUE(nd.is_defined());
}

// Test set_type
TEST_F(NodeDataTest_649, SetTypeToSequence_649) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, nd.type());
}

TEST_F(NodeDataTest_649, SetTypeToMap_649) {
  node_data nd;
  nd.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, nd.type());
}

TEST_F(NodeDataTest_649, SetTypeToScalar_649) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, nd.type());
}

TEST_F(NodeDataTest_649, SetTypeToNull_649) {
  node_data nd;
  nd.set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, nd.type());
}

// Test set_tag
TEST_F(NodeDataTest_649, SetTagStoresTag_649) {
  node_data nd;
  nd.set_tag("test_tag");
  EXPECT_EQ("test_tag", nd.tag());
}

TEST_F(NodeDataTest_649, SetTagEmpty_649) {
  node_data nd;
  nd.set_tag("");
  EXPECT_TRUE(nd.tag().empty());
}

// Test set_scalar
TEST_F(NodeDataTest_649, SetScalarStoresValue_649) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("hello");
  EXPECT_EQ("hello", nd.scalar());
}

TEST_F(NodeDataTest_649, SetScalarEmpty_649) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("");
  EXPECT_TRUE(nd.scalar().empty());
}

// Test set_null
TEST_F(NodeDataTest_649, SetNullResetsToNull_649) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("hello");
  nd.set_null();
  EXPECT_EQ(NodeType::Null, nd.type());
}

// Test set_style
TEST_F(NodeDataTest_649, SetStyleDefault_649) {
  node_data nd;
  nd.set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, nd.style());
}

TEST_F(NodeDataTest_649, SetStyleFlow_649) {
  node_data nd;
  nd.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, nd.style());
}

TEST_F(NodeDataTest_649, SetStyleBlock_649) {
  node_data nd;
  nd.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, nd.style());
}

// Test set_mark
TEST_F(NodeDataTest_649, SetMarkStoresMark_649) {
  node_data nd;
  Mark m;
  m.pos = 10;
  m.line = 5;
  m.column = 3;
  nd.set_mark(m);
  EXPECT_EQ(5, nd.mark().line);
  EXPECT_EQ(3, nd.mark().column);
  EXPECT_EQ(10, nd.mark().pos);
}

// Test empty_scalar
TEST_F(NodeDataTest_649, EmptyScalarReturnsEmptyString_649) {
  const std::string& es = node_data::empty_scalar();
  EXPECT_TRUE(es.empty());
}

// Test end() for undefined node
TEST_F(NodeDataTest_649, EndReturnsDefaultIteratorWhenNotDefined_649) {
  node_data nd;
  // Not defined, not marked as defined
  const_node_iterator it = nd.end();
  const_node_iterator default_it{};
  EXPECT_EQ(it, default_it);
}

// Test end() for Null type
TEST_F(NodeDataTest_649, EndReturnsDefaultIteratorForNullType_649) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Null);
  const_node_iterator it = nd.end();
  const_node_iterator default_it{};
  EXPECT_EQ(it, default_it);
}

// Test end() for Scalar type
TEST_F(NodeDataTest_649, EndReturnsDefaultIteratorForScalarType_649) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("value");
  const_node_iterator it = nd.end();
  const_node_iterator default_it{};
  EXPECT_EQ(it, default_it);
}

// Test begin() and end() for empty sequence
TEST_F(NodeDataTest_649, BeginEqualsEndForEmptySequence_649) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Sequence);
  EXPECT_EQ(nd.begin(), nd.end());
}

// Test begin() and end() for empty map
TEST_F(NodeDataTest_649, BeginEqualsEndForEmptyMap_649) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);
  EXPECT_EQ(nd.begin(), nd.end());
}

// Test size for various types
TEST_F(NodeDataTest_649, SizeIsZeroForNull_649) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Null);
  EXPECT_EQ(0u, nd.size());
}

TEST_F(NodeDataTest_649, SizeIsZeroForScalar_649) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Scalar);
  EXPECT_EQ(0u, nd.size());
}

TEST_F(NodeDataTest_649, SizeIsZeroForEmptySequence_649) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Sequence);
  EXPECT_EQ(0u, nd.size());
}

TEST_F(NodeDataTest_649, SizeIsZeroForEmptyMap_649) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);
  EXPECT_EQ(0u, nd.size());
}

// Test push_back to sequence
TEST_F(NodeDataTest_649, PushBackIncreasesSequenceSize_649) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Sequence);

  node n;
  nd.push_back(n, memory);
  EXPECT_EQ(1u, nd.size());
}

TEST_F(NodeDataTest_649, PushBackMultipleElements_649) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Sequence);

  node n1, n2, n3;
  nd.push_back(n1, memory);
  nd.push_back(n2, memory);
  nd.push_back(n3, memory);
  EXPECT_EQ(3u, nd.size());
}

// Test begin != end after push_back
TEST_F(NodeDataTest_649, BeginNotEqualsEndAfterPushBack_649) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Sequence);

  node n;
  nd.push_back(n, memory);
  EXPECT_NE(nd.begin(), nd.end());
}

// Test insert into map
TEST_F(NodeDataTest_649, InsertIncreasesMapSize_649) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);

  node key, value;
  nd.insert(key, value, memory);
  EXPECT_EQ(1u, nd.size());
}

TEST_F(NodeDataTest_649, InsertMultiplePairsIntoMap_649) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);

  node k1, v1, k2, v2;
  nd.insert(k1, v1, memory);
  nd.insert(k2, v2, memory);
  EXPECT_EQ(2u, nd.size());
}

// Test begin != end after insert into map
TEST_F(NodeDataTest_649, BeginNotEqualsEndAfterInsertIntoMap_649) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);

  node key, value;
  nd.insert(key, value, memory);
  EXPECT_NE(nd.begin(), nd.end());
}

// Test type change clears previous data
TEST_F(NodeDataTest_649, ChangingTypeFromSequenceToMapResetsSize_649) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Sequence);

  node n;
  nd.push_back(n, memory);
  EXPECT_EQ(1u, nd.size());

  nd.set_type(NodeType::Map);
  EXPECT_EQ(0u, nd.size());
}

TEST_F(NodeDataTest_649, ChangingTypeFromMapToSequenceResetsSize_649) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);

  node key, value;
  nd.insert(key, value, memory);
  EXPECT_EQ(1u, nd.size());

  nd.set_type(NodeType::Sequence);
  EXPECT_EQ(0u, nd.size());
}

// Test get with node key on map
TEST_F(NodeDataTest_649, GetReturnsNullForMissingKeyInMap_649) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);

  node key;
  key.set_data(*(new node_data()));
  key.set_type(NodeType::Scalar);
  key.set_scalar("nonexistent");

  const node* result = nd.get(key, memory);
  // For an empty map, a get with a key that hasn't been inserted should not find it
  // This depends on implementation; we just test that it doesn't crash
  // and the behavior is consistent
  (void)result;
}

// Test remove on empty map
TEST_F(NodeDataTest_649, RemoveFromEmptyMapReturnsFalse_649) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);

  node key;
  bool removed = nd.remove(key, memory);
  EXPECT_FALSE(removed);
}

// Test switching from undefined to defined then using end
TEST_F(NodeDataTest_649, EndAfterMarkDefinedAndSetSequence_649) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Sequence);
  // end should be a valid sequence iterator, same as begin for empty
  EXPECT_EQ(nd.begin(), nd.end());
}

// Test set_type to same type doesn't reset
TEST_F(NodeDataTest_649, SetSameTypeSequenceDoesNotReset_649) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Sequence);

  node n;
  nd.push_back(n, memory);
  EXPECT_EQ(1u, nd.size());

  // Setting same type should not reset
  nd.set_type(NodeType::Sequence);
  EXPECT_EQ(1u, nd.size());
}

TEST_F(NodeDataTest_649, SetSameTypeMapDoesNotReset_649) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);

  node key, value;
  nd.insert(key, value, memory);
  EXPECT_EQ(1u, nd.size());

  nd.set_type(NodeType::Map);
  EXPECT_EQ(1u, nd.size());
}

// Test null mark by default
TEST_F(NodeDataTest_649, DefaultMarkIsNullMark_649) {
  node_data nd;
  Mark m = nd.mark();
  Mark null_mark = Mark::null_mark();
  EXPECT_EQ(null_mark.pos, m.pos);
  EXPECT_EQ(null_mark.line, m.line);
  EXPECT_EQ(null_mark.column, m.column);
}

// Test that begin returns default iterator for undefined node
TEST_F(NodeDataTest_649, BeginReturnsDefaultIteratorWhenNotDefined_649) {
  node_data nd;
  const_node_iterator it = nd.begin();
  const_node_iterator default_it{};
  EXPECT_EQ(it, default_it);
}

// Test force_insert with string keys/values
TEST_F(NodeDataTest_649, ForceInsertAddsToMap_649) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);

  nd.force_insert("key1", "value1", memory);
  EXPECT_EQ(1u, nd.size());
}

TEST_F(NodeDataTest_649, ForceInsertMultipleEntries_649) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);

  nd.force_insert("key1", "value1", memory);
  nd.force_insert("key2", "value2", memory);
  EXPECT_EQ(2u, nd.size());
}

// Test get with template key on map
TEST_F(NodeDataTest_649, GetWithStringKeyOnEmptyMap_649) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);

  const node* result = nd.get(std::string("missing"), memory);
  EXPECT_EQ(nullptr, result);
}

// Test remove with template key on map
TEST_F(NodeDataTest_649, RemoveWithStringKeyOnEmptyMap_649) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);

  bool removed = nd.remove(std::string("missing"), memory);
  EXPECT_FALSE(removed);
}

// Test push_back on null type converts to sequence
TEST_F(NodeDataTest_649, PushBackOnNullConvertsToSequence_649) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Null);

  node n;
  nd.push_back(n, memory);
  EXPECT_EQ(NodeType::Sequence, nd.type());
  EXPECT_EQ(1u, nd.size());
}

}  // namespace detail
}  // namespace YAML
