#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"

namespace re2 {

class RegexpTest_158 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// Test Parse with a simple literal pattern
TEST_F(RegexpTest_158, ParseSimpleLiteral_158) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test Parse with empty string
TEST_F(RegexpTest_158, ParseEmptyString_158) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  re->Decref();
}

// Test Parse with invalid regex
TEST_F(RegexpTest_158, ParseInvalidRegex_158) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[z-a]", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

// Test cap() returns the capture index for a Capture regexp
TEST_F(RegexpTest_158, CaptureReturnsCapIndex_158) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  // The top-level should be a capture
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 1);
  re->Decref();
}

// Test multiple captures
TEST_F(RegexpTest_158, MultipleCaptureGroups_158) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// Test NumCaptures with no captures
TEST_F(RegexpTest_158, NumCapturesZero_158) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

// Test NewLiteral creates a literal regexp
TEST_F(RegexpTest_158, NewLiteral_158) {
  Regexp* re = Regexp::NewLiteral('A', Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'A');
  re->Decref();
}

// Test Star creates a star regexp
TEST_F(RegexpTest_158, StarCreation_158) {
  Regexp* lit = Regexp::NewLiteral('x', Regexp::NoParseFlags);
  Regexp* star = Regexp::Star(lit, Regexp::NoParseFlags);
  ASSERT_NE(star, nullptr);
  EXPECT_EQ(star->op(), kRegexpStar);
  star->Decref();
}

// Test Plus creates a plus regexp
TEST_F(RegexpTest_158, PlusCreation_158) {
  Regexp* lit = Regexp::NewLiteral('x', Regexp::NoParseFlags);
  Regexp* plus = Regexp::Plus(lit, Regexp::NoParseFlags);
  ASSERT_NE(plus, nullptr);
  EXPECT_EQ(plus->op(), kRegexpPlus);
  plus->Decref();
}

// Test Quest creates a quest regexp
TEST_F(RegexpTest_158, QuestCreation_158) {
  Regexp* lit = Regexp::NewLiteral('x', Regexp::NoParseFlags);
  Regexp* quest = Regexp::Quest(lit, Regexp::NoParseFlags);
  ASSERT_NE(quest, nullptr);
  EXPECT_EQ(quest->op(), kRegexpQuest);
  quest->Decref();
}

// Test Concat creates a concat regexp
TEST_F(RegexpTest_158, ConcatCreation_158) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* concat = Regexp::Concat(subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(concat, nullptr);
  EXPECT_EQ(concat->op(), kRegexpConcat);
  EXPECT_EQ(concat->nsub(), 2);
  concat->Decref();
}

// Test Alternate creates an alternate regexp
TEST_F(RegexpTest_158, AlternateCreation_158) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* alt = Regexp::Alternate(subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(alt, nullptr);
  // Could be kRegexpAlternate or kRegexpCharClass depending on factoring
  alt->Decref();
}

// Test Capture creates a capture regexp
TEST_F(RegexpTest_158, CaptureCreation_158) {
  Regexp* lit = Regexp::NewLiteral('x', Regexp::NoParseFlags);
  Regexp* cap = Regexp::Capture(lit, Regexp::NoParseFlags, 5);
  ASSERT_NE(cap, nullptr);
  EXPECT_EQ(cap->op(), kRegexpCapture);
  EXPECT_EQ(cap->cap(), 5);
  cap->Decref();
}

// Test HaveMatch creates a HaveMatch regexp
TEST_F(RegexpTest_158, HaveMatchCreation_158) {
  Regexp* re = Regexp::HaveMatch(42, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), 42);
  re->Decref();
}

// Test Repeat creates a repeat regexp
TEST_F(RegexpTest_158, RepeatCreation_158) {
  Regexp* lit = Regexp::NewLiteral('x', Regexp::NoParseFlags);
  Regexp* rep = Regexp::Repeat(lit, Regexp::NoParseFlags, 2, 5);
  ASSERT_NE(rep, nullptr);
  EXPECT_EQ(rep->op(), kRegexpRepeat);
  EXPECT_EQ(rep->min(), 2);
  EXPECT_EQ(rep->max(), 5);
  rep->Decref();
}

// Test LiteralString creates a literal string regexp
TEST_F(RegexpTest_158, LiteralStringCreation_158) {
  Rune runes[] = {'h', 'e', 'l', 'l', 'o'};
  Regexp* re = Regexp::LiteralString(runes, 5, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 5);
  re->Decref();
}

// Test ToString round trip
TEST_F(RegexpTest_158, ToStringRoundTrip_158) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+b*c?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test Dump produces output
TEST_F(RegexpTest_158, DumpProducesOutput_158) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string dump = re->Dump();
  EXPECT_FALSE(dump.empty());
  re->Decref();
}

// Test Incref and Decref
TEST_F(RegexpTest_158, IncrefDecref_158) {
  Regexp* re = Regexp::NewLiteral('z', Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  Regexp* re2 = re->Incref();
  EXPECT_EQ(re, re2);
  re->Decref();
  re->Decref();
}

// Test Simplify
TEST_F(RegexpTest_158, Simplify_158) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a|b)+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simple = re->Simplify();
  ASSERT_NE(simple, nullptr);
  simple->Decref();
  re->Decref();
}

// Test SimplifyRegexp static method
TEST_F(RegexpTest_158, SimplifyRegexpStatic_158) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{2,4}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

// Test NamedCaptures with named groups
TEST_F(RegexpTest_158, NamedCaptures_158) {
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

// Test NamedCaptures returns null when no named captures
TEST_F(RegexpTest_158, NamedCapturesNull_158) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* named = re->NamedCaptures();
  EXPECT_EQ(named, nullptr);
  re->Decref();
}

// Test CaptureNames
TEST_F(RegexpTest_158, CaptureNames_158) {
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

// Test RequiredPrefix
TEST_F(RegexpTest_158, RequiredPrefix_158) {
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

// Test CompileToProg
TEST_F(RegexpTest_158, CompileToProg_158) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileToReverseProg
TEST_F(RegexpTest_158, CompileToReverseProg_158) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test parse_flags
TEST_F(RegexpTest_158, ParseFlags_158) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::FoldCase);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->parse_flags() & Regexp::FoldCase);
  re->Decref();
}

// Test op accessor
TEST_F(RegexpTest_158, OpAccessor_158) {
  Regexp* re = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// Test Concat with single element
TEST_F(RegexpTest_158, ConcatSingleElement_158) {
  Regexp* subs[1];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* concat = Regexp::Concat(subs, 1, Regexp::NoParseFlags);
  ASSERT_NE(concat, nullptr);
  // Single element concat should just return the element itself
  EXPECT_EQ(concat->op(), kRegexpLiteral);
  concat->Decref();
}

// Test Concat with zero elements
TEST_F(RegexpTest_158, ConcatZeroElements_158) {
  Regexp* concat = Regexp::Concat(nullptr, 0, Regexp::NoParseFlags);
  ASSERT_NE(concat, nullptr);
  EXPECT_EQ(concat->op(), kRegexpEmptyMatch);
  concat->Decref();
}

// Test Alternate with zero elements
TEST_F(RegexpTest_158, AlternateZeroElements_158) {
  Regexp* alt = Regexp::Alternate(nullptr, 0, Regexp::NoParseFlags);
  ASSERT_NE(alt, nullptr);
  EXPECT_EQ(alt->op(), kRegexpNoMatch);
  alt->Decref();
}

// Test Alternate with single element
TEST_F(RegexpTest_158, AlternateSingleElement_158) {
  Regexp* subs[1];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* alt = Regexp::Alternate(subs, 1, Regexp::NoParseFlags);
  ASSERT_NE(alt, nullptr);
  EXPECT_EQ(alt->op(), kRegexpLiteral);
  alt->Decref();
}

// Test NullWalk does not crash
TEST_F(RegexpTest_158, NullWalkDoesNotCrash_158) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a(b|c)d+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_NO_FATAL_FAILURE(re->NullWalk());
  re->Decref();
}

// Test parsing character class
TEST_F(RegexpTest_158, ParseCharClass_158) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->op(), kRegexpCharClass);
  re->Decref();
}

// Test parsing anchors
TEST_F(RegexpTest_158, ParseAnchors_158) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc$", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test parsing dot (any char)
TEST_F(RegexpTest_158, ParseDot_158) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test Capture with name
TEST_F(RegexpTest_158, CaptureWithName_158) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<test>abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 1);
  const std::string* name = re->name();
  ASSERT_NE(name, nullptr);
  EXPECT_EQ(*name, "test");
  re->Decref();
}

// Test Repeat with unbounded max (e.g., a{3,})
TEST_F(RegexpTest_158, RepeatUnboundedMax_158) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3,}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test Repeat exact count (e.g., a{5})
TEST_F(RegexpTest_158, RepeatExactCount_158) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test complex regex parse
TEST_F(RegexpTest_158, ParseComplexRegex_158) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a+|b*)?[c-f]{2,4}\\d+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test parse unmatched parenthesis
TEST_F(RegexpTest_158, ParseUnmatchedParen_158) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

// Test AlternateNoFactor
TEST_F(RegexpTest_158, AlternateNoFactor_158) {
  Regexp* subs[3];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  subs[2] = Regexp::NewLiteral('c', Regexp::NoParseFlags);
  Regexp* alt = Regexp::AlternateNoFactor(subs, 3, Regexp::NoParseFlags);
  ASSERT_NE(alt, nullptr);
  EXPECT_EQ(alt->op(), kRegexpAlternate);
  alt->Decref();
}

// Test sub accessor for concat
TEST_F(RegexpTest_158, SubAccessor_158) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* concat = Regexp::Concat(subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(concat, nullptr);
  EXPECT_EQ(concat->nsub(), 2);
  Regexp** sub_arr = concat->sub();
  ASSERT_NE(sub_arr, nullptr);
  EXPECT_EQ(sub_arr[0]->op(), kRegexpLiteral);
  EXPECT_EQ(sub_arr[1]->op(), kRegexpLiteral);
  concat->Decref();
}

// Test MimicsPCRE
TEST_F(RegexpTest_158, MimicsPCRE_158) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // Just verify it doesn't crash, result depends on pattern
  (void)re->MimicsPCRE();
  re->Decref();
}

// Test RequiredPrefixForAccel
TEST_F(RegexpTest_158, RequiredPrefixForAccel_158) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^hello", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  (void)re->RequiredPrefixForAccel(&prefix, &foldcase);
  re->Decref();
}

}  // namespace re2
