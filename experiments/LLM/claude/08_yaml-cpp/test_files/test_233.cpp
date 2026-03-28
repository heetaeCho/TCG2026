#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/node_data.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeRefTest_233 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = shared_memory_holder(new memory);
  }

  shared_memory_holder pMemory;
};

// Test default construction - node_ref should be valid after construction
TEST_F(NodeRefTest_233, DefaultConstruction_233) {
  node_ref ref;
  EXPECT_FALSE(ref.is_defined());
  EXPECT_EQ(ref.type(), NodeType::Null);
}

// Test mark_defined
TEST_F(NodeRefTest_233, MarkDefined_233) {
  node_ref ref;
  EXPECT_FALSE(ref.is_defined());
  ref.mark_defined();
  EXPECT_TRUE(ref.is_defined());
}

// Test set_type and type
TEST_F(NodeRefTest_233, SetTypeSequence_233) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  EXPECT_EQ(ref.type(), NodeType::Sequence);
}

TEST_F(NodeRefTest_233, SetTypeMap_233) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  EXPECT_EQ(ref.type(), NodeType::Map);
}

TEST_F(NodeRefTest_233, SetTypeScalar_233) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  EXPECT_EQ(ref.type(), NodeType::Scalar);
}

TEST_F(NodeRefTest_233, SetTypeNull_233) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_type(NodeType::Null);
  EXPECT_EQ(ref.type(), NodeType::Null);
}

// Test set_null
TEST_F(NodeRefTest_233, SetNull_233) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("hello");
  ref.set_null();
  EXPECT_EQ(ref.type(), NodeType::Null);
}

// Test set_scalar and scalar
TEST_F(NodeRefTest_233, SetScalar_233) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("test_value");
  EXPECT_EQ(ref.scalar(), "test_value");
}

TEST_F(NodeRefTest_233, SetScalarEmpty_233) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("");
  EXPECT_EQ(ref.scalar(), "");
}

// Test set_tag and tag
TEST_F(NodeRefTest_233, SetTag_233) {
  node_ref ref;
  ref.set_tag("!mytag");
  EXPECT_EQ(ref.tag(), "!mytag");
}

TEST_F(NodeRefTest_233, SetTagEmpty_233) {
  node_ref ref;
  ref.set_tag("");
  EXPECT_EQ(ref.tag(), "");
}

// Test set_style and style
TEST_F(NodeRefTest_233, SetStyleFlow_233) {
  node_ref ref;
  ref.set_style(EmitterStyle::Flow);
  EXPECT_EQ(ref.style(), EmitterStyle::Flow);
}

TEST_F(NodeRefTest_233, SetStyleBlock_233) {
  node_ref ref;
  ref.set_style(EmitterStyle::Block);
  EXPECT_EQ(ref.style(), EmitterStyle::Block);
}

TEST_F(NodeRefTest_233, SetStyleDefault_233) {
  node_ref ref;
  ref.set_style(EmitterStyle::Default);
  EXPECT_EQ(ref.style(), EmitterStyle::Default);
}

// Test set_mark and mark
TEST_F(NodeRefTest_233, SetMark_233) {
  node_ref ref;
  Mark m;
  m.line = 5;
  m.column = 10;
  m.pos = 42;
  ref.set_mark(m);
  EXPECT_EQ(ref.mark().line, 5);
  EXPECT_EQ(ref.mark().column, 10);
  EXPECT_EQ(ref.mark().pos, 42);
}

// Test size for empty node
TEST_F(NodeRefTest_233, SizeEmptyNull_233) {
  node_ref ref;
  EXPECT_EQ(ref.size(), 0u);
}

// Test size for sequence
TEST_F(NodeRefTest_233, SizeSequence_233) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  node& n1 = pMemory->create_node();
  n1.set_scalar("item1");
  ref.push_back(n1, pMemory);
  EXPECT_EQ(ref.size(), 1u);
}

TEST_F(NodeRefTest_233, SizeSequenceMultiple_233) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  node& n1 = pMemory->create_node();
  n1.set_scalar("item1");
  node& n2 = pMemory->create_node();
  n2.set_scalar("item2");
  node& n3 = pMemory->create_node();
  n3.set_scalar("item3");
  ref.push_back(n1, pMemory);
  ref.push_back(n2, pMemory);
  ref.push_back(n3, pMemory);
  EXPECT_EQ(ref.size(), 3u);
}

// Test push_back on sequence
TEST_F(NodeRefTest_233, PushBackSequence_233) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  node& n1 = pMemory->create_node();
  n1.set_scalar("value1");
  ref.push_back(n1, pMemory);
  EXPECT_EQ(ref.size(), 1u);
}

// Test insert on map
TEST_F(NodeRefTest_233, InsertMap_233) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  node& key = pMemory->create_node();
  key.set_scalar("key1");
  node& value = pMemory->create_node();
  value.set_scalar("value1");
  ref.insert(key, value, pMemory);
  EXPECT_EQ(ref.size(), 1u);
}

// Test get with node key on map
TEST_F(NodeRefTest_233, GetNodeKeyFromMap_233) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  node& key = pMemory->create_node();
  key.set_scalar("mykey");
  node& value = pMemory->create_node();
  value.set_scalar("myvalue");
  ref.insert(key, value, pMemory);

  node* result = ref.get(key, pMemory);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->scalar(), "myvalue");
}

// Test get with non-existent key
TEST_F(NodeRefTest_233, GetNonExistentKey_233) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  node& key = pMemory->create_node();
  key.set_scalar("mykey");
  node& value = pMemory->create_node();
  value.set_scalar("myvalue");
  ref.insert(key, value, pMemory);

  node& otherKey = pMemory->create_node();
  otherKey.set_scalar("nonexistent");
  node* result = ref.get(otherKey, pMemory);
  EXPECT_EQ(result, nullptr);
}

// Test remove with node key from map
TEST_F(NodeRefTest_233, RemoveNodeKeyFromMap_233) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  node& key = pMemory->create_node();
  key.set_scalar("removekey");
  node& value = pMemory->create_node();
  value.set_scalar("removevalue");
  ref.insert(key, value, pMemory);
  EXPECT_EQ(ref.size(), 1u);

  bool removed = ref.remove(key, pMemory);
  EXPECT_TRUE(removed);
  EXPECT_EQ(ref.size(), 0u);
}

// Test remove non-existent key
TEST_F(NodeRefTest_233, RemoveNonExistentKey_233) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  node& key = pMemory->create_node();
  key.set_scalar("existingkey");
  node& value = pMemory->create_node();
  value.set_scalar("existingvalue");
  ref.insert(key, value, pMemory);

  node& otherKey = pMemory->create_node();
  otherKey.set_scalar("nonexistent");
  bool removed = ref.remove(otherKey, pMemory);
  EXPECT_FALSE(removed);
  EXPECT_EQ(ref.size(), 1u);
}

// Test remove from empty map
TEST_F(NodeRefTest_233, RemoveFromEmptyMap_233) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  node& key = pMemory->create_node();
  key.set_scalar("somekey");
  bool removed = ref.remove(key, pMemory);
  EXPECT_FALSE(removed);
}

// Test template get with string key
TEST_F(NodeRefTest_233, TemplateGetStringKey_233) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  node& key = pMemory->create_node();
  key.set_scalar("strkey");
  node& value = pMemory->create_node();
  value.set_scalar("strvalue");
  ref.insert(key, value, pMemory);

  node* result = ref.get(std::string("strkey"), pMemory);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->scalar(), "strvalue");
}

// Test template get with non-existent string key
TEST_F(NodeRefTest_233, TemplateGetNonExistentStringKey_233) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  node& key = pMemory->create_node();
  key.set_scalar("present");
  node& value = pMemory->create_node();
  value.set_scalar("val");
  ref.insert(key, value, pMemory);

  node* result = ref.get(std::string("absent"), pMemory);
  EXPECT_EQ(result, nullptr);
}

// Test template remove with string key
TEST_F(NodeRefTest_233, TemplateRemoveStringKey_233) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  node& key = pMemory->create_node();
  key.set_scalar("delkey");
  node& value = pMemory->create_node();
  value.set_scalar("delvalue");
  ref.insert(key, value, pMemory);
  EXPECT_EQ(ref.size(), 1u);

  bool removed = ref.remove(std::string("delkey"), pMemory);
  EXPECT_TRUE(removed);
  EXPECT_EQ(ref.size(), 0u);
}

// Test template remove with non-existent string key
TEST_F(NodeRefTest_233, TemplateRemoveNonExistentStringKey_233) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  node& key = pMemory->create_node();
  key.set_scalar("key1");
  node& value = pMemory->create_node();
  value.set_scalar("val1");
  ref.insert(key, value, pMemory);

  bool removed = ref.remove(std::string("nokey"), pMemory);
  EXPECT_FALSE(removed);
  EXPECT_EQ(ref.size(), 1u);
}

// Test set_data copies data from another node_ref
TEST_F(NodeRefTest_233, SetData_233) {
  node_ref ref1;
  ref1.set_type(NodeType::Scalar);
  ref1.set_scalar("shared_data");
  ref1.set_tag("!tag");

  node_ref ref2;
  ref2.set_data(ref1);
  EXPECT_EQ(ref2.scalar(), "shared_data");
  EXPECT_EQ(ref2.tag(), "!tag");
  EXPECT_EQ(ref2.type(), NodeType::Scalar);
}

// Test begin/end for empty sequence
TEST_F(NodeRefTest_233, BeginEndEmptySequence_233) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  EXPECT_EQ(ref.begin(), ref.end());
}

// Test begin/end for non-empty sequence
TEST_F(NodeRefTest_233, BeginEndNonEmptySequence_233) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  node& n1 = pMemory->create_node();
  n1.set_scalar("item");
  ref.push_back(n1, pMemory);
  EXPECT_NE(ref.begin(), ref.end());
}

// Test force_insert on map
TEST_F(NodeRefTest_233, ForceInsert_233) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  ref.force_insert(std::string("fkey"), std::string("fval"), pMemory);
  EXPECT_EQ(ref.size(), 1u);
}

// Test multiple insertions into map
TEST_F(NodeRefTest_233, MultipleMapInsertions_233) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node& k1 = pMemory->create_node();
  k1.set_scalar("k1");
  node& v1 = pMemory->create_node();
  v1.set_scalar("v1");
  ref.insert(k1, v1, pMemory);

  node& k2 = pMemory->create_node();
  k2.set_scalar("k2");
  node& v2 = pMemory->create_node();
  v2.set_scalar("v2");
  ref.insert(k2, v2, pMemory);

  node& k3 = pMemory->create_node();
  k3.set_scalar("k3");
  node& v3 = pMemory->create_node();
  v3.set_scalar("v3");
  ref.insert(k3, v3, pMemory);

  EXPECT_EQ(ref.size(), 3u);

  // Remove middle key
  bool removed = ref.remove(k2, pMemory);
  EXPECT_TRUE(removed);
  EXPECT_EQ(ref.size(), 2u);

  // Verify remaining keys
  EXPECT_NE(ref.get(k1, pMemory), nullptr);
  EXPECT_EQ(ref.get(k2, pMemory), nullptr);
  EXPECT_NE(ref.get(k3, pMemory), nullptr);
}

// Test remove all entries from map
TEST_F(NodeRefTest_233, RemoveAllEntries_233) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node& k1 = pMemory->create_node();
  k1.set_scalar("a");
  node& v1 = pMemory->create_node();
  v1.set_scalar("1");
  ref.insert(k1, v1, pMemory);

  node& k2 = pMemory->create_node();
  k2.set_scalar("b");
  node& v2 = pMemory->create_node();
  v2.set_scalar("2");
  ref.insert(k2, v2, pMemory);

  EXPECT_TRUE(ref.remove(k1, pMemory));
  EXPECT_TRUE(ref.remove(k2, pMemory));
  EXPECT_EQ(ref.size(), 0u);
}

// Test get with integer key (template version)
TEST_F(NodeRefTest_233, TemplateGetIntKey_233) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  node& n = pMemory->create_node();
  n.set_scalar("first");
  ref.push_back(n, pMemory);

  node* result = ref.get(0, pMemory);
  ASSERT_NE(result, nullptr);
}

// Test that double remove returns false
TEST_F(NodeRefTest_233, DoubleRemoveSameKey_233) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("dkey");
  node& value = pMemory->create_node();
  value.set_scalar("dval");
  ref.insert(key, value, pMemory);

  EXPECT_TRUE(ref.remove(key, pMemory));
  EXPECT_FALSE(ref.remove(key, pMemory));
}

// Test mark returns null mark by default
TEST_F(NodeRefTest_233, DefaultMark_233) {
  node_ref ref;
  Mark m = ref.mark();
  EXPECT_EQ(m.line, 0);
  EXPECT_EQ(m.column, 0);
  EXPECT_EQ(m.pos, 0);
}

// Test is_defined after setting type
TEST_F(NodeRefTest_233, IsDefinedAfterSetType_233) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  // set_type should mark the node as defined
  EXPECT_TRUE(ref.is_defined());
}

}  // namespace detail
}  // namespace YAML
