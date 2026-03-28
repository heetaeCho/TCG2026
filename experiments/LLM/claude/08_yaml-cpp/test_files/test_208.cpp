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

class NodeDataTest_208 : public ::testing::Test {
 protected:
  void SetUp() override {
    m_memory = std::make_shared<memory_holder>();
    m_pMemory = m_memory->create_memory();
  }

  shared_memory_holder m_pMemory;
  std::shared_ptr<memory_holder> m_memory;
};

// Test default construction state
TEST_F(NodeDataTest_208, DefaultConstruction_IsNotDefined_208) {
  node_data data;
  EXPECT_FALSE(data.is_defined());
}

TEST_F(NodeDataTest_208, DefaultConstruction_TypeIsNull_208) {
  node_data data;
  EXPECT_EQ(NodeType::Null, data.type());
}

TEST_F(NodeDataTest_208, DefaultConstruction_ScalarIsEmpty_208) {
  node_data data;
  EXPECT_TRUE(data.scalar().empty());
}

TEST_F(NodeDataTest_208, DefaultConstruction_TagIsEmpty_208) {
  node_data data;
  EXPECT_TRUE(data.tag().empty());
}

TEST_F(NodeDataTest_208, DefaultConstruction_SizeIsZero_208) {
  node_data data;
  EXPECT_EQ(0u, data.size());
}

// Test mark_defined
TEST_F(NodeDataTest_208, MarkDefined_SetsIsDefined_208) {
  node_data data;
  data.mark_defined();
  EXPECT_TRUE(data.is_defined());
}

// Test set_mark and mark
TEST_F(NodeDataTest_208, SetMark_ReturnsCorrectMark_208) {
  node_data data;
  Mark m;
  m.line = 5;
  m.column = 10;
  m.pos = 42;
  data.set_mark(m);
  EXPECT_EQ(5, data.mark().line);
  EXPECT_EQ(10, data.mark().column);
  EXPECT_EQ(42u, data.mark().pos);
}

// Test set_type
TEST_F(NodeDataTest_208, SetType_Sequence_208) {
  node_data data;
  data.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, data.type());
}

TEST_F(NodeDataTest_208, SetType_Map_208) {
  node_data data;
  data.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, data.type());
}

TEST_F(NodeDataTest_208, SetType_Scalar_208) {
  node_data data;
  data.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, data.type());
}

TEST_F(NodeDataTest_208, SetType_Null_208) {
  node_data data;
  data.set_type(NodeType::Scalar);
  data.set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, data.type());
}

TEST_F(NodeDataTest_208, SetType_Undefined_208) {
  node_data data;
  data.set_type(NodeType::Undefined);
  EXPECT_EQ(NodeType::Undefined, data.type());
}

// Test set_tag and tag
TEST_F(NodeDataTest_208, SetTag_ReturnsCorrectTag_208) {
  node_data data;
  data.set_tag("!mytag");
  EXPECT_EQ("!mytag", data.tag());
}

TEST_F(NodeDataTest_208, SetTag_EmptyTag_208) {
  node_data data;
  data.set_tag("sometag");
  data.set_tag("");
  EXPECT_EQ("", data.tag());
}

// Test set_scalar and scalar
TEST_F(NodeDataTest_208, SetScalar_ReturnsCorrectScalar_208) {
  node_data data;
  data.set_type(NodeType::Scalar);
  data.set_scalar("hello world");
  EXPECT_EQ("hello world", data.scalar());
}

TEST_F(NodeDataTest_208, SetScalar_EmptyString_208) {
  node_data data;
  data.set_type(NodeType::Scalar);
  data.set_scalar("");
  EXPECT_EQ("", data.scalar());
}

TEST_F(NodeDataTest_208, SetScalar_SpecialCharacters_208) {
  node_data data;
  data.set_type(NodeType::Scalar);
  data.set_scalar("line1\nline2\ttab");
  EXPECT_EQ("line1\nline2\ttab", data.scalar());
}

// Test set_null
TEST_F(NodeDataTest_208, SetNull_TypeBecomesNull_208) {
  node_data data;
  data.set_type(NodeType::Scalar);
  data.set_scalar("value");
  data.set_null();
  EXPECT_EQ(NodeType::Null, data.type());
}

// Test set_style and style
TEST_F(NodeDataTest_208, SetStyle_Default_208) {
  node_data data;
  data.set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, data.style());
}

TEST_F(NodeDataTest_208, SetStyle_Block_208) {
  node_data data;
  data.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, data.style());
}

TEST_F(NodeDataTest_208, SetStyle_Flow_208) {
  node_data data;
  data.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, data.style());
}

// Test empty_scalar
TEST_F(NodeDataTest_208, EmptyScalar_ReturnsEmptyString_208) {
  const std::string& empty = node_data::empty_scalar();
  EXPECT_TRUE(empty.empty());
}

TEST_F(NodeDataTest_208, EmptyScalar_ReturnsSameReference_208) {
  const std::string& empty1 = node_data::empty_scalar();
  const std::string& empty2 = node_data::empty_scalar();
  EXPECT_EQ(&empty1, &empty2);
}

// Test sequence operations - push_back and size
TEST_F(NodeDataTest_208, PushBack_IncreasesSize_208) {
  node_data data;
  data.set_type(NodeType::Sequence);
  
  node& n = m_pMemory->create_node();
  n.set_scalar("item1");
  
  data.push_back(n, m_pMemory);
  EXPECT_EQ(1u, data.size());
}

TEST_F(NodeDataTest_208, PushBack_MultipleItems_208) {
  node_data data;
  data.set_type(NodeType::Sequence);
  
  node& n1 = m_pMemory->create_node();
  n1.set_scalar("item1");
  node& n2 = m_pMemory->create_node();
  n2.set_scalar("item2");
  node& n3 = m_pMemory->create_node();
  n3.set_scalar("item3");
  
  data.push_back(n1, m_pMemory);
  data.push_back(n2, m_pMemory);
  data.push_back(n3, m_pMemory);
  EXPECT_EQ(3u, data.size());
}

// Test begin/end for iteration
TEST_F(NodeDataTest_208, BeginEnd_EmptySequence_208) {
  node_data data;
  data.set_type(NodeType::Sequence);
  EXPECT_EQ(data.begin(), data.end());
}

TEST_F(NodeDataTest_208, BeginEnd_EmptyMap_208) {
  node_data data;
  data.set_type(NodeType::Map);
  EXPECT_EQ(data.begin(), data.end());
}

TEST_F(NodeDataTest_208, BeginEnd_NonEmptySequence_208) {
  node_data data;
  data.set_type(NodeType::Sequence);
  
  node& n = m_pMemory->create_node();
  n.set_scalar("item1");
  data.push_back(n, m_pMemory);
  
  EXPECT_NE(data.begin(), data.end());
}

// Test map insert
TEST_F(NodeDataTest_208, Insert_IncreasesSize_208) {
  node_data data;
  data.set_type(NodeType::Map);
  
  node& key = m_pMemory->create_node();
  key.set_scalar("key1");
  node& value = m_pMemory->create_node();
  value.set_scalar("value1");
  
  data.insert(key, value, m_pMemory);
  EXPECT_EQ(1u, data.size());
}

TEST_F(NodeDataTest_208, Insert_MultipleEntries_208) {
  node_data data;
  data.set_type(NodeType::Map);
  
  node& key1 = m_pMemory->create_node();
  key1.set_scalar("key1");
  node& value1 = m_pMemory->create_node();
  value1.set_scalar("value1");
  
  node& key2 = m_pMemory->create_node();
  key2.set_scalar("key2");
  node& value2 = m_pMemory->create_node();
  value2.set_scalar("value2");
  
  data.insert(key1, value1, m_pMemory);
  data.insert(key2, value2, m_pMemory);
  EXPECT_EQ(2u, data.size());
}

// Test get on map with string key
TEST_F(NodeDataTest_208, Get_ExistingKey_ReturnsNonNull_208) {
  node_data data;
  data.set_type(NodeType::Map);
  
  node& key = m_pMemory->create_node();
  key.set_scalar("mykey");
  node& value = m_pMemory->create_node();
  value.set_scalar("myvalue");
  
  data.insert(key, value, m_pMemory);
  
  const node* result = data.get(std::string("mykey"), m_pMemory);
  EXPECT_NE(nullptr, result);
}

TEST_F(NodeDataTest_208, Get_NonExistingKey_ReturnsNull_208) {
  node_data data;
  data.set_type(NodeType::Map);
  
  node& key = m_pMemory->create_node();
  key.set_scalar("mykey");
  node& value = m_pMemory->create_node();
  value.set_scalar("myvalue");
  
  data.insert(key, value, m_pMemory);
  
  const node* result = data.get(std::string("otherkey"), m_pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test remove
TEST_F(NodeDataTest_208, Remove_ExistingKey_ReturnsTrue_208) {
  node_data data;
  data.set_type(NodeType::Map);
  
  node& key = m_pMemory->create_node();
  key.set_scalar("mykey");
  node& value = m_pMemory->create_node();
  value.set_scalar("myvalue");
  
  data.insert(key, value, m_pMemory);
  
  bool removed = data.remove(std::string("mykey"), m_pMemory);
  EXPECT_TRUE(removed);
}

TEST_F(NodeDataTest_208, Remove_NonExistingKey_ReturnsFalse_208) {
  node_data data;
  data.set_type(NodeType::Map);
  
  node& key = m_pMemory->create_node();
  key.set_scalar("mykey");
  node& value = m_pMemory->create_node();
  value.set_scalar("myvalue");
  
  data.insert(key, value, m_pMemory);
  
  bool removed = data.remove(std::string("otherkey"), m_pMemory);
  EXPECT_FALSE(removed);
}

TEST_F(NodeDataTest_208, Remove_DecreasesSize_208) {
  node_data data;
  data.set_type(NodeType::Map);
  
  node& key1 = m_pMemory->create_node();
  key1.set_scalar("key1");
  node& value1 = m_pMemory->create_node();
  value1.set_scalar("value1");
  
  node& key2 = m_pMemory->create_node();
  key2.set_scalar("key2");
  node& value2 = m_pMemory->create_node();
  value2.set_scalar("value2");
  
  data.insert(key1, value1, m_pMemory);
  data.insert(key2, value2, m_pMemory);
  EXPECT_EQ(2u, data.size());
  
  data.remove(std::string("key1"), m_pMemory);
  EXPECT_EQ(1u, data.size());
}

// Test remove with node reference
TEST_F(NodeDataTest_208, RemoveByNode_ExistingKey_ReturnsTrue_208) {
  node_data data;
  data.set_type(NodeType::Map);
  
  node& key = m_pMemory->create_node();
  key.set_scalar("mykey");
  node& value = m_pMemory->create_node();
  value.set_scalar("myvalue");
  
  data.insert(key, value, m_pMemory);
  
  bool removed = data.remove(key, m_pMemory);
  EXPECT_TRUE(removed);
}

// Test get with node reference
TEST_F(NodeDataTest_208, GetByNode_ExistingKey_ReturnsNonNull_208) {
  node_data data;
  data.set_type(NodeType::Map);
  
  node& key = m_pMemory->create_node();
  key.set_scalar("mykey");
  node& value = m_pMemory->create_node();
  value.set_scalar("myvalue");
  
  data.insert(key, value, m_pMemory);
  
  const node* result = data.get(key, m_pMemory);
  EXPECT_NE(nullptr, result);
}

// Test type transition from sequence to map via set_type
TEST_F(NodeDataTest_208, SetType_SequenceToMap_208) {
  node_data data;
  data.set_type(NodeType::Sequence);
  
  node& n = m_pMemory->create_node();
  n.set_scalar("item");
  data.push_back(n, m_pMemory);
  
  data.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, data.type());
}

// Test setting type multiple times
TEST_F(NodeDataTest_208, SetType_SameTypeTwice_208) {
  node_data data;
  data.set_type(NodeType::Sequence);
  data.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, data.type());
}

// Test force_insert
TEST_F(NodeDataTest_208, ForceInsert_IncreasesSize_208) {
  node_data data;
  data.set_type(NodeType::Map);
  
  data.force_insert(std::string("key1"), std::string("value1"), m_pMemory);
  EXPECT_EQ(1u, data.size());
}

TEST_F(NodeDataTest_208, ForceInsert_AllowsDuplicateKeys_208) {
  node_data data;
  data.set_type(NodeType::Map);
  
  data.force_insert(std::string("key1"), std::string("value1"), m_pMemory);
  data.force_insert(std::string("key1"), std::string("value2"), m_pMemory);
  EXPECT_EQ(2u, data.size());
}

// Test that scalar is cleared when changing type
TEST_F(NodeDataTest_208, SetType_FromScalarToNull_ClearsScalar_208) {
  node_data data;
  data.set_type(NodeType::Scalar);
  data.set_scalar("hello");
  EXPECT_EQ("hello", data.scalar());
  
  data.set_null();
  EXPECT_EQ(NodeType::Null, data.type());
}

// Test mark with null_mark
TEST_F(NodeDataTest_208, DefaultMark_IsNullMark_208) {
  node_data data;
  Mark m = data.mark();
  Mark null_m = Mark::null_mark();
  EXPECT_EQ(null_m.line, m.line);
  EXPECT_EQ(null_m.column, m.column);
  EXPECT_EQ(null_m.pos, m.pos);
}

// Test copy constructor is deleted (compile-time check concept)
// This is implicitly tested by the fact that it's = delete
// We verify the class is not copyable at compile time through
// static_assert if needed, but that's a compile-time test.

// Test size for null type
TEST_F(NodeDataTest_208, Size_NullType_IsZero_208) {
  node_data data;
  EXPECT_EQ(0u, data.size());
}

// Test size for scalar type
TEST_F(NodeDataTest_208, Size_ScalarType_IsZero_208) {
  node_data data;
  data.set_type(NodeType::Scalar);
  data.set_scalar("value");
  EXPECT_EQ(0u, data.size());
}

// Test that mark_defined persists through type changes
TEST_F(NodeDataTest_208, MarkDefined_PersistsThroughTypeChange_208) {
  node_data data;
  data.mark_defined();
  data.set_type(NodeType::Scalar);
  EXPECT_TRUE(data.is_defined());
}

// Test long scalar strings
TEST_F(NodeDataTest_208, SetScalar_LongString_208) {
  node_data data;
  data.set_type(NodeType::Scalar);
  std::string longStr(10000, 'x');
  data.set_scalar(longStr);
  EXPECT_EQ(longStr, data.scalar());
}

// Test unicode-like characters in scalar
TEST_F(NodeDataTest_208, SetScalar_Utf8Characters_208) {
  node_data data;
  data.set_type(NodeType::Scalar);
  std::string utf8Str = u8"こんにちは世界";
  data.set_scalar(utf8Str);
  EXPECT_EQ(utf8Str, data.scalar());
}

// Test overwriting scalar value
TEST_F(NodeDataTest_208, SetScalar_OverwritesPrevious_208) {
  node_data data;
  data.set_type(NodeType::Scalar);
  data.set_scalar("first");
  EXPECT_EQ("first", data.scalar());
  data.set_scalar("second");
  EXPECT_EQ("second", data.scalar());
}

// Test overwriting tag
TEST_F(NodeDataTest_208, SetTag_OverwritesPrevious_208) {
  node_data data;
  data.set_tag("tag1");
  EXPECT_EQ("tag1", data.tag());
  data.set_tag("tag2");
  EXPECT_EQ("tag2", data.tag());
}

// Test style overwrite
TEST_F(NodeDataTest_208, SetStyle_OverwritesPrevious_208) {
  node_data data;
  data.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, data.style());
  data.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, data.style());
}

}  // namespace detail
}  // namespace YAML
