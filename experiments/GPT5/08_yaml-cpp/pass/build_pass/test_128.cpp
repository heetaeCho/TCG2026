// File: ./TestProjects/yaml-cpp/test/exp_docstart_test_128.cpp

#include <gtest/gtest.h>

#include <string>

#include "TestProjects/yaml-cpp/src/exp.h"
#include "TestProjects/yaml-cpp/src/regex_yaml.h"

namespace {

using YAML::RegEx;

class ExpDocStartTest_128 : public ::testing::Test {};

TEST_F(ExpDocStartTest_128, ReturnsStableSingletonReference_128) {
  const RegEx* a = &YAML::Exp::DocStart();
  const RegEx* b = &YAML::Exp::DocStart();
  EXPECT_EQ(a, b);
}

TEST_F(ExpDocStartTest_128, MatchesExactMarkerOnly_128) {
  const RegEx& re = YAML::Exp::DocStart();

  EXPECT_TRUE(re.Matches(std::string("---")));
  // If Matches() is implemented as "full string matches", this should be false.
  EXPECT_FALSE(re.Matches(std::string("")));
  EXPECT_FALSE(re.Matches(std::string("--")));
  EXPECT_FALSE(re.Matches(std::string("----")));
}

TEST_F(ExpDocStartTest_128, MatchConsumesMarkerLengthForExactMarker_128) {
  const RegEx& re = YAML::Exp::DocStart();

  const std::string s = "---";
  const int n = re.Match(s);

  // Observable contract we can assert without knowing internal mechanics:
  // successful match should return a non-negative consumption not exceeding input size.
  EXPECT_GE(n, 0);
  EXPECT_LE(static_cast<size_t>(n), s.size());

  // For this specific literal marker, it should consume exactly its length.
  EXPECT_EQ(n, 3);
}

TEST_F(ExpDocStartTest_128, DoesNotFullyMatchWhenNonBlankSuffixPresent_128) {
  const RegEx& re = YAML::Exp::DocStart();

  // DocStart() should not fully match when immediately followed by a non-blank, non-break character.
  EXPECT_FALSE(re.Matches(std::string("---x")));

  // But a prefix match may still exist; Match() should indicate how much was consumed.
  const int n = re.Match(std::string("---x"));
  EXPECT_GE(n, 0);
  EXPECT_LE(n, 4);
  EXPECT_EQ(n, 3);
}

TEST_F(ExpDocStartTest_128, MatchesWhenFollowedByCommonBreak_128) {
  const RegEx& re = YAML::Exp::DocStart();

  EXPECT_TRUE(re.Matches(std::string("---\n")));
  EXPECT_EQ(re.Match(std::string("---\n")), 4);
}

TEST_F(ExpDocStartTest_128, MatchesWhenFollowedByCommonBlank_128) {
  const RegEx& re = YAML::Exp::DocStart();

  EXPECT_TRUE(re.Matches(std::string("--- ")));
  EXPECT_EQ(re.Match(std::string("--- ")), 4);
}

}  // namespace
