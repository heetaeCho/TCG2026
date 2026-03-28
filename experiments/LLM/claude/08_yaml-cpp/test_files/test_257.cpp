#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeTest_257 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = create_shared_memory();
  }

  shared_memory_holder pMemory;
};

// Test default construction - node should not be defined initially
TEST_F(NodeTest_257, DefaultConstruction_IsNotDefined_257) {
  node& n = pMemory->create_node();
  // A freshly created node should have Null or Undefined type
  EXPECT_FALSE(n.is_defined());
}

// Test mark_defined makes node defined
TEST_F(NodeTest_257, MarkDefined_MakesNodeDefined_257) {
  node& n = pMemory->create_node();
  n.mark_defined();
  EXPECT_TRUE(n.is_defined());
}

// Test set_type to Sequence
TEST_F(NodeTest_257, SetType_Sequence_257) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
}

// Test set_type to Map
TEST_F(NodeTest_257, SetType_Map_257) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, n.type());
}

// Test set_type to Scalar
TEST_F(NodeTest_257, SetType_Scalar_257) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, n.type());
}

// Test set_null
TEST_F(NodeTest_257, SetNull_TypeBecomesNull_257) {
  node& n = pMemory->create_node();
  n.set_null();
  EXPECT_EQ(NodeType::Null, n.type());
}

// Test set_scalar and scalar getter
TEST_F(NodeTest_257, SetScalar_ReturnsCorrectValue_257) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");
  EXPECT_EQ("hello", n.scalar());
}

// Test set_scalar with empty string
TEST_F(NodeTest_257, SetScalar_EmptyString_257) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  n.set_scalar("");
  EXPECT_EQ("", n.scalar());
}

// Test set_tag and tag getter
TEST_F(NodeTest_257, SetTag_ReturnsCorrectValue_257) {
  node& n = pMemory->create_node();
  n.set_tag("!mytag");
  EXPECT_EQ("!mytag", n.tag());
}

// Test set_style and style getter
TEST_F(NodeTest_257, SetStyle_Flow_257) {
  node& n = pMemory->create_node();
  n.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, n.style());
}

TEST_F(NodeTest_257, SetStyle_Block_257) {
  node& n = pMemory->create_node();
  n.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, n.style());
}

// Test is() - same node
TEST_F(NodeTest_257, Is_SameNode_ReturnsTrue_257) {
  node& n = pMemory->create_node();
  EXPECT_TRUE(n.is(n));
}

// Test is() - different nodes
TEST_F(NodeTest_257, Is_DifferentNodes_ReturnsFalse_257) {
  node& n1 = pMemory->create_node();
  node& n2 = pMemory->create_node();
  EXPECT_FALSE(n1.is(n2));
}

// Test ref() returns non-null
TEST_F(NodeTest_257, Ref_ReturnsNonNull_257) {
  node& n = pMemory->create_node();
  EXPECT_NE(nullptr, n.ref());
}

// Test push_back on a sequence
TEST_F(NodeTest_257, PushBack_IncreasesSize_257) {
  node& seq = pMemory->create_node();
  seq.set_type(NodeType::Sequence);

  node& child1 = pMemory->create_node();
  child1.set_scalar("item1");

  EXPECT_EQ(0u, seq.size());
  seq.push_back(child1, pMemory);
  EXPECT_EQ(1u, seq.size());
}

// Test push_back multiple items
TEST_F(NodeTest_257, PushBack_MultipleItems_257) {
  node& seq = pMemory->create_node();
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

// Test begin/end iteration on sequence
TEST_F(NodeTest_257, BeginEnd_SequenceIteration_257) {
  node& seq = pMemory->create_node();
  seq.set_type(NodeType::Sequence);

  node& child1 = pMemory->create_node();
  child1.set_scalar("a");
  node& child2 = pMemory->create_node();
  child2.set_scalar("b");

  seq.push_back(child1, pMemory);
  seq.push_back(child2, pMemory);

  int count = 0;
  for (auto it = seq.begin(); it != seq.end(); ++it) {
    count++;
  }
  EXPECT_EQ(2, count);
}

// Test empty sequence begin == end
TEST_F(NodeTest_257, BeginEnd_EmptySequence_257) {
  node& seq = pMemory->create_node();
  seq.set_type(NodeType::Sequence);
  EXPECT_TRUE(seq.begin() == seq.end());
}

// Test insert into map
TEST_F(NodeTest_257, Insert_MapKeyValue_257) {
  node& map = pMemory->create_node();
  map.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("key1");
  node& value = pMemory->create_node();
  value.set_scalar("value1");

  map.insert(key, value, pMemory);
  EXPECT_EQ(1u, map.size());
}

// Test get from map with string key
TEST_F(NodeTest_257, Get_ExistingKey_ReturnsNode_257) {
  node& map = pMemory->create_node();
  map.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("mykey");
  node& value = pMemory->create_node();
  value.set_scalar("myvalue");

  map.insert(key, value, pMemory);

  node* result = map.get(std::string("mykey"), pMemory);
  EXPECT_NE(nullptr, result);
}

// Test get from map with non-existing key
TEST_F(NodeTest_257, Get_NonExistingKey_ReturnsNull_257) {
  node& map = pMemory->create_node();
  map.set_type(NodeType::Map);

  node* result = map.get(std::string("nonexistent"), pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test remove from map
TEST_F(NodeTest_257, Remove_ExistingKey_ReturnsTrue_257) {
  node& map = pMemory->create_node();
  map.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("removekey");
  node& value = pMemory->create_node();
  value.set_scalar("removevalue");

  map.insert(key, value, pMemory);
  bool removed = map.remove(std::string("removekey"), pMemory);
  EXPECT_TRUE(removed);
}

// Test remove non-existing key
TEST_F(NodeTest_257, Remove_NonExistingKey_ReturnsFalse_257) {
  node& map = pMemory->create_node();
  map.set_type(NodeType::Map);

  bool removed = map.remove(std::string("nonexistent"), pMemory);
  EXPECT_FALSE(removed);
}

// Test set_data copies data from another node
TEST_F(NodeTest_257, SetData_CopiesFromOtherNode_257) {
  node& n1 = pMemory->create_node();
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("copied");

  node& n2 = pMemory->create_node();
  n2.set_data(n1);

  EXPECT_EQ(NodeType::Scalar, n2.type());
  EXPECT_EQ("copied", n2.scalar());
}

// Test set_ref makes node refer to same data
TEST_F(NodeTest_257, SetRef_SharesReference_257) {
  node& n1 = pMemory->create_node();
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("shared");

  node& n2 = pMemory->create_node();
  n2.set_ref(n1);

  EXPECT_EQ("shared", n2.scalar());
}

// Test set_mark and mark getter
TEST_F(NodeTest_257, SetMark_ReturnsCorrectMark_257) {
  node& n = pMemory->create_node();
  Mark m;
  m.line = 10;
  m.column = 20;
  m.pos = 30;
  n.set_mark(m);

  const Mark& retrieved = n.mark();
  EXPECT_EQ(10, retrieved.line);
  EXPECT_EQ(20, retrieved.column);
  EXPECT_EQ(30, retrieved.pos);
}

// Test equals with matching scalar
TEST_F(NodeTest_257, Equals_MatchingScalar_ReturnsTrue_257) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  n.set_scalar("test");

  EXPECT_TRUE(n.equals(std::string("test"), pMemory));
}

// Test equals with non-matching scalar
TEST_F(NodeTest_257, Equals_NonMatchingScalar_ReturnsFalse_257) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  n.set_scalar("test");

  EXPECT_FALSE(n.equals(std::string("other"), pMemory));
}

// Test equals with const char*
TEST_F(NodeTest_257, Equals_ConstCharPtr_Matching_257) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");

  EXPECT_TRUE(n.equals("hello", pMemory));
}

// Test equals with const char* non-matching
TEST_F(NodeTest_257, Equals_ConstCharPtr_NonMatching_257) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");

  EXPECT_FALSE(n.equals("world", pMemory));
}

// Test size of empty node
TEST_F(NodeTest_257, Size_EmptyNode_ReturnsZero_257) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(0u, n.size());
}

// Test size of map
TEST_F(NodeTest_257, Size_MapWithEntries_257) {
  node& map = pMemory->create_node();
  map.set_type(NodeType::Map);

  node& key1 = pMemory->create_node();
  key1.set_scalar("k1");
  node& val1 = pMemory->create_node();
  val1.set_scalar("v1");

  node& key2 = pMemory->create_node();
  key2.set_scalar("k2");
  node& val2 = pMemory->create_node();
  val2.set_scalar("v2");

  map.insert(key1, val1, pMemory);
  map.insert(key2, val2, pMemory);

  EXPECT_EQ(2u, map.size());
}

// Test force_insert
TEST_F(NodeTest_257, ForceInsert_AddsEntry_257) {
  node& map = pMemory->create_node();
  map.set_type(NodeType::Map);

  map.force_insert(std::string("fkey"), std::string("fval"), pMemory);
  EXPECT_EQ(1u, map.size());
}

// Test get with node reference key
TEST_F(NodeTest_257, Get_WithNodeKey_257) {
  node& map = pMemory->create_node();
  map.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("nodekey");
  node& value = pMemory->create_node();
  value.set_scalar("nodevalue");

  map.insert(key, value, pMemory);

  node& searchKey = pMemory->create_node();
  searchKey.set_scalar("nodekey");
  node* result = map.get(searchKey, pMemory);
  EXPECT_NE(nullptr, result);
}

// Test remove with node reference key
TEST_F(NodeTest_257, Remove_WithNodeKey_Existing_257) {
  node& map = pMemory->create_node();
  map.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("rnodekey");
  node& value = pMemory->create_node();
  value.set_scalar("rnodevalue");

  map.insert(key, value, pMemory);

  node& removeKey = pMemory->create_node();
  removeKey.set_scalar("rnodekey");
  bool removed = map.remove(removeKey, pMemory);
  EXPECT_TRUE(removed);
}

// Test remove with node reference key - non existing
TEST_F(NodeTest_257, Remove_WithNodeKey_NonExisting_257) {
  node& map = pMemory->create_node();
  map.set_type(NodeType::Map);

  node& removeKey = pMemory->create_node();
  removeKey.set_scalar("doesnotexist");
  bool removed = map.remove(removeKey, pMemory);
  EXPECT_FALSE(removed);
}

// Test add_dependency doesn't crash
TEST_F(NodeTest_257, AddDependency_NoCrash_257) {
  node& n1 = pMemory->create_node();
  node& n2 = pMemory->create_node();
  EXPECT_NO_THROW(n1.add_dependency(n2));
}

// Test type of default node
TEST_F(NodeTest_257, DefaultType_IsUndefined_257) {
  node& n = pMemory->create_node();
  EXPECT_EQ(NodeType::Undefined, n.type());
}

// Test changing type from Scalar to Map
TEST_F(NodeTest_257, ChangeType_ScalarToMap_257) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  n.set_scalar("value");
  EXPECT_EQ(NodeType::Scalar, n.type());

  n.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, n.type());
}

// Test push_back creates proper dependency
TEST_F(NodeTest_257, PushBack_ChildNotSameAsParent_257) {
  node& seq = pMemory->create_node();
  seq.set_type(NodeType::Sequence);

  node& child = pMemory->create_node();
  child.set_scalar("child");

  seq.push_back(child, pMemory);

  EXPECT_FALSE(seq.is(child));
}

// Test set_tag with empty tag
TEST_F(NodeTest_257, SetTag_EmptyString_257) {
  node& n = pMemory->create_node();
  n.set_tag("");
  EXPECT_EQ("", n.tag());
}

// Test multiple push_back and iteration
TEST_F(NodeTest_257, PushBack_IterateAllElements_257) {
  node& seq = pMemory->create_node();
  seq.set_type(NodeType::Sequence);

  const int NUM_ITEMS = 5;
  for (int i = 0; i < NUM_ITEMS; i++) {
    node& child = pMemory->create_node();
    child.set_scalar(std::to_string(i));
    seq.push_back(child, pMemory);
  }

  EXPECT_EQ(static_cast<std::size_t>(NUM_ITEMS), seq.size());

  int count = 0;
  for (auto it = seq.begin(); it != seq.end(); ++it) {
    count++;
  }
  EXPECT_EQ(NUM_ITEMS, count);
}

}  // namespace detail
}  // namespace YAML
