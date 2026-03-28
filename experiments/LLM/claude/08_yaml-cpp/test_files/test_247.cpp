#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeTest_247 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = create_memory();
  }

  shared_memory_holder pMemory;
};

// Test default construction - node should not be defined initially
TEST_F(NodeTest_247, DefaultConstructedNodeIsNotDefined_247) {
  node n;
  EXPECT_FALSE(n.is_defined());
}

// Test default construction - type should be Undefined
TEST_F(NodeTest_247, DefaultConstructedNodeTypeIsUndefined_247) {
  node n;
  EXPECT_EQ(NodeType::Undefined, n.type());
}

// Test mark_defined makes node defined
TEST_F(NodeTest_247, MarkDefinedMakesNodeDefined_247) {
  node n;
  n.mark_defined();
  EXPECT_TRUE(n.is_defined());
}

// Test set_null sets type to Null
TEST_F(NodeTest_247, SetNullSetsTypeToNull_247) {
  node n;
  n.mark_defined();
  n.set_null();
  EXPECT_EQ(NodeType::Null, n.type());
}

// Test set_scalar and scalar retrieval
TEST_F(NodeTest_247, SetScalarAndRetrieve_247) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");
  EXPECT_EQ("hello", n.scalar());
}

// Test set_type to Sequence
TEST_F(NodeTest_247, SetTypeSequence_247) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(NodeType::Sequence, n.type());
}

// Test set_type to Map
TEST_F(NodeTest_247, SetTypeMap_247) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, n.type());
}

// Test set_tag and tag retrieval
TEST_F(NodeTest_247, SetTagAndRetrieve_247) {
  node n;
  n.mark_defined();
  n.set_tag("!custom");
  EXPECT_EQ("!custom", n.tag());
}

// Test set_style and style retrieval
TEST_F(NodeTest_247, SetStyleAndRetrieve_247) {
  node n;
  n.mark_defined();
  n.set_style(EmitterStyle::Flow);
  EXPECT_EQ(EmitterStyle::Flow, n.style());
}

// Test is() identity - a node is itself
TEST_F(NodeTest_247, NodeIsItself_247) {
  node n;
  EXPECT_TRUE(n.is(n));
}

// Test is() - two different nodes are not the same
TEST_F(NodeTest_247, DifferentNodesAreNotSame_247) {
  node n1;
  node n2;
  EXPECT_FALSE(n1.is(n2));
}

// Test ref() returns non-null
TEST_F(NodeTest_247, RefReturnsNonNull_247) {
  node n;
  EXPECT_NE(nullptr, n.ref());
}

// Test set_data from another node copies data
TEST_F(NodeTest_247, SetDataCopiesScalar_247) {
  node src;
  src.mark_defined();
  src.set_type(NodeType::Scalar);
  src.set_scalar("copied");

  node dst;
  dst.set_data(src);
  EXPECT_TRUE(dst.is_defined());
  EXPECT_EQ("copied", dst.scalar());
}

// Test set_data from undefined node does not mark target as defined
TEST_F(NodeTest_247, SetDataFromUndefinedNodeDoesNotMarkDefined_247) {
  node src;  // not defined
  node dst;
  dst.set_data(src);
  EXPECT_FALSE(dst.is_defined());
}

// Test set_data from defined node marks target as defined
TEST_F(NodeTest_247, SetDataFromDefinedNodeMarksTargetDefined_247) {
  node src;
  src.mark_defined();
  src.set_null();

  node dst;
  EXPECT_FALSE(dst.is_defined());
  dst.set_data(src);
  EXPECT_TRUE(dst.is_defined());
}

// Test set_ref makes nodes share the same ref
TEST_F(NodeTest_247, SetRefSharesReference_247) {
  node n1;
  n1.mark_defined();
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("shared");

  node n2;
  n2.set_ref(n1);
  EXPECT_EQ("shared", n2.scalar());
  EXPECT_TRUE(n2.is_defined());
}

// Test size for empty sequence
TEST_F(NodeTest_247, EmptySequenceHasSizeZero_247) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Sequence);
  EXPECT_EQ(0u, n.size());
}

// Test push_back increases size
TEST_F(NodeTest_247, PushBackIncreasesSize_247) {
  node seq;
  seq.mark_defined();
  seq.set_type(NodeType::Sequence);

  node elem;
  elem.mark_defined();
  elem.set_type(NodeType::Scalar);
  elem.set_scalar("item1");

  seq.push_back(elem, pMemory);
  EXPECT_EQ(1u, seq.size());
}

// Test push_back multiple elements
TEST_F(NodeTest_247, PushBackMultipleElements_247) {
  node seq;
  seq.mark_defined();
  seq.set_type(NodeType::Sequence);

  node elem1;
  elem1.mark_defined();
  elem1.set_type(NodeType::Scalar);
  elem1.set_scalar("a");

  node elem2;
  elem2.mark_defined();
  elem2.set_type(NodeType::Scalar);
  elem2.set_scalar("b");

  seq.push_back(elem1, pMemory);
  seq.push_back(elem2, pMemory);
  EXPECT_EQ(2u, seq.size());
}

// Test empty map has size zero
TEST_F(NodeTest_247, EmptyMapHasSizeZero_247) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Map);
  EXPECT_EQ(0u, n.size());
}

// Test insert into map increases size
TEST_F(NodeTest_247, InsertIntoMapIncreasesSize_247) {
  node map;
  map.mark_defined();
  map.set_type(NodeType::Map);

  node key;
  key.mark_defined();
  key.set_type(NodeType::Scalar);
  key.set_scalar("key1");

  node value;
  value.mark_defined();
  value.set_type(NodeType::Scalar);
  value.set_scalar("value1");

  map.insert(key, value, pMemory);
  EXPECT_EQ(1u, map.size());
}

// Test get from map by string key
TEST_F(NodeTest_247, GetFromMapByStringKey_247) {
  node map;
  map.mark_defined();
  map.set_type(NodeType::Map);

  node key;
  key.mark_defined();
  key.set_type(NodeType::Scalar);
  key.set_scalar("mykey");

  node value;
  value.mark_defined();
  value.set_type(NodeType::Scalar);
  value.set_scalar("myvalue");

  map.insert(key, value, pMemory);

  node* result = map.get(std::string("mykey"), pMemory);
  EXPECT_NE(nullptr, result);
  if (result) {
    EXPECT_EQ("myvalue", result->scalar());
  }
}

// Test get returns nullptr for non-existent key
TEST_F(NodeTest_247, GetReturnsNullForNonExistentKey_247) {
  node map;
  map.mark_defined();
  map.set_type(NodeType::Map);

  node* result = map.get(std::string("nonexistent"), pMemory);
  EXPECT_EQ(nullptr, result);
}

// Test remove from map
TEST_F(NodeTest_247, RemoveFromMap_247) {
  node map;
  map.mark_defined();
  map.set_type(NodeType::Map);

  node key;
  key.mark_defined();
  key.set_type(NodeType::Scalar);
  key.set_scalar("removeMe");

  node value;
  value.mark_defined();
  value.set_type(NodeType::Scalar);
  value.set_scalar("val");

  map.insert(key, value, pMemory);
  EXPECT_EQ(1u, map.size());

  bool removed = map.remove(std::string("removeMe"), pMemory);
  EXPECT_TRUE(removed);
}

// Test remove non-existent key returns false
TEST_F(NodeTest_247, RemoveNonExistentKeyReturnsFalse_247) {
  node map;
  map.mark_defined();
  map.set_type(NodeType::Map);

  bool removed = map.remove(std::string("nope"), pMemory);
  EXPECT_FALSE(removed);
}

// Test begin/end for empty sequence
TEST_F(NodeTest_247, BeginEqualsEndForEmptySequence_247) {
  node seq;
  seq.mark_defined();
  seq.set_type(NodeType::Sequence);
  EXPECT_TRUE(seq.begin() == seq.end());
}

// Test equals with matching scalar
TEST_F(NodeTest_247, EqualsMatchingScalar_247) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Scalar);
  n.set_scalar("test");

  EXPECT_TRUE(n.equals(std::string("test"), pMemory));
}

// Test equals with non-matching scalar
TEST_F(NodeTest_247, EqualsNonMatchingScalar_247) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Scalar);
  n.set_scalar("test");

  EXPECT_FALSE(n.equals(std::string("other"), pMemory));
}

// Test equals with const char*
TEST_F(NodeTest_247, EqualsConstCharPtr_247) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Scalar);
  n.set_scalar("hello");

  EXPECT_TRUE(n.equals("hello", pMemory));
  EXPECT_FALSE(n.equals("world", pMemory));
}

// Test set_mark
TEST_F(NodeTest_247, SetMarkAndRetrieve_247) {
  node n;
  Mark m;
  m.line = 5;
  m.column = 10;
  n.set_mark(m);
  EXPECT_EQ(5, n.mark().line);
  EXPECT_EQ(10, n.mark().column);
}

// Test set_scalar on empty string
TEST_F(NodeTest_247, SetScalarEmptyString_247) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Scalar);
  n.set_scalar("");
  EXPECT_EQ("", n.scalar());
}

// Test set_tag empty string
TEST_F(NodeTest_247, SetTagEmptyString_247) {
  node n;
  n.mark_defined();
  n.set_tag("");
  EXPECT_EQ("", n.tag());
}

// Test default style
TEST_F(NodeTest_247, DefaultStyleIsDefault_247) {
  node n;
  EXPECT_EQ(EmitterStyle::Default, n.style());
}

// Test set_style Block
TEST_F(NodeTest_247, SetStyleBlock_247) {
  node n;
  n.set_style(EmitterStyle::Block);
  EXPECT_EQ(EmitterStyle::Block, n.style());
}

// Test set_data copies type
TEST_F(NodeTest_247, SetDataCopiesType_247) {
  node src;
  src.mark_defined();
  src.set_type(NodeType::Sequence);

  node dst;
  dst.set_data(src);
  EXPECT_EQ(NodeType::Sequence, dst.type());
}

// Test add_dependency does not change the node's own state
TEST_F(NodeTest_247, AddDependencyDoesNotChangeDefinedState_247) {
  node n;
  node dep;
  dep.mark_defined();

  EXPECT_FALSE(n.is_defined());
  n.add_dependency(dep);
  EXPECT_FALSE(n.is_defined());
}

// Test get by node key
TEST_F(NodeTest_247, GetByNodeKey_247) {
  node map;
  map.mark_defined();
  map.set_type(NodeType::Map);

  node key;
  key.mark_defined();
  key.set_type(NodeType::Scalar);
  key.set_scalar("nodekey");

  node value;
  value.mark_defined();
  value.set_type(NodeType::Scalar);
  value.set_scalar("nodevalue");

  map.insert(key, value, pMemory);

  node lookupKey;
  lookupKey.mark_defined();
  lookupKey.set_type(NodeType::Scalar);
  lookupKey.set_scalar("nodekey");

  node* result = map.get(lookupKey, pMemory);
  EXPECT_NE(nullptr, result);
  if (result) {
    EXPECT_EQ("nodevalue", result->scalar());
  }
}

// Test remove by node key
TEST_F(NodeTest_247, RemoveByNodeKey_247) {
  node map;
  map.mark_defined();
  map.set_type(NodeType::Map);

  node key;
  key.mark_defined();
  key.set_type(NodeType::Scalar);
  key.set_scalar("toremove");

  node value;
  value.mark_defined();
  value.set_type(NodeType::Scalar);
  value.set_scalar("val");

  map.insert(key, value, pMemory);

  node removeKey;
  removeKey.mark_defined();
  removeKey.set_type(NodeType::Scalar);
  removeKey.set_scalar("toremove");

  bool removed = map.remove(removeKey, pMemory);
  EXPECT_TRUE(removed);
}

// Test force_insert into map
TEST_F(NodeTest_247, ForceInsertIntoMap_247) {
  node map;
  map.mark_defined();
  map.set_type(NodeType::Map);

  map.force_insert(std::string("fkey"), std::string("fval"), pMemory);
  EXPECT_EQ(1u, map.size());

  node* result = map.get(std::string("fkey"), pMemory);
  EXPECT_NE(nullptr, result);
  if (result) {
    EXPECT_EQ("fval", result->scalar());
  }
}

// Test changing type from Scalar to Map
TEST_F(NodeTest_247, ChangeTypeFromScalarToMap_247) {
  node n;
  n.mark_defined();
  n.set_type(NodeType::Scalar);
  n.set_scalar("test");
  EXPECT_EQ(NodeType::Scalar, n.type());

  n.set_type(NodeType::Map);
  EXPECT_EQ(NodeType::Map, n.type());
}

// Test set_ref then modify original
TEST_F(NodeTest_247, SetRefSharesUnderlyingData_247) {
  node n1;
  n1.mark_defined();
  n1.set_type(NodeType::Scalar);
  n1.set_scalar("initial");

  node n2;
  n2.set_ref(n1);
  EXPECT_EQ("initial", n2.scalar());

  // After set_ref, n2 should share the same ref as n1
  EXPECT_TRUE(n2.is_defined());
}

}  // namespace detail
}  // namespace YAML
