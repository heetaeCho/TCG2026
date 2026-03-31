#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/walker-inl.h"
#include "absl/strings/string_view.h"

namespace re2 {

class ParseStateTest_494 : public ::testing::Test {
 protected:
  void SetUp() override {
    status_ = new RegexpStatus();
  }

  void TearDown() override {
    delete status_;
  }

  RegexpStatus* status_;
};

// Test basic construction and flags accessor
TEST_F(ParseStateTest_494, ConstructionAndFlags_494) {
  absl::string_view pattern("abc");
  Regexp::ParseState ps(Regexp::PerlX, pattern, status_);
  EXPECT_EQ(ps.flags(), Regexp::PerlX);
}

// Test rune_max with default Latin1 flags
TEST_F(ParseStateTest_494, RuneMaxLatin1_494) {
  absl::string_view pattern("abc");
  Regexp::ParseState ps(Regexp::Latin1, pattern, status_);
  EXPECT_EQ(ps.rune_max(), 0xFF);
}

// Test rune_max with UTF-8 (non-Latin1) flags
TEST_F(ParseStateTest_494, RuneMaxUTF8_494) {
  absl::string_view pattern("abc");
  Regexp::ParseState ps(Regexp::PerlX, pattern, status_);
  // When not Latin1, rune_max should be Runemax (0x10FFFF)
  EXPECT_GT(ps.rune_max(), 0xFF);
}

// Test PushLiteral returns true
TEST_F(ParseStateTest_494, PushLiteralReturnsTrue_494) {
  absl::string_view pattern("a");
  Regexp::ParseState ps(Regexp::PerlX, pattern, status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
}

// Test PushDot returns true
TEST_F(ParseStateTest_494, PushDotReturnsTrue_494) {
  absl::string_view pattern(".");
  Regexp::ParseState ps(Regexp::PerlX, pattern, status_);
  EXPECT_TRUE(ps.PushDot());
}

// Test PushCaret returns true
TEST_F(ParseStateTest_494, PushCaretReturnsTrue_494) {
  absl::string_view pattern("^");
  Regexp::ParseState ps(Regexp::PerlX, pattern, status_);
  EXPECT_TRUE(ps.PushCaret());
}

// Test PushDollar returns true
TEST_F(ParseStateTest_494, PushDollarReturnsTrue_494) {
  absl::string_view pattern("$");
  Regexp::ParseState ps(Regexp::PerlX, pattern, status_);
  EXPECT_TRUE(ps.PushDollar());
}

// Test PushWordBoundary returns true (word=true)
TEST_F(ParseStateTest_494, PushWordBoundaryTrue_494) {
  absl::string_view pattern("\\b");
  Regexp::ParseState ps(Regexp::PerlX, pattern, status_);
  EXPECT_TRUE(ps.PushWordBoundary(true));
}

// Test PushWordBoundary returns true (word=false)
TEST_F(ParseStateTest_494, PushWordBoundaryFalse_494) {
  absl::string_view pattern("\\B");
  Regexp::ParseState ps(Regexp::PerlX, pattern, status_);
  EXPECT_TRUE(ps.PushWordBoundary(false));
}

// Test PushSimpleOp returns true for NoMatch
TEST_F(ParseStateTest_494, PushSimpleOpNoMatch_494) {
  absl::string_view pattern("(?!)");
  Regexp::ParseState ps(Regexp::PerlX, pattern, status_);
  EXPECT_TRUE(ps.PushSimpleOp(kRegexpNoMatch));
}

// Test simple concatenation: push two literals, finish
TEST_F(ParseStateTest_494, PushTwoLiteralsAndFinish_494) {
  absl::string_view pattern("ab");
  Regexp::ParseState ps(Regexp::PerlX, pattern, status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushLiteral('b'));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test single literal and finish
TEST_F(ParseStateTest_494, SingleLiteralFinish_494) {
  absl::string_view pattern("a");
  Regexp::ParseState ps(Regexp::PerlX, pattern, status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test DoFinish with empty pattern produces valid result
TEST_F(ParseStateTest_494, EmptyPatternFinish_494) {
  absl::string_view pattern("");
  Regexp::ParseState ps(Regexp::PerlX, pattern, status_);
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test DoLeftParen and DoRightParen
TEST_F(ParseStateTest_494, LeftParenRightParen_494) {
  absl::string_view pattern("(a)");
  Regexp::ParseState ps(Regexp::PerlX, pattern, status_);
  EXPECT_TRUE(ps.DoLeftParen(absl::string_view()));
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.DoRightParen());
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test DoLeftParenNoCapture and DoRightParen
TEST_F(ParseStateTest_494, NoCaptureGroup_494) {
  absl::string_view pattern("(?:a)");
  Regexp::ParseState ps(Regexp::PerlX, pattern, status_);
  EXPECT_TRUE(ps.DoLeftParenNoCapture());
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.DoRightParen());
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test DoVerticalBar (alternation)
TEST_F(ParseStateTest_494, Alternation_494) {
  absl::string_view pattern("a|b");
  Regexp::ParseState ps(Regexp::PerlX, pattern, status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.DoVerticalBar());
  EXPECT_TRUE(ps.PushLiteral('b'));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test PushRepeatOp with kRegexpStar
TEST_F(ParseStateTest_494, PushRepeatOpStar_494) {
  absl::string_view pattern("a*");
  Regexp::ParseState ps(Regexp::PerlX, pattern, status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushRepeatOp(kRegexpStar, pattern.substr(1), false));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test PushRepeatOp with kRegexpPlus
TEST_F(ParseStateTest_494, PushRepeatOpPlus_494) {
  absl::string_view pattern("a+");
  Regexp::ParseState ps(Regexp::PerlX, pattern, status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushRepeatOp(kRegexpPlus, pattern.substr(1), false));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test PushRepeatOp with kRegexpQuest
TEST_F(ParseStateTest_494, PushRepeatOpQuest_494) {
  absl::string_view pattern("a?");
  Regexp::ParseState ps(Regexp::PerlX, pattern, status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushRepeatOp(kRegexpQuest, pattern.substr(1), false));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test PushRepeatOp with non-greedy
TEST_F(ParseStateTest_494, PushRepeatOpNonGreedy_494) {
  absl::string_view pattern("a*?");
  Regexp::ParseState ps(Regexp::PerlX, pattern, status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushRepeatOp(kRegexpStar, pattern.substr(1), true));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test PushRepetition with min=0, max=1 (like ?)
TEST_F(ParseStateTest_494, PushRepetitionZeroToOne_494) {
  absl::string_view pattern("a{0,1}");
  Regexp::ParseState ps(Regexp::PerlX, pattern, status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushRepetition(0, 1, pattern.substr(1), false));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test PushRepetition with min=2, max=5
TEST_F(ParseStateTest_494, PushRepetitionTwoToFive_494) {
  absl::string_view pattern("a{2,5}");
  Regexp::ParseState ps(Regexp::PerlX, pattern, status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushRepetition(2, 5, pattern.substr(1), false));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test PushRepetition with min=max (exact count)
TEST_F(ParseStateTest_494, PushRepetitionExact_494) {
  absl::string_view pattern("a{3}");
  Regexp::ParseState ps(Regexp::PerlX, pattern, status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushRepetition(3, 3, pattern.substr(1), false));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test PushRepetition with min=0, max=-1 (unbounded, like *)
TEST_F(ParseStateTest_494, PushRepetitionUnbounded_494) {
  absl::string_view pattern("a{0,}");
  Regexp::ParseState ps(Regexp::PerlX, pattern, status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushRepetition(0, -1, pattern.substr(1), false));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test named capture group
TEST_F(ParseStateTest_494, NamedCaptureGroup_494) {
  absl::string_view pattern("(?P<name>a)");
  Regexp::ParseState ps(Regexp::PerlX, pattern, status_);
  EXPECT_TRUE(ps.DoLeftParen(absl::string_view("name")));
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.DoRightParen());
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test nested groups
TEST_F(ParseStateTest_494, NestedGroups_494) {
  absl::string_view pattern("((a))");
  Regexp::ParseState ps(Regexp::PerlX, pattern, status_);
  EXPECT_TRUE(ps.DoLeftParen(absl::string_view()));
  EXPECT_TRUE(ps.DoLeftParen(absl::string_view()));
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.DoRightParen());
  EXPECT_TRUE(ps.DoRightParen());
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test complex pattern: (a|b)*
TEST_F(ParseStateTest_494, ComplexPatternAlternationStar_494) {
  absl::string_view pattern("(a|b)*");
  Regexp::ParseState ps(Regexp::PerlX, pattern, status_);
  EXPECT_TRUE(ps.DoLeftParen(absl::string_view()));
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.DoVerticalBar());
  EXPECT_TRUE(ps.PushLiteral('b'));
  EXPECT_TRUE(ps.DoRightParen());
  EXPECT_TRUE(ps.PushRepeatOp(kRegexpStar, pattern.substr(5), false));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test MaybeConcatString
TEST_F(ParseStateTest_494, MaybeConcatStringBasic_494) {
  absl::string_view pattern("ab");
  Regexp::ParseState ps(Regexp::PerlX, pattern, status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  // MaybeConcatString tries to concatenate string literals
  // After one literal, there's nothing to concat with
  bool result = ps.MaybeConcatString('a', Regexp::PerlX);
  // The result depends on whether there are two adjacent string literals
  // We just verify it doesn't crash and returns a bool
  (void)result;
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test ParseCCCharacter with simple character
TEST_F(ParseStateTest_494, ParseCCCharacterSimple_494) {
  absl::string_view s("a]");
  Rune r;
  absl::string_view whole_class("[a]");
  RegexpStatus status;
  bool ok = Regexp::ParseState::ParseCCCharacter(&s, &r, whole_class, &status);
  EXPECT_TRUE(ok);
  EXPECT_EQ(r, 'a');
}

// Test ParseCCCharacter with escaped character
TEST_F(ParseStateTest_494, ParseCCCharacterEscaped_494) {
  absl::string_view s("\\n]");
  Rune r;
  absl::string_view whole_class("[\\n]");
  RegexpStatus status;
  bool ok = Regexp::ParseState::ParseCCCharacter(&s, &r, whole_class, &status);
  EXPECT_TRUE(ok);
  EXPECT_EQ(r, '\n');
}

// Test ParseCCRange with a valid range
TEST_F(ParseStateTest_494, ParseCCRangeValid_494) {
  absl::string_view s("a-z]");
  RuneRange rr;
  absl::string_view whole_class("[a-z]");
  RegexpStatus status;
  bool ok = Regexp::ParseState::ParseCCRange(&s, &rr, whole_class, &status);
  EXPECT_TRUE(ok);
  EXPECT_EQ(rr.lo, 'a');
  EXPECT_EQ(rr.hi, 'z');
}

// Test DoRightParen without matching DoLeftParen should fail
TEST_F(ParseStateTest_494, UnmatchedRightParen_494) {
  absl::string_view pattern(")");
  Regexp::ParseState ps(Regexp::PerlX, pattern, status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  // DoRightParen without a preceding DoLeftParen
  bool result = ps.DoRightParen();
  // This should return false since there's no matching left paren
  EXPECT_FALSE(result);
}

// Test multiple alternations: a|b|c
TEST_F(ParseStateTest_494, MultipleAlternations_494) {
  absl::string_view pattern("a|b|c");
  Regexp::ParseState ps(Regexp::PerlX, pattern, status_);
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.DoVerticalBar());
  EXPECT_TRUE(ps.PushLiteral('b'));
  EXPECT_TRUE(ps.DoVerticalBar());
  EXPECT_TRUE(ps.PushLiteral('c'));
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test long concatenation
TEST_F(ParseStateTest_494, LongConcatenation_494) {
  absl::string_view pattern("abcdefghij");
  Regexp::ParseState ps(Regexp::PerlX, pattern, status_);
  for (char c = 'a'; c <= 'j'; c++) {
    EXPECT_TRUE(ps.PushLiteral(c));
  }
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test using the high-level Parse function as integration test
TEST_F(ParseStateTest_494, IntegrationParseSimple_494) {
  Regexp* re = Regexp::Parse("abc", Regexp::PerlX, status_);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test using the high-level Parse function with character class
TEST_F(ParseStateTest_494, IntegrationParseCharClass_494) {
  Regexp* re = Regexp::Parse("[a-z]", Regexp::PerlX, status_);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test using the high-level Parse function with dot
TEST_F(ParseStateTest_494, IntegrationParseDot_494) {
  Regexp* re = Regexp::Parse(".", Regexp::PerlX, status_);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test using the high-level Parse function with anchors
TEST_F(ParseStateTest_494, IntegrationParseAnchors_494) {
  Regexp* re = Regexp::Parse("^abc$", Regexp::PerlX, status_);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test using the high-level Parse function with quantifiers
TEST_F(ParseStateTest_494, IntegrationParseQuantifiers_494) {
  Regexp* re = Regexp::Parse("a*b+c?", Regexp::PerlX, status_);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test using the high-level Parse function with groups and alternation
TEST_F(ParseStateTest_494, IntegrationParseGroupAlt_494) {
  Regexp* re = Regexp::Parse("(a|b)+", Regexp::PerlX, status_);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test using the high-level Parse function with repetition bounds
TEST_F(ParseStateTest_494, IntegrationParseRepetitionBounds_494) {
  Regexp* re = Regexp::Parse("a{2,5}", Regexp::PerlX, status_);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test using the high-level Parse function with invalid regex
TEST_F(ParseStateTest_494, IntegrationParseInvalid_494) {
  Regexp* re = Regexp::Parse("(", Regexp::PerlX, status_);
  EXPECT_EQ(re, nullptr);
}

// Test using the high-level Parse function with empty pattern
TEST_F(ParseStateTest_494, IntegrationParseEmpty_494) {
  Regexp* re = Regexp::Parse("", Regexp::PerlX, status_);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test using the high-level Parse function with word boundary
TEST_F(ParseStateTest_494, IntegrationParseWordBoundary_494) {
  Regexp* re = Regexp::Parse("\\bfoo\\b", Regexp::PerlX, status_);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test PushLiteral with Unicode rune
TEST_F(ParseStateTest_494, PushLiteralUnicode_494) {
  absl::string_view pattern("é");
  Regexp::ParseState ps(Regexp::PerlX, pattern, status_);
  EXPECT_TRUE(ps.PushLiteral(0x00E9));  // é
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test flags accessor returns correct flags
TEST_F(ParseStateTest_494, FlagsAccessorMultiple_494) {
  absl::string_view pattern("abc");
  ParseFlags combined = static_cast<ParseFlags>(Regexp::PerlX | Regexp::Latin1);
  Regexp::ParseState ps(combined, pattern, status_);
  EXPECT_EQ(ps.flags(), combined);
}

}  // namespace re2
