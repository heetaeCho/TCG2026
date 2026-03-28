#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeRefTest_220 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = std::make_shared<memory_holder>();
  }

  shared_memory_holder pMemory;
};

// Test default construction - node_ref should start as undefined with Null type
TEST_F(NodeRefTest_220, DefaultConstruction_IsNotDefined_220) {
  node_ref ref;
  EXPECT_FALSE(ref.is_defined());
}

TEST_F(NodeRefTest_220, DefaultConstruction_TypeIsNull_220) {
  node_ref ref;
  EXPECT_EQ(NodeType::Null, ref.type());
}

TEST_F(NodeRefTest_220, DefaultConstruction_ScalarIsEmpty_220) {
  node_ref ref;
  EXPECT_TRUE(ref.scalar().empty());
}

TEST_F(NodeRefTest_220, DefaultConstruction_TagIsEmpty_220) {
  node_ref ref;
  EXPECT_TRUE(ref.tag().empty());
}

TEST_F(NodeRefTest_220, DefaultConstruction_SizeIsZero_220) {
  node_ref ref;
  EXPECT_EQ(0u, ref.size());
}

// Test mark_defined
TEST_F(NodeRefTest_220, MarkDefined_MakesNodeDefined_220) {
  node_ref ref;
  ref.mark_defined();
  EXPECT_TRUE(ref.is_defined());
}

// Test set_type
TEST_F(NodeRefTest_220, SetType_Scalar_220) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, ref.type());
}

TEST_F(NodeRefTest_220, SetType_Sequence_220) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, ref.type());
}

TEST_F(NodeRefTest_220, SetType_Map_220) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, ref.type());
}

TEST_F(NodeRefTest_220, SetType_Null_220) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, ref.type());
  ref.set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, ref.type());
}

TEST_F(NodeRefTest_220, SetType_Undefined_220) {
  node_ref ref;
  ref.set_type(NodeType::Undefined);
  EXPECT_EQ(NodeType::Undefined, ref.type());
}

// Test set_tag
TEST_F(NodeRefTest_220, SetTag_SetsAndReturnsTag_220) {
  node_ref ref;
  ref.set_tag("!custom");
  EXPECT_EQ("!custom", ref.tag());
}

TEST_F(NodeRefTest_220, SetTag_EmptyTag_220) {
  node_ref ref;
  ref.set_tag("something");
  ref.set_tag("");
  EXPECT_EQ("", ref.tag());
}

// Test set_scalar
TEST_F(NodeRefTest_220, SetScalar_SetsAndReturnsScalar_220) {
  node_ref ref;
  ref.set_scalar("hello");
  EXPECT_EQ("hello", ref.scalar());
}

TEST_F(NodeRefTest_220, SetScalar_EmptyScalar_220) {
  node_ref ref;
  ref.set_scalar("");
  EXPECT_EQ("", ref.scalar());
}

TEST_F(NodeRefTest_220, SetScalar_OverwriteScalar_220) {
  node_ref ref;
  ref.set_scalar("first");
  EXPECT_EQ("first", ref.scalar());
  ref.set_scalar("second");
  EXPECT_EQ("second", ref.scalar());
}

// Test set_null
TEST_F(NodeRefTest_220, SetNull_SetsTypeToNull_220) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("value");
  ref.set_null();
  EXPECT_EQ(NodeType::Null, ref.type());
}

// Test set_style
TEST_F(NodeRefTest_220, SetStyle_Block_220) {
  node_ref ref;
  ref.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, ref.style());
}

TEST_F(NodeRefTest_220, SetStyle_Flow_220) {
  node_ref ref;
  ref.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, ref.style());
}

TEST_F(NodeRefTest_220, SetStyle_Default_220) {
  node_ref ref;
  ref.set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, ref.style());
}

// Test set_mark
TEST_F(NodeRefTest_220, SetMark_SetsAndReturnsMark_220) {
  node_ref ref;
  Mark m;
  m.line = 10;
  m.column = 20;
  m.pos = 30;
  ref.set_mark(m);
  EXPECT_EQ(10, ref.mark().line);
  EXPECT_EQ(20, ref.mark().column);
  EXPECT_EQ(30u, ref.mark().pos);
}

// Test set_data - copies data from another node_ref
TEST_F(NodeRefTest_220, SetData_CopiesFromAnotherNodeRef_220) {
  node_ref source;
  source.set_type(NodeType::Scalar);
  source.set_scalar("copied_value");
  source.set_tag("!tag");
  source.mark_defined();

  node_ref target;
  target.set_data(source);

  EXPECT_EQ(NodeType::Scalar, target.type());
  EXPECT_EQ("copied_value", target.scalar());
  EXPECT_EQ("!tag", target.tag());
}

// Test sequence operations
TEST_F(NodeRefTest_220, PushBack_IncreasesSize_220) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);

  memory mem;
  shared_memory_holder pMem = mem.create_holder();
  
  node& n = mem.create_node();
  n.set_scalar("item1");

  ref.push_back(n, pMem);
  EXPECT_EQ(1u, ref.size());
}

TEST_F(NodeRefTest_220, PushBack_MultipleItems_220) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);

  memory mem;
  shared_memory_holder pMem = mem.create_holder();

  node& n1 = mem.create_node();
  n1.set_scalar("item1");
  node& n2 = mem.create_node();
  n2.set_scalar("item2");

  ref.push_back(n1, pMem);
  ref.push_back(n2, pMem);
  EXPECT_EQ(2u, ref.size());
}

// Test map operations
TEST_F(NodeRefTest_220, Insert_IncreasesSize_220) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  memory mem;
  shared_memory_holder pMem = mem.create_holder();

  node& key = mem.create_node();
  key.set_scalar("key1");
  node& value = mem.create_node();
  value.set_scalar("value1");

  ref.insert(key, value, pMem);
  EXPECT_EQ(1u, ref.size());
}

// Test begin/end for empty container
TEST_F(NodeRefTest_220, BeginEndEqual_WhenEmpty_220) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  EXPECT_EQ(ref.begin(), ref.end());
}

// Test get with template key
TEST_F(NodeRefTest_220, Get_ReturnsNullForNonexistentKey_220) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  memory mem;
  shared_memory_holder pMem = mem.create_holder();

  node* result = ref.get(std::string("nonexistent"), pMem);
  EXPECT_EQ(nullptr, result);
}

// Test remove with template key
TEST_F(NodeRefTest_220, Remove_ReturnsFalseForNonexistentKey_220) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  memory mem;
  shared_memory_holder pMem = mem.create_holder();

  bool result = ref.remove(std::string("nonexistent"), pMem);
  EXPECT_FALSE(result);
}

// Test changing type clears previous data
TEST_F(NodeRefTest_220, SetType_ChangingTypeClearsData_220) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("test");
  EXPECT_EQ("test", ref.scalar());

  ref.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, ref.type());
  EXPECT_EQ(0u, ref.size());
}

// Test setting type to same type doesn't break
TEST_F(NodeRefTest_220, SetType_SameTypeNoOp_220) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("test");
  ref.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, ref.type());
  EXPECT_EQ("test", ref.scalar());
}

// Test insert and get on map
TEST_F(NodeRefTest_220, InsertAndGet_ReturnsInsertedValue_220) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  memory mem;
  shared_memory_holder pMem = mem.create_holder();

  node& key = mem.create_node();
  key.set_scalar("mykey");
  node& value = mem.create_node();
  value.set_scalar("myvalue");

  ref.insert(key, value, pMem);

  node* found = ref.get(std::string("mykey"), pMem);
  EXPECT_NE(nullptr, found);
}

// Test insert and remove on map
TEST_F(NodeRefTest_220, InsertAndRemove_RemovesEntry_220) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  memory mem;
  shared_memory_holder pMem = mem.create_holder();

  node& key = mem.create_node();
  key.set_scalar("mykey");
  node& value = mem.create_node();
  value.set_scalar("myvalue");

  ref.insert(key, value, pMem);
  EXPECT_EQ(1u, ref.size());

  bool removed = ref.remove(std::string("mykey"), pMem);
  EXPECT_TRUE(removed);
  EXPECT_EQ(0u, ref.size());
}

// Test force_insert
TEST_F(NodeRefTest_220, ForceInsert_AddsToMap_220) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  memory mem;
  shared_memory_holder pMem = mem.create_holder();

  ref.force_insert(std::string("key1"), std::string("value1"), pMem);
  EXPECT_EQ(1u, ref.size());
}

// Test default mark is null mark
TEST_F(NodeRefTest_220, DefaultMark_IsNullMark_220) {
  node_ref ref;
  const Mark& m = ref.mark();
  EXPECT_EQ(Mark::null_mark().line, m.line);
  EXPECT_EQ(Mark::null_mark().column, m.column);
  EXPECT_EQ(Mark::null_mark().pos, m.pos);
}

// Test default style
TEST_F(NodeRefTest_220, DefaultStyle_IsDefault_220) {
  node_ref ref;
  EXPECT_EQ(EmitterStyle::Default, ref.style());
}

// Test large scalar
TEST_F(NodeRefTest_220, SetScalar_LargeString_220) {
  node_ref ref;
  std::string largeStr(10000, 'x');
  ref.set_scalar(largeStr);
  EXPECT_EQ(largeStr, ref.scalar());
}

// Test special characters in scalar
TEST_F(NodeRefTest_220, SetScalar_SpecialCharacters_220) {
  node_ref ref;
  ref.set_scalar("hello\nworld\t\"test\"");
  EXPECT_EQ("hello\nworld\t\"test\"", ref.scalar());
}

// Test set_type from Sequence to Map
TEST_F(NodeRefTest_220, SetType_SequenceToMap_220) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);

  memory mem;
  shared_memory_holder pMem = mem.create_holder();

  node& n = mem.create_node();
  n.set_scalar("item");
  ref.push_back(n, pMem);
  EXPECT_EQ(1u, ref.size());

  ref.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, ref.type());
}

// Test get with node& on map
TEST_F(NodeRefTest_220, GetWithNodeRef_ReturnsValue_220) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  memory mem;
  shared_memory_holder pMem = mem.create_holder();

  node& key = mem.create_node();
  key.set_scalar("k");
  node& value = mem.create_node();
  value.set_scalar("v");

  ref.insert(key, value, pMem);

  node* result = ref.get(key, pMem);
  EXPECT_NE(nullptr, result);
}

// Test remove with node& on map
TEST_F(NodeRefTest_220, RemoveWithNodeRef_220) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  memory mem;
  shared_memory_holder pMem = mem.create_holder();

  node& key = mem.create_node();
  key.set_scalar("k");
  node& value = mem.create_node();
  value.set_scalar("v");

  ref.insert(key, value, pMem);
  EXPECT_EQ(1u, ref.size());

  bool removed = ref.remove(key, pMem);
  EXPECT_TRUE(removed);
}

// Test remove with node& for nonexistent key
TEST_F(NodeRefTest_220, RemoveWithNodeRef_Nonexistent_220) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  memory mem;
  shared_memory_holder pMem = mem.create_holder();

  node& key = mem.create_node();
  key.set_scalar("nonexistent");

  bool removed = ref.remove(key, pMem);
  EXPECT_FALSE(removed);
}

}  // namespace detail
}  // namespace YAML
