#include "gtest/gtest.h"
#include "re2/prog.h"

namespace re2 {

// Test normal word characters - uppercase letters
TEST(ProgIsWordCharTest_132, UppercaseLetters_132) {
  EXPECT_TRUE(Prog::IsWordChar('A'));
  EXPECT_TRUE(Prog::IsWordChar('M'));
  EXPECT_TRUE(Prog::IsWordChar('Z'));
}

// Test normal word characters - lowercase letters
TEST(ProgIsWordCharTest_132, LowercaseLetters_132) {
  EXPECT_TRUE(Prog::IsWordChar('a'));
  EXPECT_TRUE(Prog::IsWordChar('m'));
  EXPECT_TRUE(Prog::IsWordChar('z'));
}

// Test normal word characters - digits
TEST(ProgIsWordCharTest_132, Digits_132) {
  EXPECT_TRUE(Prog::IsWordChar('0'));
  EXPECT_TRUE(Prog::IsWordChar('5'));
  EXPECT_TRUE(Prog::IsWordChar('9'));
}

// Test normal word character - underscore
TEST(ProgIsWordCharTest_132, Underscore_132) {
  EXPECT_TRUE(Prog::IsWordChar('_'));
}

// Test all uppercase letters
TEST(ProgIsWordCharTest_132, AllUppercaseLetters_132) {
  for (char c = 'A'; c <= 'Z'; ++c) {
    EXPECT_TRUE(Prog::IsWordChar(static_cast<uint8_t>(c))) << "Failed for: " << c;
  }
}

// Test all lowercase letters
TEST(ProgIsWordCharTest_132, AllLowercaseLetters_132) {
  for (char c = 'a'; c <= 'z'; ++c) {
    EXPECT_TRUE(Prog::IsWordChar(static_cast<uint8_t>(c))) << "Failed for: " << c;
  }
}

// Test all digits
TEST(ProgIsWordCharTest_132, AllDigits_132) {
  for (char c = '0'; c <= '9'; ++c) {
    EXPECT_TRUE(Prog::IsWordChar(static_cast<uint8_t>(c))) << "Failed for: " << c;
  }
}

// Test boundary conditions - characters just before/after uppercase range
TEST(ProgIsWordCharTest_132, BoundaryUppercase_132) {
  EXPECT_FALSE(Prog::IsWordChar('@'));  // 'A' - 1
  EXPECT_TRUE(Prog::IsWordChar('A'));
  EXPECT_TRUE(Prog::IsWordChar('Z'));
  EXPECT_FALSE(Prog::IsWordChar('['));  // 'Z' + 1
}

// Test boundary conditions - characters just before/after lowercase range
TEST(ProgIsWordCharTest_132, BoundaryLowercase_132) {
  EXPECT_FALSE(Prog::IsWordChar('`'));  // 'a' - 1
  EXPECT_TRUE(Prog::IsWordChar('a'));
  EXPECT_TRUE(Prog::IsWordChar('z'));
  EXPECT_FALSE(Prog::IsWordChar('{'));  // 'z' + 1
}

// Test boundary conditions - characters just before/after digit range
TEST(ProgIsWordCharTest_132, BoundaryDigits_132) {
  EXPECT_FALSE(Prog::IsWordChar('/'));  // '0' - 1
  EXPECT_TRUE(Prog::IsWordChar('0'));
  EXPECT_TRUE(Prog::IsWordChar('9'));
  EXPECT_FALSE(Prog::IsWordChar(':'));  // '9' + 1
}

// Test non-word characters - common punctuation and symbols
TEST(ProgIsWordCharTest_132, NonWordCharsPunctuation_132) {
  EXPECT_FALSE(Prog::IsWordChar(' '));
  EXPECT_FALSE(Prog::IsWordChar('!'));
  EXPECT_FALSE(Prog::IsWordChar('#'));
  EXPECT_FALSE(Prog::IsWordChar('$'));
  EXPECT_FALSE(Prog::IsWordChar('%'));
  EXPECT_FALSE(Prog::IsWordChar('&'));
  EXPECT_FALSE(Prog::IsWordChar('('));
  EXPECT_FALSE(Prog::IsWordChar(')'));
  EXPECT_FALSE(Prog::IsWordChar('*'));
  EXPECT_FALSE(Prog::IsWordChar('+'));
  EXPECT_FALSE(Prog::IsWordChar(','));
  EXPECT_FALSE(Prog::IsWordChar('-'));
  EXPECT_FALSE(Prog::IsWordChar('.'));
  EXPECT_FALSE(Prog::IsWordChar(';'));
  EXPECT_FALSE(Prog::IsWordChar('<'));
  EXPECT_FALSE(Prog::IsWordChar('='));
  EXPECT_FALSE(Prog::IsWordChar('>'));
  EXPECT_FALSE(Prog::IsWordChar('?'));
  EXPECT_FALSE(Prog::IsWordChar('^'));
  EXPECT_FALSE(Prog::IsWordChar('~'));
}

// Test non-word characters - control characters
TEST(ProgIsWordCharTest_132, NonWordCharsControlChars_132) {
  EXPECT_FALSE(Prog::IsWordChar(0));    // NUL
  EXPECT_FALSE(Prog::IsWordChar(1));    // SOH
  EXPECT_FALSE(Prog::IsWordChar('\t')); // TAB
  EXPECT_FALSE(Prog::IsWordChar('\n')); // LF
  EXPECT_FALSE(Prog::IsWordChar('\r')); // CR
  EXPECT_FALSE(Prog::IsWordChar(127));  // DEL
}

// Test non-word characters - high byte values (extended ASCII)
TEST(ProgIsWordCharTest_132, NonWordCharsHighBytes_132) {
  EXPECT_FALSE(Prog::IsWordChar(128));
  EXPECT_FALSE(Prog::IsWordChar(200));
  EXPECT_FALSE(Prog::IsWordChar(255));
}

// Test that underscore neighbors are not word chars
TEST(ProgIsWordCharTest_132, UnderscoreNeighbors_132) {
  // '_' is 95
  EXPECT_FALSE(Prog::IsWordChar(94));   // '^'
  EXPECT_TRUE(Prog::IsWordChar(95));    // '_'
  EXPECT_FALSE(Prog::IsWordChar(96));   // '`'
}

// Exhaustive test: count of word characters should be exactly 63
// (26 uppercase + 26 lowercase + 10 digits + 1 underscore)
TEST(ProgIsWordCharTest_132, ExactWordCharCount_132) {
  int count = 0;
  for (int c = 0; c < 256; ++c) {
    if (Prog::IsWordChar(static_cast<uint8_t>(c))) {
      ++count;
    }
  }
  EXPECT_EQ(63, count);
}

}  // namespace re2
