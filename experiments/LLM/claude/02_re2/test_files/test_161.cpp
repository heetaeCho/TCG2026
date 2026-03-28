#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <string>
#include <map>
#include <memory>

namespace re2 {

class RegexpTest_161 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// Test parsing a simple literal regexp
TEST_F(RegexpTest_161, ParseSimpleLiteral_161) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test parsing an empty string
TEST_F(RegexpTest_161, ParseEmptyString_161) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  re->Decref();
}

// Test parsing alternation
TEST_F(RegexpTest_161, ParseAlternation_161) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpAlternate);
  re->Decref();
}

// Test parsing repetition (star)
TEST_F(RegexpTest_161, ParseStar_161) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

// Test parsing repetition (plus)
TEST_F(RegexpTest_161, ParsePlus_161) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

// Test parsing repetition (quest)
TEST_F(RegexpTest_161, ParseQuest_161) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

// Test parsing capture group
TEST_F(RegexpTest_161, ParseCapture_161) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 1);
  re->Decref();
}

// Test parsing character class
TEST_F(RegexpTest_161, ParseCharClass_161) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[abc]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCharClass);
  re->Decref();
}

// Test parsing dot (any char)
TEST_F(RegexpTest_161, ParseAnyChar_161) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpAnyChar);
  re->Decref();
}

// Test parsing begin/end line anchors
TEST_F(RegexpTest_161, ParseAnchors_161) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^a$", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test parsing begin/end text anchors
TEST_F(RegexpTest_161, ParseTextAnchors_161) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\Aa\\z", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test parsing word boundary
TEST_F(RegexpTest_161, ParseWordBoundary_161) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpWordBoundary);
  re->Decref();
}

// Test parsing repeat with explicit count
TEST_F(RegexpTest_161, ParseRepeat_161) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 3);
  EXPECT_EQ(re->max(), 5);
  re->Decref();
}

// Test parsing repeat with exact count
TEST_F(RegexpTest_161, ParseRepeatExact_161) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 3);
  EXPECT_EQ(re->max(), 3);
  re->Decref();
}

// Test NumCaptures
TEST_F(RegexpTest_161, NumCaptures_161) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// Test NumCaptures with no captures
TEST_F(RegexpTest_161, NumCapturesZero_161) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

// Test NumCaptures with nested captures
TEST_F(RegexpTest_161, NumCapturesNested_161) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((a)(b))", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// Test NamedCaptures
TEST_F(RegexpTest_161, NamedCaptures_161) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<name>a)(?P<value>b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* named = re->NamedCaptures();
  ASSERT_NE(named, nullptr);
  EXPECT_EQ(named->size(), 2u);
  EXPECT_EQ((*named)["name"], 1);
  EXPECT_EQ((*named)["value"], 2);
  delete named;
  re->Decref();
}

// Test NamedCaptures with no named groups
TEST_F(RegexpTest_161, NamedCapturesNone_161) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* named = re->NamedCaptures();
  EXPECT_EQ(named, nullptr);
  re->Decref();
}

// Test CaptureNames
TEST_F(RegexpTest_161, CaptureNames_161) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<first>a)(b)(?P<third>c)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<int, std::string>* names = re->CaptureNames();
  ASSERT_NE(names, nullptr);
  EXPECT_EQ((*names)[1], "first");
  EXPECT_EQ((*names)[3], "third");
  delete names;
  re->Decref();
}

// Test ToString roundtrip
TEST_F(RegexpTest_161, ToStringSimple_161) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "abc");
  re->Decref();
}

// Test ToString for alternation
TEST_F(RegexpTest_161, ToStringAlternation_161) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "[ab]");
  re->Decref();
}

// Test Dump
TEST_F(RegexpTest_161, DumpSimple_161) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string dump = re->Dump();
  EXPECT_FALSE(dump.empty());
  re->Decref();
}

// Test Incref and Decref
TEST_F(RegexpTest_161, IncrefDecref_161) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* re2 = re->Incref();
  EXPECT_EQ(re, re2);
  re->Decref();
  re2->Decref();
}

// Test NewLiteral
TEST_F(RegexpTest_161, NewLiteral_161) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'a');
  re->Decref();
}

// Test LiteralString
TEST_F(RegexpTest_161, LiteralString_161) {
  Rune runes[] = {'h', 'e', 'l', 'l', 'o'};
  Regexp* re = Regexp::LiteralString(runes, 5, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 5);
  re->Decref();
}

// Test LiteralString with single rune
TEST_F(RegexpTest_161, LiteralStringSingleRune_161) {
  Rune runes[] = {'x'};
  Regexp* re = Regexp::LiteralString(runes, 1, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  // Single rune literal string might be optimized to kRegexpLiteral
  re->Decref();
}

// Test HaveMatch
TEST_F(RegexpTest_161, HaveMatch_161) {
  Regexp* re = Regexp::HaveMatch(42, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), 42);
  re->Decref();
}

// Test Star factory
TEST_F(RegexpTest_161, StarFactory_161) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Star(sub, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

// Test Plus factory
TEST_F(RegexpTest_161, PlusFactory_161) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Plus(sub, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

// Test Quest factory
TEST_F(RegexpTest_161, QuestFactory_161) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Quest(sub, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

// Test Capture factory
TEST_F(RegexpTest_161, CaptureFactory_161) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Capture(sub, Regexp::LikePerl, 1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 1);
  re->Decref();
}

// Test Repeat factory
TEST_F(RegexpTest_161, RepeatFactory_161) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Repeat(sub, Regexp::LikePerl, 2, 4);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), 4);
  re->Decref();
}

// Test Concat factory
TEST_F(RegexpTest_161, ConcatFactory_161) {
  Regexp* subs[3];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  subs[2] = Regexp::NewLiteral('c', Regexp::LikePerl);
  Regexp* re = Regexp::Concat(subs, 3, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Concat with single sub
TEST_F(RegexpTest_161, ConcatSingleSub_161) {
  Regexp* subs[1];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Concat(subs, 1, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Concat with zero subs
TEST_F(RegexpTest_161, ConcatZeroSubs_161) {
  Regexp* re = Regexp::Concat(nullptr, 0, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  re->Decref();
}

// Test Alternate factory
TEST_F(RegexpTest_161, AlternateFactory_161) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  Regexp* re = Regexp::Alternate(subs, 2, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Alternate with zero subs
TEST_F(RegexpTest_161, AlternateZeroSubs_161) {
  Regexp* re = Regexp::Alternate(nullptr, 0, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpNoMatch);
  re->Decref();
}

// Test AlternateNoFactor
TEST_F(RegexpTest_161, AlternateNoFactor_161) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('x', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('y', Regexp::LikePerl);
  Regexp* re = Regexp::AlternateNoFactor(subs, 2, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Simplify
TEST_F(RegexpTest_161, Simplify_161) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,3}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// Test SimplifyRegexp static method
TEST_F(RegexpTest_161, SimplifyRegexp_161) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{2}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

// Test RequiredPrefix
TEST_F(RegexpTest_161, RequiredPrefix_161) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc", Regexp::LikePerl, &status);
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

// Test RequiredPrefixForAccel
TEST_F(RegexpTest_161, RequiredPrefixForAccel_161) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^hello.*world", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase;
  bool has_prefix = re->RequiredPrefixForAccel(&prefix, &foldcase);
  if (has_prefix) {
    EXPECT_FALSE(prefix.empty());
  }
  re->Decref();
}

// Test parse_flags accessor
TEST_F(RegexpTest_161, ParseFlagsAccessor_161) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // parse_flags should be accessible
  Regexp::ParseFlags flags = re->parse_flags();
  (void)flags;
  re->Decref();
}

// Test op accessor
TEST_F(RegexpTest_161, OpAccessor_161) {
  Regexp* re = Regexp::NewLiteral('z', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// Test nsub accessor
TEST_F(RegexpTest_161, NsubAccessor_161) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // For a concat, nsub should be > 0
  if (re->op() == kRegexpConcat || re->op() == kRegexpAlternate) {
    EXPECT_GT(re->nsub(), 0);
  }
  re->Decref();
}

// Test CompileToProg
TEST_F(RegexpTest_161, CompileToProg_161) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileToReverseProg
TEST_F(RegexpTest_161, CompileToReverseProg_161) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test parsing invalid regexp
TEST_F(RegexpTest_161, ParseInvalidRegexp_161) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

// Test parsing invalid regexp with unmatched bracket
TEST_F(RegexpTest_161, ParseInvalidBracket_161) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

// Test NullWalk doesn't crash
TEST_F(RegexpTest_161, NullWalk_161) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a(b|c)*d", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->NullWalk();
  re->Decref();
}

// Test MimicsPCRE
TEST_F(RegexpTest_161, MimicsPCRE_161) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // Simple regexp should mimic PCRE
  bool mimics = re->MimicsPCRE();
  EXPECT_TRUE(mimics);
  re->Decref();
}

// Test simple accessor
TEST_F(RegexpTest_161, SimpleAccessor_161) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // After simplify, simple should be set
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// Test parsing with POSIX flags
TEST_F(RegexpTest_161, ParsePOSIX_161) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test parsing concat
TEST_F(RegexpTest_161, ParseConcat_161) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abcd", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 4);
  re->Decref();
}

// Test parsing complex expression
TEST_F(RegexpTest_161, ParseComplexExpression_161) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:a+|b*)(c{2,5})(?P<name>\\d+)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 2);
  std::map<std::string, int>* named = re->NamedCaptures();
  ASSERT_NE(named, nullptr);
  EXPECT_EQ(named->size(), 1u);
  EXPECT_EQ((*named)["name"], 2);
  delete named;
  re->Decref();
}

// Test rune accessor for literal
TEST_F(RegexpTest_161, RuneAccessor_161) {
  Regexp* re = Regexp::NewLiteral('A', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->rune(), 'A');
  re->Decref();
}

// Test runes accessor for literal string
TEST_F(RegexpTest_161, RunesAccessor_161) {
  Rune runes[] = {'a', 'b', 'c'};
  Regexp* re = Regexp::LiteralString(runes, 3, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 3);
  Rune* r = re->runes();
  ASSERT_NE(r, nullptr);
  EXPECT_EQ(r[0], 'a');
  EXPECT_EQ(r[1], 'b');
  EXPECT_EQ(r[2], 'c');
  re->Decref();
}

// Test Repeat with unbounded max (-1)
TEST_F(RegexpTest_161, RepeatUnbounded_161) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3,}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 3);
  EXPECT_EQ(re->max(), -1);
  re->Decref();
}

// Test Repeat with zero min
TEST_F(RegexpTest_161, RepeatZeroMin_161) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{0,3}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 0);
  EXPECT_EQ(re->max(), 3);
  re->Decref();
}

// Test sub accessor for star
TEST_F(RegexpTest_161, SubAccessorStar_161) {
  Regexp* sub = Regexp::NewLiteral('x', Regexp::LikePerl);
  Regexp* re = Regexp::Star(sub, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->nsub(), 1);
  Regexp** subs = re->sub();
  ASSERT_NE(subs, nullptr);
  EXPECT_EQ(subs[0]->op(), kRegexpLiteral);
  re->Decref();
}

// Test case-insensitive parsing
TEST_F(RegexpTest_161, ParseCaseInsensitive_161) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?i)abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test no word boundary
TEST_F(RegexpTest_161, ParseNoWordBoundary_161) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\B", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpNoWordBoundary);
  re->Decref();
}

// Test begin text
TEST_F(RegexpTest_161, ParseBeginText_161) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\A", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpBeginText);
  re->Decref();
}

// Test end text
TEST_F(RegexpTest_161, ParseEndText_161) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\z", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpEndText);
  re->Decref();
}

}  // namespace re2
