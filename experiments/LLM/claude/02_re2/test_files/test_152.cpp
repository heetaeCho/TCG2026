#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <string>
#include <map>
#include <memory>

namespace re2 {

class RegexpTest_152 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Cleanup handled by Decref calls in individual tests
  }
};

// Test parsing a simple literal regexp
TEST_F(RegexpTest_152, ParseSimpleLiteral_152) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test parsing an empty string
TEST_F(RegexpTest_152, ParseEmptyString_152) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test parsing an invalid regexp
TEST_F(RegexpTest_152, ParseInvalidRegexp_152) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[invalid", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

// Test parse_flags returns the flags used during construction
TEST_F(RegexpTest_152, ParseFlagsReturned_152) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // The parse flags should have LikePerl bits set (at minimum)
  EXPECT_NE(re->parse_flags() & Regexp::LikePerl, 0);
  re->Decref();
}

// Test ToString round-trips for a simple pattern
TEST_F(RegexpTest_152, ToStringSimple_152) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "abc");
  re->Decref();
}

// Test ToString for alternation
TEST_F(RegexpTest_152, ToStringAlternation_152) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "[ab]");
  re->Decref();
}

// Test Dump produces non-empty output
TEST_F(RegexpTest_152, DumpNonEmpty_152) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+b*c?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string dump = re->Dump();
  EXPECT_FALSE(dump.empty());
  re->Decref();
}

// Test NumCaptures with no captures
TEST_F(RegexpTest_152, NumCapturesZero_152) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

// Test NumCaptures with captures
TEST_F(RegexpTest_152, NumCapturesNonZero_152) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// Test NumCaptures with nested captures
TEST_F(RegexpTest_152, NumCapturesNested_152) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((a)(b))", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// Test NamedCaptures returns null when no named captures
TEST_F(RegexpTest_152, NamedCapturesNone_152) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* names = re->NamedCaptures();
  EXPECT_EQ(names, nullptr);
  re->Decref();
}

// Test NamedCaptures with named groups
TEST_F(RegexpTest_152, NamedCapturesPresent_152) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<first>a)(?P<second>b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* names = re->NamedCaptures();
  ASSERT_NE(names, nullptr);
  EXPECT_EQ(names->size(), 2u);
  EXPECT_EQ((*names)["first"], 1);
  EXPECT_EQ((*names)["second"], 2);
  delete names;
  re->Decref();
}

// Test CaptureNames with named groups
TEST_F(RegexpTest_152, CaptureNamesPresent_152) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<foo>a)(?P<bar>b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<int, std::string>* capnames = re->CaptureNames();
  ASSERT_NE(capnames, nullptr);
  EXPECT_EQ((*capnames)[1], "foo");
  EXPECT_EQ((*capnames)[2], "bar");
  delete capnames;
  re->Decref();
}

// Test CaptureNames with no named groups
TEST_F(RegexpTest_152, CaptureNamesNone_152) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<int, std::string>* capnames = re->CaptureNames();
  EXPECT_EQ(capnames, nullptr);
  re->Decref();
}

// Test Incref and Decref
TEST_F(RegexpTest_152, IncrefDecref_152) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* re2 = re->Incref();
  EXPECT_EQ(re, re2);
  // Now ref count is 2, decref twice
  re->Decref();
  re2->Decref();
}

// Test Simplify
TEST_F(RegexpTest_152, Simplify_152) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// Test SimplifyRegexp static method
TEST_F(RegexpTest_152, SimplifyRegexpStatic_152) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{2,5}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

// Test SimplifyRegexp with invalid input
TEST_F(RegexpTest_152, SimplifyRegexpInvalid_152) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("[invalid", Regexp::LikePerl, &dst, &status);
  EXPECT_FALSE(ok);
}

// Test RequiredPrefix
TEST_F(RegexpTest_152, RequiredPrefixSimple_152) {
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

// Test RequiredPrefix with no prefix
TEST_F(RegexpTest_152, RequiredPrefixNone_152) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".*abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;
  bool has_prefix = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  EXPECT_FALSE(has_prefix);
  re->Decref();
}

// Test RequiredPrefixForAccel
TEST_F(RegexpTest_152, RequiredPrefixForAccel_152) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^hello", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  bool has = re->RequiredPrefixForAccel(&prefix, &foldcase);
  if (has) {
    EXPECT_FALSE(prefix.empty());
  }
  re->Decref();
}

// Test NewLiteral
TEST_F(RegexpTest_152, NewLiteral_152) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'a');
  re->Decref();
}

// Test LiteralString
TEST_F(RegexpTest_152, LiteralString_152) {
  Rune runes[] = {'h', 'e', 'l', 'l', 'o'};
  Regexp* re = Regexp::LiteralString(runes, 5, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 5);
  re->Decref();
}

// Test HaveMatch
TEST_F(RegexpTest_152, HaveMatch_152) {
  Regexp* re = Regexp::HaveMatch(42, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), 42);
  re->Decref();
}

// Test Plus
TEST_F(RegexpTest_152, Plus_152) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Plus(sub, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

// Test Star
TEST_F(RegexpTest_152, Star_152) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Star(sub, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

// Test Quest
TEST_F(RegexpTest_152, Quest_152) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Quest(sub, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

// Test Concat
TEST_F(RegexpTest_152, Concat_152) {
  Regexp* subs[3];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  subs[2] = Regexp::NewLiteral('c', Regexp::NoParseFlags);
  Regexp* re = Regexp::Concat(subs, 3, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Concat with zero subs
TEST_F(RegexpTest_152, ConcatEmpty_152) {
  Regexp* re = Regexp::Concat(nullptr, 0, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  re->Decref();
}

// Test Concat with one sub
TEST_F(RegexpTest_152, ConcatSingle_152) {
  Regexp* subs[1];
  subs[0] = Regexp::NewLiteral('x', Regexp::NoParseFlags);
  Regexp* re = Regexp::Concat(subs, 1, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// Test Alternate
TEST_F(RegexpTest_152, Alternate_152) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* re = Regexp::Alternate(subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Alternate with zero subs
TEST_F(RegexpTest_152, AlternateEmpty_152) {
  Regexp* re = Regexp::Alternate(nullptr, 0, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpNoMatch);
  re->Decref();
}

// Test AlternateNoFactor
TEST_F(RegexpTest_152, AlternateNoFactor_152) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* re = Regexp::AlternateNoFactor(subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Capture
TEST_F(RegexpTest_152, Capture_152) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Capture(sub, Regexp::NoParseFlags, 1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 1);
  re->Decref();
}

// Test Repeat
TEST_F(RegexpTest_152, Repeat_152) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 2, 5);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), 5);
  re->Decref();
}

// Test Repeat with unbounded max (-1)
TEST_F(RegexpTest_152, RepeatUnbounded_152) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 3, -1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->min(), 3);
  EXPECT_EQ(re->max(), -1);
  re->Decref();
}

// Test CompileToProg
TEST_F(RegexpTest_152, CompileToProg_152) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileToReverseProg
TEST_F(RegexpTest_152, CompileToReverseProg_152) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test NullWalk does not crash
TEST_F(RegexpTest_152, NullWalk_152) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a|b)*c+d?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->NullWalk();  // Should not crash
  re->Decref();
}

// Test MimicsPCRE on simple pattern
TEST_F(RegexpTest_152, MimicsPCRE_152) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // Simple literal should mimic PCRE
  bool mimics = re->MimicsPCRE();
  EXPECT_TRUE(mimics);
  re->Decref();
}

// Test op() accessor
TEST_F(RegexpTest_152, OpAccessor_152) {
  Regexp* re = Regexp::NewLiteral('z', Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// Test nsub() for concat
TEST_F(RegexpTest_152, NsubAccessor_152) {
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

// Test parsing character classes
TEST_F(RegexpTest_152, ParseCharacterClass_152) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test parsing with POSIX flags
TEST_F(RegexpTest_152, ParsePOSIX_152) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc|def", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test parsing complex pattern
TEST_F(RegexpTest_152, ParseComplex_152) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^(?:foo|bar)\\d+\\.\\w*$", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test parsing unanchored repetition
TEST_F(RegexpTest_152, ParseRepetition_152) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3,7}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test parsing invalid: mismatched parenthesis
TEST_F(RegexpTest_152, ParseMismatchedParen_152) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

// Test parsing invalid: bad escape
TEST_F(RegexpTest_152, ParseBadRepetition_152) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("*abc", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

// Test Simplify on already simple expression
TEST_F(RegexpTest_152, SimplifyAlreadySimple_152) {
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

// Test parsing dot-star
TEST_F(RegexpTest_152, ParseDotStar_152) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test sub() accessor for Plus
TEST_F(RegexpTest_152, SubAccessor_152) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Plus(sub, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->nsub(), 1);
  EXPECT_NE(re->sub(), nullptr);
  EXPECT_EQ(re->sub()[0]->op(), kRegexpLiteral);
  re->Decref();
}

// Test simple() accessor
TEST_F(RegexpTest_152, SimpleAccessor_152) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  // After Simplify, simple() should reflect computed simplicity
  // We just verify it returns without crashing
  (void)simplified->simple();
  simplified->Decref();
  re->Decref();
}

// Test parsing Unicode escape
TEST_F(RegexpTest_152, ParseUnicodeEscape_152) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\x{41}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

}  // namespace re2
