// File: ./TestProjects/yaml-cpp/test/exp_end_scalar_in_flow_test_146.cpp

#include <gtest/gtest.h>

#include "TestProjects/yaml-cpp/src/exp.h"
#include "TestProjects/yaml-cpp/src/regex_yaml.h"

namespace {

class EndScalarInFlowTest_146 : public ::testing::Test {};

TEST_F(EndScalarInFlowTest_146, ReturnsStableReference_146) {
  const YAML::RegEx* a = &YAML::Exp::EndScalarInFlow();
  const YAML::RegEx* b = &YAML::Exp::EndScalarInFlow();
  EXPECT_EQ(a, b);
}

TEST_F(EndScalarInFlowTest_146, MatchesSingleCharacterDelimiters_146) {
  const YAML::RegEx& ex = YAML::Exp::EndScalarInFlow();

  EXPECT_TRUE(ex.Matches(','));  // from ",?[]{}" OR-set
  EXPECT_TRUE(ex.Matches('?'));
  EXPECT_TRUE(ex.Matches('['));
  EXPECT_TRUE(ex.Matches(']'));
  EXPECT_TRUE(ex.Matches('{'));
  EXPECT_TRUE(ex.Matches('}'));
}

TEST_F(EndScalarInFlowTest_146, DoesNotMatchUnrelatedCharacters_146) {
  const YAML::RegEx& ex = YAML::Exp::EndScalarInFlow();

  EXPECT_FALSE(ex.Matches('a'));
  EXPECT_FALSE(ex.Matches('0'));
  EXPECT_FALSE(ex.Matches(';'));
  EXPECT_FALSE(ex.Matches('_'));
}

TEST_F(EndScalarInFlowTest_146, MatchesColonAlone_146) {
  const YAML::RegEx& ex = YAML::Exp::EndScalarInFlow();

  EXPECT_TRUE(ex.Matches(std::string(":")));
}

TEST_F(EndScalarInFlowTest_146, MatchesColonFollowedByFlowTerminators_146) {
  const YAML::RegEx& ex = YAML::Exp::EndScalarInFlow();

  EXPECT_TRUE(ex.Matches(std::string(":,")));
  EXPECT_TRUE(ex.Matches(std::string(":]")));
  EXPECT_TRUE(ex.Matches(std::string(":}")));
}

TEST_F(EndScalarInFlowTest_146, MatchesColonFollowedByBlankOrBreak_146) {
  const YAML::RegEx& ex = YAML::Exp::EndScalarInFlow();

  // We only assert common blank/break examples; this is observable behavior via Matches().
  EXPECT_TRUE(ex.Matches(std::string(": ")));
  EXPECT_TRUE(ex.Matches(std::string(":\n")));
}

TEST_F(EndScalarInFlowTest_146, DoesNotMatchEmptyString_146) {
  const YAML::RegEx& ex = YAML::Exp::EndScalarInFlow();

  EXPECT_FALSE(ex.Matches(std::string("")));
}

TEST_F(EndScalarInFlowTest_146, DoesNotMatchColonFollowedByNonTerminator_146) {
  const YAML::RegEx& ex = YAML::Exp::EndScalarInFlow();

  EXPECT_FALSE(ex.Matches(std::string(":a")));
  EXPECT_FALSE(ex.Matches(std::string("::")));
  EXPECT_FALSE(ex.Matches(std::string(":_")));
}

TEST_F(EndScalarInFlowTest_146, DoesNotMatchMultiCharacterWhenOnlySingleDelimiterExpected_146) {
  const YAML::RegEx& ex = YAML::Exp::EndScalarInFlow();

  // The delimiter alternatives include single characters like ',' ']' '}' etc.
  // If Matches() requires full-string match, repeated delimiters should not match.
  EXPECT_FALSE(ex.Matches(std::string(",,")));
  EXPECT_FALSE(ex.Matches(std::string("[]")));
  EXPECT_FALSE(ex.Matches(std::string("{}")));
}

}  // namespace
