#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeTest_255 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory.reset(new Memory);
  }

  shared_memory_holder pMemory;
};

// Test default construction - node should not be defined initially
TEST_F(NodeTest_255, DefaultConstruction_IsNotDefined_255) {
  node n;
  EXPECT_FALSE(n.is_defined());
}

// Test default construction - type should be Undefined
TEST_F(NodeTest_255, DefaultConstruction_TypeIsUndefined_255) {
  node n;
  EXPECT_EQ(NodeType::Undefined, n.type());
}

// Test mark_defined makes node defined
TEST_F(NodeTest_255, MarkDefined_MakesNodeDefined_255) {
  node n;
  n.mark_defined();
  EXPECT_TRUE(n.is_defined());
}

// Test set_type to Null
TEST_F(NodeTest_255, SetType_Null_255) {
  node n;
  n.set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, n.type());
}

// Test set_type to Scalar
TEST_F(NodeTest_255, SetType_Scalar_255) {
  node n;
  n.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, n.type());
}

// Test set_type to Sequence
TEST_F(NodeTest_255, SetType_Sequence_255) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
}

// Test set_type to Map
TEST_F(NodeTest_255, SetType_Map_255) {
  node n;
  n.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, n.type());
}

// Test set_null sets type to Null
TEST_F(NodeTest_255, SetNull_SetsTypeToNull_255) {
  node n;
  n.set_null();
  EXPECT_EQ(NodeType::Null, n.type());
}

// Test set_scalar and retrieve scalar
TEST_F(NodeTest_255, SetScalar_RetrieveScalar_255) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");
  EXPECT_EQ("hello", n.scalar());
}

// Test set_scalar with empty string
TEST_F(NodeTest_255, SetScalar_EmptyString_255) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("");
  EXPECT_EQ("", n.scalar());
}

// Test set_tag and retrieve tag
TEST_F(NodeTest_255, SetTag_RetrieveTag_255) {
  node n;
  n.set_tag("!mytag");
  EXPECT_EQ("!mytag", n.tag());
}

// Test set_tag with empty string
TEST_F(NodeTest_255, SetTag_EmptyString_255) {
  node n;
  n.set_tag("");
  EXPECT_EQ("", n.tag());
}

// Test set_style and retrieve style
TEST_F(NodeTest_255, SetStyle_Block_255) {
  node n;
  n.set_type(NodeType::Sequence);
  n.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, n.style());
}

TEST_F(NodeTest_255, SetStyle_Flow_255) {
  node n;
  n.set_type(NodeType::Sequence);
  n.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, n.style());
}

TEST_F(NodeTest_255, SetStyle_Default_255) {
  node n;
  n.set_type(NodeType::Sequence);
  n.set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, n.style());
}

// Test is() - same node
TEST_F(NodeTest_255, Is_SameNode_ReturnsTrue_255) {
  node n;
  EXPECT_TRUE(n.is(n));
}

// Test is() - different nodes
TEST_F(NodeTest_255, Is_DifferentNode_ReturnsFalse_255) {
  node n1;
  node n2;
  EXPECT_FALSE(n1.is(n2));
}

// Test ref() returns non-null
TEST_F(NodeTest_255, Ref_ReturnsNonNull_255) {
  node n;
  EXPECT_NE(nullptr, n.ref());
}

// Test size of empty sequence
TEST_F(NodeTest_255, Size_EmptySequence_255) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(0u, n.size());
}

// Test push_back increases size
TEST_F(NodeTest_255, PushBack_IncreasesSize_255) {
  node n;
  n.set_type(NodeType::Sequence);
  
  node child;
  child.set_type(NodeType::Scalar);
  child.set_scalar("value1");
  
  n.push_back(child, pMemory);
  EXPECT_EQ(1u, n.size());
}

// Test push_back multiple elements
TEST_F(NodeTest_255, PushBack_MultipleElements_255) {
  node n;
  n.set_type(NodeType::Sequence);
  
  node child1;
  child1.set_type(NodeType::Scalar);
  child1.set_scalar("value1");
  
  node child2;
  child2.set_type(NodeType::Scalar);
  child2.set_scalar("value2");
  
  n.push_back(child1, pMemory);
  n.push_back(child2, pMemory);
  EXPECT_EQ(2u, n.size());
}

// Test begin and end on empty sequence
TEST_F(NodeTest_255, BeginEndEmptySequence_255) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(n.begin(), n.end());
}

// Test begin != end after push_back
TEST_F(NodeTest_255, BeginEnd_AfterPushBack_NotEqual_255) {
  node n;
  n.set_type(NodeType::Sequence);
  
  node child;
  child.set_type(NodeType::Scalar);
  child.set_scalar("value");
  
  n.push_back(child, pMemory);
  EXPECT_NE(n.begin(), n.end());
}

// Test insert into map
TEST_F(NodeTest_255, Insert_IntoMap_IncreasesSize_255) {
  node n;
  n.set_type(NodeType::Map);
  
  node key;
  key.set_type(NodeType::Scalar);
  key.set_scalar("key1");
  
  node value;
  value.set_type(NodeType::Scalar);
  value.set_scalar("value1");
  
  n.insert(key, value, pMemory);
  EXPECT_EQ(1u, n.size());
}

// Test get on map
TEST_F(NodeTest_255, Get_ExistingKey_ReturnsNonNull_255) {
  node n;
  n.set_type(NodeType::Map);
  
  node key;
  key.set_type(NodeType::Scalar);
  key.set_scalar("mykey");
  
  node value;
  value.set_type(NodeType::Scalar);
  value.set_scalar("myvalue");
  
  n.insert(key, value, pMemory);
  
  node* result = n.get(std::string("mykey"), pMemory);
  EXPECT_NE(nullptr, result);
}

// Test get on map with non-existing key
TEST_F(NodeTest_255, Get_NonExistingKey_ReturnsNull_255) {
  node n;
  n.set_type(NodeType::Map);
  
  node* result = n.get(std::string("nonexistent"), pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test remove from map
TEST_F(NodeTest_255, Remove_ExistingKey_ReturnsTrue_255) {
  node n;
  n.set_type(NodeType::Map);
  
  node key;
  key.set_type(NodeType::Scalar);
  key.set_scalar("mykey");
  
  node value;
  value.set_type(NodeType::Scalar);
  value.set_scalar("myvalue");
  
  n.insert(key, value, pMemory);
  
  bool removed = n.remove(std::string("mykey"), pMemory);
  EXPECT_TRUE(removed);
}

// Test remove non-existing key
TEST_F(NodeTest_255, Remove_NonExistingKey_ReturnsFalse_255) {
  node n;
  n.set_type(NodeType::Map);
  
  bool removed = n.remove(std::string("nonexistent"), pMemory);
  EXPECT_FALSE(removed);
}

// Test remove by node reference
TEST_F(NodeTest_255, Remove_ByNodeRef_ExistingKey_ReturnsTrue_255) {
  node n;
  n.set_type(NodeType::Map);
  
  node key;
  key.set_type(NodeType::Scalar);
  key.set_scalar("mykey");
  
  node value;
  value.set_type(NodeType::Scalar);
  value.set_scalar("myvalue");
  
  n.insert(key, value, pMemory);
  
  bool removed = n.remove(key, pMemory);
  EXPECT_TRUE(removed);
}

// Test set_data copies data from another node
TEST_F(NodeTest_255, SetData_CopiesFromAnotherNode_255) {
  node n1;
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("copied");
  
  node n2;
  n2.set_data(n1);
  
  EXPECT_EQ(NodeType::Scalar, n2.type());
  EXPECT_EQ("copied", n2.scalar());
}

// Test set_ref shares ref with another node
TEST_F(NodeTest_255, SetRef_SharesRefWithAnotherNode_255) {
  node n1;
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("shared");
  
  node n2;
  n2.set_ref(n1);
  
  EXPECT_EQ(NodeType::Scalar, n2.type());
  EXPECT_EQ("shared", n2.scalar());
}

// Test set_mark
TEST_F(NodeTest_255, SetMark_RetrieveMark_255) {
  node n;
  Mark m;
  m.line = 10;
  m.column = 20;
  m.pos = 30;
  n.set_mark(m);
  
  const Mark& retrieved = n.mark();
  EXPECT_EQ(10, retrieved.line);
  EXPECT_EQ(20, retrieved.column);
  EXPECT_EQ(30, retrieved.pos);
}

// Test equals with matching scalar
TEST_F(NodeTest_255, Equals_MatchingScalar_ReturnsTrue_255) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("test");
  
  EXPECT_TRUE(n.equals(std::string("test"), pMemory));
}

// Test equals with non-matching scalar
TEST_F(NodeTest_255, Equals_NonMatchingScalar_ReturnsFalse_255) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("test");
  
  EXPECT_FALSE(n.equals(std::string("other"), pMemory));
}

// Test equals with const char*
TEST_F(NodeTest_255, Equals_ConstCharPtr_Matching_255) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");
  
  EXPECT_TRUE(n.equals("hello", pMemory));
}

// Test equals with const char* non-matching
TEST_F(NodeTest_255, Equals_ConstCharPtr_NonMatching_255) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");
  
  EXPECT_FALSE(n.equals("world", pMemory));
}

// Test force_insert into map
TEST_F(NodeTest_255, ForceInsert_IntoMap_255) {
  node n;
  n.set_type(NodeType::Map);
  
  n.force_insert(std::string("key1"), std::string("val1"), pMemory);
  EXPECT_EQ(1u, n.size());
  
  // Force insert same key - should still add (force)
  n.force_insert(std::string("key1"), std::string("val2"), pMemory);
  EXPECT_EQ(2u, n.size());
}

// Test add_dependency does not change node behavior
TEST_F(NodeTest_255, AddDependency_DoesNotChangeType_255) {
  node n1;
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("independent");
  
  node n2;
  n2.set_type(NodeType::Scalar);
  n2.set_scalar("dependent");
  
  n2.add_dependency(n1);
  
  // Adding dependency shouldn't change the node's own properties
  EXPECT_EQ(NodeType::Scalar, n2.type());
  EXPECT_EQ("dependent", n2.scalar());
}

// Test size of empty map
TEST_F(NodeTest_255, Size_EmptyMap_255) {
  node n;
  n.set_type(NodeType::Map);
  EXPECT_EQ(0u, n.size());
}

// Test begin/end on map
TEST_F(NodeTest_255, BeginEnd_EmptyMap_255) {
  node n;
  n.set_type(NodeType::Map);
  EXPECT_EQ(n.begin(), n.end());
}

// Test begin/end on map with elements
TEST_F(NodeTest_255, BeginEnd_MapWithElements_255) {
  node n;
  n.set_type(NodeType::Map);
  
  node key;
  key.set_type(NodeType::Scalar);
  key.set_scalar("k");
  
  node value;
  value.set_type(NodeType::Scalar);
  value.set_scalar("v");
  
  n.insert(key, value, pMemory);
  EXPECT_NE(n.begin(), n.end());
}

// Test get by node reference
TEST_F(NodeTest_255, Get_ByNodeRef_ExistingKey_255) {
  node n;
  n.set_type(NodeType::Map);
  
  node key;
  key.set_type(NodeType::Scalar);
  key.set_scalar("mykey");
  
  node value;
  value.set_type(NodeType::Scalar);
  value.set_scalar("myvalue");
  
  n.insert(key, value, pMemory);
  
  node* result = n.get(key, pMemory);
  EXPECT_NE(nullptr, result);
}

// Test get by node reference - non-existing
TEST_F(NodeTest_255, Get_ByNodeRef_NonExistingKey_255) {
  node n;
  n.set_type(NodeType::Map);
  
  node key;
  key.set_type(NodeType::Scalar);
  key.set_scalar("nonexistent");
  
  node* result = n.get(key, pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test changing type clears previous data behavior
TEST_F(NodeTest_255, ChangeType_FromScalarToSequence_255) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");
  
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
  EXPECT_EQ(0u, n.size());
}

// Test set_scalar with special characters
TEST_F(NodeTest_255, SetScalar_SpecialCharacters_255) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello\nworld\t!");
  EXPECT_EQ("hello\nworld\t!", n.scalar());
}

// Test set_scalar with very long string
TEST_F(NodeTest_255, SetScalar_LongString_255) {
  node n;
  n.set_type(NodeType::Scalar);
  std::string longStr(10000, 'x');
  n.set_scalar(longStr);
  EXPECT_EQ(longStr, n.scalar());
}

}  // namespace detail
}  // namespace YAML
