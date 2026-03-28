#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"

namespace re2 {

class RegexpTest_162 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// Test HaveMatch creates a regexp with the correct match_id
TEST_F(RegexpTest_162, HaveMatchReturnsCorrectMatchId_162) {
  Regexp* re = Regexp::HaveMatch(42, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), 42);
  re->Decref();
}

// Test HaveMatch with match_id of 0
TEST_F(RegexpTest_162, HaveMatchWithZeroMatchId_162) {
  Regexp* re = Regexp::HaveMatch(0, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->match_id(), 0);
  re->Decref();
}

// Test HaveMatch with negative match_id
TEST_F(RegexpTest_162, HaveMatchWithNegativeMatchId_162) {
  Regexp* re = Regexp::HaveMatch(-1, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->match_id(), -1);
  re->Decref();
}

// Test HaveMatch with large match_id
TEST_F(RegexpTest_162, HaveMatchWithLargeMatchId_162) {
  Regexp* re = Regexp::HaveMatch(999999, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->match_id(), 999999);
  re->Decref();
}

// Test Parse returns a valid Regexp for a simple pattern
TEST_F(RegexpTest_162, ParseSimplePattern_162) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test Parse returns null for an invalid pattern
TEST_F(RegexpTest_162, ParseInvalidPattern_162) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[invalid", Regexp::NoParseFlags, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

// Test Parse empty pattern
TEST_F(RegexpTest_162, ParseEmptyPattern_162) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  re->Decref();
}

// Test NewLiteral creates a regexp with the correct rune
TEST_F(RegexpTest_162, NewLiteralCreatesCorrectRune_162) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'a');
  re->Decref();
}

// Test Plus creates a regexp with kRegexpPlus op
TEST_F(RegexpTest_162, PlusCreatesCorrectOp_162) {
  Regexp* sub = Regexp::NewLiteral('x', Regexp::NoParseFlags);
  Regexp* re = Regexp::Plus(sub, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

// Test Star creates a regexp with kRegexpStar op
TEST_F(RegexpTest_162, StarCreatesCorrectOp_162) {
  Regexp* sub = Regexp::NewLiteral('y', Regexp::NoParseFlags);
  Regexp* re = Regexp::Star(sub, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

// Test Quest creates a regexp with kRegexpQuest op
TEST_F(RegexpTest_162, QuestCreatesCorrectOp_162) {
  Regexp* sub = Regexp::NewLiteral('z', Regexp::NoParseFlags);
  Regexp* re = Regexp::Quest(sub, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

// Test Concat creates a regexp with kRegexpConcat op
TEST_F(RegexpTest_162, ConcatCreatesCorrectOp_162) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* re = Regexp::Concat(subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpConcat);
  EXPECT_EQ(re->nsub(), 2);
  re->Decref();
}

// Test Concat with single sub returns the sub itself
TEST_F(RegexpTest_162, ConcatSingleSubReturnsSub_162) {
  Regexp* subs[1];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Concat(subs, 1, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// Test Concat with zero subs returns empty match
TEST_F(RegexpTest_162, ConcatZeroSubsReturnsEmptyMatch_162) {
  Regexp* re = Regexp::Concat(nullptr, 0, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  re->Decref();
}

// Test Alternate creates a regexp with kRegexpAlternate op
TEST_F(RegexpTest_162, AlternateCreatesCorrectOp_162) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* re = Regexp::Alternate(subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Alternate with zero subs returns NoMatch
TEST_F(RegexpTest_162, AlternateZeroSubsReturnsNoMatch_162) {
  Regexp* re = Regexp::Alternate(nullptr, 0, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpNoMatch);
  re->Decref();
}

// Test Alternate with single sub returns the sub
TEST_F(RegexpTest_162, AlternateSingleSubReturnsSub_162) {
  Regexp* subs[1];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Alternate(subs, 1, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// Test Capture creates a regexp with kRegexpCapture op
TEST_F(RegexpTest_162, CaptureCreatesCorrectOp_162) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Capture(sub, Regexp::NoParseFlags, 1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 1);
  re->Decref();
}

// Test Repeat creates a regexp with kRegexpRepeat op
TEST_F(RegexpTest_162, RepeatCreatesCorrectOp_162) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 2, 5);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), 5);
  re->Decref();
}

// Test Repeat with min == max
TEST_F(RegexpTest_162, RepeatExactCount_162) {
  Regexp* sub = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 3, 3);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->min(), 3);
  EXPECT_EQ(re->max(), 3);
  re->Decref();
}

// Test Repeat with unbounded max (-1 typically means unbounded)
TEST_F(RegexpTest_162, RepeatUnbounded_162) {
  Regexp* sub = Regexp::NewLiteral('c', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 1, -1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->min(), 1);
  EXPECT_EQ(re->max(), -1);
  re->Decref();
}

// Test LiteralString creates a regexp with kRegexpLiteralString op
TEST_F(RegexpTest_162, LiteralStringCreatesCorrectOp_162) {
  Rune runes[] = {'h', 'e', 'l', 'l', 'o'};
  Regexp* re = Regexp::LiteralString(runes, 5, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 5);
  re->Decref();
}

// Test Incref and Decref reference counting
TEST_F(RegexpTest_162, IncrefIncrementsRefCount_162) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  // Initial ref count should be 1
  Regexp* re2 = re->Incref();
  EXPECT_EQ(re, re2);
  // Now ref count is 2, need to Decref twice
  re->Decref();
  re->Decref();
}

// Test ToString produces a valid string representation
TEST_F(RegexpTest_162, ToStringProducesValidString_162) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+b*", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test Dump produces a valid string
TEST_F(RegexpTest_162, DumpProducesValidString_162) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  std::string d = re->Dump();
  EXPECT_FALSE(d.empty());
  re->Decref();
}

// Test NumCaptures for pattern with no captures
TEST_F(RegexpTest_162, NumCapturesNoCaptures_162) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

// Test NumCaptures for pattern with captures
TEST_F(RegexpTest_162, NumCapturesWithCaptures_162) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// Test NumCaptures for nested captures
TEST_F(RegexpTest_162, NumCapturesNested_162) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((a)(b))", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// Test NamedCaptures returns nullptr when no named captures
TEST_F(RegexpTest_162, NamedCapturesNone_162) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  auto* names = re->NamedCaptures();
  EXPECT_EQ(names, nullptr);
  re->Decref();
}

// Test NamedCaptures returns map when named captures exist
TEST_F(RegexpTest_162, NamedCapturesWithNames_162) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<first>a)(?P<second>b)",
                             Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  auto* names = re->NamedCaptures();
  ASSERT_NE(names, nullptr);
  EXPECT_EQ(names->size(), 2u);
  EXPECT_EQ((*names)["first"], 1);
  EXPECT_EQ((*names)["second"], 2);
  delete names;
  re->Decref();
}

// Test CaptureNames returns map for named captures
TEST_F(RegexpTest_162, CaptureNamesWithNames_162) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<foo>a)(?P<bar>b)",
                             Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  auto* capture_names = re->CaptureNames();
  ASSERT_NE(capture_names, nullptr);
  EXPECT_EQ(capture_names->size(), 2u);
  EXPECT_EQ((*capture_names)[1], "foo");
  EXPECT_EQ((*capture_names)[2], "bar");
  delete capture_names;
  re->Decref();
}

// Test CaptureNames returns nullptr when no named captures
TEST_F(RegexpTest_162, CaptureNamesNone_162) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  auto* capture_names = re->CaptureNames();
  EXPECT_EQ(capture_names, nullptr);
  re->Decref();
}

// Test Simplify returns a valid regexp
TEST_F(RegexpTest_162, SimplifyReturnsValid_162) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,4}", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// Test SimplifyRegexp static function
TEST_F(RegexpTest_162, SimplifyRegexpStatic_162) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{2,4}", Regexp::NoParseFlags, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

// Test SimplifyRegexp with invalid pattern
TEST_F(RegexpTest_162, SimplifyRegexpInvalidPattern_162) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("[invalid", Regexp::NoParseFlags, &dst, &status);
  EXPECT_FALSE(ok);
}

// Test RequiredPrefix
TEST_F(RegexpTest_162, RequiredPrefixSimple_162) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc.*", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase;
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

// Test RequiredPrefix returns false for patterns without required prefix
TEST_F(RegexpTest_162, RequiredPrefixNoPrefix_162) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase;
  Regexp* suffix = nullptr;
  bool has_prefix = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  EXPECT_FALSE(has_prefix);
  re->Decref();
}

// Test op() accessor
TEST_F(RegexpTest_162, OpAccessor_162) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// Test parse_flags() accessor
TEST_F(RegexpTest_162, ParseFlagsAccessor_162) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::FoldCase);
  EXPECT_TRUE(re->parse_flags() & Regexp::FoldCase);
  re->Decref();
}

// Test CompileToProg returns a valid Prog
TEST_F(RegexpTest_162, CompileToProg_162) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileToReverseProg returns a valid Prog
TEST_F(RegexpTest_162, CompileToReverseProg_162) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test AlternateNoFactor
TEST_F(RegexpTest_162, AlternateNoFactor_162) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* re = Regexp::AlternateNoFactor(subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpAlternate);
  re->Decref();
}

// Test Parse with character class
TEST_F(RegexpTest_162, ParseCharacterClass_162) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCharClass);
  re->Decref();
}

// Test Parse with dot (any char)
TEST_F(RegexpTest_162, ParseAnyChar_162) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  // In non-dotall mode, . matches any char except newline, typically kRegexpAnyChar
  re->Decref();
}

// Test Parse with anchors
TEST_F(RegexpTest_162, ParseAnchors_162) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^$", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Parse complex pattern
TEST_F(RegexpTest_162, ParseComplexPattern_162) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a+|b*c)?\\d{2,5}", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test Parse with PerlX flags
TEST_F(RegexpTest_162, ParseWithPerlXFlags_162) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:abc)+", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test NullWalk doesn't crash
TEST_F(RegexpTest_162, NullWalkDoesNotCrash_162) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_NO_FATAL_FAILURE(re->NullWalk());
  re->Decref();
}

// Test sub() accessor for concat
TEST_F(RegexpTest_162, SubAccessor_162) {
  Regexp* subs[3];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  subs[2] = Regexp::NewLiteral('c', Regexp::NoParseFlags);
  Regexp* re = Regexp::Concat(subs, 3, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->nsub(), 3);
  Regexp** result_subs = re->sub();
  ASSERT_NE(result_subs, nullptr);
  for (int i = 0; i < 3; i++) {
    EXPECT_EQ(result_subs[i]->op(), kRegexpLiteral);
  }
  re->Decref();
}

// Test MimicsPCRE
TEST_F(RegexpTest_162, MimicsPCRE_162) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  // Just check it doesn't crash; the result depends on the pattern
  re->MimicsPCRE();
  re->Decref();
}

// Test ToString round-trip for simple patterns
TEST_F(RegexpTest_162, ToStringRoundTrip_162) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "abc");
  re->Decref();
}

// Test Repeat with min=0 max=0
TEST_F(RegexpTest_162, RepeatZeroZero_162) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 0, 0);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->min(), 0);
  EXPECT_EQ(re->max(), 0);
  re->Decref();
}

// Test HaveMatch with multiple different IDs
TEST_F(RegexpTest_162, HaveMatchMultipleIds_162) {
  for (int i = 0; i < 10; i++) {
    Regexp* re = Regexp::HaveMatch(i, Regexp::NoParseFlags);
    ASSERT_NE(re, nullptr);
    EXPECT_EQ(re->match_id(), i);
    re->Decref();
  }
}

// Test RequiredPrefixForAccel
TEST_F(RegexpTest_162, RequiredPrefixForAccel_162) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^hello.*", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase;
  re->RequiredPrefixForAccel(&prefix, &foldcase);
  re->Decref();
}

}  // namespace re2
