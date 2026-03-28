#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include "absl/strings/string_view.h"

namespace re2 {

class ParseStateTest_480 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that rune_max() returns the expected value based on Latin1 flags
TEST_F(ParseStateTest_480, RuneMaxLatin1_480) {
  RegexpStatus status;
  absl::string_view pattern("abc");
  Regexp::ParseState ps(Regexp::Latin1, pattern, &status);
  EXPECT_EQ(ps.rune_max(), 0xFF);
}

// Test that rune_max() returns the expected value for non-Latin1 (Unicode) flags
TEST_F(ParseStateTest_480, RuneMaxUnicode_480) {
  RegexpStatus status;
  absl::string_view pattern("abc");
  Regexp::ParseState ps(Regexp::PerlX, pattern, &status);
  EXPECT_EQ(ps.rune_max(), Runemax);
}

// Test flags() accessor
TEST_F(ParseStateTest_480, FlagsAccessor_480) {
  RegexpStatus status;
  absl::string_view pattern("test");
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(Regexp::PerlX | Regexp::OneLine);
  Regexp::ParseState ps(flags, pattern, &status);
  EXPECT_EQ(ps.flags(), flags);
}

// Test PushLiteral and DoFinish for a simple literal
TEST_F(ParseStateTest_480, PushLiteralAndFinish_480) {
  RegexpStatus status;
  absl::string_view pattern("a");
  Regexp::ParseState ps(Regexp::PerlX, pattern, &status);
  EXPECT_TRUE(ps.PushLiteral('a'));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test PushDot and DoFinish
TEST_F(ParseStateTest_480, PushDotAndFinish_480) {
  RegexpStatus status;
  absl::string_view pattern(".");
  Regexp::ParseState ps(Regexp::PerlX, pattern, &status);
  EXPECT_TRUE(ps.PushDot());
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test PushCaret and DoFinish
TEST_F(ParseStateTest_480, PushCaretAndFinish_480) {
  RegexpStatus status;
  absl::string_view pattern("^");
  Regexp::ParseState ps(Regexp::PerlX, pattern, &status);
  EXPECT_TRUE(ps.PushCaret());
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test PushDollar and DoFinish
TEST_F(ParseStateTest_480, PushDollarAndFinish_480) {
  RegexpStatus status;
  absl::string_view pattern("$");
  Regexp::ParseState ps(Regexp::PerlX, pattern, &status);
  EXPECT_TRUE(ps.PushDollar());
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test PushWordBoundary (word=true) and DoFinish
TEST_F(ParseStateTest_480, PushWordBoundaryTrue_480) {
  RegexpStatus status;
  absl::string_view pattern("\\b");
  Regexp::ParseState ps(Regexp::PerlX, pattern, &status);
  EXPECT_TRUE(ps.PushWordBoundary(true));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test PushWordBoundary (word=false) and DoFinish
TEST_F(ParseStateTest_480, PushWordBoundaryFalse_480) {
  RegexpStatus status;
  absl::string_view pattern("\\B");
  Regexp::ParseState ps(Regexp::PerlX, pattern, &status);
  EXPECT_TRUE(ps.PushWordBoundary(false));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test concatenation of two literals
TEST_F(ParseStateTest_480, ConcatenationOfLiterals_480) {
  RegexpStatus status;
  absl::string_view pattern("ab");
  Regexp::ParseState ps(Regexp::PerlX, pattern, &status);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushLiteral('b'));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test alternation via DoLeftParen, DoVerticalBar, DoRightParen
TEST_F(ParseStateTest_480, AlternationWithParens_480) {
  RegexpStatus status;
  absl::string_view pattern("(a|b)");
  Regexp::ParseState ps(Regexp::PerlX, pattern, &status);
  EXPECT_TRUE(ps.DoLeftParen(absl::string_view()));
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.DoVerticalBar());
  EXPECT_TRUE(ps.PushLiteral('b'));
  EXPECT_TRUE(ps.DoRightParen());
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test DoLeftParenNoCapture
TEST_F(ParseStateTest_480, DoLeftParenNoCapture_480) {
  RegexpStatus status;
  absl::string_view pattern("(?:a)");
  Regexp::ParseState ps(Regexp::PerlX, pattern, &status);
  EXPECT_TRUE(ps.DoLeftParenNoCapture());
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.DoRightParen());
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test PushRepeatOp with kRegexpStar
TEST_F(ParseStateTest_480, PushRepeatOpStar_480) {
  RegexpStatus status;
  absl::string_view pattern("a*");
  Regexp::ParseState ps(Regexp::PerlX, pattern, &status);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushRepeatOp(kRegexpStar, pattern, false));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test PushRepeatOp with kRegexpPlus
TEST_F(ParseStateTest_480, PushRepeatOpPlus_480) {
  RegexpStatus status;
  absl::string_view pattern("a+");
  Regexp::ParseState ps(Regexp::PerlX, pattern, &status);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushRepeatOp(kRegexpPlus, pattern, false));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test PushRepeatOp with kRegexpQuest
TEST_F(ParseStateTest_480, PushRepeatOpQuest_480) {
  RegexpStatus status;
  absl::string_view pattern("a?");
  Regexp::ParseState ps(Regexp::PerlX, pattern, &status);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushRepeatOp(kRegexpQuest, pattern, false));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test PushRepeatOp nongreedy
TEST_F(ParseStateTest_480, PushRepeatOpNonGreedy_480) {
  RegexpStatus status;
  absl::string_view pattern("a*?");
  Regexp::ParseState ps(Regexp::PerlX, pattern, &status);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushRepeatOp(kRegexpStar, pattern, true));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test PushRepetition with specific min and max
TEST_F(ParseStateTest_480, PushRepetition_480) {
  RegexpStatus status;
  absl::string_view pattern("a{2,5}");
  Regexp::ParseState ps(Regexp::PerlX, pattern, &status);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushRepetition(2, 5, pattern, false));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test PushRepetition with min == max
TEST_F(ParseStateTest_480, PushRepetitionExact_480) {
  RegexpStatus status;
  absl::string_view pattern("a{3}");
  Regexp::ParseState ps(Regexp::PerlX, pattern, &status);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushRepetition(3, 3, pattern, false));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test PushRepetition with unbounded max (-1)
TEST_F(ParseStateTest_480, PushRepetitionUnbounded_480) {
  RegexpStatus status;
  absl::string_view pattern("a{2,}");
  Regexp::ParseState ps(Regexp::PerlX, pattern, &status);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushRepetition(2, -1, pattern, false));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test DoFinish on empty pattern
TEST_F(ParseStateTest_480, EmptyPatternFinish_480) {
  RegexpStatus status;
  absl::string_view pattern("");
  Regexp::ParseState ps(Regexp::PerlX, pattern, &status);
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test multiple literals with MaybeConcatString hint
TEST_F(ParseStateTest_480, MaybeConcatString_480) {
  RegexpStatus status;
  absl::string_view pattern("ab");
  Regexp::ParseState ps(Regexp::PerlX, pattern, &status);
  EXPECT_TRUE(ps.PushLiteral('a'));
  // MaybeConcatString tries to merge sequential literals
  bool concat_result = ps.MaybeConcatString('b', Regexp::PerlX);
  // We just check it doesn't crash; result depends on state
  (void)concat_result;
  EXPECT_TRUE(ps.PushLiteral('b'));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test ParseCCCharacter with a simple character
TEST_F(ParseStateTest_480, ParseCCCharacterSimple_480) {
  RegexpStatus status;
  absl::string_view pattern("[a]");
  Regexp::ParseState ps(Regexp::PerlX, pattern, &status);
  absl::string_view s("a]");
  Rune rp = 0;
  bool result = ps.ParseCCCharacter(&s, &rp, pattern, &status);
  EXPECT_TRUE(result);
  EXPECT_EQ(rp, 'a');
}

// Test ParseCCCharacter with escape sequence
TEST_F(ParseStateTest_480, ParseCCCharacterEscape_480) {
  RegexpStatus status;
  absl::string_view pattern("[\\n]");
  Regexp::ParseState ps(Regexp::PerlX, pattern, &status);
  absl::string_view s("\\n]");
  Rune rp = 0;
  bool result = ps.ParseCCCharacter(&s, &rp, pattern, &status);
  EXPECT_TRUE(result);
  EXPECT_EQ(rp, '\n');
}

// Test ParseCCRange with a valid range
TEST_F(ParseStateTest_480, ParseCCRangeValid_480) {
  RegexpStatus status;
  absl::string_view pattern("[a-z]");
  Regexp::ParseState ps(Regexp::PerlX, pattern, &status);
  absl::string_view s("a-z]");
  RuneRange rr;
  bool result = ps.ParseCCRange(&s, &rr, pattern, &status);
  EXPECT_TRUE(result);
  EXPECT_EQ(rr.lo, 'a');
  EXPECT_EQ(rr.hi, 'z');
}

// Test ParseCharClass with a simple character class
TEST_F(ParseStateTest_480, ParseCharClassSimple_480) {
  RegexpStatus status;
  absl::string_view pattern("[abc]");
  Regexp::ParseState ps(Regexp::PerlX, pattern, &status);
  absl::string_view s("[abc]");
  Regexp* out_re = nullptr;
  bool result = ps.ParseCharClass(&s, &out_re, &status);
  EXPECT_TRUE(result);
  ASSERT_NE(out_re, nullptr);
  out_re->Decref();
}

// Test ParseCharClass with negated character class
TEST_F(ParseStateTest_480, ParseCharClassNegated_480) {
  RegexpStatus status;
  absl::string_view pattern("[^abc]");
  Regexp::ParseState ps(Regexp::PerlX, pattern, &status);
  absl::string_view s("[^abc]");
  Regexp* out_re = nullptr;
  bool result = ps.ParseCharClass(&s, &out_re, &status);
  EXPECT_TRUE(result);
  ASSERT_NE(out_re, nullptr);
  out_re->Decref();
}

// Test ParseCharClass with a range
TEST_F(ParseStateTest_480, ParseCharClassRange_480) {
  RegexpStatus status;
  absl::string_view pattern("[a-z]");
  Regexp::ParseState ps(Regexp::PerlX, pattern, &status);
  absl::string_view s("[a-z]");
  Regexp* out_re = nullptr;
  bool result = ps.ParseCharClass(&s, &out_re, &status);
  EXPECT_TRUE(result);
  ASSERT_NE(out_re, nullptr);
  out_re->Decref();
}

// Test that DoRightParen fails when no matching left paren
TEST_F(ParseStateTest_480, DoRightParenWithoutLeftParen_480) {
  RegexpStatus status;
  absl::string_view pattern(")");
  Regexp::ParseState ps(Regexp::PerlX, pattern, &status);
  EXPECT_TRUE(ps.PushLiteral('a'));
  bool result = ps.DoRightParen();
  EXPECT_FALSE(result);
}

// Test nested groups
TEST_F(ParseStateTest_480, NestedGroups_480) {
  RegexpStatus status;
  absl::string_view pattern("((a))");
  Regexp::ParseState ps(Regexp::PerlX, pattern, &status);
  EXPECT_TRUE(ps.DoLeftParen(absl::string_view()));
  EXPECT_TRUE(ps.DoLeftParen(absl::string_view()));
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.DoRightParen());
  EXPECT_TRUE(ps.DoRightParen());
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test named capture group
TEST_F(ParseStateTest_480, NamedCaptureGroup_480) {
  RegexpStatus status;
  absl::string_view pattern("(?P<name>a)");
  Regexp::ParseState ps(Regexp::PerlX, pattern, &status);
  EXPECT_TRUE(ps.DoLeftParen(absl::string_view("name")));
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.DoRightParen());
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test PushRepeatOp on empty stack (should fail or handle gracefully)
TEST_F(ParseStateTest_480, PushRepeatOpOnEmpty_480) {
  RegexpStatus status;
  absl::string_view pattern("*");
  Regexp::ParseState ps(Regexp::PerlX, pattern, &status);
  // Pushing repeat with nothing on stack
  bool result = ps.PushRepeatOp(kRegexpStar, pattern, false);
  EXPECT_FALSE(result);
}

// Test multiple alternations
TEST_F(ParseStateTest_480, MultipleAlternations_480) {
  RegexpStatus status;
  absl::string_view pattern("a|b|c");
  Regexp::ParseState ps(Regexp::PerlX, pattern, &status);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.DoVerticalBar());
  EXPECT_TRUE(ps.PushLiteral('b'));
  EXPECT_TRUE(ps.DoVerticalBar());
  EXPECT_TRUE(ps.PushLiteral('c'));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test that Regexp::Parse works for a basic regex (integration-like test)
TEST_F(ParseStateTest_480, RegexpParseBasic_480) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test that Regexp::Parse works for alternation
TEST_F(ParseStateTest_480, RegexpParseAlternation_480) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test that Regexp::Parse works for character classes
TEST_F(ParseStateTest_480, RegexpParseCharClass_480) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test that Regexp::Parse handles invalid regex
TEST_F(ParseStateTest_480, RegexpParseInvalid_480) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(", Regexp::PerlX, &status);
  EXPECT_EQ(re, nullptr);
}

// Test that Regexp::Parse handles invalid repeat
TEST_F(ParseStateTest_480, RegexpParseInvalidRepeat_480) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("*", Regexp::PerlX, &status);
  EXPECT_EQ(re, nullptr);
}

// Test ParsePerlFlags with basic flag string
TEST_F(ParseStateTest_480, ParsePerlFlagsBasic_480) {
  RegexpStatus status;
  absl::string_view pattern("(?i)abc");
  Regexp::ParseState ps(Regexp::PerlX, pattern, &status);
  absl::string_view s("?i)abc");
  bool result = ps.ParsePerlFlags(&s);
  EXPECT_TRUE(result);
}

// Test PushSimpleOp
TEST_F(ParseStateTest_480, PushSimpleOpNoWordBoundary_480) {
  RegexpStatus status;
  absl::string_view pattern("\\b");
  Regexp::ParseState ps(Regexp::PerlX, pattern, &status);
  EXPECT_TRUE(ps.PushSimpleOp(kRegexpWordBoundary));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test PushLiteral with Unicode rune
TEST_F(ParseStateTest_480, PushLiteralUnicode_480) {
  RegexpStatus status;
  absl::string_view pattern("\xC3\xA9");  // é in UTF-8
  Regexp::ParseState ps(Regexp::PerlX, pattern, &status);
  EXPECT_TRUE(ps.PushLiteral(0xE9));  // é
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test that DoFinish after DoVerticalBar with only one side still works
TEST_F(ParseStateTest_480, AlternationOneSide_480) {
  RegexpStatus status;
  absl::string_view pattern("a|");
  Regexp::ParseState ps(Regexp::PerlX, pattern, &status);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.DoVerticalBar());
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

}  // namespace re2
