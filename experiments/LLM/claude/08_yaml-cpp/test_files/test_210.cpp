#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node_data.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeDataTest_210 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = std::make_shared<memory_holder>();
  }

  shared_memory_holder pMemory;
};

// Test default construction state
TEST_F(NodeDataTest_210, DefaultConstruction_IsDefined_210) {
  node_data nd;
  EXPECT_FALSE(nd.is_defined());
}

TEST_F(NodeDataTest_210, DefaultConstruction_TypeIsNull_210) {
  node_data nd;
  EXPECT_EQ(NodeType::Null, nd.type());
}

TEST_F(NodeDataTest_210, DefaultConstruction_TagIsEmpty_210) {
  node_data nd;
  EXPECT_TRUE(nd.tag().empty());
}

TEST_F(NodeDataTest_210, DefaultConstruction_ScalarIsEmpty_210) {
  node_data nd;
  EXPECT_TRUE(nd.scalar().empty());
}

TEST_F(NodeDataTest_210, DefaultConstruction_StyleIsDefault_210) {
  node_data nd;
  EXPECT_EQ(EmitterStyle::Default, nd.style());
}

TEST_F(NodeDataTest_210, DefaultConstruction_MarkIsNull_210) {
  node_data nd;
  EXPECT_EQ(Mark::null_mark().line, nd.mark().line);
  EXPECT_EQ(Mark::null_mark().column, nd.mark().column);
  EXPECT_EQ(Mark::null_mark().pos, nd.mark().pos);
}

// Test mark_defined
TEST_F(NodeDataTest_210, MarkDefined_SetsDefined_210) {
  node_data nd;
  nd.mark_defined();
  EXPECT_TRUE(nd.is_defined());
}

// Test set_mark
TEST_F(NodeDataTest_210, SetMark_UpdatesMark_210) {
  node_data nd;
  Mark m;
  m.line = 5;
  m.column = 10;
  m.pos = 42;
  nd.set_mark(m);
  EXPECT_EQ(5, nd.mark().line);
  EXPECT_EQ(10, nd.mark().column);
  EXPECT_EQ(42, nd.mark().pos);
}

// Test set_type
TEST_F(NodeDataTest_210, SetType_Scalar_210) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, nd.type());
}

TEST_F(NodeDataTest_210, SetType_Sequence_210) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, nd.type());
}

TEST_F(NodeDataTest_210, SetType_Map_210) {
  node_data nd;
  nd.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, nd.type());
}

TEST_F(NodeDataTest_210, SetType_Null_210) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, nd.type());
}

TEST_F(NodeDataTest_210, SetType_Undefined_210) {
  node_data nd;
  nd.set_type(NodeType::Undefined);
  EXPECT_EQ(NodeType::Undefined, nd.type());
}

// Test set_tag
TEST_F(NodeDataTest_210, SetTag_SetsTag_210) {
  node_data nd;
  nd.set_tag("my_tag");
  EXPECT_EQ("my_tag", nd.tag());
}

TEST_F(NodeDataTest_210, SetTag_EmptyTag_210) {
  node_data nd;
  nd.set_tag("some_tag");
  nd.set_tag("");
  EXPECT_EQ("", nd.tag());
}

// Test set_style
TEST_F(NodeDataTest_210, SetStyle_Block_210) {
  node_data nd;
  nd.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, nd.style());
}

TEST_F(NodeDataTest_210, SetStyle_Flow_210) {
  node_data nd;
  nd.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, nd.style());
}

TEST_F(NodeDataTest_210, SetStyle_Default_210) {
  node_data nd;
  nd.set_style(EmitterStyle::Flow);
  nd.set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, nd.style());
}

// Test set_null
TEST_F(NodeDataTest_210, SetNull_SetsTypeToNull_210) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_null();
  EXPECT_EQ(NodeType::Null, nd.type());
}

TEST_F(NodeDataTest_210, SetNull_MarksDefined_210) {
  node_data nd;
  nd.set_null();
  EXPECT_TRUE(nd.is_defined());
}

// Test set_scalar
TEST_F(NodeDataTest_210, SetScalar_SetsScalarValue_210) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("hello");
  EXPECT_EQ("hello", nd.scalar());
}

TEST_F(NodeDataTest_210, SetScalar_EmptyScalar_210) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("");
  EXPECT_EQ("", nd.scalar());
}

TEST_F(NodeDataTest_210, SetScalar_MarksDefined_210) {
  node_data nd;
  nd.set_scalar("test");
  EXPECT_TRUE(nd.is_defined());
}

// Test empty_scalar
TEST_F(NodeDataTest_210, EmptyScalar_ReturnsEmptyString_210) {
  const std::string& empty = node_data::empty_scalar();
  EXPECT_TRUE(empty.empty());
}

TEST_F(NodeDataTest_210, EmptyScalar_ReturnsSameReference_210) {
  const std::string& ref1 = node_data::empty_scalar();
  const std::string& ref2 = node_data::empty_scalar();
  EXPECT_EQ(&ref1, &ref2);
}

// Test size for default (Null)
TEST_F(NodeDataTest_210, Size_NullType_ReturnsZero_210) {
  node_data nd;
  EXPECT_EQ(0u, nd.size());
}

// Test size for sequence
TEST_F(NodeDataTest_210, Size_EmptySequence_ReturnsZero_210) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  EXPECT_EQ(0u, nd.size());
}

TEST_F(NodeDataTest_210, Size_SequenceWithOneElement_210) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  
  node& n = pMemory->create_node();
  n.set_scalar("value1");
  nd.push_back(n, pMemory);
  
  EXPECT_EQ(1u, nd.size());
}

TEST_F(NodeDataTest_210, Size_SequenceWithMultipleElements_210) {
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
  
  EXPECT_EQ(3u, nd.size());
}

// Test size for map
TEST_F(NodeDataTest_210, Size_EmptyMap_ReturnsZero_210) {
  node_data nd;
  nd.set_type(NodeType::Map);
  EXPECT_EQ(0u, nd.size());
}

TEST_F(NodeDataTest_210, Size_MapWithOneElement_210) {
  node_data nd;
  nd.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("key1");
  node& val = pMemory->create_node();
  val.set_scalar("val1");
  nd.insert(key, val, pMemory);
  
  EXPECT_EQ(1u, nd.size());
}

// Test push_back on sequence
TEST_F(NodeDataTest_210, PushBack_AddsToSequence_210) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  
  node& n = pMemory->create_node();
  n.set_scalar("test");
  nd.push_back(n, pMemory);
  
  EXPECT_EQ(1u, nd.size());
}

// Test begin/end on empty sequence
TEST_F(NodeDataTest_210, BeginEnd_EmptySequence_Equal_210) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  EXPECT_EQ(nd.begin(), nd.end());
}

// Test begin/end on non-empty sequence
TEST_F(NodeDataTest_210, BeginEnd_NonEmptySequence_NotEqual_210) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  
  node& n = pMemory->create_node();
  n.set_scalar("test");
  nd.push_back(n, pMemory);
  
  EXPECT_NE(nd.begin(), nd.end());
}

// Test insert into map
TEST_F(NodeDataTest_210, Insert_AddsToMap_210) {
  node_data nd;
  nd.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("key");
  node& val = pMemory->create_node();
  val.set_scalar("value");
  nd.insert(key, val, pMemory);
  
  EXPECT_EQ(1u, nd.size());
}

// Test get on map
TEST_F(NodeDataTest_210, Get_ExistingKey_ReturnsNonNull_210) {
  node_data nd;
  nd.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("key");
  node& val = pMemory->create_node();
  val.set_scalar("value");
  nd.insert(key, val, pMemory);
  
  const node* result = nd.get(key, pMemory);
  EXPECT_NE(nullptr, result);
}

TEST_F(NodeDataTest_210, Get_NonExistingKey_ReturnsNull_210) {
  node_data nd;
  nd.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("key");
  node& val = pMemory->create_node();
  val.set_scalar("value");
  nd.insert(key, val, pMemory);
  
  node& otherKey = pMemory->create_node();
  otherKey.set_scalar("other");
  
  const node* result = nd.get(otherKey, pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test remove from map
TEST_F(NodeDataTest_210, Remove_ExistingKey_ReturnsTrue_210) {
  node_data nd;
  nd.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("key");
  node& val = pMemory->create_node();
  val.set_scalar("value");
  nd.insert(key, val, pMemory);
  
  EXPECT_TRUE(nd.remove(key, pMemory));
}

TEST_F(NodeDataTest_210, Remove_NonExistingKey_ReturnsFalse_210) {
  node_data nd;
  nd.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("key");
  node& val = pMemory->create_node();
  val.set_scalar("value");
  nd.insert(key, val, pMemory);
  
  node& otherKey = pMemory->create_node();
  otherKey.set_scalar("other");
  
  EXPECT_FALSE(nd.remove(otherKey, pMemory));
}

TEST_F(NodeDataTest_210, Remove_DecreasesSize_210) {
  node_data nd;
  nd.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("key");
  node& val = pMemory->create_node();
  val.set_scalar("value");
  nd.insert(key, val, pMemory);
  
  EXPECT_EQ(1u, nd.size());
  nd.remove(key, pMemory);
  EXPECT_EQ(0u, nd.size());
}

// Test template get with string key
TEST_F(NodeDataTest_210, TemplateGet_StringKey_ExistingKey_210) {
  node_data nd;
  nd.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("mykey");
  node& val = pMemory->create_node();
  val.set_scalar("myvalue");
  nd.insert(key, val, pMemory);
  
  const node* result = nd.get(std::string("mykey"), pMemory);
  EXPECT_NE(nullptr, result);
}

TEST_F(NodeDataTest_210, TemplateGet_StringKey_NonExistingKey_210) {
  node_data nd;
  nd.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("mykey");
  node& val = pMemory->create_node();
  val.set_scalar("myvalue");
  nd.insert(key, val, pMemory);
  
  const node* result = nd.get(std::string("nokey"), pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test template remove with string key
TEST_F(NodeDataTest_210, TemplateRemove_StringKey_ExistingKey_210) {
  node_data nd;
  nd.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("mykey");
  node& val = pMemory->create_node();
  val.set_scalar("myvalue");
  nd.insert(key, val, pMemory);
  
  EXPECT_TRUE(nd.remove(std::string("mykey"), pMemory));
}

TEST_F(NodeDataTest_210, TemplateRemove_StringKey_NonExistingKey_210) {
  node_data nd;
  nd.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("mykey");
  node& val = pMemory->create_node();
  val.set_scalar("myvalue");
  nd.insert(key, val, pMemory);
  
  EXPECT_FALSE(nd.remove(std::string("nokey"), pMemory));
}

// Test force_insert
TEST_F(NodeDataTest_210, ForceInsert_AddsToMap_210) {
  node_data nd;
  nd.set_type(NodeType::Map);
  
  nd.force_insert(std::string("key"), std::string("value"), pMemory);
  
  EXPECT_EQ(1u, nd.size());
}

// Test type change from sequence to map
TEST_F(NodeDataTest_210, SetType_SequenceToMap_210) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  
  node& n = pMemory->create_node();
  n.set_scalar("elem");
  nd.push_back(n, pMemory);
  
  EXPECT_EQ(NodeType::Sequence, nd.type());
  
  nd.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, nd.type());
}

// Test that changing type to same type is idempotent
TEST_F(NodeDataTest_210, SetType_SameType_NoChange_210) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("test");
  nd.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, nd.type());
  EXPECT_EQ("test", nd.scalar());
}

// Test changing type resets scalar
TEST_F(NodeDataTest_210, SetType_ChangingFromScalar_ResetsScalar_210) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("hello");
  EXPECT_EQ("hello", nd.scalar());
  
  nd.set_type(NodeType::Null);
  // After changing type from Scalar, scalar may be reset
  // This verifies the type changed
  EXPECT_EQ(NodeType::Null, nd.type());
}

// Test copy constructor is deleted
TEST_F(NodeDataTest_210, CopyConstructorDeleted_210) {
  EXPECT_FALSE(std::is_copy_constructible<node_data>::value);
}

// Test copy assignment is deleted
TEST_F(NodeDataTest_210, CopyAssignmentDeleted_210) {
  EXPECT_FALSE(std::is_copy_assignable<node_data>::value);
}

// Test multiple insertions into map
TEST_F(NodeDataTest_210, Insert_MultipleEntries_210) {
  node_data nd;
  nd.set_type(NodeType::Map);
  
  for (int i = 0; i < 5; i++) {
    node& key = pMemory->create_node();
    key.set_scalar("key" + std::to_string(i));
    node& val = pMemory->create_node();
    val.set_scalar("val" + std::to_string(i));
    nd.insert(key, val, pMemory);
  }
  
  EXPECT_EQ(5u, nd.size());
}

// Test begin/end iteration count on map
TEST_F(NodeDataTest_210, BeginEnd_MapIteration_210) {
  node_data nd;
  nd.set_type(NodeType::Map);
  
  for (int i = 0; i < 3; i++) {
    node& key = pMemory->create_node();
    key.set_scalar("key" + std::to_string(i));
    node& val = pMemory->create_node();
    val.set_scalar("val" + std::to_string(i));
    nd.insert(key, val, pMemory);
  }
  
  int count = 0;
  for (auto it = nd.begin(); it != nd.end(); ++it) {
    count++;
  }
  EXPECT_EQ(3, count);
}

// Test begin/end iteration count on sequence
TEST_F(NodeDataTest_210, BeginEnd_SequenceIteration_210) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  
  for (int i = 0; i < 4; i++) {
    node& n = pMemory->create_node();
    n.set_scalar("elem" + std::to_string(i));
    nd.push_back(n, pMemory);
  }
  
  int count = 0;
  for (auto it = nd.begin(); it != nd.end(); ++it) {
    count++;
  }
  EXPECT_EQ(4, count);
}

// Test set_scalar overwrites previous scalar
TEST_F(NodeDataTest_210, SetScalar_Overwrite_210) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("first");
  EXPECT_EQ("first", nd.scalar());
  nd.set_scalar("second");
  EXPECT_EQ("second", nd.scalar());
}

// Test set_tag overwrites previous tag
TEST_F(NodeDataTest_210, SetTag_Overwrite_210) {
  node_data nd;
  nd.set_tag("tag1");
  EXPECT_EQ("tag1", nd.tag());
  nd.set_tag("tag2");
  EXPECT_EQ("tag2", nd.tag());
}

// Test set_mark overwrites previous mark
TEST_F(NodeDataTest_210, SetMark_Overwrite_210) {
  node_data nd;
  Mark m1;
  m1.line = 1;
  m1.column = 2;
  nd.set_mark(m1);
  
  Mark m2;
  m2.line = 10;
  m2.column = 20;
  nd.set_mark(m2);
  
  EXPECT_EQ(10, nd.mark().line);
  EXPECT_EQ(20, nd.mark().column);
}

// Test force_insert allows duplicate keys
TEST_F(NodeDataTest_210, ForceInsert_DuplicateKeys_210) {
  node_data nd;
  nd.set_type(NodeType::Map);
  
  nd.force_insert(std::string("key"), std::string("value1"), pMemory);
  nd.force_insert(std::string("key"), std::string("value2"), pMemory);
  
  // force_insert should add regardless of key duplication
  EXPECT_EQ(2u, nd.size());
}

// Test size on Scalar type
TEST_F(NodeDataTest_210, Size_ScalarType_ReturnsZero_210) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("test");
  EXPECT_EQ(0u, nd.size());
}

}  // namespace detail
}  // namespace YAML
