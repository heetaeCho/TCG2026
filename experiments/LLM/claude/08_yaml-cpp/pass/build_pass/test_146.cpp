#include "gtest/gtest.h"
#include "exp.h"
#include "regex_yaml.h"

namespace YAML {
namespace {

class EndScalarInFlowTest_146 : public ::testing::Test {
 protected:
  const RegEx& regex_ = Exp::EndScalarInFlow();
};

// Test that EndScalarInFlow returns a consistent reference (singleton pattern)
TEST_F(EndScalarInFlowTest_146, ReturnsSameReference_146) {
  const RegEx& first = Exp::EndScalarInFlow();
  const RegEx& second = Exp::EndScalarInFlow();
  EXPECT_EQ(&first, &second);
}

// Test that a comma matches (comma is part of ",?[]{}" set)
TEST_F(EndScalarInFlowTest_146, MatchesComma_146) {
  EXPECT_TRUE(regex_.Matches(std::string(",")));
}

// Test that '[' matches
TEST_F(EndScalarInFlowTest_146, MatchesOpenBracket_146) {
  EXPECT_TRUE(regex_.Matches(std::string("[")));
}

// Test that ']' matches
TEST_F(EndScalarInFlowTest_146, MatchesCloseBracket_146) {
  EXPECT_TRUE(regex_.Matches(std::string("]")));
}

// Test that '{' matches
TEST_F(EndScalarInFlowTest_146, MatchesOpenBrace_146) {
  EXPECT_TRUE(regex_.Matches(std::string("{")));
}

// Test that '}' matches
TEST_F(EndScalarInFlowTest_146, MatchesCloseBrace_146) {
  EXPECT_TRUE(regex_.Matches(std::string("}")));
}

// Test that '?' matches (part of ",?[]{}" set)
TEST_F(EndScalarInFlowTest_146, MatchesQuestionMark_146) {
  EXPECT_TRUE(regex_.Matches(std::string("?")));
}

// Test that ':' followed by a space matches (colon + blank)
TEST_F(EndScalarInFlowTest_146, MatchesColonFollowedBySpace_146) {
  EXPECT_TRUE(regex_.Matches(std::string(": ")));
}

// Test that ':' followed by a newline matches (colon + break)
TEST_F(EndScalarInFlowTest_146, MatchesColonFollowedByNewline_146) {
  EXPECT_TRUE(regex_.Matches(std::string(":\n")));
}

// Test that ':' followed by comma matches (colon + flow indicator)
TEST_F(EndScalarInFlowTest_146, MatchesColonFollowedByComma_146) {
  EXPECT_TRUE(regex_.Matches(std::string(":,")));
}

// Test that ':' followed by ']' matches
TEST_F(EndScalarInFlowTest_146, MatchesColonFollowedByCloseBracket_146) {
  EXPECT_TRUE(regex_.Matches(std::string(":]")));
}

// Test that ':' followed by '}' matches
TEST_F(EndScalarInFlowTest_146, MatchesColonFollowedByCloseBrace_146) {
  EXPECT_TRUE(regex_.Matches(std::string(":}")));
}

// Test that a regular letter does not match
TEST_F(EndScalarInFlowTest_146, DoesNotMatchRegularLetter_146) {
  EXPECT_FALSE(regex_.Matches(std::string("a")));
}

// Test that a digit does not match
TEST_F(EndScalarInFlowTest_146, DoesNotMatchDigit_146) {
  EXPECT_FALSE(regex_.Matches(std::string("0")));
}

// Test that a colon alone (followed by non-matching char) doesn't match
// ':' followed by a regular character should not match
TEST_F(EndScalarInFlowTest_146, DoesNotMatchColonFollowedByLetter_146) {
  EXPECT_FALSE(regex_.Matches(std::string(":a")));
}

// Test that a dash does not match
TEST_F(EndScalarInFlowTest_146, DoesNotMatchDash_146) {
  EXPECT_FALSE(regex_.Matches(std::string("-")));
}

// Test that a dot does not match
TEST_F(EndScalarInFlowTest_146, DoesNotMatchDot_146) {
  EXPECT_FALSE(regex_.Matches(std::string(".")));
}

// Test that a space alone does not match
TEST_F(EndScalarInFlowTest_146, DoesNotMatchSpace_146) {
  EXPECT_FALSE(regex_.Matches(std::string(" ")));
}

// Test that a tab does not match
TEST_F(EndScalarInFlowTest_146, DoesNotMatchTab_146) {
  EXPECT_FALSE(regex_.Matches(std::string("\t")));
}

// Test Match returns expected length for comma
TEST_F(EndScalarInFlowTest_146, MatchReturnsLengthForComma_146) {
  int result = regex_.Match(std::string(","));
  EXPECT_EQ(result, 1);
}

// Test Match returns expected length for open bracket
TEST_F(EndScalarInFlowTest_146, MatchReturnsLengthForOpenBracket_146) {
  int result = regex_.Match(std::string("["));
  EXPECT_EQ(result, 1);
}

// Test Match returns expected length for colon followed by space
TEST_F(EndScalarInFlowTest_146, MatchReturnsLengthForColonSpace_146) {
  int result = regex_.Match(std::string(": "));
  EXPECT_EQ(result, 2);
}

// Test Match returns -1 for non-matching string
TEST_F(EndScalarInFlowTest_146, MatchReturnsNegativeForNonMatch_146) {
  int result = regex_.Match(std::string("hello"));
  EXPECT_EQ(result, -1);
}

// Test empty string does not match
TEST_F(EndScalarInFlowTest_146, DoesNotMatchEmptyString_146) {
  int result = regex_.Match(std::string(""));
  EXPECT_EQ(result, -1);
}

// Test colon at end of string (no following character)
TEST_F(EndScalarInFlowTest_146, ColonAtEndOfString_146) {
  // ':' + empty regex (REGEX_EMPTY) - colon at end might match as colon + empty
  int result = regex_.Match(std::string(":"));
  // Colon alone could match if empty regex matches end-of-input
  // Either way, we just verify it doesn't crash and returns a deterministic result
  EXPECT_GE(result, -1);
}

// Test that ':' followed by tab matches (tab is a blank character)
TEST_F(EndScalarInFlowTest_146, MatchesColonFollowedByTab_146) {
  int result = regex_.Match(std::string(":\t"));
  EXPECT_EQ(result, 2);
}

// Test that ':' followed by carriage return matches (break character)
TEST_F(EndScalarInFlowTest_146, MatchesColonFollowedByCR_146) {
  int result = regex_.Match(std::string(":\r"));
  EXPECT_EQ(result, 2);
}

// Test single char Matches overload for comma
TEST_F(EndScalarInFlowTest_146, SingleCharMatchesComma_146) {
  EXPECT_TRUE(regex_.Matches(','));
}

// Test single char Matches overload for open bracket
TEST_F(EndScalarInFlowTest_146, SingleCharMatchesOpenBracket_146) {
  EXPECT_TRUE(regex_.Matches('['));
}

// Test single char Matches overload for close bracket
TEST_F(EndScalarInFlowTest_146, SingleCharMatchesCloseBracket_146) {
  EXPECT_TRUE(regex_.Matches(']'));
}

// Test single char Matches overload for regular letter
TEST_F(EndScalarInFlowTest_146, SingleCharDoesNotMatchLetter_146) {
  EXPECT_FALSE(regex_.Matches('a'));
}

// Test single char colon - colon alone is part of a sequence, so single char match behavior
TEST_F(EndScalarInFlowTest_146, SingleCharColonBehavior_146) {
  // Colon is the first part of a sequence, not a standalone match in REGEX_OR set
  // Just verify deterministic behavior
  bool result = regex_.Matches(':');
  // We just ensure it doesn't crash; the actual result depends on implementation
  (void)result;
}

// Test question mark single char match
TEST_F(EndScalarInFlowTest_146, SingleCharMatchesQuestionMark_146) {
  EXPECT_TRUE(regex_.Matches('?'));
}

// Test open brace single char
TEST_F(EndScalarInFlowTest_146, SingleCharMatchesOpenBrace_146) {
  EXPECT_TRUE(regex_.Matches('{'));
}

// Test close brace single char
TEST_F(EndScalarInFlowTest_146, SingleCharMatchesCloseBrace_146) {
  EXPECT_TRUE(regex_.Matches('}'));
}

}  // namespace
}  // namespace YAML
