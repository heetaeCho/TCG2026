#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeTest_252 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = create_shared_memory();
  }

  shared_memory_holder pMemory;
};

// Test that a newly created node is not defined
TEST_F(NodeTest_252, NewNodeIsNotDefined_252) {
  node n;
  EXPECT_FALSE(n.is_defined());
}

// Test that mark_defined makes the node defined
TEST_F(NodeTest_252, MarkDefinedMakesNodeDefined_252) {
  node n;
  n.mark_defined();
  EXPECT_TRUE(n.is_defined());
}

// Test default type of a new node
TEST_F(NodeTest_252, NewNodeTypeIsUndefined_252) {
  node n;
  EXPECT_EQ(NodeType::Undefined, n.type());
}

// Test set_type and type
TEST_F(NodeTest_252, SetTypeScalar_252) {
  node n;
  n.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, n.type());
  EXPECT_TRUE(n.is_defined());
}

TEST_F(NodeTest_252, SetTypeSequence_252) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
}

TEST_F(NodeTest_252, SetTypeMap_252) {
  node n;
  n.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, n.type());
}

TEST_F(NodeTest_252, SetTypeNull_252) {
  node n;
  n.set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, n.type());
}

// Test set_null
TEST_F(NodeTest_252, SetNullSetsTypeToNull_252) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_null();
  EXPECT_EQ(NodeType::Null, n.type());
}

// Test set_scalar and scalar
TEST_F(NodeTest_252, SetAndGetScalar_252) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");
  EXPECT_EQ("hello", n.scalar());
}

TEST_F(NodeTest_252, SetScalarEmptyString_252) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("");
  EXPECT_EQ("", n.scalar());
}

// Test set_tag and tag
TEST_F(NodeTest_252, SetAndGetTag_252) {
  node n;
  n.set_tag("!mytag");
  EXPECT_EQ("!mytag", n.tag());
  EXPECT_TRUE(n.is_defined());
}

TEST_F(NodeTest_252, SetTagEmptyString_252) {
  node n;
  n.set_tag("");
  EXPECT_EQ("", n.tag());
}

TEST_F(NodeTest_252, DefaultTagIsEmpty_252) {
  node n;
  EXPECT_EQ("", n.tag());
}

// Test set_style and style
TEST_F(NodeTest_252, SetAndGetStyleDefault_252) {
  node n;
  n.set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, n.style());
}

TEST_F(NodeTest_252, SetAndGetStyleFlow_252) {
  node n;
  n.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, n.style());
}

TEST_F(NodeTest_252, SetAndGetStyleBlock_252) {
  node n;
  n.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, n.style());
}

// Test is() - identity check
TEST_F(NodeTest_252, NodeIsSelf_252) {
  node n;
  EXPECT_TRUE(n.is(n));
}

TEST_F(NodeTest_252, DifferentNodesAreNotSame_252) {
  node n1;
  node n2;
  EXPECT_FALSE(n1.is(n2));
}

// Test ref() returns non-null
TEST_F(NodeTest_252, RefIsNotNull_252) {
  node n;
  EXPECT_NE(nullptr, n.ref());
}

// Test set_mark and mark
TEST_F(NodeTest_252, SetAndGetMark_252) {
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

// Test size on empty sequence
TEST_F(NodeTest_252, EmptySequenceSize_252) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(0u, n.size());
}

// Test push_back on sequence
TEST_F(NodeTest_252, PushBackIncreasesSize_252) {
  node n;
  n.set_type(NodeType::Sequence);
  
  node& child = pMemory->create_node();
  child.set_type(NodeType::Scalar);
  child.set_scalar("value1");
  
  n.push_back(child, pMemory);
  EXPECT_EQ(1u, n.size());
}

TEST_F(NodeTest_252, PushBackMultipleElements_252) {
  node n;
  n.set_type(NodeType::Sequence);
  
  node& child1 = pMemory->create_node();
  child1.set_type(NodeType::Scalar);
  child1.set_scalar("a");
  
  node& child2 = pMemory->create_node();
  child2.set_type(NodeType::Scalar);
  child2.set_scalar("b");
  
  n.push_back(child1, pMemory);
  n.push_back(child2, pMemory);
  EXPECT_EQ(2u, n.size());
}

// Test begin/end on empty sequence
TEST_F(NodeTest_252, EmptySequenceBeginEqualsEnd_252) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_TRUE(n.begin() == n.end());
}

// Test insert on map
TEST_F(NodeTest_252, InsertIncreasesMapSize_252) {
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

// Test get on map
TEST_F(NodeTest_252, GetExistingKeyFromMap_252) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_type(NodeType::Scalar);
  key.set_scalar("mykey");
  
  node& value = pMemory->create_node();
  value.set_type(NodeType::Scalar);
  value.set_scalar("myvalue");
  
  n.insert(key, value, pMemory);
  
  node* result = n.get(key, pMemory);
  EXPECT_NE(nullptr, result);
  EXPECT_EQ("myvalue", result->scalar());
}

// Test get with string key
TEST_F(NodeTest_252, GetWithStringKey_252) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_type(NodeType::Scalar);
  key.set_scalar("testkey");
  
  node& value = pMemory->create_node();
  value.set_type(NodeType::Scalar);
  value.set_scalar("testval");
  
  n.insert(key, value, pMemory);
  
  node* result = n.get(std::string("testkey"), pMemory);
  EXPECT_NE(nullptr, result);
  EXPECT_EQ("testval", result->scalar());
}

// Test get nonexistent key returns null
TEST_F(NodeTest_252, GetNonexistentKeyReturnsNull_252) {
  node n;
  n.set_type(NodeType::Map);
  
  node* result = n.get(std::string("nonexistent"), pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test remove from map
TEST_F(NodeTest_252, RemoveExistingKeyFromMap_252) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_type(NodeType::Scalar);
  key.set_scalar("removekey");
  
  node& value = pMemory->create_node();
  value.set_type(NodeType::Scalar);
  value.set_scalar("removeval");
  
  n.insert(key, value, pMemory);
  EXPECT_EQ(1u, n.size());
  
  bool removed = n.remove(key, pMemory);
  EXPECT_TRUE(removed);
}

// Test remove nonexistent key
TEST_F(NodeTest_252, RemoveNonexistentKeyReturnsFalse_252) {
  node n;
  n.set_type(NodeType::Map);
  
  bool removed = n.remove(std::string("nokey"), pMemory);
  EXPECT_FALSE(removed);
}

// Test set_data copies data from another node
TEST_F(NodeTest_252, SetDataCopiesFromOtherNode_252) {
  node n1;
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("data");
  n1.set_tag("!tag");
  
  node n2;
  n2.set_data(n1);
  
  EXPECT_EQ("data", n2.scalar());
  EXPECT_EQ("!tag", n2.tag());
  EXPECT_EQ(NodeType::Scalar, n2.type());
}

// Test set_ref makes nodes share the same ref
TEST_F(NodeTest_252, SetRefSharesRef_252) {
  node n1;
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("shared");
  
  node n2;
  n2.set_ref(n1);
  
  EXPECT_EQ("shared", n2.scalar());
  EXPECT_EQ(n1.ref(), n2.ref());
}

// Test equals with matching scalar
TEST_F(NodeTest_252, EqualsMatchingScalar_252) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("test");
  
  EXPECT_TRUE(n.equals(std::string("test"), pMemory));
}

// Test equals with non-matching scalar
TEST_F(NodeTest_252, EqualsNonMatchingScalar_252) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("test");
  
  EXPECT_FALSE(n.equals(std::string("other"), pMemory));
}

// Test equals with const char*
TEST_F(NodeTest_252, EqualsConstCharPtr_252) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");
  
  EXPECT_TRUE(n.equals("hello", pMemory));
  EXPECT_FALSE(n.equals("world", pMemory));
}

// Test add_dependency doesn't change observable state but doesn't crash
TEST_F(NodeTest_252, AddDependencyDoesNotCrash_252) {
  node n1;
  node n2;
  n1.add_dependency(n2);
  // Just verify no crash
  EXPECT_TRUE(true);
}

// Test setting scalar overwrites previous scalar
TEST_F(NodeTest_252, SetScalarOverwritesPrevious_252) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("first");
  EXPECT_EQ("first", n.scalar());
  n.set_scalar("second");
  EXPECT_EQ("second", n.scalar());
}

// Test setting tag overwrites previous tag
TEST_F(NodeTest_252, SetTagOverwritesPrevious_252) {
  node n;
  n.set_tag("!first");
  EXPECT_EQ("!first", n.tag());
  n.set_tag("!second");
  EXPECT_EQ("!second", n.tag());
}

// Test changing type
TEST_F(NodeTest_252, ChangeType_252) {
  node n;
  n.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, n.type());
  n.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, n.type());
}

// Test empty map size
TEST_F(NodeTest_252, EmptyMapSize_252) {
  node n;
  n.set_type(NodeType::Map);
  EXPECT_EQ(0u, n.size());
}

// Test force_insert on map
TEST_F(NodeTest_252, ForceInsertOnMap_252) {
  node n;
  n.set_type(NodeType::Map);
  
  n.force_insert(std::string("key"), std::string("value"), pMemory);
  EXPECT_EQ(1u, n.size());
}

// Test multiple force_inserts with same key
TEST_F(NodeTest_252, ForceInsertDuplicateKey_252) {
  node n;
  n.set_type(NodeType::Map);
  
  n.force_insert(std::string("key"), std::string("value1"), pMemory);
  n.force_insert(std::string("key"), std::string("value2"), pMemory);
  EXPECT_EQ(2u, n.size());
}

// Test set_mark with default mark
TEST_F(NodeTest_252, DefaultMark_252) {
  node n;
  const Mark& m = n.mark();
  // Default mark should have line=0, column=0, pos=0 (or similar default)
  EXPECT_GE(m.line, 0);
  EXPECT_GE(m.column, 0);
}

// Test that after set_null, node is defined
TEST_F(NodeTest_252, SetNullMakesNodeDefined_252) {
  node n;
  n.set_null();
  EXPECT_TRUE(n.is_defined());
  EXPECT_EQ(NodeType::Null, n.type());
}

// Test sequence iteration after push_back
TEST_F(NodeTest_252, SequenceIterationAfterPushBack_252) {
  node n;
  n.set_type(NodeType::Sequence);
  
  node& child = pMemory->create_node();
  child.set_type(NodeType::Scalar);
  child.set_scalar("item");
  
  n.push_back(child, pMemory);
  
  EXPECT_FALSE(n.begin() == n.end());
}

}  // namespace detail
}  // namespace YAML
