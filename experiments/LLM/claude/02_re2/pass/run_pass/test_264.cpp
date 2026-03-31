#include "gtest/gtest.h"
#include "re2/re2.h"
#include <string>

namespace re2 {

// Test fixture for MaxSubmatch tests
class RE2MaxSubmatchTest_264 : public ::testing::Test {
protected:
};

// Normal operation: single backreference
TEST_F(RE2MaxSubmatchTest_264, SingleBackreference_264) {
  EXPECT_EQ(1, RE2::MaxSubmatch("\\1"));
}

// Normal operation: multiple backreferences, returns the max
TEST_F(RE2MaxSubmatchTest_264, MultipleBackreferencesReturnsMax_264) {
  EXPECT_EQ(5, RE2::MaxSubmatch("\\1\\3\\5\\2"));
}

// Normal operation: backreference \\0
TEST_F(RE2MaxSubmatchTest_264, BackreferenceZero_264) {
  EXPECT_EQ(0, RE2::MaxSubmatch("\\0"));
}

// Normal operation: backreference \\9 (highest single digit)
TEST_F(RE2MaxSubmatchTest_264, BackreferenceNine_264) {
  EXPECT_EQ(9, RE2::MaxSubmatch("\\9"));
}

// Empty string should return 0
TEST_F(RE2MaxSubmatchTest_264, EmptyString_264) {
  EXPECT_EQ(0, RE2::MaxSubmatch(""));
}

// String with no backslashes returns 0
TEST_F(RE2MaxSubmatchTest_264, NoBackslashes_264) {
  EXPECT_EQ(0, RE2::MaxSubmatch("hello world"));
}

// String with backslash but no digit after it
TEST_F(RE2MaxSubmatchTest_264, BackslashFollowedByNonDigit_264) {
  EXPECT_EQ(0, RE2::MaxSubmatch("\\n\\t\\a"));
}

// String with backslash at the very end (no character follows)
TEST_F(RE2MaxSubmatchTest_264, TrailingBackslash_264) {
  EXPECT_EQ(0, RE2::MaxSubmatch("hello\\"));
}

// Mixed content: some backreferences, some non-digit escapes
TEST_F(RE2MaxSubmatchTest_264, MixedContent_264) {
  EXPECT_EQ(3, RE2::MaxSubmatch("foo\\3bar\\n\\1baz"));
}

// Only plain digits (no backslash) should not be counted
TEST_F(RE2MaxSubmatchTest_264, PlainDigitsNotCounted_264) {
  EXPECT_EQ(0, RE2::MaxSubmatch("12345"));
}

// Multiple identical backreferences
TEST_F(RE2MaxSubmatchTest_264, IdenticalBackreferences_264) {
  EXPECT_EQ(2, RE2::MaxSubmatch("\\2\\2\\2"));
}

// Backreference with text around it
TEST_F(RE2MaxSubmatchTest_264, BackreferenceWithSurroundingText_264) {
  EXPECT_EQ(7, RE2::MaxSubmatch("prefix\\7suffix"));
}

// Two consecutive backslashes: \\\\1 means backslash-backslash then '1'
// The first \\ is a backslash followed by another backslash (which is not a digit),
// then '1' is just a plain character
TEST_F(RE2MaxSubmatchTest_264, DoubleBackslashThenDigit_264) {
  // "\\\\1" in C++ string literal is two characters: '\', '\', '1'
  // First '\' sees next '\' which is not a digit -> skip
  // Then '1' is not preceded by '\' -> not counted
  EXPECT_EQ(0, RE2::MaxSubmatch("\\\\1"));
}

// Backslash followed by a letter then a digit: \\a5
TEST_F(RE2MaxSubmatchTest_264, BackslashLetterThenDigit_264) {
  EXPECT_EQ(0, RE2::MaxSubmatch("\\a5"));
}

// All single-digit backreferences present
TEST_F(RE2MaxSubmatchTest_264, AllSingleDigitBackreferences_264) {
  EXPECT_EQ(9, RE2::MaxSubmatch("\\0\\1\\2\\3\\4\\5\\6\\7\\8\\9"));
}

// Rewrite string with only backslash-digit pairs in reverse order
TEST_F(RE2MaxSubmatchTest_264, ReverseOrderBackreferences_264) {
  EXPECT_EQ(9, RE2::MaxSubmatch("\\9\\8\\7\\6\\5\\4\\3\\2\\1\\0"));
}

// Single character string (just a backslash)
TEST_F(RE2MaxSubmatchTest_264, SingleBackslashChar_264) {
  EXPECT_EQ(0, RE2::MaxSubmatch(absl::string_view("\\", 1)));
}

// Verify that only single-digit references are recognized (\\12 is \\1 followed by '2')
TEST_F(RE2MaxSubmatchTest_264, MultiDigitIsSingleDigitOnly_264) {
  // "\\12" -> backslash followed by '1' (which is digit, n=1), then '2' is plain
  EXPECT_EQ(1, RE2::MaxSubmatch("\\12"));
}

// String with embedded null bytes (using string_view)
TEST_F(RE2MaxSubmatchTest_264, EmbeddedNullByte_264) {
  std::string s("\\3");
  s.push_back('\0');
  s.append("\\5");
  EXPECT_EQ(5, RE2::MaxSubmatch(absl::string_view(s.data(), s.size())));
}

}  // namespace re2
