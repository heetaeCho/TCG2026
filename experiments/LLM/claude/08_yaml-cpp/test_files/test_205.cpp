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

class NodeDataTest_205 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = std::make_shared<memory_holder>();
  }

  shared_memory_holder pMemory;
};

// Test default construction state
TEST_F(NodeDataTest_205, DefaultConstruction_IsNotDefined_205) {
  node_data nd;
  EXPECT_FALSE(nd.is_defined());
}

TEST_F(NodeDataTest_205, DefaultConstruction_TypeIsNull_205) {
  node_data nd;
  EXPECT_EQ(NodeType::Null, nd.type());
}

TEST_F(NodeDataTest_205, DefaultConstruction_ScalarIsEmpty_205) {
  node_data nd;
  EXPECT_TRUE(nd.scalar().empty());
}

TEST_F(NodeDataTest_205, DefaultConstruction_TagIsEmpty_205) {
  node_data nd;
  EXPECT_TRUE(nd.tag().empty());
}

TEST_F(NodeDataTest_205, DefaultConstruction_SizeIsZero_205) {
  node_data nd;
  EXPECT_EQ(0u, nd.size());
}

// Test mark_defined
TEST_F(NodeDataTest_205, MarkDefined_MakesNodeDefined_205) {
  node_data nd;
  nd.mark_defined();
  EXPECT_TRUE(nd.is_defined());
}

// Test set_type
TEST_F(NodeDataTest_205, SetType_Sequence_205) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, nd.type());
}

TEST_F(NodeDataTest_205, SetType_Map_205) {
  node_data nd;
  nd.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, nd.type());
}

TEST_F(NodeDataTest_205, SetType_Scalar_205) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, nd.type());
}

TEST_F(NodeDataTest_205, SetType_Null_205) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, nd.type());
}

TEST_F(NodeDataTest_205, SetType_Undefined_205) {
  node_data nd;
  nd.set_type(NodeType::Undefined);
  EXPECT_EQ(NodeType::Undefined, nd.type());
}

// Test set_tag
TEST_F(NodeDataTest_205, SetTag_StoresTag_205) {
  node_data nd;
  nd.set_tag("!mytag");
  EXPECT_EQ("!mytag", nd.tag());
}

TEST_F(NodeDataTest_205, SetTag_EmptyTag_205) {
  node_data nd;
  nd.set_tag("");
  EXPECT_EQ("", nd.tag());
}

TEST_F(NodeDataTest_205, SetTag_OverwriteTag_205) {
  node_data nd;
  nd.set_tag("first");
  nd.set_tag("second");
  EXPECT_EQ("second", nd.tag());
}

// Test set_scalar
TEST_F(NodeDataTest_205, SetScalar_StoresScalar_205) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("hello");
  EXPECT_EQ("hello", nd.scalar());
}

TEST_F(NodeDataTest_205, SetScalar_EmptyString_205) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("");
  EXPECT_EQ("", nd.scalar());
}

// Test set_null
TEST_F(NodeDataTest_205, SetNull_SetsTypeToNull_205) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("value");
  nd.set_null();
  EXPECT_EQ(NodeType::Null, nd.type());
}

// Test set_style
TEST_F(NodeDataTest_205, SetStyle_Block_205) {
  node_data nd;
  nd.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, nd.style());
}

TEST_F(NodeDataTest_205, SetStyle_Flow_205) {
  node_data nd;
  nd.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, nd.style());
}

TEST_F(NodeDataTest_205, SetStyle_Default_205) {
  node_data nd;
  nd.set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, nd.style());
}

// Test set_mark
TEST_F(NodeDataTest_205, SetMark_StoresMark_205) {
  node_data nd;
  Mark m;
  m.line = 5;
  m.column = 10;
  m.pos = 42;
  nd.set_mark(m);
  EXPECT_EQ(5, nd.mark().line);
  EXPECT_EQ(10, nd.mark().column);
  EXPECT_EQ(42u, nd.mark().pos);
}

// Test empty_scalar
TEST_F(NodeDataTest_205, EmptyScalar_ReturnsEmptyString_205) {
  const std::string& es = node_data::empty_scalar();
  EXPECT_TRUE(es.empty());
}

TEST_F(NodeDataTest_205, EmptyScalar_ReturnsSameReference_205) {
  const std::string& es1 = node_data::empty_scalar();
  const std::string& es2 = node_data::empty_scalar();
  EXPECT_EQ(&es1, &es2);
}

// Test sequence operations: push_back and size
TEST_F(NodeDataTest_205, PushBack_IncreasesSize_205) {
  node_data nd;
  nd.set_type(NodeType::Sequence);

  node& n1 = pMemory->create_node();
  n1.set_data(new node_data());
  nd.push_back(n1, pMemory);
  EXPECT_EQ(1u, nd.size());

  node& n2 = pMemory->create_node();
  n2.set_data(new node_data());
  nd.push_back(n2, pMemory);
  EXPECT_EQ(2u, nd.size());
}

// Test sequence begin/end iterators
TEST_F(NodeDataTest_205, Sequence_BeginEndIterators_205) {
  node_data nd;
  nd.set_type(NodeType::Sequence);

  // Empty sequence
  EXPECT_EQ(nd.begin(), nd.end());

  node& n1 = pMemory->create_node();
  n1.set_data(new node_data());
  nd.push_back(n1, pMemory);

  EXPECT_NE(nd.begin(), nd.end());
}

// Test map operations: insert and size
TEST_F(NodeDataTest_205, Insert_IncreasesMapSize_205) {
  node_data nd;
  nd.set_type(NodeType::Map);

  node& key1 = pMemory->create_node();
  key1.set_data(new node_data());
  key1.set_type(NodeType::Scalar);
  key1.set_scalar("key1");

  node& val1 = pMemory->create_node();
  val1.set_data(new node_data());
  val1.set_type(NodeType::Scalar);
  val1.set_scalar("val1");

  nd.insert(key1, val1, pMemory);
  EXPECT_EQ(1u, nd.size());
}

// Test get with key on map
TEST_F(NodeDataTest_205, MapGet_ExistingKey_ReturnsNode_205) {
  node_data nd;
  nd.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_data(new node_data());
  key.set_type(NodeType::Scalar);
  key.set_scalar("mykey");

  node& val = pMemory->create_node();
  val.set_data(new node_data());
  val.set_type(NodeType::Scalar);
  val.set_scalar("myval");

  nd.insert(key, val, pMemory);

  node* result = nd.get(key, pMemory);
  EXPECT_NE(nullptr, result);
}

// Test get with template key
TEST_F(NodeDataTest_205, MapGetTemplate_ExistingKey_ReturnsNode_205) {
  node_data nd;
  nd.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_data(new node_data());
  key.set_type(NodeType::Scalar);
  key.set_scalar("hello");

  node& val = pMemory->create_node();
  val.set_data(new node_data());
  val.set_type(NodeType::Scalar);
  val.set_scalar("world");

  nd.insert(key, val, pMemory);

  const node* result = nd.get(std::string("hello"), pMemory);
  EXPECT_NE(nullptr, result);
}

TEST_F(NodeDataTest_205, MapGetTemplate_NonExistingKey_ReturnsNull_205) {
  node_data nd;
  nd.set_type(NodeType::Map);

  const node* result = nd.get(std::string("nonexistent"), pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test remove
TEST_F(NodeDataTest_205, MapRemove_ExistingKey_ReturnsTrue_205) {
  node_data nd;
  nd.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_data(new node_data());
  key.set_type(NodeType::Scalar);
  key.set_scalar("removekey");

  node& val = pMemory->create_node();
  val.set_data(new node_data());
  val.set_type(NodeType::Scalar);
  val.set_scalar("removeval");

  nd.insert(key, val, pMemory);

  bool removed = nd.remove(key, pMemory);
  EXPECT_TRUE(removed);
}

TEST_F(NodeDataTest_205, MapRemoveTemplate_NonExistingKey_ReturnsFalse_205) {
  node_data nd;
  nd.set_type(NodeType::Map);

  bool removed = nd.remove(std::string("nonexistent"), pMemory);
  EXPECT_FALSE(removed);
}

// Test force_insert
TEST_F(NodeDataTest_205, ForceInsert_AddsToMap_205) {
  node_data nd;
  nd.set_type(NodeType::Map);

  nd.force_insert(std::string("fkey"), std::string("fval"), pMemory);
  EXPECT_EQ(1u, nd.size());
}

// Test changing type resets content
TEST_F(NodeDataTest_205, SetTypeSequenceThenMap_ResetsSize_205) {
  node_data nd;
  nd.set_type(NodeType::Sequence);

  node& n1 = pMemory->create_node();
  n1.set_data(new node_data());
  nd.push_back(n1, pMemory);
  EXPECT_EQ(1u, nd.size());

  nd.set_type(NodeType::Map);
  EXPECT_EQ(0u, nd.size());
}

// Test setting type to same type doesn't reset
TEST_F(NodeDataTest_205, SetTypeSameType_DoesNotReset_205) {
  node_data nd;
  nd.set_type(NodeType::Sequence);

  node& n1 = pMemory->create_node();
  n1.set_data(new node_data());
  nd.push_back(n1, pMemory);

  nd.set_type(NodeType::Sequence);
  // If setting same type, size should remain
  EXPECT_EQ(1u, nd.size());
}

// Test copy construction is deleted
TEST_F(NodeDataTest_205, CopyConstructorIsDeleted_205) {
  EXPECT_FALSE(std::is_copy_constructible<node_data>::value);
}

// Test copy assignment is deleted
TEST_F(NodeDataTest_205, CopyAssignmentIsDeleted_205) {
  EXPECT_FALSE(std::is_copy_assignable<node_data>::value);
}

// Test null mark on default construction
TEST_F(NodeDataTest_205, DefaultMark_IsNullMark_205) {
  node_data nd;
  EXPECT_EQ(Mark::null_mark().line, nd.mark().line);
  EXPECT_EQ(Mark::null_mark().column, nd.mark().column);
  EXPECT_EQ(Mark::null_mark().pos, nd.mark().pos);
}

// Test multiple push_backs
TEST_F(NodeDataTest_205, PushBack_MultipleElements_205) {
  node_data nd;
  nd.set_type(NodeType::Sequence);

  for (int i = 0; i < 10; ++i) {
    node& n = pMemory->create_node();
    n.set_data(new node_data());
    nd.push_back(n, pMemory);
  }
  EXPECT_EQ(10u, nd.size());
}

// Test size for Null type
TEST_F(NodeDataTest_205, NullType_SizeIsZero_205) {
  node_data nd;
  EXPECT_EQ(0u, nd.size());
}

// Test size for Scalar type
TEST_F(NodeDataTest_205, ScalarType_SizeIsZero_205) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("test");
  EXPECT_EQ(0u, nd.size());
}

// Test default style
TEST_F(NodeDataTest_205, DefaultStyle_IsDefault_205) {
  node_data nd;
  EXPECT_EQ(EmitterStyle::Default, nd.style());
}

}  // namespace detail
}  // namespace YAML
