// TEST_ID: 653
// File: test_node_data_remove_653.cpp

#include <gtest/gtest.h>

#include <yaml-cpp/node/detail/node.h>
#include <yaml-cpp/node/detail/node_data.h>
#include <yaml-cpp/node/detail/memory.h>

namespace {

using YAML::detail::node;
using YAML::detail::node_data;
using YAML::detail::shared_memory_holder;
using YAML::detail::memory_holder;
using YAML::detail::NodeType;

// Helper to make a memory holder (yaml-cpp internals typically require it)
shared_memory_holder MakeMemory_653() {
  return shared_memory_holder(new memory_holder());
}

// Helper to make a node backed by the same memory holder
node& NewNode_653(shared_memory_holder& mem) {
  // memory_holder typically owns created nodes; create_node() returns node*
  return *mem->create_node();
}

// Helper to create a scalar node (so node::is(key) can match by content)
node& NewScalarNode_653(shared_memory_holder& mem, const std::string& value) {
  node& n = NewNode_653(mem);
  n.mark_defined();
  n.set_scalar(value);
  return n;
}

}  // namespace

// remove() should return false if the node_data is not a map (observable return value).
TEST(NodeDataRemoveTest_653, ReturnsFalseWhenNotMap_653) {
  shared_memory_holder mem = MakeMemory_653();

  node_data data;
  data.set_type(NodeType::Scalar);

  node& key = NewScalarNode_653(mem, "k");

  EXPECT_FALSE(data.remove(key, mem));
}

// When map is empty, remove() should return false.
TEST(NodeDataRemoveTest_653, EmptyMapReturnsFalse_653) {
  shared_memory_holder mem = MakeMemory_653();

  node_data data;
  data.set_type(NodeType::Map);

  node& key = NewScalarNode_653(mem, "k");

  EXPECT_FALSE(data.remove(key, mem));
}

// When the key does not exist in the map, remove() should return false and not change size.
TEST(NodeDataRemoveTest_653, MissingKeyReturnsFalseAndKeepsSize_653) {
  shared_memory_holder mem = MakeMemory_653();

  node_data data;
  data.set_type(NodeType::Map);

  node& existingKey = NewScalarNode_653(mem, "existing");
  node& existingVal = NewScalarNode_653(mem, "v");
  data.insert(existingKey, existingVal, mem);

  const std::size_t before = data.size();
  ASSERT_GE(before, 1u);

  node& missingKey = NewScalarNode_653(mem, "missing");
  EXPECT_FALSE(data.remove(missingKey, mem));
  EXPECT_EQ(data.size(), before);
}

// When the key exists, remove() should return true and the entry should be gone afterward.
TEST(NodeDataRemoveTest_653, ExistingKeyReturnsTrueAndRemovesEntry_653) {
  shared_memory_holder mem = MakeMemory_653();

  node_data data;
  data.set_type(NodeType::Map);

  node& key = NewScalarNode_653(mem, "k");
  node& val = NewScalarNode_653(mem, "v");
  data.insert(key, val, mem);

  const std::size_t before = data.size();
  ASSERT_GE(before, 1u);

  EXPECT_TRUE(data.remove(key, mem));
  EXPECT_EQ(data.size(), before - 1);

  // Removing again should now return false (idempotent behavior observable via return value).
  EXPECT_FALSE(data.remove(key, mem));
}

// Removing one key from a multi-entry map should not remove other entries.
TEST(NodeDataRemoveTest_653, RemovesOnlyMatchingKeyInMultiEntryMap_653) {
  shared_memory_holder mem = MakeMemory_653();

  node_data data;
  data.set_type(NodeType::Map);

  node& k1 = NewScalarNode_653(mem, "k1");
  node& v1 = NewScalarNode_653(mem, "v1");
  node& k2 = NewScalarNode_653(mem, "k2");
  node& v2 = NewScalarNode_653(mem, "v2");
  node& k3 = NewScalarNode_653(mem, "k3");
  node& v3 = NewScalarNode_653(mem, "v3");

  data.insert(k1, v1, mem);
  data.insert(k2, v2, mem);
  data.insert(k3, v3, mem);

  const std::size_t before = data.size();
  ASSERT_GE(before, 3u);

  EXPECT_TRUE(data.remove(k2, mem));
  EXPECT_EQ(data.size(), before - 1);

  // Other keys should still be removable (i.e., still present).
  EXPECT_TRUE(data.remove(k1, mem));
  EXPECT_TRUE(data.remove(k3, mem));
  EXPECT_EQ(data.size(), 0u);
}

// Boundary-ish case: removing from a map that contains a key node with identical scalar content.
// This validates observable behavior of matching via node::is(key) (black-box via return value).
TEST(NodeDataRemoveTest_653, MatchesKeyByContentNotPointer_653) {
  shared_memory_holder mem = MakeMemory_653();

  node_data data;
  data.set_type(NodeType::Map);

  node& storedKey = NewScalarNode_653(mem, "same");
  node& storedVal = NewScalarNode_653(mem, "v");
  data.insert(storedKey, storedVal, mem);

  // A distinct node with the same scalar content.
  node& queryKey = NewScalarNode_653(mem, "same");

  EXPECT_TRUE(data.remove(queryKey, mem));
  EXPECT_FALSE(data.remove(queryKey, mem));
  EXPECT_EQ(data.size(), 0u);
}