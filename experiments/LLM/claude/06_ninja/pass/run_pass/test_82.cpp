#include "gtest/gtest.h"
#include "string_piece_util.h"

// Test normal lowercase letters remain unchanged
TEST(ToLowerASCIITest_82, LowercaseLettersUnchanged_82) {
  for (char c = 'a'; c <= 'z'; ++c) {
    EXPECT_EQ(c, ToLowerASCII(c)) << "Failed for character: " << c;
  }
}

// Test uppercase letters are converted to lowercase
TEST(ToLowerASCIITest_82, UppercaseLettersConverted_82) {
  for (char c = 'A'; c <= 'Z'; ++c) {
    char expected = c + ('a' - 'A');
    EXPECT_EQ(expected, ToLowerASCII(c)) << "Failed for character: " << c;
  }
}

// Test digits remain unchanged
TEST(ToLowerASCIITest_82, DigitsUnchanged_82) {
  for (char c = '0'; c <= '9'; ++c) {
    EXPECT_EQ(c, ToLowerASCII(c)) << "Failed for character: " << c;
  }
}

// Test specific uppercase to lowercase conversions
TEST(ToLowerASCIITest_82, SpecificConversions_82) {
  EXPECT_EQ('a', ToLowerASCII('A'));
  EXPECT_EQ('z', ToLowerASCII('Z'));
  EXPECT_EQ('m', ToLowerASCII('M'));
}

// Test boundary: character just before 'A' (which is '@')
TEST(ToLowerASCIITest_82, CharBeforeUppercaseA_82) {
  EXPECT_EQ('@', ToLowerASCII('@'));
}

// Test boundary: character just after 'Z' (which is '[')
TEST(ToLowerASCIITest_82, CharAfterUppercaseZ_82) {
  EXPECT_EQ('[', ToLowerASCII('['));
}

// Test special characters remain unchanged
TEST(ToLowerASCIITest_82, SpecialCharactersUnchanged_82) {
  EXPECT_EQ(' ', ToLowerASCII(' '));
  EXPECT_EQ('!', ToLowerASCII('!'));
  EXPECT_EQ('/', ToLowerASCII('/'));
  EXPECT_EQ('.', ToLowerASCII('.'));
  EXPECT_EQ('-', ToLowerASCII('-'));
  EXPECT_EQ('_', ToLowerASCII('_'));
  EXPECT_EQ('~', ToLowerASCII('~'));
}

// Test null character
TEST(ToLowerASCIITest_82, NullCharUnchanged_82) {
  EXPECT_EQ('\0', ToLowerASCII('\0'));
}

// Test characters with high ASCII values
TEST(ToLowerASCIITest_82, HighASCIIUnchanged_82) {
  EXPECT_EQ(127, ToLowerASCII(127));  // DEL character
}

// Test boundary characters 'A' and 'Z' specifically
TEST(ToLowerASCIITest_82, BoundaryUppercaseAandZ_82) {
  EXPECT_EQ('a', ToLowerASCII('A'));
  EXPECT_EQ('z', ToLowerASCII('Z'));
}

// Test boundary characters 'a' and 'z' specifically (should not change)
TEST(ToLowerASCIITest_82, BoundaryLowercaseAandZ_82) {
  EXPECT_EQ('a', ToLowerASCII('a'));
  EXPECT_EQ('z', ToLowerASCII('z'));
}

// Test tab and newline characters remain unchanged
TEST(ToLowerASCIITest_82, WhitespaceCharactersUnchanged_82) {
  EXPECT_EQ('\t', ToLowerASCII('\t'));
  EXPECT_EQ('\n', ToLowerASCII('\n'));
  EXPECT_EQ('\r', ToLowerASCII('\r'));
}

// Test characters between 'Z' and 'a' (like backslash, caret, etc.)
TEST(ToLowerASCIITest_82, CharsBetweenUpperAndLowerRanges_82) {
  EXPECT_EQ('\\', ToLowerASCII('\\'));
  EXPECT_EQ(']', ToLowerASCII(']'));
  EXPECT_EQ('^', ToLowerASCII('^'));
  EXPECT_EQ('`', ToLowerASCII('`'));
}

// Test characters after lowercase 'z' remain unchanged
TEST(ToLowerASCIITest_82, CharsAfterLowercaseZ_82) {
  EXPECT_EQ('{', ToLowerASCII('{'));
  EXPECT_EQ('|', ToLowerASCII('|'));
  EXPECT_EQ('}', ToLowerASCII('}'));
}
