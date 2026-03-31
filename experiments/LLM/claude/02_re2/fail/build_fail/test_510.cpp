#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include "util/utf.h"

namespace re2 {

// Helper to parse a regexp and get the Regexp* object
class RegexpParseTest_510 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}

  Regexp* Parse(const char* pattern, Regexp::ParseFlags flags = Regexp::LikePerl) {
    RegexpStatus status;
    Regexp* re = Regexp::Parse(pattern, flags, &status);
    return re;
  }
};

// Test basic concatenation via Parse - simple literal concatenation
TEST_F(RegexpParseTest_510, ParseSimpleConcatenation_510) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // "abc" should produce a concat of three literals
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  re->Decref();
}

// Test empty pattern produces empty match
TEST_F(RegexpParseTest_510, ParseEmptyPattern_510) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  re->Decref();
}

// Test single literal character
TEST_F(RegexpParseTest_510, ParseSingleLiteral_510) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'a');
  re->Decref();
}

// Test alternation
TEST_F(RegexpParseTest_510, ParseAlternation_510) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpAlternate);
  EXPECT_EQ(re->nsub(), 2);
  re->Decref();
}

// Test parenthesized group (capture)
TEST_F(RegexpParseTest_510, ParseCapture_510) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 1);
  re->Decref();
}

// Test non-capturing group
TEST_F(RegexpParseTest_510, ParseNonCapturingGroup_510) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:a)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // Non-capturing group around a single literal should just be the literal
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// Test star repetition
TEST_F(RegexpParseTest_510, ParseStar_510) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

// Test plus repetition
TEST_F(RegexpParseTest_510, ParsePlus_510) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

// Test quest repetition
TEST_F(RegexpParseTest_510, ParseQuest_510) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

// Test repeat with braces
TEST_F(RegexpParseTest_510, ParseRepeat_510) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), 5);
  re->Decref();
}

// Test dot (any char)
TEST_F(RegexpParseTest_510, ParseDot_510) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // Dot in Perl mode with default flags should be kRegexpAnyChar or a char class
  // depending on flags; just check it parsed
  ASSERT_TRUE(re->op() == kRegexpAnyChar || re->op() == kRegexpCharClass);
  re->Decref();
}

// Test begin/end line anchors
TEST_F(RegexpParseTest_510, ParseAnchors_510) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^a$", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpConcat);
  re->Decref();
}

// Test character class
TEST_F(RegexpParseTest_510, ParseCharClass_510) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[abc]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCharClass);
  re->Decref();
}

// Test word boundary
TEST_F(RegexpParseTest_510, ParseWordBoundary_510) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpWordBoundary);
  re->Decref();
}

// Test non-word boundary
TEST_F(RegexpParseTest_510, ParseNoWordBoundary_510) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\B", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpNoWordBoundary);
  re->Decref();
}

// Test concatenation of multiple items within a group
TEST_F(RegexpParseTest_510, ParseConcatenationInGroup_510) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(ab)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  // The sub should be a LiteralString for "ab"
  ASSERT_GE(re->nsub(), 1);
  Regexp** subs = re->sub();
  EXPECT_EQ(subs[0]->op(), kRegexpLiteralString);
  re->Decref();
}

// Test concatenation after alternation (complex expression)
TEST_F(RegexpParseTest_510, ParseComplexExpression_510) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("ab|cd", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpAlternate);
  EXPECT_EQ(re->nsub(), 2);
  Regexp** subs = re->sub();
  // Each alternative should be a concatenation of two literals (LiteralString)
  EXPECT_EQ(subs[0]->op(), kRegexpLiteralString);
  EXPECT_EQ(subs[1]->op(), kRegexpLiteralString);
  re->Decref();
}

// Test multiple alternations
TEST_F(RegexpParseTest_510, ParseMultipleAlternations_510) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b|c", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpAlternate);
  EXPECT_EQ(re->nsub(), 3);
  re->Decref();
}

// Test nested groups
TEST_F(RegexpParseTest_510, ParseNestedGroups_510) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((a)(b))", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 1);
  re->Decref();
}

// Test invalid regexp returns null
TEST_F(RegexpParseTest_510, ParseInvalidRegexp_510) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
}

// Test invalid regexp with unmatched paren
TEST_F(RegexpParseTest_510, ParseUnmatchedRightParen_510) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(")", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
}

// Test empty alternation branch
TEST_F(RegexpParseTest_510, ParseEmptyAlternationBranch_510) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpAlternate);
  re->Decref();
}

// Test empty concatenation in group
TEST_F(RegexpParseTest_510, ParseEmptyGroup_510) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("()", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  // The sub should be an empty match
  ASSERT_GE(re->nsub(), 1);
  Regexp** subs = re->sub();
  EXPECT_EQ(subs[0]->op(), kRegexpEmptyMatch);
  re->Decref();
}

// Test NumCaptures
TEST_F(RegexpParseTest_510, NumCaptures_510) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// Test NumCaptures with nested captures
TEST_F(RegexpParseTest_510, NumCapturesNested_510) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((a)(b))", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// Test ToString roundtrip
TEST_F(RegexpParseTest_510, ToString_510) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "abc");
  re->Decref();
}

// Test Dump produces non-empty string
TEST_F(RegexpParseTest_510, Dump_510) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string d = re->Dump();
  EXPECT_FALSE(d.empty());
  re->Decref();
}

// Test Simplify
TEST_F(RegexpParseTest_510, Simplify_510) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simple = re->Simplify();
  ASSERT_NE(simple, nullptr);
  // Simplify should produce something parseable
  std::string s = simple->ToString();
  EXPECT_FALSE(s.empty());
  simple->Decref();
  re->Decref();
}

// Test SimplifyRegexp static function
TEST_F(RegexpParseTest_510, SimplifyRegexp_510) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{2,3}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

// Test Incref and Decref
TEST_F(RegexpParseTest_510, IncrefDecref_510) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_GE(re->Ref(), 1);
  Regexp* re2 = re->Incref();
  EXPECT_EQ(re2, re);
  EXPECT_GE(re->Ref(), 2);
  re->Decref();
  re->Decref();
}

// Test concatenation with dot and star
TEST_F(RegexpParseTest_510, ParseDotStar_510) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

// Test complex concatenation with alternation and repetition
TEST_F(RegexpParseTest_510, ParseComplexConcatAlt_510) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a+|b*c)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  re->Decref();
}

// Test escaped characters
TEST_F(RegexpParseTest_510, ParseEscapedChars_510) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\.", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), '.');
  re->Decref();
}

// Test named capture
TEST_F(RegexpParseTest_510, ParseNamedCapture_510) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<name>abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_NE(re->name(), nullptr);
  EXPECT_EQ(*re->name(), "name");
  re->Decref();
}

// Test NamedCaptures
TEST_F(RegexpParseTest_510, NamedCaptures_510) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<foo>a)(?P<bar>b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  auto* names = re->NamedCaptures();
  ASSERT_NE(names, nullptr);
  EXPECT_EQ(names->size(), 2u);
  EXPECT_EQ((*names)["foo"], 1);
  EXPECT_EQ((*names)["bar"], 2);
  delete names;
  re->Decref();
}

// Test CaptureNames
TEST_F(RegexpParseTest_510, CaptureNames_510) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<foo>a)(?P<bar>b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  auto* cnames = re->CaptureNames();
  ASSERT_NE(cnames, nullptr);
  EXPECT_EQ(cnames->size(), 2u);
  EXPECT_EQ((*cnames)[1], "foo");
  EXPECT_EQ((*cnames)[2], "bar");
  delete cnames;
  re->Decref();
}

// Test HaveMatch
TEST_F(RegexpParseTest_510, HaveMatch_510) {
  Regexp* re = Regexp::HaveMatch(42, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), 42);
  re->Decref();
}

// Test NewLiteral
TEST_F(RegexpParseTest_510, NewLiteral_510) {
  Regexp* re = Regexp::NewLiteral('x', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'x');
  re->Decref();
}

// Test LiteralString
TEST_F(RegexpParseTest_510, LiteralString_510) {
  Rune runes[] = {'h', 'e', 'l', 'l', 'o'};
  Regexp* re = Regexp::LiteralString(runes, 5, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 5);
  re->Decref();
}

// Test Plus static method
TEST_F(RegexpParseTest_510, PlusStatic_510) {
  Regexp* lit = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Plus(lit, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

// Test Star static method
TEST_F(RegexpParseTest_510, StarStatic_510) {
  Regexp* lit = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Star(lit, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

// Test Quest static method
TEST_F(RegexpParseTest_510, QuestStatic_510) {
  Regexp* lit = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Quest(lit, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

// Test Capture static method
TEST_F(RegexpParseTest_510, CaptureStatic_510) {
  Regexp* lit = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Capture(lit, Regexp::LikePerl, 1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 1);
  re->Decref();
}

// Test Concat static method
TEST_F(RegexpParseTest_510, ConcatStatic_510) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  Regexp* re = Regexp::Concat(subs, 2, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  // Could be concat or literal string
  EXPECT_TRUE(re->op() == kRegexpConcat || re->op() == kRegexpLiteralString);
  re->Decref();
}

// Test Concat with zero subs
TEST_F(RegexpParseTest_510, ConcatZeroSubs_510) {
  Regexp* re = Regexp::Concat(nullptr, 0, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  re->Decref();
}

// Test Alternate static method
TEST_F(RegexpParseTest_510, AlternateStatic_510) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  Regexp* re = Regexp::Alternate(subs, 2, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  // Could be alternate or char class after factoring
  re->Decref();
}

// Test Alternate with zero subs
TEST_F(RegexpParseTest_510, AlternateZeroSubs_510) {
  Regexp* re = Regexp::Alternate(nullptr, 0, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpNoMatch);
  re->Decref();
}

// Test Repeat static method
TEST_F(RegexpParseTest_510, RepeatStatic_510) {
  Regexp* lit = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Repeat(lit, Regexp::LikePerl, 2, 5);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), 5);
  re->Decref();
}

// Test RequiredPrefix
TEST_F(RegexpParseTest_510, RequiredPrefix_510) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase;
  Regexp* suffix = nullptr;
  bool has_prefix = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  if (has_prefix) {
    EXPECT_FALSE(prefix.empty());
    if (suffix) suffix->Decref();
  }
  re->Decref();
}

// Test invalid character class
TEST_F(RegexpParseTest_510, ParseInvalidCharClass_510) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[z-a]", Regexp::LikePerl, &status);
  // This should fail since z > a
  EXPECT_EQ(re, nullptr);
}

// Test escaped special characters in concatenation
TEST_F(RegexpParseTest_510, ParseEscapedSpecials_510) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\(\\)\\[\\]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test concatenation followed by alternation in complex pattern
TEST_F(RegexpParseTest_510, ParseConcatThenAlternate_510) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("ab|cd|ef", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpAlternate);
  EXPECT_EQ(re->nsub(), 3);
  re->Decref();
}

// Test Concat with one sub
TEST_F(RegexpParseTest_510, ConcatOneSub_510) {
  Regexp* subs[1];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Concat(subs, 1, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// Test Alternate with one sub
TEST_F(RegexpParseTest_510, AlternateOneSub_510) {
  Regexp* subs[1];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Alternate(subs, 1, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// Test parse flags
TEST_F(RegexpParseTest_510, ParseFlagsPreserved_510) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::Latin1, &status);
  ASSERT_NE(re, nullptr);
  // Check flags are Latin1
  EXPECT_TRUE((re->parse_flags() & Regexp::Latin1) != 0);
  re->Decref();
}

}  // namespace re2
