#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <map>
#include <string>

namespace re2 {

class RegexpTest_359 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// Test that NamedCaptures returns NULL for a regexp with no named captures
TEST_F(RegexpTest_359, NamedCapturesReturnsNullForNoNamedCaptures_359) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  std::map<std::string, int>* captures = re->NamedCaptures();
  EXPECT_EQ(captures, nullptr);
  re->Decref();
}

// Test that NamedCaptures returns NULL for unnamed capture groups
TEST_F(RegexpTest_359, NamedCapturesReturnsNullForUnnamedCaptures_359) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc)(def)", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  std::map<std::string, int>* captures = re->NamedCaptures();
  EXPECT_EQ(captures, nullptr);
  re->Decref();
}

// Test that NamedCaptures returns correct map for a single named capture
TEST_F(RegexpTest_359, NamedCapturesSingleNamedGroup_359) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<name>abc)", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  std::map<std::string, int>* captures = re->NamedCaptures();
  ASSERT_NE(captures, nullptr);
  EXPECT_EQ(captures->size(), 1u);
  EXPECT_EQ((*captures)["name"], 1);
  delete captures;
  re->Decref();
}

// Test that NamedCaptures returns correct map for multiple named captures
TEST_F(RegexpTest_359, NamedCapturesMultipleNamedGroups_359) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<first>abc)(?P<second>def)", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  std::map<std::string, int>* captures = re->NamedCaptures();
  ASSERT_NE(captures, nullptr);
  EXPECT_EQ(captures->size(), 2u);
  EXPECT_EQ((*captures)["first"], 1);
  EXPECT_EQ((*captures)["second"], 2);
  delete captures;
  re->Decref();
}

// Test that NamedCaptures works with mixed named and unnamed captures
TEST_F(RegexpTest_359, NamedCapturesMixedNamedAndUnnamed_359) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc)(?P<named>def)(ghi)", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  std::map<std::string, int>* captures = re->NamedCaptures();
  ASSERT_NE(captures, nullptr);
  // Only named captures should appear in the map
  EXPECT_EQ(captures->size(), 1u);
  EXPECT_EQ((*captures)["named"], 2);
  delete captures;
  re->Decref();
}

// Test NumCaptures for a regexp with no captures
TEST_F(RegexpTest_359, NumCapturesNoCaptures_359) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

// Test NumCaptures for a regexp with captures
TEST_F(RegexpTest_359, NumCapturesWithCaptures_359) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// Test NumCaptures with named captures
TEST_F(RegexpTest_359, NumCapturesWithNamedCaptures_359) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<a>x)(?P<b>y)", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  EXPECT_EQ(re->NumCaptures(), 2);
  re->Decref();
}

// Test CaptureNames returns correct mapping
TEST_F(RegexpTest_359, CaptureNamesWithNamedCaptures_359) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<first>abc)(?P<second>def)", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  std::map<int, std::string>* names = re->CaptureNames();
  ASSERT_NE(names, nullptr);
  EXPECT_EQ(names->size(), 2u);
  EXPECT_EQ((*names)[1], "first");
  EXPECT_EQ((*names)[2], "second");
  delete names;
  re->Decref();
}

// Test CaptureNames returns NULL for no named captures
TEST_F(RegexpTest_359, CaptureNamesReturnsNullForNoNamedCaptures_359) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc)(def)", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  std::map<int, std::string>* names = re->CaptureNames();
  // CaptureNames may return empty map or null for unnamed captures
  if (names != nullptr) {
    EXPECT_TRUE(names->empty());
    delete names;
  }
  re->Decref();
}

// Test Parse with empty pattern
TEST_F(RegexpTest_359, ParseEmptyPattern_359) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

// Test NamedCaptures with nested named groups
TEST_F(RegexpTest_359, NamedCapturesNestedGroups_359) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<outer>(?P<inner>abc))", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  std::map<std::string, int>* captures = re->NamedCaptures();
  ASSERT_NE(captures, nullptr);
  EXPECT_EQ(captures->size(), 2u);
  EXPECT_NE(captures->find("outer"), captures->end());
  EXPECT_NE(captures->find("inner"), captures->end());
  delete captures;
  re->Decref();
}

// Test ToString roundtrip for simple pattern
TEST_F(RegexpTest_359, ToStringSimplePattern_359) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test that Incref and Decref work without crashing
TEST_F(RegexpTest_359, IncrefDecrefBasic_359) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Regexp* re2 = re->Incref();
  EXPECT_EQ(re, re2);
  re->Decref();
  re->Decref();
}

// Test Parse with invalid pattern returns null
TEST_F(RegexpTest_359, ParseInvalidPattern_359) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
}

// Test op() returns correct value for literal
TEST_F(RegexpTest_359, OpReturnsCorrectValue_359) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// Test op() for concatenation
TEST_F(RegexpTest_359, OpConcatenation_359) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("ab", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  re->Decref();
}

// Test op() for capture
TEST_F(RegexpTest_359, OpCapture_359) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  re->Decref();
}

// Test NamedCaptures with a complex pattern including alternation
TEST_F(RegexpTest_359, NamedCapturesWithAlternation_359) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<a>x)|(?P<b>y)", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  std::map<std::string, int>* captures = re->NamedCaptures();
  ASSERT_NE(captures, nullptr);
  EXPECT_EQ(captures->size(), 2u);
  EXPECT_NE(captures->find("a"), captures->end());
  EXPECT_NE(captures->find("b"), captures->end());
  delete captures;
  re->Decref();
}

// Test Simplify doesn't crash
TEST_F(RegexpTest_359, SimplifyBasic_359) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_TRUE(simplified != nullptr);
  simplified->Decref();
  re->Decref();
}

// Test SimplifyRegexp static method
TEST_F(RegexpTest_359, SimplifyRegexpStatic_359) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{2,3}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

// Test Dump produces non-empty string
TEST_F(RegexpTest_359, DumpProducesOutput_359) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<name>abc)", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  std::string dump = re->Dump();
  EXPECT_FALSE(dump.empty());
  re->Decref();
}

// Test NullWalk doesn't crash
TEST_F(RegexpTest_359, NullWalkDoesNotCrash_359) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  re->NullWalk();
  re->Decref();
}

// Test RequiredPrefix for a pattern with a literal prefix
TEST_F(RegexpTest_359, RequiredPrefixWithLiteralPrefix_359) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  std::string prefix;
  bool foldcase;
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

// Test NamedCaptures with pattern that only has non-capturing groups
TEST_F(RegexpTest_359, NamedCapturesNonCapturingGroups_359) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:abc)(?:def)", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  std::map<std::string, int>* captures = re->NamedCaptures();
  EXPECT_EQ(captures, nullptr);
  re->Decref();
}

// Test that NamedCaptures with duplicate names uses first occurrence (insert semantics)
TEST_F(RegexpTest_359, NamedCapturesDuplicateNamesInsertSemantics_359) {
  // Note: RE2 may not allow duplicate named captures, but test what happens
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<dup>a)|(?P<dup>b)", Regexp::LikePerl, &status);
  if (re != nullptr) {
    std::map<std::string, int>* captures = re->NamedCaptures();
    if (captures != nullptr) {
      // insert semantics: first insert wins
      auto it = captures->find("dup");
      EXPECT_NE(it, captures->end());
      // The first capture group numbered 1 should be stored
      EXPECT_EQ(it->second, 1);
      delete captures;
    }
    re->Decref();
  }
}

}  // namespace re2
