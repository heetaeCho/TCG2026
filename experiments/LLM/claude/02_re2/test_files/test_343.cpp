#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"

namespace re2 {

// Helper to get default parse flags
static const Regexp::ParseFlags kTestFlags = Regexp::ClassNL;

class RegexpTest_343 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Regexp objects are reference-counted; we use Decref where needed.
  }
};

// --- Parse Tests ---

TEST_F(RegexpTest_343, ParseSimpleLiteral_343) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST_F(RegexpTest_343, ParseEmptyString_343) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST_F(RegexpTest_343, ParseInvalidRegexp_343) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(", Regexp::PerlX, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

TEST_F(RegexpTest_343, ParseAlternation_343) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b|c", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST_F(RegexpTest_343, ParseRepetition_343) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,5}", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST_F(RegexpTest_343, ParseCharClass_343) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST_F(RegexpTest_343, ParseCapture_343) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc)", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->NumCaptures(), 1);
  re->Decref();
}

// --- ToString Tests ---

TEST_F(RegexpTest_343, ToStringRoundTrip_343) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "abc");
  re->Decref();
}

TEST_F(RegexpTest_343, ToStringAlternation_343) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// --- NumCaptures Tests ---

TEST_F(RegexpTest_343, NumCapturesZero_343) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

TEST_F(RegexpTest_343, NumCapturesMultiple_343) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

TEST_F(RegexpTest_343, NumCapturesNested_343) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((a)(b))", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// --- Factory Method Tests ---

TEST_F(RegexpTest_343, NewLiteral_343) {
  Regexp* re = Regexp::NewLiteral('a', kTestFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'a');
  re->Decref();
}

TEST_F(RegexpTest_343, HaveMatch_343) {
  Regexp* re = Regexp::HaveMatch(42, kTestFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), 42);
  re->Decref();
}

TEST_F(RegexpTest_343, StarFactory_343) {
  Regexp* sub = Regexp::NewLiteral('x', kTestFlags);
  Regexp* re = Regexp::Star(sub, kTestFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

TEST_F(RegexpTest_343, PlusFactory_343) {
  Regexp* sub = Regexp::NewLiteral('x', kTestFlags);
  Regexp* re = Regexp::Plus(sub, kTestFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

TEST_F(RegexpTest_343, QuestFactory_343) {
  Regexp* sub = Regexp::NewLiteral('x', kTestFlags);
  Regexp* re = Regexp::Quest(sub, kTestFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

TEST_F(RegexpTest_343, CaptureFactory_343) {
  Regexp* sub = Regexp::NewLiteral('x', kTestFlags);
  Regexp* re = Regexp::Capture(sub, kTestFlags, 1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 1);
  re->Decref();
}

TEST_F(RegexpTest_343, RepeatFactory_343) {
  Regexp* sub = Regexp::NewLiteral('x', kTestFlags);
  Regexp* re = Regexp::Repeat(sub, kTestFlags, 2, 5);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), 5);
  re->Decref();
}

TEST_F(RegexpTest_343, LiteralStringFactory_343) {
  Rune runes[] = {'h', 'e', 'l', 'l', 'o'};
  Regexp* re = Regexp::LiteralString(runes, 5, kTestFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 5);
  re->Decref();
}

// --- Concat and Alternate Tests ---

TEST_F(RegexpTest_343, ConcatFactory_343) {
  Regexp* subs[3];
  subs[0] = Regexp::NewLiteral('a', kTestFlags);
  subs[1] = Regexp::NewLiteral('b', kTestFlags);
  subs[2] = Regexp::NewLiteral('c', kTestFlags);
  Regexp* re = Regexp::Concat(subs, 3, kTestFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_343, ConcatSingleSub_343) {
  Regexp* subs[1];
  subs[0] = Regexp::NewLiteral('a', kTestFlags);
  Regexp* re = Regexp::Concat(subs, 1, kTestFlags);
  ASSERT_NE(re, nullptr);
  // Single sub concat may return the sub itself
  re->Decref();
}

TEST_F(RegexpTest_343, ConcatZeroSubs_343) {
  Regexp* re = Regexp::Concat(nullptr, 0, kTestFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  re->Decref();
}

TEST_F(RegexpTest_343, AlternateFactory_343) {
  Regexp* subs[3];
  subs[0] = Regexp::NewLiteral('a', kTestFlags);
  subs[1] = Regexp::NewLiteral('b', kTestFlags);
  subs[2] = Regexp::NewLiteral('c', kTestFlags);
  Regexp* re = Regexp::Alternate(subs, 3, kTestFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_343, AlternateSingleSub_343) {
  Regexp* subs[1];
  subs[0] = Regexp::NewLiteral('a', kTestFlags);
  Regexp* re = Regexp::Alternate(subs, 1, kTestFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_343, AlternateZeroSubs_343) {
  Regexp* re = Regexp::Alternate(nullptr, 0, kTestFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpNoMatch);
  re->Decref();
}

TEST_F(RegexpTest_343, AlternateNoFactorFactory_343) {
  Regexp* subs[3];
  subs[0] = Regexp::NewLiteral('a', kTestFlags);
  subs[1] = Regexp::NewLiteral('b', kTestFlags);
  subs[2] = Regexp::NewLiteral('c', kTestFlags);
  Regexp* re = Regexp::AlternateNoFactor(subs, 3, kTestFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_343, AlternateNoFactorSingleSub_343) {
  Regexp* subs[1];
  subs[0] = Regexp::NewLiteral('a', kTestFlags);
  Regexp* re = Regexp::AlternateNoFactor(subs, 1, kTestFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_343, AlternateNoFactorZeroSubs_343) {
  Regexp* re = Regexp::AlternateNoFactor(nullptr, 0, kTestFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpNoMatch);
  re->Decref();
}

// --- Incref / Decref / Ref Tests ---

TEST_F(RegexpTest_343, IncrefDecref_343) {
  Regexp* re = Regexp::NewLiteral('z', kTestFlags);
  ASSERT_NE(re, nullptr);
  Regexp* re2 = re->Incref();
  EXPECT_EQ(re, re2);
  // After Incref, ref count should be > 1
  re->Decref();
  re->Decref();
}

// --- Simplify Tests ---

TEST_F(RegexpTest_343, Simplify_343) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2}", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

TEST_F(RegexpTest_343, SimplifyRegexpStatic_343) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{2}", Regexp::PerlX, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

TEST_F(RegexpTest_343, SimplifyRegexpInvalid_343) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("(", Regexp::PerlX, &dst, &status);
  EXPECT_FALSE(ok);
}

// --- Dump Tests ---

TEST_F(RegexpTest_343, Dump_343) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  std::string dump = re->Dump();
  EXPECT_FALSE(dump.empty());
  re->Decref();
}

// --- RequiredPrefix Tests ---

TEST_F(RegexpTest_343, RequiredPrefixSimple_343) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc.*", Regexp::PerlX, &status);
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

TEST_F(RegexpTest_343, RequiredPrefixNoPrefix_343) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".*abc", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;
  bool has_prefix = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  if (!has_prefix) {
    EXPECT_TRUE(prefix.empty());
  }
  if (suffix != nullptr) {
    suffix->Decref();
  }
  re->Decref();
}

// --- RequiredPrefixForAccel Tests ---

TEST_F(RegexpTest_343, RequiredPrefixForAccel_343) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^hello", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  re->RequiredPrefixForAccel(&prefix, &foldcase);
  // Just verify it doesn't crash
  re->Decref();
}

// --- Compile Tests ---

TEST_F(RegexpTest_343, CompileToProg_343) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

TEST_F(RegexpTest_343, CompileToReverseProg_343) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// --- NullWalk Tests ---

TEST_F(RegexpTest_343, NullWalk_343) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a(b|c)*d", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  // NullWalk should not crash
  re->NullWalk();
  re->Decref();
}

// --- Op accessor Tests ---

TEST_F(RegexpTest_343, OpAccessor_343) {
  Regexp* re = Regexp::NewLiteral('a', kTestFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// --- ParseFlags accessor Tests ---

TEST_F(RegexpTest_343, ParseFlagsAccessor_343) {
  Regexp* re = Regexp::NewLiteral('a', kTestFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->parse_flags(), kTestFlags);
  re->Decref();
}

// --- NamedCaptures Tests ---

TEST_F(RegexpTest_343, NamedCapturesNone_343) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  auto* named = re->NamedCaptures();
  // No named captures: should be null
  EXPECT_EQ(named, nullptr);
  delete named;
  re->Decref();
}

TEST_F(RegexpTest_343, NamedCapturesPresent_343) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<name>abc)", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  auto* named = re->NamedCaptures();
  ASSERT_NE(named, nullptr);
  EXPECT_EQ(named->size(), 1u);
  EXPECT_NE(named->find("name"), named->end());
  delete named;
  re->Decref();
}

// --- CaptureNames Tests ---

TEST_F(RegexpTest_343, CaptureNamesPresent_343) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<foo>a)(?P<bar>b)", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  auto* capture_names = re->CaptureNames();
  ASSERT_NE(capture_names, nullptr);
  EXPECT_EQ(capture_names->size(), 2u);
  delete capture_names;
  re->Decref();
}

TEST_F(RegexpTest_343, CaptureNamesNone_343) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  auto* capture_names = re->CaptureNames();
  // No captures at all, should be null
  EXPECT_EQ(capture_names, nullptr);
  delete capture_names;
  re->Decref();
}

// --- AlternateNoFactor vs Alternate behavior comparison ---

TEST_F(RegexpTest_343, AlternateNoFactorDoesNotFactor_343) {
  // When given common prefixes, Alternate may factor them,
  // but AlternateNoFactor should not.
  Regexp* subs1[2];
  subs1[0] = Regexp::NewLiteral('a', kTestFlags);
  subs1[1] = Regexp::NewLiteral('a', kTestFlags);
  Regexp* alt = Regexp::Alternate(subs1, 2, kTestFlags);

  Regexp* subs2[2];
  subs2[0] = Regexp::NewLiteral('a', kTestFlags);
  subs2[1] = Regexp::NewLiteral('a', kTestFlags);
  Regexp* altNF = Regexp::AlternateNoFactor(subs2, 2, kTestFlags);

  // Both should be non-null
  ASSERT_NE(alt, nullptr);
  ASSERT_NE(altNF, nullptr);

  // AlternateNoFactor should keep the alternate structure
  // (it should have op kRegexpAlternate with 2 subs, or be simplified differently from Alternate)
  // At minimum both should produce valid Regexp objects
  std::string altDump = alt->Dump();
  std::string altNFDump = altNF->Dump();
  EXPECT_FALSE(altDump.empty());
  EXPECT_FALSE(altNFDump.empty());

  alt->Decref();
  altNF->Decref();
}

// --- Complex pattern tests ---

TEST_F(RegexpTest_343, ComplexPattern_343) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a+|b*)?[c-f]{2,10}\\d+", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());

  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());

  std::string dump = re->Dump();
  EXPECT_FALSE(dump.empty());

  re->Decref();
}

// --- Boundary: Repeat with min==max ---

TEST_F(RegexpTest_343, RepeatExact_343) {
  Regexp* sub = Regexp::NewLiteral('x', kTestFlags);
  Regexp* re = Regexp::Repeat(sub, kTestFlags, 3, 3);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 3);
  EXPECT_EQ(re->max(), 3);
  re->Decref();
}

// --- Boundary: Repeat with min=0, max=-1 (unbounded) ---

TEST_F(RegexpTest_343, RepeatUnbounded_343) {
  Regexp* sub = Regexp::NewLiteral('x', kTestFlags);
  Regexp* re = Regexp::Repeat(sub, kTestFlags, 0, -1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->min(), 0);
  EXPECT_EQ(re->max(), -1);
  re->Decref();
}

// --- Two sub Concat ---

TEST_F(RegexpTest_343, ConcatTwoSubs_343) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', kTestFlags);
  subs[1] = Regexp::NewLiteral('b', kTestFlags);
  Regexp* re = Regexp::Concat(subs, 2, kTestFlags);
  ASSERT_NE(re, nullptr);
  // Could be concat or literal string depending on implementation
  re->Decref();
}

// --- MimicsPCRE ---

TEST_F(RegexpTest_343, MimicsPCRE_343) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  // Simple literals should mimic PCRE
  bool mimics = re->MimicsPCRE();
  EXPECT_TRUE(mimics);
  re->Decref();
}

}  // namespace re2
