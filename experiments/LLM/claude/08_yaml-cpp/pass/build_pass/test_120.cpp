#include "gtest/gtest.h"
#include "exp.h"
#include "regex_yaml.h"

namespace YAML {
namespace {

// Test fixture for BlankOrBreak tests
class BlankOrBreakTest_120 : public ::testing::Test {
 protected:
  const RegEx& blankOrBreak = Exp::BlankOrBreak();
};

// Normal operation: space character should match
TEST_F(BlankOrBreakTest_120, MatchesSpace_120) {
  EXPECT_TRUE(blankOrBreak.Matches(' '));
}

// Normal operation: tab character should match
TEST_F(BlankOrBreakTest_120, MatchesTab_120) {
  EXPECT_TRUE(blankOrBreak.Matches('\t'));
}

// Normal operation: newline character should match (line break)
TEST_F(BlankOrBreakTest_120, MatchesNewline_120) {
  EXPECT_TRUE(blankOrBreak.Matches('\n'));
}

// Normal operation: carriage return should match (line break)
TEST_F(BlankOrBreakTest_120, MatchesCarriageReturn_120) {
  EXPECT_TRUE(blankOrBreak.Matches('\r'));
}

// Error/boundary: regular letter should not match
TEST_F(BlankOrBreakTest_120, DoesNotMatchLetter_120) {
  EXPECT_FALSE(blankOrBreak.Matches('a'));
}

// Error/boundary: digit should not match
TEST_F(BlankOrBreakTest_120, DoesNotMatchDigit_120) {
  EXPECT_FALSE(blankOrBreak.Matches('0'));
}

// Error/boundary: punctuation should not match
TEST_F(BlankOrBreakTest_120, DoesNotMatchPunctuation_120) {
  EXPECT_FALSE(blankOrBreak.Matches('.'));
}

// Error/boundary: null character should not match
TEST_F(BlankOrBreakTest_120, DoesNotMatchNullChar_120) {
  EXPECT_FALSE(blankOrBreak.Matches('\0'));
}

// Error/boundary: special characters should not match
TEST_F(BlankOrBreakTest_120, DoesNotMatchExclamation_120) {
  EXPECT_FALSE(blankOrBreak.Matches('!'));
}

TEST_F(BlankOrBreakTest_120, DoesNotMatchColon_120) {
  EXPECT_FALSE(blankOrBreak.Matches(':'));
}

TEST_F(BlankOrBreakTest_120, DoesNotMatchHash_120) {
  EXPECT_FALSE(blankOrBreak.Matches('#'));
}

// Verify the returned reference is always the same (singleton behavior)
TEST_F(BlankOrBreakTest_120, ReturnsSameReference_120) {
  const RegEx& ref1 = Exp::BlankOrBreak();
  const RegEx& ref2 = Exp::BlankOrBreak();
  EXPECT_EQ(&ref1, &ref2);
}

// String-based Match tests
TEST_F(BlankOrBreakTest_120, MatchStringWithSpace_120) {
  EXPECT_TRUE(blankOrBreak.Matches(std::string(" ")));
}

TEST_F(BlankOrBreakTest_120, MatchStringWithTab_120) {
  EXPECT_TRUE(blankOrBreak.Matches(std::string("\t")));
}

TEST_F(BlankOrBreakTest_120, MatchStringWithNewline_120) {
  EXPECT_TRUE(blankOrBreak.Matches(std::string("\n")));
}

TEST_F(BlankOrBreakTest_120, DoesNotMatchStringWithLetter_120) {
  EXPECT_FALSE(blankOrBreak.Matches(std::string("a")));
}

// Match (int return) tests - checks length of match
TEST_F(BlankOrBreakTest_120, MatchReturnsOneForSpace_120) {
  int result = blankOrBreak.Match(std::string(" "));
  EXPECT_EQ(result, 1);
}

TEST_F(BlankOrBreakTest_120, MatchReturnsOneForTab_120) {
  int result = blankOrBreak.Match(std::string("\t"));
  EXPECT_EQ(result, 1);
}

TEST_F(BlankOrBreakTest_120, MatchReturnsOneForNewline_120) {
  int result = blankOrBreak.Match(std::string("\n"));
  EXPECT_EQ(result, 1);
}

TEST_F(BlankOrBreakTest_120, MatchReturnsNegativeForNonMatch_120) {
  int result = blankOrBreak.Match(std::string("x"));
  EXPECT_EQ(result, -1);
}

// Boundary: empty string
TEST_F(BlankOrBreakTest_120, MatchReturnsNegativeForEmptyString_120) {
  int result = blankOrBreak.Match(std::string(""));
  EXPECT_EQ(result, -1);
}

// Test with various non-printable characters that are not blank or break
TEST_F(BlankOrBreakTest_120, DoesNotMatchBell_120) {
  EXPECT_FALSE(blankOrBreak.Matches('\a'));
}

TEST_F(BlankOrBreakTest_120, DoesNotMatchBackspace_120) {
  EXPECT_FALSE(blankOrBreak.Matches('\b'));
}

TEST_F(BlankOrBreakTest_120, DoesNotMatchFormFeed_120) {
  EXPECT_FALSE(blankOrBreak.Matches('\f'));
}

TEST_F(BlankOrBreakTest_120, DoesNotMatchVerticalTab_120) {
  // Vertical tab is not typically considered a YAML blank or break
  EXPECT_FALSE(blankOrBreak.Matches('\v'));
}

// Match with string starting with blank followed by other chars
TEST_F(BlankOrBreakTest_120, MatchOnlyFirstCharOfString_120) {
  int result = blankOrBreak.Match(std::string(" hello"));
  // Should match just the first character
  EXPECT_EQ(result, 1);
}

TEST_F(BlankOrBreakTest_120, MatchOnlyFirstCharNewlineFollowedByText_120) {
  int result = blankOrBreak.Match(std::string("\nhello"));
  EXPECT_EQ(result, 1);
}

}  // namespace
}  // namespace YAML
