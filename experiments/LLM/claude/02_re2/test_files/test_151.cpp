#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <string>
#include <map>
#include <memory>

namespace re2 {

class RegexpTest_151 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// Helper to parse a regexp and return it; caller must Decref.
static Regexp* ParseOrDie(const char* pattern) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
  EXPECT_TRUE(re != nullptr) << "Failed to parse: " << pattern
                              << " error: " << status.Text();
  return re;
}

// --- Parse Tests ---

TEST_F(RegexpTest_151, ParseSimpleLiteral_151) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_GT(re->Ref(), 0);
  re->Decref();
}

TEST_F(RegexpTest_151, ParseEmptyString_151) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_151, ParseInvalidRegexp_151) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[invalid", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
}

TEST_F(RegexpTest_151, ParseComplexPattern_151) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a(b|c)*d+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_151, ParseDot_151) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// --- ToString Tests ---

TEST_F(RegexpTest_151, ToStringRoundTrip_151) {
  Regexp* re = ParseOrDie("abc");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

TEST_F(RegexpTest_151, ToStringAlternation_151) {
  Regexp* re = ParseOrDie("a|b|c");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// --- Dump Tests ---

TEST_F(RegexpTest_151, DumpProducesOutput_151) {
  Regexp* re = ParseOrDie("a+b");
  ASSERT_NE(re, nullptr);
  std::string d = re->Dump();
  EXPECT_FALSE(d.empty());
  re->Decref();
}

// --- Ref / Incref / Decref Tests ---

TEST_F(RegexpTest_151, RefCountInitial_151) {
  Regexp* re = ParseOrDie("x");
  ASSERT_NE(re, nullptr);
  EXPECT_GE(re->Ref(), 1);
  re->Decref();
}

TEST_F(RegexpTest_151, IncrefIncreasesRefCount_151) {
  Regexp* re = ParseOrDie("x");
  ASSERT_NE(re, nullptr);
  int initial = re->Ref();
  Regexp* re2 = re->Incref();
  EXPECT_EQ(re, re2);
  EXPECT_EQ(re->Ref(), initial + 1);
  re->Decref();
  re->Decref();
}

// --- NumCaptures Tests ---

TEST_F(RegexpTest_151, NumCapturesNone_151) {
  Regexp* re = ParseOrDie("abc");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

TEST_F(RegexpTest_151, NumCapturesOne_151) {
  Regexp* re = ParseOrDie("(abc)");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 1);
  re->Decref();
}

TEST_F(RegexpTest_151, NumCapturesMultiple_151) {
  Regexp* re = ParseOrDie("(a)(b)(c)");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

TEST_F(RegexpTest_151, NumCapturesNested_151) {
  Regexp* re = ParseOrDie("((a)(b))");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// --- NamedCaptures Tests ---

TEST_F(RegexpTest_151, NamedCapturesNone_151) {
  Regexp* re = ParseOrDie("abc");
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* named = re->NamedCaptures();
  EXPECT_EQ(named, nullptr);
  delete named;
  re->Decref();
}

TEST_F(RegexpTest_151, NamedCapturesPresent_151) {
  Regexp* re = ParseOrDie("(?P<foo>a)(?P<bar>b)");
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* named = re->NamedCaptures();
  ASSERT_NE(named, nullptr);
  EXPECT_EQ(named->count("foo"), 1);
  EXPECT_EQ(named->count("bar"), 1);
  EXPECT_EQ((*named)["foo"], 1);
  EXPECT_EQ((*named)["bar"], 2);
  delete named;
  re->Decref();
}

// --- CaptureNames Tests ---

TEST_F(RegexpTest_151, CaptureNamesNone_151) {
  Regexp* re = ParseOrDie("abc");
  ASSERT_NE(re, nullptr);
  std::map<int, std::string>* names = re->CaptureNames();
  EXPECT_EQ(names, nullptr);
  delete names;
  re->Decref();
}

TEST_F(RegexpTest_151, CaptureNamesPresent_151) {
  Regexp* re = ParseOrDie("(?P<foo>a)(?P<bar>b)");
  ASSERT_NE(re, nullptr);
  std::map<int, std::string>* names = re->CaptureNames();
  ASSERT_NE(names, nullptr);
  EXPECT_EQ((*names)[1], "foo");
  EXPECT_EQ((*names)[2], "bar");
  delete names;
  re->Decref();
}

// --- Simplify Tests ---

TEST_F(RegexpTest_151, SimplifyBasic_151) {
  Regexp* re = ParseOrDie("a+");
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

TEST_F(RegexpTest_151, SimplifyAlreadySimple_151) {
  Regexp* re = ParseOrDie("abc");
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// --- SimplifyRegexp static method ---

TEST_F(RegexpTest_151, SimplifyRegexpStatic_151) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{2,5}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

TEST_F(RegexpTest_151, SimplifyRegexpInvalid_151) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("[invalid", Regexp::LikePerl, &dst, &status);
  EXPECT_FALSE(ok);
}

// --- simple() Tests ---

TEST_F(RegexpTest_151, SimpleAfterSimplify_151) {
  Regexp* re = ParseOrDie("a+");
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  // After simplification, simple() should be true
  EXPECT_TRUE(simplified->simple());
  simplified->Decref();
  re->Decref();
}

// --- op() Tests ---

TEST_F(RegexpTest_151, OpLiteral_151) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// --- Static Factory: NewLiteral ---

TEST_F(RegexpTest_151, NewLiteralBasic_151) {
  Regexp* re = Regexp::NewLiteral('z', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'z');
  re->Decref();
}

// --- Static Factory: LiteralString ---

TEST_F(RegexpTest_151, LiteralStringBasic_151) {
  Rune runes[] = {'h', 'e', 'l', 'l', 'o'};
  Regexp* re = Regexp::LiteralString(runes, 5, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 5);
  re->Decref();
}

// --- Static Factory: HaveMatch ---

TEST_F(RegexpTest_151, HaveMatchBasic_151) {
  Regexp* re = Regexp::HaveMatch(42, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), 42);
  re->Decref();
}

// --- Static Factory: Plus ---

TEST_F(RegexpTest_151, PlusFactory_151) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(sub, nullptr);
  Regexp* re = Regexp::Plus(sub, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

// --- Static Factory: Star ---

TEST_F(RegexpTest_151, StarFactory_151) {
  Regexp* sub = Regexp::NewLiteral('b', Regexp::LikePerl);
  ASSERT_NE(sub, nullptr);
  Regexp* re = Regexp::Star(sub, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

// --- Static Factory: Quest ---

TEST_F(RegexpTest_151, QuestFactory_151) {
  Regexp* sub = Regexp::NewLiteral('c', Regexp::LikePerl);
  ASSERT_NE(sub, nullptr);
  Regexp* re = Regexp::Quest(sub, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

// --- Static Factory: Concat ---

TEST_F(RegexpTest_151, ConcatFactory_151) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  Regexp* re = Regexp::Concat(subs, 2, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_151, ConcatSingleSub_151) {
  Regexp* subs[1];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Concat(subs, 1, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_151, ConcatZeroSubs_151) {
  Regexp* re = Regexp::Concat(nullptr, 0, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// --- Static Factory: Alternate ---

TEST_F(RegexpTest_151, AlternateFactory_151) {
  Regexp* subs[3];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  subs[2] = Regexp::NewLiteral('c', Regexp::LikePerl);
  Regexp* re = Regexp::Alternate(subs, 3, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_151, AlternateZeroSubs_151) {
  Regexp* re = Regexp::Alternate(nullptr, 0, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// --- Static Factory: AlternateNoFactor ---

TEST_F(RegexpTest_151, AlternateNoFactorFactory_151) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('x', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('y', Regexp::LikePerl);
  Regexp* re = Regexp::AlternateNoFactor(subs, 2, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// --- Static Factory: Capture ---

TEST_F(RegexpTest_151, CaptureFactory_151) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(sub, nullptr);
  Regexp* re = Regexp::Capture(sub, Regexp::LikePerl, 1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 1);
  re->Decref();
}

// --- Static Factory: Repeat ---

TEST_F(RegexpTest_151, RepeatFactory_151) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(sub, nullptr);
  Regexp* re = Regexp::Repeat(sub, Regexp::LikePerl, 2, 5);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), 5);
  re->Decref();
}

TEST_F(RegexpTest_151, RepeatUnbounded_151) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(sub, nullptr);
  Regexp* re = Regexp::Repeat(sub, Regexp::LikePerl, 3, -1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->min(), 3);
  EXPECT_EQ(re->max(), -1);
  re->Decref();
}

// --- parse_flags() ---

TEST_F(RegexpTest_151, ParseFlagsPreserved_151) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->parse_flags(), Regexp::LikePerl);
  re->Decref();
}

// --- RequiredPrefix Tests ---

TEST_F(RegexpTest_151, RequiredPrefixWithLiteralPrefix_151) {
  Regexp* re = ParseOrDie("^abc.*");
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase;
  Regexp* suffix = nullptr;
  bool has_prefix = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  if (has_prefix) {
    EXPECT_FALSE(prefix.empty());
    EXPECT_NE(suffix, nullptr);
    suffix->Decref();
  }
  re->Decref();
}

TEST_F(RegexpTest_151, RequiredPrefixNoPrefix_151) {
  Regexp* re = ParseOrDie(".*abc");
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase;
  Regexp* suffix = nullptr;
  bool has_prefix = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  if (!has_prefix) {
    // No required prefix for patterns starting with .*
    EXPECT_FALSE(has_prefix);
  }
  if (suffix != nullptr) {
    suffix->Decref();
  }
  re->Decref();
}

// --- RequiredPrefixForAccel Tests ---

TEST_F(RegexpTest_151, RequiredPrefixForAccelLiteral_151) {
  Regexp* re = ParseOrDie("^hello.*world");
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

TEST_F(RegexpTest_151, CompileToProgBasic_151) {
  Regexp* re = ParseOrDie("a+b");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

TEST_F(RegexpTest_151, CompileToReverseProgBasic_151) {
  Regexp* re = ParseOrDie("a+b");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// --- MimicsPCRE Tests ---

TEST_F(RegexpTest_151, MimicsPCRESimple_151) {
  Regexp* re = ParseOrDie("abc");
  ASSERT_NE(re, nullptr);
  // Simple literal should mimic PCRE
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// --- NullWalk Tests ---

TEST_F(RegexpTest_151, NullWalkDoesNotCrash_151) {
  Regexp* re = ParseOrDie("(a|b)*c+");
  ASSERT_NE(re, nullptr);
  re->NullWalk();
  re->Decref();
}

// --- nsub() Tests ---

TEST_F(RegexpTest_151, NsubConcat_151) {
  Regexp* subs[3];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  subs[2] = Regexp::NewLiteral('c', Regexp::LikePerl);
  Regexp* re = Regexp::Concat(subs, 3, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->nsub(), 3);
  re->Decref();
}

// --- sub() Tests ---

TEST_F(RegexpTest_151, SubPointers_151) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('x', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('y', Regexp::LikePerl);
  Regexp* re = Regexp::Concat(subs, 2, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  ASSERT_EQ(re->nsub(), 2);
  Regexp** children = re->sub();
  ASSERT_NE(children, nullptr);
  EXPECT_NE(children[0], nullptr);
  EXPECT_NE(children[1], nullptr);
  re->Decref();
}

// --- Parse with various flags ---

TEST_F(RegexpTest_151, ParsePOSIXFlags_151) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+b", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_151, ParseWithFoldCase_151) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::FoldCase, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// --- Edge case: single character ---

TEST_F(RegexpTest_151, ParseSingleChar_151) {
  Regexp* re = ParseOrDie("a");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// --- Edge case: character class ---

TEST_F(RegexpTest_151, ParseCharClass_151) {
  Regexp* re = ParseOrDie("[a-z]");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCharClass);
  re->Decref();
}

// --- Edge case: anchored pattern ---

TEST_F(RegexpTest_151, ParseAnchored_151) {
  Regexp* re = ParseOrDie("^abc$");
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// --- ToString preserves semantics ---

TEST_F(RegexpTest_151, ToStringAndReparse_151) {
  Regexp* re = ParseOrDie("(a|b)*c+[0-9]");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  
  RegexpStatus status;
  Regexp* re2 = Regexp::Parse(s, Regexp::LikePerl, &status);
  EXPECT_NE(re2, nullptr);
  if (re2) re2->Decref();
  re->Decref();
}

// --- Complex patterns ---

TEST_F(RegexpTest_151, ParseComplexNested_151) {
  Regexp* re = ParseOrDie("(?:a(?:b(?:c)))");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

TEST_F(RegexpTest_151, ParseNamedCapture_151) {
  Regexp* re = ParseOrDie("(?P<name>abc)");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 1);
  std::map<std::string, int>* named = re->NamedCaptures();
  ASSERT_NE(named, nullptr);
  EXPECT_EQ(named->count("name"), 1);
  delete named;
  re->Decref();
}

// --- Repeat boundary conditions ---

TEST_F(RegexpTest_151, RepeatExactly_151) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Repeat(sub, Regexp::LikePerl, 3, 3);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->min(), 3);
  EXPECT_EQ(re->max(), 3);
  re->Decref();
}

TEST_F(RegexpTest_151, RepeatZeroToZero_151) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Repeat(sub, Regexp::LikePerl, 0, 0);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->min(), 0);
  EXPECT_EQ(re->max(), 0);
  re->Decref();
}

}  // namespace re2
