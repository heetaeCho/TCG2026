// TEST_ID: 565
#include <gtest/gtest.h>

#include <string>
#include <utility>

#include <yaml-cpp/yaml.h>

namespace {

class NodeResetTest_565 : public ::testing::Test {
protected:
  // Best-effort way (using only public API) to obtain a node that is observably invalid.
  // In yaml-cpp, subscripting a scalar node is expected to produce an invalid "Zombie" node,
  // which throws YAML::InvalidNode when most operations are attempted.
  static YAML::Node MakeObservablyInvalidNode() {
    YAML::Node scalar("scalar-value");
    YAML::Node maybeInvalid = scalar["someKey"];
    return maybeInvalid;
  }

  static bool ThrowsInvalidNodeOnType(const YAML::Node& n) {
    try {
      (void)n.Type();
      return false;
    } catch (const YAML::InvalidNode&) {
      return true;
    }
  }
};

TEST_F(NodeResetTest_565, ResetWithValidRhsMakesNodesIdenticalByIs_565) {
  YAML::Node rhs("hello");
  YAML::Node lhs("world");

  // Precondition sanity (observable, no private state)
  EXPECT_FALSE(lhs.is(rhs));

  EXPECT_NO_THROW(lhs.reset(rhs));

  // Observable behavior: lhs should now refer to the same underlying node as rhs.
  EXPECT_TRUE(lhs.is(rhs));

  // And observable data should match rhs after reset.
  EXPECT_EQ(lhs.Scalar(), rhs.Scalar());
  EXPECT_EQ(lhs.Type(), rhs.Type());
}

TEST_F(NodeResetTest_565, ResetOnSelfDoesNotThrowAndStillIsSelf_565) {
  YAML::Node n("self");

  EXPECT_NO_THROW(n.reset(n));
  EXPECT_TRUE(n.is(n));
  EXPECT_EQ(n.Scalar(), "self");
}

TEST_F(NodeResetTest_565, ResetCopiesNonScalarTypesToo_565) {
  YAML::Node rhs(YAML::NodeType::Sequence);
  rhs.push_back(1);
  rhs.push_back(2);

  YAML::Node lhs(YAML::NodeType::Map);
  lhs["k"] = "v";

  EXPECT_FALSE(lhs.is(rhs));

  EXPECT_NO_THROW(lhs.reset(rhs));

  EXPECT_TRUE(lhs.is(rhs));
  EXPECT_EQ(lhs.Type(), rhs.Type());
  EXPECT_EQ(lhs.size(), rhs.size());
  EXPECT_EQ(lhs[0].as<int>(), 1);
  EXPECT_EQ(lhs[1].as<int>(), 2);
}

TEST_F(NodeResetTest_565, ResetThrowsWhenRhsIsInvalidNode_565) {
  YAML::Node rhsInvalid = MakeObservablyInvalidNode();

  // Confirm (via public API) that this node is actually invalid in this build.
  ASSERT_TRUE(ThrowsInvalidNodeOnType(rhsInvalid))
      << "Test precondition failed: could not create an observably invalid YAML::Node via public API.";

  YAML::Node lhs("valid");

  EXPECT_THROW(lhs.reset(rhsInvalid), YAML::InvalidNode);
}

TEST_F(NodeResetTest_565, ResetThrowsWhenLhsIsInvalidNode_565) {
  YAML::Node lhsInvalid = MakeObservablyInvalidNode();

  // Confirm (via public API) that this node is actually invalid in this build.
  ASSERT_TRUE(ThrowsInvalidNodeOnType(lhsInvalid))
      << "Test precondition failed: could not create an observably invalid YAML::Node via public API.";

  YAML::Node rhs("valid");

  EXPECT_THROW(lhsInvalid.reset(rhs), YAML::InvalidNode);
}

TEST_F(NodeResetTest_565, ResetThrowsWhenEitherSideInvalidEvenIfOtherLooksFine_565) {
  YAML::Node invalidA = MakeObservablyInvalidNode();
  YAML::Node invalidB = MakeObservablyInvalidNode();

  ASSERT_TRUE(ThrowsInvalidNodeOnType(invalidA));
  ASSERT_TRUE(ThrowsInvalidNodeOnType(invalidB));

  EXPECT_THROW(invalidA.reset(invalidB), YAML::InvalidNode);
}

}  // namespace