#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"

namespace re2 {

// Helper to get default parse flags
static const Regexp::ParseFlags kTestFlags = Regexp::LikePerl;

class RegexpTest_338 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Regexp objects are reference counted; we use Decref in tests
  }
};

// --- Parse Tests ---

TEST_F(RegexpTest_338, ParseSimpleLiteral_338) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", kTestFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST_F(RegexpTest_338, ParseEmptyString_338) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", kTestFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST_F(RegexpTest_338, ParseInvalidRegexp_338) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc", kTestFlags, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

TEST_F(RegexpTest_338, ParseAlternation_338) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b|c", kTestFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST_F(RegexpTest_338, ParseCharClass_338) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", kTestFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST_F(RegexpTest_338, ParseRepetition_338) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,5}", kTestFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST_F(RegexpTest_338, ParseComplexPattern_338) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(foo|bar)+baz.*", kTestFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// --- Plus Tests ---

TEST_F(RegexpTest_338, PlusCreatesRegexp_338) {
  RegexpStatus status;
  Regexp* sub = Regexp::Parse("a", kTestFlags, &status);
  ASSERT_NE(sub, nullptr);

  Regexp* re = Regexp::Plus(sub, kTestFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

// --- Star Tests ---

TEST_F(RegexpTest_338, StarCreatesRegexp_338) {
  RegexpStatus status;
  Regexp* sub = Regexp::Parse("a", kTestFlags, &status);
  ASSERT_NE(sub, nullptr);

  Regexp* re = Regexp::Star(sub, kTestFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

// --- Quest Tests ---

TEST_F(RegexpTest_338, QuestCreatesRegexp_338) {
  RegexpStatus status;
  Regexp* sub = Regexp::Parse("a", kTestFlags, &status);
  ASSERT_NE(sub, nullptr);

  Regexp* re = Regexp::Quest(sub, kTestFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

// --- NewLiteral Tests ---

TEST_F(RegexpTest_338, NewLiteralCreatesRegexp_338) {
  Regexp* re = Regexp::NewLiteral('x', kTestFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'x');
  re->Decref();
}

TEST_F(RegexpTest_338, NewLiteralUnicode_338) {
  Regexp* re = Regexp::NewLiteral(0x4e16, kTestFlags);  // Unicode char '世'
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 0x4e16);
  re->Decref();
}

// --- LiteralString Tests ---

TEST_F(RegexpTest_338, LiteralStringCreatesRegexp_338) {
  Rune runes[] = {'h', 'e', 'l', 'l', 'o'};
  Regexp* re = Regexp::LiteralString(runes, 5, kTestFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 5);
  re->Decref();
}

TEST_F(RegexpTest_338, LiteralStringSingleChar_338) {
  Rune runes[] = {'a'};
  Regexp* re = Regexp::LiteralString(runes, 1, kTestFlags);
  ASSERT_NE(re, nullptr);
  // Single-char literal string might be optimized to kRegexpLiteral
  // or remain kRegexpLiteralString depending on implementation
  re->Decref();
}

// --- HaveMatch Tests ---

TEST_F(RegexpTest_338, HaveMatchCreatesRegexp_338) {
  Regexp* re = Regexp::HaveMatch(42, kTestFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), 42);
  re->Decref();
}

TEST_F(RegexpTest_338, HaveMatchZero_338) {
  Regexp* re = Regexp::HaveMatch(0, kTestFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), 0);
  re->Decref();
}

// --- Concat Tests ---

TEST_F(RegexpTest_338, ConcatCreatesRegexp_338) {
  Regexp* subs[3];
  subs[0] = Regexp::NewLiteral('a', kTestFlags);
  subs[1] = Regexp::NewLiteral('b', kTestFlags);
  subs[2] = Regexp::NewLiteral('c', kTestFlags);

  Regexp* re = Regexp::Concat(subs, 3, kTestFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_338, ConcatEmptyList_338) {
  Regexp* re = Regexp::Concat(nullptr, 0, kTestFlags);
  ASSERT_NE(re, nullptr);
  // Empty concat should produce an empty match
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  re->Decref();
}

TEST_F(RegexpTest_338, ConcatSingleElement_338) {
  Regexp* sub = Regexp::NewLiteral('z', kTestFlags);
  Regexp* re = Regexp::Concat(&sub, 1, kTestFlags);
  ASSERT_NE(re, nullptr);
  // Single-element concat should just return the sub
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// --- Alternate Tests ---

TEST_F(RegexpTest_338, AlternateCreatesRegexp_338) {
  Regexp* subs[3];
  subs[0] = Regexp::NewLiteral('a', kTestFlags);
  subs[1] = Regexp::NewLiteral('b', kTestFlags);
  subs[2] = Regexp::NewLiteral('c', kTestFlags);

  Regexp* re = Regexp::Alternate(subs, 3, kTestFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_338, AlternateEmpty_338) {
  Regexp* re = Regexp::Alternate(nullptr, 0, kTestFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpNoMatch);
  re->Decref();
}

TEST_F(RegexpTest_338, AlternateSingleElement_338) {
  Regexp* sub = Regexp::NewLiteral('x', kTestFlags);
  Regexp* re = Regexp::Alternate(&sub, 1, kTestFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// --- AlternateNoFactor Tests ---

TEST_F(RegexpTest_338, AlternateNoFactorCreatesRegexp_338) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', kTestFlags);
  subs[1] = Regexp::NewLiteral('b', kTestFlags);

  Regexp* re = Regexp::AlternateNoFactor(subs, 2, kTestFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// --- Capture Tests ---

TEST_F(RegexpTest_338, CaptureCreatesRegexp_338) {
  Regexp* sub = Regexp::NewLiteral('a', kTestFlags);
  Regexp* re = Regexp::Capture(sub, kTestFlags, 1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 1);
  re->Decref();
}

TEST_F(RegexpTest_338, CaptureZero_338) {
  Regexp* sub = Regexp::NewLiteral('a', kTestFlags);
  Regexp* re = Regexp::Capture(sub, kTestFlags, 0);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 0);
  re->Decref();
}

// --- Repeat Tests ---

TEST_F(RegexpTest_338, RepeatCreatesRegexp_338) {
  Regexp* sub = Regexp::NewLiteral('a', kTestFlags);
  Regexp* re = Regexp::Repeat(sub, kTestFlags, 2, 5);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), 5);
  re->Decref();
}

TEST_F(RegexpTest_338, RepeatExactCount_338) {
  Regexp* sub = Regexp::NewLiteral('b', kTestFlags);
  Regexp* re = Regexp::Repeat(sub, kTestFlags, 3, 3);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 3);
  EXPECT_EQ(re->max(), 3);
  re->Decref();
}

TEST_F(RegexpTest_338, RepeatUnbounded_338) {
  Regexp* sub = Regexp::NewLiteral('c', kTestFlags);
  Regexp* re = Regexp::Repeat(sub, kTestFlags, 1, -1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 1);
  EXPECT_EQ(re->max(), -1);
  re->Decref();
}

// --- ToString Tests ---

TEST_F(RegexpTest_338, ToStringLiteral_338) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", kTestFlags, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

TEST_F(RegexpTest_338, ToStringComplex_338) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a|b)+c*", kTestFlags, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// --- Dump Tests ---

TEST_F(RegexpTest_338, DumpProducesOutput_338) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+b*", kTestFlags, &status);
  ASSERT_NE(re, nullptr);
  std::string d = re->Dump();
  EXPECT_FALSE(d.empty());
  re->Decref();
}

// --- NumCaptures Tests ---

TEST_F(RegexpTest_338, NumCapturesNone_338) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", kTestFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

TEST_F(RegexpTest_338, NumCapturesOne_338) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc)", kTestFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 1);
  re->Decref();
}

TEST_F(RegexpTest_338, NumCapturesMultiple_338) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)(c)", kTestFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

TEST_F(RegexpTest_338, NumCapturesNested_338) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((a)(b))", kTestFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// --- NamedCaptures Tests ---

TEST_F(RegexpTest_338, NamedCapturesNone_338) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", kTestFlags, &status);
  ASSERT_NE(re, nullptr);
  auto* named = re->NamedCaptures();
  // No named captures, should return nullptr
  EXPECT_EQ(named, nullptr);
  delete named;
  re->Decref();
}

TEST_F(RegexpTest_338, NamedCapturesPresent_338) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<name>abc)", kTestFlags, &status);
  ASSERT_NE(re, nullptr);
  auto* named = re->NamedCaptures();
  ASSERT_NE(named, nullptr);
  EXPECT_EQ(named->size(), 1u);
  EXPECT_NE(named->find("name"), named->end());
  delete named;
  re->Decref();
}

// --- CaptureNames Tests ---

TEST_F(RegexpTest_338, CaptureNamesNone_338) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", kTestFlags, &status);
  ASSERT_NE(re, nullptr);
  auto* names = re->CaptureNames();
  // No capture names
  EXPECT_EQ(names, nullptr);
  delete names;
  re->Decref();
}

TEST_F(RegexpTest_338, CaptureNamesPresent_338) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<foo>a)(?P<bar>b)", kTestFlags, &status);
  ASSERT_NE(re, nullptr);
  auto* names = re->CaptureNames();
  ASSERT_NE(names, nullptr);
  EXPECT_EQ(names->size(), 2u);
  delete names;
  re->Decref();
}

// --- Simplify Tests ---

TEST_F(RegexpTest_338, SimplifyReturnsNonNull_338) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,5}", kTestFlags, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// --- SimplifyRegexp Tests ---

TEST_F(RegexpTest_338, SimplifyRegexpSucceeds_338) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{2,4}", kTestFlags, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

TEST_F(RegexpTest_338, SimplifyRegexpInvalid_338) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("(abc", kTestFlags, &dst, &status);
  EXPECT_FALSE(ok);
}

// --- Reference Counting Tests ---

TEST_F(RegexpTest_338, IncrefDecref_338) {
  Regexp* re = Regexp::NewLiteral('a', kTestFlags);
  ASSERT_NE(re, nullptr);
  // Initially ref should be 1 (or at least positive)
  Regexp* re2 = re->Incref();
  EXPECT_EQ(re2, re);
  // Now decref twice
  re->Decref();
  re->Decref();
}

// --- Op accessor Tests ---

TEST_F(RegexpTest_338, OpAccessorLiteral_338) {
  Regexp* re = Regexp::NewLiteral('z', kTestFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

TEST_F(RegexpTest_338, OpAccessorStar_338) {
  Regexp* sub = Regexp::NewLiteral('a', kTestFlags);
  Regexp* re = Regexp::Star(sub, kTestFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

TEST_F(RegexpTest_338, OpAccessorQuest_338) {
  Regexp* sub = Regexp::NewLiteral('a', kTestFlags);
  Regexp* re = Regexp::Quest(sub, kTestFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

TEST_F(RegexpTest_338, OpAccessorPlus_338) {
  Regexp* sub = Regexp::NewLiteral('a', kTestFlags);
  Regexp* re = Regexp::Plus(sub, kTestFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

// --- parse_flags accessor Tests ---

TEST_F(RegexpTest_338, ParseFlagsAccessor_338) {
  Regexp* re = Regexp::NewLiteral('a', kTestFlags);
  ASSERT_NE(re, nullptr);
  // The parse flags should at least include what we set
  EXPECT_NE(re->parse_flags() & kTestFlags, Regexp::ParseFlags(0));
  re->Decref();
}

// --- CompileToProg Tests ---

TEST_F(RegexpTest_338, CompileToProgSucceeds_338) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+b", kTestFlags, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// --- CompileToReverseProg Tests ---

TEST_F(RegexpTest_338, CompileToReverseProgSucceeds_338) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", kTestFlags, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// --- RequiredPrefix Tests ---

TEST_F(RegexpTest_338, RequiredPrefixLiteral_338) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc.*", kTestFlags, &status);
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

TEST_F(RegexpTest_338, RequiredPrefixNoPrefix_338) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".*abc", kTestFlags, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;
  bool has_prefix = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  EXPECT_FALSE(has_prefix);
  re->Decref();
}

// --- NullWalk Tests ---

TEST_F(RegexpTest_338, NullWalkDoesNotCrash_338) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a|b)*c+", kTestFlags, &status);
  ASSERT_NE(re, nullptr);
  // NullWalk should not crash
  re->NullWalk();
  re->Decref();
}

// --- nsub accessor Tests ---

TEST_F(RegexpTest_338, NsubForPlus_338) {
  Regexp* sub = Regexp::NewLiteral('a', kTestFlags);
  Regexp* re = Regexp::Plus(sub, kTestFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->nsub(), 1);
  re->Decref();
}

TEST_F(RegexpTest_338, NsubForConcat_338) {
  Regexp* subs[3];
  subs[0] = Regexp::NewLiteral('a', kTestFlags);
  subs[1] = Regexp::NewLiteral('b', kTestFlags);
  subs[2] = Regexp::NewLiteral('c', kTestFlags);

  Regexp* re = Regexp::Concat(subs, 3, kTestFlags);
  ASSERT_NE(re, nullptr);
  if (re->op() == kRegexpConcat) {
    EXPECT_EQ(re->nsub(), 3);
  }
  re->Decref();
}

// --- Boundary: Parse complex nested patterns ---

TEST_F(RegexpTest_338, ParseDeeplyNested_338) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((((a))))", kTestFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 4);
  re->Decref();
}

// --- Boundary: Single character patterns ---

TEST_F(RegexpTest_338, ParseSingleChar_338) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", kTestFlags, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "a");
  re->Decref();
}

// --- Boundary: Dot pattern ---

TEST_F(RegexpTest_338, ParseDot_338) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".", kTestFlags, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// --- Error case: Unbalanced brackets ---

TEST_F(RegexpTest_338, ParseUnbalancedBracket_338) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[abc", kTestFlags, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

// --- Error case: Bad repetition ---

TEST_F(RegexpTest_338, ParseBadRepetition_338) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("*", kTestFlags, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

// --- MimicsPCRE Tests ---

TEST_F(RegexpTest_338, MimicsPCRESimple_338) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", kTestFlags, &status);
  ASSERT_NE(re, nullptr);
  // Simple patterns should mimic PCRE
  bool mimics = re->MimicsPCRE();
  EXPECT_TRUE(mimics);
  re->Decref();
}

// --- RequiredPrefixForAccel Tests ---

TEST_F(RegexpTest_338, RequiredPrefixForAccelLiteral_338) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc.*", kTestFlags, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  re->RequiredPrefixForAccel(&prefix, &foldcase);
  // Just ensure it doesn't crash; prefix may or may not be found
  re->Decref();
}

}  // namespace re2
