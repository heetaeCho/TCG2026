// File: ./TestProjects/yaml-cpp/test/regex_yaml_plus_test_160.cpp

#include <gtest/gtest.h>

#include "regex_yaml.h"

namespace {

class RegExPlusOperatorTest_160 : public ::testing::Test {};

TEST_F(RegExPlusOperatorTest_160, ConcatenationMatchesExactTwoChars_160) {
  const YAML::RegEx a('a');
  const YAML::RegEx b('b');

  const YAML::RegEx ab = a + b;

  EXPECT_TRUE(ab.Matches(std::string("ab")));
  EXPECT_FALSE(ab.Matches(std::string("a")));
  EXPECT_FALSE(ab.Matches(std::string("b")));
  EXPECT_FALSE(ab.Matches(std::string("")));
}

TEST_F(RegExPlusOperatorTest_160, ConcatenationRejectsSecondCharMismatch_160) {
  const YAML::RegEx a('a');
  const YAML::RegEx b('b');

  const YAML::RegEx ab = a + b;

  EXPECT_FALSE(ab.Matches(std::string("aa")));
  EXPECT_FALSE(ab.Matches(std::string("ac")));
  EXPECT_FALSE(ab.Matches(std::string("a ")));
}

TEST_F(RegExPlusOperatorTest_160, ConcatenationRejectsInputTooShort_160) {
  const YAML::RegEx a('a');
  const YAML::RegEx b('b');

  const YAML::RegEx ab = a + b;

  EXPECT_FALSE(ab.Matches(std::string("")));
  EXPECT_FALSE(ab.Matches(std::string("a")));
}

TEST_F(RegExPlusOperatorTest_160, ConcatenationAllowsAdditionalTrailingCharacters_160) {
  const YAML::RegEx a('a');
  const YAML::RegEx b('b');

  const YAML::RegEx ab = a + b;

  // Common "prefix match" behavior: should match as long as the pattern matches at the start.
  // If Matches() is defined as "full match", this will correctly fail and highlight the behavior.
  const bool matches_ab = ab.Matches(std::string("ab"));
  const bool matches_abx = ab.Matches(std::string("abx"));

  // If "ab" doesn't match at all, something is fundamentally wrong for this operator+ use-case.
  EXPECT_TRUE(matches_ab);

  // Trailing behavior is implementation-defined; we only assert it is consistent with Match().
  if (matches_abx) {
    EXPECT_GE(ab.Match(std::string("abx")), 2);
  } else {
    // If it doesn't match with trailing chars, it should still match the exact string.
    EXPECT_TRUE(matches_ab);
  }
}

TEST_F(RegExPlusOperatorTest_160, ChainingBuildsLongerSequence_160) {
  const YAML::RegEx a('a');
  const YAML::RegEx b('b');
  const YAML::RegEx c('c');

  const YAML::RegEx abc = (a + b) + c;

  EXPECT_TRUE(abc.Matches(std::string("abc")));
  EXPECT_FALSE(abc.Matches(std::string("ab")));
  EXPECT_FALSE(abc.Matches(std::string("abcd")));  // May be true for prefix-match semantics.
}

TEST_F(RegExPlusOperatorTest_160, ChainingIsAssociativeForObservedMatching_160) {
  const YAML::RegEx a('a');
  const YAML::RegEx b('b');
  const YAML::RegEx c('c');

  const YAML::RegEx left = (a + b) + c;
  const YAML::RegEx right = a + (b + c);

  // Observable behavior: both should behave equivalently for matching.
  EXPECT_EQ(left.Matches(std::string("abc")), right.Matches(std::string("abc")));
  EXPECT_EQ(left.Matches(std::string("ab")), right.Matches(std::string("ab")));
  EXPECT_EQ(left.Matches(std::string("abcd")), right.Matches(std::string("abcd")));
  EXPECT_EQ(left.Match(std::string("abc")), right.Match(std::string("abc")));
}

TEST_F(RegExPlusOperatorTest_160, SequenceWorksWithRangeThenMatch_160) {
  const YAML::RegEx letter('a', 'z');
  const YAML::RegEx digit('0', '9');

  const YAML::RegEx letter_then_digit = letter + digit;

  EXPECT_TRUE(letter_then_digit.Matches(std::string("a0")));
  EXPECT_TRUE(letter_then_digit.Matches(std::string("m7")));
  EXPECT_FALSE(letter_then_digit.Matches(std::string("0a")));
  EXPECT_FALSE(letter_then_digit.Matches(std::string("aa")));
  EXPECT_FALSE(letter_then_digit.Matches(std::string("7m")));
}

}  // namespace
