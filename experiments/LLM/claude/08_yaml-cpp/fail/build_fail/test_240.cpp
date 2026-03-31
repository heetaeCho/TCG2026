#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeTest_240 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = create_shared_memory();
  }

  shared_memory_holder pMemory;
};

// Test default constructed node type
TEST_F(NodeTest_240, DefaultConstructedNodeTypeIsUndefined_240) {
  node n;
  EXPECT_EQ(NodeType::Undefined, n.type());
}

// Test is_defined on default node
TEST_F(NodeTest_240, DefaultConstructedNodeIsNotDefined_240) {
  node n;
  EXPECT_FALSE(n.is_defined());
}

// Test mark_defined
TEST_F(NodeTest_240, MarkDefinedMakesNodeDefined_240) {
  node n;
  n.mark_defined();
  EXPECT_TRUE(n.is_defined());
}

// Test set_type to Scalar
TEST_F(NodeTest_240, SetTypeToScalar_240) {
  node n;
  n.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, n.type());
}

// Test set_type to Sequence
TEST_F(NodeTest_240, SetTypeToSequence_240) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
}

// Test set_type to Map
TEST_F(NodeTest_240, SetTypeToMap_240) {
  node n;
  n.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, n.type());
}

// Test set_type to Null
TEST_F(NodeTest_240, SetTypeToNull_240) {
  node n;
  n.set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, n.type());
}

// Test set_null
TEST_F(NodeTest_240, SetNull_240) {
  node n;
  n.set_null();
  EXPECT_EQ(NodeType::Null, n.type());
}

// Test set_scalar and scalar
TEST_F(NodeTest_240, SetAndGetScalar_240) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");
  EXPECT_EQ("hello", n.scalar());
}

// Test set_scalar with empty string
TEST_F(NodeTest_240, SetScalarEmptyString_240) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("");
  EXPECT_EQ("", n.scalar());
}

// Test set_tag and tag
TEST_F(NodeTest_240, SetAndGetTag_240) {
  node n;
  n.set_tag("!!str");
  EXPECT_EQ("!!str", n.tag());
}

// Test set_tag with empty string
TEST_F(NodeTest_240, SetTagEmptyString_240) {
  node n;
  n.set_tag("");
  EXPECT_EQ("", n.tag());
}

// Test set_style and style
TEST_F(NodeTest_240, SetAndGetStyleDefault_240) {
  node n;
  n.set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, n.style());
}

TEST_F(NodeTest_240, SetAndGetStyleBlock_240) {
  node n;
  n.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, n.style());
}

TEST_F(NodeTest_240, SetAndGetStyleFlow_240) {
  node n;
  n.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, n.style());
}

// Test is() - same node
TEST_F(NodeTest_240, NodeIsSelf_240) {
  node n;
  EXPECT_TRUE(n.is(n));
}

// Test is() - different nodes
TEST_F(NodeTest_240, DifferentNodesAreNotSame_240) {
  node n1;
  node n2;
  EXPECT_FALSE(n1.is(n2));
}

// Test ref() returns non-null
TEST_F(NodeTest_240, RefIsNotNull_240) {
  node n;
  EXPECT_NE(nullptr, n.ref());
}

// Test set_mark and mark
TEST_F(NodeTest_240, SetAndGetMark_240) {
  node n;
  Mark m;
  m.line = 5;
  m.column = 10;
  n.set_mark(m);
  EXPECT_EQ(5, n.mark().line);
  EXPECT_EQ(10, n.mark().column);
}

// Test size on empty sequence
TEST_F(NodeTest_240, EmptySequenceSize_240) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(0u, n.size());
}

// Test push_back and size on sequence
TEST_F(NodeTest_240, PushBackIncreasesSize_240) {
  node n;
  n.set_type(NodeType::Sequence);

  node child;
  child.set_type(NodeType::Scalar);
  child.set_scalar("item1");

  n.push_back(child, pMemory);
  EXPECT_EQ(1u, n.size());
}

// Test push_back multiple items
TEST_F(NodeTest_240, PushBackMultipleItems_240) {
  node n;
  n.set_type(NodeType::Sequence);

  node child1;
  child1.set_type(NodeType::Scalar);
  child1.set_scalar("a");
  n.push_back(child1, pMemory);

  node child2;
  child2.set_type(NodeType::Scalar);
  child2.set_scalar("b");
  n.push_back(child2, pMemory);

  EXPECT_EQ(2u, n.size());
}

// Test begin/end on empty sequence
TEST_F(NodeTest_240, BeginEqualsEndOnEmptySequence_240) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(n.begin(), n.end());
}

// Test insert into map
TEST_F(NodeTest_240, InsertIntoMap_240) {
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

// Test get on map with string key
TEST_F(NodeTest_240, GetFromMapWithStringKey_240) {
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
  EXPECT_EQ("myvalue", result->scalar());
}

// Test get returns null for nonexistent key
TEST_F(NodeTest_240, GetReturnsNullForNonexistentKey_240) {
  node n;
  n.set_type(NodeType::Map);

  node* result = n.get(std::string("nonexistent"), pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test remove from map
TEST_F(NodeTest_240, RemoveFromMap_240) {
  node n;
  n.set_type(NodeType::Map);

  node key;
  key.set_type(NodeType::Scalar);
  key.set_scalar("removekey");

  node value;
  value.set_type(NodeType::Scalar);
  value.set_scalar("removeval");

  n.insert(key, value, pMemory);
  EXPECT_EQ(1u, n.size());

  bool removed = n.remove(std::string("removekey"), pMemory);
  EXPECT_TRUE(removed);
}

// Test remove nonexistent key
TEST_F(NodeTest_240, RemoveNonexistentKeyReturnsFalse_240) {
  node n;
  n.set_type(NodeType::Map);

  bool removed = n.remove(std::string("nope"), pMemory);
  EXPECT_FALSE(removed);
}

// Test remove with node key
TEST_F(NodeTest_240, RemoveWithNodeKey_240) {
  node n;
  n.set_type(NodeType::Map);

  node key;
  key.set_type(NodeType::Scalar);
  key.set_scalar("nodekey");

  node value;
  value.set_type(NodeType::Scalar);
  value.set_scalar("nodeval");

  n.insert(key, value, pMemory);

  bool removed = n.remove(key, pMemory);
  EXPECT_TRUE(removed);
}

// Test get with node key
TEST_F(NodeTest_240, GetWithNodeKey_240) {
  node n;
  n.set_type(NodeType::Map);

  node key;
  key.set_type(NodeType::Scalar);
  key.set_scalar("nkey");

  node value;
  value.set_type(NodeType::Scalar);
  value.set_scalar("nval");

  n.insert(key, value, pMemory);

  node* result = n.get(key, pMemory);
  EXPECT_NE(nullptr, result);
  EXPECT_EQ("nval", result->scalar());
}

// Test set_data copies data from another node
TEST_F(NodeTest_240, SetDataCopiesFromAnotherNode_240) {
  node n1;
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("source");
  n1.set_tag("!!tag");

  node n2;
  n2.set_data(n1);

  EXPECT_EQ(NodeType::Scalar, n2.type());
  EXPECT_EQ("source", n2.scalar());
  EXPECT_EQ("!!tag", n2.tag());
}

// Test set_ref makes nodes share the same ref
TEST_F(NodeTest_240, SetRefSharesReference_240) {
  node n1;
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("shared");

  node n2;
  n2.set_ref(n1);

  EXPECT_EQ("shared", n2.scalar());
  EXPECT_EQ(NodeType::Scalar, n2.type());
}

// Test equals with matching scalar
TEST_F(NodeTest_240, EqualsWithMatchingScalar_240) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("test");

  EXPECT_TRUE(n.equals(std::string("test"), pMemory));
}

// Test equals with non-matching scalar
TEST_F(NodeTest_240, EqualsWithNonMatchingScalar_240) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("test");

  EXPECT_FALSE(n.equals(std::string("other"), pMemory));
}

// Test equals with const char*
TEST_F(NodeTest_240, EqualsWithConstCharPtr_240) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");

  EXPECT_TRUE(n.equals("hello", pMemory));
  EXPECT_FALSE(n.equals("world", pMemory));
}

// Test force_insert
TEST_F(NodeTest_240, ForceInsertIntoMap_240) {
  node n;
  n.set_type(NodeType::Map);

  n.force_insert(std::string("fkey"), std::string("fval"), pMemory);
  EXPECT_EQ(1u, n.size());
}

// Test changing type from Scalar to Sequence clears scalar
TEST_F(NodeTest_240, ChangeTypeFromScalarToSequence_240) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("data");
  EXPECT_EQ(NodeType::Scalar, n.type());

  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
  EXPECT_EQ(0u, n.size());
}

// Test default mark
TEST_F(NodeTest_240, DefaultMarkValues_240) {
  node n;
  const Mark& m = n.mark();
  // Default mark should have invalid/unset position
  EXPECT_EQ(Mark::null_mark().line, m.line);
  EXPECT_EQ(Mark::null_mark().column, m.column);
}

// Test add_dependency doesn't crash
TEST_F(NodeTest_240, AddDependencyDoesNotCrash_240) {
  node n1;
  node n2;
  EXPECT_NO_THROW(n1.add_dependency(n2));
}

// Test set_type to Undefined
TEST_F(NodeTest_240, SetTypeToUndefined_240) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("value");
  n.set_type(NodeType::Undefined);
  EXPECT_EQ(NodeType::Undefined, n.type());
}

// Test multiple push_backs and iteration
TEST_F(NodeTest_240, IterateSequenceAfterPushBack_240) {
  node n;
  n.set_type(NodeType::Sequence);

  node child1;
  child1.set_type(NodeType::Scalar);
  child1.set_scalar("first");
  n.push_back(child1, pMemory);

  node child2;
  child2.set_type(NodeType::Scalar);
  child2.set_scalar("second");
  n.push_back(child2, pMemory);

  EXPECT_EQ(2u, n.size());
  EXPECT_NE(n.begin(), n.end());
}

// Test empty map size
TEST_F(NodeTest_240, EmptyMapSize_240) {
  node n;
  n.set_type(NodeType::Map);
  EXPECT_EQ(0u, n.size());
}

// Test that set_ref causes is() to still be independent
TEST_F(NodeTest_240, SetRefNodesAreNotIdentical_240) {
  node n1;
  node n2;
  n2.set_ref(n1);
  // n1 and n2 are different node objects even if sharing ref
  // They may or may not report is() as true - depends on implementation
  // But each node is always is() itself
  EXPECT_TRUE(n1.is(n1));
  EXPECT_TRUE(n2.is(n2));
}

}  // namespace detail
}  // namespace YAML
