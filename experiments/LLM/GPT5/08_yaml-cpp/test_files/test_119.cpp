// TEST_ID: 119
#include <gtest/gtest.h>

#include "TestProjects/yaml-cpp/src/exp.h"
#include "TestProjects/yaml-cpp/src/regex_yaml.h"

namespace {

class BreakExpTest_119 : public ::testing::Test {};

TEST_F(BreakExpTest_119, ReturnsSameInstanceAcrossCalls_119) {
  const YAML::RegEx* a = &YAML::Exp::Break();
  const YAML::RegEx* b = &YAML::Exp::Break();
  EXPECT_EQ(a, b);
}

TEST_F(BreakExpTest_119, MatchesNewlineChar_119) {
  EXPECT_TRUE(YAML::Exp::Break().Matches('\n'));
}

TEST_F(BreakExpTest_119, MatchesCarriageReturnChar_119) {
  EXPECT_TRUE(YAML::Exp::Break().Matches('\r'));
}

TEST_F(BreakExpTest_119, DoesNotMatchOtherCommonChars_119) {
  const auto& br = YAML::Exp::Break();
  EXPECT_FALSE(br.Matches('a'));
  EXPECT_FALSE(br.Matches('Z'));
  EXPECT_FALSE(br.Matches('0'));
  EXPECT_FALSE(br.Matches(' '));
  EXPECT_FALSE(br.Matches('\t'));
}

TEST_F(BreakExpTest_119, MatchesSingleCharStrings_119) {
  const auto& br = YAML::Exp::Break();
  EXPECT_TRUE(br.Matches(std::string("\n")));
  EXPECT_TRUE(br.Matches(std::string("\r")));
}

TEST_F(BreakExpTest_119, MatchesCRLFString_119) {
  EXPECT_TRUE(YAML::Exp::Break().Matches(std::string("\r\n")));
}

TEST_F(BreakExpTest_119, DoesNotMatchEmptyOrNonBreakStrings_119) {
  const auto& br = YAML::Exp::Break();
  EXPECT_FALSE(br.Matches(std::string("")));
  EXPECT_FALSE(br.Matches(std::string("x")));
  EXPECT_FALSE(br.Matches(std::string("x\n")));
  EXPECT_FALSE(br.Matches(std::string("\n\r")));
}

TEST_F(BreakExpTest_119, MatchIsPositiveForBreaksAndNonPositiveOtherwise_119) {
  const auto& br = YAML::Exp::Break();

  EXPECT_GT(br.Match(std::string("\n")), 0);
  EXPECT_GT(br.Match(std::string("\r")), 0);
  EXPECT_GT(br.Match(std::string("\r\n")), 0);

  EXPECT_LE(br.Match(std::string("")), 0);
  EXPECT_LE(br.Match(std::string("x")), 0);
  EXPECT_LE(br.Match(std::string("x\n")), 0);
}

}  // namespace
