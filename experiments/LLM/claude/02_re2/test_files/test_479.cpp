#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include "absl/strings/string_view.h"

namespace re2 {

class ParseStateTest_479 : public ::testing::Test {
 protected:
  RegexpStatus status_;
};

// Test that flags() returns the flags passed to the constructor
TEST_F(ParseStateTest_479, FlagsReturnsConstructorFlags_479) {
  Regexp::ParseState ps(Regexp::PerlX, "abc", &status_);
  EXPECT_EQ(ps.flags(), Regexp::PerlX);
}

// Test with different flag values
TEST_F(ParseStateTest_479, FlagsReturnsLatin1Flag_479) {
  Regexp::ParseState ps(Regexp::Latin1, "test", &status_);
  EXPECT_EQ(ps.flags(), Regexp::Latin1);
}

// Test with no flags (zero)
TEST_F(ParseStateTest_479, FlagsReturnsNoFlags_479) {
  Regexp::ParseState ps(Regexp::NoParseFlags, "", &status_);
  EXPECT_EQ(ps.flags(), Regexp::NoParseFlags);
}

// Test with combined flags
TEST_F(ParseStateTest_479, FlagsReturnsCombinedFlags_479) {
  Regexp::ParseFlags combined = static_cast<Regexp::ParseFlags>(
      Regexp::PerlX | Regexp::Latin1);
  Regexp::ParseState ps(combined, "abc", &status_);
  EXPECT_EQ(ps.flags(), combined);
}

// Test PushLiteral with a simple character
TEST_F(ParseStateTest_479, PushLiteralSimpleChar_479) {
  Regexp::ParseState ps(Regexp::PerlX, "a", &status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
}

// Test PushLiteral with multiple characters then DoFinish
TEST_F(ParseStateTest_479, PushLiteralMultipleAndFinish_479) {
  Regexp::ParseState ps(Regexp::PerlX, "ab", &status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushLiteral('b'));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test PushDot
TEST_F(ParseStateTest_479, PushDot_479) {
  Regexp::ParseState ps(Regexp::PerlX, ".", &status_);
  EXPECT_TRUE(ps.PushDot());
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test PushCaret
TEST_F(ParseStateTest_479, PushCaret_479) {
  Regexp::ParseState ps(Regexp::PerlX, "^", &status_);
  EXPECT_TRUE(ps.PushCaret());
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test PushDollar
TEST_F(ParseStateTest_479, PushDollar_479) {
  Regexp::ParseState ps(Regexp::PerlX, "$", &status_);
  EXPECT_TRUE(ps.PushDollar());
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test PushWordBoundary true
TEST_F(ParseStateTest_479, PushWordBoundaryTrue_479) {
  Regexp::ParseState ps(Regexp::PerlX, "\\b", &status_);
  EXPECT_TRUE(ps.PushWordBoundary(true));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test PushWordBoundary false (non-word boundary)
TEST_F(ParseStateTest_479, PushWordBoundaryFalse_479) {
  Regexp::ParseState ps(Regexp::PerlX, "\\B", &status_);
  EXPECT_TRUE(ps.PushWordBoundary(false));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test DoLeftParen and DoRightParen
TEST_F(ParseStateTest_479, ParenthesesGrouping_479) {
  Regexp::ParseState ps(Regexp::PerlX, "(a)", &status_);
  EXPECT_TRUE(ps.DoLeftParen(""));
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.DoRightParen());
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test DoLeftParenNoCapture and DoRightParen
TEST_F(ParseStateTest_479, NoCaptureParentheses_479) {
  Regexp::ParseState ps(Regexp::PerlX, "(?:a)", &status_);
  EXPECT_TRUE(ps.DoLeftParenNoCapture());
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.DoRightParen());
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test DoVerticalBar (alternation)
TEST_F(ParseStateTest_479, Alternation_479) {
  Regexp::ParseState ps(Regexp::PerlX, "a|b", &status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.DoVerticalBar());
  EXPECT_TRUE(ps.PushLiteral('b'));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test PushRepeatOp with star
TEST_F(ParseStateTest_479, PushRepeatOpStar_479) {
  absl::string_view s = "a*";
  Regexp::ParseState ps(Regexp::PerlX, s, &status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushRepeatOp(kRegexpStar, s.substr(1), false));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test PushRepeatOp with plus
TEST_F(ParseStateTest_479, PushRepeatOpPlus_479) {
  absl::string_view s = "a+";
  Regexp::ParseState ps(Regexp::PerlX, s, &status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushRepeatOp(kRegexpPlus, s.substr(1), false));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test PushRepeatOp with quest (optional)
TEST_F(ParseStateTest_479, PushRepeatOpQuest_479) {
  absl::string_view s = "a?";
  Regexp::ParseState ps(Regexp::PerlX, s, &status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushRepeatOp(kRegexpQuest, s.substr(1), false));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test PushRepetition with specific min and max
TEST_F(ParseStateTest_479, PushRepetitionMinMax_479) {
  absl::string_view s = "a{2,5}";
  Regexp::ParseState ps(Regexp::PerlX, s, &status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushRepetition(2, 5, s.substr(1), false));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test PushRepetition with min==max (exact count)
TEST_F(ParseStateTest_479, PushRepetitionExactCount_479) {
  absl::string_view s = "a{3}";
  Regexp::ParseState ps(Regexp::PerlX, s, &status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushRepetition(3, 3, s.substr(1), false));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test PushRepetition nongreedy
TEST_F(ParseStateTest_479, PushRepetitionNongreedy_479) {
  absl::string_view s = "a{2,5}?";
  Regexp::ParseState ps(Regexp::PerlX, s, &status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushRepetition(2, 5, s.substr(1), true));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test DoFinish with empty expression
TEST_F(ParseStateTest_479, DoFinishEmpty_479) {
  Regexp::ParseState ps(Regexp::PerlX, "", &status_);
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test DoRightParen without matching left paren should fail
TEST_F(ParseStateTest_479, UnmatchedRightParen_479) {
  Regexp::ParseState ps(Regexp::PerlX, ")", &status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_FALSE(ps.DoRightParen());
}

// Test named capture group
TEST_F(ParseStateTest_479, NamedCaptureGroup_479) {
  Regexp::ParseState ps(Regexp::PerlX, "(?P<name>a)", &status_);
  EXPECT_TRUE(ps.DoLeftParen("name"));
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.DoRightParen());
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test nested parentheses
TEST_F(ParseStateTest_479, NestedParentheses_479) {
  Regexp::ParseState ps(Regexp::PerlX, "((a))", &status_);
  EXPECT_TRUE(ps.DoLeftParen(""));
  EXPECT_TRUE(ps.DoLeftParen(""));
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.DoRightParen());
  EXPECT_TRUE(ps.DoRightParen());
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test PushRepeatOp nongreedy star
TEST_F(ParseStateTest_479, PushRepeatOpNongreedyStar_479) {
  absl::string_view s = "a*?";
  Regexp::ParseState ps(Regexp::PerlX, s, &status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushRepeatOp(kRegexpStar, s.substr(1), true));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test complex expression: (a|b)*
TEST_F(ParseStateTest_479, ComplexAlternationWithStar_479) {
  absl::string_view s = "(a|b)*";
  Regexp::ParseState ps(Regexp::PerlX, s, &status_);
  EXPECT_TRUE(ps.DoLeftParen(""));
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.DoVerticalBar());
  EXPECT_TRUE(ps.PushLiteral('b'));
  EXPECT_TRUE(ps.DoRightParen());
  EXPECT_TRUE(ps.PushRepeatOp(kRegexpStar, s.substr(5), false));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test PushRepetition with min=0 max=-1 (unbounded)
TEST_F(ParseStateTest_479, PushRepetitionUnbounded_479) {
  absl::string_view s = "a{0,}";
  Regexp::ParseState ps(Regexp::PerlX, s, &status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushRepetition(0, -1, s.substr(1), false));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test multiple alternations
TEST_F(ParseStateTest_479, MultipleAlternations_479) {
  Regexp::ParseState ps(Regexp::PerlX, "a|b|c", &status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.DoVerticalBar());
  EXPECT_TRUE(ps.PushLiteral('b'));
  EXPECT_TRUE(ps.DoVerticalBar());
  EXPECT_TRUE(ps.PushLiteral('c'));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test using Regexp::Parse as a higher-level integration test
TEST_F(ParseStateTest_479, RegexpParseSimple_479) {
  Regexp* re = Regexp::Parse("abc", Regexp::PerlX, &status_);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Regexp::Parse with alternation
TEST_F(ParseStateTest_479, RegexpParseAlternation_479) {
  Regexp* re = Regexp::Parse("a|b", Regexp::PerlX, &status_);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Regexp::Parse with character class
TEST_F(ParseStateTest_479, RegexpParseCharClass_479) {
  Regexp* re = Regexp::Parse("[abc]", Regexp::PerlX, &status_);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Regexp::Parse with character class range
TEST_F(ParseStateTest_479, RegexpParseCharClassRange_479) {
  Regexp* re = Regexp::Parse("[a-z]", Regexp::PerlX, &status_);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Regexp::Parse with negated character class
TEST_F(ParseStateTest_479, RegexpParseNegatedCharClass_479) {
  Regexp* re = Regexp::Parse("[^abc]", Regexp::PerlX, &status_);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Regexp::Parse invalid regex returns null
TEST_F(ParseStateTest_479, RegexpParseInvalid_479) {
  Regexp* re = Regexp::Parse("(", Regexp::PerlX, &status_);
  EXPECT_EQ(re, nullptr);
}

// Test Regexp::Parse invalid regex unmatched right paren
TEST_F(ParseStateTest_479, RegexpParseUnmatchedRightParen_479) {
  Regexp* re = Regexp::Parse(")", Regexp::PerlX, &status_);
  EXPECT_EQ(re, nullptr);
}

// Test Regexp::Parse with repetition
TEST_F(ParseStateTest_479, RegexpParseRepetition_479) {
  Regexp* re = Regexp::Parse("a{3,5}", Regexp::PerlX, &status_);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Regexp::Parse with escape sequences
TEST_F(ParseStateTest_479, RegexpParseEscapeSequences_479) {
  Regexp* re = Regexp::Parse("\\d+", Regexp::PerlX, &status_);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Regexp::Parse with word boundary
TEST_F(ParseStateTest_479, RegexpParseWordBoundary_479) {
  Regexp* re = Regexp::Parse("\\bword\\b", Regexp::PerlX, &status_);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Regexp::Parse empty string
TEST_F(ParseStateTest_479, RegexpParseEmptyString_479) {
  Regexp* re = Regexp::Parse("", Regexp::PerlX, &status_);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test PushSimpleOp
TEST_F(ParseStateTest_479, PushSimpleOpNoWordBoundary_479) {
  Regexp::ParseState ps(Regexp::PerlX, "\\B", &status_);
  EXPECT_TRUE(ps.PushSimpleOp(kRegexpNoWordBoundary));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test MaybeConcatString
TEST_F(ParseStateTest_479, MaybeConcatStringInitiallyFalse_479) {
  Regexp::ParseState ps(Regexp::PerlX, "a", &status_);
  // Before pushing anything, MaybeConcatString should return false
  EXPECT_FALSE(ps.MaybeConcatString('a', Regexp::PerlX));
}

// Test MaybeConcatString after pushing literals
TEST_F(ParseStateTest_479, MaybeConcatStringAfterLiterals_479) {
  Regexp::ParseState ps(Regexp::PerlX, "ab", &status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushLiteral('b'));
  // After two literals, MaybeConcatString should attempt concat
  bool result = ps.MaybeConcatString('c', Regexp::PerlX);
  // The result depends on internal state; we just verify it doesn't crash
  (void)result;
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test PushRepetition with min > max should still work (implementation handles it)
TEST_F(ParseStateTest_479, PushRepetitionMinGreaterThanMax_479) {
  absl::string_view s = "a{5,2}";
  Regexp::ParseState ps(Regexp::PerlX, s, &status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  // This may fail since min > max is invalid
  bool result = ps.PushRepetition(5, 2, s.substr(1), false);
  (void)result;  // Just checking it doesn't crash
}

// Test Regexp::Parse with Perl flags group
TEST_F(ParseStateTest_479, RegexpParsePerlFlags_479) {
  Regexp* re = Regexp::Parse("(?i)abc", Regexp::PerlX, &status_);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Regexp::Parse with named capture
TEST_F(ParseStateTest_479, RegexpParseNamedCapture_479) {
  Regexp* re = Regexp::Parse("(?P<name>abc)", Regexp::PerlX, &status_);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Regexp::Parse with non-capturing group
TEST_F(ParseStateTest_479, RegexpParseNonCapturing_479) {
  Regexp* re = Regexp::Parse("(?:abc)", Regexp::PerlX, &status_);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test flags with FoldCase
TEST_F(ParseStateTest_479, FlagsWithFoldCase_479) {
  Regexp::ParseState ps(Regexp::FoldCase, "abc", &status_);
  EXPECT_EQ(ps.flags() & Regexp::FoldCase, Regexp::FoldCase);
}

}  // namespace re2
