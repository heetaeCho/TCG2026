// File: ./TestProjects/yaml-cpp/test/exp_plain_scalar_test_143.cpp

#include <gtest/gtest.h>

#include "TestProjects/yaml-cpp/src/exp.h"

namespace {

class PlainScalarTest_143 : public ::testing::Test {
 protected:
  static const YAML::RegEx& Plain() { return YAML::Exp::PlainScalar(); }
};

TEST_F(PlainScalarTest_143, ReturnsStableSingletonReference_143) {
  const YAML::RegEx* p1 = &Plain();
  const YAML::RegEx* p2 = &Plain();
  const YAML::RegEx* p3 = &Plain();

  EXPECT_EQ(p1, p2);
  EXPECT_EQ(p2, p3);
}

TEST_F(PlainScalarTest_143, MatchesTypicalNonSpecialCharacter_143) {
  EXPECT_TRUE(Plain().Matches('a'));
  EXPECT_TRUE(Plain().Matches('Z'));
  EXPECT_TRUE(Plain().Matches('0'));
  EXPECT_TRUE(Plain().Matches('_'));
}

TEST_F(PlainScalarTest_143, DoesNotMatchBlankOrLineBreakCharacters_143) {
  // Blank
  EXPECT_FALSE(Plain().Matches(' '));
  EXPECT_FALSE(Plain().Matches('\t'));

  // Breaks
  EXPECT_FALSE(Plain().Matches('\n'));
  EXPECT_FALSE(Plain().Matches('\r'));
}

TEST_F(PlainScalarTest_143, DoesNotMatchYamlIndicatorPunctuationCharacters_143) {
  // These characters are explicitly listed in the expression used by PlainScalar().
  const char disallowed[] = {',', '[', ']', '{', '}', '#', '&', '*', '!', '|',
                             '>', '\'', '"', '%', '@', '`'};

  for (char ch : disallowed) {
    EXPECT_FALSE(Plain().Matches(ch)) << "Unexpectedly matched disallowed char: '" << ch << "'";
  }
}

TEST_F(PlainScalarTest_143, DoesNotMatchLeadingDashQuestionColonCharacters_143) {
  // These are explicitly part of the "-?:" alternation in the expression.
  EXPECT_FALSE(Plain().Matches('-'));
  EXPECT_FALSE(Plain().Matches('?'));
  EXPECT_FALSE(Plain().Matches(':'));
}

TEST_F(PlainScalarTest_143, StringMatchesForSimpleAllowedString_143) {
  // Use the public string API as well (observable behavior).
  EXPECT_TRUE(Plain().Matches(std::string("abc")));
  EXPECT_TRUE(Plain().Matches(std::string("A1_")));
}

TEST_F(PlainScalarTest_143, StringDoesNotMatchForDisallowedSingleCharacterStrings_143) {
  EXPECT_FALSE(Plain().Matches(std::string(" ")));
  EXPECT_FALSE(Plain().Matches(std::string("\n")));
  EXPECT_FALSE(Plain().Matches(std::string(",")));
  EXPECT_FALSE(Plain().Matches(std::string("-")));
  EXPECT_FALSE(Plain().Matches(std::string("?")));
  EXPECT_FALSE(Plain().Matches(std::string(":")));
}

}  // namespace
