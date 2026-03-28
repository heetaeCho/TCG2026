#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeRefTest_225 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = std::make_shared<memory_holder>();
  }

  shared_memory_holder pMemory;
};

// Test that a default-constructed node_ref is not defined
TEST_F(NodeRefTest_225, DefaultConstructedIsNotDefined_225) {
  node_ref ref;
  EXPECT_FALSE(ref.is_defined());
}

// Test that a default-constructed node_ref has Null type
TEST_F(NodeRefTest_225, DefaultConstructedTypeIsNull_225) {
  node_ref ref;
  EXPECT_EQ(NodeType::Null, ref.type());
}

// Test mark_defined makes node defined
TEST_F(NodeRefTest_225, MarkDefinedMakesNodeDefined_225) {
  node_ref ref;
  ref.mark_defined();
  EXPECT_TRUE(ref.is_defined());
}

// Test set_type to Sequence
TEST_F(NodeRefTest_225, SetTypeSequence_225) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, ref.type());
}

// Test set_type to Map
TEST_F(NodeRefTest_225, SetTypeMap_225) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, ref.type());
}

// Test set_type to Scalar
TEST_F(NodeRefTest_225, SetTypeScalar_225) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, ref.type());
}

// Test set_null sets type to Null
TEST_F(NodeRefTest_225, SetNullSetsTypeNull_225) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_null();
  EXPECT_EQ(NodeType::Null, ref.type());
}

// Test set_scalar and scalar()
TEST_F(NodeRefTest_225, SetScalarAndGetScalar_225) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("hello");
  EXPECT_EQ("hello", ref.scalar());
}

// Test set_tag and tag()
TEST_F(NodeRefTest_225, SetTagAndGetTag_225) {
  node_ref ref;
  ref.set_tag("!custom");
  EXPECT_EQ("!custom", ref.tag());
}

// Test set_style and style()
TEST_F(NodeRefTest_225, SetStyleAndGetStyle_225) {
  node_ref ref;
  ref.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, ref.style());
}

// Test set_style Block
TEST_F(NodeRefTest_225, SetStyleBlock_225) {
  node_ref ref;
  ref.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, ref.style());
}

// Test default style is Default
TEST_F(NodeRefTest_225, DefaultStyleIsDefault_225) {
  node_ref ref;
  EXPECT_EQ(EmitterStyle::Default, ref.style());
}

// Test size of default node_ref is 0
TEST_F(NodeRefTest_225, DefaultSizeIsZero_225) {
  node_ref ref;
  EXPECT_EQ(0u, ref.size());
}

// Test size after pushing back to a sequence
TEST_F(NodeRefTest_225, SizeAfterPushBackSequence_225) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);

  node n;
  ref.push_back(n, pMemory);
  EXPECT_EQ(1u, ref.size());
}

// Test size after pushing back multiple elements
TEST_F(NodeRefTest_225, SizeAfterMultiplePushBack_225) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);

  node n1, n2, n3;
  ref.push_back(n1, pMemory);
  ref.push_back(n2, pMemory);
  ref.push_back(n3, pMemory);
  EXPECT_EQ(3u, ref.size());
}

// Test size of a map after insert
TEST_F(NodeRefTest_225, SizeAfterMapInsert_225) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node key, value;
  ref.insert(key, value, pMemory);
  EXPECT_EQ(1u, ref.size());
}

// Test set_mark and mark()
TEST_F(NodeRefTest_225, SetMarkAndGetMark_225) {
  node_ref ref;
  Mark m;
  m.line = 5;
  m.column = 10;
  m.pos = 42;
  ref.set_mark(m);
  EXPECT_EQ(5, ref.mark().line);
  EXPECT_EQ(10, ref.mark().column);
  EXPECT_EQ(42u, ref.mark().pos);
}

// Test default scalar is empty
TEST_F(NodeRefTest_225, DefaultScalarIsEmpty_225) {
  node_ref ref;
  EXPECT_TRUE(ref.scalar().empty());
}

// Test default tag is empty
TEST_F(NodeRefTest_225, DefaultTagIsEmpty_225) {
  node_ref ref;
  EXPECT_TRUE(ref.tag().empty());
}

// Test set_scalar with empty string
TEST_F(NodeRefTest_225, SetEmptyScalar_225) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("");
  EXPECT_EQ("", ref.scalar());
}

// Test set_tag with empty string
TEST_F(NodeRefTest_225, SetEmptyTag_225) {
  node_ref ref;
  ref.set_tag("");
  EXPECT_EQ("", ref.tag());
}

// Test set_scalar with long string
TEST_F(NodeRefTest_225, SetLongScalar_225) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  std::string longStr(10000, 'x');
  ref.set_scalar(longStr);
  EXPECT_EQ(longStr, ref.scalar());
}

// Test set_data copies data from another node_ref
TEST_F(NodeRefTest_225, SetDataCopiesFromAnotherRef_225) {
  node_ref ref1;
  ref1.set_type(NodeType::Scalar);
  ref1.set_scalar("test_value");
  ref1.set_tag("!tag");
  ref1.mark_defined();

  node_ref ref2;
  ref2.set_data(ref1);

  EXPECT_EQ(NodeType::Scalar, ref2.type());
  EXPECT_EQ("test_value", ref2.scalar());
  EXPECT_EQ("!tag", ref2.tag());
  EXPECT_TRUE(ref2.is_defined());
}

// Test begin and end for empty sequence
TEST_F(NodeRefTest_225, BeginEqualsEndForEmptySequence_225) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  EXPECT_EQ(ref.begin(), ref.end());
}

// Test begin and end for non-empty sequence
TEST_F(NodeRefTest_225, BeginNotEqualsEndForNonEmptySequence_225) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  node n;
  ref.push_back(n, pMemory);
  EXPECT_NE(ref.begin(), ref.end());
}

// Test type change from Sequence to Map
TEST_F(NodeRefTest_225, ChangeTypeFromSequenceToMap_225) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, ref.type());
  ref.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, ref.type());
}

// Test setting type to Null resets size
TEST_F(NodeRefTest_225, SetTypeNullResetsSize_225) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  node n;
  ref.push_back(n, pMemory);
  EXPECT_EQ(1u, ref.size());

  ref.set_type(NodeType::Null);
  EXPECT_EQ(0u, ref.size());
}

// Test set_type to Undefined
TEST_F(NodeRefTest_225, SetTypeUndefined_225) {
  node_ref ref;
  ref.set_type(NodeType::Undefined);
  EXPECT_EQ(NodeType::Undefined, ref.type());
}

// Test scalar value is preserved when set multiple times
TEST_F(NodeRefTest_225, ScalarOverwrittenOnMultipleSets_225) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("first");
  EXPECT_EQ("first", ref.scalar());
  ref.set_scalar("second");
  EXPECT_EQ("second", ref.scalar());
}

// Test tag value is preserved when set multiple times
TEST_F(NodeRefTest_225, TagOverwrittenOnMultipleSets_225) {
  node_ref ref;
  ref.set_tag("!first");
  EXPECT_EQ("!first", ref.tag());
  ref.set_tag("!second");
  EXPECT_EQ("!second", ref.tag());
}

// Test map size with multiple inserts
TEST_F(NodeRefTest_225, MapSizeAfterMultipleInserts_225) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node k1, v1, k2, v2;
  ref.insert(k1, v1, pMemory);
  ref.insert(k2, v2, pMemory);
  EXPECT_EQ(2u, ref.size());
}

}  // namespace detail
}  // namespace YAML
