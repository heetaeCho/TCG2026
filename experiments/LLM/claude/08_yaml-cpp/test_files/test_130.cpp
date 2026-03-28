#include "gtest/gtest.h"
#include "exp.h"
#include "regex_yaml.h"

namespace YAML {
namespace {

// Test fixture for DocIndicator tests
class DocIndicatorTest_130 : public ::testing::Test {
 protected:
  const RegEx& doc_indicator_ = Exp::DocIndicator();
};

// Test that DocIndicator matches the document start indicator "---"
TEST_F(DocIndicatorTest_130, MatchesDocStart_130) {
  EXPECT_TRUE(doc_indicator_.Matches(std::string("---")));
}

// Test that DocIndicator matches the document end indicator "..."
TEST_F(DocIndicatorTest_130, MatchesDocEnd_130) {
  EXPECT_TRUE(doc_indicator_.Matches(std::string("...")));
}

// Test that DocIndicator does not match an empty string
TEST_F(DocIndicatorTest_130, DoesNotMatchEmptyString_130) {
  EXPECT_FALSE(doc_indicator_.Matches(std::string("")));
}

// Test that DocIndicator does not match a single dash
TEST_F(DocIndicatorTest_130, DoesNotMatchSingleDash_130) {
  EXPECT_FALSE(doc_indicator_.Matches(std::string("-")));
}

// Test that DocIndicator does not match two dashes
TEST_F(DocIndicatorTest_130, DoesNotMatchTwoDashes_130) {
  EXPECT_FALSE(doc_indicator_.Matches(std::string("--")));
}

// Test that DocIndicator does not match a single dot
TEST_F(DocIndicatorTest_130, DoesNotMatchSingleDot_130) {
  EXPECT_FALSE(doc_indicator_.Matches(std::string(".")));
}

// Test that DocIndicator does not match two dots
TEST_F(DocIndicatorTest_130, DoesNotMatchTwoDots_130) {
  EXPECT_FALSE(doc_indicator_.Matches(std::string("..")));
}

// Test that DocIndicator does not match random text
TEST_F(DocIndicatorTest_130, DoesNotMatchRandomText_130) {
  EXPECT_FALSE(doc_indicator_.Matches(std::string("abc")));
}

// Test that DocIndicator does not match mixed indicators like "-.."
TEST_F(DocIndicatorTest_130, DoesNotMatchMixedDashDot_130) {
  EXPECT_FALSE(doc_indicator_.Matches(std::string("-..")));
}

// Test that DocIndicator does not match mixed indicators like "..-"
TEST_F(DocIndicatorTest_130, DoesNotMatchMixedDotDash_130) {
  EXPECT_FALSE(doc_indicator_.Matches(std::string("..-")));
}

// Test that DocIndicator does not match "..−" (dot dot dash)
TEST_F(DocIndicatorTest_130, DoesNotMatchDotDotDash_130) {
  EXPECT_FALSE(doc_indicator_.Matches(std::string("..-")));
}

// Test that DocIndicator does not match "--."
TEST_F(DocIndicatorTest_130, DoesNotMatchDashDashDot_130) {
  EXPECT_FALSE(doc_indicator_.Matches(std::string("--.")));
}

// Test that Match returns 3 for "---"
TEST_F(DocIndicatorTest_130, MatchReturnsThreeForDocStart_130) {
  int result = doc_indicator_.Match(std::string("---"));
  EXPECT_EQ(3, result);
}

// Test that Match returns 3 for "..."
TEST_F(DocIndicatorTest_130, MatchReturnsThreeForDocEnd_130) {
  int result = doc_indicator_.Match(std::string("..."));
  EXPECT_EQ(3, result);
}

// Test that Match returns -1 for non-matching string
TEST_F(DocIndicatorTest_130, MatchReturnsNegativeForNonMatch_130) {
  int result = doc_indicator_.Match(std::string("abc"));
  EXPECT_EQ(-1, result);
}

// Test that Match returns -1 for empty string
TEST_F(DocIndicatorTest_130, MatchReturnsNegativeForEmpty_130) {
  int result = doc_indicator_.Match(std::string(""));
  EXPECT_EQ(-1, result);
}

// Test that DocIndicator returns a consistent reference (singleton behavior)
TEST_F(DocIndicatorTest_130, ReturnsSameReference_130) {
  const RegEx& ref1 = Exp::DocIndicator();
  const RegEx& ref2 = Exp::DocIndicator();
  EXPECT_EQ(&ref1, &ref2);
}

// Test that Match returns 3 for "---extra" (matches prefix)
TEST_F(DocIndicatorTest_130, MatchReturnsThreeForDocStartWithTrailing_130) {
  int result = doc_indicator_.Match(std::string("---extra"));
  EXPECT_EQ(3, result);
}

// Test that Match returns 3 for "...extra" (matches prefix)
TEST_F(DocIndicatorTest_130, MatchReturnsThreeForDocEndWithTrailing_130) {
  int result = doc_indicator_.Match(std::string("...extra"));
  EXPECT_EQ(3, result);
}

// Test that DocIndicator does not match four dashes
TEST_F(DocIndicatorTest_130, DoesNotMatchFourDashes_130) {
  // Matches should check exact match; "----" is not exactly "---"
  EXPECT_FALSE(doc_indicator_.Matches(std::string("----")));
}

// Test that DocIndicator does not match four dots
TEST_F(DocIndicatorTest_130, DoesNotMatchFourDots_130) {
  EXPECT_FALSE(doc_indicator_.Matches(std::string("....")));
}

// Test Match returns -1 for partial doc start "--"
TEST_F(DocIndicatorTest_130, MatchReturnsNegativeForPartialDocStart_130) {
  int result = doc_indicator_.Match(std::string("--"));
  EXPECT_EQ(-1, result);
}

// Test Match returns -1 for partial doc end ".."
TEST_F(DocIndicatorTest_130, MatchReturnsNegativeForPartialDocEnd_130) {
  int result = doc_indicator_.Match(std::string(".."));
  EXPECT_EQ(-1, result);
}

// Test that DocIndicator does not match a space-prefixed doc start
TEST_F(DocIndicatorTest_130, DoesNotMatchSpacePrefixedDocStart_130) {
  EXPECT_FALSE(doc_indicator_.Matches(std::string(" ---")));
}

// Test that DocIndicator does not match a space-prefixed doc end
TEST_F(DocIndicatorTest_130, DoesNotMatchSpacePrefixedDocEnd_130) {
  EXPECT_FALSE(doc_indicator_.Matches(std::string(" ...")));
}

}  // namespace
}  // namespace YAML
