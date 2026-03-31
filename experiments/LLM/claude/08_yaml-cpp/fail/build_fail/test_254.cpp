#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeTest_254 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = std::make_shared<memory>();
  }

  shared_memory_holder pMemory;
};

// Test default construction - node should be undefined with Undefined type
TEST_F(NodeTest_254, DefaultConstruction_254) {
  node n;
  EXPECT_FALSE(n.is_defined());
  EXPECT_EQ(NodeType::Undefined, n.type());
}

// Test size returns 0 for a default (undefined) node
TEST_F(NodeTest_254, DefaultNodeSizeIsZero_254) {
  node n;
  EXPECT_EQ(0u, n.size());
}

// Test is() method - node is itself
TEST_F(NodeTest_254, NodeIsSelf_254) {
  node n;
  EXPECT_TRUE(n.is(n));
}

// Test is() method - two different nodes are not the same
TEST_F(NodeTest_254, DifferentNodesAreNotSame_254) {
  node n1;
  node n2;
  EXPECT_FALSE(n1.is(n2));
}

// Test mark_defined makes the node defined
TEST_F(NodeTest_254, MarkDefined_254) {
  node n;
  EXPECT_FALSE(n.is_defined());
  n.mark_defined();
  EXPECT_TRUE(n.is_defined());
}

// Test set_type to Scalar
TEST_F(NodeTest_254, SetTypeScalar_254) {
  node n;
  n.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, n.type());
}

// Test set_type to Sequence
TEST_F(NodeTest_254, SetTypeSequence_254) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
}

// Test set_type to Map
TEST_F(NodeTest_254, SetTypeMap_254) {
  node n;
  n.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, n.type());
}

// Test set_type to Null
TEST_F(NodeTest_254, SetTypeNull_254) {
  node n;
  n.set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, n.type());
}

// Test set_null
TEST_F(NodeTest_254, SetNull_254) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");
  n.set_null();
  EXPECT_EQ(NodeType::Null, n.type());
}

// Test set_scalar and scalar retrieval
TEST_F(NodeTest_254, SetAndGetScalar_254) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("test_value");
  EXPECT_EQ("test_value", n.scalar());
}

// Test set_scalar with empty string
TEST_F(NodeTest_254, SetEmptyScalar_254) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("");
  EXPECT_EQ("", n.scalar());
}

// Test set_tag and tag retrieval
TEST_F(NodeTest_254, SetAndGetTag_254) {
  node n;
  n.set_tag("!custom_tag");
  EXPECT_EQ("!custom_tag", n.tag());
}

// Test set_tag with empty string
TEST_F(NodeTest_254, SetEmptyTag_254) {
  node n;
  n.set_tag("");
  EXPECT_EQ("", n.tag());
}

// Test set_style and style retrieval
TEST_F(NodeTest_254, SetAndGetStyleBlock_254) {
  node n;
  n.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, n.style());
}

TEST_F(NodeTest_254, SetAndGetStyleFlow_254) {
  node n;
  n.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, n.style());
}

TEST_F(NodeTest_254, SetAndGetStyleDefault_254) {
  node n;
  n.set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, n.style());
}

// Test set_mark and mark retrieval
TEST_F(NodeTest_254, SetAndGetMark_254) {
  node n;
  Mark m;
  m.line = 5;
  m.column = 10;
  m.pos = 42;
  n.set_mark(m);
  const Mark& retrieved = n.mark();
  EXPECT_EQ(5, retrieved.line);
  EXPECT_EQ(10, retrieved.column);
  EXPECT_EQ(42u, retrieved.pos);
}

// Test ref() returns non-null
TEST_F(NodeTest_254, RefNotNull_254) {
  node n;
  EXPECT_NE(nullptr, n.ref());
}

// Test push_back on a sequence and size increases
TEST_F(NodeTest_254, PushBackIncreasesSize_254) {
  node n;
  n.set_type(NodeType::Sequence);
  
  node& child = pMemory->create_node();
  child.set_type(NodeType::Scalar);
  child.set_scalar("item1");
  
  n.push_back(child, pMemory);
  EXPECT_EQ(1u, n.size());
}

// Test push_back multiple items
TEST_F(NodeTest_254, PushBackMultipleItems_254) {
  node n;
  n.set_type(NodeType::Sequence);
  
  node& child1 = pMemory->create_node();
  child1.set_type(NodeType::Scalar);
  child1.set_scalar("item1");
  
  node& child2 = pMemory->create_node();
  child2.set_type(NodeType::Scalar);
  child2.set_scalar("item2");
  
  node& child3 = pMemory->create_node();
  child3.set_type(NodeType::Scalar);
  child3.set_scalar("item3");
  
  n.push_back(child1, pMemory);
  n.push_back(child2, pMemory);
  n.push_back(child3, pMemory);
  EXPECT_EQ(3u, n.size());
}

// Test insert into map increases size
TEST_F(NodeTest_254, InsertIntoMapIncreasesSize_254) {
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

// Test insert multiple pairs into map
TEST_F(NodeTest_254, InsertMultiplePairsIntoMap_254) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key1 = pMemory->create_node();
  key1.set_type(NodeType::Scalar);
  key1.set_scalar("key1");
  node& val1 = pMemory->create_node();
  val1.set_type(NodeType::Scalar);
  val1.set_scalar("val1");
  
  node& key2 = pMemory->create_node();
  key2.set_type(NodeType::Scalar);
  key2.set_scalar("key2");
  node& val2 = pMemory->create_node();
  val2.set_type(NodeType::Scalar);
  val2.set_scalar("val2");
  
  n.insert(key1, val1, pMemory);
  n.insert(key2, val2, pMemory);
  EXPECT_EQ(2u, n.size());
}

// Test get on a map with string key
TEST_F(NodeTest_254, GetStringKeyFromMap_254) {
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
  EXPECT_NE(nullptr, result);
  EXPECT_EQ("myvalue", result->scalar());
}

// Test get returns nullptr for non-existent key
TEST_F(NodeTest_254, GetNonExistentKeyReturnsNull_254) {
  node n;
  n.set_type(NodeType::Map);
  
  node* result = n.get(std::string("nonexistent"), pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test remove from map
TEST_F(NodeTest_254, RemoveFromMap_254) {
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
TEST_F(NodeTest_254, RemoveNonExistentKeyReturnsFalse_254) {
  node n;
  n.set_type(NodeType::Map);
  
  bool removed = n.remove(std::string("nonexistent"), pMemory);
  EXPECT_FALSE(removed);
}

// Test set_data copies data from another node
TEST_F(NodeTest_254, SetDataCopiesFromOtherNode_254) {
  node n1;
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("original");
  
  node n2;
  n2.set_data(n1);
  EXPECT_EQ(NodeType::Scalar, n2.type());
  EXPECT_EQ("original", n2.scalar());
}

// Test set_ref makes node share ref with another
TEST_F(NodeTest_254, SetRefSharesReference_254) {
  node n1;
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("shared");
  
  node n2;
  n2.set_ref(n1);
  EXPECT_EQ("shared", n2.scalar());
  EXPECT_EQ(NodeType::Scalar, n2.type());
}

// Test equals with string
TEST_F(NodeTest_254, EqualsString_254) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");
  
  EXPECT_TRUE(n.equals(std::string("hello"), pMemory));
  EXPECT_FALSE(n.equals(std::string("world"), pMemory));
}

// Test equals with const char*
TEST_F(NodeTest_254, EqualsConstCharPtr_254) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");
  
  EXPECT_TRUE(n.equals("hello", pMemory));
  EXPECT_FALSE(n.equals("world", pMemory));
}

// Test begin and end iterators on empty sequence
TEST_F(NodeTest_254, EmptySequenceBeginEqualsEnd_254) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(n.begin(), n.end());
}

// Test begin and end iterators on non-empty sequence
TEST_F(NodeTest_254, NonEmptySequenceBeginNotEqualsEnd_254) {
  node n;
  n.set_type(NodeType::Sequence);
  
  node& child = pMemory->create_node();
  child.set_type(NodeType::Scalar);
  child.set_scalar("item");
  
  n.push_back(child, pMemory);
  EXPECT_NE(n.begin(), n.end());
}

// Test force_insert
TEST_F(NodeTest_254, ForceInsert_254) {
  node n;
  n.set_type(NodeType::Map);
  
  n.force_insert(std::string("fkey"), std::string("fvalue"), pMemory);
  EXPECT_EQ(1u, n.size());
}

// Test add_dependency doesn't change type or size
TEST_F(NodeTest_254, AddDependencyDoesNotChangeNode_254) {
  node n1;
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("main");
  
  node n2;
  n2.set_type(NodeType::Scalar);
  n2.set_scalar("dep");
  
  n1.add_dependency(n2);
  // Adding dependency should not change the node's observable state
  EXPECT_EQ(NodeType::Scalar, n1.type());
  EXPECT_EQ("main", n1.scalar());
}

// Test changing type from Sequence to Map
TEST_F(NodeTest_254, ChangeTypeFromSequenceToMap_254) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
  
  n.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, n.type());
}

// Test size of undefined node
TEST_F(NodeTest_254, UndefinedNodeSize_254) {
  node n;
  EXPECT_EQ(0u, n.size());
}

// Test size of null node
TEST_F(NodeTest_254, NullNodeSize_254) {
  node n;
  n.set_null();
  EXPECT_EQ(0u, n.size());
}

// Test scalar on a scalar node with special characters
TEST_F(NodeTest_254, ScalarWithSpecialCharacters_254) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello\nworld\ttab");
  EXPECT_EQ("hello\nworld\ttab", n.scalar());
}

// Test overwriting scalar
TEST_F(NodeTest_254, OverwriteScalar_254) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("first");
  EXPECT_EQ("first", n.scalar());
  
  n.set_scalar("second");
  EXPECT_EQ("second", n.scalar());
}

// Test overwriting tag
TEST_F(NodeTest_254, OverwriteTag_254) {
  node n;
  n.set_tag("!first");
  EXPECT_EQ("!first", n.tag());
  
  n.set_tag("!second");
  EXPECT_EQ("!second", n.tag());
}

// Test get with node key
TEST_F(NodeTest_254, GetWithNodeKey_254) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_type(NodeType::Scalar);
  key.set_scalar("nodekey");
  
  node& value = pMemory->create_node();
  value.set_type(NodeType::Scalar);
  value.set_scalar("nodevalue");
  
  n.insert(key, value, pMemory);
  
  node* result = n.get(key, pMemory);
  EXPECT_NE(nullptr, result);
  EXPECT_EQ("nodevalue", result->scalar());
}

// Test remove with node key
TEST_F(NodeTest_254, RemoveWithNodeKey_254) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_type(NodeType::Scalar);
  key.set_scalar("toremove");
  
  node& value = pMemory->create_node();
  value.set_type(NodeType::Scalar);
  value.set_scalar("val");
  
  n.insert(key, value, pMemory);
  EXPECT_EQ(1u, n.size());
  
  bool removed = n.remove(key, pMemory);
  EXPECT_TRUE(removed);
}

// Test remove with non-existent node key
TEST_F(NodeTest_254, RemoveNonExistentNodeKey_254) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_type(NodeType::Scalar);
  key.set_scalar("nonexistent");
  
  bool removed = n.remove(key, pMemory);
  EXPECT_FALSE(removed);
}

// Test default mark values
TEST_F(NodeTest_254, DefaultMarkValues_254) {
  node n;
  const Mark& m = n.mark();
  // Default mark should have line and column as -1 (Mark::null_mark equivalent)
  // This is implementation-dependent but we check it's accessible
  (void)m.line;
  (void)m.column;
  (void)m.pos;
}

}  // namespace detail
}  // namespace YAML
