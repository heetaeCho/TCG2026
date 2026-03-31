#include "gtest/gtest.h"

// Declaration of the function under test
bool islatinalpha(int c);

// Normal operation: lowercase letters
TEST(IsLatinAlphaTest_145, LowercaseA_145) {
  EXPECT_TRUE(islatinalpha('a'));
}

TEST(IsLatinAlphaTest_145, LowercaseZ_145) {
  EXPECT_TRUE(islatinalpha('z'));
}

TEST(IsLatinAlphaTest_145, LowercaseM_145) {
  EXPECT_TRUE(islatinalpha('m'));
}

// Normal operation: uppercase letters
TEST(IsLatinAlphaTest_145, UppercaseA_145) {
  EXPECT_TRUE(islatinalpha('A'));
}

TEST(IsLatinAlphaTest_145, UppercaseZ_145) {
  EXPECT_TRUE(islatinalpha('Z'));
}

TEST(IsLatinAlphaTest_145, UppercaseM_145) {
  EXPECT_TRUE(islatinalpha('M'));
}

// Boundary conditions: characters just outside the lowercase range
TEST(IsLatinAlphaTest_145, CharBeforeLowercaseA_145) {
  EXPECT_FALSE(islatinalpha('a' - 1));
}

TEST(IsLatinAlphaTest_145, CharAfterLowercaseZ_145) {
  EXPECT_FALSE(islatinalpha('z' + 1));
}

// Boundary conditions: characters just outside the uppercase range
TEST(IsLatinAlphaTest_145, CharBeforeUppercaseA_145) {
  EXPECT_FALSE(islatinalpha('A' - 1));
}

TEST(IsLatinAlphaTest_145, CharAfterUppercaseZ_145) {
  EXPECT_FALSE(islatinalpha('Z' + 1));
}

// Non-alpha characters: digits
TEST(IsLatinAlphaTest_145, Digit0_145) {
  EXPECT_FALSE(islatinalpha('0'));
}

TEST(IsLatinAlphaTest_145, Digit9_145) {
  EXPECT_FALSE(islatinalpha('9'));
}

// Non-alpha characters: special characters
TEST(IsLatinAlphaTest_145, Space_145) {
  EXPECT_FALSE(islatinalpha(' '));
}

TEST(IsLatinAlphaTest_145, Underscore_145) {
  EXPECT_FALSE(islatinalpha('_'));
}

TEST(IsLatinAlphaTest_145, Dot_145) {
  EXPECT_FALSE(islatinalpha('.'));
}

TEST(IsLatinAlphaTest_145, AtSign_145) {
  EXPECT_FALSE(islatinalpha('@'));
}

TEST(IsLatinAlphaTest_145, LeftBracket_145) {
  EXPECT_FALSE(islatinalpha('['));
}

TEST(IsLatinAlphaTest_145, Backslash_145) {
  EXPECT_FALSE(islatinalpha('\\'));
}

// Edge cases: null character
TEST(IsLatinAlphaTest_145, NullChar_145) {
  EXPECT_FALSE(islatinalpha(0));
}

// Edge cases: negative value
TEST(IsLatinAlphaTest_145, NegativeValue_145) {
  EXPECT_FALSE(islatinalpha(-1));
}

// Edge cases: large positive value
TEST(IsLatinAlphaTest_145, LargePositiveValue_145) {
  EXPECT_FALSE(islatinalpha(256));
}

// Edge cases: newline and tab
TEST(IsLatinAlphaTest_145, Newline_145) {
  EXPECT_FALSE(islatinalpha('\n'));
}

TEST(IsLatinAlphaTest_145, Tab_145) {
  EXPECT_FALSE(islatinalpha('\t'));
}

// All lowercase letters
TEST(IsLatinAlphaTest_145, AllLowercaseLetters_145) {
  for (char c = 'a'; c <= 'z'; ++c) {
    EXPECT_TRUE(islatinalpha(c)) << "Failed for character: " << c;
  }
}

// All uppercase letters
TEST(IsLatinAlphaTest_145, AllUppercaseLetters_145) {
  for (char c = 'A'; c <= 'Z'; ++c) {
    EXPECT_TRUE(islatinalpha(c)) << "Failed for character: " << c;
  }
}

// Characters between uppercase and lowercase ranges (e.g., '[', '\\', ']', '^', '_', '`')
TEST(IsLatinAlphaTest_145, CharsBetweenUpperAndLowerRanges_145) {
  for (int c = 'Z' + 1; c < 'a'; ++c) {
    EXPECT_FALSE(islatinalpha(c)) << "Should be false for character code: " << c;
  }
}

// Non-latin high-value characters (e.g., extended ASCII)
TEST(IsLatinAlphaTest_145, ExtendedAscii128_145) {
  EXPECT_FALSE(islatinalpha(128));
}

TEST(IsLatinAlphaTest_145, ExtendedAscii255_145) {
  EXPECT_FALSE(islatinalpha(255));
}
