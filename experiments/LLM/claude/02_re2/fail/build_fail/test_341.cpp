#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"

namespace re2 {

class RegexpTest_341 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// ==================== Parse Tests ====================

TEST_F(RegexpTest_341, ParseSimpleLiteral_341) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST_F(RegexpTest_341, ParseEmptyString_341) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST_F(RegexpTest_341, ParseInvalidRegexp_341) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

TEST_F(RegexpTest_341, ParseAlternation_341) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b|c", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST_F(RegexpTest_341, ParseCharacterClass_341) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST_F(RegexpTest_341, ParseRepetition_341) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST_F(RegexpTest_341, ParseCapture_341) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST_F(RegexpTest_341, ParseNestedGroups_341) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((a)(b))", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// ==================== ToString Tests ====================

TEST_F(RegexpTest_341, ToStringSimple_341) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

TEST_F(RegexpTest_341, ToStringRoundTrip_341) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*b+c?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  // Parse it again to ensure round trip works
  Regexp* re2 = Regexp::Parse(s, Regexp::LikePerl, &status);
  ASSERT_NE(re2, nullptr);
  re->Decref();
  re2->Decref();
}

// ==================== NumCaptures Tests ====================

TEST_F(RegexpTest_341, NumCapturesZero_341) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

TEST_F(RegexpTest_341, NumCapturesOne_341) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 1);
  re->Decref();
}

TEST_F(RegexpTest_341, NumCapturesMultiple_341) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

TEST_F(RegexpTest_341, NumCapturesNested_341) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((a)(b))", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// ==================== Concat Tests ====================

TEST_F(RegexpTest_341, ConcatSingleSub_341) {
  Regexp* lit = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(lit, nullptr);
  Regexp* subs[] = {lit};
  Regexp* result = Regexp::Concat(subs, 1, Regexp::LikePerl);
  ASSERT_NE(result, nullptr);
  // When only one sub, the result should be that sub itself
  result->Decref();
}

TEST_F(RegexpTest_341, ConcatMultipleSubs_341) {
  Regexp* a = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* b = Regexp::NewLiteral('b', Regexp::LikePerl);
  Regexp* c = Regexp::NewLiteral('c', Regexp::LikePerl);
  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);
  ASSERT_NE(c, nullptr);
  Regexp* subs[] = {a, b, c};
  Regexp* result = Regexp::Concat(subs, 3, Regexp::LikePerl);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->op(), kRegexpConcat);
  EXPECT_EQ(result->nsub(), 3);
  result->Decref();
}

TEST_F(RegexpTest_341, ConcatZeroSubs_341) {
  Regexp* result = Regexp::Concat(nullptr, 0, Regexp::LikePerl);
  ASSERT_NE(result, nullptr);
  // Zero sub concat should return an empty match
  EXPECT_EQ(result->op(), kRegexpEmptyMatch);
  result->Decref();
}

// ==================== Alternate Tests ====================

TEST_F(RegexpTest_341, AlternateSingleSub_341) {
  Regexp* lit = Regexp::NewLiteral('x', Regexp::LikePerl);
  ASSERT_NE(lit, nullptr);
  Regexp* subs[] = {lit};
  Regexp* result = Regexp::Alternate(subs, 1, Regexp::LikePerl);
  ASSERT_NE(result, nullptr);
  result->Decref();
}

TEST_F(RegexpTest_341, AlternateMultipleSubs_341) {
  Regexp* a = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* b = Regexp::NewLiteral('b', Regexp::LikePerl);
  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);
  Regexp* subs[] = {a, b};
  Regexp* result = Regexp::Alternate(subs, 2, Regexp::LikePerl);
  ASSERT_NE(result, nullptr);
  result->Decref();
}

TEST_F(RegexpTest_341, AlternateZeroSubs_341) {
  Regexp* result = Regexp::Alternate(nullptr, 0, Regexp::LikePerl);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->op(), kRegexpNoMatch);
  result->Decref();
}

// ==================== AlternateNoFactor Tests ====================

TEST_F(RegexpTest_341, AlternateNoFactorMultipleSubs_341) {
  Regexp* a = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* b = Regexp::NewLiteral('b', Regexp::LikePerl);
  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);
  Regexp* subs[] = {a, b};
  Regexp* result = Regexp::AlternateNoFactor(subs, 2, Regexp::LikePerl);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->op(), kRegexpAlternate);
  result->Decref();
}

// ==================== Star/Plus/Quest Tests ====================

TEST_F(RegexpTest_341, StarCreation_341) {
  Regexp* lit = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(lit, nullptr);
  Regexp* result = Regexp::Star(lit, Regexp::LikePerl);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->op(), kRegexpStar);
  result->Decref();
}

TEST_F(RegexpTest_341, PlusCreation_341) {
  Regexp* lit = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(lit, nullptr);
  Regexp* result = Regexp::Plus(lit, Regexp::LikePerl);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->op(), kRegexpPlus);
  result->Decref();
}

TEST_F(RegexpTest_341, QuestCreation_341) {
  Regexp* lit = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(lit, nullptr);
  Regexp* result = Regexp::Quest(lit, Regexp::LikePerl);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->op(), kRegexpQuest);
  result->Decref();
}

// ==================== NewLiteral Tests ====================

TEST_F(RegexpTest_341, NewLiteralBasic_341) {
  Regexp* re = Regexp::NewLiteral('z', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'z');
  re->Decref();
}

TEST_F(RegexpTest_341, NewLiteralUnicode_341) {
  Regexp* re = Regexp::NewLiteral(0x00E9, Regexp::LikePerl);  // é
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 0x00E9);
  re->Decref();
}

// ==================== LiteralString Tests ====================

TEST_F(RegexpTest_341, LiteralStringBasic_341) {
  Rune runes[] = {'h', 'e', 'l', 'l', 'o'};
  Regexp* re = Regexp::LiteralString(runes, 5, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 5);
  re->Decref();
}

TEST_F(RegexpTest_341, LiteralStringSingleRune_341) {
  Rune runes[] = {'a'};
  Regexp* re = Regexp::LiteralString(runes, 1, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  // Single rune literal string might be optimized to kRegexpLiteral
  re->Decref();
}

// ==================== HaveMatch Tests ====================

TEST_F(RegexpTest_341, HaveMatchBasic_341) {
  Regexp* re = Regexp::HaveMatch(42, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), 42);
  re->Decref();
}

TEST_F(RegexpTest_341, HaveMatchZero_341) {
  Regexp* re = Regexp::HaveMatch(0, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), 0);
  re->Decref();
}

// ==================== Capture Tests ====================

TEST_F(RegexpTest_341, CaptureBasic_341) {
  Regexp* lit = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(lit, nullptr);
  Regexp* result = Regexp::Capture(lit, Regexp::LikePerl, 1);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->op(), kRegexpCapture);
  EXPECT_EQ(result->cap(), 1);
  result->Decref();
}

// ==================== Repeat Tests ====================

TEST_F(RegexpTest_341, RepeatExact_341) {
  Regexp* lit = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(lit, nullptr);
  Regexp* result = Regexp::Repeat(lit, Regexp::LikePerl, 3, 3);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->op(), kRegexpRepeat);
  EXPECT_EQ(result->min(), 3);
  EXPECT_EQ(result->max(), 3);
  result->Decref();
}

TEST_F(RegexpTest_341, RepeatRange_341) {
  Regexp* lit = Regexp::NewLiteral('b', Regexp::LikePerl);
  ASSERT_NE(lit, nullptr);
  Regexp* result = Regexp::Repeat(lit, Regexp::LikePerl, 2, 5);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->op(), kRegexpRepeat);
  EXPECT_EQ(result->min(), 2);
  EXPECT_EQ(result->max(), 5);
  result->Decref();
}

TEST_F(RegexpTest_341, RepeatUnbounded_341) {
  Regexp* lit = Regexp::NewLiteral('c', Regexp::LikePerl);
  ASSERT_NE(lit, nullptr);
  Regexp* result = Regexp::Repeat(lit, Regexp::LikePerl, 1, -1);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->min(), 1);
  EXPECT_EQ(result->max(), -1);
  result->Decref();
}

// ==================== Incref/Decref/Ref Tests ====================

TEST_F(RegexpTest_341, IncrefDecref_341) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  // Initial ref should be at least 1
  Regexp* increfed = re->Incref();
  EXPECT_EQ(increfed, re);
  // Now decref twice (once for incref, once for the original)
  re->Decref();
  re->Decref();
}

// ==================== Simplify Tests ====================

TEST_F(RegexpTest_341, SimplifyBasic_341) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// ==================== SimplifyRegexp Tests ====================

TEST_F(RegexpTest_341, SimplifyRegexpStatic_341) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{2,4}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

TEST_F(RegexpTest_341, SimplifyRegexpInvalid_341) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("(", Regexp::LikePerl, &dst, &status);
  EXPECT_FALSE(ok);
}

// ==================== Dump Tests ====================

TEST_F(RegexpTest_341, DumpLiteral_341) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  std::string dump = re->Dump();
  EXPECT_FALSE(dump.empty());
  re->Decref();
}

TEST_F(RegexpTest_341, DumpParsed_341) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a|b)*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string dump = re->Dump();
  EXPECT_FALSE(dump.empty());
  re->Decref();
}

// ==================== RequiredPrefix Tests ====================

TEST_F(RegexpTest_341, RequiredPrefixWithLiteralPrefix_341) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc.*", Regexp::LikePerl, &status);
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

TEST_F(RegexpTest_341, RequiredPrefixNoPrefix_341) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".*abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;
  bool has_prefix = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  if (!has_prefix) {
    EXPECT_TRUE(prefix.empty());
  } else {
    if (suffix != nullptr) {
      suffix->Decref();
    }
  }
  re->Decref();
}

// ==================== NamedCaptures Tests ====================

TEST_F(RegexpTest_341, NamedCapturesNone_341) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* named = re->NamedCaptures();
  // No named captures, so should return nullptr
  EXPECT_EQ(named, nullptr);
  delete named;
  re->Decref();
}

TEST_F(RegexpTest_341, NamedCapturesPresent_341) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<name>abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* named = re->NamedCaptures();
  ASSERT_NE(named, nullptr);
  EXPECT_EQ(named->size(), 1u);
  EXPECT_NE(named->find("name"), named->end());
  delete named;
  re->Decref();
}

// ==================== CaptureNames Tests ====================

TEST_F(RegexpTest_341, CaptureNamesNone_341) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<int, std::string>* names = re->CaptureNames();
  EXPECT_EQ(names, nullptr);
  delete names;
  re->Decref();
}

TEST_F(RegexpTest_341, CaptureNamesPresent_341) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<first>a)(?P<second>b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<int, std::string>* names = re->CaptureNames();
  ASSERT_NE(names, nullptr);
  EXPECT_EQ(names->size(), 2u);
  delete names;
  re->Decref();
}

// ==================== CompileToProg Tests ====================

TEST_F(RegexpTest_341, CompileToProgBasic_341) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

TEST_F(RegexpTest_341, CompileToReverseProgBasic_341) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// ==================== Op and ParseFlags Tests ====================

TEST_F(RegexpTest_341, OpOfParsedRegexp_341) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

TEST_F(RegexpTest_341, OpOfParsedConcat_341) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // "abc" should be a concat of literals or a literal string
  RegexpOp op = re->op();
  EXPECT_TRUE(op == kRegexpConcat || op == kRegexpLiteralString);
  re->Decref();
}

// ==================== Complex Pattern Tests ====================

TEST_F(RegexpTest_341, ComplexPatternParse_341) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^(foo|bar).*baz[0-9]+$", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

TEST_F(RegexpTest_341, NullWalk_341) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a|b)*c+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // NullWalk should not crash
  re->NullWalk();
  re->Decref();
}

// ==================== RequiredPrefixForAccel Tests ====================

TEST_F(RegexpTest_341, RequiredPrefixForAccelBasic_341) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^hello", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  re->RequiredPrefixForAccel(&prefix, &foldcase);
  // Just verify it doesn't crash; prefix may or may not be set
  re->Decref();
}

// ==================== Sub Access Tests ====================

TEST_F(RegexpTest_341, SubAccessOnConcat_341) {
  Regexp* a = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* b = Regexp::NewLiteral('b', Regexp::LikePerl);
  Regexp* subs[] = {a, b};
  Regexp* result = Regexp::Concat(subs, 2, Regexp::LikePerl);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->op(), kRegexpConcat);
  EXPECT_EQ(result->nsub(), 2);
  Regexp** result_subs = result->sub();
  ASSERT_NE(result_subs, nullptr);
  EXPECT_EQ(result_subs[0]->op(), kRegexpLiteral);
  EXPECT_EQ(result_subs[1]->op(), kRegexpLiteral);
  result->Decref();
}

// ==================== simple() Tests ====================

TEST_F(RegexpTest_341, SimpleAfterParse_341) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // simple() returns a bool; just verify it doesn't crash
  bool s = re->simple();
  (void)s;
  re->Decref();
}

// ==================== parse_flags() Tests ====================

TEST_F(RegexpTest_341, ParseFlagsAccessor_341) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  Regexp::ParseFlags pf = re->parse_flags();
  // Should include at least the flags we specified
  EXPECT_NE(pf & Regexp::LikePerl, 0);
  re->Decref();
}

}  // namespace re2
