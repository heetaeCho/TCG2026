#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <map>
#include <string>

namespace re2 {

// Test fixture for Regexp tests
class RegexpTest_364 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// Test that CaptureNames returns NULL for a regexp with no captures
TEST_F(RegexpTest_364, CaptureNamesNullForNoCaptures_364) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  std::map<int, std::string>* names = re->CaptureNames();
  EXPECT_EQ(names, nullptr);
  delete names;
  
  re->Decref();
}

// Test that CaptureNames returns NULL for unnamed captures
TEST_F(RegexpTest_364, CaptureNamesNullForUnnamedCaptures_364) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc)(def)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  std::map<int, std::string>* names = re->CaptureNames();
  EXPECT_EQ(names, nullptr);
  delete names;
  
  re->Decref();
}

// Test that CaptureNames returns correct map for a single named capture
TEST_F(RegexpTest_364, CaptureNamesSingleNamedCapture_364) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<foo>abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  std::map<int, std::string>* names = re->CaptureNames();
  ASSERT_NE(names, nullptr);
  EXPECT_EQ(names->size(), 1u);
  EXPECT_EQ((*names)[1], "foo");
  
  delete names;
  re->Decref();
}

// Test that CaptureNames returns correct map for multiple named captures
TEST_F(RegexpTest_364, CaptureNamesMultipleNamedCaptures_364) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<first>abc)(?P<second>def)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  std::map<int, std::string>* names = re->CaptureNames();
  ASSERT_NE(names, nullptr);
  EXPECT_EQ(names->size(), 2u);
  EXPECT_EQ((*names)[1], "first");
  EXPECT_EQ((*names)[2], "second");
  
  delete names;
  re->Decref();
}

// Test that CaptureNames only returns named captures (not unnamed ones)
TEST_F(RegexpTest_364, CaptureNamesMixedNamedAndUnnamed_364) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc)(?P<named>def)(ghi)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  std::map<int, std::string>* names = re->CaptureNames();
  ASSERT_NE(names, nullptr);
  // Only the named capture should appear
  EXPECT_EQ(names->size(), 1u);
  EXPECT_EQ((*names)[2], "named");
  
  delete names;
  re->Decref();
}

// Test NumCaptures counts all captures (named and unnamed)
TEST_F(RegexpTest_364, NumCapturesCountsAll_364) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc)(?P<named>def)(ghi)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  EXPECT_EQ(re->NumCaptures(), 3);
  
  re->Decref();
}

// Test NamedCaptures returns name->index mapping
TEST_F(RegexpTest_364, NamedCapturesMapping_364) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<alpha>a)(?P<beta>b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  std::map<std::string, int>* named = re->NamedCaptures();
  ASSERT_NE(named, nullptr);
  EXPECT_EQ(named->size(), 2u);
  EXPECT_EQ((*named)["alpha"], 1);
  EXPECT_EQ((*named)["beta"], 2);
  
  delete named;
  re->Decref();
}

// Test NamedCaptures returns NULL when there are no named captures
TEST_F(RegexpTest_364, NamedCapturesNullWhenNone_364) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  std::map<std::string, int>* named = re->NamedCaptures();
  EXPECT_EQ(named, nullptr);
  delete named;
  
  re->Decref();
}

// Test CaptureNames with nested named captures
TEST_F(RegexpTest_364, CaptureNamesNestedCaptures_364) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<outer>(?P<inner>abc))", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  std::map<int, std::string>* names = re->CaptureNames();
  ASSERT_NE(names, nullptr);
  EXPECT_EQ(names->size(), 2u);
  EXPECT_EQ((*names)[1], "outer");
  EXPECT_EQ((*names)[2], "inner");
  
  delete names;
  re->Decref();
}

// Test CaptureNames with empty pattern (no captures)
TEST_F(RegexpTest_364, CaptureNamesEmptyPattern_364) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  std::map<int, std::string>* names = re->CaptureNames();
  EXPECT_EQ(names, nullptr);
  delete names;
  
  re->Decref();
}

// Test Parse returns a valid regexp and basic ops
TEST_F(RegexpTest_364, ParseSimpleRegexp_364) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  
  re->Decref();
}

// Test Parse of alternation
TEST_F(RegexpTest_364, ParseAlternation_364) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpAlternate);
  
  re->Decref();
}

// Test Parse of concatenation
TEST_F(RegexpTest_364, ParseConcat_364) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("ab", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  
  re->Decref();
}

// Test Parse of star
TEST_F(RegexpTest_364, ParseStar_364) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  
  re->Decref();
}

// Test Parse of plus
TEST_F(RegexpTest_364, ParsePlus_364) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  
  re->Decref();
}

// Test Parse of quest
TEST_F(RegexpTest_364, ParseQuest_364) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  
  re->Decref();
}

// Test ToString roundtrip
TEST_F(RegexpTest_364, ToStringRoundtrip_364) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<name>abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  
  re->Decref();
}

// Test Dump produces non-empty output
TEST_F(RegexpTest_364, DumpProducesOutput_364) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<x>a+)b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  std::string d = re->Dump();
  EXPECT_FALSE(d.empty());
  
  re->Decref();
}

// Test NumCaptures with no captures
TEST_F(RegexpTest_364, NumCapturesZero_364) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  EXPECT_EQ(re->NumCaptures(), 0);
  
  re->Decref();
}

// Test NumCaptures with one capture
TEST_F(RegexpTest_364, NumCapturesOne_364) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  EXPECT_EQ(re->NumCaptures(), 1);
  
  re->Decref();
}

// Test Simplify returns a valid regexp
TEST_F(RegexpTest_364, SimplifyReturnsValid_364) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  
  simplified->Decref();
  re->Decref();
}

// Test SimplifyRegexp static method
TEST_F(RegexpTest_364, SimplifyRegexpStatic_364) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{2,5}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

// Test CaptureNames with complex pattern involving alternation and named captures
TEST_F(RegexpTest_364, CaptureNamesComplexPattern_364) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<a>x)|(?P<b>y)|(?P<c>z)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  std::map<int, std::string>* names = re->CaptureNames();
  ASSERT_NE(names, nullptr);
  EXPECT_EQ(names->size(), 3u);
  EXPECT_EQ((*names)[1], "a");
  EXPECT_EQ((*names)[2], "b");
  EXPECT_EQ((*names)[3], "c");
  
  delete names;
  re->Decref();
}

// Test HaveMatch factory
TEST_F(RegexpTest_364, HaveMatchFactory_364) {
  Regexp* re = Regexp::HaveMatch(42, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), 42);
  
  re->Decref();
}

// Test NewLiteral factory
TEST_F(RegexpTest_364, NewLiteralFactory_364) {
  Regexp* re = Regexp::NewLiteral('A', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'A');
  
  re->Decref();
}

// Test Capture factory
TEST_F(RegexpTest_364, CaptureFactory_364) {
  Regexp* sub = Regexp::NewLiteral('x', Regexp::LikePerl);
  ASSERT_NE(sub, nullptr);
  
  Regexp* cap = Regexp::Capture(sub, Regexp::LikePerl, 5);
  ASSERT_NE(cap, nullptr);
  EXPECT_EQ(cap->op(), kRegexpCapture);
  EXPECT_EQ(cap->cap(), 5);
  
  cap->Decref();
}

// Test Star factory
TEST_F(RegexpTest_364, StarFactory_364) {
  Regexp* sub = Regexp::NewLiteral('y', Regexp::LikePerl);
  ASSERT_NE(sub, nullptr);
  
  Regexp* star = Regexp::Star(sub, Regexp::LikePerl);
  ASSERT_NE(star, nullptr);
  EXPECT_EQ(star->op(), kRegexpStar);
  
  star->Decref();
}

// Test Plus factory
TEST_F(RegexpTest_364, PlusFactory_364) {
  Regexp* sub = Regexp::NewLiteral('z', Regexp::LikePerl);
  ASSERT_NE(sub, nullptr);
  
  Regexp* plus = Regexp::Plus(sub, Regexp::LikePerl);
  ASSERT_NE(plus, nullptr);
  EXPECT_EQ(plus->op(), kRegexpPlus);
  
  plus->Decref();
}

// Test Quest factory
TEST_F(RegexpTest_364, QuestFactory_364) {
  Regexp* sub = Regexp::NewLiteral('w', Regexp::LikePerl);
  ASSERT_NE(sub, nullptr);
  
  Regexp* quest = Regexp::Quest(sub, Regexp::LikePerl);
  ASSERT_NE(quest, nullptr);
  EXPECT_EQ(quest->op(), kRegexpQuest);
  
  quest->Decref();
}

// Test LiteralString factory
TEST_F(RegexpTest_364, LiteralStringFactory_364) {
  Rune runes[] = {'h', 'e', 'l', 'l', 'o'};
  Regexp* re = Regexp::LiteralString(runes, 5, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 5);
  
  re->Decref();
}

// Test RequiredPrefix
TEST_F(RegexpTest_364, RequiredPrefixSimple_364) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^hello.*", Regexp::LikePerl, &status);
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

// Test Incref/Decref reference counting
TEST_F(RegexpTest_364, IncrefDecref_364) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  
  Regexp* re2 = re->Incref();
  EXPECT_EQ(re, re2);
  
  // Decref twice since we incref'd once
  re->Decref();
  re->Decref();
}

}  // namespace re2
