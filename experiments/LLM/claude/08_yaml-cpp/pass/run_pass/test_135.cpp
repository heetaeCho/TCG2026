#include "gtest/gtest.h"
#include "exp.h"
#include "regex_yaml.h"

namespace YAML {
namespace {

class ValueInFlowTest_135 : public ::testing::Test {
 protected:
  const RegEx& valueInFlow = Exp::ValueInFlow();
};

// Test that ValueInFlow returns the same object every time (static)
TEST_F(ValueInFlowTest_135, ReturnsSameInstance_135) {
  const RegEx& first = Exp::ValueInFlow();
  const RegEx& second = Exp::ValueInFlow();
  EXPECT_EQ(&first, &second);
}

// Test that ':' followed by a space matches
TEST_F(ValueInFlowTest_135, MatchesColonFollowedBySpace_135) {
  std::string input = ": ";
  int result = valueInFlow.Match(input);
  EXPECT_EQ(result, 2);
}

// Test that ':' followed by a tab matches
TEST_F(ValueInFlowTest_135, MatchesColonFollowedByTab_135) {
  std::string input = ":\t";
  int result = valueInFlow.Match(input);
  EXPECT_EQ(result, 2);
}

// Test that ':' followed by a newline matches
TEST_F(ValueInFlowTest_135, MatchesColonFollowedByNewline_135) {
  std::string input = ":\n";
  int result = valueInFlow.Match(input);
  EXPECT_EQ(result, 2);
}

// Test that ':' followed by a comma matches
TEST_F(ValueInFlowTest_135, MatchesColonFollowedByComma_135) {
  std::string input = ":,";
  int result = valueInFlow.Match(input);
  EXPECT_EQ(result, 2);
}

// Test that ':' followed by ']' matches
TEST_F(ValueInFlowTest_135, MatchesColonFollowedByCloseBracket_135) {
  std::string input = ":]";
  int result = valueInFlow.Match(input);
  EXPECT_EQ(result, 2);
}

// Test that ':' followed by '}' matches
TEST_F(ValueInFlowTest_135, MatchesColonFollowedByCloseBrace_135) {
  std::string input = ":}";
  int result = valueInFlow.Match(input);
  EXPECT_EQ(result, 2);
}

// Test that ':' followed by a regular character does NOT match
TEST_F(ValueInFlowTest_135, DoesNotMatchColonFollowedByAlpha_135) {
  std::string input = ":a";
  int result = valueInFlow.Match(input);
  EXPECT_EQ(result, -1);
}

// Test that ':' followed by a digit does NOT match
TEST_F(ValueInFlowTest_135, DoesNotMatchColonFollowedByDigit_135) {
  std::string input = ":5";
  int result = valueInFlow.Match(input);
  EXPECT_EQ(result, -1);
}

// Test that a string not starting with ':' does not match
TEST_F(ValueInFlowTest_135, DoesNotMatchNonColon_135) {
  std::string input = "a ";
  int result = valueInFlow.Match(input);
  EXPECT_EQ(result, -1);
}

// Test that an empty string does not match
TEST_F(ValueInFlowTest_135, DoesNotMatchEmptyString_135) {
  std::string input = "";
  int result = valueInFlow.Match(input);
  EXPECT_EQ(result, -1);
}

// Test that a single colon alone does not match (no following character)
TEST_F(ValueInFlowTest_135, DoesNotMatchLoneColon_135) {
  std::string input = ":";
  int result = valueInFlow.Match(input);
  EXPECT_EQ(result, -1);
}

// Test Matches method with matching input
TEST_F(ValueInFlowTest_135, MatchesMethodReturnsTrueForColonSpace_135) {
  std::string input = ": ";
  EXPECT_TRUE(valueInFlow.Matches(input));
}

// Test Matches method with non-matching input
TEST_F(ValueInFlowTest_135, MatchesMethodReturnsFalseForColonAlpha_135) {
  std::string input = ":a";
  EXPECT_FALSE(valueInFlow.Matches(input));
}

// Test Matches method with empty string
TEST_F(ValueInFlowTest_135, MatchesMethodReturnsFalseForEmptyString_135) {
  std::string input = "";
  EXPECT_FALSE(valueInFlow.Matches(input));
}

// Test that ':' followed by carriage return matches (if it's a break)
TEST_F(ValueInFlowTest_135, MatchesColonFollowedByCarriageReturn_135) {
  std::string input = ":\r";
  int result = valueInFlow.Match(input);
  // \r is a break character, so it should match
  EXPECT_EQ(result, 2);
}

// Test colon followed by special characters that are not in the set
TEST_F(ValueInFlowTest_135, DoesNotMatchColonFollowedByExclamation_135) {
  std::string input = ":!";
  int result = valueInFlow.Match(input);
  EXPECT_EQ(result, -1);
}

// Test colon followed by colon (should not match)
TEST_F(ValueInFlowTest_135, DoesNotMatchColonFollowedByColon_135) {
  std::string input = "::";
  int result = valueInFlow.Match(input);
  EXPECT_EQ(result, -1);
}

// Test that only the first two characters are consumed in a longer matching string
TEST_F(ValueInFlowTest_135, MatchLengthIsTwoForLongerString_135) {
  std::string input = ": hello";
  int result = valueInFlow.Match(input);
  EXPECT_EQ(result, 2);
}

// Test colon followed by '[' (not in the flow indicators set for this regex)
TEST_F(ValueInFlowTest_135, DoesNotMatchColonFollowedByOpenBracket_135) {
  std::string input = ":[";
  int result = valueInFlow.Match(input);
  EXPECT_EQ(result, -1);
}

// Test colon followed by '{' (not in the flow indicators set for this regex)
TEST_F(ValueInFlowTest_135, DoesNotMatchColonFollowedByOpenBrace_135) {
  std::string input = ":{";
  int result = valueInFlow.Match(input);
  EXPECT_EQ(result, -1);
}

}  // namespace
}  // namespace YAML
