// File: ./TestProjects/yaml-cpp/test/exp_ampersand_test_137.cpp

#include <gtest/gtest.h>

#include "exp.h"         // YAML::Exp::Ampersand
#include "regex_yaml.h"  // YAML::RegEx

namespace {

class ExpAmpersandTest_137 : public ::testing::Test {};

TEST_F(ExpAmpersandTest_137, ReturnsSameInstanceAcrossCalls_137) {
  const YAML::RegEx* first = &YAML::Exp::Ampersand();
  const YAML::RegEx* second = &YAML::Exp::Ampersand();
  const YAML::RegEx* third = &YAML::Exp::Ampersand();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(ExpAmpersandTest_137, MatchesAmpersandCharacter_137) {
  const YAML::RegEx& ex = YAML::Exp::Ampersand();
  EXPECT_TRUE(ex.Matches('&'));
}

TEST_F(ExpAmpersandTest_137, DoesNotMatchDifferentCharacters_137) {
  const YAML::RegEx& ex = YAML::Exp::Ampersand();

  EXPECT_FALSE(ex.Matches('a'));
  EXPECT_FALSE(ex.Matches(' '));
  EXPECT_FALSE(ex.Matches('\n'));
  EXPECT_FALSE(ex.Matches('\t'));
  EXPECT_FALSE(ex.Matches('\0'));  // boundary-ish: NUL char
  EXPECT_FALSE(ex.Matches('#'));
}

TEST_F(ExpAmpersandTest_137, ReturnedReferenceRemainsUsableAfterMultipleCalls_137) {
  const YAML::RegEx* saved = &YAML::Exp::Ampersand();

  // Call again a few times (should not invalidate the saved reference).
  (void)YAML::Exp::Ampersand();
  (void)YAML::Exp::Ampersand();

  EXPECT_TRUE(saved->Matches('&'));
  EXPECT_FALSE(saved->Matches('x'));
}

}  // namespace
