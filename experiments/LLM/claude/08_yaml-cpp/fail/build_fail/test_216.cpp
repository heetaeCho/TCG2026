#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/node_data.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"
#include "yaml-cpp/emitterstyle.h"
#include "yaml-cpp/node/type.h"
#include "yaml-cpp/mark.h"

namespace YAML {
namespace detail {

class NodeRefTest_216 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = std::make_shared<memory_holder>();
  }

  shared_memory_holder pMemory;
};

// Test default construction
TEST_F(NodeRefTest_216, DefaultConstruction_IsNotDefined_216) {
  node_ref ref;
  EXPECT_FALSE(ref.is_defined());
}

TEST_F(NodeRefTest_216, DefaultConstruction_TypeIsNull_216) {
  node_ref ref;
  EXPECT_EQ(NodeType::Null, ref.type());
}

TEST_F(NodeRefTest_216, DefaultConstruction_ScalarIsEmpty_216) {
  node_ref ref;
  EXPECT_TRUE(ref.scalar().empty());
}

TEST_F(NodeRefTest_216, DefaultConstruction_TagIsEmpty_216) {
  node_ref ref;
  EXPECT_TRUE(ref.tag().empty());
}

TEST_F(NodeRefTest_216, DefaultConstruction_StyleIsDefault_216) {
  node_ref ref;
  EXPECT_EQ(EmitterStyle::Default, ref.style());
}

TEST_F(NodeRefTest_216, DefaultConstruction_SizeIsZero_216) {
  node_ref ref;
  EXPECT_EQ(0u, ref.size());
}

// Test mark_defined
TEST_F(NodeRefTest_216, MarkDefined_BecomeDefined_216) {
  node_ref ref;
  ref.mark_defined();
  EXPECT_TRUE(ref.is_defined());
}

// Test set_type
TEST_F(NodeRefTest_216, SetType_Scalar_216) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, ref.type());
}

TEST_F(NodeRefTest_216, SetType_Sequence_216) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, ref.type());
}

TEST_F(NodeRefTest_216, SetType_Map_216) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, ref.type());
}

TEST_F(NodeRefTest_216, SetType_Null_216) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, ref.type());
}

TEST_F(NodeRefTest_216, SetType_Undefined_216) {
  node_ref ref;
  ref.set_type(NodeType::Undefined);
  EXPECT_EQ(NodeType::Undefined, ref.type());
}

// Test set_scalar
TEST_F(NodeRefTest_216, SetScalar_BasicString_216) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("hello");
  EXPECT_EQ("hello", ref.scalar());
}

TEST_F(NodeRefTest_216, SetScalar_EmptyString_216) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("");
  EXPECT_EQ("", ref.scalar());
}

TEST_F(NodeRefTest_216, SetScalar_OverwriteExisting_216) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("first");
  ref.set_scalar("second");
  EXPECT_EQ("second", ref.scalar());
}

// Test set_tag
TEST_F(NodeRefTest_216, SetTag_BasicTag_216) {
  node_ref ref;
  ref.set_tag("!!int");
  EXPECT_EQ("!!int", ref.tag());
}

TEST_F(NodeRefTest_216, SetTag_EmptyTag_216) {
  node_ref ref;
  ref.set_tag("");
  EXPECT_EQ("", ref.tag());
}

// Test set_style
TEST_F(NodeRefTest_216, SetStyle_Block_216) {
  node_ref ref;
  ref.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, ref.style());
}

TEST_F(NodeRefTest_216, SetStyle_Flow_216) {
  node_ref ref;
  ref.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, ref.style());
}

TEST_F(NodeRefTest_216, SetStyle_Default_216) {
  node_ref ref;
  ref.set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, ref.style());
}

// Test set_null
TEST_F(NodeRefTest_216, SetNull_TypeBecomesNull_216) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("test");
  ref.set_null();
  EXPECT_EQ(NodeType::Null, ref.type());
}

// Test set_mark
TEST_F(NodeRefTest_216, SetMark_ValidMark_216) {
  node_ref ref;
  Mark mark;
  mark.pos = 10;
  mark.line = 5;
  mark.column = 3;
  ref.set_mark(mark);
  EXPECT_EQ(5, ref.mark().line);
  EXPECT_EQ(3, ref.mark().column);
  EXPECT_EQ(10, ref.mark().pos);
}

TEST_F(NodeRefTest_216, SetMark_NullMark_216) {
  node_ref ref;
  ref.set_mark(Mark::null_mark());
  // Should not crash; null mark is valid
  const Mark& m = ref.mark();
  (void)m;
}

// Test set_data (copy data from another node_ref)
TEST_F(NodeRefTest_216, SetData_CopiesScalar_216) {
  node_ref src;
  src.set_type(NodeType::Scalar);
  src.set_scalar("copied");
  src.set_tag("!!str");
  src.set_style(EmitterStyle::Flow);
  src.mark_defined();

  node_ref dst;
  dst.set_data(src);

  EXPECT_EQ("copied", dst.scalar());
  EXPECT_EQ("!!str", dst.tag());
  EXPECT_EQ(EmitterStyle::Flow, dst.style());
}

// Test sequence operations
TEST_F(NodeRefTest_216, PushBack_IncreasesSize_216) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);

  node n;
  ref.push_back(n, pMemory);
  EXPECT_EQ(1u, ref.size());
}

TEST_F(NodeRefTest_216, PushBack_MultipleTimes_216) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);

  node n1, n2, n3;
  ref.push_back(n1, pMemory);
  ref.push_back(n2, pMemory);
  ref.push_back(n3, pMemory);
  EXPECT_EQ(3u, ref.size());
}

// Test begin/end on empty sequence
TEST_F(NodeRefTest_216, BeginEnd_EmptySequence_216) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  EXPECT_EQ(ref.begin(), ref.end());
}

// Test map operations
TEST_F(NodeRefTest_216, Insert_IncreasesSize_216) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node key, value;
  key.set_ref(node_ref());
  key.ref()->set_type(NodeType::Scalar);
  key.ref()->set_scalar("key1");

  ref.insert(key, value, pMemory);
  EXPECT_EQ(1u, ref.size());
}

// Test changing type clears content
TEST_F(NodeRefTest_216, ChangeType_ScalarToSequence_ClearsScalar_216) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("test");
  ref.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, ref.type());
  EXPECT_EQ(0u, ref.size());
}

TEST_F(NodeRefTest_216, ChangeType_SequenceToMap_216) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  node n;
  ref.push_back(n, pMemory);
  EXPECT_EQ(1u, ref.size());

  ref.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, ref.type());
}

// Test setting type to same type is idempotent
TEST_F(NodeRefTest_216, SetType_SameType_NoChange_216) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("value");
  ref.set_type(NodeType::Scalar);
  EXPECT_EQ("value", ref.scalar());
}

// Test long scalar values
TEST_F(NodeRefTest_216, SetScalar_LongString_216) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  std::string longStr(10000, 'a');
  ref.set_scalar(longStr);
  EXPECT_EQ(longStr, ref.scalar());
}

// Test scalar with special characters
TEST_F(NodeRefTest_216, SetScalar_SpecialCharacters_216) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("hello\nworld\t\r\n");
  EXPECT_EQ("hello\nworld\t\r\n", ref.scalar());
}

// Test tag with unicode-like content
TEST_F(NodeRefTest_216, SetTag_SpecialContent_216) {
  node_ref ref;
  ref.set_tag("!custom/tag");
  EXPECT_EQ("!custom/tag", ref.tag());
}

// Test size for null type
TEST_F(NodeRefTest_216, Size_NullType_216) {
  node_ref ref;
  EXPECT_EQ(0u, ref.size());
}

// Test size for scalar type
TEST_F(NodeRefTest_216, Size_ScalarType_216) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("test");
  EXPECT_EQ(0u, ref.size());
}

// Test that begin == end for non-collection types
TEST_F(NodeRefTest_216, BeginEnd_NullType_216) {
  node_ref ref;
  // For null type, begin should equal end
  EXPECT_EQ(ref.begin(), ref.end());
}

}  // namespace detail
}  // namespace YAML
