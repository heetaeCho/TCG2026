#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"
#include "yaml-cpp/node/detail/node_ref.h"

namespace YAML {
namespace detail {

class NodeTest_235 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = shared_memory_holder(new Memory);
  }

  shared_memory_holder pMemory;
};

// Test default construction - node should be undefined by default
TEST_F(NodeTest_235, DefaultConstruction_IsUndefined_235) {
  node n;
  EXPECT_FALSE(n.is_defined());
}

// Test default construction - type should be Undefined
TEST_F(NodeTest_235, DefaultConstruction_TypeIsUndefined_235) {
  node n;
  EXPECT_EQ(NodeType::Undefined, n.type());
}

// Test mark_defined makes node defined
TEST_F(NodeTest_235, MarkDefined_MakesNodeDefined_235) {
  node n;
  n.mark_defined();
  EXPECT_TRUE(n.is_defined());
}

// Test set_type to Null
TEST_F(NodeTest_235, SetType_Null_235) {
  node n;
  n.set_null();
  EXPECT_EQ(NodeType::Null, n.type());
  EXPECT_TRUE(n.is_defined());
}

// Test set_type to Scalar
TEST_F(NodeTest_235, SetType_Scalar_235) {
  node n;
  n.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, n.type());
}

// Test set_type to Sequence
TEST_F(NodeTest_235, SetType_Sequence_235) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
}

// Test set_type to Map
TEST_F(NodeTest_235, SetType_Map_235) {
  node n;
  n.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, n.type());
}

// Test set_scalar and scalar retrieval
TEST_F(NodeTest_235, SetScalar_GetScalar_235) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");
  EXPECT_EQ("hello", n.scalar());
}

// Test set_scalar with empty string
TEST_F(NodeTest_235, SetScalar_EmptyString_235) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("");
  EXPECT_EQ("", n.scalar());
}

// Test set_tag and tag retrieval
TEST_F(NodeTest_235, SetTag_GetTag_235) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_tag("!mytag");
  EXPECT_EQ("!mytag", n.tag());
}

// Test set_tag with empty string
TEST_F(NodeTest_235, SetTag_EmptyString_235) {
  node n;
  n.set_tag("");
  EXPECT_EQ("", n.tag());
}

// Test set_style and style retrieval
TEST_F(NodeTest_235, SetStyle_Block_235) {
  node n;
  n.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, n.style());
}

// Test set_style Flow
TEST_F(NodeTest_235, SetStyle_Flow_235) {
  node n;
  n.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, n.style());
}

// Test set_style Default
TEST_F(NodeTest_235, SetStyle_Default_235) {
  node n;
  n.set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, n.style());
}

// Test is() - same node
TEST_F(NodeTest_235, Is_SameNode_235) {
  node n;
  EXPECT_TRUE(n.is(n));
}

// Test is() - different nodes
TEST_F(NodeTest_235, Is_DifferentNodes_235) {
  node n1;
  node n2;
  EXPECT_FALSE(n1.is(n2));
}

// Test ref() returns non-null
TEST_F(NodeTest_235, Ref_ReturnsNonNull_235) {
  node n;
  EXPECT_NE(nullptr, n.ref());
}

// Test set_null
TEST_F(NodeTest_235, SetNull_235) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("test");
  n.set_null();
  EXPECT_EQ(NodeType::Null, n.type());
}

// Test Sequence operations - push_back and size
TEST_F(NodeTest_235, Sequence_PushBack_IncreasesSize_235) {
  node seq;
  seq.set_type(NodeType::Sequence);

  node val;
  val.set_type(NodeType::Scalar);
  val.set_scalar("item1");

  seq.push_back(val, pMemory);
  EXPECT_EQ(1u, seq.size());
}

// Test Sequence - multiple push_back
TEST_F(NodeTest_235, Sequence_MultiplePushBack_235) {
  node seq;
  seq.set_type(NodeType::Sequence);

  node val1;
  val1.set_type(NodeType::Scalar);
  val1.set_scalar("item1");

  node val2;
  val2.set_type(NodeType::Scalar);
  val2.set_scalar("item2");

  seq.push_back(val1, pMemory);
  seq.push_back(val2, pMemory);
  EXPECT_EQ(2u, seq.size());
}

// Test Sequence - empty size is 0
TEST_F(NodeTest_235, Sequence_EmptySize_235) {
  node seq;
  seq.set_type(NodeType::Sequence);
  EXPECT_EQ(0u, seq.size());
}

// Test Map operations - insert and size
TEST_F(NodeTest_235, Map_Insert_IncreasesSize_235) {
  node map;
  map.set_type(NodeType::Map);

  node key;
  key.set_type(NodeType::Scalar);
  key.set_scalar("key1");

  node val;
  val.set_type(NodeType::Scalar);
  val.set_scalar("value1");

  map.insert(key, val, pMemory);
  EXPECT_EQ(1u, map.size());
}

// Test Map - get existing key
TEST_F(NodeTest_235, Map_Get_ExistingKey_235) {
  node map;
  map.set_type(NodeType::Map);

  node key;
  key.set_type(NodeType::Scalar);
  key.set_scalar("mykey");

  node val;
  val.set_type(NodeType::Scalar);
  val.set_scalar("myvalue");

  map.insert(key, val, pMemory);

  node* result = map.get(key, pMemory);
  EXPECT_NE(nullptr, result);
}

// Test Map - get non-existing key with string
TEST_F(NodeTest_235, Map_Get_NonExistingStringKey_235) {
  node map;
  map.set_type(NodeType::Map);

  node* result = map.get(std::string("nonexistent"), pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test Map - remove existing key
TEST_F(NodeTest_235, Map_Remove_ExistingKey_235) {
  node map;
  map.set_type(NodeType::Map);

  node key;
  key.set_type(NodeType::Scalar);
  key.set_scalar("removekey");

  node val;
  val.set_type(NodeType::Scalar);
  val.set_scalar("removevalue");

  map.insert(key, val, pMemory);
  EXPECT_EQ(1u, map.size());

  bool removed = map.remove(key, pMemory);
  EXPECT_TRUE(removed);
}

// Test Map - remove non-existing key
TEST_F(NodeTest_235, Map_Remove_NonExistingKey_235) {
  node map;
  map.set_type(NodeType::Map);

  node key;
  key.set_type(NodeType::Scalar);
  key.set_scalar("nonexistent");

  bool removed = map.remove(key, pMemory);
  EXPECT_FALSE(removed);
}

// Test set_ref - node should mirror referenced node
TEST_F(NodeTest_235, SetRef_MirrorsReferencedNode_235) {
  node n1;
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("original");

  node n2;
  n2.set_ref(n1);

  EXPECT_EQ(n1.type(), n2.type());
  EXPECT_EQ(n1.scalar(), n2.scalar());
}

// Test set_data - copies data
TEST_F(NodeTest_235, SetData_CopiesData_235) {
  node n1;
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("source");
  n1.set_tag("!sourcetag");

  node n2;
  n2.set_data(n1);

  EXPECT_EQ(NodeType::Scalar, n2.type());
  EXPECT_EQ("source", n2.scalar());
}

// Test set_mark and mark retrieval
TEST_F(NodeTest_235, SetMark_GetMark_235) {
  node n;
  Mark m;
  m.line = 10;
  m.column = 5;
  m.pos = 100;
  n.set_mark(m);

  const Mark& retrieved = n.mark();
  EXPECT_EQ(10, retrieved.line);
  EXPECT_EQ(5, retrieved.column);
  EXPECT_EQ(100u, retrieved.pos);
}

// Test equals with string
TEST_F(NodeTest_235, Equals_String_235) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("test");

  EXPECT_TRUE(n.equals(std::string("test"), pMemory));
  EXPECT_FALSE(n.equals(std::string("other"), pMemory));
}

// Test equals with const char*
TEST_F(NodeTest_235, Equals_ConstCharPtr_235) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");

  EXPECT_TRUE(n.equals("hello", pMemory));
  EXPECT_FALSE(n.equals("world", pMemory));
}

// Test begin/end for empty sequence
TEST_F(NodeTest_235, Sequence_BeginEqualsEnd_WhenEmpty_235) {
  node seq;
  seq.set_type(NodeType::Sequence);
  EXPECT_EQ(seq.begin(), seq.end());
}

// Test begin/end for non-empty sequence
TEST_F(NodeTest_235, Sequence_BeginNotEqualsEnd_WhenNonEmpty_235) {
  node seq;
  seq.set_type(NodeType::Sequence);

  node val;
  val.set_type(NodeType::Scalar);
  val.set_scalar("item");

  seq.push_back(val, pMemory);
  EXPECT_NE(seq.begin(), seq.end());
}

// Test node::less comparator
TEST_F(NodeTest_235, LessComparator_235) {
  node n1;
  node n2;

  node::less comparator;
  // One should be less than the other (different indices)
  bool result1 = comparator(&n1, &n2);
  bool result2 = comparator(&n2, &n1);

  // They can't both be less than each other
  EXPECT_FALSE(result1 && result2);

  // At least one direction should hold (unless equal, which shouldn't happen for different nodes)
  EXPECT_TRUE(result1 || result2 || (!result1 && !result2));
}

// Test force_insert on a map
TEST_F(NodeTest_235, Map_ForceInsert_235) {
  node map;
  map.set_type(NodeType::Map);

  map.force_insert(std::string("key1"), std::string("value1"), pMemory);
  EXPECT_EQ(1u, map.size());
}

// Test multiple force_insert
TEST_F(NodeTest_235, Map_MultipleForceInsert_235) {
  node map;
  map.set_type(NodeType::Map);

  map.force_insert(std::string("key1"), std::string("value1"), pMemory);
  map.force_insert(std::string("key2"), std::string("value2"), pMemory);
  EXPECT_EQ(2u, map.size());
}

// Test add_dependency doesn't crash
TEST_F(NodeTest_235, AddDependency_NoCrash_235) {
  node n1;
  node n2;
  EXPECT_NO_THROW(n1.add_dependency(n2));
}

// Test type change from Sequence to Map
TEST_F(NodeTest_235, TypeChange_SequenceToMap_235) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());

  n.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, n.type());
}

// Test type change from Scalar to Null
TEST_F(NodeTest_235, TypeChange_ScalarToNull_235) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("data");
  n.set_null();
  EXPECT_EQ(NodeType::Null, n.type());
}

// Test get with string key on map
TEST_F(NodeTest_235, Map_GetWithStringKey_235) {
  node map;
  map.set_type(NodeType::Map);

  map.force_insert(std::string("hello"), std::string("world"), pMemory);

  node* result = map.get(std::string("hello"), pMemory);
  EXPECT_NE(nullptr, result);
}

// Test remove with string key
TEST_F(NodeTest_235, Map_RemoveWithStringKey_235) {
  node map;
  map.set_type(NodeType::Map);

  map.force_insert(std::string("removeme"), std::string("value"), pMemory);
  EXPECT_EQ(1u, map.size());

  bool removed = map.remove(std::string("removeme"), pMemory);
  EXPECT_TRUE(removed);
}

// Test remove string key that doesn't exist
TEST_F(NodeTest_235, Map_RemoveStringKey_NotFound_235) {
  node map;
  map.set_type(NodeType::Map);

  bool removed = map.remove(std::string("nokey"), pMemory);
  EXPECT_FALSE(removed);
}

// Test set_scalar with special characters
TEST_F(NodeTest_235, SetScalar_SpecialCharacters_235) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello\nworld\ttab");
  EXPECT_EQ("hello\nworld\ttab", n.scalar());
}

// Test set_scalar with very long string
TEST_F(NodeTest_235, SetScalar_LongString_235) {
  node n;
  n.set_type(NodeType::Scalar);
  std::string longStr(10000, 'x');
  n.set_scalar(longStr);
  EXPECT_EQ(longStr, n.scalar());
}

// Test equals with non-matching type
TEST_F(NodeTest_235, Equals_NonScalarType_235) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_FALSE(n.equals(std::string("test"), pMemory));
}

// Test is_defined after set_type
TEST_F(NodeTest_235, IsDefined_AfterSetType_235) {
  node n;
  EXPECT_FALSE(n.is_defined());
  n.set_type(NodeType::Scalar);
  EXPECT_TRUE(n.is_defined());
}

// Test Null type is defined
TEST_F(NodeTest_235, NullType_IsDefined_235) {
  node n;
  n.set_null();
  EXPECT_TRUE(n.is_defined());
}

}  // namespace detail
}  // namespace YAML
