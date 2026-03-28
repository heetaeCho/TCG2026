#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"

namespace re2 {

class RegexpTest_159 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// Test Parse with a simple literal string
TEST_F(RegexpTest_159, ParseSimpleLiteral_159) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test Parse with empty string
TEST_F(RegexpTest_159, ParseEmptyString_159) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  re->Decref();
}

// Test Parse with invalid regex
TEST_F(RegexpTest_159, ParseInvalidRegex_159) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[invalid", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

// Test Parse with alternation
TEST_F(RegexpTest_159, ParseAlternation_159) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpAlternate);
  re->Decref();
}

// Test Parse with capture group
TEST_F(RegexpTest_159, ParseCapture_159) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 1);
  re->Decref();
}

// Test Parse with named capture group
TEST_F(RegexpTest_159, ParseNamedCapture_159) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<name>abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  ASSERT_NE(re->name(), nullptr);
  EXPECT_EQ(*re->name(), "name");
  re->Decref();
}

// Test Parse with star quantifier
TEST_F(RegexpTest_159, ParseStar_159) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

// Test Parse with plus quantifier
TEST_F(RegexpTest_159, ParsePlus_159) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

// Test Parse with quest quantifier
TEST_F(RegexpTest_159, ParseQuest_159) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

// Test Parse with character class
TEST_F(RegexpTest_159, ParseCharClass_159) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[abc]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCharClass);
  re->Decref();
}

// Test Parse with concatenation
TEST_F(RegexpTest_159, ParseConcat_159) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  re->Decref();
}

// Test Parse with repeat
TEST_F(RegexpTest_159, ParseRepeat_159) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), 5);
  re->Decref();
}

// Test Parse with anchors
TEST_F(RegexpTest_159, ParseBeginText_159) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\Aabc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Parse with dot (any char)
TEST_F(RegexpTest_159, ParseAnyChar_159) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpAnyChar);
  re->Decref();
}

// Test ToString round-trip
TEST_F(RegexpTest_159, ToStringRoundTrip_159) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a(b|c)d", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test NumCaptures
TEST_F(RegexpTest_159, NumCapturesNone_159) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

TEST_F(RegexpTest_159, NumCapturesMultiple_159) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// Test NamedCaptures
TEST_F(RegexpTest_159, NamedCapturesPresent_159) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<first>a)(?P<second>b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* named = re->NamedCaptures();
  ASSERT_NE(named, nullptr);
  EXPECT_EQ(named->size(), 2u);
  EXPECT_EQ((*named)["first"], 1);
  EXPECT_EQ((*named)["second"], 2);
  delete named;
  re->Decref();
}

TEST_F(RegexpTest_159, NamedCapturesNone_159) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* named = re->NamedCaptures();
  EXPECT_EQ(named, nullptr);
  re->Decref();
}

// Test CaptureNames
TEST_F(RegexpTest_159, CaptureNamesPresent_159) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<first>a)(?P<second>b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<int, std::string>* names = re->CaptureNames();
  ASSERT_NE(names, nullptr);
  EXPECT_EQ((*names)[1], "first");
  EXPECT_EQ((*names)[2], "second");
  delete names;
  re->Decref();
}

// Test Incref and Decref
TEST_F(RegexpTest_159, IncrefDecref_159) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* re2 = re->Incref();
  EXPECT_EQ(re, re2);
  re->Decref();
  re2->Decref();
}

// Test Simplify
TEST_F(RegexpTest_159, Simplify_159) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3,3}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// Test SimplifyRegexp static
TEST_F(RegexpTest_159, SimplifyRegexpStatic_159) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{2}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

// Test Dump
TEST_F(RegexpTest_159, Dump_159) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string dump = re->Dump();
  EXPECT_FALSE(dump.empty());
  re->Decref();
}

// Test NewLiteral
TEST_F(RegexpTest_159, NewLiteral_159) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'a');
  re->Decref();
}

// Test LiteralString
TEST_F(RegexpTest_159, LiteralString_159) {
  Rune runes[] = {'h', 'e', 'l', 'l', 'o'};
  Regexp* re = Regexp::LiteralString(runes, 5, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 5);
  re->Decref();
}

// Test HaveMatch
TEST_F(RegexpTest_159, HaveMatch_159) {
  Regexp* re = Regexp::HaveMatch(42, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), 42);
  re->Decref();
}

// Test Star static factory
TEST_F(RegexpTest_159, StarFactory_159) {
  Regexp* sub = Regexp::NewLiteral('x', Regexp::NoParseFlags);
  Regexp* re = Regexp::Star(sub, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

// Test Plus static factory
TEST_F(RegexpTest_159, PlusFactory_159) {
  Regexp* sub = Regexp::NewLiteral('x', Regexp::NoParseFlags);
  Regexp* re = Regexp::Plus(sub, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

// Test Quest static factory
TEST_F(RegexpTest_159, QuestFactory_159) {
  Regexp* sub = Regexp::NewLiteral('x', Regexp::NoParseFlags);
  Regexp* re = Regexp::Quest(sub, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

// Test Capture static factory
TEST_F(RegexpTest_159, CaptureFactory_159) {
  Regexp* sub = Regexp::NewLiteral('x', Regexp::NoParseFlags);
  Regexp* re = Regexp::Capture(sub, Regexp::NoParseFlags, 1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 1);
  re->Decref();
}

// Test Repeat static factory
TEST_F(RegexpTest_159, RepeatFactory_159) {
  Regexp* sub = Regexp::NewLiteral('x', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 2, 5);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), 5);
  re->Decref();
}

// Test Concat static factory
TEST_F(RegexpTest_159, ConcatFactory_159) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* re = Regexp::Concat(subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpConcat);
  EXPECT_EQ(re->nsub(), 2);
  re->Decref();
}

// Test Alternate static factory
TEST_F(RegexpTest_159, AlternateFactory_159) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* re = Regexp::Alternate(subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test AlternateNoFactor static factory
TEST_F(RegexpTest_159, AlternateNoFactorFactory_159) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* re = Regexp::AlternateNoFactor(subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpAlternate);
  re->Decref();
}

// Test RequiredPrefix
TEST_F(RegexpTest_159, RequiredPrefixTrue_159) {
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

TEST_F(RegexpTest_159, RequiredPrefixFalse_159) {
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

// Test op() accessor
TEST_F(RegexpTest_159, OpAccessor_159) {
  Regexp* re = Regexp::NewLiteral('z', Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// Test parse_flags() accessor
TEST_F(RegexpTest_159, ParseFlagsAccessor_159) {
  Regexp* re = Regexp::NewLiteral('z', Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->parse_flags(), Regexp::NoParseFlags);
  re->Decref();
}

// Test nsub() for leaf node
TEST_F(RegexpTest_159, NsubLeaf_159) {
  Regexp* re = Regexp::NewLiteral('z', Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->nsub(), 0);
  re->Decref();
}

// Test CompileToProg
TEST_F(RegexpTest_159, CompileToProg_159) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("ab+c", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileToReverseProg
TEST_F(RegexpTest_159, CompileToReverseProg_159) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("ab+c", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test NullWalk (just ensure it doesn't crash)
TEST_F(RegexpTest_159, NullWalk_159) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a|b)*c+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->NullWalk();
  re->Decref();
}

// Test Parse with word boundary
TEST_F(RegexpTest_159, ParseWordBoundary_159) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\bword\\b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Parse with complex regex
TEST_F(RegexpTest_159, ParseComplexRegex_159) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:a(?:b|c)*d)+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_GT(re->NumCaptures(), -1);
  re->Decref();
}

// Test single character literal string
TEST_F(RegexpTest_159, LiteralStringSingle_159) {
  Rune runes[] = {'z'};
  Regexp* re = Regexp::LiteralString(runes, 1, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  // Single rune literal string might be optimized to kRegexpLiteral
  re->Decref();
}

// Test Concat with single element
TEST_F(RegexpTest_159, ConcatSingleElement_159) {
  Regexp* subs[1];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Concat(subs, 1, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  // Single element concat should simplify to the element itself
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// Test Alternate with single element
TEST_F(RegexpTest_159, AlternateSingleElement_159) {
  Regexp* subs[1];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Alternate(subs, 1, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// Test Concat with zero elements
TEST_F(RegexpTest_159, ConcatZeroElements_159) {
  Regexp* re = Regexp::Concat(nullptr, 0, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  re->Decref();
}

// Test Alternate with zero elements
TEST_F(RegexpTest_159, AlternateZeroElements_159) {
  Regexp* re = Regexp::Alternate(nullptr, 0, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpNoMatch);
  re->Decref();
}

// Test Capture with name() returning nullptr for unnamed capture
TEST_F(RegexpTest_159, CaptureUnnamedHasNullName_159) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Capture(sub, Regexp::NoParseFlags, 1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->name(), nullptr);
  re->Decref();
}

// Test Parse with nested captures
TEST_F(RegexpTest_159, ParseNestedCaptures_159) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((a)(b(c)))", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 4);
  re->Decref();
}

// Test sub() accessor for concat
TEST_F(RegexpTest_159, SubAccessor_159) {
  Regexp* subs[3];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  subs[2] = Regexp::NewLiteral('c', Regexp::NoParseFlags);
  Regexp* re = Regexp::Concat(subs, 3, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpConcat);
  EXPECT_EQ(re->nsub(), 3);
  Regexp** result_subs = re->sub();
  ASSERT_NE(result_subs, nullptr);
  for (int i = 0; i < re->nsub(); i++) {
    EXPECT_NE(result_subs[i], nullptr);
  }
  re->Decref();
}

// Test Repeat with unbounded max (max = -1)
TEST_F(RegexpTest_159, RepeatUnbounded_159) {
  Regexp* sub = Regexp::NewLiteral('x', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 3, -1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 3);
  EXPECT_EQ(re->max(), -1);
  re->Decref();
}

// Test simple() accessor after Simplify
TEST_F(RegexpTest_159, SimpleAccessor_159) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* s = re->Simplify();
  ASSERT_NE(s, nullptr);
  // After Simplify, simple() should return true
  EXPECT_TRUE(s->simple());
  s->Decref();
  re->Decref();
}

// Test RequiredPrefixForAccel
TEST_F(RegexpTest_159, RequiredPrefixForAccel_159) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^foobar.*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  bool has = re->RequiredPrefixForAccel(&prefix, &foldcase);
  if (has) {
    EXPECT_FALSE(prefix.empty());
  }
  re->Decref();
}

// Test MimicsPCRE
TEST_F(RegexpTest_159, MimicsPCRE_159) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // Simple literal should mimic PCRE
  bool mimics = re->MimicsPCRE();
  EXPECT_TRUE(mimics);
  re->Decref();
}

// Test Parse with case-insensitive flag
TEST_F(RegexpTest_159, ParseCaseInsensitive_159) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?i)abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

}  // namespace re2
