// File: string_needs_shell_escaping_test.cc

#include "gtest/gtest.h"

#include <string>

// Forward declaration; implementation lives in util.cc.
bool StringNeedsShellEscaping(const std::string& input);

class StringNeedsShellEscapingTest_138 : public ::testing::Test {};

// Empty input: loop body is never entered, so it should not need escaping.
TEST_F(StringNeedsShellEscapingTest_138, EmptyStringDoesNotNeedEscaping_138) {
  EXPECT_FALSE(StringNeedsShellEscaping(""));
}

// A string that consists only of characters that are known to be shell-safe
// (e.g., ASCII letters and digits) should not need escaping.
TEST_F(StringNeedsShellEscapingTest_138, AllSafeCharactersDoNotNeedEscaping_138) {
  std::string input = "ABCXYZ0123456789";
  EXPECT_FALSE(StringNeedsShellEscaping(input));
}

// If the *first* character is unsafe (e.g., space), the whole string should
// be considered as needing escaping.
TEST_F(StringNeedsShellEscapingTest_138, LeadingUnsafeCharacterNeedsEscaping_138) {
  std::string input = " abc";
  EXPECT_TRUE(StringNeedsShellEscaping(input));
}

// If an unsafe character appears in the *middle* of the string,
// the function should report that escaping is needed.
TEST_F(StringNeedsShellEscapingTest_138, MiddleUnsafeCharacterNeedsEscaping_138) {
  std::string input = "ABC DEF";
  EXPECT_TRUE(StringNeedsShellEscaping(input));
}

// If an unsafe character appears at the *end* of the string,
// it should still be detected and reported.
TEST_F(StringNeedsShellEscapingTest_138, TrailingUnsafeCharacterNeedsEscaping_138) {
  std::string input = "ABC$";
  EXPECT_TRUE(StringNeedsShellEscaping(input));
}

// Mixed safe and unsafe characters: as long as there is at least one unsafe
// character, escaping should be required.
TEST_F(StringNeedsShellEscapingTest_138, MixedSafeAndUnsafeCharactersNeedsEscaping_138) {
  std::string input = "SafePart&UnsafePart";
  EXPECT_TRUE(StringNeedsShellEscaping(input));
}

// Non-ASCII / high-bit characters are typically not considered shell-safe;
// they should cause the function to report that escaping is needed.
TEST_F(StringNeedsShellEscapingTest_138, NonAsciiCharacterNeedsEscaping_138) {
  // char with the high bit set; exact visual representation is not important.
  std::string input(1, static_cast<char>(0x80));
  EXPECT_TRUE(StringNeedsShellEscaping(input));
}

// A long string consisting only of safe characters should still be handled
// correctly and not require escaping.
TEST_F(StringNeedsShellEscapingTest_138, LongSafeStringDoesNotNeedEscaping_138) {
  std::string input;
  for (int i = 0; i < 1024; ++i) {
    input.push_back('A');  // a character that IsKnownShellSafeCharacter should accept
  }

  EXPECT_FALSE(StringNeedsShellEscaping(input));
}
