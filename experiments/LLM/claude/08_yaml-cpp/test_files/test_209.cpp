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

class NodeDataTest_209 : public ::testing::Test {
 protected:
  void SetUp() override {
    m_memory = std::make_shared<memory_holder>();
    m_pMemory = m_memory->create_holder();
  }

  std::shared_ptr<memory_holder> m_memory;
  shared_memory_holder m_pMemory;
};

// ============================================================
// Constructor / Default State Tests
// ============================================================

TEST_F(NodeDataTest_209, DefaultConstruction_IsNotDefined_209) {
  node_data nd;
  EXPECT_FALSE(nd.is_defined());
}

TEST_F(NodeDataTest_209, DefaultConstruction_TypeIsNull_209) {
  node_data nd;
  EXPECT_EQ(NodeType::Null, nd.type());
}

TEST_F(NodeDataTest_209, DefaultConstruction_TagIsEmpty_209) {
  node_data nd;
  EXPECT_TRUE(nd.tag().empty());
}

TEST_F(NodeDataTest_209, DefaultConstruction_ScalarIsEmpty_209) {
  node_data nd;
  EXPECT_TRUE(nd.scalar().empty());
}

TEST_F(NodeDataTest_209, DefaultConstruction_SizeIsZero_209) {
  node_data nd;
  EXPECT_EQ(0u, nd.size());
}

TEST_F(NodeDataTest_209, DefaultConstruction_MarkIsNull_209) {
  node_data nd;
  EXPECT_EQ(Mark::null_mark().line, nd.mark().line);
  EXPECT_EQ(Mark::null_mark().column, nd.mark().column);
  EXPECT_EQ(Mark::null_mark().pos, nd.mark().pos);
}

// ============================================================
// mark_defined Tests
// ============================================================

TEST_F(NodeDataTest_209, MarkDefined_SetsIsDefined_209) {
  node_data nd;
  nd.mark_defined();
  EXPECT_TRUE(nd.is_defined());
}

// ============================================================
// set_mark Tests
// ============================================================

TEST_F(NodeDataTest_209, SetMark_StoresMark_209) {
  node_data nd;
  Mark m;
  m.line = 10;
  m.column = 20;
  m.pos = 30;
  nd.set_mark(m);
  EXPECT_EQ(10, nd.mark().line);
  EXPECT_EQ(20, nd.mark().column);
  EXPECT_EQ(30, nd.mark().pos);
}

// ============================================================
// set_type Tests
// ============================================================

TEST_F(NodeDataTest_209, SetType_Null_209) {
  node_data nd;
  nd.set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, nd.type());
}

TEST_F(NodeDataTest_209, SetType_Scalar_209) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, nd.type());
}

TEST_F(NodeDataTest_209, SetType_Sequence_209) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, nd.type());
}

TEST_F(NodeDataTest_209, SetType_Map_209) {
  node_data nd;
  nd.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, nd.type());
}

TEST_F(NodeDataTest_209, SetType_Undefined_209) {
  node_data nd;
  nd.set_type(NodeType::Undefined);
  EXPECT_EQ(NodeType::Undefined, nd.type());
}

TEST_F(NodeDataTest_209, SetType_MarksDefined_209) {
  node_data nd;
  EXPECT_FALSE(nd.is_defined());
  nd.set_type(NodeType::Scalar);
  EXPECT_TRUE(nd.is_defined());
}

TEST_F(NodeDataTest_209, SetType_SequenceThenNull_ResetsSize_209) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  node& n = m_pMemory->create_node();
  n.set_scalar("val");
  nd.push_back(n, m_pMemory);
  EXPECT_EQ(1u, nd.size());
  nd.set_type(NodeType::Null);
  EXPECT_EQ(0u, nd.size());
}

// ============================================================
// set_tag Tests
// ============================================================

TEST_F(NodeDataTest_209, SetTag_StoresTag_209) {
  node_data nd;
  nd.set_tag("!mytag");
  EXPECT_EQ("!mytag", nd.tag());
}

TEST_F(NodeDataTest_209, SetTag_EmptyString_209) {
  node_data nd;
  nd.set_tag("!sometag");
  nd.set_tag("");
  EXPECT_EQ("", nd.tag());
}

TEST_F(NodeDataTest_209, SetTag_OverwritesPrevious_209) {
  node_data nd;
  nd.set_tag("first");
  nd.set_tag("second");
  EXPECT_EQ("second", nd.tag());
}

// ============================================================
// set_null Tests
// ============================================================

TEST_F(NodeDataTest_209, SetNull_TypeBecomesNull_209) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_null();
  EXPECT_EQ(NodeType::Null, nd.type());
}

TEST_F(NodeDataTest_209, SetNull_RemainsDefined_209) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_null();
  EXPECT_TRUE(nd.is_defined());
}

// ============================================================
// set_scalar Tests
// ============================================================

TEST_F(NodeDataTest_209, SetScalar_StoresScalar_209) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("hello");
  EXPECT_EQ("hello", nd.scalar());
}

TEST_F(NodeDataTest_209, SetScalar_EmptyString_209) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("");
  EXPECT_EQ("", nd.scalar());
}

TEST_F(NodeDataTest_209, SetScalar_Overwrites_209) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("first");
  nd.set_scalar("second");
  EXPECT_EQ("second", nd.scalar());
}

// ============================================================
// set_style Tests
// ============================================================

TEST_F(NodeDataTest_209, SetStyle_Default_209) {
  node_data nd;
  nd.set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, nd.style());
}

TEST_F(NodeDataTest_209, SetStyle_Block_209) {
  node_data nd;
  nd.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, nd.style());
}

TEST_F(NodeDataTest_209, SetStyle_Flow_209) {
  node_data nd;
  nd.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, nd.style());
}

// ============================================================
// empty_scalar Tests
// ============================================================

TEST_F(NodeDataTest_209, EmptyScalar_ReturnsEmptyString_209) {
  const std::string& es = node_data::empty_scalar();
  EXPECT_TRUE(es.empty());
}

TEST_F(NodeDataTest_209, EmptyScalar_ReturnsSameReference_209) {
  const std::string& es1 = node_data::empty_scalar();
  const std::string& es2 = node_data::empty_scalar();
  EXPECT_EQ(&es1, &es2);
}

// ============================================================
// Sequence Operations: push_back, size, begin, end
// ============================================================

TEST_F(NodeDataTest_209, PushBack_IncreasesSize_209) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  node& n1 = m_pMemory->create_node();
  n1.set_scalar("a");
  nd.push_back(n1, m_pMemory);
  EXPECT_EQ(1u, nd.size());
}

TEST_F(NodeDataTest_209, PushBack_MultipleTimes_209) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  node& n1 = m_pMemory->create_node();
  node& n2 = m_pMemory->create_node();
  node& n3 = m_pMemory->create_node();
  n1.set_scalar("a");
  n2.set_scalar("b");
  n3.set_scalar("c");
  nd.push_back(n1, m_pMemory);
  nd.push_back(n2, m_pMemory);
  nd.push_back(n3, m_pMemory);
  EXPECT_EQ(3u, nd.size());
}

TEST_F(NodeDataTest_209, BeginEnd_EmptySequence_209) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  EXPECT_EQ(nd.begin(), nd.end());
}

TEST_F(NodeDataTest_209, BeginEnd_NonEmptySequence_209) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  node& n1 = m_pMemory->create_node();
  n1.set_scalar("val");
  nd.push_back(n1, m_pMemory);
  EXPECT_NE(nd.begin(), nd.end());
}

// ============================================================
// Map Operations: insert, size, get, remove
// ============================================================

TEST_F(NodeDataTest_209, Insert_IncreasesSize_209) {
  node_data nd;
  nd.set_type(NodeType::Map);
  node& key = m_pMemory->create_node();
  key.set_scalar("key1");
  node& val = m_pMemory->create_node();
  val.set_scalar("val1");
  nd.insert(key, val, m_pMemory);
  EXPECT_EQ(1u, nd.size());
}

TEST_F(NodeDataTest_209, Insert_MultipleKeys_209) {
  node_data nd;
  nd.set_type(NodeType::Map);

  node& k1 = m_pMemory->create_node();
  k1.set_scalar("k1");
  node& v1 = m_pMemory->create_node();
  v1.set_scalar("v1");
  nd.insert(k1, v1, m_pMemory);

  node& k2 = m_pMemory->create_node();
  k2.set_scalar("k2");
  node& v2 = m_pMemory->create_node();
  v2.set_scalar("v2");
  nd.insert(k2, v2, m_pMemory);

  EXPECT_EQ(2u, nd.size());
}

TEST_F(NodeDataTest_209, GetNode_ExistingKey_ReturnsNonNull_209) {
  node_data nd;
  nd.set_type(NodeType::Map);
  node& key = m_pMemory->create_node();
  key.set_scalar("mykey");
  node& val = m_pMemory->create_node();
  val.set_scalar("myval");
  nd.insert(key, val, m_pMemory);

  const node* result = nd.get(key, m_pMemory);
  EXPECT_NE(nullptr, result);
}

TEST_F(NodeDataTest_209, GetNode_NonExistingKey_ReturnsNull_209) {
  node_data nd;
  nd.set_type(NodeType::Map);
  node& key = m_pMemory->create_node();
  key.set_scalar("nonexistent");

  const node* result = nd.get(key, m_pMemory);
  EXPECT_EQ(nullptr, result);
}

TEST_F(NodeDataTest_209, Remove_ExistingKey_ReturnsTrue_209) {
  node_data nd;
  nd.set_type(NodeType::Map);
  node& key = m_pMemory->create_node();
  key.set_scalar("mykey");
  node& val = m_pMemory->create_node();
  val.set_scalar("myval");
  nd.insert(key, val, m_pMemory);

  bool removed = nd.remove(key, m_pMemory);
  EXPECT_TRUE(removed);
}

TEST_F(NodeDataTest_209, Remove_NonExistingKey_ReturnsFalse_209) {
  node_data nd;
  nd.set_type(NodeType::Map);
  node& key = m_pMemory->create_node();
  key.set_scalar("nonexistent");

  bool removed = nd.remove(key, m_pMemory);
  EXPECT_FALSE(removed);
}

TEST_F(NodeDataTest_209, Remove_DecreasesSize_209) {
  node_data nd;
  nd.set_type(NodeType::Map);
  node& key = m_pMemory->create_node();
  key.set_scalar("mykey");
  node& val = m_pMemory->create_node();
  val.set_scalar("myval");
  nd.insert(key, val, m_pMemory);
  EXPECT_EQ(1u, nd.size());

  nd.remove(key, m_pMemory);
  EXPECT_EQ(0u, nd.size());
}

// ============================================================
// Template get/remove with string key
// ============================================================

TEST_F(NodeDataTest_209, TemplateGet_ExistingStringKey_209) {
  node_data nd;
  nd.set_type(NodeType::Map);
  node& key = m_pMemory->create_node();
  key.set_scalar("hello");
  node& val = m_pMemory->create_node();
  val.set_scalar("world");
  nd.insert(key, val, m_pMemory);

  const node* result = nd.get(std::string("hello"), m_pMemory);
  EXPECT_NE(nullptr, result);
}

TEST_F(NodeDataTest_209, TemplateGet_NonExistingStringKey_209) {
  node_data nd;
  nd.set_type(NodeType::Map);

  const node* result = nd.get(std::string("missing"), m_pMemory);
  EXPECT_EQ(nullptr, result);
}

TEST_F(NodeDataTest_209, TemplateRemove_ExistingStringKey_209) {
  node_data nd;
  nd.set_type(NodeType::Map);
  node& key = m_pMemory->create_node();
  key.set_scalar("hello");
  node& val = m_pMemory->create_node();
  val.set_scalar("world");
  nd.insert(key, val, m_pMemory);

  bool removed = nd.remove(std::string("hello"), m_pMemory);
  EXPECT_TRUE(removed);
}

TEST_F(NodeDataTest_209, TemplateRemove_NonExistingStringKey_209) {
  node_data nd;
  nd.set_type(NodeType::Map);

  bool removed = nd.remove(std::string("missing"), m_pMemory);
  EXPECT_FALSE(removed);
}

// ============================================================
// force_insert Tests
// ============================================================

TEST_F(NodeDataTest_209, ForceInsert_IncreasesSize_209) {
  node_data nd;
  nd.set_type(NodeType::Map);
  nd.force_insert(std::string("k1"), std::string("v1"), m_pMemory);
  EXPECT_EQ(1u, nd.size());
}

TEST_F(NodeDataTest_209, ForceInsert_DuplicateKeys_BothKept_209) {
  node_data nd;
  nd.set_type(NodeType::Map);
  nd.force_insert(std::string("k1"), std::string("v1"), m_pMemory);
  nd.force_insert(std::string("k1"), std::string("v2"), m_pMemory);
  // force_insert should allow duplicate keys
  EXPECT_EQ(2u, nd.size());
}

// ============================================================
// Type Transition Tests
// ============================================================

TEST_F(NodeDataTest_209, TypeTransition_NullToSequence_209) {
  node_data nd;
  EXPECT_EQ(NodeType::Null, nd.type());
  nd.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, nd.type());
  EXPECT_EQ(0u, nd.size());
}

TEST_F(NodeDataTest_209, TypeTransition_SequenceToMap_209) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  node& n = m_pMemory->create_node();
  n.set_scalar("item");
  nd.push_back(n, m_pMemory);
  EXPECT_EQ(1u, nd.size());

  nd.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, nd.type());
}

TEST_F(NodeDataTest_209, TypeTransition_MapToNull_209) {
  node_data nd;
  nd.set_type(NodeType::Map);
  node& k = m_pMemory->create_node();
  k.set_scalar("k");
  node& v = m_pMemory->create_node();
  v.set_scalar("v");
  nd.insert(k, v, m_pMemory);
  EXPECT_EQ(1u, nd.size());

  nd.set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, nd.type());
  EXPECT_EQ(0u, nd.size());
}

// ============================================================
// Boundary: Size for different types
// ============================================================

TEST_F(NodeDataTest_209, Size_NullType_IsZero_209) {
  node_data nd;
  EXPECT_EQ(0u, nd.size());
}

TEST_F(NodeDataTest_209, Size_ScalarType_IsZero_209) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("hello");
  EXPECT_EQ(0u, nd.size());
}

TEST_F(NodeDataTest_209, Size_EmptyMap_IsZero_209) {
  node_data nd;
  nd.set_type(NodeType::Map);
  EXPECT_EQ(0u, nd.size());
}

// ============================================================
// Copy prevention
// ============================================================

TEST_F(NodeDataTest_209, CopyConstructorDeleted_209) {
  EXPECT_FALSE(std::is_copy_constructible<node_data>::value);
}

TEST_F(NodeDataTest_209, CopyAssignmentDeleted_209) {
  EXPECT_FALSE(std::is_copy_assignable<node_data>::value);
}

// ============================================================
// BeginEnd for Map
// ============================================================

TEST_F(NodeDataTest_209, BeginEnd_EmptyMap_209) {
  node_data nd;
  nd.set_type(NodeType::Map);
  EXPECT_EQ(nd.begin(), nd.end());
}

TEST_F(NodeDataTest_209, BeginEnd_NonEmptyMap_209) {
  node_data nd;
  nd.set_type(NodeType::Map);
  node& k = m_pMemory->create_node();
  k.set_scalar("key");
  node& v = m_pMemory->create_node();
  v.set_scalar("val");
  nd.insert(k, v, m_pMemory);
  EXPECT_NE(nd.begin(), nd.end());
}

// ============================================================
// Push_back on Null type converts to Sequence
// ============================================================

TEST_F(NodeDataTest_209, PushBack_OnNullType_ConvertsToSequence_209) {
  node_data nd;
  EXPECT_EQ(NodeType::Null, nd.type());
  node& n = m_pMemory->create_node();
  n.set_scalar("item");
  nd.push_back(n, m_pMemory);
  EXPECT_EQ(NodeType::Sequence, nd.type());
  EXPECT_EQ(1u, nd.size());
}

// ============================================================
// Insert on Null type converts to Map
// ============================================================

TEST_F(NodeDataTest_209, Insert_OnNullType_ConvertsToMap_209) {
  node_data nd;
  EXPECT_EQ(NodeType::Null, nd.type());
  node& k = m_pMemory->create_node();
  k.set_scalar("key");
  node& v = m_pMemory->create_node();
  v.set_scalar("val");
  nd.insert(k, v, m_pMemory);
  EXPECT_EQ(NodeType::Map, nd.type());
  EXPECT_EQ(1u, nd.size());
}

}  // namespace detail
}  // namespace YAML
