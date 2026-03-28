// File: prog_iswordchar_test_132.cc
#include <gtest/gtest.h>
#include <cstdint>

// Include path may vary depending on your build setup.
// Adjust include as needed if your project structure is different.
#include "re2/prog.h"

using re2::Prog;

TEST(ProgIsWordChar_132, ReturnsTrueForUppercaseLetters_132) {
  for (uint8_t c = static_cast<uint8_t>('A'); c <= static_cast<uint8_t>('Z'); ++c) {
    EXPECT_TRUE(Prog::IsWordChar(c)) << "Expected true for uppercase letter " << char(c);
  }
}

TEST(ProgIsWordChar_132, ReturnsTrueForLowercaseLetters_132) {
  for (uint8_t c = static_cast<uint8_t>('a'); c <= static_cast<uint8_t>('z'); ++c) {
    EXPECT_TRUE(Prog::IsWordChar(c)) << "Expected true for lowercase letter " << char(c);
  }
}

TEST(ProgIsWordChar_132, ReturnsTrueForDigits_132) {
  for (uint8_t c = static_cast<uint8_t>('0'); c <= static_cast<uint8_t>('9'); ++c) {
    EXPECT_TRUE(Prog::IsWordChar(c)) << "Expected true for digit " << char(c);
  }
}

TEST(ProgIsWordChar_132, ReturnsTrueForUnderscore_132) {
  EXPECT_TRUE(Prog::IsWordChar(static_cast<uint8_t>('_')));
}

TEST(ProgIsWordChar_132, ReturnsFalseForCommonPunctuationAndSpace_132) {
  const char* chars = " -+*/=!@#$%^&()[]{}|\\;:'\",.<>?/`~";
  for (const char* p = chars; *p; ++p) {
    uint8_t c = static_cast<uint8_t>(*p);
    if (c == static_cast<uint8_t>('_')) continue;  // underscore is handled elsewhere
    EXPECT_FALSE(Prog::IsWordChar(c)) << "Expected false for punctuation/space " << *p;
  }
}

TEST(ProgIsWordChar_132, ReturnsFalseAtAlphabetBoundaries_132) {
  // Just below and above 'A'..'Z'
  EXPECT_FALSE(Prog::IsWordChar(static_cast<uint8_t>('A' - 1)));  // '@'
  EXPECT_FALSE(Prog::IsWordChar(static_cast<uint8_t>('Z' + 1)));  // '['

  // Just below and above 'a'..'z'
  EXPECT_FALSE(Prog::IsWordChar(static_cast<uint8_t>('a' - 1)));  // '`'
  EXPECT_FALSE(Prog::IsWordChar(static_cast<uint8_t>('z' + 1)));  // '{'
}

TEST(ProgIsWordChar_132, ReturnsFalseAtDigitBoundaries_132) {
  EXPECT_FALSE(Prog::IsWordChar(static_cast<uint8_t>('0' - 1)));  // '/'
  EXPECT_FALSE(Prog::IsWordChar(static_cast<uint8_t>('9' + 1)));  // ':'
}

TEST(ProgIsWordChar_132, ReturnsFalseForControlAndExtendedBytes_132) {
  // Control chars
  EXPECT_FALSE(Prog::IsWordChar(static_cast<uint8_t>(0x00)));
  EXPECT_FALSE(Prog::IsWordChar(static_cast<uint8_t>('\n')));
  EXPECT_FALSE(Prog::IsWordChar(static_cast<uint8_t>('\t')));

  // Extended (non-ASCII) bytes
  EXPECT_FALSE(Prog::IsWordChar(static_cast<uint8_t>(0x80)));
  EXPECT_FALSE(Prog::IsWordChar(static_cast<uint8_t>(0xC0)));
  EXPECT_FALSE(Prog::IsWordChar(static_cast<uint8_t>(0xFF)));
}

TEST(ProgIsWordChar_132, HandlesUnsignedPromotionSafely_132) {
  // Ensure behavior is correct regardless of char signedness in the build.
  // Cast from int to uint8_t to mimic potential negative signed char values.
  int values[] = {-1, -128, 128, 255};
  for (int v : values) {
    uint8_t c = static_cast<uint8_t>(v);
    // For these particular byte values, IsWordChar should return false.
    // (-1 -> 255), (-128 -> 128), 128, 255 are all outside [A-Za-z0-9_] range.
    EXPECT_FALSE(Prog::IsWordChar(c)) << "Expected false for byte value " << int(c);
  }
}
