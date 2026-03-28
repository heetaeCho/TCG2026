#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeTest_256 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = create_shared_memory();
  }

  shared_memory_holder pMemory;
};

// Test default construction - node should be undefined initially
TEST_F(NodeTest_256, DefaultConstruction_IsNotDefined_256) {
  node n;
  EXPECT_FALSE(n.is_defined());
}

// Test default type is Undefined
TEST_F(NodeTest_256, DefaultConstruction_TypeIsUndefined_256) {
  node n;
  EXPECT_EQ(NodeType::Undefined, n.type());
}

// Test mark_defined makes the node defined
TEST_F(NodeTest_256, MarkDefined_MakesNodeDefined_256) {
  node n;
  n.mark_defined();
  EXPECT_TRUE(n.is_defined());
}

// Test set_type to Null
TEST_F(NodeTest_256, SetTypeNull_TypeIsNull_256) {
  node n;
  n.set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, n.type());
}

// Test set_type to Scalar
TEST_F(NodeTest_256, SetTypeScalar_TypeIsScalar_256) {
  node n;
  n.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, n.type());
}

// Test set_type to Sequence
TEST_F(NodeTest_256, SetTypeSequence_TypeIsSequence_256) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
}

// Test set_type to Map
TEST_F(NodeTest_256, SetTypeMap_TypeIsMap_256) {
  node n;
  n.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, n.type());
}

// Test set_scalar and scalar retrieval
TEST_F(NodeTest_256, SetScalar_ReturnsCorrectScalar_256) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");
  EXPECT_EQ("hello", n.scalar());
}

// Test set_scalar with empty string
TEST_F(NodeTest_256, SetScalarEmpty_ReturnsEmptyString_256) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("");
  EXPECT_EQ("", n.scalar());
}

// Test set_tag and tag retrieval
TEST_F(NodeTest_256, SetTag_ReturnsCorrectTag_256) {
  node n;
  n.set_tag("!custom");
  EXPECT_EQ("!custom", n.tag());
}

// Test set_tag with empty string
TEST_F(NodeTest_256, SetTagEmpty_ReturnsEmptyTag_256) {
  node n;
  n.set_tag("");
  EXPECT_EQ("", n.tag());
}

// Test set_style and style retrieval
TEST_F(NodeTest_256, SetStyleBlock_ReturnsBlock_256) {
  node n;
  n.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, n.style());
}

TEST_F(NodeTest_256, SetStyleFlow_ReturnsFlow_256) {
  node n;
  n.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, n.style());
}

TEST_F(NodeTest_256, SetStyleDefault_ReturnsDefault_256) {
  node n;
  n.set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, n.style());
}

// Test set_null
TEST_F(NodeTest_256, SetNull_TypeIsNull_256) {
  node n;
  n.set_null();
  EXPECT_EQ(NodeType::Null, n.type());
}

// Test is() with same node
TEST_F(NodeTest_256, Is_SameNode_ReturnsTrue_256) {
  node n;
  EXPECT_TRUE(n.is(n));
}

// Test is() with different nodes
TEST_F(NodeTest_256, Is_DifferentNode_ReturnsFalse_256) {
  node n1;
  node n2;
  EXPECT_FALSE(n1.is(n2));
}

// Test ref() returns non-null
TEST_F(NodeTest_256, Ref_ReturnsNonNull_256) {
  node n;
  EXPECT_NE(nullptr, n.ref());
}

// Test size of empty sequence
TEST_F(NodeTest_256, EmptySequence_SizeIsZero_256) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(0u, n.size());
}

// Test push_back increases size
TEST_F(NodeTest_256, PushBack_IncreasesSize_256) {
  node n;
  n.set_type(NodeType::Sequence);
  
  node& child = pMemory->create_node();
  child.set_scalar("value");
  n.push_back(child, pMemory);
  
  EXPECT_EQ(1u, n.size());
}

// Test multiple push_backs
TEST_F(NodeTest_256, MultiplePushBacks_CorrectSize_256) {
  node n;
  n.set_type(NodeType::Sequence);
  
  node& child1 = pMemory->create_node();
  child1.set_scalar("v1");
  n.push_back(child1, pMemory);
  
  node& child2 = pMemory->create_node();
  child2.set_scalar("v2");
  n.push_back(child2, pMemory);
  
  node& child3 = pMemory->create_node();
  child3.set_scalar("v3");
  n.push_back(child3, pMemory);
  
  EXPECT_EQ(3u, n.size());
}

// Test begin/end on empty sequence
TEST_F(NodeTest_256, EmptySequence_BeginEqualsEnd_256) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_TRUE(n.begin() == n.end());
}

// Test begin/end on non-empty sequence
TEST_F(NodeTest_256, NonEmptySequence_BeginNotEqualsEnd_256) {
  node n;
  n.set_type(NodeType::Sequence);
  
  node& child = pMemory->create_node();
  child.set_scalar("val");
  n.push_back(child, pMemory);
  
  EXPECT_FALSE(n.begin() == n.end());
}

// Test map insert and size
TEST_F(NodeTest_256, MapInsert_IncreasesSize_256) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("key1");
  node& value = pMemory->create_node();
  value.set_scalar("value1");
  
  n.insert(key, value, pMemory);
  EXPECT_EQ(1u, n.size());
}

// Test empty map size
TEST_F(NodeTest_256, EmptyMap_SizeIsZero_256) {
  node n;
  n.set_type(NodeType::Map);
  EXPECT_EQ(0u, n.size());
}

// Test set_mark and mark retrieval
TEST_F(NodeTest_256, SetMark_ReturnsCorrectMark_256) {
  node n;
  Mark m;
  m.line = 5;
  m.column = 10;
  n.set_mark(m);
  
  const Mark& retrieved = n.mark();
  EXPECT_EQ(5, retrieved.line);
  EXPECT_EQ(10, retrieved.column);
}

// Test set_data copies data from another node
TEST_F(NodeTest_256, SetData_CopiesFromOtherNode_256) {
  node n1;
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("test_data");
  
  node n2;
  n2.set_data(n1);
  
  EXPECT_EQ(NodeType::Scalar, n2.type());
  EXPECT_EQ("test_data", n2.scalar());
}

// Test set_ref shares reference with another node
TEST_F(NodeTest_256, SetRef_SharesReference_256) {
  node n1;
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("shared");
  
  node n2;
  n2.set_ref(n1);
  
  EXPECT_EQ("shared", n2.scalar());
  EXPECT_EQ(NodeType::Scalar, n2.type());
}

// Test equals with matching scalar
TEST_F(NodeTest_256, Equals_MatchingScalar_ReturnsTrue_256) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");
  
  EXPECT_TRUE(n.equals(std::string("hello"), pMemory));
}

// Test equals with non-matching scalar
TEST_F(NodeTest_256, Equals_NonMatchingScalar_ReturnsFalse_256) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");
  
  EXPECT_FALSE(n.equals(std::string("world"), pMemory));
}

// Test equals with const char*
TEST_F(NodeTest_256, Equals_ConstCharStar_Matching_ReturnsTrue_256) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("test");
  
  EXPECT_TRUE(n.equals("test", pMemory));
}

// Test equals with const char* non-matching
TEST_F(NodeTest_256, Equals_ConstCharStar_NonMatching_ReturnsFalse_256) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("test");
  
  EXPECT_FALSE(n.equals("other", pMemory));
}

// Test get on map returns correct node
TEST_F(NodeTest_256, MapGet_ExistingKey_ReturnsNode_256) {
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

// Test get on map with non-existing key
TEST_F(NodeTest_256, MapGet_NonExistingKey_ReturnsNull_256) {
  node n;
  n.set_type(NodeType::Map);
  
  node* result = n.get(std::string("nonexistent"), pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test remove from map
TEST_F(NodeTest_256, MapRemove_ExistingKey_ReturnsTrue_256) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("key_to_remove");
  node& value = pMemory->create_node();
  value.set_scalar("val");
  
  n.insert(key, value, pMemory);
  
  bool removed = n.remove(std::string("key_to_remove"), pMemory);
  EXPECT_TRUE(removed);
}

// Test remove from map with non-existing key
TEST_F(NodeTest_256, MapRemove_NonExistingKey_ReturnsFalse_256) {
  node n;
  n.set_type(NodeType::Map);
  
  bool removed = n.remove(std::string("no_such_key"), pMemory);
  EXPECT_FALSE(removed);
}

// Test remove with node& key
TEST_F(NodeTest_256, MapRemoveByNodeRef_ExistingKey_ReturnsTrue_256) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("k");
  node& value = pMemory->create_node();
  value.set_scalar("v");
  
  n.insert(key, value, pMemory);
  
  bool removed = n.remove(key, pMemory);
  EXPECT_TRUE(removed);
}

// Test force_insert on map
TEST_F(NodeTest_256, ForceInsert_IncreasesSize_256) {
  node n;
  n.set_type(NodeType::Map);
  
  n.force_insert(std::string("fkey"), std::string("fval"), pMemory);
  EXPECT_EQ(1u, n.size());
}

// Test that after set_null, node type is Null and defined
TEST_F(NodeTest_256, SetNull_IsDefinedAndNull_256) {
  node n;
  n.set_null();
  EXPECT_EQ(NodeType::Null, n.type());
  EXPECT_TRUE(n.is_defined());
}

// Test overwriting scalar
TEST_F(NodeTest_256, OverwriteScalar_ReturnsNewValue_256) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("first");
  EXPECT_EQ("first", n.scalar());
  
  n.set_scalar("second");
  EXPECT_EQ("second", n.scalar());
}

// Test changing type from Scalar to Sequence
TEST_F(NodeTest_256, ChangeType_ScalarToSequence_256) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("val");
  
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
  EXPECT_EQ(0u, n.size());
}

// Test add_dependency (no crash, basic smoke test)
TEST_F(NodeTest_256, AddDependency_NoCrash_256) {
  node n1;
  node n2;
  EXPECT_NO_THROW(n1.add_dependency(n2));
}

// Test begin/end on empty map
TEST_F(NodeTest_256, EmptyMap_BeginEqualsEnd_256) {
  node n;
  n.set_type(NodeType::Map);
  EXPECT_TRUE(n.begin() == n.end());
}

// Test begin/end on non-empty map
TEST_F(NodeTest_256, NonEmptyMap_BeginNotEqualsEnd_256) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("k");
  node& value = pMemory->create_node();
  value.set_scalar("v");
  n.insert(key, value, pMemory);
  
  EXPECT_FALSE(n.begin() == n.end());
}

// Test get with node& key on map
TEST_F(NodeTest_256, MapGetByNodeRef_ExistingKey_ReturnsNode_256) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("nk");
  node& value = pMemory->create_node();
  value.set_scalar("nv");
  
  n.insert(key, value, pMemory);
  
  node* result = n.get(key, pMemory);
  EXPECT_NE(nullptr, result);
  EXPECT_EQ("nv", result->scalar());
}

}  // namespace detail
}  // namespace YAML
