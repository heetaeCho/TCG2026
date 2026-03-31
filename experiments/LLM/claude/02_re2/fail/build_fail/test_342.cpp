#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <string>
#include <map>
#include <memory>

namespace re2 {

// Helper to parse a regexp and return it (caller must Decref)
static Regexp* ParseOrDie(const char* pattern) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
  EXPECT_TRUE(re != nullptr) << "Failed to parse: " << pattern
                              << " error: " << status.Text();
  return re;
}

class RegexpTest_342 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Tests are responsible for Decref-ing their own regexps
  }
};

// --- Parse tests ---

TEST_F(RegexpTest_342, ParseSimpleLiteral_342) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

TEST_F(RegexpTest_342, ParseEmptyString_342) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_342, ParseInvalidRegexp_342) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
}

TEST_F(RegexpTest_342, ParseAlternation_342) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b|c", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpAlternate);
  re->Decref();
}

TEST_F(RegexpTest_342, ParseConcat_342) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // "abc" should be a literal string or concat of literals
  re->Decref();
}

TEST_F(RegexpTest_342, ParseStar_342) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

TEST_F(RegexpTest_342, ParsePlus_342) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

TEST_F(RegexpTest_342, ParseQuest_342) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

TEST_F(RegexpTest_342, ParseCapture_342) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  re->Decref();
}

TEST_F(RegexpTest_342, ParseRepeat_342) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), 5);
  re->Decref();
}

TEST_F(RegexpTest_342, ParseCharClass_342) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCharClass);
  re->Decref();
}

TEST_F(RegexpTest_342, ParseAnyChar_342) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // Depending on flags, could be kRegexpAnyChar or kRegexpCharClass
  re->Decref();
}

// --- ToString tests ---

TEST_F(RegexpTest_342, ToStringRoundTrip_342) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "[a-b]");
  re->Decref();
}

TEST_F(RegexpTest_342, ToStringLiteral_342) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("x", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "x");
  re->Decref();
}

// --- Dump tests ---

TEST_F(RegexpTest_342, DumpNotEmpty_342) {
  Regexp* re = ParseOrDie("abc");
  ASSERT_NE(re, nullptr);
  std::string d = re->Dump();
  EXPECT_FALSE(d.empty());
  re->Decref();
}

// --- NumCaptures tests ---

TEST_F(RegexpTest_342, NumCapturesZero_342) {
  Regexp* re = ParseOrDie("abc");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

TEST_F(RegexpTest_342, NumCapturesOne_342) {
  Regexp* re = ParseOrDie("(abc)");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 1);
  re->Decref();
}

TEST_F(RegexpTest_342, NumCapturesMultiple_342) {
  Regexp* re = ParseOrDie("(a)(b)(c)");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

TEST_F(RegexpTest_342, NumCapturesNested_342) {
  Regexp* re = ParseOrDie("((a)(b))");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// --- NamedCaptures tests ---

TEST_F(RegexpTest_342, NamedCapturesNone_342) {
  Regexp* re = ParseOrDie("abc");
  ASSERT_NE(re, nullptr);
  auto* named = re->NamedCaptures();
  // If no named captures, should return nullptr
  EXPECT_EQ(named, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_342, NamedCapturesPresent_342) {
  Regexp* re = ParseOrDie("(?P<name>abc)");
  ASSERT_NE(re, nullptr);
  auto* named = re->NamedCaptures();
  ASSERT_NE(named, nullptr);
  EXPECT_EQ(named->size(), 1u);
  EXPECT_NE(named->find("name"), named->end());
  EXPECT_EQ((*named)["name"], 1);
  delete named;
  re->Decref();
}

// --- CaptureNames tests ---

TEST_F(RegexpTest_342, CaptureNamesNone_342) {
  Regexp* re = ParseOrDie("abc");
  ASSERT_NE(re, nullptr);
  auto* names = re->CaptureNames();
  EXPECT_EQ(names, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_342, CaptureNamesPresent_342) {
  Regexp* re = ParseOrDie("(?P<foo>a)(?P<bar>b)");
  ASSERT_NE(re, nullptr);
  auto* names = re->CaptureNames();
  ASSERT_NE(names, nullptr);
  EXPECT_EQ(names->size(), 2u);
  EXPECT_EQ((*names)[1], "foo");
  EXPECT_EQ((*names)[2], "bar");
  delete names;
  re->Decref();
}

// --- Incref / Decref / Ref tests ---

TEST_F(RegexpTest_342, IncrefIncreasesRef_342) {
  Regexp* re = ParseOrDie("a");
  ASSERT_NE(re, nullptr);
  // After Parse, ref should be at least 1
  Regexp* re2 = re->Incref();
  EXPECT_EQ(re2, re);
  // Decref twice to clean up
  re->Decref();
  re->Decref();
}

// --- Static factory: NewLiteral ---

TEST_F(RegexpTest_342, NewLiteralCreatesLiteral_342) {
  Regexp* re = Regexp::NewLiteral('A', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'A');
  re->Decref();
}

// --- Static factory: HaveMatch ---

TEST_F(RegexpTest_342, HaveMatchCreatesHaveMatch_342) {
  Regexp* re = Regexp::HaveMatch(42, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), 42);
  re->Decref();
}

// --- Static factory: Plus ---

TEST_F(RegexpTest_342, PlusCreatesPlus_342) {
  Regexp* sub = Regexp::NewLiteral('x', Regexp::LikePerl);
  Regexp* re = Regexp::Plus(sub, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

// --- Static factory: Star ---

TEST_F(RegexpTest_342, StarCreatesStar_342) {
  Regexp* sub = Regexp::NewLiteral('x', Regexp::LikePerl);
  Regexp* re = Regexp::Star(sub, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

// --- Static factory: Quest ---

TEST_F(RegexpTest_342, QuestCreatesQuest_342) {
  Regexp* sub = Regexp::NewLiteral('x', Regexp::LikePerl);
  Regexp* re = Regexp::Quest(sub, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

// --- Static factory: Capture ---

TEST_F(RegexpTest_342, CaptureCreatesCapture_342) {
  Regexp* sub = Regexp::NewLiteral('x', Regexp::LikePerl);
  Regexp* re = Regexp::Capture(sub, Regexp::LikePerl, 1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 1);
  re->Decref();
}

// --- Static factory: Repeat ---

TEST_F(RegexpTest_342, RepeatCreatesRepeat_342) {
  Regexp* sub = Regexp::NewLiteral('x', Regexp::LikePerl);
  Regexp* re = Regexp::Repeat(sub, Regexp::LikePerl, 3, 7);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 3);
  EXPECT_EQ(re->max(), 7);
  re->Decref();
}

TEST_F(RegexpTest_342, RepeatExactCount_342) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Repeat(sub, Regexp::LikePerl, 5, 5);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->min(), 5);
  EXPECT_EQ(re->max(), 5);
  re->Decref();
}

// --- Static factory: Concat ---

TEST_F(RegexpTest_342, ConcatMultipleSubs_342) {
  Regexp* subs[3];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  subs[2] = Regexp::NewLiteral('c', Regexp::LikePerl);
  Regexp* re = Regexp::Concat(subs, 3, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_342, ConcatSingleSub_342) {
  Regexp* subs[1];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Concat(subs, 1, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  // With a single sub, Concat may return the sub itself
  re->Decref();
}

TEST_F(RegexpTest_342, ConcatZeroSubs_342) {
  Regexp* re = Regexp::Concat(nullptr, 0, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  re->Decref();
}

// --- Static factory: Alternate ---

TEST_F(RegexpTest_342, AlternateMultipleSubs_342) {
  Regexp* subs[3];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  subs[2] = Regexp::NewLiteral('c', Regexp::LikePerl);
  Regexp* re = Regexp::Alternate(subs, 3, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_342, AlternateSingleSub_342) {
  Regexp* subs[1];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Alternate(subs, 1, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_342, AlternateZeroSubs_342) {
  Regexp* re = Regexp::Alternate(nullptr, 0, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpNoMatch);
  re->Decref();
}

// --- Static factory: AlternateNoFactor ---

TEST_F(RegexpTest_342, AlternateNoFactorMultipleSubs_342) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('x', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('y', Regexp::LikePerl);
  Regexp* re = Regexp::AlternateNoFactor(subs, 2, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpAlternate);
  re->Decref();
}

// --- Static factory: LiteralString ---

TEST_F(RegexpTest_342, LiteralStringCreatesLiteralString_342) {
  Rune runes[] = {'h', 'e', 'l', 'l', 'o'};
  Regexp* re = Regexp::LiteralString(runes, 5, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 5);
  re->Decref();
}

TEST_F(RegexpTest_342, LiteralStringSingleRune_342) {
  Rune runes[] = {'a'};
  Regexp* re = Regexp::LiteralString(runes, 1, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  // Single rune might be optimized to kRegexpLiteral
  re->Decref();
}

// --- Simplify tests ---

TEST_F(RegexpTest_342, SimplifyBasic_342) {
  Regexp* re = ParseOrDie("a{3}");
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

TEST_F(RegexpTest_342, SimplifyAlreadySimple_342) {
  Regexp* re = ParseOrDie("abc");
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// --- SimplifyRegexp (static) tests ---

TEST_F(RegexpTest_342, SimplifyRegexpBasic_342) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{2,3}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

TEST_F(RegexpTest_342, SimplifyRegexpInvalid_342) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("(", Regexp::LikePerl, &dst, &status);
  EXPECT_FALSE(ok);
}

// --- RequiredPrefix tests ---

TEST_F(RegexpTest_342, RequiredPrefixWithPrefix_342) {
  // ^hello.* should have required prefix "hello"
  Regexp* re = ParseOrDie("^hello.*");
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
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

TEST_F(RegexpTest_342, RequiredPrefixNoPrefix_342) {
  Regexp* re = ParseOrDie(".*hello");
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;
  bool has_prefix = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  EXPECT_FALSE(has_prefix);
  re->Decref();
}

// --- RequiredPrefixForAccel tests ---

TEST_F(RegexpTest_342, RequiredPrefixForAccelBasic_342) {
  Regexp* re = ParseOrDie("^test.*");
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  re->RequiredPrefixForAccel(&prefix, &foldcase);
  // Just check it doesn't crash
  re->Decref();
}

// --- CompileToProg tests ---

TEST_F(RegexpTest_342, CompileToProgBasic_342) {
  Regexp* re = ParseOrDie("a+b");
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  Prog* prog = simplified->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  simplified->Decref();
  re->Decref();
}

TEST_F(RegexpTest_342, CompileToReverseProgBasic_342) {
  Regexp* re = ParseOrDie("a+b");
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  Prog* prog = simplified->CompileToReverseProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  simplified->Decref();
  re->Decref();
}

// --- NullWalk tests ---

TEST_F(RegexpTest_342, NullWalkDoesNotCrash_342) {
  Regexp* re = ParseOrDie("(a|b)*c+[def]");
  ASSERT_NE(re, nullptr);
  re->NullWalk();
  re->Decref();
}

// --- op() accessor tests ---

TEST_F(RegexpTest_342, OpAccessorLiteral_342) {
  Regexp* re = Regexp::NewLiteral('z', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// --- parse_flags() accessor tests ---

TEST_F(RegexpTest_342, ParseFlagsAccessor_342) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->parse_flags(), Regexp::LikePerl);
  re->Decref();
}

// --- nsub() accessor tests ---

TEST_F(RegexpTest_342, NsubAccessorConcat_342) {
  Regexp* subs[3];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  subs[2] = Regexp::NewLiteral('c', Regexp::LikePerl);
  Regexp* re = Regexp::Concat(subs, 3, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  if (re->op() == kRegexpConcat || re->op() == kRegexpLiteralString) {
    // If concat, should have nsub 3
    if (re->op() == kRegexpConcat) {
      EXPECT_EQ(re->nsub(), 3);
    }
  }
  re->Decref();
}

// --- Complex pattern tests ---

TEST_F(RegexpTest_342, ParseComplexPattern_342) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(
      "(?:(?P<name>[a-zA-Z]+)|(?P<num>[0-9]+))\\s*=\\s*(.+)",
      Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  auto* named = re->NamedCaptures();
  ASSERT_NE(named, nullptr);
  EXPECT_EQ(named->size(), 2u);
  EXPECT_NE(named->find("name"), named->end());
  EXPECT_NE(named->find("num"), named->end());
  delete named;
  re->Decref();
}

// --- Boundary: Repeat with min=0, max=0 ---

TEST_F(RegexpTest_342, RepeatZeroZero_342) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Repeat(sub, Regexp::LikePerl, 0, 0);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// --- Boundary: Repeat with min=0, max=-1 (unbounded) ---

TEST_F(RegexpTest_342, RepeatZeroUnbounded_342) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Repeat(sub, Regexp::LikePerl, 0, -1);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// --- Boundary: Repeat with min=1, max=-1 (unbounded) ---

TEST_F(RegexpTest_342, RepeatOneUnbounded_342) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Repeat(sub, Regexp::LikePerl, 1, -1);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// --- Unicode literal ---

TEST_F(RegexpTest_342, NewLiteralUnicode_342) {
  Regexp* re = Regexp::NewLiteral(0x4e16, Regexp::LikePerl);  // CJK character
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 0x4e16);
  re->Decref();
}

// --- MimicsPCRE ---

TEST_F(RegexpTest_342, MimicsPCRESimple_342) {
  Regexp* re = ParseOrDie("abc");
  ASSERT_NE(re, nullptr);
  // Should not crash; for simple patterns this should return true
  bool result = re->MimicsPCRE();
  EXPECT_TRUE(result);
  re->Decref();
}

// --- Alternate with many subs to exercise factoring ---

TEST_F(RegexpTest_342, AlternateFactoring_342) {
  // Create alternation of literals with common prefix
  Regexp* subs[4];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  subs[2] = Regexp::NewLiteral('c', Regexp::LikePerl);
  subs[3] = Regexp::NewLiteral('d', Regexp::LikePerl);
  Regexp* re = Regexp::Alternate(subs, 4, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  // Factoring may have turned this into a char class
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// --- sub() accessor ---

TEST_F(RegexpTest_342, SubAccessor_342) {
  Regexp* re = ParseOrDie("(a)(b)");
  ASSERT_NE(re, nullptr);
  if (re->op() == kRegexpConcat) {
    EXPECT_GE(re->nsub(), 2);
    Regexp** subs = re->sub();
    ASSERT_NE(subs, nullptr);
    for (int i = 0; i < re->nsub(); i++) {
      EXPECT_NE(subs[i], nullptr);
    }
  }
  re->Decref();
}

// --- FUZZING_ONLY_set_maximum_repeat_count ---

TEST_F(RegexpTest_342, FuzzingSetMaxRepeatCount_342) {
  // Just verify it doesn't crash
  Regexp::FUZZING_ONLY_set_maximum_repeat_count(1000);
  // Reset to a large value
  Regexp::FUZZING_ONLY_set_maximum_repeat_count(1000);
}

// --- Parse with different flags ---

TEST_F(RegexpTest_342, ParseWithPOSIXFlags_342) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_342, ParseWithNoFlags_342) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc",
      static_cast<Regexp::ParseFlags>(0), &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// --- simple() accessor ---

TEST_F(RegexpTest_342, SimpleAccessor_342) {
  Regexp* re = ParseOrDie("a");
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  EXPECT_TRUE(simplified->simple());
  simplified->Decref();
  re->Decref();
}

// --- Alternate of two subs that are identical ---

TEST_F(RegexpTest_342, AlternateIdenticalSubs_342) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Alternate(subs, 2, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// --- Parse anchored patterns ---

TEST_F(RegexpTest_342, ParseBeginEndText_342) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\Ahello\\z", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_342, ParseBeginEndLine_342) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^hello$", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// --- Parse word boundary ---

TEST_F(RegexpTest_342, ParseWordBoundary_342) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\bhello\\b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

}  // namespace re2
