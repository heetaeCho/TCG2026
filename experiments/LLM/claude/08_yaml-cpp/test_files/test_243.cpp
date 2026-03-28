#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeTest_243 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = create_shared_memory();
  }

  shared_memory_holder pMemory;
};

// Test default construction - node should exist but be undefined
TEST_F(NodeTest_243, DefaultConstruction_IsNotDefined_243) {
  node n;
  EXPECT_FALSE(n.is_defined());
}

// Test default type is Undefined
TEST_F(NodeTest_243, DefaultConstruction_TypeIsUndefined_243) {
  node n;
  EXPECT_EQ(NodeType::Undefined, n.type());
}

// Test mark_defined makes node defined
TEST_F(NodeTest_243, MarkDefined_MakesNodeDefined_243) {
  node n;
  n.mark_defined();
  EXPECT_TRUE(n.is_defined());
}

// Test set_type to Scalar
TEST_F(NodeTest_243, SetType_Scalar_243) {
  node n;
  n.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, n.type());
}

// Test set_type to Sequence
TEST_F(NodeTest_243, SetType_Sequence_243) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
}

// Test set_type to Map
TEST_F(NodeTest_243, SetType_Map_243) {
  node n;
  n.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, n.type());
}

// Test set_type to Null
TEST_F(NodeTest_243, SetType_Null_243) {
  node n;
  n.set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, n.type());
}

// Test set_null sets type to Null
TEST_F(NodeTest_243, SetNull_TypeBecomesNull_243) {
  node n;
  n.set_scalar("hello");
  n.set_null();
  EXPECT_EQ(NodeType::Null, n.type());
}

// Test set_scalar and scalar retrieval
TEST_F(NodeTest_243, SetScalar_ReturnsCorrectValue_243) {
  node n;
  n.set_scalar("test_value");
  EXPECT_EQ("test_value", n.scalar());
}

// Test set_scalar with empty string
TEST_F(NodeTest_243, SetScalar_EmptyString_243) {
  node n;
  n.set_scalar("");
  EXPECT_EQ("", n.scalar());
}

// Test set_tag and tag retrieval
TEST_F(NodeTest_243, SetTag_ReturnsCorrectValue_243) {
  node n;
  n.set_tag("!custom_tag");
  EXPECT_EQ("!custom_tag", n.tag());
}

// Test set_tag with empty string
TEST_F(NodeTest_243, SetTag_EmptyString_243) {
  node n;
  n.set_tag("");
  EXPECT_EQ("", n.tag());
}

// Test default style
TEST_F(NodeTest_243, DefaultStyle_IsDefault_243) {
  node n;
  EXPECT_EQ(EmitterStyle::Default, n.style());
}

// Test set_style to Flow
TEST_F(NodeTest_243, SetStyle_Flow_243) {
  node n;
  n.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, n.style());
}

// Test set_style to Block
TEST_F(NodeTest_243, SetStyle_Block_243) {
  node n;
  n.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, n.style());
}

// Test set_style to Default
TEST_F(NodeTest_243, SetStyle_Default_243) {
  node n;
  n.set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, n.style());
}

// Test is() - same node
TEST_F(NodeTest_243, Is_SameNode_ReturnsTrue_243) {
  node n;
  EXPECT_TRUE(n.is(n));
}

// Test is() - different nodes
TEST_F(NodeTest_243, Is_DifferentNodes_ReturnsFalse_243) {
  node n1;
  node n2;
  EXPECT_FALSE(n1.is(n2));
}

// Test ref() returns non-null
TEST_F(NodeTest_243, Ref_ReturnsNonNull_243) {
  node n;
  EXPECT_NE(nullptr, n.ref());
}

// Test set_mark and mark retrieval
TEST_F(NodeTest_243, SetMark_ReturnsCorrectMark_243) {
  node n;
  Mark m;
  m.line = 5;
  m.column = 10;
  m.pos = 50;
  n.set_mark(m);
  EXPECT_EQ(5, n.mark().line);
  EXPECT_EQ(10, n.mark().column);
  EXPECT_EQ(50, n.mark().pos);
}

// Test size of empty sequence
TEST_F(NodeTest_243, Size_EmptySequence_ReturnsZero_243) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(0u, n.size());
}

// Test push_back increases size
TEST_F(NodeTest_243, PushBack_IncreasesSize_243) {
  node n;
  n.set_type(NodeType::Sequence);
  
  node& child = pMemory->create_node();
  child.set_scalar("item1");
  n.push_back(child, pMemory);
  
  EXPECT_EQ(1u, n.size());
}

// Test push_back multiple items
TEST_F(NodeTest_243, PushBack_MultipleItems_243) {
  node n;
  n.set_type(NodeType::Sequence);
  
  node& child1 = pMemory->create_node();
  child1.set_scalar("item1");
  n.push_back(child1, pMemory);
  
  node& child2 = pMemory->create_node();
  child2.set_scalar("item2");
  n.push_back(child2, pMemory);
  
  EXPECT_EQ(2u, n.size());
}

// Test insert into map
TEST_F(NodeTest_243, Insert_IntoMap_IncreasesSize_243) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("key1");
  node& value = pMemory->create_node();
  value.set_scalar("value1");
  
  n.insert(key, value, pMemory);
  EXPECT_EQ(1u, n.size());
}

// Test get on map
TEST_F(NodeTest_243, Get_ExistingKey_ReturnsNonNull_243) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("mykey");
  node& value = pMemory->create_node();
  value.set_scalar("myvalue");
  
  n.insert(key, value, pMemory);
  
  node* result = n.get(std::string("mykey"), pMemory);
  EXPECT_NE(nullptr, result);
}

// Test get on map with non-existing key
TEST_F(NodeTest_243, Get_NonExistingKey_ReturnsNull_243) {
  node n;
  n.set_type(NodeType::Map);
  
  node* result = n.get(std::string("nonexistent"), pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test remove from map
TEST_F(NodeTest_243, Remove_ExistingKey_ReturnsTrue_243) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("removekey");
  node& value = pMemory->create_node();
  value.set_scalar("removevalue");
  
  n.insert(key, value, pMemory);
  
  bool removed = n.remove(std::string("removekey"), pMemory);
  EXPECT_TRUE(removed);
}

// Test remove non-existing key from map
TEST_F(NodeTest_243, Remove_NonExistingKey_ReturnsFalse_243) {
  node n;
  n.set_type(NodeType::Map);
  
  bool removed = n.remove(std::string("nonexistent"), pMemory);
  EXPECT_FALSE(removed);
}

// Test remove with node key
TEST_F(NodeTest_243, Remove_WithNodeKey_ExistingKey_243) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("nodekey");
  node& value = pMemory->create_node();
  value.set_scalar("nodevalue");
  
  n.insert(key, value, pMemory);
  
  bool removed = n.remove(key, pMemory);
  EXPECT_TRUE(removed);
}

// Test begin and end on empty sequence
TEST_F(NodeTest_243, BeginEnd_EmptySequence_AreEqual_243) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(n.begin(), n.end());
}

// Test begin and end on non-empty sequence
TEST_F(NodeTest_243, BeginEnd_NonEmptySequence_AreNotEqual_243) {
  node n;
  n.set_type(NodeType::Sequence);
  
  node& child = pMemory->create_node();
  child.set_scalar("item");
  n.push_back(child, pMemory);
  
  EXPECT_NE(n.begin(), n.end());
}

// Test equals with matching scalar
TEST_F(NodeTest_243, Equals_MatchingScalar_ReturnsTrue_243) {
  node n;
  n.set_scalar("hello");
  EXPECT_TRUE(n.equals(std::string("hello"), pMemory));
}

// Test equals with non-matching scalar
TEST_F(NodeTest_243, Equals_NonMatchingScalar_ReturnsFalse_243) {
  node n;
  n.set_scalar("hello");
  EXPECT_FALSE(n.equals(std::string("world"), pMemory));
}

// Test equals with const char*
TEST_F(NodeTest_243, Equals_ConstCharPtr_Matching_243) {
  node n;
  n.set_scalar("test");
  EXPECT_TRUE(n.equals("test", pMemory));
}

// Test equals with const char* non-matching
TEST_F(NodeTest_243, Equals_ConstCharPtr_NonMatching_243) {
  node n;
  n.set_scalar("test");
  EXPECT_FALSE(n.equals("other", pMemory));
}

// Test set_data copies data from another node
TEST_F(NodeTest_243, SetData_CopiesFromOtherNode_243) {
  node n1;
  n1.set_scalar("source_data");
  n1.set_tag("!source_tag");
  n1.set_style(EmitterStyle::Flow);
  
  node n2;
  n2.set_data(n1);
  
  EXPECT_EQ("source_data", n2.scalar());
  EXPECT_EQ("!source_tag", n2.tag());
  EXPECT_EQ(EmitterStyle::Flow, n2.style());
}

// Test set_ref makes nodes share the same reference
TEST_F(NodeTest_243, SetRef_SharesReference_243) {
  node n1;
  n1.set_scalar("shared_value");
  
  node n2;
  n2.set_ref(n1);
  
  EXPECT_EQ("shared_value", n2.scalar());
}

// Test scalar type after set_scalar
TEST_F(NodeTest_243, SetScalar_TypeBecomesScalar_243) {
  node n;
  n.set_scalar("value");
  EXPECT_EQ(NodeType::Scalar, n.type());
}

// Test overwriting scalar
TEST_F(NodeTest_243, SetScalar_OverwritesPrevious_243) {
  node n;
  n.set_scalar("first");
  EXPECT_EQ("first", n.scalar());
  n.set_scalar("second");
  EXPECT_EQ("second", n.scalar());
}

// Test force_insert
TEST_F(NodeTest_243, ForceInsert_AddsToMap_243) {
  node n;
  n.set_type(NodeType::Map);
  
  n.force_insert(std::string("fkey"), std::string("fvalue"), pMemory);
  EXPECT_EQ(1u, n.size());
}

// Test size of empty map
TEST_F(NodeTest_243, Size_EmptyMap_ReturnsZero_243) {
  node n;
  n.set_type(NodeType::Map);
  EXPECT_EQ(0u, n.size());
}

// Test get with node key
TEST_F(NodeTest_243, Get_WithNodeKey_ReturnsCorrectValue_243) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("nkey");
  node& value = pMemory->create_node();
  value.set_scalar("nvalue");
  
  n.insert(key, value, pMemory);
  
  node* result = n.get(key, pMemory);
  EXPECT_NE(nullptr, result);
  EXPECT_EQ("nvalue", result->scalar());
}

// Test set_mark default
TEST_F(NodeTest_243, DefaultMark_IsZero_243) {
  node n;
  EXPECT_EQ(0, n.mark().line);
  EXPECT_EQ(0, n.mark().column);
  EXPECT_EQ(0, n.mark().pos);
}

// Test add_dependency doesn't crash
TEST_F(NodeTest_243, AddDependency_DoesNotCrash_243) {
  node n1;
  node n2;
  EXPECT_NO_THROW(n1.add_dependency(n2));
}

// Test changing type from Scalar to Map
TEST_F(NodeTest_243, ChangeType_ScalarToMap_243) {
  node n;
  n.set_scalar("value");
  EXPECT_EQ(NodeType::Scalar, n.type());
  n.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, n.type());
}

// Test changing type from Sequence to Scalar
TEST_F(NodeTest_243, ChangeType_SequenceToScalar_243) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
  n.set_scalar("now_scalar");
  EXPECT_EQ(NodeType::Scalar, n.type());
  EXPECT_EQ("now_scalar", n.scalar());
}

}  // namespace detail
}  // namespace YAML
