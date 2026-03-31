#include "gtest/gtest.h"
#include "exp.h"
#include "regex_yaml.h"

namespace YAML {
namespace {

class ScanScalarEndInFlowTest_147 : public ::testing::Test {
 protected:
  const RegEx& regex_ = Exp::ScanScalarEndInFlow();
};

// Test that the function returns a valid reference (doesn't crash)
TEST_F(ScanScalarEndInFlowTest_147, ReturnsValidReference_147) {
  const RegEx& ref = Exp::ScanScalarEndInFlow();
  // Just verifying it doesn't crash and returns something
  (void)ref;
}

// Test that calling it multiple times returns the same static object
TEST_F(ScanScalarEndInFlowTest_147, ReturnsSameStaticObject_147) {
  const RegEx& ref1 = Exp::ScanScalarEndInFlow();
  const RegEx& ref2 = Exp::ScanScalarEndInFlow();
  EXPECT_EQ(&ref1, &ref2);
}

// Test that flow scalar end characters match (comma is a flow indicator)
TEST_F(ScanScalarEndInFlowTest_147, MatchesComma_147) {
  EXPECT_TRUE(regex_.Matches(','));
}

// Test that flow scalar end characters match ([ is a flow indicator)
TEST_F(ScanScalarEndInFlowTest_147, MatchesOpenBracket_147) {
  EXPECT_TRUE(regex_.Matches('['));
}

// Test that flow scalar end characters match (] is a flow indicator)
TEST_F(ScanScalarEndInFlowTest_147, MatchesCloseBracket_147) {
  EXPECT_TRUE(regex_.Matches(']'));
}

// Test that flow scalar end characters match ({ is a flow indicator)
TEST_F(ScanScalarEndInFlowTest_147, MatchesOpenBrace_147) {
  EXPECT_TRUE(regex_.Matches('{'));
}

// Test that flow scalar end characters match (} is a flow indicator)
TEST_F(ScanScalarEndInFlowTest_147, MatchesCloseBrace_147) {
  EXPECT_TRUE(regex_.Matches('}'));
}

// Test that colon matches (end of scalar in flow)
TEST_F(ScanScalarEndInFlowTest_147, MatchesColon_147) {
  // Colon is typically an EndScalarInFlow character
  EXPECT_TRUE(regex_.Matches(':'));
}

// Test that regular alphanumeric characters do not match
TEST_F(ScanScalarEndInFlowTest_147, DoesNotMatchAlpha_147) {
  EXPECT_FALSE(regex_.Matches('a'));
}

TEST_F(ScanScalarEndInFlowTest_147, DoesNotMatchDigit_147) {
  EXPECT_FALSE(regex_.Matches('5'));
}

TEST_F(ScanScalarEndInFlowTest_147, DoesNotMatchDot_147) {
  EXPECT_FALSE(regex_.Matches('.'));
}

TEST_F(ScanScalarEndInFlowTest_147, DoesNotMatchDash_147) {
  EXPECT_FALSE(regex_.Matches('-'));
}

TEST_F(ScanScalarEndInFlowTest_147, DoesNotMatchUnderscore_147) {
  EXPECT_FALSE(regex_.Matches('_'));
}

// Test string matching for blank+comment pattern (space followed by #)
TEST_F(ScanScalarEndInFlowTest_147, MatchesSpaceComment_147) {
  std::string input = " #";
  int result = regex_.Match(input);
  EXPECT_GE(result, 1);
}

// Test string matching for tab+comment pattern
TEST_F(ScanScalarEndInFlowTest_147, MatchesTabComment_147) {
  std::string input = "\t#";
  int result = regex_.Match(input);
  EXPECT_GE(result, 1);
}

// Test that a hash alone without preceding blank doesn't match the comment part
TEST_F(ScanScalarEndInFlowTest_147, HashAloneDoesNotMatch_147) {
  EXPECT_FALSE(regex_.Matches('#'));
}

// Test empty string doesn't match
TEST_F(ScanScalarEndInFlowTest_147, EmptyStringDoesNotMatch_147) {
  std::string input = "";
  int result = regex_.Match(input);
  EXPECT_LE(result, 0);
}

// Test that string starting with comma matches
TEST_F(ScanScalarEndInFlowTest_147, StringStartingWithCommaMatches_147) {
  std::string input = ",value";
  int result = regex_.Match(input);
  EXPECT_GE(result, 1);
}

// Test that string starting with close brace matches
TEST_F(ScanScalarEndInFlowTest_147, StringStartingWithCloseBraceMatches_147) {
  std::string input = "}";
  int result = regex_.Match(input);
  EXPECT_GE(result, 1);
}

// Test that a regular word doesn't match
TEST_F(ScanScalarEndInFlowTest_147, RegularWordDoesNotMatch_147) {
  std::string input = "hello";
  int result = regex_.Match(input);
  EXPECT_LE(result, 0);
}

// Test newline followed by comment (blank or break + comment)
TEST_F(ScanScalarEndInFlowTest_147, MatchesNewlineComment_147) {
  std::string input = "\n#";
  int result = regex_.Match(input);
  // Newline is a "break" character, so this should match BlankOrBreak + Comment
  EXPECT_GE(result, 1);
}

}  // namespace
}  // namespace YAML
