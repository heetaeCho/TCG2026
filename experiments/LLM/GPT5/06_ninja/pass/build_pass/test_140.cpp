// File: ./TestProjects/ninja/src/util_get_shell_escaped_string_test.cc

#include "util.h"

#include "gtest/gtest.h"

using std::string;

// TEST_ID: 140

// Verifies that when the input does not need escaping, it is simply appended.
TEST(GetShellEscapedStringTest_140, AppendsWithoutEscapingWhenNotNeeded_140) {
  string result = "prefix:";
  const string input = "abcXYZ09";

  GetShellEscapedString(input, &result);

  EXPECT_EQ("prefix:abcXYZ09", result);
}

// Verifies that an input containing spaces is wrapped in single quotes.
TEST(GetShellEscapedStringTest_140, WrapsInSingleQuotesWhenEscapingNeeded_140) {
  string result;
  const string input = "foo bar";

  GetShellEscapedString(input, &result);

  EXPECT_EQ("'foo bar'", result);
}

// Verifies proper escaping of a single embedded single quote.
TEST(GetShellEscapedStringTest_140, EscapesEmbeddedSingleQuote_140) {
  string result;
  const string input = "foo'bar";

  GetShellEscapedString(input, &result);

  // Expected POSIX-style single-quote escaping: 'foo'\''bar'
  EXPECT_EQ("'foo'\\''bar'", result);
}

// Verifies proper escaping when multiple single quotes appear in the input.
TEST(GetShellEscapedStringTest_140, EscapesMultipleSingleQuotes_140) {
  string result;
  const string input = "a'b'c";

  GetShellEscapedString(input, &result);

  // 'a'\''b'\''c'
  EXPECT_EQ("'a'\\''b'\\''c'", result);
}

// Verifies behavior for empty input (should just leave result unchanged).
TEST(GetShellEscapedStringTest_140, EmptyInputLeavesResultUnchanged_140) {
  string result = "existing";
  const string input;  // empty string

  GetShellEscapedString(input, &result);

  EXPECT_EQ("existing", result);
}

// Verifies that existing content in result is preserved and new escaped
// content is appended after it.
TEST(GetShellEscapedStringTest_140, AppendsToExistingResultWithEscaping_140) {
  string result = "prefix:";
  const string input = "with space";

  GetShellEscapedString(input, &result);

  EXPECT_EQ("prefix:'with space'", result);
}

#ifndef NDEBUG
// Verifies that passing a null result pointer triggers the internal assert
// in debug builds.
TEST(GetShellEscapedStringTest_140, NullResultPointerTriggersAssert_140) {
  // ASSERT in GetShellEscapedString should fire.
  EXPECT_DEATH_IF_SUPPORTED(
      GetShellEscapedString("test", nullptr),
      "");
}
#endif  // NDEBUG
