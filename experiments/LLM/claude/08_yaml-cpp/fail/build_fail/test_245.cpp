#include "gtest/gtest.h"
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/type.h"

namespace YAML {
namespace detail {

class NodeTest_245 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = shared_memory_holder(new Memory);
  }

  shared_memory_holder pMemory;
};

// Test that a default-constructed node is not defined
TEST_F(NodeTest_245, DefaultConstructedNodeIsNotDefined_245) {
  node n;
  // A default node should have Undefined or Null type behavior
  EXPECT_FALSE(n.is_defined());
}

// Test that mark_defined makes a node defined
TEST_F(NodeTest_245, MarkDefinedMakesNodeDefined_245) {
  node n;
  n.mark_defined();
  EXPECT_TRUE(n.is_defined());
}

// Test that a node is itself
TEST_F(NodeTest_245, NodeIsItself_245) {
  node n;
  EXPECT_TRUE(n.is(n));
}

// Test that two different nodes are not the same
TEST_F(NodeTest_245, DifferentNodesAreNotSame_245) {
  node n1;
  node n2;
  EXPECT_FALSE(n1.is(n2));
}

// Test set_type and type
TEST_F(NodeTest_245, SetTypeAndGetType_245) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, n.type());
}

// Test set_type to Sequence
TEST_F(NodeTest_245, SetTypeSequence_245) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
}

// Test set_type to Map
TEST_F(NodeTest_245, SetTypeMap_245) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, n.type());
}

// Test set_null sets type to Null
TEST_F(NodeTest_245, SetNullSetsTypeNull_245) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Scalar);
  n.set_null();
  EXPECT_EQ(NodeType::Null, n.type());
}

// Test set_scalar and scalar
TEST_F(NodeTest_245, SetScalarAndGetScalar_245) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");
  EXPECT_EQ("hello", n.scalar());
}

// Test set_scalar with empty string
TEST_F(NodeTest_245, SetScalarEmpty_245) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Scalar);
  n.set_scalar("");
  EXPECT_EQ("", n.scalar());
}

// Test set_tag and tag
TEST_F(NodeTest_245, SetTagAndGetTag_245) {
  node n;
  n.mark_defined();
  n.set_tag("!mytag");
  EXPECT_EQ("!mytag", n.tag());
}

// Test set_tag with empty string
TEST_F(NodeTest_245, SetTagEmpty_245) {
  node n;
  n.mark_defined();
  n.set_tag("");
  EXPECT_EQ("", n.tag());
}

// Test set_style and style
TEST_F(NodeTest_245, SetStyleAndGetStyle_245) {
  node n;
  n.mark_defined();
  n.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, n.style());
}

// Test set_style Block
TEST_F(NodeTest_245, SetStyleBlock_245) {
  node n;
  n.mark_defined();
  n.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, n.style());
}

// Test set_style Default
TEST_F(NodeTest_245, SetStyleDefault_245) {
  node n;
  n.mark_defined();
  n.set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, n.style());
}

// Test sequence push_back and size
TEST_F(NodeTest_245, PushBackIncreasesSize_245) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(0u, n.size());

  node child;
  child.mark_defined();
  child.set_type(NodeType::Scalar);
  child.set_scalar("item1");
  n.push_back(child, pMemory);
  EXPECT_EQ(1u, n.size());
}

// Test sequence push_back multiple items
TEST_F(NodeTest_245, PushBackMultipleItems_245) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Sequence);

  node child1;
  child1.mark_defined();
  child1.set_type(NodeType::Scalar);
  child1.set_scalar("a");

  node child2;
  child2.mark_defined();
  child2.set_type(NodeType::Scalar);
  child2.set_scalar("b");

  n.push_back(child1, pMemory);
  n.push_back(child2, pMemory);
  EXPECT_EQ(2u, n.size());
}

// Test begin and end for empty sequence
TEST_F(NodeTest_245, EmptySequenceBeginEqualsEnd_245) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Sequence);
  EXPECT_TRUE(n.begin() == n.end());
}

// Test begin and end for non-empty sequence
TEST_F(NodeTest_245, NonEmptySequenceBeginNotEqualsEnd_245) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Sequence);

  node child;
  child.mark_defined();
  child.set_type(NodeType::Scalar);
  child.set_scalar("value");
  n.push_back(child, pMemory);

  EXPECT_FALSE(n.begin() == n.end());
}

// Test map insert and size
TEST_F(NodeTest_245, MapInsertIncreasesSize_245) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Map);
  EXPECT_EQ(0u, n.size());

  node key;
  key.mark_defined();
  key.set_type(NodeType::Scalar);
  key.set_scalar("key1");

  node value;
  value.mark_defined();
  value.set_type(NodeType::Scalar);
  value.set_scalar("value1");

  n.insert(key, value, pMemory);
  EXPECT_EQ(1u, n.size());
}

// Test add_dependency: when node is defined, rhs gets marked defined
TEST_F(NodeTest_245, AddDependencyDefinedNodeMarksRhsDefined_245) {
  node n;
  n.mark_defined();

  node rhs;
  EXPECT_FALSE(rhs.is_defined());
  n.add_dependency(rhs);
  EXPECT_TRUE(rhs.is_defined());
}

// Test add_dependency: when node is not defined, rhs stays undefined
TEST_F(NodeTest_245, AddDependencyUndefinedNodeDoesNotMarkRhsDefined_245) {
  node n;
  // n is not defined
  node rhs;
  EXPECT_FALSE(rhs.is_defined());
  n.add_dependency(rhs);
  EXPECT_FALSE(rhs.is_defined());
}

// Test add_dependency: deferred marking - when node becomes defined later,
// dependencies should also become defined
TEST_F(NodeTest_245, AddDependencyDeferredMarking_245) {
  node n;
  node rhs;
  
  // n is not defined, so rhs should not be marked defined yet
  n.add_dependency(rhs);
  EXPECT_FALSE(rhs.is_defined());
  
  // Now mark n defined; rhs should also become defined
  n.mark_defined();
  EXPECT_TRUE(n.is_defined());
  EXPECT_TRUE(rhs.is_defined());
}

// Test set_ref copies reference from another node
TEST_F(NodeTest_245, SetRefCopiesReference_245) {
  node n1;
  n1.mark_defined();
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("original");

  node n2;
  n2.mark_defined();
  n2.set_ref(n1);
  EXPECT_EQ("original", n2.scalar());
}

// Test set_data copies data from another node
TEST_F(NodeTest_245, SetDataCopiesData_245) {
  node n1;
  n1.mark_defined();
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("data_value");

  node n2;
  n2.mark_defined();
  n2.set_data(n1);
  EXPECT_EQ(NodeType::Scalar, n2.type());
  EXPECT_EQ("data_value", n2.scalar());
}

// Test ref returns non-null for valid node
TEST_F(NodeTest_245, RefReturnsNonNull_245) {
  node n;
  EXPECT_NE(nullptr, n.ref());
}

// Test mark returns a Mark object
TEST_F(NodeTest_245, MarkReturnsValidMark_245) {
  node n;
  n.mark_defined();
  const Mark& m = n.mark();
  // Default mark should have line/column 0 or similar default values
  (void)m; // Just ensure no crash
}

// Test set_mark
TEST_F(NodeTest_245, SetMark_245) {
  node n;
  n.mark_defined();
  Mark m(10, 20, 30);
  n.set_mark(m);
  const Mark& retrieved = n.mark();
  EXPECT_EQ(10, retrieved.pos);
  EXPECT_EQ(20, retrieved.line);
  EXPECT_EQ(30, retrieved.column);
}

// Test get on map returns correct node
TEST_F(NodeTest_245, MapGetReturnsCorrectNode_245) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Map);

  node key;
  key.mark_defined();
  key.set_type(NodeType::Scalar);
  key.set_scalar("mykey");

  node value;
  value.mark_defined();
  value.set_type(NodeType::Scalar);
  value.set_scalar("myvalue");

  n.insert(key, value, pMemory);

  node* found = n.get(key, pMemory);
  EXPECT_NE(nullptr, found);
}

// Test get with string key on map
TEST_F(NodeTest_245, MapGetWithStringKey_245) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Map);

  node key;
  key.mark_defined();
  key.set_type(NodeType::Scalar);
  key.set_scalar("strkey");

  node value;
  value.mark_defined();
  value.set_type(NodeType::Scalar);
  value.set_scalar("strvalue");

  n.insert(key, value, pMemory);

  node* found = n.get(std::string("strkey"), pMemory);
  EXPECT_NE(nullptr, found);
}

// Test get returns null for nonexistent key
TEST_F(NodeTest_245, MapGetNonExistentKeyReturnsNull_245) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Map);

  node* found = n.get(std::string("nonexistent"), pMemory);
  EXPECT_EQ(nullptr, found);
}

// Test remove from map
TEST_F(NodeTest_245, MapRemoveExistingKey_245) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Map);

  node key;
  key.mark_defined();
  key.set_type(NodeType::Scalar);
  key.set_scalar("removekey");

  node value;
  value.mark_defined();
  value.set_type(NodeType::Scalar);
  value.set_scalar("removevalue");

  n.insert(key, value, pMemory);
  EXPECT_EQ(1u, n.size());

  bool removed = n.remove(key, pMemory);
  EXPECT_TRUE(removed);
}

// Test remove nonexistent key
TEST_F(NodeTest_245, MapRemoveNonExistentKey_245) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Map);

  bool removed = n.remove(std::string("nokey"), pMemory);
  EXPECT_FALSE(removed);
}

// Test equals with matching scalar
TEST_F(NodeTest_245, EqualsMatchingScalar_245) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Scalar);
  n.set_scalar("test");

  EXPECT_TRUE(n.equals(std::string("test"), pMemory));
}

// Test equals with non-matching scalar
TEST_F(NodeTest_245, EqualsNonMatchingScalar_245) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Scalar);
  n.set_scalar("test");

  EXPECT_FALSE(n.equals(std::string("other"), pMemory));
}

// Test equals with const char*
TEST_F(NodeTest_245, EqualsConstCharPtr_245) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");

  EXPECT_TRUE(n.equals("hello", pMemory));
  EXPECT_FALSE(n.equals("world", pMemory));
}

// Test default type of undefined node
TEST_F(NodeTest_245, UndefinedNodeType_245) {
  node n;
  EXPECT_EQ(NodeType::Undefined, n.type());
}

// Test that set_type to Null works
TEST_F(NodeTest_245, SetTypeNull_245) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, n.type());
}

// Test multiple dependencies
TEST_F(NodeTest_245, AddMultipleDependencies_245) {
  node n;
  node dep1;
  node dep2;
  node dep3;

  n.add_dependency(dep1);
  n.add_dependency(dep2);
  n.add_dependency(dep3);

  EXPECT_FALSE(dep1.is_defined());
  EXPECT_FALSE(dep2.is_defined());
  EXPECT_FALSE(dep3.is_defined());

  n.mark_defined();

  EXPECT_TRUE(dep1.is_defined());
  EXPECT_TRUE(dep2.is_defined());
  EXPECT_TRUE(dep3.is_defined());
}

// Test force_insert on map
TEST_F(NodeTest_245, ForceInsertOnMap_245) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Map);

  n.force_insert(std::string("key"), std::string("value"), pMemory);
  EXPECT_EQ(1u, n.size());
}

// Test overwriting scalar
TEST_F(NodeTest_245, OverwriteScalar_245) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Scalar);
  n.set_scalar("first");
  EXPECT_EQ("first", n.scalar());

  n.set_scalar("second");
  EXPECT_EQ("second", n.scalar());
}

// Test overwriting tag
TEST_F(NodeTest_245, OverwriteTag_245) {
  node n;
  n.mark_defined();
  n.set_tag("!tag1");
  EXPECT_EQ("!tag1", n.tag());

  n.set_tag("!tag2");
  EXPECT_EQ("!tag2", n.tag());
}

// Test size of empty map
TEST_F(NodeTest_245, EmptyMapSizeIsZero_245) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Map);
  EXPECT_EQ(0u, n.size());
}

// Test size of empty sequence
TEST_F(NodeTest_245, EmptySequenceSizeIsZero_245) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(0u, n.size());
}

}  // namespace detail
}  // namespace YAML
