#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"
#include "yaml-cpp/node/detail/node_ref.h"

namespace YAML {
namespace detail {

class NodeTest_263 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = shared_memory_holder(new memory);
  }

  shared_memory_holder pMemory;
};

// Test default construction - node should not be defined initially
TEST_F(NodeTest_263, DefaultConstructionIsNotDefined_263) {
  node n;
  // A freshly constructed node should have some default state
  EXPECT_FALSE(n.is_defined());
}

// Test that default node type is Undefined
TEST_F(NodeTest_263, DefaultTypeIsUndefined_263) {
  node n;
  EXPECT_EQ(NodeType::Undefined, n.type());
}

// Test mark_defined makes node defined
TEST_F(NodeTest_263, MarkDefinedMakesNodeDefined_263) {
  node n;
  n.mark_defined();
  EXPECT_TRUE(n.is_defined());
}

// Test set_null sets type to Null
TEST_F(NodeTest_263, SetNullSetsTypeToNull_263) {
  node n;
  n.set_null();
  EXPECT_EQ(NodeType::Null, n.type());
}

// Test set_scalar sets scalar value and type
TEST_F(NodeTest_263, SetScalarSetsValue_263) {
  node n;
  n.set_scalar("hello");
  EXPECT_EQ(NodeType::Scalar, n.type());
  EXPECT_EQ("hello", n.scalar());
}

// Test set_scalar with empty string
TEST_F(NodeTest_263, SetScalarEmptyString_263) {
  node n;
  n.set_scalar("");
  EXPECT_EQ(NodeType::Scalar, n.type());
  EXPECT_EQ("", n.scalar());
}

// Test set_tag and tag retrieval
TEST_F(NodeTest_263, SetTagAndRetrieve_263) {
  node n;
  n.set_tag("!mytag");
  EXPECT_EQ("!mytag", n.tag());
}

// Test set_tag with empty string
TEST_F(NodeTest_263, SetTagEmptyString_263) {
  node n;
  n.set_tag("");
  EXPECT_EQ("", n.tag());
}

// Test set_style and style retrieval
TEST_F(NodeTest_263, SetStyleBlock_263) {
  node n;
  n.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, n.style());
}

TEST_F(NodeTest_263, SetStyleFlow_263) {
  node n;
  n.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, n.style());
}

TEST_F(NodeTest_263, SetStyleDefault_263) {
  node n;
  n.set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, n.style());
}

// Test set_type to Sequence
TEST_F(NodeTest_263, SetTypeSequence_263) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
}

// Test set_type to Map
TEST_F(NodeTest_263, SetTypeMap_263) {
  node n;
  n.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, n.type());
}

// Test set_type to Scalar
TEST_F(NodeTest_263, SetTypeScalar_263) {
  node n;
  n.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, n.type());
}

// Test is() identity - same node
TEST_F(NodeTest_263, IsReturnsTrueForSameNode_263) {
  node n;
  EXPECT_TRUE(n.is(n));
}

// Test is() identity - different nodes
TEST_F(NodeTest_263, IsReturnsFalseForDifferentNodes_263) {
  node n1;
  node n2;
  EXPECT_FALSE(n1.is(n2));
}

// Test ref() returns non-null
TEST_F(NodeTest_263, RefReturnsNonNull_263) {
  node n;
  EXPECT_NE(nullptr, n.ref());
}

// Test size of empty sequence
TEST_F(NodeTest_263, EmptySequenceHasSizeZero_263) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(0u, n.size());
}

// Test push_back increases sequence size
TEST_F(NodeTest_263, PushBackIncreasesSize_263) {
  node n;
  n.set_type(NodeType::Sequence);
  
  node& child = pMemory->create_node();
  child.set_scalar("item1");
  
  n.push_back(child, pMemory);
  EXPECT_EQ(1u, n.size());
}

// Test push_back multiple items
TEST_F(NodeTest_263, PushBackMultipleItems_263) {
  node n;
  n.set_type(NodeType::Sequence);
  
  node& child1 = pMemory->create_node();
  child1.set_scalar("item1");
  node& child2 = pMemory->create_node();
  child2.set_scalar("item2");
  node& child3 = pMemory->create_node();
  child3.set_scalar("item3");
  
  n.push_back(child1, pMemory);
  n.push_back(child2, pMemory);
  n.push_back(child3, pMemory);
  
  EXPECT_EQ(3u, n.size());
}

// Test begin() == end() for empty sequence
TEST_F(NodeTest_263, EmptySequenceBeginEqualsEnd_263) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_TRUE(n.begin() == n.end());
}

// Test iteration over sequence with items
TEST_F(NodeTest_263, SequenceIterationCountsCorrectly_263) {
  node n;
  n.set_type(NodeType::Sequence);
  
  node& child1 = pMemory->create_node();
  child1.set_scalar("a");
  node& child2 = pMemory->create_node();
  child2.set_scalar("b");
  
  n.push_back(child1, pMemory);
  n.push_back(child2, pMemory);
  
  std::size_t count = 0;
  for (auto it = n.begin(); it != n.end(); ++it) {
    ++count;
  }
  EXPECT_EQ(2u, count);
}

// Test insert into map
TEST_F(NodeTest_263, InsertIntoMap_263) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("key1");
  node& value = pMemory->create_node();
  value.set_scalar("value1");
  
  n.insert(key, value, pMemory);
  EXPECT_EQ(1u, n.size());
}

// Test get from map with string key
TEST_F(NodeTest_263, GetFromMapWithStringKey_263) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("mykey");
  node& value = pMemory->create_node();
  value.set_scalar("myvalue");
  
  n.insert(key, value, pMemory);
  
  node* result = n.get(std::string("mykey"), pMemory);
  EXPECT_NE(nullptr, result);
  EXPECT_EQ("myvalue", result->scalar());
}

// Test get from map returns null for non-existent key
TEST_F(NodeTest_263, GetFromMapReturnsNullForMissingKey_263) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("mykey");
  node& value = pMemory->create_node();
  value.set_scalar("myvalue");
  
  n.insert(key, value, pMemory);
  
  node* result = n.get(std::string("nonexistent"), pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test get with node key
TEST_F(NodeTest_263, GetWithNodeKey_263) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("nodekey");
  node& value = pMemory->create_node();
  value.set_scalar("nodevalue");
  
  n.insert(key, value, pMemory);
  
  node* result = n.get(key, pMemory);
  EXPECT_NE(nullptr, result);
  EXPECT_EQ("nodevalue", result->scalar());
}

// Test remove from map with string key
TEST_F(NodeTest_263, RemoveFromMapWithStringKey_263) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("removekey");
  node& value = pMemory->create_node();
  value.set_scalar("removevalue");
  
  n.insert(key, value, pMemory);
  EXPECT_EQ(1u, n.size());
  
  bool removed = n.remove(std::string("removekey"), pMemory);
  EXPECT_TRUE(removed);
}

// Test remove non-existent key returns false
TEST_F(NodeTest_263, RemoveNonExistentKeyReturnsFalse_263) {
  node n;
  n.set_type(NodeType::Map);
  
  bool removed = n.remove(std::string("nonexistent"), pMemory);
  EXPECT_FALSE(removed);
}

// Test remove with node key
TEST_F(NodeTest_263, RemoveWithNodeKey_263) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("nkey");
  node& value = pMemory->create_node();
  value.set_scalar("nvalue");
  
  n.insert(key, value, pMemory);
  
  bool removed = n.remove(key, pMemory);
  EXPECT_TRUE(removed);
}

// Test set_ref makes node reference another
TEST_F(NodeTest_263, SetRefCopiesReference_263) {
  node n1;
  n1.set_scalar("original");
  
  node n2;
  n2.set_ref(n1);
  
  EXPECT_EQ("original", n2.scalar());
  EXPECT_EQ(NodeType::Scalar, n2.type());
}

// Test set_data copies data from another node
TEST_F(NodeTest_263, SetDataCopiesData_263) {
  node n1;
  n1.set_scalar("data_value");
  n1.set_tag("!tag");
  
  node n2;
  n2.set_data(n1);
  
  EXPECT_EQ("data_value", n2.scalar());
  EXPECT_EQ("!tag", n2.tag());
}

// Test set_mark
TEST_F(NodeTest_263, SetMarkSetsMarkCorrectly_263) {
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

// Test equals with string
TEST_F(NodeTest_263, EqualsWithMatchingString_263) {
  node n;
  n.set_scalar("test");
  
  EXPECT_TRUE(n.equals(std::string("test"), pMemory));
}

// Test equals with non-matching string
TEST_F(NodeTest_263, EqualsWithNonMatchingString_263) {
  node n;
  n.set_scalar("test");
  
  EXPECT_FALSE(n.equals(std::string("other"), pMemory));
}

// Test equals with const char*
TEST_F(NodeTest_263, EqualsWithConstCharPtr_263) {
  node n;
  n.set_scalar("hello");
  
  EXPECT_TRUE(n.equals("hello", pMemory));
}

// Test equals with non-matching const char*
TEST_F(NodeTest_263, EqualsWithNonMatchingConstCharPtr_263) {
  node n;
  n.set_scalar("hello");
  
  EXPECT_FALSE(n.equals("world", pMemory));
}

// Test force_insert into map
TEST_F(NodeTest_263, ForceInsertIntoMap_263) {
  node n;
  n.set_type(NodeType::Map);
  
  n.force_insert(std::string("fkey"), std::string("fval"), pMemory);
  EXPECT_EQ(1u, n.size());
}

// Test force_insert allows duplicate keys
TEST_F(NodeTest_263, ForceInsertAllowsDuplicateKeys_263) {
  node n;
  n.set_type(NodeType::Map);
  
  n.force_insert(std::string("dup"), std::string("val1"), pMemory);
  n.force_insert(std::string("dup"), std::string("val2"), pMemory);
  EXPECT_EQ(2u, n.size());
}

// Test empty map has size zero
TEST_F(NodeTest_263, EmptyMapHasSizeZero_263) {
  node n;
  n.set_type(NodeType::Map);
  EXPECT_EQ(0u, n.size());
}

// Test changing type resets content
TEST_F(NodeTest_263, ChangingTypeFromScalarToSequence_263) {
  node n;
  n.set_scalar("value");
  EXPECT_EQ(NodeType::Scalar, n.type());
  
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
  EXPECT_EQ(0u, n.size());
}

// Test add_dependency doesn't crash
TEST_F(NodeTest_263, AddDependencyDoesNotCrash_263) {
  node n1;
  node n2;
  n1.add_dependency(n2);
  // Just verify no crash; dependency tracking is internal
}

// Test set_scalar overwrites previous scalar
TEST_F(NodeTest_263, SetScalarOverwritesPrevious_263) {
  node n;
  n.set_scalar("first");
  EXPECT_EQ("first", n.scalar());
  
  n.set_scalar("second");
  EXPECT_EQ("second", n.scalar());
}

// Test map iteration
TEST_F(NodeTest_263, MapIterationCountsCorrectly_263) {
  node n;
  n.set_type(NodeType::Map);
  
  node& k1 = pMemory->create_node();
  k1.set_scalar("k1");
  node& v1 = pMemory->create_node();
  v1.set_scalar("v1");
  
  node& k2 = pMemory->create_node();
  k2.set_scalar("k2");
  node& v2 = pMemory->create_node();
  v2.set_scalar("v2");
  
  n.insert(k1, v1, pMemory);
  n.insert(k2, v2, pMemory);
  
  std::size_t count = 0;
  for (auto it = n.begin(); it != n.end(); ++it) {
    ++count;
  }
  EXPECT_EQ(2u, count);
}

// Test get on empty map returns null
TEST_F(NodeTest_263, GetOnEmptyMapReturnsNull_263) {
  node n;
  n.set_type(NodeType::Map);
  
  node* result = n.get(std::string("anything"), pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test remove on empty map returns false
TEST_F(NodeTest_263, RemoveOnEmptyMapReturnsFalse_263) {
  node n;
  n.set_type(NodeType::Map);
  
  bool removed = n.remove(std::string("anything"), pMemory);
  EXPECT_FALSE(removed);
}

// Test multiple operations on same node
TEST_F(NodeTest_263, MultipleOperationsOnSameNode_263) {
  node n;
  n.set_type(NodeType::Map);
  
  node& k1 = pMemory->create_node();
  k1.set_scalar("a");
  node& v1 = pMemory->create_node();
  v1.set_scalar("1");
  
  n.insert(k1, v1, pMemory);
  EXPECT_EQ(1u, n.size());
  
  node* found = n.get(std::string("a"), pMemory);
  EXPECT_NE(nullptr, found);
  EXPECT_EQ("1", found->scalar());
  
  n.remove(std::string("a"), pMemory);
  
  node* notFound = n.get(std::string("a"), pMemory);
  EXPECT_EQ(nullptr, notFound);
}

}  // namespace detail
}  // namespace YAML
