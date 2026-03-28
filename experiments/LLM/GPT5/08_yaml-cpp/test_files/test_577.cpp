// TEST_ID: 577
#include <gtest/gtest.h>

#include <yaml-cpp/yaml.h>

namespace {

class OperatorEqualTest_577 : public ::testing::Test {
protected:
  // Create nodes through the public API without assuming internal semantics.
  static YAML::Node Load(const std::string& text) { return YAML::Load(text); }
};

TEST_F(OperatorEqualTest_577, ReflexiveEqualsMatchesIs_577) {
  YAML::Node n;  // default-constructed node
  EXPECT_EQ((n == n), n.is(n));
}

TEST_F(OperatorEqualTest_577, CopyConstructedNodeEqualsMatchesIs_577) {
  YAML::Node a = Load("key: value");
  YAML::Node b(a);  // copy construction

  // operator== is specified to delegate to lhs.is(rhs)
  EXPECT_EQ((a == b), a.is(b));
  EXPECT_EQ((b == a), b.is(a));
}

TEST_F(OperatorEqualTest_577, AssignedNodeEqualsMatchesIs_577) {
  YAML::Node a = Load("[1, 2, 3]");
  YAML::Node b;
  b = a;  // assignment

  EXPECT_EQ((a == b), a.is(b));
  EXPECT_EQ((b == a), b.is(a));
}

TEST_F(OperatorEqualTest_577, DistinctButSimilarContentNodesEqualsMatchesIs_577) {
  // These nodes may have similar content, but we do NOT assume semantic equality.
  // We only verify delegation to Node::is().
  YAML::Node a = Load("a");
  YAML::Node b = Load("a");

  EXPECT_EQ((a == b), a.is(b));
  EXPECT_EQ((b == a), b.is(a));
}

TEST_F(OperatorEqualTest_577, DifferentKindsOfNodesEqualsMatchesIs_577) {
  YAML::Node scalar = Load("hello");
  YAML::Node seq = Load("[hello]");
  YAML::Node map = Load("{hello: world}");

  EXPECT_EQ((scalar == seq), scalar.is(seq));
  EXPECT_EQ((scalar == map), scalar.is(map));
  EXPECT_EQ((seq == map), seq.is(map));

  EXPECT_EQ((seq == scalar), seq.is(scalar));
  EXPECT_EQ((map == scalar), map.is(scalar));
  EXPECT_EQ((map == seq), map.is(seq));
}

TEST_F(OperatorEqualTest_577, ComparingWithSelfAfterMutationEqualsMatchesIs_577) {
  YAML::Node n = Load("[1, 2]");
  // Mutate through the public API (doesn't matter what it does internally).
  n.push_back(3);

  EXPECT_EQ((n == n), n.is(n));
}

}  // namespace