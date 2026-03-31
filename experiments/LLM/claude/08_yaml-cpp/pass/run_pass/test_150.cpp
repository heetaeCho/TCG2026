#include "gtest/gtest.h"
#include "exp.h"
#include "regex_yaml.h"

namespace YAML {
namespace {

// Test fixture for Exp::EscBreak tests
class ExpEscBreakTest_150 : public ::testing::Test {
 protected:
  const RegEx& esc_break = Exp::EscBreak();
};

// Test that EscBreak returns a valid RegEx reference
TEST_F(ExpEscBreakTest_150, ReturnsValidRegEx_150) {
  // EscBreak should return a reference to a static RegEx; just verify it doesn't crash
  const RegEx& ref = Exp::EscBreak();
  (void)ref;
  SUCCEED();
}

// Test that EscBreak returns the same object each time (static)
TEST_F(ExpEscBreakTest_150, ReturnsSameStaticInstance_150) {
  const RegEx& ref1 = Exp::EscBreak();
  const RegEx& ref2 = Exp::EscBreak();
  EXPECT_EQ(&ref1, &ref2);
}

// Test that EscBreak matches backslash followed by newline (\n)
TEST_F(ExpEscBreakTest_150, MatchesBackslashFollowedByNewline_150) {
  std::string input = "\\\n";
  int result = esc_break.Match(input);
  EXPECT_EQ(result, 2);
}

// Test that EscBreak matches backslash followed by carriage return (\r)
TEST_F(ExpEscBreakTest_150, MatchesBackslashFollowedByCarriageReturn_150) {
  std::string input = "\\\r";
  int result = esc_break.Match(input);
  EXPECT_GE(result, 2);
}

// Test that EscBreak matches backslash followed by \r\n
TEST_F(ExpEscBreakTest_150, MatchesBackslashFollowedByCRLF_150) {
  std::string input = "\\\r\n";
  int result = esc_break.Match(input);
  EXPECT_GE(result, 2);
}

// Test that EscBreak does NOT match a single backslash alone
TEST_F(ExpEscBreakTest_150, DoesNotMatchSingleBackslash_150) {
  std::string input = "\\";
  int result = esc_break.Match(input);
  EXPECT_LE(result, 0);
}

// Test that EscBreak does NOT match a bare newline (no backslash)
TEST_F(ExpEscBreakTest_150, DoesNotMatchBareNewline_150) {
  std::string input = "\n";
  int result = esc_break.Match(input);
  EXPECT_LE(result, 0);
}

// Test that EscBreak does NOT match an empty string
TEST_F(ExpEscBreakTest_150, DoesNotMatchEmptyString_150) {
  std::string input = "";
  int result = esc_break.Match(input);
  EXPECT_LE(result, 0);
}

// Test that EscBreak does NOT match regular text
TEST_F(ExpEscBreakTest_150, DoesNotMatchRegularText_150) {
  std::string input = "hello";
  int result = esc_break.Match(input);
  EXPECT_LE(result, 0);
}

// Test that EscBreak does NOT match backslash followed by regular character
TEST_F(ExpEscBreakTest_150, DoesNotMatchBackslashFollowedByRegularChar_150) {
  std::string input = "\\a";
  int result = esc_break.Match(input);
  EXPECT_LE(result, 0);
}

// Test that EscBreak does NOT match backslash followed by space
TEST_F(ExpEscBreakTest_150, DoesNotMatchBackslashFollowedBySpace_150) {
  std::string input = "\\ ";
  int result = esc_break.Match(input);
  EXPECT_LE(result, 0);
}

// Test Matches(string) with valid escape break sequence
TEST_F(ExpEscBreakTest_150, MatchesFunctionReturnsTrueForValidSequence_150) {
  std::string input = "\\\n";
  bool result = esc_break.Matches(input);
  EXPECT_TRUE(result);
}

// Test Matches(string) returns false for invalid input
TEST_F(ExpEscBreakTest_150, MatchesFunctionReturnsFalseForInvalidSequence_150) {
  std::string input = "abc";
  bool result = esc_break.Matches(input);
  EXPECT_FALSE(result);
}

// Test that backslash followed by tab does not match
TEST_F(ExpEscBreakTest_150, DoesNotMatchBackslashFollowedByTab_150) {
  std::string input = "\\\t";
  int result = esc_break.Match(input);
  EXPECT_LE(result, 0);
}

// Test that a double backslash does not match
TEST_F(ExpEscBreakTest_150, DoesNotMatchDoubleBackslash_150) {
  std::string input = "\\\\";
  int result = esc_break.Match(input);
  EXPECT_LE(result, 0);
}

// Test Match with backslash + newline + extra characters (should match prefix)
TEST_F(ExpEscBreakTest_150, MatchReturnsLengthOfMatchedPrefix_150) {
  std::string input = "\\\nfoo";
  int result = esc_break.Match(input);
  EXPECT_EQ(result, 2);
}

// Test Matches(char) - single character should not match a two-char sequence
TEST_F(ExpEscBreakTest_150, SingleCharDoesNotMatch_150) {
  EXPECT_FALSE(esc_break.Matches('\\'));
  EXPECT_FALSE(esc_break.Matches('\n'));
  EXPECT_FALSE(esc_break.Matches('\r'));
  EXPECT_FALSE(esc_break.Matches('a'));
}

}  // namespace
}  // namespace YAML
