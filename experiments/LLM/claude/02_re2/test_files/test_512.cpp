#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"

namespace re2 {

// Test fixture for MaybeConcatString tests via ParseState
class MaybeConcatStringTest_512 : public ::testing::Test {
 protected:
  RegexpStatus status_;
};

// Test: MaybeConcatString returns false when stack is empty (no elements)
TEST_F(MaybeConcatStringTest_512, EmptyStackReturnsFalse_512) {
  Regexp::ParseState ps(Regexp::LikePerl, "test", &status_);
  // Stack is empty, MaybeConcatString should return false
  bool result = ps.MaybeConcatString('a', Regexp::NoParseFlags);
  EXPECT_FALSE(result);
}

// Test: MaybeConcatString returns false when only one element on stack
TEST_F(MaybeConcatStringTest_512, SingleElementStackReturnsFalse_512) {
  Regexp::ParseState ps(Regexp::LikePerl, "ab", &status_);
  ps.PushLiteral('a');
  // Only one element, re2 (down_) would be NULL
  bool result = ps.MaybeConcatString('b', Regexp::LikePerl);
  EXPECT_FALSE(result);
}

// Test: MaybeConcatString returns true when two literals on stack and r >= 0
TEST_F(MaybeConcatStringTest_512, TwoLiteralsWithPositiveR_512) {
  Regexp::ParseState ps(Regexp::LikePerl, "abc", &status_);
  ps.PushLiteral('a');
  ps.PushLiteral('b');
  // Two literals on stack, r >= 0 should return true
  bool result = ps.MaybeConcatString('c', Regexp::LikePerl);
  EXPECT_TRUE(result);
}

// Test: MaybeConcatString returns false when two literals on stack and r < 0
TEST_F(MaybeConcatStringTest_512, TwoLiteralsWithNegativeR_512) {
  Regexp::ParseState ps(Regexp::LikePerl, "ab", &status_);
  ps.PushLiteral('a');
  ps.PushLiteral('b');
  // r < 0 should return false (but still concatenates)
  bool result = ps.MaybeConcatString(-1, Regexp::LikePerl);
  EXPECT_FALSE(result);
}

// Test: MaybeConcatString returns false when top is not literal (e.g., dot)
TEST_F(MaybeConcatStringTest_512, NonLiteralTopReturnsFalse_512) {
  Regexp::ParseState ps(Regexp::LikePerl, "a.", &status_);
  ps.PushLiteral('a');
  ps.PushDot();
  bool result = ps.MaybeConcatString('b', Regexp::LikePerl);
  EXPECT_FALSE(result);
}

// Test: MaybeConcatString returns false when second-from-top is not literal
TEST_F(MaybeConcatStringTest_512, NonLiteralSecondReturnsFalse_512) {
  Regexp::ParseState ps(Regexp::LikePerl, ".a", &status_);
  ps.PushDot();
  ps.PushLiteral('a');
  bool result = ps.MaybeConcatString('b', Regexp::LikePerl);
  EXPECT_FALSE(result);
}

// Test: MaybeConcatString returns false when FoldCase flags differ
TEST_F(MaybeConcatStringTest_512, DifferentFoldCaseReturnsFalse_512) {
  Regexp::ParseState ps(Regexp::LikePerl, "ab", &status_);
  // Push literal with FoldCase
  Regexp* re1 = Regexp::NewLiteral('a', Regexp::FoldCase);
  ps.PushRegexp(re1);
  // Push literal without FoldCase
  Regexp* re2 = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  ps.PushRegexp(re2);
  bool result = ps.MaybeConcatString('c', Regexp::LikePerl);
  EXPECT_FALSE(result);
}

// Test: MaybeConcatString with matching FoldCase flags succeeds
TEST_F(MaybeConcatStringTest_512, MatchingFoldCaseReturnsTrue_512) {
  Regexp::ParseState ps(Regexp::LikePerl, "ab", &status_);
  Regexp* re1 = Regexp::NewLiteral('a', Regexp::FoldCase);
  ps.PushRegexp(re1);
  Regexp* re2 = Regexp::NewLiteral('b', Regexp::FoldCase);
  ps.PushRegexp(re2);
  bool result = ps.MaybeConcatString('c', Regexp::FoldCase);
  EXPECT_TRUE(result);
}

// Integration test: Parse concatenated string and verify via ToString
TEST_F(MaybeConcatStringTest_512, ParseConcatenatedLiterals_512) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  std::string s = re->Dump();
  // "abc" should be parsed as a literal string
  EXPECT_NE(s.find("lit{abc}"), std::string::npos);
  re->Decref();
}

// Integration test: Parse single character
TEST_F(MaybeConcatStringTest_512, ParseSingleLiteral_512) {
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  std::string s = re->Dump();
  EXPECT_NE(s.find("lit{a}"), std::string::npos);
  re->Decref();
}

// Integration test: Parse two characters concatenated
TEST_F(MaybeConcatStringTest_512, ParseTwoLiterals_512) {
  Regexp* re = Regexp::Parse("ab", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  std::string s = re->Dump();
  EXPECT_NE(s.find("lit{ab}"), std::string::npos);
  re->Decref();
}

// Integration test: Alternation prevents concat
TEST_F(MaybeConcatStringTest_512, AlternationDoesNotConcat_512) {
  Regexp* re = Regexp::Parse("a|b", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  std::string s = re->Dump();
  EXPECT_NE(s.find("alt"), std::string::npos);
  re->Decref();
}

// Integration test: Mixed literals and operators
TEST_F(MaybeConcatStringTest_512, MixedLiteralsAndOperators_512) {
  Regexp* re = Regexp::Parse("ab.cd", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  std::string s = re->Dump();
  // Should contain lit{ab} and lit{cd} with dot in between
  EXPECT_NE(s.find("lit{ab}"), std::string::npos);
  EXPECT_NE(s.find("lit{cd}"), std::string::npos);
  re->Decref();
}

// Test: Multiple concat calls building a longer string
TEST_F(MaybeConcatStringTest_512, MultipleConcatsBuildsLongerString_512) {
  Regexp* re = Regexp::Parse("abcdef", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  std::string s = re->Dump();
  EXPECT_NE(s.find("lit{abcdef}"), std::string::npos);
  re->Decref();
}

// Test: FoldCase literals concatenation
TEST_F(MaybeConcatStringTest_512, FoldCaseLiteralsConcatenation_512) {
  Regexp* re = Regexp::Parse("(?i)abc", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  std::string s = re->Dump();
  // With fold case, should still concat the string
  EXPECT_NE(s.find("litfold{abc}"), std::string::npos);
  re->Decref();
}

// Test: Empty regex
TEST_F(MaybeConcatStringTest_512, EmptyRegex_512) {
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test: Pushing a non-literal between two literals prevents concatenation
TEST_F(MaybeConcatStringTest_512, NonLiteralBetweenLiterals_512) {
  Regexp* re = Regexp::Parse("a.b", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  std::string s = re->Dump();
  // Should not concatenate a and b into one string
  EXPECT_EQ(s.find("lit{ab}"), std::string::npos);
  re->Decref();
}

}  // namespace re2
