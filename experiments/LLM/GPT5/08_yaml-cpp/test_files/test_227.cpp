// TEST_ID: 227
#include <gtest/gtest.h>

#include <iterator>

#include "yaml-cpp/node/detail/node_ref.h"

namespace {

using YAML::detail::node_ref;

class NodeRefEndTest_227 : public ::testing::Test {};

TEST_F(NodeRefEndTest_227, DefaultConstructed_BeginEqualsEnd_227) {
  const node_ref n;

  // Observable iterator property for an empty/default node.
  EXPECT_EQ(n.begin(), n.end());
}

TEST_F(NodeRefEndTest_227, DefaultConstructed_DistanceMatchesSize_227) {
  const node_ref n;

  // end() must be usable and consistent with begin()/size().
  const auto dist = static_cast<std::size_t>(std::distance(n.begin(), n.end()));
  EXPECT_EQ(dist, n.size());
}

TEST_F(NodeRefEndTest_227, EndIsStableAcrossMultipleCalls_227) {
  const node_ref n;

  const auto e1 = n.end();
  const auto e2 = n.end();
  EXPECT_EQ(e1, e2);

  const auto b1 = n.begin();
  const auto b2 = n.begin();
  EXPECT_EQ(b1, b2);

  EXPECT_EQ(b1, e1);
}

TEST_F(NodeRefEndTest_227, AfterSetNull_BeginEqualsEndAndDistanceMatchesSize_227) {
  node_ref n;
  n.set_null();

  EXPECT_EQ(n.begin(), n.end());
  const auto dist = static_cast<std::size_t>(std::distance(n.begin(), n.end()));
  EXPECT_EQ(dist, n.size());
}

TEST_F(NodeRefEndTest_227, AfterSetScalar_BeginEqualsEndAndDistanceMatchesSize_227) {
  node_ref n;
  n.set_scalar("hello");

  EXPECT_EQ(n.begin(), n.end());
  const auto dist = static_cast<std::size_t>(std::distance(n.begin(), n.end()));
  EXPECT_EQ(dist, n.size());
}

TEST_F(NodeRefEndTest_227, AfterSetTypeToNull_BeginEqualsEndAndDistanceMatchesSize_227) {
  node_ref n;
  n.set_type(YAML::NodeType::Null);

  EXPECT_EQ(n.begin(), n.end());
  const auto dist = static_cast<std::size_t>(std::distance(n.begin(), n.end()));
  EXPECT_EQ(dist, n.size());
}

TEST_F(NodeRefEndTest_227, AfterSetTypeToSequence_EmptySequenceBeginEqualsEnd_227) {
  node_ref n;
  n.set_type(YAML::NodeType::Sequence);

  // With no pushed elements, iterating should still be empty.
  EXPECT_EQ(n.begin(), n.end());
  const auto dist = static_cast<std::size_t>(std::distance(n.begin(), n.end()));
  EXPECT_EQ(dist, n.size());
}

TEST_F(NodeRefEndTest_227, AfterSetTypeToMap_EmptyMapBeginEqualsEnd_227) {
  node_ref n;
  n.set_type(YAML::NodeType::Map);

  // With no inserted pairs, iterating should still be empty.
  EXPECT_EQ(n.begin(), n.end());
  const auto dist = static_cast<std::size_t>(std::distance(n.begin(), n.end()));
  EXPECT_EQ(dist, n.size());
}

TEST_F(NodeRefEndTest_227, ConstAccess_EndCallableAndConsistent_227) {
  node_ref n;
  n.set_scalar("x");

  const node_ref& cn = n;
  (void)cn.end();  // Should be callable on const object.

  EXPECT_EQ(cn.begin(), cn.end());
  const auto dist = static_cast<std::size_t>(std::distance(cn.begin(), cn.end()));
  EXPECT_EQ(dist, cn.size());
}

TEST_F(NodeRefEndTest_227, AfterSetData_SharedDataKeepsIteratorConsistency_227) {
  node_ref a;
  a.set_scalar("shared");

  node_ref b;
  b.set_data(a);

  // Observable: data-visible fields match; iterator contract remains consistent.
  EXPECT_EQ(b.scalar(), a.scalar());

  EXPECT_EQ(a.begin(), a.end());
  EXPECT_EQ(b.begin(), b.end());

  const auto dist_a = static_cast<std::size_t>(std::distance(a.begin(), a.end()));
  const auto dist_b = static_cast<std::size_t>(std::distance(b.begin(), b.end()));
  EXPECT_EQ(dist_a, a.size());
  EXPECT_EQ(dist_b, b.size());
}

}  // namespace