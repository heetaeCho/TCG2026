#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"

namespace re2 {

class RegexpTest_155 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// Test Parse with a simple literal pattern
TEST_F(RegexpTest_155, ParseSimpleLiteral_155) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test Parse with empty string
TEST_F(RegexpTest_155, ParseEmptyString_155) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  re->Decref();
}

// Test Parse with invalid regex
TEST_F(RegexpTest_155, ParseInvalidRegex_155) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

// Test ToString round-trip
TEST_F(RegexpTest_155, ToStringRoundTrip_155) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+b*c?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test NewLiteral
TEST_F(RegexpTest_155, NewLiteral_155) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'a');
  re->Decref();
}

// Test Plus factory
TEST_F(RegexpTest_155, PlusFactory_155) {
  Regexp* lit = Regexp::NewLiteral('x', Regexp::NoParseFlags);
  Regexp* plus = Regexp::Plus(lit, Regexp::NoParseFlags);
  ASSERT_NE(plus, nullptr);
  EXPECT_EQ(plus->op(), kRegexpPlus);
  plus->Decref();
}

// Test Star factory
TEST_F(RegexpTest_155, StarFactory_155) {
  Regexp* lit = Regexp::NewLiteral('y', Regexp::NoParseFlags);
  Regexp* star = Regexp::Star(lit, Regexp::NoParseFlags);
  ASSERT_NE(star, nullptr);
  EXPECT_EQ(star->op(), kRegexpStar);
  star->Decref();
}

// Test Quest factory
TEST_F(RegexpTest_155, QuestFactory_155) {
  Regexp* lit = Regexp::NewLiteral('z', Regexp::NoParseFlags);
  Regexp* quest = Regexp::Quest(lit, Regexp::NoParseFlags);
  ASSERT_NE(quest, nullptr);
  EXPECT_EQ(quest->op(), kRegexpQuest);
  quest->Decref();
}

// Test Concat factory
TEST_F(RegexpTest_155, ConcatFactory_155) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* concat = Regexp::Concat(subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(concat, nullptr);
  EXPECT_EQ(concat->op(), kRegexpConcat);
  EXPECT_EQ(concat->nsub(), 2);
  concat->Decref();
}

// Test Alternate factory
TEST_F(RegexpTest_155, AlternateFactory_155) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* alt = Regexp::Alternate(subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(alt, nullptr);
  // Could be kRegexpAlternate or kRegexpCharClass after factoring
  alt->Decref();
}

// Test Capture factory
TEST_F(RegexpTest_155, CaptureFactory_155) {
  Regexp* lit = Regexp::NewLiteral('c', Regexp::NoParseFlags);
  Regexp* cap = Regexp::Capture(lit, Regexp::NoParseFlags, 1);
  ASSERT_NE(cap, nullptr);
  EXPECT_EQ(cap->op(), kRegexpCapture);
  EXPECT_EQ(cap->cap(), 1);
  cap->Decref();
}

// Test Repeat factory
TEST_F(RegexpTest_155, RepeatFactory_155) {
  Regexp* lit = Regexp::NewLiteral('d', Regexp::NoParseFlags);
  Regexp* rep = Regexp::Repeat(lit, Regexp::NoParseFlags, 2, 5);
  ASSERT_NE(rep, nullptr);
  EXPECT_EQ(rep->op(), kRegexpRepeat);
  EXPECT_EQ(rep->min(), 2);
  EXPECT_EQ(rep->max(), 5);
  rep->Decref();
}

// Test Repeat with unbounded max (-1)
TEST_F(RegexpTest_155, RepeatUnboundedMax_155) {
  Regexp* lit = Regexp::NewLiteral('e', Regexp::NoParseFlags);
  Regexp* rep = Regexp::Repeat(lit, Regexp::NoParseFlags, 3, -1);
  ASSERT_NE(rep, nullptr);
  EXPECT_EQ(rep->op(), kRegexpRepeat);
  EXPECT_EQ(rep->min(), 3);
  EXPECT_EQ(rep->max(), -1);
  rep->Decref();
}

// Test Repeat with min == max
TEST_F(RegexpTest_155, RepeatExactCount_155) {
  Regexp* lit = Regexp::NewLiteral('f', Regexp::NoParseFlags);
  Regexp* rep = Regexp::Repeat(lit, Regexp::NoParseFlags, 4, 4);
  ASSERT_NE(rep, nullptr);
  EXPECT_EQ(rep->min(), 4);
  EXPECT_EQ(rep->max(), 4);
  rep->Decref();
}

// Test HaveMatch
TEST_F(RegexpTest_155, HaveMatch_155) {
  Regexp* hm = Regexp::HaveMatch(42, Regexp::NoParseFlags);
  ASSERT_NE(hm, nullptr);
  EXPECT_EQ(hm->op(), kRegexpHaveMatch);
  EXPECT_EQ(hm->match_id(), 42);
  hm->Decref();
}

// Test LiteralString
TEST_F(RegexpTest_155, LiteralString_155) {
  Rune runes[] = {'h', 'e', 'l', 'l', 'o'};
  Regexp* ls = Regexp::LiteralString(runes, 5, Regexp::NoParseFlags);
  ASSERT_NE(ls, nullptr);
  EXPECT_EQ(ls->op(), kRegexpLiteralString);
  EXPECT_EQ(ls->nrunes(), 5);
  ls->Decref();
}

// Test NumCaptures
TEST_F(RegexpTest_155, NumCaptures_155) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// Test NumCaptures with no captures
TEST_F(RegexpTest_155, NumCapturesNone_155) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

// Test NamedCaptures
TEST_F(RegexpTest_155, NamedCaptures_155) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<name>a)(?P<value>b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  auto* named = re->NamedCaptures();
  ASSERT_NE(named, nullptr);
  EXPECT_EQ(named->size(), 2u);
  EXPECT_NE(named->find("name"), named->end());
  EXPECT_NE(named->find("value"), named->end());
  delete named;
  re->Decref();
}

// Test NamedCaptures returns null when no named groups
TEST_F(RegexpTest_155, NamedCapturesNone_155) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  auto* named = re->NamedCaptures();
  EXPECT_EQ(named, nullptr);
  re->Decref();
}

// Test CaptureNames
TEST_F(RegexpTest_155, CaptureNames_155) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<first>a)(?P<second>b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  auto* names = re->CaptureNames();
  ASSERT_NE(names, nullptr);
  EXPECT_GE(names->size(), 2u);
  delete names;
  re->Decref();
}

// Test Incref and Decref
TEST_F(RegexpTest_155, IncrefDecref_155) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  Regexp* re2 = re->Incref();
  EXPECT_EQ(re, re2);
  re->Decref();
  re->Decref();
}

// Test Simplify
TEST_F(RegexpTest_155, Simplify_155) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simple = re->Simplify();
  ASSERT_NE(simple, nullptr);
  simple->Decref();
  re->Decref();
}

// Test SimplifyRegexp static method
TEST_F(RegexpTest_155, SimplifyRegexpStatic_155) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{2,4}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

// Test Dump
TEST_F(RegexpTest_155, Dump_155) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string dump = re->Dump();
  EXPECT_FALSE(dump.empty());
  re->Decref();
}

// Test op() accessor
TEST_F(RegexpTest_155, OpAccessor_155) {
  Regexp* re = Regexp::NewLiteral('q', Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// Test parse_flags() accessor
TEST_F(RegexpTest_155, ParseFlagsAccessor_155) {
  Regexp* re = Regexp::NewLiteral('q', Regexp::FoldCase);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->parse_flags() & Regexp::FoldCase);
  re->Decref();
}

// Test Concat with single sub
TEST_F(RegexpTest_155, ConcatSingleSub_155) {
  Regexp* subs[1];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* concat = Regexp::Concat(subs, 1, Regexp::NoParseFlags);
  ASSERT_NE(concat, nullptr);
  // With a single sub, Concat may just return the sub itself
  EXPECT_EQ(concat->op(), kRegexpLiteral);
  concat->Decref();
}

// Test Concat with zero subs
TEST_F(RegexpTest_155, ConcatZeroSubs_155) {
  Regexp* concat = Regexp::Concat(nullptr, 0, Regexp::NoParseFlags);
  ASSERT_NE(concat, nullptr);
  EXPECT_EQ(concat->op(), kRegexpEmptyMatch);
  concat->Decref();
}

// Test Alternate with single sub
TEST_F(RegexpTest_155, AlternateSingleSub_155) {
  Regexp* subs[1];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* alt = Regexp::Alternate(subs, 1, Regexp::NoParseFlags);
  ASSERT_NE(alt, nullptr);
  EXPECT_EQ(alt->op(), kRegexpLiteral);
  alt->Decref();
}

// Test Alternate with zero subs
TEST_F(RegexpTest_155, AlternateZeroSubs_155) {
  Regexp* alt = Regexp::Alternate(nullptr, 0, Regexp::NoParseFlags);
  ASSERT_NE(alt, nullptr);
  EXPECT_EQ(alt->op(), kRegexpNoMatch);
  alt->Decref();
}

// Test AlternateNoFactor
TEST_F(RegexpTest_155, AlternateNoFactor_155) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* alt = Regexp::AlternateNoFactor(subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(alt, nullptr);
  EXPECT_EQ(alt->op(), kRegexpAlternate);
  alt->Decref();
}

// Test RequiredPrefix with anchored literal
TEST_F(RegexpTest_155, RequiredPrefix_155) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc", Regexp::LikePerl, &status);
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

// Test RequiredPrefix with no prefix
TEST_F(RegexpTest_155, RequiredPrefixNone_155) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".*abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;
  bool has_prefix = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  EXPECT_FALSE(has_prefix);
  re->Decref();
}

// Test CompileToProg
TEST_F(RegexpTest_155, CompileToProg_155) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileToReverseProg
TEST_F(RegexpTest_155, CompileToReverseProg_155) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Repeat min=0, max=0
TEST_F(RegexpTest_155, RepeatZeroZero_155) {
  Regexp* lit = Regexp::NewLiteral('g', Regexp::NoParseFlags);
  Regexp* rep = Regexp::Repeat(lit, Regexp::NoParseFlags, 0, 0);
  ASSERT_NE(rep, nullptr);
  EXPECT_EQ(rep->min(), 0);
  EXPECT_EQ(rep->max(), 0);
  rep->Decref();
}

// Test Parse with character class
TEST_F(RegexpTest_155, ParseCharClass_155) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCharClass);
  re->Decref();
}

// Test Parse with anchors
TEST_F(RegexpTest_155, ParseAnchors_155) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc$", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test Parse with nested groups
TEST_F(RegexpTest_155, ParseNestedGroups_155) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((a)(b(c)))", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 4);
  re->Decref();
}

// Test Parse with repetition in regex string
TEST_F(RegexpTest_155, ParseRepetition_155) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test Parse with dot (any char)
TEST_F(RegexpTest_155, ParseAnyChar_155) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test simple() accessor after simplify
TEST_F(RegexpTest_155, SimpleAccessor_155) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simple = re->Simplify();
  ASSERT_NE(simple, nullptr);
  // After simplification, simple() should return true
  EXPECT_TRUE(simple->simple());
  simple->Decref();
  re->Decref();
}

// Test sub() on Concat
TEST_F(RegexpTest_155, SubAccessorOnConcat_155) {
  Regexp* subs[3];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  subs[2] = Regexp::NewLiteral('c', Regexp::NoParseFlags);
  Regexp* concat = Regexp::Concat(subs, 3, Regexp::NoParseFlags);
  ASSERT_NE(concat, nullptr);
  EXPECT_EQ(concat->nsub(), 3);
  Regexp** csubs = concat->sub();
  ASSERT_NE(csubs, nullptr);
  for (int i = 0; i < 3; i++) {
    EXPECT_EQ(csubs[i]->op(), kRegexpLiteral);
  }
  concat->Decref();
}

// Test NullWalk doesn't crash
TEST_F(RegexpTest_155, NullWalk_155) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a|b)*c+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->NullWalk();  // Should not crash
  re->Decref();
}

// Test MimicsPCRE
TEST_F(RegexpTest_155, MimicsPCRE_155) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // Simple literal should mimic PCRE
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Test max() on a Repeat regexp specifically (the partial code focus)
TEST_F(RegexpTest_155, MaxOnRepeat_155) {
  Regexp* lit = Regexp::NewLiteral('h', Regexp::NoParseFlags);
  Regexp* rep = Regexp::Repeat(lit, Regexp::NoParseFlags, 1, 10);
  ASSERT_NE(rep, nullptr);
  EXPECT_EQ(rep->op(), kRegexpRepeat);
  EXPECT_EQ(rep->max(), 10);
  EXPECT_EQ(rep->min(), 1);
  rep->Decref();
}

// Test Repeat with large values
TEST_F(RegexpTest_155, RepeatLargeValues_155) {
  Regexp* lit = Regexp::NewLiteral('i', Regexp::NoParseFlags);
  Regexp* rep = Regexp::Repeat(lit, Regexp::NoParseFlags, 0, 1000);
  ASSERT_NE(rep, nullptr);
  EXPECT_EQ(rep->max(), 1000);
  EXPECT_EQ(rep->min(), 0);
  rep->Decref();
}

// Test LiteralString with single rune
TEST_F(RegexpTest_155, LiteralStringSingleRune_155) {
  Rune runes[] = {'z'};
  Regexp* ls = Regexp::LiteralString(runes, 1, Regexp::NoParseFlags);
  ASSERT_NE(ls, nullptr);
  // A single rune literal string might be optimized to kRegexpLiteral
  ls->Decref();
}

// Test Parse with complex regex
TEST_F(RegexpTest_155, ParseComplexRegex_155) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:foo|bar)+(?P<num>[0-9]{2,4})", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->NumCaptures(), 1);
  auto* named = re->NamedCaptures();
  ASSERT_NE(named, nullptr);
  EXPECT_NE(named->find("num"), named->end());
  delete named;
  re->Decref();
}

}  // namespace re2
