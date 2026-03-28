// TEST_ID: 139
#include <gtest/gtest.h>

#include "exp.h"
#include "regex_yaml.h"

namespace {

class AnchorTest_139 : public ::testing::Test {};

TEST_F(AnchorTest_139, ReturnsSameInstanceEachCall_139) {
  const YAML::RegEx* a1 = &YAML::Exp::Anchor();
  const YAML::RegEx* a2 = &YAML::Exp::Anchor();
  const YAML::RegEx* a3 = &YAML::Exp::Anchor();

  EXPECT_EQ(a1, a2);
  EXPECT_EQ(a2, a3);
}

TEST_F(AnchorTest_139, DoesNotMatchBracketBraceCommaCharacters_139) {
  const YAML::RegEx& re = YAML::Exp::Anchor();

  // Characters explicitly present in the expression inside Anchor(): "[]{},"
  EXPECT_FALSE(re.Matches('['));
  EXPECT_FALSE(re.Matches(']'));
  EXPECT_FALSE(re.Matches('{'));
  EXPECT_FALSE(re.Matches('}'));
  EXPECT_FALSE(re.Matches(','));
}

TEST_F(AnchorTest_139, MatchesCommonNonDelimiterCharacters_139) {
  const YAML::RegEx& re = YAML::Exp::Anchor();

  // A small, representative set of characters that are not in "[]{},"
  // and are typically not blanks/breaks.
  EXPECT_TRUE(re.Matches('a'));
  EXPECT_TRUE(re.Matches('Z'));
  EXPECT_TRUE(re.Matches('0'));
  EXPECT_TRUE(re.Matches('_'));
  EXPECT_TRUE(re.Matches('-'));
  EXPECT_TRUE(re.Matches('.'));
}

TEST_F(AnchorTest_139, DoesNotMatchCommonBlanksAndLineBreaks_139) {
  const YAML::RegEx& re = YAML::Exp::Anchor();

  // Based on the public interface usage in Anchor(): it negates an OR with BlankOrBreak().
  // Verify typical blank/break characters are rejected.
  EXPECT_FALSE(re.Matches(' '));
  EXPECT_FALSE(re.Matches('\t'));
  EXPECT_FALSE(re.Matches('\n'));
  EXPECT_FALSE(re.Matches('\r'));
}

TEST_F(AnchorTest_139, MatchesCharAndSingleCharStringConsistently_139) {
  const YAML::RegEx& re = YAML::Exp::Anchor();

  // Sanity check that char vs single-character string agree for a few cases.
  EXPECT_EQ(re.Matches('a'), re.Matches(std::string("a")));
  EXPECT_EQ(re.Matches('['), re.Matches(std::string("[")));
  EXPECT_EQ(re.Matches(' '), re.Matches(std::string(" ")));
}

}  // namespace
