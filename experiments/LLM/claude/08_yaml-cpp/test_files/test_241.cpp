#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeTest_241 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = create_shared_memory();
  }

  shared_memory_holder pMemory;
};

// Test default construction - node should not be defined initially
TEST_F(NodeTest_241, DefaultConstructionIsNotDefined_241) {
  node n;
  EXPECT_FALSE(n.is_defined());
}

// Test default construction - type should be Undefined
TEST_F(NodeTest_241, DefaultConstructionTypeIsUndefined_241) {
  node n;
  EXPECT_EQ(NodeType::Undefined, n.type());
}

// Test scalar on a default node
TEST_F(NodeTest_241, DefaultNodeScalarIsEmpty_241) {
  node n;
  EXPECT_TRUE(n.scalar().empty());
}

// Test tag on a default node
TEST_F(NodeTest_241, DefaultNodeTagIsEmpty_241) {
  node n;
  EXPECT_TRUE(n.tag().empty());
}

// Test set_scalar and retrieve scalar
TEST_F(NodeTest_241, SetScalarAndRetrieve_241) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");
  EXPECT_EQ("hello", n.scalar());
}

// Test set_type to Scalar
TEST_F(NodeTest_241, SetTypeScalar_241) {
  node n;
  n.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, n.type());
}

// Test set_type to Sequence
TEST_F(NodeTest_241, SetTypeSequence_241) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
}

// Test set_type to Map
TEST_F(NodeTest_241, SetTypeMap_241) {
  node n;
  n.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, n.type());
}

// Test set_null
TEST_F(NodeTest_241, SetNull_241) {
  node n;
  n.set_null();
  EXPECT_EQ(NodeType::Null, n.type());
}

// Test mark_defined
TEST_F(NodeTest_241, MarkDefined_241) {
  node n;
  EXPECT_FALSE(n.is_defined());
  n.mark_defined();
  EXPECT_TRUE(n.is_defined());
}

// Test set_tag and retrieve tag
TEST_F(NodeTest_241, SetTagAndRetrieve_241) {
  node n;
  n.set_tag("!mytag");
  EXPECT_EQ("!mytag", n.tag());
}

// Test set_style and retrieve style
TEST_F(NodeTest_241, SetStyleAndRetrieve_241) {
  node n;
  n.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, n.style());
}

// Test default style
TEST_F(NodeTest_241, DefaultStyle_241) {
  node n;
  EXPECT_EQ(EmitterStyle::Default, n.style());
}

// Test is() - same node
TEST_F(NodeTest_241, IsSameNode_241) {
  node n;
  EXPECT_TRUE(n.is(n));
}

// Test is() - different nodes
TEST_F(NodeTest_241, IsDifferentNodes_241) {
  node n1;
  node n2;
  EXPECT_FALSE(n1.is(n2));
}

// Test ref() is not null
TEST_F(NodeTest_241, RefIsNotNull_241) {
  node n;
  EXPECT_NE(nullptr, n.ref());
}

// Test size of default node
TEST_F(NodeTest_241, DefaultNodeSizeIsZero_241) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(0u, n.size());
}

// Test push_back increases size
TEST_F(NodeTest_241, PushBackIncreasesSize_241) {
  node n;
  n.set_type(NodeType::Sequence);
  
  node& child = pMemory->create_node();
  child.set_type(NodeType::Scalar);
  child.set_scalar("item1");
  
  n.push_back(child, pMemory);
  EXPECT_EQ(1u, n.size());
}

// Test push_back multiple items
TEST_F(NodeTest_241, PushBackMultipleItems_241) {
  node n;
  n.set_type(NodeType::Sequence);
  
  node& child1 = pMemory->create_node();
  child1.set_type(NodeType::Scalar);
  child1.set_scalar("item1");
  
  node& child2 = pMemory->create_node();
  child2.set_type(NodeType::Scalar);
  child2.set_scalar("item2");
  
  n.push_back(child1, pMemory);
  n.push_back(child2, pMemory);
  EXPECT_EQ(2u, n.size());
}

// Test set_data copies data from another node
TEST_F(NodeTest_241, SetDataCopiesFromAnotherNode_241) {
  node n1;
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("source");
  
  node n2;
  n2.set_data(n1);
  EXPECT_EQ("source", n2.scalar());
  EXPECT_EQ(NodeType::Scalar, n2.type());
}

// Test set_ref makes node reference another node's ref
TEST_F(NodeTest_241, SetRefSharesRef_241) {
  node n1;
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("shared");
  
  node n2;
  n2.set_ref(n1);
  EXPECT_EQ("shared", n2.scalar());
}

// Test set_mark
TEST_F(NodeTest_241, SetMark_241) {
  node n;
  Mark m;
  m.line = 10;
  m.column = 5;
  m.pos = 100;
  n.set_mark(m);
  
  const Mark& retrieved = n.mark();
  EXPECT_EQ(10, retrieved.line);
  EXPECT_EQ(5, retrieved.column);
  EXPECT_EQ(100, retrieved.pos);
}

// Test equals with matching scalar
TEST_F(NodeTest_241, EqualsMatchingScalar_241) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("test");
  
  EXPECT_TRUE(n.equals(std::string("test"), pMemory));
}

// Test equals with non-matching scalar
TEST_F(NodeTest_241, EqualsNonMatchingScalar_241) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("test");
  
  EXPECT_FALSE(n.equals(std::string("other"), pMemory));
}

// Test equals with const char*
TEST_F(NodeTest_241, EqualsConstCharPtr_241) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");
  
  EXPECT_TRUE(n.equals("hello", pMemory));
  EXPECT_FALSE(n.equals("world", pMemory));
}

// Test insert into map
TEST_F(NodeTest_241, InsertIntoMap_241) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_type(NodeType::Scalar);
  key.set_scalar("key1");
  
  node& value = pMemory->create_node();
  value.set_type(NodeType::Scalar);
  value.set_scalar("value1");
  
  n.insert(key, value, pMemory);
  EXPECT_EQ(1u, n.size());
}

// Test get from map with string key
TEST_F(NodeTest_241, GetFromMapWithStringKey_241) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_type(NodeType::Scalar);
  key.set_scalar("mykey");
  
  node& value = pMemory->create_node();
  value.set_type(NodeType::Scalar);
  value.set_scalar("myvalue");
  
  n.insert(key, value, pMemory);
  
  node* result = n.get(std::string("mykey"), pMemory);
  ASSERT_NE(nullptr, result);
  EXPECT_EQ("myvalue", result->scalar());
}

// Test get returns null for non-existent key
TEST_F(NodeTest_241, GetReturnsNullForNonExistentKey_241) {
  node n;
  n.set_type(NodeType::Map);
  
  node* result = n.get(std::string("nonexistent"), pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test remove from map
TEST_F(NodeTest_241, RemoveFromMap_241) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_type(NodeType::Scalar);
  key.set_scalar("removekey");
  
  node& value = pMemory->create_node();
  value.set_type(NodeType::Scalar);
  value.set_scalar("removevalue");
  
  n.insert(key, value, pMemory);
  EXPECT_EQ(1u, n.size());
  
  bool removed = n.remove(std::string("removekey"), pMemory);
  EXPECT_TRUE(removed);
}

// Test remove non-existent key returns false
TEST_F(NodeTest_241, RemoveNonExistentKeyReturnsFalse_241) {
  node n;
  n.set_type(NodeType::Map);
  
  bool removed = n.remove(std::string("nokey"), pMemory);
  EXPECT_FALSE(removed);
}

// Test begin/end iterators on empty sequence
TEST_F(NodeTest_241, BeginEqualsEndOnEmptySequence_241) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(n.begin(), n.end());
}

// Test begin/end iterators on non-empty sequence
TEST_F(NodeTest_241, BeginNotEqualsEndOnNonEmptySequence_241) {
  node n;
  n.set_type(NodeType::Sequence);
  
  node& child = pMemory->create_node();
  child.set_type(NodeType::Scalar);
  child.set_scalar("item");
  
  n.push_back(child, pMemory);
  EXPECT_NE(n.begin(), n.end());
}

// Test set_scalar with empty string
TEST_F(NodeTest_241, SetScalarEmptyString_241) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("");
  EXPECT_EQ("", n.scalar());
}

// Test set_scalar with very long string
TEST_F(NodeTest_241, SetScalarLongString_241) {
  node n;
  n.set_type(NodeType::Scalar);
  std::string longStr(10000, 'x');
  n.set_scalar(longStr);
  EXPECT_EQ(longStr, n.scalar());
}

// Test changing type from Scalar to Map
TEST_F(NodeTest_241, ChangeTypeFromScalarToMap_241) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");
  
  n.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, n.type());
}

// Test set_style with Block style
TEST_F(NodeTest_241, SetStyleBlock_241) {
  node n;
  n.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, n.style());
}

// Test force_insert into map
TEST_F(NodeTest_241, ForceInsertIntoMap_241) {
  node n;
  n.set_type(NodeType::Map);
  
  n.force_insert(std::string("fkey"), std::string("fvalue"), pMemory);
  EXPECT_EQ(1u, n.size());
}

// Test remove with node key
TEST_F(NodeTest_241, RemoveWithNodeKey_241) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_type(NodeType::Scalar);
  key.set_scalar("nodekey");
  
  node& value = pMemory->create_node();
  value.set_type(NodeType::Scalar);
  value.set_scalar("nodevalue");
  
  n.insert(key, value, pMemory);
  
  bool removed = n.remove(key, pMemory);
  EXPECT_TRUE(removed);
}

// Test get with node key
TEST_F(NodeTest_241, GetWithNodeKey_241) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_type(NodeType::Scalar);
  key.set_scalar("nkey");
  
  node& value = pMemory->create_node();
  value.set_type(NodeType::Scalar);
  value.set_scalar("nvalue");
  
  n.insert(key, value, pMemory);
  
  node* result = n.get(key, pMemory);
  ASSERT_NE(nullptr, result);
  EXPECT_EQ("nvalue", result->scalar());
}

// Test set_type to Null
TEST_F(NodeTest_241, SetTypeNull_241) {
  node n;
  n.set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, n.type());
}

// Test that two separately created nodes are not the same
TEST_F(NodeTest_241, TwoCreatedNodesAreNotSame_241) {
  node& n1 = pMemory->create_node();
  node& n2 = pMemory->create_node();
  EXPECT_FALSE(n1.is(n2));
}

// Test set_tag with empty string
TEST_F(NodeTest_241, SetTagEmptyString_241) {
  node n;
  n.set_tag("");
  EXPECT_EQ("", n.tag());
}

// Test mark defaults
TEST_F(NodeTest_241, DefaultMark_241) {
  node n;
  const Mark& m = n.mark();
  EXPECT_EQ(Mark::null_mark().line, m.line);
  EXPECT_EQ(Mark::null_mark().column, m.column);
  EXPECT_EQ(Mark::null_mark().pos, m.pos);
}

}  // namespace detail
}  // namespace YAML
