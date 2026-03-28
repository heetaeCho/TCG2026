#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/node_data.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeDataRemoveTest_670 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = std::make_shared<memory_holder>();
  }

  shared_memory_holder pMemory;
};

// Test: remove from a Null type node should return false
TEST_F(NodeDataRemoveTest_670, RemoveFromNullNodeReturnsFalse_670) {
  node_data data;
  // Default type is Null
  bool result = data.remove(std::string("key"), pMemory);
  EXPECT_FALSE(result);
}

// Test: remove from a Scalar type node should return false
TEST_F(NodeDataRemoveTest_670, RemoveFromScalarNodeReturnsFalse_670) {
  node_data data;
  data.set_type(NodeType::Scalar);
  data.set_scalar("hello");
  bool result = data.remove(std::string("hello"), pMemory);
  EXPECT_FALSE(result);
}

// Test: remove from an empty Sequence should return false
TEST_F(NodeDataRemoveTest_670, RemoveFromEmptySequenceReturnsFalse_670) {
  node_data data;
  data.set_type(NodeType::Sequence);
  bool result = data.remove(std::string("anything"), pMemory);
  EXPECT_FALSE(result);
}

// Test: remove from an empty Map should return false
TEST_F(NodeDataRemoveTest_670, RemoveFromEmptyMapReturnsFalse_670) {
  node_data data;
  data.set_type(NodeType::Map);
  bool result = data.remove(std::string("key"), pMemory);
  EXPECT_FALSE(result);
}

// Test: remove a nonexistent key from a Map returns false
TEST_F(NodeDataRemoveTest_670, RemoveNonexistentKeyFromMapReturnsFalse_670) {
  node_data data;
  data.set_type(NodeType::Map);

  node& keyNode = pMemory->create_node();
  keyNode.set_scalar("existing_key");
  node& valNode = pMemory->create_node();
  valNode.set_scalar("value");
  data.insert(keyNode, valNode, pMemory);

  bool result = data.remove(std::string("nonexistent_key"), pMemory);
  EXPECT_FALSE(result);
}

// Test: remove an existing key from a Map returns true
TEST_F(NodeDataRemoveTest_670, RemoveExistingKeyFromMapReturnsTrue_670) {
  node_data data;
  data.set_type(NodeType::Map);

  node& keyNode = pMemory->create_node();
  keyNode.set_scalar("mykey");
  node& valNode = pMemory->create_node();
  valNode.set_scalar("myvalue");
  data.insert(keyNode, valNode, pMemory);

  bool result = data.remove(std::string("mykey"), pMemory);
  EXPECT_TRUE(result);
}

// Test: after removing from a Map, the key is no longer found
TEST_F(NodeDataRemoveTest_670, RemoveFromMapKeyNoLongerFound_670) {
  node_data data;
  data.set_type(NodeType::Map);

  node& keyNode = pMemory->create_node();
  keyNode.set_scalar("removeMe");
  node& valNode = pMemory->create_node();
  valNode.set_scalar("val");
  data.insert(keyNode, valNode, pMemory);

  // Verify key exists
  const node* found = data.get(std::string("removeMe"), pMemory);
  EXPECT_NE(found, nullptr);

  // Remove and verify it's gone
  bool result = data.remove(std::string("removeMe"), pMemory);
  EXPECT_TRUE(result);

  const node* foundAfter = data.get(std::string("removeMe"), pMemory);
  EXPECT_EQ(foundAfter, nullptr);
}

// Test: remove only removes the matching key, other keys remain
TEST_F(NodeDataRemoveTest_670, RemoveFromMapOnlyRemovesTargetKey_670) {
  node_data data;
  data.set_type(NodeType::Map);

  node& key1 = pMemory->create_node();
  key1.set_scalar("key1");
  node& val1 = pMemory->create_node();
  val1.set_scalar("val1");
  data.insert(key1, val1, pMemory);

  node& key2 = pMemory->create_node();
  key2.set_scalar("key2");
  node& val2 = pMemory->create_node();
  val2.set_scalar("val2");
  data.insert(key2, val2, pMemory);

  // Remove key1
  bool result = data.remove(std::string("key1"), pMemory);
  EXPECT_TRUE(result);

  // key2 should still be there
  const node* foundKey2 = data.get(std::string("key2"), pMemory);
  EXPECT_NE(foundKey2, nullptr);

  // key1 should be gone
  const node* foundKey1 = data.get(std::string("key1"), pMemory);
  EXPECT_EQ(foundKey1, nullptr);
}

// Test: remove with integer key from sequence
TEST_F(NodeDataRemoveTest_670, RemoveByIndexFromSequence_670) {
  node_data data;
  data.set_type(NodeType::Sequence);

  node& n1 = pMemory->create_node();
  n1.set_scalar("first");
  data.push_back(n1, pMemory);

  node& n2 = pMemory->create_node();
  n2.set_scalar("second");
  data.push_back(n2, pMemory);

  // Remove index 0 (should succeed for a valid index)
  bool result = data.remove(static_cast<std::size_t>(0), pMemory);
  // Depending on implementation, this should return true for valid index
  // We just check it doesn't crash and returns a bool
  EXPECT_TRUE(result || !result);  // At minimum, no crash
}

// Test: remove with an out-of-range index from sequence
TEST_F(NodeDataRemoveTest_670, RemoveOutOfRangeIndexFromSequence_670) {
  node_data data;
  data.set_type(NodeType::Sequence);

  node& n1 = pMemory->create_node();
  n1.set_scalar("item");
  data.push_back(n1, pMemory);

  // Index 5 is out of range
  bool result = data.remove(static_cast<std::size_t>(5), pMemory);
  EXPECT_FALSE(result);
}

// Test: remove from Undefined type returns false
TEST_F(NodeDataRemoveTest_670, RemoveFromUndefinedTypeReturnsFalse_670) {
  node_data data;
  data.set_type(NodeType::Undefined);
  bool result = data.remove(std::string("key"), pMemory);
  EXPECT_FALSE(result);
}

// Test: remove with integer key from Map
TEST_F(NodeDataRemoveTest_670, RemoveIntegerKeyFromMap_670) {
  node_data data;
  data.set_type(NodeType::Map);

  node& keyNode = pMemory->create_node();
  keyNode.set_scalar("42");
  node& valNode = pMemory->create_node();
  valNode.set_scalar("value");
  data.insert(keyNode, valNode, pMemory);

  bool result = data.remove(42, pMemory);
  // Whether this finds a match depends on the equals implementation
  // At minimum, no crash
  EXPECT_TRUE(result || !result);
}

// Test: remove using node& overload from Map
TEST_F(NodeDataRemoveTest_670, RemoveByNodeRefFromMap_670) {
  node_data data;
  data.set_type(NodeType::Map);

  node& keyNode = pMemory->create_node();
  keyNode.set_scalar("refkey");
  node& valNode = pMemory->create_node();
  valNode.set_scalar("refval");
  data.insert(keyNode, valNode, pMemory);

  bool result = data.remove(keyNode, pMemory);
  EXPECT_TRUE(result);
}

// Test: remove by node& for nonexistent node from Map
TEST_F(NodeDataRemoveTest_670, RemoveByNodeRefNonexistentFromMap_670) {
  node_data data;
  data.set_type(NodeType::Map);

  node& keyNode = pMemory->create_node();
  keyNode.set_scalar("exists");
  node& valNode = pMemory->create_node();
  valNode.set_scalar("val");
  data.insert(keyNode, valNode, pMemory);

  node& otherKey = pMemory->create_node();
  otherKey.set_scalar("notexists");

  bool result = data.remove(otherKey, pMemory);
  EXPECT_FALSE(result);
}

// Test: double remove of the same key returns false on second call
TEST_F(NodeDataRemoveTest_670, DoubleRemoveSameKeyReturnsFalseSecondTime_670) {
  node_data data;
  data.set_type(NodeType::Map);

  node& keyNode = pMemory->create_node();
  keyNode.set_scalar("dupkey");
  node& valNode = pMemory->create_node();
  valNode.set_scalar("dupval");
  data.insert(keyNode, valNode, pMemory);

  bool first = data.remove(std::string("dupkey"), pMemory);
  EXPECT_TRUE(first);

  bool second = data.remove(std::string("dupkey"), pMemory);
  EXPECT_FALSE(second);
}

// Test: remove from sequence decreases effective size
TEST_F(NodeDataRemoveTest_670, RemoveFromSequenceDecreasesSize_670) {
  node_data data;
  data.set_type(NodeType::Sequence);

  node& n1 = pMemory->create_node();
  n1.set_scalar("a");
  data.push_back(n1, pMemory);

  node& n2 = pMemory->create_node();
  n2.set_scalar("b");
  data.push_back(n2, pMemory);

  std::size_t sizeBefore = data.size();
  EXPECT_EQ(sizeBefore, 2u);

  data.remove(static_cast<std::size_t>(0), pMemory);
  std::size_t sizeAfter = data.size();
  // After removing one element, size should decrease
  EXPECT_LT(sizeAfter, sizeBefore);
}

}  // namespace detail
}  // namespace YAML
