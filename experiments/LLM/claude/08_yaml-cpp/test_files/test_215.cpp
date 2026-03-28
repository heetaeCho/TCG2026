#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/node_data.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"
#include "yaml-cpp/node/type.h"
#include "yaml-cpp/emitterstyle.h"
#include "yaml-cpp/mark.h"

#include <string>
#include <memory>

namespace YAML {
namespace detail {

class NodeRefTest_215 : public ::testing::Test {
 protected:
  void SetUp() override {
    ref_ = std::make_unique<node_ref>();
    pMemory_ = std::make_shared<memory>();
  }

  std::unique_ptr<node_ref> ref_;
  shared_memory_holder pMemory_;
};

// Test default construction state
TEST_F(NodeRefTest_215, DefaultConstruction_IsNotDefined_215) {
  EXPECT_FALSE(ref_->is_defined());
}

TEST_F(NodeRefTest_215, DefaultConstruction_TypeIsNull_215) {
  EXPECT_EQ(NodeType::Null, ref_->type());
}

TEST_F(NodeRefTest_215, DefaultConstruction_TagIsEmpty_215) {
  EXPECT_TRUE(ref_->tag().empty());
}

TEST_F(NodeRefTest_215, DefaultConstruction_ScalarIsEmpty_215) {
  EXPECT_TRUE(ref_->scalar().empty());
}

TEST_F(NodeRefTest_215, DefaultConstruction_SizeIsZero_215) {
  EXPECT_EQ(0u, ref_->size());
}

// Test mark_defined
TEST_F(NodeRefTest_215, MarkDefined_MakesNodeDefined_215) {
  ref_->mark_defined();
  EXPECT_TRUE(ref_->is_defined());
}

// Test set_tag and tag
TEST_F(NodeRefTest_215, SetTag_ReturnsSetTag_215) {
  ref_->set_tag("!mytag");
  EXPECT_EQ("!mytag", ref_->tag());
}

TEST_F(NodeRefTest_215, SetTag_EmptyTag_215) {
  ref_->set_tag("");
  EXPECT_EQ("", ref_->tag());
}

TEST_F(NodeRefTest_215, SetTag_OverwriteTag_215) {
  ref_->set_tag("!first");
  ref_->set_tag("!second");
  EXPECT_EQ("!second", ref_->tag());
}

// Test set_type and type
TEST_F(NodeRefTest_215, SetType_Scalar_215) {
  ref_->set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, ref_->type());
}

TEST_F(NodeRefTest_215, SetType_Sequence_215) {
  ref_->set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, ref_->type());
}

TEST_F(NodeRefTest_215, SetType_Map_215) {
  ref_->set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, ref_->type());
}

TEST_F(NodeRefTest_215, SetType_Null_215) {
  ref_->set_type(NodeType::Scalar);
  ref_->set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, ref_->type());
}

TEST_F(NodeRefTest_215, SetType_Undefined_215) {
  ref_->set_type(NodeType::Undefined);
  EXPECT_EQ(NodeType::Undefined, ref_->type());
}

// Test set_scalar and scalar
TEST_F(NodeRefTest_215, SetScalar_ReturnsSetScalar_215) {
  ref_->set_type(NodeType::Scalar);
  ref_->set_scalar("hello");
  EXPECT_EQ("hello", ref_->scalar());
}

TEST_F(NodeRefTest_215, SetScalar_EmptyString_215) {
  ref_->set_type(NodeType::Scalar);
  ref_->set_scalar("");
  EXPECT_EQ("", ref_->scalar());
}

TEST_F(NodeRefTest_215, SetScalar_Overwrite_215) {
  ref_->set_type(NodeType::Scalar);
  ref_->set_scalar("first");
  ref_->set_scalar("second");
  EXPECT_EQ("second", ref_->scalar());
}

// Test set_null
TEST_F(NodeRefTest_215, SetNull_TypeBecomesNull_215) {
  ref_->set_type(NodeType::Scalar);
  ref_->set_null();
  EXPECT_EQ(NodeType::Null, ref_->type());
}

// Test set_style and style
TEST_F(NodeRefTest_215, SetStyle_Block_215) {
  ref_->set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, ref_->style());
}

TEST_F(NodeRefTest_215, SetStyle_Flow_215) {
  ref_->set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, ref_->style());
}

TEST_F(NodeRefTest_215, SetStyle_Default_215) {
  ref_->set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, ref_->style());
}

// Test set_mark and mark
TEST_F(NodeRefTest_215, SetMark_ReturnsSetMark_215) {
  Mark m;
  m.line = 5;
  m.column = 10;
  m.pos = 42;
  ref_->set_mark(m);
  EXPECT_EQ(5, ref_->mark().line);
  EXPECT_EQ(10, ref_->mark().column);
  EXPECT_EQ(42u, ref_->mark().pos);
}

// Test sequence operations
TEST_F(NodeRefTest_215, PushBack_IncreasesSize_215) {
  ref_->set_type(NodeType::Sequence);
  node& n = pMemory_->create_node();
  n.set_scalar("item");
  ref_->push_back(n, pMemory_);
  EXPECT_EQ(1u, ref_->size());
}

TEST_F(NodeRefTest_215, PushBack_MultipleTimes_215) {
  ref_->set_type(NodeType::Sequence);
  node& n1 = pMemory_->create_node();
  n1.set_scalar("item1");
  node& n2 = pMemory_->create_node();
  n2.set_scalar("item2");
  ref_->push_back(n1, pMemory_);
  ref_->push_back(n2, pMemory_);
  EXPECT_EQ(2u, ref_->size());
}

// Test begin/end iterators for empty sequence
TEST_F(NodeRefTest_215, BeginEqualsEnd_EmptySequence_215) {
  ref_->set_type(NodeType::Sequence);
  EXPECT_EQ(ref_->begin(), ref_->end());
}

// Test map operations
TEST_F(NodeRefTest_215, Insert_IncreasesSize_215) {
  ref_->set_type(NodeType::Map);
  node& key = pMemory_->create_node();
  key.set_scalar("key1");
  node& val = pMemory_->create_node();
  val.set_scalar("val1");
  ref_->insert(key, val, pMemory_);
  EXPECT_EQ(1u, ref_->size());
}

// Test get with node key
TEST_F(NodeRefTest_215, Get_NonExistentKey_ReturnsNull_215) {
  ref_->set_type(NodeType::Map);
  node& key = pMemory_->create_node();
  key.set_scalar("nonexistent");
  const node* result = ref_->get(key, pMemory_);
  EXPECT_EQ(nullptr, result);
}

TEST_F(NodeRefTest_215, Get_ExistingKey_ReturnsNode_215) {
  ref_->set_type(NodeType::Map);
  node& key = pMemory_->create_node();
  key.set_scalar("mykey");
  node& val = pMemory_->create_node();
  val.set_scalar("myval");
  ref_->insert(key, val, pMemory_);
  const node* result = ref_->get(key, pMemory_);
  EXPECT_NE(nullptr, result);
}

// Test get with template key
TEST_F(NodeRefTest_215, GetTemplated_NonExistentKey_ReturnsNull_215) {
  ref_->set_type(NodeType::Map);
  const node* result = ref_->get(std::string("nonexistent"), pMemory_);
  EXPECT_EQ(nullptr, result);
}

// Test remove
TEST_F(NodeRefTest_215, Remove_ExistingKey_ReturnsTrue_215) {
  ref_->set_type(NodeType::Map);
  node& key = pMemory_->create_node();
  key.set_scalar("removekey");
  node& val = pMemory_->create_node();
  val.set_scalar("removeval");
  ref_->insert(key, val, pMemory_);
  EXPECT_TRUE(ref_->remove(key, pMemory_));
}

TEST_F(NodeRefTest_215, Remove_NonExistentKey_ReturnsFalse_215) {
  ref_->set_type(NodeType::Map);
  node& key = pMemory_->create_node();
  key.set_scalar("nonexistent");
  EXPECT_FALSE(ref_->remove(key, pMemory_));
}

TEST_F(NodeRefTest_215, RemoveTemplated_NonExistentKey_ReturnsFalse_215) {
  ref_->set_type(NodeType::Map);
  EXPECT_FALSE(ref_->remove(std::string("nonexistent"), pMemory_));
}

// Test set_data copies data from another node_ref
TEST_F(NodeRefTest_215, SetData_CopiesTag_215) {
  node_ref other;
  other.set_tag("!copiedtag");
  other.set_type(NodeType::Scalar);
  other.set_scalar("copiedscalar");
  
  ref_->set_data(other);
  EXPECT_EQ("!copiedtag", ref_->tag());
  EXPECT_EQ("copiedscalar", ref_->scalar());
}

TEST_F(NodeRefTest_215, SetData_CopiesType_215) {
  node_ref other;
  other.set_type(NodeType::Scalar);
  
  ref_->set_data(other);
  EXPECT_EQ(NodeType::Scalar, ref_->type());
}

// Test force_insert
TEST_F(NodeRefTest_215, ForceInsert_IncreasesMapSize_215) {
  ref_->set_type(NodeType::Map);
  ref_->force_insert(std::string("key"), std::string("value"), pMemory_);
  EXPECT_EQ(1u, ref_->size());
}

// Test sequence with begin/end iteration
TEST_F(NodeRefTest_215, Sequence_BeginNotEqualsEnd_AfterPush_215) {
  ref_->set_type(NodeType::Sequence);
  node& n = pMemory_->create_node();
  n.set_scalar("elem");
  ref_->push_back(n, pMemory_);
  EXPECT_NE(ref_->begin(), ref_->end());
}

// Test long tag string
TEST_F(NodeRefTest_215, SetTag_LongString_215) {
  std::string longTag(1000, 'x');
  ref_->set_tag(longTag);
  EXPECT_EQ(longTag, ref_->tag());
}

// Test long scalar string
TEST_F(NodeRefTest_215, SetScalar_LongString_215) {
  ref_->set_type(NodeType::Scalar);
  std::string longScalar(10000, 'a');
  ref_->set_scalar(longScalar);
  EXPECT_EQ(longScalar, ref_->scalar());
}

// Test that setting type resets appropriately
TEST_F(NodeRefTest_215, SetType_FromScalarToSequence_215) {
  ref_->set_type(NodeType::Scalar);
  ref_->set_scalar("test");
  ref_->set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, ref_->type());
  EXPECT_EQ(0u, ref_->size());
}

TEST_F(NodeRefTest_215, SetType_FromSequenceToMap_215) {
  ref_->set_type(NodeType::Sequence);
  node& n = pMemory_->create_node();
  n.set_scalar("item");
  ref_->push_back(n, pMemory_);
  ref_->set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, ref_->type());
}

// Test multiple inserts to map
TEST_F(NodeRefTest_215, MultipleInserts_Map_215) {
  ref_->set_type(NodeType::Map);
  for (int i = 0; i < 10; ++i) {
    node& key = pMemory_->create_node();
    key.set_scalar("key" + std::to_string(i));
    node& val = pMemory_->create_node();
    val.set_scalar("val" + std::to_string(i));
    ref_->insert(key, val, pMemory_);
  }
  EXPECT_EQ(10u, ref_->size());
}

// Test remove decreases size
TEST_F(NodeRefTest_215, Remove_DecreasesSize_215) {
  ref_->set_type(NodeType::Map);
  node& key = pMemory_->create_node();
  key.set_scalar("toremove");
  node& val = pMemory_->create_node();
  val.set_scalar("val");
  ref_->insert(key, val, pMemory_);
  EXPECT_EQ(1u, ref_->size());
  ref_->remove(key, pMemory_);
  EXPECT_EQ(0u, ref_->size());
}

// Test default mark is null
TEST_F(NodeRefTest_215, DefaultMark_IsNullMark_215) {
  Mark m = ref_->mark();
  Mark null_mark = Mark::null_mark();
  EXPECT_EQ(null_mark.line, m.line);
  EXPECT_EQ(null_mark.column, m.column);
  EXPECT_EQ(null_mark.pos, m.pos);
}

}  // namespace detail
}  // namespace YAML
