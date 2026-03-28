// TEST_ID: 256
//
// Unit tests for YAML::detail::node::end() const
//
// File under test: yaml-cpp/node/detail/node.h
// Interface under test:
//   const_node_iterator end() const;
//
// Notes:
// - These tests treat the implementation as a black box.
// - Behavior is verified only via public interfaces (begin/end/push_back/insert/size/type).
// - We avoid relying on internal state or implementation details.

#include <gtest/gtest.h>

#include <iterator>   // std::distance
#include <type_traits>

#include "yaml-cpp/node/detail/node.h"

namespace {

class NodeEndTest_256 : public ::testing::Test {};

TEST_F(NodeEndTest_256, EndIsCallableOnConstNode_256) {
  const YAML::detail::node n;

  // Should be callable and not throw (observable behavior).
  EXPECT_NO_THROW({
    auto it = n.end();
    (void)it;
  });
}

TEST_F(NodeEndTest_256, EndEqualsBeginOnDefaultConstructedNode_256) {
  const YAML::detail::node n;

  // For an empty container-like interface, begin/end should match.
  // (We only assert what is observable via the iterator interface.)
  EXPECT_EQ(n.begin(), n.end());

  // If iterators are at least input iterators, distance(begin,end) should be 0.
  EXPECT_EQ(std::distance(n.begin(), n.end()), 0);
}

TEST_F(NodeEndTest_256, EndIsIdempotent_256) {
  const YAML::detail::node n;

  const auto e1 = n.end();
  const auto e2 = n.end();
  EXPECT_EQ(e1, e2);
}

TEST_F(NodeEndTest_256, EndMatchesAfterNonConstMutationWhenViewedAsConst_256) {
  YAML::detail::node n;

  // Mutate (if supported). We don't assume which mutations affect iteration;
  // we only ensure calling end() on a const view remains valid and consistent.
  EXPECT_NO_THROW({
    // Attempt to make it a sequence and add one element.
    n.set_type(YAML::NodeType::Sequence);
    YAML::detail::node child;
    child.set_scalar("x");
    YAML::detail::shared_memory_holder mem;  // default/empty holder should be acceptable
    n.push_back(child, mem);
  });

  const YAML::detail::node& cn = n;

  EXPECT_NO_THROW({
    auto b = cn.begin();
    auto e = cn.end();
    (void)b;
    (void)e;
  });

  // Const and non-const views should agree on iterator endpoints.
  EXPECT_EQ(cn.end(), n.end());
}

TEST_F(NodeEndTest_256, EndUpdatesAfterPushBackIntoSequence_256) {
  YAML::detail::node n;
  n.set_type(YAML::NodeType::Sequence);

  YAML::detail::shared_memory_holder mem;

  const auto before = std::distance(n.begin(), n.end());

  YAML::detail::node child;
  child.set_scalar("item");
  n.push_back(child, mem);

  const auto after = std::distance(n.begin(), n.end());

  // Observable effect: iteration span should grow by 1 for a sequence push_back.
  EXPECT_EQ(after, before + 1);
  EXPECT_NE(n.begin(), n.end());
}

TEST_F(NodeEndTest_256, EndUpdatesAfterInsertIntoMap_256) {
  YAML::detail::node n;
  n.set_type(YAML::NodeType::Map);

  YAML::detail::shared_memory_holder mem;

  const auto before = std::distance(n.begin(), n.end());

  YAML::detail::node key;
  key.set_scalar("k");
  YAML::detail::node value;
  value.set_scalar("v");

  n.insert(key, value, mem);

  const auto after = std::distance(n.begin(), n.end());

  // Observable effect: map iteration span should grow by 1 for an insert.
  EXPECT_EQ(after, before + 1);
  EXPECT_NE(n.begin(), n.end());
}

}  // namespace