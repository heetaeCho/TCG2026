#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include "util/logging.h"

namespace re2 {

// Test basic parsing of simple literals
TEST(RegexpParseTest_498, ParseSimpleLiteral_498) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test parsing empty string
TEST(RegexpParseTest_498, ParseEmptyString_498) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test parsing with repetition operators
TEST(RegexpParseTest_498, ParseRepetition_498) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*b+c?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test parsing character class
TEST(RegexpParseTest_498, ParseCharClass_498) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test parsing alternation
TEST(RegexpParseTest_498, ParseAlternation_498) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b|c", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test parsing capture groups
TEST(RegexpParseTest_498, ParseCaptureGroup_498) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc)(def)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->NumCaptures(), 2);
  re->Decref();
}

// Test parsing named capture groups
TEST(RegexpParseTest_498, ParseNamedCapture_498) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<name>abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->NumCaptures(), 1);
  auto* named = re->NamedCaptures();
  ASSERT_NE(named, nullptr);
  EXPECT_EQ(named->count("name"), 1);
  delete named;
  re->Decref();
}

// Test parsing invalid regex
TEST(RegexpParseTest_498, ParseInvalidRegex_498) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

// Test parsing invalid regex - bad repetition
TEST(RegexpParseTest_498, ParseInvalidRepetition_498) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("*abc", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

// Test parsing counted repetition
TEST(RegexpParseTest_498, ParseCountedRepetition_498) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test parsing exact repetition
TEST(RegexpParseTest_498, ParseExactRepetition_498) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test parsing minimum repetition
TEST(RegexpParseTest_498, ParseMinRepetition_498) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3,}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test parsing anchors
TEST(RegexpParseTest_498, ParseAnchors_498) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc$", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test parsing dot (any character)
TEST(RegexpParseTest_498, ParseDot_498) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a.b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test parsing escape sequences
TEST(RegexpParseTest_498, ParseEscapeSequences_498) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\d\\w\\s", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test parsing negated character class
TEST(RegexpParseTest_498, ParseNegatedCharClass_498) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[^a-z]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test ToString roundtrip
TEST(RegexpParseTest_498, ToStringRoundtrip_498) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test Dump
TEST(RegexpParseTest_498, Dump_498) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a(b)c", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string d = re->Dump();
  EXPECT_FALSE(d.empty());
  re->Decref();
}

// Test NumCaptures with no captures
TEST(RegexpParseTest_498, NumCapturesZero_498) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

// Test NumCaptures with multiple captures
TEST(RegexpParseTest_498, NumCapturesMultiple_498) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// Test nested captures
TEST(RegexpParseTest_498, NumCapturesNested_498) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((a)(b))", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// Test CaptureNames
TEST(RegexpParseTest_498, CaptureNames_498) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<first>a)(?P<second>b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  auto* names = re->CaptureNames();
  ASSERT_NE(names, nullptr);
  EXPECT_EQ(names->size(), 2u);
  EXPECT_EQ((*names)[1], "first");
  EXPECT_EQ((*names)[2], "second");
  delete names;
  re->Decref();
}

// Test Simplify
TEST(RegexpParseTest_498, Simplify_498) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// Test SimplifyRegexp static method
TEST(RegexpParseTest_498, SimplifyRegexpStatic_498) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{2,5}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

// Test RequiredPrefix
TEST(RegexpParseTest_498, RequiredPrefix_498) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc.*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase;
  Regexp* suffix = nullptr;
  bool has_prefix = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  if (has_prefix) {
    EXPECT_FALSE(prefix.empty());
    if (suffix != nullptr) {
      suffix->Decref();
    }
  }
  re->Decref();
}

// Test Incref and Decref
TEST(RegexpParseTest_498, IncrefDecref_498) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* re2 = re->Incref();
  EXPECT_EQ(re, re2);
  re->Decref();
  re->Decref();
}

// Test parsing with POSIX flags
TEST(RegexpParseTest_498, ParsePOSIX_498) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc|def", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test parsing non-greedy operators
TEST(RegexpParseTest_498, ParseNonGreedy_498) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*?b+?c??", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test parsing complex regex
TEST(RegexpParseTest_498, ParseComplex_498) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:a|b)*(?P<name>\\d+)\\.\\w+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->NumCaptures(), 1);
  re->Decref();
}

// Test parsing unmatched close paren
TEST(RegexpParseTest_498, ParseUnmatchedCloseParen_498) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc)", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

// Test parsing bad escape
TEST(RegexpParseTest_498, ParseBadEscape_498) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

// Test parsing Unicode
TEST(RegexpParseTest_498, ParseUnicode_498) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\p{Greek}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test parsing deeply nested groups
TEST(RegexpParseTest_498, ParseDeepNesting_498) {
  RegexpStatus status;
  std::string pattern = "";
  for (int i = 0; i < 50; i++) pattern += "(";
  pattern += "a";
  for (int i = 0; i < 50; i++) pattern += ")";
  Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->NumCaptures(), 50);
  re->Decref();
}

// Test NullWalk doesn't crash
TEST(RegexpParseTest_498, NullWalk_498) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a(b|c)*d", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->NullWalk();
  re->Decref();
}

// Test parsing with FoldCase flag
TEST(RegexpParseTest_498, ParseFoldCase_498) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl | Regexp::FoldCase, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test HaveMatch
TEST(RegexpParseTest_498, HaveMatch_498) {
  Regexp* re = Regexp::HaveMatch(1, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), 1);
  re->Decref();
}

// Test NewLiteral
TEST(RegexpParseTest_498, NewLiteral_498) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'a');
  re->Decref();
}

// Test Plus, Star, Quest factory methods
TEST(RegexpParseTest_498, PlusStarQuest_498) {
  Regexp* lit = Regexp::NewLiteral('x', Regexp::LikePerl);
  
  Regexp* plus = Regexp::Plus(lit->Incref(), Regexp::LikePerl);
  ASSERT_NE(plus, nullptr);
  EXPECT_EQ(plus->op(), kRegexpPlus);
  plus->Decref();
  
  Regexp* star = Regexp::Star(lit->Incref(), Regexp::LikePerl);
  ASSERT_NE(star, nullptr);
  EXPECT_EQ(star->op(), kRegexpStar);
  star->Decref();
  
  Regexp* quest = Regexp::Quest(lit->Incref(), Regexp::LikePerl);
  ASSERT_NE(quest, nullptr);
  EXPECT_EQ(quest->op(), kRegexpQuest);
  quest->Decref();
  
  lit->Decref();
}

// Test Repeat factory method
TEST(RegexpParseTest_498, Repeat_498) {
  Regexp* lit = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* rep = Regexp::Repeat(lit, Regexp::LikePerl, 2, 5);
  ASSERT_NE(rep, nullptr);
  EXPECT_EQ(rep->op(), kRegexpRepeat);
  EXPECT_EQ(rep->min(), 2);
  EXPECT_EQ(rep->max(), 5);
  rep->Decref();
}

// Test Capture factory method
TEST(RegexpParseTest_498, Capture_498) {
  Regexp* lit = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* cap = Regexp::Capture(lit, Regexp::LikePerl, 1);
  ASSERT_NE(cap, nullptr);
  EXPECT_EQ(cap->op(), kRegexpCapture);
  EXPECT_EQ(cap->cap(), 1);
  cap->Decref();
}

// Test Concat factory method
TEST(RegexpParseTest_498, Concat_498) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  Regexp* cat = Regexp::Concat(subs, 2, Regexp::LikePerl);
  ASSERT_NE(cat, nullptr);
  cat->Decref();
}

// Test Alternate factory method
TEST(RegexpParseTest_498, Alternate_498) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  Regexp* alt = Regexp::Alternate(subs, 2, Regexp::LikePerl);
  ASSERT_NE(alt, nullptr);
  alt->Decref();
}

// Test LiteralString factory method
TEST(RegexpParseTest_498, LiteralString_498) {
  Rune runes[] = {'h', 'e', 'l', 'l', 'o'};
  Regexp* re = Regexp::LiteralString(runes, 5, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 5);
  re->Decref();
}

// Test parsing with bad character class
TEST(RegexpParseTest_498, ParseBadCharClass_498) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[z-a]", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

// Test parsing non-capturing group
TEST(RegexpParseTest_498, ParseNonCapturingGroup_498) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

// Test NamedCaptures returns null when no named captures
TEST(RegexpParseTest_498, NamedCapturesNull_498) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  auto* named = re->NamedCaptures();
  EXPECT_EQ(named, nullptr);
  re->Decref();
}

// Test large repetition count
TEST(RegexpParseTest_498, ParseLargeRepetition_498) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{1000}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test CompileToProg
TEST(RegexpParseTest_498, CompileToProg_498) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileToReverseProg
TEST(RegexpParseTest_498, CompileToReverseProg_498) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test RequiredPrefixForAccel
TEST(RegexpParseTest_498, RequiredPrefixForAccel_498) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^hello.*world", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase;
  re->RequiredPrefixForAccel(&prefix, &foldcase);
  // Just checking it doesn't crash; actual behavior depends on impl
  re->Decref();
}

// Test parsing escaped special characters
TEST(RegexpParseTest_498, ParseEscapedSpecial_498) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\[\\]\\(\\)\\{\\}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test AlternateNoFactor
TEST(RegexpParseTest_498, AlternateNoFactor_498) {
  Regexp* subs[3];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  subs[2] = Regexp::NewLiteral('c', Regexp::LikePerl);
  Regexp* alt = Regexp::AlternateNoFactor(subs, 3, Regexp::LikePerl);
  ASSERT_NE(alt, nullptr);
  alt->Decref();
}

// Test single sub concat returns the sub itself
TEST(RegexpParseTest_498, ConcatSingleSub_498) {
  Regexp* subs[1];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* cat = Regexp::Concat(subs, 1, Regexp::LikePerl);
  ASSERT_NE(cat, nullptr);
  cat->Decref();
}

// Test zero sub concat
TEST(RegexpParseTest_498, ConcatZeroSubs_498) {
  Regexp* cat = Regexp::Concat(nullptr, 0, Regexp::LikePerl);
  ASSERT_NE(cat, nullptr);
  cat->Decref();
}

// Test zero sub alternate
TEST(RegexpParseTest_498, AlternateZeroSubs_498) {
  Regexp* alt = Regexp::Alternate(nullptr, 0, Regexp::LikePerl);
  ASSERT_NE(alt, nullptr);
  alt->Decref();
}

}  // namespace re2
