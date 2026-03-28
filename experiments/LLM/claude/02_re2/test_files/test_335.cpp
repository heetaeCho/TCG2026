#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <string>
#include <map>

namespace re2 {

// Helper to parse a regexp and return it (caller must Decref)
static Regexp* ParseRegexp(const char* pattern, Regexp::ParseFlags flags = Regexp::LikePerl) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(pattern, flags, &status);
  return re;
}

// ==================== Incref / Decref / Ref Tests ====================

TEST(RegexpIncrefTest_335, InitialRefCountIsOne_335) {
  Regexp* re = ParseRegexp("a");
  ASSERT_NE(re, nullptr);
  // A freshly parsed regexp that hasn't been shared should have ref count >= 1
  // We can observe this indirectly: calling Incref and then checking Ref
  EXPECT_GE(re->Ref(), 1);
  re->Decref();
}

TEST(RegexpIncrefTest_335, IncrefIncreasesRefCount_335) {
  Regexp* re = ParseRegexp("b");
  ASSERT_NE(re, nullptr);
  int initial_ref = re->Ref();
  re->Incref();
  EXPECT_EQ(re->Ref(), initial_ref + 1);
  re->Decref();
  re->Decref();
}

TEST(RegexpIncrefTest_335, MultipleIncrefDecref_335) {
  Regexp* re = ParseRegexp("c");
  ASSERT_NE(re, nullptr);
  int initial_ref = re->Ref();
  re->Incref();
  re->Incref();
  re->Incref();
  EXPECT_EQ(re->Ref(), initial_ref + 3);
  re->Decref();
  re->Decref();
  re->Decref();
  EXPECT_EQ(re->Ref(), initial_ref);
  re->Decref();
}

TEST(RegexpIncrefTest_335, IncrefReturnsSamePointer_335) {
  Regexp* re = ParseRegexp("d");
  ASSERT_NE(re, nullptr);
  Regexp* re2 = re->Incref();
  EXPECT_EQ(re, re2);
  re->Decref();
  re->Decref();
}

// ==================== Parse Tests ====================

TEST(RegexpParseTest_335, SimpleCharParse_335) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST(RegexpParseTest_335, EmptyPattern_335) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST(RegexpParseTest_335, ComplexPattern_335) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a|b)*c+d?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST(RegexpParseTest_335, InvalidPattern_335) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

TEST(RegexpParseTest_335, InvalidPatternUnmatchedBracket_335) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[abc", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

// ==================== ToString Tests ====================

TEST(RegexpToStringTest_335, SimpleLiteral_335) {
  Regexp* re = ParseRegexp("abc");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "abc");
  re->Decref();
}

TEST(RegexpToStringTest_335, Alternation_335) {
  Regexp* re = ParseRegexp("a|b");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "a|b");
  re->Decref();
}

TEST(RegexpToStringTest_335, Repetition_335) {
  Regexp* re = ParseRegexp("a*");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "a*");
  re->Decref();
}

// ==================== NumCaptures Tests ====================

TEST(RegexpNumCapturesTest_335, NoCaptures_335) {
  Regexp* re = ParseRegexp("abc");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

TEST(RegexpNumCapturesTest_335, OneCapture_335) {
  Regexp* re = ParseRegexp("(a)bc");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 1);
  re->Decref();
}

TEST(RegexpNumCapturesTest_335, MultipleCaptures_335) {
  Regexp* re = ParseRegexp("(a)(b)(c)");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

TEST(RegexpNumCapturesTest_335, NestedCaptures_335) {
  Regexp* re = ParseRegexp("((a)(b))");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// ==================== NamedCaptures Tests ====================

TEST(RegexpNamedCapturesTest_335, NoNamedCaptures_335) {
  Regexp* re = ParseRegexp("(a)(b)");
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* names = re->NamedCaptures();
  EXPECT_EQ(names, nullptr);
  re->Decref();
}

TEST(RegexpNamedCapturesTest_335, WithNamedCaptures_335) {
  Regexp* re = ParseRegexp("(?P<first>a)(?P<second>b)");
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* names = re->NamedCaptures();
  ASSERT_NE(names, nullptr);
  EXPECT_EQ((*names)["first"], 1);
  EXPECT_EQ((*names)["second"], 2);
  delete names;
  re->Decref();
}

// ==================== CaptureNames Tests ====================

TEST(RegexpCaptureNamesTest_335, NoCaptureNames_335) {
  Regexp* re = ParseRegexp("abc");
  ASSERT_NE(re, nullptr);
  std::map<int, std::string>* names = re->CaptureNames();
  EXPECT_EQ(names, nullptr);
  re->Decref();
}

TEST(RegexpCaptureNamesTest_335, WithCaptureNames_335) {
  Regexp* re = ParseRegexp("(?P<x>a)(?P<y>b)");
  ASSERT_NE(re, nullptr);
  std::map<int, std::string>* names = re->CaptureNames();
  ASSERT_NE(names, nullptr);
  EXPECT_EQ((*names)[1], "x");
  EXPECT_EQ((*names)[2], "y");
  delete names;
  re->Decref();
}

// ==================== Simplify Tests ====================

TEST(RegexpSimplifyTest_335, SimplePatternSimplifies_335) {
  Regexp* re = ParseRegexp("a");
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

TEST(RegexpSimplifyTest_335, ComplexPatternSimplifies_335) {
  Regexp* re = ParseRegexp("(?:a{2,5})");
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// ==================== SimplifyRegexp (static) Tests ====================

TEST(RegexpSimplifyRegexpTest_335, BasicSimplification_335) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a+", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

TEST(RegexpSimplifyRegexpTest_335, InvalidPattern_335) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("(", Regexp::LikePerl, &dst, &status);
  EXPECT_FALSE(ok);
}

// ==================== Static Factory Tests ====================

TEST(RegexpFactoryTest_335, NewLiteral_335) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'a');
  re->Decref();
}

TEST(RegexpFactoryTest_335, HaveMatch_335) {
  Regexp* re = Regexp::HaveMatch(42, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), 42);
  re->Decref();
}

TEST(RegexpFactoryTest_335, Plus_335) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(sub, nullptr);
  Regexp* re = Regexp::Plus(sub, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

TEST(RegexpFactoryTest_335, Star_335) {
  Regexp* sub = Regexp::NewLiteral('b', Regexp::LikePerl);
  ASSERT_NE(sub, nullptr);
  Regexp* re = Regexp::Star(sub, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

TEST(RegexpFactoryTest_335, Quest_335) {
  Regexp* sub = Regexp::NewLiteral('c', Regexp::LikePerl);
  ASSERT_NE(sub, nullptr);
  Regexp* re = Regexp::Quest(sub, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

TEST(RegexpFactoryTest_335, Capture_335) {
  Regexp* sub = Regexp::NewLiteral('d', Regexp::LikePerl);
  ASSERT_NE(sub, nullptr);
  Regexp* re = Regexp::Capture(sub, Regexp::LikePerl, 1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 1);
  re->Decref();
}

TEST(RegexpFactoryTest_335, Repeat_335) {
  Regexp* sub = Regexp::NewLiteral('e', Regexp::LikePerl);
  ASSERT_NE(sub, nullptr);
  Regexp* re = Regexp::Repeat(sub, Regexp::LikePerl, 2, 5);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), 5);
  re->Decref();
}

TEST(RegexpFactoryTest_335, LiteralString_335) {
  Rune runes[] = {'h', 'e', 'l', 'l', 'o'};
  Regexp* re = Regexp::LiteralString(runes, 5, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 5);
  re->Decref();
}

TEST(RegexpFactoryTest_335, Concat_335) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  Regexp* re = Regexp::Concat(subs, 2, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST(RegexpFactoryTest_335, Alternate_335) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  Regexp* re = Regexp::Alternate(subs, 2, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST(RegexpFactoryTest_335, AlternateNoFactor_335) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('x', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('y', Regexp::LikePerl);
  Regexp* re = Regexp::AlternateNoFactor(subs, 2, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// ==================== Dump Tests ====================

TEST(RegexpDumpTest_335, DumpProducesNonEmptyString_335) {
  Regexp* re = ParseRegexp("a+b*");
  ASSERT_NE(re, nullptr);
  std::string dump = re->Dump();
  EXPECT_FALSE(dump.empty());
  re->Decref();
}

// ==================== op() accessor Tests ====================

TEST(RegexpAccessorTest_335, OpForLiteral_335) {
  Regexp* re = Regexp::NewLiteral('z', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// ==================== RequiredPrefix Tests ====================

TEST(RegexpRequiredPrefixTest_335, LiteralPrefix_335) {
  Regexp* re = ParseRegexp("^abc");
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;
  bool has_prefix = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  if (has_prefix) {
    EXPECT_FALSE(prefix.empty());
    if (suffix != nullptr)
      suffix->Decref();
  }
  re->Decref();
}

TEST(RegexpRequiredPrefixTest_335, NoPrefix_335) {
  Regexp* re = ParseRegexp("a*b");
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;
  bool has_prefix = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  if (has_prefix && suffix != nullptr)
    suffix->Decref();
  re->Decref();
}

// ==================== RequiredPrefixForAccel Tests ====================

TEST(RegexpRequiredPrefixForAccelTest_335, WithLiteralPrefix_335) {
  Regexp* re = ParseRegexp("^hello.*world");
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  bool has = re->RequiredPrefixForAccel(&prefix, &foldcase);
  if (has) {
    EXPECT_FALSE(prefix.empty());
  }
  re->Decref();
}

// ==================== CompileToProg Tests ====================

TEST(RegexpCompileTest_335, CompileToProg_335) {
  Regexp* re = ParseRegexp("a+b");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

TEST(RegexpCompileTest_335, CompileToReverseProg_335) {
  Regexp* re = ParseRegexp("a+b");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// ==================== NullWalk Tests ====================

TEST(RegexpNullWalkTest_335, NullWalkDoesNotCrash_335) {
  Regexp* re = ParseRegexp("(a|b)*c+");
  ASSERT_NE(re, nullptr);
  EXPECT_NO_FATAL_FAILURE(re->NullWalk());
  re->Decref();
}

// ==================== parse_flags / simple / nsub accessors ====================

TEST(RegexpAccessorTest_335, ParseFlagsAccessor_335) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // parse_flags should reflect the flags used during parsing
  // We just check it doesn't crash and returns something
  Regexp::ParseFlags flags = re->parse_flags();
  (void)flags;
  re->Decref();
}

TEST(RegexpAccessorTest_335, NsubAccessor_335) {
  Regexp* re = ParseRegexp("abc");
  ASSERT_NE(re, nullptr);
  // For a concatenation, nsub should be > 0
  // For a literal, nsub should be 0
  int nsub = re->nsub();
  EXPECT_GE(nsub, 0);
  re->Decref();
}

// ==================== MimicsPCRE Tests ====================

TEST(RegexpMimicsPCRETest_335, SimpleLiteral_335) {
  Regexp* re = ParseRegexp("abc");
  ASSERT_NE(re, nullptr);
  // Simple literal should mimic PCRE
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// ==================== Edge Cases ====================

TEST(RegexpEdgeCaseTest_335, SingleCharPattern_335) {
  Regexp* re = ParseRegexp("a");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

TEST(RegexpEdgeCaseTest_335, DotPattern_335) {
  Regexp* re = ParseRegexp(".");
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST(RegexpEdgeCaseTest_335, ConcatEmptySubs_335) {
  Regexp* re = Regexp::Concat(nullptr, 0, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST(RegexpEdgeCaseTest_335, AlternateEmptySubs_335) {
  Regexp* re = Regexp::Alternate(nullptr, 0, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST(RegexpEdgeCaseTest_335, ConcatSingleSub_335) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* subs[] = {sub};
  Regexp* re = Regexp::Concat(subs, 1, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST(RegexpEdgeCaseTest_335, RepeatWithZeroMin_335) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Repeat(sub, Regexp::LikePerl, 0, 10);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->min(), 0);
  EXPECT_EQ(re->max(), 10);
  re->Decref();
}

TEST(RegexpEdgeCaseTest_335, RepeatWithUnboundedMax_335) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Repeat(sub, Regexp::LikePerl, 1, -1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->min(), 1);
  EXPECT_EQ(re->max(), -1);
  re->Decref();
}

// ==================== Stress Incref/Decref ====================

TEST(RegexpIncrefStressTest_335, ManyIncrefDecref_335) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  const int N = 100;
  for (int i = 0; i < N; i++) {
    re->Incref();
  }
  EXPECT_EQ(re->Ref(), N + 1);
  for (int i = 0; i < N; i++) {
    re->Decref();
  }
  EXPECT_EQ(re->Ref(), 1);
  re->Decref();
}

}  // namespace re2
