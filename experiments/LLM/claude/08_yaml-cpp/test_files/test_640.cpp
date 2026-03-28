#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node_data.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeDataTest_640 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = std::make_shared<memory_holder>();
  }

  shared_memory_holder pMemory;
};

// Test default construction state
TEST_F(NodeDataTest_640, DefaultConstruction_IsDefined_640) {
  node_data nd;
  EXPECT_FALSE(nd.is_defined());
}

TEST_F(NodeDataTest_640, DefaultConstruction_TypeIsNull_640) {
  node_data nd;
  EXPECT_EQ(NodeType::Null, nd.type());
}

TEST_F(NodeDataTest_640, DefaultConstruction_ScalarIsEmpty_640) {
  node_data nd;
  EXPECT_TRUE(nd.scalar().empty());
}

TEST_F(NodeDataTest_640, DefaultConstruction_TagIsEmpty_640) {
  node_data nd;
  EXPECT_TRUE(nd.tag().empty());
}

TEST_F(NodeDataTest_640, DefaultConstruction_SizeIsZero_640) {
  node_data nd;
  EXPECT_EQ(0u, nd.size());
}

// Test mark_defined
TEST_F(NodeDataTest_640, MarkDefined_SetsIsDefined_640) {
  node_data nd;
  nd.mark_defined();
  EXPECT_TRUE(nd.is_defined());
}

TEST_F(NodeDataTest_640, MarkDefined_TypeRemainsNull_640) {
  node_data nd;
  nd.mark_defined();
  EXPECT_EQ(NodeType::Null, nd.type());
}

// Test set_type
TEST_F(NodeDataTest_640, SetType_Scalar_640) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, nd.type());
}

TEST_F(NodeDataTest_640, SetType_Sequence_640) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, nd.type());
}

TEST_F(NodeDataTest_640, SetType_Map_640) {
  node_data nd;
  nd.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, nd.type());
}

TEST_F(NodeDataTest_640, SetType_Null_640) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, nd.type());
}

TEST_F(NodeDataTest_640, SetType_Undefined_640) {
  node_data nd;
  nd.set_type(NodeType::Undefined);
  EXPECT_EQ(NodeType::Undefined, nd.type());
}

// Test set_tag
TEST_F(NodeDataTest_640, SetTag_NormalTag_640) {
  node_data nd;
  nd.set_tag("!custom_tag");
  EXPECT_EQ("!custom_tag", nd.tag());
}

TEST_F(NodeDataTest_640, SetTag_EmptyTag_640) {
  node_data nd;
  nd.set_tag("");
  EXPECT_TRUE(nd.tag().empty());
}

TEST_F(NodeDataTest_640, SetTag_OverwriteTag_640) {
  node_data nd;
  nd.set_tag("first");
  nd.set_tag("second");
  EXPECT_EQ("second", nd.tag());
}

// Test set_scalar
TEST_F(NodeDataTest_640, SetScalar_NormalString_640) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("hello");
  EXPECT_EQ("hello", nd.scalar());
}

TEST_F(NodeDataTest_640, SetScalar_EmptyString_640) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("");
  EXPECT_TRUE(nd.scalar().empty());
}

TEST_F(NodeDataTest_640, SetScalar_Overwrite_640) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("first");
  nd.set_scalar("second");
  EXPECT_EQ("second", nd.scalar());
}

// Test set_null
TEST_F(NodeDataTest_640, SetNull_TypeBecomesNull_640) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_null();
  EXPECT_EQ(NodeType::Null, nd.type());
}

// Test set_style
TEST_F(NodeDataTest_640, SetStyle_Default_640) {
  node_data nd;
  nd.set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, nd.style());
}

TEST_F(NodeDataTest_640, SetStyle_Block_640) {
  node_data nd;
  nd.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, nd.style());
}

TEST_F(NodeDataTest_640, SetStyle_Flow_640) {
  node_data nd;
  nd.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, nd.style());
}

// Test set_mark
TEST_F(NodeDataTest_640, SetMark_CustomMark_640) {
  node_data nd;
  Mark m;
  m.line = 5;
  m.column = 10;
  nd.set_mark(m);
  EXPECT_EQ(5, nd.mark().line);
  EXPECT_EQ(10, nd.mark().column);
}

// Test empty_scalar
TEST_F(NodeDataTest_640, EmptyScalar_ReturnsEmptyString_640) {
  const std::string& es = node_data::empty_scalar();
  EXPECT_TRUE(es.empty());
}

TEST_F(NodeDataTest_640, EmptyScalar_ReturnsSameReference_640) {
  const std::string& es1 = node_data::empty_scalar();
  const std::string& es2 = node_data::empty_scalar();
  EXPECT_EQ(&es1, &es2);
}

// Test sequence operations
TEST_F(NodeDataTest_640, PushBack_IncreasesSize_640) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  
  node& n = pMemory->create_node();
  n.set_scalar("item1");
  
  nd.push_back(n, pMemory);
  EXPECT_EQ(1u, nd.size());
}

TEST_F(NodeDataTest_640, PushBack_MultipleItems_640) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  
  node& n1 = pMemory->create_node();
  n1.set_scalar("item1");
  node& n2 = pMemory->create_node();
  n2.set_scalar("item2");
  node& n3 = pMemory->create_node();
  n3.set_scalar("item3");
  
  nd.push_back(n1, pMemory);
  nd.push_back(n2, pMemory);
  nd.push_back(n3, pMemory);
  EXPECT_EQ(3u, nd.size());
}

// Test map operations
TEST_F(NodeDataTest_640, Insert_MapIncreasesSize_640) {
  node_data nd;
  nd.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("key1");
  node& value = pMemory->create_node();
  value.set_scalar("value1");
  
  nd.insert(key, value, pMemory);
  EXPECT_EQ(1u, nd.size());
}

TEST_F(NodeDataTest_640, Insert_MultipleMapEntries_640) {
  node_data nd;
  nd.set_type(NodeType::Map);
  
  for (int i = 0; i < 5; ++i) {
    node& key = pMemory->create_node();
    key.set_scalar("key" + std::to_string(i));
    node& value = pMemory->create_node();
    value.set_scalar("value" + std::to_string(i));
    nd.insert(key, value, pMemory);
  }
  EXPECT_EQ(5u, nd.size());
}

// Test get on map
TEST_F(NodeDataTest_640, Get_ExistingKey_ReturnsNonNull_640) {
  node_data nd;
  nd.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("mykey");
  node& value = pMemory->create_node();
  value.set_scalar("myvalue");
  
  nd.insert(key, value, pMemory);
  
  const node* result = nd.get(std::string("mykey"), pMemory);
  EXPECT_NE(nullptr, result);
}

TEST_F(NodeDataTest_640, Get_NonExistingKey_ReturnsNull_640) {
  node_data nd;
  nd.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("mykey");
  node& value = pMemory->create_node();
  value.set_scalar("myvalue");
  
  nd.insert(key, value, pMemory);
  
  const node* result = nd.get(std::string("nonexistent"), pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test remove on map
TEST_F(NodeDataTest_640, Remove_ExistingKey_ReturnsTrue_640) {
  node_data nd;
  nd.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("removekey");
  node& value = pMemory->create_node();
  value.set_scalar("removevalue");
  
  nd.insert(key, value, pMemory);
  
  bool removed = nd.remove(std::string("removekey"), pMemory);
  EXPECT_TRUE(removed);
}

TEST_F(NodeDataTest_640, Remove_NonExistingKey_ReturnsFalse_640) {
  node_data nd;
  nd.set_type(NodeType::Map);
  
  bool removed = nd.remove(std::string("nonexistent"), pMemory);
  EXPECT_FALSE(removed);
}

TEST_F(NodeDataTest_640, Remove_DecreasesSize_640) {
  node_data nd;
  nd.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("key1");
  node& value = pMemory->create_node();
  value.set_scalar("value1");
  
  nd.insert(key, value, pMemory);
  EXPECT_EQ(1u, nd.size());
  
  nd.remove(std::string("key1"), pMemory);
  EXPECT_EQ(0u, nd.size());
}

// Test begin/end iterators
TEST_F(NodeDataTest_640, BeginEnd_EmptySequence_640) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  EXPECT_EQ(nd.begin(), nd.end());
}

TEST_F(NodeDataTest_640, BeginEnd_EmptyMap_640) {
  node_data nd;
  nd.set_type(NodeType::Map);
  EXPECT_EQ(nd.begin(), nd.end());
}

TEST_F(NodeDataTest_640, BeginEnd_NonEmptySequence_640) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  
  node& n = pMemory->create_node();
  n.set_scalar("item");
  nd.push_back(n, pMemory);
  
  EXPECT_NE(nd.begin(), nd.end());
}

// Test type changes clear data
TEST_F(NodeDataTest_640, SetType_ScalarToSequence_ClearsScalar_640) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("hello");
  nd.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, nd.type());
  EXPECT_EQ(0u, nd.size());
}

TEST_F(NodeDataTest_640, SetType_SequenceToMap_ClearsSequence_640) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  
  node& n = pMemory->create_node();
  n.set_scalar("item");
  nd.push_back(n, pMemory);
  EXPECT_EQ(1u, nd.size());
  
  nd.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, nd.type());
  EXPECT_EQ(0u, nd.size());
}

// Test mark_defined on Undefined type
TEST_F(NodeDataTest_640, MarkDefined_UndefinedBecomesNull_640) {
  node_data nd;
  nd.set_type(NodeType::Undefined);
  EXPECT_EQ(NodeType::Undefined, nd.type());
  nd.mark_defined();
  EXPECT_EQ(NodeType::Null, nd.type());
  EXPECT_TRUE(nd.is_defined());
}

// Test mark_defined on non-Undefined type preserves type
TEST_F(NodeDataTest_640, MarkDefined_ScalarRemainsScalar_640) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.mark_defined();
  EXPECT_EQ(NodeType::Scalar, nd.type());
  EXPECT_TRUE(nd.is_defined());
}

TEST_F(NodeDataTest_640, MarkDefined_SequenceRemainsSequence_640) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  nd.mark_defined();
  EXPECT_EQ(NodeType::Sequence, nd.type());
  EXPECT_TRUE(nd.is_defined());
}

TEST_F(NodeDataTest_640, MarkDefined_MapRemainsMap_640) {
  node_data nd;
  nd.set_type(NodeType::Map);
  nd.mark_defined();
  EXPECT_EQ(NodeType::Map, nd.type());
  EXPECT_TRUE(nd.is_defined());
}

// Test force_insert
TEST_F(NodeDataTest_640, ForceInsert_AddsToMap_640) {
  node_data nd;
  nd.set_type(NodeType::Map);
  
  nd.force_insert(std::string("key"), std::string("value"), pMemory);
  EXPECT_EQ(1u, nd.size());
}

TEST_F(NodeDataTest_640, ForceInsert_AllowsDuplicateKeys_640) {
  node_data nd;
  nd.set_type(NodeType::Map);
  
  nd.force_insert(std::string("key"), std::string("value1"), pMemory);
  nd.force_insert(std::string("key"), std::string("value2"), pMemory);
  EXPECT_EQ(2u, nd.size());
}

// Test get with node reference
TEST_F(NodeDataTest_640, GetNode_ExistingKey_ReturnsNonNull_640) {
  node_data nd;
  nd.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("nodekey");
  node& value = pMemory->create_node();
  value.set_scalar("nodevalue");
  
  nd.insert(key, value, pMemory);
  
  const node* result = nd.get(key, pMemory);
  EXPECT_NE(nullptr, result);
}

// Test remove with node reference
TEST_F(NodeDataTest_640, RemoveNode_ExistingKey_ReturnsTrue_640) {
  node_data nd;
  nd.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("removekey");
  node& value = pMemory->create_node();
  value.set_scalar("removevalue");
  
  nd.insert(key, value, pMemory);
  
  bool removed = nd.remove(key, pMemory);
  EXPECT_TRUE(removed);
}

TEST_F(NodeDataTest_640, RemoveNode_NonExistingKey_ReturnsFalse_640) {
  node_data nd;
  nd.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("nonexistent");
  
  bool removed = nd.remove(key, pMemory);
  EXPECT_FALSE(removed);
}

// Test size for different types
TEST_F(NodeDataTest_640, Size_NullTypeIsZero_640) {
  node_data nd;
  EXPECT_EQ(0u, nd.size());
}

TEST_F(NodeDataTest_640, Size_ScalarTypeIsZero_640) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("test");
  EXPECT_EQ(0u, nd.size());
}

// Test copy constructor is deleted (compile-time check, not runtime)
// node_data is not copyable, verified by the = delete declarations

// Test setting same type does not reset data
TEST_F(NodeDataTest_640, SetType_SameType_NoReset_640) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  
  node& n = pMemory->create_node();
  n.set_scalar("item");
  nd.push_back(n, pMemory);
  EXPECT_EQ(1u, nd.size());
  
  nd.set_type(NodeType::Sequence);
  EXPECT_EQ(1u, nd.size());
}

// Test push_back on null converts to sequence
TEST_F(NodeDataTest_640, PushBack_OnNull_ConvertsToSequence_640) {
  node_data nd;
  // default type is Null
  EXPECT_EQ(NodeType::Null, nd.type());
  
  node& n = pMemory->create_node();
  n.set_scalar("item");
  nd.push_back(n, pMemory);
  
  EXPECT_EQ(NodeType::Sequence, nd.type());
  EXPECT_EQ(1u, nd.size());
}

// Test mark with null mark
TEST_F(NodeDataTest_640, SetMark_NullMark_640) {
  node_data nd;
  nd.set_mark(Mark::null_mark());
  // Just verify it doesn't crash and mark is accessible
  const Mark& m = nd.mark();
  (void)m;
}

// Test large number of sequence items
TEST_F(NodeDataTest_640, PushBack_ManyItems_640) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  
  const int count = 100;
  for (int i = 0; i < count; ++i) {
    node& n = pMemory->create_node();
    n.set_scalar("item" + std::to_string(i));
    nd.push_back(n, pMemory);
  }
  EXPECT_EQ(static_cast<std::size_t>(count), nd.size());
}

// Test large number of map entries
TEST_F(NodeDataTest_640, Insert_ManyEntries_640) {
  node_data nd;
  nd.set_type(NodeType::Map);
  
  const int count = 100;
  for (int i = 0; i < count; ++i) {
    node& key = pMemory->create_node();
    key.set_scalar("key" + std::to_string(i));
    node& value = pMemory->create_node();
    value.set_scalar("value" + std::to_string(i));
    nd.insert(key, value, pMemory);
  }
  EXPECT_EQ(static_cast<std::size_t>(count), nd.size());
}

// Test get with integer key
TEST_F(NodeDataTest_640, Get_IntegerKey_640) {
  node_data nd;
  nd.set_type(NodeType::Map);
  
  nd.force_insert(42, std::string("answer"), pMemory);
  
  const node* result = nd.get(42, pMemory);
  EXPECT_NE(nullptr, result);
}

// Test set_scalar on non-scalar type (might convert or work depending on implementation)
TEST_F(NodeDataTest_640, SetScalar_SetsValue_640) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("test_value");
  EXPECT_EQ("test_value", nd.scalar());
  EXPECT_EQ(NodeType::Scalar, nd.type());
}

}  // namespace detail
}  // namespace YAML
