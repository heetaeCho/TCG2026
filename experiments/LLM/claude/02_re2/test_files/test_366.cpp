#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <map>
#include <string>

namespace re2 {

class RegexpCaptureNamesTest_366 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// Test CaptureNames with no captures - should return empty or null map
TEST_F(RegexpCaptureNamesTest_366, NoCaptureNames_366) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  std::map<int, std::string>* names = re->CaptureNames();
  // With no named captures, the map should be null or empty
  if (names != nullptr) {
    EXPECT_TRUE(names->empty());
    delete names;
  }

  re->Decref();
}

// Test CaptureNames with a single named capture
TEST_F(RegexpCaptureNamesTest_366, SingleNamedCapture_366) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<first>abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  std::map<int, std::string>* names = re->CaptureNames();
  ASSERT_NE(names, nullptr);
  EXPECT_EQ(names->size(), 1u);
  EXPECT_EQ((*names)[1], "first");

  delete names;
  re->Decref();
}

// Test CaptureNames with multiple named captures
TEST_F(RegexpCaptureNamesTest_366, MultipleNamedCaptures_366) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<first>abc)(?P<second>def)(?P<third>ghi)",
                             Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  std::map<int, std::string>* names = re->CaptureNames();
  ASSERT_NE(names, nullptr);
  EXPECT_EQ(names->size(), 3u);
  EXPECT_EQ((*names)[1], "first");
  EXPECT_EQ((*names)[2], "second");
  EXPECT_EQ((*names)[3], "third");

  delete names;
  re->Decref();
}

// Test CaptureNames with mixed named and unnamed captures
TEST_F(RegexpCaptureNamesTest_366, MixedNamedAndUnnamedCaptures_366) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc)(?P<named>def)(ghi)",
                             Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  std::map<int, std::string>* names = re->CaptureNames();
  ASSERT_NE(names, nullptr);
  // Only named captures should appear in the map
  EXPECT_EQ(names->count(2), 1u);
  EXPECT_EQ((*names)[2], "named");

  delete names;
  re->Decref();
}

// Test CaptureNames with nested named captures
TEST_F(RegexpCaptureNamesTest_366, NestedNamedCaptures_366) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<outer>(?P<inner>abc)def)",
                             Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  std::map<int, std::string>* names = re->CaptureNames();
  ASSERT_NE(names, nullptr);
  EXPECT_EQ(names->size(), 2u);
  EXPECT_EQ((*names)[1], "outer");
  EXPECT_EQ((*names)[2], "inner");

  delete names;
  re->Decref();
}

// Test CaptureNames with only unnamed captures
TEST_F(RegexpCaptureNamesTest_366, OnlyUnnamedCaptures_366) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc)(def)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  std::map<int, std::string>* names = re->CaptureNames();
  // Unnamed captures should not appear in the map
  if (names != nullptr) {
    EXPECT_TRUE(names->empty());
    delete names;
  }

  re->Decref();
}

// Test NumCaptures for correctness
TEST_F(RegexpCaptureNamesTest_366, NumCaptures_366) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<a>x)(y)(?P<b>z)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  EXPECT_EQ(re->NumCaptures(), 3);

  re->Decref();
}

// Test NamedCaptures returns mapping from name to index
TEST_F(RegexpCaptureNamesTest_366, NamedCaptures_366) {
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

// Test CaptureNames with alternation containing named captures
TEST_F(RegexpCaptureNamesTest_366, AlternationWithNamedCaptures_366) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<left>abc)|(?P<right>def)",
                             Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  std::map<int, std::string>* names = re->CaptureNames();
  ASSERT_NE(names, nullptr);
  EXPECT_EQ(names->size(), 2u);
  EXPECT_EQ((*names)[1], "left");
  EXPECT_EQ((*names)[2], "right");

  delete names;
  re->Decref();
}

// Test CaptureNames with a simple literal (no groups at all)
TEST_F(RegexpCaptureNamesTest_366, SimpleLiteralNoCaptureNames_366) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  std::map<int, std::string>* names = re->CaptureNames();
  if (names != nullptr) {
    EXPECT_TRUE(names->empty());
    delete names;
  }

  re->Decref();
}

// Test CaptureNames with repeated named capture
TEST_F(RegexpCaptureNamesTest_366, RepeatedNamedCapture_366) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<word>\\w+)+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  std::map<int, std::string>* names = re->CaptureNames();
  ASSERT_NE(names, nullptr);
  EXPECT_GE(names->size(), 1u);
  EXPECT_EQ((*names)[1], "word");

  delete names;
  re->Decref();
}

// Test Parse with invalid regex returns null
TEST_F(RegexpCaptureNamesTest_366, InvalidRegexParseReturnsNull_366) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[invalid", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
}

// Test ToString roundtrip
TEST_F(RegexpCaptureNamesTest_366, ToStringBasic_366) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());

  re->Decref();
}

// Test SimplifyRegexp
TEST_F(RegexpCaptureNamesTest_366, SimplifyRegexp_366) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{2,3}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

// Test Dump
TEST_F(RegexpCaptureNamesTest_366, DumpBasic_366) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<name>abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  std::string dump = re->Dump();
  EXPECT_FALSE(dump.empty());

  re->Decref();
}

// Test Incref and Decref don't crash
TEST_F(RegexpCaptureNamesTest_366, IncrefDecref_366) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  Regexp* ref = re->Incref();
  EXPECT_EQ(ref, re);

  ref->Decref();
  re->Decref();
}

// Test NumCaptures with no captures
TEST_F(RegexpCaptureNamesTest_366, NumCapturesZero_366) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  EXPECT_EQ(re->NumCaptures(), 0);

  re->Decref();
}

// Test CaptureNames with complex pattern
TEST_F(RegexpCaptureNamesTest_366, ComplexPatternCaptureNames_366) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(
      "(?P<year>\\d{4})-(?P<month>\\d{2})-(?P<day>\\d{2})",
      Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  std::map<int, std::string>* names = re->CaptureNames();
  ASSERT_NE(names, nullptr);
  EXPECT_EQ(names->size(), 3u);
  EXPECT_EQ((*names)[1], "year");
  EXPECT_EQ((*names)[2], "month");
  EXPECT_EQ((*names)[3], "day");

  delete names;
  re->Decref();
}

}  // namespace re2
