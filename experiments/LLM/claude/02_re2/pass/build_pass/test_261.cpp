#include <gtest/gtest.h>

// We need to access the static function. Since it's in a namespace but static,
// we'll need to include the source or redeclare. Since we're testing the 
// function as a black box and it's static (file-local linkage), we need to
// work around this. One common approach is to include the .cc file directly
// for testing static functions.

// Include the source file to get access to the static function
// We need to replicate enough context for it to compile
#include "re2/re2.h"

// Since ascii_strcasecmp is a static function inside re2.cc, we cannot
// directly access it from a test file. We'll include the .cc file to
// gain access to the static function for testing purposes.
namespace re2 {
// Redeclare the function signature - we include the cc file
// to get the actual implementation
static int ascii_strcasecmp(const char* a, const char* b, size_t len);
}

// Since the function is static in re2.cc, we include the implementation
// to make it accessible in this translation unit.
#include "re2/re2.cc"

namespace {

using re2::ascii_strcasecmp;

// Test: Equal strings (lowercase)
TEST(AsciiStrcasecmpTest_261, EqualLowercaseStrings_261) {
  const char* a = "hello";
  const char* b = "hello";
  EXPECT_EQ(0, ascii_strcasecmp(a, b, 5));
}

// Test: Equal strings where b has uppercase letters (should match case-insensitively for b)
TEST(AsciiStrcasecmpTest_261, BUppercaseMatchesALowercase_261) {
  const char* a = "hello";
  const char* b = "HELLO";
  EXPECT_EQ(0, ascii_strcasecmp(a, b, 5));
}

// Test: Note that only b is lowercased, not a. So uppercase A vs lowercase b should NOT match.
// The function only converts y (from b) to lowercase, not x (from a).
TEST(AsciiStrcasecmpTest_261, AUppercaseBLowercaseDoesNotMatch_261) {
  const char* a = "HELLO";
  const char* b = "hello";
  // 'H' (0x48) vs 'h' (0x68) -> 'H' - 'h' = 0x48 - 0x68 = negative
  EXPECT_NE(0, ascii_strcasecmp(a, b, 5));
}

// Test: A has uppercase, B has uppercase -> b gets lowered, a stays uppercase -> should not match
TEST(AsciiStrcasecmpTest_261, BothUppercaseMatches_261) {
  const char* a = "HELLO";
  const char* b = "HELLO";
  // b's 'H' becomes 'h', a's 'H' stays 'H'. 'H'(72) != 'h'(104)
  // Wait, actually let's re-read: only y (b) is lowered if uppercase.
  // So x='H'(72), y='H' -> y becomes 'h'(104). 72 != 104 -> not equal
  EXPECT_NE(0, ascii_strcasecmp(a, b, 5));
}

// Test: Zero length comparison should return 0
TEST(AsciiStrcasecmpTest_261, ZeroLength_261) {
  const char* a = "abc";
  const char* b = "xyz";
  EXPECT_EQ(0, ascii_strcasecmp(a, b, 0));
}

// Test: Single character equal
TEST(AsciiStrcasecmpTest_261, SingleCharEqual_261) {
  const char* a = "a";
  const char* b = "A";
  EXPECT_EQ(0, ascii_strcasecmp(a, b, 1));
}

// Test: Single character not equal
TEST(AsciiStrcasecmpTest_261, SingleCharNotEqual_261) {
  const char* a = "a";
  const char* b = "b";
  // 'a'(97) - 'b'(98) = -1
  EXPECT_LT(ascii_strcasecmp(a, b, 1), 0);
}

// Test: b greater than a after case folding
TEST(AsciiStrcasecmpTest_261, AGreaterThanB_261) {
  const char* a = "b";
  const char* b = "A";  // A becomes 'a'
  // 'b'(98) - 'a'(97) = 1
  EXPECT_GT(ascii_strcasecmp(a, b, 1), 0);
}

// Test: Partial comparison (only compare first n characters)
TEST(AsciiStrcasecmpTest_261, PartialComparison_261) {
  const char* a = "hello world";
  const char* b = "HELLO xyz";
  // Compare only first 5 chars: "hello" vs "HELLO" (b lowered)
  EXPECT_EQ(0, ascii_strcasecmp(a, b, 5));
}

// Test: Difference at the end
TEST(AsciiStrcasecmpTest_261, DifferenceAtEnd_261) {
  const char* a = "hellx";
  const char* b = "HELLO";
  // First 4 chars match (b lowered). 5th: x='x'(120) vs y='O'->o(111). 120-111=9
  EXPECT_GT(ascii_strcasecmp(a, b, 5), 0);
}

// Test: Difference at the beginning
TEST(AsciiStrcasecmpTest_261, DifferenceAtBeginning_261) {
  const char* a = "aello";
  const char* b = "HELLO";
  // x='a'(97), y='H'->'h'(104). 97-104 = -7
  EXPECT_LT(ascii_strcasecmp(a, b, 5), 0);
}

// Test: Numeric characters (not affected by case conversion)
TEST(AsciiStrcasecmpTest_261, NumericCharacters_261) {
  const char* a = "12345";
  const char* b = "12345";
  EXPECT_EQ(0, ascii_strcasecmp(a, b, 5));
}

// Test: Mixed alphanumeric
TEST(AsciiStrcasecmpTest_261, MixedAlphanumeric_261) {
  const char* a = "a1b2c";
  const char* b = "A1B2C";
  EXPECT_EQ(0, ascii_strcasecmp(a, b, 5));
}

// Test: Special characters (not affected by lowering)
TEST(AsciiStrcasecmpTest_261, SpecialCharacters_261) {
  const char* a = "!@#$%";
  const char* b = "!@#$%";
  EXPECT_EQ(0, ascii_strcasecmp(a, b, 5));
}

// Test: Boundary of uppercase range - 'A' and 'Z'
TEST(AsciiStrcasecmpTest_261, BoundaryUppercaseA_261) {
  const char* a = "a";
  const char* b = "A";
  EXPECT_EQ(0, ascii_strcasecmp(a, b, 1));
}

TEST(AsciiStrcasecmpTest_261, BoundaryUppercaseZ_261) {
  const char* a = "z";
  const char* b = "Z";
  EXPECT_EQ(0, ascii_strcasecmp(a, b, 1));
}

// Test: Character just before 'A' (0x40 = '@') should NOT be lowered
TEST(AsciiStrcasecmpTest_261, CharBeforeUppercaseRange_261) {
  const char* a = "@";  // 0x40
  const char* b = "@";  // 0x40, not in A-Z so not lowered
  EXPECT_EQ(0, ascii_strcasecmp(a, b, 1));
}

// Test: Character just after 'Z' (0x5B = '[') should NOT be lowered
TEST(AsciiStrcasecmpTest_261, CharAfterUppercaseRange_261) {
  const char* a = "[";  // 0x5B
  const char* b = "[";  // 0x5B, not in A-Z so not lowered
  EXPECT_EQ(0, ascii_strcasecmp(a, b, 1));
}

// Test: Null bytes in the middle
TEST(AsciiStrcasecmpTest_261, NullBytesInMiddle_261) {
  const char a[] = {'a', '\0', 'b'};
  const char b[] = {'A', '\0', 'B'};
  EXPECT_EQ(0, ascii_strcasecmp(a, b, 3));
}

// Test: Length 1 with different values
TEST(AsciiStrcasecmpTest_261, LengthOneReturnValue_261) {
  const char* a = "z";
  const char* b = "A";  // becomes 'a'
  // 'z'(122) - 'a'(97) = 25
  EXPECT_EQ(25, ascii_strcasecmp(a, b, 1));
}

}  // namespace
