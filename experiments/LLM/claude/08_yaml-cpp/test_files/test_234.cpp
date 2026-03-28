#include "gtest/gtest.h"
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/memory.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/type.h"
#include "yaml-cpp/emitterstyle.h"
#include "yaml-cpp/mark.h"

#include <string>
#include <memory>

namespace YAML {
namespace detail {

class NodeRefTest_234 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = std::make_shared<memory_holder>();
    ref = std::unique_ptr<node_ref>(new node_ref());
  }

  shared_memory_holder pMemory;
  std::unique_ptr<node_ref> ref;

  shared_memory_holder create_memory() {
    return std::make_shared<memory_holder>();
  }
};

// Test default construction and initial state
TEST_F(NodeRefTest_234, DefaultConstruction_IsDefined_234) {
  // A freshly constructed node_ref should exist but may not be "defined" initially
  // Based on typical yaml-cpp behavior, a new node_ref is not defined until mark_defined
  EXPECT_FALSE(ref->is_defined());
}

TEST_F(NodeRefTest_234, DefaultConstruction_Type_234) {
  // Default type should be Undefined
  EXPECT_EQ(NodeType::Undefined, ref->type());
}

TEST_F(NodeRefTest_234, MarkDefined_234) {
  ref->mark_defined();
  EXPECT_TRUE(ref->is_defined());
}

// Test set_null
TEST_F(NodeRefTest_234, SetNull_234) {
  ref->set_null();
  EXPECT_EQ(NodeType::Null, ref->type());
  EXPECT_TRUE(ref->is_defined());
}

// Test set_scalar and scalar()
TEST_F(NodeRefTest_234, SetScalar_234) {
  ref->set_scalar("hello");
  EXPECT_EQ(NodeType::Scalar, ref->type());
  EXPECT_EQ("hello", ref->scalar());
  EXPECT_TRUE(ref->is_defined());
}

TEST_F(NodeRefTest_234, SetScalarEmpty_234) {
  ref->set_scalar("");
  EXPECT_EQ(NodeType::Scalar, ref->type());
  EXPECT_EQ("", ref->scalar());
}

// Test set_tag and tag()
TEST_F(NodeRefTest_234, SetTag_234) {
  ref->set_tag("!mytag");
  EXPECT_EQ("!mytag", ref->tag());
}

TEST_F(NodeRefTest_234, SetTagEmpty_234) {
  ref->set_tag("");
  EXPECT_EQ("", ref->tag());
}

// Test set_type
TEST_F(NodeRefTest_234, SetTypeSequence_234) {
  ref->set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, ref->type());
  EXPECT_TRUE(ref->is_defined());
}

TEST_F(NodeRefTest_234, SetTypeMap_234) {
  ref->set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, ref->type());
  EXPECT_TRUE(ref->is_defined());
}

TEST_F(NodeRefTest_234, SetTypeNull_234) {
  ref->set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, ref->type());
}

TEST_F(NodeRefTest_234, SetTypeUndefined_234) {
  ref->set_scalar("test");
  ref->set_type(NodeType::Undefined);
  EXPECT_EQ(NodeType::Undefined, ref->type());
}

// Test set_style and style()
TEST_F(NodeRefTest_234, SetStyleDefault_234) {
  ref->set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, ref->style());
}

TEST_F(NodeRefTest_234, SetStyleBlock_234) {
  ref->set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, ref->style());
}

TEST_F(NodeRefTest_234, SetStyleFlow_234) {
  ref->set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, ref->style());
}

// Test set_mark and mark()
TEST_F(NodeRefTest_234, SetMark_234) {
  Mark m;
  m.line = 10;
  m.column = 20;
  m.pos = 30;
  ref->set_mark(m);
  const Mark& retrieved = ref->mark();
  EXPECT_EQ(10, retrieved.line);
  EXPECT_EQ(20, retrieved.column);
  EXPECT_EQ(30, retrieved.pos);
}

// Test sequence operations: size, push_back, begin/end
TEST_F(NodeRefTest_234, SequenceSize_Empty_234) {
  ref->set_type(NodeType::Sequence);
  EXPECT_EQ(0u, ref->size());
}

TEST_F(NodeRefTest_234, SequencePushBack_234) {
  ref->set_type(NodeType::Sequence);
  
  memory mem;
  node& n = mem.create_node();
  n.set_scalar("item1");
  
  shared_memory_holder smh = mem.create_memory();
  ref->push_back(n, smh);
  EXPECT_EQ(1u, ref->size());
}

TEST_F(NodeRefTest_234, SequencePushBackMultiple_234) {
  ref->set_type(NodeType::Sequence);
  
  memory mem;
  shared_memory_holder smh = mem.create_memory();
  
  node& n1 = mem.create_node();
  n1.set_scalar("item1");
  ref->push_back(n1, smh);
  
  node& n2 = mem.create_node();
  n2.set_scalar("item2");
  ref->push_back(n2, smh);
  
  EXPECT_EQ(2u, ref->size());
}

TEST_F(NodeRefTest_234, SequenceBeginEndEmpty_234) {
  ref->set_type(NodeType::Sequence);
  EXPECT_TRUE(ref->begin() == ref->end());
}

// Test map operations: insert, size
TEST_F(NodeRefTest_234, MapSize_Empty_234) {
  ref->set_type(NodeType::Map);
  EXPECT_EQ(0u, ref->size());
}

TEST_F(NodeRefTest_234, MapInsert_234) {
  ref->set_type(NodeType::Map);
  
  memory mem;
  shared_memory_holder smh = mem.create_memory();
  
  node& key = mem.create_node();
  key.set_scalar("key1");
  
  node& value = mem.create_node();
  value.set_scalar("value1");
  
  ref->insert(key, value, smh);
  EXPECT_EQ(1u, ref->size());
}

// Test get with string key on a map
TEST_F(NodeRefTest_234, MapGetExistingKey_234) {
  ref->set_type(NodeType::Map);
  
  memory mem;
  shared_memory_holder smh = mem.create_memory();
  
  node& key = mem.create_node();
  key.set_scalar("mykey");
  
  node& value = mem.create_node();
  value.set_scalar("myvalue");
  
  ref->insert(key, value, smh);
  
  node* result = ref->get(std::string("mykey"), smh);
  EXPECT_NE(nullptr, result);
}

TEST_F(NodeRefTest_234, MapGetNonExistingKey_234) {
  ref->set_type(NodeType::Map);
  
  memory mem;
  shared_memory_holder smh = mem.create_memory();
  
  node* result = ref->get(std::string("nonexistent"), smh);
  EXPECT_EQ(nullptr, result);
}

// Test remove with string key
TEST_F(NodeRefTest_234, MapRemoveExistingKey_234) {
  ref->set_type(NodeType::Map);
  
  memory mem;
  shared_memory_holder smh = mem.create_memory();
  
  node& key = mem.create_node();
  key.set_scalar("removekey");
  
  node& value = mem.create_node();
  value.set_scalar("removevalue");
  
  ref->insert(key, value, smh);
  EXPECT_EQ(1u, ref->size());
  
  bool removed = ref->remove(std::string("removekey"), smh);
  EXPECT_TRUE(removed);
}

TEST_F(NodeRefTest_234, MapRemoveNonExistingKey_234) {
  ref->set_type(NodeType::Map);
  
  memory mem;
  shared_memory_holder smh = mem.create_memory();
  
  bool removed = ref->remove(std::string("nonexistent"), smh);
  EXPECT_FALSE(removed);
}

// Test remove with node key
TEST_F(NodeRefTest_234, MapRemoveByNode_234) {
  ref->set_type(NodeType::Map);
  
  memory mem;
  shared_memory_holder smh = mem.create_memory();
  
  node& key = mem.create_node();
  key.set_scalar("nodekey");
  
  node& value = mem.create_node();
  value.set_scalar("nodevalue");
  
  ref->insert(key, value, smh);
  
  bool removed = ref->remove(key, smh);
  EXPECT_TRUE(removed);
}

// Test get with node key
TEST_F(NodeRefTest_234, MapGetByNode_234) {
  ref->set_type(NodeType::Map);
  
  memory mem;
  shared_memory_holder smh = mem.create_memory();
  
  node& key = mem.create_node();
  key.set_scalar("nodekey");
  
  node& value = mem.create_node();
  value.set_scalar("nodevalue");
  
  ref->insert(key, value, smh);
  
  node* result = ref->get(key, smh);
  EXPECT_NE(nullptr, result);
}

// Test set_data copies from another node_ref
TEST_F(NodeRefTest_234, SetData_234) {
  node_ref other;
  other.set_scalar("copied");
  other.set_tag("!tag");
  
  ref->set_data(other);
  EXPECT_EQ("copied", ref->scalar());
  EXPECT_EQ("!tag", ref->tag());
  EXPECT_EQ(NodeType::Scalar, ref->type());
}

// Test force_insert on a map
TEST_F(NodeRefTest_234, ForceInsert_234) {
  ref->set_type(NodeType::Map);
  
  memory mem;
  shared_memory_holder smh = mem.create_memory();
  
  node& key = mem.create_node();
  key.set_scalar("forcekey");
  
  node& value = mem.create_node();
  value.set_scalar("forcevalue");
  
  ref->force_insert(key, value, smh);
  EXPECT_EQ(1u, ref->size());
}

// Test that copy construction is deleted
TEST_F(NodeRefTest_234, CopyConstructionDeleted_234) {
  EXPECT_FALSE(std::is_copy_constructible<node_ref>::value);
}

// Test that copy assignment is deleted
TEST_F(NodeRefTest_234, CopyAssignmentDeleted_234) {
  EXPECT_FALSE(std::is_copy_assignable<node_ref>::value);
}

// Test changing type resets content
TEST_F(NodeRefTest_234, ChangeTypeResetsContent_234) {
  ref->set_scalar("test_scalar");
  EXPECT_EQ(NodeType::Scalar, ref->type());
  EXPECT_EQ("test_scalar", ref->scalar());
  
  ref->set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, ref->type());
  EXPECT_EQ(0u, ref->size());
}

// Test set scalar overwrite
TEST_F(NodeRefTest_234, SetScalarOverwrite_234) {
  ref->set_scalar("first");
  EXPECT_EQ("first", ref->scalar());
  
  ref->set_scalar("second");
  EXPECT_EQ("second", ref->scalar());
}

// Test default mark values
TEST_F(NodeRefTest_234, DefaultMark_234) {
  const Mark& m = ref->mark();
  EXPECT_EQ(0, m.line);
  EXPECT_EQ(0, m.column);
  EXPECT_EQ(0, m.pos);
}

// Test default style
TEST_F(NodeRefTest_234, DefaultStyle_234) {
  EXPECT_EQ(EmitterStyle::Default, ref->style());
}

// Test default tag is empty
TEST_F(NodeRefTest_234, DefaultTagEmpty_234) {
  EXPECT_EQ("", ref->tag());
}

}  // namespace detail
}  // namespace YAML
