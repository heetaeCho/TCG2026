#include "gtest/gtest.h"
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeTest_253 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory.reset(new Memory);
  }

  shared_memory_holder pMemory;
};

// Test default construction - node should not be defined initially
TEST_F(NodeTest_253, DefaultConstruction_IsNotDefined_253) {
  node n;
  EXPECT_FALSE(n.is_defined());
}

// Test default type is Undefined
TEST_F(NodeTest_253, DefaultConstruction_TypeIsUndefined_253) {
  node n;
  EXPECT_EQ(NodeType::Undefined, n.type());
}

// Test mark_defined makes node defined
TEST_F(NodeTest_253, MarkDefined_MakesNodeDefined_253) {
  node n;
  n.mark_defined();
  EXPECT_TRUE(n.is_defined());
}

// Test set_type to Scalar
TEST_F(NodeTest_253, SetType_Scalar_253) {
  node n;
  n.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, n.type());
  EXPECT_TRUE(n.is_defined());
}

// Test set_type to Sequence
TEST_F(NodeTest_253, SetType_Sequence_253) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
}

// Test set_type to Map
TEST_F(NodeTest_253, SetType_Map_253) {
  node n;
  n.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, n.type());
}

// Test set_type to Null
TEST_F(NodeTest_253, SetType_Null_253) {
  node n;
  n.set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, n.type());
}

// Test set_null
TEST_F(NodeTest_253, SetNull_TypeIsNull_253) {
  node n;
  n.set_null();
  EXPECT_EQ(NodeType::Null, n.type());
  EXPECT_TRUE(n.is_defined());
}

// Test set_scalar and scalar retrieval
TEST_F(NodeTest_253, SetScalar_ReturnsCorrectValue_253) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");
  EXPECT_EQ("hello", n.scalar());
}

// Test set_scalar with empty string
TEST_F(NodeTest_253, SetScalar_EmptyString_253) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("");
  EXPECT_EQ("", n.scalar());
}

// Test set_tag and tag retrieval
TEST_F(NodeTest_253, SetTag_ReturnsCorrectValue_253) {
  node n;
  n.mark_defined();
  n.set_tag("!mytag");
  EXPECT_EQ("!mytag", n.tag());
}

// Test set_tag with empty string
TEST_F(NodeTest_253, SetTag_EmptyString_253) {
  node n;
  n.mark_defined();
  n.set_tag("");
  EXPECT_EQ("", n.tag());
}

// Test set_style and style retrieval
TEST_F(NodeTest_253, SetStyle_Block_253) {
  node n;
  n.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, n.style());
}

TEST_F(NodeTest_253, SetStyle_Flow_253) {
  node n;
  n.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, n.style());
}

TEST_F(NodeTest_253, SetStyle_Default_253) {
  node n;
  n.set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, n.style());
}

// Test set_style marks node as defined
TEST_F(NodeTest_253, SetStyle_MarksNodeDefined_253) {
  node n;
  EXPECT_FALSE(n.is_defined());
  n.set_style(EmitterStyle::Block);
  EXPECT_TRUE(n.is_defined());
}

// Test set_mark
TEST_F(NodeTest_253, SetMark_ReturnsCorrectMark_253) {
  node n;
  Mark m;
  m.line = 5;
  m.column = 10;
  m.pos = 42;
  n.set_mark(m);
  const Mark& retrieved = n.mark();
  EXPECT_EQ(5, retrieved.line);
  EXPECT_EQ(10, retrieved.column);
  EXPECT_EQ(42, retrieved.pos);
}

// Test is() - same node
TEST_F(NodeTest_253, Is_SameNode_ReturnsTrue_253) {
  node n;
  EXPECT_TRUE(n.is(n));
}

// Test is() - different nodes
TEST_F(NodeTest_253, Is_DifferentNode_ReturnsFalse_253) {
  node n1;
  node n2;
  EXPECT_FALSE(n1.is(n2));
}

// Test ref() returns non-null
TEST_F(NodeTest_253, Ref_ReturnsNonNull_253) {
  node n;
  EXPECT_NE(nullptr, n.ref());
}

// Test size for empty sequence
TEST_F(NodeTest_253, Size_EmptySequence_ReturnsZero_253) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(0u, n.size());
}

// Test push_back and size for sequence
TEST_F(NodeTest_253, PushBack_IncreasesSize_253) {
  node n;
  n.set_type(NodeType::Sequence);
  
  node& child = pMemory->create_node();
  child.set_type(NodeType::Scalar);
  child.set_scalar("item1");
  
  n.push_back(child, pMemory);
  EXPECT_EQ(1u, n.size());
}

// Test push_back multiple items
TEST_F(NodeTest_253, PushBack_MultipleItems_253) {
  node n;
  n.set_type(NodeType::Sequence);
  
  node& child1 = pMemory->create_node();
  child1.set_type(NodeType::Scalar);
  child1.set_scalar("item1");
  
  node& child2 = pMemory->create_node();
  child2.set_type(NodeType::Scalar);
  child2.set_scalar("item2");
  
  n.push_back(child1, pMemory);
  n.push_back(child2, pMemory);
  EXPECT_EQ(2u, n.size());
}

// Test begin/end for empty sequence
TEST_F(NodeTest_253, BeginEnd_EmptySequence_AreEqual_253) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(n.begin(), n.end());
}

// Test size for empty map
TEST_F(NodeTest_253, Size_EmptyMap_ReturnsZero_253) {
  node n;
  n.set_type(NodeType::Map);
  EXPECT_EQ(0u, n.size());
}

// Test insert into map
TEST_F(NodeTest_253, Insert_IncreasesMapSize_253) {
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

// Test get from map with string key
TEST_F(NodeTest_253, Get_ExistingKey_ReturnsNode_253) {
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

// Test get from map with non-existing key
TEST_F(NodeTest_253, Get_NonExistingKey_ReturnsNull_253) {
  node n;
  n.set_type(NodeType::Map);
  
  node* result = n.get(std::string("nonexistent"), pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test remove from map
TEST_F(NodeTest_253, Remove_ExistingKey_ReturnsTrue_253) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_type(NodeType::Scalar);
  key.set_scalar("removekey");
  
  node& value = pMemory->create_node();
  value.set_type(NodeType::Scalar);
  value.set_scalar("removevalue");
  
  n.insert(key, value, pMemory);
  EXPECT_EQ(1u, n.size());
  
  bool removed = n.remove(std::string("removekey"), pMemory);
  EXPECT_TRUE(removed);
}

// Test remove non-existing key
TEST_F(NodeTest_253, Remove_NonExistingKey_ReturnsFalse_253) {
  node n;
  n.set_type(NodeType::Map);
  
  bool removed = n.remove(std::string("nonexistent"), pMemory);
  EXPECT_FALSE(removed);
}

// Test remove by node reference
TEST_F(NodeTest_253, Remove_ByNodeRef_ExistingKey_ReturnsTrue_253) {
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

// Test set_data copies data from another node
TEST_F(NodeTest_253, SetData_CopiesFromOtherNode_253) {
  node n1;
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("copied");
  n1.set_tag("!tag");
  
  node n2;
  n2.set_data(n1);
  
  EXPECT_EQ(NodeType::Scalar, n2.type());
  EXPECT_EQ("copied", n2.scalar());
  EXPECT_EQ("!tag", n2.tag());
}

// Test set_ref shares reference with another node
TEST_F(NodeTest_253, SetRef_SharesReference_253) {
  node n1;
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("shared");
  
  node n2;
  n2.set_ref(n1);
  
  EXPECT_EQ("shared", n2.scalar());
  EXPECT_EQ(NodeType::Scalar, n2.type());
}

// Test equals with matching scalar
TEST_F(NodeTest_253, Equals_MatchingScalar_ReturnsTrue_253) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("test");
  
  EXPECT_TRUE(n.equals(std::string("test"), pMemory));
}

// Test equals with non-matching scalar
TEST_F(NodeTest_253, Equals_NonMatchingScalar_ReturnsFalse_253) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("test");
  
  EXPECT_FALSE(n.equals(std::string("other"), pMemory));
}

// Test equals with const char*
TEST_F(NodeTest_253, Equals_ConstCharPtr_Matching_253) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");
  
  EXPECT_TRUE(n.equals("hello", pMemory));
}

// Test equals with const char* non-matching
TEST_F(NodeTest_253, Equals_ConstCharPtr_NonMatching_253) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");
  
  EXPECT_FALSE(n.equals("world", pMemory));
}

// Test force_insert into map
TEST_F(NodeTest_253, ForceInsert_AddsToMap_253) {
  node n;
  n.set_type(NodeType::Map);
  
  n.force_insert(std::string("key"), std::string("value"), pMemory);
  EXPECT_EQ(1u, n.size());
}

// Test changing type from Scalar to Sequence
TEST_F(NodeTest_253, ChangeType_ScalarToSequence_253) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("test");
  EXPECT_EQ(NodeType::Scalar, n.type());
  
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
  EXPECT_EQ(0u, n.size());
}

// Test add_dependency does not crash
TEST_F(NodeTest_253, AddDependency_DoesNotCrash_253) {
  node n1;
  node n2;
  n1.add_dependency(n2);
  // No crash, just verifying it can be called
  SUCCEED();
}

// Test get by node reference
TEST_F(NodeTest_253, Get_ByNodeRef_253) {
  node n;
  n.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_type(NodeType::Scalar);
  key.set_scalar("refkey");
  
  node& value = pMemory->create_node();
  value.set_type(NodeType::Scalar);
  value.set_scalar("refvalue");
  
  n.insert(key, value, pMemory);
  
  node* result = n.get(key, pMemory);
  EXPECT_NE(nullptr, result);
  EXPECT_EQ("refvalue", result->scalar());
}

// Test default style
TEST_F(NodeTest_253, DefaultStyle_IsDefault_253) {
  node n;
  n.mark_defined();
  EXPECT_EQ(EmitterStyle::Default, n.style());
}

// Test overwriting scalar
TEST_F(NodeTest_253, SetScalar_Overwrite_253) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("first");
  EXPECT_EQ("first", n.scalar());
  
  n.set_scalar("second");
  EXPECT_EQ("second", n.scalar());
}

// Test overwriting tag
TEST_F(NodeTest_253, SetTag_Overwrite_253) {
  node n;
  n.mark_defined();
  n.set_tag("!first");
  EXPECT_EQ("!first", n.tag());
  
  n.set_tag("!second");
  EXPECT_EQ("!second", n.tag());
}

// Test multiple push_back and iteration
TEST_F(NodeTest_253, PushBack_IterateSequence_253) {
  node n;
  n.set_type(NodeType::Sequence);
  
  for (int i = 0; i < 5; ++i) {
    node& child = pMemory->create_node();
    child.set_type(NodeType::Scalar);
    child.set_scalar(std::to_string(i));
    n.push_back(child, pMemory);
  }
  
  EXPECT_EQ(5u, n.size());
  
  int count = 0;
  for (auto it = n.begin(); it != n.end(); ++it) {
    ++count;
  }
  EXPECT_EQ(5, count);
}

}  // namespace detail
}  // namespace YAML
