#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/node_data.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeRefTest_214 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = std::make_shared<memory_holder>();
    ref = std::unique_ptr<node_ref>(new node_ref());
  }

  std::unique_ptr<node_ref> ref;
  shared_memory_holder pMemory;

  node& create_node() {
    return pMemory->create_node();
  }
};

// Test default construction - node should not be defined
TEST_F(NodeRefTest_214, DefaultConstruction_IsNotDefined_214) {
  EXPECT_FALSE(ref->is_defined());
}

// Test default type is Null
TEST_F(NodeRefTest_214, DefaultConstruction_TypeIsNull_214) {
  EXPECT_EQ(NodeType::Null, ref->type());
}

// Test default scalar is empty
TEST_F(NodeRefTest_214, DefaultConstruction_ScalarIsEmpty_214) {
  EXPECT_TRUE(ref->scalar().empty());
}

// Test default tag is empty
TEST_F(NodeRefTest_214, DefaultConstruction_TagIsEmpty_214) {
  EXPECT_TRUE(ref->tag().empty());
}

// Test mark_defined makes the node defined
TEST_F(NodeRefTest_214, MarkDefined_MakesNodeDefined_214) {
  ref->mark_defined();
  EXPECT_TRUE(ref->is_defined());
}

// Test set_type to Scalar
TEST_F(NodeRefTest_214, SetType_Scalar_214) {
  ref->set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, ref->type());
}

// Test set_type to Sequence
TEST_F(NodeRefTest_214, SetType_Sequence_214) {
  ref->set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, ref->type());
}

// Test set_type to Map
TEST_F(NodeRefTest_214, SetType_Map_214) {
  ref->set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, ref->type());
}

// Test set_type to Null
TEST_F(NodeRefTest_214, SetType_Null_214) {
  ref->set_type(NodeType::Scalar);
  ref->set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, ref->type());
}

// Test set_type to Undefined
TEST_F(NodeRefTest_214, SetType_Undefined_214) {
  ref->set_type(NodeType::Scalar);
  ref->set_type(NodeType::Undefined);
  EXPECT_EQ(NodeType::Undefined, ref->type());
}

// Test set_scalar
TEST_F(NodeRefTest_214, SetScalar_BasicString_214) {
  ref->set_type(NodeType::Scalar);
  ref->set_scalar("hello");
  EXPECT_EQ("hello", ref->scalar());
}

// Test set_scalar with empty string
TEST_F(NodeRefTest_214, SetScalar_EmptyString_214) {
  ref->set_type(NodeType::Scalar);
  ref->set_scalar("");
  EXPECT_EQ("", ref->scalar());
}

// Test set_scalar overwrites previous value
TEST_F(NodeRefTest_214, SetScalar_OverwritesPrevious_214) {
  ref->set_type(NodeType::Scalar);
  ref->set_scalar("first");
  ref->set_scalar("second");
  EXPECT_EQ("second", ref->scalar());
}

// Test set_tag
TEST_F(NodeRefTest_214, SetTag_BasicTag_214) {
  ref->set_tag("!mytag");
  EXPECT_EQ("!mytag", ref->tag());
}

// Test set_tag with empty string
TEST_F(NodeRefTest_214, SetTag_EmptyTag_214) {
  ref->set_tag("");
  EXPECT_EQ("", ref->tag());
}

// Test set_null
TEST_F(NodeRefTest_214, SetNull_SetsTypeToNull_214) {
  ref->set_type(NodeType::Scalar);
  ref->set_scalar("something");
  ref->set_null();
  EXPECT_EQ(NodeType::Null, ref->type());
}

// Test set_mark
TEST_F(NodeRefTest_214, SetMark_214) {
  Mark mark;
  mark.line = 5;
  mark.column = 10;
  mark.pos = 42;
  ref->set_mark(mark);
  EXPECT_EQ(5, ref->mark().line);
  EXPECT_EQ(10, ref->mark().column);
  EXPECT_EQ(42, ref->mark().pos);
}

// Test default mark is null mark
TEST_F(NodeRefTest_214, DefaultMark_IsNullMark_214) {
  const Mark& m = ref->mark();
  EXPECT_EQ(Mark::null_mark().line, m.line);
  EXPECT_EQ(Mark::null_mark().column, m.column);
  EXPECT_EQ(Mark::null_mark().pos, m.pos);
}

// Test set_style
TEST_F(NodeRefTest_214, SetStyle_Flow_214) {
  ref->set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, ref->style());
}

// Test set_style Block
TEST_F(NodeRefTest_214, SetStyle_Block_214) {
  ref->set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, ref->style());
}

// Test set_style Default
TEST_F(NodeRefTest_214, SetStyle_Default_214) {
  ref->set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, ref->style());
}

// Test size of empty node is 0
TEST_F(NodeRefTest_214, Size_EmptyNode_IsZero_214) {
  EXPECT_EQ(0u, ref->size());
}

// Test size of a sequence after push_back
TEST_F(NodeRefTest_214, PushBack_IncreasesSize_214) {
  ref->set_type(NodeType::Sequence);
  node& n = create_node();
  n.set_scalar("value1");
  ref->push_back(n, pMemory);
  EXPECT_EQ(1u, ref->size());
}

// Test push_back multiple items
TEST_F(NodeRefTest_214, PushBack_MultipleItems_214) {
  ref->set_type(NodeType::Sequence);
  node& n1 = create_node();
  n1.set_scalar("v1");
  node& n2 = create_node();
  n2.set_scalar("v2");
  node& n3 = create_node();
  n3.set_scalar("v3");
  ref->push_back(n1, pMemory);
  ref->push_back(n2, pMemory);
  ref->push_back(n3, pMemory);
  EXPECT_EQ(3u, ref->size());
}

// Test insert key-value into map
TEST_F(NodeRefTest_214, Insert_KeyValue_IncreasesSize_214) {
  ref->set_type(NodeType::Map);
  node& key = create_node();
  key.set_scalar("key1");
  node& value = create_node();
  value.set_scalar("val1");
  ref->insert(key, value, pMemory);
  EXPECT_EQ(1u, ref->size());
}

// Test insert multiple key-value pairs
TEST_F(NodeRefTest_214, Insert_MultipleKeyValues_214) {
  ref->set_type(NodeType::Map);
  for (int i = 0; i < 5; i++) {
    node& key = create_node();
    key.set_scalar("key" + std::to_string(i));
    node& value = create_node();
    value.set_scalar("val" + std::to_string(i));
    ref->insert(key, value, pMemory);
  }
  EXPECT_EQ(5u, ref->size());
}

// Test get on a map with string key
TEST_F(NodeRefTest_214, Get_ExistingKey_ReturnsNode_214) {
  ref->set_type(NodeType::Map);
  node& key = create_node();
  key.set_scalar("mykey");
  node& value = create_node();
  value.set_scalar("myvalue");
  ref->insert(key, value, pMemory);

  node* result = ref->get(std::string("mykey"), pMemory);
  EXPECT_NE(nullptr, result);
}

// Test get on a map with non-existing key
TEST_F(NodeRefTest_214, Get_NonExistingKey_ReturnsNull_214) {
  ref->set_type(NodeType::Map);
  node& key = create_node();
  key.set_scalar("mykey");
  node& value = create_node();
  value.set_scalar("myvalue");
  ref->insert(key, value, pMemory);

  node* result = ref->get(std::string("otherkey"), pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test remove on a map
TEST_F(NodeRefTest_214, Remove_ExistingKey_ReturnsTrue_214) {
  ref->set_type(NodeType::Map);
  node& key = create_node();
  key.set_scalar("removekey");
  node& value = create_node();
  value.set_scalar("removeval");
  ref->insert(key, value, pMemory);

  bool removed = ref->remove(std::string("removekey"), pMemory);
  EXPECT_TRUE(removed);
}

// Test remove on a map with non-existing key
TEST_F(NodeRefTest_214, Remove_NonExistingKey_ReturnsFalse_214) {
  ref->set_type(NodeType::Map);
  node& key = create_node();
  key.set_scalar("existingkey");
  node& value = create_node();
  value.set_scalar("val");
  ref->insert(key, value, pMemory);

  bool removed = ref->remove(std::string("nonexistent"), pMemory);
  EXPECT_FALSE(removed);
}

// Test remove with node reference
TEST_F(NodeRefTest_214, Remove_WithNodeRef_ExistingKey_ReturnsTrue_214) {
  ref->set_type(NodeType::Map);
  node& key = create_node();
  key.set_scalar("nodekey");
  node& value = create_node();
  value.set_scalar("nodeval");
  ref->insert(key, value, pMemory);

  bool removed = ref->remove(key, pMemory);
  EXPECT_TRUE(removed);
}

// Test remove with node reference for non-existing key
TEST_F(NodeRefTest_214, Remove_WithNodeRef_NonExistingKey_ReturnsFalse_214) {
  ref->set_type(NodeType::Map);
  node& key = create_node();
  key.set_scalar("realkey");
  node& value = create_node();
  value.set_scalar("realval");
  ref->insert(key, value, pMemory);

  node& otherKey = create_node();
  otherKey.set_scalar("fakekey");
  bool removed = ref->remove(otherKey, pMemory);
  EXPECT_FALSE(removed);
}

// Test get with node reference
TEST_F(NodeRefTest_214, Get_WithNodeRef_ExistingKey_214) {
  ref->set_type(NodeType::Map);
  node& key = create_node();
  key.set_scalar("nkey");
  node& value = create_node();
  value.set_scalar("nval");
  ref->insert(key, value, pMemory);

  node* result = ref->get(key, pMemory);
  EXPECT_NE(nullptr, result);
}

// Test get with node reference for non-existing key
TEST_F(NodeRefTest_214, Get_WithNodeRef_NonExistingKey_214) {
  ref->set_type(NodeType::Map);
  node& key = create_node();
  key.set_scalar("nkey2");
  node& value = create_node();
  value.set_scalar("nval2");
  ref->insert(key, value, pMemory);

  node& otherKey = create_node();
  otherKey.set_scalar("nothere");
  node* result = ref->get(otherKey, pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test begin and end iterators for empty sequence
TEST_F(NodeRefTest_214, BeginEnd_EmptySequence_AreEqual_214) {
  ref->set_type(NodeType::Sequence);
  EXPECT_EQ(ref->begin(), ref->end());
}

// Test begin and end for non-empty sequence
TEST_F(NodeRefTest_214, BeginEnd_NonEmptySequence_AreNotEqual_214) {
  ref->set_type(NodeType::Sequence);
  node& n = create_node();
  n.set_scalar("item");
  ref->push_back(n, pMemory);
  EXPECT_NE(ref->begin(), ref->end());
}

// Test set_data copies data from another node_ref
TEST_F(NodeRefTest_214, SetData_CopiesFromOther_214) {
  node_ref other;
  other.set_type(NodeType::Scalar);
  other.set_scalar("copied_value");
  other.set_tag("!copied_tag");
  other.mark_defined();

  ref->set_data(other);
  EXPECT_EQ("copied_value", ref->scalar());
  EXPECT_EQ("!copied_tag", ref->tag());
  EXPECT_EQ(NodeType::Scalar, ref->type());
  EXPECT_TRUE(ref->is_defined());
}

// Test setting scalar with long string
TEST_F(NodeRefTest_214, SetScalar_LongString_214) {
  ref->set_type(NodeType::Scalar);
  std::string longStr(10000, 'x');
  ref->set_scalar(longStr);
  EXPECT_EQ(longStr, ref->scalar());
}

// Test setting scalar with special characters
TEST_F(NodeRefTest_214, SetScalar_SpecialCharacters_214) {
  ref->set_type(NodeType::Scalar);
  ref->set_scalar("hello\nworld\ttab\0null");
  // The string will be truncated at \0 due to C-string behavior in std::string ctor
  // but set_scalar takes const std::string&, so it depends on how it's constructed
  EXPECT_FALSE(ref->scalar().empty());
}

// Test force_insert
TEST_F(NodeRefTest_214, ForceInsert_AddsToMap_214) {
  ref->set_type(NodeType::Map);
  ref->force_insert(std::string("forcekey"), std::string("forceval"), pMemory);
  EXPECT_EQ(1u, ref->size());
}

// Test force_insert multiple with same key
TEST_F(NodeRefTest_214, ForceInsert_DuplicateKeys_214) {
  ref->set_type(NodeType::Map);
  ref->force_insert(std::string("dup"), std::string("val1"), pMemory);
  ref->force_insert(std::string("dup"), std::string("val2"), pMemory);
  // force_insert should allow duplicates
  EXPECT_EQ(2u, ref->size());
}

// Test size on empty map
TEST_F(NodeRefTest_214, Size_EmptyMap_IsZero_214) {
  ref->set_type(NodeType::Map);
  EXPECT_EQ(0u, ref->size());
}

// Test type changes clear previous data - sequence to scalar
TEST_F(NodeRefTest_214, SetType_SequenceToScalar_ClearsSequence_214) {
  ref->set_type(NodeType::Sequence);
  node& n = create_node();
  n.set_scalar("item");
  ref->push_back(n, pMemory);
  EXPECT_EQ(1u, ref->size());

  ref->set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, ref->type());
}

// Test switching type from Map to Null
TEST_F(NodeRefTest_214, SetType_MapToNull_214) {
  ref->set_type(NodeType::Map);
  node& key = create_node();
  key.set_scalar("k");
  node& value = create_node();
  value.set_scalar("v");
  ref->insert(key, value, pMemory);

  ref->set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, ref->type());
}

// Test scalar with unicode-like content
TEST_F(NodeRefTest_214, SetScalar_UnicodeContent_214) {
  ref->set_type(NodeType::Scalar);
  std::string unicodeStr = u8"こんにちは世界";
  ref->set_scalar(unicodeStr);
  EXPECT_EQ(unicodeStr, ref->scalar());
}

// Test size after remove decreases
TEST_F(NodeRefTest_214, Remove_DecreasesSize_214) {
  ref->set_type(NodeType::Map);
  node& key1 = create_node();
  key1.set_scalar("k1");
  node& val1 = create_node();
  val1.set_scalar("v1");
  ref->insert(key1, val1, pMemory);

  node& key2 = create_node();
  key2.set_scalar("k2");
  node& val2 = create_node();
  val2.set_scalar("v2");
  ref->insert(key2, val2, pMemory);

  EXPECT_EQ(2u, ref->size());
  ref->remove(std::string("k1"), pMemory);
  EXPECT_EQ(1u, ref->size());
}

}  // namespace detail
}  // namespace YAML
