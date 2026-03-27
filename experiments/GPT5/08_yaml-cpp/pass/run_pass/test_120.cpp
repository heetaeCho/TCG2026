// File: ./TestProjects/yaml-cpp/test/exp_blank_or_break_test_120.cpp

#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "exp.h"         // YAML::Exp::BlankOrBreak(), and (expected) Blank(), Break()
#include "regex_yaml.h"  // YAML::RegEx

namespace {

class BlankOrBreakTest_120 : public ::testing::Test {};

TEST_F(BlankOrBreakTest_120, ReturnsSameReferenceOnRepeatedCalls_120) {
  const YAML::RegEx* first = nullptr;
  ASSERT_NO_THROW(first = &YAML::Exp::BlankOrBreak());
  ASSERT_NE(first, nullptr);

  const YAML::RegEx* second = nullptr;
  ASSERT_NO_THROW(second = &YAML::Exp::BlankOrBreak());
  ASSERT_NE(second, nullptr);

  EXPECT_EQ(first, second);
}

TEST_F(BlankOrBreakTest_120, MatchesCharEqualsBlankOrBreakUnion_120) {
  const YAML::RegEx& blank = YAML::Exp::Blank();
  const YAML::RegEx& brk = YAML::Exp::Break();
  const YAML::RegEx& bob = YAML::Exp::BlankOrBreak();

  const std::vector<char> candidates = {
      ' ', '\t', '\n', '\r', '\v', '\f', 'a', '0', '-', '_', '#', '\0',
  };

  for (char ch : candidates) {
    const bool expected = blank.Matches(ch) || brk.Matches(ch);
    EXPECT_EQ(bob.Matches(ch), expected) << "ch int=" << static_cast<int>(ch);
  }
}

TEST_F(BlankOrBreakTest_120, MatchesSingleCharStringEqualsBlankOrBreakUnion_120) {
  const YAML::RegEx& blank = YAML::Exp::Blank();
  const YAML::RegEx& brk = YAML::Exp::Break();
  const YAML::RegEx& bob = YAML::Exp::BlankOrBreak();

  const std::vector<char> candidates = {
      ' ', '\t', '\n', '\r', '\v', '\f', 'a', '0', '-', '\0',
  };

  for (char ch : candidates) {
    const std::string s(1, ch);
    const bool expected = blank.Matches(s) || brk.Matches(s);
    EXPECT_EQ(bob.Matches(s), expected) << "ch int=" << static_cast<int>(ch);
  }
}

TEST_F(BlankOrBreakTest_120, MatchesEmptyStringEqualsBlankOrBreakUnion_120) {
  const YAML::RegEx& blank = YAML::Exp::Blank();
  const YAML::RegEx& brk = YAML::Exp::Break();
  const YAML::RegEx& bob = YAML::Exp::BlankOrBreak();

  const std::string empty;
  EXPECT_EQ(bob.Matches(empty), blank.Matches(empty) || brk.Matches(empty));
}

TEST_F(BlankOrBreakTest_120, DoesNotThrowWhenQueryingMatches_120) {
  const YAML::RegEx& bob = YAML::Exp::BlankOrBreak();

  EXPECT_NO_THROW((void)bob.Matches(' '));
  EXPECT_NO_THROW((void)bob.Matches('\n'));
  EXPECT_NO_THROW((void)bob.Matches('a'));
  EXPECT_NO_THROW((void)bob.Matches(std::string()));
  EXPECT_NO_THROW((void)bob.Matches(std::string("x")));
}

}  // namespace
