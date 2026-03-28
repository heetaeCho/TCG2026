#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <string>
#include <map>
#include <memory>

namespace re2 {

// Helper to manage Regexp lifetime via Decref
class RegexpGuard {
 public:
  explicit RegexpGuard(Regexp* re) : re_(re) {}
  ~RegexpGuard() { if (re_) re_->Decref(); }
  Regexp* get() { return re_; }
  Regexp* release() { Regexp* r = re_; re_ = nullptr; return r; }
 private:
  Regexp* re_;
};

// Test NewLiteral creates a regexp with correct op and rune
TEST(RegexpTest_346, NewLiteralBasic_346) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'a');
  re->Decref();
}

// Test NewLiteral with unicode rune
TEST(RegexpTest_346, NewLiteralUnicode_346) {
  Regexp* re = Regexp::NewLiteral(0x4e16, Regexp::NoParseFlags);  // Chinese character
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 0x4e16);
  re->Decref();
}

// Test NewLiteral with FoldCase flag
TEST(RegexpTest_346, NewLiteralWithFoldCase_346) {
  Regexp* re = Regexp::NewLiteral('A', Regexp::FoldCase);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'A');
  EXPECT_TRUE(re->parse_flags() & Regexp::FoldCase);
  re->Decref();
}

// Test Parse with a simple literal
TEST(RegexpTest_346, ParseSimpleLiteral_346) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test Parse with empty string
TEST(RegexpTest_346, ParseEmptyString_346) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  re->Decref();
}

// Test Parse with invalid regex
TEST(RegexpTest_346, ParseInvalidRegex_346) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

// Test Parse with alternation
TEST(RegexpTest_346, ParseAlternation_346) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpAlternate);
  re->Decref();
}

// Test Parse with star
TEST(RegexpTest_346, ParseStar_346) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

// Test Parse with plus
TEST(RegexpTest_346, ParsePlus_346) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

// Test Parse with quest
TEST(RegexpTest_346, ParseQuest_346) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

// Test Parse with capture group
TEST(RegexpTest_346, ParseCapture_346) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  re->Decref();
}

// Test Parse with character class
TEST(RegexpTest_346, ParseCharClass_346) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[abc]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCharClass);
  re->Decref();
}

// Test Parse with repeat
TEST(RegexpTest_346, ParseRepeat_346) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), 5);
  re->Decref();
}

// Test Parse with concat
TEST(RegexpTest_346, ParseConcat_346) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("ab", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpConcat);
  re->Decref();
}

// Test Parse with anchors
TEST(RegexpTest_346, ParseBeginEndLine_346) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^a$", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Parse dot matches any char
TEST(RegexpTest_346, ParseAnyChar_346) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpAnyChar);
  re->Decref();
}

// Test Incref and Decref
TEST(RegexpTest_346, IncrefDecref_346) {
  Regexp* re = Regexp::NewLiteral('x', Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->Ref(), 1);
  Regexp* re2 = re->Incref();
  EXPECT_EQ(re2, re);
  EXPECT_EQ(re->Ref(), 2);
  re->Decref();
  EXPECT_EQ(re->Ref(), 1);
  re->Decref();
}

// Test ToString roundtrip
TEST(RegexpTest_346, ToStringSimple_346) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test ToString for alternation
TEST(RegexpTest_346, ToStringAlternation_346) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b|c", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test NumCaptures
TEST(RegexpTest_346, NumCapturesNone_346) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

// Test NumCaptures with captures
TEST(RegexpTest_346, NumCapturesMultiple_346) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// Test NumCaptures with nested captures
TEST(RegexpTest_346, NumCapturesNested_346) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((a)(b))", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// Test NamedCaptures
TEST(RegexpTest_346, NamedCapturesNone_346) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* named = re->NamedCaptures();
  EXPECT_EQ(named, nullptr);
  delete named;
  re->Decref();
}

// Test NamedCaptures with named groups
TEST(RegexpTest_346, NamedCapturesPresent_346) {
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
TEST(RegexpTest_346, CaptureNamesPresent_346) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<foo>a)(?P<bar>b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<int, std::string>* names = re->CaptureNames();
  ASSERT_NE(names, nullptr);
  EXPECT_EQ((*names)[1], "foo");
  EXPECT_EQ((*names)[2], "bar");
  delete names;
  re->Decref();
}

// Test Simplify
TEST(RegexpTest_346, SimplifyBasic_346) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// Test SimplifyRegexp static method
TEST(RegexpTest_346, SimplifyRegexpStatic_346) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{2}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

// Test SimplifyRegexp with invalid regex
TEST(RegexpTest_346, SimplifyRegexpInvalid_346) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("(", Regexp::LikePerl, &dst, &status);
  EXPECT_FALSE(ok);
}

// Test Star creation
TEST(RegexpTest_346, StarCreation_346) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Star(sub, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

// Test Plus creation
TEST(RegexpTest_346, PlusCreation_346) {
  Regexp* sub = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* re = Regexp::Plus(sub, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

// Test Quest creation
TEST(RegexpTest_346, QuestCreation_346) {
  Regexp* sub = Regexp::NewLiteral('c', Regexp::NoParseFlags);
  Regexp* re = Regexp::Quest(sub, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

// Test Concat creation
TEST(RegexpTest_346, ConcatCreation_346) {
  Regexp* subs[3];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  subs[2] = Regexp::NewLiteral('c', Regexp::NoParseFlags);
  Regexp* re = Regexp::Concat(subs, 3, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpConcat);
  re->Decref();
}

// Test Concat with single element
TEST(RegexpTest_346, ConcatSingleElement_346) {
  Regexp* subs[1];
  subs[0] = Regexp::NewLiteral('x', Regexp::NoParseFlags);
  Regexp* re = Regexp::Concat(subs, 1, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  // Single element concat should just return the element itself
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// Test Concat with zero elements
TEST(RegexpTest_346, ConcatZeroElements_346) {
  Regexp* re = Regexp::Concat(nullptr, 0, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  re->Decref();
}

// Test Alternate creation
TEST(RegexpTest_346, AlternateCreation_346) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* re = Regexp::Alternate(subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Alternate with single element
TEST(RegexpTest_346, AlternateSingleElement_346) {
  Regexp* subs[1];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Alternate(subs, 1, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// Test Alternate with zero elements
TEST(RegexpTest_346, AlternateZeroElements_346) {
  Regexp* re = Regexp::Alternate(nullptr, 0, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpNoMatch);
  re->Decref();
}

// Test AlternateNoFactor
TEST(RegexpTest_346, AlternateNoFactor_346) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* re = Regexp::AlternateNoFactor(subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpAlternate);
  re->Decref();
}

// Test Capture creation
TEST(RegexpTest_346, CaptureCreation_346) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Capture(sub, Regexp::NoParseFlags, 1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 1);
  re->Decref();
}

// Test Repeat creation
TEST(RegexpTest_346, RepeatCreation_346) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 2, 5);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), 5);
  re->Decref();
}

// Test Repeat with unbounded max
TEST(RegexpTest_346, RepeatUnbounded_346) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 1, -1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 1);
  EXPECT_EQ(re->max(), -1);
  re->Decref();
}

// Test HaveMatch creation
TEST(RegexpTest_346, HaveMatchCreation_346) {
  Regexp* re = Regexp::HaveMatch(42, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), 42);
  re->Decref();
}

// Test LiteralString
TEST(RegexpTest_346, LiteralStringCreation_346) {
  Rune runes[] = {'h', 'e', 'l', 'l', 'o'};
  Regexp* re = Regexp::LiteralString(runes, 5, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 5);
  re->Decref();
}

// Test Dump
TEST(RegexpTest_346, DumpBasic_346) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string dump = re->Dump();
  EXPECT_FALSE(dump.empty());
  re->Decref();
}

// Test CompileToProg
TEST(RegexpTest_346, CompileToProg_346) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileToReverseProg
TEST(RegexpTest_346, CompileToReverseProg_346) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test RequiredPrefix on prefixed literal
TEST(RegexpTest_346, RequiredPrefixLiteral_346) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;
  bool has_prefix = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  if (has_prefix) {
    EXPECT_FALSE(prefix.empty());
    if (suffix) suffix->Decref();
  }
  re->Decref();
}

// Test RequiredPrefix on non-prefixed pattern
TEST(RegexpTest_346, RequiredPrefixNone_346) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;
  bool has_prefix = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  EXPECT_FALSE(has_prefix);
  re->Decref();
}

// Test op accessor
TEST(RegexpTest_346, OpAccessor_346) {
  Regexp* re = Regexp::NewLiteral('z', Regexp::NoParseFlags);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// Test parse_flags accessor
TEST(RegexpTest_346, ParseFlagsAccessor_346) {
  Regexp* re = Regexp::NewLiteral('z', Regexp::FoldCase);
  EXPECT_TRUE(re->parse_flags() & Regexp::FoldCase);
  re->Decref();
}

// Test nsub for star
TEST(RegexpTest_346, NsubStar_346) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Star(sub, Regexp::NoParseFlags);
  EXPECT_EQ(re->nsub(), 1);
  re->Decref();
}

// Test nsub for concat
TEST(RegexpTest_346, NsubConcat_346) {
  Regexp* subs[3];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  subs[2] = Regexp::NewLiteral('c', Regexp::NoParseFlags);
  Regexp* re = Regexp::Concat(subs, 3, Regexp::NoParseFlags);
  EXPECT_EQ(re->nsub(), 3);
  re->Decref();
}

// Test sub accessor
TEST(RegexpTest_346, SubAccessor_346) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* re = Regexp::Concat(subs, 2, Regexp::NoParseFlags);
  ASSERT_EQ(re->nsub(), 2);
  Regexp** sub = re->sub();
  ASSERT_NE(sub, nullptr);
  EXPECT_EQ(sub[0]->op(), kRegexpLiteral);
  EXPECT_EQ(sub[0]->rune(), 'a');
  EXPECT_EQ(sub[1]->op(), kRegexpLiteral);
  EXPECT_EQ(sub[1]->rune(), 'b');
  re->Decref();
}

// Test NullWalk doesn't crash
TEST(RegexpTest_346, NullWalkNoCrash_346) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a(b|c)*d", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_NO_FATAL_FAILURE(re->NullWalk());
  re->Decref();
}

// Test complex pattern parse and ToString round-trip
TEST(RegexpTest_346, ComplexPatternRoundTrip_346) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:a|b)+c{2,4}d?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test Parse with word boundary
TEST(RegexpTest_346, ParseWordBoundary_346) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\bword\\b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Parse with escaped metacharacters
TEST(RegexpTest_346, ParseEscapedMetachars_346) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\(\\)\\[\\]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Repeat with min == max (exact count)
TEST(RegexpTest_346, RepeatExactCount_346) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 3, 3);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 3);
  EXPECT_EQ(re->max(), 3);
  re->Decref();
}

// Test Parse with deeply nested groups
TEST(RegexpTest_346, ParseDeepNesting_346) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((((a))))", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 4);
  re->Decref();
}

// Test Parse with non-capturing groups
TEST(RegexpTest_346, ParseNonCapturingGroup_346) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:a)(?:b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

// Test Parse with bad repeat
TEST(RegexpTest_346, ParseBadRepeat_346) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("*", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

// Test Parse with unmatched close paren
TEST(RegexpTest_346, ParseUnmatchedCloseParen_346) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(")", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

// Test simple() accessor
TEST(RegexpTest_346, SimpleAccessor_346) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  // Just test we can call it; the result depends on internal state
  (void)re->simple();
  re->Decref();
}

// Test MimicsPCRE
TEST(RegexpTest_346, MimicsPCRE_346) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // Simple literal should mimic PCRE
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Test RequiredPrefixForAccel
TEST(RegexpTest_346, RequiredPrefixForAccel_346) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^hello.*world", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  bool result = re->RequiredPrefixForAccel(&prefix, &foldcase);
  // Just verify the call completes without crash
  (void)result;
  re->Decref();
}

}  // namespace re2
