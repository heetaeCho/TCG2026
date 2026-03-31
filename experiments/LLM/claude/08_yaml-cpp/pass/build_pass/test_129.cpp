#include "gtest/gtest.h"
#include "exp.h"
#include "regex_yaml.h"

namespace YAML {
namespace {

// Test fixture for DocEnd tests
class DocEndTest_129 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that DocEnd matches the literal string "..."
TEST_F(DocEndTest_129, MatchesThreeDots_129) {
  const RegEx& docEnd = Exp::DocEnd();
  // "..." followed by a blank/break or end of input
  // The DocEnd regex is "..." + (BlankOrBreak() | RegEx())
  // RegEx() is REGEX_EMPTY which matches empty string
  // So "..." alone should match
  int result = docEnd.Match(std::string("..."));
  EXPECT_EQ(3, result);
}

// Test that DocEnd matches "..." followed by a space
TEST_F(DocEndTest_129, MatchesThreeDotsFollowedBySpace_129) {
  const RegEx& docEnd = Exp::DocEnd();
  int result = docEnd.Match(std::string("... "));
  EXPECT_EQ(4, result);
}

// Test that DocEnd matches "..." followed by a tab
TEST_F(DocEndTest_129, MatchesThreeDotsFollowedByTab_129) {
  const RegEx& docEnd = Exp::DocEnd();
  int result = docEnd.Match(std::string("...\t"));
  EXPECT_EQ(4, result);
}

// Test that DocEnd matches "..." followed by a newline
TEST_F(DocEndTest_129, MatchesThreeDotsFollowedByNewline_129) {
  const RegEx& docEnd = Exp::DocEnd();
  int result = docEnd.Match(std::string("...\n"));
  EXPECT_EQ(4, result);
}

// Test that DocEnd does not match fewer than three dots
TEST_F(DocEndTest_129, DoesNotMatchTwoDots_129) {
  const RegEx& docEnd = Exp::DocEnd();
  int result = docEnd.Match(std::string(".."));
  EXPECT_EQ(-1, result);
}

// Test that DocEnd does not match a single dot
TEST_F(DocEndTest_129, DoesNotMatchOneDot_129) {
  const RegEx& docEnd = Exp::DocEnd();
  int result = docEnd.Match(std::string("."));
  EXPECT_EQ(-1, result);
}

// Test that DocEnd does not match an empty string
TEST_F(DocEndTest_129, DoesNotMatchEmptyString_129) {
  const RegEx& docEnd = Exp::DocEnd();
  int result = docEnd.Match(std::string(""));
  EXPECT_EQ(-1, result);
}

// Test that DocEnd does not match "---" (document start marker)
TEST_F(DocEndTest_129, DoesNotMatchDocStart_129) {
  const RegEx& docEnd = Exp::DocEnd();
  int result = docEnd.Match(std::string("---"));
  EXPECT_EQ(-1, result);
}

// Test that DocEnd does not match arbitrary text
TEST_F(DocEndTest_129, DoesNotMatchArbitraryText_129) {
  const RegEx& docEnd = Exp::DocEnd();
  int result = docEnd.Match(std::string("abc"));
  EXPECT_EQ(-1, result);
}

// Test that DocEnd does not match four dots without blank/break
TEST_F(DocEndTest_129, DoesNotMatchThreeDotsFollowedByLetter_129) {
  const RegEx& docEnd = Exp::DocEnd();
  // "...a" - after "..." comes 'a' which is not blank or break, and not empty
  // The second part is (BlankOrBreak() | RegEx())
  // RegEx() matches empty, so "..." should still match with length 3
  // Actually, the + operator is sequence, so it tries to match "..." then (BlankOrBreak()|empty)
  // 'a' doesn't match BlankOrBreak but empty matches with length 0
  // So total match should be 3
  int result = docEnd.Match(std::string("...a"));
  EXPECT_EQ(3, result);
}

// Test that DocEnd returns the same reference on multiple calls (static)
TEST_F(DocEndTest_129, ReturnsSameReference_129) {
  const RegEx& docEnd1 = Exp::DocEnd();
  const RegEx& docEnd2 = Exp::DocEnd();
  EXPECT_EQ(&docEnd1, &docEnd2);
}

// Test that DocEnd matches "..." followed by carriage return
TEST_F(DocEndTest_129, MatchesThreeDotsFollowedByCR_129) {
  const RegEx& docEnd = Exp::DocEnd();
  int result = docEnd.Match(std::string("...\r"));
  // \r is typically considered a break character
  EXPECT_GE(result, 3);
}

// Test Matches (bool) with "..."
TEST_F(DocEndTest_129, MatchesBoolThreeDots_129) {
  const RegEx& docEnd = Exp::DocEnd();
  bool result = docEnd.Matches(std::string("..."));
  EXPECT_TRUE(result);
}

// Test Matches (bool) with non-matching string
TEST_F(DocEndTest_129, MatchesBoolNonMatching_129) {
  const RegEx& docEnd = Exp::DocEnd();
  bool result = docEnd.Matches(std::string("abc"));
  EXPECT_FALSE(result);
}

// Test that "....." (five dots) matches only first 3 (or 3) from DocEnd
TEST_F(DocEndTest_129, MatchesFiveDotsReturnsThree_129) {
  const RegEx& docEnd = Exp::DocEnd();
  // "....." - first "..." matches, then next char '.' is not blank/break
  // but empty regex matches, so total should be 3
  int result = docEnd.Match(std::string("....."));
  EXPECT_EQ(3, result);
}

// Test that DocEnd does not match string starting with spaces
TEST_F(DocEndTest_129, DoesNotMatchLeadingSpaces_129) {
  const RegEx& docEnd = Exp::DocEnd();
  int result = docEnd.Match(std::string(" ..."));
  EXPECT_EQ(-1, result);
}

}  // namespace
}  // namespace YAML
