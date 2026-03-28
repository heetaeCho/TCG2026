// TEST_ID: 184
#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

namespace {

class NodeIteratorNotEqualTest_184 : public ::testing::Test {};

TEST_F(NodeIteratorNotEqualTest_184, EqualIteratorsReturnFalse_184) {
  YAML::Node seq = YAML::Load("[1, 2, 3]");
  auto it1 = seq.begin();
  auto it2 = seq.begin();

  // Sanity: equal iterators should not be "not equal".
  EXPECT_FALSE(it1 != it2);

  // Also verify the observable contract from the provided implementation:
  // operator!= is the logical negation of operator==.
  EXPECT_EQ((it1 != it2), !(it1 == it2));
}

TEST_F(NodeIteratorNotEqualTest_184, DifferentIteratorsReturnTrue_184) {
  YAML::Node seq = YAML::Load("[10, 20]");
  auto it1 = seq.begin();
  auto it2 = seq.begin();
  ++it2;  // advance to a different position

  EXPECT_TRUE(it1 != it2);
  EXPECT_EQ((it1 != it2), !(it1 == it2));
}

TEST_F(NodeIteratorNotEqualTest_184, EmptySequenceBeginEqualsEnd_184) {
  YAML::Node emptySeq = YAML::Load("[]");
  auto b = emptySeq.begin();
  auto e = emptySeq.end();

  EXPECT_FALSE(b != e);
  EXPECT_EQ((b != e), !(b == e));
}

TEST_F(NodeIteratorNotEqualTest_184, MapIteratorNotEqualBehavior_184) {
  YAML::Node m = YAML::Load("{a: 1, b: 2}");
  auto b = m.begin();
  auto e = m.end();

  // Non-empty map: begin and end should be different (observable through iteration API).
  EXPECT_TRUE(b != e);
  EXPECT_EQ((b != e), !(b == e));

  auto b2 = m.begin();
  EXPECT_FALSE(b != b2);
  EXPECT_EQ((b != b2), !(b == b2));

  ++b2;
  // If the map has at least two entries, advancing should yield a different iterator.
  // (The YAML input above does.)
  EXPECT_TRUE(b != b2);
  EXPECT_EQ((b != b2), !(b == b2));
}

TEST_F(NodeIteratorNotEqualTest_184, CrossConstAndNonConstIteratorsAreComparable_184) {
  YAML::Node seq = YAML::Load("[1, 2]");
  const YAML::Node& cseq = seq;

  auto it = seq.begin();
  auto cit = cseq.begin();

  // Same underlying position should compare equal => != false.
  EXPECT_FALSE(it != cit);
  EXPECT_EQ((it != cit), !(it == cit));

  ++it;  // move non-const iterator forward
  EXPECT_TRUE(it != cit);
  EXPECT_EQ((it != cit), !(it == cit));
}

TEST_F(NodeIteratorNotEqualTest_184, IteratorsFromDifferentNodesAreNotEqual_184) {
  YAML::Node s1 = YAML::Load("[1]");
  YAML::Node s2 = YAML::Load("[1]");

  auto it1 = s1.begin();
  auto it2 = s2.begin();

  // Iterators from different containers should not compare equal.
  EXPECT_TRUE(it1 != it2);
  EXPECT_EQ((it1 != it2), !(it1 == it2));
}

TEST_F(NodeIteratorNotEqualTest_184, SelfComparisonIsNeverNotEqual_184) {
  YAML::Node seq = YAML::Load("[42]");
  auto it = seq.begin();

  EXPECT_FALSE(it != it);
  EXPECT_EQ((it != it), !(it == it));
}

}  // namespace