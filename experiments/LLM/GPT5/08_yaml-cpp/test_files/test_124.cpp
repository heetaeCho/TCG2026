// File: ./TestProjects/yaml-cpp/test/exp_word_test_124.cpp

#include <gtest/gtest.h>

#include "exp.h"  // YAML::Exp::Word()

namespace {

class WordTest_124 : public ::testing::Test {};

TEST_F(WordTest_124, ReturnsSameInstanceAcrossCalls_124) {
  const YAML::RegEx* a = &YAML::Exp::Word();
  const YAML::RegEx* b = &YAML::Exp::Word();
  EXPECT_EQ(a, b);
}

TEST_F(WordTest_124, MatchesLettersDigitsAndHyphen_124) {
  const YAML::RegEx& word = YAML::Exp::Word();

  EXPECT_TRUE(word.Matches('a'));
  EXPECT_TRUE(word.Matches('z'));
  EXPECT_TRUE(word.Matches('A'));
  EXPECT_TRUE(word.Matches('Z'));

  EXPECT_TRUE(word.Matches('0'));
  EXPECT_TRUE(word.Matches('9'));

  EXPECT_TRUE(word.Matches('-'));
}

TEST_F(WordTest_124, DoesNotMatchCommonNonWordCharacters_124) {
  const YAML::RegEx& word = YAML::Exp::Word();

  EXPECT_FALSE(word.Matches('_'));
  EXPECT_FALSE(word.Matches(' '));
  EXPECT_FALSE(word.Matches('\n'));
  EXPECT_FALSE(word.Matches('\t'));
  EXPECT_FALSE(word.Matches('.'));
  EXPECT_FALSE(word.Matches('/'));
  EXPECT_FALSE(word.Matches('@'));
}

TEST_F(WordTest_124, MatchesSingleCharacterStrings_124) {
  const YAML::RegEx& word = YAML::Exp::Word();

  EXPECT_TRUE(word.Matches(std::string("a")));
  EXPECT_TRUE(word.Matches(std::string("Z")));
  EXPECT_TRUE(word.Matches(std::string("0")));
  EXPECT_TRUE(word.Matches(std::string("-")));

  EXPECT_FALSE(word.Matches(std::string("_")));
  EXPECT_FALSE(word.Matches(std::string(" ")));
  EXPECT_FALSE(word.Matches(std::string(".")));
}

TEST_F(WordTest_124, MatchPositiveForValidAndNonPositiveForInvalid_124) {
  const YAML::RegEx& word = YAML::Exp::Word();

  // We only assert "success vs failure" via the sign of the return value,
  // without assuming exact semantics (e.g., matched length).
  EXPECT_GT(word.Match(std::string("a")), 0);
  EXPECT_GT(word.Match(std::string("-")), 0);

  EXPECT_LE(word.Match(std::string(" ")), 0);
  EXPECT_LE(word.Match(std::string("_")), 0);
  EXPECT_LE(word.Match(std::string(".")), 0);
}

}  // namespace
