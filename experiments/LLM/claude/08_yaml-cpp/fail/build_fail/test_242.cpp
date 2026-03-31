#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeTest_242 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = create_shared_memory();
  }

  shared_memory_holder pMemory;
};

// Test default construction - node should exist but be undefined
TEST_F(NodeTest_242, DefaultConstruction_IsNotDefined_242) {
  node n;
  EXPECT_FALSE(n.is_defined());
}

// Test default type is Undefined
TEST_F(NodeTest_242, DefaultConstruction_TypeIsUndefined_242) {
  node n;
  EXPECT_EQ(NodeType::Undefined, n.type());
}

// Test tag on default node is empty
TEST_F(NodeTest_242, DefaultConstruction_TagIsEmpty_242) {
  node n;
  EXPECT_TRUE(n.tag().empty());
}

// Test scalar on default node is empty
TEST_F(NodeTest_242, DefaultConstruction_ScalarIsEmpty_242) {
  node n;
  EXPECT_TRUE(n.scalar().empty());
}

// Test set_tag and retrieve
TEST_F(NodeTest_242, SetTag_ReturnsCorrectTag_242) {
  node n;
  n.set_tag("!mytag");
  EXPECT_EQ("!mytag", n.tag());
}

// Test set_scalar and retrieve
TEST_F(NodeTest_242, SetScalar_ReturnsCorrectScalar_242) {
  node n;
  n.set_scalar("hello");
  EXPECT_EQ("hello", n.scalar());
}

// Test set_type to Scalar
TEST_F(NodeTest_242, SetTypeScalar_TypeIsScalar_242) {
  node n;
  n.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, n.type());
}

// Test set_type to Sequence
TEST_F(NodeTest_242, SetTypeSequence_TypeIsSequence_242) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
}

// Test set_type to Map
TEST_F(NodeTest_242, SetTypeMap_TypeIsMap_242) {
  node n;
  n.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, n.type());
}

// Test set_null sets type to Null
TEST_F(NodeTest_242, SetNull_TypeIsNull_242) {
  node n;
  n.set_null();
  EXPECT_EQ(NodeType::Null, n.type());
}

// Test mark_defined makes node defined
TEST_F(NodeTest_242, MarkDefined_IsDefinedReturnsTrue_242) {
  node n;
  n.mark_defined();
  EXPECT_TRUE(n.is_defined());
}

// Test is() with same node
TEST_F(NodeTest_242, Is_SameNode_ReturnsTrue_242) {
  node n;
  EXPECT_TRUE(n.is(n));
}

// Test is() with different node
TEST_F(NodeTest_242, Is_DifferentNode_ReturnsFalse_242) {
  node n1;
  node n2;
  EXPECT_FALSE(n1.is(n2));
}

// Test ref() returns non-null
TEST_F(NodeTest_242, Ref_ReturnsNonNull_242) {
  node n;
  EXPECT_NE(nullptr, n.ref());
}

// Test set_mark and retrieve mark
TEST_F(NodeTest_242, SetMark_ReturnsCorrectMark_242) {
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

// Test default style
TEST_F(NodeTest_242, DefaultStyle_242) {
  node n;
  // Default style should be the default EmitterStyle
  EmitterStyle::value s = n.style();
  // Just verify it doesn't crash and returns some valid value
  EXPECT_TRUE(s == EmitterStyle::Default || s == EmitterStyle::Block ||
              s == EmitterStyle::Flow);
}

// Test set_style
TEST_F(NodeTest_242, SetStyle_ReturnsCorrectStyle_242) {
  node n;
  n.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, n.style());
}

// Test set_style Block
TEST_F(NodeTest_242, SetStyleBlock_ReturnsBlock_242) {
  node n;
  n.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, n.style());
}

// Test size of default node is 0
TEST_F(NodeTest_242, DefaultNode_SizeIsZero_242) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(0u, n.size());
}

// Test push_back increases size for sequence
TEST_F(NodeTest_242, PushBack_IncreasesSize_242) {
  node seq;
  seq.set_type(NodeType::Sequence);
  
  node& child = pMemory->create_node();
  child.set_scalar("item1");
  
  seq.push_back(child, pMemory);
  EXPECT_EQ(1u, seq.size());
}

// Test push_back multiple items
TEST_F(NodeTest_242, PushBackMultiple_CorrectSize_242) {
  node seq;
  seq.set_type(NodeType::Sequence);
  
  node& child1 = pMemory->create_node();
  child1.set_scalar("item1");
  node& child2 = pMemory->create_node();
  child2.set_scalar("item2");
  node& child3 = pMemory->create_node();
  child3.set_scalar("item3");
  
  seq.push_back(child1, pMemory);
  seq.push_back(child2, pMemory);
  seq.push_back(child3, pMemory);
  EXPECT_EQ(3u, seq.size());
}

// Test begin == end for empty sequence
TEST_F(NodeTest_242, EmptySequence_BeginEqualsEnd_242) {
  node seq;
  seq.set_type(NodeType::Sequence);
  EXPECT_TRUE(seq.begin() == seq.end());
}

// Test set_data copies data from another node
TEST_F(NodeTest_242, SetData_CopiesFromOtherNode_242) {
  node n1;
  n1.set_scalar("copied");
  n1.set_tag("!tag");
  n1.set_type(NodeType::Scalar);
  
  node n2;
  n2.set_data(n1);
  
  EXPECT_EQ("copied", n2.scalar());
  EXPECT_EQ("!tag", n2.tag());
}

// Test equals with matching scalar
TEST_F(NodeTest_242, Equals_MatchingScalar_ReturnsTrue_242) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("test");
  
  EXPECT_TRUE(n.equals(std::string("test"), pMemory));
}

// Test equals with non-matching scalar
TEST_F(NodeTest_242, Equals_NonMatchingScalar_ReturnsFalse_242) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("test");
  
  EXPECT_FALSE(n.equals(std::string("other"), pMemory));
}

// Test equals with const char*
TEST_F(NodeTest_242, Equals_CString_MatchingScalar_ReturnsTrue_242) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");
  
  EXPECT_TRUE(n.equals("hello", pMemory));
}

// Test equals with const char* non-matching
TEST_F(NodeTest_242, Equals_CString_NonMatchingScalar_ReturnsFalse_242) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");
  
  EXPECT_FALSE(n.equals("world", pMemory));
}

// Test insert into map
TEST_F(NodeTest_242, Insert_IntoMap_IncreasesSize_242) {
  node map_node;
  map_node.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_type(NodeType::Scalar);
  key.set_scalar("key1");
  
  node& value = pMemory->create_node();
  value.set_type(NodeType::Scalar);
  value.set_scalar("value1");
  
  map_node.insert(key, value, pMemory);
  EXPECT_EQ(1u, map_node.size());
}

// Test get on map with string key
TEST_F(NodeTest_242, Get_ExistingKey_ReturnsNonNull_242) {
  node map_node;
  map_node.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_type(NodeType::Scalar);
  key.set_scalar("mykey");
  
  node& value = pMemory->create_node();
  value.set_type(NodeType::Scalar);
  value.set_scalar("myvalue");
  
  map_node.insert(key, value, pMemory);
  
  node* result = map_node.get(std::string("mykey"), pMemory);
  EXPECT_NE(nullptr, result);
}

// Test get on map with non-existing key
TEST_F(NodeTest_242, Get_NonExistingKey_ReturnsNull_242) {
  node map_node;
  map_node.set_type(NodeType::Map);
  
  node* result = map_node.get(std::string("nonexistent"), pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test remove from map
TEST_F(NodeTest_242, Remove_ExistingKey_ReturnsTrue_242) {
  node map_node;
  map_node.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_type(NodeType::Scalar);
  key.set_scalar("removekey");
  
  node& value = pMemory->create_node();
  value.set_type(NodeType::Scalar);
  value.set_scalar("removevalue");
  
  map_node.insert(key, value, pMemory);
  
  bool removed = map_node.remove(std::string("removekey"), pMemory);
  EXPECT_TRUE(removed);
}

// Test remove non-existing key
TEST_F(NodeTest_242, Remove_NonExistingKey_ReturnsFalse_242) {
  node map_node;
  map_node.set_type(NodeType::Map);
  
  bool removed = map_node.remove(std::string("nonexistent"), pMemory);
  EXPECT_FALSE(removed);
}

// Test set_tag with empty string
TEST_F(NodeTest_242, SetTag_EmptyString_242) {
  node n;
  n.set_tag("");
  EXPECT_TRUE(n.tag().empty());
}

// Test set_scalar with empty string
TEST_F(NodeTest_242, SetScalar_EmptyString_242) {
  node n;
  n.set_scalar("");
  EXPECT_TRUE(n.scalar().empty());
}

// Test overwriting tag
TEST_F(NodeTest_242, SetTag_OverwriteTag_242) {
  node n;
  n.set_tag("!first");
  EXPECT_EQ("!first", n.tag());
  n.set_tag("!second");
  EXPECT_EQ("!second", n.tag());
}

// Test overwriting scalar
TEST_F(NodeTest_242, SetScalar_OverwriteScalar_242) {
  node n;
  n.set_scalar("first");
  EXPECT_EQ("first", n.scalar());
  n.set_scalar("second");
  EXPECT_EQ("second", n.scalar());
}

// Test set_type changes type from Sequence to Map
TEST_F(NodeTest_242, SetType_ChangeFromSequenceToMap_242) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
  n.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, n.type());
}

// Test add_dependency doesn't crash
TEST_F(NodeTest_242, AddDependency_NoCrash_242) {
  node n1;
  node n2;
  EXPECT_NO_THROW(n1.add_dependency(n2));
}

// Test set_ref makes nodes share the same ref
TEST_F(NodeTest_242, SetRef_SharesRef_242) {
  node n1;
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("shared");
  
  node n2;
  n2.set_ref(n1);
  
  EXPECT_EQ("shared", n2.scalar());
  EXPECT_EQ(NodeType::Scalar, n2.type());
}

// Test set_null after setting scalar
TEST_F(NodeTest_242, SetNull_AfterScalar_TypeBecomesNull_242) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("value");
  n.set_null();
  EXPECT_EQ(NodeType::Null, n.type());
}

// Test default mark values
TEST_F(NodeTest_242, DefaultMark_HasDefaultValues_242) {
  node n;
  const Mark& m = n.mark();
  // Default mark values - just check it doesn't crash
  (void)m.line;
  (void)m.column;
  (void)m.pos;
}

// Test equals with empty string
TEST_F(NodeTest_242, Equals_EmptyString_242) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("");
  
  EXPECT_TRUE(n.equals(std::string(""), pMemory));
}

// Test get with node key
TEST_F(NodeTest_242, Get_WithNodeKey_ExistingKey_242) {
  node map_node;
  map_node.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_type(NodeType::Scalar);
  key.set_scalar("nodekey");
  
  node& value = pMemory->create_node();
  value.set_type(NodeType::Scalar);
  value.set_scalar("nodevalue");
  
  map_node.insert(key, value, pMemory);
  
  node* result = map_node.get(key, pMemory);
  EXPECT_NE(nullptr, result);
}

// Test remove with node key
TEST_F(NodeTest_242, Remove_WithNodeKey_ExistingKey_ReturnsTrue_242) {
  node map_node;
  map_node.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_type(NodeType::Scalar);
  key.set_scalar("removekey");
  
  node& value = pMemory->create_node();
  value.set_type(NodeType::Scalar);
  value.set_scalar("removevalue");
  
  map_node.insert(key, value, pMemory);
  
  bool removed = map_node.remove(key, pMemory);
  EXPECT_TRUE(removed);
}

// Test size of map after multiple inserts
TEST_F(NodeTest_242, Map_MultipleInserts_CorrectSize_242) {
  node map_node;
  map_node.set_type(NodeType::Map);
  
  for (int i = 0; i < 5; ++i) {
    node& key = pMemory->create_node();
    key.set_type(NodeType::Scalar);
    key.set_scalar("key" + std::to_string(i));
    
    node& value = pMemory->create_node();
    value.set_type(NodeType::Scalar);
    value.set_scalar("value" + std::to_string(i));
    
    map_node.insert(key, value, pMemory);
  }
  
  EXPECT_EQ(5u, map_node.size());
}

}  // namespace detail
}  // namespace YAML
