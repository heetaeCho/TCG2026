#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeTest_261 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory.reset(new Memory);
  }

  shared_memory_holder pMemory;
};

// Test default construction - node should not be defined initially
TEST_F(NodeTest_261, DefaultConstructionIsNotDefined_261) {
  node n;
  EXPECT_FALSE(n.is_defined());
}

// Test default construction - type should be Undefined
TEST_F(NodeTest_261, DefaultConstructionTypeUndefined_261) {
  node n;
  EXPECT_EQ(NodeType::Undefined, n.type());
}

// Test mark_defined
TEST_F(NodeTest_261, MarkDefinedMakesNodeDefined_261) {
  node n;
  n.mark_defined();
  EXPECT_TRUE(n.is_defined());
}

// Test set_null sets type to Null
TEST_F(NodeTest_261, SetNullChangesTypeToNull_261) {
  node n;
  n.mark_defined();
  n.set_null();
  EXPECT_EQ(NodeType::Null, n.type());
}

// Test set_scalar
TEST_F(NodeTest_261, SetScalarStoresValue_261) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");
  EXPECT_EQ("hello", n.scalar());
}

// Test set_type to Sequence
TEST_F(NodeTest_261, SetTypeSequence_261) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
}

// Test set_type to Map
TEST_F(NodeTest_261, SetTypeMap_261) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, n.type());
}

// Test set_tag and tag retrieval
TEST_F(NodeTest_261, SetTagRetrievesTag_261) {
  node n;
  n.mark_defined();
  n.set_tag("!custom");
  EXPECT_EQ("!custom", n.tag());
}

// Test empty tag by default
TEST_F(NodeTest_261, DefaultTagIsEmpty_261) {
  node n;
  EXPECT_EQ("", n.tag());
}

// Test set_style
TEST_F(NodeTest_261, SetStyleRetrievesStyle_261) {
  node n;
  n.mark_defined();
  n.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, n.style());
}

// Test default style
TEST_F(NodeTest_261, DefaultStyleIsDefault_261) {
  node n;
  EXPECT_EQ(EmitterStyle::Default, n.style());
}

// Test is() - same node
TEST_F(NodeTest_261, NodeIsSameAsItself_261) {
  node n;
  EXPECT_TRUE(n.is(n));
}

// Test is() - different nodes
TEST_F(NodeTest_261, DifferentNodesAreNotSame_261) {
  node n1;
  node n2;
  EXPECT_FALSE(n1.is(n2));
}

// Test ref() returns non-null
TEST_F(NodeTest_261, RefReturnsNonNull_261) {
  node n;
  EXPECT_NE(nullptr, n.ref());
}

// Test size() of empty sequence
TEST_F(NodeTest_261, EmptySequenceSizeIsZero_261) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(0u, n.size());
}

// Test push_back increases size
TEST_F(NodeTest_261, PushBackIncreasesSize_261) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Sequence);

  node child;
  child.mark_defined();
  child.set_type(NodeType::Scalar);
  child.set_scalar("item");

  n.push_back(child, pMemory);
  EXPECT_EQ(1u, n.size());
}

// Test push_back multiple items
TEST_F(NodeTest_261, PushBackMultipleItems_261) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Sequence);

  node child1;
  child1.mark_defined();
  child1.set_type(NodeType::Scalar);
  child1.set_scalar("item1");

  node child2;
  child2.mark_defined();
  child2.set_type(NodeType::Scalar);
  child2.set_scalar("item2");

  n.push_back(child1, pMemory);
  n.push_back(child2, pMemory);
  EXPECT_EQ(2u, n.size());
}

// Test set_data copies data from another node
TEST_F(NodeTest_261, SetDataCopiesFromAnotherNode_261) {
  node src;
  src.mark_defined();
  src.set_type(NodeType::Scalar);
  src.set_scalar("source");

  node dst;
  dst.set_data(src);
  EXPECT_EQ("source", dst.scalar());
  EXPECT_EQ(NodeType::Scalar, dst.type());
}

// Test set_ref makes nodes reference the same data
TEST_F(NodeTest_261, SetRefMakesNodeShareRef_261) {
  node src;
  src.mark_defined();
  src.set_type(NodeType::Scalar);
  src.set_scalar("shared");

  node dst;
  dst.set_ref(src);
  EXPECT_TRUE(dst.is(src));
}

// Test get on map with string key
TEST_F(NodeTest_261, GetStringKeyFromMap_261) {
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

  node* result = n.get(std::string("mykey"), pMemory);
  EXPECT_NE(nullptr, result);
}

// Test get with non-existent key returns nullptr
TEST_F(NodeTest_261, GetNonExistentKeyReturnsNull_261) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Map);

  node* result = n.get(std::string("nonexistent"), pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test get with node key
TEST_F(NodeTest_261, GetWithNodeKey_261) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Map);

  node key;
  key.mark_defined();
  key.set_type(NodeType::Scalar);
  key.set_scalar("nodekey");

  node value;
  value.mark_defined();
  value.set_type(NodeType::Scalar);
  value.set_scalar("nodevalue");

  n.insert(key, value, pMemory);

  node* result = n.get(key, pMemory);
  EXPECT_NE(nullptr, result);
}

// Test remove from map
TEST_F(NodeTest_261, RemoveExistingKeyReturnsTrue_261) {
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

  bool removed = n.remove(std::string("removekey"), pMemory);
  EXPECT_TRUE(removed);
}

// Test remove non-existent key
TEST_F(NodeTest_261, RemoveNonExistentKeyReturnsFalse_261) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Map);

  bool removed = n.remove(std::string("nonexistent"), pMemory);
  EXPECT_FALSE(removed);
}

// Test remove with node key
TEST_F(NodeTest_261, RemoveWithNodeKey_261) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Map);

  node key;
  key.mark_defined();
  key.set_type(NodeType::Scalar);
  key.set_scalar("nkey");

  node value;
  value.mark_defined();
  value.set_type(NodeType::Scalar);
  value.set_scalar("nvalue");

  n.insert(key, value, pMemory);

  bool removed = n.remove(key, pMemory);
  EXPECT_TRUE(removed);
}

// Test equals with matching scalar
TEST_F(NodeTest_261, EqualsReturnsTrueForMatchingScalar_261) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Scalar);
  n.set_scalar("test");

  EXPECT_TRUE(n.equals(std::string("test"), pMemory));
}

// Test equals with non-matching scalar
TEST_F(NodeTest_261, EqualsReturnsFalseForNonMatchingScalar_261) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Scalar);
  n.set_scalar("test");

  EXPECT_FALSE(n.equals(std::string("other"), pMemory));
}

// Test equals with const char*
TEST_F(NodeTest_261, EqualsWithConstCharPtr_261) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");

  EXPECT_TRUE(n.equals("hello", pMemory));
  EXPECT_FALSE(n.equals("world", pMemory));
}

// Test set_mark
TEST_F(NodeTest_261, SetMarkAndRetrieve_261) {
  node n;
  Mark m;
  m.line = 5;
  m.column = 10;
  n.set_mark(m);

  const Mark& retrieved = n.mark();
  EXPECT_EQ(5, retrieved.line);
  EXPECT_EQ(10, retrieved.column);
}

// Test begin/end on empty sequence
TEST_F(NodeTest_261, BeginEqualsEndOnEmptySequence_261) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Sequence);

  EXPECT_TRUE(n.begin() == n.end());
}

// Test begin/end on sequence with elements
TEST_F(NodeTest_261, BeginNotEqualEndOnNonEmptySequence_261) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Sequence);

  node child;
  child.mark_defined();
  child.set_type(NodeType::Scalar);
  child.set_scalar("element");

  n.push_back(child, pMemory);

  EXPECT_FALSE(n.begin() == n.end());
}

// Test insert into map increases size
TEST_F(NodeTest_261, InsertIncreasesMapSize_261) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Map);

  EXPECT_EQ(0u, n.size());

  node key;
  key.mark_defined();
  key.set_type(NodeType::Scalar);
  key.set_scalar("k");

  node value;
  value.mark_defined();
  value.set_type(NodeType::Scalar);
  value.set_scalar("v");

  n.insert(key, value, pMemory);
  EXPECT_EQ(1u, n.size());
}

// Test force_insert
TEST_F(NodeTest_261, ForceInsertAddsEntry_261) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Map);

  n.force_insert(std::string("fkey"), std::string("fvalue"), pMemory);
  EXPECT_EQ(1u, n.size());
}

// Test overwriting scalar
TEST_F(NodeTest_261, OverwriteScalarValue_261) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Scalar);
  n.set_scalar("first");
  EXPECT_EQ("first", n.scalar());

  n.set_scalar("second");
  EXPECT_EQ("second", n.scalar());
}

// Test changing type clears previous content
TEST_F(NodeTest_261, ChangingTypeFromSequenceToScalar_261) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Sequence);

  node child;
  child.mark_defined();
  child.set_type(NodeType::Scalar);
  child.set_scalar("item");
  n.push_back(child, pMemory);
  EXPECT_EQ(1u, n.size());

  n.set_type(NodeType::Scalar);
  n.set_scalar("now_scalar");
  EXPECT_EQ(NodeType::Scalar, n.type());
  EXPECT_EQ("now_scalar", n.scalar());
}

// Test empty scalar
TEST_F(NodeTest_261, EmptyScalarValue_261) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Scalar);
  n.set_scalar("");
  EXPECT_EQ("", n.scalar());
}

// Test set_tag with empty string
TEST_F(NodeTest_261, SetEmptyTag_261) {
  node n;
  n.mark_defined();
  n.set_tag("");
  EXPECT_EQ("", n.tag());
}

// Test add_dependency doesn't change node behavior
TEST_F(NodeTest_261, AddDependencyDoesNotChangeType_261) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Scalar);
  n.set_scalar("original");

  node dep;
  dep.mark_defined();
  dep.set_type(NodeType::Scalar);
  dep.set_scalar("dependency");

  n.add_dependency(dep);

  // The node's own type and scalar should be unchanged
  EXPECT_EQ(NodeType::Scalar, n.type());
  EXPECT_EQ("original", n.scalar());
}

}  // namespace detail
}  // namespace YAML
