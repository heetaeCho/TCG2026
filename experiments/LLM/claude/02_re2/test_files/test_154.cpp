#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"

namespace re2 {

class RegexpTest_154 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// Test Parse with a simple literal pattern
TEST_F(RegexpTest_154, ParseSimpleLiteral_154) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test Parse with empty string
TEST_F(RegexpTest_154, ParseEmptyString_154) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  re->Decref();
}

// Test Parse with invalid regex
TEST_F(RegexpTest_154, ParseInvalidRegex_154) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

// Test NewLiteral creates a literal regexp
TEST_F(RegexpTest_154, NewLiteral_154) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'a');
  re->Decref();
}

// Test Plus creates a plus regexp
TEST_F(RegexpTest_154, PlusCreation_154) {
  Regexp* sub = Regexp::NewLiteral('x', Regexp::NoParseFlags);
  Regexp* re = Regexp::Plus(sub, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

// Test Star creates a star regexp
TEST_F(RegexpTest_154, StarCreation_154) {
  Regexp* sub = Regexp::NewLiteral('x', Regexp::NoParseFlags);
  Regexp* re = Regexp::Star(sub, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

// Test Quest creates a quest regexp
TEST_F(RegexpTest_154, QuestCreation_154) {
  Regexp* sub = Regexp::NewLiteral('x', Regexp::NoParseFlags);
  Regexp* re = Regexp::Quest(sub, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

// Test Repeat creates a repeat regexp with min and max
TEST_F(RegexpTest_154, RepeatCreation_154) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 2, 5);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), 5);
  re->Decref();
}

// Test Repeat with min == max
TEST_F(RegexpTest_154, RepeatMinEqualsMax_154) {
  Regexp* sub = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 3, 3);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 3);
  EXPECT_EQ(re->max(), 3);
  re->Decref();
}

// Test Repeat with min=0 and max=-1 (unbounded)
TEST_F(RegexpTest_154, RepeatUnbounded_154) {
  Regexp* sub = Regexp::NewLiteral('c', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 0, -1);
  ASSERT_NE(re, nullptr);
  // Unbounded repeat may be simplified to Star
  // But if it stays as Repeat:
  if (re->op() == kRegexpRepeat) {
    EXPECT_EQ(re->min(), 0);
    EXPECT_EQ(re->max(), -1);
  }
  re->Decref();
}

// Test Repeat with min=1 and max=-1 (unbounded)
TEST_F(RegexpTest_154, RepeatMinOneUnbounded_154) {
  Regexp* sub = Regexp::NewLiteral('d', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 1, -1);
  ASSERT_NE(re, nullptr);
  if (re->op() == kRegexpRepeat) {
    EXPECT_EQ(re->min(), 1);
    EXPECT_EQ(re->max(), -1);
  }
  re->Decref();
}

// Test Capture creates a capture regexp
TEST_F(RegexpTest_154, CaptureCreation_154) {
  Regexp* sub = Regexp::NewLiteral('z', Regexp::NoParseFlags);
  Regexp* re = Regexp::Capture(sub, Regexp::NoParseFlags, 1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 1);
  re->Decref();
}

// Test HaveMatch
TEST_F(RegexpTest_154, HaveMatch_154) {
  Regexp* re = Regexp::HaveMatch(42, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), 42);
  re->Decref();
}

// Test Concat with multiple subs
TEST_F(RegexpTest_154, ConcatCreation_154) {
  Regexp* subs[3];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  subs[2] = Regexp::NewLiteral('c', Regexp::NoParseFlags);
  Regexp* re = Regexp::Concat(subs, 3, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Alternate with multiple subs
TEST_F(RegexpTest_154, AlternateCreation_154) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('x', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('y', Regexp::NoParseFlags);
  Regexp* re = Regexp::Alternate(subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test LiteralString
TEST_F(RegexpTest_154, LiteralString_154) {
  Rune runes[] = {'h', 'e', 'l', 'l', 'o'};
  Regexp* re = Regexp::LiteralString(runes, 5, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 5);
  re->Decref();
}

// Test ToString roundtrip
TEST_F(RegexpTest_154, ToStringRoundtrip_154) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+b*c?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test Dump produces non-empty output
TEST_F(RegexpTest_154, DumpNonEmpty_154) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string d = re->Dump();
  EXPECT_FALSE(d.empty());
  re->Decref();
}

// Test NumCaptures
TEST_F(RegexpTest_154, NumCapturesNone_154) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

// Test NumCaptures with groups
TEST_F(RegexpTest_154, NumCapturesWithGroups_154) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// Test NumCaptures with nested groups
TEST_F(RegexpTest_154, NumCapturesNested_154) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((a)(b))", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// Test NamedCaptures returns null when no named captures
TEST_F(RegexpTest_154, NamedCapturesNone_154) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  auto* named = re->NamedCaptures();
  EXPECT_EQ(named, nullptr);
  delete named;
  re->Decref();
}

// Test NamedCaptures with named groups
TEST_F(RegexpTest_154, NamedCapturesPresent_154) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<first>a)(?P<second>b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  auto* named = re->NamedCaptures();
  ASSERT_NE(named, nullptr);
  EXPECT_EQ(named->size(), 2u);
  EXPECT_EQ((*named)["first"], 1);
  EXPECT_EQ((*named)["second"], 2);
  delete named;
  re->Decref();
}

// Test CaptureNames
TEST_F(RegexpTest_154, CaptureNames_154) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<foo>a)(b)(?P<bar>c)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  auto* names = re->CaptureNames();
  ASSERT_NE(names, nullptr);
  EXPECT_EQ((*names)[1], "foo");
  EXPECT_EQ((*names)[3], "bar");
  delete names;
  re->Decref();
}

// Test Simplify
TEST_F(RegexpTest_154, Simplify_154) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simple = re->Simplify();
  ASSERT_NE(simple, nullptr);
  simple->Decref();
  re->Decref();
}

// Test SimplifyRegexp static
TEST_F(RegexpTest_154, SimplifyRegexpStatic_154) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{2,4}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

// Test Incref and Decref
TEST_F(RegexpTest_154, IncrefDecref_154) {
  Regexp* re = Regexp::NewLiteral('q', Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  Regexp* re2 = re->Incref();
  EXPECT_EQ(re, re2);
  re->Decref();
  re->Decref();
}

// Test RequiredPrefix with anchored literal prefix
TEST_F(RegexpTest_154, RequiredPrefixAnchored_154) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc.*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;
  bool has = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  if (has) {
    EXPECT_FALSE(prefix.empty());
    ASSERT_NE(suffix, nullptr);
    suffix->Decref();
  }
  re->Decref();
}

// Test RequiredPrefix with non-anchored pattern
TEST_F(RegexpTest_154, RequiredPrefixNotAnchored_154) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc.*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;
  bool has = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  EXPECT_FALSE(has);
  re->Decref();
}

// Test op() accessor
TEST_F(RegexpTest_154, OpAccessor_154) {
  Regexp* re = Regexp::NewLiteral('m', Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// Test parse_flags accessor
TEST_F(RegexpTest_154, ParseFlagsAccessor_154) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // Just verify we can call parse_flags without crash
  Regexp::ParseFlags flags = re->parse_flags();
  (void)flags;
  re->Decref();
}

// Test Concat with single sub
TEST_F(RegexpTest_154, ConcatSingleSub_154) {
  Regexp* subs[1];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Concat(subs, 1, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  // Single sub concat should return the sub itself or a wrapper
  re->Decref();
}

// Test Alternate with single sub
TEST_F(RegexpTest_154, AlternateSingleSub_154) {
  Regexp* subs[1];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Alternate(subs, 1, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Concat with zero subs
TEST_F(RegexpTest_154, ConcatZeroSubs_154) {
  Regexp* re = Regexp::Concat(nullptr, 0, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  re->Decref();
}

// Test Alternate with zero subs
TEST_F(RegexpTest_154, AlternateZeroSubs_154) {
  Regexp* re = Regexp::Alternate(nullptr, 0, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpNoMatch);
  re->Decref();
}

// Test Parse complex pattern
TEST_F(RegexpTest_154, ParseComplexPattern_154) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]+\\d{2,4}(foo|bar)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->NumCaptures(), 1);
  re->Decref();
}

// Test Repeat boundary: min=0, max=0
TEST_F(RegexpTest_154, RepeatMinMaxZero_154) {
  Regexp* sub = Regexp::NewLiteral('e', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 0, 0);
  ASSERT_NE(re, nullptr);
  if (re->op() == kRegexpRepeat) {
    EXPECT_EQ(re->min(), 0);
    EXPECT_EQ(re->max(), 0);
  }
  re->Decref();
}

// Test Repeat parsed from string
TEST_F(RegexpTest_154, RepeatParsedFromString_154) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3,7}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  // The parsed regexp should be a repeat
  if (re->op() == kRegexpRepeat) {
    EXPECT_EQ(re->min(), 3);
    EXPECT_EQ(re->max(), 7);
  }
  re->Decref();
}

// Test CompileToProg
TEST_F(RegexpTest_154, CompileToProg_154) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileToReverseProg
TEST_F(RegexpTest_154, CompileToReverseProg_154) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test NullWalk doesn't crash
TEST_F(RegexpTest_154, NullWalkNoCrash_154) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a|b)*c+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->NullWalk();
  re->Decref();
}

// Test simple() accessor
TEST_F(RegexpTest_154, SimpleAccessor_154) {
  Regexp* re = Regexp::NewLiteral('t', Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  // Just call simple(), verify it doesn't crash
  bool s = re->simple();
  (void)s;
  re->Decref();
}

// Test AlternateNoFactor
TEST_F(RegexpTest_154, AlternateNoFactor_154) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('x', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('y', Regexp::NoParseFlags);
  Regexp* re = Regexp::AlternateNoFactor(subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpAlternate);
  re->Decref();
}

// Test nsub() for Concat
TEST_F(RegexpTest_154, NsubForConcat_154) {
  Regexp* subs[3];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  subs[2] = Regexp::NewLiteral('c', Regexp::NoParseFlags);
  Regexp* re = Regexp::Concat(subs, 3, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  if (re->op() == kRegexpConcat) {
    EXPECT_EQ(re->nsub(), 3);
  }
  re->Decref();
}

// Test sub() accessor for Concat
TEST_F(RegexpTest_154, SubAccessorForConcat_154) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('p', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('q', Regexp::NoParseFlags);
  Regexp* re = Regexp::Concat(subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  if (re->op() == kRegexpConcat) {
    EXPECT_EQ(re->nsub(), 2);
    Regexp** sub_array = re->sub();
    ASSERT_NE(sub_array, nullptr);
    EXPECT_EQ(sub_array[0]->op(), kRegexpLiteral);
    EXPECT_EQ(sub_array[1]->op(), kRegexpLiteral);
  }
  re->Decref();
}

// Test RequiredPrefixForAccel
TEST_F(RegexpTest_154, RequiredPrefixForAccel_154) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^hello.*world", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  bool has = re->RequiredPrefixForAccel(&prefix, &foldcase);
  if (has) {
    EXPECT_FALSE(prefix.empty());
  }
  re->Decref();
}

// Test Parse with POSIX flags
TEST_F(RegexpTest_154, ParsePosixFlags_154) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc|def", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test MimicsPCRE
TEST_F(RegexpTest_154, MimicsPCRE_154) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // Simple patterns should mimic PCRE
  bool mimics = re->MimicsPCRE();
  EXPECT_TRUE(mimics);
  re->Decref();
}

}  // namespace re2
