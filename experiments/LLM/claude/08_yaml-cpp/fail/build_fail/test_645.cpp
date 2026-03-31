#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node_data.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeDataTest_645 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = std::make_shared<memory_holder>();
  }

  shared_memory_holder pMemory;
};

// Test default construction
TEST_F(NodeDataTest_645, DefaultConstruction_645) {
  node_data nd;
  EXPECT_FALSE(nd.is_defined());
  EXPECT_EQ(nd.type(), NodeType::Null);
  EXPECT_TRUE(nd.scalar().empty());
  EXPECT_TRUE(nd.tag().empty());
}

// Test set_null
TEST_F(NodeDataTest_645, SetNull_645) {
  node_data nd;
  nd.set_null();
  EXPECT_TRUE(nd.is_defined());
  EXPECT_EQ(nd.type(), NodeType::Null);
}

// Test mark_defined
TEST_F(NodeDataTest_645, MarkDefined_645) {
  node_data nd;
  EXPECT_FALSE(nd.is_defined());
  nd.mark_defined();
  EXPECT_TRUE(nd.is_defined());
}

// Test set_type to Scalar
TEST_F(NodeDataTest_645, SetTypeScalar_645) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  EXPECT_TRUE(nd.is_defined());
  EXPECT_EQ(nd.type(), NodeType::Scalar);
}

// Test set_type to Sequence
TEST_F(NodeDataTest_645, SetTypeSequence_645) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  EXPECT_TRUE(nd.is_defined());
  EXPECT_EQ(nd.type(), NodeType::Sequence);
}

// Test set_type to Map
TEST_F(NodeDataTest_645, SetTypeMap_645) {
  node_data nd;
  nd.set_type(NodeType::Map);
  EXPECT_TRUE(nd.is_defined());
  EXPECT_EQ(nd.type(), NodeType::Map);
}

// Test set_type to Null
TEST_F(NodeDataTest_645, SetTypeNull_645) {
  node_data nd;
  nd.set_type(NodeType::Null);
  EXPECT_TRUE(nd.is_defined());
  EXPECT_EQ(nd.type(), NodeType::Null);
}

// Test set_type to Undefined resets
TEST_F(NodeDataTest_645, SetTypeUndefined_645) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  EXPECT_EQ(nd.type(), NodeType::Scalar);
  nd.set_type(NodeType::Undefined);
  EXPECT_FALSE(nd.is_defined());
  EXPECT_EQ(nd.type(), NodeType::Undefined);
}

// Test set_tag
TEST_F(NodeDataTest_645, SetTag_645) {
  node_data nd;
  nd.set_tag("my_tag");
  EXPECT_EQ(nd.tag(), "my_tag");
}

// Test set_tag with empty string
TEST_F(NodeDataTest_645, SetTagEmpty_645) {
  node_data nd;
  nd.set_tag("");
  EXPECT_EQ(nd.tag(), "");
}

// Test set_scalar
TEST_F(NodeDataTest_645, SetScalar_645) {
  node_data nd;
  nd.set_scalar("hello");
  EXPECT_EQ(nd.scalar(), "hello");
  EXPECT_TRUE(nd.is_defined());
  EXPECT_EQ(nd.type(), NodeType::Scalar);
}

// Test set_scalar with empty string
TEST_F(NodeDataTest_645, SetScalarEmpty_645) {
  node_data nd;
  nd.set_scalar("");
  EXPECT_EQ(nd.scalar(), "");
  EXPECT_EQ(nd.type(), NodeType::Scalar);
}

// Test set_style
TEST_F(NodeDataTest_645, SetStyleDefault_645) {
  node_data nd;
  nd.set_style(EmitterStyle::Default);
  EXPECT_EQ(nd.style(), EmitterStyle::Default);
}

TEST_F(NodeDataTest_645, SetStyleBlock_645) {
  node_data nd;
  nd.set_style(EmitterStyle::Block);
  EXPECT_EQ(nd.style(), EmitterStyle::Block);
}

TEST_F(NodeDataTest_645, SetStyleFlow_645) {
  node_data nd;
  nd.set_style(EmitterStyle::Flow);
  EXPECT_EQ(nd.style(), EmitterStyle::Flow);
}

// Test set_mark
TEST_F(NodeDataTest_645, SetMark_645) {
  node_data nd;
  Mark m;
  m.line = 5;
  m.column = 10;
  m.pos = 42;
  nd.set_mark(m);
  EXPECT_EQ(nd.mark().line, 5);
  EXPECT_EQ(nd.mark().column, 10);
  EXPECT_EQ(nd.mark().pos, 42);
}

// Test empty_scalar static method
TEST_F(NodeDataTest_645, EmptyScalar_645) {
  const std::string& es = node_data::empty_scalar();
  EXPECT_TRUE(es.empty());
}

// Test size for null node
TEST_F(NodeDataTest_645, SizeNull_645) {
  node_data nd;
  nd.set_null();
  EXPECT_EQ(nd.size(), 0u);
}

// Test size for scalar node
TEST_F(NodeDataTest_645, SizeScalar_645) {
  node_data nd;
  nd.set_scalar("test");
  EXPECT_EQ(nd.size(), 0u);
}

// Test size for empty sequence
TEST_F(NodeDataTest_645, SizeEmptySequence_645) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  EXPECT_EQ(nd.size(), 0u);
}

// Test push_back increases size for sequence
TEST_F(NodeDataTest_645, PushBackToSequence_645) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  
  node& n1 = pMemory->create_node();
  n1.set_scalar("value1");
  nd.push_back(n1, pMemory);
  
  EXPECT_EQ(nd.size(), 1u);
}

// Test push_back multiple elements
TEST_F(NodeDataTest_645, PushBackMultiple_645) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  
  node& n1 = pMemory->create_node();
  n1.set_scalar("value1");
  nd.push_back(n1, pMemory);
  
  node& n2 = pMemory->create_node();
  n2.set_scalar("value2");
  nd.push_back(n2, pMemory);
  
  node& n3 = pMemory->create_node();
  n3.set_scalar("value3");
  nd.push_back(n3, pMemory);
  
  EXPECT_EQ(nd.size(), 3u);
}

// Test empty map size
TEST_F(NodeDataTest_645, SizeEmptyMap_645) {
  node_data nd;
  nd.set_type(NodeType::Map);
  EXPECT_EQ(nd.size(), 0u);
}

// Test insert into map
TEST_F(NodeDataTest_645, InsertIntoMap_645) {
  node_data nd;
  nd.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("key1");
  node& value = pMemory->create_node();
  value.set_scalar("val1");
  
  nd.insert(key, value, pMemory);
  EXPECT_EQ(nd.size(), 1u);
}

// Test insert multiple into map
TEST_F(NodeDataTest_645, InsertMultipleIntoMap_645) {
  node_data nd;
  nd.set_type(NodeType::Map);
  
  node& key1 = pMemory->create_node();
  key1.set_scalar("key1");
  node& val1 = pMemory->create_node();
  val1.set_scalar("val1");
  nd.insert(key1, val1, pMemory);
  
  node& key2 = pMemory->create_node();
  key2.set_scalar("key2");
  node& val2 = pMemory->create_node();
  val2.set_scalar("val2");
  nd.insert(key2, val2, pMemory);
  
  EXPECT_EQ(nd.size(), 2u);
}

// Test get from map using node key
TEST_F(NodeDataTest_645, GetFromMapWithNodeKey_645) {
  node_data nd;
  nd.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("mykey");
  node& value = pMemory->create_node();
  value.set_scalar("myvalue");
  
  nd.insert(key, value, pMemory);
  
  // Get with the same key node should find it
  node* result = nd.get(key, pMemory);
  EXPECT_NE(result, nullptr);
}

// Test get with template key from map
TEST_F(NodeDataTest_645, GetWithTemplateKey_645) {
  node_data nd;
  nd.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("hello");
  node& value = pMemory->create_node();
  value.set_scalar("world");
  
  nd.insert(key, value, pMemory);
  
  node* result = nd.get(std::string("hello"), pMemory);
  EXPECT_NE(result, nullptr);
}

// Test get nonexistent key returns null
TEST_F(NodeDataTest_645, GetNonexistentKeyReturnsNull_645) {
  node_data nd;
  nd.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("existing");
  node& value = pMemory->create_node();
  value.set_scalar("val");
  
  nd.insert(key, value, pMemory);
  
  node* result = nd.get(std::string("nonexistent"), pMemory);
  EXPECT_EQ(result, nullptr);
}

// Test remove from map with template key
TEST_F(NodeDataTest_645, RemoveFromMap_645) {
  node_data nd;
  nd.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("toremove");
  node& value = pMemory->create_node();
  value.set_scalar("val");
  
  nd.insert(key, value, pMemory);
  EXPECT_EQ(nd.size(), 1u);
  
  bool removed = nd.remove(std::string("toremove"), pMemory);
  EXPECT_TRUE(removed);
}

// Test remove nonexistent key
TEST_F(NodeDataTest_645, RemoveNonexistentKey_645) {
  node_data nd;
  nd.set_type(NodeType::Map);
  
  bool removed = nd.remove(std::string("doesntexist"), pMemory);
  EXPECT_FALSE(removed);
}

// Test remove using node key
TEST_F(NodeDataTest_645, RemoveWithNodeKey_645) {
  node_data nd;
  nd.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("k");
  node& value = pMemory->create_node();
  value.set_scalar("v");
  
  nd.insert(key, value, pMemory);
  EXPECT_EQ(nd.size(), 1u);
  
  bool removed = nd.remove(key, pMemory);
  EXPECT_TRUE(removed);
}

// Test changing type from Sequence to Map
TEST_F(NodeDataTest_645, ChangeTypeSequenceToMap_645) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  EXPECT_EQ(nd.type(), NodeType::Sequence);
  
  nd.set_type(NodeType::Map);
  EXPECT_EQ(nd.type(), NodeType::Map);
}

// Test changing type from Map to Sequence
TEST_F(NodeDataTest_645, ChangeTypeMapToSequence_645) {
  node_data nd;
  nd.set_type(NodeType::Map);
  EXPECT_EQ(nd.type(), NodeType::Map);
  
  nd.set_type(NodeType::Sequence);
  EXPECT_EQ(nd.type(), NodeType::Sequence);
}

// Test changing type from Scalar to Null
TEST_F(NodeDataTest_645, ChangeTypeScalarToNull_645) {
  node_data nd;
  nd.set_scalar("data");
  EXPECT_EQ(nd.type(), NodeType::Scalar);
  
  nd.set_null();
  EXPECT_EQ(nd.type(), NodeType::Null);
}

// Test begin/end for empty sequence
TEST_F(NodeDataTest_645, BeginEndEmptySequence_645) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  EXPECT_EQ(nd.begin(), nd.end());
}

// Test begin/end for non-empty sequence
TEST_F(NodeDataTest_645, BeginEndNonEmptySequence_645) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  
  node& n1 = pMemory->create_node();
  n1.set_scalar("val");
  nd.push_back(n1, pMemory);
  
  EXPECT_NE(nd.begin(), nd.end());
}

// Test force_insert
TEST_F(NodeDataTest_645, ForceInsert_645) {
  node_data nd;
  nd.set_type(NodeType::Map);
  
  nd.force_insert(std::string("forcekey"), std::string("forceval"), pMemory);
  EXPECT_EQ(nd.size(), 1u);
}

// Test force_insert allows duplicates
TEST_F(NodeDataTest_645, ForceInsertDuplicateKeys_645) {
  node_data nd;
  nd.set_type(NodeType::Map);
  
  nd.force_insert(std::string("key"), std::string("val1"), pMemory);
  nd.force_insert(std::string("key"), std::string("val2"), pMemory);
  EXPECT_EQ(nd.size(), 2u);
}

// Test setting scalar overwrites previous scalar
TEST_F(NodeDataTest_645, SetScalarOverwrite_645) {
  node_data nd;
  nd.set_scalar("first");
  EXPECT_EQ(nd.scalar(), "first");
  
  nd.set_scalar("second");
  EXPECT_EQ(nd.scalar(), "second");
}

// Test set_tag overwrites previous tag
TEST_F(NodeDataTest_645, SetTagOverwrite_645) {
  node_data nd;
  nd.set_tag("tag1");
  EXPECT_EQ(nd.tag(), "tag1");
  
  nd.set_tag("tag2");
  EXPECT_EQ(nd.tag(), "tag2");
}

// Test that set_null clears scalar
TEST_F(NodeDataTest_645, SetNullAfterScalar_645) {
  node_data nd;
  nd.set_scalar("data");
  EXPECT_EQ(nd.type(), NodeType::Scalar);
  
  nd.set_null();
  EXPECT_EQ(nd.type(), NodeType::Null);
  EXPECT_TRUE(nd.is_defined());
}

// Test push_back on null type (should convert to sequence)
TEST_F(NodeDataTest_645, PushBackOnNullConvertsToSequence_645) {
  node_data nd;
  nd.set_null();
  
  node& n1 = pMemory->create_node();
  n1.set_scalar("val");
  nd.push_back(n1, pMemory);
  
  EXPECT_EQ(nd.type(), NodeType::Sequence);
  EXPECT_EQ(nd.size(), 1u);
}

// Test copy constructor is deleted (compile-time; just verify no crash creating two separate objects)
TEST_F(NodeDataTest_645, TwoSeparateInstances_645) {
  node_data nd1;
  node_data nd2;
  
  nd1.set_scalar("a");
  nd2.set_scalar("b");
  
  EXPECT_EQ(nd1.scalar(), "a");
  EXPECT_EQ(nd2.scalar(), "b");
}

// Test set_mark with null mark
TEST_F(NodeDataTest_645, SetMarkNull_645) {
  node_data nd;
  nd.set_mark(Mark::null_mark());
  // Just verify no crash and mark is retrievable
  nd.mark();
}

// Test empty_scalar returns same reference
TEST_F(NodeDataTest_645, EmptyScalarConsistent_645) {
  const std::string& es1 = node_data::empty_scalar();
  const std::string& es2 = node_data::empty_scalar();
  EXPECT_EQ(&es1, &es2);
}

}  // namespace detail
}  // namespace YAML
