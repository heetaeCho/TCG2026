// File: ./TestProjects/yaml-cpp/test/exp_space_test_116.cpp

#include <gtest/gtest.h>

#include "TestProjects/yaml-cpp/src/exp.h"
#include "TestProjects/yaml-cpp/src/regex_yaml.h"

namespace {

using YAML::RegEx;

class SpaceExpTest_116 : public ::testing::Test {
 protected:
  const RegEx& Space() { return YAML::Exp::Space(); }
};

TEST_F(SpaceExpTest_116, ReturnsSameInstanceAcrossCalls_116) {
  const RegEx* a = &Space();
  const RegEx* b = &Space();
  EXPECT_EQ(a, b);
}

TEST_F(SpaceExpTest_116, MatchesSingleSpaceCharacter_116) {
  EXPECT_TRUE(Space().Matches(' '));
}

TEST_F(SpaceExpTest_116, DoesNotMatchCommonNonSpaceCharacters_116) {
  EXPECT_FALSE(Space().Matches('a'));
  EXPECT_FALSE(Space().Matches('\t'));
  EXPECT_FALSE(Space().Matches('\n'));
  EXPECT_FALSE(Space().Matches('\r'));
  EXPECT_FALSE(Space().Matches('\0'));
}

TEST_F(SpaceExpTest_116, MatchesSingleSpaceString_116) {
  EXPECT_TRUE(Space().Matches(std::string(" ")));
}

TEST_F(SpaceExpTest_116, MatchConsumesOneSpaceAtBeginningOfString_116) {
  EXPECT_EQ(Space().Match(std::string(" ")), 1);
  EXPECT_EQ(Space().Match(std::string("  ")), 1);
  EXPECT_EQ(Space().Match(std::string(" a")), 1);
}

TEST_F(SpaceExpTest_116, MatchFailsWhenStringDoesNotStartWithSpace_116) {
  EXPECT_EQ(Space().Match(std::string("")), -1);
  EXPECT_EQ(Space().Match(std::string("a")), -1);
  EXPECT_EQ(Space().Match(std::string("a ")), -1);
}

}  // namespace
