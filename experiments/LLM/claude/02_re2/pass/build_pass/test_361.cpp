#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <map>
#include <string>

namespace re2 {

class NamedCapturesTest_361 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// Test that a regex with no named captures returns NULL
TEST_F(NamedCapturesTest_361, NoNamedCaptures_ReturnsNull_361) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  std::map<std::string, int>* captures = re->NamedCaptures();
  EXPECT_EQ(captures, nullptr);

  re->Decref();
}

// Test that a regex with one named capture returns a map with one entry
TEST_F(NamedCapturesTest_361, SingleNamedCapture_361) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<name>abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  std::map<std::string, int>* captures = re->NamedCaptures();
  ASSERT_NE(captures, nullptr);
  EXPECT_EQ(captures->size(), 1u);
  EXPECT_EQ((*captures)["name"], 1);

  delete captures;
  re->Decref();
}

// Test that a regex with multiple named captures returns all of them
TEST_F(NamedCapturesTest_361, MultipleNamedCaptures_361) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<first>a)(?P<second>b)(?P<third>c)",
                             Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  std::map<std::string, int>* captures = re->NamedCaptures();
  ASSERT_NE(captures, nullptr);
  EXPECT_EQ(captures->size(), 3u);
  EXPECT_EQ((*captures)["first"], 1);
  EXPECT_EQ((*captures)["second"], 2);
  EXPECT_EQ((*captures)["third"], 3);

  delete captures;
  re->Decref();
}

// Test that unnamed captures do not appear in NamedCaptures
TEST_F(NamedCapturesTest_361, MixedNamedAndUnnamedCaptures_361) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(?P<name>b)(c)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  std::map<std::string, int>* captures = re->NamedCaptures();
  ASSERT_NE(captures, nullptr);
  EXPECT_EQ(captures->size(), 1u);
  EXPECT_EQ((*captures)["name"], 2);

  delete captures;
  re->Decref();
}

// Test that only unnamed captures returns NULL
TEST_F(NamedCapturesTest_361, OnlyUnnamedCaptures_ReturnsNull_361) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  std::map<std::string, int>* captures = re->NamedCaptures();
  EXPECT_EQ(captures, nullptr);

  re->Decref();
}

// Test a regex with no captures at all
TEST_F(NamedCapturesTest_361, NoCapturesAtAll_ReturnsNull_361) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc|def", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  std::map<std::string, int>* captures = re->NamedCaptures();
  EXPECT_EQ(captures, nullptr);

  re->Decref();
}

// Test named capture with nested groups
TEST_F(NamedCapturesTest_361, NestedNamedCaptures_361) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<outer>a(?P<inner>b)c)",
                             Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  std::map<std::string, int>* captures = re->NamedCaptures();
  ASSERT_NE(captures, nullptr);
  EXPECT_EQ(captures->size(), 2u);
  EXPECT_EQ((*captures)["outer"], 1);
  EXPECT_EQ((*captures)["inner"], 2);

  delete captures;
  re->Decref();
}

// Test NumCaptures for a simple pattern
TEST_F(NamedCapturesTest_361, NumCaptures_NoCaptures_361) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  EXPECT_EQ(re->NumCaptures(), 0);

  re->Decref();
}

// Test NumCaptures with captures
TEST_F(NamedCapturesTest_361, NumCaptures_WithCaptures_361) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)(?P<c>c)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  EXPECT_EQ(re->NumCaptures(), 3);

  re->Decref();
}

// Test CaptureNames
TEST_F(NamedCapturesTest_361, CaptureNames_MixedCaptures_361) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(?P<name>b)(c)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  std::map<int, std::string>* names = re->CaptureNames();
  ASSERT_NE(names, nullptr);
  // Capture 2 should be named "name"
  auto it = names->find(2);
  ASSERT_NE(it, names->end());
  EXPECT_EQ(it->second, "name");

  delete names;
  re->Decref();
}

// Test CaptureNames returns NULL when no captures
TEST_F(NamedCapturesTest_361, CaptureNames_NoCaptures_361) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  std::map<int, std::string>* names = re->CaptureNames();
  EXPECT_EQ(names, nullptr);

  re->Decref();
}

// Test with alternation containing named captures
TEST_F(NamedCapturesTest_361, NamedCapturesInAlternation_361) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<a>x)|(?P<b>y)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  std::map<std::string, int>* captures = re->NamedCaptures();
  ASSERT_NE(captures, nullptr);
  EXPECT_EQ(captures->size(), 2u);
  EXPECT_EQ((*captures)["a"], 1);
  EXPECT_EQ((*captures)["b"], 2);

  delete captures;
  re->Decref();
}

// Test empty regex
TEST_F(NamedCapturesTest_361, EmptyRegex_361) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  std::map<std::string, int>* captures = re->NamedCaptures();
  EXPECT_EQ(captures, nullptr);

  re->Decref();
}

// Test named capture with complex pattern
TEST_F(NamedCapturesTest_361, ComplexPattern_361) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<year>\\d{4})-(?P<month>\\d{2})-(?P<day>\\d{2})",
                             Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  std::map<std::string, int>* captures = re->NamedCaptures();
  ASSERT_NE(captures, nullptr);
  EXPECT_EQ(captures->size(), 3u);
  EXPECT_EQ((*captures)["year"], 1);
  EXPECT_EQ((*captures)["month"], 2);
  EXPECT_EQ((*captures)["day"], 3);

  delete captures;
  re->Decref();
}

// Test ToString roundtrip
TEST_F(NamedCapturesTest_361, ToString_361) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<name>abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());

  re->Decref();
}

// Test Simplify
TEST_F(NamedCapturesTest_361, Simplify_PreservesNamedCaptures_361) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<name>a+)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);

  std::map<std::string, int>* captures = simplified->NamedCaptures();
  ASSERT_NE(captures, nullptr);
  EXPECT_EQ(captures->size(), 1u);
  EXPECT_EQ((*captures)["name"], 1);

  delete captures;
  simplified->Decref();
  re->Decref();
}

// Test SimplifyRegexp static method
TEST_F(NamedCapturesTest_361, SimplifyRegexp_361) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a+", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

// Test Parse with invalid regex
TEST_F(NamedCapturesTest_361, ParseInvalidRegex_361) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<>abc)", Regexp::LikePerl, &status);
  // An empty name should cause a parse error
  EXPECT_EQ(re, nullptr);
}

// Test single literal character
TEST_F(NamedCapturesTest_361, SingleLiteral_NoCaptures_361) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  EXPECT_EQ(re->NumCaptures(), 0);
  EXPECT_EQ(re->NamedCaptures(), nullptr);

  re->Decref();
}

}  // namespace re2
