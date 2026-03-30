// File: ./TestProjects/yaml-cpp/test/exp_alphanumeric_test_123.cpp

#include <gtest/gtest.h>

#include "exp.h"          // YAML::Exp::AlphaNumeric()
#include "regex_yaml.h"   // YAML::RegEx

namespace {

class AlphaNumericExpTest_123 : public ::testing::Test {};

TEST_F(AlphaNumericExpTest_123, ReturnsSameInstanceAcrossCalls_123) {
  const YAML::RegEx* p1 = &YAML::Exp::AlphaNumeric();
  const YAML::RegEx* p2 = &YAML::Exp::AlphaNumeric();
  const YAML::RegEx* p3 = &YAML::Exp::AlphaNumeric();

  EXPECT_EQ(p1, p2);
  EXPECT_EQ(p2, p3);
}

TEST_F(AlphaNumericExpTest_123, MatchesLettersAndDigits_123) {
  const YAML::RegEx& ex = YAML::Exp::AlphaNumeric();

  // Representative letters
  EXPECT_TRUE(ex.Matches('a'));
  EXPECT_TRUE(ex.Matches('z'));
  EXPECT_TRUE(ex.Matches('A'));
  EXPECT_TRUE(ex.Matches('Z'));

  // Representative digits
  EXPECT_TRUE(ex.Matches('0'));
  EXPECT_TRUE(ex.Matches('5'));
  EXPECT_TRUE(ex.Matches('9'));
}

TEST_F(AlphaNumericExpTest_123, DoesNotMatchNonAlphanumericCharacters_123) {
  const YAML::RegEx& ex = YAML::Exp::AlphaNumeric();

  // Common non-alphanumeric characters
  EXPECT_FALSE(ex.Matches('_'));
  EXPECT_FALSE(ex.Matches('-'));
  EXPECT_FALSE(ex.Matches(' '));
  EXPECT_FALSE(ex.Matches('\n'));
  EXPECT_FALSE(ex.Matches('.'));
  EXPECT_FALSE(ex.Matches('/'));
}

TEST_F(AlphaNumericExpTest_123, MatchesSingleCharacterStrings_123) {
  const YAML::RegEx& ex = YAML::Exp::AlphaNumeric();

  EXPECT_TRUE(ex.Matches(std::string("a")));
  EXPECT_TRUE(ex.Matches(std::string("Z")));
  EXPECT_TRUE(ex.Matches(std::string("0")));
  EXPECT_TRUE(ex.Matches(std::string("9")));

  EXPECT_FALSE(ex.Matches(std::string("_")));
  EXPECT_FALSE(ex.Matches(std::string(" ")));
}

TEST_F(AlphaNumericExpTest_123, RejectsEmptyString_123) {
  const YAML::RegEx& ex = YAML::Exp::AlphaNumeric();
  EXPECT_FALSE(ex.Matches(std::string("")));
}

}  // namespace
