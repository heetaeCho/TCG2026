#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/node_data.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeRefTest_232 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = shared_memory_holder(new Memory);
  }

  shared_memory_holder pMemory;
};

// Test default construction - node_ref should be defined with Null type
TEST_F(NodeRefTest_232, DefaultConstruction_IsNotDefined_232) {
  node_ref ref;
  EXPECT_FALSE(ref.is_defined());
}

TEST_F(NodeRefTest_232, DefaultConstruction_TypeIsNull_232) {
  node_ref ref;
  EXPECT_EQ(NodeType::Null, ref.type());
}

TEST_F(NodeRefTest_232, MarkDefined_232) {
  node_ref ref;
  ref.mark_defined();
  EXPECT_TRUE(ref.is_defined());
}

TEST_F(NodeRefTest_232, SetType_Sequence_232) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, ref.type());
}

TEST_F(NodeRefTest_232, SetType_Map_232) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, ref.type());
}

TEST_F(NodeRefTest_232, SetType_Scalar_232) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, ref.type());
}

TEST_F(NodeRefTest_232, SetType_Null_232) {
  node_ref ref;
  ref.set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, ref.type());
}

TEST_F(NodeRefTest_232, SetType_Undefined_232) {
  node_ref ref;
  ref.set_type(NodeType::Undefined);
  EXPECT_EQ(NodeType::Undefined, ref.type());
}

TEST_F(NodeRefTest_232, SetScalar_232) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("hello");
  EXPECT_EQ("hello", ref.scalar());
}

TEST_F(NodeRefTest_232, SetScalar_EmptyString_232) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("");
  EXPECT_EQ("", ref.scalar());
}

TEST_F(NodeRefTest_232, SetTag_232) {
  node_ref ref;
  ref.set_tag("!mytag");
  EXPECT_EQ("!mytag", ref.tag());
}

TEST_F(NodeRefTest_232, SetTag_Empty_232) {
  node_ref ref;
  ref.set_tag("");
  EXPECT_EQ("", ref.tag());
}

TEST_F(NodeRefTest_232, SetNull_232) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("value");
  ref.set_null();
  EXPECT_EQ(NodeType::Null, ref.type());
}

TEST_F(NodeRefTest_232, SetStyle_Flow_232) {
  node_ref ref;
  ref.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, ref.style());
}

TEST_F(NodeRefTest_232, SetStyle_Block_232) {
  node_ref ref;
  ref.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, ref.style());
}

TEST_F(NodeRefTest_232, SetStyle_Default_232) {
  node_ref ref;
  ref.set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, ref.style());
}

TEST_F(NodeRefTest_232, SetMark_232) {
  node_ref ref;
  Mark mark;
  mark.line = 5;
  mark.column = 10;
  mark.pos = 50;
  ref.set_mark(mark);
  EXPECT_EQ(5, ref.mark().line);
  EXPECT_EQ(10, ref.mark().column);
  EXPECT_EQ(50, ref.mark().pos);
}

TEST_F(NodeRefTest_232, SizeInitiallyZero_232) {
  node_ref ref;
  EXPECT_EQ(0u, ref.size());
}

TEST_F(NodeRefTest_232, PushBack_IncreasesSize_232) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  node& n = pMemory->create_node();
  n.set_scalar("item");
  ref.push_back(n, pMemory);
  EXPECT_EQ(1u, ref.size());
}

TEST_F(NodeRefTest_232, PushBack_MultipleTimes_232) {
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
  EXPECT_EQ(3u, ref.size());
}

TEST_F(NodeRefTest_232, GetByNode_NullType_ReturnsNull_232) {
  node_ref ref;
  node& key = pMemory->create_node();
  key.set_scalar("nonexistent");
  node* result = ref.get(key, pMemory);
  EXPECT_EQ(nullptr, result);
}

TEST_F(NodeRefTest_232, GetByStringKey_MapType_232) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("mykey");
  node& value = pMemory->create_node();
  value.set_scalar("myvalue");
  
  ref.insert(key, value, pMemory);
  
  node* result = ref.get(key, pMemory);
  EXPECT_NE(nullptr, result);
  if (result) {
    EXPECT_EQ("myvalue", result->scalar());
  }
}

TEST_F(NodeRefTest_232, GetByTemplateKey_Sequence_232) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  
  node& n1 = pMemory->create_node();
  n1.set_scalar("first");
  node& n2 = pMemory->create_node();
  n2.set_scalar("second");
  
  ref.push_back(n1, pMemory);
  ref.push_back(n2, pMemory);
  
  // Access by index
  node* result = ref.get(std::string("0"), pMemory);
  // In a sequence, get by key "0" may or may not work depending on implementation
  // but we can at least test it doesn't crash
}

TEST_F(NodeRefTest_232, Insert_IntoMap_232) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("key1");
  node& value = pMemory->create_node();
  value.set_scalar("value1");
  
  ref.insert(key, value, pMemory);
  EXPECT_EQ(1u, ref.size());
}

TEST_F(NodeRefTest_232, Insert_MultipleEntries_232) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  
  node& key1 = pMemory->create_node();
  key1.set_scalar("key1");
  node& value1 = pMemory->create_node();
  value1.set_scalar("value1");
  
  node& key2 = pMemory->create_node();
  key2.set_scalar("key2");
  node& value2 = pMemory->create_node();
  value2.set_scalar("value2");
  
  ref.insert(key1, value1, pMemory);
  ref.insert(key2, value2, pMemory);
  EXPECT_EQ(2u, ref.size());
}

TEST_F(NodeRefTest_232, Remove_ExistingKey_232) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("key1");
  node& value = pMemory->create_node();
  value.set_scalar("value1");
  
  ref.insert(key, value, pMemory);
  EXPECT_EQ(1u, ref.size());
  
  bool removed = ref.remove(key, pMemory);
  EXPECT_TRUE(removed);
}

TEST_F(NodeRefTest_232, Remove_NonExistingKey_232) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  
  node& key1 = pMemory->create_node();
  key1.set_scalar("key1");
  node& value1 = pMemory->create_node();
  value1.set_scalar("value1");
  ref.insert(key1, value1, pMemory);
  
  node& nonExistentKey = pMemory->create_node();
  nonExistentKey.set_scalar("nonexistent");
  
  bool removed = ref.remove(nonExistentKey, pMemory);
  EXPECT_FALSE(removed);
}

TEST_F(NodeRefTest_232, BeginEndEmpty_232) {
  node_ref ref;
  EXPECT_EQ(ref.begin(), ref.end());
}

TEST_F(NodeRefTest_232, BeginEnd_SequenceNotEmpty_232) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  
  node& n = pMemory->create_node();
  n.set_scalar("item");
  ref.push_back(n, pMemory);
  
  EXPECT_NE(ref.begin(), ref.end());
}

TEST_F(NodeRefTest_232, SetData_CopiesFromOther_232) {
  node_ref ref1;
  ref1.set_type(NodeType::Scalar);
  ref1.set_scalar("test_value");
  ref1.set_tag("!tag");
  ref1.mark_defined();
  
  node_ref ref2;
  ref2.set_data(ref1);
  
  EXPECT_EQ(NodeType::Scalar, ref2.type());
  EXPECT_EQ("test_value", ref2.scalar());
  EXPECT_EQ("!tag", ref2.tag());
}

TEST_F(NodeRefTest_232, ForceInsert_232) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  
  ref.force_insert(std::string("key"), std::string("value"), pMemory);
  EXPECT_EQ(1u, ref.size());
}

TEST_F(NodeRefTest_232, DefaultScalar_IsEmpty_232) {
  node_ref ref;
  EXPECT_EQ("", ref.scalar());
}

TEST_F(NodeRefTest_232, DefaultTag_IsEmpty_232) {
  node_ref ref;
  EXPECT_EQ("", ref.tag());
}

TEST_F(NodeRefTest_232, SequencePushBackThenGet_232) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  
  node& n1 = pMemory->create_node();
  n1.set_scalar("first");
  ref.push_back(n1, pMemory);
  
  // Attempt to get by index 0
  node* result = ref.get(0, pMemory);
  EXPECT_NE(nullptr, result);
}

TEST_F(NodeRefTest_232, SequenceGet_OutOfBounds_ReturnsNull_232) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  
  node& n1 = pMemory->create_node();
  n1.set_scalar("first");
  ref.push_back(n1, pMemory);
  
  // Attempt to get by index 5 (out of bounds)
  node* result = ref.get(5, pMemory);
  EXPECT_EQ(nullptr, result);
}

TEST_F(NodeRefTest_232, MapInsertAndGetByNode_232) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("mapkey");
  node& value = pMemory->create_node();
  value.set_scalar("mapvalue");
  
  ref.insert(key, value, pMemory);
  
  node* found = ref.get(key, pMemory);
  ASSERT_NE(nullptr, found);
  EXPECT_EQ("mapvalue", found->scalar());
}

TEST_F(NodeRefTest_232, SetTypeOverwritesPrevious_232) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("hello");
  EXPECT_EQ(NodeType::Scalar, ref.type());
  
  ref.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, ref.type());
}

TEST_F(NodeRefTest_232, RemoveByTemplateKey_Map_232) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  
  ref.force_insert(std::string("removekey"), std::string("removevalue"), pMemory);
  EXPECT_EQ(1u, ref.size());
  
  bool removed = ref.remove(std::string("removekey"), pMemory);
  EXPECT_TRUE(removed);
}

TEST_F(NodeRefTest_232, RemoveByTemplateKey_Nonexistent_232) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  
  ref.force_insert(std::string("existingkey"), std::string("value"), pMemory);
  
  bool removed = ref.remove(std::string("nonexistentkey"), pMemory);
  EXPECT_FALSE(removed);
}

}  // namespace detail
}  // namespace YAML
