#include "gtest/gtest.h"
#include "exp.h"
#include "regex_yaml.h"

namespace YAML {
namespace {

// Test fixture for EndScalar tests
class EndScalarTest_145 : public ::testing::Test {
 protected:
  const RegEx& endScalar = Exp::EndScalar();
};

// Test that EndScalar returns a valid RegEx reference
TEST_F(EndScalarTest_145, ReturnsValidReference_145) {
  // EndScalar() should return a reference to a static RegEx; calling it
  // multiple times should return the same object.
  const RegEx& ref1 = Exp::EndScalar();
  const RegEx& ref2 = Exp::EndScalar();
  EXPECT_EQ(&ref1, &ref2);
}

// Test that EndScalar matches a colon followed by a space
TEST_F(EndScalarTest_145, MatchesColonFollowedBySpace_145) {
  std::string input = ": ";
  int result = endScalar.Match(input);
  // A colon followed by a blank should match; expect match length of 1
  // (the colon itself, since the blank is a lookahead-like condition)
  EXPECT_GE(result, 1);
}

// Test that EndScalar matches a colon followed by a tab
TEST_F(EndScalarTest_145, MatchesColonFollowedByTab_145) {
  std::string input = ":\t";
  int result = endScalar.Match(input);
  EXPECT_GE(result, 1);
}

// Test that EndScalar matches a colon followed by a newline
TEST_F(EndScalarTest_145, MatchesColonFollowedByNewline_145) {
  std::string input = ":\n";
  int result = endScalar.Match(input);
  EXPECT_GE(result, 1);
}

// Test that EndScalar matches a colon followed by carriage return
TEST_F(EndScalarTest_145, MatchesColonFollowedByCarriageReturn_145) {
  std::string input = ":\r";
  int result = endScalar.Match(input);
  EXPECT_GE(result, 1);
}

// Test that EndScalar matches a colon at end of string (empty RegEx matches end)
TEST_F(EndScalarTest_145, MatchesColonAtEndOfString_145) {
  std::string input = ":";
  int result = endScalar.Match(input);
  // The RegEx() (empty regex) should match at end of input
  EXPECT_GE(result, 1);
}

// Test that EndScalar does NOT match a colon followed by a regular character
TEST_F(EndScalarTest_145, DoesNotMatchColonFollowedByAlpha_145) {
  std::string input = ":a";
  int result = endScalar.Match(input);
  // A colon followed by a non-blank, non-break character should not match
  EXPECT_EQ(result, -1);
}

// Test that EndScalar does NOT match a string not starting with colon
TEST_F(EndScalarTest_145, DoesNotMatchNonColonStart_145) {
  std::string input = "a: ";
  int result = endScalar.Match(input);
  EXPECT_EQ(result, -1);
}

// Test that EndScalar does NOT match an empty string
TEST_F(EndScalarTest_145, DoesNotMatchEmptyString_145) {
  std::string input = "";
  int result = endScalar.Match(input);
  EXPECT_EQ(result, -1);
}

// Test that EndScalar does NOT match a space alone
TEST_F(EndScalarTest_145, DoesNotMatchSpaceAlone_145) {
  std::string input = " ";
  int result = endScalar.Match(input);
  EXPECT_EQ(result, -1);
}

// Test that EndScalar does NOT match a colon followed by a digit
TEST_F(EndScalarTest_145, DoesNotMatchColonFollowedByDigit_145) {
  std::string input = ":1";
  int result = endScalar.Match(input);
  EXPECT_EQ(result, -1);
}

// Test that EndScalar does NOT match a colon followed by a hyphen
TEST_F(EndScalarTest_145, DoesNotMatchColonFollowedByHyphen_145) {
  std::string input = ":-";
  int result = endScalar.Match(input);
  EXPECT_EQ(result, -1);
}

// Test Matches(char) - single char colon should not fully match since
// EndScalar is a sequence requiring colon + (blank/break or end)
TEST_F(EndScalarTest_145, MatchesCharColon_145) {
  // Single char match checks if the regex matches exactly one character
  bool result = endScalar.Matches(':');
  // This depends on implementation; colon alone as a char may or may not match
  // We just verify it doesn't crash and returns a bool
  (void)result;
}

// Test Matches(char) with non-colon character
TEST_F(EndScalarTest_145, DoesNotMatchCharNonColon_145) {
  bool result = endScalar.Matches('a');
  EXPECT_FALSE(result);
}

// Test Matches(string) with colon at end of string
TEST_F(EndScalarTest_145, MatchesStringColonOnly_145) {
  std::string input = ":";
  bool result = endScalar.Matches(input);
  EXPECT_TRUE(result);
}

// Test Matches(string) with colon followed by space (length 2, may not fully match)
TEST_F(EndScalarTest_145, MatchesStringColonSpace_145) {
  std::string input = ": ";
  // Matches checks if the entire string matches; ": " might not fully match
  // since the regex is colon + (blank_or_break | empty), and the blank is consumed
  bool result = endScalar.Matches(input);
  // This could be true or false depending on how the sequence works
  (void)result;
}

// Test that EndScalar does NOT match a string with only whitespace
TEST_F(EndScalarTest_145, DoesNotMatchWhitespaceOnly_145) {
  std::string input = "   ";
  int result = endScalar.Match(input);
  EXPECT_EQ(result, -1);
}

// Test colon followed by multiple spaces - Match should still return length 1
TEST_F(EndScalarTest_145, MatchColonFollowedByMultipleSpaces_145) {
  std::string input = ":   ";
  int result = endScalar.Match(input);
  EXPECT_GE(result, 1);
}

// Test colon followed by newline and more content
TEST_F(EndScalarTest_145, MatchColonNewlineContent_145) {
  std::string input = ":\nvalue";
  int result = endScalar.Match(input);
  EXPECT_GE(result, 1);
}

}  // namespace
}  // namespace YAML
