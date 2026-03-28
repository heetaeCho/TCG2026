#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeRefTest_222 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = std::make_shared<memory_holder>();
    ref = std::unique_ptr<node_ref>(new node_ref());
  }

  shared_memory_holder pMemory;
  std::unique_ptr<node_ref> ref;

  node& create_node() {
    return pMemory->create_node();
  }
};

// Test default construction state
TEST_F(NodeRefTest_222, DefaultConstruction_IsNotDefined_222) {
  EXPECT_FALSE(ref->is_defined());
}

TEST_F(NodeRefTest_222, DefaultConstruction_TypeIsNull_222) {
  EXPECT_EQ(NodeType::Null, ref->type());
}

TEST_F(NodeRefTest_222, DefaultConstruction_ScalarIsEmpty_222) {
  EXPECT_TRUE(ref->scalar().empty());
}

TEST_F(NodeRefTest_222, DefaultConstruction_TagIsEmpty_222) {
  EXPECT_TRUE(ref->tag().empty());
}

TEST_F(NodeRefTest_222, DefaultConstruction_SizeIsZero_222) {
  EXPECT_EQ(0u, ref->size());
}

// Test mark_defined
TEST_F(NodeRefTest_222, MarkDefined_MakesNodeDefined_222) {
  ref->mark_defined();
  EXPECT_TRUE(ref->is_defined());
}

// Test set_null
TEST_F(NodeRefTest_222, SetNull_SetsTypeToNull_222) {
  ref->mark_defined();
  ref->set_type(NodeType::Scalar);
  ref->set_null();
  EXPECT_EQ(NodeType::Null, ref->type());
}

TEST_F(NodeRefTest_222, SetNull_MakesNodeDefined_222) {
  ref->set_null();
  EXPECT_TRUE(ref->is_defined());
}

// Test set_type
TEST_F(NodeRefTest_222, SetType_Scalar_222) {
  ref->set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, ref->type());
}

TEST_F(NodeRefTest_222, SetType_Sequence_222) {
  ref->set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, ref->type());
}

TEST_F(NodeRefTest_222, SetType_Map_222) {
  ref->set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, ref->type());
}

TEST_F(NodeRefTest_222, SetType_Null_222) {
  ref->set_type(NodeType::Scalar);
  ref->set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, ref->type());
}

TEST_F(NodeRefTest_222, SetType_Undefined_222) {
  ref->set_type(NodeType::Undefined);
  EXPECT_EQ(NodeType::Undefined, ref->type());
}

// Test set_tag
TEST_F(NodeRefTest_222, SetTag_StoresTag_222) {
  ref->set_tag("!custom");
  EXPECT_EQ("!custom", ref->tag());
}

TEST_F(NodeRefTest_222, SetTag_EmptyTag_222) {
  ref->set_tag("something");
  ref->set_tag("");
  EXPECT_EQ("", ref->tag());
}

// Test set_scalar
TEST_F(NodeRefTest_222, SetScalar_StoresScalar_222) {
  ref->set_type(NodeType::Scalar);
  ref->set_scalar("hello");
  EXPECT_EQ("hello", ref->scalar());
}

TEST_F(NodeRefTest_222, SetScalar_EmptyString_222) {
  ref->set_type(NodeType::Scalar);
  ref->set_scalar("");
  EXPECT_EQ("", ref->scalar());
}

TEST_F(NodeRefTest_222, SetScalar_LongString_222) {
  ref->set_type(NodeType::Scalar);
  std::string longStr(10000, 'x');
  ref->set_scalar(longStr);
  EXPECT_EQ(longStr, ref->scalar());
}

// Test set_style
TEST_F(NodeRefTest_222, SetStyle_Block_222) {
  ref->set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, ref->style());
}

TEST_F(NodeRefTest_222, SetStyle_Flow_222) {
  ref->set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, ref->style());
}

TEST_F(NodeRefTest_222, SetStyle_Default_222) {
  ref->set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, ref->style());
}

// Test set_mark
TEST_F(NodeRefTest_222, SetMark_StoresMark_222) {
  Mark m;
  m.pos = 10;
  m.line = 5;
  m.column = 3;
  ref->set_mark(m);
  const Mark& stored = ref->mark();
  EXPECT_EQ(5, stored.line);
  EXPECT_EQ(3, stored.column);
}

// Test sequence operations
TEST_F(NodeRefTest_222, PushBack_IncreasesSize_222) {
  ref->set_type(NodeType::Sequence);
  node& n = create_node();
  ref->push_back(n, pMemory);
  EXPECT_EQ(1u, ref->size());
}

TEST_F(NodeRefTest_222, PushBack_MultipleTimes_222) {
  ref->set_type(NodeType::Sequence);
  node& n1 = create_node();
  node& n2 = create_node();
  node& n3 = create_node();
  ref->push_back(n1, pMemory);
  ref->push_back(n2, pMemory);
  ref->push_back(n3, pMemory);
  EXPECT_EQ(3u, ref->size());
}

// Test begin/end for empty sequence
TEST_F(NodeRefTest_222, BeginEqualsEnd_EmptySequence_222) {
  ref->set_type(NodeType::Sequence);
  EXPECT_EQ(ref->begin(), ref->end());
}

// Test begin/end for non-empty sequence
TEST_F(NodeRefTest_222, BeginNotEqualsEnd_NonEmptySequence_222) {
  ref->set_type(NodeType::Sequence);
  node& n = create_node();
  ref->push_back(n, pMemory);
  EXPECT_NE(ref->begin(), ref->end());
}

// Test map operations
TEST_F(NodeRefTest_222, Insert_IncreasesSize_222) {
  ref->set_type(NodeType::Map);
  node& key = create_node();
  node& value = create_node();
  ref->insert(key, value, pMemory);
  EXPECT_EQ(1u, ref->size());
}

TEST_F(NodeRefTest_222, Insert_MultipleEntries_222) {
  ref->set_type(NodeType::Map);
  node& k1 = create_node();
  node& v1 = create_node();
  node& k2 = create_node();
  node& v2 = create_node();
  ref->insert(k1, v1, pMemory);
  ref->insert(k2, v2, pMemory);
  EXPECT_EQ(2u, ref->size());
}

// Test get with node key
TEST_F(NodeRefTest_222, Get_ExistingKey_ReturnsNonNull_222) {
  ref->set_type(NodeType::Map);
  node& key = create_node();
  key.set_scalar("mykey");
  node& value = create_node();
  value.set_scalar("myvalue");
  ref->insert(key, value, pMemory);
  
  node* result = ref->get(key, pMemory);
  EXPECT_NE(nullptr, result);
}

TEST_F(NodeRefTest_222, Get_NonExistingKey_ReturnsNull_222) {
  ref->set_type(NodeType::Map);
  node& key = create_node();
  key.set_scalar("nonexistent");
  
  node* result = ref->get(key, pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test get with string key
TEST_F(NodeRefTest_222, GetByStringKey_ExistingKey_222) {
  ref->set_type(NodeType::Map);
  node& key = create_node();
  key.set_scalar("testkey");
  node& value = create_node();
  value.set_scalar("testvalue");
  ref->insert(key, value, pMemory);
  
  node* result = ref->get(std::string("testkey"), pMemory);
  EXPECT_NE(nullptr, result);
}

TEST_F(NodeRefTest_222, GetByStringKey_NonExistingKey_222) {
  ref->set_type(NodeType::Map);
  node* result = ref->get(std::string("nosuchkey"), pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test remove
TEST_F(NodeRefTest_222, Remove_ExistingNodeKey_ReturnsTrue_222) {
  ref->set_type(NodeType::Map);
  node& key = create_node();
  key.set_scalar("removekey");
  node& value = create_node();
  value.set_scalar("removevalue");
  ref->insert(key, value, pMemory);
  
  bool removed = ref->remove(key, pMemory);
  EXPECT_TRUE(removed);
}

TEST_F(NodeRefTest_222, Remove_NonExistingNodeKey_ReturnsFalse_222) {
  ref->set_type(NodeType::Map);
  node& key = create_node();
  key.set_scalar("nokey");
  
  bool removed = ref->remove(key, pMemory);
  EXPECT_FALSE(removed);
}

TEST_F(NodeRefTest_222, Remove_ByStringKey_ExistingKey_222) {
  ref->set_type(NodeType::Map);
  node& key = create_node();
  key.set_scalar("strkey");
  node& value = create_node();
  value.set_scalar("strvalue");
  ref->insert(key, value, pMemory);
  
  bool removed = ref->remove(std::string("strkey"), pMemory);
  EXPECT_TRUE(removed);
}

TEST_F(NodeRefTest_222, Remove_ByStringKey_NonExistingKey_222) {
  ref->set_type(NodeType::Map);
  bool removed = ref->remove(std::string("nosuchkey"), pMemory);
  EXPECT_FALSE(removed);
}

// Test set_data copies data from another node_ref
TEST_F(NodeRefTest_222, SetData_CopiesFromAnotherRef_222) {
  node_ref other;
  other.mark_defined();
  other.set_type(NodeType::Scalar);
  other.set_scalar("copied");
  other.set_tag("!tag");
  
  ref->set_data(other);
  EXPECT_EQ(NodeType::Scalar, ref->type());
  EXPECT_EQ("copied", ref->scalar());
  EXPECT_EQ("!tag", ref->tag());
}

// Test force_insert
TEST_F(NodeRefTest_222, ForceInsert_AddsEntry_222) {
  ref->set_type(NodeType::Map);
  ref->force_insert(std::string("forcekey"), std::string("forcevalue"), pMemory);
  EXPECT_EQ(1u, ref->size());
}

// Test type transitions
TEST_F(NodeRefTest_222, TypeTransition_NullToScalar_222) {
  EXPECT_EQ(NodeType::Null, ref->type());
  ref->set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, ref->type());
}

TEST_F(NodeRefTest_222, TypeTransition_ScalarToSequence_222) {
  ref->set_type(NodeType::Scalar);
  ref->set_scalar("value");
  ref->set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, ref->type());
}

TEST_F(NodeRefTest_222, TypeTransition_SequenceToMap_222) {
  ref->set_type(NodeType::Sequence);
  ref->set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, ref->type());
}

// Test that setting null clears scalar
TEST_F(NodeRefTest_222, SetNull_ClearsScalar_222) {
  ref->set_type(NodeType::Scalar);
  ref->set_scalar("hello");
  EXPECT_EQ("hello", ref->scalar());
  ref->set_null();
  EXPECT_EQ(NodeType::Null, ref->type());
}

// Test size of null node
TEST_F(NodeRefTest_222, Size_NullNode_IsZero_222) {
  EXPECT_EQ(0u, ref->size());
}

// Test size of scalar node
TEST_F(NodeRefTest_222, Size_ScalarNode_IsZero_222) {
  ref->set_type(NodeType::Scalar);
  ref->set_scalar("test");
  EXPECT_EQ(0u, ref->size());
}

// Test map begin/end when empty
TEST_F(NodeRefTest_222, BeginEqualsEnd_EmptyMap_222) {
  ref->set_type(NodeType::Map);
  EXPECT_EQ(ref->begin(), ref->end());
}

// Test map begin/end when non-empty
TEST_F(NodeRefTest_222, BeginNotEqualsEnd_NonEmptyMap_222) {
  ref->set_type(NodeType::Map);
  node& key = create_node();
  key.set_scalar("k");
  node& value = create_node();
  value.set_scalar("v");
  ref->insert(key, value, pMemory);
  EXPECT_NE(ref->begin(), ref->end());
}

// Test that after remove, size decreases
TEST_F(NodeRefTest_222, Remove_DecreasesSize_222) {
  ref->set_type(NodeType::Map);
  node& key = create_node();
  key.set_scalar("delkey");
  node& value = create_node();
  value.set_scalar("delval");
  ref->insert(key, value, pMemory);
  EXPECT_EQ(1u, ref->size());
  
  ref->remove(std::string("delkey"), pMemory);
  EXPECT_EQ(0u, ref->size());
}

// Test mark with null mark
TEST_F(NodeRefTest_222, DefaultMark_IsNullMark_222) {
  const Mark& m = ref->mark();
  // null mark typically has specific values
  EXPECT_EQ(Mark::null_mark().pos, m.pos);
  EXPECT_EQ(Mark::null_mark().line, m.line);
  EXPECT_EQ(Mark::null_mark().column, m.column);
}

// Test overwriting scalar
TEST_F(NodeRefTest_222, SetScalar_OverwritesPrevious_222) {
  ref->set_type(NodeType::Scalar);
  ref->set_scalar("first");
  EXPECT_EQ("first", ref->scalar());
  ref->set_scalar("second");
  EXPECT_EQ("second", ref->scalar());
}

// Test overwriting tag
TEST_F(NodeRefTest_222, SetTag_OverwritesPrevious_222) {
  ref->set_tag("!first");
  EXPECT_EQ("!first", ref->tag());
  ref->set_tag("!second");
  EXPECT_EQ("!second", ref->tag());
}

}  // namespace detail
}  // namespace YAML
