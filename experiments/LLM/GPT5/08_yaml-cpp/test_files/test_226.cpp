// File: test/node_ref_begin_test_226.cpp

#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_ref.h"

namespace {

using YAML::detail::node_ref;

class NodeRefBeginTest_226 : public ::testing::Test {};

TEST_F(NodeRefBeginTest_226, DefaultConstructedBeginEqualsEnd_226) {
  node_ref nr;

  const auto b = nr.begin();
  const auto e = nr.end();

  EXPECT_EQ(b, e);
}

TEST_F(NodeRefBeginTest_226, BeginCallableOnConstObject_226) {
  node_ref nr;
  const node_ref& cnr = nr;

  const auto b = cnr.begin();
  const auto e = cnr.end();

  EXPECT_EQ(b, e);
}

TEST_F(NodeRefBeginTest_226, BeginIsStableAcrossCalls_226) {
  node_ref nr;

  const auto b1 = nr.begin();
  const auto b2 = nr.begin();
  const auto e = nr.end();

  EXPECT_EQ(b1, b2);
  EXPECT_EQ(b1, e);
}

TEST_F(NodeRefBeginTest_226, BeginDoesNotChangeObservableSize_226) {
  node_ref nr;

  const std::size_t s1 = nr.size();
  (void)nr.begin();
  const std::size_t s2 = nr.size();

  EXPECT_EQ(s1, s2);
}

}  // namespace