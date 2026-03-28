// TEST_ID: 236
#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node.h"

namespace {

using YAML::detail::node;

class NodeIsTest_236 : public ::testing::Test {};

TEST_F(NodeIsTest_236, Reflexive_IsSelfTrue_236) {
  node a;
  EXPECT_TRUE(a.is(a));
}

TEST_F(NodeIsTest_236, DistinctDefaultConstructedNodes_AreNotSame_236) {
  node a;
  node b;

  EXPECT_FALSE(a.is(b));
  EXPECT_FALSE(b.is(a));
}

TEST_F(NodeIsTest_236, AfterSetRef_NodesBecomeSame_236) {
  node a;
  node b;

  b.set_ref(a);

  EXPECT_TRUE(a.is(b));
  EXPECT_TRUE(b.is(a));
}

TEST_F(NodeIsTest_236, TransitiveSharingViaSetRef_AllSame_236) {
  node a;
  node b;
  node c;

  b.set_ref(a);
  c.set_ref(b);

  EXPECT_TRUE(a.is(b));
  EXPECT_TRUE(b.is(c));
  EXPECT_TRUE(a.is(c));

  EXPECT_TRUE(b.is(a));
  EXPECT_TRUE(c.is(b));
  EXPECT_TRUE(c.is(a));
}

TEST_F(NodeIsTest_236, SharingRefDoesNotAffectUnrelatedNode_236) {
  node a;
  node b;
  node c;

  b.set_ref(a);

  EXPECT_TRUE(a.is(b));
  EXPECT_FALSE(a.is(c));
  EXPECT_FALSE(b.is(c));
  EXPECT_FALSE(c.is(a));
  EXPECT_FALSE(c.is(b));
}

TEST_F(NodeIsTest_236, RepeatedCalls_AreStable_236) {
  node a;
  node b;

  // Repeated checks should not mutate observable behavior.
  EXPECT_FALSE(a.is(b));
  EXPECT_FALSE(a.is(b));

  b.set_ref(a);

  EXPECT_TRUE(a.is(b));
  EXPECT_TRUE(a.is(b));
  EXPECT_TRUE(b.is(a));
  EXPECT_TRUE(b.is(a));
}

}  // namespace