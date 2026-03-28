#include "gtest/gtest.h"
#include "exp.h"
#include "regex_yaml.h"

namespace YAML {
namespace {

// =============================================================================
// Tests for DocStart() regex
// =============================================================================

class DocStartTest_128 : public ::testing::Test {
 protected:
  const RegEx& doc_start_ = Exp::DocStart();
};

// Normal operation: "---" followed by a space should match
TEST_F(DocStartTest_128, MatchesDocStartWithSpace_128) {
  EXPECT_TRUE(doc_start_.Matches("--- "));
}

// Normal operation: "---" followed by a newline should match
TEST_F(DocStartTest_128, MatchesDocStartWithNewline_128) {
  EXPECT_TRUE(doc_start_.Matches("---\n"));
}

// Normal operation: "---" followed by a tab should match
TEST_F(DocStartTest_128, MatchesDocStartWithTab_128) {
  EXPECT_TRUE(doc_start_.Matches("---\t"));
}

// Normal operation: "---" followed by carriage return should match
TEST_F(DocStartTest_128, MatchesDocStartWithCarriageReturn_128) {
  EXPECT_TRUE(doc_start_.Matches("---\r"));
}

// Bare "---" with nothing after (end of input) should match
TEST_F(DocStartTest_128, MatchesDocStartAtEndOfInput_128) {
  // "---" followed by nothing — the RegEx() (empty) alternative should match
  EXPECT_TRUE(doc_start_.Matches("---"));
}

// Error/boundary: Only two dashes should not match
TEST_F(DocStartTest_128, DoesNotMatchTwoDashes_128) {
  EXPECT_FALSE(doc_start_.Matches("--"));
}

// Error/boundary: Single dash should not match
TEST_F(DocStartTest_128, DoesNotMatchSingleDash_128) {
  EXPECT_FALSE(doc_start_.Matches("-"));
}

// Error/boundary: Empty string should not match
TEST_F(DocStartTest_128, DoesNotMatchEmptyString_128) {
  EXPECT_FALSE(doc_start_.Matches(""));
}

// Error case: "---" followed by a non-blank character should not match
TEST_F(DocStartTest_128, DoesNotMatchDocStartFollowedByAlpha_128) {
  EXPECT_FALSE(doc_start_.Matches("---a"));
}

// Error case: "---" followed by a digit should not match
TEST_F(DocStartTest_128, DoesNotMatchDocStartFollowedByDigit_128) {
  EXPECT_FALSE(doc_start_.Matches("---1"));
}

// Error case: Four dashes is not a doc start (the 4th char is '-', not blank/break)
TEST_F(DocStartTest_128, DoesNotMatchFourDashes_128) {
  EXPECT_FALSE(doc_start_.Matches("----"));
}

// Error case: Completely different string
TEST_F(DocStartTest_128, DoesNotMatchRandomString_128) {
  EXPECT_FALSE(doc_start_.Matches("hello"));
}

// Error case: "..." is doc end, not doc start
TEST_F(DocStartTest_128, DoesNotMatchDocEnd_128) {
  EXPECT_FALSE(doc_start_.Matches("..."));
}

// Match length tests using Match()
TEST_F(DocStartTest_128, MatchReturnsCorrectLengthForDocStartWithSpace_128) {
  int result = doc_start_.Match("--- ");
  EXPECT_EQ(result, 4);
}

TEST_F(DocStartTest_128, MatchReturnsCorrectLengthForBareDocStart_128) {
  int result = doc_start_.Match("---");
  EXPECT_EQ(result, 3);
}

TEST_F(DocStartTest_128, MatchReturnsCorrectLengthForDocStartWithNewline_128) {
  int result = doc_start_.Match("---\n");
  EXPECT_EQ(result, 4);
}

TEST_F(DocStartTest_128, MatchReturnsNegativeForNonMatch_128) {
  int result = doc_start_.Match("--");
  EXPECT_EQ(result, -1);
}

TEST_F(DocStartTest_128, MatchReturnsNegativeForEmpty_128) {
  int result = doc_start_.Match("");
  EXPECT_EQ(result, -1);
}

TEST_F(DocStartTest_128, MatchReturnsNegativeForDocStartFollowedByAlpha_128) {
  int result = doc_start_.Match("---x");
  EXPECT_EQ(result, -1);
}

// Verify DocStart() returns the same static instance each time (singleton)
TEST_F(DocStartTest_128, ReturnsSameInstance_128) {
  const RegEx& first = Exp::DocStart();
  const RegEx& second = Exp::DocStart();
  EXPECT_EQ(&first, &second);
}

// Boundary: String starting with spaces then "---"
TEST_F(DocStartTest_128, DoesNotMatchLeadingSpaceBeforeDashes_128) {
  EXPECT_FALSE(doc_start_.Matches(" ---"));
}

// Boundary: Only whitespace
TEST_F(DocStartTest_128, DoesNotMatchOnlyWhitespace_128) {
  EXPECT_FALSE(doc_start_.Matches("   "));
}

}  // namespace
}  // namespace YAML
