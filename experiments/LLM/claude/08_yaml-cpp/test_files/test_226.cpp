#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/node_data.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"
#include "yaml-cpp/node/type.h"
#include "yaml-cpp/emitterstyle.h"
#include "yaml-cpp/mark.h"

namespace YAML {
namespace detail {

class NodeRefTest_226 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = std::make_shared<memory_holder>();
    // Ensure memory holder is properly initialized
  }

  shared_memory_holder pMemory;
};

// Test default construction - node should not be defined initially
TEST_F(NodeRefTest_226, DefaultConstructionIsNotDefined_226) {
  node_ref ref;
  EXPECT_FALSE(ref.is_defined());
}

// Test default type is Null
TEST_F(NodeRefTest_226, DefaultTypeIsNull_226) {
  node_ref ref;
  EXPECT_EQ(NodeType::Null, ref.type());
}

// Test mark_defined makes node defined
TEST_F(NodeRefTest_226, MarkDefinedMakesNodeDefined_226) {
  node_ref ref;
  ref.mark_defined();
  EXPECT_TRUE(ref.is_defined());
}

// Test set_type to Sequence
TEST_F(NodeRefTest_226, SetTypeSequence_226) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, ref.type());
}

// Test set_type to Map
TEST_F(NodeRefTest_226, SetTypeMap_226) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, ref.type());
}

// Test set_type to Scalar
TEST_F(NodeRefTest_226, SetTypeScalar_226) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, ref.type());
}

// Test set_type to Null
TEST_F(NodeRefTest_226, SetTypeNull_226) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, ref.type());
}

// Test set_type to Undefined
TEST_F(NodeRefTest_226, SetTypeUndefined_226) {
  node_ref ref;
  ref.set_type(NodeType::Undefined);
  EXPECT_EQ(NodeType::Undefined, ref.type());
}

// Test set_scalar and scalar retrieval
TEST_F(NodeRefTest_226, SetScalarAndRetrieve_226) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("hello");
  EXPECT_EQ("hello", ref.scalar());
}

// Test set_scalar with empty string
TEST_F(NodeRefTest_226, SetScalarEmptyString_226) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("");
  EXPECT_EQ("", ref.scalar());
}

// Test set_tag and tag retrieval
TEST_F(NodeRefTest_226, SetTagAndRetrieve_226) {
  node_ref ref;
  ref.set_tag("!mytag");
  EXPECT_EQ("!mytag", ref.tag());
}

// Test set_tag with empty string
TEST_F(NodeRefTest_226, SetTagEmptyString_226) {
  node_ref ref;
  ref.set_tag("");
  EXPECT_EQ("", ref.tag());
}

// Test set_style and style retrieval
TEST_F(NodeRefTest_226, SetStyleBlock_226) {
  node_ref ref;
  ref.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, ref.style());
}

// Test set_style Flow
TEST_F(NodeRefTest_226, SetStyleFlow_226) {
  node_ref ref;
  ref.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, ref.style());
}

// Test set_style Default
TEST_F(NodeRefTest_226, SetStyleDefault_226) {
  node_ref ref;
  ref.set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, ref.style());
}

// Test set_null sets type to Null
TEST_F(NodeRefTest_226, SetNullSetsTypeNull_226) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_null();
  EXPECT_EQ(NodeType::Null, ref.type());
}

// Test set_mark and mark retrieval
TEST_F(NodeRefTest_226, SetMarkAndRetrieve_226) {
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

// Test default mark is null mark
TEST_F(NodeRefTest_226, DefaultMarkIsNullMark_226) {
  node_ref ref;
  const Mark& m = ref.mark();
  EXPECT_EQ(Mark::null_mark().line, m.line);
  EXPECT_EQ(Mark::null_mark().column, m.column);
  EXPECT_EQ(Mark::null_mark().pos, m.pos);
}

// Test size of empty sequence
TEST_F(NodeRefTest_226, EmptySequenceSize_226) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  EXPECT_EQ(0u, ref.size());
}

// Test size of empty map
TEST_F(NodeRefTest_226, EmptyMapSize_226) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  EXPECT_EQ(0u, ref.size());
}

// Test begin equals end for empty sequence
TEST_F(NodeRefTest_226, BeginEqualsEndForEmptySequence_226) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  EXPECT_EQ(ref.begin(), ref.end());
}

// Test begin equals end for empty map
TEST_F(NodeRefTest_226, BeginEqualsEndForEmptyMap_226) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  EXPECT_EQ(ref.begin(), ref.end());
}

// Test push_back increases size for sequence
TEST_F(NodeRefTest_226, PushBackIncreasesSequenceSize_226) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);

  memory mem;
  node& n = mem.create_node();
  n.set_type(NodeType::Scalar);
  n.set_scalar("value1");

  shared_memory_holder pMem = mem.create_memory();
  ref.push_back(n, pMem);
  EXPECT_EQ(1u, ref.size());
}

// Test push_back multiple elements
TEST_F(NodeRefTest_226, PushBackMultipleElements_226) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);

  memory mem;
  node& n1 = mem.create_node();
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("a");

  node& n2 = mem.create_node();
  n2.set_type(NodeType::Scalar);
  n2.set_scalar("b");

  shared_memory_holder pMem = mem.create_memory();
  ref.push_back(n1, pMem);
  ref.push_back(n2, pMem);
  EXPECT_EQ(2u, ref.size());
}

// Test begin != end after push_back
TEST_F(NodeRefTest_226, BeginNotEqualsEndAfterPushBack_226) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);

  memory mem;
  node& n = mem.create_node();
  n.set_type(NodeType::Scalar);
  n.set_scalar("item");

  shared_memory_holder pMem = mem.create_memory();
  ref.push_back(n, pMem);
  EXPECT_NE(ref.begin(), ref.end());
}

// Test set_data copies data from another node_ref
TEST_F(NodeRefTest_226, SetDataCopiesFromAnotherNodeRef_226) {
  node_ref src;
  src.set_type(NodeType::Scalar);
  src.set_scalar("copied_value");
  src.set_tag("!tag");
  src.mark_defined();

  node_ref dst;
  dst.set_data(src);

  EXPECT_EQ(NodeType::Scalar, dst.type());
  EXPECT_EQ("copied_value", dst.scalar());
  EXPECT_EQ("!tag", dst.tag());
}

// Test scalar returns empty for non-scalar type
TEST_F(NodeRefTest_226, ScalarEmptyForNonScalar_226) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  EXPECT_EQ("", ref.scalar());
}

// Test re-setting type clears previous state
TEST_F(NodeRefTest_226, ResetTypeClearsPreviousState_226) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("hello");
  EXPECT_EQ("hello", ref.scalar());

  ref.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, ref.type());
  EXPECT_EQ(0u, ref.size());
}

// Test size for Null type
TEST_F(NodeRefTest_226, SizeForNullType_226) {
  node_ref ref;
  EXPECT_EQ(0u, ref.size());
}

// Test insert for map type
TEST_F(NodeRefTest_226, InsertIncreasesMapSize_226) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  memory mem;
  node& key = mem.create_node();
  key.set_type(NodeType::Scalar);
  key.set_scalar("key1");

  node& val = mem.create_node();
  val.set_type(NodeType::Scalar);
  val.set_scalar("val1");

  shared_memory_holder pMem = mem.create_memory();
  ref.insert(key, val, pMem);
  EXPECT_EQ(1u, ref.size());
}

// Test multiple inserts into map
TEST_F(NodeRefTest_226, MultipleInsertsIntoMap_226) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  memory mem;
  shared_memory_holder pMem = mem.create_memory();

  node& key1 = mem.create_node();
  key1.set_type(NodeType::Scalar);
  key1.set_scalar("k1");
  node& val1 = mem.create_node();
  val1.set_type(NodeType::Scalar);
  val1.set_scalar("v1");
  ref.insert(key1, val1, pMem);

  node& key2 = mem.create_node();
  key2.set_type(NodeType::Scalar);
  key2.set_scalar("k2");
  node& val2 = mem.create_node();
  val2.set_type(NodeType::Scalar);
  val2.set_scalar("v2");
  ref.insert(key2, val2, pMem);

  EXPECT_EQ(2u, ref.size());
}

// Test set_scalar overwrites previous scalar
TEST_F(NodeRefTest_226, SetScalarOverwritesPrevious_226) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("first");
  EXPECT_EQ("first", ref.scalar());

  ref.set_scalar("second");
  EXPECT_EQ("second", ref.scalar());
}

// Test set_tag overwrites previous tag
TEST_F(NodeRefTest_226, SetTagOverwritesPrevious_226) {
  node_ref ref;
  ref.set_tag("!tag1");
  EXPECT_EQ("!tag1", ref.tag());

  ref.set_tag("!tag2");
  EXPECT_EQ("!tag2", ref.tag());
}

// Test set_scalar with special characters
TEST_F(NodeRefTest_226, SetScalarSpecialCharacters_226) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("hello\nworld\ttab");
  EXPECT_EQ("hello\nworld\ttab", ref.scalar());
}

// Test set_scalar with very long string
TEST_F(NodeRefTest_226, SetScalarLongString_226) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  std::string longStr(10000, 'x');
  ref.set_scalar(longStr);
  EXPECT_EQ(longStr, ref.scalar());
}

}  // namespace detail
}  // namespace YAML
