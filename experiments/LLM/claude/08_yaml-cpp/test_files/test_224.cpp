#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeRefTest_224 : public ::testing::Test {
 protected:
  void SetUp() override {
    m_pMemory.reset(new Memory);
  }

  shared_memory_holder m_pMemory;
};

// Test default construction - node_ref should be in undefined/null state
TEST_F(NodeRefTest_224, DefaultConstruction_IsNotDefined_224) {
  node_ref ref;
  EXPECT_FALSE(ref.is_defined());
}

TEST_F(NodeRefTest_224, DefaultConstruction_TypeIsNull_224) {
  node_ref ref;
  EXPECT_EQ(NodeType::Null, ref.type());
}

TEST_F(NodeRefTest_224, DefaultConstruction_ScalarIsEmpty_224) {
  node_ref ref;
  EXPECT_TRUE(ref.scalar().empty());
}

TEST_F(NodeRefTest_224, DefaultConstruction_TagIsEmpty_224) {
  node_ref ref;
  EXPECT_TRUE(ref.tag().empty());
}

TEST_F(NodeRefTest_224, DefaultConstruction_StyleIsDefault_224) {
  node_ref ref;
  EXPECT_EQ(EmitterStyle::Default, ref.style());
}

TEST_F(NodeRefTest_224, DefaultConstruction_SizeIsZero_224) {
  node_ref ref;
  EXPECT_EQ(0u, ref.size());
}

// Test mark_defined
TEST_F(NodeRefTest_224, MarkDefined_MakesNodeDefined_224) {
  node_ref ref;
  ref.mark_defined();
  EXPECT_TRUE(ref.is_defined());
}

// Test set_type
TEST_F(NodeRefTest_224, SetType_Scalar_224) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, ref.type());
}

TEST_F(NodeRefTest_224, SetType_Sequence_224) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, ref.type());
}

TEST_F(NodeRefTest_224, SetType_Map_224) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, ref.type());
}

TEST_F(NodeRefTest_224, SetType_Null_224) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, ref.type());
}

TEST_F(NodeRefTest_224, SetType_Undefined_224) {
  node_ref ref;
  ref.set_type(NodeType::Undefined);
  EXPECT_EQ(NodeType::Undefined, ref.type());
}

// Test set_tag
TEST_F(NodeRefTest_224, SetTag_SetsTag_224) {
  node_ref ref;
  ref.set_tag("!mytag");
  EXPECT_EQ("!mytag", ref.tag());
}

TEST_F(NodeRefTest_224, SetTag_EmptyTag_224) {
  node_ref ref;
  ref.set_tag("");
  EXPECT_EQ("", ref.tag());
}

TEST_F(NodeRefTest_224, SetTag_OverwriteTag_224) {
  node_ref ref;
  ref.set_tag("!first");
  ref.set_tag("!second");
  EXPECT_EQ("!second", ref.tag());
}

// Test set_scalar
TEST_F(NodeRefTest_224, SetScalar_SetsScalar_224) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("hello");
  EXPECT_EQ("hello", ref.scalar());
}

TEST_F(NodeRefTest_224, SetScalar_EmptyScalar_224) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("");
  EXPECT_EQ("", ref.scalar());
}

TEST_F(NodeRefTest_224, SetScalar_OverwriteScalar_224) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("first");
  ref.set_scalar("second");
  EXPECT_EQ("second", ref.scalar());
}

// Test set_null
TEST_F(NodeRefTest_224, SetNull_TypeBecomesNull_224) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_null();
  EXPECT_EQ(NodeType::Null, ref.type());
}

// Test set_style
TEST_F(NodeRefTest_224, SetStyle_Block_224) {
  node_ref ref;
  ref.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, ref.style());
}

TEST_F(NodeRefTest_224, SetStyle_Flow_224) {
  node_ref ref;
  ref.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, ref.style());
}

TEST_F(NodeRefTest_224, SetStyle_Default_224) {
  node_ref ref;
  ref.set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, ref.style());
}

// Test set_mark
TEST_F(NodeRefTest_224, SetMark_SetsMarkValues_224) {
  node_ref ref;
  Mark mark;
  mark.line = 10;
  mark.column = 20;
  mark.pos = 30;
  ref.set_mark(mark);
  EXPECT_EQ(10, ref.mark().line);
  EXPECT_EQ(20, ref.mark().column);
  EXPECT_EQ(30, ref.mark().pos);
}

// Test default mark is null
TEST_F(NodeRefTest_224, DefaultMark_IsNullMark_224) {
  node_ref ref;
  Mark null_mark = Mark::null_mark();
  EXPECT_EQ(null_mark.line, ref.mark().line);
  EXPECT_EQ(null_mark.column, ref.mark().column);
  EXPECT_EQ(null_mark.pos, ref.mark().pos);
}

// Test sequence operations
TEST_F(NodeRefTest_224, PushBack_IncreasesSize_224) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);

  node& n = m_pMemory->create_node();
  n.set_scalar("test");

  ref.push_back(n, m_pMemory);
  EXPECT_EQ(1u, ref.size());
}

TEST_F(NodeRefTest_224, PushBack_MultiplePushBacks_224) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);

  node& n1 = m_pMemory->create_node();
  n1.set_scalar("a");
  node& n2 = m_pMemory->create_node();
  n2.set_scalar("b");
  node& n3 = m_pMemory->create_node();
  n3.set_scalar("c");

  ref.push_back(n1, m_pMemory);
  ref.push_back(n2, m_pMemory);
  ref.push_back(n3, m_pMemory);
  EXPECT_EQ(3u, ref.size());
}

// Test begin/end for empty sequence
TEST_F(NodeRefTest_224, BeginEqualsEnd_EmptySequence_224) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  EXPECT_EQ(ref.begin(), ref.end());
}

// Test map operations - insert
TEST_F(NodeRefTest_224, Insert_IncreasesSize_224) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node& key = m_pMemory->create_node();
  key.set_scalar("key1");
  node& val = m_pMemory->create_node();
  val.set_scalar("val1");

  ref.insert(key, val, m_pMemory);
  EXPECT_EQ(1u, ref.size());
}

TEST_F(NodeRefTest_224, Insert_MultipleInserts_224) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node& key1 = m_pMemory->create_node();
  key1.set_scalar("key1");
  node& val1 = m_pMemory->create_node();
  val1.set_scalar("val1");

  node& key2 = m_pMemory->create_node();
  key2.set_scalar("key2");
  node& val2 = m_pMemory->create_node();
  val2.set_scalar("val2");

  ref.insert(key1, val1, m_pMemory);
  ref.insert(key2, val2, m_pMemory);
  EXPECT_EQ(2u, ref.size());
}

// Test begin/end for empty map
TEST_F(NodeRefTest_224, BeginEqualsEnd_EmptyMap_224) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  EXPECT_EQ(ref.begin(), ref.end());
}

// Test get on map with string key
TEST_F(NodeRefTest_224, Get_StringKey_ExistingKey_224) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node& key = m_pMemory->create_node();
  key.set_scalar("mykey");
  node& val = m_pMemory->create_node();
  val.set_scalar("myval");

  ref.insert(key, val, m_pMemory);

  node* result = ref.get(std::string("mykey"), m_pMemory);
  EXPECT_NE(nullptr, result);
}

TEST_F(NodeRefTest_224, Get_StringKey_NonExistingKey_224) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node& key = m_pMemory->create_node();
  key.set_scalar("mykey");
  node& val = m_pMemory->create_node();
  val.set_scalar("myval");

  ref.insert(key, val, m_pMemory);

  node* result = ref.get(std::string("nonexistent"), m_pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test remove on map with string key
TEST_F(NodeRefTest_224, Remove_StringKey_ExistingKey_224) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node& key = m_pMemory->create_node();
  key.set_scalar("mykey");
  node& val = m_pMemory->create_node();
  val.set_scalar("myval");

  ref.insert(key, val, m_pMemory);

  bool removed = ref.remove(std::string("mykey"), m_pMemory);
  EXPECT_TRUE(removed);
}

TEST_F(NodeRefTest_224, Remove_StringKey_NonExistingKey_224) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node& key = m_pMemory->create_node();
  key.set_scalar("mykey");
  node& val = m_pMemory->create_node();
  val.set_scalar("myval");

  ref.insert(key, val, m_pMemory);

  bool removed = ref.remove(std::string("nonexistent"), m_pMemory);
  EXPECT_FALSE(removed);
}

// Test get with node key
TEST_F(NodeRefTest_224, Get_NodeKey_ExistingKey_224) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node& key = m_pMemory->create_node();
  key.set_scalar("mykey");
  node& val = m_pMemory->create_node();
  val.set_scalar("myval");

  ref.insert(key, val, m_pMemory);

  node* result = ref.get(key, m_pMemory);
  EXPECT_NE(nullptr, result);
}

TEST_F(NodeRefTest_224, Get_NodeKey_NonExistingKey_224) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node& key = m_pMemory->create_node();
  key.set_scalar("mykey");
  node& val = m_pMemory->create_node();
  val.set_scalar("myval");

  ref.insert(key, val, m_pMemory);

  node& otherKey = m_pMemory->create_node();
  otherKey.set_scalar("otherkey");

  node* result = ref.get(otherKey, m_pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test remove with node key
TEST_F(NodeRefTest_224, Remove_NodeKey_ExistingKey_224) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node& key = m_pMemory->create_node();
  key.set_scalar("mykey");
  node& val = m_pMemory->create_node();
  val.set_scalar("myval");

  ref.insert(key, val, m_pMemory);

  bool removed = ref.remove(key, m_pMemory);
  EXPECT_TRUE(removed);
}

TEST_F(NodeRefTest_224, Remove_NodeKey_NonExistingKey_224) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node& key = m_pMemory->create_node();
  key.set_scalar("mykey");
  node& val = m_pMemory->create_node();
  val.set_scalar("myval");

  ref.insert(key, val, m_pMemory);

  node& otherKey = m_pMemory->create_node();
  otherKey.set_scalar("otherkey");

  bool removed = ref.remove(otherKey, m_pMemory);
  EXPECT_FALSE(removed);
}

// Test set_data copies from another node_ref
TEST_F(NodeRefTest_224, SetData_CopiesState_224) {
  node_ref source;
  source.set_type(NodeType::Scalar);
  source.set_scalar("copied");
  source.set_tag("!tag");
  source.set_style(EmitterStyle::Flow);
  source.mark_defined();

  node_ref target;
  target.set_data(source);

  EXPECT_EQ("copied", target.scalar());
  EXPECT_EQ("!tag", target.tag());
  EXPECT_EQ(EmitterStyle::Flow, target.style());
}

// Test force_insert
TEST_F(NodeRefTest_224, ForceInsert_AddsToMap_224) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  ref.force_insert(std::string("key1"), std::string("val1"), m_pMemory);
  EXPECT_EQ(1u, ref.size());
}

TEST_F(NodeRefTest_224, ForceInsert_MultiplePairs_224) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  ref.force_insert(std::string("key1"), std::string("val1"), m_pMemory);
  ref.force_insert(std::string("key2"), std::string("val2"), m_pMemory);
  ref.force_insert(std::string("key3"), std::string("val3"), m_pMemory);
  EXPECT_EQ(3u, ref.size());
}

// Test size for null node
TEST_F(NodeRefTest_224, Size_NullNode_IsZero_224) {
  node_ref ref;
  EXPECT_EQ(0u, ref.size());
}

// Test changing type resets contents
TEST_F(NodeRefTest_224, SetType_ChangingTypeFromScalar_ResetsScalar_224) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("hello");
  EXPECT_EQ("hello", ref.scalar());

  ref.set_type(NodeType::Null);
  // After changing to Null, scalar should be empty
  EXPECT_TRUE(ref.scalar().empty());
}

// Test switching between sequence and map
TEST_F(NodeRefTest_224, SetType_SequenceToMap_224) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);

  node& n = m_pMemory->create_node();
  n.set_scalar("test");
  ref.push_back(n, m_pMemory);
  EXPECT_EQ(1u, ref.size());

  ref.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, ref.type());
}

// Test setting style multiple times
TEST_F(NodeRefTest_224, SetStyle_MultipleTimes_224) {
  node_ref ref;
  ref.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, ref.style());
  ref.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, ref.style());
  ref.set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, ref.style());
}

// Test that set_scalar also sets type to scalar
TEST_F(NodeRefTest_224, SetScalar_SetsScalarValue_224) {
  node_ref ref;
  ref.set_scalar("value");
  EXPECT_EQ("value", ref.scalar());
  EXPECT_EQ(NodeType::Scalar, ref.type());
}

// Test large scalar
TEST_F(NodeRefTest_224, SetScalar_LargeScalar_224) {
  node_ref ref;
  std::string large(10000, 'x');
  ref.set_scalar(large);
  EXPECT_EQ(large, ref.scalar());
}

// Test that mark_defined keeps type
TEST_F(NodeRefTest_224, MarkDefined_KeepsType_224) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.mark_defined();
  EXPECT_TRUE(ref.is_defined());
  EXPECT_EQ(NodeType::Scalar, ref.type());
}

}  // namespace detail
}  // namespace YAML
