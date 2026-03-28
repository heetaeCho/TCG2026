// File: util_getwin32escapedstring_test.cc

#include "gtest/gtest.h"
#include "util.h"

#include <string>

using std::string;

// TEST_ID = 141

// A string that does NOT need escaping should be appended as-is.
TEST(GetWin32EscapedStringTest_141, DoesNotEscapeSafeStringAndAppends_141) {
  string result = "prefix:";
  GetWin32EscapedString("simple", &result);

  EXPECT_EQ("prefix:simple", result);
}

// Empty string should be turned into "" (quoted empty string).
TEST(GetWin32EscapedStringTest_141, EmptyStringGetsWrappedInQuotes_141) {
  string result;
  GetWin32EscapedString("", &result);

  EXPECT_EQ("\"\"", result);
}

// String with spaces should be quoted, contents unchanged.
TEST(GetWin32EscapedStringTest_141, StringWithSpacesIsQuoted_141) {
  string result;
  GetWin32EscapedString("hello world", &result);

  EXPECT_EQ("\"hello world\"", result);
}

// String containing a double quote: the quote should be escaped and
// surrounding quotes added, with backslashes handled correctly.
TEST(GetWin32EscapedStringTest_141, StringWithQuoteIsEscaped_141) {
  string result;
  GetWin32EscapedString("foo\"bar", &result);

  // Expected: "foo\"bar" wrapped in quotes:
  //   -> "foo\"bar"
  EXPECT_EQ("\"foo\\\"bar\"", result);
}

// When the string needs quoting and ends with backslashes, those trailing
// backslashes should be doubled inside the quotes.
TEST(GetWin32EscapedStringTest_141, TrailingBackslashesAreDoubledWhenQuoted_141) {
  string result;
  // One trailing backslash, but overall string needs quoting (due to space).
  GetWin32EscapedString("path with space\\", &result);

  // Expected content: "path with space\\" (two backslashes before closing quote).
  EXPECT_EQ("\"path with space\\\\\"", result);
}

// Backslashes immediately before an inner quote should be correctly escaped:
// original backslash is kept, and additional backslashes are added so that
// the inner quote is preserved when parsed by Win32.
TEST(GetWin32EscapedStringTest_141, BackslashesBeforeInnerQuoteAreEscaped_141) {
  string result;
  // Path-like input with a backslash before a quote, requiring quoting.
  GetWin32EscapedString("C:\\path\\with\\quote\\\"end", &result);

  // Expected (characters):
  //   "C:\path\with\quote\\\"end"
  // As a C++ string literal (each '\' is escaped as '\\'):
  EXPECT_EQ("\"C:\\\\path\\\\with\\\\quote\\\\\\\\\\\"end\"", result);
}
