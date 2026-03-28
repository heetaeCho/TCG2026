#include "gtest/gtest.h"
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeTest_249 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory.reset(new Memory);
  }

  shared_memory_holder pMemory;
};

// Test default construction - node should be undefined initially
TEST_F(NodeTest_249, DefaultConstruction_IsUndefined_249) {
  node n;
  EXPECT_FALSE(n.is_defined());
}

// Test default construction - type should be Undefined
TEST_F(NodeTest_249, DefaultConstruction_TypeIsUndefined_249) {
  node n;
  EXPECT_EQ(NodeType::Undefined, n.type());
}

// Test set_type to Null
TEST_F(NodeTest_249, SetType_Null_249) {
  node n;
  n.set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, n.type());
  EXPECT_TRUE(n.is_defined());
}

// Test set_type to Scalar
TEST_F(NodeTest_249, SetType_Scalar_249) {
  node n;
  n.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, n.type());
  EXPECT_TRUE(n.is_defined());
}

// Test set_type to Sequence
TEST_F(NodeTest_249, SetType_Sequence_249) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
  EXPECT_TRUE(n.is_defined());
}

// Test set_type to Map
TEST_F(NodeTest_249, SetType_Map_249) {
  node n;
  n.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, n.type());
  EXPECT_TRUE(n.is_defined());
}

// Test set_type to Undefined does not mark as defined
TEST_F(NodeTest_249, SetType_Undefined_DoesNotMarkDefined_249) {
  node n;
  n.set_type(NodeType::Undefined);
  EXPECT_FALSE(n.is_defined());
}

// Test mark_defined
TEST_F(NodeTest_249, MarkDefined_249) {
  node n;
  EXPECT_FALSE(n.is_defined());
  n.mark_defined();
  EXPECT_TRUE(n.is_defined());
}

// Test set_scalar
TEST_F(NodeTest_249, SetScalar_249) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");
  EXPECT_EQ("hello", n.scalar());
}

// Test set_scalar with empty string
TEST_F(NodeTest_249, SetScalar_EmptyString_249) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("");
  EXPECT_EQ("", n.scalar());
}

// Test set_tag
TEST_F(NodeTest_249, SetTag_249) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_tag("!mytag");
  EXPECT_EQ("!mytag", n.tag());
}

// Test set_tag with empty string
TEST_F(NodeTest_249, SetTag_EmptyString_249) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_tag("");
  EXPECT_EQ("", n.tag());
}

// Test set_style
TEST_F(NodeTest_249, SetStyle_Flow_249) {
  node n;
  n.set_type(NodeType::Sequence);
  n.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, n.style());
}

// Test set_style Block
TEST_F(NodeTest_249, SetStyle_Block_249) {
  node n;
  n.set_type(NodeType::Sequence);
  n.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, n.style());
}

// Test set_style Default
TEST_F(NodeTest_249, SetStyle_Default_249) {
  node n;
  n.set_type(NodeType::Sequence);
  n.set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, n.style());
}

// Test set_null
TEST_F(NodeTest_249, SetNull_249) {
  node n;
  n.set_null();
  EXPECT_EQ(NodeType::Null, n.type());
}

// Test is() - same node
TEST_F(NodeTest_249, Is_SameNode_249) {
  node n;
  EXPECT_TRUE(n.is(n));
}

// Test is() - different nodes
TEST_F(NodeTest_249, Is_DifferentNodes_249) {
  node n1;
  node n2;
  EXPECT_FALSE(n1.is(n2));
}

// Test ref() returns non-null
TEST_F(NodeTest_249, Ref_NonNull_249) {
  node n;
  EXPECT_NE(nullptr, n.ref());
}

// Test set_mark
TEST_F(NodeTest_249, SetMark_249) {
  node n;
  Mark m;
  m.line = 5;
  m.column = 10;
  m.pos = 42;
  n.set_mark(m);
  EXPECT_EQ(5, n.mark().line);
  EXPECT_EQ(10, n.mark().column);
  EXPECT_EQ(42, n.mark().pos);
}

// Test sequence push_back and size
TEST_F(NodeTest_249, Sequence_PushBack_249) {
  node n;
  n.set_type(NodeType::Sequence);
  
  node& child = pMemory->create_node();
  child.set_type(NodeType::Scalar);
  child.set_scalar("item1");
  
  n.push_back(child, pMemory);
  EXPECT_EQ(1u, n.size());
}

// Test sequence multiple push_back
TEST_F(NodeTest_249, Sequence_MultiplePushBack_249) {
  node n;
  n.set_type(NodeType::Sequence);
  
  node& child1 = pMemory->create_node();
  child1.set_type(NodeType::Scalar);
  child1.set_scalar("item1");
  
  node& child2 = pMemory->create_node();
  child2.set_type(NodeType::Scalar);
  child2.set_scalar("item2");
  
  n.push_back(child1, pMemory);
  n.push_back(child2, pMemory);
  EXPECT_EQ(2u, n.size());
}

// Test empty sequence size
TEST_F(NodeTest_249, Sequence_EmptySize_249) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(0u, n.size());
}

// Test map insert and size
TEST_F(NodeTest_249, Map_Insert_249) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_type(NodeType::Scalar);
  key.set_scalar("key1");
  
  node& value = pMemory->create_node();
  value.set_type(NodeType::Scalar);
  value.set_scalar("value1");
  
  n.insert(key, value, pMemory);
  EXPECT_EQ(1u, n.size());
}

// Test empty map size
TEST_F(NodeTest_249, Map_EmptySize_249) {
  node n;
  n.set_type(NodeType::Map);
  EXPECT_EQ(0u, n.size());
}

// Test set_data copies type from another node
TEST_F(NodeTest_249, SetData_CopiesType_249) {
  node n1;
  node n2;
  n2.set_type(NodeType::Scalar);
  n2.set_scalar("copied");
  
  n1.set_data(n2);
  EXPECT_EQ(NodeType::Scalar, n1.type());
  EXPECT_EQ("copied", n1.scalar());
}

// Test set_ref makes nodes share the same ref
TEST_F(NodeTest_249, SetRef_SharesRef_249) {
  node n1;
  node n2;
  n2.set_type(NodeType::Scalar);
  n2.set_scalar("shared");
  
  n1.set_ref(n2);
  EXPECT_EQ(NodeType::Scalar, n1.type());
  EXPECT_EQ("shared", n1.scalar());
}

// Test changing type from Scalar to Sequence
TEST_F(NodeTest_249, SetType_ChangeScalarToSequence_249) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");
  EXPECT_EQ(NodeType::Scalar, n.type());
  
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
}

// Test changing type from Sequence to Map
TEST_F(NodeTest_249, SetType_ChangeSequenceToMap_249) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
  
  n.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, n.type());
}

// Test set_type to non-Undefined marks defined, then setting Undefined does not unmark
TEST_F(NodeTest_249, SetType_NonUndefinedThenUndefined_StaysDefined_249) {
  node n;
  n.set_type(NodeType::Scalar);
  EXPECT_TRUE(n.is_defined());
  
  // Setting to Undefined type - mark_defined is NOT called but the type changes
  // The node should still be "defined" since mark_defined was called previously
  n.set_type(NodeType::Undefined);
  EXPECT_TRUE(n.is_defined());
}

// Test equals with string scalar
TEST_F(NodeTest_249, Equals_StringScalar_249) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("test");
  
  EXPECT_TRUE(n.equals(std::string("test"), pMemory));
  EXPECT_FALSE(n.equals(std::string("other"), pMemory));
}

// Test equals with const char*
TEST_F(NodeTest_249, Equals_ConstCharPtr_249) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("test");
  
  EXPECT_TRUE(n.equals("test", pMemory));
  EXPECT_FALSE(n.equals("other", pMemory));
}

// Test begin/end for empty sequence
TEST_F(NodeTest_249, Sequence_BeginEndEmpty_249) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(n.begin(), n.end());
}

// Test get on map
TEST_F(NodeTest_249, Map_Get_249) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_type(NodeType::Scalar);
  key.set_scalar("mykey");
  
  node& value = pMemory->create_node();
  value.set_type(NodeType::Scalar);
  value.set_scalar("myvalue");
  
  n.insert(key, value, pMemory);
  
  node* result = n.get(std::string("mykey"), pMemory);
  EXPECT_NE(nullptr, result);
  EXPECT_EQ("myvalue", result->scalar());
}

// Test get on map returns null for non-existent key
TEST_F(NodeTest_249, Map_Get_NonExistent_249) {
  node n;
  n.set_type(NodeType::Map);
  
  node* result = n.get(std::string("nonexistent"), pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test remove on map
TEST_F(NodeTest_249, Map_Remove_249) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_type(NodeType::Scalar);
  key.set_scalar("removekey");
  
  node& value = pMemory->create_node();
  value.set_type(NodeType::Scalar);
  value.set_scalar("removevalue");
  
  n.insert(key, value, pMemory);
  EXPECT_EQ(1u, n.size());
  
  bool removed = n.remove(std::string("removekey"), pMemory);
  EXPECT_TRUE(removed);
}

// Test remove non-existent key
TEST_F(NodeTest_249, Map_Remove_NonExistent_249) {
  node n;
  n.set_type(NodeType::Map);
  
  bool removed = n.remove(std::string("nonexistent"), pMemory);
  EXPECT_FALSE(removed);
}

// Test add_dependency does not affect node identity
TEST_F(NodeTest_249, AddDependency_DoesNotAffectIdentity_249) {
  node n1;
  node n2;
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("node1");
  
  n1.add_dependency(n2);
  
  // Node should still be the same
  EXPECT_TRUE(n1.is(n1));
  EXPECT_FALSE(n1.is(n2));
  EXPECT_EQ("node1", n1.scalar());
}

// Test force_insert on map
TEST_F(NodeTest_249, Map_ForceInsert_249) {
  node n;
  n.set_type(NodeType::Map);
  
  n.force_insert(std::string("forcekey"), std::string("forcevalue"), pMemory);
  EXPECT_EQ(1u, n.size());
}

// Test multiple type changes
TEST_F(NodeTest_249, MultipleTypeChanges_249) {
  node n;
  n.set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, n.type());
  
  n.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, n.type());
  
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
  
  n.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, n.type());
}

// Test set_scalar with special characters
TEST_F(NodeTest_249, SetScalar_SpecialCharacters_249) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello\nworld\ttab");
  EXPECT_EQ("hello\nworld\ttab", n.scalar());
}

// Test set_scalar with very long string
TEST_F(NodeTest_249, SetScalar_LongString_249) {
  node n;
  n.set_type(NodeType::Scalar);
  std::string longStr(10000, 'x');
  n.set_scalar(longStr);
  EXPECT_EQ(longStr, n.scalar());
}

}  // namespace detail
}  // namespace YAML
