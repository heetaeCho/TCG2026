#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include "absl/strings/string_view.h"

namespace re2 {

// Test fixture for ParseState tests
class ParseStateTest_501 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// Test fixture for Regexp tests
class RegexpTest_501 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// =============================================================================
// Tests for Regexp::Parse
// =============================================================================

TEST_F(RegexpTest_501, ParseSimpleLiteral_501) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST_F(RegexpTest_501, ParseEmptyString_501) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST_F(RegexpTest_501, ParseInvalidRegexp_501) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

TEST_F(RegexpTest_501, ParseUnmatchedRightParen_501) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(")", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

TEST_F(RegexpTest_501, ParseWithCapture_501) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->NumCaptures(), 2);
  re->Decref();
}

TEST_F(RegexpTest_501, ParseNamedCapture_501) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<name>abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->NumCaptures(), 1);
  
  std::map<std::string, int>* named = re->NamedCaptures();
  ASSERT_NE(named, nullptr);
  EXPECT_EQ(named->count("name"), 1);
  EXPECT_EQ((*named)["name"], 1);
  delete named;
  
  re->Decref();
}

TEST_F(RegexpTest_501, ParseMultipleNamedCaptures_501) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<first>a)(?P<second>b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->NumCaptures(), 2);
  
  std::map<std::string, int>* named = re->NamedCaptures();
  ASSERT_NE(named, nullptr);
  EXPECT_EQ(named->size(), 2);
  EXPECT_EQ((*named)["first"], 1);
  EXPECT_EQ((*named)["second"], 2);
  delete named;
  
  re->Decref();
}

TEST_F(RegexpTest_501, ParseCaptureNames_501) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<hello>a)(b)(?P<world>c)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->NumCaptures(), 3);
  
  std::map<int, std::string>* capnames = re->CaptureNames();
  ASSERT_NE(capnames, nullptr);
  EXPECT_EQ((*capnames)[1], "hello");
  EXPECT_EQ((*capnames)[3], "world");
  delete capnames;
  
  re->Decref();
}

TEST_F(RegexpTest_501, ParseAlternation_501) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b|c", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST_F(RegexpTest_501, ParseRepetition_501) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST_F(RegexpTest_501, ParseStar_501) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST_F(RegexpTest_501, ParsePlus_501) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST_F(RegexpTest_501, ParseQuestion_501) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST_F(RegexpTest_501, ParseCharClass_501) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST_F(RegexpTest_501, ParseNegatedCharClass_501) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[^a-z]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST_F(RegexpTest_501, ParseDot_501) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST_F(RegexpTest_501, ParseAnchorCaret_501) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST_F(RegexpTest_501, ParseAnchorDollar_501) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc$", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST_F(RegexpTest_501, ParseWordBoundary_501) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\babc\\b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST_F(RegexpTest_501, ParseNonCapturingGroup_501) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

TEST_F(RegexpTest_501, ParseNestedCaptures_501) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((a)(b))", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// =============================================================================
// Tests for Regexp::ToString and Dump
// =============================================================================

TEST_F(RegexpTest_501, ToStringSimple_501) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

TEST_F(RegexpTest_501, DumpSimple_501) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string d = re->Dump();
  EXPECT_FALSE(d.empty());
  re->Decref();
}

// =============================================================================
// Tests for Regexp::Simplify
// =============================================================================

TEST_F(RegexpTest_501, SimplifyBasic_501) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

TEST_F(RegexpTest_501, SimplifyRegexpStatic_501) {
  RegexpStatus status;
  std::string dst;
  bool ok = Regexp::SimplifyRegexp("a{2,5}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

// =============================================================================
// Tests for Regexp Ref counting
// =============================================================================

TEST_F(RegexpTest_501, IncrefDecref_501) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_GE(re->Ref(), 1);
  
  Regexp* re2 = re->Incref();
  EXPECT_EQ(re, re2);
  EXPECT_GE(re->Ref(), 2);
  
  re->Decref();
  re2->Decref();
}

// =============================================================================
// Tests for static factory methods
// =============================================================================

TEST_F(RegexpTest_501, NewLiteral_501) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->rune(), 'a');
  re->Decref();
}

TEST_F(RegexpTest_501, HaveMatch_501) {
  Regexp* re = Regexp::HaveMatch(42, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->match_id(), 42);
  re->Decref();
}

TEST_F(RegexpTest_501, LiteralStringFactory_501) {
  Rune runes[] = {'h', 'e', 'l', 'l', 'o'};
  Regexp* re = Regexp::LiteralString(runes, 5, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->nrunes(), 5);
  re->Decref();
}

TEST_F(RegexpTest_501, CaptureFactory_501) {
  Regexp* sub = Regexp::NewLiteral('x', Regexp::LikePerl);
  Regexp* re = Regexp::Capture(sub, Regexp::LikePerl, 1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->cap(), 1);
  re->Decref();
}

TEST_F(RegexpTest_501, PlusFactory_501) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Plus(sub, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_501, StarFactory_501) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Star(sub, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_501, QuestFactory_501) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Quest(sub, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_501, RepeatFactory_501) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Repeat(sub, Regexp::LikePerl, 2, 5);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), 5);
  re->Decref();
}

TEST_F(RegexpTest_501, ConcatFactory_501) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  Regexp* re = Regexp::Concat(subs, 2, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_501, AlternateFactory_501) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  Regexp* re = Regexp::Alternate(subs, 2, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_501, AlternateNoFactorFactory_501) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  Regexp* re = Regexp::AlternateNoFactor(subs, 2, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// =============================================================================
// Tests for NumCaptures
// =============================================================================

TEST_F(RegexpTest_501, NumCapturesZero_501) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

TEST_F(RegexpTest_501, NumCapturesOne_501) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 1);
  re->Decref();
}

TEST_F(RegexpTest_501, NumCapturesMultiple_501) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)(c)(d)(e)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 5);
  re->Decref();
}

// =============================================================================
// Tests for RequiredPrefix
// =============================================================================

TEST_F(RegexpTest_501, RequiredPrefixSimple_501) {
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

TEST_F(RegexpTest_501, RequiredPrefixNone_501) {
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

// =============================================================================
// Tests for CompileToProg
// =============================================================================

TEST_F(RegexpTest_501, CompileToProgSimple_501) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

TEST_F(RegexpTest_501, CompileToReverseProgSimple_501) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// =============================================================================
// Tests for MimicsPCRE
// =============================================================================

TEST_F(RegexpTest_501, MimicsPCRESimple_501) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // Simple literal should mimic PCRE
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// =============================================================================
// Tests for NullWalk
// =============================================================================

TEST_F(RegexpTest_501, NullWalkDoesNotCrash_501) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // Should not crash
  re->NullWalk();
  re->Decref();
}

// =============================================================================
// Tests for parse_flags and op accessors
// =============================================================================

TEST_F(RegexpTest_501, ParseFlagsAccessor_501) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  // Flags should match what was set
  EXPECT_EQ(re->parse_flags(), Regexp::LikePerl);
  re->Decref();
}

// =============================================================================
// Tests for complex patterns via Parse
// =============================================================================

TEST_F(RegexpTest_501, ParseComplexPattern_501) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:a|b)*c+[d-f]{2,4}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

TEST_F(RegexpTest_501, ParseEscapedCharacters_501) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\d+\\.\\w+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST_F(RegexpTest_501, ParseBadRepetition_501) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("*", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

TEST_F(RegexpTest_501, ParseBadBracket_501) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

TEST_F(RegexpTest_501, ParseUnicodeCharClass_501) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\p{Greek}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// =============================================================================
// Test NamedCaptures with no captures
// =============================================================================

TEST_F(RegexpTest_501, NamedCapturesNone_501) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* named = re->NamedCaptures();
  EXPECT_EQ(named, nullptr);
  delete named;
  re->Decref();
}

TEST_F(RegexpTest_501, CaptureNamesNone_501) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<int, std::string>* capnames = re->CaptureNames();
  // With no named captures, might return nullptr or empty
  if (capnames != nullptr) {
    EXPECT_TRUE(capnames->empty());
  }
  delete capnames;
  re->Decref();
}

// =============================================================================
// Test NamedCaptures with unnamed captures only
// =============================================================================

TEST_F(RegexpTest_501, NamedCapturesWithUnnamedOnly_501) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* named = re->NamedCaptures();
  // No named captures, should be nullptr
  EXPECT_EQ(named, nullptr);
  delete named;
  re->Decref();
}

// =============================================================================
// Test Concat and Alternate with single element
// =============================================================================

TEST_F(RegexpTest_501, ConcatSingle_501) {
  Regexp* subs[1];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Concat(subs, 1, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpTest_501, AlternateSingle_501) {
  Regexp* subs[1];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Alternate(subs, 1, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// =============================================================================
// Test POSIX flags
// =============================================================================

TEST_F(RegexpTest_501, ParsePOSIXFlags_501) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// =============================================================================
// Test ToString roundtrip
// =============================================================================

TEST_F(RegexpTest_501, ToStringRoundtrip_501) {
  RegexpStatus status;
  Regexp* re1 = Regexp::Parse("a|b", Regexp::LikePerl, &status);
  ASSERT_NE(re1, nullptr);
  std::string s = re1->ToString();
  
  Regexp* re2 = Regexp::Parse(s, Regexp::LikePerl, &status);
  ASSERT_NE(re2, nullptr);
  EXPECT_TRUE(status.ok());
  
  re1->Decref();
  re2->Decref();
}

// =============================================================================
// Test RequiredPrefixForAccel
// =============================================================================

TEST_F(RegexpTest_501, RequiredPrefixForAccel_501) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^hello.*world", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  std::string prefix;
  bool foldcase = false;
  bool has = re->RequiredPrefixForAccel(&prefix, &foldcase);
  if (has) {
    EXPECT_FALSE(prefix.empty());
  }
  re->Decref();
}

// =============================================================================
// Test case insensitive parsing
// =============================================================================

TEST_F(RegexpTest_501, ParseCaseInsensitive_501) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?i)abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// =============================================================================
// Test simple accessor
// =============================================================================

TEST_F(RegexpTest_501, SimpleAccessor_501) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  // simple() should be a bool
  bool s = re->simple();
  (void)s;  // just making sure it doesn't crash
  re->Decref();
}

}  // namespace re2
