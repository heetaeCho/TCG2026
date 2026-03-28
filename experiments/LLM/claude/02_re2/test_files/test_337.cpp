#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <string>
#include <map>
#include <memory>

namespace re2 {

class RegexpTest_337 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Cleanup handled by Decref calls in tests
  }
};

// Test HaveMatch creates a regexp with correct op and match_id
TEST_F(RegexpTest_337, HaveMatch_BasicCreation_337) {
  Regexp* re = Regexp::HaveMatch(42, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), 42);
  re->Decref();
}

// Test HaveMatch with zero match_id
TEST_F(RegexpTest_337, HaveMatch_ZeroMatchId_337) {
  Regexp* re = Regexp::HaveMatch(0, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), 0);
  re->Decref();
}

// Test HaveMatch with negative match_id
TEST_F(RegexpTest_337, HaveMatch_NegativeMatchId_337) {
  Regexp* re = Regexp::HaveMatch(-1, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), -1);
  re->Decref();
}

// Test HaveMatch with large match_id
TEST_F(RegexpTest_337, HaveMatch_LargeMatchId_337) {
  Regexp* re = Regexp::HaveMatch(999999, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->match_id(), 999999);
  re->Decref();
}

// Test Parse with a simple literal
TEST_F(RegexpTest_337, Parse_SimpleLiteral_337) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test Parse with empty string
TEST_F(RegexpTest_337, Parse_EmptyString_337) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test Parse with invalid regex
TEST_F(RegexpTest_337, Parse_InvalidRegex_337) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(", Regexp::NoParseFlags, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

// Test Parse with alternation
TEST_F(RegexpTest_337, Parse_Alternation_337) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->op(), kRegexpAlternate);
  re->Decref();
}

// Test Parse with star
TEST_F(RegexpTest_337, Parse_Star_337) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

// Test Parse with plus
TEST_F(RegexpTest_337, Parse_Plus_337) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

// Test Parse with quest
TEST_F(RegexpTest_337, Parse_Quest_337) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a?", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

// Test Parse with capture
TEST_F(RegexpTest_337, Parse_Capture_337) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->op(), kRegexpCapture);
  re->Decref();
}

// Test NumCaptures
TEST_F(RegexpTest_337, NumCaptures_NoCaptures_337) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

// Test NumCaptures with captures
TEST_F(RegexpTest_337, NumCaptures_WithCaptures_337) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// Test NumCaptures with nested captures
TEST_F(RegexpTest_337, NumCaptures_NestedCaptures_337) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((a)(b))", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// Test ToString roundtrip
TEST_F(RegexpTest_337, ToString_SimpleLiteral_337) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test Dump
TEST_F(RegexpTest_337, Dump_BasicRegexp_337) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  std::string dump = re->Dump();
  EXPECT_FALSE(dump.empty());
  re->Decref();
}

// Test NewLiteral
TEST_F(RegexpTest_337, NewLiteral_Basic_337) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'a');
  re->Decref();
}

// Test NewLiteral with Unicode
TEST_F(RegexpTest_337, NewLiteral_Unicode_337) {
  Regexp* re = Regexp::NewLiteral(0x1234, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 0x1234);
  re->Decref();
}

// Test LiteralString
TEST_F(RegexpTest_337, LiteralString_Basic_337) {
  Rune runes[] = {'h', 'e', 'l', 'l', 'o'};
  Regexp* re = Regexp::LiteralString(runes, 5, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 5);
  re->Decref();
}

// Test Star factory
TEST_F(RegexpTest_337, Star_Factory_337) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Star(sub, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

// Test Plus factory
TEST_F(RegexpTest_337, Plus_Factory_337) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Plus(sub, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

// Test Quest factory
TEST_F(RegexpTest_337, Quest_Factory_337) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Quest(sub, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

// Test Concat factory
TEST_F(RegexpTest_337, Concat_Factory_337) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* re = Regexp::Concat(subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Concat with single element
TEST_F(RegexpTest_337, Concat_SingleElement_337) {
  Regexp* subs[1];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Concat(subs, 1, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Concat with zero elements
TEST_F(RegexpTest_337, Concat_ZeroElements_337) {
  Regexp* re = Regexp::Concat(nullptr, 0, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  re->Decref();
}

// Test Alternate factory
TEST_F(RegexpTest_337, Alternate_Factory_337) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* re = Regexp::Alternate(subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Alternate with zero elements
TEST_F(RegexpTest_337, Alternate_ZeroElements_337) {
  Regexp* re = Regexp::Alternate(nullptr, 0, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpNoMatch);
  re->Decref();
}

// Test AlternateNoFactor
TEST_F(RegexpTest_337, AlternateNoFactor_Basic_337) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* re = Regexp::AlternateNoFactor(subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Capture factory
TEST_F(RegexpTest_337, Capture_Factory_337) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Capture(sub, Regexp::NoParseFlags, 1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 1);
  re->Decref();
}

// Test Repeat factory
TEST_F(RegexpTest_337, Repeat_Factory_337) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 2, 5);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), 5);
  re->Decref();
}

// Test Repeat with exact count
TEST_F(RegexpTest_337, Repeat_ExactCount_337) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 3, 3);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 3);
  EXPECT_EQ(re->max(), 3);
  re->Decref();
}

// Test Incref and Decref
TEST_F(RegexpTest_337, IncrefDecref_337) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  Regexp* re2 = re->Incref();
  EXPECT_EQ(re, re2);
  re->Decref();
  re->Decref();
}

// Test Simplify
TEST_F(RegexpTest_337, Simplify_Basic_337) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simple = re->Simplify();
  ASSERT_NE(simple, nullptr);
  simple->Decref();
  re->Decref();
}

// Test SimplifyRegexp static method
TEST_F(RegexpTest_337, SimplifyRegexp_Basic_337) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("a+", Regexp::NoParseFlags, &dst, &status);
  EXPECT_TRUE(result);
  EXPECT_FALSE(dst.empty());
}

// Test SimplifyRegexp with invalid input
TEST_F(RegexpTest_337, SimplifyRegexp_Invalid_337) {
  std::string dst;
  RegexpStatus status;
  bool result = Regexp::SimplifyRegexp("(", Regexp::NoParseFlags, &dst, &status);
  EXPECT_FALSE(result);
}

// Test NamedCaptures with no named captures
TEST_F(RegexpTest_337, NamedCaptures_None_337) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* named = re->NamedCaptures();
  EXPECT_EQ(named, nullptr);
  delete named;
  re->Decref();
}

// Test NamedCaptures with named captures
TEST_F(RegexpTest_337, NamedCaptures_WithNames_337) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<foo>a)(?P<bar>b)", Regexp::PerlX, &status);
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
TEST_F(RegexpTest_337, CaptureNames_WithNames_337) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<foo>a)(?P<bar>b)", Regexp::PerlX, &status);
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
TEST_F(RegexpTest_337, RequiredPrefix_WithPrefix_337) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc.*", Regexp::PerlX, &status);
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

// Test RequiredPrefix without prefix
TEST_F(RegexpTest_337, RequiredPrefix_NoPrefix_337) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".*abc", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase;
  Regexp* suffix = nullptr;
  bool has_prefix = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  EXPECT_FALSE(has_prefix);
  re->Decref();
}

// Test CompileToProg
TEST_F(RegexpTest_337, CompileToProg_Basic_337) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileToReverseProg
TEST_F(RegexpTest_337, CompileToReverseProg_Basic_337) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test parse_flags accessor
TEST_F(RegexpTest_337, ParseFlags_Accessor_337) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->parse_flags(), Regexp::NoParseFlags);
  re->Decref();
}

// Test op accessor
TEST_F(RegexpTest_337, Op_Accessor_337) {
  Regexp* re = Regexp::NewLiteral('x', Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// Test Parse with character class
TEST_F(RegexpTest_337, Parse_CharClass_337) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->op(), kRegexpCharClass);
  re->Decref();
}

// Test Parse with dot (any char)
TEST_F(RegexpTest_337, Parse_AnyChar_337) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test Parse with anchors
TEST_F(RegexpTest_337, Parse_BeginEndLine_337) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^a$", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test Parse with repeat syntax
TEST_F(RegexpTest_337, Parse_Repeat_337) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,5}", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test HaveMatch preserves parse flags
TEST_F(RegexpTest_337, HaveMatch_ParseFlags_337) {
  Regexp* re = Regexp::HaveMatch(10, Regexp::FoldCase);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), 10);
  EXPECT_NE(re->parse_flags() & Regexp::FoldCase, 0);
  re->Decref();
}

// Test NullWalk doesn't crash
TEST_F(RegexpTest_337, NullWalk_NoCrash_337) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a+)(b*)", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  re->NullWalk();
  re->Decref();
}

// Test MimicsPCRE
TEST_F(RegexpTest_337, MimicsPCRE_Simple_337) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  // Simple patterns should mimic PCRE
  bool mimics = re->MimicsPCRE();
  EXPECT_TRUE(mimics);
  re->Decref();
}

// Test sub accessor for concat
TEST_F(RegexpTest_337, Sub_Accessor_337) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("ab", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  if (re->op() == kRegexpConcat || re->op() == kRegexpLiteralString) {
    // Multi-character literal or concat
    if (re->op() == kRegexpConcat) {
      EXPECT_GT(re->nsub(), 0);
      EXPECT_NE(re->sub(), nullptr);
    }
  }
  re->Decref();
}

// Test parse with word boundary
TEST_F(RegexpTest_337, Parse_WordBoundary_337) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\bfoo\\b", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test Alternate with single element
TEST_F(RegexpTest_337, Alternate_SingleElement_337) {
  Regexp* subs[1];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Alternate(subs, 1, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  // Single alternate should be the element itself
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// Test Repeat with unbounded max (use -1 for unlimited)
TEST_F(RegexpTest_337, Repeat_Unbounded_337) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 2, -1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), -1);
  re->Decref();
}

// Test Repeat with zero min and max
TEST_F(RegexpTest_337, Repeat_ZeroZero_337) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 0, 0);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Parse with complex regex
TEST_F(RegexpTest_337, Parse_ComplexRegex_337) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:foo|bar)+baz{2,4}.*", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test RequiredPrefixForAccel
TEST_F(RegexpTest_337, RequiredPrefixForAccel_337) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc.*", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase;
  re->RequiredPrefixForAccel(&prefix, &foldcase);
  // Just ensure no crash; result depends on implementation
  re->Decref();
}

}  // namespace re2
