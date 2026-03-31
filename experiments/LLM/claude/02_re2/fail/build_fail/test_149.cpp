#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <string>
#include <map>
#include <memory>

namespace re2 {

class RegexpTest_149 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// Helper to parse and auto-decref
struct RegexpDeleter {
  void operator()(Regexp* re) const {
    if (re) re->Decref();
  }
};
using RegexpPtr = std::unique_ptr<Regexp, RegexpDeleter>;

static RegexpPtr ParseRegexp(const char* pattern, Regexp::ParseFlags flags = Regexp::LikePerl) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(pattern, flags, &status);
  return RegexpPtr(re);
}

// --- Parse Tests ---

TEST_F(RegexpTest_149, ParseSimpleLiteral_149) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST_F(RegexpTest_149, ParseEmptyString_149) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_149, ParseInvalidRegexp_149) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

TEST_F(RegexpTest_149, ParseComplexPattern_149) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a(b|c)*d+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_149, ParseCharacterClass_149) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z0-9]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// --- Op Tests ---

TEST_F(RegexpTest_149, OpOfLiteral_149) {
  auto re = ParseRegexp("a");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
}

TEST_F(RegexpTest_149, OpOfConcat_149) {
  auto re = ParseRegexp("ab");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpConcat);
}

TEST_F(RegexpTest_149, OpOfAlternate_149) {
  auto re = ParseRegexp("a|b");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpAlternate);
}

TEST_F(RegexpTest_149, OpOfStar_149) {
  auto re = ParseRegexp("a*");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
}

TEST_F(RegexpTest_149, OpOfPlus_149) {
  auto re = ParseRegexp("a+");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
}

TEST_F(RegexpTest_149, OpOfQuest_149) {
  auto re = ParseRegexp("a?");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
}

TEST_F(RegexpTest_149, OpOfCapture_149) {
  auto re = ParseRegexp("(a)");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
}

// --- ToString Tests ---

TEST_F(RegexpTest_149, ToStringSimple_149) {
  auto re = ParseRegexp("abc");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "abc");
}

TEST_F(RegexpTest_149, ToStringAlternate_149) {
  auto re = ParseRegexp("a|b");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "[ab]");
}

TEST_F(RegexpTest_149, ToStringStar_149) {
  auto re = ParseRegexp("a*");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "a*");
}

// --- Dump Tests ---

TEST_F(RegexpTest_149, DumpLiteral_149) {
  auto re = ParseRegexp("a");
  ASSERT_NE(re, nullptr);
  std::string d = re->Dump();
  EXPECT_FALSE(d.empty());
}

// --- NumCaptures Tests ---

TEST_F(RegexpTest_149, NumCapturesNone_149) {
  auto re = ParseRegexp("abc");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
}

TEST_F(RegexpTest_149, NumCapturesOne_149) {
  auto re = ParseRegexp("(abc)");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 1);
}

TEST_F(RegexpTest_149, NumCapturesMultiple_149) {
  auto re = ParseRegexp("(a)(b)(c)");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
}

TEST_F(RegexpTest_149, NumCapturesNested_149) {
  auto re = ParseRegexp("((a)(b))");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
}

// --- NamedCaptures Tests ---

TEST_F(RegexpTest_149, NamedCapturesNone_149) {
  auto re = ParseRegexp("(abc)");
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* named = re->NamedCaptures();
  EXPECT_EQ(named, nullptr);
  delete named;
}

TEST_F(RegexpTest_149, NamedCapturesPresent_149) {
  auto re = ParseRegexp("(?P<name>abc)");
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* named = re->NamedCaptures();
  ASSERT_NE(named, nullptr);
  EXPECT_EQ(named->size(), 1u);
  EXPECT_EQ((*named)["name"], 1);
  delete named;
}

// --- CaptureNames Tests ---

TEST_F(RegexpTest_149, CaptureNamesPresent_149) {
  auto re = ParseRegexp("(?P<foo>a)(?P<bar>b)");
  ASSERT_NE(re, nullptr);
  std::map<int, std::string>* names = re->CaptureNames();
  ASSERT_NE(names, nullptr);
  EXPECT_EQ((*names)[1], "foo");
  EXPECT_EQ((*names)[2], "bar");
  delete names;
}

TEST_F(RegexpTest_149, CaptureNamesNone_149) {
  auto re = ParseRegexp("abc");
  ASSERT_NE(re, nullptr);
  std::map<int, std::string>* names = re->CaptureNames();
  EXPECT_EQ(names, nullptr);
  delete names;
}

// --- Incref/Decref Tests ---

TEST_F(RegexpTest_149, IncrefDecref_149) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* re2 = re->Incref();
  EXPECT_EQ(re, re2);
  re->Decref();
  re->Decref();
}

// --- Simplify Tests ---

TEST_F(RegexpTest_149, SimplifyBasic_149) {
  auto re = ParseRegexp("a{2,3}");
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
}

// --- SimplifyRegexp (static) Tests ---

TEST_F(RegexpTest_149, SimplifyRegexpStatic_149) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{2,3}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

TEST_F(RegexpTest_149, SimplifyRegexpInvalid_149) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("(", Regexp::LikePerl, &dst, &status);
  EXPECT_FALSE(ok);
}

// --- Static Factory: NewLiteral ---

TEST_F(RegexpTest_149, NewLiteralOp_149) {
  Regexp* re = Regexp::NewLiteral('x', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'x');
  re->Decref();
}

// --- Static Factory: HaveMatch ---

TEST_F(RegexpTest_149, HaveMatchOp_149) {
  Regexp* re = Regexp::HaveMatch(42, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), 42);
  re->Decref();
}

// --- Static Factory: Plus ---

TEST_F(RegexpTest_149, PlusFactory_149) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Plus(sub, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

// --- Static Factory: Star ---

TEST_F(RegexpTest_149, StarFactory_149) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Star(sub, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

// --- Static Factory: Quest ---

TEST_F(RegexpTest_149, QuestFactory_149) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Quest(sub, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

// --- Static Factory: Capture ---

TEST_F(RegexpTest_149, CaptureFactory_149) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Capture(sub, Regexp::LikePerl, 1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 1);
  re->Decref();
}

// --- Static Factory: Repeat ---

TEST_F(RegexpTest_149, RepeatFactory_149) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Repeat(sub, Regexp::LikePerl, 2, 5);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), 5);
  re->Decref();
}

// --- Static Factory: Concat ---

TEST_F(RegexpTest_149, ConcatFactory_149) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  Regexp* re = Regexp::Concat(subs, 2, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpConcat);
  re->Decref();
}

TEST_F(RegexpTest_149, ConcatEmptyFactory_149) {
  Regexp* re = Regexp::Concat(nullptr, 0, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// --- Static Factory: Alternate ---

TEST_F(RegexpTest_149, AlternateFactory_149) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  Regexp* re = Regexp::Alternate(subs, 2, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_149, AlternateEmptyFactory_149) {
  Regexp* re = Regexp::Alternate(nullptr, 0, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// --- Static Factory: AlternateNoFactor ---

TEST_F(RegexpTest_149, AlternateNoFactorFactory_149) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  Regexp* re = Regexp::AlternateNoFactor(subs, 2, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// --- Static Factory: LiteralString ---

TEST_F(RegexpTest_149, LiteralStringFactory_149) {
  Rune runes[] = {'h', 'e', 'l', 'l', 'o'};
  Regexp* re = Regexp::LiteralString(runes, 5, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 5);
  re->Decref();
}

// --- RequiredPrefix Tests ---

TEST_F(RegexpTest_149, RequiredPrefixSimple_149) {
  auto re = ParseRegexp("^abc");
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;
  bool has_prefix = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  if (has_prefix) {
    EXPECT_FALSE(prefix.empty());
    if (suffix) suffix->Decref();
  }
}

TEST_F(RegexpTest_149, RequiredPrefixNoPrefix_149) {
  auto re = ParseRegexp("a*b");
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;
  bool has_prefix = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  EXPECT_FALSE(has_prefix);
}

// --- RequiredPrefixForAccel Tests ---

TEST_F(RegexpTest_149, RequiredPrefixForAccelSimple_149) {
  auto re = ParseRegexp("^hello.*world");
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  bool has = re->RequiredPrefixForAccel(&prefix, &foldcase);
  if (has) {
    EXPECT_FALSE(prefix.empty());
  }
}

// --- CompileToProg Tests ---

TEST_F(RegexpTest_149, CompileToProgBasic_149) {
  auto re = ParseRegexp("a+b");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// --- CompileToReverseProg Tests ---

TEST_F(RegexpTest_149, CompileToReverseProgBasic_149) {
  auto re = ParseRegexp("abc");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// --- NullWalk Test ---

TEST_F(RegexpTest_149, NullWalkDoesNotCrash_149) {
  auto re = ParseRegexp("(a|b)*c+");
  ASSERT_NE(re, nullptr);
  re->NullWalk();
}

// --- MimicsPCRE Tests ---

TEST_F(RegexpTest_149, MimicsPCRESimple_149) {
  auto re = ParseRegexp("abc");
  ASSERT_NE(re, nullptr);
  // Simple patterns should mimic PCRE
  EXPECT_TRUE(re->MimicsPCRE());
}

// --- parse_flags Tests ---

TEST_F(RegexpTest_149, ParseFlagsPreserved_149) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // Just check it doesn't crash and returns something
  Regexp::ParseFlags flags = re->parse_flags();
  (void)flags;
  re->Decref();
}

// --- nsub Tests ---

TEST_F(RegexpTest_149, NsubConcat_149) {
  auto re = ParseRegexp("ab");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpConcat);
  EXPECT_EQ(re->nsub(), 2);
}

TEST_F(RegexpTest_149, NsubAlternate_149) {
  auto re = ParseRegexp("a|b|c");
  ASSERT_NE(re, nullptr);
  // Could be charclass or alternate
  if (re->op() == kRegexpAlternate) {
    EXPECT_GE(re->nsub(), 2);
  }
}

// --- simple Tests ---

TEST_F(RegexpTest_149, SimpleAfterSimplify_149) {
  auto re = ParseRegexp("a{2,3}");
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  EXPECT_TRUE(simplified->simple());
  simplified->Decref();
}

// --- sub Tests ---

TEST_F(RegexpTest_149, SubOfConcat_149) {
  auto re = ParseRegexp("ab");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpConcat);
  Regexp** subs = re->sub();
  ASSERT_NE(subs, nullptr);
  EXPECT_EQ(subs[0]->op(), kRegexpLiteral);
  EXPECT_EQ(subs[1]->op(), kRegexpLiteral);
}

// --- Repeat min/max Tests ---

TEST_F(RegexpTest_149, RepeatMinMax_149) {
  auto re = ParseRegexp("a{3,7}");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 3);
  EXPECT_EQ(re->max(), 7);
}

TEST_F(RegexpTest_149, RepeatExact_149) {
  auto re = ParseRegexp("a{5}");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 5);
  EXPECT_EQ(re->max(), 5);
}

TEST_F(RegexpTest_149, RepeatUnbounded_149) {
  auto re = ParseRegexp("a{2,}");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), -1);
}

// --- Rune Tests ---

TEST_F(RegexpTest_149, RuneOfLiteral_149) {
  auto re = ParseRegexp("x");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'x');
}

// --- Cap Tests ---

TEST_F(RegexpTest_149, CapOfCapture_149) {
  auto re = ParseRegexp("(a)");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 1);
}

// --- Complex Parse Tests ---

TEST_F(RegexpTest_149, ParseDotStar_149) {
  auto re = ParseRegexp(".*");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
}

TEST_F(RegexpTest_149, ParseNestedGroups_149) {
  auto re = ParseRegexp("((a)(b(c)))");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 4);
}

TEST_F(RegexpTest_149, ParseEscapedChars_149) {
  auto re = ParseRegexp("\\d+\\.\\d+");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
}

// --- Boundary: Single character ---

TEST_F(RegexpTest_149, ParseSingleChar_149) {
  auto re = ParseRegexp("z");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'z');
}

// --- Boundary: Very long alternation ---

TEST_F(RegexpTest_149, ParseLongAlternation_149) {
  auto re = ParseRegexp("a|b|c|d|e|f|g|h|i|j");
  ASSERT_NE(re, nullptr);
  // Likely a CharClass after factoring
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
}

// --- POSIX flags ---

TEST_F(RegexpTest_149, ParsePOSIX_149) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// --- match_id on HaveMatch ---

TEST_F(RegexpTest_149, HaveMatchZero_149) {
  Regexp* re = Regexp::HaveMatch(0, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->match_id(), 0);
  re->Decref();
}

TEST_F(RegexpTest_149, HaveMatchLargeId_149) {
  Regexp* re = Regexp::HaveMatch(99999, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->match_id(), 99999);
  re->Decref();
}

// --- Concat with single sub ---

TEST_F(RegexpTest_149, ConcatSingleSub_149) {
  Regexp* subs[1];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Concat(subs, 1, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  // With single sub, might just return the sub itself
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// --- Alternate with single sub ---

TEST_F(RegexpTest_149, AlternateSingleSub_149) {
  Regexp* subs[1];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Alternate(subs, 1, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// --- Dump on complex regexp ---

TEST_F(RegexpTest_149, DumpComplex_149) {
  auto re = ParseRegexp("(?P<name>a+)(b|c){2,4}");
  ASSERT_NE(re, nullptr);
  std::string d = re->Dump();
  EXPECT_FALSE(d.empty());
}

// --- ToString roundtrip ---

TEST_F(RegexpTest_149, ToStringRoundtrip_149) {
  RegexpStatus status;
  const char* pattern = "ab+c";
  Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  // Parse again
  Regexp* re2 = Regexp::Parse(s, Regexp::LikePerl, &status);
  ASSERT_NE(re2, nullptr);
  std::string s2 = re2->ToString();
  EXPECT_EQ(s, s2);
  re->Decref();
  re2->Decref();
}

}  // namespace re2
