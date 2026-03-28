#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <string>
#include <map>
#include <memory>

namespace re2 {

// Helper to parse a regexp and return it (caller must Decref)
static Regexp* ParseRegexp(const char* pattern, Regexp::ParseFlags flags = Regexp::LikePerl) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(pattern, flags, &status);
  return re;
}

// ==================== Parse Tests ====================

TEST(RegexpTest_340, ParseSimpleLiteral_340) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

TEST(RegexpTest_340, ParseEmptyString_340) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST(RegexpTest_340, ParseInvalidRegexp_340) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_NE(status.code(), kRegexpSuccess);
}

TEST(RegexpTest_340, ParseAlternation_340) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpAlternate);
  re->Decref();
}

TEST(RegexpTest_340, ParseStar_340) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

TEST(RegexpTest_340, ParsePlus_340) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

TEST(RegexpTest_340, ParseQuest_340) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

TEST(RegexpTest_340, ParseCapture_340) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  re->Decref();
}

TEST(RegexpTest_340, ParseRepeat_340) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST(RegexpTest_340, ParseCharClass_340) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[abc]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCharClass);
  re->Decref();
}

TEST(RegexpTest_340, ParseDot_340) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST(RegexpTest_340, ParseAnchors_340) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc$", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// ==================== ToString Tests ====================

TEST(RegexpTest_340, ToStringSimple_340) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "abc");
  re->Decref();
}

TEST(RegexpTest_340, ToStringAlternation_340) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "a|b");
  re->Decref();
}

TEST(RegexpTest_340, ToStringStar_340) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "a*");
  re->Decref();
}

// ==================== Dump Tests ====================

TEST(RegexpTest_340, DumpNotEmpty_340) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string d = re->Dump();
  EXPECT_FALSE(d.empty());
  re->Decref();
}

// ==================== Static Factory Methods ====================

TEST(RegexpTest_340, NewLiteral_340) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'a');
  re->Decref();
}

TEST(RegexpTest_340, LiteralString_340) {
  Rune runes[] = {'h', 'e', 'l', 'l', 'o'};
  Regexp* re = Regexp::LiteralString(runes, 5, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 5);
  re->Decref();
}

TEST(RegexpTest_340, HaveMatch_340) {
  Regexp* re = Regexp::HaveMatch(42, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), 42);
  re->Decref();
}

TEST(RegexpTest_340, StarFactory_340) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(sub, nullptr);
  Regexp* re = Regexp::Star(sub, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

TEST(RegexpTest_340, PlusFactory_340) {
  Regexp* sub = Regexp::NewLiteral('b', Regexp::LikePerl);
  ASSERT_NE(sub, nullptr);
  Regexp* re = Regexp::Plus(sub, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

TEST(RegexpTest_340, QuestFactory_340) {
  Regexp* sub = Regexp::NewLiteral('c', Regexp::LikePerl);
  ASSERT_NE(sub, nullptr);
  Regexp* re = Regexp::Quest(sub, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

TEST(RegexpTest_340, ConcatFactory_340) {
  Regexp* subs[3];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  subs[2] = Regexp::NewLiteral('c', Regexp::LikePerl);
  Regexp* re = Regexp::Concat(subs, 3, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpConcat);
  re->Decref();
}

TEST(RegexpTest_340, ConcatFactoryEmpty_340) {
  Regexp* re = Regexp::Concat(nullptr, 0, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  re->Decref();
}

TEST(RegexpTest_340, ConcatFactorySingle_340) {
  Regexp* sub = Regexp::NewLiteral('x', Regexp::LikePerl);
  Regexp* re = Regexp::Concat(&sub, 1, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  // Single element concat should just return the sub itself
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

TEST(RegexpTest_340, AlternateFactory_340) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  Regexp* re = Regexp::Alternate(subs, 2, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST(RegexpTest_340, AlternateFactoryEmpty_340) {
  Regexp* re = Regexp::Alternate(nullptr, 0, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpNoMatch);
  re->Decref();
}

TEST(RegexpTest_340, AlternateFactorySingle_340) {
  Regexp* sub = Regexp::NewLiteral('y', Regexp::LikePerl);
  Regexp* re = Regexp::Alternate(&sub, 1, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

TEST(RegexpTest_340, AlternateNoFactor_340) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  Regexp* re = Regexp::AlternateNoFactor(subs, 2, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST(RegexpTest_340, CaptureFactory_340) {
  Regexp* sub = Regexp::NewLiteral('z', Regexp::LikePerl);
  Regexp* re = Regexp::Capture(sub, Regexp::LikePerl, 1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 1);
  re->Decref();
}

TEST(RegexpTest_340, RepeatFactory_340) {
  Regexp* sub = Regexp::NewLiteral('w', Regexp::LikePerl);
  Regexp* re = Regexp::Repeat(sub, Regexp::LikePerl, 2, 5);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), 5);
  re->Decref();
}

TEST(RegexpTest_340, RepeatFactoryExact_340) {
  Regexp* sub = Regexp::NewLiteral('v', Regexp::LikePerl);
  Regexp* re = Regexp::Repeat(sub, Regexp::LikePerl, 3, 3);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 3);
  EXPECT_EQ(re->max(), 3);
  re->Decref();
}

// ==================== Ref Counting Tests ====================

TEST(RegexpTest_340, IncrefDecref_340) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  Regexp* re2 = re->Incref();
  EXPECT_EQ(re2, re);
  // Decref twice to balance
  re->Decref();
  re->Decref();
}

// ==================== NumCaptures Tests ====================

TEST(RegexpTest_340, NumCapturesNone_340) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

TEST(RegexpTest_340, NumCapturesOne_340) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 1);
  re->Decref();
}

TEST(RegexpTest_340, NumCapturesMultiple_340) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

TEST(RegexpTest_340, NumCapturesNested_340) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((a)(b))", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// ==================== NamedCaptures Tests ====================

TEST(RegexpTest_340, NamedCapturesNone_340) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* named = re->NamedCaptures();
  EXPECT_EQ(named, nullptr);
  delete named;
  re->Decref();
}

TEST(RegexpTest_340, NamedCapturesPresent_340) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<name>abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* named = re->NamedCaptures();
  ASSERT_NE(named, nullptr);
  EXPECT_EQ(named->size(), 1u);
  EXPECT_EQ((*named)["name"], 1);
  delete named;
  re->Decref();
}

// ==================== CaptureNames Tests ====================

TEST(RegexpTest_340, CaptureNamesNone_340) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<int, std::string>* names = re->CaptureNames();
  EXPECT_EQ(names, nullptr);
  delete names;
  re->Decref();
}

TEST(RegexpTest_340, CaptureNamesPresent_340) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<foo>abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<int, std::string>* names = re->CaptureNames();
  ASSERT_NE(names, nullptr);
  EXPECT_EQ(names->size(), 1u);
  EXPECT_EQ((*names)[1], "foo");
  delete names;
  re->Decref();
}

// ==================== Simplify Tests ====================

TEST(RegexpTest_340, SimplifyBasic_340) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

TEST(RegexpTest_340, SimplifyRegexpStatic_340) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{2,4}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

// ==================== RequiredPrefix Tests ====================

TEST(RegexpTest_340, RequiredPrefixLiteral_340) {
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

TEST(RegexpTest_340, RequiredPrefixNone_340) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase;
  Regexp* suffix = nullptr;
  bool has_prefix = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  EXPECT_FALSE(has_prefix);
  re->Decref();
}

TEST(RegexpTest_340, RequiredPrefixForAccel_340) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^hello", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase;
  bool has_prefix = re->RequiredPrefixForAccel(&prefix, &foldcase);
  if (has_prefix) {
    EXPECT_FALSE(prefix.empty());
  }
  re->Decref();
}

// ==================== CompileToProg Tests ====================

TEST(RegexpTest_340, CompileToProgBasic_340) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

TEST(RegexpTest_340, CompileToReverseProgBasic_340) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// ==================== Op and Properties Tests ====================

TEST(RegexpTest_340, OpLiteral_340) {
  Regexp* re = Regexp::NewLiteral('x', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

TEST(RegexpTest_340, NsubConcat_340) {
  Regexp* subs[3];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  subs[2] = Regexp::NewLiteral('c', Regexp::LikePerl);
  Regexp* re = Regexp::Concat(subs, 3, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->nsub(), 3);
  re->Decref();
}

TEST(RegexpTest_340, ParseFlags_340) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->parse_flags() & Regexp::LikePerl, Regexp::LikePerl);
  re->Decref();
}

// ==================== NullWalk Test ====================

TEST(RegexpTest_340, NullWalkDoesNotCrash_340) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a+)(b*)|c", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->NullWalk();
  re->Decref();
}

// ==================== MimicsPCRE Test ====================

TEST(RegexpTest_340, MimicsPCRESimple_340) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // Simple literals should mimic PCRE
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// ==================== Quest (from partial code) Tests ====================

TEST(RegexpTest_340, QuestSetsOpCorrectly_340) {
  Regexp* sub = Regexp::NewLiteral('q', Regexp::LikePerl);
  ASSERT_NE(sub, nullptr);
  Regexp* re = Regexp::Quest(sub, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  EXPECT_EQ(re->nsub(), 1);
  re->Decref();
}

TEST(RegexpTest_340, QuestNonGreedy_340) {
  Regexp* sub = Regexp::NewLiteral('r', Regexp::LikePerl);
  ASSERT_NE(sub, nullptr);
  Regexp* re = Regexp::Quest(sub, static_cast<Regexp::ParseFlags>(Regexp::LikePerl | Regexp::NonGreedy));
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

// ==================== Complex Patterns ====================

TEST(RegexpTest_340, ParseComplexPattern_340) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:a|b)*c+[d-f]{2,4}(?P<grp>\\d+)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  
  EXPECT_EQ(re->NumCaptures(), 1);
  
  std::map<std::string, int>* named = re->NamedCaptures();
  ASSERT_NE(named, nullptr);
  EXPECT_EQ((*named)["grp"], 1);
  delete named;
  
  re->Decref();
}

TEST(RegexpTest_340, ParseWordBoundary_340) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\bword\\b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

// ==================== Boundary: Repeat with min=0, max=0 ====================

TEST(RegexpTest_340, RepeatZeroZero_340) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Repeat(sub, Regexp::LikePerl, 0, 0);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// ==================== Boundary: Repeat unbounded ====================

TEST(RegexpTest_340, RepeatUnbounded_340) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Repeat(sub, Regexp::LikePerl, 1, -1);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// ==================== LiteralString with single rune ====================

TEST(RegexpTest_340, LiteralStringSingleRune_340) {
  Rune runes[] = {'x'};
  Regexp* re = Regexp::LiteralString(runes, 1, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// ==================== Multiple Incref/Decref ====================

TEST(RegexpTest_340, MultipleIncrefDecref_340) {
  Regexp* re = Regexp::NewLiteral('m', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Incref();
  re->Incref();
  re->Incref();
  // Now ref count should be 4, need 4 Decrefs
  re->Decref();
  re->Decref();
  re->Decref();
  re->Decref();
}

// ==================== Simplify roundtrip ====================

TEST(RegexpTest_340, SimplifyRegexpRoundtrip_340) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a?", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

TEST(RegexpTest_340, SimplifyRegexpComplex_340) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("(a{0,3}|b+)*", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
}

// ==================== Parse with POSIX flags ====================

TEST(RegexpTest_340, ParsePOSIX_340) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// ==================== Sub access for Star ====================

TEST(RegexpTest_340, StarSubAccess_340) {
  Regexp* sub = Regexp::NewLiteral('s', Regexp::LikePerl);
  Regexp* re = Regexp::Star(sub, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  EXPECT_EQ(re->nsub(), 1);
  Regexp** subs = re->sub();
  ASSERT_NE(subs, nullptr);
  EXPECT_EQ(subs[0]->op(), kRegexpLiteral);
  re->Decref();
}

// ==================== HaveMatch with zero ====================

TEST(RegexpTest_340, HaveMatchZero_340) {
  Regexp* re = Regexp::HaveMatch(0, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), 0);
  re->Decref();
}

// ==================== Capture with cap=0 ====================

TEST(RegexpTest_340, CaptureZero_340) {
  Regexp* sub = Regexp::NewLiteral('t', Regexp::LikePerl);
  Regexp* re = Regexp::Capture(sub, Regexp::LikePerl, 0);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 0);
  re->Decref();
}

}  // namespace re2
