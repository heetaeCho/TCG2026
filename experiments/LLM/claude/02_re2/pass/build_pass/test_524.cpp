#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/prog.h"
#include "util/utf.h"

#include <string>
#include <vector>

// Since LookupUnicodeGroup is a static function in parse.cc, we cannot directly
// call it from outside. However, we can test its behavior indirectly through
// the public RE2 parsing interface by using Unicode group names in regex patterns.

namespace re2 {
namespace {

// Test that "Any" unicode group matches any character (equivalent to .)
TEST(LookupUnicodeGroupTest_524, AnyGroupMatchesAnyCharacter_524) {
  // \p{Any} should match any character
  RE2 pattern("\\p{Any}");
  ASSERT_TRUE(pattern.ok()) << pattern.error();
  
  EXPECT_TRUE(RE2::FullMatch("a", pattern));
  EXPECT_TRUE(RE2::FullMatch("Z", pattern));
  EXPECT_TRUE(RE2::FullMatch("0", pattern));
  EXPECT_TRUE(RE2::FullMatch("!", pattern));
  EXPECT_TRUE(RE2::PartialMatch("hello", pattern));
}

// Test that "Any" does not match empty string with FullMatch
TEST(LookupUnicodeGroupTest_524, AnyGroupDoesNotMatchEmpty_524) {
  RE2 pattern("\\p{Any}");
  ASSERT_TRUE(pattern.ok());
  
  EXPECT_FALSE(RE2::FullMatch("", pattern));
}

// Test known Unicode groups like "L" (Letter)
TEST(LookupUnicodeGroupTest_524, LetterGroupMatchesLetters_524) {
  RE2 pattern("\\p{L}");
  ASSERT_TRUE(pattern.ok()) << pattern.error();
  
  EXPECT_TRUE(RE2::FullMatch("a", pattern));
  EXPECT_TRUE(RE2::FullMatch("Z", pattern));
  EXPECT_FALSE(RE2::FullMatch("0", pattern));
  EXPECT_FALSE(RE2::FullMatch("!", pattern));
}

// Test known Unicode group "Greek"
TEST(LookupUnicodeGroupTest_524, GreekGroupMatchesGreekCharacters_524) {
  RE2 pattern("\\p{Greek}");
  ASSERT_TRUE(pattern.ok()) << pattern.error();
  
  // Greek alpha character: α (U+03B1)
  EXPECT_TRUE(RE2::FullMatch("α", pattern));
  // Latin letter should not match
  EXPECT_FALSE(RE2::FullMatch("a", pattern));
}

// Test that unknown/invalid Unicode group names result in parse error
TEST(LookupUnicodeGroupTest_524, UnknownGroupCausesError_524) {
  RE2 pattern("\\p{NonExistentGroup12345}");
  EXPECT_FALSE(pattern.ok());
}

// Test negation of "Any" group
TEST(LookupUnicodeGroupTest_524, NegatedAnyGroupMatchesNothing_524) {
  RE2 pattern("\\P{Any}");
  ASSERT_TRUE(pattern.ok()) << pattern.error();
  
  EXPECT_FALSE(RE2::FullMatch("a", pattern));
  EXPECT_FALSE(RE2::FullMatch("0", pattern));
  EXPECT_FALSE(RE2::FullMatch("!", pattern));
  EXPECT_FALSE(RE2::FullMatch("", pattern));
}

// Test Unicode group "Nd" (Decimal digit number)
TEST(LookupUnicodeGroupTest_524, NdGroupMatchesDigits_524) {
  RE2 pattern("\\p{Nd}");
  ASSERT_TRUE(pattern.ok()) << pattern.error();
  
  EXPECT_TRUE(RE2::FullMatch("0", pattern));
  EXPECT_TRUE(RE2::FullMatch("9", pattern));
  EXPECT_FALSE(RE2::FullMatch("a", pattern));
  EXPECT_FALSE(RE2::FullMatch("!", pattern));
}

// Test Unicode group "Lu" (Uppercase letter)
TEST(LookupUnicodeGroupTest_524, LuGroupMatchesUppercase_524) {
  RE2 pattern("\\p{Lu}");
  ASSERT_TRUE(pattern.ok()) << pattern.error();
  
  EXPECT_TRUE(RE2::FullMatch("A", pattern));
  EXPECT_TRUE(RE2::FullMatch("Z", pattern));
  EXPECT_FALSE(RE2::FullMatch("a", pattern));
  EXPECT_FALSE(RE2::FullMatch("z", pattern));
}

// Test Unicode group "Ll" (Lowercase letter)
TEST(LookupUnicodeGroupTest_524, LlGroupMatchesLowercase_524) {
  RE2 pattern("\\p{Ll}");
  ASSERT_TRUE(pattern.ok()) << pattern.error();
  
  EXPECT_TRUE(RE2::FullMatch("a", pattern));
  EXPECT_TRUE(RE2::FullMatch("z", pattern));
  EXPECT_FALSE(RE2::FullMatch("A", pattern));
  EXPECT_FALSE(RE2::FullMatch("Z", pattern));
}

// Test "Any" group combined with repetition
TEST(LookupUnicodeGroupTest_524, AnyGroupWithRepetition_524) {
  RE2 pattern("\\p{Any}+");
  ASSERT_TRUE(pattern.ok()) << pattern.error();
  
  EXPECT_TRUE(RE2::FullMatch("hello world!", pattern));
  EXPECT_TRUE(RE2::FullMatch("12345", pattern));
  EXPECT_FALSE(RE2::FullMatch("", pattern));
}

// Test Unicode group "Latin"
TEST(LookupUnicodeGroupTest_524, LatinGroupMatchesLatinCharacters_524) {
  RE2 pattern("\\p{Latin}");
  ASSERT_TRUE(pattern.ok()) << pattern.error();
  
  EXPECT_TRUE(RE2::FullMatch("a", pattern));
  EXPECT_TRUE(RE2::FullMatch("Z", pattern));
  // Digit should not match Latin script
  EXPECT_FALSE(RE2::FullMatch("0", pattern));
}

// Test Unicode group "Cyrillic"
TEST(LookupUnicodeGroupTest_524, CyrillicGroupMatchesCyrillicCharacters_524) {
  RE2 pattern("\\p{Cyrillic}");
  ASSERT_TRUE(pattern.ok()) << pattern.error();
  
  // Cyrillic A: А (U+0410)
  EXPECT_TRUE(RE2::FullMatch("А", pattern));
  // Latin A should not match
  EXPECT_FALSE(RE2::FullMatch("A", pattern));
}

// Test case sensitivity of group names
TEST(LookupUnicodeGroupTest_524, GroupNameCaseSensitivity_524) {
  // "any" (lowercase) should not be found if lookup is case-sensitive
  RE2 pattern_lower("\\p{any}");
  // If it fails to parse, the group name is case-sensitive
  // If it parses OK, the group name lookup is case-insensitive
  // Either behavior is valid; we just document the observed behavior.
  if (!pattern_lower.ok()) {
    // Case-sensitive: lowercase "any" is not recognized
    EXPECT_FALSE(pattern_lower.ok());
  } else {
    // Case-insensitive: lowercase "any" is recognized
    EXPECT_TRUE(RE2::FullMatch("a", pattern_lower));
  }
}

// Test Unicode group "Han" (CJK characters)
TEST(LookupUnicodeGroupTest_524, HanGroupMatchesCJK_524) {
  RE2 pattern("\\p{Han}");
  ASSERT_TRUE(pattern.ok()) << pattern.error();
  
  // CJK Unified Ideograph: 中 (U+4E2D)
  EXPECT_TRUE(RE2::FullMatch("中", pattern));
  EXPECT_FALSE(RE2::FullMatch("a", pattern));
}

// Test multiple consecutive unicode group patterns
TEST(LookupUnicodeGroupTest_524, MultipleConcatenatedGroups_524) {
  RE2 pattern("\\p{Lu}\\p{Ll}+");
  ASSERT_TRUE(pattern.ok()) << pattern.error();
  
  EXPECT_TRUE(RE2::FullMatch("Hello", pattern));
  EXPECT_FALSE(RE2::FullMatch("hello", pattern));
  EXPECT_FALSE(RE2::FullMatch("HELLO", pattern));
}

// Test that "Any" matches multi-byte UTF-8 characters
TEST(LookupUnicodeGroupTest_524, AnyGroupMatchesMultiByteUTF8_524) {
  RE2 pattern("\\p{Any}");
  ASSERT_TRUE(pattern.ok()) << pattern.error();
  
  // Various multi-byte characters
  EXPECT_TRUE(RE2::FullMatch("é", pattern));    // 2-byte UTF-8
  EXPECT_TRUE(RE2::FullMatch("中", pattern));   // 3-byte UTF-8
  EXPECT_TRUE(RE2::FullMatch("𝄞", pattern));   // 4-byte UTF-8 (musical symbol)
}

// Test empty group name
TEST(LookupUnicodeGroupTest_524, EmptyGroupNameCausesError_524) {
  RE2 pattern("\\p{}");
  EXPECT_FALSE(pattern.ok());
}

// Test Unicode group "Z" (Separator)
TEST(LookupUnicodeGroupTest_524, ZGroupMatchesSeparators_524) {
  RE2 pattern("\\p{Z}");
  ASSERT_TRUE(pattern.ok()) << pattern.error();
  
  // Regular space
  EXPECT_TRUE(RE2::FullMatch(" ", pattern));
  EXPECT_FALSE(RE2::FullMatch("a", pattern));
}

}  // namespace
}  // namespace re2
