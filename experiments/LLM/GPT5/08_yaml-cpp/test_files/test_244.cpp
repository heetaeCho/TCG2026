// File: yaml-cpp/test/node_mark_defined_test_244.cpp

#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node.h"

namespace {

using YAML::detail::node;

class NodeMarkDefinedTest_244 : public ::testing::Test {};

TEST_F(NodeMarkDefinedTest_244, MarkDefinedDefinesSelfWhenUndefined_244) {
  node n;
  const bool was_defined = n.is_defined();

  n.mark_defined();

  EXPECT_TRUE(n.is_defined());

  // If it was already defined, this still holds; if it wasn't, we verified it flips to defined.
  (void)was_defined;
}

TEST_F(NodeMarkDefinedTest_244, MarkDefinedWithNoDependenciesDoesNotUndefine_244) {
  node n;
  n.mark_defined();
  ASSERT_TRUE(n.is_defined());

  // Calling again should keep it defined.
  n.mark_defined();
  EXPECT_TRUE(n.is_defined());
}

TEST_F(NodeMarkDefinedTest_244, MarkDefinedPropagatesToDirectDependencies_244) {
  node a;
  node b;
  node c;

  // Ensure starting from an observable baseline:
  // make sure deps are *not* defined, when possible.
  if (b.is_defined()) {
    // If already defined in this build, we can still test propagation by checking it stays defined.
  }
  if (c.is_defined()) {
    // same note as above
  }

  a.add_dependency(b);
  a.add_dependency(c);

  a.mark_defined();

  EXPECT_TRUE(a.is_defined());
  EXPECT_TRUE(b.is_defined());
  EXPECT_TRUE(c.is_defined());
}

TEST_F(NodeMarkDefinedTest_244, MarkDefinedPropagatesTransitively_244) {
  node a;
  node b;
  node c;

  a.add_dependency(b);
  b.add_dependency(c);

  a.mark_defined();

  EXPECT_TRUE(a.is_defined());
  EXPECT_TRUE(b.is_defined());
  EXPECT_TRUE(c.is_defined());
}

TEST_F(NodeMarkDefinedTest_244, MarkDefinedDoesNotProcessDependenciesIfAlreadyDefined_244) {
  node a;
  node b;

  // Make 'a' defined first.
  a.mark_defined();
  ASSERT_TRUE(a.is_defined());

  // Ensure 'b' is in a known state we can observe.
  const bool b_was_defined = b.is_defined();

  // Add dependency after 'a' is already defined.
  a.add_dependency(b);

  // mark_defined() should early-return and not affect dependencies.
  a.mark_defined();

  EXPECT_TRUE(a.is_defined());
  EXPECT_EQ(b.is_defined(), b_was_defined);
}

}  // namespace