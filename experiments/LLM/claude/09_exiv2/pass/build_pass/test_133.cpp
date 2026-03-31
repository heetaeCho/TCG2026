#include <gtest/gtest.h>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>

// Include the header under test
#include "exiv2/value.hpp"

using Exiv2::LangAltValueComparator;

// Test fixture
class LangAltValueComparatorTest_133 : public ::testing::Test {
 protected:
  LangAltValueComparator comp;
};

// ============================================================
// Tests for size-based ordering (longer strings come first)
// ============================================================

TEST_F(LangAltValueComparatorTest_133, LongerStringComesFirst_133) {
  // Strings of different sizes: longer string should be "less than" (ordered first)
  EXPECT_TRUE(comp("abcde", "abc"));
}

TEST_F(LangAltValueComparatorTest_133, ShorterStringComesSecond_133) {
  // Shorter string should NOT be "less than" longer string
  EXPECT_FALSE(comp("abc", "abcde"));
}

TEST_F(LangAltValueComparatorTest_133, DifferentSizesByOne_133) {
  EXPECT_TRUE(comp("ab", "a"));
  EXPECT_FALSE(comp("a", "ab"));
}

// ============================================================
// Tests for same-size strings (case-insensitive reverse lex order)
// ============================================================

TEST_F(LangAltValueComparatorTest_133, SameSizeLexicographicGreaterComesFirst_133) {
  // Same length, compare case-insensitively with '>' comparator
  // "b" > "a" in tolower, so comp("b", "a") should be true
  EXPECT_TRUE(comp("b", "a"));
}

TEST_F(LangAltValueComparatorTest_133, SameSizeLexicographicLesserComesSecond_133) {
  EXPECT_FALSE(comp("a", "b"));
}

TEST_F(LangAltValueComparatorTest_133, SameSizeSameStringReturnsFalse_133) {
  // Identical strings: should return false (strict weak ordering)
  EXPECT_FALSE(comp("abc", "abc"));
}

TEST_F(LangAltValueComparatorTest_133, SameSizeCaseInsensitiveEqual_133) {
  // "ABC" and "abc" are equal case-insensitively, same length
  // std::lexicographical_compare with '>' should return false for equal elements
  EXPECT_FALSE(comp("ABC", "abc"));
  EXPECT_FALSE(comp("abc", "ABC"));
}

TEST_F(LangAltValueComparatorTest_133, SameSizeCaseInsensitiveOrdering_133) {
  // "B" (tolower='b') vs "a" (tolower='a'): 'b' > 'a' => true
  EXPECT_TRUE(comp("B", "a"));
  EXPECT_TRUE(comp("B", "A"));
}

TEST_F(LangAltValueComparatorTest_133, SameSizeMixedCase_133) {
  // "Za" vs "zB" - same length 2
  // tolower: 'z' vs 'z' => equal, then 'a' vs 'b' => 'a' > 'b' is false
  EXPECT_FALSE(comp("Za", "zB"));
  // Reverse: 'z' vs 'z' => equal, then 'b' vs 'a' => 'b' > 'a' is true
  EXPECT_TRUE(comp("zB", "Za"));
}

// ============================================================
// Tests with empty strings
// ============================================================

TEST_F(LangAltValueComparatorTest_133, EmptyVsEmpty_133) {
  EXPECT_FALSE(comp("", ""));
}

TEST_F(LangAltValueComparatorTest_133, EmptyVsNonEmpty_133) {
  // Non-empty has larger size, so non-empty comes first
  EXPECT_FALSE(comp("", "a"));
  EXPECT_TRUE(comp("a", ""));
}

// ============================================================
// Tests with single character strings
// ============================================================

TEST_F(LangAltValueComparatorTest_133, SingleCharSame_133) {
  EXPECT_FALSE(comp("a", "a"));
}

TEST_F(LangAltValueComparatorTest_133, SingleCharDifferentCase_133) {
  EXPECT_FALSE(comp("A", "a"));
  EXPECT_FALSE(comp("a", "A"));
}

// ============================================================
// Tests verifying it works correctly as a comparator in std::map
// ============================================================

TEST_F(LangAltValueComparatorTest_133, UsableInMapAsComparator_133) {
  std::map<std::string, std::string, LangAltValueComparator> langAltMap;
  
  langAltMap["x-default"] = "Default value";
  langAltMap["en"] = "English";
  langAltMap["de"] = "German";
  langAltMap["fr-FR"] = "French (France)";
  
  EXPECT_EQ(langAltMap.size(), 4u);
  EXPECT_EQ(langAltMap["x-default"], "Default value");
  EXPECT_EQ(langAltMap["en"], "English");
  EXPECT_EQ(langAltMap["de"], "German");
  EXPECT_EQ(langAltMap["fr-FR"], "French (France)");
}

TEST_F(LangAltValueComparatorTest_133, MapOrderingLongerKeysFirst_133) {
  std::map<std::string, int, LangAltValueComparator> m;
  m["a"] = 1;
  m["bb"] = 2;
  m["ccc"] = 3;
  
  // Iteration order: longest first
  auto it = m.begin();
  EXPECT_EQ(it->first, "ccc");
  ++it;
  EXPECT_EQ(it->first, "bb");
  ++it;
  EXPECT_EQ(it->first, "a");
}

TEST_F(LangAltValueComparatorTest_133, MapOrderingSameLengthReverseLex_133) {
  std::map<std::string, int, LangAltValueComparator> m;
  m["aa"] = 1;
  m["ab"] = 2;
  m["ba"] = 3;
  m["bb"] = 4;
  
  // Same length: reverse lexicographic (case-insensitive, '>' comparison)
  // Order should be: bb, ba, ab, aa
  std::vector<std::string> keys;
  for (const auto& kv : m) {
    keys.push_back(kv.first);
  }
  ASSERT_EQ(keys.size(), 4u);
  EXPECT_EQ(keys[0], "bb");
  EXPECT_EQ(keys[1], "ba");
  EXPECT_EQ(keys[2], "ab");
  EXPECT_EQ(keys[3], "aa");
}

TEST_F(LangAltValueComparatorTest_133, CaseInsensitiveKeysCollideInMap_133) {
  std::map<std::string, int, LangAltValueComparator> m;
  m["EN"] = 1;
  m["en"] = 2;
  
  // Since "EN" and "en" are case-insensitively equal and same length,
  // they should be treated as the same key
  EXPECT_EQ(m.size(), 1u);
  // The second insertion overwrites the first
  EXPECT_EQ(m.begin()->second, 2);
}

// ============================================================
// Tests with numeric and special characters
// ============================================================

TEST_F(LangAltValueComparatorTest_133, NumericStrings_133) {
  // "9" vs "1" - same length, '9' > '1' => true
  EXPECT_TRUE(comp("9", "1"));
  EXPECT_FALSE(comp("1", "9"));
}

TEST_F(LangAltValueComparatorTest_133, SpecialCharacters_133) {
  // Special characters: '-' (45) vs '!' (33) in ASCII
  // tolower doesn't change these. '-' > '!' => true
  EXPECT_TRUE(comp("-", "!"));
  EXPECT_FALSE(comp("!", "-"));
}

// ============================================================
// Transitivity and antisymmetry tests
// ============================================================

TEST_F(LangAltValueComparatorTest_133, Antisymmetry_133) {
  // If comp(a,b) is true, then comp(b,a) must be false
  std::string a = "xyz";
  std::string b = "abc";
  if (comp(a, b)) {
    EXPECT_FALSE(comp(b, a));
  } else if (comp(b, a)) {
    EXPECT_FALSE(comp(a, b));
  }
}

TEST_F(LangAltValueComparatorTest_133, Transitivity_133) {
  // If comp(a,b) and comp(b,c), then comp(a,c)
  std::string a = "c";
  std::string b = "b";
  std::string c = "a";
  EXPECT_TRUE(comp(a, b));
  EXPECT_TRUE(comp(b, c));
  EXPECT_TRUE(comp(a, c));
}

// ============================================================
// Realistic language tag ordering
// ============================================================

TEST_F(LangAltValueComparatorTest_133, RealisticLangTags_133) {
  // "x-default" (9 chars) should come before "en-US" (5 chars)
  EXPECT_TRUE(comp("x-default", "en-US"));
  // "en-US" (5 chars) should come before "en" (2 chars)
  EXPECT_TRUE(comp("en-US", "en"));
  // "de" and "en" are same length; 'e' > 'd' => "en" > "de"
  EXPECT_TRUE(comp("en", "de"));
}

TEST_F(LangAltValueComparatorTest_133, SameLengthLangTags_133) {
  // "fr-FR" vs "en-US" - same length (5)
  // tolower: 'f' vs 'e' => 'f' > 'e' => true
  EXPECT_TRUE(comp("fr-FR", "en-US"));
}

// ============================================================
// Usable in std::set
// ============================================================

TEST_F(LangAltValueComparatorTest_133, UsableInSet_133) {
  std::set<std::string, LangAltValueComparator> s;
  s.insert("hello");
  s.insert("world");
  s.insert("HELLO"); // Should collide with "hello"
  s.insert("hi");
  
  // "hello" and "HELLO" are same length and case-insensitively equal
  EXPECT_EQ(s.size(), 3u);
  EXPECT_NE(s.find("hello"), s.end());
  EXPECT_NE(s.find("HELLO"), s.end()); // finds same element
}
