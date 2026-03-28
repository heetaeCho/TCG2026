#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node_data.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"
#include "yaml-cpp/node/type.h"
#include "yaml-cpp/emitterstyle.h"
#include "yaml-cpp/mark.h"

namespace YAML {
namespace detail {

class NodeDataTest_643 : public ::testing::Test {
 protected:
  void SetUp() override {
    m_memory.reset(new Memory);
  }

  shared_memory_holder m_memory;
};

// === Construction and Default State ===

TEST_F(NodeDataTest_643, DefaultConstruction_IsNotDefined_643) {
  node_data nd;
  EXPECT_FALSE(nd.is_defined());
}

TEST_F(NodeDataTest_643, DefaultConstruction_TypeIsNull_643) {
  node_data nd;
  EXPECT_EQ(NodeType::Null, nd.type());
}

TEST_F(NodeDataTest_643, DefaultConstruction_TagIsEmpty_643) {
  node_data nd;
  EXPECT_TRUE(nd.tag().empty());
}

TEST_F(NodeDataTest_643, DefaultConstruction_ScalarIsEmpty_643) {
  node_data nd;
  EXPECT_TRUE(nd.scalar().empty());
}

TEST_F(NodeDataTest_643, DefaultConstruction_MarkIsNull_643) {
  node_data nd;
  EXPECT_EQ(Mark::null_mark().line, nd.mark().line);
  EXPECT_EQ(Mark::null_mark().column, nd.mark().column);
  EXPECT_EQ(Mark::null_mark().pos, nd.mark().pos);
}

// === mark_defined ===

TEST_F(NodeDataTest_643, MarkDefined_SetsIsDefined_643) {
  node_data nd;
  nd.mark_defined();
  EXPECT_TRUE(nd.is_defined());
}

// === set_mark ===

TEST_F(NodeDataTest_643, SetMark_StoresMark_643) {
  node_data nd;
  Mark m;
  m.line = 10;
  m.column = 20;
  m.pos = 30;
  nd.set_mark(m);
  EXPECT_EQ(10u, nd.mark().line);
  EXPECT_EQ(20u, nd.mark().column);
  EXPECT_EQ(30u, nd.mark().pos);
}

// === set_type ===

TEST_F(NodeDataTest_643, SetType_Sequence_643) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, nd.type());
}

TEST_F(NodeDataTest_643, SetType_Map_643) {
  node_data nd;
  nd.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, nd.type());
}

TEST_F(NodeDataTest_643, SetType_Scalar_643) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, nd.type());
}

TEST_F(NodeDataTest_643, SetType_Null_643) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, nd.type());
}

TEST_F(NodeDataTest_643, SetType_Undefined_643) {
  node_data nd;
  nd.set_type(NodeType::Undefined);
  EXPECT_EQ(NodeType::Undefined, nd.type());
}

TEST_F(NodeDataTest_643, SetType_MarksDefined_643) {
  node_data nd;
  EXPECT_FALSE(nd.is_defined());
  nd.set_type(NodeType::Scalar);
  EXPECT_TRUE(nd.is_defined());
}

// === set_tag ===

TEST_F(NodeDataTest_643, SetTag_StoresTag_643) {
  node_data nd;
  nd.set_tag("!!str");
  EXPECT_EQ("!!str", nd.tag());
}

TEST_F(NodeDataTest_643, SetTag_EmptyString_643) {
  node_data nd;
  nd.set_tag("something");
  nd.set_tag("");
  EXPECT_EQ("", nd.tag());
}

TEST_F(NodeDataTest_643, SetTag_OverwritesPreviousTag_643) {
  node_data nd;
  nd.set_tag("first");
  nd.set_tag("second");
  EXPECT_EQ("second", nd.tag());
}

// === set_null ===

TEST_F(NodeDataTest_643, SetNull_TypeBecomesNull_643) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_null();
  EXPECT_EQ(NodeType::Null, nd.type());
}

TEST_F(NodeDataTest_643, SetNull_MarksDefined_643) {
  node_data nd;
  nd.set_null();
  EXPECT_TRUE(nd.is_defined());
}

// === set_scalar ===

TEST_F(NodeDataTest_643, SetScalar_StoresScalar_643) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("hello");
  EXPECT_EQ("hello", nd.scalar());
}

TEST_F(NodeDataTest_643, SetScalar_EmptyString_643) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("");
  EXPECT_EQ("", nd.scalar());
}

TEST_F(NodeDataTest_643, SetScalar_OverwritesPrevious_643) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("first");
  nd.set_scalar("second");
  EXPECT_EQ("second", nd.scalar());
}

// === set_style ===

TEST_F(NodeDataTest_643, SetStyle_Block_643) {
  node_data nd;
  nd.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, nd.style());
}

TEST_F(NodeDataTest_643, SetStyle_Flow_643) {
  node_data nd;
  nd.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, nd.style());
}

TEST_F(NodeDataTest_643, SetStyle_Default_643) {
  node_data nd;
  nd.set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, nd.style());
}

// === empty_scalar ===

TEST_F(NodeDataTest_643, EmptyScalar_ReturnsEmptyString_643) {
  const std::string& empty = node_data::empty_scalar();
  EXPECT_TRUE(empty.empty());
}

TEST_F(NodeDataTest_643, EmptyScalar_ReturnsSameReference_643) {
  const std::string& a = node_data::empty_scalar();
  const std::string& b = node_data::empty_scalar();
  EXPECT_EQ(&a, &b);
}

// === size ===

TEST_F(NodeDataTest_643, Size_NullTypeReturnsZero_643) {
  node_data nd;
  EXPECT_EQ(0u, nd.size());
}

TEST_F(NodeDataTest_643, Size_EmptySequenceReturnsZero_643) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  EXPECT_EQ(0u, nd.size());
}

TEST_F(NodeDataTest_643, Size_EmptyMapReturnsZero_643) {
  node_data nd;
  nd.set_type(NodeType::Map);
  EXPECT_EQ(0u, nd.size());
}

TEST_F(NodeDataTest_643, Size_SequenceAfterPushBack_643) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  node& n1 = m_memory->create_node();
  n1.set_scalar("val1");
  nd.push_back(n1, m_memory);
  EXPECT_EQ(1u, nd.size());
}

TEST_F(NodeDataTest_643, Size_SequenceMultiplePushBacks_643) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  node& n1 = m_memory->create_node();
  n1.set_scalar("val1");
  node& n2 = m_memory->create_node();
  n2.set_scalar("val2");
  node& n3 = m_memory->create_node();
  n3.set_scalar("val3");
  nd.push_back(n1, m_memory);
  nd.push_back(n2, m_memory);
  nd.push_back(n3, m_memory);
  EXPECT_EQ(3u, nd.size());
}

// === push_back ===

TEST_F(NodeDataTest_643, PushBack_AddsToSequence_643) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  node& n1 = m_memory->create_node();
  n1.set_scalar("test");
  nd.push_back(n1, m_memory);
  EXPECT_EQ(1u, nd.size());
}

// === insert (map) ===

TEST_F(NodeDataTest_643, Insert_AddsToMap_643) {
  node_data nd;
  nd.set_type(NodeType::Map);
  node& key = m_memory->create_node();
  key.set_scalar("key1");
  node& val = m_memory->create_node();
  val.set_scalar("val1");
  nd.insert(key, val, m_memory);
  EXPECT_EQ(1u, nd.size());
}

TEST_F(NodeDataTest_643, Insert_MultipleEntries_643) {
  node_data nd;
  nd.set_type(NodeType::Map);

  node& k1 = m_memory->create_node();
  k1.set_scalar("key1");
  node& v1 = m_memory->create_node();
  v1.set_scalar("val1");
  nd.insert(k1, v1, m_memory);

  node& k2 = m_memory->create_node();
  k2.set_scalar("key2");
  node& v2 = m_memory->create_node();
  v2.set_scalar("val2");
  nd.insert(k2, v2, m_memory);

  EXPECT_EQ(2u, nd.size());
}

// === get (template version with string key) ===

TEST_F(NodeDataTest_643, Get_ExistingKeyReturnsNonNull_643) {
  node_data nd;
  nd.set_type(NodeType::Map);

  node& key = m_memory->create_node();
  key.set_scalar("mykey");
  node& val = m_memory->create_node();
  val.set_scalar("myval");
  nd.insert(key, val, m_memory);

  const node* result = nd.get(std::string("mykey"), m_memory);
  EXPECT_NE(nullptr, result);
}

TEST_F(NodeDataTest_643, Get_NonExistingKeyReturnsNull_643) {
  node_data nd;
  nd.set_type(NodeType::Map);

  node& key = m_memory->create_node();
  key.set_scalar("mykey");
  node& val = m_memory->create_node();
  val.set_scalar("myval");
  nd.insert(key, val, m_memory);

  const node* result = nd.get(std::string("otherkey"), m_memory);
  EXPECT_EQ(nullptr, result);
}

TEST_F(NodeDataTest_643, Get_EmptyMapReturnsNull_643) {
  node_data nd;
  nd.set_type(NodeType::Map);

  const node* result = nd.get(std::string("anykey"), m_memory);
  EXPECT_EQ(nullptr, result);
}

// === remove (template version with string key) ===

TEST_F(NodeDataTest_643, Remove_ExistingKeyReturnsTrue_643) {
  node_data nd;
  nd.set_type(NodeType::Map);

  node& key = m_memory->create_node();
  key.set_scalar("mykey");
  node& val = m_memory->create_node();
  val.set_scalar("myval");
  nd.insert(key, val, m_memory);

  EXPECT_TRUE(nd.remove(std::string("mykey"), m_memory));
}

TEST_F(NodeDataTest_643, Remove_NonExistingKeyReturnsFalse_643) {
  node_data nd;
  nd.set_type(NodeType::Map);

  node& key = m_memory->create_node();
  key.set_scalar("mykey");
  node& val = m_memory->create_node();
  val.set_scalar("myval");
  nd.insert(key, val, m_memory);

  EXPECT_FALSE(nd.remove(std::string("otherkey"), m_memory));
}

TEST_F(NodeDataTest_643, Remove_DecreasesSize_643) {
  node_data nd;
  nd.set_type(NodeType::Map);

  node& k1 = m_memory->create_node();
  k1.set_scalar("key1");
  node& v1 = m_memory->create_node();
  v1.set_scalar("val1");
  nd.insert(k1, v1, m_memory);

  node& k2 = m_memory->create_node();
  k2.set_scalar("key2");
  node& v2 = m_memory->create_node();
  v2.set_scalar("val2");
  nd.insert(k2, v2, m_memory);

  EXPECT_EQ(2u, nd.size());
  nd.remove(std::string("key1"), m_memory);
  EXPECT_EQ(1u, nd.size());
}

// === begin/end iterators ===

TEST_F(NodeDataTest_643, BeginEndEqual_EmptySequence_643) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  EXPECT_EQ(nd.begin(), nd.end());
}

TEST_F(NodeDataTest_643, BeginEndNotEqual_NonEmptySequence_643) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  node& n1 = m_memory->create_node();
  n1.set_scalar("val");
  nd.push_back(n1, m_memory);
  EXPECT_NE(nd.begin(), nd.end());
}

TEST_F(NodeDataTest_643, BeginEndEqual_EmptyMap_643) {
  node_data nd;
  nd.set_type(NodeType::Map);
  EXPECT_EQ(nd.begin(), nd.end());
}

// === Type changes (Sequence -> Map conversion via insert) ===

TEST_F(NodeDataTest_643, SetType_SequenceThenMap_ClearsSequence_643) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  node& n1 = m_memory->create_node();
  n1.set_scalar("val");
  nd.push_back(n1, m_memory);
  EXPECT_EQ(1u, nd.size());

  nd.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, nd.type());
  EXPECT_EQ(0u, nd.size());
}

TEST_F(NodeDataTest_643, SetType_MapThenSequence_ClearsMap_643) {
  node_data nd;
  nd.set_type(NodeType::Map);
  node& key = m_memory->create_node();
  key.set_scalar("key");
  node& val = m_memory->create_node();
  val.set_scalar("val");
  nd.insert(key, val, m_memory);
  EXPECT_EQ(1u, nd.size());

  nd.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, nd.type());
  EXPECT_EQ(0u, nd.size());
}

// === force_insert ===

TEST_F(NodeDataTest_643, ForceInsert_AddsToMap_643) {
  node_data nd;
  nd.set_type(NodeType::Map);
  nd.force_insert(std::string("key1"), std::string("val1"), m_memory);
  EXPECT_EQ(1u, nd.size());
}

TEST_F(NodeDataTest_643, ForceInsert_AllowsDuplicateKeys_643) {
  node_data nd;
  nd.set_type(NodeType::Map);
  nd.force_insert(std::string("key"), std::string("val1"), m_memory);
  nd.force_insert(std::string("key"), std::string("val2"), m_memory);
  EXPECT_EQ(2u, nd.size());
}

// === get with node& key ===

TEST_F(NodeDataTest_643, GetNodeKey_ExistingReturnsNonNull_643) {
  node_data nd;
  nd.set_type(NodeType::Map);

  node& key = m_memory->create_node();
  key.set_scalar("mykey");
  node& val = m_memory->create_node();
  val.set_scalar("myval");
  nd.insert(key, val, m_memory);

  const node_data& cnd = nd;
  const node* result = cnd.get(key, m_memory);
  EXPECT_NE(nullptr, result);
}

// === remove with node& key ===

TEST_F(NodeDataTest_643, RemoveNodeKey_ExistingReturnsTrue_643) {
  node_data nd;
  nd.set_type(NodeType::Map);

  node& key = m_memory->create_node();
  key.set_scalar("mykey");
  node& val = m_memory->create_node();
  val.set_scalar("myval");
  nd.insert(key, val, m_memory);

  EXPECT_TRUE(nd.remove(key, m_memory));
  EXPECT_EQ(0u, nd.size());
}

TEST_F(NodeDataTest_643, RemoveNodeKey_NonExistingReturnsFalse_643) {
  node_data nd;
  nd.set_type(NodeType::Map);

  node& key = m_memory->create_node();
  key.set_scalar("mykey");
  node& val = m_memory->create_node();
  val.set_scalar("myval");
  nd.insert(key, val, m_memory);

  node& otherKey = m_memory->create_node();
  otherKey.set_scalar("other");
  EXPECT_FALSE(nd.remove(otherKey, m_memory));
}

// === Changing type resets scalar ===

TEST_F(NodeDataTest_643, SetTypeNull_ClearsScalar_643) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("hello");
  EXPECT_EQ("hello", nd.scalar());

  nd.set_type(NodeType::Null);
  // After setting type to Null, the scalar should be cleared
  EXPECT_TRUE(nd.scalar().empty());
}

// === Copy/assignment deleted ===
// This is a compile-time check; we verify the class is non-copyable
// by static_assert or simply noting the deleted members.

TEST_F(NodeDataTest_643, SetScalar_LargeString_643) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  std::string largeStr(10000, 'x');
  nd.set_scalar(largeStr);
  EXPECT_EQ(largeStr, nd.scalar());
}

TEST_F(NodeDataTest_643, SetTag_LargeString_643) {
  node_data nd;
  std::string largeTag(10000, 't');
  nd.set_tag(largeTag);
  EXPECT_EQ(largeTag, nd.tag());
}

// === Sequence push_back then convert to map ===

TEST_F(NodeDataTest_643, PushBackToSequence_GetByIndex_643) {
  node_data nd;
  nd.set_type(NodeType::Sequence);

  node& n0 = m_memory->create_node();
  n0.set_scalar("zero");
  node& n1 = m_memory->create_node();
  n1.set_scalar("one");

  nd.push_back(n0, m_memory);
  nd.push_back(n1, m_memory);

  // Get by integer index in a sequence (template get)
  const node* result = nd.get(0, m_memory);
  EXPECT_NE(nullptr, result);
}

TEST_F(NodeDataTest_643, Get_IntegerKeyOutOfRange_ReturnsNull_643) {
  node_data nd;
  nd.set_type(NodeType::Sequence);

  node& n0 = m_memory->create_node();
  n0.set_scalar("zero");
  nd.push_back(n0, m_memory);

  const node* result = nd.get(5, m_memory);
  EXPECT_EQ(nullptr, result);
}

}  // namespace detail
}  // namespace YAML
