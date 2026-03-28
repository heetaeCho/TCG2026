#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/node_data.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"
#include "yaml-cpp/node/type.h"
#include "yaml-cpp/emitterstyle.h"
#include "yaml-cpp/mark.h"

namespace YAML {
namespace detail {

class NodeRefTest_227 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = std::make_shared<memory_holder>();
    ref = std::unique_ptr<node_ref>(new node_ref());
  }

  std::unique_ptr<node_ref> ref;
  shared_memory_holder pMemory;

  node& create_node() {
    return pMemory->create_node();
  }
};

// Test default construction state
TEST_F(NodeRefTest_227, DefaultConstruction_IsNotDefined_227) {
  EXPECT_FALSE(ref->is_defined());
}

TEST_F(NodeRefTest_227, DefaultConstruction_TypeIsNull_227) {
  EXPECT_EQ(NodeType::Null, ref->type());
}

TEST_F(NodeRefTest_227, DefaultConstruction_ScalarIsEmpty_227) {
  EXPECT_TRUE(ref->scalar().empty());
}

TEST_F(NodeRefTest_227, DefaultConstruction_TagIsEmpty_227) {
  EXPECT_TRUE(ref->tag().empty());
}

// Test mark_defined
TEST_F(NodeRefTest_227, MarkDefined_MakesNodeDefined_227) {
  ref->mark_defined();
  EXPECT_TRUE(ref->is_defined());
}

// Test set_type
TEST_F(NodeRefTest_227, SetType_Sequence_227) {
  ref->set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, ref->type());
}

TEST_F(NodeRefTest_227, SetType_Map_227) {
  ref->set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, ref->type());
}

TEST_F(NodeRefTest_227, SetType_Scalar_227) {
  ref->set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, ref->type());
}

TEST_F(NodeRefTest_227, SetType_Null_227) {
  ref->set_type(NodeType::Scalar);
  ref->set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, ref->type());
}

TEST_F(NodeRefTest_227, SetType_Undefined_227) {
  ref->set_type(NodeType::Undefined);
  EXPECT_EQ(NodeType::Undefined, ref->type());
}

// Test set_tag
TEST_F(NodeRefTest_227, SetTag_ReturnsCorrectTag_227) {
  ref->set_tag("!!str");
  EXPECT_EQ("!!str", ref->tag());
}

TEST_F(NodeRefTest_227, SetTag_EmptyTag_227) {
  ref->set_tag("");
  EXPECT_EQ("", ref->tag());
}

TEST_F(NodeRefTest_227, SetTag_OverwritesTag_227) {
  ref->set_tag("first");
  ref->set_tag("second");
  EXPECT_EQ("second", ref->tag());
}

// Test set_null
TEST_F(NodeRefTest_227, SetNull_TypeIsNull_227) {
  ref->set_type(NodeType::Scalar);
  ref->set_null();
  EXPECT_EQ(NodeType::Null, ref->type());
}

// Test set_scalar
TEST_F(NodeRefTest_227, SetScalar_ReturnsCorrectValue_227) {
  ref->set_scalar("hello");
  EXPECT_EQ("hello", ref->scalar());
}

TEST_F(NodeRefTest_227, SetScalar_EmptyString_227) {
  ref->set_scalar("");
  EXPECT_EQ("", ref->scalar());
}

TEST_F(NodeRefTest_227, SetScalar_OverwritesScalar_227) {
  ref->set_scalar("first");
  ref->set_scalar("second");
  EXPECT_EQ("second", ref->scalar());
}

// Test set_style
TEST_F(NodeRefTest_227, SetStyle_Block_227) {
  ref->set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, ref->style());
}

TEST_F(NodeRefTest_227, SetStyle_Flow_227) {
  ref->set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, ref->style());
}

TEST_F(NodeRefTest_227, SetStyle_Default_227) {
  ref->set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, ref->style());
}

// Test set_mark
TEST_F(NodeRefTest_227, SetMark_ReturnsCorrectMark_227) {
  Mark mark;
  mark.pos = 10;
  mark.line = 5;
  mark.column = 3;
  ref->set_mark(mark);
  EXPECT_EQ(5, ref->mark().line);
  EXPECT_EQ(3, ref->mark().column);
}

// Test size for default (null) node
TEST_F(NodeRefTest_227, Size_DefaultIsZero_227) {
  EXPECT_EQ(0u, ref->size());
}

// Test begin/end for default node
TEST_F(NodeRefTest_227, BeginEqualsEnd_DefaultNode_227) {
  EXPECT_TRUE(ref->begin() == ref->end());
}

// Test sequence operations
TEST_F(NodeRefTest_227, PushBack_IncreasesSize_227) {
  ref->set_type(NodeType::Sequence);
  node& n = create_node();
  ref->push_back(n, pMemory);
  EXPECT_EQ(1u, ref->size());
}

TEST_F(NodeRefTest_227, PushBack_MultiplePushesIncreaseSize_227) {
  ref->set_type(NodeType::Sequence);
  node& n1 = create_node();
  node& n2 = create_node();
  node& n3 = create_node();
  ref->push_back(n1, pMemory);
  ref->push_back(n2, pMemory);
  ref->push_back(n3, pMemory);
  EXPECT_EQ(3u, ref->size());
}

TEST_F(NodeRefTest_227, Sequence_BeginNotEqualsEnd_AfterPush_227) {
  ref->set_type(NodeType::Sequence);
  node& n = create_node();
  ref->push_back(n, pMemory);
  EXPECT_FALSE(ref->begin() == ref->end());
}

// Test map operations
TEST_F(NodeRefTest_227, Insert_IncreasesSize_227) {
  ref->set_type(NodeType::Map);
  node& key = create_node();
  node& value = create_node();
  ref->insert(key, value, pMemory);
  EXPECT_EQ(1u, ref->size());
}

TEST_F(NodeRefTest_227, Map_BeginNotEqualsEnd_AfterInsert_227) {
  ref->set_type(NodeType::Map);
  node& key = create_node();
  node& value = create_node();
  ref->insert(key, value, pMemory);
  EXPECT_FALSE(ref->begin() == ref->end());
}

// Test set_data copies data from another node_ref
TEST_F(NodeRefTest_227, SetData_CopiesScalar_227) {
  node_ref other;
  other.set_scalar("copied");
  other.set_tag("!!tag");
  other.mark_defined();
  
  ref->set_data(other);
  EXPECT_EQ("copied", ref->scalar());
  EXPECT_EQ("!!tag", ref->tag());
}

TEST_F(NodeRefTest_227, SetData_CopiesType_227) {
  node_ref other;
  other.set_type(NodeType::Sequence);
  other.mark_defined();
  
  ref->set_data(other);
  EXPECT_EQ(NodeType::Sequence, ref->type());
}

// Test get with node key on map
TEST_F(NodeRefTest_227, Get_NodeKey_ReturnsNullForMissing_227) {
  ref->set_type(NodeType::Map);
  node& key = create_node();
  key.set_scalar("nonexistent");
  node* result = ref->get(key, pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test remove on empty map
TEST_F(NodeRefTest_227, Remove_NodeKey_ReturnsFalseForEmpty_227) {
  ref->set_type(NodeType::Map);
  node& key = create_node();
  key.set_scalar("nonexistent");
  EXPECT_FALSE(ref->remove(key, pMemory));
}

// Test force_insert
TEST_F(NodeRefTest_227, ForceInsert_IncreasesSize_227) {
  ref->set_type(NodeType::Map);
  ref->force_insert("key1", "value1", pMemory);
  EXPECT_EQ(1u, ref->size());
}

TEST_F(NodeRefTest_227, ForceInsert_MultipleEntries_227) {
  ref->set_type(NodeType::Map);
  ref->force_insert("key1", "value1", pMemory);
  ref->force_insert("key2", "value2", pMemory);
  EXPECT_EQ(2u, ref->size());
}

// Test template get with string key
TEST_F(NodeRefTest_227, GetTemplate_ReturnsNullForMissing_227) {
  ref->set_type(NodeType::Map);
  node* result = ref->get(std::string("missing"), pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test template remove with string key
TEST_F(NodeRefTest_227, RemoveTemplate_ReturnsFalseForMissing_227) {
  ref->set_type(NodeType::Map);
  EXPECT_FALSE(ref->remove(std::string("missing"), pMemory));
}

// Test switching type resets content
TEST_F(NodeRefTest_227, SetType_SwitchFromSequenceToMap_ResetsSize_227) {
  ref->set_type(NodeType::Sequence);
  node& n = create_node();
  ref->push_back(n, pMemory);
  EXPECT_EQ(1u, ref->size());
  
  ref->set_type(NodeType::Map);
  EXPECT_EQ(0u, ref->size());
}

TEST_F(NodeRefTest_227, SetType_SwitchFromMapToSequence_ResetsSize_227) {
  ref->set_type(NodeType::Map);
  node& key = create_node();
  node& value = create_node();
  ref->insert(key, value, pMemory);
  EXPECT_EQ(1u, ref->size());
  
  ref->set_type(NodeType::Sequence);
  EXPECT_EQ(0u, ref->size());
}

// Test null mark by default
TEST_F(NodeRefTest_227, DefaultMark_IsNullMark_227) {
  const Mark& m = ref->mark();
  EXPECT_EQ(Mark::null_mark().pos, m.pos);
  EXPECT_EQ(Mark::null_mark().line, m.line);
  EXPECT_EQ(Mark::null_mark().column, m.column);
}

// Test setting type to same type does not reset
TEST_F(NodeRefTest_227, SetType_SameType_DoesNotReset_227) {
  ref->set_type(NodeType::Sequence);
  node& n = create_node();
  ref->push_back(n, pMemory);
  EXPECT_EQ(1u, ref->size());
  
  ref->set_type(NodeType::Sequence);
  EXPECT_EQ(1u, ref->size());
}

// Test scalar type after set_scalar
TEST_F(NodeRefTest_227, SetScalar_SetsTypeToScalar_227) {
  ref->set_scalar("test");
  EXPECT_EQ(NodeType::Scalar, ref->type());
}

// Test large scalar string
TEST_F(NodeRefTest_227, SetScalar_LargeString_227) {
  std::string large(10000, 'x');
  ref->set_scalar(large);
  EXPECT_EQ(large, ref->scalar());
}

// Test special characters in scalar
TEST_F(NodeRefTest_227, SetScalar_SpecialCharacters_227) {
  std::string special = "hello\nworld\t\r\0test";
  ref->set_scalar(special);
  EXPECT_EQ(special, ref->scalar());
}

// Test special characters in tag
TEST_F(NodeRefTest_227, SetTag_SpecialCharacters_227) {
  ref->set_tag("tag:yaml.org,2002:str");
  EXPECT_EQ("tag:yaml.org,2002:str", ref->tag());
}

}  // namespace detail
}  // namespace YAML
