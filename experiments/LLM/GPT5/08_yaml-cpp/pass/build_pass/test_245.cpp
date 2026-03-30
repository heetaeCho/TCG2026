// File: test/node/detail/node_add_dependency_test.cpp

#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node.h"

namespace {

using YAML::detail::node;

class AddDependencyTest_245 : public ::testing::Test {};

TEST_F(AddDependencyTest_245, WhenLhsIsDefined_AddDependencyMarksRhsDefined_245) {
  node lhs;
  node rhs;

  EXPECT_FALSE(rhs.is_defined());

  lhs.mark_defined();
  EXPECT_TRUE(lhs.is_defined());

  lhs.add_dependency(rhs);

  EXPECT_TRUE(rhs.is_defined());
}

TEST_F(AddDependencyTest_245, WhenLhsIsNotDefined_AddDependencyDoesNotImmediatelyDefineRhs_245) {
  node lhs;
  node rhs;

  EXPECT_FALSE(lhs.is_defined());
  EXPECT_FALSE(rhs.is_defined());

  lhs.add_dependency(rhs);

  // Observable behavior: if lhs isn't defined, rhs should not become defined immediately.
  EXPECT_FALSE(rhs.is_defined());
}

TEST_F(AddDependencyTest_245, WhenLhsLaterBecomesDefined_DependencyRhsBecomesDefined_245) {
  node lhs;
  node rhs;

  EXPECT_FALSE(lhs.is_defined());
  EXPECT_FALSE(rhs.is_defined());

  lhs.add_dependency(rhs);
  EXPECT_FALSE(rhs.is_defined());

  lhs.mark_defined();
  EXPECT_TRUE(lhs.is_defined());

  // Observable behavior: defining lhs should propagate to dependencies.
  EXPECT_TRUE(rhs.is_defined());
}

TEST_F(AddDependencyTest_245, MultipleDependencies_AllBecomeDefinedAfterLhsDefined_245) {
  node lhs;
  node rhs1;
  node rhs2;

  EXPECT_FALSE(lhs.is_defined());
  EXPECT_FALSE(rhs1.is_defined());
  EXPECT_FALSE(rhs2.is_defined());

  lhs.add_dependency(rhs1);
  lhs.add_dependency(rhs2);

  EXPECT_FALSE(rhs1.is_defined());
  EXPECT_FALSE(rhs2.is_defined());

  lhs.mark_defined();

  EXPECT_TRUE(rhs1.is_defined());
  EXPECT_TRUE(rhs2.is_defined());
}

TEST_F(AddDependencyTest_245, SelfDependency_DoesNotCrashAndRemainsDefinedAfterMarkDefined_245) {
  node n;

  // Add self as dependency while undefined, then define.
  EXPECT_FALSE(n.is_defined());
  n.add_dependency(n);

  n.mark_defined();
  EXPECT_TRUE(n.is_defined());

  // Add self as dependency while already defined.
  n.add_dependency(n);
  EXPECT_TRUE(n.is_defined());
}

}  // namespace