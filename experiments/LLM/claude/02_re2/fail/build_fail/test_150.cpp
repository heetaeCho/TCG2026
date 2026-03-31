#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <string>
#include <map>
#include <memory>

namespace re2 {

class RegexpTest_150 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// Helper to parse a regexp and manage lifetime
static Regexp* ParseOrDie(const char* pattern) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
  EXPECT_TRUE(re != nullptr) << "Failed to parse: " << pattern
                              << " error: " << status.Text();
  return re;
}

// ==================== Parse Tests ====================

TEST_F(RegexpTest_150, ParseSimpleLiteral_150) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_GT(re->Ref(), 0);
  re->Decref();
}

TEST_F(RegexpTest_150, ParseEmptyString_150) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_150, ParseInvalidRegexp_150) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
}

TEST_F(RegexpTest_150, ParseComplexPattern_150) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a(b|c)*d+[e-f]?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_150, ParseWithFlags_150) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?i)hello", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// ==================== ToString Tests ====================

TEST_F(RegexpTest_150, ToStringRoundTrip_150) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

TEST_F(RegexpTest_150, ToStringAlternation_150) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b|c", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// ==================== Dump Tests ====================

TEST_F(RegexpTest_150, DumpSimple_150) {
  Regexp* re = ParseOrDie("abc");
  ASSERT_NE(re, nullptr);
  std::string d = re->Dump();
  EXPECT_FALSE(d.empty());
  re->Decref();
}

// ==================== Ref / Incref / Decref Tests ====================

TEST_F(RegexpTest_150, RefCountBasic_150) {
  Regexp* re = ParseOrDie("x");
  ASSERT_NE(re, nullptr);
  int initial_ref = re->Ref();
  EXPECT_GE(initial_ref, 1);
  re->Decref();
}

TEST_F(RegexpTest_150, IncrefIncreasesRefCount_150) {
  Regexp* re = ParseOrDie("x");
  ASSERT_NE(re, nullptr);
  Regexp* re2 = re->Incref();
  EXPECT_EQ(re, re2);
  // Now ref count should be at least 2
  EXPECT_GE(re->Ref(), 2);
  re->Decref();
  re->Decref();
}

// ==================== Op Tests ====================

TEST_F(RegexpTest_150, OpLiteral_150) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// ==================== nsub Tests ====================

TEST_F(RegexpTest_150, NsubLiteral_150) {
  Regexp* re = Regexp::NewLiteral('z', Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->nsub(), 0);
  re->Decref();
}

TEST_F(RegexpTest_150, NsubStar_150) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Star(sub, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->nsub(), 1);
  re->Decref();
}

TEST_F(RegexpTest_150, NsubConcat_150) {
  Regexp* subs[3];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  subs[2] = Regexp::NewLiteral('c', Regexp::NoParseFlags);
  Regexp* re = Regexp::Concat(subs, 3, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->nsub(), 3);
  re->Decref();
}

// ==================== NumCaptures Tests ====================

TEST_F(RegexpTest_150, NumCapturesNone_150) {
  Regexp* re = ParseOrDie("abc");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

TEST_F(RegexpTest_150, NumCapturesOne_150) {
  Regexp* re = ParseOrDie("(abc)");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 1);
  re->Decref();
}

TEST_F(RegexpTest_150, NumCapturesMultiple_150) {
  Regexp* re = ParseOrDie("(a)(b)(c)");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

TEST_F(RegexpTest_150, NumCapturesNested_150) {
  Regexp* re = ParseOrDie("((a)(b))");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

TEST_F(RegexpTest_150, NumCapturesNonCapturing_150) {
  Regexp* re = ParseOrDie("(?:abc)");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

// ==================== NamedCaptures Tests ====================

TEST_F(RegexpTest_150, NamedCapturesNone_150) {
  Regexp* re = ParseOrDie("abc");
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* named = re->NamedCaptures();
  EXPECT_EQ(named, nullptr);
  delete named;
  re->Decref();
}

TEST_F(RegexpTest_150, NamedCapturesPresent_150) {
  Regexp* re = ParseOrDie("(?P<name>abc)");
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* named = re->NamedCaptures();
  ASSERT_NE(named, nullptr);
  EXPECT_EQ(named->size(), 1u);
  EXPECT_NE(named->find("name"), named->end());
  EXPECT_EQ((*named)["name"], 1);
  delete named;
  re->Decref();
}

// ==================== CaptureNames Tests ====================

TEST_F(RegexpTest_150, CaptureNamesNone_150) {
  Regexp* re = ParseOrDie("abc");
  ASSERT_NE(re, nullptr);
  std::map<int, std::string>* names = re->CaptureNames();
  EXPECT_EQ(names, nullptr);
  delete names;
  re->Decref();
}

TEST_F(RegexpTest_150, CaptureNamesPresent_150) {
  Regexp* re = ParseOrDie("(?P<foo>a)(?P<bar>b)");
  ASSERT_NE(re, nullptr);
  std::map<int, std::string>* names = re->CaptureNames();
  ASSERT_NE(names, nullptr);
  EXPECT_EQ(names->size(), 2u);
  EXPECT_EQ((*names)[1], "foo");
  EXPECT_EQ((*names)[2], "bar");
  delete names;
  re->Decref();
}

// ==================== Static Factory Tests ====================

TEST_F(RegexpTest_150, NewLiteralBasic_150) {
  Regexp* re = Regexp::NewLiteral('x', Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'x');
  re->Decref();
}

TEST_F(RegexpTest_150, PlusCreation_150) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Plus(sub, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  EXPECT_EQ(re->nsub(), 1);
  re->Decref();
}

TEST_F(RegexpTest_150, StarCreation_150) {
  Regexp* sub = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* re = Regexp::Star(sub, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  EXPECT_EQ(re->nsub(), 1);
  re->Decref();
}

TEST_F(RegexpTest_150, QuestCreation_150) {
  Regexp* sub = Regexp::NewLiteral('c', Regexp::NoParseFlags);
  Regexp* re = Regexp::Quest(sub, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  EXPECT_EQ(re->nsub(), 1);
  re->Decref();
}

TEST_F(RegexpTest_150, ConcatCreation_150) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* re = Regexp::Concat(subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpConcat);
  EXPECT_EQ(re->nsub(), 2);
  re->Decref();
}

TEST_F(RegexpTest_150, ConcatEmptyArray_150) {
  Regexp* re = Regexp::Concat(nullptr, 0, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_150, ConcatSingleElement_150) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Concat(&sub, 1, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  // Single-element concat might be optimized to just the element
  re->Decref();
}

TEST_F(RegexpTest_150, AlternateCreation_150) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* re = Regexp::Alternate(subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_150, AlternateEmptyArray_150) {
  Regexp* re = Regexp::Alternate(nullptr, 0, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_150, AlternateNoFactorCreation_150) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* re = Regexp::AlternateNoFactor(subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_150, CaptureCreation_150) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Capture(sub, Regexp::NoParseFlags, 1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 1);
  re->Decref();
}

TEST_F(RegexpTest_150, RepeatCreation_150) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 2, 5);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), 5);
  re->Decref();
}

TEST_F(RegexpTest_150, RepeatExact_150) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 3, 3);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->min(), 3);
  EXPECT_EQ(re->max(), 3);
  re->Decref();
}

TEST_F(RegexpTest_150, RepeatUnbounded_150) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 1, -1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->min(), 1);
  EXPECT_EQ(re->max(), -1);
  re->Decref();
}

TEST_F(RegexpTest_150, HaveMatchCreation_150) {
  Regexp* re = Regexp::HaveMatch(42, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), 42);
  re->Decref();
}

TEST_F(RegexpTest_150, LiteralStringCreation_150) {
  Rune runes[] = {'h', 'e', 'l', 'l', 'o'};
  Regexp* re = Regexp::LiteralString(runes, 5, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 5);
  re->Decref();
}

// ==================== Simplify Tests ====================

TEST_F(RegexpTest_150, SimplifyBasic_150) {
  Regexp* re = ParseOrDie("a+");
  ASSERT_NE(re, nullptr);
  Regexp* simp = re->Simplify();
  ASSERT_NE(simp, nullptr);
  simp->Decref();
  re->Decref();
}

TEST_F(RegexpTest_150, SimplifyRegexpStatic_150) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{2,4}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

TEST_F(RegexpTest_150, SimplifyRegexpInvalid_150) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("(", Regexp::LikePerl, &dst, &status);
  EXPECT_FALSE(ok);
}

// ==================== RequiredPrefix Tests ====================

TEST_F(RegexpTest_150, RequiredPrefixSimple_150) {
  Regexp* re = ParseOrDie("^abc.*");
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;
  bool has_prefix = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  if (has_prefix) {
    EXPECT_FALSE(prefix.empty());
    if (suffix) suffix->Decref();
  }
  re->Decref();
}

TEST_F(RegexpTest_150, RequiredPrefixNone_150) {
  Regexp* re = ParseOrDie("a|b");
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;
  bool has_prefix = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  EXPECT_FALSE(has_prefix);
  re->Decref();
}

TEST_F(RegexpTest_150, RequiredPrefixForAccel_150) {
  Regexp* re = ParseOrDie("^hello.*world");
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  re->RequiredPrefixForAccel(&prefix, &foldcase);
  // Just checking it doesn't crash; prefix may or may not be set
  re->Decref();
}

// ==================== CompileToProg Tests ====================

TEST_F(RegexpTest_150, CompileToProgBasic_150) {
  Regexp* re = ParseOrDie("abc");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

TEST_F(RegexpTest_150, CompileToReverseProgBasic_150) {
  Regexp* re = ParseOrDie("abc");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// ==================== NullWalk Tests ====================

TEST_F(RegexpTest_150, NullWalkDoesNotCrash_150) {
  Regexp* re = ParseOrDie("a(b|c)*d");
  ASSERT_NE(re, nullptr);
  re->NullWalk();
  re->Decref();
}

// ==================== MimicsPCRE Tests ====================

TEST_F(RegexpTest_150, MimicsPCRESimple_150) {
  Regexp* re = ParseOrDie("abc");
  ASSERT_NE(re, nullptr);
  // Simple patterns should mimic PCRE
  bool result = re->MimicsPCRE();
  EXPECT_TRUE(result);
  re->Decref();
}

// ==================== parse_flags Tests ====================

TEST_F(RegexpTest_150, ParseFlagsPreserved_150) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::FoldCase);
  ASSERT_NE(re, nullptr);
  EXPECT_NE(re->parse_flags() & Regexp::FoldCase, 0);
  re->Decref();
}

// ==================== simple Tests ====================

TEST_F(RegexpTest_150, SimpleAfterSimplify_150) {
  Regexp* re = ParseOrDie("abc");
  ASSERT_NE(re, nullptr);
  Regexp* simp = re->Simplify();
  ASSERT_NE(simp, nullptr);
  // After simplify, the regexp should be simple
  EXPECT_TRUE(simp->simple());
  simp->Decref();
  re->Decref();
}

// ==================== sub Tests ====================

TEST_F(RegexpTest_150, SubAccessConcat_150) {
  Regexp* subs_arr[2];
  subs_arr[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs_arr[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* re = Regexp::Concat(subs_arr, 2, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  ASSERT_EQ(re->nsub(), 2);
  Regexp** s = re->sub();
  ASSERT_NE(s, nullptr);
  EXPECT_EQ(s[0]->op(), kRegexpLiteral);
  EXPECT_EQ(s[1]->op(), kRegexpLiteral);
  re->Decref();
}

// ==================== Unicode/Rune Tests ====================

TEST_F(RegexpTest_150, NewLiteralUnicode_150) {
  // Unicode character: U+00E9 (é)
  Regexp* re = Regexp::NewLiteral(0x00E9, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->rune(), 0x00E9);
  re->Decref();
}

// ==================== Complex Pattern Tests ====================

TEST_F(RegexpTest_150, ParseComplexNested_150) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a(b(c)d)e)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

TEST_F(RegexpTest_150, ParseCharacterClass_150) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z0-9]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

TEST_F(RegexpTest_150, ParseDotStar_150) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_150, ParseEscapeSequences_150) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\d+\\s\\w", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// ==================== Boundary Tests ====================

TEST_F(RegexpTest_150, RepeatZeroZero_150) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 0, 0);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->min(), 0);
  EXPECT_EQ(re->max(), 0);
  re->Decref();
}

TEST_F(RegexpTest_150, LiteralStringEmpty_150) {
  // Empty literal string
  Regexp* re = Regexp::LiteralString(nullptr, 0, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_150, HaveMatchZero_150) {
  Regexp* re = Regexp::HaveMatch(0, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->match_id(), 0);
  re->Decref();
}

TEST_F(RegexpTest_150, CaptureZero_150) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Capture(sub, Regexp::NoParseFlags, 0);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->cap(), 0);
  re->Decref();
}

// ==================== Multiple Named Captures ====================

TEST_F(RegexpTest_150, MultipleNamedCaptures_150) {
  Regexp* re = ParseOrDie("(?P<first>\\w+)\\s(?P<second>\\w+)\\s(?P<third>\\w+)");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  std::map<std::string, int>* named = re->NamedCaptures();
  ASSERT_NE(named, nullptr);
  EXPECT_EQ(named->size(), 3u);
  EXPECT_EQ((*named)["first"], 1);
  EXPECT_EQ((*named)["second"], 2);
  EXPECT_EQ((*named)["third"], 3);
  delete named;
  
  std::map<int, std::string>* capture_names = re->CaptureNames();
  ASSERT_NE(capture_names, nullptr);
  EXPECT_EQ((*capture_names)[1], "first");
  EXPECT_EQ((*capture_names)[2], "second");
  EXPECT_EQ((*capture_names)[3], "third");
  delete capture_names;
  
  re->Decref();
}

// ==================== POSIX Flags Tests ====================

TEST_F(RegexpTest_150, ParsePOSIXFlags_150) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[[:alpha:]]", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// ==================== NonGreedy Tests ====================

TEST_F(RegexpTest_150, ParseNonGreedy_150) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_NE(re->parse_flags() & Regexp::NonGreedy, 0);
  re->Decref();
}

// ==================== FoldCase Factory Test ====================

TEST_F(RegexpTest_150, NewLiteralFoldCase_150) {
  Regexp* re = Regexp::NewLiteral('A', Regexp::FoldCase);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->rune(), 'a');  // Folded to lowercase typically
  re->Decref();
}

}  // namespace re2
