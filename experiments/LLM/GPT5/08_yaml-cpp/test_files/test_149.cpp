// TEST_ID: 149
#include <gtest/gtest.h>

#include "exp.h"  // YAML::Exp::EscSingleQuote()

namespace {

class EscSingleQuoteTest_149 : public ::testing::Test {};

TEST_F(EscSingleQuoteTest_149, ReturnsSameInstanceAcrossCalls_149) {
  const YAML::RegEx* first = &YAML::Exp::EscSingleQuote();
  const YAML::RegEx* second = &YAML::Exp::EscSingleQuote();
  const YAML::RegEx* third = &YAML::Exp::EscSingleQuote();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(EscSingleQuoteTest_149, MatchesExactlyTwoSingleQuotes_149) {
  const auto& re = YAML::Exp::EscSingleQuote();

  EXPECT_TRUE(re.Matches(std::string("''")));
  EXPECT_EQ(re.Match(std::string("''")), 2);
}

TEST_F(EscSingleQuoteTest_149, DoesNotMatchSingleQuoteOnly_149) {
  const auto& re = YAML::Exp::EscSingleQuote();

  EXPECT_FALSE(re.Matches(std::string("'")));
  EXPECT_LT(re.Match(std::string("'")), 2);
}

TEST_F(EscSingleQuoteTest_149, DoesNotMatchEmptyString_149) {
  const auto& re = YAML::Exp::EscSingleQuote();

  EXPECT_FALSE(re.Matches(std::string("")));
  EXPECT_LE(re.Match(std::string("")), 0);
}

TEST_F(EscSingleQuoteTest_149, DoesNotMatchMoreThanTwoSingleQuotesAsWholeString_149) {
  const auto& re = YAML::Exp::EscSingleQuote();

  EXPECT_FALSE(re.Matches(std::string("'''")));
  // If Match() reports the matched prefix length, it should match exactly 2 at the start.
  EXPECT_EQ(re.Match(std::string("'''")), 2);
}

TEST_F(EscSingleQuoteTest_149, MatchFindsPrefixInLongerString_149) {
  const auto& re = YAML::Exp::EscSingleQuote();

  EXPECT_EQ(re.Match(std::string("''abc")), 2);
  EXPECT_FALSE(re.Matches(std::string("''abc")));
}

TEST_F(EscSingleQuoteTest_149, DoesNotMatchDifferentCharacters_149) {
  const auto& re = YAML::Exp::EscSingleQuote();

  EXPECT_FALSE(re.Matches(std::string("\"\"")));
  EXPECT_FALSE(re.Matches(std::string("aa")));
  EXPECT_LT(re.Match(std::string("aa")), 2);
}

}  // namespace
