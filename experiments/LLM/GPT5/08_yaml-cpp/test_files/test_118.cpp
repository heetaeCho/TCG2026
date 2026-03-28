// TEST_ID: 118
#include <gtest/gtest.h>

#include "exp.h"  // YAML::Exp::Blank()

namespace {

class BlankExpTest_118 : public ::testing::Test {};

TEST_F(BlankExpTest_118, ReturnsSameReferenceAcrossCalls_118) {
  const YAML::RegEx& a = YAML::Exp::Blank();
  const YAML::RegEx& b = YAML::Exp::Blank();
  EXPECT_EQ(&a, &b) << "Blank() should return a stable reference (singleton-like).";
}

TEST_F(BlankExpTest_118, MatchesSpaceCharacter_118) {
  const YAML::RegEx& blank = YAML::Exp::Blank();
  EXPECT_TRUE(blank.Matches(' '));
}

TEST_F(BlankExpTest_118, MatchesTabCharacter_118) {
  const YAML::RegEx& blank = YAML::Exp::Blank();
  EXPECT_TRUE(blank.Matches('\t'));
}

TEST_F(BlankExpTest_118, DoesNotMatchNewlineCharacter_118) {
  const YAML::RegEx& blank = YAML::Exp::Blank();
  EXPECT_FALSE(blank.Matches('\n'));
}

TEST_F(BlankExpTest_118, DoesNotMatchRegularLetterCharacter_118) {
  const YAML::RegEx& blank = YAML::Exp::Blank();
  EXPECT_FALSE(blank.Matches('a'));
  EXPECT_FALSE(blank.Matches('Z'));
}

TEST_F(BlankExpTest_118, DoesNotMatchNullCharacter_118) {
  const YAML::RegEx& blank = YAML::Exp::Blank();
  EXPECT_FALSE(blank.Matches('\0'));
}

}  // namespace
