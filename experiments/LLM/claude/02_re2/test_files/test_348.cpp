#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <string>
#include <map>

namespace re2 {

// Helper to create a simple parsed Regexp
static Regexp* ParseOrDie(const char* pattern) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
  EXPECT_TRUE(re != nullptr) << "Failed to parse: " << pattern
                              << " error: " << status.Text();
  return re;
}

class RegexpTest_348 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Cleanup is handled by Decref in individual tests
  }
};

// Test NewCharClass creates a regexp with kRegexpCharClass op
TEST_F(RegexpTest_348, NewCharClassCreatesCharClassRegexp_348) {
  // Parse a character class pattern to get a CharClass
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  // Verify it parsed correctly - character classes result in kRegexpCharClass
  EXPECT_EQ(re->op(), kRegexpCharClass);
  
  // Get the char class
  CharClass* cc = re->cc();
  EXPECT_NE(cc, nullptr);
  
  re->Decref();
}

// Test basic Parse functionality
TEST_F(RegexpTest_348, ParseSimpleLiteral_348) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  re->Decref();
}

// Test Parse with empty pattern
TEST_F(RegexpTest_348, ParseEmptyPattern_348) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  re->Decref();
}

// Test Parse single character literal
TEST_F(RegexpTest_348, ParseSingleLiteral_348) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'a');
  re->Decref();
}

// Test Parse invalid pattern returns null
TEST_F(RegexpTest_348, ParseInvalidPattern_348) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
}

// Test Parse alternation
TEST_F(RegexpTest_348, ParseAlternation_348) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // Could be kRegexpCharClass due to optimization, or kRegexpAlternate
  re->Decref();
}

// Test Parse concatenation
TEST_F(RegexpTest_348, ParseConcat_348) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("ab", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Star factory
TEST_F(RegexpTest_348, StarCreatesStarOp_348) {
  Regexp* sub = ParseOrDie("a");
  ASSERT_NE(sub, nullptr);
  Regexp* star = Regexp::Star(sub, Regexp::LikePerl);
  ASSERT_NE(star, nullptr);
  EXPECT_EQ(star->op(), kRegexpStar);
  star->Decref();
}

// Test Plus factory
TEST_F(RegexpTest_348, PlusCreatesPlusOp_348) {
  Regexp* sub = ParseOrDie("a");
  ASSERT_NE(sub, nullptr);
  Regexp* plus = Regexp::Plus(sub, Regexp::LikePerl);
  ASSERT_NE(plus, nullptr);
  EXPECT_EQ(plus->op(), kRegexpPlus);
  plus->Decref();
}

// Test Quest factory
TEST_F(RegexpTest_348, QuestCreatesQuestOp_348) {
  Regexp* sub = ParseOrDie("a");
  ASSERT_NE(sub, nullptr);
  Regexp* quest = Regexp::Quest(sub, Regexp::LikePerl);
  ASSERT_NE(quest, nullptr);
  EXPECT_EQ(quest->op(), kRegexpQuest);
  quest->Decref();
}

// Test NewLiteral factory
TEST_F(RegexpTest_348, NewLiteralCreatesLiteralOp_348) {
  Regexp* re = Regexp::NewLiteral('x', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'x');
  re->Decref();
}

// Test NewLiteral with unicode character
TEST_F(RegexpTest_348, NewLiteralUnicode_348) {
  Regexp* re = Regexp::NewLiteral(0x4e2d, Regexp::LikePerl);  // Chinese character
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 0x4e2d);
  re->Decref();
}

// Test HaveMatch factory
TEST_F(RegexpTest_348, HaveMatchCreatesHaveMatchOp_348) {
  Regexp* re = Regexp::HaveMatch(42, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), 42);
  re->Decref();
}

// Test Capture factory
TEST_F(RegexpTest_348, CaptureCreatesCaptureOp_348) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* cap = Regexp::Capture(sub, Regexp::LikePerl, 1);
  ASSERT_NE(cap, nullptr);
  EXPECT_EQ(cap->op(), kRegexpCapture);
  EXPECT_EQ(cap->cap(), 1);
  cap->Decref();
}

// Test Repeat factory
TEST_F(RegexpTest_348, RepeatCreatesRepeatOp_348) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* rep = Regexp::Repeat(sub, Regexp::LikePerl, 2, 5);
  ASSERT_NE(rep, nullptr);
  EXPECT_EQ(rep->op(), kRegexpRepeat);
  EXPECT_EQ(rep->min(), 2);
  EXPECT_EQ(rep->max(), 5);
  rep->Decref();
}

// Test Concat factory
TEST_F(RegexpTest_348, ConcatCreatesConcatOp_348) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  Regexp* concat = Regexp::Concat(subs, 2, Regexp::LikePerl);
  ASSERT_NE(concat, nullptr);
  EXPECT_EQ(concat->op(), kRegexpConcat);
  EXPECT_EQ(concat->nsub(), 2);
  concat->Decref();
}

// Test Concat with single sub
TEST_F(RegexpTest_348, ConcatSingleSub_348) {
  Regexp* subs[1];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* concat = Regexp::Concat(subs, 1, Regexp::LikePerl);
  ASSERT_NE(concat, nullptr);
  // Single sub concat may be optimized to just return the sub
  EXPECT_EQ(concat->op(), kRegexpLiteral);
  concat->Decref();
}

// Test Concat with zero subs
TEST_F(RegexpTest_348, ConcatZeroSubs_348) {
  Regexp* concat = Regexp::Concat(nullptr, 0, Regexp::LikePerl);
  ASSERT_NE(concat, nullptr);
  EXPECT_EQ(concat->op(), kRegexpEmptyMatch);
  concat->Decref();
}

// Test Alternate factory
TEST_F(RegexpTest_348, AlternateCreatesAlternateOp_348) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  Regexp* alt = Regexp::Alternate(subs, 2, Regexp::LikePerl);
  ASSERT_NE(alt, nullptr);
  // May be optimized to a char class
  alt->Decref();
}

// Test Alternate with single sub
TEST_F(RegexpTest_348, AlternateSingleSub_348) {
  Regexp* subs[1];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* alt = Regexp::Alternate(subs, 1, Regexp::LikePerl);
  ASSERT_NE(alt, nullptr);
  EXPECT_EQ(alt->op(), kRegexpLiteral);
  alt->Decref();
}

// Test Alternate with zero subs
TEST_F(RegexpTest_348, AlternateZeroSubs_348) {
  Regexp* alt = Regexp::Alternate(nullptr, 0, Regexp::LikePerl);
  ASSERT_NE(alt, nullptr);
  EXPECT_EQ(alt->op(), kRegexpNoMatch);
  alt->Decref();
}

// Test Incref/Decref reference counting
TEST_F(RegexpTest_348, IncrefDecrefRefCount_348) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->Ref(), 1);
  
  Regexp* re2 = re->Incref();
  EXPECT_EQ(re, re2);
  EXPECT_EQ(re->Ref(), 2);
  
  re->Decref();
  EXPECT_EQ(re2->Ref(), 1);
  
  re2->Decref();
}

// Test ToString
TEST_F(RegexpTest_348, ToStringSimple_348) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "abc");
  re->Decref();
}

// Test ToString of complex pattern
TEST_F(RegexpTest_348, ToStringComplex_348) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a(b|c)*d", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test NumCaptures
TEST_F(RegexpTest_348, NumCapturesNoCaptures_348) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

// Test NumCaptures with captures
TEST_F(RegexpTest_348, NumCapturesWithCaptures_348) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// Test NumCaptures with nested captures
TEST_F(RegexpTest_348, NumCapturesNested_348) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((a)(b))", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// Test LiteralString factory
TEST_F(RegexpTest_348, LiteralStringCreatesLiteralStringOp_348) {
  Rune runes[] = {'h', 'e', 'l', 'l', 'o'};
  Regexp* re = Regexp::LiteralString(runes, 5, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 5);
  re->Decref();
}

// Test parse_flags accessor
TEST_F(RegexpTest_348, ParseFlagsAccessor_348) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->parse_flags(), Regexp::LikePerl);
  re->Decref();
}

// Test Simplify
TEST_F(RegexpTest_348, SimplifyDoesNotReturnNull_348) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// Test SimplifyRegexp static
TEST_F(RegexpTest_348, SimplifyRegexpStatic_348) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{2,5}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

// Test Dump
TEST_F(RegexpTest_348, DumpProducesNonEmptyString_348) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+b*c?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string dump = re->Dump();
  EXPECT_FALSE(dump.empty());
  re->Decref();
}

// Test CharClass Contains
TEST_F(RegexpTest_348, CharClassContains_348) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  ASSERT_EQ(re->op(), kRegexpCharClass);
  
  CharClass* cc = re->cc();
  ASSERT_NE(cc, nullptr);
  
  EXPECT_TRUE(cc->Contains('a'));
  EXPECT_TRUE(cc->Contains('m'));
  EXPECT_TRUE(cc->Contains('z'));
  EXPECT_FALSE(cc->Contains('A'));
  EXPECT_FALSE(cc->Contains('0'));
  
  re->Decref();
}

// Test CharClass size
TEST_F(RegexpTest_348, CharClassSize_348) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  ASSERT_EQ(re->op(), kRegexpCharClass);
  
  CharClass* cc = re->cc();
  ASSERT_NE(cc, nullptr);
  EXPECT_EQ(cc->size(), 26);
  
  re->Decref();
}

// Test CharClass empty
TEST_F(RegexpTest_348, CharClassNotEmpty_348) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  ASSERT_EQ(re->op(), kRegexpCharClass);
  
  CharClass* cc = re->cc();
  ASSERT_NE(cc, nullptr);
  EXPECT_FALSE(cc->empty());
  
  re->Decref();
}

// Test Parse with dot (any char)
TEST_F(RegexpTest_348, ParseDotAnyChar_348) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // In Perl mode, dot doesn't match newline, so it's a char class
  re->Decref();
}

// Test Parse anchors
TEST_F(RegexpTest_348, ParseAnchors_348) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc$", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test NamedCaptures with no named captures
TEST_F(RegexpTest_348, NamedCapturesNone_348) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* named = re->NamedCaptures();
  EXPECT_EQ(named, nullptr);
  delete named;
  re->Decref();
}

// Test NamedCaptures with named captures
TEST_F(RegexpTest_348, NamedCapturesPresent_348) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<foo>a)(?P<bar>b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* named = re->NamedCaptures();
  ASSERT_NE(named, nullptr);
  EXPECT_EQ(named->size(), 2u);
  EXPECT_EQ((*named)["foo"], 1);
  EXPECT_EQ((*named)["bar"], 2);
  delete named;
  re->Decref();
}

// Test CaptureNames
TEST_F(RegexpTest_348, CaptureNamesPresent_348) {
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
TEST_F(RegexpTest_348, RequiredPrefixSimple_348) {
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

// Test Repeat with min == max
TEST_F(RegexpTest_348, RepeatExact_348) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* rep = Regexp::Repeat(sub, Regexp::LikePerl, 3, 3);
  ASSERT_NE(rep, nullptr);
  EXPECT_EQ(rep->op(), kRegexpRepeat);
  EXPECT_EQ(rep->min(), 3);
  EXPECT_EQ(rep->max(), 3);
  rep->Decref();
}

// Test Repeat with -1 max (unbounded)
TEST_F(RegexpTest_348, RepeatUnbounded_348) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* rep = Regexp::Repeat(sub, Regexp::LikePerl, 2, -1);
  ASSERT_NE(rep, nullptr);
  EXPECT_EQ(rep->op(), kRegexpRepeat);
  EXPECT_EQ(rep->min(), 2);
  EXPECT_EQ(rep->max(), -1);
  rep->Decref();
}

// Test AlternateNoFactor
TEST_F(RegexpTest_348, AlternateNoFactorBasic_348) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  Regexp* alt = Regexp::AlternateNoFactor(subs, 2, Regexp::LikePerl);
  ASSERT_NE(alt, nullptr);
  alt->Decref();
}

// Test op() accessor
TEST_F(RegexpTest_348, OpAccessor_348) {
  Regexp* re = Regexp::NewLiteral('z', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// Test nsub() accessor on concat
TEST_F(RegexpTest_348, NsubAccessor_348) {
  Regexp* subs[3];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  subs[2] = Regexp::NewLiteral('c', Regexp::LikePerl);
  Regexp* concat = Regexp::Concat(subs, 3, Regexp::LikePerl);
  ASSERT_NE(concat, nullptr);
  EXPECT_EQ(concat->nsub(), 3);
  concat->Decref();
}

// Test sub() accessor
TEST_F(RegexpTest_348, SubAccessor_348) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('x', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('y', Regexp::LikePerl);
  Regexp* concat = Regexp::Concat(subs, 2, Regexp::LikePerl);
  ASSERT_NE(concat, nullptr);
  ASSERT_EQ(concat->nsub(), 2);
  Regexp** sub_arr = concat->sub();
  ASSERT_NE(sub_arr, nullptr);
  EXPECT_EQ(sub_arr[0]->op(), kRegexpLiteral);
  EXPECT_EQ(sub_arr[1]->op(), kRegexpLiteral);
  concat->Decref();
}

// Test Parse with unmatched parenthesis
TEST_F(RegexpTest_348, ParseUnmatchedParen_348) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
}

// Test Parse with bad escape
TEST_F(RegexpTest_348, ParseBadEscape_348) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
}

// Test CharClass iteration (begin/end)
TEST_F(RegexpTest_348, CharClassIteration_348) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[abc]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  ASSERT_EQ(re->op(), kRegexpCharClass);
  
  CharClass* cc = re->cc();
  ASSERT_NE(cc, nullptr);
  
  int count = 0;
  for (auto it = cc->begin(); it != cc->end(); ++it) {
    count++;
  }
  EXPECT_GT(count, 0);
  
  re->Decref();
}

// Test CompileToProg returns non-null for valid regexp
TEST_F(RegexpTest_348, CompileToProg_348) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileToReverseProg returns non-null for valid regexp
TEST_F(RegexpTest_348, CompileToReverseProg_348) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

}  // namespace re2
