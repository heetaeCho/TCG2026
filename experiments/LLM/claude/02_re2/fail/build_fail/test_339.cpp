#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <string>
#include <map>
#include <memory>

namespace re2 {

class RegexpTest_339 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Regexp objects are reference counted and cleaned up via Decref
  }
};

// --- Parse Tests ---

TEST_F(RegexpTest_339, ParseSimpleLiteral_339) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST_F(RegexpTest_339, ParseEmptyString_339) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST_F(RegexpTest_339, ParseInvalidRegexp_339) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[invalid", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

TEST_F(RegexpTest_339, ParseStar_339) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

TEST_F(RegexpTest_339, ParsePlus_339) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

TEST_F(RegexpTest_339, ParseQuest_339) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

TEST_F(RegexpTest_339, ParseAlternation_339) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST_F(RegexpTest_339, ParseCapture_339) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->op(), kRegexpCapture);
  re->Decref();
}

TEST_F(RegexpTest_339, ParseCharClass_339) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->op(), kRegexpCharClass);
  re->Decref();
}

TEST_F(RegexpTest_339, ParseRepeat_339) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST_F(RegexpTest_339, ParseDot_339) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// --- ToString Tests ---

TEST_F(RegexpTest_339, ToStringLiteral_339) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "abc");
  re->Decref();
}

TEST_F(RegexpTest_339, ToStringRoundTrip_339) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a(b|c)*d", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// --- Star, Plus, Quest factory methods ---

TEST_F(RegexpTest_339, StarFactory_339) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(sub, nullptr);
  Regexp* star = Regexp::Star(sub, Regexp::LikePerl);
  ASSERT_NE(star, nullptr);
  EXPECT_EQ(star->op(), kRegexpStar);
  star->Decref();
}

TEST_F(RegexpTest_339, PlusFactory_339) {
  Regexp* sub = Regexp::NewLiteral('b', Regexp::LikePerl);
  ASSERT_NE(sub, nullptr);
  Regexp* plus = Regexp::Plus(sub, Regexp::LikePerl);
  ASSERT_NE(plus, nullptr);
  EXPECT_EQ(plus->op(), kRegexpPlus);
  plus->Decref();
}

TEST_F(RegexpTest_339, QuestFactory_339) {
  Regexp* sub = Regexp::NewLiteral('c', Regexp::LikePerl);
  ASSERT_NE(sub, nullptr);
  Regexp* quest = Regexp::Quest(sub, Regexp::LikePerl);
  ASSERT_NE(quest, nullptr);
  EXPECT_EQ(quest->op(), kRegexpQuest);
  quest->Decref();
}

// --- NewLiteral Tests ---

TEST_F(RegexpTest_339, NewLiteralBasic_339) {
  Regexp* re = Regexp::NewLiteral('x', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'x');
  re->Decref();
}

TEST_F(RegexpTest_339, NewLiteralUnicode_339) {
  Regexp* re = Regexp::NewLiteral(0x4e16, Regexp::LikePerl);  // Unicode char
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 0x4e16);
  re->Decref();
}

// --- LiteralString Tests ---

TEST_F(RegexpTest_339, LiteralStringBasic_339) {
  Rune runes[] = {'h', 'e', 'l', 'l', 'o'};
  Regexp* re = Regexp::LiteralString(runes, 5, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 5);
  re->Decref();
}

TEST_F(RegexpTest_339, LiteralStringSingleChar_339) {
  Rune runes[] = {'z'};
  Regexp* re = Regexp::LiteralString(runes, 1, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  // Single character literal string might be optimized to kRegexpLiteral
  re->Decref();
}

// --- Concat Tests ---

TEST_F(RegexpTest_339, ConcatTwoSubs_339) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  Regexp* re = Regexp::Concat(subs, 2, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_339, ConcatSingleSub_339) {
  Regexp* subs[1];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Concat(subs, 1, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_339, ConcatZeroSubs_339) {
  Regexp* re = Regexp::Concat(nullptr, 0, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  re->Decref();
}

// --- Alternate Tests ---

TEST_F(RegexpTest_339, AlternateTwoSubs_339) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  Regexp* re = Regexp::Alternate(subs, 2, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_339, AlternateSingleSub_339) {
  Regexp* subs[1];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Alternate(subs, 1, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_339, AlternateZeroSubs_339) {
  Regexp* re = Regexp::Alternate(nullptr, 0, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpNoMatch);
  re->Decref();
}

// --- AlternateNoFactor Tests ---

TEST_F(RegexpTest_339, AlternateNoFactorTwoSubs_339) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('x', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('y', Regexp::LikePerl);
  Regexp* re = Regexp::AlternateNoFactor(subs, 2, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// --- Capture Tests ---

TEST_F(RegexpTest_339, CaptureBasic_339) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Capture(sub, Regexp::LikePerl, 1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 1);
  re->Decref();
}

// --- Repeat Tests ---

TEST_F(RegexpTest_339, RepeatFixedCount_339) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Repeat(sub, Regexp::LikePerl, 3, 3);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 3);
  EXPECT_EQ(re->max(), 3);
  re->Decref();
}

TEST_F(RegexpTest_339, RepeatRange_339) {
  Regexp* sub = Regexp::NewLiteral('b', Regexp::LikePerl);
  Regexp* re = Regexp::Repeat(sub, Regexp::LikePerl, 2, 5);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), 5);
  re->Decref();
}

TEST_F(RegexpTest_339, RepeatUnbounded_339) {
  Regexp* sub = Regexp::NewLiteral('c', Regexp::LikePerl);
  Regexp* re = Regexp::Repeat(sub, Regexp::LikePerl, 1, -1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->min(), 1);
  EXPECT_EQ(re->max(), -1);
  re->Decref();
}

// --- HaveMatch Tests ---

TEST_F(RegexpTest_339, HaveMatchBasic_339) {
  Regexp* re = Regexp::HaveMatch(42, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), 42);
  re->Decref();
}

// --- Incref / Decref / Ref Tests ---

TEST_F(RegexpTest_339, IncrefIncreasesRef_339) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  Regexp* re2 = re->Incref();
  EXPECT_EQ(re, re2);
  // Decref twice
  re->Decref();
  re->Decref();
}

// --- NumCaptures Tests ---

TEST_F(RegexpTest_339, NumCapturesNone_339) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

TEST_F(RegexpTest_339, NumCapturesOne_339) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 1);
  re->Decref();
}

TEST_F(RegexpTest_339, NumCapturesMultiple_339) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

TEST_F(RegexpTest_339, NumCapturesNested_339) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((a)(b))", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// --- NamedCaptures Tests ---

TEST_F(RegexpTest_339, NamedCapturesNone_339) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  auto* named = re->NamedCaptures();
  // No named captures, should be nullptr
  EXPECT_EQ(named, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_339, NamedCapturesExist_339) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<name>abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  auto* named = re->NamedCaptures();
  ASSERT_NE(named, nullptr);
  EXPECT_EQ(named->size(), 1u);
  EXPECT_EQ((*named)["name"], 1);
  delete named;
  re->Decref();
}

// --- CaptureNames Tests ---

TEST_F(RegexpTest_339, CaptureNamesBasic_339) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<foo>a)(?P<bar>b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  auto* names = re->CaptureNames();
  ASSERT_NE(names, nullptr);
  EXPECT_EQ(names->size(), 2u);
  EXPECT_EQ((*names)[1], "foo");
  EXPECT_EQ((*names)[2], "bar");
  delete names;
  re->Decref();
}

// --- Simplify Tests ---

TEST_F(RegexpTest_339, SimplifyBasic_339) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// --- SimplifyRegexp Tests ---

TEST_F(RegexpTest_339, SimplifyRegexpString_339) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{2}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

TEST_F(RegexpTest_339, SimplifyRegexpInvalid_339) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("[bad", Regexp::LikePerl, &dst, &status);
  EXPECT_FALSE(ok);
}

// --- RequiredPrefix Tests ---

TEST_F(RegexpTest_339, RequiredPrefixSimple_339) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^hello.*", Regexp::LikePerl, &status);
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

TEST_F(RegexpTest_339, RequiredPrefixNoPrefix_339) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".*hello", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;
  bool has_prefix = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  EXPECT_FALSE(has_prefix);
  re->Decref();
}

// --- RequiredPrefixForAccel Tests ---

TEST_F(RegexpTest_339, RequiredPrefixForAccelSimple_339) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc.*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  bool has_prefix = re->RequiredPrefixForAccel(&prefix, &foldcase);
  if (has_prefix) {
    EXPECT_FALSE(prefix.empty());
  }
  re->Decref();
}

// --- Dump Tests ---

TEST_F(RegexpTest_339, DumpLiteral_339) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  std::string dump = re->Dump();
  EXPECT_FALSE(dump.empty());
  re->Decref();
}

TEST_F(RegexpTest_339, DumpComplex_339) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a|b)*c+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string dump = re->Dump();
  EXPECT_FALSE(dump.empty());
  re->Decref();
}

// --- Op accessor tests ---

TEST_F(RegexpTest_339, OpAccessor_339) {
  Regexp* re = Regexp::NewLiteral('z', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// --- ParseFlags accessor ---

TEST_F(RegexpTest_339, ParseFlagsAccessor_339) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  Regexp::ParseFlags flags = re->parse_flags();
  // LikePerl is a combination of flags; just ensure we get something non-zero
  EXPECT_NE(static_cast<int>(flags), 0);
  re->Decref();
}

// --- nsub accessor ---

TEST_F(RegexpTest_339, NsubStar_339) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* star = Regexp::Star(sub, Regexp::LikePerl);
  ASSERT_NE(star, nullptr);
  EXPECT_EQ(star->nsub(), 1);
  star->Decref();
}

TEST_F(RegexpTest_339, NsubConcat_339) {
  Regexp* subs[3];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  subs[2] = Regexp::NewLiteral('c', Regexp::LikePerl);
  Regexp* re = Regexp::Concat(subs, 3, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->nsub(), 3);
  re->Decref();
}

// --- sub accessor ---

TEST_F(RegexpTest_339, SubAccessor_339) {
  Regexp* sub_re = Regexp::NewLiteral('d', Regexp::LikePerl);
  Regexp* star = Regexp::Star(sub_re, Regexp::LikePerl);
  ASSERT_NE(star, nullptr);
  ASSERT_EQ(star->nsub(), 1);
  Regexp** subs = star->sub();
  ASSERT_NE(subs, nullptr);
  EXPECT_EQ(subs[0]->op(), kRegexpLiteral);
  EXPECT_EQ(subs[0]->rune(), 'd');
  star->Decref();
}

// --- CompileToProg Tests ---

TEST_F(RegexpTest_339, CompileToProgBasic_339) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// --- CompileToReverseProg Tests ---

TEST_F(RegexpTest_339, CompileToReverseProgBasic_339) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// --- Complex patterns ---

TEST_F(RegexpTest_339, ParseComplexPattern_339) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^(foo|bar)+baz[0-9]{2,4}$", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// --- Anchor patterns ---

TEST_F(RegexpTest_339, ParseBeginLine_339) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST_F(RegexpTest_339, ParseEndLine_339) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc$", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// --- Non-greedy variants ---

TEST_F(RegexpTest_339, StarNonGreedy_339) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* star = Regexp::Star(sub, static_cast<Regexp::ParseFlags>(
      Regexp::LikePerl | Regexp::NonGreedy));
  ASSERT_NE(star, nullptr);
  EXPECT_EQ(star->op(), kRegexpStar);
  star->Decref();
}

TEST_F(RegexpTest_339, PlusNonGreedy_339) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* plus = Regexp::Plus(sub, static_cast<Regexp::ParseFlags>(
      Regexp::LikePerl | Regexp::NonGreedy));
  ASSERT_NE(plus, nullptr);
  EXPECT_EQ(plus->op(), kRegexpPlus);
  plus->Decref();
}

TEST_F(RegexpTest_339, QuestNonGreedy_339) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* quest = Regexp::Quest(sub, static_cast<Regexp::ParseFlags>(
      Regexp::LikePerl | Regexp::NonGreedy));
  ASSERT_NE(quest, nullptr);
  EXPECT_EQ(quest->op(), kRegexpQuest);
  quest->Decref();
}

// --- NullWalk test ---

TEST_F(RegexpTest_339, NullWalkDoesNotCrash_339) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a(b|c)*d", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // NullWalk should not crash
  re->NullWalk();
  re->Decref();
}

// --- MimicsPCRE test ---

TEST_F(RegexpTest_339, MimicsPCRESimple_339) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // Simple literal should mimic PCRE
  bool mimics = re->MimicsPCRE();
  EXPECT_TRUE(mimics);
  re->Decref();
}

// --- Multiple Decref after Incref ---

TEST_F(RegexpTest_339, MultipleIncrefDecref_339) {
  Regexp* re = Regexp::NewLiteral('q', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Incref();
  re->Incref();
  // 3 references total now
  re->Decref();
  re->Decref();
  re->Decref();
}

// --- Repeat with min=0 max=0 ---

TEST_F(RegexpTest_339, RepeatZeroZero_339) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Repeat(sub, Regexp::LikePerl, 0, 0);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// --- HaveMatch with zero match_id ---

TEST_F(RegexpTest_339, HaveMatchZero_339) {
  Regexp* re = Regexp::HaveMatch(0, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), 0);
  re->Decref();
}

// --- Alternate with many subs ---

TEST_F(RegexpTest_339, AlternateManySubs_339) {
  const int n = 10;
  Regexp* subs[n];
  for (int i = 0; i < n; i++) {
    subs[i] = Regexp::NewLiteral('a' + i, Regexp::LikePerl);
  }
  Regexp* re = Regexp::Alternate(subs, n, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// --- Concat with many subs ---

TEST_F(RegexpTest_339, ConcatManySubs_339) {
  const int n = 10;
  Regexp* subs[n];
  for (int i = 0; i < n; i++) {
    subs[i] = Regexp::NewLiteral('a' + i, Regexp::LikePerl);
  }
  Regexp* re = Regexp::Concat(subs, n, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->nsub(), n);
  re->Decref();
}

}  // namespace re2
