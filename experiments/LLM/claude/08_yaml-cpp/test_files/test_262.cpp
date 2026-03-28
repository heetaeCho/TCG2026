#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeTest_262 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = create_shared_memory();
  }

  shared_memory_holder pMemory;
};

// Test default construction - node should not be defined initially
TEST_F(NodeTest_262, DefaultConstructionIsNotDefined_262) {
  node n;
  EXPECT_FALSE(n.is_defined());
}

// Test default construction - type should be Undefined
TEST_F(NodeTest_262, DefaultConstructionTypeUndefined_262) {
  node n;
  EXPECT_EQ(NodeType::Undefined, n.type());
}

// Test mark_defined makes node defined
TEST_F(NodeTest_262, MarkDefinedMakesNodeDefined_262) {
  node n;
  n.mark_defined();
  EXPECT_TRUE(n.is_defined());
}

// Test set_null sets type to Null
TEST_F(NodeTest_262, SetNullSetsTypeToNull_262) {
  node n;
  n.set_null();
  EXPECT_EQ(NodeType::Null, n.type());
}

// Test set_scalar sets scalar value
TEST_F(NodeTest_262, SetScalarSetsValue_262) {
  node n;
  n.set_scalar("hello");
  EXPECT_EQ("hello", n.scalar());
  EXPECT_EQ(NodeType::Scalar, n.type());
}

// Test set_scalar with empty string
TEST_F(NodeTest_262, SetScalarEmptyString_262) {
  node n;
  n.set_scalar("");
  EXPECT_EQ("", n.scalar());
  EXPECT_EQ(NodeType::Scalar, n.type());
}

// Test set_type to Sequence
TEST_F(NodeTest_262, SetTypeSequence_262) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
}

// Test set_type to Map
TEST_F(NodeTest_262, SetTypeMap_262) {
  node n;
  n.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, n.type());
}

// Test set_tag and get tag
TEST_F(NodeTest_262, SetTagAndGetTag_262) {
  node n;
  n.set_tag("!custom");
  EXPECT_EQ("!custom", n.tag());
}

// Test set_tag with empty string
TEST_F(NodeTest_262, SetTagEmptyString_262) {
  node n;
  n.set_tag("");
  EXPECT_EQ("", n.tag());
}

// Test set_style and get style
TEST_F(NodeTest_262, SetStyleAndGetStyle_262) {
  node n;
  n.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, n.style());
}

// Test set_style Block
TEST_F(NodeTest_262, SetStyleBlock_262) {
  node n;
  n.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, n.style());
}

// Test is() - same node
TEST_F(NodeTest_262, IsSameNode_262) {
  node n;
  EXPECT_TRUE(n.is(n));
}

// Test is() - different nodes
TEST_F(NodeTest_262, IsDifferentNodes_262) {
  node n1;
  node n2;
  EXPECT_FALSE(n1.is(n2));
}

// Test ref() returns non-null
TEST_F(NodeTest_262, RefReturnsNonNull_262) {
  node n;
  EXPECT_NE(nullptr, n.ref());
}

// Test size of empty node
TEST_F(NodeTest_262, SizeOfEmptyNode_262) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(0u, n.size());
}

// Test push_back increases size for sequence
TEST_F(NodeTest_262, PushBackIncreasesSize_262) {
  node seq;
  seq.set_type(NodeType::Sequence);
  
  node& child = pMemory->create_node();
  child.set_scalar("item1");
  
  seq.push_back(child, pMemory);
  EXPECT_EQ(1u, seq.size());
}

// Test push_back multiple items
TEST_F(NodeTest_262, PushBackMultipleItems_262) {
  node seq;
  seq.set_type(NodeType::Sequence);
  
  node& child1 = pMemory->create_node();
  child1.set_scalar("item1");
  node& child2 = pMemory->create_node();
  child2.set_scalar("item2");
  node& child3 = pMemory->create_node();
  child3.set_scalar("item3");
  
  seq.push_back(child1, pMemory);
  seq.push_back(child2, pMemory);
  seq.push_back(child3, pMemory);
  EXPECT_EQ(3u, seq.size());
}

// Test insert into map
TEST_F(NodeTest_262, InsertIntoMap_262) {
  node map;
  map.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("key1");
  node& value = pMemory->create_node();
  value.set_scalar("value1");
  
  map.insert(key, value, pMemory);
  EXPECT_EQ(1u, map.size());
}

// Test get with string key on map
TEST_F(NodeTest_262, GetStringKeyFromMap_262) {
  node map;
  map.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("mykey");
  node& value = pMemory->create_node();
  value.set_scalar("myvalue");
  
  map.insert(key, value, pMemory);
  
  node* result = map.get(std::string("mykey"), pMemory);
  EXPECT_NE(nullptr, result);
  EXPECT_EQ("myvalue", result->scalar());
}

// Test get with non-existing key returns null
TEST_F(NodeTest_262, GetNonExistingKeyReturnsNull_262) {
  node map;
  map.set_type(NodeType::Map);
  
  node* result = map.get(std::string("nonexistent"), pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test remove with string key
TEST_F(NodeTest_262, RemoveStringKeyFromMap_262) {
  node map;
  map.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("removekey");
  node& value = pMemory->create_node();
  value.set_scalar("removevalue");
  
  map.insert(key, value, pMemory);
  EXPECT_EQ(1u, map.size());
  
  bool removed = map.remove(std::string("removekey"), pMemory);
  EXPECT_TRUE(removed);
}

// Test remove non-existing key returns false
TEST_F(NodeTest_262, RemoveNonExistingKeyReturnsFalse_262) {
  node map;
  map.set_type(NodeType::Map);
  
  bool removed = map.remove(std::string("nonexistent"), pMemory);
  EXPECT_FALSE(removed);
}

// Test remove with node key
TEST_F(NodeTest_262, RemoveNodeKeyFromMap_262) {
  node map;
  map.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("nodekey");
  node& value = pMemory->create_node();
  value.set_scalar("nodevalue");
  
  map.insert(key, value, pMemory);
  EXPECT_EQ(1u, map.size());
  
  bool removed = map.remove(key, pMemory);
  EXPECT_TRUE(removed);
}

// Test remove with node key that doesn't exist
TEST_F(NodeTest_262, RemoveNonExistingNodeKeyReturnsFalse_262) {
  node map;
  map.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("nonexistent_node_key");
  
  bool removed = map.remove(key, pMemory);
  EXPECT_FALSE(removed);
}

// Test get with node key
TEST_F(NodeTest_262, GetNodeKeyFromMap_262) {
  node map;
  map.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("nodekey");
  node& value = pMemory->create_node();
  value.set_scalar("nodevalue");
  
  map.insert(key, value, pMemory);
  
  node* result = map.get(key, pMemory);
  EXPECT_NE(nullptr, result);
  EXPECT_EQ("nodevalue", result->scalar());
}

// Test set_data copies data from another node
TEST_F(NodeTest_262, SetDataCopiesFromAnotherNode_262) {
  node src;
  src.set_scalar("source_data");
  src.set_tag("!src_tag");
  
  node dst;
  dst.set_data(src);
  
  EXPECT_EQ("source_data", dst.scalar());
  EXPECT_EQ("!src_tag", dst.tag());
}

// Test set_mark sets the mark
TEST_F(NodeTest_262, SetMarkSetsNodeMark_262) {
  node n;
  Mark m;
  m.line = 10;
  m.column = 20;
  m.pos = 30;
  n.set_mark(m);
  
  const Mark& result = n.mark();
  EXPECT_EQ(10, result.line);
  EXPECT_EQ(20, result.column);
  EXPECT_EQ(30, result.pos);
}

// Test equals with matching scalar
TEST_F(NodeTest_262, EqualsMatchingScalar_262) {
  node n;
  n.set_scalar("test");
  
  EXPECT_TRUE(n.equals(std::string("test"), pMemory));
}

// Test equals with non-matching scalar
TEST_F(NodeTest_262, EqualsNonMatchingScalar_262) {
  node n;
  n.set_scalar("test");
  
  EXPECT_FALSE(n.equals(std::string("other"), pMemory));
}

// Test equals with const char*
TEST_F(NodeTest_262, EqualsConstCharPointer_262) {
  node n;
  n.set_scalar("hello");
  
  EXPECT_TRUE(n.equals("hello", pMemory));
}

// Test equals with non-matching const char*
TEST_F(NodeTest_262, EqualsNonMatchingConstCharPointer_262) {
  node n;
  n.set_scalar("hello");
  
  EXPECT_FALSE(n.equals("world", pMemory));
}

// Test begin/end iterators on empty sequence
TEST_F(NodeTest_262, BeginEndOnEmptySequence_262) {
  node seq;
  seq.set_type(NodeType::Sequence);
  
  EXPECT_EQ(seq.begin(), seq.end());
}

// Test begin/end iterators on non-empty sequence
TEST_F(NodeTest_262, BeginEndOnNonEmptySequence_262) {
  node seq;
  seq.set_type(NodeType::Sequence);
  
  node& child = pMemory->create_node();
  child.set_scalar("item");
  seq.push_back(child, pMemory);
  
  EXPECT_NE(seq.begin(), seq.end());
}

// Test set_ref makes node reference another
TEST_F(NodeTest_262, SetRefReferencesAnotherNode_262) {
  node src;
  src.set_scalar("referenced");
  
  node dst;
  dst.set_ref(src);
  
  EXPECT_EQ("referenced", dst.scalar());
  EXPECT_EQ(NodeType::Scalar, dst.type());
}

// Test multiple inserts into map
TEST_F(NodeTest_262, MultipleInsertsIntoMap_262) {
  node map;
  map.set_type(NodeType::Map);
  
  for (int i = 0; i < 5; i++) {
    node& key = pMemory->create_node();
    key.set_scalar("key" + std::to_string(i));
    node& value = pMemory->create_node();
    value.set_scalar("value" + std::to_string(i));
    map.insert(key, value, pMemory);
  }
  
  EXPECT_EQ(5u, map.size());
}

// Test force_insert into map
TEST_F(NodeTest_262, ForceInsertIntoMap_262) {
  node map;
  map.set_type(NodeType::Map);
  
  map.force_insert(std::string("fkey"), std::string("fvalue"), pMemory);
  EXPECT_EQ(1u, map.size());
}

// Test size of empty map
TEST_F(NodeTest_262, SizeOfEmptyMap_262) {
  node map;
  map.set_type(NodeType::Map);
  EXPECT_EQ(0u, map.size());
}

// Test changing type from Scalar to Sequence
TEST_F(NodeTest_262, ChangeTypeScalarToSequence_262) {
  node n;
  n.set_scalar("value");
  EXPECT_EQ(NodeType::Scalar, n.type());
  
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
}

// Test changing type from Sequence to Map
TEST_F(NodeTest_262, ChangeTypeSequenceToMap_262) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
  
  n.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, n.type());
}

// Test default style
TEST_F(NodeTest_262, DefaultStyleIsDefault_262) {
  node n;
  EXPECT_EQ(EmitterStyle::Default, n.style());
}

// Test remove after insert and then get returns null
TEST_F(NodeTest_262, RemoveThenGetReturnsNull_262) {
  node map;
  map.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("tempkey");
  node& value = pMemory->create_node();
  value.set_scalar("tempvalue");
  
  map.insert(key, value, pMemory);
  EXPECT_NE(nullptr, map.get(std::string("tempkey"), pMemory));
  
  bool removed = map.remove(std::string("tempkey"), pMemory);
  EXPECT_TRUE(removed);
  
  node* result = map.get(std::string("tempkey"), pMemory);
  EXPECT_EQ(nullptr, result);
}

}  // namespace detail
}  // namespace YAML
