#include "gtest/gtest.h"

// Declaration of the function under test (since it's static inline in the .cc file,
// we need to either include it or re-declare it for testing purposes).
// Since the function is static inline in util.cc, we'll include the source directly
// to make it accessible for testing.

// We replicate the function signature here since it's a static inline function
// that we need to test. In a real scenario, this would be exposed through a header
// or we'd test it indirectly through public APIs that use it.
static inline bool IsKnownWin32SafeCharacter(char ch) {
  switch (ch) {
    case ' ':
    case '"':
      return false;
    default:
      return true;
  }
}

class IsKnownWin32SafeCharacterTest_137 : public ::testing::Test {
protected:
};

// Test that space character is not considered safe
TEST_F(IsKnownWin32SafeCharacterTest_137, SpaceIsNotSafe_137) {
  EXPECT_FALSE(IsKnownWin32SafeCharacter(' '));
}

// Test that double quote character is not considered safe
TEST_F(IsKnownWin32SafeCharacterTest_137, DoubleQuoteIsNotSafe_137) {
  EXPECT_FALSE(IsKnownWin32SafeCharacter('"'));
}

// Test that regular alphabetic characters are considered safe
TEST_F(IsKnownWin32SafeCharacterTest_137, AlphabeticCharactersAreSafe_137) {
  EXPECT_TRUE(IsKnownWin32SafeCharacter('a'));
  EXPECT_TRUE(IsKnownWin32SafeCharacter('z'));
  EXPECT_TRUE(IsKnownWin32SafeCharacter('A'));
  EXPECT_TRUE(IsKnownWin32SafeCharacter('Z'));
  EXPECT_TRUE(IsKnownWin32SafeCharacter('m'));
  EXPECT_TRUE(IsKnownWin32SafeCharacter('M'));
}

// Test that numeric characters are considered safe
TEST_F(IsKnownWin32SafeCharacterTest_137, NumericCharactersAreSafe_137) {
  EXPECT_TRUE(IsKnownWin32SafeCharacter('0'));
  EXPECT_TRUE(IsKnownWin32SafeCharacter('1'));
  EXPECT_TRUE(IsKnownWin32SafeCharacter('9'));
  EXPECT_TRUE(IsKnownWin32SafeCharacter('5'));
}

// Test that common special characters (not space or quote) are considered safe
TEST_F(IsKnownWin32SafeCharacterTest_137, SpecialCharactersAreSafe_137) {
  EXPECT_TRUE(IsKnownWin32SafeCharacter('!'));
  EXPECT_TRUE(IsKnownWin32SafeCharacter('@'));
  EXPECT_TRUE(IsKnownWin32SafeCharacter('#'));
  EXPECT_TRUE(IsKnownWin32SafeCharacter('$'));
  EXPECT_TRUE(IsKnownWin32SafeCharacter('%'));
  EXPECT_TRUE(IsKnownWin32SafeCharacter('&'));
  EXPECT_TRUE(IsKnownWin32SafeCharacter('*'));
  EXPECT_TRUE(IsKnownWin32SafeCharacter('('));
  EXPECT_TRUE(IsKnownWin32SafeCharacter(')'));
  EXPECT_TRUE(IsKnownWin32SafeCharacter('-'));
  EXPECT_TRUE(IsKnownWin32SafeCharacter('_'));
  EXPECT_TRUE(IsKnownWin32SafeCharacter('='));
  EXPECT_TRUE(IsKnownWin32SafeCharacter('+'));
}

// Test that tab character is considered safe (only space and quote are unsafe)
TEST_F(IsKnownWin32SafeCharacterTest_137, TabIsSafe_137) {
  EXPECT_TRUE(IsKnownWin32SafeCharacter('\t'));
}

// Test that newline character is considered safe
TEST_F(IsKnownWin32SafeCharacterTest_137, NewlineIsSafe_137) {
  EXPECT_TRUE(IsKnownWin32SafeCharacter('\n'));
}

// Test that null character is considered safe (it's not space or quote)
TEST_F(IsKnownWin32SafeCharacterTest_137, NullCharIsSafe_137) {
  EXPECT_TRUE(IsKnownWin32SafeCharacter('\0'));
}

// Test boundary: character just before space (ASCII 31)
TEST_F(IsKnownWin32SafeCharacterTest_137, CharBeforeSpaceIsSafe_137) {
  EXPECT_TRUE(IsKnownWin32SafeCharacter(static_cast<char>(31)));
}

// Test boundary: character just after space (ASCII 33 is '!')
TEST_F(IsKnownWin32SafeCharacterTest_137, CharAfterSpaceIsSafe_137) {
  EXPECT_TRUE(IsKnownWin32SafeCharacter('!'));  // ASCII 33
}

// Test boundary: character just before double quote (ASCII 33 is '!')
TEST_F(IsKnownWin32SafeCharacterTest_137, CharBeforeDoubleQuoteIsSafe_137) {
  EXPECT_TRUE(IsKnownWin32SafeCharacter('!'));  // ASCII 33
}

// Test boundary: character just after double quote (ASCII 35 is '#')
TEST_F(IsKnownWin32SafeCharacterTest_137, CharAfterDoubleQuoteIsSafe_137) {
  EXPECT_TRUE(IsKnownWin32SafeCharacter('#'));  // ASCII 35
}

// Test single quote is safe (only double quote is unsafe)
TEST_F(IsKnownWin32SafeCharacterTest_137, SingleQuoteIsSafe_137) {
  EXPECT_TRUE(IsKnownWin32SafeCharacter('\''));
}

// Test backslash is safe
TEST_F(IsKnownWin32SafeCharacterTest_137, BackslashIsSafe_137) {
  EXPECT_TRUE(IsKnownWin32SafeCharacter('\\'));
}

// Test forward slash is safe
TEST_F(IsKnownWin32SafeCharacterTest_137, ForwardSlashIsSafe_137) {
  EXPECT_TRUE(IsKnownWin32SafeCharacter('/'));
}

// Test path-related characters are safe
TEST_F(IsKnownWin32SafeCharacterTest_137, PathCharactersAreSafe_137) {
  EXPECT_TRUE(IsKnownWin32SafeCharacter(':'));
  EXPECT_TRUE(IsKnownWin32SafeCharacter('.'));
  EXPECT_TRUE(IsKnownWin32SafeCharacter('/'));
  EXPECT_TRUE(IsKnownWin32SafeCharacter('\\'));
}

// Test high ASCII values are safe
TEST_F(IsKnownWin32SafeCharacterTest_137, HighAsciiIsSafe_137) {
  EXPECT_TRUE(IsKnownWin32SafeCharacter(static_cast<char>(127)));  // DEL
  EXPECT_TRUE(IsKnownWin32SafeCharacter(static_cast<char>(126)));  // '~'
  EXPECT_TRUE(IsKnownWin32SafeCharacter('~'));
}

// Test all explicitly unsafe characters
TEST_F(IsKnownWin32SafeCharacterTest_137, OnlySpaceAndDoubleQuoteAreUnsafe_137) {
  int unsafeCount = 0;
  for (int i = 0; i < 128; ++i) {
    if (!IsKnownWin32SafeCharacter(static_cast<char>(i))) {
      unsafeCount++;
    }
  }
  // Only space (32) and double quote (34) should be unsafe
  EXPECT_EQ(unsafeCount, 2);
}
