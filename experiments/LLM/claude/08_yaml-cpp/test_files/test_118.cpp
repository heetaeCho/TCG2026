#include "gtest/gtest.h"
#include "exp.h"
#include "regex_yaml.h"

namespace YAML {
namespace {

// Test that Blank() returns a valid RegEx reference
TEST(BlankTest_118, ReturnsValidReference_118) {
  const RegEx& blank = Exp::Blank();
  // Just verify we can obtain the reference without crashing
  (void)blank;
}

// Test that Blank() returns the same object each time (static)
TEST(BlankTest_118, ReturnsSameStaticInstance_118) {
  const RegEx& blank1 = Exp::Blank();
  const RegEx& blank2 = Exp::Blank();
  EXPECT_EQ(&blank1, &blank2);
}

// Test that Blank() matches a space character
TEST(BlankTest_118, MatchesSpace_118) {
  const RegEx& blank = Exp::Blank();
  EXPECT_TRUE(blank.Matches(' '));
}

// Test that Blank() matches a tab character
TEST(BlankTest_118, MatchesTab_118) {
  const RegEx& blank = Exp::Blank();
  EXPECT_TRUE(blank.Matches('\t'));
}

// Test that Blank() does not match a regular letter
TEST(BlankTest_118, DoesNotMatchLetter_118) {
  const RegEx& blank = Exp::Blank();
  EXPECT_FALSE(blank.Matches('a'));
}

// Test that Blank() does not match a digit
TEST(BlankTest_118, DoesNotMatchDigit_118) {
  const RegEx& blank = Exp::Blank();
  EXPECT_FALSE(blank.Matches('0'));
}

// Test that Blank() does not match newline
TEST(BlankTest_118, DoesNotMatchNewline_118) {
  const RegEx& blank = Exp::Blank();
  EXPECT_FALSE(blank.Matches('\n'));
}

// Test that Blank() does not match carriage return
TEST(BlankTest_118, DoesNotMatchCarriageReturn_118) {
  const RegEx& blank = Exp::Blank();
  EXPECT_FALSE(blank.Matches('\r'));
}

// Test that Blank() does not match null character
TEST(BlankTest_118, DoesNotMatchNull_118) {
  const RegEx& blank = Exp::Blank();
  EXPECT_FALSE(blank.Matches('\0'));
}

// Test that Blank() does not match special characters
TEST(BlankTest_118, DoesNotMatchSpecialChars_118) {
  const RegEx& blank = Exp::Blank();
  EXPECT_FALSE(blank.Matches('!'));
  EXPECT_FALSE(blank.Matches('@'));
  EXPECT_FALSE(blank.Matches('#'));
  EXPECT_FALSE(blank.Matches('-'));
  EXPECT_FALSE(blank.Matches('_'));
}

// Test Match with a string starting with space
TEST(BlankTest_118, MatchStringStartingWithSpace_118) {
  const RegEx& blank = Exp::Blank();
  int result = blank.Match(std::string(" hello"));
  EXPECT_EQ(result, 1);
}

// Test Match with a string starting with tab
TEST(BlankTest_118, MatchStringStartingWithTab_118) {
  const RegEx& blank = Exp::Blank();
  int result = blank.Match(std::string("\thello"));
  EXPECT_EQ(result, 1);
}

// Test Match with a string starting with non-blank
TEST(BlankTest_118, MatchStringStartingWithNonBlank_118) {
  const RegEx& blank = Exp::Blank();
  int result = blank.Match(std::string("hello"));
  EXPECT_EQ(result, -1);
}

// Test Match with empty string
TEST(BlankTest_118, MatchEmptyString_118) {
  const RegEx& blank = Exp::Blank();
  int result = blank.Match(std::string(""));
  EXPECT_EQ(result, -1);
}

// Test Matches with string containing only a space
TEST(BlankTest_118, MatchesStringWithOnlySpace_118) {
  const RegEx& blank = Exp::Blank();
  EXPECT_TRUE(blank.Matches(std::string(" ")));
}

// Test Matches with string containing only a tab
TEST(BlankTest_118, MatchesStringWithOnlyTab_118) {
  const RegEx& blank = Exp::Blank();
  EXPECT_TRUE(blank.Matches(std::string("\t")));
}

// Test Matches with a multi-character string (should not match fully)
TEST(BlankTest_118, MatchesMultiCharString_118) {
  const RegEx& blank = Exp::Blank();
  // A blank regex matches a single character, so a multi-char string shouldn't fully match
  EXPECT_FALSE(blank.Matches(std::string("  ")));
}

// Test that Blank does not match vertical tab
TEST(BlankTest_118, DoesNotMatchVerticalTab_118) {
  const RegEx& blank = Exp::Blank();
  EXPECT_FALSE(blank.Matches('\v'));
}

// Test that Blank does not match form feed
TEST(BlankTest_118, DoesNotMatchFormFeed_118) {
  const RegEx& blank = Exp::Blank();
  EXPECT_FALSE(blank.Matches('\f'));
}

}  // namespace
}  // namespace YAML
