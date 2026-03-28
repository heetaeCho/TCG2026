#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <string>

namespace re2 {

class RegexpParseTest_483 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// Test basic parsing of a simple literal string
TEST_F(RegexpParseTest_483, ParseSimpleLiteral_483) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  std::string dump = re->Dump();
  EXPECT_FALSE(dump.empty());
  re->Decref();
}

// Test parsing an empty string
TEST_F(RegexpParseTest_483, ParseEmptyString_483) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test parsing a character class with a single character
TEST_F(RegexpParseTest_483, ParseSingleCharClass_483) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  // A single-char class should be simplified to a literal
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// Test parsing a character class with two characters that are case-folded
TEST_F(RegexpParseTest_483, ParseCaseFoldCharClass_483) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[Aa]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  // Should collapse to a case-folded literal 'a'
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'a');
  re->Decref();
}

// Test parsing a character class with two characters (not case-fold pair)
TEST_F(RegexpParseTest_483, ParseTwoCharClassNonFold_483) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[ab]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  // Two distinct chars that are not a case-fold pair should remain a char class
  EXPECT_EQ(re->op(), kRegexpCharClass);
  re->Decref();
}

// Test parsing a multi-character character class
TEST_F(RegexpParseTest_483, ParseMultiCharClass_483) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[abc]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->op(), kRegexpCharClass);
  re->Decref();
}

// Test parsing alternation
TEST_F(RegexpParseTest_483, ParseAlternation_483) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test parsing concatenation
TEST_F(RegexpParseTest_483, ParseConcatenation_483) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("ab", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test parsing repetition operators
TEST_F(RegexpParseTest_483, ParseStar_483) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

TEST_F(RegexpParseTest_483, ParsePlus_483) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

TEST_F(RegexpParseTest_483, ParseQuest_483) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

// Test parsing with capture groups
TEST_F(RegexpParseTest_483, ParseCapture_483) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->NumCaptures(), 1);
  re->Decref();
}

// Test parsing with named capture groups
TEST_F(RegexpParseTest_483, ParseNamedCapture_483) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<name>a)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->NumCaptures(), 1);
  auto* named = re->NamedCaptures();
  ASSERT_NE(named, nullptr);
  EXPECT_EQ(named->count("name"), 1);
  delete named;
  re->Decref();
}

// Test parsing dot
TEST_F(RegexpParseTest_483, ParseDot_483) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test parsing anchors
TEST_F(RegexpParseTest_483, ParseCaret_483) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^a", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST_F(RegexpParseTest_483, ParseDollar_483) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a$", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test parsing word boundary
TEST_F(RegexpParseTest_483, ParseWordBoundary_483) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->op(), kRegexpWordBoundary);
  re->Decref();
}

// Test parsing non-word boundary
TEST_F(RegexpParseTest_483, ParseNoWordBoundary_483) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\B", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->op(), kRegexpNoWordBoundary);
  re->Decref();
}

// Test parsing repetition with min and max
TEST_F(RegexpParseTest_483, ParseRepetition_483) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), 5);
  re->Decref();
}

// Test parsing exact repetition
TEST_F(RegexpParseTest_483, ParseExactRepetition_483) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 3);
  EXPECT_EQ(re->max(), 3);
  re->Decref();
}

// Test parsing non-greedy repetition
TEST_F(RegexpParseTest_483, ParseNonGreedyStar_483) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->op(), kRegexpStar);
  EXPECT_TRUE(re->parse_flags() & Regexp::NonGreedy);
  re->Decref();
}

// Test invalid regex
TEST_F(RegexpParseTest_483, ParseInvalidRegex_483) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

// Test invalid regex - unmatched right paren
TEST_F(RegexpParseTest_483, ParseUnmatchedRightParen_483) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(")", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

// Test parsing complex expression
TEST_F(RegexpParseTest_483, ParseComplexExpr_483) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a|b)*c+d?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test parsing with FoldCase flag
TEST_F(RegexpParseTest_483, ParseFoldCase_483) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?i)abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test parsing Perl character classes
TEST_F(RegexpParseTest_483, ParsePerlCharClass_483) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\d+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test parsing with no-capture flag
TEST_F(RegexpParseTest_483, ParseNeverCapture_483) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)", Regexp::LikePerl | Regexp::NeverCapture, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  // With NeverCapture, there should be no captures
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

// Test multiple captures
TEST_F(RegexpParseTest_483, ParseMultipleCaptures_483) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// Test Simplify
TEST_F(RegexpParseTest_483, Simplify_483) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{1}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// Test SimplifyRegexp
TEST_F(RegexpParseTest_483, SimplifyRegexp_483) {
  RegexpStatus status;
  std::string dst;
  bool ok = Regexp::SimplifyRegexp("a{2,3}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

// Test ToString round-trip
TEST_F(RegexpParseTest_483, ToString_483) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+b*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test Dump
TEST_F(RegexpParseTest_483, Dump_483) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string dump = re->Dump();
  EXPECT_FALSE(dump.empty());
  re->Decref();
}

// Test Incref and Decref
TEST_F(RegexpParseTest_483, IncrefDecref_483) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* re2 = re->Incref();
  EXPECT_EQ(re, re2);
  re->Decref();
  re->Decref();
}

// Test NewLiteral
TEST_F(RegexpParseTest_483, NewLiteral_483) {
  Regexp* re = Regexp::NewLiteral('x', Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'x');
  re->Decref();
}

// Test Plus static constructor
TEST_F(RegexpParseTest_483, StaticPlus_483) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Plus(sub, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

// Test Star static constructor
TEST_F(RegexpParseTest_483, StaticStar_483) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Star(sub, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

// Test Quest static constructor
TEST_F(RegexpParseTest_483, StaticQuest_483) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Quest(sub, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

// Test Capture static constructor
TEST_F(RegexpParseTest_483, StaticCapture_483) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Capture(sub, Regexp::NoParseFlags, 1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 1);
  re->Decref();
}

// Test Repeat static constructor
TEST_F(RegexpParseTest_483, StaticRepeat_483) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 2, 5);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), 5);
  re->Decref();
}

// Test Concat static constructor
TEST_F(RegexpParseTest_483, StaticConcat_483) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* re = Regexp::Concat(subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Alternate static constructor
TEST_F(RegexpParseTest_483, StaticAlternate_483) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* re = Regexp::Alternate(subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test HaveMatch
TEST_F(RegexpParseTest_483, HaveMatch_483) {
  Regexp* re = Regexp::HaveMatch(42, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), 42);
  re->Decref();
}

// Test LiteralString
TEST_F(RegexpParseTest_483, LiteralString_483) {
  Rune runes[] = {'h', 'e', 'l', 'l', 'o'};
  Regexp* re = Regexp::LiteralString(runes, 5, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 5);
  re->Decref();
}

// Test parsing of character class [Bb] - case fold pair
TEST_F(RegexpParseTest_483, ParseCaseFoldB_483) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[Bb]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  // Should collapse to case-folded literal 'b'
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'b');
  re->Decref();
}

// Test parsing [Zz] - case fold pair
TEST_F(RegexpParseTest_483, ParseCaseFoldZ_483) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[Zz]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'z');
  re->Decref();
}

// Test parsing character class range
TEST_F(RegexpParseTest_483, ParseCharClassRange_483) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->op(), kRegexpCharClass);
  re->Decref();
}

// Test parsing with Latin1 flag
TEST_F(RegexpParseTest_483, ParseLatin1_483) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a]", Regexp::Latin1 | Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  // Single char class should be simplified
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// Test bad repetition (nothing to repeat)
TEST_F(RegexpParseTest_483, ParseBadRepetition_483) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("*", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

// Test nested groups
TEST_F(RegexpParseTest_483, ParseNestedGroups_483) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((a)(b))", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// Test RequiredPrefix
TEST_F(RegexpParseTest_483, RequiredPrefix_483) {
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

// Test parsing escape sequences
TEST_F(RegexpParseTest_483, ParseEscapeSequences_483) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\n\\t\\r", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test parsing non-capturing group
TEST_F(RegexpParseTest_483, ParseNonCapturingGroup_483) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:a)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

// Test CaptureNames
TEST_F(RegexpParseTest_483, CaptureNames_483) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<first>a)(?P<second>b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  auto* names = re->CaptureNames();
  ASSERT_NE(names, nullptr);
  EXPECT_EQ(names->size(), 2u);
  delete names;
  re->Decref();
}

}  // namespace re2
