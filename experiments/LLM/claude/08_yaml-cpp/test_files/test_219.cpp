#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/node_data.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"
#include "yaml-cpp/mark.h"

namespace YAML {
namespace detail {

class NodeRefTest_219 : public ::testing::Test {
 protected:
  void SetUp() override {
    ref_ = std::make_unique<node_ref>();
    pMemory_ = std::make_shared<memory>();
  }

  std::unique_ptr<node_ref> ref_;
  shared_memory_holder pMemory_;
};

// Test default construction - node should not be defined
TEST_F(NodeRefTest_219, DefaultConstruction_IsNotDefined_219) {
  EXPECT_FALSE(ref_->is_defined());
}

// Test default construction - type should be Null
TEST_F(NodeRefTest_219, DefaultConstruction_TypeIsNull_219) {
  EXPECT_EQ(NodeType::Null, ref_->type());
}

// Test default construction - mark should be null
TEST_F(NodeRefTest_219, DefaultConstruction_MarkIsNull_219) {
  EXPECT_TRUE(ref_->mark().is_null());
}

// Test default construction - scalar should be empty
TEST_F(NodeRefTest_219, DefaultConstruction_ScalarIsEmpty_219) {
  EXPECT_TRUE(ref_->scalar().empty());
}

// Test default construction - tag should be empty
TEST_F(NodeRefTest_219, DefaultConstruction_TagIsEmpty_219) {
  EXPECT_TRUE(ref_->tag().empty());
}

// Test default construction - size should be 0
TEST_F(NodeRefTest_219, DefaultConstruction_SizeIsZero_219) {
  EXPECT_EQ(0u, ref_->size());
}

// Test mark_defined
TEST_F(NodeRefTest_219, MarkDefined_MakesNodeDefined_219) {
  ref_->mark_defined();
  EXPECT_TRUE(ref_->is_defined());
}

// Test set_mark with a specific mark
TEST_F(NodeRefTest_219, SetMark_SetsMarkCorrectly_219) {
  Mark m;
  ref_->set_mark(m);
  // After setting a default mark, it should be retrievable
  const Mark& retrieved = ref_->mark();
  EXPECT_EQ(m.pos, retrieved.pos);
  EXPECT_EQ(m.line, retrieved.line);
  EXPECT_EQ(m.column, retrieved.column);
}

// Test set_mark with null mark
TEST_F(NodeRefTest_219, SetMark_NullMark_219) {
  Mark m = Mark::null_mark();
  ref_->set_mark(m);
  EXPECT_TRUE(ref_->mark().is_null());
}

// Test set_type to Scalar
TEST_F(NodeRefTest_219, SetType_Scalar_219) {
  ref_->set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, ref_->type());
}

// Test set_type to Sequence
TEST_F(NodeRefTest_219, SetType_Sequence_219) {
  ref_->set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, ref_->type());
}

// Test set_type to Map
TEST_F(NodeRefTest_219, SetType_Map_219) {
  ref_->set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, ref_->type());
}

// Test set_type to Null
TEST_F(NodeRefTest_219, SetType_Null_219) {
  ref_->set_type(NodeType::Scalar);
  ref_->set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, ref_->type());
}

// Test set_type to Undefined
TEST_F(NodeRefTest_219, SetType_Undefined_219) {
  ref_->set_type(NodeType::Undefined);
  EXPECT_EQ(NodeType::Undefined, ref_->type());
}

// Test set_tag
TEST_F(NodeRefTest_219, SetTag_SetsTagCorrectly_219) {
  ref_->set_tag("!custom_tag");
  EXPECT_EQ("!custom_tag", ref_->tag());
}

// Test set_tag with empty string
TEST_F(NodeRefTest_219, SetTag_EmptyString_219) {
  ref_->set_tag("");
  EXPECT_EQ("", ref_->tag());
}

// Test set_null
TEST_F(NodeRefTest_219, SetNull_SetsTypeToNull_219) {
  ref_->set_type(NodeType::Scalar);
  ref_->set_null();
  EXPECT_EQ(NodeType::Null, ref_->type());
}

// Test set_scalar
TEST_F(NodeRefTest_219, SetScalar_SetsScalarCorrectly_219) {
  ref_->set_scalar("hello");
  EXPECT_EQ("hello", ref_->scalar());
}

// Test set_scalar with empty string
TEST_F(NodeRefTest_219, SetScalar_EmptyString_219) {
  ref_->set_scalar("");
  EXPECT_EQ("", ref_->scalar());
}

// Test set_scalar with special characters
TEST_F(NodeRefTest_219, SetScalar_SpecialCharacters_219) {
  ref_->set_scalar("hello\nworld\ttab");
  EXPECT_EQ("hello\nworld\ttab", ref_->scalar());
}

// Test set_style
TEST_F(NodeRefTest_219, SetStyle_Block_219) {
  ref_->set_type(NodeType::Sequence);
  ref_->set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, ref_->style());
}

// Test set_style Flow
TEST_F(NodeRefTest_219, SetStyle_Flow_219) {
  ref_->set_type(NodeType::Sequence);
  ref_->set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, ref_->style());
}

// Test set_style Default
TEST_F(NodeRefTest_219, SetStyle_Default_219) {
  ref_->set_type(NodeType::Sequence);
  ref_->set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, ref_->style());
}

// Test set_data copies data from another node_ref
TEST_F(NodeRefTest_219, SetData_CopiesFromOtherRef_219) {
  node_ref other;
  other.set_type(NodeType::Scalar);
  other.set_scalar("test_value");
  other.set_tag("!tag");
  other.mark_defined();

  ref_->set_data(other);
  
  EXPECT_EQ("test_value", ref_->scalar());
  EXPECT_EQ("!tag", ref_->tag());
}

// Test push_back on sequence
TEST_F(NodeRefTest_219, PushBack_IncreasesSize_219) {
  ref_->set_type(NodeType::Sequence);
  
  node& n = pMemory_->create_node();
  n.set_scalar("item1");
  
  ref_->push_back(n, pMemory_);
  EXPECT_EQ(1u, ref_->size());
}

// Test push_back multiple items
TEST_F(NodeRefTest_219, PushBack_MultipleItems_219) {
  ref_->set_type(NodeType::Sequence);
  
  node& n1 = pMemory_->create_node();
  n1.set_scalar("item1");
  node& n2 = pMemory_->create_node();
  n2.set_scalar("item2");
  node& n3 = pMemory_->create_node();
  n3.set_scalar("item3");
  
  ref_->push_back(n1, pMemory_);
  ref_->push_back(n2, pMemory_);
  ref_->push_back(n3, pMemory_);
  
  EXPECT_EQ(3u, ref_->size());
}

// Test begin and end on empty sequence
TEST_F(NodeRefTest_219, BeginEndOnEmptySequence_219) {
  ref_->set_type(NodeType::Sequence);
  EXPECT_EQ(ref_->begin(), ref_->end());
}

// Test begin and end on non-empty sequence
TEST_F(NodeRefTest_219, BeginEndOnNonEmptySequence_219) {
  ref_->set_type(NodeType::Sequence);
  
  node& n = pMemory_->create_node();
  n.set_scalar("item");
  ref_->push_back(n, pMemory_);
  
  EXPECT_NE(ref_->begin(), ref_->end());
}

// Test insert on map
TEST_F(NodeRefTest_219, Insert_IncreasesSize_219) {
  ref_->set_type(NodeType::Map);
  
  node& key = pMemory_->create_node();
  key.set_scalar("key1");
  node& value = pMemory_->create_node();
  value.set_scalar("value1");
  
  ref_->insert(key, value, pMemory_);
  EXPECT_EQ(1u, ref_->size());
}

// Test get on map with string key
TEST_F(NodeRefTest_219, Get_ExistingKey_ReturnsNode_219) {
  ref_->set_type(NodeType::Map);
  
  node& key = pMemory_->create_node();
  key.set_scalar("mykey");
  node& value = pMemory_->create_node();
  value.set_scalar("myvalue");
  
  ref_->insert(key, value, pMemory_);
  
  node* result = ref_->get(std::string("mykey"), pMemory_);
  EXPECT_NE(nullptr, result);
}

// Test get with non-existing key returns nullptr
TEST_F(NodeRefTest_219, Get_NonExistingKey_ReturnsNull_219) {
  ref_->set_type(NodeType::Map);
  
  node* result = ref_->get(std::string("nonexistent"), pMemory_);
  EXPECT_EQ(nullptr, result);
}

// Test remove on map
TEST_F(NodeRefTest_219, Remove_ExistingKey_ReturnsTrue_219) {
  ref_->set_type(NodeType::Map);
  
  node& key = pMemory_->create_node();
  key.set_scalar("key_to_remove");
  node& value = pMemory_->create_node();
  value.set_scalar("value");
  
  ref_->insert(key, value, pMemory_);
  
  bool removed = ref_->remove(std::string("key_to_remove"), pMemory_);
  EXPECT_TRUE(removed);
}

// Test remove with non-existing key returns false
TEST_F(NodeRefTest_219, Remove_NonExistingKey_ReturnsFalse_219) {
  ref_->set_type(NodeType::Map);
  
  bool removed = ref_->remove(std::string("nonexistent"), pMemory_);
  EXPECT_FALSE(removed);
}

// Test remove with node key
TEST_F(NodeRefTest_219, Remove_NodeKey_ExistingKey_ReturnsTrue_219) {
  ref_->set_type(NodeType::Map);
  
  node& key = pMemory_->create_node();
  key.set_scalar("node_key");
  node& value = pMemory_->create_node();
  value.set_scalar("node_value");
  
  ref_->insert(key, value, pMemory_);
  
  bool removed = ref_->remove(key, pMemory_);
  EXPECT_TRUE(removed);
}

// Test get with node key
TEST_F(NodeRefTest_219, Get_NodeKey_ExistingKey_ReturnsNode_219) {
  ref_->set_type(NodeType::Map);
  
  node& key = pMemory_->create_node();
  key.set_scalar("node_key");
  node& value = pMemory_->create_node();
  value.set_scalar("node_value");
  
  ref_->insert(key, value, pMemory_);
  
  node* result = ref_->get(key, pMemory_);
  EXPECT_NE(nullptr, result);
}

// Test changing type resets content
TEST_F(NodeRefTest_219, SetType_ChangingTypeResetsContent_219) {
  ref_->set_type(NodeType::Scalar);
  ref_->set_scalar("some value");
  
  ref_->set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, ref_->type());
  EXPECT_EQ(0u, ref_->size());
}

// Test force_insert on map
TEST_F(NodeRefTest_219, ForceInsert_AddsToMap_219) {
  ref_->set_type(NodeType::Map);
  
  ref_->force_insert(std::string("forced_key"), std::string("forced_value"), pMemory_);
  EXPECT_EQ(1u, ref_->size());
}

// Test set_scalar sets type to Scalar
TEST_F(NodeRefTest_219, SetScalar_SetsTypeToScalar_219) {
  ref_->set_scalar("test");
  EXPECT_EQ(NodeType::Scalar, ref_->type());
}

// Test multiple tag changes
TEST_F(NodeRefTest_219, SetTag_MultipleChanges_219) {
  ref_->set_tag("!first");
  EXPECT_EQ("!first", ref_->tag());
  ref_->set_tag("!second");
  EXPECT_EQ("!second", ref_->tag());
  ref_->set_tag("!third");
  EXPECT_EQ("!third", ref_->tag());
}

// Test multiple scalar changes
TEST_F(NodeRefTest_219, SetScalar_MultipleChanges_219) {
  ref_->set_scalar("first");
  EXPECT_EQ("first", ref_->scalar());
  ref_->set_scalar("second");
  EXPECT_EQ("second", ref_->scalar());
}

// Test size on null type
TEST_F(NodeRefTest_219, Size_NullType_ReturnsZero_219) {
  EXPECT_EQ(0u, ref_->size());
}

// Test begin and end on null type
TEST_F(NodeRefTest_219, BeginEnd_NullType_AreEqual_219) {
  EXPECT_EQ(ref_->begin(), ref_->end());
}

// Test long scalar value
TEST_F(NodeRefTest_219, SetScalar_LongString_219) {
  std::string longStr(10000, 'x');
  ref_->set_scalar(longStr);
  EXPECT_EQ(longStr, ref_->scalar());
}

// Test unicode-like scalar
TEST_F(NodeRefTest_219, SetScalar_UnicodeCharacters_219) {
  ref_->set_scalar("日本語テスト");
  EXPECT_EQ("日本語テスト", ref_->scalar());
}

}  // namespace detail
}  // namespace YAML
