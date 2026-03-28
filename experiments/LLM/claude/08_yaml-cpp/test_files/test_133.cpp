#include "gtest/gtest.h"
#include "exp.h"
#include "regex_yaml.h"

namespace YAML {
namespace {

// =============================================================================
// Tests for KeyInFlow() from exp.h
// KeyInFlow() returns a RegEx that matches '?' followed by a blank or break
// =============================================================================

class KeyInFlowTest_133 : public ::testing::Test {
 protected:
  const RegEx& key_in_flow_ = Exp::KeyInFlow();
};

// Test that KeyInFlow matches '?' followed by a space
TEST_F(KeyInFlowTest_133, MatchesQuestionMarkFollowedBySpace_133) {
  std::string input = "? ";
  int result = key_in_flow_.Match(input);
  EXPECT_EQ(result, 2);
}

// Test that KeyInFlow matches '?' followed by a tab
TEST_F(KeyInFlowTest_133, MatchesQuestionMarkFollowedByTab_133) {
  std::string input = "?\t";
  int result = key_in_flow_.Match(input);
  EXPECT_EQ(result, 2);
}

// Test that KeyInFlow matches '?' followed by a newline
TEST_F(KeyInFlowTest_133, MatchesQuestionMarkFollowedByNewline_133) {
  std::string input = "?\n";
  int result = key_in_flow_.Match(input);
  EXPECT_EQ(result, 2);
}

// Test that KeyInFlow matches '?' followed by a carriage return
TEST_F(KeyInFlowTest_133, MatchesQuestionMarkFollowedByCarriageReturn_133) {
  std::string input = "?\r";
  int result = key_in_flow_.Match(input);
  EXPECT_EQ(result, 2);
}

// Test that KeyInFlow does NOT match '?' followed by a non-blank character
TEST_F(KeyInFlowTest_133, DoesNotMatchQuestionMarkFollowedByNonBlank_133) {
  std::string input = "?a";
  int result = key_in_flow_.Match(input);
  EXPECT_EQ(result, -1);
}

// Test that KeyInFlow does NOT match a lone '?'
TEST_F(KeyInFlowTest_133, DoesNotMatchLoneQuestionMark_133) {
  std::string input = "?";
  int result = key_in_flow_.Match(input);
  EXPECT_EQ(result, -1);
}

// Test that KeyInFlow does NOT match an empty string
TEST_F(KeyInFlowTest_133, DoesNotMatchEmptyString_133) {
  std::string input = "";
  int result = key_in_flow_.Match(input);
  EXPECT_EQ(result, -1);
}

// Test that KeyInFlow does NOT match a string starting with a different character
TEST_F(KeyInFlowTest_133, DoesNotMatchDifferentCharacterFollowedBySpace_133) {
  std::string input = "a ";
  int result = key_in_flow_.Match(input);
  EXPECT_EQ(result, -1);
}

// Test that KeyInFlow does NOT match a space alone
TEST_F(KeyInFlowTest_133, DoesNotMatchSpaceAlone_133) {
  std::string input = " ";
  int result = key_in_flow_.Match(input);
  EXPECT_EQ(result, -1);
}

// Test that KeyInFlow does NOT match just a letter
TEST_F(KeyInFlowTest_133, DoesNotMatchJustALetter_133) {
  std::string input = "a";
  int result = key_in_flow_.Match(input);
  EXPECT_EQ(result, -1);
}

// Test that KeyInFlow returns the same static instance each time
TEST_F(KeyInFlowTest_133, ReturnsSameInstanceEachCall_133) {
  const RegEx& first = Exp::KeyInFlow();
  const RegEx& second = Exp::KeyInFlow();
  EXPECT_EQ(&first, &second);
}

// Test that Matches returns true for '?' followed by space
TEST_F(KeyInFlowTest_133, MatchesBoolReturnsTrueForValidInput_133) {
  std::string input = "? ";
  EXPECT_TRUE(key_in_flow_.Matches(input));
}

// Test that Matches returns false for '?' followed by non-blank
TEST_F(KeyInFlowTest_133, MatchesBoolReturnsFalseForInvalidInput_133) {
  std::string input = "?x";
  EXPECT_FALSE(key_in_flow_.Matches(input));
}

// Test that Matches returns false for empty string
TEST_F(KeyInFlowTest_133, MatchesBoolReturnsFalseForEmptyString_133) {
  std::string input = "";
  EXPECT_FALSE(key_in_flow_.Matches(input));
}

// Test that KeyInFlow does NOT match '?' followed by digit
TEST_F(KeyInFlowTest_133, DoesNotMatchQuestionMarkFollowedByDigit_133) {
  std::string input = "?0";
  int result = key_in_flow_.Match(input);
  EXPECT_EQ(result, -1);
}

// Test that KeyInFlow does NOT match '?' followed by '?'
TEST_F(KeyInFlowTest_133, DoesNotMatchQuestionMarkFollowedByQuestionMark_133) {
  std::string input = "??";
  int result = key_in_flow_.Match(input);
  EXPECT_EQ(result, -1);
}

// Test with longer string starting with valid pattern - Match should return 2
TEST_F(KeyInFlowTest_133, MatchesOnlyFirstTwoCharsOfLongerString_133) {
  std::string input = "? value";
  int result = key_in_flow_.Match(input);
  EXPECT_EQ(result, 2);
}

// Test that KeyInFlow does NOT match when '?' is not the first character
TEST_F(KeyInFlowTest_133, DoesNotMatchWhenQuestionMarkNotFirst_133) {
  std::string input = " ?";
  int result = key_in_flow_.Match(input);
  EXPECT_EQ(result, -1);
}

}  // namespace
}  // namespace YAML
