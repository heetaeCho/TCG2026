// File: ./TestProjects/yaml-cpp/test/regex_or_operator_test_158.cpp

#include <gtest/gtest.h>

#include "regex_yaml.h"

namespace {

using YAML::RegEx;

TEST(RegExOrOperatorTest_158, MatchesLeftOperandChar_158) {
  const RegEx a('a');
  const RegEx b('b');

  const RegEx ex = a | b;

  EXPECT_TRUE(ex.Matches('a'));
  EXPECT_FALSE(ex.Matches('c'));
}

TEST(RegExOrOperatorTest_158, MatchesRightOperandChar_158) {
  const RegEx a('a');
  const RegEx b('b');

  const RegEx ex = a | b;

  EXPECT_TRUE(ex.Matches('b'));
  EXPECT_FALSE(ex.Matches('c'));
}

TEST(RegExOrOperatorTest_158, DoesNotMatchWhenNeitherOperandMatches_158) {
  const RegEx a('a');
  const RegEx b('b');

  const RegEx ex = a | b;

  EXPECT_FALSE(ex.Matches('z'));
  EXPECT_FALSE(ex.Matches('\0'));
}

TEST(RegExOrOperatorTest_158, WorksWithRangeOperands_158) {
  const RegEx digits('0', '9');
  const RegEx lower('a', 'z');

  const RegEx ex = digits | lower;

  EXPECT_TRUE(ex.Matches('0'));
  EXPECT_TRUE(ex.Matches('7'));
  EXPECT_TRUE(ex.Matches('a'));
  EXPECT_TRUE(ex.Matches('m'));
  EXPECT_FALSE(ex.Matches('A'));
  EXPECT_FALSE(ex.Matches('-'));
}

TEST(RegExOrOperatorTest_158, ChainingOrOperatorsMatchesAnyAlternative_158) {
  const RegEx ex = (RegEx('a') | RegEx('b')) | RegEx('c');

  EXPECT_TRUE(ex.Matches('a'));
  EXPECT_TRUE(ex.Matches('b'));
  EXPECT_TRUE(ex.Matches('c'));
  EXPECT_FALSE(ex.Matches('d'));
}

TEST(RegExOrOperatorTest_158, OrderDoesNotAffectObservableMatches_158) {
  const RegEx a('x');
  const RegEx b('y');

  const RegEx ex1 = a | b;
  const RegEx ex2 = b | a;

  EXPECT_TRUE(ex1.Matches('x'));
  EXPECT_TRUE(ex1.Matches('y'));
  EXPECT_FALSE(ex1.Matches('z'));

  EXPECT_TRUE(ex2.Matches('x'));
  EXPECT_TRUE(ex2.Matches('y'));
  EXPECT_FALSE(ex2.Matches('z'));
}

TEST(RegExOrOperatorTest_158, OriginalOperandsRemainUsableAfterOr_158) {
  const RegEx a('a');
  const RegEx b('b');

  const RegEx ex = a | b;

  // Using originals after composing should remain valid/observable.
  EXPECT_TRUE(a.Matches('a'));
  EXPECT_FALSE(a.Matches('b'));

  EXPECT_TRUE(b.Matches('b'));
  EXPECT_FALSE(b.Matches('a'));

  EXPECT_TRUE(ex.Matches('a'));
  EXPECT_TRUE(ex.Matches('b'));
}

TEST(RegExOrOperatorTest_158, WorksWhenOneSideIsDefaultConstructed_158) {
  const RegEx empty;   // default-constructed
  const RegEx x('x');

  const RegEx ex1 = empty | x;
  const RegEx ex2 = x | empty;

  // Regardless of how "empty" behaves, OR should still match what 'x' matches.
  EXPECT_TRUE(ex1.Matches('x'));
  EXPECT_TRUE(ex2.Matches('x'));
}

TEST(RegExOrOperatorTest_158, DoesNotThrowOnMatchesCalls_158) {
  const RegEx ex = RegEx('a') | RegEx('b');

  EXPECT_NO_THROW((void)ex.Matches('a'));
  EXPECT_NO_THROW((void)ex.Matches('b'));
  EXPECT_NO_THROW((void)ex.Matches('z'));
}

}  // namespace
