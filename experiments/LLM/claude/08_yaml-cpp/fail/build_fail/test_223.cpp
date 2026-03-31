#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/node_data.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeRefTest_223 : public ::testing::Test {
 protected:
  void SetUp() override {
    ref_ = std::make_unique<node_ref>();
    pMemory_ = std::make_shared<memory>();
  }

  std::unique_ptr<node_ref> ref_;
  shared_memory_holder pMemory_;
};

// Test default construction - node should not be defined initially
TEST_F(NodeRefTest_223, DefaultConstruction_IsNotDefined_223) {
  EXPECT_FALSE(ref_->is_defined());
}

// Test default type is Null
TEST_F(NodeRefTest_223, DefaultConstruction_TypeIsNull_223) {
  EXPECT_EQ(NodeType::Null, ref_->type());
}

// Test mark_defined makes the node defined
TEST_F(NodeRefTest_223, MarkDefined_MakesNodeDefined_223) {
  ref_->mark_defined();
  EXPECT_TRUE(ref_->is_defined());
}

// Test set_scalar sets scalar value
TEST_F(NodeRefTest_223, SetScalar_SetsValue_223) {
  ref_->set_scalar("hello");
  EXPECT_EQ("hello", ref_->scalar());
}

// Test set_scalar changes type to Scalar
TEST_F(NodeRefTest_223, SetScalar_ChangesTypeToScalar_223) {
  ref_->set_scalar("test");
  EXPECT_EQ(NodeType::Scalar, ref_->type());
}

// Test set_scalar with empty string
TEST_F(NodeRefTest_223, SetScalar_EmptyString_223) {
  ref_->set_scalar("");
  EXPECT_EQ("", ref_->scalar());
  EXPECT_EQ(NodeType::Scalar, ref_->type());
}

// Test set_scalar with long string
TEST_F(NodeRefTest_223, SetScalar_LongString_223) {
  std::string longStr(10000, 'x');
  ref_->set_scalar(longStr);
  EXPECT_EQ(longStr, ref_->scalar());
}

// Test set_scalar with special characters
TEST_F(NodeRefTest_223, SetScalar_SpecialCharacters_223) {
  ref_->set_scalar("hello\nworld\ttab");
  EXPECT_EQ("hello\nworld\ttab", ref_->scalar());
}

// Test set_null sets type to Null
TEST_F(NodeRefTest_223, SetNull_SetsTypeToNull_223) {
  ref_->set_scalar("not null");
  ref_->set_null();
  EXPECT_EQ(NodeType::Null, ref_->type());
}

// Test set_tag
TEST_F(NodeRefTest_223, SetTag_SetsTag_223) {
  ref_->set_tag("!mytag");
  EXPECT_EQ("!mytag", ref_->tag());
}

// Test set_tag with empty string
TEST_F(NodeRefTest_223, SetTag_EmptyString_223) {
  ref_->set_tag("");
  EXPECT_EQ("", ref_->tag());
}

// Test set_type to Sequence
TEST_F(NodeRefTest_223, SetType_Sequence_223) {
  ref_->set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, ref_->type());
}

// Test set_type to Map
TEST_F(NodeRefTest_223, SetType_Map_223) {
  ref_->set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, ref_->type());
}

// Test set_type to Scalar
TEST_F(NodeRefTest_223, SetType_Scalar_223) {
  ref_->set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, ref_->type());
}

// Test set_type to Null
TEST_F(NodeRefTest_223, SetType_Null_223) {
  ref_->set_type(NodeType::Scalar);
  ref_->set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, ref_->type());
}

// Test set_type to Undefined
TEST_F(NodeRefTest_223, SetType_Undefined_223) {
  ref_->set_type(NodeType::Undefined);
  EXPECT_EQ(NodeType::Undefined, ref_->type());
}

// Test set_style
TEST_F(NodeRefTest_223, SetStyle_Flow_223) {
  ref_->set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, ref_->style());
}

// Test set_style Block
TEST_F(NodeRefTest_223, SetStyle_Block_223) {
  ref_->set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, ref_->style());
}

// Test set_style Default
TEST_F(NodeRefTest_223, SetStyle_Default_223) {
  ref_->set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, ref_->style());
}

// Test set_mark
TEST_F(NodeRefTest_223, SetMark_223) {
  Mark m;
  m.line = 10;
  m.column = 5;
  m.pos = 100;
  ref_->set_mark(m);
  EXPECT_EQ(10, ref_->mark().line);
  EXPECT_EQ(5, ref_->mark().column);
  EXPECT_EQ(100, ref_->mark().pos);
}

// Test size is 0 for empty sequence
TEST_F(NodeRefTest_223, Size_EmptySequence_223) {
  ref_->set_type(NodeType::Sequence);
  EXPECT_EQ(0u, ref_->size());
}

// Test size is 0 for empty map
TEST_F(NodeRefTest_223, Size_EmptyMap_223) {
  ref_->set_type(NodeType::Map);
  EXPECT_EQ(0u, ref_->size());
}

// Test push_back increases size for sequence
TEST_F(NodeRefTest_223, PushBack_IncreasesSize_223) {
  ref_->set_type(NodeType::Sequence);
  node& n = pMemory_->create_node();
  n.set_scalar("value1");
  ref_->push_back(n, pMemory_);
  EXPECT_EQ(1u, ref_->size());
}

// Test push_back multiple elements
TEST_F(NodeRefTest_223, PushBack_MultipleElements_223) {
  ref_->set_type(NodeType::Sequence);
  node& n1 = pMemory_->create_node();
  n1.set_scalar("value1");
  node& n2 = pMemory_->create_node();
  n2.set_scalar("value2");
  node& n3 = pMemory_->create_node();
  n3.set_scalar("value3");
  ref_->push_back(n1, pMemory_);
  ref_->push_back(n2, pMemory_);
  ref_->push_back(n3, pMemory_);
  EXPECT_EQ(3u, ref_->size());
}

// Test begin/end for empty sequence
TEST_F(NodeRefTest_223, BeginEndEmptySequence_223) {
  ref_->set_type(NodeType::Sequence);
  EXPECT_EQ(ref_->begin(), ref_->end());
}

// Test insert into map
TEST_F(NodeRefTest_223, Insert_IntoMap_223) {
  ref_->set_type(NodeType::Map);
  node& key = pMemory_->create_node();
  key.set_scalar("key1");
  node& value = pMemory_->create_node();
  value.set_scalar("val1");
  ref_->insert(key, value, pMemory_);
  EXPECT_EQ(1u, ref_->size());
}

// Test get with string key on map
TEST_F(NodeRefTest_223, Get_StringKey_Found_223) {
  ref_->set_type(NodeType::Map);
  node& key = pMemory_->create_node();
  key.set_scalar("mykey");
  node& value = pMemory_->create_node();
  value.set_scalar("myvalue");
  ref_->insert(key, value, pMemory_);
  
  node* result = ref_->get(std::string("mykey"), pMemory_);
  EXPECT_NE(nullptr, result);
}

// Test get with string key not found
TEST_F(NodeRefTest_223, Get_StringKey_NotFound_223) {
  ref_->set_type(NodeType::Map);
  node* result = ref_->get(std::string("nonexistent"), pMemory_);
  EXPECT_EQ(nullptr, result);
}

// Test remove from map
TEST_F(NodeRefTest_223, Remove_StringKey_223) {
  ref_->set_type(NodeType::Map);
  node& key = pMemory_->create_node();
  key.set_scalar("removekey");
  node& value = pMemory_->create_node();
  value.set_scalar("removeval");
  ref_->insert(key, value, pMemory_);
  
  bool removed = ref_->remove(std::string("removekey"), pMemory_);
  EXPECT_TRUE(removed);
}

// Test remove non-existent key
TEST_F(NodeRefTest_223, Remove_NonExistentKey_223) {
  ref_->set_type(NodeType::Map);
  bool removed = ref_->remove(std::string("nokey"), pMemory_);
  EXPECT_FALSE(removed);
}

// Test set_data copies data from another node_ref
TEST_F(NodeRefTest_223, SetData_CopiesFromOther_223) {
  node_ref other;
  other.set_scalar("copied_value");
  other.set_tag("!copiedtag");
  
  ref_->set_data(other);
  EXPECT_EQ("copied_value", ref_->scalar());
  EXPECT_EQ("!copiedtag", ref_->tag());
}

// Test overwriting scalar
TEST_F(NodeRefTest_223, SetScalar_Overwrite_223) {
  ref_->set_scalar("first");
  EXPECT_EQ("first", ref_->scalar());
  ref_->set_scalar("second");
  EXPECT_EQ("second", ref_->scalar());
}

// Test set_scalar after set_null
TEST_F(NodeRefTest_223, SetScalar_AfterNull_223) {
  ref_->set_null();
  EXPECT_EQ(NodeType::Null, ref_->type());
  ref_->set_scalar("revived");
  EXPECT_EQ("revived", ref_->scalar());
  EXPECT_EQ(NodeType::Scalar, ref_->type());
}

// Test changing type from Sequence to Map
TEST_F(NodeRefTest_223, SetType_SequenceToMap_223) {
  ref_->set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, ref_->type());
  ref_->set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, ref_->type());
}

// Test node_ref with node key get/remove
TEST_F(NodeRefTest_223, Get_NodeKey_223) {
  ref_->set_type(NodeType::Map);
  node& key = pMemory_->create_node();
  key.set_scalar("nodekey");
  node& value = pMemory_->create_node();
  value.set_scalar("nodeval");
  ref_->insert(key, value, pMemory_);
  
  node* result = ref_->get(key, pMemory_);
  EXPECT_NE(nullptr, result);
}

// Test remove with node key
TEST_F(NodeRefTest_223, Remove_NodeKey_223) {
  ref_->set_type(NodeType::Map);
  node& key = pMemory_->create_node();
  key.set_scalar("rnodekey");
  node& value = pMemory_->create_node();
  value.set_scalar("rnodeval");
  ref_->insert(key, value, pMemory_);
  
  bool removed = ref_->remove(key, pMemory_);
  EXPECT_TRUE(removed);
}

// Test remove node key not found
TEST_F(NodeRefTest_223, Remove_NodeKey_NotFound_223) {
  ref_->set_type(NodeType::Map);
  node& key = pMemory_->create_node();
  key.set_scalar("missingkey");
  bool removed = ref_->remove(key, pMemory_);
  EXPECT_FALSE(removed);
}

// Test force_insert
TEST_F(NodeRefTest_223, ForceInsert_223) {
  ref_->set_type(NodeType::Map);
  ref_->force_insert(std::string("forcekey"), std::string("forceval"), pMemory_);
  EXPECT_EQ(1u, ref_->size());
}

// Test scalar returns empty for non-scalar types
TEST_F(NodeRefTest_223, Scalar_NonScalarType_ReturnsEmpty_223) {
  ref_->set_type(NodeType::Sequence);
  EXPECT_EQ("", ref_->scalar());
}

// Test default scalar is empty
TEST_F(NodeRefTest_223, DefaultScalar_Empty_223) {
  EXPECT_EQ("", ref_->scalar());
}

// Test default tag is empty
TEST_F(NodeRefTest_223, DefaultTag_Empty_223) {
  EXPECT_EQ("", ref_->tag());
}

// Test setting scalar with unicode
TEST_F(NodeRefTest_223, SetScalar_Unicode_223) {
  ref_->set_scalar("日本語テスト");
  EXPECT_EQ("日本語テスト", ref_->scalar());
}

// Test multiple inserts into map
TEST_F(NodeRefTest_223, Insert_MultipleEntries_223) {
  ref_->set_type(NodeType::Map);
  for (int i = 0; i < 10; ++i) {
    node& key = pMemory_->create_node();
    key.set_scalar("key" + std::to_string(i));
    node& value = pMemory_->create_node();
    value.set_scalar("val" + std::to_string(i));
    ref_->insert(key, value, pMemory_);
  }
  EXPECT_EQ(10u, ref_->size());
}

// Test begin/end for non-empty sequence
TEST_F(NodeRefTest_223, BeginEnd_NonEmptySequence_223) {
  ref_->set_type(NodeType::Sequence);
  node& n = pMemory_->create_node();
  n.set_scalar("item");
  ref_->push_back(n, pMemory_);
  EXPECT_NE(ref_->begin(), ref_->end());
}

}  // namespace detail
}  // namespace YAML
