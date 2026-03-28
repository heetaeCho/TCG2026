#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node_data.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"
#include "yaml-cpp/node/type.h"

namespace YAML {
namespace detail {

class NodeDataTest_642 : public ::testing::Test {
 protected:
  void SetUp() override {
    m_pMemory.reset(new Memory);
  }

  shared_memory_holder m_pMemory;
};

// Test default construction
TEST_F(NodeDataTest_642, DefaultConstruction_IsNotDefined_642) {
  node_data nd;
  EXPECT_FALSE(nd.is_defined());
  EXPECT_EQ(NodeType::Null, nd.type());
}

// Test set_type to Null
TEST_F(NodeDataTest_642, SetTypeNull_TypeIsNull_642) {
  node_data nd;
  nd.set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, nd.type());
  EXPECT_TRUE(nd.is_defined());
}

// Test set_type to Scalar
TEST_F(NodeDataTest_642, SetTypeScalar_TypeIsScalar_642) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, nd.type());
  EXPECT_TRUE(nd.is_defined());
}

// Test set_type to Sequence
TEST_F(NodeDataTest_642, SetTypeSequence_TypeIsSequence_642) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, nd.type());
  EXPECT_TRUE(nd.is_defined());
}

// Test set_type to Map
TEST_F(NodeDataTest_642, SetTypeMap_TypeIsMap_642) {
  node_data nd;
  nd.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, nd.type());
  EXPECT_TRUE(nd.is_defined());
}

// Test set_type to Undefined
TEST_F(NodeDataTest_642, SetTypeUndefined_IsNotDefined_642) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  EXPECT_TRUE(nd.is_defined());
  nd.set_type(NodeType::Undefined);
  EXPECT_FALSE(nd.is_defined());
  EXPECT_EQ(NodeType::Undefined, nd.type());
}

// Test setting same type twice doesn't change anything
TEST_F(NodeDataTest_642, SetSameTypeTwice_NoChange_642) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("hello");
  nd.set_type(NodeType::Scalar);
  // Scalar should remain since type didn't change
  EXPECT_EQ("hello", nd.scalar());
}

// Test set_type clears scalar when switching from Scalar to Scalar (fresh set)
TEST_F(NodeDataTest_642, SetTypeScalarClearsScalar_642) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("test");
  EXPECT_EQ("test", nd.scalar());
  // Switch to a different type then back to scalar
  nd.set_type(NodeType::Map);
  nd.set_type(NodeType::Scalar);
  EXPECT_EQ("", nd.scalar());
}

// Test mark_defined
TEST_F(NodeDataTest_642, MarkDefined_IsDefinedReturnsTrue_642) {
  node_data nd;
  EXPECT_FALSE(nd.is_defined());
  nd.mark_defined();
  EXPECT_TRUE(nd.is_defined());
}

// Test set_tag and tag
TEST_F(NodeDataTest_642, SetTag_TagIsRetrievable_642) {
  node_data nd;
  nd.set_tag("!mytag");
  EXPECT_EQ("!mytag", nd.tag());
}

// Test set_tag empty
TEST_F(NodeDataTest_642, SetEmptyTag_TagIsEmpty_642) {
  node_data nd;
  nd.set_tag("");
  EXPECT_EQ("", nd.tag());
}

// Test set_null
TEST_F(NodeDataTest_642, SetNull_TypeBecomesNull_642) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_null();
  EXPECT_EQ(NodeType::Null, nd.type());
  EXPECT_TRUE(nd.is_defined());
}

// Test set_scalar
TEST_F(NodeDataTest_642, SetScalar_ScalarAndTypeCorrect_642) {
  node_data nd;
  nd.set_scalar("value");
  EXPECT_EQ(NodeType::Scalar, nd.type());
  EXPECT_EQ("value", nd.scalar());
  EXPECT_TRUE(nd.is_defined());
}

// Test set_scalar with empty string
TEST_F(NodeDataTest_642, SetScalarEmpty_ScalarIsEmpty_642) {
  node_data nd;
  nd.set_scalar("");
  EXPECT_EQ(NodeType::Scalar, nd.type());
  EXPECT_EQ("", nd.scalar());
}

// Test set_style
TEST_F(NodeDataTest_642, SetStyle_StyleIsRetrievable_642) {
  node_data nd;
  nd.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, nd.style());
}

// Test set_style Block
TEST_F(NodeDataTest_642, SetStyleBlock_642) {
  node_data nd;
  nd.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, nd.style());
}

// Test set_mark
TEST_F(NodeDataTest_642, SetMark_MarkIsRetrievable_642) {
  node_data nd;
  Mark m;
  m.line = 5;
  m.column = 10;
  nd.set_mark(m);
  EXPECT_EQ(5, nd.mark().line);
  EXPECT_EQ(10, nd.mark().column);
}

// Test empty_scalar static method
TEST_F(NodeDataTest_642, EmptyScalar_ReturnsEmptyString_642) {
  const std::string& empty = node_data::empty_scalar();
  EXPECT_TRUE(empty.empty());
}

// Test size for empty sequence
TEST_F(NodeDataTest_642, SizeEmptySequence_ReturnsZero_642) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  EXPECT_EQ(0u, nd.size());
}

// Test size for empty map
TEST_F(NodeDataTest_642, SizeEmptyMap_ReturnsZero_642) {
  node_data nd;
  nd.set_type(NodeType::Map);
  EXPECT_EQ(0u, nd.size());
}

// Test push_back on sequence
TEST_F(NodeDataTest_642, PushBackSequence_SizeIncreases_642) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  node& n = m_pMemory->create_node();
  n.set_scalar("item1");
  nd.push_back(n, m_pMemory);
  EXPECT_EQ(1u, nd.size());
}

// Test push_back multiple items
TEST_F(NodeDataTest_642, PushBackMultiple_SizeCorrect_642) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  for (int i = 0; i < 5; ++i) {
    node& n = m_pMemory->create_node();
    n.set_scalar("item");
    nd.push_back(n, m_pMemory);
  }
  EXPECT_EQ(5u, nd.size());
}

// Test insert on map
TEST_F(NodeDataTest_642, InsertMap_SizeIncreases_642) {
  node_data nd;
  nd.set_type(NodeType::Map);
  node& key = m_pMemory->create_node();
  key.set_scalar("key1");
  node& value = m_pMemory->create_node();
  value.set_scalar("value1");
  nd.insert(key, value, m_pMemory);
  EXPECT_EQ(1u, nd.size());
}

// Test get with string key on map
TEST_F(NodeDataTest_642, GetStringKeyMap_ReturnsNode_642) {
  node_data nd;
  nd.set_type(NodeType::Map);
  node& key = m_pMemory->create_node();
  key.set_scalar("mykey");
  node& value = m_pMemory->create_node();
  value.set_scalar("myvalue");
  nd.insert(key, value, m_pMemory);

  const node* result = nd.get(std::string("mykey"), m_pMemory);
  EXPECT_NE(nullptr, result);
}

// Test get with non-existing key returns nullptr
TEST_F(NodeDataTest_642, GetNonExistingKey_ReturnsNull_642) {
  node_data nd;
  nd.set_type(NodeType::Map);
  const node* result = nd.get(std::string("nonexistent"), m_pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test remove on map
TEST_F(NodeDataTest_642, RemoveExistingKey_ReturnsTrue_642) {
  node_data nd;
  nd.set_type(NodeType::Map);
  node& key = m_pMemory->create_node();
  key.set_scalar("removekey");
  node& value = m_pMemory->create_node();
  value.set_scalar("removevalue");
  nd.insert(key, value, m_pMemory);
  EXPECT_EQ(1u, nd.size());

  bool removed = nd.remove(std::string("removekey"), m_pMemory);
  EXPECT_TRUE(removed);
}

// Test remove non-existing key
TEST_F(NodeDataTest_642, RemoveNonExistingKey_ReturnsFalse_642) {
  node_data nd;
  nd.set_type(NodeType::Map);
  bool removed = nd.remove(std::string("nokey"), m_pMemory);
  EXPECT_FALSE(removed);
}

// Test begin == end for empty sequence
TEST_F(NodeDataTest_642, BeginEqualsEndEmptySequence_642) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  EXPECT_EQ(nd.begin(), nd.end());
}

// Test begin != end for non-empty sequence
TEST_F(NodeDataTest_642, BeginNotEqualsEndNonEmptySequence_642) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  node& n = m_pMemory->create_node();
  n.set_scalar("item");
  nd.push_back(n, m_pMemory);
  EXPECT_NE(nd.begin(), nd.end());
}

// Test begin == end for empty map
TEST_F(NodeDataTest_642, BeginEqualsEndEmptyMap_642) {
  node_data nd;
  nd.set_type(NodeType::Map);
  EXPECT_EQ(nd.begin(), nd.end());
}

// Test transition from Scalar to Sequence
TEST_F(NodeDataTest_642, TransitionScalarToSequence_642) {
  node_data nd;
  nd.set_scalar("hello");
  EXPECT_EQ(NodeType::Scalar, nd.type());
  nd.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, nd.type());
  EXPECT_EQ(0u, nd.size());
}

// Test transition from Sequence to Map
TEST_F(NodeDataTest_642, TransitionSequenceToMap_642) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  node& n = m_pMemory->create_node();
  n.set_scalar("item");
  nd.push_back(n, m_pMemory);
  EXPECT_EQ(1u, nd.size());

  nd.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, nd.type());
  EXPECT_EQ(0u, nd.size());
}

// Test transition from Map to Null
TEST_F(NodeDataTest_642, TransitionMapToNull_642) {
  node_data nd;
  nd.set_type(NodeType::Map);
  nd.set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, nd.type());
  EXPECT_TRUE(nd.is_defined());
}

// Test force_insert
TEST_F(NodeDataTest_642, ForceInsert_AddsEntry_642) {
  node_data nd;
  nd.set_type(NodeType::Map);
  nd.force_insert(std::string("key"), std::string("val"), m_pMemory);
  EXPECT_EQ(1u, nd.size());
}

// Test set_type Undefined then back to Scalar
TEST_F(NodeDataTest_642, SetUndefinedThenScalar_IsDefinedTrue_642) {
  node_data nd;
  nd.set_type(NodeType::Undefined);
  EXPECT_FALSE(nd.is_defined());
  nd.set_type(NodeType::Scalar);
  EXPECT_TRUE(nd.is_defined());
  EXPECT_EQ(NodeType::Scalar, nd.type());
}

// Test default scalar is empty for freshly created node_data
TEST_F(NodeDataTest_642, DefaultScalarIsEmpty_642) {
  node_data nd;
  EXPECT_TRUE(nd.scalar().empty());
}

// Test default tag is empty
TEST_F(NodeDataTest_642, DefaultTagIsEmpty_642) {
  node_data nd;
  EXPECT_TRUE(nd.tag().empty());
}

// Test get with node& key on map
TEST_F(NodeDataTest_642, GetWithNodeKey_ReturnsCorrectNode_642) {
  node_data nd;
  nd.set_type(NodeType::Map);
  node& key = m_pMemory->create_node();
  key.set_scalar("nodekey");
  node& value = m_pMemory->create_node();
  value.set_scalar("nodevalue");
  nd.insert(key, value, m_pMemory);

  const node* result = nd.get(key, m_pMemory);
  EXPECT_NE(nullptr, result);
}

// Test remove with node& key
TEST_F(NodeDataTest_642, RemoveWithNodeKey_ReturnsTrue_642) {
  node_data nd;
  nd.set_type(NodeType::Map);
  node& key = m_pMemory->create_node();
  key.set_scalar("k");
  node& value = m_pMemory->create_node();
  value.set_scalar("v");
  nd.insert(key, value, m_pMemory);

  bool removed = nd.remove(key, m_pMemory);
  EXPECT_TRUE(removed);
}

// Test set_scalar overwrites previous scalar
TEST_F(NodeDataTest_642, SetScalarOverwrites_642) {
  node_data nd;
  nd.set_scalar("first");
  EXPECT_EQ("first", nd.scalar());
  nd.set_scalar("second");
  EXPECT_EQ("second", nd.scalar());
}

// Test mark_defined does not change type
TEST_F(NodeDataTest_642, MarkDefinedDoesNotChangeType_642) {
  node_data nd;
  EXPECT_EQ(NodeType::Null, nd.type());
  nd.mark_defined();
  EXPECT_EQ(NodeType::Null, nd.type());
  EXPECT_TRUE(nd.is_defined());
}

// Test set_style Default
TEST_F(NodeDataTest_642, SetStyleDefault_642) {
  node_data nd;
  nd.set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, nd.style());
}

// Test size for Null type
TEST_F(NodeDataTest_642, SizeForNullType_ReturnsZero_642) {
  node_data nd;
  nd.set_type(NodeType::Null);
  EXPECT_EQ(0u, nd.size());
}

// Test size for Scalar type
TEST_F(NodeDataTest_642, SizeForScalarType_ReturnsZero_642) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  EXPECT_EQ(0u, nd.size());
}

}  // namespace detail
}  // namespace YAML
