#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"
#include "yaml-cpp/node/detail/node_ref.h"

namespace YAML {
namespace detail {

class NodeTest_260 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = shared_memory_holder(new memory);
  }

  shared_memory_holder pMemory;
};

// Test default construction - node should not be defined by default
TEST_F(NodeTest_260, DefaultConstructionIsNotDefined_260) {
  node n;
  // A freshly constructed node should exist but type may be Undefined
  EXPECT_EQ(n.type(), NodeType::Undefined);
  EXPECT_FALSE(n.is_defined());
}

// Test that node is itself
TEST_F(NodeTest_260, NodeIsSelf_260) {
  node n;
  EXPECT_TRUE(n.is(n));
}

// Test that two different nodes are not the same
TEST_F(NodeTest_260, DifferentNodesAreNotSame_260) {
  node n1;
  node n2;
  EXPECT_FALSE(n1.is(n2));
}

// Test mark_defined makes node defined
TEST_F(NodeTest_260, MarkDefinedMakesNodeDefined_260) {
  node n;
  n.mark_defined();
  EXPECT_TRUE(n.is_defined());
}

// Test set_null sets type to Null
TEST_F(NodeTest_260, SetNullSetsTypeToNull_260) {
  node n;
  n.set_null();
  EXPECT_EQ(n.type(), NodeType::Null);
  EXPECT_TRUE(n.is_defined());
}

// Test set_scalar sets type and value
TEST_F(NodeTest_260, SetScalarSetsScalarValue_260) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");
  EXPECT_EQ(n.type(), NodeType::Scalar);
  EXPECT_EQ(n.scalar(), "hello");
}

// Test set_type to Sequence
TEST_F(NodeTest_260, SetTypeSequence_260) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(n.type(), NodeType::Sequence);
}

// Test set_type to Map
TEST_F(NodeTest_260, SetTypeMap_260) {
  node n;
  n.set_type(NodeType::Map);
  EXPECT_EQ(n.type(), NodeType::Map);
}

// Test set_tag and tag retrieval
TEST_F(NodeTest_260, SetAndGetTag_260) {
  node n;
  n.set_tag("!custom");
  EXPECT_EQ(n.tag(), "!custom");
}

// Test set_style and style retrieval
TEST_F(NodeTest_260, SetAndGetStyle_260) {
  node n;
  n.set_style(EmitterStyle::Flow);
  EXPECT_EQ(n.style(), EmitterStyle::Flow);
}

// Test set_style Block
TEST_F(NodeTest_260, SetStyleBlock_260) {
  node n;
  n.set_style(EmitterStyle::Block);
  EXPECT_EQ(n.style(), EmitterStyle::Block);
}

// Test set_style Default
TEST_F(NodeTest_260, SetStyleDefault_260) {
  node n;
  n.set_style(EmitterStyle::Default);
  EXPECT_EQ(n.style(), EmitterStyle::Default);
}

// Test size of empty sequence
TEST_F(NodeTest_260, EmptySequenceHasSizeZero_260) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(n.size(), 0u);
}

// Test push_back increases size for sequence
TEST_F(NodeTest_260, PushBackIncreasesSize_260) {
  node n;
  n.set_type(NodeType::Sequence);

  node& child = pMemory->create_node();
  child.set_scalar("value1");
  n.push_back(child, pMemory);

  EXPECT_EQ(n.size(), 1u);
}

// Test push_back multiple elements
TEST_F(NodeTest_260, PushBackMultipleElements_260) {
  node n;
  n.set_type(NodeType::Sequence);

  node& child1 = pMemory->create_node();
  child1.set_scalar("value1");
  n.push_back(child1, pMemory);

  node& child2 = pMemory->create_node();
  child2.set_scalar("value2");
  n.push_back(child2, pMemory);

  EXPECT_EQ(n.size(), 2u);
}

// Test insert into map
TEST_F(NodeTest_260, InsertIntoMap_260) {
  node n;
  n.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("key1");

  node& value = pMemory->create_node();
  value.set_scalar("value1");

  n.insert(key, value, pMemory);
  EXPECT_EQ(n.size(), 1u);
}

// Test get on map with string key
TEST_F(NodeTest_260, GetFromMapWithStringKey_260) {
  node n;
  n.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("mykey");

  node& value = pMemory->create_node();
  value.set_scalar("myvalue");

  n.insert(key, value, pMemory);

  node* result = n.get(std::string("mykey"), pMemory);
  EXPECT_NE(result, nullptr);
  EXPECT_EQ(result->scalar(), "myvalue");
}

// Test get returns nullptr for non-existent key
TEST_F(NodeTest_260, GetNonExistentKeyReturnsNull_260) {
  node n;
  n.set_type(NodeType::Map);

  node* result = n.get(std::string("nonexistent"), pMemory);
  EXPECT_EQ(result, nullptr);
}

// Test remove from map with string key
TEST_F(NodeTest_260, RemoveFromMapWithStringKey_260) {
  node n;
  n.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("removekey");

  node& value = pMemory->create_node();
  value.set_scalar("removevalue");

  n.insert(key, value, pMemory);
  EXPECT_EQ(n.size(), 1u);

  bool removed = n.remove(std::string("removekey"), pMemory);
  EXPECT_TRUE(removed);
}

// Test remove non-existent key returns false
TEST_F(NodeTest_260, RemoveNonExistentKeyReturnsFalse_260) {
  node n;
  n.set_type(NodeType::Map);

  bool removed = n.remove(std::string("nonexistent"), pMemory);
  EXPECT_FALSE(removed);
}

// Test remove with node key
TEST_F(NodeTest_260, RemoveWithNodeKey_260) {
  node n;
  n.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("nodekey");

  node& value = pMemory->create_node();
  value.set_scalar("nodevalue");

  n.insert(key, value, pMemory);
  EXPECT_EQ(n.size(), 1u);

  bool removed = n.remove(key, pMemory);
  EXPECT_TRUE(removed);
}

// Test remove with non-existent node key returns false
TEST_F(NodeTest_260, RemoveWithNonExistentNodeKeyReturnsFalse_260) {
  node n;
  n.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("nonexistent_node_key");

  bool removed = n.remove(key, pMemory);
  EXPECT_FALSE(removed);
}

// Test set_ref copies another node's reference
TEST_F(NodeTest_260, SetRefCopiesReference_260) {
  node n1;
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("original");

  node n2;
  n2.set_ref(n1);

  EXPECT_EQ(n2.type(), NodeType::Scalar);
  EXPECT_EQ(n2.scalar(), "original");
}

// Test set_data copies another node's data
TEST_F(NodeTest_260, SetDataCopiesData_260) {
  node n1;
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("data_source");

  node n2;
  n2.set_data(n1);

  EXPECT_EQ(n2.type(), NodeType::Scalar);
  EXPECT_EQ(n2.scalar(), "data_source");
}

// Test ref() returns non-null pointer
TEST_F(NodeTest_260, RefReturnsNonNull_260) {
  node n;
  EXPECT_NE(n.ref(), nullptr);
}

// Test set_mark and mark retrieval
TEST_F(NodeTest_260, SetAndGetMark_260) {
  node n;
  Mark m;
  m.line = 5;
  m.column = 10;
  n.set_mark(m);

  const Mark& retrieved = n.mark();
  EXPECT_EQ(retrieved.line, 5);
  EXPECT_EQ(retrieved.column, 10);
}

// Test equals with string
TEST_F(NodeTest_260, EqualsWithString_260) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("test_value");

  EXPECT_TRUE(n.equals(std::string("test_value"), pMemory));
  EXPECT_FALSE(n.equals(std::string("other_value"), pMemory));
}

// Test equals with const char*
TEST_F(NodeTest_260, EqualsWithConstChar_260) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");

  EXPECT_TRUE(n.equals("hello", pMemory));
  EXPECT_FALSE(n.equals("world", pMemory));
}

// Test begin/end for empty sequence
TEST_F(NodeTest_260, BeginEqualsEndForEmptySequence_260) {
  node n;
  n.set_type(NodeType::Sequence);

  EXPECT_TRUE(n.begin() == n.end());
}

// Test begin/end for non-empty sequence
TEST_F(NodeTest_260, BeginNotEqualsEndForNonEmptySequence_260) {
  node n;
  n.set_type(NodeType::Sequence);

  node& child = pMemory->create_node();
  child.set_scalar("item");
  n.push_back(child, pMemory);

  EXPECT_FALSE(n.begin() == n.end());
}

// Test empty map size
TEST_F(NodeTest_260, EmptyMapHasSizeZero_260) {
  node n;
  n.set_type(NodeType::Map);
  EXPECT_EQ(n.size(), 0u);
}

// Test multiple insert into map
TEST_F(NodeTest_260, MultipleInsertIntoMap_260) {
  node n;
  n.set_type(NodeType::Map);

  node& key1 = pMemory->create_node();
  key1.set_scalar("key1");
  node& val1 = pMemory->create_node();
  val1.set_scalar("val1");
  n.insert(key1, val1, pMemory);

  node& key2 = pMemory->create_node();
  key2.set_scalar("key2");
  node& val2 = pMemory->create_node();
  val2.set_scalar("val2");
  n.insert(key2, val2, pMemory);

  EXPECT_EQ(n.size(), 2u);
}

// Test get with node key
TEST_F(NodeTest_260, GetWithNodeKey_260) {
  node n;
  n.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("nkey");
  node& val = pMemory->create_node();
  val.set_scalar("nval");
  n.insert(key, val, pMemory);

  node* result = n.get(key, pMemory);
  EXPECT_NE(result, nullptr);
  EXPECT_EQ(result->scalar(), "nval");
}

// Test scalar on empty/undefined node (boundary)
TEST_F(NodeTest_260, SetScalarOverwrite_260) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("first");
  EXPECT_EQ(n.scalar(), "first");

  n.set_scalar("second");
  EXPECT_EQ(n.scalar(), "second");
}

// Test changing type from Scalar to Map
TEST_F(NodeTest_260, ChangeTypeFromScalarToMap_260) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("value");
  EXPECT_EQ(n.type(), NodeType::Scalar);

  n.set_type(NodeType::Map);
  EXPECT_EQ(n.type(), NodeType::Map);
}

// Test set_null after setting scalar
TEST_F(NodeTest_260, SetNullAfterScalar_260) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("something");
  n.set_null();
  EXPECT_EQ(n.type(), NodeType::Null);
}

// Test force_insert into map
TEST_F(NodeTest_260, ForceInsertIntoMap_260) {
  node n;
  n.set_type(NodeType::Map);

  n.force_insert(std::string("fkey"), std::string("fval"), pMemory);
  EXPECT_EQ(n.size(), 1u);

  node* result = n.get(std::string("fkey"), pMemory);
  EXPECT_NE(result, nullptr);
}

// Test empty tag by default
TEST_F(NodeTest_260, DefaultTagIsEmpty_260) {
  node n;
  EXPECT_EQ(n.tag(), "");
}

// Test add_dependency does not change type
TEST_F(NodeTest_260, AddDependencyDoesNotChangeType_260) {
  node n1;
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("parent");

  node n2;
  n2.set_type(NodeType::Scalar);
  n2.set_scalar("child");

  n1.add_dependency(n2);
  EXPECT_EQ(n1.type(), NodeType::Scalar);
  EXPECT_EQ(n1.scalar(), "parent");
}

// Test remove after insert and re-get returns null
TEST_F(NodeTest_260, RemoveThenGetReturnsNull_260) {
  node n;
  n.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("tempkey");
  node& val = pMemory->create_node();
  val.set_scalar("tempval");
  n.insert(key, val, pMemory);

  EXPECT_NE(n.get(std::string("tempkey"), pMemory), nullptr);

  bool removed = n.remove(std::string("tempkey"), pMemory);
  EXPECT_TRUE(removed);

  node* result = n.get(std::string("tempkey"), pMemory);
  EXPECT_EQ(result, nullptr);
}

// Test remove twice returns false on second attempt
TEST_F(NodeTest_260, RemoveTwiceReturnsFalseOnSecond_260) {
  node n;
  n.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("doubleremove");
  node& val = pMemory->create_node();
  val.set_scalar("val");
  n.insert(key, val, pMemory);

  EXPECT_TRUE(n.remove(std::string("doubleremove"), pMemory));
  EXPECT_FALSE(n.remove(std::string("doubleremove"), pMemory));
}

}  // namespace detail
}  // namespace YAML
