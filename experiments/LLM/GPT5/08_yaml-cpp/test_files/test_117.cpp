// File: ./TestProjects/yaml-cpp/test/exp_tab_test_117.cpp

#include <gtest/gtest.h>

#include "exp.h"
#include "regex_yaml.h"

namespace {

class ExpTabTest_117 : public ::testing::Test {};

TEST_F(ExpTabTest_117, ReturnsSameInstanceEveryCall_117) {
  const YAML::RegEx* first = &YAML::Exp::Tab();
  const YAML::RegEx* second = &YAML::Exp::Tab();
  const YAML::RegEx* third = &YAML::Exp::Tab();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(ExpTabTest_117, MatchesTabCharacter_117) {
  const YAML::RegEx& tab = YAML::Exp::Tab();

  EXPECT_TRUE(tab.Matches('\t'));
  EXPECT_TRUE(tab.Matches(std::string("\t")));
}

TEST_F(ExpTabTest_117, DoesNotMatchCommonNonTabCharacters_117) {
  const YAML::RegEx& tab = YAML::Exp::Tab();

  EXPECT_FALSE(tab.Matches(' '));
  EXPECT_FALSE(tab.Matches('\n'));
  EXPECT_FALSE(tab.Matches('\r'));
  EXPECT_FALSE(tab.Matches('\v'));
  EXPECT_FALSE(tab.Matches('\f'));
  EXPECT_FALSE(tab.Matches('a'));
  EXPECT_FALSE(tab.Matches('0'));
}

TEST_F(ExpTabTest_117, DoesNotMatchNonTabStrings_117) {
  const YAML::RegEx& tab = YAML::Exp::Tab();

  EXPECT_FALSE(tab.Matches(std::string("")));
  EXPECT_FALSE(tab.Matches(std::string(" ")));
  EXPECT_FALSE(tab.Matches(std::string("\n")));
  EXPECT_FALSE(tab.Matches(std::string("abc")));
  EXPECT_FALSE(tab.Matches(std::string(" \t")));   // not exactly tab-only
  EXPECT_FALSE(tab.Matches(std::string("\t ")));   // not exactly tab-only
  EXPECT_FALSE(tab.Matches(std::string("\t\t")));  // multiple characters
}

TEST_F(ExpTabTest_117, MultipleReferencesPointToSameUnderlyingObject_117) {
  const YAML::RegEx& r1 = YAML::Exp::Tab();
  const YAML::RegEx& r2 = YAML::Exp::Tab();

  EXPECT_EQ(&r1, &r2);

  // Sanity: behavior consistent across references
  EXPECT_TRUE(r1.Matches('\t'));
  EXPECT_TRUE(r2.Matches('\t'));
  EXPECT_FALSE(r1.Matches(' '));
  EXPECT_FALSE(r2.Matches(' '));
}

}  // namespace
