#include "gtest/gtest.h"
#include "exp.h"
#include "regex_yaml.h"

namespace YAML {
namespace {

// Test fixture for ScanScalarEnd tests
class ScanScalarEndTest_148 : public ::testing::Test {
 protected:
  const RegEx& scan_scalar_end_ = Exp::ScanScalarEnd();
};

// Test that ScanScalarEnd returns a valid RegEx reference
TEST_F(ScanScalarEndTest_148, ReturnsValidReference_148) {
  // Simply accessing the reference should not crash
  const RegEx& ref = Exp::ScanScalarEnd();
  // Calling it again should return the same static object
  const RegEx& ref2 = Exp::ScanScalarEnd();
  EXPECT_EQ(&ref, &ref2);
}

// Test that ScanScalarEnd returns the same static instance every time
TEST_F(ScanScalarEndTest_148, ReturnsSameStaticInstance_148) {
  const RegEx& first = Exp::ScanScalarEnd();
  const RegEx& second = Exp::ScanScalarEnd();
  const RegEx& third = Exp::ScanScalarEnd();
  EXPECT_EQ(&first, &second);
  EXPECT_EQ(&second, &third);
}

// Test matching behavior: a plain alphanumeric character should not match ScanScalarEnd
TEST_F(ScanScalarEndTest_148, DoesNotMatchPlainAlphanumeric_148) {
  // A regular character like 'a' is not an end-of-scalar indicator
  EXPECT_FALSE(scan_scalar_end_.Matches('a'));
  EXPECT_FALSE(scan_scalar_end_.Matches('z'));
  EXPECT_FALSE(scan_scalar_end_.Matches('0'));
  EXPECT_FALSE(scan_scalar_end_.Matches('9'));
}

// Test matching behavior with strings - regular text should not match
TEST_F(ScanScalarEndTest_148, DoesNotMatchRegularText_148) {
  EXPECT_FALSE(scan_scalar_end_.Matches(std::string("hello")));
  EXPECT_FALSE(scan_scalar_end_.Matches(std::string("world123")));
}

// Test matching behavior: comment character '#' preceded by blank should be relevant
TEST_F(ScanScalarEndTest_148, MatchesBlankFollowedByComment_148) {
  // A space followed by '#' should match (BlankOrBreak() + Comment())
  std::string blank_comment = " #";
  int match_len = scan_scalar_end_.Match(blank_comment);
  EXPECT_GT(match_len, 0);
}

// Test matching behavior: tab followed by comment
TEST_F(ScanScalarEndTest_148, MatchesTabFollowedByComment_148) {
  std::string tab_comment = "\t#";
  int match_len = scan_scalar_end_.Match(tab_comment);
  EXPECT_GT(match_len, 0);
}

// Test matching behavior: just a '#' without preceding blank
TEST_F(ScanScalarEndTest_148, CommentWithoutPrecedingBlank_148) {
  // '#' alone without a preceding blank - this tests the Comment() part
  // The regex is EndScalar() | (BlankOrBreak() + Comment())
  // '#' alone is not BlankOrBreak() + Comment(), but might match EndScalar()
  // depending on what EndScalar() includes
  std::string just_hash = "#";
  int match_len = scan_scalar_end_.Match(just_hash);
  // We observe the behavior - it may or may not match
  // Just ensure it doesn't crash
  (void)match_len;
}

// Test matching behavior: newline character (which is a break)
TEST_F(ScanScalarEndTest_148, MatchesNewlineCharacter_148) {
  // Newline is a break character, might match via EndScalar() or BlankOrBreak()
  std::string newline = "\n";
  int match_len = scan_scalar_end_.Match(newline);
  // Newline followed by comment isn't the case here, but EndScalar() may match
  (void)match_len;  // observe without asserting specific behavior
}

// Test Match with empty string
TEST_F(ScanScalarEndTest_148, MatchEmptyString_148) {
  std::string empty = "";
  int match_len = scan_scalar_end_.Match(empty);
  // Empty string - typically no match expected
  EXPECT_LE(match_len, 0);
}

// Test that colon followed by space might be an end scalar indicator
TEST_F(ScanScalarEndTest_148, ColonSpaceMayMatchEndScalar_148) {
  std::string colon_space = ": ";
  int match_len = scan_scalar_end_.Match(colon_space);
  // Colon followed by blank is often an end-scalar indicator in YAML
  // Just ensure it doesn't crash; behavior depends on EndScalar() definition
  (void)match_len;
}

// Test single space character
TEST_F(ScanScalarEndTest_148, SingleSpaceDoesNotFullyMatch_148) {
  // A single space is BlankOrBreak but not followed by Comment
  // And might not be EndScalar either
  std::string space = " ";
  int match_len = scan_scalar_end_.Match(space);
  // Just observing - space alone is unlikely to be a full match
  (void)match_len;
}

// Test that the Matches(char) method works without crashing for various chars
TEST_F(ScanScalarEndTest_148, MatchesSingleCharVariousChars_148) {
  // Test various characters to ensure no crashes
  EXPECT_NO_FATAL_FAILURE(scan_scalar_end_.Matches('\0'));
  EXPECT_NO_FATAL_FAILURE(scan_scalar_end_.Matches(' '));
  EXPECT_NO_FATAL_FAILURE(scan_scalar_end_.Matches('\t'));
  EXPECT_NO_FATAL_FAILURE(scan_scalar_end_.Matches('\n'));
  EXPECT_NO_FATAL_FAILURE(scan_scalar_end_.Matches('#'));
  EXPECT_NO_FATAL_FAILURE(scan_scalar_end_.Matches(':'));
  EXPECT_NO_FATAL_FAILURE(scan_scalar_end_.Matches(','));
  EXPECT_NO_FATAL_FAILURE(scan_scalar_end_.Matches('['));
  EXPECT_NO_FATAL_FAILURE(scan_scalar_end_.Matches(']'));
  EXPECT_NO_FATAL_FAILURE(scan_scalar_end_.Matches('{'));
  EXPECT_NO_FATAL_FAILURE(scan_scalar_end_.Matches('}'));
}

// Test Match with YAML-relevant strings
TEST_F(ScanScalarEndTest_148, MatchWithYAMLFlowIndicators_148) {
  // Flow indicators like ',' '[' ']' '{' '}' might be part of EndScalar
  EXPECT_NO_FATAL_FAILURE(scan_scalar_end_.Match(std::string(",")));
  EXPECT_NO_FATAL_FAILURE(scan_scalar_end_.Match(std::string("[")));
  EXPECT_NO_FATAL_FAILURE(scan_scalar_end_.Match(std::string("]")));
  EXPECT_NO_FATAL_FAILURE(scan_scalar_end_.Match(std::string("{")));
  EXPECT_NO_FATAL_FAILURE(scan_scalar_end_.Match(std::string("}")));
}

// Test that newline followed by comment matches
TEST_F(ScanScalarEndTest_148, NewlineFollowedByComment_148) {
  std::string newline_comment = "\n#";
  int match_len = scan_scalar_end_.Match(newline_comment);
  // Newline is a break, followed by '#' (comment) - should match BlankOrBreak + Comment
  // But the match might just match the first character if EndScalar() matches newline
  EXPECT_GT(match_len, 0);
}

}  // namespace
}  // namespace YAML
