#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node_data.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeDataTest_644 : public ::testing::Test {
 protected:
  void SetUp() override {
    data_ = std::make_unique<node_data>();
    pMemory_ = std::make_shared<memory>();
  }

  std::unique_ptr<node_data> data_;
  shared_memory_holder pMemory_;
};

// Test default construction state
TEST_F(NodeDataTest_644, DefaultConstruction_IsNotDefined_644) {
  EXPECT_FALSE(data_->is_defined());
}

TEST_F(NodeDataTest_644, DefaultConstruction_TypeIsNull_644) {
  EXPECT_EQ(NodeType::Null, data_->type());
}

TEST_F(NodeDataTest_644, DefaultConstruction_TagIsEmpty_644) {
  EXPECT_TRUE(data_->tag().empty());
}

TEST_F(NodeDataTest_644, DefaultConstruction_ScalarIsEmpty_644) {
  EXPECT_TRUE(data_->scalar().empty());
}

TEST_F(NodeDataTest_644, DefaultConstruction_StyleIsDefault_644) {
  EXPECT_EQ(EmitterStyle::Default, data_->style());
}

TEST_F(NodeDataTest_644, DefaultConstruction_SizeIsZero_644) {
  EXPECT_EQ(0u, data_->size());
}

// Test mark_defined
TEST_F(NodeDataTest_644, MarkDefined_SetsDefinedTrue_644) {
  data_->mark_defined();
  EXPECT_TRUE(data_->is_defined());
}

// Test set_mark
TEST_F(NodeDataTest_644, SetMark_StoresMark_644) {
  Mark m(10, 20, 30);
  data_->set_mark(m);
  EXPECT_EQ(10, data_->mark().pos);
  EXPECT_EQ(20, data_->mark().line);
  EXPECT_EQ(30, data_->mark().column);
}

TEST_F(NodeDataTest_644, SetMark_NullMark_644) {
  data_->set_mark(Mark::null_mark());
  // Should not crash; mark should be null mark
}

// Test set_type
TEST_F(NodeDataTest_644, SetType_Scalar_644) {
  data_->set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, data_->type());
}

TEST_F(NodeDataTest_644, SetType_Sequence_644) {
  data_->set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, data_->type());
}

TEST_F(NodeDataTest_644, SetType_Map_644) {
  data_->set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, data_->type());
}

TEST_F(NodeDataTest_644, SetType_Null_644) {
  data_->set_type(NodeType::Scalar);
  data_->set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, data_->type());
}

TEST_F(NodeDataTest_644, SetType_Undefined_644) {
  data_->set_type(NodeType::Undefined);
  EXPECT_EQ(NodeType::Undefined, data_->type());
}

// Test set_tag
TEST_F(NodeDataTest_644, SetTag_NonEmpty_644) {
  data_->set_tag("!mytag");
  EXPECT_EQ("!mytag", data_->tag());
}

TEST_F(NodeDataTest_644, SetTag_Empty_644) {
  data_->set_tag("!mytag");
  data_->set_tag("");
  EXPECT_EQ("", data_->tag());
}

TEST_F(NodeDataTest_644, SetTag_SpecialCharacters_644) {
  data_->set_tag("tag:yaml.org,2002:str");
  EXPECT_EQ("tag:yaml.org,2002:str", data_->tag());
}

// Test set_null
TEST_F(NodeDataTest_644, SetNull_SetsTypeToNull_644) {
  data_->set_type(NodeType::Scalar);
  data_->set_null();
  EXPECT_EQ(NodeType::Null, data_->type());
}

// Test set_scalar
TEST_F(NodeDataTest_644, SetScalar_SetsScalarValue_644) {
  data_->set_scalar("hello");
  EXPECT_EQ("hello", data_->scalar());
}

TEST_F(NodeDataTest_644, SetScalar_EmptyString_644) {
  data_->set_scalar("");
  EXPECT_EQ("", data_->scalar());
}

TEST_F(NodeDataTest_644, SetScalar_LongString_644) {
  std::string longStr(10000, 'x');
  data_->set_scalar(longStr);
  EXPECT_EQ(longStr, data_->scalar());
}

TEST_F(NodeDataTest_644, SetScalar_OverwritesPrevious_644) {
  data_->set_scalar("first");
  data_->set_scalar("second");
  EXPECT_EQ("second", data_->scalar());
}

// Test set_style
TEST_F(NodeDataTest_644, SetStyle_Block_644) {
  data_->set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, data_->style());
}

TEST_F(NodeDataTest_644, SetStyle_Flow_644) {
  data_->set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, data_->style());
}

TEST_F(NodeDataTest_644, SetStyle_Default_644) {
  data_->set_style(EmitterStyle::Flow);
  data_->set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, data_->style());
}

// Test empty_scalar
TEST_F(NodeDataTest_644, EmptyScalar_ReturnsEmptyString_644) {
  const std::string& es = node_data::empty_scalar();
  EXPECT_TRUE(es.empty());
}

TEST_F(NodeDataTest_644, EmptyScalar_ReturnsSameReference_644) {
  const std::string& es1 = node_data::empty_scalar();
  const std::string& es2 = node_data::empty_scalar();
  EXPECT_EQ(&es1, &es2);
}

// Test sequence operations
TEST_F(NodeDataTest_644, PushBack_IncreasesSize_644) {
  data_->set_type(NodeType::Sequence);
  node& n = pMemory_->create_node();
  n.set_scalar("item");
  data_->push_back(n, pMemory_);
  EXPECT_EQ(1u, data_->size());
}

TEST_F(NodeDataTest_644, PushBack_MultipleItems_644) {
  data_->set_type(NodeType::Sequence);
  for (int i = 0; i < 5; ++i) {
    node& n = pMemory_->create_node();
    n.set_scalar(std::to_string(i));
    data_->push_back(n, pMemory_);
  }
  EXPECT_EQ(5u, data_->size());
}

// Test begin/end iterators on empty sequence
TEST_F(NodeDataTest_644, BeginEndOnSequence_Empty_644) {
  data_->set_type(NodeType::Sequence);
  EXPECT_EQ(data_->begin(), data_->end());
}

// Test begin/end iterators on non-empty sequence
TEST_F(NodeDataTest_644, BeginEndOnSequence_NonEmpty_644) {
  data_->set_type(NodeType::Sequence);
  node& n = pMemory_->create_node();
  n.set_scalar("test");
  data_->push_back(n, pMemory_);
  EXPECT_NE(data_->begin(), data_->end());
}

// Test map operations
TEST_F(NodeDataTest_644, Insert_IncreasesMapSize_644) {
  data_->set_type(NodeType::Map);
  node& key = pMemory_->create_node();
  key.set_scalar("key1");
  node& val = pMemory_->create_node();
  val.set_scalar("val1");
  data_->insert(key, val, pMemory_);
  EXPECT_EQ(1u, data_->size());
}

TEST_F(NodeDataTest_644, Insert_MultipleEntries_644) {
  data_->set_type(NodeType::Map);
  for (int i = 0; i < 3; ++i) {
    node& key = pMemory_->create_node();
    key.set_scalar("key" + std::to_string(i));
    node& val = pMemory_->create_node();
    val.set_scalar("val" + std::to_string(i));
    data_->insert(key, val, pMemory_);
  }
  EXPECT_EQ(3u, data_->size());
}

// Test get on map
TEST_F(NodeDataTest_644, Get_ExistingKey_ReturnsNonNull_644) {
  data_->set_type(NodeType::Map);
  node& key = pMemory_->create_node();
  key.set_scalar("mykey");
  node& val = pMemory_->create_node();
  val.set_scalar("myval");
  data_->insert(key, val, pMemory_);

  const node* result = data_->get(std::string("mykey"), pMemory_);
  EXPECT_NE(nullptr, result);
}

TEST_F(NodeDataTest_644, Get_NonExistingKey_ReturnsNull_644) {
  data_->set_type(NodeType::Map);
  node& key = pMemory_->create_node();
  key.set_scalar("mykey");
  node& val = pMemory_->create_node();
  val.set_scalar("myval");
  data_->insert(key, val, pMemory_);

  const node* result = data_->get(std::string("nonexistent"), pMemory_);
  EXPECT_EQ(nullptr, result);
}

// Test remove on map
TEST_F(NodeDataTest_644, Remove_ExistingKey_ReturnsTrue_644) {
  data_->set_type(NodeType::Map);
  node& key = pMemory_->create_node();
  key.set_scalar("removekey");
  node& val = pMemory_->create_node();
  val.set_scalar("removeval");
  data_->insert(key, val, pMemory_);

  bool removed = data_->remove(std::string("removekey"), pMemory_);
  EXPECT_TRUE(removed);
}

TEST_F(NodeDataTest_644, Remove_NonExistingKey_ReturnsFalse_644) {
  data_->set_type(NodeType::Map);
  bool removed = data_->remove(std::string("nokey"), pMemory_);
  EXPECT_FALSE(removed);
}

TEST_F(NodeDataTest_644, Remove_DecreasesSize_644) {
  data_->set_type(NodeType::Map);
  node& key = pMemory_->create_node();
  key.set_scalar("k");
  node& val = pMemory_->create_node();
  val.set_scalar("v");
  data_->insert(key, val, pMemory_);
  EXPECT_EQ(1u, data_->size());

  data_->remove(std::string("k"), pMemory_);
  EXPECT_EQ(0u, data_->size());
}

// Test remove with node reference
TEST_F(NodeDataTest_644, RemoveByNode_ExistingKey_644) {
  data_->set_type(NodeType::Map);
  node& key = pMemory_->create_node();
  key.set_scalar("nodekey");
  node& val = pMemory_->create_node();
  val.set_scalar("nodeval");
  data_->insert(key, val, pMemory_);

  bool removed = data_->remove(key, pMemory_);
  EXPECT_TRUE(removed);
}

// Test force_insert
TEST_F(NodeDataTest_644, ForceInsert_AddsEntry_644) {
  data_->set_type(NodeType::Map);
  data_->force_insert(std::string("fkey"), std::string("fval"), pMemory_);
  EXPECT_EQ(1u, data_->size());
}

TEST_F(NodeDataTest_644, ForceInsert_AllowsDuplicateKeys_644) {
  data_->set_type(NodeType::Map);
  data_->force_insert(std::string("dup"), std::string("val1"), pMemory_);
  data_->force_insert(std::string("dup"), std::string("val2"), pMemory_);
  EXPECT_EQ(2u, data_->size());
}

// Test type transitions
TEST_F(NodeDataTest_644, TypeTransition_NullToScalar_644) {
  EXPECT_EQ(NodeType::Null, data_->type());
  data_->set_type(NodeType::Scalar);
  data_->set_scalar("value");
  EXPECT_EQ(NodeType::Scalar, data_->type());
  EXPECT_EQ("value", data_->scalar());
}

TEST_F(NodeDataTest_644, TypeTransition_SequenceToMap_644) {
  data_->set_type(NodeType::Sequence);
  node& n = pMemory_->create_node();
  n.set_scalar("item");
  data_->push_back(n, pMemory_);
  
  // Converting sequence to map
  data_->set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, data_->type());
}

// Test size on different types
TEST_F(NodeDataTest_644, Size_NullType_ReturnsZero_644) {
  EXPECT_EQ(0u, data_->size());
}

TEST_F(NodeDataTest_644, Size_ScalarType_ReturnsZero_644) {
  data_->set_type(NodeType::Scalar);
  data_->set_scalar("hello");
  EXPECT_EQ(0u, data_->size());
}

// Test begin/end on map
TEST_F(NodeDataTest_644, BeginEndOnMap_Empty_644) {
  data_->set_type(NodeType::Map);
  EXPECT_EQ(data_->begin(), data_->end());
}

TEST_F(NodeDataTest_644, BeginEndOnMap_NonEmpty_644) {
  data_->set_type(NodeType::Map);
  node& key = pMemory_->create_node();
  key.set_scalar("k");
  node& val = pMemory_->create_node();
  val.set_scalar("v");
  data_->insert(key, val, pMemory_);
  EXPECT_NE(data_->begin(), data_->end());
}

// Test mark with specific values
TEST_F(NodeDataTest_644, Mark_DefaultIsNullMark_644) {
  Mark m = data_->mark();
  Mark null_m = Mark::null_mark();
  EXPECT_EQ(null_m.pos, m.pos);
  EXPECT_EQ(null_m.line, m.line);
  EXPECT_EQ(null_m.column, m.column);
}

// Test get by node reference
TEST_F(NodeDataTest_644, GetByNodeRef_ExistingKey_644) {
  data_->set_type(NodeType::Map);
  node& key = pMemory_->create_node();
  key.set_scalar("refkey");
  node& val = pMemory_->create_node();
  val.set_scalar("refval");
  data_->insert(key, val, pMemory_);

  const node* result = data_->get(key, pMemory_);
  EXPECT_NE(nullptr, result);
}

// Test push_back on null type converts to sequence
TEST_F(NodeDataTest_644, PushBack_OnNullType_ConvertsToSequence_644) {
  node& n = pMemory_->create_node();
  n.set_scalar("item");
  data_->push_back(n, pMemory_);
  EXPECT_EQ(NodeType::Sequence, data_->type());
  EXPECT_EQ(1u, data_->size());
}

}  // namespace detail
}  // namespace YAML
