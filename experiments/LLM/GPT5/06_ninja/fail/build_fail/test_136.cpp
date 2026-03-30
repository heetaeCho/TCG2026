// File: util_is_known_shell_safe_character_test_136.cc

#include "gtest/gtest.h"

// Include the implementation file so we can access the internal static function.
// This is a common pattern in Ninja's own tests for testing internal helpers.
#include "util.cc"

class IsKnownShellSafeCharacterTest_136 : public ::testing::Test {};

// Verifies that uppercase letters are considered shell-safe.
TEST_F(IsKnownShellSafeCharacterTest_136, UppercaseLettersAreSafe_136) {
  EXPECT_TRUE(IsKnownShellSafeCharacter('A'));
  EXPECT_TRUE(IsKnownShellSafeCharacter('Z'));

  // A couple of mid-range uppercase letters as normal-operation examples.
  EXPECT_TRUE(IsKnownShellSafeCharacter('M'));
  EXPECT_TRUE(IsKnownShellSafeCharacter('Q'));
}

// Verifies that lowercase letters are considered shell-safe.
TEST_F(IsKnownShellSafeCharacterTest_136, LowercaseLettersAreSafe_136) {
  EXPECT_TRUE(IsKnownShellSafeCharacter('a'));
  EXPECT_TRUE(IsKnownShellSafeCharacter('z'));

  // Some mid-range lowercase letters as normal-operation examples.
  EXPECT_TRUE(IsKnownShellSafeCharacter('m'));
  EXPECT_TRUE(IsKnownShellSafeCharacter('q'));
}

// Verifies that digits are considered shell-safe.
TEST_F(IsKnownShellSafeCharacterTest_136, DigitsAreSafe_136) {
  EXPECT_TRUE(IsKnownShellSafeCharacter('0'));
  EXPECT_TRUE(IsKnownShellSafeCharacter('9'));

  // Some middle digits as additional checks.
  EXPECT_TRUE(IsKnownShellSafeCharacter('3'));
  EXPECT_TRUE(IsKnownShellSafeCharacter('7'));
}

// Verifies that the documented special characters are considered shell-safe.
TEST_F(IsKnownShellSafeCharacterTest_136, SpecificSymbolsAreSafe_136) {
  EXPECT_TRUE(IsKnownShellSafeCharacter('_'));
  EXPECT_TRUE(IsKnownShellSafeCharacter('+'));
  EXPECT_TRUE(IsKnownShellSafeCharacter('-'));
  EXPECT_TRUE(IsKnownShellSafeCharacter('.'));
  EXPECT_TRUE(IsKnownShellSafeCharacter('/'));
}

// Verifies that some common special characters are *not* considered shell-safe.
TEST_F(IsKnownShellSafeCharacterTest_136, CommonSpecialCharactersAreNotSafe_136) {
  EXPECT_FALSE(IsKnownShellSafeCharacter(' '));   // space
  EXPECT_FALSE(IsKnownShellSafeCharacter('*'));
  EXPECT_FALSE(IsKnownShellSafeCharacter('?'));
  EXPECT_FALSE(IsKnownShellSafeCharacter('$'));
  EXPECT_FALSE(IsKnownShellSafeCharacter('('));
  EXPECT_FALSE(IsKnownShellSafeCharacter(')'));
}

// Boundary tests around known ranges: characters just outside letters/digits.
TEST_F(IsKnownShellSafeCharacterTest_136, BoundaryCharactersAroundRanges_136) {
  // Just before and after 'A'..'Z'
  EXPECT_FALSE(IsKnownShellSafeCharacter('A' - 1));  // '@'
  EXPECT_FALSE(IsKnownShellSafeCharacter('Z' + 1));  // '['

  // Just before and after 'a'..'z'
  EXPECT_FALSE(IsKnownShellSafeCharacter('a' - 1));  // '`'
  EXPECT_FALSE(IsKnownShellSafeCharacter('z' + 1));  // '{'

  // Around digits '0'..'9'
  EXPECT_TRUE(IsKnownShellSafeCharacter('0'));       // in range
  EXPECT_TRUE(IsKnownShellSafeCharacter('9'));       // in range
  EXPECT_TRUE(IsKnownShellSafeCharacter('/'));       // explicit safe symbol
  EXPECT_FALSE(IsKnownShellSafeCharacter(':'));      // just after '9'
}

// Verifies behavior for control / non-printable characters.
TEST_F(IsKnownShellSafeCharacterTest_136, ControlAndNonPrintableCharactersAreNotSafe_136) {
  EXPECT_FALSE(IsKnownShellSafeCharacter('\0'));   // null
  EXPECT_FALSE(IsKnownShellSafeCharacter('\n'));   // newline
  EXPECT_FALSE(IsKnownShellSafeCharacter('\t'));   // tab
}
