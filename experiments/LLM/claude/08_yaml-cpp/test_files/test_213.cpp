#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeRefTest_213 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = std::make_shared<memory_holder>();
  }

  shared_memory_holder pMemory;
};

// Test default construction - node_ref should be Null type by default
TEST_F(NodeRefTest_213, DefaultConstructionIsNull_213) {
  node_ref ref;
  EXPECT_EQ(NodeType::Null, ref.type());
}

// Test default construction - not defined by default
TEST_F(NodeRefTest_213, DefaultConstructionIsNotDefined_213) {
  node_ref ref;
  EXPECT_FALSE(ref.is_defined());
}

// Test mark_defined makes node defined
TEST_F(NodeRefTest_213, MarkDefinedMakesNodeDefined_213) {
  node_ref ref;
  ref.mark_defined();
  EXPECT_TRUE(ref.is_defined());
}

// Test set_type to Scalar
TEST_F(NodeRefTest_213, SetTypeScalar_213) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, ref.type());
}

// Test set_type to Sequence
TEST_F(NodeRefTest_213, SetTypeSequence_213) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, ref.type());
}

// Test set_type to Map
TEST_F(NodeRefTest_213, SetTypeMap_213) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, ref.type());
}

// Test set_type to Null
TEST_F(NodeRefTest_213, SetTypeNull_213) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, ref.type());
  ref.set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, ref.type());
}

// Test set_type to Undefined
TEST_F(NodeRefTest_213, SetTypeUndefined_213) {
  node_ref ref;
  ref.set_type(NodeType::Undefined);
  EXPECT_EQ(NodeType::Undefined, ref.type());
}

// Test set_null sets type to Null
TEST_F(NodeRefTest_213, SetNullSetsTypeToNull_213) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_null();
  EXPECT_EQ(NodeType::Null, ref.type());
}

// Test scalar default is empty
TEST_F(NodeRefTest_213, DefaultScalarIsEmpty_213) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  EXPECT_EQ("", ref.scalar());
}

// Test set_scalar and retrieve
TEST_F(NodeRefTest_213, SetAndGetScalar_213) {
  node_ref ref;
  ref.set_scalar("hello");
  EXPECT_EQ("hello", ref.scalar());
}

// Test set_scalar with empty string
TEST_F(NodeRefTest_213, SetScalarEmpty_213) {
  node_ref ref;
  ref.set_scalar("");
  EXPECT_EQ("", ref.scalar());
}

// Test set_scalar with special characters
TEST_F(NodeRefTest_213, SetScalarSpecialChars_213) {
  node_ref ref;
  ref.set_scalar("hello\nworld\t!");
  EXPECT_EQ("hello\nworld\t!", ref.scalar());
}

// Test tag default is empty
TEST_F(NodeRefTest_213, DefaultTagIsEmpty_213) {
  node_ref ref;
  EXPECT_EQ("", ref.tag());
}

// Test set_tag and retrieve
TEST_F(NodeRefTest_213, SetAndGetTag_213) {
  node_ref ref;
  ref.set_tag("!!str");
  EXPECT_EQ("!!str", ref.tag());
}

// Test set_tag with empty string
TEST_F(NodeRefTest_213, SetTagEmpty_213) {
  node_ref ref;
  ref.set_tag("!!int");
  ref.set_tag("");
  EXPECT_EQ("", ref.tag());
}

// Test style default
TEST_F(NodeRefTest_213, DefaultStyle_213) {
  node_ref ref;
  EXPECT_EQ(EmitterStyle::Default, ref.style());
}

// Test set_style to Flow
TEST_F(NodeRefTest_213, SetStyleFlow_213) {
  node_ref ref;
  ref.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, ref.style());
}

// Test set_style to Block
TEST_F(NodeRefTest_213, SetStyleBlock_213) {
  node_ref ref;
  ref.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, ref.style());
}

// Test mark default
TEST_F(NodeRefTest_213, DefaultMark_213) {
  node_ref ref;
  const Mark& m = ref.mark();
  EXPECT_EQ(Mark::null_mark().line, m.line);
  EXPECT_EQ(Mark::null_mark().column, m.column);
  EXPECT_EQ(Mark::null_mark().pos, m.pos);
}

// Test set_mark
TEST_F(NodeRefTest_213, SetMark_213) {
  node_ref ref;
  Mark mark;
  mark.line = 5;
  mark.column = 10;
  mark.pos = 42;
  ref.set_mark(mark);
  EXPECT_EQ(5, ref.mark().line);
  EXPECT_EQ(10, ref.mark().column);
  EXPECT_EQ(42, ref.mark().pos);
}

// Test size of default (Null) node is 0
TEST_F(NodeRefTest_213, SizeOfNullNodeIsZero_213) {
  node_ref ref;
  EXPECT_EQ(0u, ref.size());
}

// Test size of sequence after push_back
TEST_F(NodeRefTest_213, SizeOfSequenceAfterPushBack_213) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  
  node& n1 = pMemory->create_node();
  n1.set_scalar("value1");
  ref.push_back(n1, pMemory);
  
  EXPECT_EQ(1u, ref.size());
}

// Test size of sequence after multiple push_backs
TEST_F(NodeRefTest_213, SizeOfSequenceAfterMultiplePushBacks_213) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  
  node& n1 = pMemory->create_node();
  n1.set_scalar("value1");
  node& n2 = pMemory->create_node();
  n2.set_scalar("value2");
  node& n3 = pMemory->create_node();
  n3.set_scalar("value3");
  
  ref.push_back(n1, pMemory);
  ref.push_back(n2, pMemory);
  ref.push_back(n3, pMemory);
  
  EXPECT_EQ(3u, ref.size());
}

// Test size of map after insert
TEST_F(NodeRefTest_213, SizeOfMapAfterInsert_213) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("key1");
  node& value = pMemory->create_node();
  value.set_scalar("value1");
  
  ref.insert(key, value, pMemory);
  
  EXPECT_EQ(1u, ref.size());
}

// Test begin equals end for empty sequence
TEST_F(NodeRefTest_213, BeginEqualsEndForEmptySequence_213) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  EXPECT_EQ(ref.begin(), ref.end());
}

// Test begin does not equal end for non-empty sequence
TEST_F(NodeRefTest_213, BeginNotEqualsEndForNonEmptySequence_213) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  
  node& n1 = pMemory->create_node();
  n1.set_scalar("value1");
  ref.push_back(n1, pMemory);
  
  EXPECT_NE(ref.begin(), ref.end());
}

// Test set_data copies from another node_ref
TEST_F(NodeRefTest_213, SetDataCopiesFromAnother_213) {
  node_ref ref1;
  ref1.set_type(NodeType::Scalar);
  ref1.set_scalar("test_value");
  ref1.set_tag("!!str");
  ref1.mark_defined();
  
  node_ref ref2;
  ref2.set_data(ref1);
  
  EXPECT_EQ(NodeType::Scalar, ref2.type());
  EXPECT_EQ("test_value", ref2.scalar());
  EXPECT_EQ("!!str", ref2.tag());
}

// Test get with string key on map returns nullptr when key doesn't exist
TEST_F(NodeRefTest_213, GetNonExistentKeyReturnsNull_213) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  
  node* result = ref.get(std::string("nonexistent"), pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test get with string key on map returns node when key exists
TEST_F(NodeRefTest_213, GetExistentKeyReturnsNode_213) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("mykey");
  node& value = pMemory->create_node();
  value.set_scalar("myvalue");
  
  ref.insert(key, value, pMemory);
  
  node* result = ref.get(std::string("mykey"), pMemory);
  EXPECT_NE(nullptr, result);
}

// Test remove on map with non-existent key returns false
TEST_F(NodeRefTest_213, RemoveNonExistentKeyReturnsFalse_213) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  
  bool result = ref.remove(std::string("nonexistent"), pMemory);
  EXPECT_FALSE(result);
}

// Test remove on map with existing key returns true
TEST_F(NodeRefTest_213, RemoveExistentKeyReturnsTrue_213) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("mykey");
  node& value = pMemory->create_node();
  value.set_scalar("myvalue");
  
  ref.insert(key, value, pMemory);
  
  bool result = ref.remove(std::string("mykey"), pMemory);
  EXPECT_TRUE(result);
}

// Test remove with node reference
TEST_F(NodeRefTest_213, RemoveByNodeRef_213) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("mykey");
  node& value = pMemory->create_node();
  value.set_scalar("myvalue");
  
  ref.insert(key, value, pMemory);
  
  bool result = ref.remove(key, pMemory);
  EXPECT_TRUE(result);
  EXPECT_EQ(0u, ref.size());
}

// Test force_insert adds a key-value pair
TEST_F(NodeRefTest_213, ForceInsertAddsKeyValuePair_213) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  
  ref.force_insert(std::string("key1"), std::string("value1"), pMemory);
  
  EXPECT_EQ(1u, ref.size());
}

// Test setting type from Sequence to Map
TEST_F(NodeRefTest_213, ChangeTypeFromSequenceToMap_213) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, ref.type());
  
  ref.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, ref.type());
}

// Test setting type from Map to Scalar
TEST_F(NodeRefTest_213, ChangeTypeFromMapToScalar_213) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, ref.type());
  
  ref.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, ref.type());
}

// Test push_back on Null type converts to Sequence
TEST_F(NodeRefTest_213, PushBackOnNullConvertsToSequence_213) {
  node_ref ref;
  EXPECT_EQ(NodeType::Null, ref.type());
  
  node& n1 = pMemory->create_node();
  n1.set_scalar("value1");
  ref.push_back(n1, pMemory);
  
  EXPECT_EQ(NodeType::Sequence, ref.type());
  EXPECT_EQ(1u, ref.size());
}

// Test get with node reference on map
TEST_F(NodeRefTest_213, GetByNodeRef_213) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("mykey");
  node& value = pMemory->create_node();
  value.set_scalar("myvalue");
  
  ref.insert(key, value, pMemory);
  
  node* result = ref.get(key, pMemory);
  EXPECT_NE(nullptr, result);
}

// Test get by node reference returns null for non-existent key
TEST_F(NodeRefTest_213, GetByNodeRefNonExistent_213) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_scalar("nonexistent");
  
  node* result = ref.get(key, pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test multiple operations in sequence
TEST_F(NodeRefTest_213, MultipleOperationsInSequence_213) {
  node_ref ref;
  ref.mark_defined();
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("test");
  ref.set_tag("!!str");
  ref.set_style(EmitterStyle::Flow);
  
  EXPECT_TRUE(ref.is_defined());
  EXPECT_EQ(NodeType::Scalar, ref.type());
  EXPECT_EQ("test", ref.scalar());
  EXPECT_EQ("!!str", ref.tag());
  EXPECT_EQ(EmitterStyle::Flow, ref.style());
}

// Test set_scalar overwrites previous value
TEST_F(NodeRefTest_213, SetScalarOverwritesPrevious_213) {
  node_ref ref;
  ref.set_scalar("first");
  EXPECT_EQ("first", ref.scalar());
  ref.set_scalar("second");
  EXPECT_EQ("second", ref.scalar());
}

// Test insert on Null type converts to Map
TEST_F(NodeRefTest_213, InsertOnNullConvertsToMap_213) {
  node_ref ref;
  EXPECT_EQ(NodeType::Null, ref.type());
  
  node& key = pMemory->create_node();
  key.set_scalar("key");
  node& value = pMemory->create_node();
  value.set_scalar("value");
  
  ref.insert(key, value, pMemory);
  
  EXPECT_EQ(NodeType::Map, ref.type());
}

// Test size after remove
TEST_F(NodeRefTest_213, SizeAfterRemove_213) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  
  node& key1 = pMemory->create_node();
  key1.set_scalar("key1");
  node& val1 = pMemory->create_node();
  val1.set_scalar("val1");
  
  node& key2 = pMemory->create_node();
  key2.set_scalar("key2");
  node& val2 = pMemory->create_node();
  val2.set_scalar("val2");
  
  ref.insert(key1, val1, pMemory);
  ref.insert(key2, val2, pMemory);
  EXPECT_EQ(2u, ref.size());
  
  ref.remove(std::string("key1"), pMemory);
  EXPECT_EQ(1u, ref.size());
}

// Test very long scalar value
TEST_F(NodeRefTest_213, VeryLongScalar_213) {
  node_ref ref;
  std::string longStr(10000, 'x');
  ref.set_scalar(longStr);
  EXPECT_EQ(longStr, ref.scalar());
}

// Test setting same type multiple times
TEST_F(NodeRefTest_213, SetSameTypeMultipleTimes_213) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, ref.type());
}

// Test integer key for get
TEST_F(NodeRefTest_213, GetWithIntegerKey_213) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  
  node& n1 = pMemory->create_node();
  n1.set_scalar("value0");
  ref.push_back(n1, pMemory);
  
  node* result = ref.get(0, pMemory);
  EXPECT_NE(nullptr, result);
}

}  // namespace detail
}  // namespace YAML
