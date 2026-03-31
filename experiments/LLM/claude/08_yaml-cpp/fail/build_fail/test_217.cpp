#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeRefTest_217 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = std::make_shared<memory_holder>();
  }

  shared_memory_holder pMemory;
};

// Test default construction - node_ref should start as undefined and Null type
TEST_F(NodeRefTest_217, DefaultConstruction_IsNotDefined_217) {
  node_ref ref;
  EXPECT_FALSE(ref.is_defined());
}

TEST_F(NodeRefTest_217, DefaultConstruction_TypeIsNull_217) {
  node_ref ref;
  EXPECT_EQ(NodeType::Null, ref.type());
}

TEST_F(NodeRefTest_217, DefaultConstruction_ScalarIsEmpty_217) {
  node_ref ref;
  EXPECT_TRUE(ref.scalar().empty());
}

TEST_F(NodeRefTest_217, DefaultConstruction_TagIsEmpty_217) {
  node_ref ref;
  EXPECT_TRUE(ref.tag().empty());
}

// Test mark_defined
TEST_F(NodeRefTest_217, MarkDefined_MakesNodeDefined_217) {
  node_ref ref;
  EXPECT_FALSE(ref.is_defined());
  ref.mark_defined();
  EXPECT_TRUE(ref.is_defined());
}

// Test set_type
TEST_F(NodeRefTest_217, SetType_Scalar_217) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, ref.type());
}

TEST_F(NodeRefTest_217, SetType_Sequence_217) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, ref.type());
}

TEST_F(NodeRefTest_217, SetType_Map_217) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, ref.type());
}

TEST_F(NodeRefTest_217, SetType_Null_217) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, ref.type());
  ref.set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, ref.type());
}

TEST_F(NodeRefTest_217, SetType_Undefined_217) {
  node_ref ref;
  ref.set_type(NodeType::Undefined);
  EXPECT_EQ(NodeType::Undefined, ref.type());
}

// Test set_scalar
TEST_F(NodeRefTest_217, SetScalar_BasicString_217) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("hello");
  EXPECT_EQ("hello", ref.scalar());
}

TEST_F(NodeRefTest_217, SetScalar_EmptyString_217) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("");
  EXPECT_EQ("", ref.scalar());
}

TEST_F(NodeRefTest_217, SetScalar_OverwritePreviousValue_217) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("first");
  EXPECT_EQ("first", ref.scalar());
  ref.set_scalar("second");
  EXPECT_EQ("second", ref.scalar());
}

// Test set_tag
TEST_F(NodeRefTest_217, SetTag_BasicTag_217) {
  node_ref ref;
  ref.set_tag("!mytag");
  EXPECT_EQ("!mytag", ref.tag());
}

TEST_F(NodeRefTest_217, SetTag_EmptyTag_217) {
  node_ref ref;
  ref.set_tag("");
  EXPECT_EQ("", ref.tag());
}

// Test set_null
TEST_F(NodeRefTest_217, SetNull_ResetsToNull_217) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("test");
  ref.set_null();
  EXPECT_EQ(NodeType::Null, ref.type());
}

// Test set_mark
TEST_F(NodeRefTest_217, SetMark_StoresMark_217) {
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

// Test set_style
TEST_F(NodeRefTest_217, SetStyle_Block_217) {
  node_ref ref;
  ref.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, ref.style());
}

TEST_F(NodeRefTest_217, SetStyle_Flow_217) {
  node_ref ref;
  ref.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, ref.style());
}

TEST_F(NodeRefTest_217, SetStyle_Default_217) {
  node_ref ref;
  ref.set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, ref.style());
}

// Test size for empty node
TEST_F(NodeRefTest_217, Size_EmptyNode_ReturnsZero_217) {
  node_ref ref;
  EXPECT_EQ(0u, ref.size());
}

// Test size for sequence
TEST_F(NodeRefTest_217, Size_SequenceWithElements_217) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  
  node n1;
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("val1");
  
  node n2;
  n2.set_type(NodeType::Scalar);
  n2.set_scalar("val2");
  
  ref.push_back(n1, pMemory);
  ref.push_back(n2, pMemory);
  
  EXPECT_EQ(2u, ref.size());
}

// Test push_back for sequence
TEST_F(NodeRefTest_217, PushBack_AddsToSequence_217) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("item");
  
  ref.push_back(n, pMemory);
  EXPECT_EQ(1u, ref.size());
}

// Test begin/end for empty sequence
TEST_F(NodeRefTest_217, BeginEnd_EmptySequence_217) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  EXPECT_EQ(ref.begin(), ref.end());
}

// Test set_data copies data from another node_ref
TEST_F(NodeRefTest_217, SetData_CopiesFromOther_217) {
  node_ref ref1;
  ref1.set_type(NodeType::Scalar);
  ref1.set_scalar("copied");
  ref1.set_tag("!tag");
  ref1.mark_defined();
  
  node_ref ref2;
  ref2.set_data(ref1);
  
  EXPECT_EQ(NodeType::Scalar, ref2.type());
  EXPECT_EQ("copied", ref2.scalar());
  EXPECT_EQ("!tag", ref2.tag());
  EXPECT_TRUE(ref2.is_defined());
}

// Test insert for map
TEST_F(NodeRefTest_217, Insert_MapKeyValue_217) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  
  node key;
  key.set_type(NodeType::Scalar);
  key.set_scalar("key1");
  
  node value;
  value.set_type(NodeType::Scalar);
  value.set_scalar("value1");
  
  ref.insert(key, value, pMemory);
  EXPECT_EQ(1u, ref.size());
}

// Test get with string key on map
TEST_F(NodeRefTest_217, Get_ExistingStringKey_ReturnsNonNull_217) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  
  node key;
  key.set_type(NodeType::Scalar);
  key.set_scalar("mykey");
  
  node value;
  value.set_type(NodeType::Scalar);
  value.set_scalar("myvalue");
  
  ref.insert(key, value, pMemory);
  
  const node* result = ref.get(std::string("mykey"), pMemory);
  EXPECT_NE(nullptr, result);
}

// Test get with non-existing key returns null
TEST_F(NodeRefTest_217, Get_NonExistingKey_ReturnsNull_217) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  
  const node* result = ref.get(std::string("nonexistent"), pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test remove with existing key
TEST_F(NodeRefTest_217, Remove_ExistingKey_ReturnsTrue_217) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  
  node key;
  key.set_type(NodeType::Scalar);
  key.set_scalar("removekey");
  
  node value;
  value.set_type(NodeType::Scalar);
  value.set_scalar("removeval");
  
  ref.insert(key, value, pMemory);
  EXPECT_EQ(1u, ref.size());
  
  bool removed = ref.remove(std::string("removekey"), pMemory);
  EXPECT_TRUE(removed);
}

// Test remove with non-existing key
TEST_F(NodeRefTest_217, Remove_NonExistingKey_ReturnsFalse_217) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  
  bool removed = ref.remove(std::string("nokey"), pMemory);
  EXPECT_FALSE(removed);
}

// Test get with node key
TEST_F(NodeRefTest_217, GetByNode_ExistingKey_ReturnsNonNull_217) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  
  node key;
  key.set_type(NodeType::Scalar);
  key.set_scalar("nodekey");
  
  node value;
  value.set_type(NodeType::Scalar);
  value.set_scalar("nodeval");
  
  ref.insert(key, value, pMemory);
  
  const node* result = ref.get(key, pMemory);
  EXPECT_NE(nullptr, result);
}

// Test remove with node key
TEST_F(NodeRefTest_217, RemoveByNode_ExistingKey_ReturnsTrue_217) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  
  node key;
  key.set_type(NodeType::Scalar);
  key.set_scalar("noderemkey");
  
  node value;
  value.set_type(NodeType::Scalar);
  value.set_scalar("noderemval");
  
  ref.insert(key, value, pMemory);
  
  bool removed = ref.remove(key, pMemory);
  EXPECT_TRUE(removed);
}

// Test force_insert
TEST_F(NodeRefTest_217, ForceInsert_AddsToMap_217) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  
  ref.force_insert(std::string("forcekey"), std::string("forceval"), pMemory);
  EXPECT_EQ(1u, ref.size());
}

// Test multiple operations combined
TEST_F(NodeRefTest_217, CombinedOperations_MarkDefinedThenSetScalar_217) {
  node_ref ref;
  ref.mark_defined();
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("combined");
  ref.set_tag("!combined_tag");
  ref.set_style(EmitterStyle::Flow);
  
  EXPECT_TRUE(ref.is_defined());
  EXPECT_EQ(NodeType::Scalar, ref.type());
  EXPECT_EQ("combined", ref.scalar());
  EXPECT_EQ("!combined_tag", ref.tag());
  EXPECT_EQ(EmitterStyle::Flow, ref.style());
}

// Test changing type resets content
TEST_F(NodeRefTest_217, SetType_ChangingType_ResetsContent_217) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("data");
  EXPECT_EQ("data", ref.scalar());
  
  ref.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, ref.type());
  EXPECT_EQ(0u, ref.size());
}

// Test default mark is null mark
TEST_F(NodeRefTest_217, DefaultMark_IsNullMark_217) {
  node_ref ref;
  const Mark& m = ref.mark();
  EXPECT_EQ(Mark::null_mark().line, m.line);
  EXPECT_EQ(Mark::null_mark().column, m.column);
  EXPECT_EQ(Mark::null_mark().pos, m.pos);
}

// Test size for map
TEST_F(NodeRefTest_217, Size_MapWithMultipleEntries_217) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  
  for (int i = 0; i < 5; i++) {
    node key;
    key.set_type(NodeType::Scalar);
    key.set_scalar("key" + std::to_string(i));
    
    node value;
    value.set_type(NodeType::Scalar);
    value.set_scalar("val" + std::to_string(i));
    
    ref.insert(key, value, pMemory);
  }
  
  EXPECT_EQ(5u, ref.size());
}

// Test that set_data shares data
TEST_F(NodeRefTest_217, SetData_SharedDataReflectsChanges_217) {
  node_ref ref1;
  ref1.set_type(NodeType::Scalar);
  ref1.set_scalar("original");
  ref1.mark_defined();
  
  node_ref ref2;
  ref2.set_data(ref1);
  
  // Both should see the same data
  EXPECT_EQ(ref1.scalar(), ref2.scalar());
  EXPECT_EQ(ref1.type(), ref2.type());
}

}  // namespace detail
}  // namespace YAML
