// TEST_ID: 140
// File: ./TestProjects/yaml-cpp/test/anchor_end_test_140.cpp

#include <gtest/gtest.h>

#include "exp.h"         // YAML::Exp::AnchorEnd()
#include "regex_yaml.h"  // YAML::RegEx

namespace {

class AnchorEndTest_140 : public ::testing::Test {
protected:
  static const YAML::RegEx& R() { return YAML::Exp::AnchorEnd(); }
};

TEST_F(AnchorEndTest_140, ReturnsSameInstanceAcrossCalls_140) {
  const YAML::RegEx* p1 = &YAML::Exp::AnchorEnd();
  const YAML::RegEx* p2 = &YAML::Exp::AnchorEnd();
  const YAML::RegEx* p3 = &R();

  EXPECT_EQ(p1, p2);
  EXPECT_EQ(p2, p3);
}

TEST_F(AnchorEndTest_140, MatchesAllExplicitAnchorEndDelimiterChars_140) {
  // From implementation: RegEx("?:,]}%@`", REGEX_OR) | BlankOrBreak()
  const char kExpectedMatches[] = {'?', ':', ',', ']', '}', '%', '@', '`'};

  for (char ch : kExpectedMatches) {
    EXPECT_TRUE(R().Matches(ch)) << "Expected to match delimiter char: '" << ch << "'";
  }
}

TEST_F(AnchorEndTest_140, DoesNotMatchSomeCommonNonDelimiterChars_140) {
  // These are not listed in the explicit delimiter set. We avoid guessing
  // BlankOrBreak() behavior by using clearly non-blank, non-break characters.
  const char kExpectedNonMatches[] = {'a', 'Z', '0', '_', '{', '[', '#', '+'};

  for (char ch : kExpectedNonMatches) {
    EXPECT_FALSE(R().Matches(ch)) << "Expected NOT to match char: '" << ch << "'";
  }
}

TEST_F(AnchorEndTest_140, MatchesQueryIsDeterministicForSameInput_140) {
  // Basic stability check: calling Matches repeatedly should be consistent.
  const char inputs[] = {'?', 'a', '0', ']', '_'};

  for (char ch : inputs) {
    const bool first = R().Matches(ch);
    for (int i = 0; i < 5; ++i) {
      EXPECT_EQ(first, R().Matches(ch)) << "Inconsistent Matches result for char: '" << ch << "'";
    }
  }
}

}  // namespace
