#include "gtest/gtest.h"
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeTest_244 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = std::make_shared<memory>();
  }

  shared_memory_holder pMemory;
};

// Test that a newly created node is not defined
TEST_F(NodeTest_244, NewNodeIsNotDefined_244) {
  node& n = pMemory->create_node();
  EXPECT_FALSE(n.is_defined());
}

// Test that mark_defined makes a node defined
TEST_F(NodeTest_244, MarkDefinedMakesNodeDefined_244) {
  node& n = pMemory->create_node();
  n.mark_defined();
  EXPECT_TRUE(n.is_defined());
}

// Test that calling mark_defined multiple times is safe
TEST_F(NodeTest_244, MarkDefinedIdempotent_244) {
  node& n = pMemory->create_node();
  n.mark_defined();
  n.mark_defined();
  EXPECT_TRUE(n.is_defined());
}

// Test that a node is itself
TEST_F(NodeTest_244, NodeIsItself_244) {
  node& n = pMemory->create_node();
  EXPECT_TRUE(n.is(n));
}

// Test that two different nodes are not the same
TEST_F(NodeTest_244, DifferentNodesAreNotSame_244) {
  node& n1 = pMemory->create_node();
  node& n2 = pMemory->create_node();
  EXPECT_FALSE(n1.is(n2));
}

// Test that default type is Undefined
TEST_F(NodeTest_244, DefaultTypeIsUndefined_244) {
  node& n = pMemory->create_node();
  EXPECT_EQ(NodeType::Undefined, n.type());
}

// Test set_type and type
TEST_F(NodeTest_244, SetTypeScalar_244) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, n.type());
}

TEST_F(NodeTest_244, SetTypeSequence_244) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
}

TEST_F(NodeTest_244, SetTypeMap_244) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, n.type());
}

TEST_F(NodeTest_244, SetTypeNull_244) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, n.type());
}

// Test set_null
TEST_F(NodeTest_244, SetNull_244) {
  node& n = pMemory->create_node();
  n.set_null();
  EXPECT_EQ(NodeType::Null, n.type());
}

// Test set_scalar and scalar
TEST_F(NodeTest_244, SetAndGetScalar_244) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");
  EXPECT_EQ("hello", n.scalar());
}

// Test set_scalar with empty string
TEST_F(NodeTest_244, SetEmptyScalar_244) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  n.set_scalar("");
  EXPECT_EQ("", n.scalar());
}

// Test set_tag and tag
TEST_F(NodeTest_244, SetAndGetTag_244) {
  node& n = pMemory->create_node();
  n.set_tag("!mytag");
  EXPECT_EQ("!mytag", n.tag());
}

// Test set_tag with empty string
TEST_F(NodeTest_244, SetEmptyTag_244) {
  node& n = pMemory->create_node();
  n.set_tag("");
  EXPECT_EQ("", n.tag());
}

// Test set_style and style
TEST_F(NodeTest_244, SetAndGetStyleDefault_244) {
  node& n = pMemory->create_node();
  n.set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, n.style());
}

TEST_F(NodeTest_244, SetAndGetStyleBlock_244) {
  node& n = pMemory->create_node();
  n.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, n.style());
}

TEST_F(NodeTest_244, SetAndGetStyleFlow_244) {
  node& n = pMemory->create_node();
  n.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, n.style());
}

// Test that set_mark and mark work
TEST_F(NodeTest_244, SetAndGetMark_244) {
  node& n = pMemory->create_node();
  Mark m;
  m.line = 10;
  m.column = 20;
  m.pos = 30;
  n.set_mark(m);
  EXPECT_EQ(10, n.mark().line);
  EXPECT_EQ(20, n.mark().column);
  EXPECT_EQ(30, n.mark().pos);
}

// Test size of empty sequence
TEST_F(NodeTest_244, EmptySequenceSize_244) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(0u, n.size());
}

// Test push_back increases size for sequence
TEST_F(NodeTest_244, PushBackIncreasesSize_244) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Sequence);
  node& child = pMemory->create_node();
  child.set_type(NodeType::Scalar);
  child.set_scalar("value1");
  n.push_back(child, pMemory);
  EXPECT_EQ(1u, n.size());
}

// Test multiple push_backs
TEST_F(NodeTest_244, MultiplePushBacks_244) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Sequence);
  
  for (int i = 0; i < 5; i++) {
    node& child = pMemory->create_node();
    child.set_type(NodeType::Scalar);
    child.set_scalar("val" + std::to_string(i));
    n.push_back(child, pMemory);
  }
  EXPECT_EQ(5u, n.size());
}

// Test empty map size
TEST_F(NodeTest_244, EmptyMapSize_244) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Map);
  EXPECT_EQ(0u, n.size());
}

// Test insert into map
TEST_F(NodeTest_244, InsertIntoMap_244) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_type(NodeType::Scalar);
  key.set_scalar("key1");
  
  node& val = pMemory->create_node();
  val.set_type(NodeType::Scalar);
  val.set_scalar("val1");
  
  n.insert(key, val, pMemory);
  EXPECT_EQ(1u, n.size());
}

// Test add_dependency and mark_defined propagation
TEST_F(NodeTest_244, AddDependencyPropagatesMarkDefined_244) {
  node& parent = pMemory->create_node();
  node& dep = pMemory->create_node();
  
  parent.add_dependency(dep);
  
  EXPECT_FALSE(dep.is_defined());
  parent.mark_defined();
  EXPECT_TRUE(parent.is_defined());
  EXPECT_TRUE(dep.is_defined());
}

// Test that dependencies are cleared after mark_defined
TEST_F(NodeTest_244, DependenciesClearedAfterMarkDefined_244) {
  node& parent = pMemory->create_node();
  node& dep1 = pMemory->create_node();
  
  parent.add_dependency(dep1);
  parent.mark_defined();
  
  // dep1 should be defined now
  EXPECT_TRUE(dep1.is_defined());
  
  // Add a new dependency after clearing
  node& dep2 = pMemory->create_node();
  parent.add_dependency(dep2);
  
  // mark_defined again - since parent is already defined, 
  // the early return should happen and dep2 might not be marked
  parent.mark_defined();
  // After the second call, parent is already defined, so it returns early
  // The dependency dep2 should NOT be marked since the early return fires
  // Actually looking at the code: "if (is_defined()) return;" - so dep2 won't be marked
  // This is testing the early return behavior
}

// Test multiple dependencies
TEST_F(NodeTest_244, MultipleDependenciesAllMarkedDefined_244) {
  node& parent = pMemory->create_node();
  node& dep1 = pMemory->create_node();
  node& dep2 = pMemory->create_node();
  node& dep3 = pMemory->create_node();
  
  parent.add_dependency(dep1);
  parent.add_dependency(dep2);
  parent.add_dependency(dep3);
  
  EXPECT_FALSE(dep1.is_defined());
  EXPECT_FALSE(dep2.is_defined());
  EXPECT_FALSE(dep3.is_defined());
  
  parent.mark_defined();
  
  EXPECT_TRUE(dep1.is_defined());
  EXPECT_TRUE(dep2.is_defined());
  EXPECT_TRUE(dep3.is_defined());
}

// Test set_ref makes two nodes share the same ref
TEST_F(NodeTest_244, SetRefSharesReference_244) {
  node& n1 = pMemory->create_node();
  node& n2 = pMemory->create_node();
  
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("shared");
  
  n2.set_ref(n1);
  
  EXPECT_EQ("shared", n2.scalar());
  EXPECT_TRUE(n2.is(n1));
}

// Test set_data copies data
TEST_F(NodeTest_244, SetDataCopiesData_244) {
  node& n1 = pMemory->create_node();
  node& n2 = pMemory->create_node();
  
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("original");
  
  n2.set_data(n1);
  
  EXPECT_EQ("original", n2.scalar());
  // They should NOT be the same node
  EXPECT_FALSE(n2.is(n1));
}

// Test ref() returns non-null
TEST_F(NodeTest_244, RefReturnsNonNull_244) {
  node& n = pMemory->create_node();
  EXPECT_NE(nullptr, n.ref());
}

// Test equals with string
TEST_F(NodeTest_244, EqualsWithString_244) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  n.set_scalar("test");
  
  EXPECT_TRUE(n.equals(std::string("test"), pMemory));
  EXPECT_FALSE(n.equals(std::string("other"), pMemory));
}

// Test equals with const char*
TEST_F(NodeTest_244, EqualsWithCString_244) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");
  
  EXPECT_TRUE(n.equals("hello", pMemory));
  EXPECT_FALSE(n.equals("world", pMemory));
}

// Test is_defined after setting type
TEST_F(NodeTest_244, IsDefinedAfterSettingType_244) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Scalar);
  EXPECT_TRUE(n.is_defined());
}

// Test begin and end for empty sequence
TEST_F(NodeTest_244, BeginEqualsEndForEmptySequence_244) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Sequence);
  EXPECT_TRUE(n.begin() == n.end());
}

// Test begin and end for non-empty sequence
TEST_F(NodeTest_244, BeginNotEqualsEndForNonEmptySequence_244) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Sequence);
  
  node& child = pMemory->create_node();
  child.set_type(NodeType::Scalar);
  child.set_scalar("item");
  n.push_back(child, pMemory);
  
  EXPECT_FALSE(n.begin() == n.end());
}

// Test get on map
TEST_F(NodeTest_244, GetOnMap_244) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_type(NodeType::Scalar);
  key.set_scalar("mykey");
  
  node& val = pMemory->create_node();
  val.set_type(NodeType::Scalar);
  val.set_scalar("myval");
  
  n.insert(key, val, pMemory);
  
  node* result = n.get(std::string("mykey"), pMemory);
  EXPECT_NE(nullptr, result);
}

// Test get on map with non-existent key
TEST_F(NodeTest_244, GetNonExistentKey_244) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Map);
  
  node* result = n.get(std::string("nonexistent"), pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test remove from map
TEST_F(NodeTest_244, RemoveFromMap_244) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_type(NodeType::Scalar);
  key.set_scalar("removekey");
  
  node& val = pMemory->create_node();
  val.set_type(NodeType::Scalar);
  val.set_scalar("removeval");
  
  n.insert(key, val, pMemory);
  EXPECT_EQ(1u, n.size());
  
  bool removed = n.remove(std::string("removekey"), pMemory);
  EXPECT_TRUE(removed);
  EXPECT_EQ(0u, n.size());
}

// Test remove non-existent key
TEST_F(NodeTest_244, RemoveNonExistentKey_244) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Map);
  
  bool removed = n.remove(std::string("nonexistent"), pMemory);
  EXPECT_FALSE(removed);
}

// Test that mark_defined on already-defined node doesn't propagate to newly added dependencies
TEST_F(NodeTest_244, MarkDefinedEarlyReturnDoesNotPropagate_244) {
  node& parent = pMemory->create_node();
  parent.mark_defined();
  EXPECT_TRUE(parent.is_defined());
  
  node& dep = pMemory->create_node();
  parent.add_dependency(dep);
  
  // Parent is already defined, so mark_defined returns early
  parent.mark_defined();
  
  // dep should NOT be marked defined because the early return fires
  EXPECT_FALSE(dep.is_defined());
}

// Test force_insert
TEST_F(NodeTest_244, ForceInsert_244) {
  node& n = pMemory->create_node();
  n.set_type(NodeType::Map);
  
  n.force_insert(std::string("key"), std::string("value"), pMemory);
  EXPECT_EQ(1u, n.size());
}

}  // namespace detail
}  // namespace YAML
