#include "gtest/gtest.h"
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"
#include "yaml-cpp/node/detail/node_ref.h"

namespace YAML {
namespace detail {

class NodeTest_246 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = shared_memory_holder(new memory);
  }

  shared_memory_holder pMemory;
};

// Test that a newly created node is not defined
TEST_F(NodeTest_246, NewNodeIsNotDefined_246) {
  node n;
  // A freshly created node should have Undefined or Null type behavior
  // We check is_defined
  // Note: depending on implementation, a new node might not be defined
  EXPECT_FALSE(n.is_defined());
}

// Test mark_defined makes node defined
TEST_F(NodeTest_246, MarkDefinedMakesNodeDefined_246) {
  node n;
  n.mark_defined();
  EXPECT_TRUE(n.is_defined());
}

// Test that set_type changes the node type
TEST_F(NodeTest_246, SetTypeScalar_246) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, n.type());
}

TEST_F(NodeTest_246, SetTypeSequence_246) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
}

TEST_F(NodeTest_246, SetTypeMap_246) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, n.type());
}

TEST_F(NodeTest_246, SetTypeNull_246) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Null);
  EXPECT_EQ(NodeType::Null, n.type());
}

// Test set_null
TEST_F(NodeTest_246, SetNull_246) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");
  n.set_null();
  EXPECT_EQ(NodeType::Null, n.type());
}

// Test set_scalar and scalar()
TEST_F(NodeTest_246, SetScalarAndGetScalar_246) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Scalar);
  n.set_scalar("test_value");
  EXPECT_EQ("test_value", n.scalar());
}

// Test set_scalar with empty string
TEST_F(NodeTest_246, SetScalarEmptyString_246) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Scalar);
  n.set_scalar("");
  EXPECT_EQ("", n.scalar());
}

// Test set_tag and tag()
TEST_F(NodeTest_246, SetTagAndGetTag_246) {
  node n;
  n.mark_defined();
  n.set_tag("!custom_tag");
  EXPECT_EQ("!custom_tag", n.tag());
}

// Test set_tag with empty string
TEST_F(NodeTest_246, SetTagEmpty_246) {
  node n;
  n.mark_defined();
  n.set_tag("");
  EXPECT_EQ("", n.tag());
}

// Test set_style and style()
TEST_F(NodeTest_246, SetStyleBlock_246) {
  node n;
  n.mark_defined();
  n.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, n.style());
}

TEST_F(NodeTest_246, SetStyleFlow_246) {
  node n;
  n.mark_defined();
  n.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, n.style());
}

TEST_F(NodeTest_246, SetStyleDefault_246) {
  node n;
  n.mark_defined();
  n.set_style(EmitterStyle::Default);
  EXPECT_EQ(EmitterStyle::Default, n.style());
}

// Test is() for identity comparison
TEST_F(NodeTest_246, IsSameNodeReturnsTrue_246) {
  node n;
  EXPECT_TRUE(n.is(n));
}

TEST_F(NodeTest_246, IsDifferentNodeReturnsFalse_246) {
  node n1;
  node n2;
  EXPECT_FALSE(n1.is(n2));
}

// Test ref() returns non-null
TEST_F(NodeTest_246, RefIsNotNull_246) {
  node n;
  EXPECT_NE(nullptr, n.ref());
}

// Test set_ref copies reference from another node
TEST_F(NodeTest_246, SetRefCopiesRef_246) {
  node n1;
  n1.mark_defined();
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("shared");

  node n2;
  n2.set_ref(n1);

  EXPECT_TRUE(n2.is_defined());
  EXPECT_EQ("shared", n2.scalar());
  EXPECT_EQ(NodeType::Scalar, n2.type());
}

// Test set_ref from undefined node
TEST_F(NodeTest_246, SetRefFromUndefinedNode_246) {
  node n1;  // undefined
  node n2;
  n2.mark_defined();

  n2.set_ref(n1);
  // After set_ref from undefined, n2 shares n1's ref
  // but is_defined depends on whether mark_defined was called
  // Since n1 is not defined, set_ref won't call mark_defined on n2
  // but the ref is shared, so type should match n1
}

// Test set_data
TEST_F(NodeTest_246, SetDataCopiesData_246) {
  node n1;
  n1.mark_defined();
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("data_value");
  n1.set_tag("!tag");

  node n2;
  n2.mark_defined();
  n2.set_data(n1);

  EXPECT_EQ("data_value", n2.scalar());
  EXPECT_EQ(NodeType::Scalar, n2.type());
}

// Test sequence operations: push_back and size
TEST_F(NodeTest_246, PushBackIncreasesSize_246) {
  node seq;
  seq.mark_defined();
  seq.set_type(NodeType::Sequence);

  EXPECT_EQ(0u, seq.size());

  node& elem1 = pMemory->create_node();
  elem1.mark_defined();
  elem1.set_type(NodeType::Scalar);
  elem1.set_scalar("item1");

  seq.push_back(elem1, pMemory);
  EXPECT_EQ(1u, seq.size());

  node& elem2 = pMemory->create_node();
  elem2.mark_defined();
  elem2.set_type(NodeType::Scalar);
  elem2.set_scalar("item2");

  seq.push_back(elem2, pMemory);
  EXPECT_EQ(2u, seq.size());
}

// Test begin/end for sequence
TEST_F(NodeTest_246, SequenceBeginEnd_246) {
  node seq;
  seq.mark_defined();
  seq.set_type(NodeType::Sequence);

  // Empty sequence: begin == end
  EXPECT_TRUE(seq.begin() == seq.end());

  node& elem = pMemory->create_node();
  elem.mark_defined();
  elem.set_type(NodeType::Scalar);
  elem.set_scalar("item");

  seq.push_back(elem, pMemory);

  // Non-empty sequence: begin != end
  EXPECT_FALSE(seq.begin() == seq.end());
}

// Test map operations: insert and get
TEST_F(NodeTest_246, InsertAndGetMap_246) {
  node map;
  map.mark_defined();
  map.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.mark_defined();
  key.set_type(NodeType::Scalar);
  key.set_scalar("key1");

  node& value = pMemory->create_node();
  value.mark_defined();
  value.set_type(NodeType::Scalar);
  value.set_scalar("value1");

  map.insert(key, value, pMemory);
  EXPECT_EQ(1u, map.size());

  node* result = map.get(key, pMemory);
  EXPECT_NE(nullptr, result);
}

// Test get with string key
TEST_F(NodeTest_246, GetWithStringKey_246) {
  node map;
  map.mark_defined();
  map.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.mark_defined();
  key.set_type(NodeType::Scalar);
  key.set_scalar("mykey");

  node& value = pMemory->create_node();
  value.mark_defined();
  value.set_type(NodeType::Scalar);
  value.set_scalar("myvalue");

  map.insert(key, value, pMemory);

  node* result = map.get(std::string("mykey"), pMemory);
  EXPECT_NE(nullptr, result);
}

// Test get with non-existent key returns nullptr
TEST_F(NodeTest_246, GetNonExistentKeyReturnsNull_246) {
  node map;
  map.mark_defined();
  map.set_type(NodeType::Map);

  node* result = map.get(std::string("nonexistent"), pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test remove from map
TEST_F(NodeTest_246, RemoveFromMap_246) {
  node map;
  map.mark_defined();
  map.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.mark_defined();
  key.set_type(NodeType::Scalar);
  key.set_scalar("to_remove");

  node& value = pMemory->create_node();
  value.mark_defined();
  value.set_type(NodeType::Scalar);
  value.set_scalar("val");

  map.insert(key, value, pMemory);
  EXPECT_EQ(1u, map.size());

  bool removed = map.remove(key, pMemory);
  EXPECT_TRUE(removed);
}

// Test remove non-existent key
TEST_F(NodeTest_246, RemoveNonExistentKey_246) {
  node map;
  map.mark_defined();
  map.set_type(NodeType::Map);

  bool removed = map.remove(std::string("no_such_key"), pMemory);
  EXPECT_FALSE(removed);
}

// Test remove with string key
TEST_F(NodeTest_246, RemoveWithStringKey_246) {
  node map;
  map.mark_defined();
  map.set_type(NodeType::Map);

  node& key = pMemory->create_node();
  key.mark_defined();
  key.set_type(NodeType::Scalar);
  key.set_scalar("strkey");

  node& value = pMemory->create_node();
  value.mark_defined();
  value.set_type(NodeType::Scalar);
  value.set_scalar("strval");

  map.insert(key, value, pMemory);

  bool removed = map.remove(std::string("strkey"), pMemory);
  EXPECT_TRUE(removed);
}

// Test equals with matching scalar
TEST_F(NodeTest_246, EqualsMatchingScalar_246) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");

  EXPECT_TRUE(n.equals(std::string("hello"), pMemory));
}

// Test equals with non-matching scalar
TEST_F(NodeTest_246, EqualsNonMatchingScalar_246) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");

  EXPECT_FALSE(n.equals(std::string("world"), pMemory));
}

// Test equals with const char*
TEST_F(NodeTest_246, EqualsConstCharPtr_246) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Scalar);
  n.set_scalar("test");

  EXPECT_TRUE(n.equals("test", pMemory));
  EXPECT_FALSE(n.equals("other", pMemory));
}

// Test set_mark and mark
TEST_F(NodeTest_246, SetMarkAndGetMark_246) {
  node n;
  n.mark_defined();
  Mark m;
  m.line = 10;
  m.column = 20;
  m.pos = 30;
  n.set_mark(m);

  const Mark& result = n.mark();
  EXPECT_EQ(10, result.line);
  EXPECT_EQ(20, result.column);
  EXPECT_EQ(30, result.pos);
}

// Test empty sequence size is 0
TEST_F(NodeTest_246, EmptySequenceSizeZero_246) {
  node seq;
  seq.mark_defined();
  seq.set_type(NodeType::Sequence);
  EXPECT_EQ(0u, seq.size());
}

// Test empty map size is 0
TEST_F(NodeTest_246, EmptyMapSizeZero_246) {
  node map;
  map.mark_defined();
  map.set_type(NodeType::Map);
  EXPECT_EQ(0u, map.size());
}

// Test force_insert on a map
TEST_F(NodeTest_246, ForceInsertMap_246) {
  node map;
  map.mark_defined();
  map.set_type(NodeType::Map);

  map.force_insert(std::string("fkey"), std::string("fval"), pMemory);
  EXPECT_EQ(1u, map.size());
}

// Test add_dependency does not crash
TEST_F(NodeTest_246, AddDependencyNoCrash_246) {
  node n1;
  node n2;
  n1.mark_defined();
  n2.mark_defined();
  // Should not crash
  n1.add_dependency(n2);
}

// Test set_ref makes both nodes share the same ref
TEST_F(NodeTest_246, SetRefSharesRef_246) {
  node n1;
  n1.mark_defined();
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("original");

  node n2;
  n2.set_ref(n1);

  // Both should report the same scalar since they share the ref
  EXPECT_EQ(n1.scalar(), n2.scalar());

  // Modifying through n1 should be visible through n2
  n1.set_scalar("modified");
  EXPECT_EQ("modified", n2.scalar());
}

// Test set_ref from defined node marks target as defined
TEST_F(NodeTest_246, SetRefFromDefinedNodeMarksDefined_246) {
  node n1;
  n1.mark_defined();
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("val");

  node n2;
  EXPECT_FALSE(n2.is_defined());
  n2.set_ref(n1);
  EXPECT_TRUE(n2.is_defined());
}

// Test multiple push_backs to sequence
TEST_F(NodeTest_246, MultiplePushBacks_246) {
  node seq;
  seq.mark_defined();
  seq.set_type(NodeType::Sequence);

  for (int i = 0; i < 10; ++i) {
    node& elem = pMemory->create_node();
    elem.mark_defined();
    elem.set_type(NodeType::Scalar);
    elem.set_scalar(std::to_string(i));
    seq.push_back(elem, pMemory);
  }

  EXPECT_EQ(10u, seq.size());
}

// Test multiple inserts to map
TEST_F(NodeTest_246, MultipleMapInserts_246) {
  node map;
  map.mark_defined();
  map.set_type(NodeType::Map);

  for (int i = 0; i < 5; ++i) {
    node& key = pMemory->create_node();
    key.mark_defined();
    key.set_type(NodeType::Scalar);
    key.set_scalar("key" + std::to_string(i));

    node& value = pMemory->create_node();
    value.mark_defined();
    value.set_type(NodeType::Scalar);
    value.set_scalar("val" + std::to_string(i));

    map.insert(key, value, pMemory);
  }

  EXPECT_EQ(5u, map.size());
}

// Test overwriting scalar
TEST_F(NodeTest_246, OverwriteScalar_246) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Scalar);
  n.set_scalar("first");
  EXPECT_EQ("first", n.scalar());

  n.set_scalar("second");
  EXPECT_EQ("second", n.scalar());
}

// Test changing type
TEST_F(NodeTest_246, ChangeType_246) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Scalar);
  EXPECT_EQ(NodeType::Scalar, n.type());

  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());

  n.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, n.type());
}

}  // namespace detail
}  // namespace YAML
