#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <string>
#include <map>
#include <memory>

namespace re2 {

// Helper to parse a regexp and manage its lifetime
class RegexpTest_360 : public ::testing::Test {
 protected:
  Regexp* Parse(const std::string& pattern) {
    RegexpStatus status;
    Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
    EXPECT_TRUE(re != nullptr) << "Failed to parse: " << pattern
                                << " error: " << status.Text();
    return re;
  }
};

// Test basic Parse and Decref
TEST_F(RegexpTest_360, ParseSimpleLiteral_360) {
  Regexp* re = Parse("hello");
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test NumCaptures with no captures
TEST_F(RegexpTest_360, NumCapturesNone_360) {
  Regexp* re = Parse("hello");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

// Test NumCaptures with one capture
TEST_F(RegexpTest_360, NumCapturesOne_360) {
  Regexp* re = Parse("(hello)");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 1);
  re->Decref();
}

// Test NumCaptures with multiple captures
TEST_F(RegexpTest_360, NumCapturesMultiple_360) {
  Regexp* re = Parse("(a)(b)(c)");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// Test NumCaptures with nested captures
TEST_F(RegexpTest_360, NumCapturesNested_360) {
  Regexp* re = Parse("((a)(b))");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// Test NamedCaptures returns nullptr when no named captures
TEST_F(RegexpTest_360, NamedCapturesNone_360) {
  Regexp* re = Parse("(hello)");
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* captures = re->NamedCaptures();
  EXPECT_EQ(captures, nullptr);
  delete captures;
  re->Decref();
}

// Test NamedCaptures with named captures
TEST_F(RegexpTest_360, NamedCapturesPresent_360) {
  Regexp* re = Parse("(?P<name>hello)");
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* captures = re->NamedCaptures();
  ASSERT_NE(captures, nullptr);
  EXPECT_EQ(captures->size(), 1u);
  EXPECT_EQ((*captures)["name"], 1);
  delete captures;
  re->Decref();
}

// Test NamedCaptures with multiple named captures
TEST_F(RegexpTest_360, NamedCapturesMultiple_360) {
  Regexp* re = Parse("(?P<first>a)(?P<second>b)");
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* captures = re->NamedCaptures();
  ASSERT_NE(captures, nullptr);
  EXPECT_EQ(captures->size(), 2u);
  EXPECT_EQ((*captures)["first"], 1);
  EXPECT_EQ((*captures)["second"], 2);
  delete captures;
  re->Decref();
}

// Test CaptureNames returns map for unnamed captures
TEST_F(RegexpTest_360, CaptureNamesUnnamed_360) {
  Regexp* re = Parse("(a)(b)");
  ASSERT_NE(re, nullptr);
  std::map<int, std::string>* names = re->CaptureNames();
  // For unnamed captures, CaptureNames may return nullptr or empty map
  if (names != nullptr) {
    // Unnamed captures may have empty strings
    for (auto& p : *names) {
      EXPECT_GE(p.first, 1);
    }
  }
  delete names;
  re->Decref();
}

// Test CaptureNames with named captures
TEST_F(RegexpTest_360, CaptureNamesNamed_360) {
  Regexp* re = Parse("(?P<foo>a)(?P<bar>b)");
  ASSERT_NE(re, nullptr);
  std::map<int, std::string>* names = re->CaptureNames();
  ASSERT_NE(names, nullptr);
  EXPECT_EQ((*names)[1], "foo");
  EXPECT_EQ((*names)[2], "bar");
  delete names;
  re->Decref();
}

// Test ToString roundtrip
TEST_F(RegexpTest_360, ToStringSimple_360) {
  Regexp* re = Parse("abc");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test ToString with complex pattern
TEST_F(RegexpTest_360, ToStringComplex_360) {
  Regexp* re = Parse("a(b|c)*d+");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test Dump produces output
TEST_F(RegexpTest_360, DumpOutput_360) {
  Regexp* re = Parse("abc");
  ASSERT_NE(re, nullptr);
  std::string d = re->Dump();
  EXPECT_FALSE(d.empty());
  re->Decref();
}

// Test Incref and Decref
TEST_F(RegexpTest_360, IncrefDecref_360) {
  Regexp* re = Parse("abc");
  ASSERT_NE(re, nullptr);
  Regexp* re2 = re->Incref();
  EXPECT_EQ(re, re2);
  re->Decref();
  re->Decref();
}

// Test Parse with invalid pattern
TEST_F(RegexpTest_360, ParseInvalid_360) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
}

// Test Parse with empty pattern
TEST_F(RegexpTest_360, ParseEmpty_360) {
  Regexp* re = Parse("");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

// Test NewLiteral
TEST_F(RegexpTest_360, NewLiteral_360) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'a');
  re->Decref();
}

// Test HaveMatch
TEST_F(RegexpTest_360, HaveMatch_360) {
  Regexp* re = Regexp::HaveMatch(42, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), 42);
  re->Decref();
}

// Test Plus
TEST_F(RegexpTest_360, Plus_360) {
  Regexp* lit = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Plus(lit, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

// Test Star
TEST_F(RegexpTest_360, Star_360) {
  Regexp* lit = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Star(lit, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

// Test Quest
TEST_F(RegexpTest_360, Quest_360) {
  Regexp* lit = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Quest(lit, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

// Test Concat
TEST_F(RegexpTest_360, Concat_360) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* re = Regexp::Concat(subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Alternate
TEST_F(RegexpTest_360, Alternate_360) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* re = Regexp::Alternate(subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Capture
TEST_F(RegexpTest_360, Capture_360) {
  Regexp* lit = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Capture(lit, Regexp::NoParseFlags, 1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 1);
  re->Decref();
}

// Test Repeat
TEST_F(RegexpTest_360, Repeat_360) {
  Regexp* lit = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(lit, Regexp::NoParseFlags, 2, 5);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), 5);
  re->Decref();
}

// Test LiteralString
TEST_F(RegexpTest_360, LiteralString_360) {
  Rune runes[] = {'h', 'i'};
  Regexp* re = Regexp::LiteralString(runes, 2, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 2);
  re->Decref();
}

// Test Simplify
TEST_F(RegexpTest_360, Simplify_360) {
  Regexp* re = Parse("a{2,5}");
  ASSERT_NE(re, nullptr);
  Regexp* simple = re->Simplify();
  ASSERT_NE(simple, nullptr);
  simple->Decref();
  re->Decref();
}

// Test SimplifyRegexp
TEST_F(RegexpTest_360, SimplifyRegexp_360) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{2,5}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

// Test RequiredPrefix with anchored literal prefix
TEST_F(RegexpTest_360, RequiredPrefixTrue_360) {
  Regexp* re = Parse("^abc.*");
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

// Test RequiredPrefix without prefix
TEST_F(RegexpTest_360, RequiredPrefixFalse_360) {
  Regexp* re = Parse(".*abc");
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;
  bool has_prefix = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  if (!has_prefix) {
    EXPECT_TRUE(prefix.empty());
  } else {
    if (suffix) suffix->Decref();
  }
  re->Decref();
}

// Test NullWalk doesn't crash
TEST_F(RegexpTest_360, NullWalk_360) {
  Regexp* re = Parse("a(b|c)*d");
  ASSERT_NE(re, nullptr);
  re->NullWalk();
  re->Decref();
}

// Test CompileToProg
TEST_F(RegexpTest_360, CompileToProg_360) {
  Regexp* re = Parse("abc");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileToReverseProg
TEST_F(RegexpTest_360, CompileToReverseProg_360) {
  Regexp* re = Parse("abc");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test op() accessor
TEST_F(RegexpTest_360, OpAccessor_360) {
  Regexp* re = Regexp::NewLiteral('x', Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// Test parse_flags() accessor
TEST_F(RegexpTest_360, ParseFlagsAccessor_360) {
  Regexp* re = Regexp::NewLiteral('x', Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->parse_flags(), Regexp::NoParseFlags);
  re->Decref();
}

// Test Concat with zero subs
TEST_F(RegexpTest_360, ConcatZeroSubs_360) {
  Regexp* re = Regexp::Concat(nullptr, 0, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Alternate with zero subs
TEST_F(RegexpTest_360, AlternateZeroSubs_360) {
  Regexp* re = Regexp::Alternate(nullptr, 0, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Concat with single sub
TEST_F(RegexpTest_360, ConcatSingleSub_360) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Concat(&sub, 1, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Alternate with single sub
TEST_F(RegexpTest_360, AlternateSingleSub_360) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Alternate(&sub, 1, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test NamedCaptures with mixed named and unnamed captures
TEST_F(RegexpTest_360, NamedCapturesMixed_360) {
  Regexp* re = Parse("(a)(?P<name>b)(c)");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  std::map<std::string, int>* named = re->NamedCaptures();
  ASSERT_NE(named, nullptr);
  EXPECT_EQ(named->size(), 1u);
  EXPECT_EQ((*named)["name"], 2);
  delete named;
  
  std::map<int, std::string>* cnames = re->CaptureNames();
  ASSERT_NE(cnames, nullptr);
  EXPECT_NE(cnames->find(2), cnames->end());
  EXPECT_EQ((*cnames)[2], "name");
  delete cnames;
  
  re->Decref();
}

// Test RequiredPrefixForAccel
TEST_F(RegexpTest_360, RequiredPrefixForAccel_360) {
  Regexp* re = Parse("^hello.*world");
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  re->RequiredPrefixForAccel(&prefix, &foldcase);
  // Just verify it doesn't crash; the result depends on implementation
  re->Decref();
}

// Test Parse with character class
TEST_F(RegexpTest_360, ParseCharacterClass_360) {
  Regexp* re = Parse("[a-z]");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

// Test Parse with Unicode
TEST_F(RegexpTest_360, ParseUnicode_360) {
  Regexp* re = Parse("\\p{L}+");
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test MimicsPCRE
TEST_F(RegexpTest_360, MimicsPCRE_360) {
  Regexp* re = Parse("abc");
  ASSERT_NE(re, nullptr);
  // Just check it returns without crashing
  bool result = re->MimicsPCRE();
  (void)result;
  re->Decref();
}

// Test Repeat with min == max
TEST_F(RegexpTest_360, RepeatExact_360) {
  Regexp* lit = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(lit, Regexp::NoParseFlags, 3, 3);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->min(), 3);
  EXPECT_EQ(re->max(), 3);
  re->Decref();
}

// Test Repeat with unbounded max (-1)
TEST_F(RegexpTest_360, RepeatUnbounded_360) {
  Regexp* lit = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(lit, Regexp::NoParseFlags, 1, -1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->min(), 1);
  EXPECT_EQ(re->max(), -1);
  re->Decref();
}

// Test simple() accessor
TEST_F(RegexpTest_360, SimpleAccessor_360) {
  Regexp* re = Parse("a");
  ASSERT_NE(re, nullptr);
  // After Simplify, simple should be set
  Regexp* s = re->Simplify();
  ASSERT_NE(s, nullptr);
  // Just verify it doesn't crash
  bool is_simple = s->simple();
  (void)is_simple;
  s->Decref();
  re->Decref();
}

// Test AlternateNoFactor
TEST_F(RegexpTest_360, AlternateNoFactor_360) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* re = Regexp::AlternateNoFactor(subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Parse with various flags
TEST_F(RegexpTest_360, ParseWithFlags_360) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?i)abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test deeply nested captures
TEST_F(RegexpTest_360, DeepNestedCaptures_360) {
  Regexp* re = Parse("((((a))))");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 4);
  re->Decref();
}

}  // namespace re2
