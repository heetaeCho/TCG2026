#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node_data.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeDataTest_646 : public ::testing::Test {
 protected:
  void SetUp() override {
    data_ = std::make_unique<node_data>();
    pMemory_ = std::make_shared<memory>();
  }

  std::unique_ptr<node_data> data_;
  shared_memory_holder pMemory_;
};

// Test default construction state
TEST_F(NodeDataTest_646, DefaultConstruction_IsNotDefined_646) {
  EXPECT_FALSE(data_->is_defined());
}

TEST_F(NodeDataTest_646, DefaultConstruction_TypeIsNull_646) {
  EXPECT_EQ(NodeType::Null, data_->type());
}

TEST_F(NodeDataTest_646, DefaultConstruction_ScalarIsEmpty_646) {
  EXPECT_TRUE(data_->scalar().empty());
}

TEST_F(NodeDataTest_646, DefaultConstruction_TagIsEmpty_646) {
  EXPECT_TRUE(data_->tag().empty());
}

TEST_F(NodeDataTest_646, DefaultConstruction_SizeIsZero_646) {
  EXPECT_EQ(0u, data_->size());
}

// Test mark_defined
TEST_F(NodeDataTest_646, MarkDefined_SetsDefined_646) {
  data_->mark_defined();
  EXPECT_TRUE(data_->is_defined());
}

// Test set_mark
TEST_F(NodeDataTest_646, SetMark_StoresMark_646) {
  Mark m(5, 10, 15);
  data_->set_mark(m);
  EXPECT_EQ(5, data_->mark().line);
  EXPECT_EQ(10, data_->mark().column);
  EXPECT_EQ(15, data_->mark().pos);
}

// Test set_type
TEST_F(NodeDataTest_646, SetType_Scalar_646) {
  data_->set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, data_->type());
  EXPECT_TRUE(data_->is_defined());
}

TEST_F(NodeDataTest_646, SetType_Sequence_646) {
  data_->set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, data_->type());
  EXPECT_TRUE(data_->is_defined());
}

TEST_F(NodeDataTest_646, SetType_Map_646) {
  data_->set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, data_->type());
  EXPECT_TRUE(data_->is_defined());
}

TEST_F(NodeDataTest_646, SetType_Null_646) {
  data_->set_type(NodeType::Scalar);
  data_->set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, data_->type());
}

TEST_F(NodeDataTest_646, SetType_Undefined_646) {
  data_->set_type(NodeType::Scalar);
  data_->set_type(NodeType::Undefined);
  EXPECT_EQ(NodeType::Undefined, data_->type());
}

// Test set_tag
TEST_F(NodeDataTest_646, SetTag_StoresTag_646) {
  data_->set_tag("!mytag");
  EXPECT_EQ("!mytag", data_->tag());
}

TEST_F(NodeDataTest_646, SetTag_EmptyTag_646) {
  data_->set_tag("");
  EXPECT_EQ("", data_->tag());
}

// Test set_null
TEST_F(NodeDataTest_646, SetNull_SetsTypeToNull_646) {
  data_->set_type(NodeType::Scalar);
  data_->set_null();
  EXPECT_EQ(NodeType::Null, data_->type());
  EXPECT_TRUE(data_->is_defined());
}

// Test set_scalar
TEST_F(NodeDataTest_646, SetScalar_StoresScalar_646) {
  data_->set_scalar("hello");
  EXPECT_EQ("hello", data_->scalar());
  EXPECT_EQ(NodeType::Scalar, data_->type());
  EXPECT_TRUE(data_->is_defined());
}

TEST_F(NodeDataTest_646, SetScalar_EmptyString_646) {
  data_->set_scalar("");
  EXPECT_EQ("", data_->scalar());
  EXPECT_EQ(NodeType::Scalar, data_->type());
  EXPECT_TRUE(data_->is_defined());
}

TEST_F(NodeDataTest_646, SetScalar_OverwritesPrevious_646) {
  data_->set_scalar("first");
  data_->set_scalar("second");
  EXPECT_EQ("second", data_->scalar());
}

TEST_F(NodeDataTest_646, SetScalar_LongString_646) {
  std::string longStr(10000, 'x');
  data_->set_scalar(longStr);
  EXPECT_EQ(longStr, data_->scalar());
}

// Test set_style
TEST_F(NodeDataTest_646, SetStyle_Block_646) {
  data_->set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, data_->style());
}

TEST_F(NodeDataTest_646, SetStyle_Flow_646) {
  data_->set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, data_->style());
}

TEST_F(NodeDataTest_646, SetStyle_Default_646) {
  data_->set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, data_->style());
}

// Test empty_scalar
TEST_F(NodeDataTest_646, EmptyScalar_ReturnsEmptyString_646) {
  const std::string& es = node_data::empty_scalar();
  EXPECT_TRUE(es.empty());
}

TEST_F(NodeDataTest_646, EmptyScalar_ReturnsSameReference_646) {
  const std::string& es1 = node_data::empty_scalar();
  const std::string& es2 = node_data::empty_scalar();
  EXPECT_EQ(&es1, &es2);
}

// Test sequence operations (push_back, size, begin, end)
TEST_F(NodeDataTest_646, PushBack_IncreasesSize_646) {
  data_->set_type(NodeType::Sequence);
  node& n = pMemory_->create_node();
  n.set_scalar("item1");
  data_->push_back(n, pMemory_);
  EXPECT_EQ(1u, data_->size());
}

TEST_F(NodeDataTest_646, PushBack_MultipleTimes_646) {
  data_->set_type(NodeType::Sequence);
  for (int i = 0; i < 5; ++i) {
    node& n = pMemory_->create_node();
    n.set_scalar("item");
    data_->push_back(n, pMemory_);
  }
  EXPECT_EQ(5u, data_->size());
}

TEST_F(NodeDataTest_646, PushBack_OnNullConvertsToSequence_646) {
  node& n = pMemory_->create_node();
  n.set_scalar("item");
  data_->push_back(n, pMemory_);
  EXPECT_EQ(NodeType::Sequence, data_->type());
  EXPECT_EQ(1u, data_->size());
}

// Test begin/end iterators for empty sequence
TEST_F(NodeDataTest_646, BeginEnd_EmptySequence_646) {
  data_->set_type(NodeType::Sequence);
  EXPECT_EQ(data_->begin(), data_->end());
}

// Test map operations (insert, get, remove)
TEST_F(NodeDataTest_646, Insert_AddsMapEntry_646) {
  data_->set_type(NodeType::Map);
  node& key = pMemory_->create_node();
  key.set_scalar("key1");
  node& value = pMemory_->create_node();
  value.set_scalar("value1");
  data_->insert(key, value, pMemory_);
  EXPECT_EQ(1u, data_->size());
}

TEST_F(NodeDataTest_646, Get_ExistingKey_ReturnsNode_646) {
  data_->set_type(NodeType::Map);
  node& key = pMemory_->create_node();
  key.set_scalar("mykey");
  node& value = pMemory_->create_node();
  value.set_scalar("myvalue");
  data_->insert(key, value, pMemory_);

  // Get using template version with string key
  const node* result = data_->get(std::string("mykey"), pMemory_);
  EXPECT_NE(nullptr, result);
}

TEST_F(NodeDataTest_646, Get_NonExistingKey_ReturnsNull_646) {
  data_->set_type(NodeType::Map);
  node& key = pMemory_->create_node();
  key.set_scalar("mykey");
  node& value = pMemory_->create_node();
  value.set_scalar("myvalue");
  data_->insert(key, value, pMemory_);

  const node* result = data_->get(std::string("nonexistent"), pMemory_);
  EXPECT_EQ(nullptr, result);
}

TEST_F(NodeDataTest_646, Remove_ExistingKey_ReturnsTrueAndDecreasesSize_646) {
  data_->set_type(NodeType::Map);
  node& key = pMemory_->create_node();
  key.set_scalar("mykey");
  node& value = pMemory_->create_node();
  value.set_scalar("myvalue");
  data_->insert(key, value, pMemory_);
  EXPECT_EQ(1u, data_->size());

  bool removed = data_->remove(std::string("mykey"), pMemory_);
  EXPECT_TRUE(removed);
  EXPECT_EQ(0u, data_->size());
}

TEST_F(NodeDataTest_646, Remove_NonExistingKey_ReturnsFalse_646) {
  data_->set_type(NodeType::Map);
  bool removed = data_->remove(std::string("nonexistent"), pMemory_);
  EXPECT_FALSE(removed);
}

// Test force_insert
TEST_F(NodeDataTest_646, ForceInsert_AddsEntry_646) {
  data_->set_type(NodeType::Map);
  data_->force_insert(std::string("key1"), std::string("value1"), pMemory_);
  EXPECT_EQ(1u, data_->size());
}

TEST_F(NodeDataTest_646, ForceInsert_AllowsDuplicateKeys_646) {
  data_->set_type(NodeType::Map);
  data_->force_insert(std::string("key1"), std::string("value1"), pMemory_);
  data_->force_insert(std::string("key1"), std::string("value2"), pMemory_);
  EXPECT_EQ(2u, data_->size());
}

// Test type transitions
TEST_F(NodeDataTest_646, TypeTransition_ScalarToSequence_646) {
  data_->set_scalar("hello");
  EXPECT_EQ(NodeType::Scalar, data_->type());
  data_->set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, data_->type());
  EXPECT_EQ(0u, data_->size());
}

TEST_F(NodeDataTest_646, TypeTransition_ScalarToMap_646) {
  data_->set_scalar("hello");
  EXPECT_EQ(NodeType::Scalar, data_->type());
  data_->set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, data_->type());
  EXPECT_EQ(0u, data_->size());
}

TEST_F(NodeDataTest_646, TypeTransition_SequenceToMap_646) {
  data_->set_type(NodeType::Sequence);
  node& n1 = pMemory_->create_node();
  n1.set_scalar("item1");
  data_->push_back(n1, pMemory_);
  node& n2 = pMemory_->create_node();
  n2.set_scalar("item2");
  data_->push_back(n2, pMemory_);
  
  data_->set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, data_->type());
}

// Test that set_scalar with special characters works
TEST_F(NodeDataTest_646, SetScalar_SpecialCharacters_646) {
  data_->set_scalar("hello\nworld\ttab");
  EXPECT_EQ("hello\nworld\ttab", data_->scalar());
}

TEST_F(NodeDataTest_646, SetScalar_UnicodeCharacters_646) {
  data_->set_scalar("こんにちは");
  EXPECT_EQ("こんにちは", data_->scalar());
}

// Test get with node reference
TEST_F(NodeDataTest_646, GetByNodeRef_ExistingKey_646) {
  data_->set_type(NodeType::Map);
  node& key = pMemory_->create_node();
  key.set_scalar("mapkey");
  node& value = pMemory_->create_node();
  value.set_scalar("mapvalue");
  data_->insert(key, value, pMemory_);

  node& lookupKey = pMemory_->create_node();
  lookupKey.set_scalar("mapkey");
  const node* result = data_->get(lookupKey, pMemory_);
  EXPECT_NE(nullptr, result);
}

TEST_F(NodeDataTest_646, GetByNodeRef_NonExistingKey_646) {
  data_->set_type(NodeType::Map);
  node& lookupKey = pMemory_->create_node();
  lookupKey.set_scalar("nonexistent");
  const node* result = data_->get(lookupKey, pMemory_);
  EXPECT_EQ(nullptr, result);
}

// Test remove with node reference
TEST_F(NodeDataTest_646, RemoveByNodeRef_ExistingKey_646) {
  data_->set_type(NodeType::Map);
  node& key = pMemory_->create_node();
  key.set_scalar("toremove");
  node& value = pMemory_->create_node();
  value.set_scalar("val");
  data_->insert(key, value, pMemory_);

  node& removeKey = pMemory_->create_node();
  removeKey.set_scalar("toremove");
  bool removed = data_->remove(removeKey, pMemory_);
  EXPECT_TRUE(removed);
}

TEST_F(NodeDataTest_646, RemoveByNodeRef_NonExistingKey_646) {
  data_->set_type(NodeType::Map);
  node& removeKey = pMemory_->create_node();
  removeKey.set_scalar("nonexistent");
  bool removed = data_->remove(removeKey, pMemory_);
  EXPECT_FALSE(removed);
}

// Test map with multiple entries
TEST_F(NodeDataTest_646, Map_MultipleEntries_646) {
  data_->set_type(NodeType::Map);
  for (int i = 0; i < 10; ++i) {
    node& key = pMemory_->create_node();
    key.set_scalar("key" + std::to_string(i));
    node& value = pMemory_->create_node();
    value.set_scalar("value" + std::to_string(i));
    data_->insert(key, value, pMemory_);
  }
  EXPECT_EQ(10u, data_->size());
}

// Test begin/end for empty map
TEST_F(NodeDataTest_646, BeginEnd_EmptyMap_646) {
  data_->set_type(NodeType::Map);
  EXPECT_EQ(data_->begin(), data_->end());
}

// Test that mark defaults to null mark
TEST_F(NodeDataTest_646, DefaultMark_IsNullMark_646) {
  Mark nullMark = Mark::null_mark();
  EXPECT_EQ(nullMark.line, data_->mark().line);
  EXPECT_EQ(nullMark.column, data_->mark().column);
  EXPECT_EQ(nullMark.pos, data_->mark().pos);
}

// Test set_null after scalar
TEST_F(NodeDataTest_646, SetNull_AfterScalar_646) {
  data_->set_scalar("hello");
  EXPECT_EQ(NodeType::Scalar, data_->type());
  data_->set_null();
  EXPECT_EQ(NodeType::Null, data_->type());
  EXPECT_TRUE(data_->is_defined());
}

// Test size for Null type
TEST_F(NodeDataTest_646, Size_NullType_IsZero_646) {
  EXPECT_EQ(0u, data_->size());
}

// Test size for Scalar type
TEST_F(NodeDataTest_646, Size_ScalarType_IsZero_646) {
  data_->set_scalar("hello");
  EXPECT_EQ(0u, data_->size());
}

// Test get on non-map/sequence type returns null
TEST_F(NodeDataTest_646, Get_OnScalarType_ReturnsNull_646) {
  data_->set_scalar("hello");
  const node* result = data_->get(std::string("key"), pMemory_);
  EXPECT_EQ(nullptr, result);
}

}  // namespace detail
}  // namespace YAML
