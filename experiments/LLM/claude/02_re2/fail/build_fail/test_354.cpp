#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"

namespace re2 {

// Test fixture for Regexp tests
class RegexpTest_354 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// ===================== NumCaptures Tests =====================

TEST_F(RegexpTest_354, NumCapturesZeroForNonCapturingRegexp_354) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

TEST_F(RegexpTest_354, NumCapturesOneForSingleCapture_354) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 1);
  re->Decref();
}

TEST_F(RegexpTest_354, NumCapturesMultipleCaptures_354) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

TEST_F(RegexpTest_354, NumCapturesNestedCaptures_354) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((a)(b))", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

TEST_F(RegexpTest_354, NumCapturesNonCapturingGroups_354) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

TEST_F(RegexpTest_354, NumCapturesMixedGroups_354) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:a)(b)(?:c)(d)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 2);
  re->Decref();
}

TEST_F(RegexpTest_354, NumCapturesDeeplyNested_354) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(((((a)))))", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 5);
  re->Decref();
}

// ===================== Parse Tests =====================

TEST_F(RegexpTest_354, ParseSimpleLiteral_354) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  re->Decref();
}

TEST_F(RegexpTest_354, ParseEmptyString_354) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  re->Decref();
}

TEST_F(RegexpTest_354, ParseSingleCharLiteral_354) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

TEST_F(RegexpTest_354, ParseAlternation_354) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpAlternate);
  re->Decref();
}

TEST_F(RegexpTest_354, ParseStar_354) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

TEST_F(RegexpTest_354, ParsePlus_354) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

TEST_F(RegexpTest_354, ParseQuest_354) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

TEST_F(RegexpTest_354, ParseCharClass_354) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[abc]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCharClass);
  re->Decref();
}

TEST_F(RegexpTest_354, ParseDotMatchesAnyChar_354) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // Dot can be kRegexpAnyChar or kRegexpCharClass depending on flags
  re->Decref();
}

TEST_F(RegexpTest_354, ParseInvalidRegexpReturnsNull_354) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
}

TEST_F(RegexpTest_354, ParseInvalidRegexpUnmatchedBracket_354) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[abc", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
}

// ===================== ToString Tests =====================

TEST_F(RegexpTest_354, ToStringSimple_354) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

TEST_F(RegexpTest_354, ToStringRoundTrip_354) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a(b|c)*d", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  // Parse the string back to verify it's valid
  Regexp* re2 = Regexp::Parse(s, Regexp::LikePerl, &status);
  ASSERT_NE(re2, nullptr);
  re->Decref();
  re2->Decref();
}

// ===================== Simplify Tests =====================

TEST_F(RegexpTest_354, SimplifyBasic_354) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,3}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simple = re->Simplify();
  ASSERT_NE(simple, nullptr);
  simple->Decref();
  re->Decref();
}

TEST_F(RegexpTest_354, SimplifyRegexpStatic_354) {
  RegexpStatus status;
  std::string dst;
  bool ok = Regexp::SimplifyRegexp("a{2,3}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

// ===================== NamedCaptures Tests =====================

TEST_F(RegexpTest_354, NamedCapturesNone_354) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* named = re->NamedCaptures();
  // No named captures expected
  EXPECT_EQ(named, nullptr);
  delete named;
  re->Decref();
}

TEST_F(RegexpTest_354, NamedCapturesPresent_354) {
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

TEST_F(RegexpTest_354, NamedCapturesMultiple_354) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<first>a)(?P<second>b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* named = re->NamedCaptures();
  ASSERT_NE(named, nullptr);
  EXPECT_EQ(named->size(), 2u);
  EXPECT_EQ((*named)["first"], 1);
  EXPECT_EQ((*named)["second"], 2);
  delete named;
  re->Decref();
}

// ===================== CaptureNames Tests =====================

TEST_F(RegexpTest_354, CaptureNamesNone_354) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<int, std::string>* names = re->CaptureNames();
  EXPECT_EQ(names, nullptr);
  delete names;
  re->Decref();
}

TEST_F(RegexpTest_354, CaptureNamesPresent_354) {
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

// ===================== Static Factory Method Tests =====================

TEST_F(RegexpTest_354, NewLiteral_354) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'a');
  re->Decref();
}

TEST_F(RegexpTest_354, HaveMatch_354) {
  Regexp* re = Regexp::HaveMatch(42, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), 42);
  re->Decref();
}

TEST_F(RegexpTest_354, PlusFactory_354) {
  Regexp* sub = Regexp::NewLiteral('x', Regexp::LikePerl);
  Regexp* re = Regexp::Plus(sub, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

TEST_F(RegexpTest_354, StarFactory_354) {
  Regexp* sub = Regexp::NewLiteral('x', Regexp::LikePerl);
  Regexp* re = Regexp::Star(sub, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

TEST_F(RegexpTest_354, QuestFactory_354) {
  Regexp* sub = Regexp::NewLiteral('x', Regexp::LikePerl);
  Regexp* re = Regexp::Quest(sub, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

TEST_F(RegexpTest_354, CaptureFactory_354) {
  Regexp* sub = Regexp::NewLiteral('x', Regexp::LikePerl);
  Regexp* re = Regexp::Capture(sub, Regexp::LikePerl, 1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 1);
  re->Decref();
}

TEST_F(RegexpTest_354, ConcatFactory_354) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  Regexp* re = Regexp::Concat(subs, 2, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_354, AlternateFactory_354) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  Regexp* re = Regexp::Alternate(subs, 2, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_354, LiteralStringFactory_354) {
  Rune runes[] = {'h', 'e', 'l', 'l', 'o'};
  Regexp* re = Regexp::LiteralString(runes, 5, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 5);
  re->Decref();
}

TEST_F(RegexpTest_354, RepeatFactory_354) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Repeat(sub, Regexp::LikePerl, 2, 5);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), 5);
  re->Decref();
}

// ===================== Incref / Decref Tests =====================

TEST_F(RegexpTest_354, IncrefIncreasesRefCount_354) {
  Regexp* re = Regexp::NewLiteral('z', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  Regexp* re2 = re->Incref();
  EXPECT_EQ(re, re2);
  re->Decref();
  re->Decref();
}

// ===================== RequiredPrefix Tests =====================

TEST_F(RegexpTest_354, RequiredPrefixSimple_354) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc.*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;
  bool has_prefix = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  if (has_prefix) {
    EXPECT_FALSE(prefix.empty());
    if (suffix != nullptr) suffix->Decref();
  }
  re->Decref();
}

TEST_F(RegexpTest_354, RequiredPrefixNone_354) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;
  bool has_prefix = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  EXPECT_FALSE(has_prefix);
  if (suffix != nullptr) suffix->Decref();
  re->Decref();
}

// ===================== Dump Tests =====================

TEST_F(RegexpTest_354, DumpProducesNonEmptyString_354) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a(b|c)+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string dump = re->Dump();
  EXPECT_FALSE(dump.empty());
  re->Decref();
}

// ===================== NullWalk Tests =====================

TEST_F(RegexpTest_354, NullWalkDoesNotCrash_354) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a|b)*c+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // NullWalk should not crash
  re->NullWalk();
  re->Decref();
}

// ===================== CompileToProg Tests =====================

TEST_F(RegexpTest_354, CompileToProgSimple_354) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

TEST_F(RegexpTest_354, CompileToReverseProgSimple_354) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// ===================== Concat/Alternate with zero/one subs =====================

TEST_F(RegexpTest_354, ConcatZeroSubs_354) {
  Regexp* re = Regexp::Concat(nullptr, 0, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  re->Decref();
}

TEST_F(RegexpTest_354, ConcatOneSub_354) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Concat(&sub, 1, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

TEST_F(RegexpTest_354, AlternateZeroSubs_354) {
  Regexp* re = Regexp::Alternate(nullptr, 0, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpNoMatch);
  re->Decref();
}

TEST_F(RegexpTest_354, AlternateOneSub_354) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Alternate(&sub, 1, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// ===================== Complex Regex NumCaptures =====================

TEST_F(RegexpTest_354, NumCapturesComplex_354) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a(?:b(c))(d)(?P<name>e))", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 4);
  re->Decref();
}

TEST_F(RegexpTest_354, NumCapturesAlternationWithCaptures_354) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)|(b)|(c)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// ===================== RequiredPrefixForAccel Tests =====================

TEST_F(RegexpTest_354, RequiredPrefixForAccelSimple_354) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^hello.*world", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  re->RequiredPrefixForAccel(&prefix, &foldcase);
  // Just ensure it doesn't crash; result depends on implementation
  re->Decref();
}

// ===================== Parse with different flags =====================

TEST_F(RegexpTest_354, ParsePOSIXFlags_354) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_354, ParseCaseInsensitive_354) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", static_cast<Regexp::ParseFlags>(Regexp::LikePerl | Regexp::FoldCase), &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

}  // namespace re2
