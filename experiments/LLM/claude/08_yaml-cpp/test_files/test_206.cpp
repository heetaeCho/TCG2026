#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node_data.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"
#include "yaml-cpp/node/type.h"
#include "yaml-cpp/emitterstyle.h"
#include "yaml-cpp/mark.h"

namespace YAML {
namespace detail {

class NodeDataTest_206 : public ::testing::Test {
 protected:
  void SetUp() override {
    m_memory = std::make_shared<memory_holder>();
    m_pMemory = m_memory->create_memory();
  }

  shared_memory_holder m_pMemory;
  std::shared_ptr<memory_holder> m_memory;
};

// Test default construction
TEST_F(NodeDataTest_206, DefaultConstruction_206) {
  node_data nd;
  EXPECT_FALSE(nd.is_defined());
  EXPECT_EQ(nd.type(), NodeType::Null);
  EXPECT_EQ(nd.scalar(), "");
  EXPECT_EQ(nd.tag(), "");
}

// Test mark_defined
TEST_F(NodeDataTest_206, MarkDefined_206) {
  node_data nd;
  EXPECT_FALSE(nd.is_defined());
  nd.mark_defined();
  EXPECT_TRUE(nd.is_defined());
}

// Test default mark is null mark
TEST_F(NodeDataTest_206, DefaultMarkIsNullMark_206) {
  node_data nd;
  const Mark& m = nd.mark();
  Mark null_mark = Mark::null_mark();
  EXPECT_EQ(m.line, null_mark.line);
  EXPECT_EQ(m.column, null_mark.column);
  EXPECT_EQ(m.pos, null_mark.pos);
}

// Test set_mark
TEST_F(NodeDataTest_206, SetMark_206) {
  node_data nd;
  Mark mark;
  mark.line = 10;
  mark.column = 20;
  mark.pos = 30;
  nd.set_mark(mark);
  const Mark& retrieved = nd.mark();
  EXPECT_EQ(retrieved.line, 10);
  EXPECT_EQ(retrieved.column, 20);
  EXPECT_EQ(retrieved.pos, 30);
}

// Test set_type to Sequence
TEST_F(NodeDataTest_206, SetTypeSequence_206) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  EXPECT_EQ(nd.type(), NodeType::Sequence);
}

// Test set_type to Map
TEST_F(NodeDataTest_206, SetTypeMap_206) {
  node_data nd;
  nd.set_type(NodeType::Map);
  EXPECT_EQ(nd.type(), NodeType::Map);
}

// Test set_type to Scalar
TEST_F(NodeDataTest_206, SetTypeScalar_206) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  EXPECT_EQ(nd.type(), NodeType::Scalar);
}

// Test set_type to Null
TEST_F(NodeDataTest_206, SetTypeNull_206) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  EXPECT_EQ(nd.type(), NodeType::Scalar);
  nd.set_type(NodeType::Null);
  EXPECT_EQ(nd.type(), NodeType::Null);
}

// Test set_type to Undefined
TEST_F(NodeDataTest_206, SetTypeUndefined_206) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_type(NodeType::Undefined);
  EXPECT_EQ(nd.type(), NodeType::Undefined);
}

// Test set_tag
TEST_F(NodeDataTest_206, SetTag_206) {
  node_data nd;
  nd.set_tag("!!str");
  EXPECT_EQ(nd.tag(), "!!str");
}

// Test set_tag empty string
TEST_F(NodeDataTest_206, SetTagEmpty_206) {
  node_data nd;
  nd.set_tag("");
  EXPECT_EQ(nd.tag(), "");
}

// Test set_tag overwrite
TEST_F(NodeDataTest_206, SetTagOverwrite_206) {
  node_data nd;
  nd.set_tag("first");
  EXPECT_EQ(nd.tag(), "first");
  nd.set_tag("second");
  EXPECT_EQ(nd.tag(), "second");
}

// Test set_null
TEST_F(NodeDataTest_206, SetNull_206) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("hello");
  nd.set_null();
  EXPECT_EQ(nd.type(), NodeType::Null);
}

// Test set_scalar
TEST_F(NodeDataTest_206, SetScalar_206) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("test_value");
  EXPECT_EQ(nd.scalar(), "test_value");
}

// Test set_scalar with empty string
TEST_F(NodeDataTest_206, SetScalarEmpty_206) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("");
  EXPECT_EQ(nd.scalar(), "");
}

// Test set_style
TEST_F(NodeDataTest_206, SetStyleDefault_206) {
  node_data nd;
  nd.set_style(EmitterStyle::Default);
  EXPECT_EQ(nd.style(), EmitterStyle::Default);
}

TEST_F(NodeDataTest_206, SetStyleBlock_206) {
  node_data nd;
  nd.set_style(EmitterStyle::Block);
  EXPECT_EQ(nd.style(), EmitterStyle::Block);
}

TEST_F(NodeDataTest_206, SetStyleFlow_206) {
  node_data nd;
  nd.set_style(EmitterStyle::Flow);
  EXPECT_EQ(nd.style(), EmitterStyle::Flow);
}

// Test empty_scalar
TEST_F(NodeDataTest_206, EmptyScalar_206) {
  const std::string& es = node_data::empty_scalar();
  EXPECT_EQ(es, "");
}

// Test size for empty node
TEST_F(NodeDataTest_206, SizeNullNode_206) {
  node_data nd;
  EXPECT_EQ(nd.size(), 0u);
}

// Test size for sequence
TEST_F(NodeDataTest_206, SizeSequence_206) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  EXPECT_EQ(nd.size(), 0u);
}

// Test size for map
TEST_F(NodeDataTest_206, SizeMap_206) {
  node_data nd;
  nd.set_type(NodeType::Map);
  EXPECT_EQ(nd.size(), 0u);
}

// Test push_back to sequence
TEST_F(NodeDataTest_206, PushBackToSequence_206) {
  node_data nd;
  nd.set_type(NodeType::Sequence);

  node& n = m_pMemory->create_node();
  n.set_data(node_data());
  nd.push_back(n, m_pMemory);
  EXPECT_EQ(nd.size(), 1u);
}

// Test push_back multiple items
TEST_F(NodeDataTest_206, PushBackMultiple_206) {
  node_data nd;
  nd.set_type(NodeType::Sequence);

  for (int i = 0; i < 5; ++i) {
    node& n = m_pMemory->create_node();
    nd.push_back(n, m_pMemory);
  }
  EXPECT_EQ(nd.size(), 5u);
}

// Test insert to map
TEST_F(NodeDataTest_206, InsertToMap_206) {
  node_data nd;
  nd.set_type(NodeType::Map);

  node& key = m_pMemory->create_node();
  key.set_scalar("key1");
  node& value = m_pMemory->create_node();
  value.set_scalar("value1");

  nd.insert(key, value, m_pMemory);
  EXPECT_EQ(nd.size(), 1u);
}

// Test insert multiple entries to map
TEST_F(NodeDataTest_206, InsertMultipleToMap_206) {
  node_data nd;
  nd.set_type(NodeType::Map);

  for (int i = 0; i < 3; ++i) {
    node& key = m_pMemory->create_node();
    key.set_scalar("key" + std::to_string(i));
    node& value = m_pMemory->create_node();
    value.set_scalar("value" + std::to_string(i));
    nd.insert(key, value, m_pMemory);
  }
  EXPECT_EQ(nd.size(), 3u);
}

// Test begin/end for empty sequence
TEST_F(NodeDataTest_206, BeginEndEmptySequence_206) {
  node_data nd;
  nd.set_type(NodeType::Sequence);
  EXPECT_EQ(nd.begin(), nd.end());
}

// Test begin/end for empty map
TEST_F(NodeDataTest_206, BeginEndEmptyMap_206) {
  node_data nd;
  nd.set_type(NodeType::Map);
  EXPECT_EQ(nd.begin(), nd.end());
}

// Test begin/end for sequence with elements
TEST_F(NodeDataTest_206, BeginEndSequenceWithElements_206) {
  node_data nd;
  nd.set_type(NodeType::Sequence);

  node& n = m_pMemory->create_node();
  nd.push_back(n, m_pMemory);

  EXPECT_NE(nd.begin(), nd.end());
}

// Test get on map with string key
TEST_F(NodeDataTest_206, GetFromMapStringKey_206) {
  node_data nd;
  nd.set_type(NodeType::Map);

  node& key = m_pMemory->create_node();
  key.set_scalar("mykey");
  node& value = m_pMemory->create_node();
  value.set_scalar("myvalue");

  nd.insert(key, value, m_pMemory);

  const node* result = nd.get(std::string("mykey"), m_pMemory);
  EXPECT_NE(result, nullptr);
}

// Test get with non-existent key returns null
TEST_F(NodeDataTest_206, GetNonExistentKey_206) {
  node_data nd;
  nd.set_type(NodeType::Map);

  const node* result = nd.get(std::string("nonexistent"), m_pMemory);
  EXPECT_EQ(result, nullptr);
}

// Test remove from map
TEST_F(NodeDataTest_206, RemoveFromMap_206) {
  node_data nd;
  nd.set_type(NodeType::Map);

  node& key = m_pMemory->create_node();
  key.set_scalar("removekey");
  node& value = m_pMemory->create_node();
  value.set_scalar("removevalue");

  nd.insert(key, value, m_pMemory);
  EXPECT_EQ(nd.size(), 1u);

  bool removed = nd.remove(std::string("removekey"), m_pMemory);
  EXPECT_TRUE(removed);
}

// Test remove non-existent key
TEST_F(NodeDataTest_206, RemoveNonExistentKey_206) {
  node_data nd;
  nd.set_type(NodeType::Map);

  bool removed = nd.remove(std::string("nonexistent"), m_pMemory);
  EXPECT_FALSE(removed);
}

// Test force_insert
TEST_F(NodeDataTest_206, ForceInsert_206) {
  node_data nd;
  nd.set_type(NodeType::Map);

  nd.force_insert(std::string("forcekey"), std::string("forcevalue"), m_pMemory);
  EXPECT_EQ(nd.size(), 1u);
}

// Test force_insert allows duplicate keys
TEST_F(NodeDataTest_206, ForceInsertDuplicateKeys_206) {
  node_data nd;
  nd.set_type(NodeType::Map);

  nd.force_insert(std::string("dupkey"), std::string("val1"), m_pMemory);
  nd.force_insert(std::string("dupkey"), std::string("val2"), m_pMemory);
  EXPECT_EQ(nd.size(), 2u);
}

// Test changing type resets data
TEST_F(NodeDataTest_206, ChangeTypeResetsData_206) {
  node_data nd;
  nd.set_type(NodeType::Sequence);

  node& n = m_pMemory->create_node();
  nd.push_back(n, m_pMemory);
  EXPECT_EQ(nd.size(), 1u);

  nd.set_type(NodeType::Map);
  EXPECT_EQ(nd.size(), 0u);
}

// Test set_scalar on non-scalar type should throw or change type
TEST_F(NodeDataTest_206, SetScalarImpliesScalarType_206) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("hello world");
  EXPECT_EQ(nd.scalar(), "hello world");
  EXPECT_EQ(nd.type(), NodeType::Scalar);
}

// Test copy constructor is deleted (compile-time, but we confirm the class is usable)
TEST_F(NodeDataTest_206, NodeDataIsNotCopyConstructible_206) {
  EXPECT_FALSE(std::is_copy_constructible<node_data>::value);
}

// Test assignment operator is deleted
TEST_F(NodeDataTest_206, NodeDataIsNotCopyAssignable_206) {
  EXPECT_FALSE(std::is_copy_assignable<node_data>::value);
}

// Test push_back to null node converts to sequence
TEST_F(NodeDataTest_206, PushBackToNullConvertsToSequence_206) {
  node_data nd;
  EXPECT_EQ(nd.type(), NodeType::Null);

  node& n = m_pMemory->create_node();
  nd.push_back(n, m_pMemory);
  EXPECT_EQ(nd.type(), NodeType::Sequence);
  EXPECT_EQ(nd.size(), 1u);
}

// Test get with node reference on map
TEST_F(NodeDataTest_206, GetWithNodeRef_206) {
  node_data nd;
  nd.set_type(NodeType::Map);

  node& key = m_pMemory->create_node();
  key.set_scalar("nodekey");
  node& value = m_pMemory->create_node();
  value.set_scalar("nodevalue");

  nd.insert(key, value, m_pMemory);

  node& lookupKey = m_pMemory->create_node();
  lookupKey.set_scalar("nodekey");

  const node* result = nd.get(lookupKey, m_pMemory);
  EXPECT_NE(result, nullptr);
}

// Test remove with node reference
TEST_F(NodeDataTest_206, RemoveWithNodeRef_206) {
  node_data nd;
  nd.set_type(NodeType::Map);

  node& key = m_pMemory->create_node();
  key.set_scalar("remkey");
  node& value = m_pMemory->create_node();
  value.set_scalar("remvalue");

  nd.insert(key, value, m_pMemory);

  node& removeKey = m_pMemory->create_node();
  removeKey.set_scalar("remkey");

  bool removed = nd.remove(removeKey, m_pMemory);
  EXPECT_TRUE(removed);
}

// Test sequence to map conversion via insert
TEST_F(NodeDataTest_206, SequenceConvertsToMapOnInsert_206) {
  node_data nd;
  nd.set_type(NodeType::Sequence);

  node& seqNode = m_pMemory->create_node();
  nd.push_back(seqNode, m_pMemory);
  EXPECT_EQ(nd.type(), NodeType::Sequence);

  node& key = m_pMemory->create_node();
  key.set_scalar("mapkey");
  node& value = m_pMemory->create_node();
  value.set_scalar("mapvalue");

  nd.insert(key, value, m_pMemory);
  EXPECT_EQ(nd.type(), NodeType::Map);
}

// Test set_type to same type (idempotent)
TEST_F(NodeDataTest_206, SetTypeSameTypeIdempotent_206) {
  node_data nd;
  nd.set_type(NodeType::Sequence);

  node& n = m_pMemory->create_node();
  nd.push_back(n, m_pMemory);
  EXPECT_EQ(nd.size(), 1u);

  nd.set_type(NodeType::Sequence);
  // Setting same type should not reset data
  EXPECT_EQ(nd.size(), 1u);
}

// Test empty_scalar returns reference to same object
TEST_F(NodeDataTest_206, EmptyScalarSameReference_206) {
  const std::string& ref1 = node_data::empty_scalar();
  const std::string& ref2 = node_data::empty_scalar();
  EXPECT_EQ(&ref1, &ref2);
}

// Test size for scalar type
TEST_F(NodeDataTest_206, SizeScalar_206) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  EXPECT_EQ(nd.size(), 0u);
}

// Test mark_defined does not change type
TEST_F(NodeDataTest_206, MarkDefinedDoesNotChangeType_206) {
  node_data nd;
  nd.set_type(NodeType::Scalar);
  nd.mark_defined();
  EXPECT_TRUE(nd.is_defined());
  EXPECT_EQ(nd.type(), NodeType::Scalar);
}

// Test set_mark does not change type
TEST_F(NodeDataTest_206, SetMarkDoesNotChangeType_206) {
  node_data nd;
  nd.set_type(NodeType::Map);
  Mark m;
  m.line = 5;
  m.column = 10;
  m.pos = 50;
  nd.set_mark(m);
  EXPECT_EQ(nd.type(), NodeType::Map);
  EXPECT_EQ(nd.mark().line, 5);
}

}  // namespace detail
}  // namespace YAML
