#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/type.h"
#include "yaml-cpp/emitterstyle.h"
#include "yaml-cpp/mark.h"

namespace YAML {
namespace detail {

class NodeTest_237 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = shared_memory_holder(new memory_holder);
  }

  shared_memory_holder pMemory;
};

// Test that a default-constructed node has a valid ref
TEST_F(NodeTest_237, DefaultConstructionHasValidRef_237) {
  node n;
  EXPECT_NE(nullptr, n.ref());
}

// Test that a default-constructed node is defined (mark_defined has not been called, 
// but the node exists)
TEST_F(NodeTest_237, DefaultConstructionType_237) {
  node n;
  // Default node type should be Undefined
  EXPECT_EQ(NodeType::Undefined, n.type());
}

// Test is_defined on a default node
TEST_F(NodeTest_237, DefaultNodeIsNotDefined_237) {
  node n;
  EXPECT_FALSE(n.is_defined());
}

// Test mark_defined makes node defined
TEST_F(NodeTest_237, MarkDefinedMakesNodeDefined_237) {
  node n;
  n.mark_defined();
  EXPECT_TRUE(n.is_defined());
}

// Test that a node is itself
TEST_F(NodeTest_237, NodeIsItself_237) {
  node n;
  EXPECT_TRUE(n.is(n));
}

// Test that two different nodes are not the same
TEST_F(NodeTest_237, DifferentNodesAreNotSame_237) {
  node n1;
  node n2;
  EXPECT_FALSE(n1.is(n2));
}

// Test set_type to Scalar
TEST_F(NodeTest_237, SetTypeScalar_237) {
  node n;
  n.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, n.type());
}

// Test set_type to Sequence
TEST_F(NodeTest_237, SetTypeSequence_237) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
}

// Test set_type to Map
TEST_F(NodeTest_237, SetTypeMap_237) {
  node n;
  n.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, n.type());
}

// Test set_null sets type to Null
TEST_F(NodeTest_237, SetNull_237) {
  node n;
  n.set_null();
  EXPECT_EQ(NodeType::Null, n.type());
}

// Test set_scalar and scalar retrieval
TEST_F(NodeTest_237, SetAndGetScalar_237) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");
  EXPECT_EQ("hello", n.scalar());
}

// Test set_scalar with empty string
TEST_F(NodeTest_237, SetScalarEmpty_237) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("");
  EXPECT_EQ("", n.scalar());
}

// Test set_tag and tag retrieval
TEST_F(NodeTest_237, SetAndGetTag_237) {
  node n;
  n.set_tag("!mytag");
  EXPECT_EQ("!mytag", n.tag());
}

// Test set_tag with empty string
TEST_F(NodeTest_237, SetTagEmpty_237) {
  node n;
  n.set_tag("");
  EXPECT_EQ("", n.tag());
}

// Test set_style and style retrieval
TEST_F(NodeTest_237, SetAndGetStyleDefault_237) {
  node n;
  n.set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, n.style());
}

TEST_F(NodeTest_237, SetAndGetStyleBlock_237) {
  node n;
  n.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, n.style());
}

TEST_F(NodeTest_237, SetAndGetStyleFlow_237) {
  node n;
  n.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, n.style());
}

// Test set_mark and mark retrieval
TEST_F(NodeTest_237, SetAndGetMark_237) {
  node n;
  Mark m;
  m.line = 10;
  m.column = 20;
  m.pos = 30;
  n.set_mark(m);
  const Mark& result = n.mark();
  EXPECT_EQ(10, result.line);
  EXPECT_EQ(20, result.column);
  EXPECT_EQ(30, result.pos);
}

// Test size of empty sequence
TEST_F(NodeTest_237, EmptySequenceSize_237) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(0u, n.size());
}

// Test push_back increases size
TEST_F(NodeTest_237, PushBackIncreasesSize_237) {
  node n;
  n.set_type(NodeType::Sequence);
  
  node& child = pMemory->create_node();
  child.set_type(NodeType::Scalar);
  child.set_scalar("item1");
  
  n.push_back(child, pMemory);
  EXPECT_EQ(1u, n.size());
}

// Test push_back multiple items
TEST_F(NodeTest_237, PushBackMultipleItems_237) {
  node n;
  n.set_type(NodeType::Sequence);
  
  node& child1 = pMemory->create_node();
  child1.set_type(NodeType::Scalar);
  child1.set_scalar("item1");
  n.push_back(child1, pMemory);
  
  node& child2 = pMemory->create_node();
  child2.set_type(NodeType::Scalar);
  child2.set_scalar("item2");
  n.push_back(child2, pMemory);
  
  EXPECT_EQ(2u, n.size());
}

// Test begin and end iterators for empty sequence
TEST_F(NodeTest_237, EmptySequenceBeginEqualsEnd_237) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(n.begin(), n.end());
}

// Test begin and end iterators for non-empty sequence
TEST_F(NodeTest_237, NonEmptySequenceBeginNotEqualsEnd_237) {
  node n;
  n.set_type(NodeType::Sequence);
  
  node& child = pMemory->create_node();
  child.set_type(NodeType::Scalar);
  child.set_scalar("item");
  n.push_back(child, pMemory);
  
  EXPECT_NE(n.begin(), n.end());
}

// Test map insert and size
TEST_F(NodeTest_237, MapInsertIncreasesSize_237) {
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

// Test get on a map with string key
TEST_F(NodeTest_237, MapGetExistingKey_237) {
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

// Test get on a map with non-existing key returns nullptr
TEST_F(NodeTest_237, MapGetNonExistingKey_237) {
  node n;
  n.set_type(NodeType::Map);
  
  node* result = n.get(std::string("nonexistent"), pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test remove on a map
TEST_F(NodeTest_237, MapRemoveExistingKey_237) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_type(NodeType::Scalar);
  key.set_scalar("mykey");
  
  node& value = pMemory->create_node();
  value.set_type(NodeType::Scalar);
  value.set_scalar("myvalue");
  
  n.insert(key, value, pMemory);
  EXPECT_EQ(1u, n.size());
  
  bool removed = n.remove(std::string("mykey"), pMemory);
  EXPECT_TRUE(removed);
}

// Test remove non-existing key
TEST_F(NodeTest_237, MapRemoveNonExistingKey_237) {
  node n;
  n.set_type(NodeType::Map);
  
  bool removed = n.remove(std::string("nonexistent"), pMemory);
  EXPECT_FALSE(removed);
}

// Test set_ref makes node reference another node
TEST_F(NodeTest_237, SetRefCopiesRefFromOtherNode_237) {
  node n1;
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("original");
  
  node n2;
  n2.set_ref(n1);
  
  EXPECT_EQ("original", n2.scalar());
  EXPECT_EQ(NodeType::Scalar, n2.type());
}

// Test set_data copies data from another node
TEST_F(NodeTest_237, SetDataCopiesData_237) {
  node n1;
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("source");
  n1.set_tag("!tag");
  
  node n2;
  n2.set_data(n1);
  
  EXPECT_EQ(NodeType::Scalar, n2.type());
  EXPECT_EQ("source", n2.scalar());
}

// Test equals with matching scalar
TEST_F(NodeTest_237, EqualsMatchingScalar_237) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");
  
  EXPECT_TRUE(n.equals(std::string("hello"), pMemory));
}

// Test equals with non-matching scalar
TEST_F(NodeTest_237, EqualsNonMatchingScalar_237) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");
  
  EXPECT_FALSE(n.equals(std::string("world"), pMemory));
}

// Test equals with const char*
TEST_F(NodeTest_237, EqualsConstCharPtr_237) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("test");
  
  EXPECT_TRUE(n.equals("test", pMemory));
}

// Test equals with non-matching const char*
TEST_F(NodeTest_237, EqualsNonMatchingConstCharPtr_237) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("test");
  
  EXPECT_FALSE(n.equals("other", pMemory));
}

// Test empty map size
TEST_F(NodeTest_237, EmptyMapSize_237) {
  node n;
  n.set_type(NodeType::Map);
  EXPECT_EQ(0u, n.size());
}

// Test empty map begin equals end
TEST_F(NodeTest_237, EmptyMapBeginEqualsEnd_237) {
  node n;
  n.set_type(NodeType::Map);
  EXPECT_EQ(n.begin(), n.end());
}

// Test get with node key
TEST_F(NodeTest_237, MapGetWithNodeKey_237) {
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
TEST_F(NodeTest_237, MapRemoveWithNodeKey_237) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_type(NodeType::Scalar);
  key.set_scalar("nodekey");
  
  node& value = pMemory->create_node();
  value.set_type(NodeType::Scalar);
  value.set_scalar("nodevalue");
  
  n.insert(key, value, pMemory);
  
  bool removed = n.remove(key, pMemory);
  EXPECT_TRUE(removed);
}

// Test changing type resets content
TEST_F(NodeTest_237, ChangeTypeFromScalarToSequence_237) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");
  
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
  EXPECT_EQ(0u, n.size());
}

// Test force_insert on map
TEST_F(NodeTest_237, ForceInsertOnMap_237) {
  node n;
  n.set_type(NodeType::Map);
  
  n.force_insert(std::string("key1"), std::string("val1"), pMemory);
  EXPECT_EQ(1u, n.size());
}

// Test adding dependency (should not crash)
TEST_F(NodeTest_237, AddDependencyDoesNotCrash_237) {
  node n1;
  node n2;
  EXPECT_NO_THROW(n1.add_dependency(n2));
}

// Test set_null after being a scalar
TEST_F(NodeTest_237, SetNullAfterScalar_237) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("value");
  n.set_null();
  EXPECT_EQ(NodeType::Null, n.type());
}

// Test multiple inserts into a map
TEST_F(NodeTest_237, MapMultipleInserts_237) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key1 = pMemory->create_node();
  key1.set_type(NodeType::Scalar);
  key1.set_scalar("k1");
  node& val1 = pMemory->create_node();
  val1.set_type(NodeType::Scalar);
  val1.set_scalar("v1");
  n.insert(key1, val1, pMemory);
  
  node& key2 = pMemory->create_node();
  key2.set_type(NodeType::Scalar);
  key2.set_scalar("k2");
  node& val2 = pMemory->create_node();
  val2.set_type(NodeType::Scalar);
  val2.set_scalar("v2");
  n.insert(key2, val2, pMemory);
  
  EXPECT_EQ(2u, n.size());
  
  node* r1 = n.get(std::string("k1"), pMemory);
  EXPECT_NE(nullptr, r1);
  EXPECT_EQ("v1", r1->scalar());
  
  node* r2 = n.get(std::string("k2"), pMemory);
  EXPECT_NE(nullptr, r2);
  EXPECT_EQ("v2", r2->scalar());
}

// Test scalar with special characters
TEST_F(NodeTest_237, ScalarWithSpecialCharacters_237) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello\nworld\ttab");
  EXPECT_EQ("hello\nworld\ttab", n.scalar());
}

// Test scalar with unicode-like content
TEST_F(NodeTest_237, ScalarWithUnicodeContent_237) {
  node n;
  n.set_type(NodeType::Scalar);
  std::string unicode_str = u8"日本語テスト";
  n.set_scalar(unicode_str);
  EXPECT_EQ(unicode_str, n.scalar());
}

// Test default mark values
TEST_F(NodeTest_237, DefaultMarkValues_237) {
  node n;
  const Mark& m = n.mark();
  // Default mark should have line and column at 0 or some default
  // This is observable behavior
  EXPECT_GE(m.line, 0);
  EXPECT_GE(m.column, 0);
}

}  // namespace detail
}  // namespace YAML
