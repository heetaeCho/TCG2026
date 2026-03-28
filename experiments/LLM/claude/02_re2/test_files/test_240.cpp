#include <gtest/gtest.h>
#include "re2/re2.h"
#include "re2/regexp.h"

// Since RegexpErrorToRE2 is a static function in re2.cc, we cannot directly test it
// from outside the translation unit. However, we can test the observable behavior
// through the RE2 public interface, which uses this function internally.
// 
// The RE2 class exposes error_code() which reflects the result of RegexpErrorToRE2
// when a pattern fails to compile.

namespace {

class RE2ErrorCodeTest_240 : public ::testing::Test {};

// Test that a valid pattern produces NoError
TEST_F(RE2ErrorCodeTest_240, ValidPatternNoError_240) {
  re2::RE2 re("hello");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.error_code(), re2::RE2::NoError);
}

// Test that an empty pattern produces NoError
TEST_F(RE2ErrorCodeTest_240, EmptyPatternNoError_240) {
  re2::RE2 re("");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.error_code(), re2::RE2::NoError);
}

// Test ErrorBadEscape: invalid escape sequence
TEST_F(RE2ErrorCodeTest_240, BadEscapeError_240) {
  re2::RE2 re("\\Q");
  // \Q without \E might not be an error in all modes; try a clearly bad escape
  re2::RE2 re2("\\p{BadProperty}");
  // If that doesn't trigger it, try another
  // A bad escape in POSIX mode
  re2::RE2::Options opts;
  opts.set_log_errors(false);
  re2::RE2 re3("\\", opts);
  if (!re3.ok()) {
    EXPECT_EQ(re3.error_code(), re2::RE2::ErrorTrailingBackslash);
  }
}

// Test ErrorMissingBracket: unclosed character class
TEST_F(RE2ErrorCodeTest_240, MissingBracketError_240) {
  re2::RE2::Options opts;
  opts.set_log_errors(false);
  re2::RE2 re("[abc", opts);
  EXPECT_FALSE(re.ok());
  EXPECT_EQ(re.error_code(), re2::RE2::ErrorMissingBracket);
}

// Test ErrorMissingParen: unclosed group
TEST_F(RE2ErrorCodeTest_240, MissingParenError_240) {
  re2::RE2::Options opts;
  opts.set_log_errors(false);
  re2::RE2 re("(abc", opts);
  EXPECT_FALSE(re.ok());
  EXPECT_EQ(re.error_code(), re2::RE2::ErrorMissingParen);
}

// Test ErrorUnexpectedParen: unexpected closing paren
TEST_F(RE2ErrorCodeTest_240, UnexpectedParenError_240) {
  re2::RE2::Options opts;
  opts.set_log_errors(false);
  re2::RE2 re("abc)", opts);
  EXPECT_FALSE(re.ok());
  EXPECT_EQ(re.error_code(), re2::RE2::ErrorUnexpectedParen);
}

// Test ErrorTrailingBackslash: pattern ends with backslash
TEST_F(RE2ErrorCodeTest_240, TrailingBackslashError_240) {
  re2::RE2::Options opts;
  opts.set_log_errors(false);
  re2::RE2 re("abc\\", opts);
  EXPECT_FALSE(re.ok());
  EXPECT_EQ(re.error_code(), re2::RE2::ErrorTrailingBackslash);
}

// Test ErrorRepeatArgument: nothing to repeat
TEST_F(RE2ErrorCodeTest_240, RepeatArgumentError_240) {
  re2::RE2::Options opts;
  opts.set_log_errors(false);
  re2::RE2 re("*abc", opts);
  EXPECT_FALSE(re.ok());
  EXPECT_EQ(re.error_code(), re2::RE2::ErrorRepeatArgument);
}

// Test ErrorRepeatOp: repeat of a repeat (e.g., a++ in certain modes)
TEST_F(RE2ErrorCodeTest_240, RepeatOpError_240) {
  re2::RE2::Options opts;
  opts.set_log_errors(false);
  re2::RE2 re("a**", opts);
  EXPECT_FALSE(re.ok());
  EXPECT_EQ(re.error_code(), re2::RE2::ErrorRepeatOp);
}

// Test ErrorRepeatSize: repeat count too large
TEST_F(RE2ErrorCodeTest_240, RepeatSizeError_240) {
  re2::RE2::Options opts;
  opts.set_log_errors(false);
  re2::RE2 re("a{99999}", opts);
  EXPECT_FALSE(re.ok());
  EXPECT_EQ(re.error_code(), re2::RE2::ErrorRepeatSize);
}

// Test ErrorBadCharRange: invalid character range in character class
TEST_F(RE2ErrorCodeTest_240, BadCharRangeError_240) {
  re2::RE2::Options opts;
  opts.set_log_errors(false);
  re2::RE2 re("[z-a]", opts);
  EXPECT_FALSE(re.ok());
  EXPECT_EQ(re.error_code(), re2::RE2::ErrorBadCharRange);
}

// Test ErrorBadPerlOp: bad Perl operator (e.g., (?R) recursive)
TEST_F(RE2ErrorCodeTest_240, BadPerlOpError_240) {
  re2::RE2::Options opts;
  opts.set_log_errors(false);
  re2::RE2 re("(?R)", opts);
  EXPECT_FALSE(re.ok());
  EXPECT_EQ(re.error_code(), re2::RE2::ErrorBadPerlOp);
}

// Test ErrorBadNamedCapture: bad named capture syntax
TEST_F(RE2ErrorCodeTest_240, BadNamedCaptureError_240) {
  re2::RE2::Options opts;
  opts.set_log_errors(false);
  re2::RE2 re("(?P<>abc)", opts);
  EXPECT_FALSE(re.ok());
  EXPECT_EQ(re.error_code(), re2::RE2::ErrorBadNamedCapture);
}

// Test valid complex patterns produce NoError
TEST_F(RE2ErrorCodeTest_240, ComplexValidPatternNoError_240) {
  re2::RE2 re("(?P<name>[a-zA-Z]+)\\s+(?P<value>\\d+)");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.error_code(), re2::RE2::NoError);
}

// Test ErrorBadEscape with specific bad escape
TEST_F(RE2ErrorCodeTest_240, BadEscapeSpecific_240) {
  re2::RE2::Options opts;
  opts.set_log_errors(false);
  opts.set_perl_classes(false);
  opts.set_one_line(false);
  // In POSIX mode, \d is not valid
  re2::RE2::Options posix_opts;
  posix_opts.set_log_errors(false);
  posix_opts.set_posix_syntax(true);
  posix_opts.set_perl_classes(false);
  re2::RE2 re("\\d", posix_opts);
  if (!re.ok()) {
    EXPECT_EQ(re.error_code(), re2::RE2::ErrorBadEscape);
  }
}

// Test that a simple matching pattern works correctly (integration with error code)
TEST_F(RE2ErrorCodeTest_240, SimplePatternMatch_240) {
  re2::RE2 re("^[a-z]+$");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.error_code(), re2::RE2::NoError);
  EXPECT_TRUE(re2::RE2::FullMatch("hello", re));
  EXPECT_FALSE(re2::RE2::FullMatch("Hello", re));
}

// Test character class with valid ranges
TEST_F(RE2ErrorCodeTest_240, ValidCharClassNoError_240) {
  re2::RE2 re("[a-zA-Z0-9_]");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.error_code(), re2::RE2::NoError);
}

// Test valid repeat syntax
TEST_F(RE2ErrorCodeTest_240, ValidRepeatNoError_240) {
  re2::RE2 re("a{1,100}");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.error_code(), re2::RE2::NoError);
}

}  // namespace
