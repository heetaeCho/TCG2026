#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node_data.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeDataTest_639 : public ::testing::Test {
 protected:
  void SetUp() override {
    m_memory = std::make_shared<memory_holder>();
    m_pMemory = m_memory->create_memory();
  }

  shared_memory_holder m_pMemory;
  std::shared_ptr<memory_holder> m_memory;
};

// Test default construction
TEST_F(NodeDataTest_639, DefaultConstruction_639) {
  node_data nd;
  EXPECT_FALSE(nd.is_defined());
  EXPECT_EQ(nd.type(), NodeType::Null);
  EXPECT_EQ(nd.scalar(), "");
  EXPECT_EQ(nd.tag(), "");
}

// Test empty_scalar returns empty string
TEST_F(NodeDataTest_639, EmptyScalarReturnsEmptyString_639) {
  const std::string& result = node_data::empty_scalar();
  EXPECT_TRUE(result.empty());
  EXPECT_EQ(result, "");
}

// Test empty_scalar returns same reference each time
TEST_F(NodeDataTest_639, EmptyScalarReturnsSameReference_639) {
  const std::string& ref1 = node_data::empty_scalar();
  const std::string& ref2 = node_data::empty_scalar();
  EXPECT_EQ(&ref1, &ref2);
}

// Test mark_defined
TEST_F(NodeDataTest_639, MarkDefined_639) {
  node_data nd;
  EXPECT_FALSE(nd.is_defined());
  nd.mark_defined();
  EXPECT_TRUE(nd.is_defined());
}

// Test set_mark and mark
TEST_F(NodeDataTest_639, SetMark_639) {
  node_data nd;
  Mark m;
  m.line = 5;
  m.column = 10;
  m.pos = 42;
  nd.set_mark(m);
  EXPECT_EQ(nd.mark().line, 5);
  EXPECT_EQ(nd.mark().column, 10);
  EXPECT_EQ(nd.mark().pos, 42);
}

// Test set_type to Scalar
TEST_F(NodeDataTest_639, SetTypeScalar_639) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  EXPECT_EQ(nd.type(), NodeType::Scalar);
}

// Test set_type to Sequence
TEST_F(NodeDataTest_639, SetTypeSequence_639) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  EXPECT_EQ(nd.type(), NodeType::Sequence);
}

// Test set_type to Map
TEST_F(NodeDataTest_639, SetTypeMap_639) {
  node_data nd;
  nd.set_type(NodeType::Map);
  EXPECT_EQ(nd.type(), NodeType::Map);
}

// Test set_type to Null
TEST_F(NodeDataTest_639, SetTypeNull_639) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_type(NodeType::Null);
  EXPECT_EQ(nd.type(), NodeType::Null);
}

// Test set_type to Undefined
TEST_F(NodeDataTest_639, SetTypeUndefined_639) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_type(NodeType::Undefined);
  EXPECT_EQ(nd.type(), NodeType::Undefined);
}

// Test set_tag
TEST_F(NodeDataTest_639, SetTag_639) {
  node_data nd;
  nd.set_tag("!!str");
  EXPECT_EQ(nd.tag(), "!!str");
}

// Test set_tag empty string
TEST_F(NodeDataTest_639, SetTagEmpty_639) {
  node_data nd;
  nd.set_tag("");
  EXPECT_EQ(nd.tag(), "");
}

// Test set_null
TEST_F(NodeDataTest_639, SetNull_639) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("hello");
  nd.set_null();
  EXPECT_EQ(nd.type(), NodeType::Null);
}

// Test set_scalar
TEST_F(NodeDataTest_639, SetScalar_639) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("test_value");
  EXPECT_EQ(nd.scalar(), "test_value");
}

// Test set_scalar with empty string
TEST_F(NodeDataTest_639, SetScalarEmpty_639) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("");
  EXPECT_EQ(nd.scalar(), "");
}

// Test set_style
TEST_F(NodeDataTest_639, SetStyleDefault_639) {
  node_data nd;
  nd.set_style(EmitterStyle::Default);
  EXPECT_EQ(nd.style(), EmitterStyle::Default);
}

TEST_F(NodeDataTest_639, SetStyleBlock_639) {
  node_data nd;
  nd.set_style(EmitterStyle::Block);
  EXPECT_EQ(nd.style(), EmitterStyle::Block);
}

TEST_F(NodeDataTest_639, SetStyleFlow_639) {
  node_data nd;
  nd.set_style(EmitterStyle::Flow);
  EXPECT_EQ(nd.style(), EmitterStyle::Flow);
}

// Test size for empty node
TEST_F(NodeDataTest_639, SizeDefault_639) {
  node_data nd;
  EXPECT_EQ(nd.size(), 0u);
}

// Test size for sequence
TEST_F(NodeDataTest_639, SizeSequenceAfterPushBack_639) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  node& n1 = m_pMemory->create_node();
  n1.set_data(new node_data());
  n1.data().set_type(NodeType::Scalar);
  n1.data().set_scalar("item1");
  nd.push_back(n1, m_pMemory);
  EXPECT_EQ(nd.size(), 1u);
}

// Test push_back multiple items
TEST_F(NodeDataTest_639, SizeSequenceMultiplePushBack_639) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  
  node& n1 = m_pMemory->create_node();
  n1.set_data(new node_data());
  n1.data().set_type(NodeType::Scalar);
  nd.push_back(n1, m_pMemory);
  
  node& n2 = m_pMemory->create_node();
  n2.set_data(new node_data());
  n2.data().set_type(NodeType::Scalar);
  nd.push_back(n2, m_pMemory);
  
  EXPECT_EQ(nd.size(), 2u);
}

// Test begin/end for empty sequence
TEST_F(NodeDataTest_639, BeginEndEmptySequence_639) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  EXPECT_EQ(nd.begin(), nd.end());
}

// Test begin/end for empty map
TEST_F(NodeDataTest_639, BeginEndEmptyMap_639) {
  node_data nd;
  nd.set_type(NodeType::Map);
  EXPECT_EQ(nd.begin(), nd.end());
}

// Test changing type resets content
TEST_F(NodeDataTest_639, ChangeTypeFromScalarToSequence_639) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("hello");
  nd.set_type(NodeType::Sequence);
  EXPECT_EQ(nd.type(), NodeType::Sequence);
  EXPECT_EQ(nd.size(), 0u);
}

// Test changing type from sequence to map
TEST_F(NodeDataTest_639, ChangeTypeFromSequenceToMap_639) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  nd.set_type(NodeType::Map);
  EXPECT_EQ(nd.type(), NodeType::Map);
  EXPECT_EQ(nd.size(), 0u);
}

// Test scalar returns empty for non-scalar type
TEST_F(NodeDataTest_639, ScalarForNonScalarType_639) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  EXPECT_EQ(nd.scalar(), "");
}

// Test set_scalar with special characters
TEST_F(NodeDataTest_639, SetScalarSpecialCharacters_639) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("hello\nworld\ttab");
  EXPECT_EQ(nd.scalar(), "hello\nworld\ttab");
}

// Test set_tag overwrite
TEST_F(NodeDataTest_639, SetTagOverwrite_639) {
  node_data nd;
  nd.set_tag("first");
  EXPECT_EQ(nd.tag(), "first");
  nd.set_tag("second");
  EXPECT_EQ(nd.tag(), "second");
}

// Test set_scalar overwrite
TEST_F(NodeDataTest_639, SetScalarOverwrite_639) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("original");
  EXPECT_EQ(nd.scalar(), "original");
  nd.set_scalar("updated");
  EXPECT_EQ(nd.scalar(), "updated");
}

// Test mark with null mark
TEST_F(NodeDataTest_639, MarkDefaultIsNullMark_639) {
  node_data nd;
  const Mark& m = nd.mark();
  EXPECT_EQ(m.line, -1);
  EXPECT_EQ(m.column, -1);
  EXPECT_EQ(m.pos, -1);
}

// Test set_type same type is no-op
TEST_F(NodeDataTest_639, SetTypeSameType_639) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("value");
  nd.set_type(NodeType::Scalar);
  // Setting same type should be a no-op, preserving scalar
  EXPECT_EQ(nd.type(), NodeType::Scalar);
  EXPECT_EQ(nd.scalar(), "value");
}

// Test insert into map
TEST_F(NodeDataTest_639, InsertIntoMap_639) {
  node_data nd;
  nd.set_type(NodeType::Map);
  
  node& key = m_pMemory->create_node();
  key.set_data(new node_data());
  key.data().set_type(NodeType::Scalar);
  key.data().set_scalar("key1");
  
  node& value = m_pMemory->create_node();
  value.set_data(new node_data());
  value.data().set_type(NodeType::Scalar);
  value.data().set_scalar("value1");
  
  nd.insert(key, value, m_pMemory);
  EXPECT_EQ(nd.size(), 1u);
}

// Test size for map with multiple entries
TEST_F(NodeDataTest_639, MapSizeMultipleEntries_639) {
  node_data nd;
  nd.set_type(NodeType::Map);
  
  node& k1 = m_pMemory->create_node();
  k1.set_data(new node_data());
  k1.data().set_type(NodeType::Scalar);
  k1.data().set_scalar("k1");
  
  node& v1 = m_pMemory->create_node();
  v1.set_data(new node_data());
  v1.data().set_type(NodeType::Scalar);
  v1.data().set_scalar("v1");
  
  nd.insert(k1, v1, m_pMemory);
  
  node& k2 = m_pMemory->create_node();
  k2.set_data(new node_data());
  k2.data().set_type(NodeType::Scalar);
  k2.data().set_scalar("k2");
  
  node& v2 = m_pMemory->create_node();
  v2.set_data(new node_data());
  v2.data().set_type(NodeType::Scalar);
  v2.data().set_scalar("v2");
  
  nd.insert(k2, v2, m_pMemory);
  EXPECT_EQ(nd.size(), 2u);
}

// Test through the public YAML::Node API for a more integration-style test
TEST_F(NodeDataTest_639, HighLevelNodeScalar_639) {
  YAML::Node node;
  node = "hello";
  EXPECT_EQ(node.as<std::string>(), "hello");
  EXPECT_TRUE(node.IsScalar());
}

TEST_F(NodeDataTest_639, HighLevelNodeSequence_639) {
  YAML::Node node;
  node.push_back("a");
  node.push_back("b");
  EXPECT_TRUE(node.IsSequence());
  EXPECT_EQ(node.size(), 2u);
}

TEST_F(NodeDataTest_639, HighLevelNodeMap_639) {
  YAML::Node node;
  node["key"] = "value";
  EXPECT_TRUE(node.IsMap());
  EXPECT_EQ(node["key"].as<std::string>(), "value");
}

TEST_F(NodeDataTest_639, HighLevelNodeNull_639) {
  YAML::Node node;
  EXPECT_TRUE(node.IsNull());
}

TEST_F(NodeDataTest_639, HighLevelNodeTag_639) {
  YAML::Node node;
  node = "value";
  node.SetTag("!!custom");
  EXPECT_EQ(node.Tag(), "!!custom");
}

TEST_F(NodeDataTest_639, HighLevelNodeStyle_639) {
  YAML::Node node;
  node.push_back(1);
  node.push_back(2);
  node.SetStyle(EmitterStyle::Flow);
  EXPECT_EQ(node.Style(), EmitterStyle::Flow);
}

TEST_F(NodeDataTest_639, HighLevelNodeRemoveFromMap_639) {
  YAML::Node node;
  node["a"] = 1;
  node["b"] = 2;
  EXPECT_EQ(node.size(), 2u);
  node.remove("a");
  EXPECT_EQ(node.size(), 1u);
}

TEST_F(NodeDataTest_639, HighLevelNodeMarkDefined_639) {
  YAML::Node node;
  EXPECT_TRUE(node.IsDefined());  // Default-constructed nodes are defined
}

}  // namespace detail
}  // namespace YAML
