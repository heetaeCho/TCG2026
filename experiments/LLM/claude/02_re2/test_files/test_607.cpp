#include <gtest/gtest.h>
#include "re2/regexp.h"
#include "re2/re2.h"
#include "util/utf.h"

namespace re2 {

class ParseStateTest_607 : public ::testing::Test {
 protected:
  void SetUp() override {
    status_ = new RegexpStatus();
  }

  void TearDown() override {
    delete status_;
  }

  RegexpStatus* status_;
};

// Test constructor with default (non-Latin1) flags sets rune_max to Runemax
TEST_F(ParseStateTest_607, ConstructorDefaultFlags_607) {
  Regexp::ParseState ps(Regexp::NoParseFlags, "test", status_);
  EXPECT_EQ(ps.rune_max(), Runemax);
  EXPECT_EQ(ps.flags(), Regexp::NoParseFlags);
}

// Test constructor with Latin1 flag sets rune_max to 0xFF
TEST_F(ParseStateTest_607, ConstructorLatin1Flag_607) {
  Regexp::ParseState ps(Regexp::Latin1, "test", status_);
  EXPECT_EQ(ps.rune_max(), 0xFF);
  EXPECT_EQ(ps.flags(), Regexp::Latin1);
}

// Test constructor with combined flags including Latin1
TEST_F(ParseStateTest_607, ConstructorCombinedFlagsWithLatin1_607) {
  Regexp::ParseFlags combined = static_cast<Regexp::ParseFlags>(
      Regexp::Latin1 | Regexp::FoldCase);
  Regexp::ParseState ps(combined, "abc", status_);
  EXPECT_EQ(ps.rune_max(), 0xFF);
}

// Test constructor with combined flags without Latin1
TEST_F(ParseStateTest_607, ConstructorCombinedFlagsWithoutLatin1_607) {
  Regexp::ParseFlags combined = static_cast<Regexp::ParseFlags>(
      Regexp::FoldCase | Regexp::PerlClasses);
  Regexp::ParseState ps(combined, "abc", status_);
  EXPECT_EQ(ps.rune_max(), Runemax);
}

// Test PushLiteral with a simple ASCII character
TEST_F(ParseStateTest_607, PushLiteralAscii_607) {
  Regexp::ParseState ps(Regexp::NoParseFlags, "a", status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
}

// Test PushLiteral with a Unicode character
TEST_F(ParseStateTest_607, PushLiteralUnicode_607) {
  Regexp::ParseState ps(Regexp::NoParseFlags, "\\x{1234}", status_);
  EXPECT_TRUE(ps.PushLiteral(0x1234));
}

// Test PushCaret
TEST_F(ParseStateTest_607, PushCaret_607) {
  Regexp::ParseState ps(Regexp::NoParseFlags, "^abc", status_);
  EXPECT_TRUE(ps.PushCaret());
}

// Test PushDollar
TEST_F(ParseStateTest_607, PushDollar_607) {
  Regexp::ParseState ps(Regexp::NoParseFlags, "abc$", status_);
  EXPECT_TRUE(ps.PushDollar());
}

// Test PushDot
TEST_F(ParseStateTest_607, PushDot_607) {
  Regexp::ParseState ps(Regexp::NoParseFlags, ".", status_);
  EXPECT_TRUE(ps.PushDot());
}

// Test PushWordBoundary with word=true
TEST_F(ParseStateTest_607, PushWordBoundaryTrue_607) {
  Regexp::ParseState ps(Regexp::PerlB, "\\b", status_);
  EXPECT_TRUE(ps.PushWordBoundary(true));
}

// Test PushWordBoundary with word=false
TEST_F(ParseStateTest_607, PushWordBoundaryFalse_607) {
  Regexp::ParseState ps(Regexp::PerlB, "\\B", status_);
  EXPECT_TRUE(ps.PushWordBoundary(false));
}

// Test DoLeftParen and DoRightParen matching
TEST_F(ParseStateTest_607, DoLeftParenAndDoRightParen_607) {
  Regexp::ParseState ps(Regexp::NoParseFlags, "(a)", status_);
  EXPECT_TRUE(ps.DoLeftParen(""));
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.DoRightParen());
}

// Test DoLeftParenNoCapture and DoRightParen
TEST_F(ParseStateTest_607, DoLeftParenNoCaptureAndDoRightParen_607) {
  Regexp::ParseState ps(Regexp::NoParseFlags, "(?:a)", status_);
  EXPECT_TRUE(ps.DoLeftParenNoCapture());
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.DoRightParen());
}

// Test DoVerticalBar (alternation)
TEST_F(ParseStateTest_607, DoVerticalBar_607) {
  Regexp::ParseState ps(Regexp::NoParseFlags, "a|b", status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.DoVerticalBar());
  EXPECT_TRUE(ps.PushLiteral('b'));
}

// Test DoFinish with a single literal
TEST_F(ParseStateTest_607, DoFinishSingleLiteral_607) {
  Regexp::ParseState ps(Regexp::NoParseFlags, "a", status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  Regexp* re = ps.DoFinish();
  EXPECT_NE(re, nullptr);
  if (re) re->Decref();
}

// Test DoFinish with empty expression
TEST_F(ParseStateTest_607, DoFinishEmpty_607) {
  Regexp::ParseState ps(Regexp::NoParseFlags, "", status_);
  Regexp* re = ps.DoFinish();
  EXPECT_NE(re, nullptr);
  if (re) re->Decref();
}

// Test PushRepeatOp with kRegexpStar
TEST_F(ParseStateTest_607, PushRepeatOpStar_607) {
  Regexp::ParseState ps(Regexp::NoParseFlags, "a*", status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushRepeatOp(kRegexpStar, "a*", false));
}

// Test PushRepeatOp with kRegexpPlus
TEST_F(ParseStateTest_607, PushRepeatOpPlus_607) {
  Regexp::ParseState ps(Regexp::NoParseFlags, "a+", status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushRepeatOp(kRegexpPlus, "a+", false));
}

// Test PushRepeatOp with kRegexpQuest
TEST_F(ParseStateTest_607, PushRepeatOpQuest_607) {
  Regexp::ParseState ps(Regexp::NoParseFlags, "a?", status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushRepeatOp(kRegexpQuest, "a?", false));
}

// Test PushRepeatOp non-greedy
TEST_F(ParseStateTest_607, PushRepeatOpNonGreedy_607) {
  Regexp::ParseState ps(Regexp::NoParseFlags, "a*?", status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushRepeatOp(kRegexpStar, "a*?", true));
}

// Test PushRepetition with specific min and max
TEST_F(ParseStateTest_607, PushRepetitionMinMax_607) {
  Regexp::ParseState ps(Regexp::NoParseFlags, "a{2,5}", status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushRepetition(2, 5, "a{2,5}", false));
}

// Test PushRepetition with min == max
TEST_F(ParseStateTest_607, PushRepetitionExact_607) {
  Regexp::ParseState ps(Regexp::NoParseFlags, "a{3}", status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushRepetition(3, 3, "a{3}", false));
}

// Test PushRepetition with unbounded max (-1)
TEST_F(ParseStateTest_607, PushRepetitionUnbounded_607) {
  Regexp::ParseState ps(Regexp::NoParseFlags, "a{2,}", status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushRepetition(2, -1, "a{2,}", false));
}

// Test PushSimpleOp
TEST_F(ParseStateTest_607, PushSimpleOpBeginText_607) {
  Regexp::ParseState ps(Regexp::NoParseFlags, "\\A", status_);
  EXPECT_TRUE(ps.PushSimpleOp(kRegexpBeginText));
}

// Test full alternation pipeline: a|b and DoFinish
TEST_F(ParseStateTest_607, AlternationDoFinish_607) {
  Regexp::ParseState ps(Regexp::NoParseFlags, "a|b", status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.DoVerticalBar());
  EXPECT_TRUE(ps.PushLiteral('b'));
  Regexp* re = ps.DoFinish();
  EXPECT_NE(re, nullptr);
  if (re) re->Decref();
}

// Test concatenation: push multiple literals and finish
TEST_F(ParseStateTest_607, ConcatenationDoFinish_607) {
  Regexp::ParseState ps(Regexp::NoParseFlags, "ab", status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushLiteral('b'));
  Regexp* re = ps.DoFinish();
  EXPECT_NE(re, nullptr);
  if (re) re->Decref();
}

// Test named capture group
TEST_F(ParseStateTest_607, NamedCaptureGroup_607) {
  Regexp::ParseState ps(Regexp::NoParseFlags, "(?P<name>a)", status_);
  EXPECT_TRUE(ps.DoLeftParen("name"));
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.DoRightParen());
  Regexp* re = ps.DoFinish();
  EXPECT_NE(re, nullptr);
  if (re) re->Decref();
}

// Test nested groups
TEST_F(ParseStateTest_607, NestedGroups_607) {
  Regexp::ParseState ps(Regexp::NoParseFlags, "((a))", status_);
  EXPECT_TRUE(ps.DoLeftParen(""));
  EXPECT_TRUE(ps.DoLeftParen(""));
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.DoRightParen());
  EXPECT_TRUE(ps.DoRightParen());
  Regexp* re = ps.DoFinish();
  EXPECT_NE(re, nullptr);
  if (re) re->Decref();
}

// Test flags() accessor returns correct flags
TEST_F(ParseStateTest_607, FlagsAccessor_607) {
  Regexp::ParseFlags f = static_cast<Regexp::ParseFlags>(
      Regexp::FoldCase | Regexp::DotNL | Regexp::PerlClasses);
  Regexp::ParseState ps(f, "test", status_);
  EXPECT_EQ(ps.flags(), f);
}

// Test rune_max() accessor for non-Latin1
TEST_F(ParseStateTest_607, RuneMaxAccessorDefault_607) {
  Regexp::ParseState ps(Regexp::NoParseFlags, "test", status_);
  EXPECT_EQ(ps.rune_max(), 1114111);  // Runemax
}

// Test rune_max() accessor for Latin1
TEST_F(ParseStateTest_607, RuneMaxAccessorLatin1_607) {
  Regexp::ParseState ps(Regexp::Latin1, "test", status_);
  EXPECT_EQ(ps.rune_max(), 255);  // 0xFF
}

// Test ParseCCCharacter with a simple character
TEST_F(ParseStateTest_607, ParseCCCharacterSimple_607) {
  Regexp::ParseState ps(Regexp::NoParseFlags, "[a]", status_);
  absl::string_view s = "a]";
  Rune r;
  EXPECT_TRUE(ps.ParseCCCharacter(&s, &r, "[a]", status_));
  EXPECT_EQ(r, 'a');
}

// Test ParseCCCharacter with escape sequence
TEST_F(ParseStateTest_607, ParseCCCharacterEscape_607) {
  Regexp::ParseState ps(Regexp::NoParseFlags, "[\\n]", status_);
  absl::string_view s = "\\n]";
  Rune r;
  EXPECT_TRUE(ps.ParseCCCharacter(&s, &r, "[\\n]", status_));
  EXPECT_EQ(r, '\n');
}

// Test DoRightParen without matching left paren should fail
TEST_F(ParseStateTest_607, DoRightParenUnmatched_607) {
  Regexp::ParseState ps(Regexp::NoParseFlags, ")", status_);
  // No DoLeftParen was called, so DoRightParen should fail
  EXPECT_FALSE(ps.DoRightParen());
}

// Test PushRepeatOp with nothing on stack (nothing to repeat)
TEST_F(ParseStateTest_607, PushRepeatOpEmpty_607) {
  Regexp::ParseState ps(Regexp::NoParseFlags, "*", status_);
  // Nothing pushed yet, repeating nothing should fail
  EXPECT_FALSE(ps.PushRepeatOp(kRegexpStar, "*", false));
}

// Test MaybeConcatString returns false when stack is empty or not appropriate
TEST_F(ParseStateTest_607, MaybeConcatStringEmpty_607) {
  Regexp::ParseState ps(Regexp::NoParseFlags, "", status_);
  EXPECT_FALSE(ps.MaybeConcatString('a', Regexp::NoParseFlags));
}

// Test PushLiteral followed by MaybeConcatString
TEST_F(ParseStateTest_607, MaybeConcatStringAfterLiteral_607) {
  Regexp::ParseState ps(Regexp::NoParseFlags, "ab", status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  // After one literal, MaybeConcatString should not yet concat (need two)
  // This is implementation-dependent, we just check it doesn't crash
  ps.MaybeConcatString('b', Regexp::NoParseFlags);
}

// Test complex expression: (a|b)*
TEST_F(ParseStateTest_607, ComplexExpression_607) {
  Regexp::ParseState ps(Regexp::NoParseFlags, "(a|b)*", status_);
  EXPECT_TRUE(ps.DoLeftParen(""));
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.DoVerticalBar());
  EXPECT_TRUE(ps.PushLiteral('b'));
  EXPECT_TRUE(ps.DoRightParen());
  EXPECT_TRUE(ps.PushRepeatOp(kRegexpStar, "(a|b)*", false));
  Regexp* re = ps.DoFinish();
  EXPECT_NE(re, nullptr);
  if (re) re->Decref();
}

// Test with LikePerl flags
TEST_F(ParseStateTest_607, LikePerlFlags_607) {
  Regexp::ParseState ps(Regexp::LikePerl, "\\w+", status_);
  EXPECT_EQ(ps.flags(), Regexp::LikePerl);
  // LikePerl doesn't include Latin1, so rune_max should be Runemax
  EXPECT_EQ(ps.rune_max(), Runemax);
}

// Test with AllParseFlags
TEST_F(ParseStateTest_607, AllParseFlags_607) {
  // AllParseFlags includes Latin1
  Regexp::ParseState ps(Regexp::AllParseFlags, "test", status_);
  EXPECT_EQ(ps.rune_max(), 0xFF);
}

// Test constructor with empty string
TEST_F(ParseStateTest_607, ConstructorEmptyString_607) {
  Regexp::ParseState ps(Regexp::NoParseFlags, "", status_);
  EXPECT_EQ(ps.flags(), Regexp::NoParseFlags);
  EXPECT_EQ(ps.rune_max(), Runemax);
}

// Test PushDot and repeat
TEST_F(ParseStateTest_607, PushDotWithRepeat_607) {
  Regexp::ParseState ps(Regexp::NoParseFlags, ".*", status_);
  EXPECT_TRUE(ps.PushDot());
  EXPECT_TRUE(ps.PushRepeatOp(kRegexpStar, ".*", false));
  Regexp* re = ps.DoFinish();
  EXPECT_NE(re, nullptr);
  if (re) re->Decref();
}

// Test PushCaret and PushDollar in sequence
TEST_F(ParseStateTest_607, AnchoredExpression_607) {
  Regexp::ParseState ps(Regexp::NoParseFlags, "^a$", status_);
  EXPECT_TRUE(ps.PushCaret());
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushDollar());
  Regexp* re = ps.DoFinish();
  EXPECT_NE(re, nullptr);
  if (re) re->Decref();
}

// Test multiple alternations
TEST_F(ParseStateTest_607, MultipleAlternations_607) {
  Regexp::ParseState ps(Regexp::NoParseFlags, "a|b|c", status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.DoVerticalBar());
  EXPECT_TRUE(ps.PushLiteral('b'));
  EXPECT_TRUE(ps.DoVerticalBar());
  EXPECT_TRUE(ps.PushLiteral('c'));
  Regexp* re = ps.DoFinish();
  EXPECT_NE(re, nullptr);
  if (re) re->Decref();
}

// Test PushRepetition with min=0, max=0
TEST_F(ParseStateTest_607, PushRepetitionZeroZero_607) {
  Regexp::ParseState ps(Regexp::NoParseFlags, "a{0}", status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushRepetition(0, 0, "a{0}", false));
  Regexp* re = ps.DoFinish();
  EXPECT_NE(re, nullptr);
  if (re) re->Decref();
}

// Test PushRepetition with min=0, max=1 (equivalent to ?)
TEST_F(ParseStateTest_607, PushRepetitionZeroOne_607) {
  Regexp::ParseState ps(Regexp::NoParseFlags, "a{0,1}", status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushRepetition(0, 1, "a{0,1}", false));
  Regexp* re = ps.DoFinish();
  EXPECT_NE(re, nullptr);
  if (re) re->Decref();
}

}  // namespace re2
