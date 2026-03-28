#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node_data.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeDataTest_207 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = std::make_shared<memory_holder>();
  }

  shared_memory_holder pMemory;
};

// === Type Tests ===

TEST_F(NodeDataTest_207, DefaultConstructor_TypeIsUndefined_207) {
  node_data nd;
  // Not defined, so type() should return Undefined
  EXPECT_EQ(NodeType::Undefined, nd.type());
}

TEST_F(NodeDataTest_207, DefaultConstructor_IsNotDefined_207) {
  node_data nd;
  EXPECT_FALSE(nd.is_defined());
}

TEST_F(NodeDataTest_207, MarkDefined_MakesNodeDefined_207) {
  node_data nd;
  nd.mark_defined();
  EXPECT_TRUE(nd.is_defined());
}

TEST_F(NodeDataTest_207, MarkDefined_TypeBecomesNull_207) {
  node_data nd;
  nd.mark_defined();
  // Default m_type is Null
  EXPECT_EQ(NodeType::Null, nd.type());
}

TEST_F(NodeDataTest_207, SetType_Sequence_207) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, nd.type());
}

TEST_F(NodeDataTest_207, SetType_Map_207) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, nd.type());
}

TEST_F(NodeDataTest_207, SetType_Scalar_207) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, nd.type());
}

TEST_F(NodeDataTest_207, SetType_Null_207) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Sequence);
  nd.set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, nd.type());
}

TEST_F(NodeDataTest_207, SetNull_SetsTypeToNull_207) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Scalar);
  nd.set_null();
  EXPECT_EQ(NodeType::Null, nd.type());
}

// === Tag Tests ===

TEST_F(NodeDataTest_207, DefaultTag_IsEmpty_207) {
  node_data nd;
  EXPECT_TRUE(nd.tag().empty());
}

TEST_F(NodeDataTest_207, SetTag_ReturnsCorrectTag_207) {
  node_data nd;
  nd.set_tag("!mytag");
  EXPECT_EQ("!mytag", nd.tag());
}

TEST_F(NodeDataTest_207, SetTag_EmptyString_207) {
  node_data nd;
  nd.set_tag("sometag");
  nd.set_tag("");
  EXPECT_EQ("", nd.tag());
}

// === Scalar Tests ===

TEST_F(NodeDataTest_207, DefaultScalar_IsEmpty_207) {
  node_data nd;
  EXPECT_TRUE(nd.scalar().empty());
}

TEST_F(NodeDataTest_207, SetScalar_ReturnsCorrectValue_207) {
  node_data nd;
  nd.mark_defined();
  nd.set_scalar("hello world");
  EXPECT_EQ("hello world", nd.scalar());
}

TEST_F(NodeDataTest_207, SetScalar_EmptyString_207) {
  node_data nd;
  nd.mark_defined();
  nd.set_scalar("");
  EXPECT_EQ("", nd.scalar());
}

// === Style Tests ===

TEST_F(NodeDataTest_207, SetStyle_Block_207) {
  node_data nd;
  nd.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, nd.style());
}

TEST_F(NodeDataTest_207, SetStyle_Flow_207) {
  node_data nd;
  nd.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, nd.style());
}

TEST_F(NodeDataTest_207, SetStyle_Default_207) {
  node_data nd;
  nd.set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, nd.style());
}

// === Mark Tests ===

TEST_F(NodeDataTest_207, DefaultMark_IsNullMark_207) {
  node_data nd;
  const Mark& m = nd.mark();
  EXPECT_EQ(Mark::null_mark().pos, m.pos);
  EXPECT_EQ(Mark::null_mark().line, m.line);
  EXPECT_EQ(Mark::null_mark().column, m.column);
}

TEST_F(NodeDataTest_207, SetMark_ReturnsCorrectMark_207) {
  node_data nd;
  Mark mark;
  mark.pos = 10;
  mark.line = 5;
  mark.column = 3;
  nd.set_mark(mark);
  const Mark& m = nd.mark();
  EXPECT_EQ(10, m.pos);
  EXPECT_EQ(5, m.line);
  EXPECT_EQ(3, m.column);
}

// === Size Tests ===

TEST_F(NodeDataTest_207, SizeOfNull_IsZero_207) {
  node_data nd;
  nd.mark_defined();
  EXPECT_EQ(0u, nd.size());
}

TEST_F(NodeDataTest_207, SizeOfEmptySequence_IsZero_207) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Sequence);
  EXPECT_EQ(0u, nd.size());
}

TEST_F(NodeDataTest_207, SizeOfEmptyMap_IsZero_207) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);
  EXPECT_EQ(0u, nd.size());
}

// === Sequence Push Back Tests ===

TEST_F(NodeDataTest_207, PushBack_IncreasesSize_207) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Sequence);

  node& n = pMemory->create_node();
  n.set_scalar("value1");

  nd.push_back(n, pMemory);
  EXPECT_EQ(1u, nd.size());
}

TEST_F(NodeDataTest_207, PushBack_MultipleTimes_207) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Sequence);

  node& n1 = pMemory->create_node();
  n1.set_scalar("v1");
  node& n2 = pMemory->create_node();
  n2.set_scalar("v2");
  node& n3 = pMemory->create_node();
  n3.set_scalar("v3");

  nd.push_back(n1, pMemory);
  nd.push_back(n2, pMemory);
  nd.push_back(n3, pMemory);
  EXPECT_EQ(3u, nd.size());
}

// === Map Insert Tests ===

TEST_F(NodeDataTest_207, Insert_IncreasesSize_207) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("key1");
  node& val = pMemory->create_node();
  val.set_scalar("val1");

  nd.insert(key, val, pMemory);
  EXPECT_EQ(1u, nd.size());
}

TEST_F(NodeDataTest_207, Insert_MultipleEntries_207) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);

  node& k1 = pMemory->create_node();
  k1.set_scalar("k1");
  node& v1 = pMemory->create_node();
  v1.set_scalar("v1");

  node& k2 = pMemory->create_node();
  k2.set_scalar("k2");
  node& v2 = pMemory->create_node();
  v2.set_scalar("v2");

  nd.insert(k1, v1, pMemory);
  nd.insert(k2, v2, pMemory);
  EXPECT_EQ(2u, nd.size());
}

// === Get Tests (Map) ===

TEST_F(NodeDataTest_207, GetByStringKey_ExistingKey_207) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("mykey");
  node& val = pMemory->create_node();
  val.set_scalar("myval");

  nd.insert(key, val, pMemory);

  const node* result = nd.get(std::string("mykey"), pMemory);
  EXPECT_NE(nullptr, result);
}

TEST_F(NodeDataTest_207, GetByStringKey_NonExistingKey_207) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);

  const node* result = nd.get(std::string("nonexistent"), pMemory);
  EXPECT_EQ(nullptr, result);
}

TEST_F(NodeDataTest_207, GetByNodeKey_ExistingKey_207) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("nodekey");
  node& val = pMemory->create_node();
  val.set_scalar("nodeval");

  nd.insert(key, val, pMemory);

  const node* result = nd.get(key, pMemory);
  EXPECT_NE(nullptr, result);
}

TEST_F(NodeDataTest_207, GetByNodeKey_NonExistingKey_207) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("nonexistent");

  const node* result = nd.get(key, pMemory);
  EXPECT_EQ(nullptr, result);
}

// === Remove Tests ===

TEST_F(NodeDataTest_207, RemoveByStringKey_ExistingKey_207) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("removekey");
  node& val = pMemory->create_node();
  val.set_scalar("removeval");

  nd.insert(key, val, pMemory);
  EXPECT_EQ(1u, nd.size());

  bool removed = nd.remove(std::string("removekey"), pMemory);
  EXPECT_TRUE(removed);
}

TEST_F(NodeDataTest_207, RemoveByStringKey_NonExistingKey_207) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);

  bool removed = nd.remove(std::string("nonexistent"), pMemory);
  EXPECT_FALSE(removed);
}

TEST_F(NodeDataTest_207, RemoveByNodeKey_ExistingKey_207) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("rkey");
  node& val = pMemory->create_node();
  val.set_scalar("rval");

  nd.insert(key, val, pMemory);

  bool removed = nd.remove(key, pMemory);
  EXPECT_TRUE(removed);
}

TEST_F(NodeDataTest_207, RemoveByNodeKey_NonExistingKey_207) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.set_scalar("does_not_exist");

  bool removed = nd.remove(key, pMemory);
  EXPECT_FALSE(removed);
}

// === Empty Scalar Tests ===

TEST_F(NodeDataTest_207, EmptyScalar_IsEmpty_207) {
  const std::string& empty = node_data::empty_scalar();
  EXPECT_TRUE(empty.empty());
}

TEST_F(NodeDataTest_207, EmptyScalar_ReturnsSameReference_207) {
  const std::string& e1 = node_data::empty_scalar();
  const std::string& e2 = node_data::empty_scalar();
  EXPECT_EQ(&e1, &e2);
}

// === Iterator Tests ===

TEST_F(NodeDataTest_207, BeginEndOnEmptySequence_207) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Sequence);
  EXPECT_EQ(nd.begin(), nd.end());
}

TEST_F(NodeDataTest_207, BeginEndOnEmptyMap_207) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);
  EXPECT_EQ(nd.begin(), nd.end());
}

TEST_F(NodeDataTest_207, IteratorOnSequenceWithElements_207) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Sequence);

  node& n1 = pMemory->create_node();
  n1.set_scalar("a");
  node& n2 = pMemory->create_node();
  n2.set_scalar("b");

  nd.push_back(n1, pMemory);
  nd.push_back(n2, pMemory);

  int count = 0;
  for (auto it = nd.begin(); it != nd.end(); ++it) {
    count++;
  }
  EXPECT_EQ(2, count);
}

TEST_F(NodeDataTest_207, IteratorOnMapWithElements_207) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);

  node& k1 = pMemory->create_node();
  k1.set_scalar("k1");
  node& v1 = pMemory->create_node();
  v1.set_scalar("v1");
  node& k2 = pMemory->create_node();
  k2.set_scalar("k2");
  node& v2 = pMemory->create_node();
  v2.set_scalar("v2");

  nd.insert(k1, v1, pMemory);
  nd.insert(k2, v2, pMemory);

  int count = 0;
  for (auto it = nd.begin(); it != nd.end(); ++it) {
    count++;
  }
  EXPECT_EQ(2, count);
}

// === Type Transition Tests ===

TEST_F(NodeDataTest_207, SetTypeFromSequenceToMap_207) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Sequence);

  node& n1 = pMemory->create_node();
  n1.set_scalar("elem");
  nd.push_back(n1, pMemory);

  nd.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, nd.type());
}

TEST_F(NodeDataTest_207, SetTypeFromMapToSequence_207) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);

  node& k = pMemory->create_node();
  k.set_scalar("k");
  node& v = pMemory->create_node();
  v.set_scalar("v");
  nd.insert(k, v, pMemory);

  nd.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, nd.type());
}

// === Undefined vs Defined ===

TEST_F(NodeDataTest_207, UndefinedNode_TypeIsUndefined_207) {
  node_data nd;
  // Not calling mark_defined
  EXPECT_EQ(NodeType::Undefined, nd.type());
  EXPECT_FALSE(nd.is_defined());
}

TEST_F(NodeDataTest_207, DefinedNode_SetTypeThenCheckType_207) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("test");
  EXPECT_EQ(NodeType::Scalar, nd.type());
  EXPECT_TRUE(nd.is_defined());
  EXPECT_EQ("test", nd.scalar());
}

// === Force Insert Tests ===

TEST_F(NodeDataTest_207, ForceInsert_IncreasesMapSize_207) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);

  nd.force_insert(std::string("fk1"), std::string("fv1"), pMemory);
  EXPECT_EQ(1u, nd.size());

  nd.force_insert(std::string("fk2"), std::string("fv2"), pMemory);
  EXPECT_EQ(2u, nd.size());
}

TEST_F(NodeDataTest_207, ForceInsert_DuplicateKeysAllowed_207) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Map);

  nd.force_insert(std::string("dup"), std::string("v1"), pMemory);
  nd.force_insert(std::string("dup"), std::string("v2"), pMemory);
  // force_insert should allow duplicate keys
  EXPECT_EQ(2u, nd.size());
}

// === Copy/Assignment Deleted ===

TEST_F(NodeDataTest_207, CopyConstructorDeleted_207) {
  EXPECT_FALSE(std::is_copy_constructible<node_data>::value);
}

TEST_F(NodeDataTest_207, CopyAssignmentDeleted_207) {
  EXPECT_FALSE(std::is_copy_assignable<node_data>::value);
}

// === Boundary: Setting scalar on different types ===

TEST_F(NodeDataTest_207, SetScalar_SetsTypeImplicitly_207) {
  node_data nd;
  nd.mark_defined();
  nd.set_scalar("boundary_test");
  EXPECT_EQ("boundary_test", nd.scalar());
}

// === Boundary: Size of scalar type ===

TEST_F(NodeDataTest_207, SizeOfScalar_IsZero_207) {
  node_data nd;
  nd.mark_defined();
  nd.set_type(NodeType::Scalar);
  nd.set_scalar("hello");
  EXPECT_EQ(0u, nd.size());
}

// === Push back on null type (should convert to sequence) ===

TEST_F(NodeDataTest_207, PushBackOnNull_ConvertsToSequence_207) {
  node_data nd;
  nd.mark_defined();
  // Type is Null by default

  node& n = pMemory->create_node();
  n.set_scalar("val");

  nd.push_back(n, pMemory);
  EXPECT_EQ(NodeType::Sequence, nd.type());
  EXPECT_EQ(1u, nd.size());
}

}  // namespace detail
}  // namespace YAML
