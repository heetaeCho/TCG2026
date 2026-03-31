#include "gtest/gtest.h"
#include "re2/regexp.h"

namespace re2 {

class RegexpParseTest_535 : public ::testing::Test {
 protected:
  void TearDown() override {}

  // Helper to parse and check success
  Regexp* ParseSuccess(absl::string_view pattern, Regexp::ParseFlags flags) {
    RegexpStatus status;
    Regexp* re = Regexp::Parse(pattern, flags, &status);
    EXPECT_TRUE(status.ok()) << "Pattern: " << pattern
                             << " Error: " << status.Text();
    EXPECT_NE(re, nullptr);
    return re;
  }

  // Helper to parse and check failure
  void ParseFail(absl::string_view pattern, Regexp::ParseFlags flags,
                 RegexpStatusCode expected_code) {
    RegexpStatus status;
    Regexp* re = Regexp::Parse(pattern, flags, &status);
    EXPECT_EQ(re, nullptr) << "Pattern: " << pattern
                           << " should have failed but got: "
                           << (re ? re->Dump() : "null");
    EXPECT_EQ(status.code(), expected_code)
        << "Pattern: " << pattern << " Error: " << status.Text();
    if (re) re->Decref();
  }
};

// ==================== Normal Operation Tests ====================

TEST_F(RegexpParseTest_535, SimpleLiteral_535) {
  Regexp* re = ParseSuccess("abc", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpConcat);
  re->Decref();
}

TEST_F(RegexpParseTest_535, SingleCharacter_535) {
  Regexp* re = ParseSuccess("a", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'a');
  re->Decref();
}

TEST_F(RegexpParseTest_535, EmptyPattern_535) {
  Regexp* re = ParseSuccess("", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  re->Decref();
}

TEST_F(RegexpParseTest_535, DotMatchesAnyChar_535) {
  Regexp* re = ParseSuccess(".", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpAnyChar);
  re->Decref();
}

TEST_F(RegexpParseTest_535, StarRepetition_535) {
  Regexp* re = ParseSuccess("a*", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

TEST_F(RegexpParseTest_535, PlusRepetition_535) {
  Regexp* re = ParseSuccess("a+", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

TEST_F(RegexpParseTest_535, QuestRepetition_535) {
  Regexp* re = ParseSuccess("a?", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

TEST_F(RegexpParseTest_535, Alternation_535) {
  Regexp* re = ParseSuccess("a|b", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpAlternate);
  re->Decref();
}

TEST_F(RegexpParseTest_535, CaptureGroup_535) {
  Regexp* re = ParseSuccess("(a)", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  re->Decref();
}

TEST_F(RegexpParseTest_535, CharacterClass_535) {
  Regexp* re = ParseSuccess("[abc]", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCharClass);
  re->Decref();
}

TEST_F(RegexpParseTest_535, CharacterClassRange_535) {
  Regexp* re = ParseSuccess("[a-z]", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCharClass);
  re->Decref();
}

TEST_F(RegexpParseTest_535, NegatedCharacterClass_535) {
  Regexp* re = ParseSuccess("[^abc]", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCharClass);
  re->Decref();
}

TEST_F(RegexpParseTest_535, BeginLine_535) {
  Regexp* re = ParseSuccess("^a", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpConcat);
  re->Decref();
}

TEST_F(RegexpParseTest_535, EndLine_535) {
  Regexp* re = ParseSuccess("a$", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpConcat);
  re->Decref();
}

TEST_F(RegexpParseTest_535, CountedRepetition_535) {
  Regexp* re = ParseSuccess("a{3}", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 3);
  EXPECT_EQ(re->max(), 3);
  re->Decref();
}

TEST_F(RegexpParseTest_535, CountedRepetitionRange_535) {
  Regexp* re = ParseSuccess("a{2,5}", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), 5);
  re->Decref();
}

TEST_F(RegexpParseTest_535, CountedRepetitionOpen_535) {
  Regexp* re = ParseSuccess("a{2,}", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), -1);
  re->Decref();
}

TEST_F(RegexpParseTest_535, EscapedCharacter_535) {
  Regexp* re = ParseSuccess("\\.", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), '.');
  re->Decref();
}

TEST_F(RegexpParseTest_535, WordBoundary_535) {
  Regexp* re = ParseSuccess("\\b", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpWordBoundary);
  re->Decref();
}

TEST_F(RegexpParseTest_535, NonWordBoundary_535) {
  Regexp* re = ParseSuccess("\\B", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpNoWordBoundary);
  re->Decref();
}

TEST_F(RegexpParseTest_535, BeginText_535) {
  Regexp* re = ParseSuccess("\\A", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpBeginText);
  re->Decref();
}

TEST_F(RegexpParseTest_535, EndText_535) {
  Regexp* re = ParseSuccess("\\z", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpEndText);
  re->Decref();
}

TEST_F(RegexpParseTest_535, AnyByte_535) {
  Regexp* re = ParseSuccess("\\C", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpAnyByte);
  re->Decref();
}

TEST_F(RegexpParseTest_535, LiteralFlag_535) {
  Regexp* re = ParseSuccess("a.b*c", Regexp::Literal);
  ASSERT_NE(re, nullptr);
  // With Literal flag, metacharacters are treated as literals
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  re->Decref();
}

TEST_F(RegexpParseTest_535, NonGreedyStar_535) {
  Regexp* re = ParseSuccess("a*?", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  // NonGreedy flag should be set in parse_flags
  EXPECT_NE(re->parse_flags() & Regexp::NonGreedy, 0);
  re->Decref();
}

TEST_F(RegexpParseTest_535, NonGreedyPlus_535) {
  Regexp* re = ParseSuccess("a+?", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  EXPECT_NE(re->parse_flags() & Regexp::NonGreedy, 0);
  re->Decref();
}

TEST_F(RegexpParseTest_535, NonGreedyQuest_535) {
  Regexp* re = ParseSuccess("a??", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  EXPECT_NE(re->parse_flags() & Regexp::NonGreedy, 0);
  re->Decref();
}

TEST_F(RegexpParseTest_535, NestedGroups_535) {
  Regexp* re = ParseSuccess("((a)(b))", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  re->Decref();
}

TEST_F(RegexpParseTest_535, ComplexPattern_535) {
  Regexp* re = ParseSuccess("^(a+|b*)(c{2,4})$", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpParseTest_535, PerlDigitClass_535) {
  Regexp* re = ParseSuccess("\\d", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCharClass);
  re->Decref();
}

TEST_F(RegexpParseTest_535, PerlWordClass_535) {
  Regexp* re = ParseSuccess("\\w", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCharClass);
  re->Decref();
}

TEST_F(RegexpParseTest_535, PerlSpaceClass_535) {
  Regexp* re = ParseSuccess("\\s", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCharClass);
  re->Decref();
}

TEST_F(RegexpParseTest_535, QuoteLiteral_535) {
  Regexp* re = ParseSuccess("\\Q.+*?\\E", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  // Should be treated as literal ".+*?"
  re->Decref();
}

TEST_F(RegexpParseTest_535, QuoteLiteralNoEnd_535) {
  Regexp* re = ParseSuccess("\\Qabc", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpParseTest_535, NeverCaptureFlag_535) {
  Regexp* re = ParseSuccess("(a)", Regexp::LikePerl | Regexp::NeverCapture);
  ASSERT_NE(re, nullptr);
  // With NeverCapture, groups don't capture
  re->Decref();
}

TEST_F(RegexpParseTest_535, NonCapturingGroup_535) {
  Regexp* re = ParseSuccess("(?:a)", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  // Should be just 'a', not a capture
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

TEST_F(RegexpParseTest_535, NamedCapture_535) {
  Regexp* re = ParseSuccess("(?P<name>a)", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  re->Decref();
}

TEST_F(RegexpParseTest_535, FoldCaseFlag_535) {
  Regexp* re = ParseSuccess("(?i)abc", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpParseTest_535, NullStatusPointer_535) {
  // Should not crash with NULL status
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpParseTest_535, Latin1Flag_535) {
  Regexp* re = ParseSuccess("abc", Regexp::LikePerl | Regexp::Latin1);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpParseTest_535, DotNLFlag_535) {
  Regexp* re = ParseSuccess(".", Regexp::LikePerl | Regexp::DotNL);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpAnyChar);
  re->Decref();
}

TEST_F(RegexpParseTest_535, OneLine_535) {
  Regexp* re = ParseSuccess("^abc$", Regexp::LikePerl | Regexp::OneLine);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpParseTest_535, UnicodeProperty_535) {
  Regexp* re = ParseSuccess("\\pL", Regexp::LikePerl | Regexp::UnicodeGroups);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCharClass);
  re->Decref();
}

TEST_F(RegexpParseTest_535, UnicodePropertyBraces_535) {
  Regexp* re =
      ParseSuccess("\\p{Greek}", Regexp::LikePerl | Regexp::UnicodeGroups);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCharClass);
  re->Decref();
}

TEST_F(RegexpParseTest_535, MultipleAlternations_535) {
  Regexp* re = ParseSuccess("a|b|c|d", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpAlternate);
  re->Decref();
}

TEST_F(RegexpParseTest_535, NumCaptures_535) {
  Regexp* re = ParseSuccess("(a)(b)(c)", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

TEST_F(RegexpParseTest_535, DumpRoundTrip_535) {
  Regexp* re = ParseSuccess("a+b*c?", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  std::string dump = re->Dump();
  EXPECT_FALSE(dump.empty());
  re->Decref();
}

TEST_F(RegexpParseTest_535, ToStringRoundTrip_535) {
  Regexp* re = ParseSuccess("abc", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "abc");
  re->Decref();
}

// ==================== Boundary Condition Tests ====================

TEST_F(RegexpParseTest_535, CurlyBraceNotRepetition_535) {
  // {abc} is not a valid repetition, should be treated as literal
  Regexp* re = ParseSuccess("{abc}", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpParseTest_535, SingleCurlyBrace_535) {
  Regexp* re = ParseSuccess("{", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), '{');
  re->Decref();
}

TEST_F(RegexpParseTest_535, ZeroRepetition_535) {
  Regexp* re = ParseSuccess("a{0}", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpParseTest_535, ZeroToOneRepetition_535) {
  Regexp* re = ParseSuccess("a{0,1}", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpParseTest_535, LargeRepetition_535) {
  Regexp* re = ParseSuccess("a{1,1000}", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpParseTest_535, EmptyAlternation_535) {
  Regexp* re = ParseSuccess("|", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpParseTest_535, EmptyGroup_535) {
  Regexp* re = ParseSuccess("()", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpParseTest_535, EmptyCharClass_535) {
  // [^\x00-\x{10ffff}] would be empty but hard to express
  // Use a simple empty negation trick not possible easily
  // Instead test minimal char class
  Regexp* re = ParseSuccess("[a]", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpParseTest_535, CaretInCharClass_535) {
  Regexp* re = ParseSuccess("[\\^]", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpParseTest_535, DashInCharClass_535) {
  Regexp* re = ParseSuccess("[-]", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpParseTest_535, BracketInCharClass_535) {
  Regexp* re = ParseSuccess("[\\]]", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// ==================== Error Cases ====================

TEST_F(RegexpParseTest_535, UnmatchedRightParen_535) {
  ParseFail(")", Regexp::LikePerl, kRegexpUnexpectedParen);
}

TEST_F(RegexpParseTest_535, UnmatchedLeftParen_535) {
  ParseFail("(abc", Regexp::LikePerl, kRegexpMissingParen);
}

TEST_F(RegexpParseTest_535, UnmatchedLeftBracket_535) {
  ParseFail("[abc", Regexp::LikePerl, kRegexpMissingBracket);
}

TEST_F(RegexpParseTest_535, TrailingBackslash_535) {
  ParseFail("\\", Regexp::LikePerl, kRegexpTrailingBackslash);
}

TEST_F(RegexpParseTest_535, RepeatOfRepeatStar_535) {
  ParseFail("a**", Regexp::LikePerl, kRegexpRepeatOp);
}

TEST_F(RegexpParseTest_535, RepeatOfRepeatPlus_535) {
  ParseFail("a+*", Regexp::LikePerl, kRegexpRepeatOp);
}

TEST_F(RegexpParseTest_535, RepeatOfRepeatQuest_535) {
  ParseFail("a?*", Regexp::LikePerl, kRegexpRepeatOp);
}

TEST_F(RegexpParseTest_535, RepeatNothing_535) {
  ParseFail("*", Regexp::LikePerl, kRegexpRepeatArgument);
}

TEST_F(RegexpParseTest_535, PlusNothing_535) {
  ParseFail("+", Regexp::LikePerl, kRegexpRepeatArgument);
}

TEST_F(RegexpParseTest_535, QuestNothing_535) {
  ParseFail("?", Regexp::LikePerl, kRegexpRepeatArgument);
}

TEST_F(RegexpParseTest_535, BadCharRange_535) {
  ParseFail("[z-a]", Regexp::LikePerl, kRegexpBadCharRange);
}

TEST_F(RegexpParseTest_535, BadPerlOp_535) {
  ParseFail("(?z)", Regexp::LikePerl, kRegexpBadPerlOp);
}

TEST_F(RegexpParseTest_535, RepeatOfCountedRepeat_535) {
  ParseFail("a{2}*", Regexp::LikePerl, kRegexpRepeatOp);
}

TEST_F(RegexpParseTest_535, CountedRepeatOfStar_535) {
  ParseFail("a*{2}", Regexp::LikePerl, kRegexpRepeatOp);
}

TEST_F(RegexpParseTest_535, BadEscapeSequence_535) {
  ParseFail("\\x{FFFFFFFF}", Regexp::LikePerl, kRegexpBadEscape);
}

// ==================== ToString/Dump Verification Tests ====================

TEST_F(RegexpParseTest_535, ToStringSimpleConcat_535) {
  Regexp* re = ParseSuccess("abc", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->ToString(), "abc");
  re->Decref();
}

TEST_F(RegexpParseTest_535, ToStringStar_535) {
  Regexp* re = ParseSuccess("a*", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->ToString(), "a*");
  re->Decref();
}

TEST_F(RegexpParseTest_535, ToStringAlternation_535) {
  Regexp* re = ParseSuccess("a|b", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->ToString(), "[ab]");
  re->Decref();
}

TEST_F(RegexpParseTest_535, ToStringCharClass_535) {
  Regexp* re = ParseSuccess("[a-z]", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->ToString(), "[a-z]");
  re->Decref();
}

TEST_F(RegexpParseTest_535, ToStringRepeat_535) {
  Regexp* re = ParseSuccess("a{3,5}", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->ToString(), "a{3,5}");
  re->Decref();
}

TEST_F(RegexpParseTest_535, ToStringDot_535) {
  // In LikePerl mode without DotNL, dot doesn't match \n
  Regexp* re = ParseSuccess(".", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// ==================== Additional Edge Cases ====================

TEST_F(RegexpParseTest_535, MultipleCaptures_535) {
  Regexp* re = ParseSuccess("(a)(b)(c)(d)(e)", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 5);
  re->Decref();
}

TEST_F(RegexpParseTest_535, NestedQuantifiers_535) {
  // (a+)? is valid - quantifier of a group
  Regexp* re = ParseSuccess("(a+)?", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpParseTest_535, ComplexCharClass_535) {
  Regexp* re = ParseSuccess("[a-zA-Z0-9_]", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCharClass);
  re->Decref();
}

TEST_F(RegexpParseTest_535, LiteralFlagMetachars_535) {
  // With Literal flag, all metacharacters should be literals
  Regexp* re = ParseSuccess("(a+b*c?)", Regexp::Literal);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpParseTest_535, HexEscape_535) {
  Regexp* re = ParseSuccess("\\x41", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'A');
  re->Decref();
}

TEST_F(RegexpParseTest_535, OctalEscape_535) {
  Regexp* re = ParseSuccess("\\101", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'A');
  re->Decref();
}

TEST_F(RegexpParseTest_535, FlagToggleInline_535) {
  Regexp* re = ParseSuccess("(?i)abc", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpParseTest_535, FlagGroupInline_535) {
  Regexp* re = ParseSuccess("(?i:abc)", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpParseTest_535, StatusOkAfterSuccess_535) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

TEST_F(RegexpParseTest_535, StatusNotOkAfterFailure_535) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
  EXPECT_NE(status.code(), kRegexpSuccess);
}

TEST_F(RegexpParseTest_535, StatusTextNonEmptyAfterFailure_535) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  std::string text = status.Text();
  EXPECT_FALSE(text.empty());
}

TEST_F(RegexpParseTest_535, NonGreedyCountedRepeat_535) {
  Regexp* re = ParseSuccess("a{2,5}?", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_NE(re->parse_flags() & Regexp::NonGreedy, 0);
  re->Decref();
}

TEST_F(RegexpParseTest_535, EscapedSpecialChars_535) {
  Regexp* re = ParseSuccess("\\(\\)\\[\\]\\{\\}\\|\\^\\$\\.", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpParseTest_535, UnicodeCharacter_535) {
  // UTF-8 encoded unicode character
  Regexp* re = ParseSuccess("\\x{263A}", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 0x263A);
  re->Decref();
}

}  // namespace re2
