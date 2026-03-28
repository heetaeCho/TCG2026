#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/memory.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/type.h"
#include "yaml-cpp/emitterstyle.h"
#include "yaml-cpp/mark.h"

namespace YAML {
namespace detail {

class NodeRefTest_230 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = shared_memory_holder(new Memory);
  }

  shared_memory_holder pMemory;
};

// Test default construction - node should not be defined initially
TEST_F(NodeRefTest_230, DefaultConstruction_IsNotDefined_230) {
  node_ref ref;
  // A freshly constructed node_ref might have Undefined type
  EXPECT_EQ(ref.type(), NodeType::Undefined);
}

// Test is_defined returns false for freshly constructed node_ref
TEST_F(NodeRefTest_230, DefaultConstruction_IsDefinedFalse_230) {
  node_ref ref;
  EXPECT_FALSE(ref.is_defined());
}

// Test mark_defined makes node defined
TEST_F(NodeRefTest_230, MarkDefined_MakesNodeDefined_230) {
  node_ref ref;
  ref.mark_defined();
  EXPECT_TRUE(ref.is_defined());
}

// Test set_type to Null
TEST_F(NodeRefTest_230, SetType_Null_230) {
  node_ref ref;
  ref.set_type(NodeType::Null);
  EXPECT_EQ(ref.type(), NodeType::Null);
}

// Test set_type to Scalar
TEST_F(NodeRefTest_230, SetType_Scalar_230) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  EXPECT_EQ(ref.type(), NodeType::Scalar);
}

// Test set_type to Sequence
TEST_F(NodeRefTest_230, SetType_Sequence_230) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  EXPECT_EQ(ref.type(), NodeType::Sequence);
}

// Test set_type to Map
TEST_F(NodeRefTest_230, SetType_Map_230) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  EXPECT_EQ(ref.type(), NodeType::Map);
}

// Test set_null sets type to Null
TEST_F(NodeRefTest_230, SetNull_SetsTypeNull_230) {
  node_ref ref;
  ref.set_null();
  EXPECT_EQ(ref.type(), NodeType::Null);
}

// Test set_scalar sets scalar value
TEST_F(NodeRefTest_230, SetScalar_SetsScalarValue_230) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("hello");
  EXPECT_EQ(ref.scalar(), "hello");
}

// Test set_scalar with empty string
TEST_F(NodeRefTest_230, SetScalar_EmptyString_230) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("");
  EXPECT_EQ(ref.scalar(), "");
}

// Test set_tag and tag retrieval
TEST_F(NodeRefTest_230, SetTag_RetrievesTag_230) {
  node_ref ref;
  ref.set_tag("!custom_tag");
  EXPECT_EQ(ref.tag(), "!custom_tag");
}

// Test set_tag with empty string
TEST_F(NodeRefTest_230, SetTag_EmptyTag_230) {
  node_ref ref;
  ref.set_tag("");
  EXPECT_EQ(ref.tag(), "");
}

// Test set_style for Block
TEST_F(NodeRefTest_230, SetStyle_Block_230) {
  node_ref ref;
  ref.set_style(EmitterStyle::Block);
  EXPECT_EQ(ref.style(), EmitterStyle::Block);
}

// Test set_style for Flow
TEST_F(NodeRefTest_230, SetStyle_Flow_230) {
  node_ref ref;
  ref.set_style(EmitterStyle::Flow);
  EXPECT_EQ(ref.style(), EmitterStyle::Flow);
}

// Test set_style for Default
TEST_F(NodeRefTest_230, SetStyle_Default_230) {
  node_ref ref;
  ref.set_style(EmitterStyle::Default);
  EXPECT_EQ(ref.style(), EmitterStyle::Default);
}

// Test set_mark and mark retrieval
TEST_F(NodeRefTest_230, SetMark_RetrievesMark_230) {
  node_ref ref;
  Mark m;
  m.line = 5;
  m.column = 10;
  m.pos = 50;
  ref.set_mark(m);
  const Mark& retrieved = ref.mark();
  EXPECT_EQ(retrieved.line, 5);
  EXPECT_EQ(retrieved.column, 10);
  EXPECT_EQ(retrieved.pos, 50);
}

// Test size of empty sequence
TEST_F(NodeRefTest_230, Size_EmptySequence_230) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  EXPECT_EQ(ref.size(), 0u);
}

// Test size of empty map
TEST_F(NodeRefTest_230, Size_EmptyMap_230) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  EXPECT_EQ(ref.size(), 0u);
}

// Test push_back increases size for sequence
TEST_F(NodeRefTest_230, PushBack_IncreasesSize_230) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);

  node& n = pMemory->create_node();
  n.set_scalar("value1");

  ref.push_back(n, pMemory);
  EXPECT_EQ(ref.size(), 1u);
}

// Test push_back multiple elements
TEST_F(NodeRefTest_230, PushBack_MultipleElements_230) {
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
  EXPECT_EQ(ref.size(), 3u);
}

// Test insert into map increases size
TEST_F(NodeRefTest_230, Insert_IncreasesSize_230) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("key1");
  node& value = pMemory->create_node();
  value.set_scalar("value1");

  ref.insert(key, value, pMemory);
  EXPECT_EQ(ref.size(), 1u);
}

// Test get with string key on map
TEST_F(NodeRefTest_230, Get_StringKey_ReturnsNode_230) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("mykey");
  node& value = pMemory->create_node();
  value.set_scalar("myvalue");

  ref.insert(key, value, pMemory);

  node* result = ref.get(std::string("mykey"), pMemory);
  EXPECT_NE(result, nullptr);
}

// Test get with non-existent string key returns null or creates
TEST_F(NodeRefTest_230, Get_NonExistentKey_230) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node* result = ref.get(std::string("nonexistent"), pMemory);
  // Depending on implementation, this might return nullptr or a new node
  // We just verify it doesn't crash
}

// Test get with index on sequence
TEST_F(NodeRefTest_230, Get_IndexKey_OnSequence_230) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);

  node& n1 = pMemory->create_node();
  n1.set_scalar("value0");
  node& n2 = pMemory->create_node();
  n2.set_scalar("value1");

  ref.push_back(n1, pMemory);
  ref.push_back(n2, pMemory);

  node* result = ref.get(std::size_t(0), pMemory);
  EXPECT_NE(result, nullptr);
}

// Test get with node key
TEST_F(NodeRefTest_230, Get_NodeKey_230) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("nodekey");
  node& value = pMemory->create_node();
  value.set_scalar("nodevalue");

  ref.insert(key, value, pMemory);

  node* result = ref.get(key, pMemory);
  EXPECT_NE(result, nullptr);
}

// Test remove with string key
TEST_F(NodeRefTest_230, Remove_StringKey_230) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("removekey");
  node& value = pMemory->create_node();
  value.set_scalar("removevalue");

  ref.insert(key, value, pMemory);
  EXPECT_EQ(ref.size(), 1u);

  bool removed = ref.remove(std::string("removekey"), pMemory);
  EXPECT_TRUE(removed);
}

// Test remove with non-existent key returns false
TEST_F(NodeRefTest_230, Remove_NonExistentKey_ReturnsFalse_230) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  bool removed = ref.remove(std::string("nonexistent"), pMemory);
  EXPECT_FALSE(removed);
}

// Test remove with node key
TEST_F(NodeRefTest_230, Remove_NodeKey_230) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("noderemovekey");
  node& value = pMemory->create_node();
  value.set_scalar("noderemovevalue");

  ref.insert(key, value, pMemory);

  bool removed = ref.remove(key, pMemory);
  EXPECT_TRUE(removed);
}

// Test begin and end iterators on empty sequence
TEST_F(NodeRefTest_230, BeginEnd_EmptySequence_230) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  EXPECT_EQ(ref.begin(), ref.end());
}

// Test begin and end iterators on non-empty sequence
TEST_F(NodeRefTest_230, BeginEnd_NonEmptySequence_230) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);

  node& n1 = pMemory->create_node();
  n1.set_scalar("val");
  ref.push_back(n1, pMemory);

  EXPECT_NE(ref.begin(), ref.end());
}

// Test set_data copies data from another node_ref
TEST_F(NodeRefTest_230, SetData_CopiesFromOther_230) {
  node_ref ref1;
  ref1.set_type(NodeType::Scalar);
  ref1.set_scalar("copied_value");
  ref1.set_tag("!tag");

  node_ref ref2;
  ref2.set_data(ref1);

  EXPECT_EQ(ref2.type(), NodeType::Scalar);
  EXPECT_EQ(ref2.scalar(), "copied_value");
  EXPECT_EQ(ref2.tag(), "!tag");
}

// Test changing type resets content
TEST_F(NodeRefTest_230, SetType_ChangingType_230) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("test");
  EXPECT_EQ(ref.type(), NodeType::Scalar);

  ref.set_type(NodeType::Sequence);
  EXPECT_EQ(ref.type(), NodeType::Sequence);
  EXPECT_EQ(ref.size(), 0u);
}

// Test force_insert on map
TEST_F(NodeRefTest_230, ForceInsert_AddsToMap_230) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  ref.force_insert(std::string("forcekey"), std::string("forcevalue"), pMemory);
  EXPECT_EQ(ref.size(), 1u);
}

// Test force_insert duplicate keys
TEST_F(NodeRefTest_230, ForceInsert_DuplicateKeys_230) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  ref.force_insert(std::string("key"), std::string("value1"), pMemory);
  ref.force_insert(std::string("key"), std::string("value2"), pMemory);
  // force_insert should allow duplicate keys
  EXPECT_EQ(ref.size(), 2u);
}

// Test set_scalar overwrites previous scalar
TEST_F(NodeRefTest_230, SetScalar_OverwritesPrevious_230) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("first");
  EXPECT_EQ(ref.scalar(), "first");

  ref.set_scalar("second");
  EXPECT_EQ(ref.scalar(), "second");
}

// Test set_tag overwrites previous tag
TEST_F(NodeRefTest_230, SetTag_OverwritesPrevious_230) {
  node_ref ref;
  ref.set_tag("!tag1");
  EXPECT_EQ(ref.tag(), "!tag1");

  ref.set_tag("!tag2");
  EXPECT_EQ(ref.tag(), "!tag2");
}

// Test mark with default values
TEST_F(NodeRefTest_230, Mark_DefaultValues_230) {
  node_ref ref;
  const Mark& m = ref.mark();
  // Default mark should have specific default values
  // Just verify we can access it without crash
  (void)m.line;
  (void)m.column;
  (void)m.pos;
}

// Test scalar on non-scalar type (boundary case)
TEST_F(NodeRefTest_230, Scalar_OnNullType_230) {
  node_ref ref;
  ref.set_type(NodeType::Null);
  // Accessing scalar on null type - should return empty or not crash
  const std::string& s = ref.scalar();
  (void)s;
}

// Test large number of push_backs
TEST_F(NodeRefTest_230, PushBack_ManyElements_230) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);

  const int count = 100;
  for (int i = 0; i < count; i++) {
    node& n = pMemory->create_node();
    n.set_scalar(std::to_string(i));
    ref.push_back(n, pMemory);
  }
  EXPECT_EQ(ref.size(), static_cast<std::size_t>(count));
}

// Test multiple inserts into map
TEST_F(NodeRefTest_230, Insert_MultipleEntries_230) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  for (int i = 0; i < 10; i++) {
    node& key = pMemory->create_node();
    key.set_scalar("key" + std::to_string(i));
    node& value = pMemory->create_node();
    value.set_scalar("value" + std::to_string(i));
    ref.insert(key, value, pMemory);
  }
  EXPECT_EQ(ref.size(), 10u);
}

// Test set_type with same type (idempotent for same type)
TEST_F(NodeRefTest_230, SetType_SameTypeTwice_230) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  EXPECT_EQ(ref.type(), NodeType::Map);
  ref.set_type(NodeType::Map);
  EXPECT_EQ(ref.type(), NodeType::Map);
}

}  // namespace detail
}  // namespace YAML
