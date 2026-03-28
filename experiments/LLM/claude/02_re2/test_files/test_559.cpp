#include "gtest/gtest.h"
#include "re2/prefilter.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include <memory>
#include <string>
#include <vector>

namespace re2 {

// Test that Prefilter can be created from a simple literal regex
TEST(PrefilterTest_559, FromReLiteralString_559) {
  Regexp* re = Regexp::Parse("hello", Regexp::DefaultOptions, NULL);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  // A literal string should produce a non-null prefilter
  EXPECT_NE(pf, nullptr);
  delete pf;
  re->Decref();
}

// Test that Prefilter handles alternation
TEST(PrefilterTest_559, FromReAlternation_559) {
  Regexp* re = Regexp::Parse("hello|world", Regexp::DefaultOptions, NULL);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  EXPECT_NE(pf, nullptr);
  delete pf;
  re->Decref();
}

// Test that Prefilter handles dot star (match all)
TEST(PrefilterTest_559, FromReDotStar_559) {
  Regexp* re = Regexp::Parse(".*", Regexp::DefaultOptions, NULL);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  // .* matches everything, prefilter might be ALL or null-like
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
  }
  delete pf;
  re->Decref();
}

// Test that Prefilter handles empty regex
TEST(PrefilterTest_559, FromReEmpty_559) {
  Regexp* re = Regexp::Parse("", Regexp::DefaultOptions, NULL);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  // Empty regex matches everything
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
  }
  delete pf;
  re->Decref();
}

// Test prefilter with Latin1 encoding
TEST(PrefilterTest_559, FromReLatin1_559) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::DefaultOptions | Regexp::Latin1);
  Regexp* re = Regexp::Parse("hello", flags, NULL);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  EXPECT_NE(pf, nullptr);
  delete pf;
  re->Decref();
}

// Test prefilter with character class
TEST(PrefilterTest_559, FromReCharClass_559) {
  Regexp* re = Regexp::Parse("[abc]def", Regexp::DefaultOptions, NULL);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  EXPECT_NE(pf, nullptr);
  delete pf;
  re->Decref();
}

// Test prefilter with repetition
TEST(PrefilterTest_559, FromReRepetition_559) {
  Regexp* re = Regexp::Parse("a{3,5}bc", Regexp::DefaultOptions, NULL);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  EXPECT_NE(pf, nullptr);
  delete pf;
  re->Decref();
}

// Test prefilter with complex regex
TEST(PrefilterTest_559, FromReComplex_559) {
  Regexp* re = Regexp::Parse("(foo|bar).*baz[0-9]+", Regexp::DefaultOptions, NULL);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  EXPECT_NE(pf, nullptr);
  delete pf;
  re->Decref();
}

// Test Prefilter op types for ATOM
TEST(PrefilterTest_559, AtomOp_559) {
  Prefilter* pf = new Prefilter(Prefilter::ATOM);
  EXPECT_EQ(pf->op(), Prefilter::ATOM);
  delete pf;
}

// Test Prefilter op types for ALL
TEST(PrefilterTest_559, AllOp_559) {
  Prefilter* pf = new Prefilter(Prefilter::ALL);
  EXPECT_EQ(pf->op(), Prefilter::ALL);
  delete pf;
}

// Test Prefilter op types for AND
TEST(PrefilterTest_559, AndOp_559) {
  Prefilter* pf = new Prefilter(Prefilter::AND);
  EXPECT_EQ(pf->op(), Prefilter::AND);
  delete pf;
}

// Test Prefilter op types for OR
TEST(PrefilterTest_559, OrOp_559) {
  Prefilter* pf = new Prefilter(Prefilter::OR);
  EXPECT_EQ(pf->op(), Prefilter::OR);
  delete pf;
}

// Test Prefilter DebugString
TEST(PrefilterTest_559, DebugStringAtom_559) {
  Regexp* re = Regexp::Parse("hello", Regexp::DefaultOptions, NULL);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  ASSERT_NE(pf, nullptr);
  std::string debug = pf->DebugString();
  EXPECT_FALSE(debug.empty());
  delete pf;
  re->Decref();
}

// Test prefilter with single character
TEST(PrefilterTest_559, SingleChar_559) {
  Regexp* re = Regexp::Parse("a", Regexp::DefaultOptions, NULL);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  // Single character may or may not produce a useful prefilter
  delete pf;
  re->Decref();
}

// Test prefilter with question mark (optional)
TEST(PrefilterTest_559, OptionalPattern_559) {
  Regexp* re = Regexp::Parse("ab?c", Regexp::DefaultOptions, NULL);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  EXPECT_NE(pf, nullptr);
  delete pf;
  re->Decref();
}

// Test prefilter with plus (one or more)
TEST(PrefilterTest_559, PlusPattern_559) {
  Regexp* re = Regexp::Parse("ab+c", Regexp::DefaultOptions, NULL);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  EXPECT_NE(pf, nullptr);
  delete pf;
  re->Decref();
}

// Test prefilter with case-insensitive flag
TEST(PrefilterTest_559, CaseInsensitive_559) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::DefaultOptions | Regexp::FoldCase);
  Regexp* re = Regexp::Parse("Hello", flags, NULL);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  // Case insensitive should still produce some prefilter
  delete pf;
  re->Decref();
}

}  // namespace re2
