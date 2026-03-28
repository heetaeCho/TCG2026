#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeTest_238 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = create_shared_memory();
  }

  shared_memory_holder pMemory;
};

// Test that a newly created node is not defined
TEST_F(NodeTest_238, NewNodeIsNotDefined_238) {
  node n;
  EXPECT_FALSE(n.is_defined());
}

// Test that mark_defined makes the node defined
TEST_F(NodeTest_238, MarkDefinedMakesNodeDefined_238) {
  node n;
  n.mark_defined();
  EXPECT_TRUE(n.is_defined());
}

// Test that a new node has Undefined type
TEST_F(NodeTest_238, NewNodeTypeIsUndefined_238) {
  node n;
  EXPECT_EQ(NodeType::Undefined, n.type());
}

// Test setting type to Null
TEST_F(NodeTest_238, SetTypeNull_238) {
  node n;
  n.set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, n.type());
  EXPECT_TRUE(n.is_defined());
}

// Test setting type to Scalar
TEST_F(NodeTest_238, SetTypeScalar_238) {
  node n;
  n.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, n.type());
}

// Test setting type to Sequence
TEST_F(NodeTest_238, SetTypeSequence_238) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
}

// Test setting type to Map
TEST_F(NodeTest_238, SetTypeMap_238) {
  node n;
  n.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, n.type());
}

// Test set_null
TEST_F(NodeTest_238, SetNull_238) {
  node n;
  n.set_null();
  EXPECT_EQ(NodeType::Null, n.type());
}

// Test setting and getting scalar
TEST_F(NodeTest_238, SetAndGetScalar_238) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");
  EXPECT_EQ("hello", n.scalar());
}

// Test setting scalar to empty string
TEST_F(NodeTest_238, SetScalarEmpty_238) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("");
  EXPECT_EQ("", n.scalar());
}

// Test setting and getting tag
TEST_F(NodeTest_238, SetAndGetTag_238) {
  node n;
  n.set_tag("!mytag");
  EXPECT_EQ("!mytag", n.tag());
}

// Test setting tag to empty string
TEST_F(NodeTest_238, SetTagEmpty_238) {
  node n;
  n.set_tag("");
  EXPECT_EQ("", n.tag());
}

// Test setting and getting style
TEST_F(NodeTest_238, SetAndGetStyle_238) {
  node n;
  n.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, n.style());
}

// Test setting style to Block
TEST_F(NodeTest_238, SetStyleBlock_238) {
  node n;
  n.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, n.style());
}

// Test is() method - same node
TEST_F(NodeTest_238, IsSameNode_238) {
  node n;
  EXPECT_TRUE(n.is(n));
}

// Test is() method - different nodes
TEST_F(NodeTest_238, IsDifferentNode_238) {
  node n1;
  node n2;
  EXPECT_FALSE(n1.is(n2));
}

// Test ref() returns non-null
TEST_F(NodeTest_238, RefIsNotNull_238) {
  node n;
  EXPECT_NE(nullptr, n.ref());
}

// Test set_mark and mark
TEST_F(NodeTest_238, SetAndGetMark_238) {
  node n;
  Mark m;
  m.line = 5;
  m.column = 10;
  n.set_mark(m);
  EXPECT_EQ(5, n.mark().line);
  EXPECT_EQ(10, n.mark().column);
}

// Test size of new node (should be 0 for sequence/map)
TEST_F(NodeTest_238, SizeOfNewSequenceIsZero_238) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(0u, n.size());
}

// Test push_back on sequence
TEST_F(NodeTest_238, PushBackIncreasesSize_238) {
  node n;
  n.set_type(NodeType::Sequence);
  
  node& child = pMemory->create_node();
  child.set_type(NodeType::Scalar);
  child.set_scalar("value1");
  
  n.push_back(child, pMemory);
  EXPECT_EQ(1u, n.size());
}

// Test push_back multiple items
TEST_F(NodeTest_238, PushBackMultipleItems_238) {
  node n;
  n.set_type(NodeType::Sequence);
  
  node& child1 = pMemory->create_node();
  child1.set_type(NodeType::Scalar);
  child1.set_scalar("value1");
  
  node& child2 = pMemory->create_node();
  child2.set_type(NodeType::Scalar);
  child2.set_scalar("value2");
  
  n.push_back(child1, pMemory);
  n.push_back(child2, pMemory);
  EXPECT_EQ(2u, n.size());
}

// Test begin/end on empty sequence
TEST_F(NodeTest_238, BeginEqualsEndForEmptySequence_238) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_TRUE(n.begin() == n.end());
}

// Test insert on map
TEST_F(NodeTest_238, InsertIntoMap_238) {
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

// Test get on map with string key
TEST_F(NodeTest_238, GetFromMap_238) {
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

// Test get with non-existent key returns null
TEST_F(NodeTest_238, GetNonExistentKeyReturnsNull_238) {
  node n;
  n.set_type(NodeType::Map);
  
  node* result = n.get(std::string("nonexistent"), pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test remove from map
TEST_F(NodeTest_238, RemoveFromMap_238) {
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
TEST_F(NodeTest_238, RemoveNonExistentKey_238) {
  node n;
  n.set_type(NodeType::Map);
  
  bool removed = n.remove(std::string("nokey"), pMemory);
  EXPECT_FALSE(removed);
}

// Test set_data copies data from another node
TEST_F(NodeTest_238, SetDataCopiesFromOtherNode_238) {
  node n1;
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("copied");
  n1.set_tag("!tag");
  
  node n2;
  n2.set_data(n1);
  
  EXPECT_EQ("copied", n2.scalar());
  EXPECT_EQ("!tag", n2.tag());
  EXPECT_EQ(NodeType::Scalar, n2.type());
}

// Test set_ref makes nodes share reference
TEST_F(NodeTest_238, SetRefSharesReference_238) {
  node n1;
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("shared");
  
  node n2;
  n2.set_ref(n1);
  
  EXPECT_EQ("shared", n2.scalar());
  EXPECT_EQ(n1.ref(), n2.ref());
}

// Test equals with matching scalar
TEST_F(NodeTest_238, EqualsMatchingScalar_238) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("test");
  
  EXPECT_TRUE(n.equals(std::string("test"), pMemory));
}

// Test equals with non-matching scalar
TEST_F(NodeTest_238, EqualsNonMatchingScalar_238) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("test");
  
  EXPECT_FALSE(n.equals(std::string("other"), pMemory));
}

// Test equals with const char*
TEST_F(NodeTest_238, EqualsConstCharPtr_238) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");
  
  EXPECT_TRUE(n.equals("hello", pMemory));
  EXPECT_FALSE(n.equals("world", pMemory));
}

// Test size of empty map
TEST_F(NodeTest_238, SizeOfEmptyMapIsZero_238) {
  node n;
  n.set_type(NodeType::Map);
  EXPECT_EQ(0u, n.size());
}

// Test force_insert on map
TEST_F(NodeTest_238, ForceInsertIntoMap_238) {
  node n;
  n.set_type(NodeType::Map);
  
  n.force_insert(std::string("key"), std::string("value"), pMemory);
  EXPECT_EQ(1u, n.size());
}

// Test add_dependency doesn't change type
TEST_F(NodeTest_238, AddDependencyDoesNotChangeType_238) {
  node n1;
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("original");
  
  node n2;
  n2.set_type(NodeType::Scalar);
  
  n1.add_dependency(n2);
  EXPECT_EQ(NodeType::Scalar, n1.type());
  EXPECT_EQ("original", n1.scalar());
}

// Test get with node key
TEST_F(NodeTest_238, GetWithNodeKey_238) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_type(NodeType::Scalar);
  key.set_scalar("nodekey");
  
  node& value = pMemory->create_node();
  value.set_type(NodeType::Scalar);
  value.set_scalar("nodevalue");
  
  n.insert(key, value, pMemory);
  
  node* result = n.get(key, pMemory);
  EXPECT_NE(nullptr, result);
  EXPECT_EQ("nodevalue", result->scalar());
}

// Test remove with node key
TEST_F(NodeTest_238, RemoveWithNodeKey_238) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_type(NodeType::Scalar);
  key.set_scalar("removekey");
  
  node& value = pMemory->create_node();
  value.set_type(NodeType::Scalar);
  value.set_scalar("removevalue");
  
  n.insert(key, value, pMemory);
  
  bool removed = n.remove(key, pMemory);
  EXPECT_TRUE(removed);
}

// Test changing type from Scalar to Sequence
TEST_F(NodeTest_238, ChangeTypeScalarToSequence_238) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");
  
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
  EXPECT_EQ(0u, n.size());
}

// Test default style
TEST_F(NodeTest_238, DefaultStyle_238) {
  node n;
  EXPECT_EQ(EmitterStyle::Default, n.style());
}

// Test default mark values
TEST_F(NodeTest_238, DefaultMarkValues_238) {
  node n;
  const Mark& m = n.mark();
  EXPECT_EQ(0, m.line);
  EXPECT_EQ(0, m.column);
}

}  // namespace detail
}  // namespace YAML
