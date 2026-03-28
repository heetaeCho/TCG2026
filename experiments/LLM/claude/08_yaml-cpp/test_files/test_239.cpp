#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeTest_239 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = create_shared_memory();
  }

  shared_memory_holder pMemory;
};

// Test default construction - node should exist and have default state
TEST_F(NodeTest_239, DefaultConstruction_IsNotDefined_239) {
  node n;
  EXPECT_FALSE(n.is_defined());
}

TEST_F(NodeTest_239, DefaultConstruction_TypeIsUndefined_239) {
  node n;
  EXPECT_EQ(NodeType::Undefined, n.type());
}

TEST_F(NodeTest_239, DefaultConstruction_RefIsNotNull_239) {
  node n;
  EXPECT_NE(nullptr, n.ref());
}

// Test mark
TEST_F(NodeTest_239, DefaultMark_IsDefault_239) {
  node n;
  const Mark& m = n.mark();
  EXPECT_EQ(Mark::null_mark().line, m.line);
  EXPECT_EQ(Mark::null_mark().column, m.column);
}

TEST_F(NodeTest_239, SetMark_ReturnsSetMark_239) {
  node n;
  Mark mark(10, 20, 30);
  n.set_mark(mark);
  EXPECT_EQ(10, n.mark().line);
  EXPECT_EQ(20, n.mark().column);
  EXPECT_EQ(30, n.mark().pos);
}

// Test is() - identity check
TEST_F(NodeTest_239, Is_SameNode_ReturnsTrue_239) {
  node n;
  EXPECT_TRUE(n.is(n));
}

TEST_F(NodeTest_239, Is_DifferentNode_ReturnsFalse_239) {
  node n1;
  node n2;
  EXPECT_FALSE(n1.is(n2));
}

// Test mark_defined
TEST_F(NodeTest_239, MarkDefined_MakesNodeDefined_239) {
  node n;
  EXPECT_FALSE(n.is_defined());
  n.mark_defined();
  EXPECT_TRUE(n.is_defined());
}

// Test set_type
TEST_F(NodeTest_239, SetType_Scalar_239) {
  node n;
  n.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, n.type());
}

TEST_F(NodeTest_239, SetType_Sequence_239) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
}

TEST_F(NodeTest_239, SetType_Map_239) {
  node n;
  n.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, n.type());
}

TEST_F(NodeTest_239, SetType_Null_239) {
  node n;
  n.set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, n.type());
}

// Test set_null
TEST_F(NodeTest_239, SetNull_TypeIsNull_239) {
  node n;
  n.set_null();
  EXPECT_EQ(NodeType::Null, n.type());
}

// Test scalar
TEST_F(NodeTest_239, SetScalar_ReturnsScalar_239) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");
  EXPECT_EQ("hello", n.scalar());
}

TEST_F(NodeTest_239, SetScalar_EmptyString_239) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("");
  EXPECT_EQ("", n.scalar());
}

TEST_F(NodeTest_239, SetScalar_OverwritesPrevious_239) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("first");
  n.set_scalar("second");
  EXPECT_EQ("second", n.scalar());
}

// Test tag
TEST_F(NodeTest_239, SetTag_ReturnsTag_239) {
  node n;
  n.set_tag("!mytag");
  EXPECT_EQ("!mytag", n.tag());
}

TEST_F(NodeTest_239, SetTag_EmptyString_239) {
  node n;
  n.set_tag("");
  EXPECT_EQ("", n.tag());
}

// Test style
TEST_F(NodeTest_239, SetStyle_Block_239) {
  node n;
  n.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, n.style());
}

TEST_F(NodeTest_239, SetStyle_Flow_239) {
  node n;
  n.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, n.style());
}

TEST_F(NodeTest_239, SetStyle_Default_239) {
  node n;
  n.set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, n.style());
}

// Test sequence operations
TEST_F(NodeTest_239, Sequence_SizeInitiallyZero_239) {
  node n;
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(0u, n.size());
}

TEST_F(NodeTest_239, Sequence_PushBackIncreasesSize_239) {
  node n;
  n.set_type(NodeType::Sequence);

  node child;
  child.set_type(NodeType::Scalar);
  child.set_scalar("item1");

  n.push_back(child, pMemory);
  EXPECT_EQ(1u, n.size());
}

TEST_F(NodeTest_239, Sequence_PushBackMultiple_239) {
  node n;
  n.set_type(NodeType::Sequence);

  node c1, c2, c3;
  c1.set_type(NodeType::Scalar);
  c1.set_scalar("a");
  c2.set_type(NodeType::Scalar);
  c2.set_scalar("b");
  c3.set_type(NodeType::Scalar);
  c3.set_scalar("c");

  n.push_back(c1, pMemory);
  n.push_back(c2, pMemory);
  n.push_back(c3, pMemory);
  EXPECT_EQ(3u, n.size());
}

TEST_F(NodeTest_239, Sequence_BeginEndIteratorsValid_239) {
  node n;
  n.set_type(NodeType::Sequence);

  // Empty sequence: begin == end
  EXPECT_TRUE(n.begin() == n.end());

  node child;
  child.set_type(NodeType::Scalar);
  child.set_scalar("item");
  n.push_back(child, pMemory);

  // Non-empty: begin != end
  EXPECT_FALSE(n.begin() == n.end());
}

// Test map operations
TEST_F(NodeTest_239, Map_InsertIncreasesSize_239) {
  node n;
  n.set_type(NodeType::Map);

  node key;
  key.set_type(NodeType::Scalar);
  key.set_scalar("key1");

  node value;
  value.set_type(NodeType::Scalar);
  value.set_scalar("value1");

  n.insert(key, value, pMemory);
  EXPECT_EQ(1u, n.size());
}

TEST_F(NodeTest_239, Map_GetExistingKey_239) {
  node n;
  n.set_type(NodeType::Map);

  node key;
  key.set_type(NodeType::Scalar);
  key.set_scalar("mykey");

  node value;
  value.set_type(NodeType::Scalar);
  value.set_scalar("myvalue");

  n.insert(key, value, pMemory);

  node* result = n.get(std::string("mykey"), pMemory);
  EXPECT_NE(nullptr, result);
}

TEST_F(NodeTest_239, Map_GetNonExistingKey_ReturnsNull_239) {
  node n;
  n.set_type(NodeType::Map);

  node* result = n.get(std::string("nonexistent"), pMemory);
  EXPECT_EQ(nullptr, result);
}

TEST_F(NodeTest_239, Map_RemoveExistingKey_239) {
  node n;
  n.set_type(NodeType::Map);

  node key;
  key.set_type(NodeType::Scalar);
  key.set_scalar("removeMe");

  node value;
  value.set_type(NodeType::Scalar);
  value.set_scalar("val");

  n.insert(key, value, pMemory);
  EXPECT_EQ(1u, n.size());

  bool removed = n.remove(std::string("removeMe"), pMemory);
  EXPECT_TRUE(removed);
}

TEST_F(NodeTest_239, Map_RemoveNonExistingKey_ReturnsFalse_239) {
  node n;
  n.set_type(NodeType::Map);

  bool removed = n.remove(std::string("nope"), pMemory);
  EXPECT_FALSE(removed);
}

// Test set_data
TEST_F(NodeTest_239, SetData_CopiesDataFromOtherNode_239) {
  node src;
  src.set_type(NodeType::Scalar);
  src.set_scalar("copied");
  src.set_tag("!tag");

  node dst;
  dst.set_data(src);

  EXPECT_EQ(NodeType::Scalar, dst.type());
  EXPECT_EQ("copied", dst.scalar());
  EXPECT_EQ("!tag", dst.tag());
}

// Test set_ref
TEST_F(NodeTest_239, SetRef_SharesRefWithOtherNode_239) {
  node src;
  src.set_type(NodeType::Scalar);
  src.set_scalar("shared");

  node dst;
  dst.set_ref(src);

  EXPECT_EQ("shared", dst.scalar());
  EXPECT_EQ(NodeType::Scalar, dst.type());
}

// Test equals
TEST_F(NodeTest_239, Equals_ScalarMatchesString_239) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("test");

  EXPECT_TRUE(n.equals(std::string("test"), pMemory));
}

TEST_F(NodeTest_239, Equals_ScalarDoesNotMatchDifferentString_239) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("test");

  EXPECT_FALSE(n.equals(std::string("other"), pMemory));
}

TEST_F(NodeTest_239, Equals_CStringOverload_239) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");

  EXPECT_TRUE(n.equals("hello", pMemory));
  EXPECT_FALSE(n.equals("world", pMemory));
}

// Test force_insert for map
TEST_F(NodeTest_239, ForceInsert_InsertsIntoMap_239) {
  node n;
  n.set_type(NodeType::Map);

  n.force_insert(std::string("k1"), std::string("v1"), pMemory);
  EXPECT_EQ(1u, n.size());

  n.force_insert(std::string("k2"), std::string("v2"), pMemory);
  EXPECT_EQ(2u, n.size());
}

// Test add_dependency does not crash
TEST_F(NodeTest_239, AddDependency_DoesNotCrash_239) {
  node n1;
  node n2;
  EXPECT_NO_THROW(n1.add_dependency(n2));
}

// Test get with node key
TEST_F(NodeTest_239, Map_GetWithNodeKey_239) {
  node n;
  n.set_type(NodeType::Map);

  node key;
  key.set_type(NodeType::Scalar);
  key.set_scalar("nodekey");

  node value;
  value.set_type(NodeType::Scalar);
  value.set_scalar("nodevalue");

  n.insert(key, value, pMemory);

  node* result = n.get(key, pMemory);
  EXPECT_NE(nullptr, result);
}

// Test remove with node key
TEST_F(NodeTest_239, Map_RemoveWithNodeKey_239) {
  node n;
  n.set_type(NodeType::Map);

  node key;
  key.set_type(NodeType::Scalar);
  key.set_scalar("rkey");

  node value;
  value.set_type(NodeType::Scalar);
  value.set_scalar("rval");

  n.insert(key, value, pMemory);
  EXPECT_EQ(1u, n.size());

  bool removed = n.remove(key, pMemory);
  EXPECT_TRUE(removed);
}

// Test type transitions
TEST_F(NodeTest_239, TypeTransition_UndefinedToNull_239) {
  node n;
  EXPECT_EQ(NodeType::Undefined, n.type());
  n.set_null();
  EXPECT_EQ(NodeType::Null, n.type());
}

TEST_F(NodeTest_239, TypeTransition_ScalarToSequence_239) {
  node n;
  n.set_type(NodeType::Scalar);
  n.set_scalar("value");
  EXPECT_EQ(NodeType::Scalar, n.type());

  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
}

// Boundary: very long scalar
TEST_F(NodeTest_239, LongScalar_239) {
  node n;
  n.set_type(NodeType::Scalar);
  std::string longStr(10000, 'x');
  n.set_scalar(longStr);
  EXPECT_EQ(longStr, n.scalar());
}

// Boundary: special characters in scalar
TEST_F(NodeTest_239, SpecialCharactersInScalar_239) {
  node n;
  n.set_type(NodeType::Scalar);
  std::string special = "hello\nworld\t\r\0test";
  n.set_scalar(special);
  EXPECT_EQ(special, n.scalar());
}

// Test identity after set_ref
TEST_F(NodeTest_239, SetRef_NodesShareIdentity_239) {
  node src;
  src.set_type(NodeType::Scalar);
  src.set_scalar("ref_test");

  node dst;
  dst.set_ref(src);

  // After set_ref, modifying via src should be visible through dst
  src.set_scalar("updated");
  EXPECT_EQ("updated", dst.scalar());
}

}  // namespace detail
}  // namespace YAML
