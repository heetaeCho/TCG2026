#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"
#include "yaml-cpp/node/type.h"
#include "yaml-cpp/emitterstyle.h"
#include "yaml-cpp/mark.h"

#include <string>
#include <memory>

namespace YAML {
namespace detail {

class NodeRefTest_221 : public ::testing::Test {
 protected:
  void SetUp() override {
    ref_ = std::make_unique<node_ref>();
    pMemory_ = std::make_shared<memory>();
  }

  std::unique_ptr<node_ref> ref_;
  shared_memory_holder pMemory_;
};

// Test default construction - node should not be defined initially
TEST_F(NodeRefTest_221, DefaultConstruction_IsNotDefined_221) {
  EXPECT_FALSE(ref_->is_defined());
}

// Test default type is Null
TEST_F(NodeRefTest_221, DefaultConstruction_TypeIsNull_221) {
  EXPECT_EQ(NodeType::Null, ref_->type());
}

// Test mark_defined makes the node defined
TEST_F(NodeRefTest_221, MarkDefined_MakesNodeDefined_221) {
  ref_->mark_defined();
  EXPECT_TRUE(ref_->is_defined());
}

// Test set_tag and tag retrieval
TEST_F(NodeRefTest_221, SetTag_ReturnsCorrectTag_221) {
  ref_->set_tag("!mytag");
  EXPECT_EQ("!mytag", ref_->tag());
}

// Test set_tag with empty string
TEST_F(NodeRefTest_221, SetTag_EmptyString_221) {
  ref_->set_tag("");
  EXPECT_EQ("", ref_->tag());
}

// Test set_tag overwriting previous tag
TEST_F(NodeRefTest_221, SetTag_OverwritesPreviousTag_221) {
  ref_->set_tag("!first");
  ref_->set_tag("!second");
  EXPECT_EQ("!second", ref_->tag());
}

// Test set_type to Scalar
TEST_F(NodeRefTest_221, SetType_Scalar_221) {
  ref_->set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, ref_->type());
}

// Test set_type to Sequence
TEST_F(NodeRefTest_221, SetType_Sequence_221) {
  ref_->set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, ref_->type());
}

// Test set_type to Map
TEST_F(NodeRefTest_221, SetType_Map_221) {
  ref_->set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, ref_->type());
}

// Test set_type to Null
TEST_F(NodeRefTest_221, SetType_Null_221) {
  ref_->set_type(NodeType::Scalar);
  ref_->set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, ref_->type());
}

// Test set_type to Undefined
TEST_F(NodeRefTest_221, SetType_Undefined_221) {
  ref_->set_type(NodeType::Undefined);
  EXPECT_EQ(NodeType::Undefined, ref_->type());
}

// Test set_scalar and scalar retrieval
TEST_F(NodeRefTest_221, SetScalar_ReturnsCorrectScalar_221) {
  ref_->set_type(NodeType::Scalar);
  ref_->set_scalar("hello");
  EXPECT_EQ("hello", ref_->scalar());
}

// Test set_scalar with empty string
TEST_F(NodeRefTest_221, SetScalar_EmptyString_221) {
  ref_->set_type(NodeType::Scalar);
  ref_->set_scalar("");
  EXPECT_EQ("", ref_->scalar());
}

// Test set_scalar overwriting previous value
TEST_F(NodeRefTest_221, SetScalar_OverwritesPreviousValue_221) {
  ref_->set_type(NodeType::Scalar);
  ref_->set_scalar("first");
  ref_->set_scalar("second");
  EXPECT_EQ("second", ref_->scalar());
}

// Test set_null sets type to Null
TEST_F(NodeRefTest_221, SetNull_TypeBecomesNull_221) {
  ref_->set_type(NodeType::Scalar);
  ref_->set_null();
  EXPECT_EQ(NodeType::Null, ref_->type());
}

// Test set_mark and mark retrieval
TEST_F(NodeRefTest_221, SetMark_ReturnsCorrectMark_221) {
  Mark m;
  m.line = 10;
  m.column = 20;
  m.pos = 30;
  ref_->set_mark(m);
  EXPECT_EQ(10, ref_->mark().line);
  EXPECT_EQ(20, ref_->mark().column);
  EXPECT_EQ(30, ref_->mark().pos);
}

// Test default mark is null mark
TEST_F(NodeRefTest_221, DefaultMark_IsNullMark_221) {
  const Mark& m = ref_->mark();
  EXPECT_EQ(Mark::null_mark().line, m.line);
  EXPECT_EQ(Mark::null_mark().column, m.column);
  EXPECT_EQ(Mark::null_mark().pos, m.pos);
}

// Test set_style and style retrieval
TEST_F(NodeRefTest_221, SetStyle_Block_221) {
  ref_->set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, ref_->style());
}

TEST_F(NodeRefTest_221, SetStyle_Flow_221) {
  ref_->set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, ref_->style());
}

TEST_F(NodeRefTest_221, SetStyle_Default_221) {
  ref_->set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, ref_->style());
}

// Test size for default (Null) node
TEST_F(NodeRefTest_221, Size_DefaultNodeIsZero_221) {
  EXPECT_EQ(0u, ref_->size());
}

// Test size for Sequence after push_back
TEST_F(NodeRefTest_221, PushBack_IncreasesSize_221) {
  ref_->set_type(NodeType::Sequence);
  node& n = pMemory_->create_node();
  n.set_scalar("value1");
  ref_->push_back(n, pMemory_);
  EXPECT_EQ(1u, ref_->size());
}

// Test multiple push_backs
TEST_F(NodeRefTest_221, PushBack_MultipleTimes_221) {
  ref_->set_type(NodeType::Sequence);
  node& n1 = pMemory_->create_node();
  n1.set_scalar("v1");
  node& n2 = pMemory_->create_node();
  n2.set_scalar("v2");
  node& n3 = pMemory_->create_node();
  n3.set_scalar("v3");
  ref_->push_back(n1, pMemory_);
  ref_->push_back(n2, pMemory_);
  ref_->push_back(n3, pMemory_);
  EXPECT_EQ(3u, ref_->size());
}

// Test insert for Map
TEST_F(NodeRefTest_221, Insert_IncreasesSize_221) {
  ref_->set_type(NodeType::Map);
  node& key = pMemory_->create_node();
  key.set_scalar("key1");
  node& val = pMemory_->create_node();
  val.set_scalar("val1");
  ref_->insert(key, val, pMemory_);
  EXPECT_EQ(1u, ref_->size());
}

// Test get with string key on Map
TEST_F(NodeRefTest_221, Get_ExistingKey_ReturnsNonNull_221) {
  ref_->set_type(NodeType::Map);
  node& key = pMemory_->create_node();
  key.set_scalar("mykey");
  node& val = pMemory_->create_node();
  val.set_scalar("myval");
  ref_->insert(key, val, pMemory_);
  
  node* result = ref_->get(std::string("mykey"), pMemory_);
  EXPECT_NE(nullptr, result);
}

// Test get with non-existing key
TEST_F(NodeRefTest_221, Get_NonExistingKey_ReturnsNull_221) {
  ref_->set_type(NodeType::Map);
  node* result = ref_->get(std::string("nonexistent"), pMemory_);
  EXPECT_EQ(nullptr, result);
}

// Test remove with string key
TEST_F(NodeRefTest_221, Remove_ExistingKey_ReturnsTrue_221) {
  ref_->set_type(NodeType::Map);
  node& key = pMemory_->create_node();
  key.set_scalar("removekey");
  node& val = pMemory_->create_node();
  val.set_scalar("removeval");
  ref_->insert(key, val, pMemory_);
  
  bool removed = ref_->remove(std::string("removekey"), pMemory_);
  EXPECT_TRUE(removed);
}

// Test remove with non-existing key
TEST_F(NodeRefTest_221, Remove_NonExistingKey_ReturnsFalse_221) {
  ref_->set_type(NodeType::Map);
  bool removed = ref_->remove(std::string("nonexistent"), pMemory_);
  EXPECT_FALSE(removed);
}

// Test set_data copies data from another node_ref
TEST_F(NodeRefTest_221, SetData_CopiesFromOtherNodeRef_221) {
  node_ref other;
  other.set_type(NodeType::Scalar);
  other.set_scalar("copied_value");
  other.set_tag("!copiedtag");
  other.mark_defined();
  
  ref_->set_data(other);
  
  EXPECT_EQ("copied_value", ref_->scalar());
  EXPECT_EQ("!copiedtag", ref_->tag());
  EXPECT_EQ(NodeType::Scalar, ref_->type());
}

// Test begin/end iterators on empty sequence
TEST_F(NodeRefTest_221, BeginEndOnEmptySequence_221) {
  ref_->set_type(NodeType::Sequence);
  EXPECT_EQ(ref_->begin(), ref_->end());
}

// Test begin/end iterators on sequence with elements
TEST_F(NodeRefTest_221, BeginEnd_SequenceWithElements_221) {
  ref_->set_type(NodeType::Sequence);
  node& n1 = pMemory_->create_node();
  n1.set_scalar("elem1");
  ref_->push_back(n1, pMemory_);
  
  EXPECT_NE(ref_->begin(), ref_->end());
}

// Test begin/end iterators on empty map
TEST_F(NodeRefTest_221, BeginEndOnEmptyMap_221) {
  ref_->set_type(NodeType::Map);
  EXPECT_EQ(ref_->begin(), ref_->end());
}

// Test set_tag with special characters
TEST_F(NodeRefTest_221, SetTag_SpecialCharacters_221) {
  ref_->set_tag("!tag:yaml.org,2002:str");
  EXPECT_EQ("!tag:yaml.org,2002:str", ref_->tag());
}

// Test set_scalar with large string
TEST_F(NodeRefTest_221, SetScalar_LargeString_221) {
  ref_->set_type(NodeType::Scalar);
  std::string large(10000, 'x');
  ref_->set_scalar(large);
  EXPECT_EQ(large, ref_->scalar());
}

// Test set_tag with unicode-like content
TEST_F(NodeRefTest_221, SetTag_UnicodeContent_221) {
  ref_->set_tag("!日本語タグ");
  EXPECT_EQ("!日本語タグ", ref_->tag());
}

// Test force_insert on map
TEST_F(NodeRefTest_221, ForceInsert_AddsToMap_221) {
  ref_->set_type(NodeType::Map);
  ref_->force_insert(std::string("key"), std::string("value"), pMemory_);
  EXPECT_EQ(1u, ref_->size());
}

// Test force_insert with duplicate key (should still insert)
TEST_F(NodeRefTest_221, ForceInsert_DuplicateKey_221) {
  ref_->set_type(NodeType::Map);
  ref_->force_insert(std::string("key"), std::string("value1"), pMemory_);
  ref_->force_insert(std::string("key"), std::string("value2"), pMemory_);
  EXPECT_EQ(2u, ref_->size());
}

// Test changing type resets content
TEST_F(NodeRefTest_221, SetType_ChangingTypeResetsContent_221) {
  ref_->set_type(NodeType::Sequence);
  node& n = pMemory_->create_node();
  n.set_scalar("elem");
  ref_->push_back(n, pMemory_);
  EXPECT_EQ(1u, ref_->size());
  
  ref_->set_type(NodeType::Map);
  EXPECT_EQ(0u, ref_->size());
}

// Test get with node key
TEST_F(NodeRefTest_221, Get_WithNodeKey_ExistingKey_221) {
  ref_->set_type(NodeType::Map);
  node& key = pMemory_->create_node();
  key.set_scalar("nodekey");
  node& val = pMemory_->create_node();
  val.set_scalar("nodeval");
  ref_->insert(key, val, pMemory_);
  
  node* result = ref_->get(key, pMemory_);
  EXPECT_NE(nullptr, result);
}

// Test remove with node key
TEST_F(NodeRefTest_221, Remove_WithNodeKey_221) {
  ref_->set_type(NodeType::Map);
  node& key = pMemory_->create_node();
  key.set_scalar("nodekey");
  node& val = pMemory_->create_node();
  val.set_scalar("nodeval");
  ref_->insert(key, val, pMemory_);
  
  bool removed = ref_->remove(key, pMemory_);
  EXPECT_TRUE(removed);
}

// Test size remains 0 for Null type
TEST_F(NodeRefTest_221, Size_NullTypeIsZero_221) {
  EXPECT_EQ(NodeType::Null, ref_->type());
  EXPECT_EQ(0u, ref_->size());
}

// Test size remains 0 for Scalar type
TEST_F(NodeRefTest_221, Size_ScalarTypeIsZero_221) {
  ref_->set_type(NodeType::Scalar);
  ref_->set_scalar("hello");
  EXPECT_EQ(0u, ref_->size());
}

}  // namespace detail
}  // namespace YAML
