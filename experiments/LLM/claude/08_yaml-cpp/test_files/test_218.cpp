#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"
#include "yaml-cpp/node/type.h"
#include "yaml-cpp/emitterstyle.h"
#include "yaml-cpp/mark.h"

namespace YAML {
namespace detail {

class NodeRefTest_218 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory.reset(new Memory);
  }

  shared_memory_holder pMemory;
};

// Test default construction - node should not be defined initially and have Undefined type
TEST_F(NodeRefTest_218, DefaultConstruction_IsNotDefined_218) {
  node_ref ref;
  EXPECT_FALSE(ref.is_defined());
}

TEST_F(NodeRefTest_218, DefaultConstruction_TypeIsUndefined_218) {
  node_ref ref;
  EXPECT_EQ(NodeType::Undefined, ref.type());
}

// Test mark_defined makes the node defined
TEST_F(NodeRefTest_218, MarkDefined_MakesNodeDefined_218) {
  node_ref ref;
  ref.mark_defined();
  EXPECT_TRUE(ref.is_defined());
}

// Test set_type changes the type
TEST_F(NodeRefTest_218, SetType_Null_218) {
  node_ref ref;
  ref.set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, ref.type());
}

TEST_F(NodeRefTest_218, SetType_Scalar_218) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, ref.type());
}

TEST_F(NodeRefTest_218, SetType_Sequence_218) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, ref.type());
}

TEST_F(NodeRefTest_218, SetType_Map_218) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, ref.type());
}

// Test set_null sets type to Null
TEST_F(NodeRefTest_218, SetNull_TypeBecomesNull_218) {
  node_ref ref;
  ref.set_null();
  EXPECT_EQ(NodeType::Null, ref.type());
}

// Test set_scalar
TEST_F(NodeRefTest_218, SetScalar_ScalarValueIsSet_218) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("hello");
  EXPECT_EQ("hello", ref.scalar());
}

TEST_F(NodeRefTest_218, SetScalar_EmptyString_218) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("");
  EXPECT_EQ("", ref.scalar());
}

// Test set_tag and tag
TEST_F(NodeRefTest_218, SetTag_TagIsRetrievable_218) {
  node_ref ref;
  ref.set_tag("!!str");
  EXPECT_EQ("!!str", ref.tag());
}

TEST_F(NodeRefTest_218, SetTag_EmptyTag_218) {
  node_ref ref;
  ref.set_tag("");
  EXPECT_EQ("", ref.tag());
}

// Test set_style and style
TEST_F(NodeRefTest_218, SetStyle_Default_218) {
  node_ref ref;
  ref.set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, ref.style());
}

TEST_F(NodeRefTest_218, SetStyle_Block_218) {
  node_ref ref;
  ref.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, ref.style());
}

TEST_F(NodeRefTest_218, SetStyle_Flow_218) {
  node_ref ref;
  ref.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, ref.style());
}

// Test set_mark and mark
TEST_F(NodeRefTest_218, SetMark_MarkIsRetrievable_218) {
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

// Test set_data copies data from another node_ref
TEST_F(NodeRefTest_218, SetData_CopiesDataFromOther_218) {
  node_ref src;
  src.set_type(NodeType::Scalar);
  src.set_scalar("copied");
  src.set_tag("!!str");
  src.mark_defined();

  node_ref dest;
  dest.set_data(src);

  EXPECT_EQ(NodeType::Scalar, dest.type());
  EXPECT_EQ("copied", dest.scalar());
  EXPECT_EQ("!!str", dest.tag());
  EXPECT_TRUE(dest.is_defined());
}

TEST_F(NodeRefTest_218, SetData_SharedState_218) {
  node_ref src;
  src.set_type(NodeType::Scalar);
  src.set_scalar("initial");

  node_ref dest;
  dest.set_data(src);

  // After set_data, they share the same data. Modifying one should affect the other.
  src.set_scalar("modified");
  EXPECT_EQ("modified", dest.scalar());
}

// Test size for empty sequence
TEST_F(NodeRefTest_218, Size_EmptySequence_218) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  EXPECT_EQ(0u, ref.size());
}

// Test size for empty map
TEST_F(NodeRefTest_218, Size_EmptyMap_218) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  EXPECT_EQ(0u, ref.size());
}

// Test push_back on sequence
TEST_F(NodeRefTest_218, PushBack_IncreasesSize_218) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);

  node& n = pMemory->create_node();
  n.set_scalar("value1");

  ref.push_back(n, pMemory);
  EXPECT_EQ(1u, ref.size());
}

TEST_F(NodeRefTest_218, PushBack_MultiplePushes_218) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);

  node& n1 = pMemory->create_node();
  n1.set_scalar("v1");
  node& n2 = pMemory->create_node();
  n2.set_scalar("v2");
  node& n3 = pMemory->create_node();
  n3.set_scalar("v3");

  ref.push_back(n1, pMemory);
  ref.push_back(n2, pMemory);
  ref.push_back(n3, pMemory);
  EXPECT_EQ(3u, ref.size());
}

// Test begin == end for empty sequence
TEST_F(NodeRefTest_218, BeginEqualsEndForEmptySequence_218) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  EXPECT_EQ(ref.begin(), ref.end());
}

// Test begin != end after push_back
TEST_F(NodeRefTest_218, BeginNotEqualsEndAfterPushBack_218) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);

  node& n = pMemory->create_node();
  n.set_scalar("item");
  ref.push_back(n, pMemory);

  EXPECT_NE(ref.begin(), ref.end());
}

// Test insert on map
TEST_F(NodeRefTest_218, Insert_IncreasesSize_218) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("key1");
  node& value = pMemory->create_node();
  value.set_scalar("value1");

  ref.insert(key, value, pMemory);
  EXPECT_EQ(1u, ref.size());
}

// Test get with string key on map
TEST_F(NodeRefTest_218, Get_ExistingKey_ReturnsNode_218) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("mykey");
  node& value = pMemory->create_node();
  value.set_scalar("myvalue");

  ref.insert(key, value, pMemory);

  node* result = ref.get(std::string("mykey"), pMemory);
  EXPECT_NE(nullptr, result);
}

TEST_F(NodeRefTest_218, Get_NonExistingKey_ReturnsNull_218) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node* result = ref.get(std::string("nonexistent"), pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test get with index on sequence
TEST_F(NodeRefTest_218, Get_SequenceByIndex_218) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);

  node& n = pMemory->create_node();
  n.set_scalar("item0");
  ref.push_back(n, pMemory);

  node* result = ref.get(std::size_t(0), pMemory);
  EXPECT_NE(nullptr, result);
}

TEST_F(NodeRefTest_218, Get_SequenceOutOfRange_ReturnsNull_218) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);

  node* result = ref.get(std::size_t(0), pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test remove with string key on map
TEST_F(NodeRefTest_218, Remove_ExistingKey_ReturnsTrue_218) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("key1");
  node& value = pMemory->create_node();
  value.set_scalar("value1");

  ref.insert(key, value, pMemory);

  bool removed = ref.remove(std::string("key1"), pMemory);
  EXPECT_TRUE(removed);
}

TEST_F(NodeRefTest_218, Remove_NonExistingKey_ReturnsFalse_218) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  bool removed = ref.remove(std::string("nonexistent"), pMemory);
  EXPECT_FALSE(removed);
}

// Test remove with node key on map
TEST_F(NodeRefTest_218, Remove_WithNodeKey_ExistingKey_218) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("key1");
  node& value = pMemory->create_node();
  value.set_scalar("value1");

  ref.insert(key, value, pMemory);

  bool removed = ref.remove(key, pMemory);
  EXPECT_TRUE(removed);
}

TEST_F(NodeRefTest_218, Remove_WithNodeKey_NonExistingKey_218) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("nonexistent");

  bool removed = ref.remove(key, pMemory);
  EXPECT_FALSE(removed);
}

// Test get with node key on map
TEST_F(NodeRefTest_218, Get_WithNodeKey_ExistingKey_218) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("key1");
  node& value = pMemory->create_node();
  value.set_scalar("value1");

  ref.insert(key, value, pMemory);

  node* result = ref.get(key, pMemory);
  EXPECT_NE(nullptr, result);
}

TEST_F(NodeRefTest_218, Get_WithNodeKey_NonExistingKey_218) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("nonexistent");

  node* result = ref.get(key, pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test changing type resets content
TEST_F(NodeRefTest_218, SetType_ChangingFromScalarToSequence_218) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("hello");
  EXPECT_EQ(NodeType::Scalar, ref.type());

  ref.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, ref.type());
  EXPECT_EQ(0u, ref.size());
}

// Test force_insert on map
TEST_F(NodeRefTest_218, ForceInsert_AddsEntry_218) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  ref.force_insert(std::string("key1"), std::string("value1"), pMemory);
  EXPECT_EQ(1u, ref.size());
}

TEST_F(NodeRefTest_218, ForceInsert_AllowsDuplicateKeys_218) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  ref.force_insert(std::string("key1"), std::string("value1"), pMemory);
  ref.force_insert(std::string("key1"), std::string("value2"), pMemory);
  EXPECT_EQ(2u, ref.size());
}

// Test set_data from an undefined node_ref
TEST_F(NodeRefTest_218, SetData_FromUndefinedSource_218) {
  node_ref src;
  node_ref dest;
  dest.set_type(NodeType::Scalar);
  dest.set_scalar("something");

  dest.set_data(src);
  EXPECT_EQ(NodeType::Undefined, dest.type());
}

// Test that after remove, size decreases
TEST_F(NodeRefTest_218, Remove_DecreasesSize_218) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("key1");
  node& value = pMemory->create_node();
  value.set_scalar("value1");

  ref.insert(key, value, pMemory);
  EXPECT_EQ(1u, ref.size());

  ref.remove(std::string("key1"), pMemory);
  EXPECT_EQ(0u, ref.size());
}

// Test default mark values
TEST_F(NodeRefTest_218, DefaultMark_218) {
  node_ref ref;
  const Mark& m = ref.mark();
  EXPECT_EQ(0, m.pos);
  EXPECT_EQ(0, m.line);
  EXPECT_EQ(0, m.column);
}

// Test default scalar is empty
TEST_F(NodeRefTest_218, DefaultScalar_IsEmpty_218) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  EXPECT_EQ("", ref.scalar());
}

// Test default tag is empty
TEST_F(NodeRefTest_218, DefaultTag_IsEmpty_218) {
  node_ref ref;
  EXPECT_EQ("", ref.tag());
}

// Test default style
TEST_F(NodeRefTest_218, DefaultStyle_IsDefault_218) {
  node_ref ref;
  EXPECT_EQ(EmitterStyle::Default, ref.style());
}

}  // namespace detail
}  // namespace YAML
