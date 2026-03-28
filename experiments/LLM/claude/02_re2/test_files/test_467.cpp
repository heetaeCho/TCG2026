#include "gtest/gtest.h"
#include "re2/prefilter.h"
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using re2::Prefilter;

class LengthThenLexTest_467 : public ::testing::Test {
 protected:
  Prefilter::LengthThenLex cmp;
};

// Test that shorter string is less than longer string
TEST_F(LengthThenLexTest_467, ShorterStringIsLess_467) {
  EXPECT_TRUE(cmp("a", "bb"));
  EXPECT_TRUE(cmp("ab", "abc"));
  EXPECT_TRUE(cmp("", "a"));
}

// Test that longer string is not less than shorter string
TEST_F(LengthThenLexTest_467, LongerStringIsNotLess_467) {
  EXPECT_FALSE(cmp("bb", "a"));
  EXPECT_FALSE(cmp("abc", "ab"));
  EXPECT_FALSE(cmp("a", ""));
}

// Test that equal-length strings are compared lexicographically
TEST_F(LengthThenLexTest_467, SameLengthLexicographic_467) {
  EXPECT_TRUE(cmp("a", "b"));
  EXPECT_FALSE(cmp("b", "a"));
  EXPECT_TRUE(cmp("abc", "abd"));
  EXPECT_FALSE(cmp("abd", "abc"));
}

// Test that identical strings return false (strict weak ordering)
TEST_F(LengthThenLexTest_467, IdenticalStringsReturnFalse_467) {
  EXPECT_FALSE(cmp("abc", "abc"));
  EXPECT_FALSE(cmp("", ""));
  EXPECT_FALSE(cmp("x", "x"));
}

// Test empty strings
TEST_F(LengthThenLexTest_467, EmptyStrings_467) {
  EXPECT_FALSE(cmp("", ""));
  EXPECT_TRUE(cmp("", "a"));
  EXPECT_FALSE(cmp("a", ""));
}

// Test single character strings of same length
TEST_F(LengthThenLexTest_467, SingleCharSameLength_467) {
  EXPECT_TRUE(cmp("a", "z"));
  EXPECT_FALSE(cmp("z", "a"));
  EXPECT_FALSE(cmp("m", "m"));
}

// Test that length takes priority over lexicographic order
TEST_F(LengthThenLexTest_467, LengthPriorityOverLex_467) {
  // "z" is lexicographically greater than "aa", but shorter
  EXPECT_TRUE(cmp("z", "aa"));
  // "aa" is longer than "z", so not less
  EXPECT_FALSE(cmp("aa", "z"));
}

// Test with strings that have common prefixes but different lengths
TEST_F(LengthThenLexTest_467, CommonPrefixDifferentLength_467) {
  EXPECT_TRUE(cmp("ab", "abc"));
  EXPECT_FALSE(cmp("abc", "ab"));
}

// Test with strings of same length where only last char differs
TEST_F(LengthThenLexTest_467, SameLengthLastCharDiffers_467) {
  EXPECT_TRUE(cmp("aaa", "aab"));
  EXPECT_FALSE(cmp("aab", "aaa"));
}

// Test that the comparator can be used with std::sort
TEST_F(LengthThenLexTest_467, UsableWithSort_467) {
  std::vector<std::string> v = {"bbb", "aa", "a", "cc", "aaa", "b"};
  std::sort(v.begin(), v.end(), cmp);

  // Expected order: length 1 first (a, b), then length 2 (aa, cc), then length 3 (aaa, bbb)
  ASSERT_EQ(v.size(), 6u);
  EXPECT_EQ(v[0], "a");
  EXPECT_EQ(v[1], "b");
  EXPECT_EQ(v[2], "aa");
  EXPECT_EQ(v[3], "cc");
  EXPECT_EQ(v[4], "aaa");
  EXPECT_EQ(v[5], "bbb");
}

// Test that the comparator can be used with std::set
TEST_F(LengthThenLexTest_467, UsableWithSet_467) {
  std::set<std::string, Prefilter::LengthThenLex> s;
  s.insert("bb");
  s.insert("a");
  s.insert("cc");
  s.insert("aaa");

  auto it = s.begin();
  EXPECT_EQ(*it++, "a");
  EXPECT_EQ(*it++, "bb");
  EXPECT_EQ(*it++, "cc");
  EXPECT_EQ(*it++, "aaa");
  EXPECT_EQ(it, s.end());
}

// Test irreflexivity: cmp(x, x) must be false
TEST_F(LengthThenLexTest_467, Irreflexivity_467) {
  EXPECT_FALSE(cmp("test", "test"));
  EXPECT_FALSE(cmp("hello world", "hello world"));
}

// Test asymmetry: if cmp(a, b) then !cmp(b, a)
TEST_F(LengthThenLexTest_467, Asymmetry_467) {
  std::vector<std::pair<std::string, std::string>> pairs = {
    {"a", "b"}, {"a", "ab"}, {"abc", "abd"}, {"x", "yz"}, {"", "a"}
  };
  for (const auto& p : pairs) {
    if (cmp(p.first, p.second)) {
      EXPECT_FALSE(cmp(p.second, p.first))
          << "Asymmetry violated for (" << p.first << ", " << p.second << ")";
    }
  }
}

// Test transitivity with three strings of increasing length
TEST_F(LengthThenLexTest_467, Transitivity_467) {
  // a < bb < ccc by length
  EXPECT_TRUE(cmp("a", "bb"));
  EXPECT_TRUE(cmp("bb", "ccc"));
  EXPECT_TRUE(cmp("a", "ccc"));
}

// Test with longer multi-character strings of same length
TEST_F(LengthThenLexTest_467, LongerSameLengthStrings_467) {
  EXPECT_TRUE(cmp("apple", "grape"));
  EXPECT_FALSE(cmp("grape", "apple"));
  EXPECT_TRUE(cmp("abcde", "abcdf"));
  EXPECT_FALSE(cmp("abcdf", "abcde"));
}

// Test with strings containing special characters
TEST_F(LengthThenLexTest_467, SpecialCharacters_467) {
  EXPECT_TRUE(cmp("!", "a"));  // '!' (33) < 'a' (97), same length
  EXPECT_FALSE(cmp("a", "!"));
  EXPECT_TRUE(cmp(" ", "!"));  // ' ' (32) < '!' (33)
}
