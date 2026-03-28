#include <gtest/gtest.h>
#include <string>

// We need to include the header that declares the utility functions.
// Based on the ninja project structure:
#include "util.h"

using namespace std;

// Since StringNeedsShellEscaping and IsKnownShellSafeCharacter are static (internal linkage)
// in util.cc, we can't directly test them from outside the translation unit.
// However, they are used by GetShellEscapedString / ShellEscape which are public.
// We test the observable behavior through the public API.

// From the ninja codebase, the public interface includes:
// void GetShellEscapedString(const string& input, string* result);
// void GetWin32EscapedString(const string& input, string* result);

class UtilShellEscapeTest_138 : public ::testing::Test {
protected:
  string result_;
};

// Test that an empty string doesn't need escaping
TEST_F(UtilShellEscapeTest_138, EmptyString_138) {
  string input = "";
  GetShellEscapedString(input, &result_);
  EXPECT_EQ(input, result_);
}

// Test that a simple alphanumeric string passes through unchanged
TEST_F(UtilShellEscapeTest_138, SimpleAlphanumeric_138) {
  string input = "abc123";
  GetShellEscapedString(input, &result_);
  // Alphanumeric chars are shell-safe, so no escaping needed
  EXPECT_EQ(input, result_);
}

// Test that a string with only safe characters is not escaped
TEST_F(UtilShellEscapeTest_138, SafeCharactersOnly_138) {
  string input = "foo_bar-baz.txt";
  GetShellEscapedString(input, &result_);
  // Underscores, hyphens, dots are typically shell-safe
  EXPECT_EQ(input, result_);
}

// Test that a string with spaces gets escaped
TEST_F(UtilShellEscapeTest_138, StringWithSpaces_138) {
  string input = "foo bar";
  GetShellEscapedString(input, &result_);
  // Space is not shell-safe, so the string should be escaped (quoted)
  EXPECT_NE(input, result_);
  // The escaped result should contain the original content
  EXPECT_NE(string::npos, result_.find("foo"));
  EXPECT_NE(string::npos, result_.find("bar"));
}

// Test that a string with special shell characters gets escaped
TEST_F(UtilShellEscapeTest_138, SpecialShellCharacters_138) {
  string input = "echo \"hello\"";
  GetShellEscapedString(input, &result_);
  // Quotes are not shell-safe
  EXPECT_NE(input, result_);
}

// Test string with dollar sign
TEST_F(UtilShellEscapeTest_138, DollarSign_138) {
  string input = "$HOME";
  GetShellEscapedString(input, &result_);
  EXPECT_NE(input, result_);
}

// Test string with semicolons
TEST_F(UtilShellEscapeTest_138, Semicolon_138) {
  string input = "cmd1;cmd2";
  GetShellEscapedString(input, &result_);
  EXPECT_NE(input, result_);
}

// Test string with pipe character
TEST_F(UtilShellEscapeTest_138, PipeCharacter_138) {
  string input = "cmd1|cmd2";
  GetShellEscapedString(input, &result_);
  EXPECT_NE(input, result_);
}

// Test string with ampersand
TEST_F(UtilShellEscapeTest_138, Ampersand_138) {
  string input = "cmd1&cmd2";
  GetShellEscapedString(input, &result_);
  EXPECT_NE(input, result_);
}

// Test string with backtick
TEST_F(UtilShellEscapeTest_138, Backtick_138) {
  string input = "`command`";
  GetShellEscapedString(input, &result_);
  EXPECT_NE(input, result_);
}

// Test path-like string with slashes (should be safe)
TEST_F(UtilShellEscapeTest_138, PathWithSlashes_138) {
  string input = "/usr/local/bin/foo";
  GetShellEscapedString(input, &result_);
  // Forward slashes are typically shell-safe
  EXPECT_EQ(input, result_);
}

// Test single character safe
TEST_F(UtilShellEscapeTest_138, SingleSafeChar_138) {
  string input = "a";
  GetShellEscapedString(input, &result_);
  EXPECT_EQ(input, result_);
}

// Test single character unsafe
TEST_F(UtilShellEscapeTest_138, SingleUnsafeChar_138) {
  string input = " ";
  GetShellEscapedString(input, &result_);
  EXPECT_NE(input, result_);
}

// Test result is appended to existing content
TEST_F(UtilShellEscapeTest_138, AppendsToResult_138) {
  result_ = "prefix";
  string input = "abc";
  GetShellEscapedString(input, &result_);
  // Result should start with "prefix" since it appends
  EXPECT_EQ(0u, result_.find("prefix"));
  EXPECT_NE(string::npos, result_.find("abc"));
}

// Test string with equals sign (typically safe in ninja context)
TEST_F(UtilShellEscapeTest_138, EqualsSign_138) {
  string input = "CC=gcc";
  GetShellEscapedString(input, &result_);
  // Equals sign: behavior depends on IsKnownShellSafeCharacter
  // We just verify the function doesn't crash
  EXPECT_FALSE(result_.empty());
}

// Test string with newline character
TEST_F(UtilShellEscapeTest_138, NewlineCharacter_138) {
  string input = "line1\nline2";
  GetShellEscapedString(input, &result_);
  // Newline is not shell-safe
  EXPECT_NE(input, result_);
}

// Test string with tab character
TEST_F(UtilShellEscapeTest_138, TabCharacter_138) {
  string input = "col1\tcol2";
  GetShellEscapedString(input, &result_);
  EXPECT_NE(input, result_);
}

// Test long string with only safe characters
TEST_F(UtilShellEscapeTest_138, LongSafeString_138) {
  string input(1000, 'a');
  GetShellEscapedString(input, &result_);
  EXPECT_EQ(input, result_);
}

// Test string with parentheses
TEST_F(UtilShellEscapeTest_138, Parentheses_138) {
  string input = "foo(bar)";
  GetShellEscapedString(input, &result_);
  // Parentheses are typically not shell-safe
  EXPECT_NE(input, result_);
}

#ifdef _WIN32
class UtilWin32EscapeTest_138 : public ::testing::Test {
protected:
  string result_;
};

TEST_F(UtilWin32EscapeTest_138, EmptyString_138) {
  string input = "";
  GetWin32EscapedString(input, &result_);
  EXPECT_EQ("\"\"", result_);
}

TEST_F(UtilWin32EscapeTest_138, SimpleString_138) {
  string input = "abc";
  GetWin32EscapedString(input, &result_);
  EXPECT_FALSE(result_.empty());
}

TEST_F(UtilWin32EscapeTest_138, StringWithSpaces_138) {
  string input = "foo bar";
  GetWin32EscapedString(input, &result_);
  EXPECT_NE(input, result_);
}
#endif
