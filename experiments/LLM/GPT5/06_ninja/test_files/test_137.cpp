// util_is_known_win32_safe_character_test_137.cc

#include "gtest/gtest.h"

#include "util.h"  // assumes IsKnownWin32SafeCharacter is declared here

// Tests for IsKnownWin32SafeCharacter(char)
//
// Observed behavior from the interface:
//  - Returns false for certain characters (e.g. space, double quote)
//  - Returns true for other characters (alphanumeric, punctuation, control chars, etc.)

// Verifies that a space character is not considered Win32-safe.
TEST(IsKnownWin32SafeCharacterTest_137, SpaceCharacterReturnsFalse_137) {
  EXPECT_FALSE(IsKnownWin32SafeCharacter(' '));
}

// Verifies that a double quote character is not considered Win32-safe.
TEST(IsKnownWin32SafeCharacterTest_137, DoubleQuoteCharacterReturnsFalse_137) {
  EXPECT_FALSE(IsKnownWin32SafeCharacter('"'));
}

// Verifies that typical alphanumeric characters are considered Win32-safe.
TEST(IsKnownWin32SafeCharacterTest_137, AlphaNumericCharactersReturnTrue_137) {
  EXPECT_TRUE(IsKnownWin32SafeCharacter('A'));
  EXPECT_TRUE(IsKnownWin32SafeCharacter('z'));
  EXPECT_TRUE(IsKnownWin32SafeCharacter('0'));
  EXPECT_TRUE(IsKnownWin32SafeCharacter('9'));
}

// Verifies that common punctuation characters (other than space or double quote)
// are considered Win32-safe.
TEST(IsKnownWin32SafeCharacterTest_137, PunctuationCharactersReturnTrue_137) {
  EXPECT_TRUE(IsKnownWin32SafeCharacter('_'));
  EXPECT_TRUE(IsKnownWin32SafeCharacter('-'));
  EXPECT_TRUE(IsKnownWin32SafeCharacter('.'));
  EXPECT_TRUE(IsKnownWin32SafeCharacter('\\'));
}

// Verifies behavior for control and boundary ASCII characters that are not
// explicitly excluded by the interface (i.e., not space or double quote).
TEST(IsKnownWin32SafeCharacterTest_137, ControlAndBoundaryCharactersReturnTrue_137) {
  EXPECT_TRUE(IsKnownWin32SafeCharacter('\0'));   // NUL
  EXPECT_TRUE(IsKnownWin32SafeCharacter('\n'));   // newline
  EXPECT_TRUE(IsKnownWin32SafeCharacter('\t'));   // tab
  EXPECT_TRUE(IsKnownWin32SafeCharacter(static_cast<char>(127)));  // DEL in ASCII
}
