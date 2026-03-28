// TEST_ID: 134
#include <gtest/gtest.h>

#include "exp.h"  // YAML::Exp::Value()

namespace {

class ValueTest_134 : public ::testing::Test {};

TEST_F(ValueTest_134, ReturnsSameStaticInstance_134) {
  const YAML::RegEx* a = &YAML::Exp::Value();
  const YAML::RegEx* b = &YAML::Exp::Value();
  EXPECT_EQ(a, b);
}

TEST_F(ValueTest_134, MatchFailsOnEmptyString_134) {
  EXPECT_EQ(YAML::Exp::Value().Match(std::string{}), 0);
}

TEST_F(ValueTest_134, MatchFailsWhenColonNotAtStart_134) {
  EXPECT_EQ(YAML::Exp::Value().Match("abc"), 0);
  EXPECT_EQ(YAML::Exp::Value().Match(" abc"), 0);
  EXPECT_EQ(YAML::Exp::Value().Match(";"), 0);
}

TEST_F(ValueTest_134, MatchesSingleColonChar_134) {
  // Value() is a regex that begins with ':'; it should match ':' as a single-char source.
  EXPECT_TRUE(YAML::Exp::Value().Matches(':'));
}

TEST_F(ValueTest_134, DoesNotMatchNonColonChar_134) {
  EXPECT_FALSE(YAML::Exp::Value().Matches('a'));
  EXPECT_FALSE(YAML::Exp::Value().Matches(' '));
}

TEST_F(ValueTest_134, MatchSucceedsOnColonOnlyString_134) {
  const int n = YAML::Exp::Value().Match(":");
  EXPECT_GT(n, 0);
}

TEST_F(ValueTest_134, MatchSucceedsWhenColonIsFollowedByOtherText_134) {
  // We only assert that a match exists from the start; we do not assume how much is consumed.
  const int n = YAML::Exp::Value().Match(":abc");
  EXPECT_GT(n, 0);
}

TEST_F(ValueTest_134, MatchSucceedsWhenColonIsFollowedByWhitespace_134) {
  // Whether the whitespace is consumed depends on the underlying regex building blocks.
  // We only require that a match exists (observable through the public interface).
  const int n = YAML::Exp::Value().Match(": ");
  EXPECT_GT(n, 0);
}

}  // namespace
