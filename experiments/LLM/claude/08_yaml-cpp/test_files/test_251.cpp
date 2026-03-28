#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeTest_251 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = std::make_shared<memory>();
  }

  shared_memory_holder pMemory;
};

// Test default construction - node should not be defined initially
TEST_F(NodeTest_251, DefaultConstructionIsNotDefined_251) {
  node n;
  EXPECT_FALSE(n.is_defined());
}

// Test default construction - type should be Undefined
TEST_F(NodeTest_251, DefaultConstructionTypeUndefined_251) {
  node n;
  EXPECT_EQ(NodeType::Undefined, n.type());
}

// Test mark_defined makes the node defined
TEST_F(NodeTest_251, MarkDefinedMakesNodeDefined_251) {
  node n;
  n.mark_defined();
  EXPECT_TRUE(n.is_defined());
}

// Test set_scalar sets the scalar value and marks node defined
TEST_F(NodeTest_251, SetScalarSetsValue_251) {
  node n;
  n.set_scalar("hello");
  EXPECT_TRUE(n.is_defined());
  EXPECT_EQ("hello", n.scalar());
}

// Test set_scalar with empty string
TEST_F(NodeTest_251, SetScalarEmptyString_251) {
  node n;
  n.set_scalar("");
  EXPECT_TRUE(n.is_defined());
  EXPECT_EQ("", n.scalar());
}

// Test set_scalar overwrite
TEST_F(NodeTest_251, SetScalarOverwrite_251) {
  node n;
  n.set_scalar("first");
  EXPECT_EQ("first", n.scalar());
  n.set_scalar("second");
  EXPECT_EQ("second", n.scalar());
}

// Test set_null
TEST_F(NodeTest_251, SetNullSetsTypeNull_251) {
  node n;
  n.set_null();
  EXPECT_TRUE(n.is_defined());
  EXPECT_EQ(NodeType::Null, n.type());
}

// Test set_type to Sequence
TEST_F(NodeTest_251, SetTypeSequence_251) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
}

// Test set_type to Map
TEST_F(NodeTest_251, SetTypeMap_251) {
  node n;
  n.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, n.type());
}

// Test set_type to Scalar
TEST_F(NodeTest_251, SetTypeScalar_251) {
  node n;
  n.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, n.type());
}

// Test set_type to Null
TEST_F(NodeTest_251, SetTypeNull_251) {
  node n;
  n.set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, n.type());
}

// Test set_tag and tag
TEST_F(NodeTest_251, SetTagAndGetTag_251) {
  node n;
  n.set_tag("!mytag");
  EXPECT_EQ("!mytag", n.tag());
}

// Test set_tag with empty string
TEST_F(NodeTest_251, SetTagEmptyString_251) {
  node n;
  n.set_tag("");
  EXPECT_EQ("", n.tag());
}

// Test set_style
TEST_F(NodeTest_251, SetStyleFlow_251) {
  node n;
  n.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, n.style());
}

// Test set_style Block
TEST_F(NodeTest_251, SetStyleBlock_251) {
  node n;
  n.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, n.style());
}

// Test set_style Default
TEST_F(NodeTest_251, SetStyleDefault_251) {
  node n;
  n.set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, n.style());
}

// Test is() identity - same node
TEST_F(NodeTest_251, IsIdentitySameNode_251) {
  node n;
  EXPECT_TRUE(n.is(n));
}

// Test is() identity - different nodes
TEST_F(NodeTest_251, IsIdentityDifferentNodes_251) {
  node n1;
  node n2;
  EXPECT_FALSE(n1.is(n2));
}

// Test ref() returns non-null
TEST_F(NodeTest_251, RefReturnsNonNull_251) {
  node n;
  EXPECT_NE(nullptr, n.ref());
}

// Test set_mark
TEST_F(NodeTest_251, SetMarkAndGetMark_251) {
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

// Test size for empty sequence
TEST_F(NodeTest_251, SizeEmptySequence_251) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(0u, n.size());
}

// Test push_back increases size for sequence
TEST_F(NodeTest_251, PushBackIncreasesSize_251) {
  node n;
  n.set_type(NodeType::Sequence);
  
  node& child = pMemory->create_node();
  child.set_scalar("value1");
  
  n.push_back(child, pMemory);
  EXPECT_EQ(1u, n.size());
}

// Test push_back multiple elements
TEST_F(NodeTest_251, PushBackMultipleElements_251) {
  node n;
  n.set_type(NodeType::Sequence);
  
  node& child1 = pMemory->create_node();
  child1.set_scalar("value1");
  node& child2 = pMemory->create_node();
  child2.set_scalar("value2");
  node& child3 = pMemory->create_node();
  child3.set_scalar("value3");
  
  n.push_back(child1, pMemory);
  n.push_back(child2, pMemory);
  n.push_back(child3, pMemory);
  EXPECT_EQ(3u, n.size());
}

// Test insert into map
TEST_F(NodeTest_251, InsertIntoMap_251) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("key1");
  node& value = pMemory->create_node();
  value.set_scalar("value1");
  
  n.insert(key, value, pMemory);
  EXPECT_EQ(1u, n.size());
}

// Test get from map with string key
TEST_F(NodeTest_251, GetFromMapStringKey_251) {
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

// Test get from map - non-existent key returns null
TEST_F(NodeTest_251, GetNonExistentKeyReturnsNull_251) {
  node n;
  n.set_type(NodeType::Map);
  
  node* result = n.get(std::string("nonexistent"), pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test remove from map
TEST_F(NodeTest_251, RemoveFromMap_251) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("key1");
  node& value = pMemory->create_node();
  value.set_scalar("value1");
  
  n.insert(key, value, pMemory);
  EXPECT_EQ(1u, n.size());
  
  bool removed = n.remove(std::string("key1"), pMemory);
  EXPECT_TRUE(removed);
}

// Test remove non-existent key
TEST_F(NodeTest_251, RemoveNonExistentKey_251) {
  node n;
  n.set_type(NodeType::Map);
  
  bool removed = n.remove(std::string("nonexistent"), pMemory);
  EXPECT_FALSE(removed);
}

// Test set_data copies data from another node
TEST_F(NodeTest_251, SetDataCopiesFromAnotherNode_251) {
  node n1;
  n1.set_scalar("hello");
  n1.set_tag("!tag");
  
  node n2;
  n2.set_data(n1);
  
  EXPECT_TRUE(n2.is_defined());
  EXPECT_EQ("hello", n2.scalar());
  EXPECT_EQ("!tag", n2.tag());
}

// Test set_ref makes node share ref with another
TEST_F(NodeTest_251, SetRefSharesRef_251) {
  node n1;
  n1.set_scalar("shared_value");
  
  node n2;
  n2.set_ref(n1);
  
  EXPECT_EQ("shared_value", n2.scalar());
}

// Test equals with matching scalar
TEST_F(NodeTest_251, EqualsMatchingScalar_251) {
  node n;
  n.set_scalar("test");
  
  EXPECT_TRUE(n.equals(std::string("test"), pMemory));
}

// Test equals with non-matching scalar
TEST_F(NodeTest_251, EqualsNonMatchingScalar_251) {
  node n;
  n.set_scalar("test");
  
  EXPECT_FALSE(n.equals(std::string("other"), pMemory));
}

// Test equals with char* overload
TEST_F(NodeTest_251, EqualsCharPointer_251) {
  node n;
  n.set_scalar("hello");
  
  EXPECT_TRUE(n.equals("hello", pMemory));
  EXPECT_FALSE(n.equals("world", pMemory));
}

// Test begin/end iterators on empty sequence
TEST_F(NodeTest_251, BeginEndEmptySequence_251) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(n.begin(), n.end());
}

// Test begin/end iterators on non-empty sequence
TEST_F(NodeTest_251, BeginEndNonEmptySequence_251) {
  node n;
  n.set_type(NodeType::Sequence);
  
  node& child = pMemory->create_node();
  child.set_scalar("value");
  n.push_back(child, pMemory);
  
  EXPECT_NE(n.begin(), n.end());
}

// Test set_scalar with very long string
TEST_F(NodeTest_251, SetScalarLongString_251) {
  node n;
  std::string longStr(10000, 'x');
  n.set_scalar(longStr);
  EXPECT_EQ(longStr, n.scalar());
}

// Test set_scalar with special characters
TEST_F(NodeTest_251, SetScalarSpecialCharacters_251) {
  node n;
  std::string special = "line1\nline2\ttab\r\n\"quotes\"";
  n.set_scalar(special);
  EXPECT_EQ(special, n.scalar());
}

// Test set_scalar with unicode
TEST_F(NodeTest_251, SetScalarUnicode_251) {
  node n;
  std::string unicode = "こんにちは世界";
  n.set_scalar(unicode);
  EXPECT_EQ(unicode, n.scalar());
}

// Test force_insert into map
TEST_F(NodeTest_251, ForceInsertIntoMap_251) {
  node n;
  n.set_type(NodeType::Map);
  
  n.force_insert(std::string("key1"), std::string("value1"), pMemory);
  EXPECT_EQ(1u, n.size());
}

// Test add_dependency does not affect node behavior
TEST_F(NodeTest_251, AddDependencyDoesNotChangeType_251) {
  node n1;
  n1.set_scalar("main");
  
  node n2;
  n2.set_scalar("dep");
  
  NodeType::value typeBefore = n1.type();
  n1.add_dependency(n2);
  EXPECT_EQ(typeBefore, n1.type());
  EXPECT_EQ("main", n1.scalar());
}

// Test get with node key
TEST_F(NodeTest_251, GetWithNodeKey_251) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("nodekey");
  node& value = pMemory->create_node();
  value.set_scalar("nodevalue");
  
  n.insert(key, value, pMemory);
  
  node* result = n.get(key, pMemory);
  EXPECT_NE(nullptr, result);
  EXPECT_EQ("nodevalue", result->scalar());
}

// Test remove with node key
TEST_F(NodeTest_251, RemoveWithNodeKey_251) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("toremove");
  node& value = pMemory->create_node();
  value.set_scalar("val");
  
  n.insert(key, value, pMemory);
  EXPECT_EQ(1u, n.size());
  
  bool removed = n.remove(key, pMemory);
  EXPECT_TRUE(removed);
}

// Test changing type resets content
TEST_F(NodeTest_251, ChangeTypeFromScalarToSequence_251) {
  node n;
  n.set_scalar("value");
  EXPECT_EQ(NodeType::Scalar, n.type());
  
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
  EXPECT_EQ(0u, n.size());
}

// Test default mark
TEST_F(NodeTest_251, DefaultMark_251) {
  node n;
  // Default mark should have some initial values
  const Mark& m = n.mark();
  (void)m; // Just ensuring we can call it without crashing
}

// Test default tag is empty
TEST_F(NodeTest_251, DefaultTagEmpty_251) {
  node n;
  n.mark_defined();
  EXPECT_EQ("", n.tag());
}

}  // namespace detail
}  // namespace YAML
