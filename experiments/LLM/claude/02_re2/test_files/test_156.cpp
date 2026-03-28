#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <string>
#include <map>
#include <memory>

namespace re2 {

class RegexpTest_156 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// Test parsing a simple literal
TEST_F(RegexpTest_156, ParseSimpleLiteral_156) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'a');
  re->Decref();
}

// Test parsing an empty pattern gives empty match
TEST_F(RegexpTest_156, ParseEmptyPattern_156) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  re->Decref();
}

// Test parsing a concatenation
TEST_F(RegexpTest_156, ParseConcatenation_156) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("ab", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpConcat);
  EXPECT_EQ(re->nsub(), 2);
  re->Decref();
}

// Test parsing an alternation
TEST_F(RegexpTest_156, ParseAlternation_156) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpAlternate);
  re->Decref();
}

// Test parsing a star
TEST_F(RegexpTest_156, ParseStar_156) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

// Test parsing a plus
TEST_F(RegexpTest_156, ParsePlus_156) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

// Test parsing a quest
TEST_F(RegexpTest_156, ParseQuest_156) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

// Test parsing a capture group
TEST_F(RegexpTest_156, ParseCapture_156) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 1);
  re->Decref();
}

// Test parsing a repeat
TEST_F(RegexpTest_156, ParseRepeat_156) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), 5);
  re->Decref();
}

// Test parsing a character class
TEST_F(RegexpTest_156, ParseCharClass_156) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[abc]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCharClass);
  EXPECT_NE(re->cc(), nullptr);
  re->Decref();
}

// Test parsing dot (any char)
TEST_F(RegexpTest_156, ParseAnyChar_156) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // Depending on flags, this could be kRegexpAnyChar or kRegexpCharClass
  // With LikePerl, dot doesn't match newline, so it could be a char class
  // Just check it parsed successfully
  re->Decref();
}

// Test parsing begin/end anchors
TEST_F(RegexpTest_156, ParseAnchors_156) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^a$", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test parsing word boundary
TEST_F(RegexpTest_156, ParseWordBoundary_156) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpWordBoundary);
  re->Decref();
}

// Test ToString roundtrip
TEST_F(RegexpTest_156, ToStringRoundTrip_156) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+b*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test Dump
TEST_F(RegexpTest_156, Dump_156) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string dump = re->Dump();
  EXPECT_FALSE(dump.empty());
  re->Decref();
}

// Test NumCaptures
TEST_F(RegexpTest_156, NumCaptures_156) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// Test NumCaptures with no captures
TEST_F(RegexpTest_156, NumCapturesZero_156) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

// Test NamedCaptures
TEST_F(RegexpTest_156, NamedCaptures_156) {
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

// Test NamedCaptures returns null when no named captures
TEST_F(RegexpTest_156, NamedCapturesNull_156) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* named = re->NamedCaptures();
  EXPECT_EQ(named, nullptr);
  re->Decref();
}

// Test CaptureNames
TEST_F(RegexpTest_156, CaptureNames_156) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<foo>a)(b)(?P<bar>c)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<int, std::string>* capture_names = re->CaptureNames();
  ASSERT_NE(capture_names, nullptr);
  EXPECT_EQ((*capture_names)[1], "foo");
  EXPECT_EQ((*capture_names)[3], "bar");
  delete capture_names;
  re->Decref();
}

// Test Incref and Decref
TEST_F(RegexpTest_156, IncrefDecref_156) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* re2 = re->Incref();
  EXPECT_EQ(re, re2);
  re->Decref();
  re->Decref();
}

// Test NewLiteral factory method
TEST_F(RegexpTest_156, NewLiteral_156) {
  Regexp* re = Regexp::NewLiteral('x', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'x');
  re->Decref();
}

// Test HaveMatch factory method
TEST_F(RegexpTest_156, HaveMatch_156) {
  Regexp* re = Regexp::HaveMatch(42, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), 42);
  re->Decref();
}

// Test Star factory method
TEST_F(RegexpTest_156, StarFactory_156) {
  Regexp* lit = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* star = Regexp::Star(lit, Regexp::LikePerl);
  ASSERT_NE(star, nullptr);
  EXPECT_EQ(star->op(), kRegexpStar);
  star->Decref();
}

// Test Plus factory method
TEST_F(RegexpTest_156, PlusFactory_156) {
  Regexp* lit = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* plus = Regexp::Plus(lit, Regexp::LikePerl);
  ASSERT_NE(plus, nullptr);
  EXPECT_EQ(plus->op(), kRegexpPlus);
  plus->Decref();
}

// Test Quest factory method
TEST_F(RegexpTest_156, QuestFactory_156) {
  Regexp* lit = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* quest = Regexp::Quest(lit, Regexp::LikePerl);
  ASSERT_NE(quest, nullptr);
  EXPECT_EQ(quest->op(), kRegexpQuest);
  quest->Decref();
}

// Test Concat factory method
TEST_F(RegexpTest_156, ConcatFactory_156) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  Regexp* concat = Regexp::Concat(subs, 2, Regexp::LikePerl);
  ASSERT_NE(concat, nullptr);
  EXPECT_EQ(concat->op(), kRegexpConcat);
  EXPECT_EQ(concat->nsub(), 2);
  concat->Decref();
}

// Test Alternate factory method
TEST_F(RegexpTest_156, AlternateFactory_156) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  Regexp* alt = Regexp::Alternate(subs, 2, Regexp::LikePerl);
  ASSERT_NE(alt, nullptr);
  // Could be optimized to a char class, so just check it's valid
  alt->Decref();
}

// Test Capture factory method
TEST_F(RegexpTest_156, CaptureFactory_156) {
  Regexp* lit = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* cap = Regexp::Capture(lit, Regexp::LikePerl, 1);
  ASSERT_NE(cap, nullptr);
  EXPECT_EQ(cap->op(), kRegexpCapture);
  EXPECT_EQ(cap->cap(), 1);
  cap->Decref();
}

// Test Repeat factory method
TEST_F(RegexpTest_156, RepeatFactory_156) {
  Regexp* lit = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* rep = Regexp::Repeat(lit, Regexp::LikePerl, 3, 7);
  ASSERT_NE(rep, nullptr);
  EXPECT_EQ(rep->op(), kRegexpRepeat);
  EXPECT_EQ(rep->min(), 3);
  EXPECT_EQ(rep->max(), 7);
  rep->Decref();
}

// Test LiteralString factory method
TEST_F(RegexpTest_156, LiteralStringFactory_156) {
  Rune runes[] = {'h', 'e', 'l', 'l', 'o'};
  Regexp* re = Regexp::LiteralString(runes, 5, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 5);
  re->Decref();
}

// Test Simplify
TEST_F(RegexpTest_156, Simplify_156) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// Test SimplifyRegexp static method
TEST_F(RegexpTest_156, SimplifyRegexp_156) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{2}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

// Test CompileToProg
TEST_F(RegexpTest_156, CompileToProg_156) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileToReverseProg
TEST_F(RegexpTest_156, CompileToReverseProg_156) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test RequiredPrefix
TEST_F(RegexpTest_156, RequiredPrefix_156) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase;
  Regexp* suffix = nullptr;
  bool has_prefix = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  if (has_prefix) {
    EXPECT_FALSE(prefix.empty());
    if (suffix != nullptr)
      suffix->Decref();
  }
  re->Decref();
}

// Test RequiredPrefixForAccel
TEST_F(RegexpTest_156, RequiredPrefixForAccel_156) {
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
TEST_F(RegexpTest_156, ParseFlags_156) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // parse_flags should at least contain LikePerl flags
  Regexp::ParseFlags flags = re->parse_flags();
  // Just check it doesn't crash and returns something
  (void)flags;
  re->Decref();
}

// Test sub accessor for concat
TEST_F(RegexpTest_156, SubAccessor_156) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  if (re->op() == kRegexpConcat) {
    EXPECT_GT(re->nsub(), 0);
    Regexp** subs = re->sub();
    EXPECT_NE(subs, nullptr);
    for (int i = 0; i < re->nsub(); i++) {
      EXPECT_NE(subs[i], nullptr);
    }
  }
  re->Decref();
}

// Test NullWalk doesn't crash
TEST_F(RegexpTest_156, NullWalk_156) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a+|b*)+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->NullWalk();
  re->Decref();
}

// Test MimicsPCRE
TEST_F(RegexpTest_156, MimicsPCRE_156) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // Simple patterns should mimic PCRE
  bool mimics = re->MimicsPCRE();
  EXPECT_TRUE(mimics);
  re->Decref();
}

// Test Concat with zero subs gives empty match
TEST_F(RegexpTest_156, ConcatZeroSubs_156) {
  Regexp* concat = Regexp::Concat(nullptr, 0, Regexp::LikePerl);
  ASSERT_NE(concat, nullptr);
  EXPECT_EQ(concat->op(), kRegexpEmptyMatch);
  concat->Decref();
}

// Test Alternate with zero subs gives no match
TEST_F(RegexpTest_156, AlternateZeroSubs_156) {
  Regexp* alt = Regexp::Alternate(nullptr, 0, Regexp::LikePerl);
  ASSERT_NE(alt, nullptr);
  EXPECT_EQ(alt->op(), kRegexpNoMatch);
  alt->Decref();
}

// Test Concat with one sub returns that sub
TEST_F(RegexpTest_156, ConcatOneSub_156) {
  Regexp* lit = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* subs[1] = {lit};
  Regexp* concat = Regexp::Concat(subs, 1, Regexp::LikePerl);
  ASSERT_NE(concat, nullptr);
  EXPECT_EQ(concat->op(), kRegexpLiteral);
  concat->Decref();
}

// Test parsing invalid regex
TEST_F(RegexpTest_156, ParseInvalid_156) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
}

// Test parsing complex nested pattern
TEST_F(RegexpTest_156, ParseComplexPattern_156) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((a+)(b*)|(c?d)){1,3}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_GT(re->NumCaptures(), 0);
  re->Decref();
}

// Test Repeat with exact count (min == max)
TEST_F(RegexpTest_156, RepeatExactCount_156) {
  Regexp* lit = Regexp::NewLiteral('z', Regexp::LikePerl);
  Regexp* rep = Regexp::Repeat(lit, Regexp::LikePerl, 3, 3);
  ASSERT_NE(rep, nullptr);
  EXPECT_EQ(rep->op(), kRegexpRepeat);
  EXPECT_EQ(rep->min(), 3);
  EXPECT_EQ(rep->max(), 3);
  rep->Decref();
}

// Test Unicode literal
TEST_F(RegexpTest_156, UnicodeLiteral_156) {
  Regexp* re = Regexp::NewLiteral(0x4e16, Regexp::LikePerl);  // 世
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 0x4e16);
  re->Decref();
}

// Test AlternateNoFactor
TEST_F(RegexpTest_156, AlternateNoFactor_156) {
  Regexp* subs[3];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  subs[2] = Regexp::NewLiteral('c', Regexp::LikePerl);
  Regexp* alt = Regexp::AlternateNoFactor(subs, 3, Regexp::LikePerl);
  ASSERT_NE(alt, nullptr);
  alt->Decref();
}

// Test simple accessor
TEST_F(RegexpTest_156, SimpleAccessor_156) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // After Simplify, simple() should be true
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  EXPECT_TRUE(simplified->simple());
  simplified->Decref();
  re->Decref();
}

// Test parsing begin text anchor
TEST_F(RegexpTest_156, ParseBeginText_156) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\A", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpBeginText);
  re->Decref();
}

// Test parsing end text anchor
TEST_F(RegexpTest_156, ParseEndText_156) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\z", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpEndText);
  re->Decref();
}

// Test nested captures count
TEST_F(RegexpTest_156, NestedCapturesCount_156) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((a)(b(c)))", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 4);
  re->Decref();
}

// Test Ref count
TEST_F(RegexpTest_156, RefCount_156) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->Ref(), 1);
  re->Incref();
  EXPECT_EQ(re->Ref(), 2);
  re->Decref();
  EXPECT_EQ(re->Ref(), 1);
  re->Decref();
}

}  // namespace re2
