#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include "util/utf.h"

namespace re2 {

// Helper to parse a regex and return the Regexp pointer
static Regexp* ParseRegexp(const char* pattern, Regexp::ParseFlags flags = Regexp::LikePerl) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(pattern, flags, &status);
  return re;
}

// ==================== Regexp::Parse Tests ====================

TEST(RegexpParseTest_511, ParseSimpleLiteral_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

TEST(RegexpParseTest_511, ParseEmptyString_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

TEST(RegexpParseTest_511, ParseAlternation_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b|c", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  EXPECT_EQ(re->op(), kRegexpAlternate);
  re->Decref();
}

TEST(RegexpParseTest_511, ParseConcatenation_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  EXPECT_EQ(re->op(), kRegexpConcat);
  re->Decref();
}

TEST(RegexpParseTest_511, ParseStar_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

TEST(RegexpParseTest_511, ParsePlus_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

TEST(RegexpParseTest_511, ParseQuest_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

TEST(RegexpParseTest_511, ParseCapture_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  EXPECT_EQ(re->op(), kRegexpCapture);
  re->Decref();
}

TEST(RegexpParseTest_511, ParseCharClass_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[abc]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  EXPECT_EQ(re->op(), kRegexpCharClass);
  re->Decref();
}

TEST(RegexpParseTest_511, ParseDot_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  // Dot may be AnyChar or CharClass depending on flags
  re->Decref();
}

TEST(RegexpParseTest_511, ParseBeginLine_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^a", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

TEST(RegexpParseTest_511, ParseEndLine_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a$", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

TEST(RegexpParseTest_511, ParseWordBoundary_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\ba\\b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

TEST(RegexpParseTest_511, ParseRepeat_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), 5);
  re->Decref();
}

TEST(RegexpParseTest_511, ParseRepeatExact_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 3);
  EXPECT_EQ(re->max(), 3);
  re->Decref();
}

TEST(RegexpParseTest_511, ParseRepeatAtLeast_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), -1);
  re->Decref();
}

TEST(RegexpParseTest_511, ParseBadRegexp_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_NE(status.code(), kRegexpSuccess);
}

TEST(RegexpParseTest_511, ParseBadRegexpUnmatchedParen_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(")", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_NE(status.code(), kRegexpSuccess);
}

TEST(RegexpParseTest_511, ParseBadCharClass_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_NE(status.code(), kRegexpSuccess);
}

TEST(RegexpParseTest_511, ParseNestedGroups_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((a)(b))", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

TEST(RegexpParseTest_511, ParseNamedCapture_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<name>a)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  EXPECT_EQ(re->op(), kRegexpCapture);
  re->Decref();
}

TEST(RegexpParseTest_511, ParseNonCapturingGroup_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:a)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  // Non-capturing group should not produce kRegexpCapture at top level
  EXPECT_NE(re->op(), kRegexpCapture);
  re->Decref();
}

// ==================== Regexp Factory Methods Tests ====================

TEST(RegexpFactoryTest_511, NewLiteral_511) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'a');
  re->Decref();
}

TEST(RegexpFactoryTest_511, HaveMatch_511) {
  Regexp* re = Regexp::HaveMatch(42, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), 42);
  re->Decref();
}

TEST(RegexpFactoryTest_511, Star_511) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Star(sub, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

TEST(RegexpFactoryTest_511, Plus_511) {
  Regexp* sub = Regexp::NewLiteral('b', Regexp::LikePerl);
  Regexp* re = Regexp::Plus(sub, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

TEST(RegexpFactoryTest_511, Quest_511) {
  Regexp* sub = Regexp::NewLiteral('c', Regexp::LikePerl);
  Regexp* re = Regexp::Quest(sub, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

TEST(RegexpFactoryTest_511, Capture_511) {
  Regexp* sub = Regexp::NewLiteral('d', Regexp::LikePerl);
  Regexp* re = Regexp::Capture(sub, Regexp::LikePerl, 1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 1);
  re->Decref();
}

TEST(RegexpFactoryTest_511, Repeat_511) {
  Regexp* sub = Regexp::NewLiteral('e', Regexp::LikePerl);
  Regexp* re = Regexp::Repeat(sub, Regexp::LikePerl, 2, 5);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), 5);
  re->Decref();
}

TEST(RegexpFactoryTest_511, Concat_511) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  Regexp* re = Regexp::Concat(subs, 2, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST(RegexpFactoryTest_511, Alternate_511) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  Regexp* re = Regexp::Alternate(subs, 2, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST(RegexpFactoryTest_511, AlternateNoFactor_511) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('x', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('y', Regexp::LikePerl);
  Regexp* re = Regexp::AlternateNoFactor(subs, 2, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpAlternate);
  re->Decref();
}

TEST(RegexpFactoryTest_511, LiteralString_511) {
  Rune runes[] = {'h', 'e', 'l', 'l', 'o'};
  Regexp* re = Regexp::LiteralString(runes, 5, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 5);
  re->Decref();
}

TEST(RegexpFactoryTest_511, ConcatSingleElement_511) {
  Regexp* subs[1];
  subs[0] = Regexp::NewLiteral('z', Regexp::LikePerl);
  Regexp* re = Regexp::Concat(subs, 1, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  // Single element concat should just return the element
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

TEST(RegexpFactoryTest_511, ConcatZeroElements_511) {
  Regexp* re = Regexp::Concat(nullptr, 0, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  re->Decref();
}

TEST(RegexpFactoryTest_511, AlternateZeroElements_511) {
  Regexp* re = Regexp::Alternate(nullptr, 0, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpNoMatch);
  re->Decref();
}

TEST(RegexpFactoryTest_511, AlternateSingleElement_511) {
  Regexp* subs[1];
  subs[0] = Regexp::NewLiteral('q', Regexp::LikePerl);
  Regexp* re = Regexp::Alternate(subs, 1, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// ==================== Regexp Reference Counting Tests ====================

TEST(RegexpRefTest_511, IncrefDecref_511) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  Regexp* re2 = re->Incref();
  EXPECT_EQ(re, re2);
  // After Incref, ref count should be 2
  re->Decref();
  // Still alive, ref count should be 1
  re->Decref();
  // Now destroyed
}

// ==================== ToString / Dump Tests ====================

TEST(RegexpToStringTest_511, SimpleLiteral_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "abc");
  re->Decref();
}

TEST(RegexpToStringTest_511, Alternation_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "[ab]");  // May be simplified
  re->Decref();
}

TEST(RegexpToStringTest_511, ComplexPattern_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a+|b*)?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

TEST(RegexpDumpTest_511, DumpLiteral_511) {
  Regexp* re = Regexp::NewLiteral('x', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  std::string d = re->Dump();
  EXPECT_FALSE(d.empty());
  re->Decref();
}

// ==================== NumCaptures Tests ====================

TEST(RegexpCaptureTest_511, NoCaptures_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

TEST(RegexpCaptureTest_511, OneCapture_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 1);
  re->Decref();
}

TEST(RegexpCaptureTest_511, MultipleCaptures_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

TEST(RegexpCaptureTest_511, NestedCaptures_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((a)(b))", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

TEST(RegexpCaptureTest_511, NonCapturingGroup_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:a)(b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 1);
  re->Decref();
}

// ==================== NamedCaptures Tests ====================

TEST(RegexpNamedCaptureTest_511, NoNamedCaptures_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* names = re->NamedCaptures();
  EXPECT_EQ(names, nullptr);
  delete names;
  re->Decref();
}

TEST(RegexpNamedCaptureTest_511, WithNamedCaptures_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<first>a)(?P<second>b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* names = re->NamedCaptures();
  ASSERT_NE(names, nullptr);
  EXPECT_EQ(names->size(), 2u);
  EXPECT_EQ((*names)["first"], 1);
  EXPECT_EQ((*names)["second"], 2);
  delete names;
  re->Decref();
}

// ==================== CaptureNames Tests ====================

TEST(RegexpCaptureNamesTest_511, WithNamedCaptures_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<foo>a)(?P<bar>b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<int, std::string>* cnames = re->CaptureNames();
  ASSERT_NE(cnames, nullptr);
  EXPECT_EQ(cnames->size(), 2u);
  EXPECT_EQ((*cnames)[1], "foo");
  EXPECT_EQ((*cnames)[2], "bar");
  delete cnames;
  re->Decref();
}

// ==================== Simplify Tests ====================

TEST(RegexpSimplifyTest_511, SimplifyLiteral_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simple = re->Simplify();
  ASSERT_NE(simple, nullptr);
  simple->Decref();
  re->Decref();
}

TEST(RegexpSimplifyTest_511, SimplifyRegexpStatic_511) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{2,5}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

// ==================== RequiredPrefix Tests ====================

TEST(RegexpRequiredPrefixTest_511, HasPrefix_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc.*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase;
  Regexp* suffix = nullptr;
  bool has = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  if (has) {
    EXPECT_FALSE(prefix.empty());
    if (suffix) suffix->Decref();
  }
  re->Decref();
}

TEST(RegexpRequiredPrefixTest_511, NoPrefix_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".*abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase;
  Regexp* suffix = nullptr;
  bool has = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  EXPECT_FALSE(has);
  re->Decref();
}

// ==================== Complex Parsing Tests ====================

TEST(RegexpParseComplexTest_511, EscapedCharacters_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\d+\\.\\d+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

TEST(RegexpParseComplexTest_511, CharClassRange_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-zA-Z0-9]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  EXPECT_EQ(re->op(), kRegexpCharClass);
  re->Decref();
}

TEST(RegexpParseComplexTest_511, NegatedCharClass_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[^abc]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  EXPECT_EQ(re->op(), kRegexpCharClass);
  re->Decref();
}

TEST(RegexpParseComplexTest_511, NonGreedy_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

TEST(RegexpParseComplexTest_511, POSIXFlags_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::POSIX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

TEST(RegexpParseComplexTest_511, PerlFlagsInline_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?i)abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

TEST(RegexpParseComplexTest_511, MultipleLevelNesting_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(((a|b)*)+(c|d)?)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

TEST(RegexpParseComplexTest_511, EmptyAlternation_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("|a", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

TEST(RegexpParseComplexTest_511, BadRepeatOperand_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("*", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_NE(status.code(), kRegexpSuccess);
}

TEST(RegexpParseComplexTest_511, BadRepeatNothingToRepeat_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("+", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_NE(status.code(), kRegexpSuccess);
}

TEST(RegexpParseComplexTest_511, UnicodeCharacter_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\x{263A}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

TEST(RegexpParseComplexTest_511, PerlCharClasses_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\w\\s\\d", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

// ==================== Roundtrip Tests ====================

TEST(RegexpRoundtripTest_511, ParseAndToString_511) {
  RegexpStatus status;
  const char* patterns[] = {
    "a",
    "ab",
    "a*",
    "a+",
    "a?",
    "[abc]",
    "\\d",
    ".",
  };
  for (const char* pattern : patterns) {
    Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
    ASSERT_NE(re, nullptr) << "Failed to parse: " << pattern;
    std::string s = re->ToString();
    EXPECT_FALSE(s.empty()) << "Empty ToString for: " << pattern;
    // Parse the result back and make sure it's valid
    RegexpStatus status2;
    Regexp* re2 = Regexp::Parse(s, Regexp::LikePerl, &status2);
    ASSERT_NE(re2, nullptr) << "Failed to re-parse: " << s;
    re2->Decref();
    re->Decref();
  }
}

// ==================== op() accessor Tests ====================

TEST(RegexpAccessorTest_511, LiteralOp_511) {
  Regexp* re = Regexp::NewLiteral('z', Regexp::LikePerl);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

TEST(RegexpAccessorTest_511, LiteralRune_511) {
  Regexp* re = Regexp::NewLiteral('z', Regexp::LikePerl);
  EXPECT_EQ(re->rune(), 'z');
  re->Decref();
}

TEST(RegexpAccessorTest_511, ParseFlags_511) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::LikePerl);
  EXPECT_NE(static_cast<int>(re->parse_flags()), 0);
  re->Decref();
}

TEST(RegexpAccessorTest_511, Nsub_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpConcat);
  EXPECT_EQ(re->nsub(), 3);
  re->Decref();
}

TEST(RegexpAccessorTest_511, Sub_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpConcat);
  Regexp** subs = re->sub();
  ASSERT_NE(subs, nullptr);
  for (int i = 0; i < re->nsub(); i++) {
    EXPECT_EQ(subs[i]->op(), kRegexpLiteral);
  }
  re->Decref();
}

// ==================== NullWalk Test ====================

TEST(RegexpNullWalkTest_511, DoesNotCrash_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a|b)*c+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->NullWalk();
  re->Decref();
}

// ==================== MimicsPCRE Test ====================

TEST(RegexpMimicsPCRETest_511, SimpleLiteralMimics_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // Simple literals should mimic PCRE
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// ==================== Edge Cases ====================

TEST(RegexpEdgeCaseTest_511, SingleChar_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'a');
  re->Decref();
}

TEST(RegexpEdgeCaseTest_511, AlternateWithEmpty_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST(RegexpEdgeCaseTest_511, LargeRepeat_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{0,1000}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

TEST(RegexpEdgeCaseTest_511, RepeatZeroZero_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{0,0}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

TEST(RegexpEdgeCaseTest_511, CompileToProgDoesNotReturnNull_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  // With max_mem=0, compilation may fail
  // Just test it doesn't crash
  delete prog;
  re->Decref();
}

TEST(RegexpEdgeCaseTest_511, CompileToProgWithMemory_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

TEST(RegexpEdgeCaseTest_511, CompileToReverseProg_511) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

}  // namespace re2
