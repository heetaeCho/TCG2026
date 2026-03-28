#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeTest_250 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = create_shared_memory();
  }

  shared_memory_holder pMemory;
};

// Test default construction: node should not be defined initially
TEST_F(NodeTest_250, DefaultConstruction_IsNotDefined_250) {
  node n;
  EXPECT_FALSE(n.is_defined());
}

// Test default type is Undefined
TEST_F(NodeTest_250, DefaultConstruction_TypeIsUndefined_250) {
  node n;
  EXPECT_EQ(NodeType::Undefined, n.type());
}

// Test set_null marks node as defined and sets type to Null
TEST_F(NodeTest_250, SetNull_MarksDefined_250) {
  node n;
  n.set_null();
  EXPECT_TRUE(n.is_defined());
  EXPECT_EQ(NodeType::Null, n.type());
}

// Test mark_defined makes is_defined return true
TEST_F(NodeTest_250, MarkDefined_IsDefinedReturnsTrue_250) {
  node n;
  EXPECT_FALSE(n.is_defined());
  n.mark_defined();
  EXPECT_TRUE(n.is_defined());
}

// Test set_scalar sets the scalar value and type
TEST_F(NodeTest_250, SetScalar_SetsScalarValue_250) {
  node n;
  n.set_scalar("hello");
  EXPECT_TRUE(n.is_defined());
  EXPECT_EQ(NodeType::Scalar, n.type());
  EXPECT_EQ("hello", n.scalar());
}

// Test set_scalar with empty string
TEST_F(NodeTest_250, SetScalar_EmptyString_250) {
  node n;
  n.set_scalar("");
  EXPECT_TRUE(n.is_defined());
  EXPECT_EQ(NodeType::Scalar, n.type());
  EXPECT_EQ("", n.scalar());
}

// Test set_type to Sequence
TEST_F(NodeTest_250, SetType_Sequence_250) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
  EXPECT_TRUE(n.is_defined());
}

// Test set_type to Map
TEST_F(NodeTest_250, SetType_Map_250) {
  node n;
  n.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, n.type());
  EXPECT_TRUE(n.is_defined());
}

// Test set_type to Null
TEST_F(NodeTest_250, SetType_Null_250) {
  node n;
  n.set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, n.type());
}

// Test set_tag and tag retrieval
TEST_F(NodeTest_250, SetTag_RetrievesCorrectTag_250) {
  node n;
  n.set_tag("!mytag");
  EXPECT_EQ("!mytag", n.tag());
}

// Test set_tag with empty string
TEST_F(NodeTest_250, SetTag_EmptyTag_250) {
  node n;
  n.set_tag("");
  EXPECT_EQ("", n.tag());
}

// Test set_style
TEST_F(NodeTest_250, SetStyle_Block_250) {
  node n;
  n.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, n.style());
}

TEST_F(NodeTest_250, SetStyle_Flow_250) {
  node n;
  n.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, n.style());
}

TEST_F(NodeTest_250, SetStyle_Default_250) {
  node n;
  n.set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, n.style());
}

// Test is() - same node
TEST_F(NodeTest_250, Is_SameNode_ReturnsTrue_250) {
  node n;
  EXPECT_TRUE(n.is(n));
}

// Test is() - different nodes
TEST_F(NodeTest_250, Is_DifferentNodes_ReturnsFalse_250) {
  node n1;
  node n2;
  EXPECT_FALSE(n1.is(n2));
}

// Test ref() returns non-null
TEST_F(NodeTest_250, Ref_ReturnsNonNull_250) {
  node n;
  EXPECT_NE(nullptr, n.ref());
}

// Test set_mark and mark retrieval
TEST_F(NodeTest_250, SetMark_RetrievesMark_250) {
  node n;
  Mark m;
  m.pos = 10;
  m.line = 5;
  m.column = 3;
  n.set_mark(m);
  const Mark& retrieved = n.mark();
  EXPECT_EQ(5, retrieved.line);
  EXPECT_EQ(3, retrieved.column);
  EXPECT_EQ(10, retrieved.pos);
}

// Test size of empty sequence
TEST_F(NodeTest_250, Size_EmptySequence_250) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(0u, n.size());
}

// Test push_back increases size
TEST_F(NodeTest_250, PushBack_IncreasesSize_250) {
  node n;
  n.set_type(NodeType::Sequence);
  
  node& child = pMemory->create_node();
  child.set_scalar("item1");
  n.push_back(child, pMemory);
  
  EXPECT_EQ(1u, n.size());
}

// Test push_back multiple items
TEST_F(NodeTest_250, PushBack_MultipleItems_250) {
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

// Test begin/end on empty sequence
TEST_F(NodeTest_250, BeginEnd_EmptySequence_250) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(n.begin(), n.end());
}

// Test size of empty map
TEST_F(NodeTest_250, Size_EmptyMap_250) {
  node n;
  n.set_type(NodeType::Map);
  EXPECT_EQ(0u, n.size());
}

// Test insert into map
TEST_F(NodeTest_250, Insert_IntoMap_IncreasesSize_250) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("key1");
  node& value = pMemory->create_node();
  value.set_scalar("value1");
  
  n.insert(key, value, pMemory);
  EXPECT_EQ(1u, n.size());
}

// Test get on map with string key
TEST_F(NodeTest_250, Get_ExistingKey_ReturnsNode_250) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("mykey");
  node& value = pMemory->create_node();
  value.set_scalar("myvalue");
  
  n.insert(key, value, pMemory);
  
  node* result = n.get(std::string("mykey"), pMemory);
  EXPECT_NE(nullptr, result);
  EXPECT_EQ("myvalue", result->scalar());
}

// Test get on map with nonexistent key
TEST_F(NodeTest_250, Get_NonexistentKey_ReturnsNull_250) {
  node n;
  n.set_type(NodeType::Map);
  
  node* result = n.get(std::string("nokey"), pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test remove from map
TEST_F(NodeTest_250, Remove_ExistingKey_ReturnsTrue_250) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("removekey");
  node& value = pMemory->create_node();
  value.set_scalar("val");
  
  n.insert(key, value, pMemory);
  EXPECT_EQ(1u, n.size());
  
  bool removed = n.remove(std::string("removekey"), pMemory);
  EXPECT_TRUE(removed);
}

// Test remove nonexistent key
TEST_F(NodeTest_250, Remove_NonexistentKey_ReturnsFalse_250) {
  node n;
  n.set_type(NodeType::Map);
  
  bool removed = n.remove(std::string("nokey"), pMemory);
  EXPECT_FALSE(removed);
}

// Test set_data copies data from another node
TEST_F(NodeTest_250, SetData_CopiesFromOtherNode_250) {
  node n1;
  n1.set_scalar("copied");
  n1.set_tag("!tag");
  
  node n2;
  n2.set_data(n1);
  
  EXPECT_TRUE(n2.is_defined());
  EXPECT_EQ("copied", n2.scalar());
  EXPECT_EQ("!tag", n2.tag());
}

// Test set_ref makes two nodes share same ref
TEST_F(NodeTest_250, SetRef_SharesRef_250) {
  node n1;
  n1.set_scalar("shared");
  
  node n2;
  n2.set_ref(n1);
  
  EXPECT_EQ("shared", n2.scalar());
  EXPECT_EQ(n1.ref(), n2.ref());
}

// Test equals with matching scalar
TEST_F(NodeTest_250, Equals_MatchingScalar_ReturnsTrue_250) {
  node n;
  n.set_scalar("test");
  
  EXPECT_TRUE(n.equals(std::string("test"), pMemory));
}

// Test equals with non-matching scalar
TEST_F(NodeTest_250, Equals_NonMatchingScalar_ReturnsFalse_250) {
  node n;
  n.set_scalar("test");
  
  EXPECT_FALSE(n.equals(std::string("other"), pMemory));
}

// Test equals with const char*
TEST_F(NodeTest_250, Equals_ConstCharPtr_Matching_250) {
  node n;
  n.set_scalar("hello");
  
  EXPECT_TRUE(n.equals("hello", pMemory));
}

// Test equals with const char* non-matching
TEST_F(NodeTest_250, Equals_ConstCharPtr_NonMatching_250) {
  node n;
  n.set_scalar("hello");
  
  EXPECT_FALSE(n.equals("world", pMemory));
}

// Test changing type from Scalar to Sequence
TEST_F(NodeTest_250, SetType_ChangeFromScalarToSequence_250) {
  node n;
  n.set_scalar("value");
  EXPECT_EQ(NodeType::Scalar, n.type());
  
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
}

// Test force_insert
TEST_F(NodeTest_250, ForceInsert_IntoMap_250) {
  node n;
  n.set_type(NodeType::Map);
  
  n.force_insert(std::string("key"), std::string("value"), pMemory);
  EXPECT_EQ(1u, n.size());
}

// Test get with node key
TEST_F(NodeTest_250, Get_WithNodeKey_250) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("nodekey");
  node& value = pMemory->create_node();
  value.set_scalar("nodeval");
  
  n.insert(key, value, pMemory);
  
  node* result = n.get(key, pMemory);
  EXPECT_NE(nullptr, result);
  EXPECT_EQ("nodeval", result->scalar());
}

// Test remove with node key
TEST_F(NodeTest_250, Remove_WithNodeKey_250) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("rkey");
  node& value = pMemory->create_node();
  value.set_scalar("rval");
  
  n.insert(key, value, pMemory);
  
  bool removed = n.remove(key, pMemory);
  EXPECT_TRUE(removed);
}

// Test add_dependency doesn't change observable state but doesn't crash
TEST_F(NodeTest_250, AddDependency_DoesNotCrash_250) {
  node n1;
  node n2;
  n1.add_dependency(n2);
  // Just checking it doesn't crash; no observable state change through public interface
  EXPECT_TRUE(true);
}

// Test overwriting scalar
TEST_F(NodeTest_250, SetScalar_Overwrite_250) {
  node n;
  n.set_scalar("first");
  EXPECT_EQ("first", n.scalar());
  
  n.set_scalar("second");
  EXPECT_EQ("second", n.scalar());
}

// Test set_null after scalar
TEST_F(NodeTest_250, SetNull_AfterScalar_250) {
  node n;
  n.set_scalar("value");
  EXPECT_EQ(NodeType::Scalar, n.type());
  
  n.set_null();
  EXPECT_EQ(NodeType::Null, n.type());
}

// Test default mark values
TEST_F(NodeTest_250, DefaultMark_250) {
  node n;
  const Mark& m = n.mark();
  EXPECT_EQ(0, m.line);
  EXPECT_EQ(0, m.column);
  EXPECT_EQ(0, m.pos);
}

// Test begin/end iteration on sequence with elements
TEST_F(NodeTest_250, BeginEnd_SequenceWithElements_250) {
  node n;
  n.set_type(NodeType::Sequence);
  
  node& child = pMemory->create_node();
  child.set_scalar("elem");
  n.push_back(child, pMemory);
  
  EXPECT_NE(n.begin(), n.end());
}

}  // namespace detail
}  // namespace YAML
