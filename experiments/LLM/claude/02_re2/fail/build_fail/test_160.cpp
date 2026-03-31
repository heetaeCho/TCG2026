#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <string>
#include <map>
#include <memory>

namespace re2 {

class RegexpTest_160 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// --- Parse Tests ---

TEST_F(RegexpTest_160, ParseSimpleLiteral_160) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

TEST_F(RegexpTest_160, ParseEmptyString_160) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST_F(RegexpTest_160, ParseInvalidRegexp_160) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[invalid", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

TEST_F(RegexpTest_160, ParseAlternation_160) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b|c", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->op(), kRegexpAlternate);
  re->Decref();
}

TEST_F(RegexpTest_160, ParseConcatenation_160) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST_F(RegexpTest_160, ParseStar_160) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

TEST_F(RegexpTest_160, ParsePlus_160) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

TEST_F(RegexpTest_160, ParseQuest_160) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

TEST_F(RegexpTest_160, ParseCapture_160) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->op(), kRegexpCapture);
  re->Decref();
}

TEST_F(RegexpTest_160, ParseRepeat_160) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), 5);
  re->Decref();
}

TEST_F(RegexpTest_160, ParseCharClass_160) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->op(), kRegexpCharClass);
  re->Decref();
}

TEST_F(RegexpTest_160, ParseDot_160) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST_F(RegexpTest_160, ParseAnchors_160) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc$", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// --- ToString Tests ---

TEST_F(RegexpTest_160, ToStringRoundTrip_160) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a(b+)c", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

TEST_F(RegexpTest_160, ToStringLiteral_160) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "hello");
  re->Decref();
}

// --- Dump Tests ---

TEST_F(RegexpTest_160, DumpProducesOutput_160) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+b*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string dump = re->Dump();
  EXPECT_FALSE(dump.empty());
  re->Decref();
}

// --- Ref / Incref / Decref Tests ---

TEST_F(RegexpTest_160, RefCountInitiallyOne_160) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  // After creation, ref should be >= 1
  // Incref increases it, then Decref to balance
  Regexp* re2 = re->Incref();
  EXPECT_EQ(re, re2);
  re->Decref();
  re->Decref();
}

// --- NumCaptures Tests ---

TEST_F(RegexpTest_160, NumCapturesNone_160) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

TEST_F(RegexpTest_160, NumCapturesOne_160) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 1);
  re->Decref();
}

TEST_F(RegexpTest_160, NumCapturesMultiple_160) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

TEST_F(RegexpTest_160, NumCapturesNested_160) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((a)(b))", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// --- NamedCaptures Tests ---

TEST_F(RegexpTest_160, NamedCapturesNone_160) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* caps = re->NamedCaptures();
  EXPECT_EQ(caps, nullptr);
  delete caps;
  re->Decref();
}

TEST_F(RegexpTest_160, NamedCapturesPresent_160) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<name>abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* caps = re->NamedCaptures();
  ASSERT_NE(caps, nullptr);
  EXPECT_EQ(caps->size(), 1u);
  EXPECT_EQ((*caps)["name"], 1);
  delete caps;
  re->Decref();
}

// --- CaptureNames Tests ---

TEST_F(RegexpTest_160, CaptureNamesNone_160) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<int, std::string>* names = re->CaptureNames();
  EXPECT_EQ(names, nullptr);
  delete names;
  re->Decref();
}

TEST_F(RegexpTest_160, CaptureNamesPresent_160) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<foo>a)(?P<bar>b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<int, std::string>* names = re->CaptureNames();
  ASSERT_NE(names, nullptr);
  EXPECT_EQ(names->size(), 2u);
  EXPECT_EQ((*names)[1], "foo");
  EXPECT_EQ((*names)[2], "bar");
  delete names;
  re->Decref();
}

// --- Simplify Tests ---

TEST_F(RegexpTest_160, SimplifyBasic_160) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simple = re->Simplify();
  ASSERT_NE(simple, nullptr);
  std::string s = simple->ToString();
  EXPECT_FALSE(s.empty());
  simple->Decref();
  re->Decref();
}

TEST_F(RegexpTest_160, SimplifyRegexpStatic_160) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{2,3}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

// --- Static Factory Methods ---

TEST_F(RegexpTest_160, NewLiteral_160) {
  Regexp* re = Regexp::NewLiteral('x', Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'x');
  re->Decref();
}

TEST_F(RegexpTest_160, LiteralString_160) {
  Rune runes[] = {'h', 'e', 'l', 'l', 'o'};
  Regexp* re = Regexp::LiteralString(runes, 5, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 5);
  Rune* r = re->runes();
  ASSERT_NE(r, nullptr);
  EXPECT_EQ(r[0], 'h');
  EXPECT_EQ(r[1], 'e');
  EXPECT_EQ(r[2], 'l');
  EXPECT_EQ(r[3], 'l');
  EXPECT_EQ(r[4], 'o');
  re->Decref();
}

TEST_F(RegexpTest_160, HaveMatch_160) {
  Regexp* re = Regexp::HaveMatch(42, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), 42);
  re->Decref();
}

TEST_F(RegexpTest_160, PlusFactory_160) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Plus(sub, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

TEST_F(RegexpTest_160, StarFactory_160) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Star(sub, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

TEST_F(RegexpTest_160, QuestFactory_160) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Quest(sub, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

TEST_F(RegexpTest_160, CaptureFactory_160) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Capture(sub, Regexp::NoParseFlags, 1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 1);
  re->Decref();
}

TEST_F(RegexpTest_160, RepeatFactory_160) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 2, 5);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), 5);
  re->Decref();
}

TEST_F(RegexpTest_160, ConcatFactory_160) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* re = Regexp::Concat(subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_160, AlternateFactory_160) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* re = Regexp::Alternate(subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_160, AlternateNoFactorFactory_160) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* re = Regexp::AlternateNoFactor(subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_160, ConcatEmpty_160) {
  Regexp* re = Regexp::Concat(nullptr, 0, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  re->Decref();
}

TEST_F(RegexpTest_160, AlternateEmpty_160) {
  Regexp* re = Regexp::Alternate(nullptr, 0, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpNoMatch);
  re->Decref();
}

TEST_F(RegexpTest_160, ConcatSingle_160) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* subs[1] = {sub};
  Regexp* re = Regexp::Concat(subs, 1, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// --- Accessors ---

TEST_F(RegexpTest_160, OpAccessor_160) {
  Regexp* re = Regexp::NewLiteral('z', Regexp::NoParseFlags);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

TEST_F(RegexpTest_160, ParseFlagsAccessor_160) {
  Regexp* re = Regexp::NewLiteral('z', Regexp::FoldCase);
  EXPECT_NE(re->parse_flags() & Regexp::FoldCase, 0);
  re->Decref();
}

TEST_F(RegexpTest_160, NsubAccessor_160) {
  Regexp* subs[3];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  subs[2] = Regexp::NewLiteral('c', Regexp::NoParseFlags);
  Regexp* re = Regexp::Concat(subs, 3, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  if (re->op() == kRegexpConcat) {
    EXPECT_EQ(re->nsub(), 3);
  }
  re->Decref();
}

TEST_F(RegexpTest_160, SubAccessor_160) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* re = Regexp::Concat(subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  if (re->op() == kRegexpConcat) {
    Regexp** s = re->sub();
    ASSERT_NE(s, nullptr);
    EXPECT_EQ(s[0]->op(), kRegexpLiteral);
    EXPECT_EQ(s[1]->op(), kRegexpLiteral);
  }
  re->Decref();
}

// --- RequiredPrefix Tests ---

TEST_F(RegexpTest_160, RequiredPrefixSimple_160) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^hello.*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase;
  Regexp* suffix = nullptr;
  bool has_prefix = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  if (has_prefix) {
    EXPECT_FALSE(prefix.empty());
    EXPECT_FALSE(foldcase);
    if (suffix != nullptr) {
      suffix->Decref();
    }
  }
  re->Decref();
}

TEST_F(RegexpTest_160, RequiredPrefixNone_160) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".*hello", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase;
  Regexp* suffix = nullptr;
  bool has_prefix = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  EXPECT_FALSE(has_prefix);
  re->Decref();
}

// --- RequiredPrefixForAccel Tests ---

TEST_F(RegexpTest_160, RequiredPrefixForAccel_160) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^test.*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase;
  bool has = re->RequiredPrefixForAccel(&prefix, &foldcase);
  if (has) {
    EXPECT_FALSE(prefix.empty());
  }
  re->Decref();
}

// --- CompileToProg Tests ---

TEST_F(RegexpTest_160, CompileToProg_160) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

TEST_F(RegexpTest_160, CompileToReverseProg_160) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// --- NullWalk Tests ---

TEST_F(RegexpTest_160, NullWalkDoesNotCrash_160) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a|b)*c+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // NullWalk should not crash
  re->NullWalk();
  re->Decref();
}

// --- MimicsPCRE Tests ---

TEST_F(RegexpTest_160, MimicsPCRESimple_160) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // Simple literal should mimic PCRE
  bool mimics = re->MimicsPCRE();
  EXPECT_TRUE(mimics);
  re->Decref();
}

// --- Simple accessor ---

TEST_F(RegexpTest_160, SimpleAfterSimplify_160) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simple = re->Simplify();
  ASSERT_NE(simple, nullptr);
  // After simplification, simple() should return a valid boolean
  bool is_simple = simple->simple();
  (void)is_simple;  // Just verify it doesn't crash
  simple->Decref();
  re->Decref();
}

// --- Word Boundary ---

TEST_F(RegexpTest_160, ParseWordBoundary_160) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\bhello\\b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// --- Complex Regex ---

TEST_F(RegexpTest_160, ParseComplexRegex_160) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// --- LiteralString with single rune ---

TEST_F(RegexpTest_160, LiteralStringSingleRune_160) {
  Rune runes[] = {'x'};
  Regexp* re = Regexp::LiteralString(runes, 1, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  // With single rune, could be kRegexpLiteral or kRegexpLiteralString
  re->Decref();
}

// --- Repeat with same min and max ---

TEST_F(RegexpTest_160, RepeatExact_160) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 3, 3);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 3);
  EXPECT_EQ(re->max(), 3);
  re->Decref();
}

// --- Repeat with unbounded max (typically -1) ---

TEST_F(RegexpTest_160, RepeatUnbounded_160) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 1, -1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 1);
  EXPECT_EQ(re->max(), -1);
  re->Decref();
}

// --- Multiple named captures ---

TEST_F(RegexpTest_160, MultipleNamedCaptures_160) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<first>a)(?P<second>b)(?P<third>c)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  std::map<std::string, int>* caps = re->NamedCaptures();
  ASSERT_NE(caps, nullptr);
  EXPECT_EQ(caps->size(), 3u);
  EXPECT_EQ((*caps)["first"], 1);
  EXPECT_EQ((*caps)["second"], 2);
  EXPECT_EQ((*caps)["third"], 3);
  delete caps;
  re->Decref();
}

// --- Parse with FoldCase ---

TEST_F(RegexpTest_160, ParseFoldCase_160) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?i)abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// --- Unbalanced parens error ---

TEST_F(RegexpTest_160, ParseUnbalancedParens_160) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

TEST_F(RegexpTest_160, ParseBadRepeat_160) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("*abc", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

// --- Simplify idempotent ---

TEST_F(RegexpTest_160, SimplifyIdempotent_160) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* s1 = re->Simplify();
  ASSERT_NE(s1, nullptr);
  Regexp* s2 = s1->Simplify();
  ASSERT_NE(s2, nullptr);
  EXPECT_EQ(s1->ToString(), s2->ToString());
  s2->Decref();
  s1->Decref();
  re->Decref();
}

// --- HaveMatch with zero ---

TEST_F(RegexpTest_160, HaveMatchZero_160) {
  Regexp* re = Regexp::HaveMatch(0, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), 0);
  re->Decref();
}

// --- SimplifyRegexp error case ---

TEST_F(RegexpTest_160, SimplifyRegexpInvalid_160) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("[invalid", Regexp::LikePerl, &dst, &status);
  EXPECT_FALSE(ok);
}

}  // namespace re2
