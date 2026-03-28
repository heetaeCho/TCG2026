// TEST_ID: 138
// File: ./TestProjects/yaml-cpp/test/exp_comment_test_138.cpp

#include <gtest/gtest.h>

#include "TestProjects/yaml-cpp/src/exp.h"

namespace {

TEST(CommentExpTest_138, MatchesHashCharacter_138) {
  const YAML::RegEx ex = YAML::Exp::Comment();
  EXPECT_TRUE(ex.Matches('#'));
}

TEST(CommentExpTest_138, DoesNotMatchNonHashCharacters_138) {
  const YAML::RegEx ex = YAML::Exp::Comment();

  EXPECT_FALSE(ex.Matches('a'));
  EXPECT_FALSE(ex.Matches('0'));
  EXPECT_FALSE(ex.Matches('_'));
  EXPECT_FALSE(ex.Matches(' '));
  EXPECT_FALSE(ex.Matches('\n'));
}

TEST(CommentExpTest_138, MatchesHashString_138) {
  const YAML::RegEx ex = YAML::Exp::Comment();
  EXPECT_TRUE(ex.Matches(std::string("#")));
}

TEST(CommentExpTest_138, DoesNotMatchNonHashString_138) {
  const YAML::RegEx ex = YAML::Exp::Comment();

  EXPECT_FALSE(ex.Matches(std::string("a")));
  EXPECT_FALSE(ex.Matches(std::string("")));
}

TEST(CommentExpTest_138, MultipleCallsProduceUsableRegex_138) {
  const YAML::RegEx ex1 = YAML::Exp::Comment();
  const YAML::RegEx ex2 = YAML::Exp::Comment();

  EXPECT_TRUE(ex1.Matches('#'));
  EXPECT_TRUE(ex2.Matches('#'));
  EXPECT_FALSE(ex1.Matches('x'));
  EXPECT_FALSE(ex2.Matches('x'));
}

}  // namespace
