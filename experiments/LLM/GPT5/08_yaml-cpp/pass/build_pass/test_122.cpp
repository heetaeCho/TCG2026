// TEST_ID: 122
#include <gtest/gtest.h>

#include "exp.h"
#include "regex_yaml.h"

namespace {

using YAML::Exp::Alpha;

TEST(ExpAlphaTest_122, ReturnsSameReferenceAcrossCalls_122) {
  const YAML::RegEx* p1 = &Alpha();
  const YAML::RegEx* p2 = &Alpha();
  EXPECT_EQ(p1, p2);
}

TEST(ExpAlphaTest_122, MatchesLowercaseAlphabetBoundaries_122) {
  const YAML::RegEx& re = Alpha();

  EXPECT_TRUE(re.Matches('a'));
  EXPECT_TRUE(re.Matches('z'));
}

TEST(ExpAlphaTest_122, MatchesUppercaseAlphabetBoundaries_122) {
  const YAML::RegEx& re = Alpha();

  EXPECT_TRUE(re.Matches('A'));
  EXPECT_TRUE(re.Matches('Z'));
}

TEST(ExpAlphaTest_122, DoesNotMatchCharactersJustOutsideLowercaseRange_122) {
  const YAML::RegEx& re = Alpha();

  EXPECT_FALSE(re.Matches('`'));  // just before 'a'
  EXPECT_FALSE(re.Matches('{'));  // just after 'z'
}

TEST(ExpAlphaTest_122, DoesNotMatchCharactersJustOutsideUppercaseRange_122) {
  const YAML::RegEx& re = Alpha();

  EXPECT_FALSE(re.Matches('@'));  // just before 'A'
  EXPECT_FALSE(re.Matches('['));  // just after 'Z'
}

TEST(ExpAlphaTest_122, DoesNotMatchDigitsWhitespaceOrPunctuation_122) {
  const YAML::RegEx& re = Alpha();

  EXPECT_FALSE(re.Matches('0'));
  EXPECT_FALSE(re.Matches('9'));
  EXPECT_FALSE(re.Matches(' '));
  EXPECT_FALSE(re.Matches('\n'));
  EXPECT_FALSE(re.Matches('_'));
  EXPECT_FALSE(re.Matches('-'));
  EXPECT_FALSE(re.Matches('.'));
}

TEST(ExpAlphaTest_122, MatchesSingleCharacterStringsWhenAlphabetic_122) {
  const YAML::RegEx& re = Alpha();

  EXPECT_TRUE(re.Matches(std::string("a")));
  EXPECT_TRUE(re.Matches(std::string("Z")));
  EXPECT_FALSE(re.Matches(std::string("0")));
  EXPECT_FALSE(re.Matches(std::string("_")));
}

}  // namespace
