#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/type.h"
#include "yaml-cpp/emitterstyle.h"
#include "yaml-cpp/mark.h"

#include <string>
#include <memory>

namespace YAML {
namespace detail {

class NodeTest_236 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = std::make_shared<memory_holder>();
    // Use create_node from memory_holder if available, or just shared_memory_holder
    mem = shared_memory_holder(pMemory);
  }

  std::shared_ptr<memory_holder> pMemory;
  shared_memory_holder mem;
};

// Test that a node is equal to itself
TEST_F(NodeTest_236, NodeIsSelf_236) {
  node n;
  EXPECT_TRUE(n.is(n));
}

// Test that two different nodes are not the same
TEST_F(NodeTest_236, TwoDifferentNodesAreNotSame_236) {
  node n1;
  node n2;
  EXPECT_FALSE(n1.is(n2));
}

// Test ref() returns non-null
TEST_F(NodeTest_236, RefReturnsNonNull_236) {
  node n;
  EXPECT_NE(nullptr, n.ref());
}

// Test default node type
TEST_F(NodeTest_236, DefaultTypeIsUndefined_236) {
  node n;
  EXPECT_EQ(NodeType::Undefined, n.type());
}

// Test is_defined on default node
TEST_F(NodeTest_236, DefaultNodeIsNotDefined_236) {
  node n;
  EXPECT_FALSE(n.is_defined());
}

// Test mark_defined makes node defined
TEST_F(NodeTest_236, MarkDefinedMakesNodeDefined_236) {
  node n;
  n.mark_defined();
  EXPECT_TRUE(n.is_defined());
}

// Test set_type to Scalar
TEST_F(NodeTest_236, SetTypeScalar_236) {
  node n;
  n.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, n.type());
}

// Test set_type to Sequence
TEST_F(NodeTest_236, SetTypeSequence_236) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
}

// Test set_type to Map
TEST_F(NodeTest_236, SetTypeMap_236) {
  node n;
  n.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, n.type());
}

// Test set_null sets type to Null
TEST_F(NodeTest_236, SetNullSetsTypeNull_236) {
  node n;
  n.set_null();
  EXPECT_EQ(NodeType::Null, n.type());
}

// Test set_scalar and scalar retrieval
TEST_F(NodeTest_236, SetAndGetScalar_236) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");
  EXPECT_EQ("hello", n.scalar());
}

// Test set_scalar with empty string
TEST_F(NodeTest_236, SetScalarEmpty_236) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("");
  EXPECT_EQ("", n.scalar());
}

// Test set_tag and tag retrieval
TEST_F(NodeTest_236, SetAndGetTag_236) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_tag("!mytag");
  EXPECT_EQ("!mytag", n.tag());
}

// Test set_tag with empty tag
TEST_F(NodeTest_236, SetEmptyTag_236) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_tag("");
  EXPECT_EQ("", n.tag());
}

// Test set_style and style retrieval
TEST_F(NodeTest_236, SetAndGetStyleDefault_236) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, n.style());
}

// Test set_style to Flow
TEST_F(NodeTest_236, SetAndGetStyleFlow_236) {
  node n;
  n.set_type(NodeType::Sequence);
  n.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, n.style());
}

// Test set_style to Block
TEST_F(NodeTest_236, SetAndGetStyleBlock_236) {
  node n;
  n.set_type(NodeType::Sequence);
  n.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, n.style());
}

// Test set_mark and mark retrieval
TEST_F(NodeTest_236, SetAndGetMark_236) {
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

// Test size of empty sequence
TEST_F(NodeTest_236, EmptySequenceSize_236) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(0u, n.size());
}

// Test push_back increases size
TEST_F(NodeTest_236, PushBackIncreasesSize_236) {
  node n;
  n.set_type(NodeType::Sequence);
  
  node child;
  child.set_type(NodeType::Scalar);
  child.set_scalar("value1");
  
  n.push_back(child, mem);
  EXPECT_EQ(1u, n.size());
}

// Test push_back multiple elements
TEST_F(NodeTest_236, PushBackMultipleElements_236) {
  node n;
  n.set_type(NodeType::Sequence);
  
  node child1;
  child1.set_type(NodeType::Scalar);
  child1.set_scalar("v1");
  
  node child2;
  child2.set_type(NodeType::Scalar);
  child2.set_scalar("v2");
  
  n.push_back(child1, mem);
  n.push_back(child2, mem);
  EXPECT_EQ(2u, n.size());
}

// Test begin == end for empty sequence
TEST_F(NodeTest_236, BeginEqualsEndForEmptySequence_236) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_TRUE(n.begin() == n.end());
}

// Test begin != end for non-empty sequence
TEST_F(NodeTest_236, BeginNotEqualsEndForNonEmptySequence_236) {
  node n;
  n.set_type(NodeType::Sequence);
  
  node child;
  child.set_type(NodeType::Scalar);
  child.set_scalar("value");
  
  n.push_back(child, mem);
  EXPECT_FALSE(n.begin() == n.end());
}

// Test empty map size
TEST_F(NodeTest_236, EmptyMapSize_236) {
  node n;
  n.set_type(NodeType::Map);
  EXPECT_EQ(0u, n.size());
}

// Test insert into map
TEST_F(NodeTest_236, InsertIntoMap_236) {
  node n;
  n.set_type(NodeType::Map);
  
  node key;
  key.set_type(NodeType::Scalar);
  key.set_scalar("key1");
  
  node value;
  value.set_type(NodeType::Scalar);
  value.set_scalar("value1");
  
  n.insert(key, value, mem);
  EXPECT_EQ(1u, n.size());
}

// Test get from map with node key
TEST_F(NodeTest_236, GetFromMapWithNodeKey_236) {
  node n;
  n.set_type(NodeType::Map);
  
  node key;
  key.set_type(NodeType::Scalar);
  key.set_scalar("mykey");
  
  node value;
  value.set_type(NodeType::Scalar);
  value.set_scalar("myvalue");
  
  n.insert(key, value, mem);
  
  node* result = n.get(key, mem);
  EXPECT_NE(nullptr, result);
}

// Test get from map with string key
TEST_F(NodeTest_236, GetFromMapWithStringKey_236) {
  node n;
  n.set_type(NodeType::Map);
  
  node key;
  key.set_type(NodeType::Scalar);
  key.set_scalar("strkey");
  
  node value;
  value.set_type(NodeType::Scalar);
  value.set_scalar("strvalue");
  
  n.insert(key, value, mem);
  
  node* result = n.get(std::string("strkey"), mem);
  EXPECT_NE(nullptr, result);
}

// Test get non-existent key returns null
TEST_F(NodeTest_236, GetNonExistentKeyReturnsNull_236) {
  node n;
  n.set_type(NodeType::Map);
  
  node* result = n.get(std::string("nonexistent"), mem);
  EXPECT_EQ(nullptr, result);
}

// Test remove from map with node key
TEST_F(NodeTest_236, RemoveFromMapWithNodeKey_236) {
  node n;
  n.set_type(NodeType::Map);
  
  node key;
  key.set_type(NodeType::Scalar);
  key.set_scalar("removekey");
  
  node value;
  value.set_type(NodeType::Scalar);
  value.set_scalar("removeval");
  
  n.insert(key, value, mem);
  EXPECT_EQ(1u, n.size());
  
  bool removed = n.remove(key, mem);
  EXPECT_TRUE(removed);
}

// Test remove non-existent key
TEST_F(NodeTest_236, RemoveNonExistentKey_236) {
  node n;
  n.set_type(NodeType::Map);
  
  node key;
  key.set_type(NodeType::Scalar);
  key.set_scalar("nokey");
  
  bool removed = n.remove(key, mem);
  EXPECT_FALSE(removed);
}

// Test remove with string key
TEST_F(NodeTest_236, RemoveWithStringKey_236) {
  node n;
  n.set_type(NodeType::Map);
  
  node key;
  key.set_type(NodeType::Scalar);
  key.set_scalar("toremove");
  
  node value;
  value.set_type(NodeType::Scalar);
  value.set_scalar("val");
  
  n.insert(key, value, mem);
  
  bool removed = n.remove(std::string("toremove"), mem);
  EXPECT_TRUE(removed);
}

// Test set_ref makes nodes share same ref
TEST_F(NodeTest_236, SetRefMakesNodesShareRef_236) {
  node n1;
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("original");
  
  node n2;
  n2.set_ref(n1);
  
  EXPECT_TRUE(n2.is(n1));
  EXPECT_EQ("original", n2.scalar());
}

// Test set_data copies data but not identity
TEST_F(NodeTest_236, SetDataCopiesData_236) {
  node n1;
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("source");
  
  node n2;
  n2.set_data(n1);
  
  EXPECT_FALSE(n2.is(n1));
  EXPECT_EQ(NodeType::Scalar, n2.type());
  EXPECT_EQ("source", n2.scalar());
}

// Test equals with matching scalar
TEST_F(NodeTest_236, EqualsWithMatchingScalar_236) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("test");
  
  EXPECT_TRUE(n.equals(std::string("test"), mem));
}

// Test equals with non-matching scalar
TEST_F(NodeTest_236, EqualsWithNonMatchingScalar_236) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("test");
  
  EXPECT_FALSE(n.equals(std::string("other"), mem));
}

// Test equals with const char*
TEST_F(NodeTest_236, EqualsWithConstCharPtr_236) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");
  
  EXPECT_TRUE(n.equals("hello", mem));
  EXPECT_FALSE(n.equals("world", mem));
}

// Test add_dependency doesn't change node identity or type
TEST_F(NodeTest_236, AddDependencyDoesNotChangeNode_236) {
  node n1;
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("main");
  
  node n2;
  n2.set_type(NodeType::Scalar);
  n2.set_scalar("dep");
  
  n1.add_dependency(n2);
  EXPECT_EQ(NodeType::Scalar, n1.type());
  EXPECT_EQ("main", n1.scalar());
}

// Test changing type from Scalar to Sequence
TEST_F(NodeTest_236, ChangeTypeFromScalarToSequence_236) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("value");
  EXPECT_EQ(NodeType::Scalar, n.type());
  
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
}

// Test set_null after scalar
TEST_F(NodeTest_236, SetNullAfterScalar_236) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("value");
  
  n.set_null();
  EXPECT_EQ(NodeType::Null, n.type());
}

// Test default mark is zero
TEST_F(NodeTest_236, DefaultMarkIsZero_236) {
  node n;
  EXPECT_EQ(0, n.mark().line);
  EXPECT_EQ(0, n.mark().column);
  EXPECT_EQ(0, n.mark().pos);
}

// Test force_insert into map
TEST_F(NodeTest_236, ForceInsertIntoMap_236) {
  node n;
  n.set_type(NodeType::Map);
  
  n.force_insert(std::string("fkey"), std::string("fval"), mem);
  EXPECT_EQ(1u, n.size());
}

// Test force_insert allows duplicate keys (forced)
TEST_F(NodeTest_236, ForceInsertDuplicateKeys_236) {
  node n;
  n.set_type(NodeType::Map);
  
  n.force_insert(std::string("key"), std::string("val1"), mem);
  n.force_insert(std::string("key"), std::string("val2"), mem);
  EXPECT_EQ(2u, n.size());
}

// Test overwriting scalar value
TEST_F(NodeTest_236, OverwriteScalarValue_236) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("first");
  EXPECT_EQ("first", n.scalar());
  
  n.set_scalar("second");
  EXPECT_EQ("second", n.scalar());
}

// Test overwriting tag
TEST_F(NodeTest_236, OverwriteTag_236) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_tag("!tag1");
  EXPECT_EQ("!tag1", n.tag());
  
  n.set_tag("!tag2");
  EXPECT_EQ("!tag2", n.tag());
}

}  // namespace detail
}  // namespace YAML
