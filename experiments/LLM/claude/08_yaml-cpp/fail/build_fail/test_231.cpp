#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/node_data.h"
#include "yaml-cpp/node/detail/memory.h"
#include "yaml-cpp/node/detail/node.h"

namespace YAML {
namespace detail {

class NodeRefTest_231 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = create_shared_memory();
  }

  shared_memory_holder pMemory;
};

// Test default construction - node should not be defined initially
TEST_F(NodeRefTest_231, DefaultConstruction_IsNotDefined_231) {
  node_ref ref;
  // A default-constructed node_ref should exist but might not be "defined"
  // until mark_defined is called
  EXPECT_FALSE(ref.is_defined());
}

// Test mark_defined makes the node defined
TEST_F(NodeRefTest_231, MarkDefined_MakesNodeDefined_231) {
  node_ref ref;
  ref.mark_defined();
  EXPECT_TRUE(ref.is_defined());
}

// Test default type
TEST_F(NodeRefTest_231, DefaultType_IsUndefined_231) {
  node_ref ref;
  EXPECT_EQ(NodeType::Undefined, ref.type());
}

// Test set_type to Null
TEST_F(NodeRefTest_231, SetType_Null_231) {
  node_ref ref;
  ref.set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, ref.type());
}

// Test set_type to Scalar
TEST_F(NodeRefTest_231, SetType_Scalar_231) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, ref.type());
}

// Test set_type to Sequence
TEST_F(NodeRefTest_231, SetType_Sequence_231) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, ref.type());
}

// Test set_type to Map
TEST_F(NodeRefTest_231, SetType_Map_231) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, ref.type());
}

// Test set_null
TEST_F(NodeRefTest_231, SetNull_SetsTypeToNull_231) {
  node_ref ref;
  ref.set_null();
  EXPECT_EQ(NodeType::Null, ref.type());
}

// Test set_scalar and scalar getter
TEST_F(NodeRefTest_231, SetScalar_GetScalar_231) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("hello");
  EXPECT_EQ("hello", ref.scalar());
}

// Test set_scalar with empty string
TEST_F(NodeRefTest_231, SetScalar_EmptyString_231) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("");
  EXPECT_EQ("", ref.scalar());
}

// Test set_tag and tag getter
TEST_F(NodeRefTest_231, SetTag_GetTag_231) {
  node_ref ref;
  ref.set_tag("!mytag");
  EXPECT_EQ("!mytag", ref.tag());
}

// Test set_tag with empty string
TEST_F(NodeRefTest_231, SetTag_EmptyString_231) {
  node_ref ref;
  ref.set_tag("");
  EXPECT_EQ("", ref.tag());
}

// Test set_style and style getter
TEST_F(NodeRefTest_231, SetStyle_Default_231) {
  node_ref ref;
  ref.set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, ref.style());
}

TEST_F(NodeRefTest_231, SetStyle_Block_231) {
  node_ref ref;
  ref.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, ref.style());
}

TEST_F(NodeRefTest_231, SetStyle_Flow_231) {
  node_ref ref;
  ref.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, ref.style());
}

// Test mark
TEST_F(NodeRefTest_231, SetMark_GetMark_231) {
  node_ref ref;
  Mark m;
  m.line = 5;
  m.column = 10;
  m.pos = 42;
  ref.set_mark(m);
  const Mark& result = ref.mark();
  EXPECT_EQ(5, result.line);
  EXPECT_EQ(10, result.column);
  EXPECT_EQ(42, result.pos);
}

// Test size for empty sequence
TEST_F(NodeRefTest_231, Size_EmptySequence_231) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  EXPECT_EQ(0u, ref.size());
}

// Test size for empty map
TEST_F(NodeRefTest_231, Size_EmptyMap_231) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  EXPECT_EQ(0u, ref.size());
}

// Test push_back increases size for sequence
TEST_F(NodeRefTest_231, PushBack_IncreasesSize_231) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);

  node& n = pMemory->create_node();
  n.set_scalar("value1");

  ref.push_back(n, pMemory);
  EXPECT_EQ(1u, ref.size());
}

// Test push_back multiple elements
TEST_F(NodeRefTest_231, PushBack_MultipleElements_231) {
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

// Test insert into map
TEST_F(NodeRefTest_231, Insert_IntoMap_231) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("key1");
  node& value = pMemory->create_node();
  value.set_scalar("value1");

  ref.insert(key, value, pMemory);
  EXPECT_EQ(1u, ref.size());
}

// Test get with string key from map
TEST_F(NodeRefTest_231, Get_StringKey_Existing_231) {
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

// Test get with string key - non-existing
TEST_F(NodeRefTest_231, Get_StringKey_NonExisting_231) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node* result = ref.get(std::string("nonexistent"), pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test get with integer index from sequence
TEST_F(NodeRefTest_231, Get_IntegerIndex_Existing_231) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);

  node& n = pMemory->create_node();
  n.set_scalar("value0");
  ref.push_back(n, pMemory);

  node* result = ref.get(std::size_t(0), pMemory);
  EXPECT_NE(nullptr, result);
}

// Test get with integer index - out of range
TEST_F(NodeRefTest_231, Get_IntegerIndex_OutOfRange_231) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);

  node* result = ref.get(std::size_t(5), pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test remove with string key - existing key
TEST_F(NodeRefTest_231, Remove_StringKey_Existing_231) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("removekey");
  node& value = pMemory->create_node();
  value.set_scalar("removevalue");

  ref.insert(key, value, pMemory);
  EXPECT_EQ(1u, ref.size());

  bool removed = ref.remove(std::string("removekey"), pMemory);
  EXPECT_TRUE(removed);
}

// Test remove with string key - non-existing key
TEST_F(NodeRefTest_231, Remove_StringKey_NonExisting_231) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  bool removed = ref.remove(std::string("nonexistent"), pMemory);
  EXPECT_FALSE(removed);
}

// Test remove with node key - existing
TEST_F(NodeRefTest_231, Remove_NodeKey_Existing_231) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("nodekey");
  node& value = pMemory->create_node();
  value.set_scalar("nodevalue");

  ref.insert(key, value, pMemory);
  EXPECT_EQ(1u, ref.size());

  bool removed = ref.remove(key, pMemory);
  EXPECT_TRUE(removed);
}

// Test remove with node key - non-existing
TEST_F(NodeRefTest_231, Remove_NodeKey_NonExisting_231) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("nonexistentkey");

  bool removed = ref.remove(key, pMemory);
  EXPECT_FALSE(removed);
}

// Test remove from sequence by index
TEST_F(NodeRefTest_231, Remove_IntIndex_FromSequence_231) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);

  node& n1 = pMemory->create_node();
  n1.set_scalar("elem0");
  node& n2 = pMemory->create_node();
  n2.set_scalar("elem1");

  ref.push_back(n1, pMemory);
  ref.push_back(n2, pMemory);
  EXPECT_EQ(2u, ref.size());

  bool removed = ref.remove(std::size_t(0), pMemory);
  EXPECT_TRUE(removed);
}

// Test remove from sequence by out-of-range index
TEST_F(NodeRefTest_231, Remove_IntIndex_OutOfRange_231) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);

  node& n = pMemory->create_node();
  n.set_scalar("elem0");
  ref.push_back(n, pMemory);

  bool removed = ref.remove(std::size_t(10), pMemory);
  EXPECT_FALSE(removed);
}

// Test begin/end for empty sequence
TEST_F(NodeRefTest_231, BeginEnd_EmptySequence_231) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  EXPECT_EQ(ref.begin(), ref.end());
}

// Test begin/end for non-empty sequence
TEST_F(NodeRefTest_231, BeginEnd_NonEmptySequence_231) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);

  node& n = pMemory->create_node();
  n.set_scalar("value");
  ref.push_back(n, pMemory);

  EXPECT_NE(ref.begin(), ref.end());
}

// Test set_data copies from another node_ref
TEST_F(NodeRefTest_231, SetData_CopiesFromOther_231) {
  node_ref src;
  src.set_type(NodeType::Scalar);
  src.set_scalar("copied");
  src.set_tag("!tag");

  node_ref dst;
  dst.set_data(src);

  EXPECT_EQ(NodeType::Scalar, dst.type());
  EXPECT_EQ("copied", dst.scalar());
  EXPECT_EQ("!tag", dst.tag());
}

// Test force_insert into map
TEST_F(NodeRefTest_231, ForceInsert_IntoMap_231) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  ref.force_insert(std::string("key1"), std::string("value1"), pMemory);
  EXPECT_EQ(1u, ref.size());

  ref.force_insert(std::string("key2"), std::string("value2"), pMemory);
  EXPECT_EQ(2u, ref.size());
}

// Test force_insert with duplicate key (force should still insert)
TEST_F(NodeRefTest_231, ForceInsert_DuplicateKey_231) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  ref.force_insert(std::string("key"), std::string("value1"), pMemory);
  ref.force_insert(std::string("key"), std::string("value2"), pMemory);
  EXPECT_EQ(2u, ref.size());
}

// Test multiple inserts and removes on map
TEST_F(NodeRefTest_231, InsertAndRemoveMultiple_Map_231) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node& k1 = pMemory->create_node();
  k1.set_scalar("k1");
  node& v1 = pMemory->create_node();
  v1.set_scalar("v1");

  node& k2 = pMemory->create_node();
  k2.set_scalar("k2");
  node& v2 = pMemory->create_node();
  v2.set_scalar("v2");

  node& k3 = pMemory->create_node();
  k3.set_scalar("k3");
  node& v3 = pMemory->create_node();
  v3.set_scalar("v3");

  ref.insert(k1, v1, pMemory);
  ref.insert(k2, v2, pMemory);
  ref.insert(k3, v3, pMemory);
  EXPECT_EQ(3u, ref.size());

  EXPECT_TRUE(ref.remove(std::string("k2"), pMemory));
  // After removal, verify get returns null for removed key
  EXPECT_EQ(nullptr, ref.get(std::string("k2"), pMemory));

  // Others should still be accessible
  EXPECT_NE(nullptr, ref.get(std::string("k1"), pMemory));
  EXPECT_NE(nullptr, ref.get(std::string("k3"), pMemory));
}

// Test that set_scalar changes the scalar value
TEST_F(NodeRefTest_231, SetScalar_OverwritesPrevious_231) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("first");
  EXPECT_EQ("first", ref.scalar());

  ref.set_scalar("second");
  EXPECT_EQ("second", ref.scalar());
}

// Test that set_type changes from one type to another
TEST_F(NodeRefTest_231, SetType_ChangeType_231) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, ref.type());

  ref.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, ref.type());
}

// Test set_mark with default mark
TEST_F(NodeRefTest_231, SetMark_DefaultMark_231) {
  node_ref ref;
  Mark m;
  ref.set_mark(m);
  // Default mark values
  const Mark& result = ref.mark();
  EXPECT_EQ(Mark::null_mark().line, result.line);
  EXPECT_EQ(Mark::null_mark().column, result.column);
}

// Test get with node reference key
TEST_F(NodeRefTest_231, Get_NodeKey_Existing_231) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("nodegetkey");
  node& value = pMemory->create_node();
  value.set_scalar("nodegetvalue");

  ref.insert(key, value, pMemory);

  node* result = ref.get(key, pMemory);
  EXPECT_NE(nullptr, result);
}

// Test get with node reference key - not found
TEST_F(NodeRefTest_231, Get_NodeKey_NonExisting_231) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("missingkey");

  node* result = ref.get(key, pMemory);
  EXPECT_EQ(nullptr, result);
}

}  // namespace detail
}  // namespace YAML
