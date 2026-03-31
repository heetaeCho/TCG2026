#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <map>
#include <string>

namespace re2 {

// Test Parse with a simple literal string
TEST(RegexpTest_365, ParseSimpleLiteral_365) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test Parse with an empty string
TEST(RegexpTest_365, ParseEmptyString_365) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test Parse with invalid regex
TEST(RegexpTest_365, ParseInvalidRegex_365) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

// Test NumCaptures with no captures
TEST(RegexpTest_365, NumCapturesZero_365) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

// Test NumCaptures with captures
TEST(RegexpTest_365, NumCapturesMultiple_365) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// Test NumCaptures with nested captures
TEST(RegexpTest_365, NumCapturesNested_365) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((a)(b))", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// Test NamedCaptures returns nullptr when no named captures
TEST(RegexpTest_365, NamedCapturesNone_365) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* names = re->NamedCaptures();
  EXPECT_EQ(names, nullptr);
  delete names;
  re->Decref();
}

// Test NamedCaptures with named captures
TEST(RegexpTest_365, NamedCapturesPresent_365) {
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

// Test CaptureNames returns nullptr when no captures
TEST(RegexpTest_365, CaptureNamesNone_365) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<int, std::string>* names = re->CaptureNames();
  EXPECT_EQ(names, nullptr);
  delete names;
  re->Decref();
}

// Test CaptureNames with named captures
TEST(RegexpTest_365, CaptureNamesPresent_365) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<first>a)(?P<second>b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<int, std::string>* names = re->CaptureNames();
  ASSERT_NE(names, nullptr);
  EXPECT_EQ(names->size(), 2u);
  EXPECT_EQ((*names)[1], "first");
  EXPECT_EQ((*names)[2], "second");
  delete names;
  re->Decref();
}

// Test CaptureNames with mixed named and unnamed captures
TEST(RegexpTest_365, CaptureNamesMixed_365) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(?P<named>b)(c)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<int, std::string>* names = re->CaptureNames();
  // Should contain at least the named capture
  if (names != nullptr) {
    EXPECT_NE(names->find(2), names->end());
    EXPECT_EQ((*names)[2], "named");
  }
  delete names;
  re->Decref();
}

// Test ToString roundtrip
TEST(RegexpTest_365, ToStringSimple_365) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test Dump produces non-empty string
TEST(RegexpTest_365, DumpNonEmpty_365) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string d = re->Dump();
  EXPECT_FALSE(d.empty());
  re->Decref();
}

// Test Incref and Decref
TEST(RegexpTest_365, IncrefDecref_365) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* re2 = re->Incref();
  EXPECT_EQ(re, re2);
  re->Decref();
  re->Decref();
}

// Test Simplify
TEST(RegexpTest_365, Simplify_365) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{1,1}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simple = re->Simplify();
  ASSERT_NE(simple, nullptr);
  simple->Decref();
  re->Decref();
}

// Test SimplifyRegexp static method
TEST(RegexpTest_365, SimplifyRegexpStatic_365) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{2,3}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

// Test SimplifyRegexp with invalid input
TEST(RegexpTest_365, SimplifyRegexpInvalid_365) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("[invalid", Regexp::LikePerl, &dst, &status);
  EXPECT_FALSE(ok);
}

// Test NewLiteral
TEST(RegexpTest_365, NewLiteral_365) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'a');
  re->Decref();
}

// Test HaveMatch
TEST(RegexpTest_365, HaveMatch_365) {
  Regexp* re = Regexp::HaveMatch(42, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), 42);
  re->Decref();
}

// Test Plus
TEST(RegexpTest_365, Plus_365) {
  Regexp* lit = Regexp::NewLiteral('x', Regexp::LikePerl);
  Regexp* plus = Regexp::Plus(lit, Regexp::LikePerl);
  ASSERT_NE(plus, nullptr);
  EXPECT_EQ(plus->op(), kRegexpPlus);
  plus->Decref();
}

// Test Star
TEST(RegexpTest_365, Star_365) {
  Regexp* lit = Regexp::NewLiteral('x', Regexp::LikePerl);
  Regexp* star = Regexp::Star(lit, Regexp::LikePerl);
  ASSERT_NE(star, nullptr);
  EXPECT_EQ(star->op(), kRegexpStar);
  star->Decref();
}

// Test Quest
TEST(RegexpTest_365, Quest_365) {
  Regexp* lit = Regexp::NewLiteral('x', Regexp::LikePerl);
  Regexp* quest = Regexp::Quest(lit, Regexp::LikePerl);
  ASSERT_NE(quest, nullptr);
  EXPECT_EQ(quest->op(), kRegexpQuest);
  quest->Decref();
}

// Test Concat
TEST(RegexpTest_365, Concat_365) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  Regexp* cat = Regexp::Concat(subs, 2, Regexp::LikePerl);
  ASSERT_NE(cat, nullptr);
  cat->Decref();
}

// Test Alternate
TEST(RegexpTest_365, Alternate_365) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  Regexp* alt = Regexp::Alternate(subs, 2, Regexp::LikePerl);
  ASSERT_NE(alt, nullptr);
  alt->Decref();
}

// Test AlternateNoFactor
TEST(RegexpTest_365, AlternateNoFactor_365) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  Regexp* alt = Regexp::AlternateNoFactor(subs, 2, Regexp::LikePerl);
  ASSERT_NE(alt, nullptr);
  alt->Decref();
}

// Test Capture
TEST(RegexpTest_365, Capture_365) {
  Regexp* lit = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* cap = Regexp::Capture(lit, Regexp::LikePerl, 1);
  ASSERT_NE(cap, nullptr);
  EXPECT_EQ(cap->op(), kRegexpCapture);
  EXPECT_EQ(cap->cap(), 1);
  cap->Decref();
}

// Test Repeat
TEST(RegexpTest_365, Repeat_365) {
  Regexp* lit = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* rep = Regexp::Repeat(lit, Regexp::LikePerl, 2, 5);
  ASSERT_NE(rep, nullptr);
  EXPECT_EQ(rep->op(), kRegexpRepeat);
  EXPECT_EQ(rep->min(), 2);
  EXPECT_EQ(rep->max(), 5);
  rep->Decref();
}

// Test LiteralString
TEST(RegexpTest_365, LiteralString_365) {
  Rune runes[] = {'h', 'e', 'l', 'l', 'o'};
  Regexp* re = Regexp::LiteralString(runes, 5, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 5);
  re->Decref();
}

// Test RequiredPrefix on a pattern with a known prefix
TEST(RegexpTest_365, RequiredPrefix_365) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc.*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
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

// Test RequiredPrefix on pattern without prefix
TEST(RegexpTest_365, RequiredPrefixNone_365) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".*abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;
  bool has_prefix = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  if (!has_prefix) {
    EXPECT_TRUE(prefix.empty());
  }
  if (suffix != nullptr) {
    suffix->Decref();
  }
  re->Decref();
}

// Test RequiredPrefixForAccel
TEST(RegexpTest_365, RequiredPrefixForAccel_365) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^hello.*world", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  re->RequiredPrefixForAccel(&prefix, &foldcase);
  // Just check it doesn't crash; result depends on implementation
  re->Decref();
}

// Test CompileToProg
TEST(RegexpTest_365, CompileToProg_365) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileToReverseProg
TEST(RegexpTest_365, CompileToReverseProg_365) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test NullWalk doesn't crash
TEST(RegexpTest_365, NullWalk_365) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a|b)*c+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->NullWalk();
  re->Decref();
}

// Test op() accessor
TEST(RegexpTest_365, OpAccessor_365) {
  Regexp* re = Regexp::NewLiteral('z', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// Test parse_flags() accessor
TEST(RegexpTest_365, ParseFlagsAccessor_365) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // parse_flags should be set
  Regexp::ParseFlags flags = re->parse_flags();
  (void)flags;  // Just ensure it's accessible
  re->Decref();
}

// Test Concat with zero subs
TEST(RegexpTest_365, ConcatZeroSubs_365) {
  Regexp* cat = Regexp::Concat(nullptr, 0, Regexp::LikePerl);
  ASSERT_NE(cat, nullptr);
  cat->Decref();
}

// Test Alternate with zero subs
TEST(RegexpTest_365, AlternateZeroSubs_365) {
  Regexp* alt = Regexp::Alternate(nullptr, 0, Regexp::LikePerl);
  ASSERT_NE(alt, nullptr);
  alt->Decref();
}

// Test Concat with single sub
TEST(RegexpTest_365, ConcatSingleSub_365) {
  Regexp* subs[1];
  subs[0] = Regexp::NewLiteral('x', Regexp::LikePerl);
  Regexp* cat = Regexp::Concat(subs, 1, Regexp::LikePerl);
  ASSERT_NE(cat, nullptr);
  cat->Decref();
}

// Test Alternate with single sub
TEST(RegexpTest_365, AlternateSingleSub_365) {
  Regexp* subs[1];
  subs[0] = Regexp::NewLiteral('y', Regexp::LikePerl);
  Regexp* alt = Regexp::Alternate(subs, 1, Regexp::LikePerl);
  ASSERT_NE(alt, nullptr);
  alt->Decref();
}

// Test complex regex parse and ToString
TEST(RegexpTest_365, ComplexRegexToString_365) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:(?P<a>x)|(?P<b>y))+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test MimicsPCRE
TEST(RegexpTest_365, MimicsPCRE_365) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // Just check it doesn't crash and returns a boolean
  bool result = re->MimicsPCRE();
  (void)result;
  re->Decref();
}

// Test Repeat with min == max
TEST(RegexpTest_365, RepeatExact_365) {
  Regexp* lit = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* rep = Regexp::Repeat(lit, Regexp::LikePerl, 3, 3);
  ASSERT_NE(rep, nullptr);
  EXPECT_EQ(rep->min(), 3);
  EXPECT_EQ(rep->max(), 3);
  rep->Decref();
}

// Test Repeat with unbounded max (-1 typically means unbounded)
TEST(RegexpTest_365, RepeatUnbounded_365) {
  Regexp* lit = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* rep = Regexp::Repeat(lit, Regexp::LikePerl, 1, -1);
  ASSERT_NE(rep, nullptr);
  EXPECT_EQ(rep->min(), 1);
  EXPECT_EQ(rep->max(), -1);
  rep->Decref();
}

// Test sub() accessor for Plus
TEST(RegexpTest_365, SubAccessor_365) {
  Regexp* lit = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* plus = Regexp::Plus(lit, Regexp::LikePerl);
  ASSERT_NE(plus, nullptr);
  EXPECT_EQ(plus->nsub(), 1);
  EXPECT_NE(plus->sub(), nullptr);
  plus->Decref();
}

// Test Parse with character class
TEST(RegexpTest_365, ParseCharacterClass_365) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z0-9]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test Parse with anchors
TEST(RegexpTest_365, ParseAnchors_365) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc$", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test Parse with escape sequences
TEST(RegexpTest_365, ParseEscapeSequences_365) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\d+\\s\\w+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test LiteralString with single rune
TEST(RegexpTest_365, LiteralStringSingleRune_365) {
  Rune runes[] = {'a'};
  Regexp* re = Regexp::LiteralString(runes, 1, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test simple() accessor
TEST(RegexpTest_365, SimpleAccessor_365) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // After simplify, simple() should be accessible
  Regexp* simple_re = re->Simplify();
  ASSERT_NE(simple_re, nullptr);
  // simple() should return a bool value
  bool is_simple = simple_re->simple();
  (void)is_simple;
  simple_re->Decref();
  re->Decref();
}

}  // namespace re2
