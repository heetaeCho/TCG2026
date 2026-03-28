#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node_data.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeDataTest_647 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = std::make_shared<memory_holder>();
    memory = pMemory->create_memory();
  }

  std::shared_ptr<memory_holder> pMemory;
  shared_memory_holder memory;
};

// Test default construction state
TEST_F(NodeDataTest_647, DefaultConstruction_IsNotDefined_647) {
  node_data nd;
  EXPECT_FALSE(nd.is_defined());
}

TEST_F(NodeDataTest_647, DefaultConstruction_TypeIsNull_647) {
  node_data nd;
  EXPECT_EQ(NodeType::Null, nd.type());
}

TEST_F(NodeDataTest_647, DefaultConstruction_ScalarIsEmpty_647) {
  node_data nd;
  EXPECT_TRUE(nd.scalar().empty());
}

TEST_F(NodeDataTest_647, DefaultConstruction_TagIsEmpty_647) {
  node_data nd;
  EXPECT_TRUE(nd.tag().empty());
}

// Test size() when not defined
TEST_F(NodeDataTest_647, SizeWhenNotDefined_ReturnsZero_647) {
  node_data nd;
  EXPECT_EQ(0u, nd.size());
}

// Test size() for Null type
TEST_F(NodeDataTest_647, SizeForNullType_ReturnsZero_647) {
  node_data nd;
  nd.mark_defined();
  EXPECT_EQ(0u, nd.size());
}

// Test size() for Scalar type
TEST_F(NodeDataTest_647, SizeForScalarType_ReturnsZero_647) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("hello");
  EXPECT_EQ(0u, nd.size());
}

// Test mark_defined
TEST_F(NodeDataTest_647, MarkDefined_SetsIsDefined_647) {
  node_data nd;
  EXPECT_FALSE(nd.is_defined());
  nd.mark_defined();
  EXPECT_TRUE(nd.is_defined());
}

// Test set_type
TEST_F(NodeDataTest_647, SetTypeSequence_ChangesType_647) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, nd.type());
}

TEST_F(NodeDataTest_647, SetTypeMap_ChangesType_647) {
  node_data nd;
  nd.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, nd.type());
}

TEST_F(NodeDataTest_647, SetTypeScalar_ChangesType_647) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, nd.type());
}

TEST_F(NodeDataTest_647, SetTypeNull_ChangesType_647) {
  node_data nd;
  nd.set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, nd.type());
}

// Test set_tag
TEST_F(NodeDataTest_647, SetTag_ReturnsCorrectTag_647) {
  node_data nd;
  nd.set_tag("my_tag");
  EXPECT_EQ("my_tag", nd.tag());
}

TEST_F(NodeDataTest_647, SetTag_EmptyTag_647) {
  node_data nd;
  nd.set_tag("");
  EXPECT_TRUE(nd.tag().empty());
}

// Test set_scalar
TEST_F(NodeDataTest_647, SetScalar_ReturnsCorrectScalar_647) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("test_value");
  EXPECT_EQ("test_value", nd.scalar());
}

TEST_F(NodeDataTest_647, SetScalar_EmptyScalar_647) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("");
  EXPECT_TRUE(nd.scalar().empty());
}

// Test set_null
TEST_F(NodeDataTest_647, SetNull_SetsTypeToNull_647) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("something");
  nd.set_null();
  EXPECT_EQ(NodeType::Null, nd.type());
}

// Test set_mark
TEST_F(NodeDataTest_647, SetMark_ReturnsCorrectMark_647) {
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

// Test set_style
TEST_F(NodeDataTest_647, SetStyle_Flow_647) {
  node_data nd;
  nd.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, nd.style());
}

TEST_F(NodeDataTest_647, SetStyle_Block_647) {
  node_data nd;
  nd.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, nd.style());
}

TEST_F(NodeDataTest_647, SetStyle_Default_647) {
  node_data nd;
  nd.set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, nd.style());
}

// Test empty_scalar
TEST_F(NodeDataTest_647, EmptyScalar_ReturnsEmptyString_647) {
  const std::string& empty = node_data::empty_scalar();
  EXPECT_TRUE(empty.empty());
}

// Test sequence operations
TEST_F(NodeDataTest_647, SequenceSize_AfterPushBack_647) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Sequence);

  node& n1 = memory->create_node();
  n1.set_data(new node_data());
  n1.data().mark_defined();
  n1.data().set_type(NodeType::Scalar);
  n1.data().set_scalar("item1");

  nd.push_back(n1, memory);
  EXPECT_EQ(1u, nd.size());
}

TEST_F(NodeDataTest_647, SequenceSize_AfterMultiplePushBacks_647) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Sequence);

  node& n1 = memory->create_node();
  n1.set_data(new node_data());
  n1.data().mark_defined();
  n1.data().set_type(NodeType::Scalar);

  node& n2 = memory->create_node();
  n2.set_data(new node_data());
  n2.data().mark_defined();
  n2.data().set_type(NodeType::Scalar);

  nd.push_back(n1, memory);
  nd.push_back(n2, memory);
  EXPECT_EQ(2u, nd.size());
}

// Test sequence size when not defined returns 0
TEST_F(NodeDataTest_647, SequenceSize_NotDefined_ReturnsZero_647) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  // Not calling mark_defined
  EXPECT_EQ(0u, nd.size());
}

// Test map size when not defined returns 0
TEST_F(NodeDataTest_647, MapSize_NotDefined_ReturnsZero_647) {
  node_data nd;
  nd.set_type(NodeType::Map);
  // Not calling mark_defined
  EXPECT_EQ(0u, nd.size());
}

// Test empty sequence size
TEST_F(NodeDataTest_647, EmptySequence_SizeIsZero_647) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Sequence);
  EXPECT_EQ(0u, nd.size());
}

// Test empty map size
TEST_F(NodeDataTest_647, EmptyMap_SizeIsZero_647) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);
  EXPECT_EQ(0u, nd.size());
}

// Test changing type resets content
TEST_F(NodeDataTest_647, ChangeTypeFromSequenceToMap_647) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Sequence);

  node& n1 = memory->create_node();
  n1.set_data(new node_data());
  n1.data().mark_defined();
  n1.data().set_type(NodeType::Scalar);

  nd.push_back(n1, memory);
  EXPECT_EQ(1u, nd.size());

  nd.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, nd.type());
}

// Test type transition from Scalar to Sequence
TEST_F(NodeDataTest_647, ChangeTypeFromScalarToSequence_647) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("hello");
  EXPECT_EQ("hello", nd.scalar());

  nd.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, nd.type());
  EXPECT_EQ(0u, nd.size());
}

// Test set_type to same type
TEST_F(NodeDataTest_647, SetTypeSameType_NoChange_647) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("value");
  nd.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, nd.type());
}

// Integration-like test: using YAML::Node high-level API to verify node_data behavior indirectly
TEST_F(NodeDataTest_647, HighLevelNode_SequenceSize_647) {
  YAML::Node node;
  node.push_back("a");
  node.push_back("b");
  node.push_back("c");
  EXPECT_EQ(3u, node.size());
}

TEST_F(NodeDataTest_647, HighLevelNode_MapSize_647) {
  YAML::Node node;
  node["key1"] = "val1";
  node["key2"] = "val2";
  EXPECT_EQ(2u, node.size());
}

TEST_F(NodeDataTest_647, HighLevelNode_NullSize_647) {
  YAML::Node node;
  EXPECT_EQ(0u, node.size());
}

TEST_F(NodeDataTest_647, HighLevelNode_ScalarSize_647) {
  YAML::Node node("scalar_value");
  EXPECT_EQ(0u, node.size());
}

TEST_F(NodeDataTest_647, HighLevelNode_UndefinedSize_647) {
  YAML::Node node;
  // Accessing non-existing key creates undefined node
  YAML::Node child = node["nonexistent"];
  // The parent should now be a map
  // The child node is undefined
  EXPECT_FALSE(child.IsDefined());
}

TEST_F(NodeDataTest_647, HighLevelNode_EmptySequenceSize_647) {
  YAML::Node node(NodeType::Sequence);
  EXPECT_EQ(0u, node.size());
}

TEST_F(NodeDataTest_647, HighLevelNode_EmptyMapSize_647) {
  YAML::Node node(NodeType::Map);
  EXPECT_EQ(0u, node.size());
}

TEST_F(NodeDataTest_647, HighLevelNode_RemoveFromMap_647) {
  YAML::Node node;
  node["a"] = 1;
  node["b"] = 2;
  node["c"] = 3;
  EXPECT_EQ(3u, node.size());
  node.remove("b");
  EXPECT_EQ(2u, node.size());
}

TEST_F(NodeDataTest_647, HighLevelNode_RemoveFromSequence_647) {
  YAML::Node node;
  node.push_back(10);
  node.push_back(20);
  node.push_back(30);
  EXPECT_EQ(3u, node.size());
  node.remove(1);
  EXPECT_EQ(2u, node.size());
}

TEST_F(NodeDataTest_647, HighLevelNode_Tag_647) {
  YAML::Node node;
  node.SetTag("!mytag");
  EXPECT_EQ("!mytag", node.Tag());
}

TEST_F(NodeDataTest_647, HighLevelNode_Style_647) {
  YAML::Node node;
  node.SetStyle(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, node.Style());
}

// Test map operations via insert
TEST_F(NodeDataTest_647, MapInsert_IncreasesSize_647) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);

  node& key = memory->create_node();
  key.set_data(new node_data());
  key.data().mark_defined();
  key.data().set_type(NodeType::Scalar);
  key.data().set_scalar("key1");

  node& val = memory->create_node();
  val.set_data(new node_data());
  val.data().mark_defined();
  val.data().set_type(NodeType::Scalar);
  val.data().set_scalar("val1");

  nd.insert(key, val, memory);
  EXPECT_EQ(1u, nd.size());
}

}  // namespace detail
}  // namespace YAML
