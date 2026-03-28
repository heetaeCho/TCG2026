#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include "absl/strings/string_view.h"

namespace re2 {

// We need access to ParseState which is a nested class inside Regexp.
// We'll use the public Parse interface where possible, and test ParseState
// through Regexp::Parse for integration-level tests.

class ParseStateTest_500 : public ::testing::Test {
 protected:
  RegexpStatus status_;
};

// Test: IsMarker returns false for normal RegexpOps
TEST_F(ParseStateTest_500, IsMarkerReturnsFalseForLiteralOp_500) {
  absl::string_view pattern("abc");
  Regexp::ParseState ps(Regexp::LikePerl, pattern, &status_);
  // kLiteral is a normal op, should not be a marker
  EXPECT_FALSE(ps.IsMarker(kRegexpLiteral));
}

TEST_F(ParseStateTest_500, IsMarkerReturnsFalseForConcatOp_500) {
  absl::string_view pattern("abc");
  Regexp::ParseState ps(Regexp::LikePerl, pattern, &status_);
  EXPECT_FALSE(ps.IsMarker(kRegexpConcat));
}

TEST_F(ParseStateTest_500, IsMarkerReturnsFalseForAlternateOp_500) {
  absl::string_view pattern("abc");
  Regexp::ParseState ps(Regexp::LikePerl, pattern, &status_);
  EXPECT_FALSE(ps.IsMarker(kRegexpAlternate));
}

TEST_F(ParseStateTest_500, IsMarkerReturnsFalseForStarOp_500) {
  absl::string_view pattern("abc");
  Regexp::ParseState ps(Regexp::LikePerl, pattern, &status_);
  EXPECT_FALSE(ps.IsMarker(kRegexpStar));
}

TEST_F(ParseStateTest_500, IsMarkerReturnsTrueForLeftParen_500) {
  absl::string_view pattern("abc");
  Regexp::ParseState ps(Regexp::LikePerl, pattern, &status_);
  // kLeftParen is kMaxRegexpOp + 1, should be a marker
  RegexpOp kLeftParen = static_cast<RegexpOp>(kMaxRegexpOp + 1);
  EXPECT_TRUE(ps.IsMarker(kLeftParen));
}

TEST_F(ParseStateTest_500, IsMarkerReturnsTrueForOpAboveLeftParen_500) {
  absl::string_view pattern("abc");
  Regexp::ParseState ps(Regexp::LikePerl, pattern, &status_);
  RegexpOp aboveLeftParen = static_cast<RegexpOp>(kMaxRegexpOp + 2);
  EXPECT_TRUE(ps.IsMarker(aboveLeftParen));
}

TEST_F(ParseStateTest_500, IsMarkerReturnsFalseForMaxRegexpOp_500) {
  absl::string_view pattern("abc");
  Regexp::ParseState ps(Regexp::LikePerl, pattern, &status_);
  EXPECT_FALSE(ps.IsMarker(kMaxRegexpOp));
}

// Test: flags() returns the flags passed at construction
TEST_F(ParseStateTest_500, FlagsReturnConstructionFlags_500) {
  absl::string_view pattern("abc");
  Regexp::ParseState ps(Regexp::LikePerl, pattern, &status_);
  EXPECT_EQ(ps.flags(), Regexp::LikePerl);
}

TEST_F(ParseStateTest_500, FlagsReturnPOSIXFlags_500) {
  absl::string_view pattern("abc");
  Regexp::ParseState ps(Regexp::PerlX, pattern, &status_);
  EXPECT_EQ(ps.flags(), Regexp::PerlX);
}

// Test: PushLiteral and DoFinish for a single character
TEST_F(ParseStateTest_500, PushLiteralAndFinish_500) {
  absl::string_view pattern("a");
  Regexp::ParseState ps(Regexp::LikePerl, pattern, &status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test: PushDot and DoFinish
TEST_F(ParseStateTest_500, PushDotAndFinish_500) {
  absl::string_view pattern(".");
  Regexp::ParseState ps(Regexp::LikePerl, pattern, &status_);
  EXPECT_TRUE(ps.PushDot());
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test: PushCaret and DoFinish
TEST_F(ParseStateTest_500, PushCaretAndFinish_500) {
  absl::string_view pattern("^");
  Regexp::ParseState ps(Regexp::LikePerl, pattern, &status_);
  EXPECT_TRUE(ps.PushCaret());
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test: PushDollar and DoFinish
TEST_F(ParseStateTest_500, PushDollarAndFinish_500) {
  absl::string_view pattern("$");
  Regexp::ParseState ps(Regexp::LikePerl, pattern, &status_);
  EXPECT_TRUE(ps.PushDollar());
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test: PushWordBoundary (word=true) and DoFinish
TEST_F(ParseStateTest_500, PushWordBoundaryTrueAndFinish_500) {
  absl::string_view pattern("\\b");
  Regexp::ParseState ps(Regexp::LikePerl, pattern, &status_);
  EXPECT_TRUE(ps.PushWordBoundary(true));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test: PushWordBoundary (word=false) and DoFinish
TEST_F(ParseStateTest_500, PushWordBoundaryFalseAndFinish_500) {
  absl::string_view pattern("\\B");
  Regexp::ParseState ps(Regexp::LikePerl, pattern, &status_);
  EXPECT_TRUE(ps.PushWordBoundary(false));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test: Multiple PushLiteral calls create concatenation
TEST_F(ParseStateTest_500, MultipleLiteralsCreateConcat_500) {
  absl::string_view pattern("abc");
  Regexp::ParseState ps(Regexp::LikePerl, pattern, &status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushLiteral('b'));
  EXPECT_TRUE(ps.PushLiteral('c'));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test: DoLeftParen and DoRightParen
TEST_F(ParseStateTest_500, LeftParenRightParen_500) {
  absl::string_view pattern("(a)");
  Regexp::ParseState ps(Regexp::LikePerl, pattern, &status_);
  EXPECT_TRUE(ps.DoLeftParen(absl::string_view()));
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.DoRightParen());
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test: DoLeftParenNoCapture and DoRightParen
TEST_F(ParseStateTest_500, LeftParenNoCaptureRightParen_500) {
  absl::string_view pattern("(?:a)");
  Regexp::ParseState ps(Regexp::LikePerl, pattern, &status_);
  EXPECT_TRUE(ps.DoLeftParenNoCapture());
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.DoRightParen());
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test: DoVerticalBar (alternation)
TEST_F(ParseStateTest_500, VerticalBarCreatesAlternation_500) {
  absl::string_view pattern("a|b");
  Regexp::ParseState ps(Regexp::LikePerl, pattern, &status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.DoVerticalBar());
  EXPECT_TRUE(ps.PushLiteral('b'));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test: PushRepeatOp with star
TEST_F(ParseStateTest_500, PushRepeatOpStar_500) {
  absl::string_view pattern("a*");
  Regexp::ParseState ps(Regexp::LikePerl, pattern, &status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushRepeatOp(kRegexpStar, pattern, false));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test: PushRepeatOp with plus
TEST_F(ParseStateTest_500, PushRepeatOpPlus_500) {
  absl::string_view pattern("a+");
  Regexp::ParseState ps(Regexp::LikePerl, pattern, &status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushRepeatOp(kRegexpPlus, pattern, false));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test: PushRepeatOp with quest (?)
TEST_F(ParseStateTest_500, PushRepeatOpQuest_500) {
  absl::string_view pattern("a?");
  Regexp::ParseState ps(Regexp::LikePerl, pattern, &status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushRepeatOp(kRegexpQuest, pattern, false));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test: PushRepeatOp with nongreedy star
TEST_F(ParseStateTest_500, PushRepeatOpNongreedyStar_500) {
  absl::string_view pattern("a*?");
  Regexp::ParseState ps(Regexp::LikePerl, pattern, &status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushRepeatOp(kRegexpStar, pattern, true));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test: PushRepetition with specific min/max
TEST_F(ParseStateTest_500, PushRepetitionMinMax_500) {
  absl::string_view pattern("a{2,5}");
  Regexp::ParseState ps(Regexp::LikePerl, pattern, &status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushRepetition(2, 5, pattern, false));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test: PushRepetition with exact count
TEST_F(ParseStateTest_500, PushRepetitionExactCount_500) {
  absl::string_view pattern("a{3}");
  Regexp::ParseState ps(Regexp::LikePerl, pattern, &status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushRepetition(3, 3, pattern, false));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test: PushRepetition with min only (unbounded max)
TEST_F(ParseStateTest_500, PushRepetitionMinOnly_500) {
  absl::string_view pattern("a{2,}");
  Regexp::ParseState ps(Regexp::LikePerl, pattern, &status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushRepetition(2, -1, pattern, false));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test: Named capture group
TEST_F(ParseStateTest_500, NamedCaptureGroup_500) {
  absl::string_view pattern("(?P<name>a)");
  Regexp::ParseState ps(Regexp::LikePerl, pattern, &status_);
  EXPECT_TRUE(ps.DoLeftParen(absl::string_view("name")));
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.DoRightParen());
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test: Empty finish (no pushes)
TEST_F(ParseStateTest_500, EmptyFinish_500) {
  absl::string_view pattern("");
  Regexp::ParseState ps(Regexp::LikePerl, pattern, &status_);
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test: Complex expression: (a|b)*
TEST_F(ParseStateTest_500, ComplexExpression_500) {
  absl::string_view pattern("(a|b)*");
  Regexp::ParseState ps(Regexp::LikePerl, pattern, &status_);
  EXPECT_TRUE(ps.DoLeftParen(absl::string_view()));
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.DoVerticalBar());
  EXPECT_TRUE(ps.PushLiteral('b'));
  EXPECT_TRUE(ps.DoRightParen());
  EXPECT_TRUE(ps.PushRepeatOp(kRegexpStar, pattern, false));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test: DoRightParen without matching left paren should fail
TEST_F(ParseStateTest_500, UnmatchedRightParen_500) {
  absl::string_view pattern(")");
  Regexp::ParseState ps(Regexp::LikePerl, pattern, &status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  // DoRightParen without a matching DoLeftParen should return false
  EXPECT_FALSE(ps.DoRightParen());
}

// Test: Nested parentheses
TEST_F(ParseStateTest_500, NestedParentheses_500) {
  absl::string_view pattern("((a))");
  Regexp::ParseState ps(Regexp::LikePerl, pattern, &status_);
  EXPECT_TRUE(ps.DoLeftParen(absl::string_view()));
  EXPECT_TRUE(ps.DoLeftParen(absl::string_view()));
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.DoRightParen());
  EXPECT_TRUE(ps.DoRightParen());
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test: PushSimpleOp
TEST_F(ParseStateTest_500, PushSimpleOp_500) {
  absl::string_view pattern(".");
  Regexp::ParseState ps(Regexp::LikePerl, pattern, &status_);
  EXPECT_TRUE(ps.PushSimpleOp(kRegexpAnyChar));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test: Multiple alternations a|b|c
TEST_F(ParseStateTest_500, MultipleAlternations_500) {
  absl::string_view pattern("a|b|c");
  Regexp::ParseState ps(Regexp::LikePerl, pattern, &status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.DoVerticalBar());
  EXPECT_TRUE(ps.PushLiteral('b'));
  EXPECT_TRUE(ps.DoVerticalBar());
  EXPECT_TRUE(ps.PushLiteral('c'));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test: rune_max returns a reasonable value
TEST_F(ParseStateTest_500, RuneMaxReturnsValue_500) {
  absl::string_view pattern("a");
  Regexp::ParseState ps(Regexp::LikePerl, pattern, &status_);
  int rm = ps.rune_max();
  // rune_max should be a positive value (Unicode max or Latin1 max)
  EXPECT_GT(rm, 0);
}

// Test: Integration test via Regexp::Parse for simple pattern
TEST_F(ParseStateTest_500, RegexpParseSimplePattern_500) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Integration test via Regexp::Parse for alternation
TEST_F(ParseStateTest_500, RegexpParseAlternation_500) {
  Regexp* re = Regexp::Parse("a|b|c", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Integration test via Regexp::Parse for character class
TEST_F(ParseStateTest_500, RegexpParseCharClass_500) {
  Regexp* re = Regexp::Parse("[a-z]", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Integration test via Regexp::Parse for negated character class
TEST_F(ParseStateTest_500, RegexpParseNegatedCharClass_500) {
  Regexp* re = Regexp::Parse("[^a-z]", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Integration test via Regexp::Parse for repetition
TEST_F(ParseStateTest_500, RegexpParseRepetition_500) {
  Regexp* re = Regexp::Parse("a{3,5}", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Integration test via Regexp::Parse for invalid pattern
TEST_F(ParseStateTest_500, RegexpParseInvalidPattern_500) {
  Regexp* re = Regexp::Parse("(", Regexp::LikePerl, &status_);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status_.ok());
}

// Test: Integration test via Regexp::Parse for unmatched right paren
TEST_F(ParseStateTest_500, RegexpParseUnmatchedRightParen_500) {
  Regexp* re = Regexp::Parse(")", Regexp::LikePerl, &status_);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status_.ok());
}

// Test: Integration test via Regexp::Parse for empty pattern
TEST_F(ParseStateTest_500, RegexpParseEmptyPattern_500) {
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Integration test for Perl flags (?i)
TEST_F(ParseStateTest_500, RegexpParsePerlFlags_500) {
  Regexp* re = Regexp::Parse("(?i)abc", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Integration test for named group
TEST_F(ParseStateTest_500, RegexpParseNamedGroup_500) {
  Regexp* re = Regexp::Parse("(?P<name>abc)", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Integration test for complex nested pattern
TEST_F(ParseStateTest_500, RegexpParseComplexNested_500) {
  Regexp* re = Regexp::Parse("((a+)|(b*))+", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Integration test for dot star
TEST_F(ParseStateTest_500, RegexpParseDotStar_500) {
  Regexp* re = Regexp::Parse(".*", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Integration test for bad repetition pattern
TEST_F(ParseStateTest_500, RegexpParseBadRepetition_500) {
  Regexp* re = Regexp::Parse("*", Regexp::LikePerl, &status_);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status_.ok());
}

// Test: Integration test for escape sequences
TEST_F(ParseStateTest_500, RegexpParseEscapeSequences_500) {
  Regexp* re = Regexp::Parse("\\d+\\w*\\s?", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: MaybeConcatString with same flags
TEST_F(ParseStateTest_500, MaybeConcatStringBasic_500) {
  absl::string_view pattern("ab");
  Regexp::ParseState ps(Regexp::LikePerl, pattern, &status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  // MaybeConcatString tries to merge the current literal
  // The return value depends on internal state
  bool result = ps.MaybeConcatString('a', Regexp::LikePerl);
  // We just verify it doesn't crash; result depends on state
  (void)result;
}

// Test: FinishRegexp with nullptr
TEST_F(ParseStateTest_500, FinishRegexpWithNull_500) {
  absl::string_view pattern("a");
  Regexp::ParseState ps(Regexp::LikePerl, pattern, &status_);
  Regexp* result = ps.FinishRegexp(nullptr);
  // FinishRegexp(NULL) should return NULL
  EXPECT_EQ(result, nullptr);
}

// Test: Large repetition count
TEST_F(ParseStateTest_500, RegexpParseLargeRepetition_500) {
  Regexp* re = Regexp::Parse("a{1000}", Regexp::LikePerl, &status_);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Unicode literal
TEST_F(ParseStateTest_500, PushUnicodeLiteral_500) {
  absl::string_view pattern("é");
  Regexp::ParseState ps(Regexp::LikePerl, pattern, &status_);
  EXPECT_TRUE(ps.PushLiteral(0x00E9));  // é
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

}  // namespace re2
