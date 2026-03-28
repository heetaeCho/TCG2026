// TEST_ID: 157
#include <gtest/gtest.h>

#include "regex_yaml.h"

namespace {

using YAML::RegEx;

TEST(RegExNotOperatorTest_157, NegatesSingleCharacterMatch_157) {
  const RegEx a('a');
  const RegEx not_a = !a;

  EXPECT_TRUE(a.Matches('a'));
  EXPECT_FALSE(a.Matches('b'));

  EXPECT_FALSE(not_a.Matches('a'));
  EXPECT_TRUE(not_a.Matches('b'));
}

TEST(RegExNotOperatorTest_157, DoesNotMutateOriginalRegex_157) {
  RegEx a('a');

  const RegEx not_a = !a;

  // Original should behave the same after applying operator!
  EXPECT_TRUE(a.Matches('a'));
  EXPECT_FALSE(a.Matches('b'));

  // And the negated one should be inverted (observable behavior).
  EXPECT_FALSE(not_a.Matches('a'));
  EXPECT_TRUE(not_a.Matches('b'));
}

TEST(RegExNotOperatorTest_157, DoubleNegationBehavesLikeOriginal_157) {
  const RegEx a('a');
  const RegEx not_not_a = !!a;

  EXPECT_TRUE(a.Matches('a'));
  EXPECT_FALSE(a.Matches('b'));

  EXPECT_TRUE(not_not_a.Matches('a'));
  EXPECT_FALSE(not_not_a.Matches('b'));
}

TEST(RegExNotOperatorTest_157, NegatesOrComposition_157) {
  const RegEx a('a');
  const RegEx b('b');

  const RegEx a_or_b = (a | b);
  const RegEx not_a_or_b = !(a_or_b);

  EXPECT_TRUE(a_or_b.Matches('a'));
  EXPECT_TRUE(a_or_b.Matches('b'));
  EXPECT_FALSE(a_or_b.Matches('c'));

  EXPECT_FALSE(not_a_or_b.Matches('a'));
  EXPECT_FALSE(not_a_or_b.Matches('b'));
  EXPECT_TRUE(not_a_or_b.Matches('c'));
}

TEST(RegExNotOperatorTest_157, WorksWithRangeRegex_157) {
  const RegEx a_to_c('a', 'c');
  const RegEx not_a_to_c = !a_to_c;

  EXPECT_TRUE(a_to_c.Matches('a'));
  EXPECT_TRUE(a_to_c.Matches('b'));
  EXPECT_TRUE(a_to_c.Matches('c'));
  EXPECT_FALSE(a_to_c.Matches('d'));

  EXPECT_FALSE(not_a_to_c.Matches('a'));
  EXPECT_FALSE(not_a_to_c.Matches('b'));
  EXPECT_FALSE(not_a_to_c.Matches('c'));
  EXPECT_TRUE(not_a_to_c.Matches('d'));
}

}  // namespace
