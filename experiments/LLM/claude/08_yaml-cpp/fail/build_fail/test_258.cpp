#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeTest_258 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory.reset(new Memory);
  }

  shared_memory_holder pMemory;
};

// Test default construction - node should not be defined initially
TEST_F(NodeTest_258, DefaultConstructionIsNotDefined_258) {
  node n;
  EXPECT_FALSE(n.is_defined());
}

// Test default construction - type should be Undefined
TEST_F(NodeTest_258, DefaultConstructionTypeUndefined_258) {
  node n;
  EXPECT_EQ(NodeType::Undefined, n.type());
}

// Test mark_defined makes the node defined
TEST_F(NodeTest_258, MarkDefinedMakesNodeDefined_258) {
  node n;
  n.mark_defined();
  EXPECT_TRUE(n.is_defined());
}

// Test set_null sets the type to Null
TEST_F(NodeTest_258, SetNullSetsTypeToNull_258) {
  node n;
  n.set_null();
  EXPECT_EQ(NodeType::Null, n.type());
}

// Test set_scalar sets the scalar value
TEST_F(NodeTest_258, SetScalarSetsValue_258) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");
  EXPECT_EQ("hello", n.scalar());
}

// Test set_type to Sequence
TEST_F(NodeTest_258, SetTypeSequence_258) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
}

// Test set_type to Map
TEST_F(NodeTest_258, SetTypeMap_258) {
  node n;
  n.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, n.type());
}

// Test set_tag and tag retrieval
TEST_F(NodeTest_258, SetTagAndGetTag_258) {
  node n;
  n.set_tag("!mytag");
  EXPECT_EQ("!mytag", n.tag());
}

// Test set_style and style retrieval
TEST_F(NodeTest_258, SetStyleAndGetStyle_258) {
  node n;
  n.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, n.style());
}

// Test default style
TEST_F(NodeTest_258, DefaultStyle_258) {
  node n;
  EXPECT_EQ(EmitterStyle::Default, n.style());
}

// Test is() - same node returns true
TEST_F(NodeTest_258, IsSameNodeReturnsTrue_258) {
  node n;
  EXPECT_TRUE(n.is(n));
}

// Test is() - different nodes return false
TEST_F(NodeTest_258, IsDifferentNodeReturnsFalse_258) {
  node n1;
  node n2;
  EXPECT_FALSE(n1.is(n2));
}

// Test ref() returns non-null
TEST_F(NodeTest_258, RefReturnsNonNull_258) {
  node n;
  EXPECT_NE(nullptr, n.ref());
}

// Test size of empty sequence is 0
TEST_F(NodeTest_258, EmptySequenceSizeIsZero_258) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(0u, n.size());
}

// Test push_back increases size
TEST_F(NodeTest_258, PushBackIncreasesSize_258) {
  node n;
  n.set_type(NodeType::Sequence);
  
  node& child = pMemory->create_node();
  child.set_scalar("value1");
  
  n.push_back(child, pMemory);
  EXPECT_EQ(1u, n.size());
}

// Test push_back multiple elements
TEST_F(NodeTest_258, PushBackMultipleElements_258) {
  node n;
  n.set_type(NodeType::Sequence);
  
  node& child1 = pMemory->create_node();
  child1.set_scalar("value1");
  node& child2 = pMemory->create_node();
  child2.set_scalar("value2");
  
  n.push_back(child1, pMemory);
  n.push_back(child2, pMemory);
  EXPECT_EQ(2u, n.size());
}

// Test insert into map
TEST_F(NodeTest_258, InsertIntoMap_258) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("key1");
  node& value = pMemory->create_node();
  value.set_scalar("value1");
  
  n.insert(key, value, pMemory);
  EXPECT_EQ(1u, n.size());
}

// Test insert multiple entries into map
TEST_F(NodeTest_258, InsertMultipleEntriesIntoMap_258) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key1 = pMemory->create_node();
  key1.set_scalar("key1");
  node& value1 = pMemory->create_node();
  value1.set_scalar("value1");
  
  node& key2 = pMemory->create_node();
  key2.set_scalar("key2");
  node& value2 = pMemory->create_node();
  value2.set_scalar("value2");
  
  n.insert(key1, value1, pMemory);
  n.insert(key2, value2, pMemory);
  EXPECT_EQ(2u, n.size());
}

// Test get on map returns correct node
TEST_F(NodeTest_258, GetOnMapReturnsCorrectNode_258) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("mykey");
  node& value = pMemory->create_node();
  value.set_scalar("myvalue");
  
  n.insert(key, value, pMemory);
  
  node* result = n.get(std::string("mykey"), pMemory);
  ASSERT_NE(nullptr, result);
  EXPECT_EQ("myvalue", result->scalar());
}

// Test get on map returns null for non-existent key
TEST_F(NodeTest_258, GetOnMapReturnsNullForNonExistentKey_258) {
  node n;
  n.set_type(NodeType::Map);
  
  node* result = n.get(std::string("nonexistent"), pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test remove from map
TEST_F(NodeTest_258, RemoveFromMap_258) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("mykey");
  node& value = pMemory->create_node();
  value.set_scalar("myvalue");
  
  n.insert(key, value, pMemory);
  EXPECT_EQ(1u, n.size());
  
  bool removed = n.remove(std::string("mykey"), pMemory);
  EXPECT_TRUE(removed);
}

// Test remove non-existent key returns false
TEST_F(NodeTest_258, RemoveNonExistentKeyReturnsFalse_258) {
  node n;
  n.set_type(NodeType::Map);
  
  bool removed = n.remove(std::string("nonexistent"), pMemory);
  EXPECT_FALSE(removed);
}

// Test set_data copies data from another node
TEST_F(NodeTest_258, SetDataCopiesFromAnotherNode_258) {
  node n1;
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("copied_value");
  
  node n2;
  n2.set_data(n1);
  
  EXPECT_EQ(NodeType::Scalar, n2.type());
  EXPECT_EQ("copied_value", n2.scalar());
}

// Test set_ref makes node reference another node
TEST_F(NodeTest_258, SetRefReferencesAnotherNode_258) {
  node n1;
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("ref_value");
  
  node n2;
  n2.set_ref(n1);
  
  EXPECT_EQ("ref_value", n2.scalar());
}

// Test equals with matching scalar
TEST_F(NodeTest_258, EqualsWithMatchingScalar_258) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("test");
  
  EXPECT_TRUE(n.equals(std::string("test"), pMemory));
}

// Test equals with non-matching scalar
TEST_F(NodeTest_258, EqualsWithNonMatchingScalar_258) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("test");
  
  EXPECT_FALSE(n.equals(std::string("other"), pMemory));
}

// Test equals with const char*
TEST_F(NodeTest_258, EqualsWithConstCharPtr_258) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");
  
  EXPECT_TRUE(n.equals("hello", pMemory));
  EXPECT_FALSE(n.equals("world", pMemory));
}

// Test set_mark and mark retrieval
TEST_F(NodeTest_258, SetMarkAndGetMark_258) {
  node n;
  Mark m;
  m.pos = 10;
  m.line = 5;
  m.column = 3;
  n.set_mark(m);
  
  const Mark& retrieved = n.mark();
  EXPECT_EQ(5, retrieved.line);
  EXPECT_EQ(3, retrieved.column);
}

// Test empty tag by default
TEST_F(NodeTest_258, DefaultTagIsEmpty_258) {
  node n;
  EXPECT_EQ("", n.tag());
}

// Test set scalar with empty string
TEST_F(NodeTest_258, SetScalarEmptyString_258) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("");
  EXPECT_EQ("", n.scalar());
}

// Test begin and end for empty sequence
TEST_F(NodeTest_258, BeginEqualsEndForEmptySequence_258) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_TRUE(n.begin() == n.end());
}

// Test begin and end for non-empty sequence
TEST_F(NodeTest_258, BeginNotEqualsEndForNonEmptySequence_258) {
  node n;
  n.set_type(NodeType::Sequence);
  
  node& child = pMemory->create_node();
  child.set_scalar("item");
  n.push_back(child, pMemory);
  
  EXPECT_FALSE(n.begin() == n.end());
}

// Test get with node key
TEST_F(NodeTest_258, GetWithNodeKey_258) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("nodekey");
  node& value = pMemory->create_node();
  value.set_scalar("nodevalue");
  
  n.insert(key, value, pMemory);
  
  node* result = n.get(key, pMemory);
  ASSERT_NE(nullptr, result);
  EXPECT_EQ("nodevalue", result->scalar());
}

// Test remove with node key
TEST_F(NodeTest_258, RemoveWithNodeKey_258) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("removekey");
  node& value = pMemory->create_node();
  value.set_scalar("removevalue");
  
  n.insert(key, value, pMemory);
  
  bool removed = n.remove(key, pMemory);
  EXPECT_TRUE(removed);
}

// Test remove with node key that doesn't exist
TEST_F(NodeTest_258, RemoveWithNonExistentNodeKey_258) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("nonexistent");
  
  bool removed = n.remove(key, pMemory);
  EXPECT_FALSE(removed);
}

// Test force_insert
TEST_F(NodeTest_258, ForceInsertAddsEntry_258) {
  node n;
  n.set_type(NodeType::Map);
  
  n.force_insert(std::string("fkey"), std::string("fvalue"), pMemory);
  EXPECT_EQ(1u, n.size());
}

// Test changing type resets content
TEST_F(NodeTest_258, ChangingTypeResetsContent_258) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");
  
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
  EXPECT_EQ(0u, n.size());
}

// Test set_type to Null
TEST_F(NodeTest_258, SetTypeToNull_258) {
  node n;
  n.set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, n.type());
  EXPECT_TRUE(n.is_defined());
}

// Test add_dependency does not crash
TEST_F(NodeTest_258, AddDependencyDoesNotCrash_258) {
  node n1;
  node n2;
  EXPECT_NO_THROW(n1.add_dependency(n2));
}

// Test set_scalar with large string
TEST_F(NodeTest_258, SetScalarLargeString_258) {
  node n;
  n.set_type(NodeType::Scalar);
  std::string largeStr(10000, 'x');
  n.set_scalar(largeStr);
  EXPECT_EQ(largeStr, n.scalar());
}

// Test equals with integer type
TEST_F(NodeTest_258, EqualsWithIntegerType_258) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("42");
  
  EXPECT_TRUE(n.equals(42, pMemory));
}

// Test empty map size
TEST_F(NodeTest_258, EmptyMapSizeIsZero_258) {
  node n;
  n.set_type(NodeType::Map);
  EXPECT_EQ(0u, n.size());
}

// Test set_style to Block
TEST_F(NodeTest_258, SetStyleBlock_258) {
  node n;
  n.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, n.style());
}

}  // namespace detail
}  // namespace YAML
