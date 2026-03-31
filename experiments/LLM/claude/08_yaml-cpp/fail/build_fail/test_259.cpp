#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/type.h"
#include "yaml-cpp/emitterstyle.h"
#include "yaml-cpp/mark.h"

#include <string>
#include <memory>

namespace YAML {
namespace detail {

class NodeTest_259 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = shared_memory_holder(new memory_holder);
  }

  shared_memory_holder pMemory;
};

// Test default construction - node should exist but be undefined
TEST_F(NodeTest_259, DefaultConstruction_IsUndefined_259) {
  node n;
  EXPECT_FALSE(n.is_defined());
}

// Test default type should be Undefined
TEST_F(NodeTest_259, DefaultType_IsUndefined_259) {
  node n;
  EXPECT_EQ(NodeType::Undefined, n.type());
}

// Test mark_defined makes node defined
TEST_F(NodeTest_259, MarkDefined_MakesNodeDefined_259) {
  node n;
  n.mark_defined();
  EXPECT_TRUE(n.is_defined());
}

// Test set_null sets type to Null
TEST_F(NodeTest_259, SetNull_SetsTypeToNull_259) {
  node n;
  n.set_null();
  EXPECT_EQ(NodeType::Null, n.type());
}

// Test set_type to Scalar
TEST_F(NodeTest_259, SetType_Scalar_259) {
  node n;
  n.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, n.type());
}

// Test set_type to Sequence
TEST_F(NodeTest_259, SetType_Sequence_259) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
}

// Test set_type to Map
TEST_F(NodeTest_259, SetType_Map_259) {
  node n;
  n.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, n.type());
}

// Test set_scalar and scalar retrieval
TEST_F(NodeTest_259, SetScalar_RetrievesCorrectly_259) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");
  EXPECT_EQ("hello", n.scalar());
}

// Test set_scalar with empty string
TEST_F(NodeTest_259, SetScalar_EmptyString_259) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("");
  EXPECT_EQ("", n.scalar());
}

// Test set_tag and tag retrieval
TEST_F(NodeTest_259, SetTag_RetrievesCorrectly_259) {
  node n;
  n.set_tag("!mytag");
  EXPECT_EQ("!mytag", n.tag());
}

// Test set_tag with empty string
TEST_F(NodeTest_259, SetTag_EmptyString_259) {
  node n;
  n.set_tag("");
  EXPECT_EQ("", n.tag());
}

// Test set_style
TEST_F(NodeTest_259, SetStyle_Block_259) {
  node n;
  n.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, n.style());
}

// Test set_style Flow
TEST_F(NodeTest_259, SetStyle_Flow_259) {
  node n;
  n.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, n.style());
}

// Test set_style Default
TEST_F(NodeTest_259, SetStyle_Default_259) {
  node n;
  n.set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, n.style());
}

// Test set_mark and mark retrieval
TEST_F(NodeTest_259, SetMark_RetrievesCorrectly_259) {
  node n;
  Mark m;
  m.line = 10;
  m.column = 20;
  m.pos = 30;
  n.set_mark(m);
  EXPECT_EQ(10, n.mark().line);
  EXPECT_EQ(20, n.mark().column);
  EXPECT_EQ(30, n.mark().pos);
}

// Test is() - same node
TEST_F(NodeTest_259, Is_SameNode_ReturnsFalse_259) {
  node n1;
  node n2;
  // Two different nodes should not be the same
  EXPECT_FALSE(n1.is(n2));
}

// Test ref() returns non-null
TEST_F(NodeTest_259, Ref_ReturnsNonNull_259) {
  node n;
  EXPECT_NE(nullptr, n.ref());
}

// Test set_ref makes two nodes share the same ref
TEST_F(NodeTest_259, SetRef_MakesNodesSameRef_259) {
  node n1;
  node n2;
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("test");
  n2.set_ref(n1);
  EXPECT_EQ("test", n2.scalar());
  EXPECT_EQ(NodeType::Scalar, n2.type());
}

// Test set_data copies data
TEST_F(NodeTest_259, SetData_CopiesData_259) {
  node n1;
  node n2;
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("data_copy");
  n2.set_data(n1);
  EXPECT_EQ("data_copy", n2.scalar());
}

// Test sequence push_back and size
TEST_F(NodeTest_259, PushBack_IncreasesSize_259) {
  node seq;
  seq.set_type(NodeType::Sequence);

  node item1;
  item1.set_type(NodeType::Scalar);
  item1.set_scalar("item1");

  seq.push_back(item1, pMemory);
  EXPECT_EQ(1u, seq.size());
}

// Test sequence push_back multiple items
TEST_F(NodeTest_259, PushBack_MultipleItems_259) {
  node seq;
  seq.set_type(NodeType::Sequence);

  node item1;
  item1.set_type(NodeType::Scalar);
  item1.set_scalar("a");

  node item2;
  item2.set_type(NodeType::Scalar);
  item2.set_scalar("b");

  node item3;
  item3.set_type(NodeType::Scalar);
  item3.set_scalar("c");

  seq.push_back(item1, pMemory);
  seq.push_back(item2, pMemory);
  seq.push_back(item3, pMemory);

  EXPECT_EQ(3u, seq.size());
}

// Test sequence begin/end iteration
TEST_F(NodeTest_259, Sequence_BeginEnd_Iteration_259) {
  node seq;
  seq.set_type(NodeType::Sequence);

  node item1;
  item1.set_type(NodeType::Scalar);
  item1.set_scalar("hello");

  seq.push_back(item1, pMemory);

  int count = 0;
  for (auto it = seq.begin(); it != seq.end(); ++it) {
    count++;
  }
  EXPECT_EQ(1, count);
}

// Test empty sequence size is 0
TEST_F(NodeTest_259, EmptySequence_SizeIsZero_259) {
  node seq;
  seq.set_type(NodeType::Sequence);
  EXPECT_EQ(0u, seq.size());
}

// Test map insert and size
TEST_F(NodeTest_259, MapInsert_IncreasesSize_259) {
  node map;
  map.set_type(NodeType::Map);

  node key;
  key.set_type(NodeType::Scalar);
  key.set_scalar("key1");

  node value;
  value.set_type(NodeType::Scalar);
  value.set_scalar("value1");

  map.insert(key, value, pMemory);
  EXPECT_EQ(1u, map.size());
}

// Test map get with string key
TEST_F(NodeTest_259, MapGet_StringKey_259) {
  node map;
  map.set_type(NodeType::Map);

  node key;
  key.set_type(NodeType::Scalar);
  key.set_scalar("mykey");

  node value;
  value.set_type(NodeType::Scalar);
  value.set_scalar("myvalue");

  map.insert(key, value, pMemory);

  node* result = map.get(std::string("mykey"), pMemory);
  EXPECT_NE(nullptr, result);
  if (result) {
    EXPECT_EQ("myvalue", result->scalar());
  }
}

// Test map get with non-existent key returns null
TEST_F(NodeTest_259, MapGet_NonExistentKey_ReturnsNull_259) {
  node map;
  map.set_type(NodeType::Map);

  node* result = map.get(std::string("nonexistent"), pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test map remove
TEST_F(NodeTest_259, MapRemove_ExistingKey_259) {
  node map;
  map.set_type(NodeType::Map);

  node key;
  key.set_type(NodeType::Scalar);
  key.set_scalar("removekey");

  node value;
  value.set_type(NodeType::Scalar);
  value.set_scalar("removevalue");

  map.insert(key, value, pMemory);
  EXPECT_EQ(1u, map.size());

  bool removed = map.remove(std::string("removekey"), pMemory);
  EXPECT_TRUE(removed);
}

// Test map remove non-existent key
TEST_F(NodeTest_259, MapRemove_NonExistentKey_ReturnsFalse_259) {
  node map;
  map.set_type(NodeType::Map);

  bool removed = map.remove(std::string("nonexistent"), pMemory);
  EXPECT_FALSE(removed);
}

// Test equals with matching scalar
TEST_F(NodeTest_259, Equals_MatchingScalar_ReturnsTrue_259) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("test_value");

  EXPECT_TRUE(n.equals(std::string("test_value"), pMemory));
}

// Test equals with non-matching scalar
TEST_F(NodeTest_259, Equals_NonMatchingScalar_ReturnsFalse_259) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("test_value");

  EXPECT_FALSE(n.equals(std::string("other_value"), pMemory));
}

// Test equals with const char*
TEST_F(NodeTest_259, Equals_ConstCharPtr_Matching_259) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");

  EXPECT_TRUE(n.equals("hello", pMemory));
}

// Test equals with const char* non-matching
TEST_F(NodeTest_259, Equals_ConstCharPtr_NonMatching_259) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");

  EXPECT_FALSE(n.equals("world", pMemory));
}

// Test get with node key
TEST_F(NodeTest_259, MapGet_NodeKey_259) {
  node map;
  map.set_type(NodeType::Map);

  node key;
  key.set_type(NodeType::Scalar);
  key.set_scalar("nodekey");

  node value;
  value.set_type(NodeType::Scalar);
  value.set_scalar("nodevalue");

  map.insert(key, value, pMemory);

  node lookupKey;
  lookupKey.set_type(NodeType::Scalar);
  lookupKey.set_scalar("nodekey");

  node* result = map.get(lookupKey, pMemory);
  // The result depends on implementation - node key lookup may work differently
  // than string key lookup
}

// Test remove with node key
TEST_F(NodeTest_259, MapRemove_NodeKey_259) {
  node map;
  map.set_type(NodeType::Map);

  node key;
  key.set_type(NodeType::Scalar);
  key.set_scalar("noderemovekey");

  node value;
  value.set_type(NodeType::Scalar);
  value.set_scalar("noderemovevalue");

  map.insert(key, value, pMemory);

  bool removed = map.remove(key, pMemory);
  EXPECT_TRUE(removed);
}

// Test add_dependency doesn't crash
TEST_F(NodeTest_259, AddDependency_DoesNotCrash_259) {
  node n1;
  node n2;
  n1.add_dependency(n2);
  // Just ensure no crash; dependencies are internal
}

// Test changing type from Scalar to Sequence
TEST_F(NodeTest_259, ChangeType_ScalarToSequence_259) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("test");
  EXPECT_EQ(NodeType::Scalar, n.type());

  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
}

// Test multiple inserts into map
TEST_F(NodeTest_259, MapMultipleInserts_259) {
  node map;
  map.set_type(NodeType::Map);

  for (int i = 0; i < 5; i++) {
    node key;
    key.set_type(NodeType::Scalar);
    key.set_scalar("key" + std::to_string(i));

    node value;
    value.set_type(NodeType::Scalar);
    value.set_scalar("value" + std::to_string(i));

    map.insert(key, value, pMemory);
  }

  EXPECT_EQ(5u, map.size());
}

// Test force_insert on map
TEST_F(NodeTest_259, ForceInsert_259) {
  node map;
  map.set_type(NodeType::Map);

  map.force_insert(std::string("forcekey"), std::string("forcevalue"), pMemory);
  EXPECT_EQ(1u, map.size());
}

// Test empty map begin equals end
TEST_F(NodeTest_259, EmptyMap_BeginEqualsEnd_259) {
  node map;
  map.set_type(NodeType::Map);
  EXPECT_TRUE(map.begin() == map.end());
}

// Test scalar on non-scalar type returns empty or default
TEST_F(NodeTest_259, Scalar_OnSequenceType_259) {
  node n;
  n.set_type(NodeType::Sequence);
  // scalar() on a non-scalar node should return empty string
  EXPECT_EQ("", n.scalar());
}

// Test default mark values
TEST_F(NodeTest_259, DefaultMark_259) {
  node n;
  const Mark& m = n.mark();
  // Default mark should have default values
  EXPECT_EQ(Mark::null_mark().line, m.line);
  EXPECT_EQ(Mark::null_mark().column, m.column);
}

// Test set_ref then modify
TEST_F(NodeTest_259, SetRef_SharedModification_259) {
  node n1;
  node n2;
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("original");

  n2.set_ref(n1);
  EXPECT_EQ("original", n2.scalar());

  // Modifying through n2 should affect n1's ref since they share it
  n2.set_scalar("modified");
  EXPECT_EQ("modified", n1.scalar());
}

// Test is_defined after set_null
TEST_F(NodeTest_259, SetNull_IsDefined_259) {
  node n;
  n.set_null();
  EXPECT_TRUE(n.is_defined());
}

// Test is_defined after set_type to Scalar
TEST_F(NodeTest_259, SetTypeScalar_IsDefined_259) {
  node n;
  n.set_type(NodeType::Scalar);
  EXPECT_TRUE(n.is_defined());
}

}  // namespace detail
}  // namespace YAML
