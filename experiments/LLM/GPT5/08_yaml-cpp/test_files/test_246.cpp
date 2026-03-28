// TEST_ID: 246
#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node.h"

namespace {

using YAML::detail::node;

class NodeSetRefTest_246 : public ::testing::Test {
 protected:
  static node MakeDefinedNode() {
    node n;
    n.mark_defined();  // public API; we only rely on observable is_defined().
    EXPECT_TRUE(n.is_defined());
    return n;
  }

  static node MakeUndefinedNode() {
    node n;
    // We assume default-constructed node can be undefined in this codebase.
    // If this ever changes, the assertions below will catch it.
    return n;
  }
};

TEST_F(NodeSetRefTest_246, SetRefCopiesReferencePointer_246) {
  node lhs;
  node rhs;

  const auto* rhsRefBefore = rhs.ref();
  ASSERT_NE(rhsRefBefore, nullptr);

  lhs.set_ref(rhs);

  EXPECT_EQ(lhs.ref(), rhsRefBefore);
  EXPECT_EQ(lhs.ref(), rhs.ref());
}

TEST_F(NodeSetRefTest_246, SetRefMarksDefinedWhenRhsIsDefined_246) {
  node lhs = MakeUndefinedNode();
  node rhs = MakeDefinedNode();

  // Precondition (observable): lhs should start undefined for this test.
  ASSERT_FALSE(lhs.is_defined());

  lhs.set_ref(rhs);

  EXPECT_TRUE(lhs.is_defined());
  EXPECT_EQ(lhs.ref(), rhs.ref());
}

TEST_F(NodeSetRefTest_246, SetRefDoesNotMarkDefinedWhenRhsIsUndefined_246) {
  node lhs = MakeUndefinedNode();
  node rhs = MakeUndefinedNode();

  // Precondition (observable): both start undefined for this test.
  ASSERT_FALSE(lhs.is_defined());
  ASSERT_FALSE(rhs.is_defined());

  lhs.set_ref(rhs);

  EXPECT_FALSE(lhs.is_defined());
  EXPECT_EQ(lhs.ref(), rhs.ref());
}

TEST_F(NodeSetRefTest_246, SetRefDoesNotUndefineAlreadyDefinedLhs_246) {
  node lhs = MakeDefinedNode();
  node rhs = MakeUndefinedNode();

  ASSERT_TRUE(lhs.is_defined());
  ASSERT_FALSE(rhs.is_defined());

  lhs.set_ref(rhs);

  // Observable contract: set_ref only conditionally calls mark_defined();
  // it does not provide any way to "un-define" a node via the public interface.
  EXPECT_TRUE(lhs.is_defined());
  EXPECT_EQ(lhs.ref(), rhs.ref());
}

TEST_F(NodeSetRefTest_246, SetRefToSelfKeepsReferenceAndDefinedness_246) {
  node n = MakeUndefinedNode();
  const bool wasDefined = n.is_defined();
  const auto* refBefore = n.ref();
  ASSERT_NE(refBefore, nullptr);

  n.set_ref(n);

  EXPECT_EQ(n.ref(), refBefore);
  EXPECT_EQ(n.is_defined(), wasDefined);
}

}  // namespace