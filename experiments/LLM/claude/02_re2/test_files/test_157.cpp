#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <string>
#include <map>
#include <memory>

namespace re2 {

class RegexpTest_157 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// Test Parse with a simple literal
TEST_F(RegexpTest_157, ParseSimpleLiteral_157) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test Parse with empty string
TEST_F(RegexpTest_157, ParseEmptyString_157) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  re->Decref();
}

// Test Parse with invalid regex
TEST_F(RegexpTest_157, ParseInvalidRegex_157) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[z-a]", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

// Test Parse with alternation
TEST_F(RegexpTest_157, ParseAlternation_157) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpAlternate);
  re->Decref();
}

// Test Parse with star
TEST_F(RegexpTest_157, ParseStar_157) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

// Test Parse with plus
TEST_F(RegexpTest_157, ParsePlus_157) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

// Test Parse with question mark
TEST_F(RegexpTest_157, ParseQuest_157) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

// Test Parse with character class
TEST_F(RegexpTest_157, ParseCharClass_157) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[abc]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCharClass);
  EXPECT_NE(re->cc(), nullptr);
  re->Decref();
}

// Test Parse with capture group
TEST_F(RegexpTest_157, ParseCapture_157) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 1);
  re->Decref();
}

// Test Parse with concatenation
TEST_F(RegexpTest_157, ParseConcat_157) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("ab", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpConcat);
  re->Decref();
}

// Test Parse with repeat
TEST_F(RegexpTest_157, ParseRepeat_157) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), 5);
  re->Decref();
}

// Test Parse with dot (any char)
TEST_F(RegexpTest_157, ParseAnyChar_157) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // Dot matches any character except newline in Perl mode
  re->Decref();
}

// Test Incref and Decref
TEST_F(RegexpTest_157, IncrefDecref_157) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* re2 = re->Incref();
  EXPECT_EQ(re, re2);
  re->Decref();
  re->Decref();
}

// Test ToString
TEST_F(RegexpTest_157, ToString_157) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "abc");
  re->Decref();
}

// Test ToString with alternation
TEST_F(RegexpTest_157, ToStringAlternation_157) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "[ab]");
  re->Decref();
}

// Test Dump
TEST_F(RegexpTest_157, Dump_157) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string d = re->Dump();
  EXPECT_FALSE(d.empty());
  re->Decref();
}

// Test NumCaptures with no captures
TEST_F(RegexpTest_157, NumCapturesNone_157) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

// Test NumCaptures with captures
TEST_F(RegexpTest_157, NumCapturesMultiple_157) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// Test NumCaptures with nested captures
TEST_F(RegexpTest_157, NumCapturesNested_157) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((a)(b))", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// Test NamedCaptures
TEST_F(RegexpTest_157, NamedCaptures_157) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<name>abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* caps = re->NamedCaptures();
  ASSERT_NE(caps, nullptr);
  EXPECT_EQ(caps->size(), 1u);
  EXPECT_EQ((*caps)["name"], 1);
  delete caps;
  re->Decref();
}

// Test NamedCaptures with no named captures
TEST_F(RegexpTest_157, NamedCapturesNone_157) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* caps = re->NamedCaptures();
  EXPECT_EQ(caps, nullptr);
  re->Decref();
}

// Test CaptureNames
TEST_F(RegexpTest_157, CaptureNames_157) {
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

// Test NewLiteral
TEST_F(RegexpTest_157, NewLiteral_157) {
  Regexp* re = Regexp::NewLiteral('x', Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'x');
  re->Decref();
}

// Test LiteralString
TEST_F(RegexpTest_157, LiteralString_157) {
  Rune runes[] = {'h', 'e', 'l', 'l', 'o'};
  Regexp* re = Regexp::LiteralString(runes, 5, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 5);
  re->Decref();
}

// Test LiteralString with single rune
TEST_F(RegexpTest_157, LiteralStringSingle_157) {
  Rune runes[] = {'a'};
  Regexp* re = Regexp::LiteralString(runes, 1, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  // Single rune literal string might be optimized to kRegexpLiteral
  re->Decref();
}

// Test HaveMatch
TEST_F(RegexpTest_157, HaveMatch_157) {
  Regexp* re = Regexp::HaveMatch(42, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), 42);
  re->Decref();
}

// Test Plus static method
TEST_F(RegexpTest_157, PlusStatic_157) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Plus(sub, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

// Test Star static method
TEST_F(RegexpTest_157, StarStatic_157) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Star(sub, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

// Test Quest static method
TEST_F(RegexpTest_157, QuestStatic_157) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Quest(sub, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

// Test Capture static method
TEST_F(RegexpTest_157, CaptureStatic_157) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Capture(sub, Regexp::NoParseFlags, 1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 1);
  re->Decref();
}

// Test Concat static method
TEST_F(RegexpTest_157, ConcatStatic_157) {
  Regexp* subs[3];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  subs[2] = Regexp::NewLiteral('c', Regexp::NoParseFlags);
  Regexp* re = Regexp::Concat(subs, 3, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpConcat);
  EXPECT_EQ(re->nsub(), 3);
  re->Decref();
}

// Test Concat with single sub
TEST_F(RegexpTest_157, ConcatSingleSub_157) {
  Regexp* subs[1];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Concat(subs, 1, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  // Single sub concat may just return the sub itself
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// Test Concat with zero subs
TEST_F(RegexpTest_157, ConcatZeroSubs_157) {
  Regexp* re = Regexp::Concat(nullptr, 0, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  re->Decref();
}

// Test Alternate static method
TEST_F(RegexpTest_157, AlternateStatic_157) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* re = Regexp::Alternate(subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Alternate with zero subs
TEST_F(RegexpTest_157, AlternateZeroSubs_157) {
  Regexp* re = Regexp::Alternate(nullptr, 0, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpNoMatch);
  re->Decref();
}

// Test Alternate with single sub
TEST_F(RegexpTest_157, AlternateSingleSub_157) {
  Regexp* subs[1];
  subs[0] = Regexp::NewLiteral('x', Regexp::NoParseFlags);
  Regexp* re = Regexp::Alternate(subs, 1, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// Test AlternateNoFactor
TEST_F(RegexpTest_157, AlternateNoFactor_157) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* re = Regexp::AlternateNoFactor(subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Repeat
TEST_F(RegexpTest_157, RepeatStatic_157) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 3, 7);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 3);
  EXPECT_EQ(re->max(), 7);
  re->Decref();
}

// Test Repeat with unbounded max (-1)
TEST_F(RegexpTest_157, RepeatUnbounded_157) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 1, -1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 1);
  EXPECT_EQ(re->max(), -1);
  re->Decref();
}

// Test Simplify
TEST_F(RegexpTest_157, Simplify_157) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// Test SimplifyRegexp static
TEST_F(RegexpTest_157, SimplifyRegexpStatic_157) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{2}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

// Test RequiredPrefix
TEST_F(RegexpTest_157, RequiredPrefix_157) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc.*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase;
  Regexp* suffix = nullptr;
  bool has_prefix = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  if (has_prefix) {
    EXPECT_FALSE(prefix.empty());
    if (suffix) suffix->Decref();
  }
  re->Decref();
}

// Test RequiredPrefix when no prefix
TEST_F(RegexpTest_157, RequiredPrefixNone_157) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".*abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase;
  Regexp* suffix = nullptr;
  bool has_prefix = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  EXPECT_FALSE(has_prefix);
  re->Decref();
}

// Test RequiredPrefixForAccel
TEST_F(RegexpTest_157, RequiredPrefixForAccel_157) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc.*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase;
  re->RequiredPrefixForAccel(&prefix, &foldcase);
  re->Decref();
}

// Test CompileToProg
TEST_F(RegexpTest_157, CompileToProg_157) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileToReverseProg
TEST_F(RegexpTest_157, CompileToReverseProg_157) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test op() accessor
TEST_F(RegexpTest_157, OpAccessor_157) {
  Regexp* re = Regexp::NewLiteral('z', Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// Test rune() accessor
TEST_F(RegexpTest_157, RuneAccessor_157) {
  Regexp* re = Regexp::NewLiteral('Z', Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->rune(), 'Z');
  re->Decref();
}

// Test parse_flags() accessor
TEST_F(RegexpTest_157, ParseFlagsAccessor_157) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::FoldCase);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->parse_flags() & Regexp::FoldCase);
  re->Decref();
}

// Test nsub() accessor on concat
TEST_F(RegexpTest_157, NsubAccessor_157) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* re = Regexp::Concat(subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->nsub(), 2);
  re->Decref();
}

// Test sub() accessor
TEST_F(RegexpTest_157, SubAccessor_157) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('x', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('y', Regexp::NoParseFlags);
  Regexp* re = Regexp::Concat(subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  Regexp** children = re->sub();
  ASSERT_NE(children, nullptr);
  EXPECT_EQ(children[0]->op(), kRegexpLiteral);
  EXPECT_EQ(children[0]->rune(), 'x');
  EXPECT_EQ(children[1]->op(), kRegexpLiteral);
  EXPECT_EQ(children[1]->rune(), 'y');
  re->Decref();
}

// Test MimicsPCRE
TEST_F(RegexpTest_157, MimicsPCRE_157) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // Simple literals should mimic PCRE
  bool mimics = re->MimicsPCRE();
  EXPECT_TRUE(mimics);
  re->Decref();
}

// Test NullWalk does not crash
TEST_F(RegexpTest_157, NullWalk_157) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a(b|c)*d", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->NullWalk();
  re->Decref();
}

// Test Parse with begin/end anchors
TEST_F(RegexpTest_157, ParseAnchors_157) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc$", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test Parse with Unicode
TEST_F(RegexpTest_157, ParseUnicode_157) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\p{L}+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test Parse with word boundary
TEST_F(RegexpTest_157, ParseWordBoundary_157) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\bfoo\\b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test Parse with unmatched paren (error case)
TEST_F(RegexpTest_157, ParseUnmatchedParen_157) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

// Test Parse with bad escape
TEST_F(RegexpTest_157, ParseBadEscape_157) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

// Test Parse with POSIX flags
TEST_F(RegexpTest_157, ParsePOSIX_157) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc|def", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test Ref on newly created Regexp
TEST_F(RegexpTest_157, RefCount_157) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  // Newly created regexp should have ref count 1
  // After Incref, ref count should be higher
  re->Incref();
  re->Decref();
  re->Decref();
}

// Test match_id accessor
TEST_F(RegexpTest_157, MatchIdAccessor_157) {
  Regexp* re = Regexp::HaveMatch(99, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->match_id(), 99);
  re->Decref();
}

// Test NewCharClass
TEST_F(RegexpTest_157, NewCharClass_157) {
  CharClassBuilder ccb;
  ccb.AddRange('a', 'z');
  Regexp* re = Regexp::NewCharClass(ccb.GetCharClass(), Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCharClass);
  EXPECT_NE(re->cc(), nullptr);
  re->Decref();
}

// Test ToString roundtrip for complex regex
TEST_F(RegexpTest_157, ToStringComplex_157) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a(b+|c{2,3})d?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  // Parse it again to verify it's valid
  RegexpStatus status2;
  Regexp* re2 = Regexp::Parse(s, Regexp::LikePerl, &status2);
  EXPECT_NE(re2, nullptr);
  if (re2) re2->Decref();
  re->Decref();
}

// Test Simplify on already simple regex
TEST_F(RegexpTest_157, SimplifyAlreadySimple_157) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  std::string orig = re->ToString();
  std::string simp = simplified->ToString();
  EXPECT_EQ(orig, simp);
  simplified->Decref();
  re->Decref();
}

// Test Parse with case-insensitive flag
TEST_F(RegexpTest_157, ParseCaseInsensitive_157) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?i)abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test Parse named capture
TEST_F(RegexpTest_157, ParseNamedCapture_157) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<test>abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_NE(re->name(), nullptr);
  EXPECT_EQ(*re->name(), "test");
  re->Decref();
}

// Test runes() and nrunes() on literal string
TEST_F(RegexpTest_157, RunesAccessor_157) {
  Rune runes[] = {'a', 'b', 'c'};
  Regexp* re = Regexp::LiteralString(runes, 3, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->nrunes(), 3);
  EXPECT_NE(re->runes(), nullptr);
  EXPECT_EQ(re->runes()[0], 'a');
  EXPECT_EQ(re->runes()[1], 'b');
  EXPECT_EQ(re->runes()[2], 'c');
  re->Decref();
}

// Test simple() accessor
TEST_F(RegexpTest_157, SimpleAccessor_157) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  // simple() returns whether the regexp is in simplified form
  // For a newly created literal, this may vary
  re->Decref();
}

// Test Parse with bad repeat (error)
TEST_F(RegexpTest_157, ParseBadRepeat_157) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("*", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

// Test Repeat with min == max
TEST_F(RegexpTest_157, RepeatExact_157) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 5, 5);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 5);
  EXPECT_EQ(re->max(), 5);
  re->Decref();
}

// Test Repeat with min=0, max=0
TEST_F(RegexpTest_157, RepeatZero_157) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 0, 0);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

}  // namespace re2
