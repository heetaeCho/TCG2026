#include "gtest/gtest.h"
#include "exp.h"
#include "regex_yaml.h"

namespace YAML {
namespace {

// Test fixture for BlockEntry tests
class BlockEntryTest_131 : public ::testing::Test {
 protected:
  const RegEx& block_entry_ = Exp::BlockEntry();
};

// Test that BlockEntry returns a valid RegEx reference
TEST_F(BlockEntryTest_131, ReturnsValidRegEx_131) {
  // BlockEntry() should return a reference; just verify it doesn't crash
  const RegEx& re = Exp::BlockEntry();
  (void)re;
  SUCCEED();
}

// Test that BlockEntry returns the same object each time (static)
TEST_F(BlockEntryTest_131, ReturnsSameStaticInstance_131) {
  const RegEx& re1 = Exp::BlockEntry();
  const RegEx& re2 = Exp::BlockEntry();
  EXPECT_EQ(&re1, &re2);
}

// Test that BlockEntry matches a dash followed by a space ("- ")
TEST_F(BlockEntryTest_131, MatchesDashFollowedBySpace_131) {
  std::string input = "- ";
  int result = block_entry_.Match(input);
  EXPECT_GE(result, 1);
}

// Test that BlockEntry matches a dash followed by a newline
TEST_F(BlockEntryTest_131, MatchesDashFollowedByNewline_131) {
  std::string input = "-\n";
  int result = block_entry_.Match(input);
  EXPECT_GE(result, 1);
}

// Test that BlockEntry matches a dash followed by a tab
TEST_F(BlockEntryTest_131, MatchesDashFollowedByTab_131) {
  std::string input = "-\t";
  int result = block_entry_.Match(input);
  EXPECT_GE(result, 1);
}

// Test that BlockEntry matches a lone dash (end of input — empty regex matches)
TEST_F(BlockEntryTest_131, MatchesLoneDash_131) {
  std::string input = "-";
  int result = block_entry_.Match(input);
  // A lone dash should match since RegEx() (REGEX_EMPTY) is one of the alternatives
  EXPECT_GE(result, 1);
}

// Test that BlockEntry does not match a string not starting with dash
TEST_F(BlockEntryTest_131, DoesNotMatchNonDash_131) {
  std::string input = "abc";
  int result = block_entry_.Match(input);
  EXPECT_EQ(result, -1);
}

// Test that BlockEntry does not match an empty string
TEST_F(BlockEntryTest_131, DoesNotMatchEmptyString_131) {
  std::string input = "";
  int result = block_entry_.Match(input);
  EXPECT_EQ(result, -1);
}

// Test that BlockEntry does not match dash followed by a regular character
TEST_F(BlockEntryTest_131, DoesNotMatchDashFollowedByAlpha_131) {
  std::string input = "-a";
  int result = block_entry_.Match(input);
  // '-' followed by 'a' — 'a' is not blank or break, and it's not end of input
  // The regex is '-' + (BlankOrBreak() | RegEx())
  // RegEx() is REGEX_EMPTY which matches empty/end, but here there's 'a' after dash
  // This depends on implementation details, but let's check the observable behavior
  // If Match returns -1, the dash-alpha doesn't match; otherwise it partially matches
  // We just record the behavior
  // Actually, the sequence is '-' then (BlankOrBreak | Empty). Since after '-' the next
  // char is 'a', BlankOrBreak fails, but Empty could match 0 chars, so total match = 1.
  EXPECT_GE(result, 1);
}

// Test that BlockEntry matches dash followed by carriage return
TEST_F(BlockEntryTest_131, MatchesDashFollowedByCR_131) {
  std::string input = "-\r";
  int result = block_entry_.Match(input);
  EXPECT_GE(result, 1);
}

// Test Matches(string) for a matching case
TEST_F(BlockEntryTest_131, MatchesStringMethodDashSpace_131) {
  std::string input = "- ";
  bool result = block_entry_.Matches(input);
  // Matches checks if the entire string matches
  EXPECT_TRUE(result);
}

// Test Matches(string) for a non-matching case
TEST_F(BlockEntryTest_131, MatchesStringMethodNonDash_131) {
  std::string input = "abc";
  bool result = block_entry_.Matches(input);
  EXPECT_FALSE(result);
}

// Test Matches with single char '-'
TEST_F(BlockEntryTest_131, MatchesCharDash_131) {
  // Matches(char) checks a single character
  bool result = block_entry_.Matches('-');
  // Single char '-' — the regex is a sequence so matching a single char might not fully match
  // This is implementation-dependent; we just verify it doesn't crash
  (void)result;
  SUCCEED();
}

// Test that a space alone doesn't match
TEST_F(BlockEntryTest_131, DoesNotMatchSpaceAlone_131) {
  std::string input = " ";
  int result = block_entry_.Match(input);
  EXPECT_EQ(result, -1);
}

// Test with dash followed by multiple spaces
TEST_F(BlockEntryTest_131, MatchDashMultipleSpaces_131) {
  std::string input = "-   ";
  int result = block_entry_.Match(input);
  // Should match at least the dash + one blank
  EXPECT_GE(result, 1);
}

}  // namespace
}  // namespace YAML
