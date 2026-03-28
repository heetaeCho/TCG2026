#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/node_data.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeRefTest_211 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = std::make_shared<memory_holder>();
  }

  shared_memory_holder pMemory;
};

// Test that a newly created node_ref is not defined
TEST_F(NodeRefTest_211, NewNodeRefIsNotDefined_211) {
  node_ref ref;
  EXPECT_FALSE(ref.is_defined());
}

// Test that after mark_defined, is_defined returns true
TEST_F(NodeRefTest_211, MarkDefinedMakesItDefined_211) {
  node_ref ref;
  ref.mark_defined();
  EXPECT_TRUE(ref.is_defined());
}

// Test that default type is Null
TEST_F(NodeRefTest_211, DefaultTypeIsNull_211) {
  node_ref ref;
  EXPECT_EQ(NodeType::Null, ref.type());
}

// Test set_type and type
TEST_F(NodeRefTest_211, SetTypeScalar_211) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, ref.type());
}

TEST_F(NodeRefTest_211, SetTypeSequence_211) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, ref.type());
}

TEST_F(NodeRefTest_211, SetTypeMap_211) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, ref.type());
}

TEST_F(NodeRefTest_211, SetTypeUndefined_211) {
  node_ref ref;
  ref.set_type(NodeType::Undefined);
  EXPECT_EQ(NodeType::Undefined, ref.type());
}

// Test scalar
TEST_F(NodeRefTest_211, DefaultScalarIsEmpty_211) {
  node_ref ref;
  EXPECT_TRUE(ref.scalar().empty());
}

TEST_F(NodeRefTest_211, SetScalar_211) {
  node_ref ref;
  ref.set_scalar("hello");
  EXPECT_EQ("hello", ref.scalar());
}

TEST_F(NodeRefTest_211, SetScalarEmptyString_211) {
  node_ref ref;
  ref.set_scalar("");
  EXPECT_EQ("", ref.scalar());
}

TEST_F(NodeRefTest_211, SetScalarOverwrite_211) {
  node_ref ref;
  ref.set_scalar("first");
  ref.set_scalar("second");
  EXPECT_EQ("second", ref.scalar());
}

// Test tag
TEST_F(NodeRefTest_211, DefaultTagIsEmpty_211) {
  node_ref ref;
  EXPECT_TRUE(ref.tag().empty());
}

TEST_F(NodeRefTest_211, SetTag_211) {
  node_ref ref;
  ref.set_tag("!!str");
  EXPECT_EQ("!!str", ref.tag());
}

// Test set_null
TEST_F(NodeRefTest_211, SetNullResetsToNull_211) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("value");
  ref.set_null();
  EXPECT_EQ(NodeType::Null, ref.type());
}

// Test style
TEST_F(NodeRefTest_211, DefaultStyle_211) {
  node_ref ref;
  // Default style should be Default
  EXPECT_EQ(EmitterStyle::Default, ref.style());
}

TEST_F(NodeRefTest_211, SetStyleFlow_211) {
  node_ref ref;
  ref.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, ref.style());
}

TEST_F(NodeRefTest_211, SetStyleBlock_211) {
  node_ref ref;
  ref.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, ref.style());
}

// Test mark
TEST_F(NodeRefTest_211, DefaultMarkIsNull_211) {
  node_ref ref;
  const Mark& m = ref.mark();
  EXPECT_EQ(Mark::null_mark().pos, m.pos);
  EXPECT_EQ(Mark::null_mark().line, m.line);
  EXPECT_EQ(Mark::null_mark().column, m.column);
}

TEST_F(NodeRefTest_211, SetMark_211) {
  node_ref ref;
  Mark mark;
  mark.pos = 10;
  mark.line = 5;
  mark.column = 3;
  ref.set_mark(mark);
  const Mark& m = ref.mark();
  EXPECT_EQ(10, m.pos);
  EXPECT_EQ(5, m.line);
  EXPECT_EQ(3, m.column);
}

// Test size for empty node
TEST_F(NodeRefTest_211, DefaultSizeIsZero_211) {
  node_ref ref;
  EXPECT_EQ(0u, ref.size());
}

// Test size for sequence
TEST_F(NodeRefTest_211, SequenceSizeAfterPushBack_211) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  
  node& n1 = pMemory->create_node();
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("item1");
  
  ref.push_back(n1, pMemory);
  EXPECT_EQ(1u, ref.size());
}

TEST_F(NodeRefTest_211, SequenceSizeMultiplePushBack_211) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  
  node& n1 = pMemory->create_node();
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("item1");
  ref.push_back(n1, pMemory);
  
  node& n2 = pMemory->create_node();
  n2.set_type(NodeType::Scalar);
  n2.set_scalar("item2");
  ref.push_back(n2, pMemory);
  
  EXPECT_EQ(2u, ref.size());
}

// Test begin/end for empty
TEST_F(NodeRefTest_211, BeginEqualsEndForEmptySequence_211) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  EXPECT_EQ(ref.begin(), ref.end());
}

// Test set_data copies from another node_ref
TEST_F(NodeRefTest_211, SetDataCopiesType_211) {
  node_ref src;
  src.set_type(NodeType::Scalar);
  src.set_scalar("copied");
  
  node_ref dst;
  dst.set_data(src);
  
  EXPECT_EQ(NodeType::Scalar, dst.type());
  EXPECT_EQ("copied", dst.scalar());
}

TEST_F(NodeRefTest_211, SetDataCopiesTag_211) {
  node_ref src;
  src.set_tag("!!int");
  
  node_ref dst;
  dst.set_data(src);
  
  EXPECT_EQ("!!int", dst.tag());
}

TEST_F(NodeRefTest_211, SetDataCopiesStyle_211) {
  node_ref src;
  src.set_style(EmitterStyle::Flow);
  
  node_ref dst;
  dst.set_data(src);
  
  EXPECT_EQ(EmitterStyle::Flow, dst.style());
}

// Test map operations
TEST_F(NodeRefTest_211, MapInsertAndSize_211) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_type(NodeType::Scalar);
  key.set_scalar("key1");
  
  node& value = pMemory->create_node();
  value.set_type(NodeType::Scalar);
  value.set_scalar("value1");
  
  ref.insert(key, value, pMemory);
  EXPECT_EQ(1u, ref.size());
}

// Test get with string key on map
TEST_F(NodeRefTest_211, GetExistingKey_211) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_type(NodeType::Scalar);
  key.set_scalar("mykey");
  
  node& value = pMemory->create_node();
  value.set_type(NodeType::Scalar);
  value.set_scalar("myvalue");
  
  ref.insert(key, value, pMemory);
  
  node* result = ref.get(std::string("mykey"), pMemory);
  EXPECT_NE(nullptr, result);
}

TEST_F(NodeRefTest_211, GetNonExistingKey_211) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  
  node* result = ref.get(std::string("nonexistent"), pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test remove
TEST_F(NodeRefTest_211, RemoveExistingKey_211) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_type(NodeType::Scalar);
  key.set_scalar("toremove");
  
  node& value = pMemory->create_node();
  value.set_type(NodeType::Scalar);
  value.set_scalar("val");
  
  ref.insert(key, value, pMemory);
  EXPECT_EQ(1u, ref.size());
  
  bool removed = ref.remove(std::string("toremove"), pMemory);
  EXPECT_TRUE(removed);
}

TEST_F(NodeRefTest_211, RemoveNonExistingKey_211) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  
  bool removed = ref.remove(std::string("nonexistent"), pMemory);
  EXPECT_FALSE(removed);
}

// Test set_type changes and resets data
TEST_F(NodeRefTest_211, ChangeTypeFromScalarToSequence_211) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("hello");
  EXPECT_EQ(NodeType::Scalar, ref.type());
  
  ref.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, ref.type());
}

// Test setting null type
TEST_F(NodeRefTest_211, SetTypeNull_211) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("data");
  ref.set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, ref.type());
}

// Test force_insert
TEST_F(NodeRefTest_211, ForceInsertOnMap_211) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  
  ref.force_insert(std::string("key"), std::string("value"), pMemory);
  EXPECT_EQ(1u, ref.size());
}

// Test that mark_defined sets defined status
TEST_F(NodeRefTest_211, MarkDefinedOnlyOnce_211) {
  node_ref ref;
  EXPECT_FALSE(ref.is_defined());
  ref.mark_defined();
  EXPECT_TRUE(ref.is_defined());
  ref.mark_defined();  // calling again should still be defined
  EXPECT_TRUE(ref.is_defined());
}

// Test get with node key
TEST_F(NodeRefTest_211, GetWithNodeKey_211) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_type(NodeType::Scalar);
  key.set_scalar("nodekey");
  
  node& value = pMemory->create_node();
  value.set_type(NodeType::Scalar);
  value.set_scalar("nodeval");
  
  ref.insert(key, value, pMemory);
  
  node* result = ref.get(key, pMemory);
  EXPECT_NE(nullptr, result);
}

// Test remove with node key
TEST_F(NodeRefTest_211, RemoveWithNodeKey_211) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  
  node& key = pMemory->create_node();
  key.set_type(NodeType::Scalar);
  key.set_scalar("removekey");
  
  node& value = pMemory->create_node();
  value.set_type(NodeType::Scalar);
  value.set_scalar("removeval");
  
  ref.insert(key, value, pMemory);
  
  bool removed = ref.remove(key, pMemory);
  EXPECT_TRUE(removed);
}

// Test that setting scalar also changes type
TEST_F(NodeRefTest_211, SetScalarSetsTypeToScalar_211) {
  node_ref ref;
  ref.set_type(NodeType::Scalar);
  ref.set_scalar("test_scalar");
  EXPECT_EQ(NodeType::Scalar, ref.type());
  EXPECT_EQ("test_scalar", ref.scalar());
}

// Test sequence begin/end iteration
TEST_F(NodeRefTest_211, SequenceBeginEndWithElements_211) {
  node_ref ref;
  ref.set_type(NodeType::Sequence);
  
  node& n1 = pMemory->create_node();
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("elem");
  ref.push_back(n1, pMemory);
  
  EXPECT_NE(ref.begin(), ref.end());
}

// Test empty map
TEST_F(NodeRefTest_211, EmptyMapSizeZero_211) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  EXPECT_EQ(0u, ref.size());
}

// Test map begin/end empty
TEST_F(NodeRefTest_211, EmptyMapBeginEqualsEnd_211) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  EXPECT_EQ(ref.begin(), ref.end());
}

}  // namespace detail
}  // namespace YAML
