// File: ./TestProjects/re2/re2/tests/prefilter_lengththenlex_test.cc
#include "gtest/gtest.h"
#include <algorithm>
#include <string>
#include <vector>

#include "TestProjects/re2/re2/prefilter.h"

namespace {

using re2::Prefilter;

TEST(Prefilter_LengthThenLex_467, ShorterStringComesBefore_467) {
  Prefilter::LengthThenLex comp;
  EXPECT_TRUE(comp("a", "bb"));
  EXPECT_FALSE(comp("bb", "a"));
}

TEST(Prefilter_LengthThenLex_467, EqualLengthLexicographicOrder_467) {
  Prefilter::LengthThenLex comp;
  EXPECT_TRUE(comp("ab", "ac"));
  EXPECT_FALSE(comp("ac", "ab"));
}

TEST(Prefilter_LengthThenLex_467, EqualStringsReturnsFalse_467) {
  Prefilter::LengthThenLex comp;
  EXPECT_FALSE(comp("hi", "hi"));
}

TEST(Prefilter_LengthThenLex_467, EmptyStringBoundary_467) {
  Prefilter::LengthThenLex comp;
  EXPECT_TRUE(comp("", "a"));   // empty is shorter
  EXPECT_FALSE(comp("a", ""));  // reverse
  EXPECT_FALSE(comp("", ""));   // equal strings -> not less
}

TEST(Prefilter_LengthThenLex_467, SortVectorProducesExpectedOrder_467) {
  Prefilter::LengthThenLex comp;
  std::vector<std::string> v = {"bbb", "a", "aa", "ab", "", "aa"};
  std::sort(v.begin(), v.end(), comp);
  std::vector<std::string> expected = {"", "a", "aa", "aa", "ab", "bbb"};
  EXPECT_EQ(v, expected);
}

TEST(Prefilter_LengthThenLex_467, StrictWeakOrderingTransitivity_467) {
  Prefilter::LengthThenLex comp;
  const std::string a = "";
  const std::string b = "a";
  const std::string c = "aa";
  ASSERT_TRUE(comp(a, b));
  ASSERT_TRUE(comp(b, c));
  EXPECT_TRUE(comp(a, c));  // transitive: a < b < c implies a < c
}

TEST(Prefilter_LengthThenLex_467, CaseSensitivityWhenLengthsEqual_467) {
  Prefilter::LengthThenLex comp;
  // Standard std::string lexical compare is case-sensitive ('A' < 'a')
  EXPECT_TRUE(comp("A", "a"));
  EXPECT_FALSE(comp("a", "A"));
}

TEST(Prefilter_LengthThenLex_467, VeryLongEqualLengthLexicographicOrder_467) {
  Prefilter::LengthThenLex comp;
  std::string x(1000, 'x');                // "xxxx...x" (1000)
  std::string y = x; y.back() = 'y';       // same length, differs at last char
  EXPECT_TRUE(comp(x, y));                 // 'x' < 'y'
  EXPECT_FALSE(comp(y, x));
}

}  // namespace
