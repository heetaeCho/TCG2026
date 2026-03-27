// File: ./TestProjects/yaml-cpp/test/exp_chompindicator_test_151.cpp

#include <gtest/gtest.h>

#include "exp.h"
#include "regex_yaml.h"

namespace {

class ChompIndicatorTest_151 : public ::testing::Test {};

TEST_F(ChompIndicatorTest_151, ReturnsSameInstanceAcrossCalls_151) {
  const YAML::RegEx& r1 = YAML::Exp::ChompIndicator();
  const YAML::RegEx& r2 = YAML::Exp::ChompIndicator();

  // ChompIndicator() returns a reference; verify it is stable across calls.
  EXPECT_EQ(&r1, &r2);
}

TEST_F(ChompIndicatorTest_151, MatchesPlusCharacter_151) {
  const YAML::RegEx& r = YAML::Exp::ChompIndicator();
  EXPECT_TRUE(r.Matches('+'));
}

TEST_F(ChompIndicatorTest_151, MatchesMinusCharacter_151) {
  const YAML::RegEx& r = YAML::Exp::ChompIndicator();
  EXPECT_TRUE(r.Matches('-'));
}

TEST_F(ChompIndicatorTest_151, DoesNotMatchUnrelatedCharacters_151) {
  const YAML::RegEx& r = YAML::Exp::ChompIndicator();

  EXPECT_FALSE(r.Matches('a'));
  EXPECT_FALSE(r.Matches('0'));
  EXPECT_FALSE(r.Matches('_'));
  EXPECT_FALSE(r.Matches(' '));
}

TEST_F(ChompIndicatorTest_151, DoesNotMatchNulCharacter_151) {
  const YAML::RegEx& r = YAML::Exp::ChompIndicator();
  EXPECT_FALSE(r.Matches('\0'));
}

TEST_F(ChompIndicatorTest_151, RepeatedCallsAreUsable_151) {
  // A basic “smoke” test over repeated access to ensure no observable errors.
  for (int i = 0; i < 100; ++i) {
    const YAML::RegEx& r = YAML::Exp::ChompIndicator();
    EXPECT_TRUE(r.Matches('+'));
    EXPECT_TRUE(r.Matches('-'));
    EXPECT_FALSE(r.Matches('x'));
  }
}

}  // namespace
