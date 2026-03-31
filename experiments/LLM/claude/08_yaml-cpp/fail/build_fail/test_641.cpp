#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node_data.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeDataTest_641 : public ::testing::Test {
 protected:
  void SetUp() override {
    data_ = std::make_unique<node_data>();
    pMemory_ = std::make_shared<memory>();
  }

  std::unique_ptr<node_data> data_;
  shared_memory_holder pMemory_;
};

// Test default construction state
TEST_F(NodeDataTest_641, DefaultConstruction_IsNotDefined_641) {
  EXPECT_FALSE(data_->is_defined());
}

TEST_F(NodeDataTest_641, DefaultConstruction_TypeIsNull_641) {
  EXPECT_EQ(NodeType::Null, data_->type());
}

TEST_F(NodeDataTest_641, DefaultConstruction_MarkIsNull_641) {
  EXPECT_TRUE(data_->mark().is_null());
}

TEST_F(NodeDataTest_641, DefaultConstruction_ScalarIsEmpty_641) {
  EXPECT_TRUE(data_->scalar().empty());
}

TEST_F(NodeDataTest_641, DefaultConstruction_TagIsEmpty_641) {
  EXPECT_TRUE(data_->tag().empty());
}

TEST_F(NodeDataTest_641, DefaultConstruction_SizeIsZero_641) {
  EXPECT_EQ(0u, data_->size());
}

// Test mark_defined
TEST_F(NodeDataTest_641, MarkDefined_SetsDefined_641) {
  data_->mark_defined();
  EXPECT_TRUE(data_->is_defined());
}

// Test set_mark
TEST_F(NodeDataTest_641, SetMark_StoresMark_641) {
  Mark m;
  m.pos = 10;
  m.line = 5;
  m.column = 3;
  data_->set_mark(m);
  EXPECT_EQ(10, data_->mark().pos);
  EXPECT_EQ(5, data_->mark().line);
  EXPECT_EQ(3, data_->mark().column);
}

TEST_F(NodeDataTest_641, SetMark_NullMark_641) {
  // First set a non-null mark
  Mark m;
  m.pos = 10;
  m.line = 5;
  m.column = 3;
  data_->set_mark(m);
  EXPECT_FALSE(data_->mark().is_null());

  // Now set null mark
  data_->set_mark(Mark::null_mark());
  EXPECT_TRUE(data_->mark().is_null());
}

// Test set_type
TEST_F(NodeDataTest_641, SetType_Sequence_641) {
  data_->set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, data_->type());
}

TEST_F(NodeDataTest_641, SetType_Map_641) {
  data_->set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, data_->type());
}

TEST_F(NodeDataTest_641, SetType_Scalar_641) {
  data_->set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, data_->type());
}

TEST_F(NodeDataTest_641, SetType_Null_641) {
  data_->set_type(NodeType::Scalar);
  data_->set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, data_->type());
}

TEST_F(NodeDataTest_641, SetType_Undefined_641) {
  data_->set_type(NodeType::Scalar);
  data_->set_type(NodeType::Undefined);
  EXPECT_EQ(NodeType::Undefined, data_->type());
}

// Test set_tag
TEST_F(NodeDataTest_641, SetTag_SetsTag_641) {
  data_->set_tag("!!int");
  EXPECT_EQ("!!int", data_->tag());
}

TEST_F(NodeDataTest_641, SetTag_EmptyTag_641) {
  data_->set_tag("");
  EXPECT_EQ("", data_->tag());
}

TEST_F(NodeDataTest_641, SetTag_OverwriteTag_641) {
  data_->set_tag("first");
  data_->set_tag("second");
  EXPECT_EQ("second", data_->tag());
}

// Test set_null
TEST_F(NodeDataTest_641, SetNull_SetsTypeToNull_641) {
  data_->set_type(NodeType::Scalar);
  data_->set_null();
  EXPECT_EQ(NodeType::Null, data_->type());
}

// Test set_scalar
TEST_F(NodeDataTest_641, SetScalar_SetsScalarValue_641) {
  data_->set_scalar("hello");
  EXPECT_EQ("hello", data_->scalar());
}

TEST_F(NodeDataTest_641, SetScalar_EmptyScalar_641) {
  data_->set_scalar("");
  EXPECT_EQ("", data_->scalar());
}

TEST_F(NodeDataTest_641, SetScalar_OverwriteScalar_641) {
  data_->set_scalar("first");
  data_->set_scalar("second");
  EXPECT_EQ("second", data_->scalar());
}

// Test set_style
TEST_F(NodeDataTest_641, SetStyle_Block_641) {
  data_->set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, data_->style());
}

TEST_F(NodeDataTest_641, SetStyle_Flow_641) {
  data_->set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, data_->style());
}

TEST_F(NodeDataTest_641, SetStyle_Default_641) {
  data_->set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, data_->style());
}

// Test empty_scalar
TEST_F(NodeDataTest_641, EmptyScalar_ReturnsEmptyString_641) {
  const std::string& es = node_data::empty_scalar();
  EXPECT_TRUE(es.empty());
}

TEST_F(NodeDataTest_641, EmptyScalar_ReturnsSameReference_641) {
  const std::string& es1 = node_data::empty_scalar();
  const std::string& es2 = node_data::empty_scalar();
  EXPECT_EQ(&es1, &es2);
}

// Test sequence operations
TEST_F(NodeDataTest_641, PushBack_IncreasesSize_641) {
  data_->set_type(NodeType::Sequence);
  node& n = pMemory_->create_node();
  data_->push_back(n, pMemory_);
  EXPECT_EQ(1u, data_->size());
}

TEST_F(NodeDataTest_641, PushBack_MultiplePushes_641) {
  data_->set_type(NodeType::Sequence);
  node& n1 = pMemory_->create_node();
  node& n2 = pMemory_->create_node();
  node& n3 = pMemory_->create_node();
  data_->push_back(n1, pMemory_);
  data_->push_back(n2, pMemory_);
  data_->push_back(n3, pMemory_);
  EXPECT_EQ(3u, data_->size());
}

// Test begin/end iterators for sequence
TEST_F(NodeDataTest_641, BeginEndIterators_EmptySequence_641) {
  data_->set_type(NodeType::Sequence);
  EXPECT_EQ(data_->begin(), data_->end());
}

TEST_F(NodeDataTest_641, BeginEndIterators_NonEmptySequence_641) {
  data_->set_type(NodeType::Sequence);
  node& n = pMemory_->create_node();
  data_->push_back(n, pMemory_);
  EXPECT_NE(data_->begin(), data_->end());
}

// Test map operations
TEST_F(NodeDataTest_641, Insert_IncreasesSize_641) {
  data_->set_type(NodeType::Map);
  node& key = pMemory_->create_node();
  key.set_scalar("key1");
  node& value = pMemory_->create_node();
  value.set_scalar("value1");
  data_->insert(key, value, pMemory_);
  EXPECT_EQ(1u, data_->size());
}

TEST_F(NodeDataTest_641, Insert_MultipleInserts_641) {
  data_->set_type(NodeType::Map);
  
  node& key1 = pMemory_->create_node();
  key1.set_scalar("key1");
  node& val1 = pMemory_->create_node();
  val1.set_scalar("val1");
  data_->insert(key1, val1, pMemory_);

  node& key2 = pMemory_->create_node();
  key2.set_scalar("key2");
  node& val2 = pMemory_->create_node();
  val2.set_scalar("val2");
  data_->insert(key2, val2, pMemory_);

  EXPECT_EQ(2u, data_->size());
}

// Test get on map with string key
TEST_F(NodeDataTest_641, GetStringKey_ExistingKey_641) {
  data_->set_type(NodeType::Map);
  
  node& key = pMemory_->create_node();
  key.set_scalar("mykey");
  node& val = pMemory_->create_node();
  val.set_scalar("myval");
  data_->insert(key, val, pMemory_);

  const node* result = data_->get(std::string("mykey"), pMemory_);
  EXPECT_NE(nullptr, result);
}

TEST_F(NodeDataTest_641, GetStringKey_NonExistingKey_641) {
  data_->set_type(NodeType::Map);
  
  node& key = pMemory_->create_node();
  key.set_scalar("mykey");
  node& val = pMemory_->create_node();
  val.set_scalar("myval");
  data_->insert(key, val, pMemory_);

  const node* result = data_->get(std::string("nonexistent"), pMemory_);
  EXPECT_EQ(nullptr, result);
}

// Test get on node key
TEST_F(NodeDataTest_641, GetNodeKey_ExistingKey_641) {
  data_->set_type(NodeType::Map);
  
  node& key = pMemory_->create_node();
  key.set_scalar("mykey");
  node& val = pMemory_->create_node();
  val.set_scalar("myval");
  data_->insert(key, val, pMemory_);

  const node* result = data_->get(key, pMemory_);
  EXPECT_NE(nullptr, result);
}

TEST_F(NodeDataTest_641, GetNodeKey_NonExistingKey_641) {
  data_->set_type(NodeType::Map);
  
  node& key = pMemory_->create_node();
  key.set_scalar("mykey");
  node& val = pMemory_->create_node();
  val.set_scalar("myval");
  data_->insert(key, val, pMemory_);

  node& otherKey = pMemory_->create_node();
  otherKey.set_scalar("otherkey");
  const node* result = data_->get(otherKey, pMemory_);
  EXPECT_EQ(nullptr, result);
}

// Test remove with string key
TEST_F(NodeDataTest_641, RemoveStringKey_ExistingKey_641) {
  data_->set_type(NodeType::Map);
  
  node& key = pMemory_->create_node();
  key.set_scalar("mykey");
  node& val = pMemory_->create_node();
  val.set_scalar("myval");
  data_->insert(key, val, pMemory_);

  bool removed = data_->remove(std::string("mykey"), pMemory_);
  EXPECT_TRUE(removed);
}

TEST_F(NodeDataTest_641, RemoveStringKey_NonExistingKey_641) {
  data_->set_type(NodeType::Map);
  
  node& key = pMemory_->create_node();
  key.set_scalar("mykey");
  node& val = pMemory_->create_node();
  val.set_scalar("myval");
  data_->insert(key, val, pMemory_);

  bool removed = data_->remove(std::string("nonexistent"), pMemory_);
  EXPECT_FALSE(removed);
}

// Test remove with node key
TEST_F(NodeDataTest_641, RemoveNodeKey_ExistingKey_641) {
  data_->set_type(NodeType::Map);
  
  node& key = pMemory_->create_node();
  key.set_scalar("mykey");
  node& val = pMemory_->create_node();
  val.set_scalar("myval");
  data_->insert(key, val, pMemory_);

  bool removed = data_->remove(key, pMemory_);
  EXPECT_TRUE(removed);
}

TEST_F(NodeDataTest_641, RemoveNodeKey_NonExistingKey_641) {
  data_->set_type(NodeType::Map);
  
  node& key = pMemory_->create_node();
  key.set_scalar("mykey");
  node& val = pMemory_->create_node();
  val.set_scalar("myval");
  data_->insert(key, val, pMemory_);

  node& otherKey = pMemory_->create_node();
  otherKey.set_scalar("otherkey");
  bool removed = data_->remove(otherKey, pMemory_);
  EXPECT_FALSE(removed);
}

// Test force_insert
TEST_F(NodeDataTest_641, ForceInsert_IncreasesSize_641) {
  data_->set_type(NodeType::Map);
  data_->force_insert(std::string("key1"), std::string("val1"), pMemory_);
  EXPECT_EQ(1u, data_->size());
}

TEST_F(NodeDataTest_641, ForceInsert_MultipleSameKey_641) {
  data_->set_type(NodeType::Map);
  data_->force_insert(std::string("key1"), std::string("val1"), pMemory_);
  data_->force_insert(std::string("key1"), std::string("val2"), pMemory_);
  // force_insert should insert even with duplicate keys
  EXPECT_EQ(2u, data_->size());
}

// Test type transitions
TEST_F(NodeDataTest_641, TypeTransition_NullToSequence_641) {
  EXPECT_EQ(NodeType::Null, data_->type());
  data_->set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, data_->type());
  EXPECT_EQ(0u, data_->size());
}

TEST_F(NodeDataTest_641, TypeTransition_NullToMap_641) {
  EXPECT_EQ(NodeType::Null, data_->type());
  data_->set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, data_->type());
  EXPECT_EQ(0u, data_->size());
}

TEST_F(NodeDataTest_641, TypeTransition_SequenceToMap_641) {
  data_->set_type(NodeType::Sequence);
  node& n = pMemory_->create_node();
  n.set_scalar("item");
  data_->push_back(n, pMemory_);
  EXPECT_EQ(1u, data_->size());
  
  data_->set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, data_->type());
}

// Test set_scalar also sets type
TEST_F(NodeDataTest_641, SetScalar_SetsTypeToScalar_641) {
  data_->set_type(NodeType::Scalar);
  data_->set_scalar("hello");
  EXPECT_EQ(NodeType::Scalar, data_->type());
  EXPECT_EQ("hello", data_->scalar());
}

// Test size for different types
TEST_F(NodeDataTest_641, Size_NullType_641) {
  EXPECT_EQ(0u, data_->size());
}

TEST_F(NodeDataTest_641, Size_ScalarType_641) {
  data_->set_type(NodeType::Scalar);
  data_->set_scalar("test");
  EXPECT_EQ(0u, data_->size());
}

// Test begin/end for map
TEST_F(NodeDataTest_641, BeginEndIterators_EmptyMap_641) {
  data_->set_type(NodeType::Map);
  EXPECT_EQ(data_->begin(), data_->end());
}

TEST_F(NodeDataTest_641, BeginEndIterators_NonEmptyMap_641) {
  data_->set_type(NodeType::Map);
  node& key = pMemory_->create_node();
  key.set_scalar("k");
  node& val = pMemory_->create_node();
  val.set_scalar("v");
  data_->insert(key, val, pMemory_);
  EXPECT_NE(data_->begin(), data_->end());
}

// Test removing reduces lookup
TEST_F(NodeDataTest_641, Remove_ReducesGetResult_641) {
  data_->set_type(NodeType::Map);
  
  node& key = pMemory_->create_node();
  key.set_scalar("mykey");
  node& val = pMemory_->create_node();
  val.set_scalar("myval");
  data_->insert(key, val, pMemory_);

  EXPECT_NE(nullptr, data_->get(std::string("mykey"), pMemory_));
  data_->remove(std::string("mykey"), pMemory_);
  EXPECT_EQ(nullptr, data_->get(std::string("mykey"), pMemory_));
}

// Test setting type resets content
TEST_F(NodeDataTest_641, SetType_ResetsSequenceContent_641) {
  data_->set_type(NodeType::Sequence);
  node& n = pMemory_->create_node();
  data_->push_back(n, pMemory_);
  EXPECT_EQ(1u, data_->size());

  // Setting to Null should reset
  data_->set_type(NodeType::Null);
  EXPECT_EQ(0u, data_->size());
}

// Test copy constructor is deleted (compile-time check conceptually)
// We just verify we can create and use node_data normally
TEST_F(NodeDataTest_641, BasicUsage_641) {
  data_->mark_defined();
  data_->set_type(NodeType::Scalar);
  data_->set_scalar("test_value");
  data_->set_tag("!!str");
  data_->set_style(EmitterStyle::Default);
  
  EXPECT_TRUE(data_->is_defined());
  EXPECT_EQ(NodeType::Scalar, data_->type());
  EXPECT_EQ("test_value", data_->scalar());
  EXPECT_EQ("!!str", data_->tag());
  EXPECT_EQ(EmitterStyle::Default, data_->style());
}

// Test set_null clears scalar
TEST_F(NodeDataTest_641, SetNull_AfterScalar_641) {
  data_->set_type(NodeType::Scalar);
  data_->set_scalar("something");
  data_->set_null();
  EXPECT_EQ(NodeType::Null, data_->type());
}

// Test push_back on null type converts to sequence
TEST_F(NodeDataTest_641, PushBack_OnNullType_ConvertsToSequence_641) {
  EXPECT_EQ(NodeType::Null, data_->type());
  node& n = pMemory_->create_node();
  data_->push_back(n, pMemory_);
  EXPECT_EQ(NodeType::Sequence, data_->type());
  EXPECT_EQ(1u, data_->size());
}

// Test get with integer key
TEST_F(NodeDataTest_641, GetIntKey_OnSequence_641) {
  data_->set_type(NodeType::Sequence);
  node& n = pMemory_->create_node();
  n.set_scalar("item0");
  data_->push_back(n, pMemory_);

  const node* result = data_->get(0, pMemory_);
  EXPECT_NE(nullptr, result);
}

TEST_F(NodeDataTest_641, GetIntKey_OutOfRange_641) {
  data_->set_type(NodeType::Sequence);
  node& n = pMemory_->create_node();
  n.set_scalar("item0");
  data_->push_back(n, pMemory_);

  const node* result = data_->get(5, pMemory_);
  EXPECT_EQ(nullptr, result);
}

}  // namespace detail
}  // namespace YAML
