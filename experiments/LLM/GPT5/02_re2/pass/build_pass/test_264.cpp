// File: re2_maxsubmatch_test.cc
#include <gtest/gtest.h>
#include "re2/re2.h"        // Interface under test
// If your build needs it, also include absl string_view header, but we only use std::string here.

using re2::RE2;

namespace {

// Basic / normal behavior
TEST(RE2_MaxSubmatch_264, EmptyStringReturnsZero_264) {
  EXPECT_EQ(RE2::MaxSubmatch(""), 0);
}

TEST(RE2_MaxSubmatch_264, NoBackslashesReturnsZero_264) {
  EXPECT_EQ(RE2::MaxSubmatch("abc123"), 0);
}

TEST(RE2_MaxSubmatch_264, SingleDigitAfterBackslash_264) {
  EXPECT_EQ(RE2::MaxSubmatch("\\1"), 1);
  EXPECT_EQ(RE2::MaxSubmatch("prefix\\7suffix"), 7);
}

// Multiple references: returns the maximum digit after backslashes
TEST(RE2_MaxSubmatch_264, MultipleBackslashDigitsReturnsMax_264) {
  EXPECT_EQ(RE2::MaxSubmatch("\\1\\5\\3"), 5);
  EXPECT_EQ(RE2::MaxSubmatch("a\\2b\\9c\\0d\\4"), 9);
}

// Non-digit after backslash should be ignored
TEST(RE2_MaxSubmatch_264, NonDigitAfterBackslashIgnored_264) {
  EXPECT_EQ(RE2::MaxSubmatch("\\a\\b\\c"), 0);
  EXPECT_EQ(RE2::MaxSubmatch("x\\y z\\_"), 0);
}

// Trailing backslash (nothing follows) should be ignored
TEST(RE2_MaxSubmatch_264, TrailingBackslashIgnored_264) {
  EXPECT_EQ(RE2::MaxSubmatch("endswithslash\\"), 0);
}

// Only the immediate char after '\' is considered (multi-digit refs are not parsed)
// For "\12", only '1' counts; the '2' is not considered since it is not preceded by '\'.
TEST(RE2_MaxSubmatch_264, MultiDigitSequenceOnlyCountsFirstDigit_264) {
  EXPECT_EQ(RE2::MaxSubmatch("\\12"), 1);
  EXPECT_EQ(RE2::MaxSubmatch("x\\12y\\9"), 9);  // still returns the max across all valid occurrences
}

// Adjacent backslashes: second '\' can introduce a valid digit sequence later
// "\\9" -> first '\' sees second '\' (not a digit), loop continues; second '\' then sees '9' -> 9
TEST(RE2_MaxSubmatch_264, DoubleBackslashThenDigit_264) {
  EXPECT_EQ(RE2::MaxSubmatch("\\\\9"), 9);
}

// Mixed content with various escapes
TEST(RE2_MaxSubmatch_264, IntermixedTextAndEscapes_264) {
  EXPECT_EQ(RE2::MaxSubmatch("foo\\3bar\\a\\9end"), 9);
}

// Non-ASCII “digits” should be ignored by ascii_isdigit
// e.g., fullwidth '９' (U+FF19) after backslash does not count
TEST(RE2_MaxSubmatch_264, NonAsciiDigitAfterBackslashIgnored_264) {
  // UTF-8 encoding of "＼９" (backslash + fullwidth digit nine)
  const std::string s = "\\\xEF\xBC\x99";  // backslash + U+FF19
  EXPECT_EQ(RE2::MaxSubmatch(s), 0);
}

}  // namespace
