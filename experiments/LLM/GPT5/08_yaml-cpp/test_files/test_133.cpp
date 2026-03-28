// File: ./TestProjects/yaml-cpp/test/exp_key_in_flow_test_133.cpp

#include <gtest/gtest.h>

#include "exp.h"          // YAML::Exp::KeyInFlow()
#include "regex_yaml.h"   // YAML::RegEx

namespace {

class KeyInFlowTest_133 : public ::testing::Test {};

TEST_F(KeyInFlowTest_133, ReturnsSameInstanceAcrossCalls_133) {
  const YAML::RegEx* a = &YAML::Exp::KeyInFlow();
  const YAML::RegEx* b = &YAML::Exp::KeyInFlow();
  EXPECT_EQ(a, b);
}

TEST_F(KeyInFlowTest_133, MatchesQuestionFollowedBySpace_133) {
  const YAML::RegEx& ex = YAML::Exp::KeyInFlow();

  EXPECT_TRUE(ex.Matches(std::string("? ")));
  EXPECT_GT(ex.Match(std::string("? ")), 0);
}

TEST_F(KeyInFlowTest_133, MatchesQuestionFollowedByNewline_133) {
  const YAML::RegEx& ex = YAML::Exp::KeyInFlow();

  EXPECT_TRUE(ex.Matches(std::string("?\n")));
  EXPECT_GT(ex.Match(std::string("?\n")), 0);
}

TEST_F(KeyInFlowTest_133, MatchesQuestionFollowedByTab_133) {
  const YAML::RegEx& ex = YAML::Exp::KeyInFlow();

  EXPECT_TRUE(ex.Matches(std::string("?\t")));
  EXPECT_GT(ex.Match(std::string("?\t")), 0);
}

TEST_F(KeyInFlowTest_133, DoesNotMatchWhenSecondCharIsNotBlankOrBreak_133) {
  const YAML::RegEx& ex = YAML::Exp::KeyInFlow();

  EXPECT_FALSE(ex.Matches(std::string("?a")));
  EXPECT_LT(ex.Match(std::string("?a")), 0);

  EXPECT_FALSE(ex.Matches(std::string("??")));
  EXPECT_LT(ex.Match(std::string("??")), 0);
}

TEST_F(KeyInFlowTest_133, DoesNotMatchWithoutLeadingQuestionMark_133) {
  const YAML::RegEx& ex = YAML::Exp::KeyInFlow();

  EXPECT_FALSE(ex.Matches(std::string("")));
  EXPECT_LT(ex.Match(std::string("")), 0);

  EXPECT_FALSE(ex.Matches(std::string(" ")));
  EXPECT_LT(ex.Match(std::string(" ")), 0);

  EXPECT_FALSE(ex.Matches(std::string("a ")));
  EXPECT_LT(ex.Match(std::string("a ")), 0);
}

}  // namespace
