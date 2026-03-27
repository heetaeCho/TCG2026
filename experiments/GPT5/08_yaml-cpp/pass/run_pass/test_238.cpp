// node_is_defined_tests_238.cpp

#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/node_ref.h"

namespace {

using YAML::detail::node;

// Focus: YAML::detail::node::is_defined() observable behavior.

class NodeIsDefinedTest_238 : public ::testing::Test {};

TEST_F(NodeIsDefinedTest_238, MatchesUnderlyingRefIsDefined_DefaultConstructed_238) {
  node n;
  ASSERT_NE(n.ref(), nullptr);
  EXPECT_EQ(n.is_defined(), n.ref()->is_defined());
}

TEST_F(NodeIsDefinedTest_238, MatchesUnderlyingRefIsDefined_AfterMarkDefined_238) {
  node n;
  ASSERT_NE(n.ref(), nullptr);

  n.mark_defined();

  EXPECT_EQ(n.is_defined(), n.ref()->is_defined());
}

TEST_F(NodeIsDefinedTest_238, AfterSetRef_TracksSameDefinitionStateAsSource_238) {
  node a;
  node b;

  // Share reference (observable via ref pointer equality).
  b.set_ref(a);

  ASSERT_NE(a.ref(), nullptr);
  ASSERT_NE(b.ref(), nullptr);
  EXPECT_EQ(a.ref(), b.ref());

  // Whatever the state is, they should match.
  EXPECT_EQ(a.is_defined(), b.is_defined());

  // Changing the definition state through one should be reflected in the other.
  a.mark_defined();
  EXPECT_EQ(a.is_defined(), b.is_defined());
  EXPECT_EQ(a.is_defined(), a.ref()->is_defined());
  EXPECT_EQ(b.is_defined(), b.ref()->is_defined());
}

TEST_F(NodeIsDefinedTest_238, SelfSetRef_DoesNotBreakIsDefinedContract_238) {
  node n;

  // Setting ref to itself should be safe/consistent.
  n.set_ref(n);

  ASSERT_NE(n.ref(), nullptr);
  EXPECT_EQ(n.is_defined(), n.ref()->is_defined());

  n.mark_defined();
  EXPECT_EQ(n.is_defined(), n.ref()->is_defined());
}

TEST_F(NodeIsDefinedTest_238, IndependentNodes_CanHaveDifferentDefinitionStates_238) {
  node a;
  node b;

  ASSERT_NE(a.ref(), nullptr);
  ASSERT_NE(b.ref(), nullptr);

  // Two independent nodes are expected to have independent refs in normal use.
  // If implementation shares refs by default, the pointer check will reveal that,
  // and the test will still validate the is_defined/ref contract for each node.
  if (a.ref() != b.ref()) {
    a.mark_defined();
    EXPECT_NE(a.is_defined(), b.is_defined());
  }

  EXPECT_EQ(a.is_defined(), a.ref()->is_defined());
  EXPECT_EQ(b.is_defined(), b.ref()->is_defined());
}

}  // namespace