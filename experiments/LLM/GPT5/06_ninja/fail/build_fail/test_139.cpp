// File: util_string_needs_win32_escaping_test_139.cc

#include <string>
#include <gtest/gtest.h>

// For tests involving a static function in util.cc, we include the .cc file
// so that the internal function is visible in this translation unit.
#include "ninja/src/util.cc"

using std::string;

// We assume StringNeedsWin32Escaping is available in this TU via the include above.

//------------------------------------------------------------------------------
// Normal / basic behavior
//------------------------------------------------------------------------------

TEST(StringNeedsWin32EscapingTest_139, EmptyStringDoesNotNeedEscaping_139) {
  const string input = "";
  EXPECT_FALSE(StringNeedsWin32Escaping(input))
      << "Empty string should not require Win32 escaping.";
}

TEST(StringNeedsWin32EscapingTest_139, SafeAsciiCharactersDoNotNeedEscaping_139) {
  // Use characters that are commonly considered safe in Win32 command lines:
  // letters, digits, underscore, dash, dot, and backslash.
  const string input = "abcXYZ0123456789_-.\\";
  EXPECT_FALSE(StringNeedsWin32Escaping(input))
      << "String with only known safe characters should not need escaping.";
}

//------------------------------------------------------------------------------
// Presence of clearly unsafe characters
//------------------------------------------------------------------------------

TEST(StringNeedsWin32EscapingTest_139, SpaceCausesEscapingNeeded_139) {
  const string input = "path with space";
  EXPECT_TRUE(StringNeedsWin32Escaping(input))
      << "Space in the string should require Win32 escaping.";
}

TEST(StringNeedsWin32EscapingTest_139, WildcardCharactersCauseEscapingNeeded_139) {
  // '?' and '*' are typical shell wildcard characters and are generally unsafe.
  const string input1 = "file?.txt";
  const string input2 = "file*.txt";

  EXPECT_TRUE(StringNeedsWin32Escaping(input1))
      << "Question mark in the string should require Win32 escaping.";
  EXPECT_TRUE(StringNeedsWin32Escaping(input2))
      << "Asterisk in the string should require Win32 escaping.";
}

TEST(StringNeedsWin32EscapingTest_139, QuoteCharacterCausesEscapingNeeded_139) {
  const string input = "name\"withquote";
  EXPECT_TRUE(StringNeedsWin32Escaping(input))
      << "Double quote in the string should require Win32 escaping.";
}

//------------------------------------------------------------------------------
// Position of unsafe character (beginning, middle, end)
//------------------------------------------------------------------------------

TEST(StringNeedsWin32EscapingTest_139, UnsafeCharacterAtBeginning_139) {
  const string input = "#startsWithHash";
  EXPECT_TRUE(StringNeedsWin32Escaping(input))
      << "Unsafe character at the beginning should cause escaping.";
}

TEST(StringNeedsWin32EscapingTest_139, UnsafeCharacterInMiddle_139) {
  const string input = "foo bar";
  EXPECT_TRUE(StringNeedsWin32Escaping(input))
      << "Unsafe character in the middle should cause escaping.";
}

TEST(StringNeedsWin32EscapingTest_139, UnsafeCharacterAtEnd_139) {
  const string input = "file?";
  EXPECT_TRUE(StringNeedsWin32Escaping(input))
      << "Unsafe character at the end should cause escaping.";
}

//------------------------------------------------------------------------------
// Non-ASCII / high-bit characters
//------------------------------------------------------------------------------

TEST(StringNeedsWin32EscapingTest_139, NonAsciiByteCausesEscapingNeeded_139) {
  // Construct a string with a single non-ASCII byte (0x80).
  string input(1, static_cast<char>(0x80));

  EXPECT_TRUE(StringNeedsWin32Escaping(input))
      << "Non-ASCII byte should require Win32 escaping.";
}
