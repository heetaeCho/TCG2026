// File: ./TestProjects/yaml-cpp/test/exp_digit_test_121.cpp

#include <gtest/gtest.h>

#include "exp.h"  // YAML::Exp::Digit()
#include "regex_yaml.h"

namespace {

class DigitExpTest_121 : public ::testing::Test {};

TEST_F(DigitExpTest_121, ReturnsSameInstanceAcrossCalls_121) {
  const YAML::RegEx* first = &YAML::Exp::Digit();
  const YAML::RegEx* second = &YAML::Exp::Digit();
  const YAML::RegEx* third = &YAML::Exp::Digit();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(DigitExpTest_121, MatchesAllAsciiDigits_121) {
  const YAML::RegEx& digit = YAML::Exp::Digit();

  for (char ch = '0'; ch <= '9'; ++ch) {
    EXPECT_TRUE(digit.Matches(ch)) << "Expected to match digit: " << ch;
  }
}

TEST_F(DigitExpTest_121, DoesNotMatchCharactersJustOutsideRange_121) {
  const YAML::RegEx& digit = YAML::Exp::Digit();

  EXPECT_FALSE(digit.Matches('/'));  // just before '0'
  EXPECT_FALSE(digit.Matches(':'));  // just after '9'
}

TEST_F(DigitExpTest_121, DoesNotMatchSomeCommonNonDigits_121) {
  const YAML::RegEx& digit = YAML::Exp::Digit();

  EXPECT_FALSE(digit.Matches('a'));
  EXPECT_FALSE(digit.Matches('Z'));
  EXPECT_FALSE(digit.Matches(' '));
  EXPECT_FALSE(digit.Matches('-'));
  EXPECT_FALSE(digit.Matches('_'));
}

TEST_F(DigitExpTest_121, ReferenceRemainsUsableAfterSubsequentCalls_121) {
  const YAML::RegEx& first_ref = YAML::Exp::Digit();
  (void)YAML::Exp::Digit();  // call again; should not invalidate the reference

  EXPECT_TRUE(first_ref.Matches('0'));
  EXPECT_TRUE(first_ref.Matches('9'));
  EXPECT_FALSE(first_ref.Matches('x'));
}

}  // namespace
