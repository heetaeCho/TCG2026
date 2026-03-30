// TEST_ID: 135
#include <gtest/gtest.h>

#include "exp.h"          // YAML::Exp::ValueInFlow
#include "regex_yaml.h"   // YAML::RegEx

namespace {

class ValueInFlowTest_135 : public ::testing::Test {
 protected:
  static const YAML::RegEx& Re() { return YAML::Exp::ValueInFlow(); }
};

TEST_F(ValueInFlowTest_135, ReturnsStableReference_135) {
  const YAML::RegEx* p1 = &YAML::Exp::ValueInFlow();
  const YAML::RegEx* p2 = &YAML::Exp::ValueInFlow();
  EXPECT_EQ(p1, p2);
}

TEST_F(ValueInFlowTest_135, MatchesColonFollowedBySpace_135) {
  EXPECT_TRUE(Re().Matches(std::string(": ")));
}

TEST_F(ValueInFlowTest_135, MatchesColonFollowedByLineBreak_135) {
  EXPECT_TRUE(Re().Matches(std::string(":\n")));
}

TEST_F(ValueInFlowTest_135, MatchesColonFollowedByComma_135) {
  EXPECT_TRUE(Re().Matches(std::string(":,")));
}

TEST_F(ValueInFlowTest_135, MatchesColonFollowedByRightBracket_135) {
  EXPECT_TRUE(Re().Matches(std::string(":]")));
}

TEST_F(ValueInFlowTest_135, MatchesColonFollowedByRightBrace_135) {
  EXPECT_TRUE(Re().Matches(std::string(":}")));
}

TEST_F(ValueInFlowTest_135, DoesNotMatchEmptyString_135) {
  EXPECT_FALSE(Re().Matches(std::string("")));
}

TEST_F(ValueInFlowTest_135, DoesNotMatchColonAlone_135) {
  EXPECT_FALSE(Re().Matches(std::string(":")));
}

TEST_F(ValueInFlowTest_135, DoesNotMatchWithoutLeadingColon_135) {
  EXPECT_FALSE(Re().Matches(std::string(" ,")));
  EXPECT_FALSE(Re().Matches(std::string("] ")));
  EXPECT_FALSE(Re().Matches(std::string("} ")));
}

TEST_F(ValueInFlowTest_135, DoesNotMatchColonFollowedByNonAllowedCharacter_135) {
  EXPECT_FALSE(Re().Matches(std::string(":a")));
  EXPECT_FALSE(Re().Matches(std::string(":0")));
  EXPECT_FALSE(Re().Matches(std::string("::")));
}

TEST_F(ValueInFlowTest_135, DoesNotMatchLongerStringsWhenEntireStringMustMatch_135) {
  // If Matches() is defined as a full-string match (typical), these should fail.
  // If the implementation treats Matches() differently, these expectations may
  // need adjustment to use Match() instead.
  EXPECT_FALSE(Re().Matches(std::string(": a")));
  EXPECT_FALSE(Re().Matches(std::string(":,\n")));
}

}  // namespace
