// TEST_ID: 202
#include <gtest/gtest.h>

#include <yaml-cpp/yaml.h>

namespace {

class IteratorBaseNotEqualTest_202 : public ::testing::Test {};

TEST_F(IteratorBaseNotEqualTest_202, SelfComparisonIsFalse_202) {
  YAML::Node seq;
  seq.push_back(1);
  auto it = seq.begin();

  // Any iterator should not be "not equal" to itself.
  EXPECT_FALSE(it != it);
}

TEST_F(IteratorBaseNotEqualTest_202, NonEmptySequenceBeginNotEqualEnd_202) {
  YAML::Node seq;
  seq.push_back(1);

  auto b = seq.begin();
  auto e = seq.end();

  // For a non-empty container, begin and end should be different.
  EXPECT_TRUE(b != e);
}

TEST_F(IteratorBaseNotEqualTest_202, EmptySequenceBeginEqualsEndSoNotEqualIsFalse_202) {
  YAML::Node seq(YAML::NodeType::Sequence);

  auto b = seq.begin();
  auto e = seq.end();

  // For an empty container, begin and end should compare as equal => operator!= is false.
  EXPECT_FALSE(b != e);
  EXPECT_FALSE(e != b);
}

TEST_F(IteratorBaseNotEqualTest_202, IncrementReachesEndSoNotEqualBecomesFalse_202) {
  YAML::Node seq;
  seq.push_back(1);

  auto it = seq.begin();
  auto e = seq.end();

  ASSERT_TRUE(it != e);

  ++it;

  // After consuming the only element, iterator should reach end.
  EXPECT_FALSE(it != e);
  EXPECT_FALSE(e != it);
}

TEST_F(IteratorBaseNotEqualTest_202, ConstAndNonConstIteratorsCompareAcrossTypes_202) {
  YAML::Node seq;
  seq.push_back(1);
  seq.push_back(2);

  YAML::iterator it = seq.begin();
  YAML::const_iterator cit = seq.begin();
  YAML::const_iterator cend = seq.end();

  // Same position across iterator types should not be "not equal".
  EXPECT_FALSE(it != cit);
  EXPECT_FALSE(cit != it);

  // Different positions should be "not equal".
  YAML::iterator it2 = seq.begin();
  ++it2;
  EXPECT_TRUE(it2 != cit);
  EXPECT_TRUE(cit != it2);

  // Begin and end should be different for non-empty sequence, including const iterator.
  EXPECT_TRUE(cit != cend);
  EXPECT_TRUE(seq.begin() != seq.end());
}

TEST_F(IteratorBaseNotEqualTest_202, NonEmptyMapBeginNotEqualEnd_202) {
  YAML::Node m(YAML::NodeType::Map);
  m["a"] = 1;

  auto b = m.begin();
  auto e = m.end();

  EXPECT_TRUE(b != e);
}

TEST_F(IteratorBaseNotEqualTest_202, EmptyMapBeginEqualsEndSoNotEqualIsFalse_202) {
  YAML::Node m(YAML::NodeType::Map);

  auto b = m.begin();
  auto e = m.end();

  EXPECT_FALSE(b != e);
  EXPECT_FALSE(e != b);
}

}  // namespace