#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/node_data.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeRefTest_228 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = shared_memory_holder(new memory);
  }

  shared_memory_holder pMemory;
};

// Test default construction - node_ref should be in a valid initial state
TEST_F(NodeRefTest_228, DefaultConstruction_IsDefined_228) {
  node_ref ref;
  EXPECT_FALSE(ref.is_defined());
}

TEST_F(NodeRefTest_228, DefaultConstruction_TypeIsNull_228) {
  node_ref ref;
  EXPECT_EQ(NodeType::Null, ref.type());
}

TEST_F(NodeRefTest_228, DefaultConstruction_ScalarIsEmpty_228) {
  node_ref ref;
  EXPECT_TRUE(ref.scalar().empty());
}

TEST_F(NodeRefTest_228, DefaultConstruction_TagIsEmpty_228) {
  node_ref ref;
  EXPECT_TRUE(ref.tag().empty());
}

TEST_F(NodeRefTest_228, DefaultConstruction_SizeIsZero_228) {
  node_ref ref;
  EXPECT_EQ(0u, ref.size());
}

// Test mark_defined
TEST_F(NodeRefTest_228, MarkDefined_MakesNodeDefined_228) {
  node_ref ref;
  ref.mark_defined();
  EXPECT_TRUE(ref.is_defined());
}

// Test set_type
TEST_F(NodeRefTest_228, SetType_Sequence_228) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, ref.type());
}

TEST_F(NodeRefTest_228, SetType_Map_228) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, ref.type());
}

TEST_F(NodeRefTest_228, SetType_Scalar_228) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, ref.type());
}

TEST_F(NodeRefTest_228, SetType_Null_228) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  ref.set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, ref.type());
}

TEST_F(NodeRefTest_228, SetType_Undefined_228) {
  node_ref ref;
  ref.set_type(NodeType::Undefined);
  EXPECT_EQ(NodeType::Undefined, ref.type());
}

// Test set_null
TEST_F(NodeRefTest_228, SetNull_SetsTypeToNull_228) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_null();
  EXPECT_EQ(NodeType::Null, ref.type());
}

// Test set_scalar
TEST_F(NodeRefTest_228, SetScalar_SetsScalarValue_228) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("hello");
  EXPECT_EQ("hello", ref.scalar());
}

TEST_F(NodeRefTest_228, SetScalar_EmptyString_228) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("");
  EXPECT_EQ("", ref.scalar());
}

TEST_F(NodeRefTest_228, SetScalar_OverwritePrevious_228) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("first");
  ref.set_scalar("second");
  EXPECT_EQ("second", ref.scalar());
}

// Test set_tag
TEST_F(NodeRefTest_228, SetTag_SetsTagValue_228) {
  node_ref ref;
  ref.set_tag("!custom");
  EXPECT_EQ("!custom", ref.tag());
}

TEST_F(NodeRefTest_228, SetTag_EmptyTag_228) {
  node_ref ref;
  ref.set_tag("");
  EXPECT_EQ("", ref.tag());
}

// Test set_style
TEST_F(NodeRefTest_228, SetStyle_Block_228) {
  node_ref ref;
  ref.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, ref.style());
}

TEST_F(NodeRefTest_228, SetStyle_Flow_228) {
  node_ref ref;
  ref.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, ref.style());
}

TEST_F(NodeRefTest_228, SetStyle_Default_228) {
  node_ref ref;
  ref.set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, ref.style());
}

// Test set_mark
TEST_F(NodeRefTest_228, SetMark_SetsMarkValue_228) {
  node_ref ref;
  Mark m;
  m.pos = 10;
  m.line = 5;
  m.column = 3;
  ref.set_mark(m);
  EXPECT_EQ(5, ref.mark().line);
  EXPECT_EQ(3, ref.mark().column);
  EXPECT_EQ(10, ref.mark().pos);
}

// Test push_back for sequence
TEST_F(NodeRefTest_228, PushBack_AddsToSequence_228) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);

  node& n = pMemory->create_node();
  n.set_scalar("value1");

  ref.push_back(n, pMemory);
  EXPECT_EQ(1u, ref.size());
}

TEST_F(NodeRefTest_228, PushBack_MultipleElements_228) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);

  node& n1 = pMemory->create_node();
  n1.set_scalar("value1");
  node& n2 = pMemory->create_node();
  n2.set_scalar("value2");
  node& n3 = pMemory->create_node();
  n3.set_scalar("value3");

  ref.push_back(n1, pMemory);
  ref.push_back(n2, pMemory);
  ref.push_back(n3, pMemory);
  EXPECT_EQ(3u, ref.size());
}

// Test push_back on Null type should convert to Sequence
TEST_F(NodeRefTest_228, PushBack_NullTypeConvertsToSequence_228) {
  node_ref ref;
  EXPECT_EQ(NodeType::Null, ref.type());

  node& n = pMemory->create_node();
  n.set_scalar("value");

  ref.push_back(n, pMemory);
  EXPECT_EQ(NodeType::Sequence, ref.type());
  EXPECT_EQ(1u, ref.size());
}

// Test insert for map
TEST_F(NodeRefTest_228, Insert_AddsKeyValuePair_228) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("key1");
  node& value = pMemory->create_node();
  value.set_scalar("value1");

  ref.insert(key, value, pMemory);
  EXPECT_EQ(1u, ref.size());
}

TEST_F(NodeRefTest_228, Insert_MultipleKeyValuePairs_228) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node& key1 = pMemory->create_node();
  key1.set_scalar("key1");
  node& val1 = pMemory->create_node();
  val1.set_scalar("val1");

  node& key2 = pMemory->create_node();
  key2.set_scalar("key2");
  node& val2 = pMemory->create_node();
  val2.set_scalar("val2");

  ref.insert(key1, val1, pMemory);
  ref.insert(key2, val2, pMemory);
  EXPECT_EQ(2u, ref.size());
}

// Test get for map with string key
TEST_F(NodeRefTest_228, Get_ExistingStringKey_228) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("mykey");
  node& val = pMemory->create_node();
  val.set_scalar("myvalue");

  ref.insert(key, val, pMemory);

  node* result = ref.get(std::string("mykey"), pMemory);
  EXPECT_NE(nullptr, result);
  EXPECT_EQ("myvalue", result->scalar());
}

TEST_F(NodeRefTest_228, Get_NonExistingStringKey_228) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("mykey");
  node& val = pMemory->create_node();
  val.set_scalar("myvalue");

  ref.insert(key, val, pMemory);

  node* result = ref.get(std::string("nonexistent"), pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test get with node key
TEST_F(NodeRefTest_228, Get_WithNodeKey_228) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("nodekey");
  node& val = pMemory->create_node();
  val.set_scalar("nodevalue");

  ref.insert(key, val, pMemory);

  node* result = ref.get(key, pMemory);
  EXPECT_NE(nullptr, result);
  EXPECT_EQ("nodevalue", result->scalar());
}

// Test remove
TEST_F(NodeRefTest_228, Remove_ExistingKey_228) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("removekey");
  node& val = pMemory->create_node();
  val.set_scalar("removeval");

  ref.insert(key, val, pMemory);
  EXPECT_EQ(1u, ref.size());

  bool removed = ref.remove(std::string("removekey"), pMemory);
  EXPECT_TRUE(removed);
}

TEST_F(NodeRefTest_228, Remove_NonExistingKey_228) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("existingkey");
  node& val = pMemory->create_node();
  val.set_scalar("existingval");

  ref.insert(key, val, pMemory);

  bool removed = ref.remove(std::string("nonexistent"), pMemory);
  EXPECT_FALSE(removed);
}

TEST_F(NodeRefTest_228, Remove_WithNodeKey_228) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("nkey");
  node& val = pMemory->create_node();
  val.set_scalar("nval");

  ref.insert(key, val, pMemory);

  bool removed = ref.remove(key, pMemory);
  EXPECT_TRUE(removed);
}

// Test set_data - copies data from another node_ref
TEST_F(NodeRefTest_228, SetData_CopiesFromOther_228) {
  node_ref ref1;
  ref1.set_type(NodeType::Scalar);
  ref1.set_scalar("copied_data");
  ref1.set_tag("!tag");
  ref1.mark_defined();

  node_ref ref2;
  ref2.set_data(ref1);

  EXPECT_EQ(NodeType::Scalar, ref2.type());
  EXPECT_EQ("copied_data", ref2.scalar());
  EXPECT_EQ("!tag", ref2.tag());
}

// Test begin and end iterators for empty sequence
TEST_F(NodeRefTest_228, BeginEndIterators_EmptySequence_228) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  EXPECT_EQ(ref.begin(), ref.end());
}

// Test begin and end iterators for non-empty sequence
TEST_F(NodeRefTest_228, BeginEndIterators_NonEmptySequence_228) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);

  node& n1 = pMemory->create_node();
  n1.set_scalar("elem");
  ref.push_back(n1, pMemory);

  EXPECT_NE(ref.begin(), ref.end());
}

// Test force_insert
TEST_F(NodeRefTest_228, ForceInsert_AddsKeyValuePair_228) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  ref.force_insert(std::string("forcekey"), std::string("forceval"), pMemory);
  EXPECT_EQ(1u, ref.size());
}

// Test size for empty map
TEST_F(NodeRefTest_228, Size_EmptyMap_228) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  EXPECT_EQ(0u, ref.size());
}

// Test size for Null type
TEST_F(NodeRefTest_228, Size_NullType_228) {
  node_ref ref;
  EXPECT_EQ(0u, ref.size());
}

// Test sequence to map conversion via push_back then insert-like operations
TEST_F(NodeRefTest_228, PushBack_ThenConvertToMap_228) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);

  node& n1 = pMemory->create_node();
  n1.set_scalar("first");
  ref.push_back(n1, pMemory);

  node& n2 = pMemory->create_node();
  n2.set_scalar("second");
  ref.push_back(n2, pMemory);

  EXPECT_EQ(2u, ref.size());
  EXPECT_EQ(NodeType::Sequence, ref.type());
}

// Test default mark is null
TEST_F(NodeRefTest_228, DefaultMark_IsNullMark_228) {
  node_ref ref;
  const Mark& m = ref.mark();
  EXPECT_EQ(Mark::null_mark().pos, m.pos);
  EXPECT_EQ(Mark::null_mark().line, m.line);
  EXPECT_EQ(Mark::null_mark().column, m.column);
}

// Test default style
TEST_F(NodeRefTest_228, DefaultStyle_228) {
  node_ref ref;
  EXPECT_EQ(EmitterStyle::Default, ref.style());
}

// Test setting scalar on a non-Scalar type
TEST_F(NodeRefTest_228, SetScalar_ChangesTypeToScalar_228) {
  node_ref ref;
  ref.set_type(NodeType::Null);
  ref.set_scalar("test_scalar");
  EXPECT_EQ("test_scalar", ref.scalar());
}

// Test multiple type changes
TEST_F(NodeRefTest_228, MultipleTypeChanges_228) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, ref.type());

  ref.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, ref.type());

  ref.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, ref.type());

  ref.set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, ref.type());
}

// Test get on empty map returns nullptr
TEST_F(NodeRefTest_228, Get_EmptyMap_ReturnsNull_228) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node* result = ref.get(std::string("anykey"), pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test remove on empty map returns false
TEST_F(NodeRefTest_228, Remove_EmptyMap_ReturnsFalse_228) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  bool removed = ref.remove(std::string("anykey"), pMemory);
  EXPECT_FALSE(removed);
}

}  // namespace detail
}  // namespace YAML
