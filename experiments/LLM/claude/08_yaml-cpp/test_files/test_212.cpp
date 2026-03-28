#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeRefTest_212 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = std::make_shared<memory_holder>();
  }

  shared_memory_holder pMemory;
};

// Test default construction - node_ref should be created with default state
TEST_F(NodeRefTest_212, DefaultConstruction_IsNotDefined_212) {
  node_ref ref;
  EXPECT_FALSE(ref.is_defined());
}

TEST_F(NodeRefTest_212, DefaultConstruction_TypeIsNull_212) {
  node_ref ref;
  EXPECT_EQ(NodeType::Null, ref.type());
}

TEST_F(NodeRefTest_212, DefaultConstruction_ScalarIsEmpty_212) {
  node_ref ref;
  EXPECT_TRUE(ref.scalar().empty());
}

TEST_F(NodeRefTest_212, DefaultConstruction_TagIsEmpty_212) {
  node_ref ref;
  EXPECT_TRUE(ref.tag().empty());
}

TEST_F(NodeRefTest_212, DefaultConstruction_SizeIsZero_212) {
  node_ref ref;
  EXPECT_EQ(0u, ref.size());
}

// Test mark_defined
TEST_F(NodeRefTest_212, MarkDefined_MakesNodeDefined_212) {
  node_ref ref;
  ref.mark_defined();
  EXPECT_TRUE(ref.is_defined());
}

// Test set_mark and mark
TEST_F(NodeRefTest_212, SetMark_ReturnsCorrectMark_212) {
  node_ref ref;
  Mark m(5, 10, 15);
  ref.set_mark(m);
  EXPECT_EQ(5, ref.mark().line);
  EXPECT_EQ(10, ref.mark().column);
  EXPECT_EQ(15, ref.mark().pos);
}

TEST_F(NodeRefTest_212, DefaultMark_IsNullMark_212) {
  node_ref ref;
  const Mark& m = ref.mark();
  EXPECT_EQ(Mark::null_mark().line, m.line);
  EXPECT_EQ(Mark::null_mark().column, m.column);
  EXPECT_EQ(Mark::null_mark().pos, m.pos);
}

// Test set_type
TEST_F(NodeRefTest_212, SetType_Scalar_212) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, ref.type());
}

TEST_F(NodeRefTest_212, SetType_Sequence_212) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, ref.type());
}

TEST_F(NodeRefTest_212, SetType_Map_212) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, ref.type());
}

TEST_F(NodeRefTest_212, SetType_Null_212) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, ref.type());
}

TEST_F(NodeRefTest_212, SetType_Undefined_212) {
  node_ref ref;
  ref.set_type(NodeType::Undefined);
  EXPECT_EQ(NodeType::Undefined, ref.type());
}

// Test set_tag and tag
TEST_F(NodeRefTest_212, SetTag_ReturnsCorrectTag_212) {
  node_ref ref;
  ref.set_tag("!!str");
  EXPECT_EQ("!!str", ref.tag());
}

TEST_F(NodeRefTest_212, SetTag_EmptyTag_212) {
  node_ref ref;
  ref.set_tag("");
  EXPECT_TRUE(ref.tag().empty());
}

TEST_F(NodeRefTest_212, SetTag_OverwriteTag_212) {
  node_ref ref;
  ref.set_tag("first");
  ref.set_tag("second");
  EXPECT_EQ("second", ref.tag());
}

// Test set_scalar and scalar
TEST_F(NodeRefTest_212, SetScalar_ReturnsCorrectScalar_212) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("hello");
  EXPECT_EQ("hello", ref.scalar());
}

TEST_F(NodeRefTest_212, SetScalar_EmptyScalar_212) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("");
  EXPECT_TRUE(ref.scalar().empty());
}

TEST_F(NodeRefTest_212, SetScalar_OverwriteScalar_212) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("first");
  ref.set_scalar("second");
  EXPECT_EQ("second", ref.scalar());
}

// Test set_null
TEST_F(NodeRefTest_212, SetNull_TypeBecomesNull_212) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_null();
  EXPECT_EQ(NodeType::Null, ref.type());
}

// Test set_style and style
TEST_F(NodeRefTest_212, SetStyle_Block_212) {
  node_ref ref;
  ref.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, ref.style());
}

TEST_F(NodeRefTest_212, SetStyle_Flow_212) {
  node_ref ref;
  ref.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, ref.style());
}

TEST_F(NodeRefTest_212, SetStyle_Default_212) {
  node_ref ref;
  ref.set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, ref.style());
}

// Test sequence operations (push_back, size, begin, end)
TEST_F(NodeRefTest_212, PushBack_IncreasesSize_212) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);

  node n;
  ref.push_back(n, pMemory);
  EXPECT_EQ(1u, ref.size());
}

TEST_F(NodeRefTest_212, PushBack_MultipleTimes_IncreasesSize_212) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);

  node n1, n2, n3;
  ref.push_back(n1, pMemory);
  ref.push_back(n2, pMemory);
  ref.push_back(n3, pMemory);
  EXPECT_EQ(3u, ref.size());
}

// Test begin/end on empty sequence
TEST_F(NodeRefTest_212, EmptySequence_BeginEqualsEnd_212) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  EXPECT_EQ(ref.begin(), ref.end());
}

// Test begin/end on non-empty sequence
TEST_F(NodeRefTest_212, NonEmptySequence_BeginNotEqualsEnd_212) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  node n;
  ref.push_back(n, pMemory);
  EXPECT_NE(ref.begin(), ref.end());
}

// Test map operations (insert, size)
TEST_F(NodeRefTest_212, Insert_IncreasesSize_212) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node key, value;
  ref.insert(key, value, pMemory);
  EXPECT_EQ(1u, ref.size());
}

// Test set_data - copies data from another node_ref
TEST_F(NodeRefTest_212, SetData_CopiesScalar_212) {
  node_ref src;
  src.set_type(NodeType::Scalar);
  src.set_scalar("copied");
  src.set_tag("!!tag");
  src.mark_defined();

  node_ref dst;
  dst.set_data(src);

  EXPECT_EQ("copied", dst.scalar());
  EXPECT_EQ("!!tag", dst.tag());
  EXPECT_EQ(NodeType::Scalar, dst.type());
}

TEST_F(NodeRefTest_212, SetData_CopiesType_212) {
  node_ref src;
  src.set_type(NodeType::Sequence);

  node_ref dst;
  dst.set_data(src);
  EXPECT_EQ(NodeType::Sequence, dst.type());
}

// Test get on map with string key
TEST_F(NodeRefTest_212, GetOnMap_NonExistentKey_ReturnsNull_212) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  node* result = ref.get(std::string("nonexistent"), pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test remove on map with string key
TEST_F(NodeRefTest_212, RemoveOnMap_NonExistentKey_ReturnsFalse_212) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  bool removed = ref.remove(std::string("nonexistent"), pMemory);
  EXPECT_FALSE(removed);
}

// Test size on null node
TEST_F(NodeRefTest_212, NullNode_SizeIsZero_212) {
  node_ref ref;
  EXPECT_EQ(0u, ref.size());
}

// Test changing type clears content
TEST_F(NodeRefTest_212, ChangingType_ClearsSequence_212) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  node n;
  ref.push_back(n, pMemory);
  EXPECT_EQ(1u, ref.size());

  ref.set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, ref.type());
}

// Test set_type to same type doesn't break things
TEST_F(NodeRefTest_212, SetType_SameType_NoEffect_212) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("test");
  ref.set_type(NodeType::Scalar);
  EXPECT_EQ("test", ref.scalar());
}

// Test mark with specific values
TEST_F(NodeRefTest_212, SetMark_ZeroValues_212) {
  node_ref ref;
  Mark m(0, 0, 0);
  ref.set_mark(m);
  EXPECT_EQ(0, ref.mark().line);
  EXPECT_EQ(0, ref.mark().column);
  EXPECT_EQ(0, ref.mark().pos);
}

// Test long scalar strings
TEST_F(NodeRefTest_212, SetScalar_LongString_212) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  std::string longStr(10000, 'a');
  ref.set_scalar(longStr);
  EXPECT_EQ(longStr, ref.scalar());
}

// Test unicode-like tag
TEST_F(NodeRefTest_212, SetTag_SpecialCharacters_212) {
  node_ref ref;
  ref.set_tag("tag:yaml.org,2002:str");
  EXPECT_EQ("tag:yaml.org,2002:str", ref.tag());
}

// Test force_insert on map
TEST_F(NodeRefTest_212, ForceInsert_AddsToMap_212) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  ref.force_insert(std::string("key"), std::string("value"), pMemory);
  EXPECT_EQ(1u, ref.size());
}

// Test that is_defined returns false initially then true after mark_defined
TEST_F(NodeRefTest_212, IsDefinedTransition_212) {
  node_ref ref;
  EXPECT_FALSE(ref.is_defined());
  ref.mark_defined();
  EXPECT_TRUE(ref.is_defined());
}

// Test multiple push_backs and iteration
TEST_F(NodeRefTest_212, SequenceIteration_CountMatchesSize_212) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);

  const int count = 5;
  for (int i = 0; i < count; i++) {
    node n;
    ref.push_back(n, pMemory);
  }

  int iterCount = 0;
  for (auto it = ref.begin(); it != ref.end(); ++it) {
    iterCount++;
  }
  EXPECT_EQ(count, iterCount);
}

// Test empty map begin == end
TEST_F(NodeRefTest_212, EmptyMap_BeginEqualsEnd_212) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  EXPECT_EQ(ref.begin(), ref.end());
}

// Test non-empty map begin != end
TEST_F(NodeRefTest_212, NonEmptyMap_BeginNotEqualsEnd_212) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  node key, value;
  ref.insert(key, value, pMemory);
  EXPECT_NE(ref.begin(), ref.end());
}

}  // namespace detail
}  // namespace YAML
