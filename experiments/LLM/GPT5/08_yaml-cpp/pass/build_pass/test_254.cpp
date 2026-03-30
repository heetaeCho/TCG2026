// File: test/node_size_test_254.cpp

#include <gtest/gtest.h>

#include <cstddef>

#include "yaml-cpp/node/detail/node.h"

// We only rely on what the public interface shows: methods take/return shared_memory_holder,
// but we don't need its definition to pass a default-constructed value.
using YAML::detail::node;
using YAML::detail::shared_memory_holder;

namespace {

class NodeSizeTest_254 : public ::testing::Test {
 protected:
  static shared_memory_holder NoMemory() { return shared_memory_holder(); }
};

TEST_F(NodeSizeTest_254, DefaultConstructedHasDeterministicSize_254) {
  node n;
  // Observable behavior: calling size() should be safe and deterministic.
  EXPECT_EQ(n.size(), std::size_t{0});
}

TEST_F(NodeSizeTest_254, SizeUnchangedByScalarAndNullSetters_254) {
  node n;

  const std::size_t before = n.size();
  n.set_scalar("hello");
  EXPECT_EQ(n.size(), before);

  n.set_null();
  EXPECT_EQ(n.size(), before);
}

TEST_F(NodeSizeTest_254, SequencePushBackIncreasesSize_254) {
  node seq;
  seq.set_type(YAML::NodeType::Sequence);

  EXPECT_EQ(seq.size(), std::size_t{0});

  node a;
  a.set_scalar("a");
  seq.push_back(a, NoMemory());
  EXPECT_EQ(seq.size(), std::size_t{1});

  node b;
  b.set_scalar("b");
  seq.push_back(b, NoMemory());
  EXPECT_EQ(seq.size(), std::size_t{2});
}

TEST_F(NodeSizeTest_254, MapInsertIncreasesSize_254) {
  node map;
  map.set_type(YAML::NodeType::Map);

  EXPECT_EQ(map.size(), std::size_t{0});

  node k1;
  k1.set_scalar("k1");
  node v1;
  v1.set_scalar("v1");
  map.insert(k1, v1, NoMemory());
  EXPECT_EQ(map.size(), std::size_t{1});

  node k2;
  k2.set_scalar("k2");
  node v2;
  v2.set_scalar("v2");
  map.insert(k2, v2, NoMemory());
  EXPECT_EQ(map.size(), std::size_t{2});
}

TEST_F(NodeSizeTest_254, RemoveOnMapDecreasesSizeWhenElementIsPresent_254) {
  node map;
  map.set_type(YAML::NodeType::Map);

  node k1;
  k1.set_scalar("k1");
  node v1;
  v1.set_scalar("v1");
  map.insert(k1, v1, NoMemory());

  node k2;
  k2.set_scalar("k2");
  node v2;
  v2.set_scalar("v2");
  map.insert(k2, v2, NoMemory());

  ASSERT_EQ(map.size(), std::size_t{2});

  // Remove by node key overload (observable boolean + size change).
  EXPECT_TRUE(map.remove(k1, NoMemory()));
  EXPECT_EQ(map.size(), std::size_t{1});

  // Removing the same key again should not reduce size further.
  EXPECT_FALSE(map.remove(k1, NoMemory()));
  EXPECT_EQ(map.size(), std::size_t{1});
}

TEST_F(NodeSizeTest_254, GetDoesNotChangeSize_254) {
  node map;
  map.set_type(YAML::NodeType::Map);

  node key;
  key.set_scalar("k");
  node value;
  value.set_scalar("v");
  map.insert(key, value, NoMemory());

  const std::size_t before = map.size();
  (void)map.get(key, NoMemory());  // either returns non-null or null; size must not change
  EXPECT_EQ(map.size(), before);
}

TEST_F(NodeSizeTest_254, SetRefMakesSizeTrackSharedReference_254) {
  node a;
  a.set_type(YAML::NodeType::Sequence);

  node child;
  child.set_scalar("x");
  a.push_back(child, NoMemory());
  ASSERT_EQ(a.size(), std::size_t{1});

  node b;
  // After set_ref, b should observe the same size as a (observable via public API).
  b.set_ref(a);
  EXPECT_EQ(b.size(), a.size());

  node child2;
  child2.set_scalar("y");
  a.push_back(child2, NoMemory());

  // If references are shared as implied by set_ref's name/role, sizes should match.
  // This checks only observable behavior (size values), not internals.
  EXPECT_EQ(b.size(), a.size());
  EXPECT_EQ(a.size(), std::size_t{2});
}

}  // namespace